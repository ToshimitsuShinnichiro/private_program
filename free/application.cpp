/*
	application.cpp
*/

// インクルード
#include "application.h"
#include <time.h>
#include <mmsystem.h>
#include <Windows.h>

#pragma comment( lib, "winmm.lib" ) // timeGetTime() リンク指定

int CApplication::_fps = 0;

// コンストラクタ
CApplication::CApplication() : dwCurrentTime(0), dwFrameCount(0)
{	
	//時間の同期
	timeBeginPeriod( 1 );

	dwExecLastTime = dwFPSLastTime = timeGetTime( );										//現在時刻の取得
}

// デストラクタ
CApplication::~CApplication()
{
	//時間同期の終了
	timeEndPeriod( 1 );
}

// 更新
void CApplication::Update()
{
	dwCurrentTime = timeGetTime( );													//現在時間の同期

	//FPS計算
	if( ( dwCurrentTime - dwFPSLastTime ) >= 500 )
	{
		_fps = ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );			//FPSカウントの計算
		dwFPSLastTime = dwCurrentTime;												//FPSラストタイムの取得
		dwFrameCount = 0;															//フレームカウント初期化
	}

	//FPSで処理
	if( ( dwCurrentTime - dwExecLastTime ) >= ( 1000 / 60 ) )
	{
		dwExecLastTime = dwCurrentTime;												//現在時間の代入

		/*---------------
		|	ゲーム処理	|
		---------------*/
		//pManeger->Update();															//更新処理
		//pManeger->Draw();															//描画処理

		dwFrameCount++;																//フレームカウントのインクリメント
	}
}