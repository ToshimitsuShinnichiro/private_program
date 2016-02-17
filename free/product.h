/********************************************************************************************
*
*	FileContent	���ϊO�Ϗ���
*	FileName	product.h
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/
#ifndef _PRODUCT_H_
#define _PRODUCT_H_

//-----------------------------------------
//	�C���N���[�h
//-----------------------------------------
#include "main.h"
#include "renderer.h"
#include <math.h>

//-----------------------------------------
//	�v���g�^�C�v�錾
//-----------------------------------------
float DotProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B );
bool CrossProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B );
float DotProductVector( D3DXVECTOR3 ARot, float BRot );
bool CrossProductVector( D3DXVECTOR3 ARot, float BRot );
void CrossProduct( D3DXVECTOR3 *out, D3DXVECTOR3 A, D3DXVECTOR3 B );

#endif