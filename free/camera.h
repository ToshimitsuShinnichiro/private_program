//==============================================================================
//
// FineName [ camera.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �N���X�錾
//------------------------------------------------------------------------------
class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init( void );
	void Uninit( void );
	void Update( void );
	void Draw( void );
	void Release( void );
	static CCamera *Create( void );
	static CCamera *Create( D3DXVECTOR3 CameraEye, D3DXVECTOR3 CameraView, D3DXVECTOR3 CameraVec  );

	void SetCameraPos( D3DXVECTOR3 pos );
	void SetCameraNextRot( D3DXVECTOR3 rot );

	void PosRot( float rot );

	D3DXVECTOR3 *GetRotCamera( void );
	D3DXMATRIX GetCameraView( void );
	D3DXMATRIX GetBaseCameraView( void );
	D3DXMATRIX GetCameraProj( void );
	D3DXVECTOR3 *GetLookatCamera( void );
	D3DXVECTOR3 GetcameraPos( void ){ return m_posCameraP; }

	CCamera *GetCamera( void ){ return this; }

	D3DXMATRIX GetOrthoProj( void ){ return OrthoProj; }
	D3DXMATRIX GetOrthoView( void ){ return OrthoView; }

private:
	void ViewBaseRot( float rot );
	void MoveCameraAndView( void );
	void Rot( void );

	D3DXVECTOR3 m_posCameraP;													// �J�����̎��_
	D3DXVECTOR3 m_posCameraR;													// �J�����̒����_
	D3DXVECTOR3 m_vecCameraU;													// �J�����̏����

	D3DXMATRIX OrthoProj;
	D3DXMATRIX OrthoView;

	D3DXVECTOR3 m_rotCamera;													// �J�����̊p�x
	D3DXVECTOR3 m_nextCameraRot;												// �J�����̎��̊p�x
	float m_fLenght;															// �J�����̒����_����̔��a
	float m_fPosX;																// �J�����̂w���W
	float m_fPosY;																// �J�����̂x���W
	float m_fPosZ;																// �J�����̂y���W
	float m_fViewPosX;															// �����_�̂w���W
	float m_fNear;																// �O���N���b�s���O��
	float m_fFar;																// ����N���b�s���O��
	bool _doRot;																// �J�����̉�]�t���O

	// �}�g���b�N�X�֘A
	D3DXMATRIX m_mtxView;														// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxBaseView;													// �����r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;													// �v���W�F�N�V�����}�g���b�N�X
};

#endif

/* ----- EOF ----- */