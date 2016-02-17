//==============================================================================
//
// FineName [ renderer.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "keyboard.h"
#include <stdio.h>

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------
float3 D3DXOutMatrix( float3 vec, D3DXMATRIX matrix )
{
	float4 v = float4( vec.x, vec.y, vec.z, 1.0f );

	// グローバル座標へ変換
	D3DXVec4Transform( &v, &v, &matrix );

	return float3( v.x, v.y, v.z );
}

//==============================================================================
//	関数名	CRenderer
//	引数	None
//	戻り値	None
//==============================================================================
CRenderer::CRenderer()
{
}

//==============================================================================
//	関数名	~CRenderer
//	引数	None
//	戻り値	None
//==============================================================================
CRenderer::~CRenderer()
{
}

//==============================================================================
//	関数名	Init
//	引数	HWND, BOOL
//	戻り値	HRESULT
//==============================================================================
HRESULT CRenderer::Init( HWND hWnd, BOOL bWindow )
{
	D3DPRESENT_PARAMETERS d3dpp;												//パラメーター
	D3DDISPLAYMODE d3ddm;														//ディスプレイモード

	//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	//Direct3Dオブジェクトの生成に失敗したとき
	if( m_pD3D == NULL )
	{
		return E_FAIL;															//E_FAILを返す
	}

	//現在のディスプレイモードを取得
	if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		return E_FAIL;															//E_FAILを返す
	}

	//パラメータの設定
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );										//中身のクリア
	d3dpp.BackBufferCount = 1;													//バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;										//幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;										//高さ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;									//フォーマット
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;									//スワップエフェクトタイプ
	d3dpp.Windowed = bWindow;													//ウィンドウの状態
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;								//D3Dフォーマト
	d3dpp.BackBufferFormat = d3ddm.Format;										//D3Dフォーマット
	
	//ウィンドウモードの判定
	if( bWindow == TRUE )
	{	//ウィンドウモード
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{	//フルスクリーンモード
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	//デバイス生成
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
									  D3DDEVTYPE_HAL,
									  hWnd,
									  D3DCREATE_HARDWARE_VERTEXPROCESSING,		//ハードウェアを使用
									  &d3dpp,
									  &m_pD3DDevice ) ) )
	{
		if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
									  D3DDEVTYPE_HAL,
									  hWnd,
									  D3DCREATE_SOFTWARE_VERTEXPROCESSING,		//ソフトウェアを使用
									  &d3dpp,
									  &m_pD3DDevice ) ) )
		{
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
									  D3DDEVTYPE_REF,
									  hWnd,
									  D3DCREATE_HARDWARE_VERTEXPROCESSING,		//ハードウェアを使用
									  &d3dpp,
									  &m_pD3DDevice ) ) )
			{
				return E_FAIL;													//E_FAILを返す
			}
		}
	}

	/*---------------------------------------
	|	レンダーステートパラメーターの設定	|
	---------------------------------------*/
	//カルの設定
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	//Zバッファの使用
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	//αの使用
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	//αの設定
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//αの設定
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// レンダーステートの設定
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	/*-------------------------------
	|	サンプラーステートの設定	|
	-------------------------------*/
	//画像の横方向繰り返し
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	//画像の縦方向繰り返し
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	//縮小時アンチエイリアシング
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP );
	//拡大時アンチエイリアシング
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTADDRESS_WRAP );

	/*----------------------------------------
	|	テクスチャステージステートの設定	 |
	----------------------------------------*/
	//ステージステートを掛け合わせる
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	//テクスチャのアルファを指定
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	//ポリゴンのアルファを指定
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	// マルチレンダリングの最大数の取得
	D3DCAPS9 Caps;
	m_pD3DDevice->GetDeviceCaps( &Caps );
	DWORD MaxRT = Caps.NumSimultaneousRTs;

	return S_OK;
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CRenderer::Uninit( void )
{
	//デバイスの解放
	SafeRelease( m_pD3DDevice );

	//Direct3Dオブジェクトの解放
	SafeRelease( m_pD3D );
}

//==============================================================================
//	関数名	Update
//	引数	None
//	戻り値	None
//==============================================================================
void CRenderer::Update( void )
{

}

//==============================================================================
//	関数名	GetDevice
//	引数	None
//	戻り値	LPDIRECT3DDEVICE9
//==============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice( void )
{
	return m_pD3DDevice;
}

//==============================================================================
//	関数名	GetInstance
//	引数	None
//	戻り値	CRenderer
//==============================================================================
CRenderer *CRenderer::GetInstance( void )
{
	static CRenderer Renderer;

	return &Renderer;
}

//==============================================================================
//	関数名	BeginRender
//	引数	None
//	戻り値	bool
//==============================================================================
bool CRenderer::BeginRender( void )
{
	//画面のクリア
	m_pD3DDevice->Clear( 0,
						 NULL, 
						 ( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL ), 
						 D3DCOLOR_RGBA( 255, 255, 0, 255 ), 
						 1.0f, 
						 0 );

	// TODO 各レンダー内でデバイスのクリアをするものをリスト化し、ここでクリアをかける？

	//描画開始
	if( SUCCEEDED( m_pD3DDevice->BeginScene( ) ) )
	{	
		// NULLでないとき
		/*if( pCamera != NULL )
		{
			pCamera->Draw();
		*/
	}
	else
	{
		return false;
	}
	
	return true;
}

//==============================================================================
//	関数名	EndRender
//	引数	None
//	戻り値	void
//==============================================================================
void CRenderer::EndRender( void )
{
	//描画終了
	m_pD3DDevice->EndScene( );

	//バックバッファとプライマリバッファの入れ替え
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );

}

/* ----- EOF ----- */