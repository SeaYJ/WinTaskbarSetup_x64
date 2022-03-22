#include "TBSProc.h"


int openReghKey() {

	/* �������ڴ洢 ��������ֵ ������ */
#define openReCode_MAX 4
	LONG openReCode[openReCode_MAX] = { 0 };

	/* �������� */
	openReCode[0] = RegOpenKeyExA(HKEY_CURRENT_USER, reghkeyPath.USERP, 0, KEY_ALL_ACCESS, &reghKey.USERP);
	openReCode[1] = RegOpenKeyExA(HKEY_CURRENT_USER, reghkeyPath.USERA, 0, KEY_ALL_ACCESS, &reghKey.USERA);
	openReCode[2] = RegOpenKeyExA(HKEY_LOCAL_MACHINE, reghkeyPath.MACHA, 0, KEY_ALL_ACCESS, &reghKey.MACHA);
	openReCode[3] = RegOpenKeyExA(HKEY_LOCAL_MACHINE, reghkeyPath.MACHD, 0, KEY_ALL_ACCESS, &reghKey.MACHD);

	/* ����ֵ���
	* ����������򷵻ص�һ�����ֵ����⣬
	* ���������򣬷�ֹ����������
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

	/* �������ڴ洢 ��������ֵ ������ */
#define closeReCode_MAX 4
	LONG closeReCode[closeReCode_MAX] = { 0 };

	/* �������� */
	closeReCode[0] = RegCloseKey(reghKey.USERP);
	closeReCode[1] = RegCloseKey(reghKey.USERA);
	closeReCode[2] = RegCloseKey(reghKey.MACHA);
	closeReCode[3] = RegCloseKey(reghKey.MACHD);

	/* ����ֵ���
	* ����������򷵻ص�һ�����ֵ����⣬
	* ���� closeReghKey �����ķ���ֵ����Ϊ 1��
	* �����д�������
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

	/* �������ڴ洢 ��������ֵ ������ */
#define TBS_FRetCode_MAX 6
	LONG retCode[TBS_FRetCode_MAX] = { 0 };

	/* �������� */
	retCode[0] = RegSetValueExA(reghKey.USERP, "EnableTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[1] = RegSetValueExA(reghKey.USERP, "ColorPrevalence", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[2] = RegSetValueExA(reghKey.USERP, "SystemUsesLightTheme", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[3] = RegSetValueExA(reghKey.USERA, "TaskbarAcrylicOpacity", 0, REG_DWORD, (LPBYTE)&OPACITY[0], sizeof(DWORD));

	retCode[4] = RegSetValueExA(reghKey.MACHA, "UseOLEDTaskbarTransparency", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.MACHD, "ForceEffectMode", NULL, NULL, NULL, NULL)) {
		retCode[5] = RegDeleteValueA(reghKey.MACHD, "ForceEffectMode");
	}

	/* ����ֵ���
	* ����������򷵻ص�һ�����ֵ����⣬
	* ���� closeReghKey �����ķ���ֵ����Ϊ 1��
	* �����д�������
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

	/* �������ڴ洢 ��������ֵ ������ */
#define TBS_TRetCode_MAX 5
	LONG retCode[TBS_TRetCode_MAX] = { 0 };

	/* �������� */
	retCode[0] = RegSetValueExA(reghKey.USERP, "EnableTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.USERA, "TaskbarAcrylicOpacity", NULL, NULL, NULL, NULL)) {
		retCode[1] = RegDeleteValueA(reghKey.USERA, "TaskbarAcrylicOpacity");
	}

	retCode[2] = RegSetValueExA(reghKey.MACHA, "UseOLEDTaskbarTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[3] = RegSetValueExA(reghKey.MACHD, "ForceEffectMode", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[4] = RegSetValueExA(reghKey.USERP, "SystemUsesLightTheme", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	/* ����ֵ���
	* ����������򷵻ص�һ�����ֵ����⣬
	* ���� closeReghKey �����ķ���ֵ����Ϊ 1��
	* �����д�������
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

	/* �������ڴ洢 ��������ֵ ������ */
#define TBS_GRetCode_MAX 5
	LONG retCode[TBS_GRetCode_MAX] = { 0 };

	/* �������� */
	retCode[0] = RegSetValueExA(reghKey.USERP, "EnableTransparency", 0, REG_DWORD, (LPBYTE)&TURNON, sizeof(DWORD));

	retCode[1] = RegSetValueExA(reghKey.USERA, "TaskbarAcrylicOpacity", 0, REG_DWORD, (LPBYTE)&OPACITY[5], sizeof(DWORD));

	retCode[2] = RegSetValueExA(reghKey.MACHA, "UseOLEDTaskbarTransparency", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	retCode[3] = RegSetValueExA(reghKey.USERP, "SystemUsesLightTheme", 0, REG_DWORD, (LPBYTE)&TURNOFF, sizeof(DWORD));

	if (ERROR_SUCCESS == RegQueryValueExA(reghKey.MACHD, "ForceEffectMode", NULL, NULL, NULL, NULL)) {
		retCode[4] = RegDeleteValueA(reghKey.MACHD, "ForceEffectMode");
	}

	/* ����ֵ���
	* ����������򷵻ص�һ�����ֵ����⣬
	* ���� closeReghKey �����ķ���ֵ����Ϊ 1��
	* �����д�������
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

	/* �������ڴ洢 ��������ֵ ������ */
#define TBS_DRetCode_MAX 6
	LONG retCode[TBS_DRetCode_MAX] = { 0 };

	/* �������� */
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

	/* ����ֵ���
	* ����������򷵻ص�һ�����ֵ����⣬
	* ���� closeReghKey �����ķ���ֵ����Ϊ 1��
	* �����д�������
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

	if (errCode == 5) {	// ��ʶ����󣺾ܾ����ʡ�
		lstrcat((LPSTR)errorMessage, __TEXT("\n���飺�Թ���Ա������д˳���"));
	}
	else if (errCode == 6) { // ��ʶ����󣺾����Ч��
		lstrcat((LPSTR)errorMessage, __TEXT("\n���飺�ô��������������һ�������£�\n�������ѯ��ذ����ĵ�����ѯ���ߣ�\n�Խ���׸����ֵ�����"));
	}
	else {
		lstrcat((LPSTR)errorMessage, __TEXT("\n���飺δ֪��������������ϵ����������"));
	}

	MessageBox(NULL, (LPSTR)errorMessage, __TEXT("������Ϣ"), MB_OK | MB_ICONSTOP | MB_DEFBUTTON1);

	LocalFree(buffer);
	LocalFree(errorMessage);

	return 0;
}
