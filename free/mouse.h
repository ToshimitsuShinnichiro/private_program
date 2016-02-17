//==============================================================================
//
// FineName [ mouse.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "input.h"
#include "vector3D.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// クラス宣言
//------------------------------------------------------------------------------
class CMouse :public CInput
{
public:
	CMouse();
	~CMouse();

	HRESULT Init( HINSTANCE hInstance, HWND hWnd );
	void Uninit( void );
	HRESULT Update( void );

	static CMouse *Create( void );
	void Release( void );

	bool GetLClick( void );
	bool GetRClick( void );
	bool GetCClick( void );
	float GetMoveX( void ){ return ( float )m_mouseInfo.lX; }
	float GetMoveY( void ){ return ( float )m_mouseInfo.lY; }
	float GetMoveZ( void ){ return ( float )m_mouseInfo.lZ; }
	VECTOR3D GetDiff( void );

private:
	DIMOUSESTATE2 m_mouseInfo;

	VECTOR3D oldPos;
};

#endif

/* ----- EOF ----- */