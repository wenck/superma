#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <graphics.h> 	             // 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include "kcgl.h"
#include "gkgm.h"
#include <comdef.h>
#include<Windows.h>
#include <stdlib.h>




//char*转wchar_t*
wchar_t* chtow(const char* szStr)
{
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0);
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen);
	return pResult;
}

//wchar_t*转char*
char* wtoch(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

/*
int typejudge(wchar_t* x) {
	int i=0, j=-1;
	for (i; i < wcslen(x); i++) {
		//if(x[i]>)
	}
}
*/