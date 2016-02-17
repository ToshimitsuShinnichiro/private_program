//==============================================================================
//
// FineName [ keyboard.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "keyboard.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define MAX_KEY_REPEAT						( 40 )								// ���s�[�g�̑҂�����

//------------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------------

//==============================================================================
//	�֐���	CKeyboard
//	����	None
//	�߂�l	None
//==============================================================================
CKeyboard::CKeyboard()
{
}

//==============================================================================
//	�֐���	~CKeyboard
//	����	None
//	�߂�l	None
//==============================================================================
CKeyboard::~CKeyboard()
{
}

//==============================================================================
//	�֐���	Init
//	����	HINSTANECE, HWND
//	�߂�l	HRESULT
//==============================================================================
HRESULT CKeyboard::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr;																	// �i�[���[�N

	CInput::Init( hInstance, hWnd );

	// ���̓f�o�C�X�̐���
	hr = m_pDInput->CreateDevice( GUID_SysKeyboard, &m_pDIDevice, NULL );

	// �����Ɏ��s�����Ƃ�
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�L�[�{�[�h��������܂���", "�L�[�{�[�h", MB_OK );

		return hr;																// HRESULT��Ԃ�
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIDevice->SetDataFormat( &c_dfDIKeyboard );

	// �ݒ�Ɏ��s�����Ƃ�
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�f�[�^��ݒ�ł��܂���", "�f�[�^�t�H�[�}�b�g", MB_OK );

		return hr;																// HRESULT��Ԃ�
	}

	// �������[�h�̐ݒ�
	hr = m_pDIDevice->SetCooperativeLevel( hWnd, ( DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) );

	// �ݒ�Ɏ��s�����Ƃ�
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�ݒ�ł��܂���", "�������[�h", MB_OK );

		return hr;																// HRESULT��Ԃ�
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����擾(���͐���J�n)
	hr =  m_pDIDevice->Acquire();

	// �L�[�i�[���[�N�̏�����
	for( int nCnt = 0; nCnt < MAX_KEY; nCnt++ )
	{
		m_aKeyStatePress[ nCnt ] = 0;											// �L�[�������[�N
		m_aKeyStateTrigger[ nCnt ] = NULL;										// �L�[���������u�Ԃ̃��[�N
		m_aKeyStateRelease[ nCnt ] = NULL;										// �L�[��������u�Ԃ̃��[�N
		m_aKeyStateRepeat[ nCnt ] = NULL;										// �L�[�����Ԍo�ߌ�Ɏ擾�̃��[�N
		m_aKeyStateRepeatCount[ nCnt ] = NULL;									// �L�[���s�[�g�p�J�E���g
	}

	return S_OK;																// S_OK��Ԃ�
}

//==============================================================================
//	�֐���	Uninit
//	����	None
//	�߂�l	None
//==============================================================================
void CKeyboard::Uninit( void )
{
	// �L�[�{�[�h�̏I������
	CInput::Uninit();
}

//==============================================================================
//	�֐���	Update
//	����	None
//	�߂�l	None
//==============================================================================
HRESULT CKeyboard::Update( void )
{
	BYTE aKeyState[ MAX_KEY ];
	HRESULT hr = 0;

	// �f�o�C�X����L�[�{�[�h�̏��擾
	if( SUCCEEDED( m_pDIDevice->GetDeviceState( sizeof( aKeyState ), &aKeyState[ 0 ] ) ) )
	{
		/*-------------------
		|	MAX_KEY�����[�v	|
		-------------------*/
		for( int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++ )
		{
			// �L�[�g���K�[�̍쐬
			m_aKeyStateTrigger[ nCntKey ] = ( ( m_aKeyStatePress[ nCntKey ] ^ aKeyState[ nCntKey ] ) &
											   aKeyState[ nCntKey ] );			// �������u�Ԃ̃L�[���擾

			// �L�[�����[�X�̍쐬
			m_aKeyStateRelease[ nCntKey ] = ( ( m_aKeyStatePress[ nCntKey ] ^ aKeyState[ nCntKey ] ) &
												m_aKeyStatePress[ nCntKey ] );	// �������u�Ԃ̃L�[���擾

			// �L�[���s�[�g�̍쐬
			m_aKeyStateRepeat[ nCntKey ] = m_aKeyStatePress[ nCntKey ];			// ���[�s�[�g�Ƀv���X���i�[

			// 1�񉟂������Ƃ��������ςȂ��̂Ƃ�
			if( m_aKeyStateRepeat[ nCntKey ] != NULL )
			{
				// ���s�[�g�̑ҋ@����
				if( ( m_aKeyStateRepeatCount[ nCntKey ] > 0 ) && ( m_aKeyStateRepeatCount[ nCntKey ] < MAX_KEY_REPEAT ) )
				{
					m_aKeyStateRepeat[ nCntKey ] = NULL;						// �L�[���s�[�g�̒��g��NULL�ɂ���
				}

				m_aKeyStateRepeatCount[ nCntKey ]++;							// �L�[���s�[�g�ҋ@���Ԃ̃C���N�������g
			}
			else
			{
				m_aKeyStateRepeatCount[ nCntKey ] = 0;							// �L�[���s�[�g�̑ҋ@���Ԃ̏�����
			}

			// �L�[�v���X�̍쐬
			m_aKeyStatePress[ nCntKey ] = aKeyState[ nCntKey ];					// �L�[�̉������ςȂ����i�[
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDIDevice->Acquire( );
	}

	return hr;
}

//==============================================================================
//	�֐���	GetKeyboardPress
//	����	int
//	�߂�l	bool
//==============================================================================
bool CKeyboard::GetKeyboardPress( int nKey )
{
	return ( m_aKeyStatePress[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	GetKeyboardTrigger
//	����	int
//	�߂�l	bool
//==============================================================================
bool CKeyboard::GetKeyboardTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	GetKeyboardRelease
//	����	int
//	�߂�l	bool
//==============================================================================
bool CKeyboard::GetKeyboardRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	GetKeyboardRepeat
//	����	int
//	�߂�l	bool
//==============================================================================
bool CKeyboard::GetKeyboardRepeat( int nKey )
{
	return ( m_aKeyStateRepeat[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	Create
//	����	None
//	�߂�l	CKeyboard
//==============================================================================
CKeyboard *CKeyboard::Create( void )
{
	CKeyboard *pKeyboard = NULL;

	pKeyboard = NEW CKeyboard;													// �C���X�^���X�̐���

	return pKeyboard;
}

//==============================================================================
//	�֐���	Release
//	����	None
//	�߂�l	None
//==============================================================================
void CKeyboard::Release( void )
{
	// �L�[�{�[�h�̏I������
	Uninit();

	// NULL�łȂ��Ƃ�
	if( this != NULL )
	{
		delete this;														// �C���X�^���X�̉��
	}
}

/* ----- EOF ----- */