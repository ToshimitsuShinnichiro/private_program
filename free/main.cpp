/********************************************************************************************
*
*	FileContent	main����
*	FileName	main.cpp
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "main.h"
#include <time.h>
#include <mmsystem.h>
#include "window.h"
#include "application.h"

//-----------------------------------------
//	�}�N����`
//-----------------------------------------

/****************************************************
*	�֐����@WinMain
*	����	HINSTANCE, HINSTANCE, LPSTR, int
*	�߂�l	WPARAM
*	���e	WindowsMain
****************************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//win�p�ϐ�
	MSG msg;																				//���b�Z�[�W�p�}�N��
	HWND hWnd;																				//�n���h���p�}�N��
	WNDCLASSEX wcex;																		//WNDCLASSEX�}�N��

	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	CWindow *window = NEW CWindow(hInstance, &wcex);
	CApplication *application = NEW CApplication();

	//���C�����[�v
	while( 1 )
	{
		//�v���V�[�W���ɕϓ����N�����Ƃ�
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )
		{
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			application->Update();
		}
	}

	delete window;
	delete application;

	return ( int )msg.wParam;
}

/* --- EOF --- */