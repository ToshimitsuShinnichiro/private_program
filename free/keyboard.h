//==============================================================================
//
// FineName [ keyboard.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "input.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define MAX_KEY									( 256 )							// キーの最大数

//------------------------------------------------------------------------------
// クラス宣言
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

	// キー取得
	bool GetKeyboardPress( int nKey );
	bool GetKeyboardTrigger( int nKey );
	bool GetKeyboardRelease( int nKey );
	bool GetKeyboardRepeat( int nKey );

private:
	BYTE m_aKeyStatePress[ MAX_KEY ];												// キー押下ワーク
	BYTE m_aKeyStateTrigger[ MAX_KEY ];												// キーを押した瞬間のワーク
	BYTE m_aKeyStateRelease[ MAX_KEY ];												// キーを放した瞬間のワーク
	BYTE m_aKeyStateRepeat[ MAX_KEY ];												// キーを時間経過後に取得のワーク
	int m_aKeyStateRepeatCount[ MAX_KEY ];											// キーリピート用カウント
};

#endif

/* ----- EOF ----- */