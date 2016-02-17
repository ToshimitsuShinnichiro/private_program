//==============================================================================
//
// FineName [ joypad.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "input.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define MAX_JOYPAD								( 32 )							// �W���C�p�b�h�L�[�̍ő吔

typedef enum
{
	JOYKEY_LEFT = 3,
	JOYKEY_RIGHT = 0,
	JOYKEY_UP = 5,
	JOYKEY_DOWN = 1,
	JOYKEY_R1 = 4,
	JOYKEY_L1 = 2,
	JOYKEY_START = 6,
} JOYKEY;

//------------------------------------------------------------------------------
// �N���X�錾
//------------------------------------------------------------------------------
class CJoypad :public CInput
{
public:
	CJoypad();
	~CJoypad();

	HRESULT Init( HINSTANCE hInstance, HWND hWnd );
	void Uninit( void );
	HRESULT Update( void );

	static CJoypad *Create( void );

	// �L�[�擾
	bool GetPadPress( int key );
	bool GetPadTrigger( int key );
	bool GetPadRelease( int key );
	bool GetPadRepeat( int key );

	// �X�e�B�b�N�擾
	int GetCrossX( void ){ return _joyStatePress.lX; }
	int GetCrossY( void ){ return _joyStatePress.lY; }

	bool GetRightTrigger( void ){ return _rightTrigger; }
	bool GetLeftTrigger( void ){ return _leftTrigger; }
	bool GetUpTrigger( void ){ return _upTrigger; }
	bool GetDownTrigger( void ){ return _downTrigger; }

	bool GetCreate( void ){ return _isCreate; }

private:
	static BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE *didInstance, void *context );	//�W���C�p�b�h�����R�[���o�b�N�֐�
	static BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *didoi, void *context );		//�W���C�p�b�h�\�͐ݒ�R�[���o�b�N�֐�

	DIJOYSTATE _joyStatePress;
	DIJOYSTATE _joyStateTrigger;
	DIJOYSTATE _joyStateRelease;
	DIJOYSTATE _joyStateRepeat;
	DIDEVCAPS _joypadValue;

	bool _rightTrigger, _leftTrigger, _upTrigger, _downTrigger;
	bool _isCreate;

	int _repeatCount[ MAX_JOYPAD ];
};

#endif

/* ----- EOF ----- */