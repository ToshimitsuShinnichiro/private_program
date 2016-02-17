//==============================================================================
//
// FineName [ texture.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "texture.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------

//==============================================================================
//	関数名	CTexture
//	引数	None
//	戻り値	None
//==============================================================================
CTexture::CTexture()
{
	CRenderer *pRenderer = CRenderer::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	Init();
}

//==============================================================================
//	関数名	~CTexture
//	引数	None
//	戻り値	None
//==============================================================================
CTexture::~CTexture()
{
}

//==============================================================================
//	関数名	Init
//	引数	None
//	戻り値	None
//==============================================================================
void CTexture::Init( void )
{
	// テクスチャの初期化
	for( int i = 0; i < TEXTURE_MAX; i++ )
	{
		_texture[i] = NULL;
	}
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CTexture::Uninit( void )
{
	// テクスチャの数分ループ
	for( int nCnt = 0; nCnt < TEXTURE_MAX; nCnt++ )
	{
		// NULLでないとき
		SafeRelease( _texture[nCnt] );
	}
}

//==============================================================================
//	関数名	GetTexture
//	引数	None
//	戻り値	LPDIRECT3DTXTURE9
//==============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture( TEXTURENAME name )
{
	// 指定されたテクスチャが生成されていないとき
	if( _texture[name] == NULL )
	{
		CRenderer *pRenderer = CRenderer::GetInstance();
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		// テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, &g_aTextureName[ name ][0], &_texture[ name ] );
	}
	
	return _texture[name];
}


/* ----- EOF ----- */