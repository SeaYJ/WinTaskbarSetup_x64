#include "TaskbarSetup.h"
#include "resource.h"

BOOL preHandle()
{
	// 获取设备信息
	DeviceInfo.ScreenW = GetSystemMetrics(SM_CXSCREEN);	//	获取屏幕可用宽度
	DeviceInfo.ScreenH = GetSystemMetrics(SM_CYSCREEN);	//	获取屏幕可用高度

	return TRUE;
}

LRESULT CALLBACK mainMsgProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	char pszText[256] = { 0 };	// 调试程序时的字符缓冲区

	switch (msgID)
	{
	case WM_CREATE:
		MessageBox(hWnd, __TEXT("如果有任何问题，\n欢迎来 GitHub 留言，以便于我们及时为您解决问题！\nhttps://github.com/SeaYJ/TaskbarSetup\n\n->点击“确定”继续<-"), __TEXT("From SeaYJ"), MB_OK);
		CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
		createWndComponent(hWnd, (pcs->hInstance) );	// 绘制子控件的封装函数
		break;

	case WM_COMMAND:

		/*****************************\
		|        消息处理-BEGIN        |
		\*****************************/
		switch (LOWORD(wParam))
		{
		case ID_APPLY_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (tbs_style)
				{
				case NONE_TBS:
					MessageBox(hWnd, __TEXT("请选择一种样式！"), __TEXT("错误"), MB_OK | MB_ICONERROR);
					break;

				case FULLYTRANSPARENT_TBS:	// 全透明 处理
					(TBS_FullyTransparent()) ? ( MessageBox(hWnd, __TEXT("设置失败！"), __TEXT("错误"), MB_OK | MB_ICONERROR) ) : ( explorerRestart() );
					break;

				case TRANSLUCENT_TBS:		// 半透明 处理
					(TBS_Transparent()) ? (MessageBox(hWnd, __TEXT("设置失败！"), __TEXT("错误"), MB_OK | MB_ICONERROR)) : (explorerRestart());
					break;

				case GAUSSIANBLUR_TBS:		// 高斯模糊 处理
					(TBS_GaussianBlur()) ? (MessageBox(hWnd, __TEXT("设置失败！"), __TEXT("错误"), MB_OK | MB_ICONERROR)) : (explorerRestart());
					break;

				case DEFAULT_TBS:			// 默认样式 处理
					(TBS_Default()) ? (MessageBox(hWnd, __TEXT("设置失败！"), __TEXT("错误"), MB_OK | MB_ICONERROR)) : (explorerRestart());
					break;

				default:
					MessageBox(hWnd, __TEXT("未知样式！\n出现该类情况可能是发生了某种未知错误！\n建议联系作者！"), __TEXT("错误"), MB_OK | MB_ICONERROR);
					break;
				}
#ifdef _DEBUG
				sprintf(pszText, "已点击 应用样式\n");
				WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			}
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_1:	// 用户点选 全透明 按钮

			tbs_style = FULLYTRANSPARENT_TBS;

#ifdef _DEBUG
			sprintf(pszText, "已选中 全透明\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_2:	// 用户点选 半透明 按钮

			tbs_style = TRANSLUCENT_TBS;

#ifdef _DEBUG
			sprintf(pszText, "已选中 半透明\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_3:	// 用户点选 高斯模糊 按钮

			tbs_style = GAUSSIANBLUR_TBS;

#ifdef _DEBUG
			sprintf(pszText, "已选中 高斯模糊\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;

		case ID_TASKBAR_STYLE_RADIOBUTTON_4:	// 用户点选 默认样式 按钮

			tbs_style = DEFAULT_TBS;

#ifdef _DEBUG
			sprintf(pszText, "已选中 默认设置\n");
			WriteConsole(g_hOutput, pszText, (DWORD)strlen(pszText), NULL, NULL);
#endif // _DEBUG
			break;
		}
		/*****************************\
		|        消息处理-END          |
		\*****************************/
		break;

	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			int nRet = MessageBox(hWnd, __TEXT("确定退程序吗？"), __TEXT("提示"), MB_YESNO | MB_ICONQUESTION);
			if (nRet == IDYES) {
				// 用户确定要退出程序
				return DefWindowProc(hWnd, msgID, wParam, lParam);
			}
			else
			{
				// 用户选择不退出程序
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
	AllocConsole();		// 召唤 调试DOS窗口
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);	// 获取标准输出句柄
#endif // _DEBUG


	// 预处理操作
	preHandle();

	// 注册窗口类
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
	mainWnd_frame_class.hIconSm = LoadIcon(hIns, (LPCSTR)IDI_ICON2); // 任务栏 ICON
	RegisterClassEx( &mainWnd_frame_class );

	// 创建窗口
#define MAINWND_FRAME_WDITH 321
#define MAINWND_FRAME_HEIGHT 198
	
	HWND mainWnd_frame/* 主窗口 */ = CreateWindowEx(0, __TEXT("mainWnd_frame"), __TEXT("TaskbarSetup"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		(DeviceInfo.ScreenW - MAINWND_FRAME_WDITH)/2, (DeviceInfo.ScreenH - MAINWND_FRAME_HEIGHT)/2,	// 居中显示
		MAINWND_FRAME_WDITH, MAINWND_FRAME_HEIGHT, NULL, NULL, hIns, NULL);

	// 显示窗口
	ShowWindow(mainWnd_frame, SW_SHOW);
	// 绘制（刷新）窗口
	UpdateWindow( mainWnd_frame );

	// 消息处理
	MSG mainMSG = { 0 };
	while (TRUE) {
		if (PeekMessage(&mainMSG, NULL, 0, 0, PM_NOREMOVE)) 
		{
			// 有消息
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
			// 空闲处理
		}
	}

	return 0;
}

BOOL createWndComponent(HWND mainWnd_frame, HINSTANCE hIns)
{
	
#define APPLY_BUTTON_WIDTH 100
#define APPLY_BUTTON_HEIGHT 25
	
	HWND apply_button/* 应用样式 下压按钮 */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT("应用样式"),
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		(MAINWND_FRAME_WDITH - APPLY_BUTTON_WIDTH) / 2, (MAINWND_FRAME_HEIGHT - APPLY_BUTTON_HEIGHT - 46),
		APPLY_BUTTON_WIDTH, APPLY_BUTTON_HEIGHT,
		mainWnd_frame, (HMENU)ID_APPLY_BUTTON, NULL, NULL);

#define TASKBAR_STYLE_GROUPBOX_WIDTH 270
#define TASKBAR_STYLE_GROUPBOX_HEIGHT 110

	HWND taskbar_style_groupBox/* 样式选择 分组框 */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT("任务栏样式修改"),
		WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
		(MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3, 8,
		TASKBAR_STYLE_GROUPBOX_WIDTH, TASKBAR_STYLE_GROUPBOX_HEIGHT,
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_GROUPBOX, NULL, NULL);

	/* 样式选择 分组框成员 -> 单选按钮 */
#define No_1_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 9 )
#define No_2_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 1 * TASKBAR_STYLE_RADIOBUTTON_HEIGHT + 9 )
#define No_3_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 2 * TASKBAR_STYLE_RADIOBUTTON_HEIGHT + 9 )
#define No_4_TSRadioButton_PosY ( TASKBAR_STYLE_RADIOBUTTON_toTop + 3 * TASKBAR_STYLE_RADIOBUTTON_HEIGHT + 9 )
#define TASKBAR_STYLE_RADIOBUTTON_toTop 16
#define TASKBAR_STYLE_RADIOBUTTON_WIDTH 250
#define TASKBAR_STYLE_RADIOBUTTON_HEIGHT 20

	HWND taskbar_style_fullyTransparent/* 全透明 单选按钮 */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" 全透明"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_1_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT,
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_1, NULL, NULL);

	HWND taskbar_style_translucent/* 半透明 单选按钮 */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" 半透明"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_2_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT,
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_2, NULL, NULL);

	HWND taskbar_style_gaussianBlur/* 高斯模糊 单选按钮 */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" 高斯模糊"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_3_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT, 
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_3, NULL, NULL);

	HWND taskbar_style_default/* 默认样式 单选按钮 */ = CreateWindowEx(0, __TEXT("BUTTON"), __TEXT(" 默认样式"),
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		((MAINWND_FRAME_WDITH - TASKBAR_STYLE_GROUPBOX_WIDTH) / 3 + 10), No_4_TSRadioButton_PosY,
		TASKBAR_STYLE_RADIOBUTTON_WIDTH, TASKBAR_STYLE_RADIOBUTTON_HEIGHT, 
		mainWnd_frame, (HMENU)ID_TASKBAR_STYLE_RADIOBUTTON_4, NULL, NULL);

	// 设置控件字体
	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(apply_button, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_groupBox, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_default, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_translucent, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_gaussianBlur, WM_SETFONT, (WPARAM)hFont, 0);
	SendMessage(taskbar_style_fullyTransparent, WM_SETFONT, (WPARAM)hFont, 0);

	return TRUE;
}
