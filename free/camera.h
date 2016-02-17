//==============================================================================
//
// FineName [ camera.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// クラス宣言
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

	D3DXVECTOR3 m_posCameraP;													// カメラの視点
	D3DXVECTOR3 m_posCameraR;													// カメラの注視点
	D3DXVECTOR3 m_vecCameraU;													// カメラの上方向

	D3DXMATRIX OrthoProj;
	D3DXMATRIX OrthoView;

	D3DXVECTOR3 m_rotCamera;													// カメラの角度
	D3DXVECTOR3 m_nextCameraRot;												// カメラの次の角度
	float m_fLenght;															// カメラの注視点からの半径
	float m_fPosX;																// カメラのＸ座標
	float m_fPosY;																// カメラのＹ座標
	float m_fPosZ;																// カメラのＺ座標
	float m_fViewPosX;															// 注視点のＸ座標
	float m_fNear;																// 前方クリッピング面
	float m_fFar;																// 後方クリッピング面
	bool _doRot;																// カメラの回転フラグ

	// マトリックス関連
	D3DXMATRIX m_mtxView;														// ビューマトリックス
	D3DXMATRIX m_mtxBaseView;													// 初期ビューマトリックス
	D3DXMATRIX m_mtxProjection;													// プロジェクションマトリックス
};

#endif

/* ----- EOF ----- */