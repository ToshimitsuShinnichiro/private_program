//==============================================================================
//
// FineName [ debugproc.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifdef _DEBUG

#define _CRT_SECURE_NO_WARNINGS

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "debugproc.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------------

//==============================================================================
//	�֐���	CDebugProc
//	����	None
//	�߂�l	None
//==============================================================================
CDebugProc::CDebugProc()
{
	this->m_aStrDebug[0] = '\0';
}

//==============================================================================
//	�֐���	~CPlayer
//	����	None
//	�߂�l	None
//==============================================================================
CDebugProc::~CDebugProc()
{
}

//==============================================================================
//	�֐���	GetInstance
//	����	None
//	�߂�l	None
//==============================================================================
CDebugProc *CDebugProc::GetInstance( void )
{
	static CDebugProc CDebugProc;

	return &CDebugProc;
}

//==============================================================================
//	�֐���	Init
//	����	int, int
//	�߂�l	None
//==============================================================================
void CDebugProc::Init( int height, int width )
{
	CRenderer *pRenderer = CRenderer::GetInstance();							// �C���X�^���X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();							// �f�o�C�X�̎擾
	HRESULT hr;

	// �t�H���g����
	hr = D3DXCreateFont( pDevice,													// �f�o�C�X�I�u�W�F�N�g
					height,														// �����̍���
					width,														// �����̕�
					0,
					0,
					FALSE,
					SHIFTJIS_CHARSET,											// �����R�[�h
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH,
					"Terminal",													// �t�H���g�^�C�v
					&m_pD3DXFontA );											// �t�H���g�I�u�W�F�N�g
}

//==============================================================================
//	�֐���	Uninit
//	����	None
//	�߂�l	None
//==============================================================================
void CDebugProc::Uninit( void )
{
	//�t�H���g�I�u�W�F�N�g�̉��
	if( m_pD3DXFontA != NULL )
	{
		m_pD3DXFontA->Release( );												//�t�H���g�I�u�W�F�N�g�̉��
		m_pD3DXFontA = NULL;													//�t�H���g�I�u�W�F�N�g����ɂ���
	}
}

//==============================================================================
//	�֐���	Draw
//	����	None
//	�߂�l	None
//==============================================================================
void CDebugProc::Draw( void )
{
	CRenderer *pRenderer = CRenderer::GetInstance();							// �C���X�^���X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();							// �f�o�C�X�̎擾

	RECT rect = { 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH };							//��ʗ̈�

	m_pD3DXFontA->DrawText( NULL,
						   &m_aStrDebug[ 0 ],									//�`��擪�����ʒu
						   -1,
						   &rect,												//�\���̈�
						   DT_LEFT,												//�t�H���g�z�u
						   D3DCOLOR_RGBA( 255, 255, 0, 255 ) );				//�F );

	// �f�o�b�O��񃏁[�N�̃N���A
	ZeroMemory( &m_aStrDebug[ 0 ], sizeof( m_aStrDebug ) );
}

//==============================================================================
//	�֐���	PrintDebugProc
//	����	None
//	�߂�l	None
//==============================================================================
void CDebugProc::PrintDebugProc( char *fmt, ... )
{
	va_list ap;																				// ������|�C���^
	char str[ 256 ];																		// ������i�[���[�N

	// ������̍č\��
	va_start( ap, fmt );

	vsprintf( &str[ 0 ], fmt, ap );

	// �č\���I��
	va_end( ap );

	// ������̒ǉ�
	strcat( m_aStrDebug, &str[ 0 ] );
}

#endif

/* ----- EOF ----- */