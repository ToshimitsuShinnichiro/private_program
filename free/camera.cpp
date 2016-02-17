//==============================================================================
//
// FineName [ camera.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "camera.h"
#include "renderer.h"
#include "keyboard.h"
#include "product.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define VIEW_ANGLE							( 3.14f / 180.0f * 45.0f )				// 視野角
#define CAMERA_BASE_POSX					( 0.0f )							// カメラの基本Ｘ座標
#define CAMERA_BASE_POSY					( 380.0f )							// カメラの基本Ｙ座標
#define CAMERA_BASE_POSZ					( -830.0f )							// カメラの基本Ｚ座標
#define ADD_POS								( 5.0f )							// 座標の増加量
#define ADD_CAMERA_ANGLE					( D3DX_PI / 180 * 3 )				// カメラアングルの増加量
#define CAMERA_MAX							( D3DX_PI / 180 * 180 )				// カメラの最大角度
#define CAMERA_SLIDE						( D3DX_PI / 180 * 90 )				// カメラの補正
#define SLIDE_POS							( 15.0f )							// 座標をずらす
#define CAMERA_NEAR							( 1 )								// 前方クリッピング面
#define CAMERA_FAR							( 15000 )							// 後方クリッピング面

//------------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------------

//==============================================================================
//	関数名	CCamera
//	引数	None
//	戻り値	None
//==============================================================================
CCamera::CCamera()
{
	// ビュー・プロジェクションの作成
	D3DXMatrixOrthoLH( &OrthoProj, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 1000 );
	D3DXMatrixLookAtLH( &OrthoView, &float3( 0.0f, 0.0f, -1.0f ), &float3( 0.0f, 0.0f, 0.0f ), &float3( 0.0f, 1.0f, 0.0f ) );
}

//==============================================================================
//	関数名	~CCamera
//	引数	None
//	戻り値	None
//==============================================================================
CCamera::~CCamera()
{
}

//==============================================================================
//	関数名	Init
//	引数	None
//	戻り値	None
//==============================================================================
void CCamera::Init( void )
{
	m_nextCameraRot = m_rotCamera;
	m_nextCameraRot.y = 0.0f;

	_doRot = false;

	// ビューマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxBaseView );

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH( &m_mtxBaseView, &m_posCameraP, &m_posCameraR, &m_vecCameraU );
}

//==============================================================================
//	関数名	Uninit
//	引数	None
//	戻り値	None
//==============================================================================
void CCamera::Uninit( void )
{
	CCamera *pCamera = GetCamera();

	// NULLでないとき
	if( pCamera != NULL )
	{
		pCamera = NULL;
	}
}

//==============================================================================
//	関数名	Update
//	引数	None
//	戻り値	None
//==============================================================================
void CCamera::Update( void )
{
	// 注視点を中心に回転
	//this->ViewBaseRot( RADIAN( 2.0f ) );

	// 角度を合わせる
	//Rot();
}

//==============================================================================
//	関数名	Draw
//	引数	None
//	戻り値	None
//==============================================================================
void CCamera::Draw( void )
{
	CRenderer *pRenderer = CRenderer::GetInstance();							// インスタンスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();							// デバイスの取得

	/*---------------------------
	|	ビューマトリックス生成	|
	---------------------------*/
	// ビューマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxView );

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH( &m_mtxView, &m_posCameraP, &m_posCameraR, &m_vecCameraU );

	// ビューマトリックスの設定
	pDevice->SetTransform( D3DTS_VIEW, &m_mtxView );

	/*-----------------------------------
	|	プロジェクトマトリックスの生成	|
	-----------------------------------*/
	// プロジェクトマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxProjection );

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH( &m_mtxProjection, VIEW_ANGLE, ( SCREEN_WIDTH / SCREEN_HEIGHT ), m_fNear, m_fFar );

	// プロジェクションマトリックスの設定
	pDevice->SetTransform( D3DTS_PROJECTION, &m_mtxProjection );
}

//==============================================================================
//	関数名	Release
//	引数	None
//	戻り値	None
//==============================================================================
void CCamera::Release( void )
{
	CCamera *pCamera = GetCamera();

	// 後始末
	pCamera->Uninit();

	delete pCamera;

	pCamera = NULL;
}

//==============================================================================
//	関数名	Create
//	引数	None
//	戻り値	None
//==============================================================================
CCamera *CCamera::Create( void )
{
	CCamera *pCamera = NEW CCamera;

	float fLengthX = 0;																// Ｘ座標の長さ
	float fLengthY = 0;																// Ｙ座標の長さ
	float fLengthZ = 0;																// Ｚ座標の長さ
	float fRotY = 0;																	// Ｙ角度
	float fRotZ = 0;																	// Ｚ角度

	// カメラ座標の設定
	pCamera->m_fPosX = CAMERA_BASE_POSX;													// カメラのＸ座標
	pCamera->m_fPosY = CAMERA_BASE_POSY;													// カメラのＹ座標
	pCamera->m_fPosZ = CAMERA_BASE_POSZ;													// カメラのＺ座標

	pCamera->m_posCameraP = D3DXVECTOR3( pCamera->m_fPosX, pCamera->m_fPosY, pCamera->m_fPosZ );// カメラ位置
	pCamera->m_posCameraR = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );								// カメラの注視点
	pCamera->m_vecCameraU = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );								// カメラの上方向
	
	fLengthX = pCamera->m_posCameraR.x - pCamera->m_posCameraP.x;							// Ｘ座標の長さ
	fLengthY = pCamera->m_posCameraR.y - pCamera->m_posCameraP.y;							// Ｙ座標の長さ
	fLengthZ = pCamera->m_posCameraR.z - pCamera->m_posCameraP.z;							// Ｚ座標の長さ

	fRotY = 0.0f;																			// カメラの角度Y
	fRotZ = atan2f( fLengthZ, fLengthY );													// カメラの角度Z

	pCamera->m_rotCamera = D3DXVECTOR3( 0.0f, fRotY, fRotZ );								// カメラの角度

	fLengthX *= fLengthX;																	// Ｘ座標の長さの２乗
	fLengthY *= fLengthY;																	// Ｙ座標の長さの２乗
	fLengthZ *= fLengthZ;																	// Ｚ座標の長さの２乗

	pCamera->m_fLenght = sqrtf( fLengthZ + fLengthX );										// カメラの注視点からの半径

	pCamera->m_fNear = CAMERA_NEAR;															// 前方クリッピング面
	pCamera->m_fFar = CAMERA_FAR;															// 後方クリッピング面

	// 初期化
	pCamera->Init();

	return pCamera;
}

//==============================================================================
//	関数名	Create
//	引数	None
//	戻り値	None
//==============================================================================
CCamera *CCamera::Create( D3DXVECTOR3 CameraEye, D3DXVECTOR3 CameraView, D3DXVECTOR3 CameraVec )
{
	CCamera *pCamera = NEW CCamera;

	float fLengthX = 0;																// Ｘ座標の長さ
	float fLengthY = 0;																// Ｙ座標の長さ
	float fLengthZ = 0;																// Ｚ座標の長さ

	// カメラ座標の設定
	pCamera->m_fPosX = CAMERA_BASE_POSX;													// カメラのＸ座標
	pCamera->m_fPosY = CAMERA_BASE_POSY;													// カメラのＹ座標
	pCamera->m_fPosZ = CAMERA_BASE_POSZ;													// カメラのＺ座標

	pCamera->m_posCameraP = CameraEye;														// カメラ位置
	pCamera->m_posCameraR = CameraView;														// カメラの注視点
	pCamera->m_vecCameraU = CameraVec;														// カメラの上方向

	fLengthX = CameraView.x - CameraEye.x;													// Ｘ座標の長さ
	fLengthY = CameraView.y - CameraEye.y;													// Ｙ座標の長さ
	fLengthZ = CameraView.z - CameraEye.z;													// Ｚ座標の長さ

	pCamera->m_rotCamera = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );									// カメラの角度

	fLengthX *= fLengthX;																	// Ｘ座標の長さの２乗
	fLengthY *= fLengthY;																	// Ｙ座標の長さの２乗
	fLengthZ *= fLengthZ;																	// Ｚ座標の長さの２乗

	pCamera->m_fLenght = sqrtf( fLengthZ + fLengthX );										// カメラの注視点からの半径

	pCamera->m_fNear = CAMERA_NEAR;															// 前方クリッピング面
	pCamera->m_fFar = CAMERA_FAR;															// 後方クリッピング面

	// 初期化
	pCamera->Init();

	return pCamera;
}

//==============================================================================
//	関数名	Rot
//	引数	None
//	戻り値	None
//==============================================================================
void CCamera::Rot( void )
{
	bool bCrossProduct;															// 外積判定用変数
	float fWork;

	// 外積の取得
	bCrossProduct = CrossProductVector( m_rotCamera, m_nextCameraRot.y );
	_doRot= false;

	// 回転しているどうかの判定
	if( m_nextCameraRot.y != m_rotCamera.y )
	{
		_doRot = true;
	}

	if( _doRot == true )
	{
		// 外積が上方向のとき
		if( bCrossProduct == true )
		{
			// 角度の増加
			m_rotCamera.y -= RADIAN( 1.0f );
		}
		// 外積が下方向のとき
		else if( bCrossProduct == false )
		{
			// 角度の減少
			m_rotCamera.y += RADIAN( 1.0f );
		}
	}

	// 角度が近しい値になったとき
	if( ( m_nextCameraRot.y - m_rotCamera.y < RADIAN( 1.0f ) ) && ( m_nextCameraRot.y - m_rotCamera.y > -RADIAN( 1.0f ) ) )
	{
		m_rotCamera.y = m_nextCameraRot.y;										// 角度を一致させる
	}

	// 360度を超えたとき
	if( m_rotCamera.y > RADIAN( 360.0f ) )
	{
		fWork = RADIAN( 360.0f ) - m_rotCamera.y;								// 差分の取得

		m_rotCamera.y = RADIAN( 0.0f ) - fWork;									// 角度の格納
	}
	// 0度を下回ったとき
	else if( m_rotCamera.y < -RADIAN( 0.0f ) )
	{
		fWork = m_rotCamera.y + RADIAN( 0.0f );									// 差分の取得

		m_rotCamera.y = RADIAN( 360.0f ) - fWork;								// 角度の格納
	}
}

//==============================================================================
//	関数名	GetRotCamera
//	引数	None
//	戻り値	D3DXVECTOR3
//==============================================================================
D3DXVECTOR3 *CCamera::GetRotCamera( void )
{
	return &m_rotCamera;
}

//==============================================================================
//	関数名	GetCameraView
//	引数	None
//	戻り値	D3DXMATRIX
//==============================================================================
D3DXMATRIX CCamera::GetCameraView( void )
{
	return m_mtxView;
}

//==============================================================================
//	関数名	GetBaseCameraView
//	引数	None
//	戻り値	D3DXMATRIX
//==============================================================================
D3DXMATRIX CCamera::GetBaseCameraView( void )
{
	return m_mtxBaseView;
}

//==============================================================================
//	関数名	GetCameraProj
//	引数	None
//	戻り値	D3DXMATRIX
//==============================================================================
D3DXMATRIX CCamera::GetCameraProj( void )
{
	return m_mtxProjection;
}

//==============================================================================
//	関数名	GetLookatCamera
//	引数	None
//	戻り値	D3DXVECTOR3
//==============================================================================
D3DXVECTOR3 *CCamera::GetLookatCamera( void )
{
	return &m_posCameraR;
}

//==============================================================================
//	関数名	ViewBaseRot
//	引数	float
//	戻り値	None
//==============================================================================
void CCamera::ViewBaseRot( float rot )
{
	/*CKeyboard *pKeyboard = CManeger::GetKeyboard();

	// 左に回転
	if( pKeyboard->GetKeyboardRepeat( DIK_Z ) )
	{
		m_rotCamera.y -= rot;

		m_posCameraP.x = m_posCameraR.x - sinf( m_rotCamera.y ) * m_fLenght;	// Ｘ座標の格納
		m_posCameraP.z = m_posCameraR.z - cosf( m_rotCamera.y ) * m_fLenght;	// Ｚ座標の格納
	}

	// 右に回転
	if( pKeyboard->GetKeyboardRepeat( DIK_C ) )
	{
		m_rotCamera.y += rot;

		m_posCameraP.x = m_posCameraR.x - sinf( m_rotCamera.y ) * m_fLenght;	// Ｘ座標の格納
		m_posCameraP.z = m_posCameraR.z - cosf( m_rotCamera.y ) * m_fLenght;	// Ｚ座標の格納
	}

	// 上に回転
	if( pKeyboard->GetKeyboardRepeat( DIK_UP ) )
	{
		m_posCameraR.y += 2.0f;
	}

	// 下に回転
	if( pKeyboard->GetKeyboardRepeat( DIK_DOWN ) )
	{
		m_posCameraR.y -= 2.0f;
	}*/
}

//==============================================================================
//	関数名	ViewBaseRot
//	引数	float
//	戻り値	None
//==============================================================================
void CCamera::PosRot( float rot )
{
	//CKeyboard *pKeyboard = CManeger::GetKeyboard();

	// 左に回転
	m_rotCamera.y -= rot;

	m_posCameraP.x = m_posCameraR.x - sinf( m_rotCamera.y ) * m_fLenght;	// Ｘ座標の格納
	m_posCameraP.z = m_posCameraR.z - cosf( m_rotCamera.y ) * m_fLenght;	// Ｚ座標の格納
}

//==============================================================================
//	関数名	MoveCameraAndView
//	引数	None
//	戻り値	None
//==============================================================================
void CCamera::MoveCameraAndView( void )
{
	/*CKeyboard *pKeyboard = CManeger::GetKeyboard();

	// Dを押されたとき
	if( pKeyboard->GetKeyboardRepeat( DIK_D ) )
	{
		m_posCameraP.x -= ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// カメラのＸ座標の減少
		m_posCameraR.x -= ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// 注視点のＸ座標の減少

		m_posCameraP.z -= ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// カメラのＺ座標の減少
		m_posCameraR.z -= ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// 注視点のＺ座標の減少
	}

	// Aを押されたとき
	if( pKeyboard->GetKeyboardRepeat( DIK_A ) )
	{
		m_posCameraP.x += ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// カメラのＸ座標の増加
		m_posCameraR.x += ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// 注視点のＸ座標の増加

		m_posCameraP.z += ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// カメラのＺ座標の減少
		m_posCameraR.z += ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// 注視点のＺ座標の減少
	}

	// Wを押されたとき
	if( pKeyboard->GetKeyboardRepeat( DIK_W ) )
	{
		m_posCameraP.x -= ADD_POS * sinf( m_rotCamera.y );									// カメラのＸ座標の減少
		m_posCameraR.x -= ADD_POS * sinf( m_rotCamera.y );									// 注視点のＸ座標の減少

		m_posCameraP.z -= ADD_POS * cosf( m_rotCamera.y );									// カメラのＺ座標の減少
		m_posCameraR.z -= ADD_POS * cosf( m_rotCamera.y );									// 注視点のＺ座標の減少
	}

	// Sを押されたとき
	if( pKeyboard->GetKeyboardRepeat( DIK_S ) )
	{
		m_posCameraP.x += ADD_POS * sinf( m_rotCamera.y );									// カメラのＸ座標の減少
		m_posCameraR.x += ADD_POS * sinf( m_rotCamera.y );									// 注視点のＸ座標の減少

		m_posCameraP.z += ADD_POS * cosf( -m_rotCamera.y );									// カメラのＺ座標の増加
		m_posCameraR.z += ADD_POS * cosf( -m_rotCamera.y );									// 注視点のＺ座標の増加
	}*/
}

//==============================================================================
//	関数名	SetCameraPos
//	引数	D3DXVECTOR3 pos
//	戻り値	None
//==============================================================================
void CCamera::SetCameraPos( D3DXVECTOR3 pos )
{
	// カメラの注視点を引数に合わせる
	m_posCameraR = pos;

	// カメラの位置を注視点に合わせて移動
	m_posCameraP.x = pos.x + ( m_fLenght * sinf( m_rotCamera.y ) );
	m_posCameraP.z = pos.z - ( m_fLenght * cosf( m_rotCamera.y ) );
}

//==============================================================================
//	関数名	SetCameraNextRot
//	引数	D3DXVECTOR3 rot
//	戻り値	None
//==============================================================================
void CCamera::SetCameraNextRot( D3DXVECTOR3 rot )
{
	float fWork = 0.0f;

	// カメラの角度を格納
	m_nextCameraRot = rot;

	// 360度を超えたとき
	if( m_nextCameraRot.y > RADIAN( 360.0f ) )
	{
		fWork = RADIAN( 360.0f ) - m_nextCameraRot.y;							// 差分の取得
		
		m_nextCameraRot.y = RADIAN( 0.0f ) - fWork;								// 角度の格納
	}
}

/* ----- EOF ----- */