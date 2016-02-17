//==============================================================================
//
// FineName [ keyboard.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "input.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define MAX_KEY									( 256 )							// �L�[�̍ő吔

//------------------------------------------------------------------------------
// �N���X�錾
//------------------------------------------------------------------------------
class CKeyboard :public CInput
{
public:
	CKeyboard();
	~CKeyboard();

	HRESULT Init( HINSTANCE hInstance, HWND hWnd );
	void Uninit( void );
	HRESULT Update( void );

	static CKeyboard *Create( void );
	void Release( void );

	// �L�[�擾
	bool GetKeyboardPress( int nKey );
	bool GetKeyboardTrigger( int nKey );
	bool GetKeyboardRelease( int nKey );
	bool GetKeyboardRepeat( int nKey );

private:
	BYTE m_aKeyStatePress[ MAX_KEY ];												// �L�[�������[�N
	BYTE m_aKeyStateTrigger[ MAX_KEY ];												// �L�[���������u�Ԃ̃��[�N
	BYTE m_aKeyStateRelease[ MAX_KEY ];												// �L�[��������u�Ԃ̃��[�N
	BYTE m_aKeyStateRepeat[ MAX_KEY ];												// �L�[�����Ԍo�ߌ�Ɏ擾�̃��[�N
	int m_aKeyStateRepeatCount[ MAX_KEY ];											// �L�[���s�[�g�p�J�E���g
};

#endif

/* ----- EOF ----- */