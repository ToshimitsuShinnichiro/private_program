//==============================================================================
//
// FineName [ light.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// クラス宣言
//------------------------------------------------------------------------------
class CLight
{
public:
	CLight();
	~CLight();

	void Init( D3DXVECTOR3 pos, D3DXVECTOR3 color, D3DXVECTOR3 ambient );
	void Uninit( void );

	static CLight* Create( D3DXVECTOR3 pos, D3DXVECTOR3 color, D3DXVECTOR3 ambient );

	// 座標関連
	void SetPos( D3DXVECTOR3 pos ) { _pos = pos; NormalizeVec(); }
	D3DXVECTOR3 GetPos( void ) { return _pos; }
	void AddPos( D3DXVECTOR3 pos ) { _pos += pos; NormalizeVec(); }

	// 色関連
	void SetColor( D3DXVECTOR3 color ) { _color = color; }
	void SetAmbient( D3DXVECTOR3 ambient ) { _ambient = ambient; }

	D3DXVECTOR3 GetVec( void ) { return _vec; }
	D3DXVECTOR3 GetColor( void ) { return _color; }
	D3DXVECTOR3 GetAmbient( void ) { return _ambient; }

private :
	D3DXVECTOR3 _pos;
	D3DXVECTOR3 _vec;															// 座標を正規化して使う
	D3DXVECTOR3 _color;
	D3DXVECTOR3 _ambient;

	void NormalizeVec( void ) { D3DXVec3Normalize( &_vec, &_pos ); }			// Vecの正規化
};

#endif

/* ----- EOF ----- */