#ifndef _TBSPROC_H
#define _TBSPROC_H

#include <windows.h>

/* 记录相应注册表子键的路径 */
const struct ReghKeyPath
{
	LPCSTR USERP;
	LPCSTR USERA;
	LPCSTR MACHA;
	LPCSTR MACHD;
} reghkeyPath = {
	"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
	"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced",
	"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced",
	"SOFTWARE\\Microsoft\\Windows\\Dwm"
};

/* 存储并提供操作相应注册表子键的句柄 */
struct ReghKey
{
	HKEY USERP;
	HKEY USERA;
	HKEY MACHA;
	HKEY MACHD;
} reghKey = {
	NULL, NULL, NULL, NULL
};

/* 为一定的值设置名称，便于理解 */
CONST DWORD TURNOFF = 0;								// 0 - 表示关闭
CONST DWORD TURNON = 1;									// 1 - 表示打开
CONST DWORD OPACITY[11] = { 0,1,2,3,4,5,6,7,8,9,10 };		// 0 ~ 10 代表不透明度程度(0 表示全透明)

/*************************************\
* openReghKey 获得注册表子键操作句柄
* closeReghKey 释放句柄
\*************************************/
int openReghKey();
int closeReghKey();

/**************************************************\
* 四种任务栏样式的可操作函数，用于更改注册表中相应键值项
* TBS_Transparent		- 半透明
* TBS_GaussianBlur		- 高斯模糊
* TBS_FullyTransparent	- 全透明
* TBS_Default			- 默认
\**************************************************/
int TBS_Transparent();
int TBS_GaussianBlur();
int TBS_FullyTransparent();
int TBS_Default();

/* 重新启动 Windows 资源管理器 */
int explorerRestart();

/* 错误消息反馈函数 */
int errMessageBox(LONG errCode);


#endif // !_TBSPROC_H
