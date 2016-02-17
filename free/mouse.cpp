//==============================================================================
//
// FineName [ mouse.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "mouse.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------------

//==============================================================================
//	�֐���	CMouse
//	����	None
//	�߂�l	None
//==============================================================================
CMouse::CMouse()
{
}

//==============================================================================
//	�֐���	~CMouse
//	����	None
//	�߂�l	None
//==============================================================================
CMouse::~CMouse()
{
}

//==============================================================================
//	�֐���	Init
//	����	HINSTANECE, HWND
//	�߂�l	HRESULT
//==============================================================================
HRESULT CMouse::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr;																	// �i�[���[�N

	CInput::Init( hInstance, hWnd );

	// ���̓f�o�C�X�̐���
	hr = m_pDInput->CreateDevice( GUID_SysMouse, &m_pDIDevice, NULL );

	// �����Ɏ��s�����Ƃ�
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�}�E�X��������܂���", "�}�E�X", MB_OK );

		return hr;																// HRESULT��Ԃ�
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIDevice->SetDataFormat( &c_dfDIMouse2 );

	// �ݒ�Ɏ��s�����Ƃ�
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�f�[�^��ݒ�ł��܂���", "�f�[�^�t�H�[�}�b�g", MB_OK );

		return hr;																// HRESULT��Ԃ�
	}

	// �������[�h�̐ݒ�
	hr = m_pDIDevice->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );

	// �ݒ�Ɏ��s�����Ƃ�
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "�ݒ�ł��܂���", "�������[�h", MB_OK );

		return hr;																// HRESULT��Ԃ�
	}

	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
    DIPROPDWORD diprop;
    diprop.diph.dwSize  = sizeof(diprop); 
    diprop.diph.dwHeaderSize    = sizeof(diprop.diph); 
    diprop.diph.dwObj   = 0;
    diprop.diph.dwHow   = DIPH_DEVICE;
    diprop.dwData       = DIPROPAXISMODE_REL;
    //diprop.dwData       = DIPROPAXISMODE_ABS; // ��Βl���[�h�̏ꍇ
	hr = m_pDIDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	// �ݒ�Ɏ��s�����Ƃ�
    if( FAILED( hr ) )
    {
		MessageBox( NULL,"�����[�h�̐ݒ�Ɏ��s","Direct Input Error",MB_OK );

        return hr;
    }

	// �L�[�{�[�h�ւ̃A�N�Z�X�����擾(���͐���J�n)
	hr =  m_pDIDevice->Acquire();

	m_mouseInfo.lX = 0;
	m_mouseInfo.lY = 0;
	m_mouseInfo.lZ = 0;

	oldPos = VECTOR3D( 0.0f, 0.0f, 0.0f );

	for( int nCnt = 0; nCnt < 8; nCnt++ )
	{
		m_mouseInfo.rgbButtons[ nCnt ] = 0;
	}

	return S_OK;																// S_OK��Ԃ�
}

//==============================================================================
//	�֐���	Uninit
//	����	None
//	�߂�l	None
//==============================================================================
void CMouse::Uninit( void )
{
	// �L�[�{�[�h�̏I������
	CInput::Uninit();
}

//==============================================================================
//	�֐���	Update
//	����	None
//	�߂�l	None
//==============================================================================
HRESULT CMouse::Update( void )
{
	HRESULT hr = 0;

	// �f�o�C�X����}�E�X�̏��擾
	if( SUCCEEDED( m_pDIDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), &m_mouseInfo ) ) )
	{
		// �ȑO�̍��W���i�[
		oldPos = VECTOR3D( ( float )m_mouseInfo.lX, ( float )m_mouseInfo.lY, ( float )m_mouseInfo.lZ );
	}
	else
	{
		// �}�E�X�ւ̃A�N�Z�X�����擾
		m_pDIDevice->Acquire( );
	}

	return hr;
}

//==============================================================================
//	�֐���	GetLClick
//	����	None
//	�߂�l	bool
//==============================================================================
bool CMouse::GetLClick( void )
{
	return ( m_mouseInfo.rgbButtons[ 0 ] & 0x0001 )? true : false;
}

//==============================================================================
//	�֐���	GetRClick
//	����	None
//	�߂�l	bool
//==============================================================================
bool CMouse::GetRClick( void )
{
	return ( m_mouseInfo.rgbButtons[ 1 ] & 0x0001 )? true : false;
}

//==============================================================================
//	�֐���	GetCClick
//	����	None
//	�߂�l	bool
//==============================================================================
bool CMouse::GetCClick( void )
{
	return ( m_mouseInfo.rgbButtons[ 2 ] & 0x0001 )? true : false;
}

//==============================================================================
//	�֐���	GetDiff
//	����	None
//	�߂�l	VECTOR3D
//==============================================================================
VECTOR3D CMouse::GetDiff( void )
{
	float x, y, z;																// ���W�i�[���[�N

	// �����̌v�Z
	x = ( float )m_mouseInfo.lX - oldPos.x;
	y = ( float )m_mouseInfo.lY - oldPos.y;
	z = ( float )m_mouseInfo.lZ - oldPos.z;

	return VECTOR3D( x, y, z );
}

//==============================================================================
//	�֐���	Create
//	����	None
//	�߂�l	CMouse
//==============================================================================
CMouse *CMouse::Create( void )
{
	CMouse *pMouse;

	pMouse = NEW CMouse;														 // �C���X�^���X�̐���

	return pMouse;
}

//==============================================================================
//	�֐���	Release
//	����	None
//	�߂�l	None
//==============================================================================
void CMouse::Release( void )
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