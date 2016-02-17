//==============================================================================
//
// FineName [ keyboard.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "keyboard.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define MAX_KEY_REPEAT						( 40 )								// リピートの待ち時間

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------

//==============================================================================
//	関数名	CKeyboard
//	引数	None
//	戻り値	None
//==============================================================================
CKeyboard::CKeyboard()
{
}

//==============================================================================
//	関数名	~CKeyboard
//	引数	None
//	戻り値	None
//==============================================================================
CKeyboard::~CKeyboard()
{
}

//==============================================================================
//	関数名	Init
//	引数	HINSTANECE, HWND
//	戻り値	HRESULT
//==============================================================================
HRESULT CKeyboard::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr;																	// 格納ワーク

	CInput::Init( hInstance, hWnd );

	// 入力デバイスの生成
	hr = m_pDInput->CreateDevice( GUID_SysKeyboard, &m_pDIDevice, NULL );

	// 生成に失敗したとき
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "キーボードが見つかりません", "キーボード", MB_OK );

		return hr;																// HRESULTを返す
	}

	// データフォーマットの設定
	hr = m_pDIDevice->SetDataFormat( &c_dfDIKeyboard );

	// 設定に失敗したとき
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "データを設定できません", "データフォーマット", MB_OK );

		return hr;																// HRESULTを返す
	}

	// 協調モードの設定
	hr = m_pDIDevice->SetCooperativeLevel( hWnd, ( DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) );

	// 設定に失敗したとき
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "設定できません", "協調モード", MB_OK );

		return hr;																// HRESULTを返す
	}

	// キーボードへのアクセス権を取得(入力制御開始)
	hr =  m_pDIDevice->Acquire();

	// キー格納ワークの初期化
	for( int nCnt = 0; nCnt < MAX_KEY; nCnt++ )
	{
		m_aKeyStatePress[ nCnt ] = 0;											// キー押下ワーク
		m_aKeyStateTrigger[ nCnt ] = NULL;										// キーを押した瞬間のワーク
		m_aKeyStateRelease[ nCnt ] = NULL;										// キーを放した瞬間のワーク
		m_aKeyStateRepeat[ nCnt ] = NULL;										// キーを時間経過後に取得のワーク
		m_aKeyStateRepeatCount[ nCnt ] = NULL;									// キーリピート用カウント
	}

	return S_OK;																// S_OKを返す
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CKeyboard::Uninit( void )
{
	// キーボードの終了処理
	CInput::Uninit();
}

//==============================================================================
//	関数名	Update
//	引数	None
//	戻り値	None
//==============================================================================
HRESULT CKeyboard::Update( void )
{
	BYTE aKeyState[ MAX_KEY ];
	HRESULT hr = 0;

	// デバイスからキーボードの情報取得
	if( SUCCEEDED( m_pDIDevice->GetDeviceState( sizeof( aKeyState ), &aKeyState[ 0 ] ) ) )
	{
		/*-------------------
		|	MAX_KEY分ループ	|
		-------------------*/
		for( int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++ )
		{
			// キートリガーの作成
			m_aKeyStateTrigger[ nCntKey ] = ( ( m_aKeyStatePress[ nCntKey ] ^ aKeyState[ nCntKey ] ) &
											   aKeyState[ nCntKey ] );			// 押した瞬間のキー情報取得

			// キーリリースの作成
			m_aKeyStateRelease[ nCntKey ] = ( ( m_aKeyStatePress[ nCntKey ] ^ aKeyState[ nCntKey ] ) &
												m_aKeyStatePress[ nCntKey ] );	// 放した瞬間のキー情報取得

			// キーリピートの作成
			m_aKeyStateRepeat[ nCntKey ] = m_aKeyStatePress[ nCntKey ];			// リーピートにプレスを格納

			// 1回押したあとも押しっぱなしのとき
			if( m_aKeyStateRepeat[ nCntKey ] != NULL )
			{
				// リピートの待機時間
				if( ( m_aKeyStateRepeatCount[ nCntKey ] > 0 ) && ( m_aKeyStateRepeatCount[ nCntKey ] < MAX_KEY_REPEAT ) )
				{
					m_aKeyStateRepeat[ nCntKey ] = NULL;						// キーリピートの中身をNULLにする
				}

				m_aKeyStateRepeatCount[ nCntKey ]++;							// キーリピート待機時間のインクリメント
			}
			else
			{
				m_aKeyStateRepeatCount[ nCntKey ] = 0;							// キーリピートの待機時間の初期化
			}

			// キープレスの作成
			m_aKeyStatePress[ nCntKey ] = aKeyState[ nCntKey ];					// キーの押しっぱなしを格納
		}
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
bool CKeyboard::GetKeyboardPress( int nKey )
{
	return ( m_aKeyStatePress[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	GetKeyboardTrigger
//	引数	int
//	戻り値	bool
//==============================================================================
bool CKeyboard::GetKeyboardTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	GetKeyboardRelease
//	引数	int
//	戻り値	bool
//==============================================================================
bool CKeyboard::GetKeyboardRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	GetKeyboardRepeat
//	引数	int
//	戻り値	bool
//==============================================================================
bool CKeyboard::GetKeyboardRepeat( int nKey )
{
	return ( m_aKeyStateRepeat[ nKey ] & 0x0080 ) ? true : false;
}

//==============================================================================
//	関数名	Create
//	引数	None
//	戻り値	CKeyboard
//==============================================================================
CKeyboard *CKeyboard::Create( void )
{
	CKeyboard *pKeyboard = NULL;

	pKeyboard = NEW CKeyboard;													// インスタンスの生成

	return pKeyboard;
}

//==============================================================================
//	関数名	Release
//	引数	None
//	戻り値	None
//==============================================================================
void CKeyboard::Release( void )
{
	// キーボードの終了処理
	Uninit();

	// NULLでないとき
	if( this != NULL )
	{
		delete this;														// インスタンスの解放
	}
}

/* ----- EOF ----- */