/********************************************************************************************
*
*	FileContent	main処理
*	FileName	main.cpp
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "main.h"
#include <time.h>
#include <mmsystem.h>
#include "window.h"
#include "application.h"

//-----------------------------------------
//	マクロ定義
//-----------------------------------------

/****************************************************
*	関数名　WinMain
*	引数	HINSTANCE, HINSTANCE, LPSTR, int
*	戻り値	WPARAM
*	内容	WindowsMain
****************************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//win用変数
	MSG msg;																				//メッセージ用マクロ
	HWND hWnd;																				//ハンドル用マクロ
	WNDCLASSEX wcex;																		//WNDCLASSEXマクロ

	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	CWindow *window = NEW CWindow(hInstance, &wcex);
	CApplication *application = NEW CApplication();

	//メインループ
	while( 1 )
	{
		//プロシージャに変動が起きたとき
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