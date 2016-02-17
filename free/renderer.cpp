//==============================================================================
//
// FineName [ renderer.cpp ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "keyboard.h"
#include <stdio.h>

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------------
float3 D3DXOutMatrix( float3 vec, D3DXMATRIX matrix )
{
	float4 v = float4( vec.x, vec.y, vec.z, 1.0f );

	// �O���[�o�����W�֕ϊ�
	D3DXVec4Transform( &v, &v, &matrix );

	return float3( v.x, v.y, v.z );
}

//==============================================================================
//	�֐���	CRenderer
//	����	None
//	�߂�l	None
//==============================================================================
CRenderer::CRenderer()
{
}

//==============================================================================
//	�֐���	~CRenderer
//	����	None
//	�߂�l	None
//==============================================================================
CRenderer::~CRenderer()
{
}

//==============================================================================
//	�֐���	Init
//	����	HWND, BOOL
//	�߂�l	HRESULT
//==============================================================================
HRESULT CRenderer::Init( HWND hWnd, BOOL bWindow )
{
	D3DPRESENT_PARAMETERS d3dpp;												//�p�����[�^�[
	D3DDISPLAYMODE d3ddm;														//�f�B�X�v���C���[�h

	//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	//Direct3D�I�u�W�F�N�g�̐����Ɏ��s�����Ƃ�
	if( m_pD3D == NULL )
	{
		return E_FAIL;															//E_FAIL��Ԃ�
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		return E_FAIL;															//E_FAIL��Ԃ�
	}

	//�p�����[�^�̐ݒ�
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );										//���g�̃N���A
	d3dpp.BackBufferCount = 1;													//�o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;										//��
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;										//����
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;									//�t�H�[�}�b�g
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;									//�X���b�v�G�t�F�N�g�^�C�v
	d3dpp.Windowed = bWindow;													//�E�B���h�E�̏��
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;								//D3D�t�H�[�}�g
	d3dpp.BackBufferFormat = d3ddm.Format;										//D3D�t�H�[�}�b�g
	
	//�E�B���h�E���[�h�̔���
	if( bWindow == TRUE )
	{	//�E�B���h�E���[�h
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{	//�t���X�N���[�����[�h
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	//�f�o�C�X����
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
									  D3DDEVTYPE_HAL,
									  hWnd,
									  D3DCREATE_HARDWARE_VERTEXPROCESSING,		//�n�[�h�E�F�A���g�p
									  &d3dpp,
									  &m_pD3DDevice ) ) )
	{
		if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
									  D3DDEVTYPE_HAL,
									  hWnd,
									  D3DCREATE_SOFTWARE_VERTEXPROCESSING,		//�\�t�g�E�F�A���g�p
									  &d3dpp,
									  &m_pD3DDevice ) ) )
		{
			if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
									  D3DDEVTYPE_REF,
									  hWnd,
									  D3DCREATE_HARDWARE_VERTEXPROCESSING,		//�n�[�h�E�F�A���g�p
									  &d3dpp,
									  &m_pD3DDevice ) ) )
			{
				return E_FAIL;													//E_FAIL��Ԃ�
			}
		}
	}

	/*---------------------------------------
	|	�����_�[�X�e�[�g�p�����[�^�[�̐ݒ�	|
	---------------------------------------*/
	//�J���̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	//Z�o�b�t�@�̎g�p
	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	//���̎g�p
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	//���̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//���̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	/*-------------------------------
	|	�T���v���[�X�e�[�g�̐ݒ�	|
	-------------------------------*/
	//�摜�̉������J��Ԃ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	//�摜�̏c�����J��Ԃ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	//�k�����A���`�G�C���A�V���O
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP );
	//�g�厞�A���`�G�C���A�V���O
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTADDRESS_WRAP );

	/*----------------------------------------
	|	�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�	 |
	----------------------------------------*/
	//�X�e�[�W�X�e�[�g���|�����킹��
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	//�e�N�X�`���̃A���t�@���w��
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	//�|���S���̃A���t�@���w��
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	// �}���`�����_�����O�̍ő吔�̎擾
	D3DCAPS9 Caps;
	m_pD3DDevice->GetDeviceCaps( &Caps );
	DWORD MaxRT = Caps.NumSimultaneousRTs;

	return S_OK;
}

//==============================================================================
//	�֐���	Uninit
//	����	None
//	�߂�l	None
//==============================================================================
void CRenderer::Uninit( void )
{
	//�f�o�C�X�̉��
	SafeRelease( m_pD3DDevice );

	//Direct3D�I�u�W�F�N�g�̉��
	SafeRelease( m_pD3D );
}

//==============================================================================
//	�֐���	Update
//	����	None
//	�߂�l	None
//==============================================================================
void CRenderer::Update( void )
{

}

//==============================================================================
//	�֐���	GetDevice
//	����	None
//	�߂�l	LPDIRECT3DDEVICE9
//==============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice( void )
{
	return m_pD3DDevice;
}

//==============================================================================
//	�֐���	GetInstance
//	����	None
//	�߂�l	CRenderer
//==============================================================================
CRenderer *CRenderer::GetInstance( void )
{
	static CRenderer Renderer;

	return &Renderer;
}

//==============================================================================
//	�֐���	BeginRender
//	����	None
//	�߂�l	bool
//==============================================================================
bool CRenderer::BeginRender( void )
{
	//��ʂ̃N���A
	m_pD3DDevice->Clear( 0,
						 NULL, 
						 ( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL ), 
						 D3DCOLOR_RGBA( 255, 255, 0, 255 ), 
						 1.0f, 
						 0 );

	// TODO �e�����_�[���Ńf�o�C�X�̃N���A��������̂����X�g�����A�����ŃN���A��������H

	//�`��J�n
	if( SUCCEEDED( m_pD3DDevice->BeginScene( ) ) )
	{	
		// NULL�łȂ��Ƃ�
		/*if( pCamera != NULL )
		{
			pCamera->Draw();
		*/
	}
	else
	{
		return false;
	}
	
	return true;
}

//==============================================================================
//	�֐���	EndRender
//	����	None
//	�߂�l	void
//==============================================================================
void CRenderer::EndRender( void )
{
	//�`��I��
	m_pD3DDevice->EndScene( );

	//�o�b�N�o�b�t�@�ƃv���C�}���o�b�t�@�̓���ւ�
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );

}

/* ----- EOF ----- */