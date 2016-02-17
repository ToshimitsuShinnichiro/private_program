/*
	application.h
*/

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

// �C���N���[�h
#include <Windows.h>
#include "window.h"

#pragma comment( lib, "winmm.lib" ) // timeGetTime() �����N�w��

class CApplication
{
public:
	CApplication();
	~CApplication();

	void Update();

	static int GetFPS() {return _fps;}

private:
	static int _fps;

	DWORD dwExecLastTime;																	//���X�g�^�C��
	DWORD dwFPSLastTime;																	//FPS���X�g�^�C��
	DWORD dwCurrentTime;																	//�J�����g�^�C��
	DWORD dwFrameCount;																		//�t���[���J�E���g
};

#endif