#include "TaskbarSetup.h"
#include "resource.h"

BOOL preHandle()
{
	// ��ȡ�豸��Ϣ
	DeviceInfo.ScreenW = GetSystemMetrics(SM_CXSCREEN);	//	��ȡ��Ļ���ÿ��
	DeviceInfo.ScreenH = GetSystemMetrics(SM_CYSCREEN);	//	��ȡ��Ļ���ø߶�

	return TRUE;
}

LRESULT CALLBACK mainMsgProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	char pszText[256] = { 0 };	// ���Գ���ʱ���ַ�������

	switch (msgID)
	{
	case WM_CREATE:
		MessageBox(hWnd, __TEXT("������κ����⣬\n��ӭ�� GitHub ���ԣ��Ա������Ǽ�ʱΪ��������⣡\nhttps://github.com/SeaYJ/TaskbarSetup\n\n->�����ȷ��������<-"), __TEXT("From SeaYJ"), MB_OK);
		CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
		createWndComponent(hWnd, (pcs->hInstance) );	// �����ӿؼ��ķ�װ����
		break;

	case WM_COMMAND:

		/*****************************\
		|        ��Ϣ����-BEGIN        |
		\*****************************/
		switch (LOWORD(wParam))
		{
		case ID_APPLY_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (tbs_style)
				{
				case NONE_TBS:
					MessageBox(hWnd, __TEXT("��ѡ��һ����ʽ��"), __TEXT("����"), MB_OK | MB_ICONERROR);
					break;

				case FULLYTRANSPARENT_TBS:	// ȫ͸�� ����
					(TBS_FullyTransparent()) ? ( MessageBox(hWnd, __TEXT("����ʧ�ܣ�"), __TEXT("����"), MB_OK | MB_ICONERROR) ) : ( explorerRestart() );
					break;

				case TRANSLUCENT_TBS:		// ��͸�� ����
					(TBS_Transparent()) ? (MessageBox(hWnd, __TEXT("����ʧ�ܣ�"), __TEXT("����"), MB_OK | MB_ICONERROR)) : (explorerRestart());
					break;

				case GAUSSIANBLUR_TBS:		// ��˹ģ�� ����
					(TBS_GaussianBlur()) ? (MessageBox(hWnd, __TEXT("����ʧ�ܣ�"), __TEXT("����"), MB_OK | MB_ICONERROR)) : (explorerRestart());
					break;

				case DEFAULT_TBS:			// Ĭ����ʽ ����
					(TBS_Default()) ? (MessageBox(hWnd, __TEXT("����ʧ�ܣ�"), __TEXT("����"), MB_OK | MB_ICONERROR)) : (explorerRestart());
					break;

				default:
					MessageBox(hWnd, __TEXT("δ֪��ʽ��\n���ָ�����������Ƿ�����ĳ��δ֪����\n������ϵ���ߣ�"), __TEXT("����"), MB_OK | MB_ICONERROR);
					break;
				}
#ifdef _DEBUG
				sprintf(pszText, "�ѵ�� Ӧ����ʽ\n");
				WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			}
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_1:	// �û���ѡ ȫ͸�� ��ť

			tbs_style = FULLYTRANSPARENT_TBS;

#ifdef _DEBUG
			sprintf(pszText, "��ѡ�� ȫ͸��\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_2:	// �û���ѡ ��͸�� ��ť

			tbs_style = TRANSLUCENT_TBS;

#ifdef _DEBUG
			sprintf(pszText, "��ѡ�� ��͸��\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_3:	// �û���ѡ ��˹ģ�� ��ť

			tbs_style = GAUSSIANBLUR_TBS;

#ifdef _DEBUG
			sprintf(pszText, "��ѡ�� ��˹ģ��\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_4:	// �û���ѡ Ĭ����ʽ ��ť

			tbs_style = DEFAULT_TBS;

#ifdef _DEBUG
			sprintf(pszText, "��ѡ�� Ĭ������\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;
		}
		/*****************************\
		|        ��Ϣ����-END          |
		\*****************************/
		break;

	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			int nRet = MessageBox(hWnd, __TEXT("ȷ���˳�����"), __TEXT("��ʾ"), MB_YESNO | MB_ICONQUESTION);
			if (nRet == IDYES) {
				// �û�ȷ��Ҫ�˳�����
				return DefWindowProc(hWnd, msgID, wParam, lParam);
			}
			else
			{
				// �û�ѡ���˳�����
				return 0;
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

int CALLBACK WinMain(_In_ HINSTANCE hIns, _In_opt_ HINSTANCE hPreIns, _In_ LPSTR ipCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();		// �ٻ� ����DOS����
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);	// ��ȡ��׼������
#endif // _DEBUG


	// Ԥ�������
	preHandle();

	// ע�ᴰ����
	WNDCLASSEX mainWnd_frame_class = { 0 };
	mainWnd_frame_class.cbSize = sizeof(WNDCLASSEX);
	mainWnd_frame_class.style = CS_HREDRAW | CS_VREDRAW;
	mainWnd_frame_class.lpfnWndProc = mainMsgProc;
	mainWnd_frame_class.cbClsExtra = 0;
	mainWnd_frame_class.cbWndExtra = 0;
	mainWnd_frame_class.hInstance = hIns;
	mainWnd_frame_class.hIcon = LoadIcon(hIns, (LPCSTR)IDI_ICON3);
	mainWnd_frame_class.hCursor = NULL;
	mainWnd_frame_class.hbrBackground = (HBRUSH)(COLOR_BTNSHADOW);
	mainWnd_frame_class.lpszMenuName = NULL;
	mainWnd_frame_class.lpszClassName = __TEXT("mainWnd_frame");
	mainWnd_frame_class.hIconSm = LoadIcon(hIns, (LPCSTR)IDI_ICON2); // ������ ICON
	RegisterClassEx( &mainWnd_frame_class );

	// ��������
#define MAINWND_FRAME_WDITH 321
#define MAINWND_FRAME_HEIGHT 198
	
	HWND mainWnd_frame/* ������ */ = CreateWindowEx(0, __TEXT("mainWnd_frame"), __TEXT("TaskbarSetup"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		(DeviceInfo.ScreenW - MAINWND_FRAME_WDITH)/2, (DeviceInfo.ScreenH - MAINWND_FRAME_HEIGHT)/2,	// ������ʾ
		MAINWND_FRAME_WDITH, MAINWND_FRAME_HEIGHT, NULL, NULL, hIns, NULL);

	// ��ʾ����
	ShowWindow(mainWnd_frame, SW_SHOW);
	// ���ƣ�ˢ�£�����
	UpdateWindow( mainWnd_frame );

	// ��Ϣ����
	MSG mainMSG = { 0 };
	while (TRUE) {
		if (PeekMessage(&mainMSG, NULL, 0, 0, PM_NOREMOVE)) 
		{
			// ����Ϣ
			if (GetMessage(&mainMSG, NULL, 0, 0)) 
			{
				TranslateMessage(&mainMSG);
				DispatchMessage(&mainMSG);
			}
			else 
			{
				return 0;
			}
		}
		else 
		{
			// ���д���
		}
	}

	return 0;
}

BOOL createWndComponent(HWND mainWnd_frame, HINSTANCE hIns)
{
	
#define APPLY_BUTTON_WIDTH 100
#define APPLY_BUTTON_HEIGHT 25
	
	HWND apply_button/* Ӧ����ʽ ��ѹ��ť */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT("Ӧ����ʽ"),
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		(MAINWND_FRAME_WDITH - APPLY_BUTTON_WIDTH) / 2, (MAINWND_FRAME_HEIGHT - APPLY_BUTTON_HEIGHT - 46),
		APPLY_BUTTON_WIDTH, APPLY_BUTTON_HEIGHT,
		mainWnd_frame, (HMENU)ID_APPLY_BUTTON, NULL, NULL);

#define TASKBAR_STYLE_GROUPBOX_WIDTH 270
#define TASKBAR_STYLE_GROUPBOX_HEIGHT 110

	HWND taskbar_style_groupBox/* ��ʽѡ�� ����� */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT("��������ʽ�޸�"),
		WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
		(MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3, 8,
		TASKBAR_STYLE_GROUPBOX_WIDTH, TASKBAR_STYLE_GROUPBOX_HEIGHT,
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_GROUPBOX, NULL, NULL);

	/* ��ʽѡ�� ������Ա -> ��ѡ��ť */
#define No_1_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 9 )
#define No_2_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 1 * TASKBAR_STYLE_RADIOBUTTON_HEIGHT + 9 )
#define No_3_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 2 * TASKBAR_STYLE_RADIOBUTTON_HEIGHT + 9 )
#define No_4_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 3 * TASKBAR_STYLE_RADIOBUTTON_HEIGHT + 9 )
#define TASKBAR_STYLE_RADIOBUTTON_toTop 16
#define TASKBAR_STYLE_RADIOBUTTON_WIDTH 250
#define TASKBAR_STYLE_RADIOBUTTON_HEIGHT 20

	HWND taskbar_style_fullyTransparent/* ȫ͸�� ��ѡ��ť */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" ȫ͸��"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_1_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT,
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_1, NULL, NULL);

	HWND taskbar_style_translucent/* ��͸�� ��ѡ��ť */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" ��͸��"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_2_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT,
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_2, NULL, NULL);

	HWND taskbar_style_gaussianBlur/* ��˹ģ�� ��ѡ��ť */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" ��˹ģ��"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_3_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT, 
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_3, NULL, NULL);

	HWND taskbar_style_default/* Ĭ����ʽ ��ѡ��ť */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" Ĭ����ʽ"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_4_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT, 
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_4, NULL, NULL);

	// ���ÿؼ�����
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(apply_button, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_groupBox, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_default, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_translucent, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_gaussianBlur, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_fullyTransparent, WM_SETFONT, (WPARAM)hFont, 0);

	return TRUE;
}
