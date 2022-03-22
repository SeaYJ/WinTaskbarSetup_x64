#include "TBSProc.h"


int openReghKey() {

	/* 定义用于存储 函数返回值 的数组 */
#define openReCode_MAX 4
	LONG openReCode[openReCode_MAX] = { 0 };

	/* 函数操作 */
	openReCode[0] = RegOpenKeyExA(HKEY_CURRENT_USER, reghkeyPath.USERP, 0, KEY_ALL_ACCESS, &reghKey.USERP);
	openReCode[1] = RegOpenKeyExA(HKEY_CURRENT_USER, reghkeyPath.USERA, 0, KEY_ALL_ACCESS, &reghKey.USERA);
	openReCode[2] = RegOpenKeyExA(HKEY_LOCAL_MACHINE, reghkeyPath.MACHA, 0, KEY_ALL_ACCESS, &reghKey.MACHA);
	openReCode[3] = RegOpenKeyExA(HKEY_LOCAL_MACHINE, reghkeyPath.MACHD, 0, KEY_ALL_ACCESS, &reghKey.MACHD);

	/* 返回值检查
	* 如果有问题则返回第一个出现的问题，
	* 并结束程序，防止连续崩溃。
	*/
	for (int i = 0; i < openReCode_MAX; i++) {
		if (openReCode[i]) {
			errMessageBox(openReCode[i]);
			return 1;
		}
	}

	return 0;
}

int closeReghKey() {

	/* 定义用于存储 函数返回值 的数组 */
#define closeReCode_MAX 4
	LONG closeReCode[closeReCode_MAX] = { 0 };

	/* 函数操作 */
	closeReCode[0] = RegCloseKey(reghKey.USERP);
	closeReCode[1] = RegCloseKey(reghKey.USERA);
	closeReCode[2] = RegCloseKey(reghKey.MACHA);
	closeReCode[3] = RegCloseKey(reghKey.MACHD);

	/* 返回值检查
	* 如果有问题则返回第一个出现的问题，
	* 并将 closeReghKey 函数的返回值设置为 1，
	* 代表有错误发生。
	*/
	for (int i = 0; i < openReCode_MAX; i++) {
		if (closeReCode[i]) {
			errMessageBox(closeReCode[i]);
			return 1;
		}
	}

	return 0;
}

int TBS_FullyTransparent() {
	openReghKey();

	/* 定义用于存储 函数返回值 的数组 */
#define TBS_FRetCode_MAX 6
	LONG retCode[TBS_FRetCode_MAX] = { 0 };

	/* 函数操作 */
	retCode[0] = RegSetValueExA(reghKey.USERP, "EnableTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[1] = RegSetValueExA(reghKey.USERP, "ColorPrevalence", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[2] = RegSetValueExA(reghKey.USERP, "SystemUsesLightTheme", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[3] = RegSetValueExA(reghKey.USERA, "TaskbarAcrylicOpacity", 0, REG_DWORD, (LPBYTE)&OPACITY[0], sizeof(DWORD));

	retCode[4] = RegSetValueExA(reghKey.MACHA, "UseOLEDTaskbarTransparency", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.MACHD, "ForceEffectMode", NULL, NULL, NULL, NULL)) {
		retCode[5] = RegDeleteValueA(reghKey.MACHD, "ForceEffectMode");
	}

	/* 返回值检查
	* 如果有问题则返回第一个出现的问题，
	* 并将 closeReghKey 函数的返回值设置为 1，
	* 代表有错误发生。
	*/
	for (int i = 0; i < TBS_FRetCode_MAX; i++) {
		if (retCode[i]) {
			errMessageBox(retCode[i]);
			return 1;
		}
	}

	closeReghKey();
	return 0;
}

int TBS_Transparent() {
	openReghKey();

	/* 定义用于存储 函数返回值 的数组 */
#define TBS_TRetCode_MAX 5
	LONG retCode[TBS_TRetCode_MAX] = { 0 };

	/* 函数操作 */
	retCode[0] = RegSetValueExA(reghKey.USERP, "EnableTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.USERA, "TaskbarAcrylicOpacity", NULL, NULL, NULL, NULL)) {
		retCode[1] = RegDeleteValueA(reghKey.USERA, "TaskbarAcrylicOpacity");
	}

	retCode[2] = RegSetValueExA(reghKey.MACHA, "UseOLEDTaskbarTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[3] = RegSetValueExA(reghKey.MACHD, "ForceEffectMode", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[4] = RegSetValueExA(reghKey.USERP, "SystemUsesLightTheme", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	/* 返回值检查
	* 如果有问题则返回第一个出现的问题，
	* 并将 closeReghKey 函数的返回值设置为 1，
	* 代表有错误发生。
	*/
	for (int i = 0; i < TBS_TRetCode_MAX; i++) {
		if (retCode[i]) {
			errMessageBox(retCode[i]);
			return 1;
		}
	}

	closeReghKey();
	return 0;
}

int TBS_GaussianBlur() {
	openReghKey();

	/* 定义用于存储 函数返回值 的数组 */
#define TBS_GRetCode_MAX 5
	LONG retCode[TBS_GRetCode_MAX] = { 0 };

	/* 函数操作 */
	retCode[0] = RegSetValueExA(reghKey.USERP, "EnableTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[1] = RegSetValueExA(reghKey.USERA, "TaskbarAcrylicOpacity", 0, REG_DWORD, (LPBYTE)&OPACITY[5], sizeof(DWORD));

	retCode[2] = RegSetValueExA(reghKey.MACHA, "UseOLEDTaskbarTransparency", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[3] = RegSetValueExA(reghKey.USERP, "SystemUsesLightTheme", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.MACHD, "ForceEffectMode", NULL, NULL, NULL, NULL)) {
		retCode[4] = RegDeleteValueA(reghKey.MACHD, "ForceEffectMode");
	}

	/* 返回值检查
	* 如果有问题则返回第一个出现的问题，
	* 并将 closeReghKey 函数的返回值设置为 1，
	* 代表有错误发生。
	*/
	for (int i = 0; i < TBS_GRetCode_MAX; i++) {
		if (retCode[i]) {
			errMessageBox(retCode[i]);
			return 1;
		}
	}

	closeReghKey();
	return 0;
}

int TBS_Default() {
	openReghKey();

	/* 定义用于存储 函数返回值 的数组 */
#define TBS_DRetCode_MAX 6
	LONG retCode[TBS_DRetCode_MAX] = { 0 };

	/* 函数操作 */
	retCode[0] = RegSetValueExA(reghKey.USERP, "EnableTransparency", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[1] = RegSetValueExA(reghKey.USERP, "ColorPrevalence", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[2] = RegSetValueExA(reghKey.USERP, "SystemUsesLightTheme", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.USERA, "TaskbarAcrylicOpacity", NULL, NULL, NULL, NULL)) {
		retCode[1] = RegDeleteValueA(reghKey.USERA, "TaskbarAcrylicOpacity");
	}

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.MACHA, "UseOLEDTaskbarTransparency", NULL, NULL, NULL, NULL)) {
		retCode[2] = RegDeleteValueA(reghKey.MACHA, "UseOLEDTaskbarTransparency");
	}

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.MACHD, "ForceEffectMode", NULL, NULL, NULL, NULL)) {
		retCode[3] = RegDeleteValueA(reghKey.MACHD, "ForceEffectMode");
	}

	/* 返回值检查
	* 如果有问题则返回第一个出现的问题，
	* 并将 closeReghKey 函数的返回值设置为 1，
	* 代表有错误发生。
	*/
	for (int i = 0; i < TBS_DRetCode_MAX; i++) {
		if (retCode[i]) {
			errMessageBox(retCode[i]);
			return 1;
		}
	}

	closeReghKey();
	return 0;
}

int explorerRestart() {

	system("taskkill /f /IM dwm.exe 1>nul");
	system("start dwm.exe");
	return 0;
}


int errMessageBox(LONG errCode) {
	TCHAR* buffer;
	TCHAR errorMessage[1024] = {0};

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errCode,
		0,
		(LPSTR)&buffer,
		0,
		NULL);

	lstrcat((LPSTR)errorMessage, (LPSTR)buffer);

	if (errCode == 5) {	// 已识别错误：拒绝访问。
		lstrcat((LPSTR)errorMessage, __TEXT("\n建议：以管理员身份运行此程序"));
	}
	else if (errCode == 6) { // 已识别错误：句柄无效。
		lstrcat((LPSTR)errorMessage, __TEXT("\n建议：该错误可能是由于上一个错误导致，\n具体请查询相关帮助文档或咨询作者，\n以解决首个出现的问题"));
	}
	else {
		lstrcat((LPSTR)errorMessage, __TEXT("\n建议：未知错误，请与作者联系反馈此问题"));
	}

	MessageBox(NULL, (LPSTR)errorMessage, __TEXT("反馈消息"), MB_OK | MB_ICONSTOP | MB_DEFBUTTON1);

	LocalFree(buffer);
	LocalFree(errorMessage);

	return 0;
}
