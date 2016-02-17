//==============================================================================
//
// FineName [ camera.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "camera.h"
#include "renderer.h"
#include "keyboard.h"
#include "product.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define VIEW_ANGLE							( 3.14f / 180.0f * 45.0f )				// ����p
#define CAMERA_BASE_POSX					( 0.0f )							// �J�����̊�{�w���W
#define CAMERA_BASE_POSY					( 380.0f )							// �J�����̊�{�x���W
#define CAMERA_BASE_POSZ					( -830.0f )							// �J�����̊�{�y���W
#define ADD_POS								( 5.0f )							// ���W�̑�����
#define ADD_CAMERA_ANGLE					( D3DX_PI / 180 * 3 )				// �J�����A���O���̑�����
#define CAMERA_MAX							( D3DX_PI / 180 * 180 )				// �J�����̍ő�p�x
#define CAMERA_SLIDE						( D3DX_PI / 180 * 90 )				// �J�����̕␳
#define SLIDE_POS							( 15.0f )							// ���W�����炷
#define CAMERA_NEAR							( 1 )								// �O���N���b�s���O��
#define CAMERA_FAR							( 15000 )							// ����N���b�s���O��

//------------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------------

//==============================================================================
//	�֐���	CCamera
//	����	None
//	�߂�l	None
//==============================================================================
CCamera::CCamera()
{
	// �r���[�E�v���W�F�N�V�����̍쐬
	D3DXMatrixOrthoLH( &OrthoProj, SCREEN_WIDTH, SCREEN_HEIGHT, 0.5f, 1000 );
	D3DXMatrixLookAtLH( &OrthoView, &float3( 0.0f, 0.0f, -1.0f ), &float3( 0.0f, 0.0f, 0.0f ), &float3( 0.0f, 1.0f, 0.0f ) );
}

//==============================================================================
//	�֐���	~CCamera
//	����	None
//	�߂�l	None
//==============================================================================
CCamera::~CCamera()
{
}

//==============================================================================
//	�֐���	Init
//	����	None
//	�߂�l	None
//==============================================================================
void CCamera::Init( void )
{
	m_nextCameraRot = m_rotCamera;
	m_nextCameraRot.y = 0.0f;

	_doRot = false;

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxBaseView );

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH( &m_mtxBaseView, &m_posCameraP, &m_posCameraR, &m_vecCameraU );
}

//==============================================================================
//	�֐���	Uninit
//	����	None
//	�߂�l	None
//==============================================================================
void CCamera::Uninit( void )
{
	CCamera *pCamera = GetCamera();

	// NULL�łȂ��Ƃ�
	if( pCamera != NULL )
	{
		pCamera = NULL;
	}
}

//==============================================================================
//	�֐���	Update
//	����	None
//	�߂�l	None
//==============================================================================
void CCamera::Update( void )
{
	// �����_�𒆐S�ɉ�]
	//this->ViewBaseRot( RADIAN( 2.0f ) );

	// �p�x�����킹��
	//Rot();
}

//==============================================================================
//	�֐���	Draw
//	����	None
//	�߂�l	None
//==============================================================================
void CCamera::Draw( void )
{
	CRenderer *pRenderer = CRenderer::GetInstance();							// �C���X�^���X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();							// �f�o�C�X�̎擾

	/*---------------------------
	|	�r���[�}�g���b�N�X����	|
	---------------------------*/
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxView );

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH( &m_mtxView, &m_posCameraP, &m_posCameraR, &m_vecCameraU );

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_VIEW, &m_mtxView );

	/*-----------------------------------
	|	�v���W�F�N�g�}�g���b�N�X�̐���	|
	-----------------------------------*/
	// �v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxProjection );

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH( &m_mtxProjection, VIEW_ANGLE, ( SCREEN_WIDTH / SCREEN_HEIGHT ), m_fNear, m_fFar );

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_PROJECTION, &m_mtxProjection );
}

//==============================================================================
//	�֐���	Release
//	����	None
//	�߂�l	None
//==============================================================================
void CCamera::Release( void )
{
	CCamera *pCamera = GetCamera();

	// ��n��
	pCamera->Uninit();

	delete pCamera;

	pCamera = NULL;
}

//==============================================================================
//	�֐���	Create
//	����	None
//	�߂�l	None
//==============================================================================
CCamera *CCamera::Create( void )
{
	CCamera *pCamera = NEW CCamera;

	float fLengthX = 0;																// �w���W�̒���
	float fLengthY = 0;																// �x���W�̒���
	float fLengthZ = 0;																// �y���W�̒���
	float fRotY = 0;																	// �x�p�x
	float fRotZ = 0;																	// �y�p�x

	// �J�������W�̐ݒ�
	pCamera->m_fPosX = CAMERA_BASE_POSX;													// �J�����̂w���W
	pCamera->m_fPosY = CAMERA_BASE_POSY;													// �J�����̂x���W
	pCamera->m_fPosZ = CAMERA_BASE_POSZ;													// �J�����̂y���W

	pCamera->m_posCameraP = D3DXVECTOR3( pCamera->m_fPosX, pCamera->m_fPosY, pCamera->m_fPosZ );// �J�����ʒu
	pCamera->m_posCameraR = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );								// �J�����̒����_
	pCamera->m_vecCameraU = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );								// �J�����̏����
	
	fLengthX = pCamera->m_posCameraR.x - pCamera->m_posCameraP.x;							// �w���W�̒���
	fLengthY = pCamera->m_posCameraR.y - pCamera->m_posCameraP.y;							// �x���W�̒���
	fLengthZ = pCamera->m_posCameraR.z - pCamera->m_posCameraP.z;							// �y���W�̒���

	fRotY = 0.0f;																			// �J�����̊p�xY
	fRotZ = atan2f( fLengthZ, fLengthY );													// �J�����̊p�xZ

	pCamera->m_rotCamera = D3DXVECTOR3( 0.0f, fRotY, fRotZ );								// �J�����̊p�x

	fLengthX *= fLengthX;																	// �w���W�̒����̂Q��
	fLengthY *= fLengthY;																	// �x���W�̒����̂Q��
	fLengthZ *= fLengthZ;																	// �y���W�̒����̂Q��

	pCamera->m_fLenght = sqrtf( fLengthZ + fLengthX );										// �J�����̒����_����̔��a

	pCamera->m_fNear = CAMERA_NEAR;															// �O���N���b�s���O��
	pCamera->m_fFar = CAMERA_FAR;															// ����N���b�s���O��

	// ������
	pCamera->Init();

	return pCamera;
}

//==============================================================================
//	�֐���	Create
//	����	None
//	�߂�l	None
//==============================================================================
CCamera *CCamera::Create( D3DXVECTOR3 CameraEye, D3DXVECTOR3 CameraView, D3DXVECTOR3 CameraVec )
{
	CCamera *pCamera = NEW CCamera;

	float fLengthX = 0;																// �w���W�̒���
	float fLengthY = 0;																// �x���W�̒���
	float fLengthZ = 0;																// �y���W�̒���

	// �J�������W�̐ݒ�
	pCamera->m_fPosX = CAMERA_BASE_POSX;													// �J�����̂w���W
	pCamera->m_fPosY = CAMERA_BASE_POSY;													// �J�����̂x���W
	pCamera->m_fPosZ = CAMERA_BASE_POSZ;													// �J�����̂y���W

	pCamera->m_posCameraP = CameraEye;														// �J�����ʒu
	pCamera->m_posCameraR = CameraView;														// �J�����̒����_
	pCamera->m_vecCameraU = CameraVec;														// �J�����̏����

	fLengthX = CameraView.x - CameraEye.x;													// �w���W�̒���
	fLengthY = CameraView.y - CameraEye.y;													// �x���W�̒���
	fLengthZ = CameraView.z - CameraEye.z;													// �y���W�̒���

	pCamera->m_rotCamera = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );									// �J�����̊p�x

	fLengthX *= fLengthX;																	// �w���W�̒����̂Q��
	fLengthY *= fLengthY;																	// �x���W�̒����̂Q��
	fLengthZ *= fLengthZ;																	// �y���W�̒����̂Q��

	pCamera->m_fLenght = sqrtf( fLengthZ + fLengthX );										// �J�����̒����_����̔��a

	pCamera->m_fNear = CAMERA_NEAR;															// �O���N���b�s���O��
	pCamera->m_fFar = CAMERA_FAR;															// ����N���b�s���O��

	// ������
	pCamera->Init();

	return pCamera;
}

//==============================================================================
//	�֐���	Rot
//	����	None
//	�߂�l	None
//==============================================================================
void CCamera::Rot( void )
{
	bool bCrossProduct;															// �O�ϔ���p�ϐ�
	float fWork;

	// �O�ς̎擾
	bCrossProduct = CrossProductVector( m_rotCamera, m_nextCameraRot.y );
	_doRot= false;

	// ��]���Ă���ǂ����̔���
	if( m_nextCameraRot.y != m_rotCamera.y )
	{
		_doRot = true;
	}

	if( _doRot == true )
	{
		// �O�ς�������̂Ƃ�
		if( bCrossProduct == true )
		{
			// �p�x�̑���
			m_rotCamera.y -= RADIAN( 1.0f );
		}
		// �O�ς��������̂Ƃ�
		else if( bCrossProduct == false )
		{
			// �p�x�̌���
			m_rotCamera.y += RADIAN( 1.0f );
		}
	}

	// �p�x���߂����l�ɂȂ����Ƃ�
	if( ( m_nextCameraRot.y - m_rotCamera.y < RADIAN( 1.0f ) ) && ( m_nextCameraRot.y - m_rotCamera.y > -RADIAN( 1.0f ) ) )
	{
		m_rotCamera.y = m_nextCameraRot.y;										// �p�x����v������
	}

	// 360�x�𒴂����Ƃ�
	if( m_rotCamera.y > RADIAN( 360.0f ) )
	{
		fWork = RADIAN( 360.0f ) - m_rotCamera.y;								// �����̎擾

		m_rotCamera.y = RADIAN( 0.0f ) - fWork;									// �p�x�̊i�[
	}
	// 0�x����������Ƃ�
	else if( m_rotCamera.y < -RADIAN( 0.0f ) )
	{
		fWork = m_rotCamera.y + RADIAN( 0.0f );									// �����̎擾

		m_rotCamera.y = RADIAN( 360.0f ) - fWork;								// �p�x�̊i�[
	}
}

//==============================================================================
//	�֐���	GetRotCamera
//	����	None
//	�߂�l	D3DXVECTOR3
//==============================================================================
D3DXVECTOR3 *CCamera::GetRotCamera( void )
{
	return &m_rotCamera;
}

//==============================================================================
//	�֐���	GetCameraView
//	����	None
//	�߂�l	D3DXMATRIX
//==============================================================================
D3DXMATRIX CCamera::GetCameraView( void )
{
	return m_mtxView;
}

//==============================================================================
//	�֐���	GetBaseCameraView
//	����	None
//	�߂�l	D3DXMATRIX
//==============================================================================
D3DXMATRIX CCamera::GetBaseCameraView( void )
{
	return m_mtxBaseView;
}

//==============================================================================
//	�֐���	GetCameraProj
//	����	None
//	�߂�l	D3DXMATRIX
//==============================================================================
D3DXMATRIX CCamera::GetCameraProj( void )
{
	return m_mtxProjection;
}

//==============================================================================
//	�֐���	GetLookatCamera
//	����	None
//	�߂�l	D3DXVECTOR3
//==============================================================================
D3DXVECTOR3 *CCamera::GetLookatCamera( void )
{
	return &m_posCameraR;
}

//==============================================================================
//	�֐���	ViewBaseRot
//	����	float
//	�߂�l	None
//==============================================================================
void CCamera::ViewBaseRot( float rot )
{
	/*CKeyboard *pKeyboard = CManeger::GetKeyboard();

	// ���ɉ�]
	if( pKeyboard->GetKeyboardRepeat( DIK_Z ) )
	{
		m_rotCamera.y -= rot;

		m_posCameraP.x = m_posCameraR.x - sinf( m_rotCamera.y ) * m_fLenght;	// �w���W�̊i�[
		m_posCameraP.z = m_posCameraR.z - cosf( m_rotCamera.y ) * m_fLenght;	// �y���W�̊i�[
	}

	// �E�ɉ�]
	if( pKeyboard->GetKeyboardRepeat( DIK_C ) )
	{
		m_rotCamera.y += rot;

		m_posCameraP.x = m_posCameraR.x - sinf( m_rotCamera.y ) * m_fLenght;	// �w���W�̊i�[
		m_posCameraP.z = m_posCameraR.z - cosf( m_rotCamera.y ) * m_fLenght;	// �y���W�̊i�[
	}

	// ��ɉ�]
	if( pKeyboard->GetKeyboardRepeat( DIK_UP ) )
	{
		m_posCameraR.y += 2.0f;
	}

	// ���ɉ�]
	if( pKeyboard->GetKeyboardRepeat( DIK_DOWN ) )
	{
		m_posCameraR.y -= 2.0f;
	}*/
}

//==============================================================================
//	�֐���	ViewBaseRot
//	����	float
//	�߂�l	None
//==============================================================================
void CCamera::PosRot( float rot )
{
	//CKeyboard *pKeyboard = CManeger::GetKeyboard();

	// ���ɉ�]
	m_rotCamera.y -= rot;

	m_posCameraP.x = m_posCameraR.x - sinf( m_rotCamera.y ) * m_fLenght;	// �w���W�̊i�[
	m_posCameraP.z = m_posCameraR.z - cosf( m_rotCamera.y ) * m_fLenght;	// �y���W�̊i�[
}

//==============================================================================
//	�֐���	MoveCameraAndView
//	����	None
//	�߂�l	None
//==============================================================================
void CCamera::MoveCameraAndView( void )
{
	/*CKeyboard *pKeyboard = CManeger::GetKeyboard();

	// D�������ꂽ�Ƃ�
	if( pKeyboard->GetKeyboardRepeat( DIK_D ) )
	{
		m_posCameraP.x -= ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// �J�����̂w���W�̌���
		m_posCameraR.x -= ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// �����_�̂w���W�̌���

		m_posCameraP.z -= ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// �J�����̂y���W�̌���
		m_posCameraR.z -= ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// �����_�̂y���W�̌���
	}

	// A�������ꂽ�Ƃ�
	if( pKeyboard->GetKeyboardRepeat( DIK_A ) )
	{
		m_posCameraP.x += ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// �J�����̂w���W�̑���
		m_posCameraR.x += ADD_POS * sinf( m_rotCamera.y + CAMERA_SLIDE );				// �����_�̂w���W�̑���

		m_posCameraP.z += ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// �J�����̂y���W�̌���
		m_posCameraR.z += ADD_POS * cosf( m_rotCamera.y + CAMERA_SLIDE );				// �����_�̂y���W�̌���
	}

	// W�������ꂽ�Ƃ�
	if( pKeyboard->GetKeyboardRepeat( DIK_W ) )
	{
		m_posCameraP.x -= ADD_POS * sinf( m_rotCamera.y );									// �J�����̂w���W�̌���
		m_posCameraR.x -= ADD_POS * sinf( m_rotCamera.y );									// �����_�̂w���W�̌���

		m_posCameraP.z -= ADD_POS * cosf( m_rotCamera.y );									// �J�����̂y���W�̌���
		m_posCameraR.z -= ADD_POS * cosf( m_rotCamera.y );									// �����_�̂y���W�̌���
	}

	// S�������ꂽ�Ƃ�
	if( pKeyboard->GetKeyboardRepeat( DIK_S ) )
	{
		m_posCameraP.x += ADD_POS * sinf( m_rotCamera.y );									// �J�����̂w���W�̌���
		m_posCameraR.x += ADD_POS * sinf( m_rotCamera.y );									// �����_�̂w���W�̌���

		m_posCameraP.z += ADD_POS * cosf( -m_rotCamera.y );									// �J�����̂y���W�̑���
		m_posCameraR.z += ADD_POS * cosf( -m_rotCamera.y );									// �����_�̂y���W�̑���
	}*/
}

//==============================================================================
//	�֐���	SetCameraPos
//	����	D3DXVECTOR3 pos
//	�߂�l	None
//==============================================================================
void CCamera::SetCameraPos( D3DXVECTOR3 pos )
{
	// �J�����̒����_�������ɍ��킹��
	m_posCameraR = pos;

	// �J�����̈ʒu�𒍎��_�ɍ��킹�Ĉړ�
	m_posCameraP.x = pos.x + ( m_fLenght * sinf( m_rotCamera.y ) );
	m_posCameraP.z = pos.z - ( m_fLenght * cosf( m_rotCamera.y ) );
}

//==============================================================================
//	�֐���	SetCameraNextRot
//	����	D3DXVECTOR3 rot
//	�߂�l	None
//==============================================================================
void CCamera::SetCameraNextRot( D3DXVECTOR3 rot )
{
	float fWork = 0.0f;

	// �J�����̊p�x���i�[
	m_nextCameraRot = rot;

	// 360�x�𒴂����Ƃ�
	if( m_nextCameraRot.y > RADIAN( 360.0f ) )
	{
		fWork = RADIAN( 360.0f ) - m_nextCameraRot.y;							// �����̎擾
		
		m_nextCameraRot.y = RADIAN( 0.0f ) - fWork;								// �p�x�̊i�[
	}
}

/* ----- EOF ----- */