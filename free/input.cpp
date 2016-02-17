//==============================================================================
//
// FineName [ input.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "input.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------------
LPDIRECTINPUT8 CInput::m_pDInput = NULL;

//==============================================================================
//	�֐���	CInput
//	����	None
//	�߂�l	None
//==============================================================================
CInput::CInput()
{
	m_pDIDevice =NULL;
}

//==============================================================================
//	�֐���	~CInput
//	����	None
//	�߂�l	None
//==============================================================================
CInput::~CInput()
{
}

//==============================================================================
//	�֐���	Init
//	����	HINSTANECE, HWND
//	�߂�l	HRESULT
//==============================================================================
HRESULT CInput::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr = NULL;

	// DirectInput�I�u�W�F�N�g�̐���
	if( m_pDInput == NULL )
	{
		hr = DirectInput8Create( hInstance, 
								 DIRECTINPUT_VERSION, 
								 IID_IDirectInput8, 
								 ( void** )&m_pDInput,
								 NULL );
	}

	return hr;																	// HRESULT��Ԃ�
}

//==============================================================================
//	�֐���	Uninit
//	����	None
//	�߂�l	None
//==============================================================================
void CInput::Uninit( void )
{
	// �f�o�C�X�̉��
	if( m_pDIDevice != NULL )
	{
		m_pDIDevice->Unacquire( );												// �L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDIDevice->Release( );												// �L�[�{�[�h�̉��
		m_pDIDevice = NULL;														// NULL����
	}

	// DirectInput�I�u�W�F�N�g�̉��
	if( m_pDInput != NULL )
	{
		m_pDInput->Release( );													// DirectInput�I�u�W�F�N�g�̉��
		m_pDInput = NULL;														// NULL����
	}
}

//==============================================================================
//	�֐���	Update
//	����	None
//	�߂�l	HRESULT
//==============================================================================
HRESULT CInput::Update( void )
{
	HRESULT hr = 0;

	return hr;
}

/* ----- EOF ----- */