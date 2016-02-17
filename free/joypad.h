//==============================================================================
//
// FineName [ joypad.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "input.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define MAX_JOYPAD								( 32 )							// ジョイパッドキーの最大数

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
// クラス宣言
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

	// キー取得
	bool GetPadPress( int key );
	bool GetPadTrigger( int key );
	bool GetPadRelease( int key );
	bool GetPadRepeat( int key );

	// スティック取得
	int GetCrossX( void ){ return _joyStatePress.lX; }
	int GetCrossY( void ){ return _joyStatePress.lY; }

	bool GetRightTrigger( void ){ return _rightTrigger; }
	bool GetLeftTrigger( void ){ return _leftTrigger; }
	bool GetUpTrigger( void ){ return _upTrigger; }
	bool GetDownTrigger( void ){ return _downTrigger; }

	bool GetCreate( void ){ return _isCreate; }

private:
	static BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE *didInstance, void *context );	//ジョイパッド生成コールバック関数
	static BOOL CALLBACK EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *didoi, void *context );		//ジョイパッド能力設定コールバック関数

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