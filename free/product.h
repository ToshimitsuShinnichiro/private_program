/********************************************************************************************
*
*	FileContent	内積外積処理
*	FileName	product.h
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/
#ifndef _PRODUCT_H_
#define _PRODUCT_H_

//-----------------------------------------
//	インクルード
//-----------------------------------------
#include "main.h"
#include "renderer.h"
#include <math.h>

//-----------------------------------------
//	プロトタイプ宣言
//-----------------------------------------
float DotProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B );
bool CrossProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B );
float DotProductVector( D3DXVECTOR3 ARot, float BRot );
bool CrossProductVector( D3DXVECTOR3 ARot, float BRot );
void CrossProduct( D3DXVECTOR3 *out, D3DXVECTOR3 A, D3DXVECTOR3 B );

#endif