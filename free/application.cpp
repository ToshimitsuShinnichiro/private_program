/*
	application.cpp
*/

// �C���N���[�h
#include "application.h"
#include <time.h>
#include <mmsystem.h>
#include <Windows.h>

#pragma comment( lib, "winmm.lib" ) // timeGetTime() �����N�w��

int CApplication::_fps = 0;

// �R���X�g���N�^
CApplication::CApplication() : dwCurrentTime(0), dwFrameCount(0)
{	
	//���Ԃ̓���
	timeBeginPeriod( 1 );

	dwExecLastTime = dwFPSLastTime = timeGetTime( );										//���ݎ����̎擾
}

// �f�X�g���N�^
CApplication::~CApplication()
{
	//���ԓ����̏I��
	timeEndPeriod( 1 );
}

// �X�V
void CApplication::Update()
{
	dwCurrentTime = timeGetTime( );													//���ݎ��Ԃ̓���

	//FPS�v�Z
	if( ( dwCurrentTime - dwFPSLastTime ) >= 500 )
	{
		_fps = ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );			//FPS�J�E���g�̌v�Z
		dwFPSLastTime = dwCurrentTime;												//FPS���X�g�^�C���̎擾
		dwFrameCount = 0;															//�t���[���J�E���g������
	}

	//FPS�ŏ���
	if( ( dwCurrentTime - dwExecLastTime ) >= ( 1000 / 60 ) )
	{
		dwExecLastTime = dwCurrentTime;												//���ݎ��Ԃ̑��

		/*---------------
		|	�Q�[������	|
		---------------*/
		//pManeger->Update();															//�X�V����
		//pManeger->Draw();															//�`�揈��

		dwFrameCount++;																//�t���[���J�E���g�̃C���N�������g
	}
}