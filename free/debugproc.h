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
// �C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define MAX_CHAR_DEBUG						( 1024 )							// �ő啶����

//------------------------------------------------------------------------------
// �N���X�錾
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

	LPD3DXFONT m_pD3DXFontA;													//�t�H���g�I�u�W�F�N�g

	char m_aStrDebug[ MAX_CHAR_DEBUG ];											// ������i�[���[�N
};

#endif

#endif

/* ----- EOF ----- */