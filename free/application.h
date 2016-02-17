/*
	application.h
*/

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

// インクルード
#include <Windows.h>
#include "window.h"

#pragma comment( lib, "winmm.lib" ) // timeGetTime() リンク指定

class CApplication
{
public:
	CApplication();
	~CApplication();

	void Update();

	static int GetFPS() {return _fps;}

private:
	static int _fps;

	DWORD dwExecLastTime;																	//ラストタイム
	DWORD dwFPSLastTime;																	//FPSラストタイム
	DWORD dwCurrentTime;																	//カレントタイム
	DWORD dwFrameCount;																		//フレームカウント
};

#endif