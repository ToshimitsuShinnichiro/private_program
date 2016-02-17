/********************************************************************************************
*
*	FileContent	���ϊO�Ϗ���
*	FileName	product.cpp
*	Writer		Toshimitsu Shinnichirou		
*	Number		10041
*
********************************************************************************************/

//----------------------------------------------
//	�C���N���[�h
//----------------------------------------------
#include "product.h"

/****************************************************
*	�֐����@DotProduct
*	����	D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3
*	�߂�l	float
*	���e	���όv�Z�ɂ��p�x�̎擾(�E����W�n)
****************************************************/
float DotProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B )
{
	D3DXVECTOR3 Base, View;																	// �x�N�g��
	D3DXVECTOR3 Vector;																		// �x�N�g���i�[���[�N
	float fX, fY, fZ;																		// ���W�i�[���[�N
	float fWork;																			// ���[�N
	float fVector, fVectorA, fVectorB;														// �x�N�g��
	float fAngle;																			// �p�x

	// ���W���ꏏ�łȂ��Ƃ�
	if( A != B )
	{
		// �x�N�g���̍쐬
		Base = D3DXVECTOR3( ( B.x - A.x ), ( B.y - A.y ), ( B.z - A.z ) );					// Base�̍��W
		View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );			// view�̍��W

		// �x�N�g���̑傫��
		fWork = ( Base.x * Base.x ) + ( Base.y * Base.y ) + ( Base.z * Base.z );
		fVectorA = sqrt( fWork );															// �G�l�~�[�̃x�N�g���̑傫��

		fWork = ( View.x * View.x ) + ( View.y * View.y ) + ( View.z * View.z );
		fVectorB = sqrt( fWork );															// �v���C���[�׃N�g���̑傫��

		// ���όv�Z
		fX = View.x * Base.x;																// ���ςw
		fY = View.y * Base.y;																// ���ςx
		fZ = View.z * Base.z;																// ���ςy
		fVector = fX + fY + fZ;																// ����

		// cos�̒l�v�Z
		fAngle = fVector / ( fVectorA * fVectorB );											// ���όv�Z
		fAngle = acosf( fAngle );															// �p�x�̌v�Z

		return fAngle;																		// �p�x��Ԃ�
	}

	return 0;
}

/****************************************************
*	�֐����@CrossProduct
*	����	D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3
*	�߂�l	BOOL
*	���e	�O�ς̌��ʂ�Ԃ�
****************************************************/
bool CrossProduct( D3DXVECTOR3 A, D3DXVECTOR3 ARot, D3DXVECTOR3 B )
{
	D3DXVECTOR3 Base, View;																	// �x�N�g��
	D3DXVECTOR3 Vector;																		// �x�N�g���i�[���[�N
	float fX, fY, fZ;																		// ���W�i�[���[�N

	// ���W���ꏏ�łȂ��Ƃ�
	if( A != B )
	{
		// �x�N�g���̍쐬
		Base = D3DXVECTOR3( ( B.x - A.x ), ( B.y - A.y ), ( B.z - A.z ) );					// Base�̍��W
		View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );			// view�̍��W

		// �O�όv�Z
		fX = Base.y * View.z - Base.z * View.y;												// �O�ςw
		fY = Base.z * View.x - Base.x * View.z;												// �O�ςx
		fZ = Base.x * View.y - Base.y * View.x;												// �O�ςy

		// �x�N�g���̊i�[
		Vector = D3DXVECTOR3( fX, fY, fZ );

		// �O�ς�������̂Ƃ�
		if( Vector.y >= 0 )
		{
			return true;
		}
		//�O�ς��������̂Ƃ�
		else if( Vector.y < 0 )
		{
			return false;
		}
	}
	return true;
}

/****************************************************
*	�֐����@DotProductVector
*	����	D3DXVECTOR3, D3DXVECTOR3, D3DXVECTOR3
*	�߂�l	float
*	���e	���όv�Z�ɂ��p�x�̎擾(�E����W�n)
****************************************************/
float DotProductVector( D3DXVECTOR3 ARot, float BRot )
{
	D3DXVECTOR3 Base, View;																	// �x�N�g��
	D3DXVECTOR3 Vector;																		// �x�N�g���i�[���[�N
	float fX, fY, fZ;																		// ���W�i�[���[�N
	float fWork;																			// ���[�N
	float fVector, fVectorA, fVectorB;														// �x�N�g��
	float fAngle;																			// �p�x

	// �x�N�g���̍쐬
	Base = D3DXVECTOR3( 1.0f * sinf( BRot ), 0.0f, 1.0f * cosf( BRot ) );					// Base�̍��W
	View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );				// view�̍��W

	// �x�N�g���̑傫��
	fWork = ( Base.x * Base.x ) + ( Base.y * Base.y ) + ( Base.z * Base.z );
	fVectorA = sqrt( fWork );																// �G�l�~�[�̃x�N�g���̑傫��

	fWork = ( View.x * View.x ) + ( View.y * View.y ) + ( View.z * View.z );
	fVectorB = sqrt( fWork );																// �v���C���[�׃N�g���̑傫��

	// ���όv�Z
	fX = View.x * Base.x;																	// ���ςw
	fY = View.y * Base.y;																	// ���ςx
	fZ = View.z * Base.z;																	// ���ςy
	fVector = fX + fY + fZ;																	// ����

	// cos�̒l�v�Z
	fAngle = fVector / ( fVectorA * fVectorB );												// ���όv�Z
	fAngle = acosf( fAngle );																// �p�x�̌v�Z

	return fAngle;																			// �p�x��Ԃ�

	return 0;
}

/****************************************************
*	�֐����@CrossProductVector
*	����	D3DXVECTOR3, D3DXVECTOR3
*	�߂�l	BOOL
*	���e	�O�ς̌��ʂ�Ԃ�
****************************************************/
bool CrossProductVector( D3DXVECTOR3 ARot,float BRot )
{
	D3DXVECTOR3 Base, View;																	// �x�N�g��
	D3DXVECTOR3 Vector;																		// �x�N�g���i�[���[�N
	float fX, fY, fZ;																		// ���W�i�[���[�N

	// �x�N�g���̍쐬
	Base = D3DXVECTOR3( 1.0f * sinf( BRot ), 0.0f, 1.0f * cosf( BRot ) );					// Base�̍��W
	View = D3DXVECTOR3( 1.0f * sinf( ARot.y ), 0.0f, 1.0f * cosf( ARot.y ) );				// view�̍��W

	// �O�όv�Z
	fX = Base.y * View.z - Base.z * View.y;													// �O�ςw
	fY = Base.z * View.x - Base.x * View.z;													// �O�ςx
	fZ = Base.x * View.y - Base.y * View.x;													// �O�ςy

	// �x�N�g���̊i�[
	Vector = D3DXVECTOR3( fX, fY, fZ );

	// �O�ς�������̂Ƃ�
	if( Vector.y >= 0 )
	{
		return true;
	}
	//�O�ς��������̂Ƃ�
	else if( Vector.y < 0 )
	{
		return false;
	}

	return true;
}

void CrossProduct( D3DXVECTOR3 *out, D3DXVECTOR3 A, D3DXVECTOR3 B )
{
	// �x�N�g���̑傫�����Z�o
	float lengthA, lengthB, length;

	lengthA = sqrt( A.x * A.x + A.y * A.y + A.z * A.z );
	lengthB = sqrt( B.x * B.x + B.y * B.y + B.z * B.z );
	length = lengthA * lengthB;

	out->x = ( ( A.y * B.z ) - ( A.z * B.y ) ) / length;
	out->y = ( ( A.z * B.x ) - ( A.x * B.z ) ) / length;
	out->z = ( ( A.x * B.y ) - ( A.y * B.x ) ) / length;
}

/* ----- EOF ----- */