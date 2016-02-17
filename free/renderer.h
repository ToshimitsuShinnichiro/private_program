//==============================================================================
//
// FineName [ texture.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#define DIRECTINPUT_VERSION			( 0x0800 )												//インプット警告防止

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "d3dx9.h"
#include "dinput.h"
//#include "dmusici.h"

//------------------------------------------------------------------------------
//　ライブラリのリンク
//------------------------------------------------------------------------------
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "winmm.lib" )

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define FVF_VERTEX_3D			( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	// 頂点フォーマット
#define FVF_VERTEX_2D			( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )// 頂点フォーマット
#define float2					D3DXVECTOR2
#define float3					D3DXVECTOR3
#define float4					D3DXVECTOR4
#define COLOR					D3DXCOLOR

typedef struct
{
	float3	vtx;																//頂点座標
	float3 nor;																	//テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;															//反射光
	float2 tex;																	//テクスチャ座標
}VERTEX_3D;

typedef struct
{
	float3	vtx;																// 頂点座標
	float rhw;																	// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;															// 反射光
	float2 tex;																	// テクスチャ座標
}VERTEX_2D;

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
float3 D3DXOutMatrix( float3 vec, D3DXMATRIX matrix );

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// クラス宣言
//------------------------------------------------------------------------------
class CRenderer
{
public:
	HRESULT Init( HWND hWnd, BOOL bWindow );
	void Uninit( void );
	void Update( void );
	LPDIRECT3DDEVICE9 GetDevice( void );
	LPD3DXFONT GetFont( void );

	static CRenderer *GetInstance( void );

	bool BeginRender( void );
	void EndRender( void );

private:
	LPDIRECT3D9 m_pD3D;															//Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;												//デバイスオブジェクト

	CRenderer();
	CRenderer( const CRenderer &renderer );
	~CRenderer();
};

#endif

/* ----- EOF ----- */