/*
	window.h
*/

#ifndef _WINDOW_H_
#define _WINDOW_H_

// include
#include <windows.h>
#include "main.h"

#define WINDOW_NAME "Game"

class CWindow
{
public:
	CWindow(HINSTANCE instance, WNDCLASSEX* pwcex);
	~CWindow();

private:
	void SettingPram(void);
	HWND Create();

	MSG msg;																				//メッセージ用マクロ
	HWND hWnd;																				//ハンドル用マクロ
	WNDCLASSEX wcex;																		//WNDCLASSEXマクロ

	HINSTANCE instance;
	WNDCLASSEX* pwcex;
};

#endif _WINDOW_H_