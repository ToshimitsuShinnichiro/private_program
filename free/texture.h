//==============================================================================
//
// FineName [ texture.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "singleton.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
typedef enum
{
	TEXTURE_WALL = 0,
	TEXTURE_TOSHI_GENDOU,
	TEXTURE_TOSHI_HENTAI,
	TEXTURE_BULLET,
	TEXTURE_EXPLOSION,
	TEXTURE_EARTH,
	TEXTURE_SHADOW,
	TEXTURE_NUMBER,
	TEXTURE_MOUNTAIN,
	TEXTURE_SKY,
	TEXTURE_PUSH,
	TEXTURE_PAUSE_TITLE,
	TEXTURE_PAUSE_RETRY,
	TEXTURE_PAUSE_BACK,
	TEXTURE_PAUSE_BG,
	TEXTURE_LOGO_BASE,
	TEXTURE_LOGO_IN,
	TEXTURE_RESULT,
	TEXTURE_RANKING,
	TEXTURE_TITLE,
	TEXTURE_CHOOT,
	TEXTURE_CHOOT2,
	TEXTURE_FIELD,
	TEXTURE_TREE,
	TEXTURE_METAL_BASIC,
	TEXTURE_METAL_POINT,
	TEXTURE_CUTO,
	TEXTURE_LIFE,
	TEXTURE_LIFEBAR,
	TEXTURE_SKY2,
	TEXTURE_WATER,
	TEXTURE_MONE,
	TEXTURE_SUN,
	TEXTURE_NORMALMAP,
	TEXTURE_NORMALBASE,
	TEXTURE_NORMALHEIGHT,
	TEXTURE_MAX,
} TEXTURENAME;

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------
const char g_aTextureName[][ MAX_PATH ] = 
{
	"data/TEXTURE/wall002.jpg",
	"data/TEXTURE/IMG_0825.JPG",
	"data/TEXTURE/IMG_0845.JPG",
	"data/TEXTURE/bullet000.png",
	"data/TEXTURE/explosion000.png",
	"data/TEXTURE/earth000.jpg",
	"data/TEXTURE/shadow000.jpg",
	"data/TEXTURE/number000.png",
	"data/TEXTURE/mountain000.png",
	"data/TEXTURE/sky001.jpg",
	"data/TEXTURE/start.png",
	"data/TEXTURE/pause_title.png",
	"data/TEXTURE/pause_retry.png",
	"data/TEXTURE/pause_back.png",
	"data/TEXTURE/pause.jpg",
	"data/TEXTURE/logo_base.png",
	"data/TEXTURE/logo_in.png",
	"data/TEXTURE/result_logo1.png",
	"data/TEXTURE/ranking.png",
	"data/TEXTURE/TitleLogo.png",
	"data/TEXTURE/method.png",
	"data/TEXTURE/chooto.png",
	"data/TEXTURE/field003.jpg",
	"data/TEXTURE/tree001.png",
	"data/TEXTURE/metal_basic.jpg",
	"data/TEXTURE/metal_point.jpg",
	"data/TEXTURE/chooto2.png",
	"data/TEXTURE/life.jpg",
	"data/TEXTURE/lifebar.png",
	"data/TEXTURE/sky000.jpg",
	"data/TEXTURE/field001.jpg",
	"data/TEXTURE/mone_tex.BMP",
	"data/TEXTURE/sun.png",
	"data/TEXTURE/Rock_Normal.bmp",
	"data/TEXTURE/Base.bmp",
	"data/TEXTURE/Rock_Displacement.bmp",
};

//------------------------------------------------------------------------------
// クラス宣言
//------------------------------------------------------------------------------
class CTexture : public CSingleton<CTexture>
{
public:
	void Init( void );
	void Uninit( void );

	LPDIRECT3DTEXTURE9 GetTexture( TEXTURENAME name );

private :
	friend class CSingleton<CTexture>;

	CTexture();
	~CTexture();

	LPDIRECT3DTEXTURE9 _texture[ TEXTURE_MAX ];					// テクスチャポインタ
};

#endif

/* ----- EOF ----- */