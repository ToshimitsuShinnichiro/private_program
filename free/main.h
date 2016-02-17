/********************************************************************************************
*
*	FileContent	main����
*	FileName	main.h
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include <windows.h>
#include "xaudio2.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define SCREEN_WIDTH				( 800.0f )									// ��ʂ̉���
#define SCREEN_HEIGHT				( 600.0f )									// ��ʂ̏c��
#define SCREEN_TOP					( 0 )										// ��ʂ̏���W
#define SCREEN_LEFT					( 0 )										// ��ʂ̍����W
#define MAX_WIDTH_FIELD				( 1000 )									// �����̍ő吔
#define MAX_HEIGHT_FIELD			( 1000 )									// �c���̍ő吔
#define MAX_POS_Y					( 600 )										// �����̌��E
#define PI							( 3.141592f )								// �p�C
#define RADIAN( x )					( PI / 180 * x )							// ���W�A��
#define G							( -9.8f / 100.0f )							// �d��
#define MYU							( 0.23f )									// ���C�W��

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
//	�v���g�^�C�v�錾
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