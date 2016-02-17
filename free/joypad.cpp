//==============================================================================
//
// FineName [ joypad.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "joypad.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define MAX_KEY_REPEAT						( 40 )								// ���s�[�g�̑҂�����

//------------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------------

//==============================================================================
//	�֐���	CJoypad
//	����	None
//	�߂�l	None
//==============================================================================
CJoypad::CJoypad()
{
	_isCreate = false;
}

//==============================================================================
//	�֐���	~CJoypad
//	����	None
//	�߂�l	None
//==============================================================================
CJoypad::~CJoypad()
{
	Uninit();
}

//==============================================================================
//	�֐���	Init
//	����	HINSTANECE, HWND
//	�߂�l	HRESULT
//==============================================================================
HRESULT CJoypad::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr;																	// �i�[���[�N

	CInput::Init( hInstance, hWnd );

	// ���̓f�o�C�X�̐���
	hr = m_pDInput->EnumDevices( DI8DEVCLASS_GAMECTRL,			//�f�o�C�X�^�C�v(�Q�[���R���g���[��)
								 (LPDIENUMDEVICESCALLBACK)EnumJoysticksCallback,//�񋓂����f�o�C�X���Ƃ� 1 ��Ăяo�����R�[���o�b�N�֐��̃A�h���X
								 (void*)this,					//�A�v���P�[�V������`�� 32 �r�b�g�l
								 DIEDFL_ATTACHEDONLY );			//���ݐڑ�����Ă���W���C�p�b�h�̌��o

	// �����Ɏ��s�����Ƃ�
	if( m_pDIDevice == NULL )
	{
		MessageBox( hWnd, "�W���C�p�b�h��������܂���", "�W���C�p�b�h", MB_OK );

		return hr;																// HRESULT��Ԃ�
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIDevice->SetDataFormat( &c_dfDIJoystick );

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

	//�W���C�p�b�h�̔\�͂��擾����
	_joypadValue.dwSize = sizeof( DIDEVCAPS );
	hr = m_pDIDevice->GetCapabilities( &_joypadValue );

	if( FAILED( hr ) ) 
	{ 
		MessageBox( hWnd , "�W���C�p�b�h�̔\�͂̎擾�Ɏ��s���܂���." , "Error" , MB_OK );

        return FALSE; 
	}

	//�W���C�p�b�h�̔\�͂̐ݒ�
	hr = m_pDIDevice->EnumObjects( EnumAxesCallback, (void*)this, DIDFT_AXIS );

	if( FAILED( hr ) ) 
	{ 
		MessageBox( hWnd , "�W���C�p�b�h�̔\�͂̐ݒ�Ɏ��s���܂���." , "Error" , MB_OK );

        return FALSE; 
	}

	//�f�o�C�X����f�[�^���擾�ł��邱�Ƃ��m�F
	hr = m_pDIDevice -> Poll();

	//�f�[�^���擾�ł��Ȃ�������
	if ( FAILED( hr ) )
	{
		//�W���C�p�b�h�̃A�N�Z�X�����l��
		hr = m_pDIDevice -> Acquire();
		
		//�l���ł���܂ŌJ��Ԃ�
		while( hr == DIERR_INPUTLOST )
		{
			hr = m_pDIDevice -> Acquire();
		}
	}

	for( int i = 0; i < MAX_JOYPAD; i++ )
	{
		_repeatCount[i] = 0;
		_joyStatePress.rgbButtons[i] = 0;
		_joyStateTrigger.rgbButtons[i] = 0;
		_joyStateRelease.rgbButtons[i] = 0;
		_joyStateRepeat.rgbButtons[i] = 0;
	}

	_joyStatePress.lX = 0;
	_joyStatePress.lY = 0;

	_isCreate = true;

	return S_OK;																// S_OK��Ԃ�
}

//==============================================================================
//	�֐���	Uninit
//	����	None
//	�߂�l	None
//==============================================================================
void CJoypad::Uninit( void )
{
	// �L�[�{�[�h�̏I������
	CInput::Uninit();
}

//==============================================================================
//	�֐���	Update
//	����	None
//	�߂�l	None
//==============================================================================
HRESULT CJoypad::Update( void )
{
	DIJOYSTATE joyState;
	HRESULT hr = 0;

	// �\�͎擾
	m_pDIDevice->Poll();

	// �f�o�C�X����L�[�{�[�h�̏��擾
	if( SUCCEEDED( m_pDIDevice->GetDeviceState( sizeof( joyState ), &joyState ) ) )
	{
		/*-------------------
		|	MAX_KEY�����[�v	|
		-------------------*/
		for( int nCntKey = 0; nCntKey < MAX_JOYPAD; nCntKey++ )
		{
			// �L�[�g���K�[�̍쐬
			_joyStateTrigger.rgbButtons[ nCntKey ] = ( ( _joyStatePress.rgbButtons[ nCntKey ] ^ joyState.rgbButtons[ nCntKey ] ) &
											   joyState.rgbButtons[ nCntKey ] );		// �������u�Ԃ̃L�[���擾

			// �L�[�����[�X�̍쐬
			_joyStateRelease.rgbButtons[ nCntKey ] = ( ( _joyStatePress.rgbButtons[ nCntKey ] ^ joyState.rgbButtons[ nCntKey ] ) &
												_joyStatePress.rgbButtons[ nCntKey ] );	// �������u�Ԃ̃L�[���擾

			// �L�[���s�[�g�̍쐬
			_joyStateRepeat.rgbButtons[ nCntKey ] = _joyStatePress.rgbButtons[ nCntKey ];	// ���[�s�[�g�Ƀv���X���i�[

			// 1�񉟂������Ƃ��������ςȂ��̂Ƃ�
			if( _joyStateRepeat.rgbButtons[ nCntKey ] != NULL )
			{
				// ���s�[�g�̑ҋ@����
				if( ( _repeatCount[ nCntKey ] > 0 ) && ( _repeatCount[ nCntKey ] < MAX_KEY_REPEAT ) )
				{
					_joyStateRepeat.rgbButtons[ nCntKey ] = NULL;				// �L�[���s�[�g�̒��g��NULL�ɂ���
				}

				_repeatCount[ nCntKey ]++;										// �L�[���s�[�g�ҋ@���Ԃ̃C���N�������g
			}
			else
			{
				_repeatCount[ nCntKey ] = 0;									// �L�[���s�[�g�̑ҋ@���Ԃ̏�����
			}
		}

		_leftTrigger = _rightTrigger = _upTrigger = _downTrigger = false;

		// ���g���K�[
		if( ( _joyStatePress.lX < -8.0f ) && ( joyState.lX > -8.0f ) ) _leftTrigger = true;

		// �E�g���K�[
		if( ( _joyStatePress.lX > 8.0f ) && ( joyState.lX < 8.0f ) ) _rightTrigger = true;

		// ��g���K�[
		if( ( _joyStatePress.lY < -10.0f ) && ( joyState.lY > -10.0f ) ) _upTrigger = true;

		// �E�g���K�[
		if( ( _joyStatePress.lY > 8.0f ) && ( joyState.lY < 8.0f ) ) _downTrigger = true;


		// �L�[�v���X�̍쐬
		_joyStatePress = joyState;												// �L�[�̉������ςȂ����i�[
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
bool CJoypad::GetPadPress( int key )
{
	return ( _joyStatePress.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	GetKeyboardTrigger
//	����	int
//	�߂�l	bool
//==============================================================================
bool CJoypad::GetPadTrigger( int key )
{
	return ( _joyStateTrigger.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	GetKeyboardRelease
//	����	int
//	�߂�l	bool
//==============================================================================
bool CJoypad::GetPadRelease( int key )
{
	return ( _joyStateRelease.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	GetKeyboardRepeat
//	����	int
//	�߂�l	bool
//==============================================================================
bool CJoypad::GetPadRepeat( int key )
{
	return ( _joyStateRepeat.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	�֐���	Create
//	����	None
//	�߂�l	CKeyboard
//==============================================================================
CJoypad *CJoypad::Create( void )
{
	CJoypad *pJoypad  = NULL;

	pJoypad = NEW CJoypad;														// �C���X�^���X�̐���

	return pJoypad;
}

//==============================================================================
//	�֐���	EnumJoysticksCallback
//	����	None
//	�߂�l	None
//==============================================================================
BOOL CALLBACK CJoypad::EnumJoysticksCallback( const DIDEVICEINSTANCE *didInstance, void *context )
{
	HRESULT hr;

	//�W���C�p�b�h�|�C���^�ɕϊ�
	CJoypad *pJoypad = ( CJoypad* )context;
	
	//�f�o�C�X�̐���
	hr = m_pDInput->CreateDevice( didInstance->guidInstance, &pJoypad->m_pDIDevice, NULL );
	
	if ( FAILED( hr ) )
	{
		//�쐬�o���Ă��Ȃ����߂�����x
		return DIENUM_CONTINUE;
	}
	
	//�쐬����
	return DIENUM_STOP;
}

//==============================================================================
//	�֐���	EnumJoysticksCallback
//	����	None
//	�߂�l	None
//==============================================================================
BOOL CALLBACK CJoypad::EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *didoi, void *context )
{
	HRESULT     hr;
	DIPROPRANGE diprg;
	
	//�W���C�p�b�h�|�C���^�ɕϊ�
	CJoypad *pJoypad = ( CJoypad* )context;
	
	//�W���C�p�b�h�̔\�͂̐ݒ�
	diprg.diph.dwSize       = sizeof( DIPROPRANGE );
	diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.diph.dwObj        = didoi->dwType;
	diprg.lMin              = 0 - 1000;					//�\���{�^���̍ŏ��l
	diprg.lMax              = 0 + 1000;					//�\���{�^���̍ő�l

	//�f�o�C�X�ɐݒ�
	hr = pJoypad->m_pDIDevice->SetProperty( DIPROP_RANGE, &diprg.diph );
	
	if ( FAILED( hr ) )
	{
		return DIENUM_STOP;
	}
	
	return DIENUM_CONTINUE;
}

/* ----- EOF ----- */