#ifndef TASKBARSETUP_H
#define TASKBARSETUP_H

#define _CRT_SECURE_NO_WARNINGS

// ȷ�����ڷ��
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <stdio.h>

struct // ������Ļ ���� �� ���ߡ�
{
	int ScreenW;
	int ScreenH;
} DeviceInfo = { 0 };

BOOL preHandle();	//	Ԥ������

// ����ؼ�ID
#define ID_APPLY_BUTTON 0x5201
#define ID_TASKBAR_STYLE_GROUPBOX 0x5202
#define ID_TASKBAR_STYLE_RADIOBUTTON_1 0x5203
#define ID_TASKBAR_STYLE_RADIOBUTTON_2 0x5204
#define ID_TASKBAR_STYLE_RADIOBUTTON_3 0x5205
#define ID_TASKBAR_STYLE_RADIOBUTTON_4 0x5206
BOOL createWndComponent(HWND hWnd, HINSTANCE hIns);

// ���� ��ʽ��ʶ�� �� ״̬����ʽ��������
#define NONE_TBS 0x000					// ����ʽ
#define FULLYTRANSPARENT_TBS 0x001		// ȫ͸��
#define TRANSLUCENT_TBS 0x002			// ��͸��
#define GAUSSIANBLUR_TBS 0x003			// ��˹ģ��
#define DEFAULT_TBS 0x004				// Ĭ����ʽ
typedef unsigned int TBS_STYLE;			// ��������ʽ��������

// ȡĬ��ֵ������û����ʽ
TBS_STYLE tbs_style = NONE_TBS;


#ifdef _DEBUG
HANDLE g_hOutput = 0;	// ���ڴ洢��׼������
#endif // ����


#endif // !TASKBARSETUP_H
