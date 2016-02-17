/********************************************************************************************
*
*	FileContent	内積外積処理
*	FileName	product.cpp
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/

//----------------------------------------------
//	インクルード
//----------------------------------------------
#include "product.h"

/****************************************************
*	関数名　DotProduct
*	引数	D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3
*	戻り値	float
*	内容	内積計算による角度の取得(右手座標系)
****************************************************/
float DotProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B )
{
	D3DXVECTOR3 Base, View;																	// ベクトル
	D3DXVECTOR3 Vector;																		// ベクトル格納ワーク
	float fX, fY, fZ;																		// 座標格納ワーク
	float fWork;																			// ワーク
	float fVector, fVectorA, fVectorB;														// ベクトル
	float fAngle;																			// 角度

	// 座標が一緒でないとき
	if( A != B )
	{
		// ベクトルの作成
		Base = D3DXVECTOR3( ( B.x - A.x ), ( B.y - A.y ), ( B.z - A.z ) );					// Baseの座標
		View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );			// viewの座標

		// ベクトルの大きさ
		fWork = ( Base.x * Base.x ) + ( Base.y * Base.y ) + ( Base.z * Base.z );
		fVectorA = sqrt( fWork );															// エネミーのベクトルの大きさ

		fWork = ( View.x * View.x ) + ( View.y * View.y ) + ( View.z * View.z );
		fVectorB = sqrt( fWork );															// プレイヤーべクトルの大きさ

		// 内積計算
		fX = View.x * Base.x;																// 内積Ｘ
		fY = View.y * Base.y;																// 内積Ｙ
		fZ = View.z * Base.z;																// 内積Ｚ
		fVector = fX + fY + fZ;																// 内積

		// cosの値計算
		fAngle = fVector / ( fVectorA * fVectorB );											// 内積計算
		fAngle = acosf( fAngle );															// 角度の計算

		return fAngle;																		// 角度を返す
	}

	return 0;
}

/****************************************************
*	関数名　CrossProduct
*	引数	D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3
*	戻り値	BOOL
*	内容	外積の結果を返す
****************************************************/
bool CrossProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B )
{
	D3DXVECTOR3 Base, View;																	// ベクトル
	D3DXVECTOR3 Vector;																		// ベクトル格納ワーク
	float fX, fY, fZ;																		// 座標格納ワーク

	// 座標が一緒でないとき
	if( A != B )
	{
		// ベクトルの作成
		Base = D3DXVECTOR3( ( B.x - A.x ), ( B.y - A.y ), ( B.z - A.z ) );					// Baseの座標
		View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );			// viewの座標

		// 外積計算
		fX = Base.y * View.z - Base.z * View.y;												// 外積Ｘ
		fY = Base.z * View.x - Base.x * View.z;												// 外積Ｙ
		fZ = Base.x * View.y - Base.y * View.x;												// 外積Ｚ

		// ベクトルの格納
		Vector = D3DXVECTOR3( fX, fY, fZ );

		// 外積が上向きのとき
		if( Vector.y >= 0 )
		{
			return true;
		}
		//外積が下向きのとき
		else if( Vector.y < 0 )
		{
			return false;
		}
	}
	return true;
}

/****************************************************
*	関数名　DotProductVector
*	引数	D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3
*	戻り値	float
*	内容	内積計算による角度の取得(右手座標系)
****************************************************/
float DotProductVector( D3DXVECTOR3 ARot, float BRot )
{
	D3DXVECTOR3 Base, View;																	// ベクトル
	D3DXVECTOR3 Vector;																		// ベクトル格納ワーク
	float fX, fY, fZ;																		// 座標格納ワーク
	float fWork;																			// ワーク
	float fVector, fVectorA, fVectorB;														// ベクトル
	float fAngle;																			// 角度

	// ベクトルの作成
	Base = D3DXVECTOR3( 1.0f * sinf( BRot ), 0.0f, 1.0f * cosf( BRot ) );					// Baseの座標
	View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );				// viewの座標

	// ベクトルの大きさ
	fWork = ( Base.x * Base.x ) + ( Base.y * Base.y ) + ( Base.z * Base.z );
	fVectorA = sqrt( fWork );																// エネミーのベクトルの大きさ

	fWork = ( View.x * View.x ) + ( View.y * View.y ) + ( View.z * View.z );
	fVectorB = sqrt( fWork );																// プレイヤーべクトルの大きさ

	// 内積計算
	fX = View.x * Base.x;																	// 内積Ｘ
	fY = View.y * Base.y;																	// 内積Ｙ
	fZ = View.z * Base.z;																	// 内積Ｚ
	fVector = fX + fY + fZ;																	// 内積

	// cosの値計算
	fAngle = fVector / ( fVectorA * fVectorB );												// 内積計算
	fAngle = acosf( fAngle );																// 角度の計算

	return fAngle;																			// 角度を返す

	return 0;
}

/****************************************************
*	関数名　CrossProductVector
*	引数	D3DXVECTOR3, D3DXVECTOR3
*	戻り値	BOOL
*	内容	外積の結果を返す
****************************************************/
bool CrossProductVector( D3DXVECTOR3 ARot,float BRot )
{
	D3DXVECTOR3 Base, View;																	// ベクトル
	D3DXVECTOR3 Vector;																		// ベクトル格納ワーク
	float fX, fY, fZ;																		// 座標格納ワーク

	// ベクトルの作成
	Base = D3DXVECTOR3( 1.0f * sinf( BRot ), 0.0f, 1.0f * cosf( BRot ) );					// Baseの座標
	View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );				// viewの座標

	// 外積計算
	fX = Base.y * View.z - Base.z * View.y;													// 外積Ｘ
	fY = Base.z * View.x - Base.x * View.z;													// 外積Ｙ
	fZ = Base.x * View.y - Base.y * View.x;													// 外積Ｚ

	// ベクトルの格納
	Vector = D3DXVECTOR3( fX, fY, fZ );

	// 外積が上向きのとき
	if( Vector.y >= 0 )
	{
		return true;
	}
	//外積が下向きのとき
	else if( Vector.y < 0 )
	{
		return false;
	}

	return true;
}

void CrossProduct( D3DXVECTOR3 *out, D3DXVECTOR3 A, D3DXVECTOR3 B )
{
	// ベクトルの大きさを算出
	float lengthA, lengthB, length;

	lengthA = sqrt( A.x * A.x + A.y * A.y + A.z * A.z );
	lengthB = sqrt( B.x * B.x + B.y * B.y + B.z * B.z );
	length = lengthA * lengthB;

	out->x = ( ( A.y * B.z ) - ( A.z * B.y ) ) / length;
	out->y = ( ( A.z * B.x ) - ( A.x * B.z ) ) / length;
	out->z = ( ( A.x * B.y ) - ( A.y * B.x ) ) / length;
}

/* ----- EOF ----- */