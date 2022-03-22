#ifndef TASKBARSETUP_H
#define TASKBARSETUP_H

#define _CRT_SECURE_NO_WARNINGS

// 确定窗口风格
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <stdio.h>

struct // 储存屏幕 “宽” 和 “高”
{
	int ScreenW;
	int ScreenH;
} DeviceInfo = { 0 };

BOOL preHandle();	//	预处理函数

// 定义控件ID
#define ID_APPLY_BUTTON 0x5201
#define ID_TASKBAR_STYLE_GROUPBOX 0x5202
#define ID_TASKBAR_STYLE_RADIOBUTTON_1 0x5203
#define ID_TASKBAR_STYLE_RADIOBUTTON_2 0x5204
#define ID_TASKBAR_STYLE_RADIOBUTTON_3 0x5205
#define ID_TASKBAR_STYLE_RADIOBUTTON_4 0x5206
BOOL createWndComponent(HWND hWnd, HINSTANCE hIns);

// 定义 样式标识符 和 状态栏样式数据类型
#define NONE_TBS 0x000					// 无样式
#define FULLYTRANSPARENT_TBS 0x001		// 全透明
#define TRANSLUCENT_TBS 0x002			// 半透明
#define GAUSSIANBLUR_TBS 0x003			// 高斯模糊
#define DEFAULT_TBS 0x004				// 默认样式
typedef unsigned int TBS_STYLE;			// 任务栏样式数据类型

// 取默认值，代表没有样式
TBS_STYLE tbs_style = NONE_TBS;


#ifdef _DEBUG
HANDLE g_hOutput = 0;	// 用于存储标准输出句柄
#endif // 调试


#endif // !TASKBARSETUP_H
