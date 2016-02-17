//==============================================================================
//
// FineName [ mouse.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "mouse.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------

//==============================================================================
//	関数名	CMouse
//	引数	None
//	戻り値	None
//==============================================================================
CMouse::CMouse()
{
}

//==============================================================================
//	関数名	~CMouse
//	引数	None
//	戻り値	None
//==============================================================================
CMouse::~CMouse()
{
}

//==============================================================================
//	関数名	Init
//	引数	HINSTANECE, HWND
//	戻り値	HRESULT
//==============================================================================
HRESULT CMouse::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr;																	// 格納ワーク

	CInput::Init( hInstance, hWnd );

	// 入力デバイスの生成
	hr = m_pDInput->CreateDevice( GUID_SysMouse, &m_pDIDevice, NULL );

	// 生成に失敗したとき
	if( FAILED( hr ) )
	{
		MessageBox( hWnd, "マウスが見つかりません", "マウス", MB_OK );

		return hr;																// HRESULTを返す
	}

	// データフォーマットの設定
	hr = m_pDIDevice->SetDataFormat( &c_dfDIMouse2 );

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

	// 軸モードを設定（相対値モードに設定）
    DIPROPDWORD diprop;
    diprop.diph.dwSize  = sizeof(diprop); 
    diprop.diph.dwHeaderSize    = sizeof(diprop.diph); 
    diprop.diph.dwObj   = 0;
    diprop.diph.dwHow   = DIPH_DEVICE;
    diprop.dwData       = DIPROPAXISMODE_REL;
    //diprop.dwData       = DIPROPAXISMODE_ABS; // 絶対値モードの場合
	hr = m_pDIDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	// 設定に失敗したとき
    if( FAILED( hr ) )
    {
		MessageBox( NULL,"軸モードの設定に失敗","Direct Input Error",MB_OK );

        return hr;
    }

	// キーボードへのアクセス権を取得(入力制御開始)
	hr =  m_pDIDevice->Acquire();

	m_mouseInfo.lX = 0;
	m_mouseInfo.lY = 0;
	m_mouseInfo.lZ = 0;

	oldPos = VECTOR3D( 0.0f, 0.0f, 0.0f );

	for( int nCnt = 0; nCnt < 8; nCnt++ )
	{
		m_mouseInfo.rgbButtons[ nCnt ] = 0;
	}

	return S_OK;																// S_OKを返す
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CMouse::Uninit( void )
{
	// キーボードの終了処理
	CInput::Uninit();
}

//==============================================================================
//	関数名	Update
//	引数	None
//	戻り値	None
//==============================================================================
HRESULT CMouse::Update( void )
{
	HRESULT hr = 0;

	// デバイスからマウスの情報取得
	if( SUCCEEDED( m_pDIDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), &m_mouseInfo ) ) )
	{
		// 以前の座標を格納
		oldPos = VECTOR3D( ( float )m_mouseInfo.lX, ( float )m_mouseInfo.lY, ( float )m_mouseInfo.lZ );
	}
	else
	{
		// マウスへのアクセス権を取得
		m_pDIDevice->Acquire( );
	}

	return hr;
}

//==============================================================================
//	関数名	GetLClick
//	引数	None
//	戻り値	bool
//==============================================================================
bool CMouse::GetLClick( void )
{
	return ( m_mouseInfo.rgbButtons[ 0 ] & 0x0001 )? true : false;
}

//==============================================================================
//	関数名	GetRClick
//	引数	None
//	戻り値	bool
//==============================================================================
bool CMouse::GetRClick( void )
{
	return ( m_mouseInfo.rgbButtons[ 1 ] & 0x0001 )? true : false;
}

//==============================================================================
//	関数名	GetCClick
//	引数	None
//	戻り値	bool
//==============================================================================
bool CMouse::GetCClick( void )
{
	return ( m_mouseInfo.rgbButtons[ 2 ] & 0x0001 )? true : false;
}

//==============================================================================
//	関数名	GetDiff
//	引数	None
//	戻り値	VECTOR3D
//==============================================================================
VECTOR3D CMouse::GetDiff( void )
{
	float x, y, z;																// 座標格納ワーク

	// 差分の計算
	x = ( float )m_mouseInfo.lX - oldPos.x;
	y = ( float )m_mouseInfo.lY - oldPos.y;
	z = ( float )m_mouseInfo.lZ - oldPos.z;

	return VECTOR3D( x, y, z );
}

//==============================================================================
//	関数名	Create
//	引数	None
//	戻り値	CMouse
//==============================================================================
CMouse *CMouse::Create( void )
{
	CMouse *pMouse;

	pMouse = NEW CMouse;														 // インスタンスの生成

	return pMouse;
}

//==============================================================================
//	関数名	Release
//	引数	None
//	戻り値	None
//==============================================================================
void CMouse::Release( void )
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