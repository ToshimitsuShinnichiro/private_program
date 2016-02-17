//==============================================================================
//
// FineName [ debugproc.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifdef _DEBUG

#define _CRT_SECURE_NO_WARNINGS

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "debugproc.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------

//==============================================================================
//	関数名	CDebugProc
//	引数	None
//	戻り値	None
//==============================================================================
CDebugProc::CDebugProc()
{
	this->m_aStrDebug[0] = '\0';
}

//==============================================================================
//	関数名	~CPlayer
//	引数	None
//	戻り値	None
//==============================================================================
CDebugProc::~CDebugProc()
{
}

//==============================================================================
//	関数名	GetInstance
//	引数	None
//	戻り値	None
//==============================================================================
CDebugProc *CDebugProc::GetInstance( void )
{
	static CDebugProc CDebugProc;

	return &CDebugProc;
}

//==============================================================================
//	関数名	Init
//	引数	int, int
//	戻り値	None
//==============================================================================
void CDebugProc::Init( int height, int width )
{
	CRenderer *pRenderer = CRenderer::GetInstance();							// インスタンスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();							// デバイスの取得
	HRESULT hr;

	// フォント生成
	hr = D3DXCreateFont( pDevice,													// デバイスオブジェクト
					height,														// 文字の高さ
					width,														// 文字の幅
					0,
					0,
					FALSE,
					SHIFTJIS_CHARSET,											// 文字コード
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal",													// フォントタイプ
					&m_pD3DXFontA );											// フォントオブジェクト
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CDebugProc::Uninit( void )
{
	//フォントオブジェクトの解放
	if( m_pD3DXFontA != NULL )
	{
		m_pD3DXFontA->Release( );												//フォントオブジェクトの解放
		m_pD3DXFontA = NULL;													//フォントオブジェクトを空にする
	}
}

//==============================================================================
//	関数名	Draw
//	引数	None
//	戻り値	None
//==============================================================================
void CDebugProc::Draw( void )
{
	CRenderer *pRenderer = CRenderer::GetInstance();							// インスタンスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();							// デバイスの取得

	RECT rect = { 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH };							//画面領域

	m_pD3DXFontA->DrawText( NULL,
						   &m_aStrDebug[ 0 ],									//描画先頭文字位置
						   -1,
						   &rect,												//表示領域
						   DT_LEFT,												//フォント配置
						   D3DCOLOR_RGBA( 255, 255, 0, 255 ) );				//色 );

	// デバッグ情報ワークのクリア
	ZeroMemory( &m_aStrDebug[ 0 ], sizeof( m_aStrDebug ) );
}

//==============================================================================
//	関数名	PrintDebugProc
//	引数	None
//	戻り値	None
//==============================================================================
void CDebugProc::PrintDebugProc( char *fmt, ... )
{
	va_list ap;																				// 文字列ポインタ
	char str[ 256 ];																		// 文字列格納ワーク

	// 文字列の再構成
	va_start( ap, fmt );

	vsprintf( &str[ 0 ], fmt, ap );

	// 再構成終了
	va_end( ap );

	// 文字列の追加
	strcat( m_aStrDebug, &str[ 0 ] );
}

#endif

/* ----- EOF ----- */