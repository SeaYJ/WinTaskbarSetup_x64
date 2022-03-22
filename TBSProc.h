#ifndef _TBSPROC_H
#define _TBSPROC_H

#include <windows.h>

/* ��¼��Ӧע����Ӽ���·�� */
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

/* �洢���ṩ������Ӧע����Ӽ��ľ�� */
struct ReghKey
{
	HKEY USERP;
	HKEY USERA;
	HKEY MACHA;
	HKEY MACHD;
} reghKey = {
	NULL, NULL, NULL, NULL
};

/* Ϊһ����ֵ�������ƣ�������� */
CONST DWORD TURNOFF = 0;								// 0 - ��ʾ�ر�
CONST DWORD TURNON = 1;									// 1 - ��ʾ��
CONST DWORD OPACITY[11] = { 0,1,2,3,4,5,6,7,8,9,10 };		// 0 ~ 10 ����͸���ȳ̶�(0 ��ʾȫ͸��)

/*************************************\
* openReghKey ���ע����Ӽ��������
* closeReghKey �ͷž��
\*************************************/
int openReghKey();
int closeReghKey();

/**************************************************\
* ������������ʽ�Ŀɲ������������ڸ���ע�������Ӧ��ֵ��
* TBS_Transparent		- ��͸��
* TBS_GaussianBlur		- ��˹ģ��
* TBS_FullyTransparent	- ȫ͸��
* TBS_Default			- Ĭ��
\**************************************************/
int TBS_Transparent();
int TBS_GaussianBlur();
int TBS_FullyTransparent();
int TBS_Default();

/* �������� Windows ��Դ������ */
int explorerRestart();

/* ������Ϣ�������� */
int errMessageBox(LONG errCode);


#endif // !_TBSPROC_H
