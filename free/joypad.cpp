//==============================================================================
//
// FineName [ joypad.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "joypad.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define MAX_KEY_REPEAT						( 40 )								// リピートの待ち時間

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------

//==============================================================================
//	関数名	CJoypad
//	引数	None
//	戻り値	None
//==============================================================================
CJoypad::CJoypad()
{
	_isCreate = false;
}

//==============================================================================
//	関数名	~CJoypad
//	引数	None
//	戻り値	None
//==============================================================================
CJoypad::~CJoypad()
{
	Uninit();
}

//==============================================================================
//	関数名	Init
//	引数	HINSTANECE, HWND
//	戻り値	HRESULT
//==============================================================================
HRESULT CJoypad::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr;																	// 格納ワーク

	CInput::Init( hInstance, hWnd );

	// 入力デバイスの生成
	hr = m_pDInput->EnumDevices( DI8DEVCLASS_GAMECTRL,			//デバイスタイプ(ゲームコントローラ)
								 (LPDIENUMDEVICESCALLBACK)EnumJoysticksCallback,//列挙されるデバイスごとに 1 回呼び出されるコールバック関数のアドレス
								 (void*)this,					//アプリケーション定義の 32 ビット値
								 DIEDFL_ATTACHEDONLY );			//現在接続されているジョイパッドの検出

	// 生成に失敗したとき
	if( m_pDIDevice == NULL )
	{
		MessageBox( hWnd, "ジョイパッドが見つかりません", "ジョイパッド", MB_OK );

		return hr;																// HRESULTを返す
	}

	// データフォーマットの設定
	hr = m_pDIDevice->SetDataFormat( &c_dfDIJoystick );

	// 設定に失敗したとき
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "データを設定できません", "データフォーマット", MB_OK );

		return hr;																// HRESULTを返す
	}

	// 協調モードの設定
	hr = m_pDIDevice->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) );

	// 設定に失敗したとき
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "設定できません", "協調モード", MB_OK );

		return hr;																// HRESULTを返す
	}

	//ジョイパッドの能力を取得する
	_joypadValue.dwSize = sizeof( DIDEVCAPS );
	hr = m_pDIDevice->GetCapabilities( &_joypadValue );

	if( FAILED( hr ) ) 
	{ 
		MessageBox( hWnd , "ジョイパッドの能力の取得に失敗しました." , "Error" , MB_OK );

        return FALSE; 
	}

	//ジョイパッドの能力の設定
	hr = m_pDIDevice->EnumObjects( EnumAxesCallback, (void*)this, DIDFT_AXIS );

	if( FAILED( hr ) ) 
	{ 
		MessageBox( hWnd , "ジョイパッドの能力の設定に失敗しました." , "Error" , MB_OK );

        return FALSE; 
	}

	//デバイスからデータを取得できることを確認
	hr = m_pDIDevice -> Poll();

	//データを取得できなかったら
	if ( FAILED( hr ) )
	{
		//ジョイパッドのアクセス権を獲得
		hr = m_pDIDevice -> Acquire();
		
		//獲得できるまで繰り返す
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

	return S_OK;																// S_OKを返す
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CJoypad::Uninit( void )
{
	// キーボードの終了処理
	CInput::Uninit();
}

//==============================================================================
//	関数名	Update
//	引数	None
//	戻り値	None
//==============================================================================
HRESULT CJoypad::Update( void )
{
	DIJOYSTATE joyState;
	HRESULT hr = 0;

	// 能力取得
	m_pDIDevice->Poll();

	// デバイスからキーボードの情報取得
	if( SUCCEEDED( m_pDIDevice->GetDeviceState( sizeof( joyState ), &joyState ) ) )
	{
		/*-------------------
		|	MAX_KEY分ループ	|
		-------------------*/
		for( int nCntKey = 0; nCntKey < MAX_JOYPAD; nCntKey++ )
		{
			// キートリガーの作成
			_joyStateTrigger.rgbButtons[ nCntKey ] = ( ( _joyStatePress.rgbButtons[ nCntKey ] ^ joyState.rgbButtons[ nCntKey ] ) &
											   joyState.rgbButtons[ nCntKey ] );		// 押した瞬間のキー情報取得

			// キーリリースの作成
			_joyStateRelease.rgbButtons[ nCntKey ] = ( ( _joyStatePress.rgbButtons[ nCntKey ] ^ joyState.rgbButtons[ nCntKey ] ) &
												_joyStatePress.rgbButtons[ nCntKey ] );	// 放した瞬間のキー情報取得

			// キーリピートの作成
			_joyStateRepeat.rgbButtons[ nCntKey ] = _joyStatePress.rgbButtons[ nCntKey ];	// リーピートにプレスを格納

			// 1回押したあとも押しっぱなしのとき
			if( _joyStateRepeat.rgbButtons[ nCntKey ] != NULL )
			{
				// リピートの待機時間
				if( ( _repeatCount[ nCntKey ] > 0 ) && ( _repeatCount[ nCntKey ] < MAX_KEY_REPEAT ) )
				{
					_joyStateRepeat.rgbButtons[ nCntKey ] = NULL;				// キーリピートの中身をNULLにする
				}

				_repeatCount[ nCntKey ]++;										// キーリピート待機時間のインクリメント
			}
			else
			{
				_repeatCount[ nCntKey ] = 0;									// キーリピートの待機時間の初期化
			}
		}

		_leftTrigger = _rightTrigger = _upTrigger = _downTrigger = false;

		// 左トリガー
		if( ( _joyStatePress.lX < -8.0f ) && ( joyState.lX > -8.0f ) ) _leftTrigger = true;

		// 右トリガー
		if( ( _joyStatePress.lX > 8.0f ) && ( joyState.lX < 8.0f ) ) _rightTrigger = true;

		// 上トリガー
		if( ( _joyStatePress.lY < -10.0f ) && ( joyState.lY > -10.0f ) ) _upTrigger = true;

		// 右トリガー
		if( ( _joyStatePress.lY > 8.0f ) && ( joyState.lY < 8.0f ) ) _downTrigger = true;


		// キープレスの作成
		_joyStatePress = joyState;												// キーの押しっぱなしを格納
	}
	else
	{
		// キーボードへのアクセス権を取得
		m_pDIDevice->Acquire( );
	}

	return hr;
}

//==============================================================================
//	関数名	GetKeyboardPress
//	引数	int
//	戻り値	bool
//==============================================================================
bool CJoypad::GetPadPress( int key )
{
	return ( _joyStatePress.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	GetKeyboardTrigger
//	引数	int
//	戻り値	bool
//==============================================================================
bool CJoypad::GetPadTrigger( int key )
{
	return ( _joyStateTrigger.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	GetKeyboardRelease
//	引数	int
//	戻り値	bool
//==============================================================================
bool CJoypad::GetPadRelease( int key )
{
	return ( _joyStateRelease.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	GetKeyboardRepeat
//	引数	int
//	戻り値	bool
//==============================================================================
bool CJoypad::GetPadRepeat( int key )
{
	return ( _joyStateRepeat.rgbButtons[key] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	Create
//	引数	None
//	戻り値	CKeyboard
//==============================================================================
CJoypad *CJoypad::Create( void )
{
	CJoypad *pJoypad  = NULL;

	pJoypad = NEW CJoypad;														// インスタンスの生成

	return pJoypad;
}

//==============================================================================
//	関数名	EnumJoysticksCallback
//	引数	None
//	戻り値	None
//==============================================================================
BOOL CALLBACK CJoypad::EnumJoysticksCallback( const DIDEVICEINSTANCE *didInstance, void *context )
{
	HRESULT hr;

	//ジョイパッドポインタに変換
	CJoypad *pJoypad = ( CJoypad* )context;
	
	//デバイスの生成
	hr = m_pDInput->CreateDevice( didInstance->guidInstance, &pJoypad->m_pDIDevice, NULL );
	
	if ( FAILED( hr ) )
	{
		//作成出来ていないためもう一度
		return DIENUM_CONTINUE;
	}
	
	//作成完了
	return DIENUM_STOP;
}

//==============================================================================
//	関数名	EnumJoysticksCallback
//	引数	None
//	戻り値	None
//==============================================================================
BOOL CALLBACK CJoypad::EnumAxesCallback( const DIDEVICEOBJECTINSTANCE *didoi, void *context )
{
	HRESULT     hr;
	DIPROPRANGE diprg;
	
	//ジョイパッドポインタに変換
	CJoypad *pJoypad = ( CJoypad* )context;
	
	//ジョイパッドの能力の設定
	diprg.diph.dwSize       = sizeof( DIPROPRANGE );
	diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	diprg.diph.dwHow        = DIPH_BYID;
	diprg.diph.dwObj        = didoi->dwType;
	diprg.lMin              = 0 - 1000;					//十字ボタンの最小値
	diprg.lMax              = 0 + 1000;					//十字ボタンの最大値

	//デバイスに設定
	hr = pJoypad->m_pDIDevice->SetProperty( DIPROP_RANGE, &diprg.diph );
	
	if ( FAILED( hr ) )
	{
		return DIENUM_STOP;
	}
	
	return DIENUM_CONTINUE;
}

/* ----- EOF ----- */