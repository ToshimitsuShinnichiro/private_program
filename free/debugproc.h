//==============================================================================
//
// FineName [ debugoroc.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#ifdef _DEBUG

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define MAX_CHAR_DEBUG						( 1024 )							// 最大文字数

//------------------------------------------------------------------------------
// クラス宣言
//------------------------------------------------------------------------------
class CDebugProc
{
public:
	void Init( int height, int width );
	void Uninit( void );
	void PrintDebugProc( char *fmt, ... );
	void Draw( void );

	static CDebugProc *GetInstance( void );

private:
	CDebugProc();
	CDebugProc( const CDebugProc &debugProc );
	~CDebugProc();

	LPD3DXFONT m_pD3DXFontA;													//フォントオブジェクト

	char m_aStrDebug[ MAX_CHAR_DEBUG ];											// 文字列格納ワーク
};

#endif

#endif

/* ----- EOF ----- */