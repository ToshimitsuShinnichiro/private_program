/********************************************************************************************
*
*	FileContent	main処理
*	FileName	main.h
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include <windows.h>
#include "xaudio2.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define SCREEN_WIDTH				( 800.0f )									// 画面の横幅
#define SCREEN_HEIGHT				( 600.0f )									// 画面の縦幅
#define SCREEN_TOP					( 0 )										// 画面の上座標
#define SCREEN_LEFT					( 0 )										// 画面の左座標
#define MAX_WIDTH_FIELD				( 1000 )									// 横幅の最大数
#define MAX_HEIGHT_FIELD			( 1000 )									// 縦幅の最大数
#define MAX_POS_Y					( 600 )										// 高さの限界
#define PI							( 3.141592f )								// パイ
#define RADIAN( x )					( PI / 180 * x )							// ラジアン
#define G							( -9.8f / 100.0f )							// 重力
#define MYU							( 0.23f )									// 摩擦係数

#ifdef _DEBUG
#define NEW		new(_NORMAL_BLOCK,__FILE__,__LINE__)
#else
#define NEW		new
#endif

typedef enum
{
	RIGHIT = 0,
	LEFT,
	NONE
} CONTROAL;

typedef enum
{
	SHADER_DRAWTEXTURESHADOWMAP = 0,
	SHADER_DRAWTEXTURESHADOWMAPNONTEX,
	SHADER_DRAWNORMALDEPTH,
	SHADER_3DTEXNONE,
	SHADER_3DNORMAL,
	SHADER_SHADOWMAP,
	SHADER_SPECULAR,
	SHADER_3DMODEL,
	SHADER_ORIGIN,
	SHADER_NORMALMAP,
	SHADER_TOON,
	SHADER_EFFECT,
	SHADER_SCLTOON,
	SHADER_2DNORMAL,
	SHADER_MAX,
} SHADERTYPE;

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------

template <typename T>
inline void SafeDelete( T*& p )
{
	if( p != NULL )
	{
		delete ( p );

		( p ) = NULL;
	}
}

template <typename T>
inline void SafeDeleteArray( T*& p )
{
	if( p != NULL )
	{
		delete[] ( p );

		( p ) = NULL;
	}
}

template <typename T>
inline void SafeRelease( T*& p )
{
	if( p != NULL )
	{
		( p )->Release();

		( p ) = NULL;
	}
}

template <class T, class U>
inline T SCast(U p)
{
	return static_cast<T>(p);
}

template <class T>
inline T RCast(void* p)
{
	return reinterpret_cast<T>(p);
}

template <class T, class S>
inline bool Instanceof( T *t, S *s )
{
	if( dynamic_cast<t>(s) != NULL ) return true;
	return false;
}

inline float lerp(float x, float y, float s)
{
	return x + s * (y - x);
}

#endif

/* --- EOF --- */