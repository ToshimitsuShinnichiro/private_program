//==============================================================================
//
// FineName [ input.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "input.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------
LPDIRECTINPUT8 CInput::m_pDInput = NULL;

//==============================================================================
//	関数名	CInput
//	引数	None
//	戻り値	None
//==============================================================================
CInput::CInput()
{
	m_pDIDevice =NULL;
}

//==============================================================================
//	関数名	~CInput
//	引数	None
//	戻り値	None
//==============================================================================
CInput::~CInput()
{
}

//==============================================================================
//	関数名	Init
//	引数	HINSTANECE, HWND
//	戻り値	HRESULT
//==============================================================================
HRESULT CInput::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT hr = NULL;

	// DirectInputオブジェクトの生成
	if( m_pDInput == NULL )
	{
		hr = DirectInput8Create( hInstance, 
								 DIRECTINPUT_VERSION, 
								 IID_IDirectInput8, 
								 ( void** )&m_pDInput,
								 NULL );
	}

	return hr;																	// HRESULTを返す
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CInput::Uninit( void )
{
	// デバイスの解放
	if( m_pDIDevice != NULL )
	{
		m_pDIDevice->Unacquire( );												// キーボードへのアクセス権を解放
		m_pDIDevice->Release( );												// キーボードの解放
		m_pDIDevice = NULL;														// NULLを代入
	}

	// DirectInputオブジェクトの解放
	if( m_pDInput != NULL )
	{
		m_pDInput->Release( );													// DirectInputオブジェクトの解放
		m_pDInput = NULL;														// NULLを代入
	}
}

//==============================================================================
//	関数名	Update
//	引数	None
//	戻り値	HRESULT
//==============================================================================
HRESULT CInput::Update( void )
{
	HRESULT hr = 0;

	return hr;
}

/* ----- EOF ----- */