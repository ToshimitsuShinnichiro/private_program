/*
	window.cpp
*/

#include <Windows.h>
#include "window.h"

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

// コンストラクタ
CWindow::CWindow(HINSTANCE instance, WNDCLASSEX* pwcex) : instance(instance), pwcex(pwcex)
{
	SettingPram();
	hWnd = Create();

	if(hWnd == NULL)
	{
		return;
	}

	//ウィンドウの表示
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
}

// デストラクタ
CWindow::~CWindow()
{
	//ウィンドウクラスの登録解除
	UnregisterClass( "WindowSet", wcex.hInstance );
}

// ウィンドウの生成
HWND CWindow::Create()
{
	//ウィンドウクラスの登録
	RegisterClassEx( pwcex );

	//ウィンドウ生成
	return CreateWindowEx
			( 
				0,
				"WindowSet",																//クラス名
				WINDOW_NAME,																//ウィンドウ名
				WS_OVERLAPPEDWINDOW,														//種類
				CW_USEDEFAULT,																//表示位置Ｘ
				CW_USEDEFAULT,																//表示位置Ｙ
				SCREEN_WIDTH,																//幅
				SCREEN_HEIGHT,																//高さ
				NULL,																		//親ウィンドウハンドル
				NULL,																		//メニューハンドル
				instance,																	//インスタンスハンドル
				NULL																		//その他作成データ
			);
}

// プロシージャ処理
LRESULT CALLBACK WndProc( HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam )
{
	int nID = 0;																			//ID用変数

	switch( umsg )
	{
		/*-----------------------
		|	キーの押下を取得	|
		-----------------------*/
		case WM_KEYDOWN :

			switch( wParam )
			{
				/*-----------------------------------------------
				|	ESCAPEが押されたときにウィンドウを破棄する	|
				-----------------------------------------------*/
				case VK_ESCAPE :					
					nID = MessageBox( hWnd, "ゲームを終了しますか？", "ウィンドウ破棄", MB_YESNO );

					if( nID == IDYES )
					{
						DestroyWindow( hWnd );												//ウィンドウ破棄
					}

					break;
			}

			break;

		/*-------------------------------
		|	ウィンドウが破棄されるとき	|
		-------------------------------*/
		case WM_DESTROY :

			//ウィンドウを破棄する
			PostQuitMessage( 0 );

			break;
	}

	return DefWindowProc( hWnd, umsg, wParam, lParam );										//プロシージャーを返す
}

// パラメーターの設定
void CWindow::SettingPram()
{
	//ウィンドウクラスの情報を設定
	pwcex->cbSize = sizeof( WNDCLASSEX );													// 構造体サイズ
	pwcex->style = CS_CLASSDC;																// スタイル
	pwcex->lpfnWndProc = WndProc;															// ウィンドウプロシージャ
	pwcex->hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1);									// ウィンドウ背景						
	pwcex->hInstance = instance;															// インスタンスハンドル
	pwcex->cbClsExtra = 0;																	// 拡張情報１
	pwcex->cbWndExtra = 0;																	// 拡張情報２
	pwcex->hCursor = LoadCursor( NULL, IDC_ARROW );											// マウスカーソル
	pwcex->hIcon = NULL;																	// アイコン
	pwcex->hIconSm = NULL;
	pwcex->lpszClassName = "WindowSet";														// ウィンドウクラス名
	pwcex->lpszMenuName = NULL;																// メニュー名
}