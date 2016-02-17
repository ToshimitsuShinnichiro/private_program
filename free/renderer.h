//==============================================================================
//
// FineName [ texture.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#define DIRECTINPUT_VERSION			( 0x0800 )												//�C���v�b�g�x���h�~

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "d3dx9.h"
#include "dinput.h"
//#include "dmusici.h"

//------------------------------------------------------------------------------
//�@���C�u�����̃����N
//------------------------------------------------------------------------------
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "winmm.lib" )

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define FVF_VERTEX_3D			( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	// ���_�t�H�[�}�b�g
#define FVF_VERTEX_2D			( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )// ���_�t�H�[�}�b�g
#define float2					D3DXVECTOR2
#define float3					D3DXVECTOR3
#define float4					D3DXVECTOR4
#define COLOR					D3DXCOLOR

typedef struct
{
	float3	vtx;																//���_���W
	float3 nor;																	//�e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;															//���ˌ�
	float2 tex;																	//�e�N�X�`�����W
}VERTEX_3D;

typedef struct
{
	float3	vtx;																// ���_���W
	float rhw;																	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;															// ���ˌ�
	float2 tex;																	// �e�N�X�`�����W
}VERTEX_2D;

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
float3 D3DXOutMatrix( float3 vec, D3DXMATRIX matrix );

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �N���X�錾
//------------------------------------------------------------------------------
class CRenderer
{
public:
	HRESULT Init( HWND hWnd, BOOL bWindow );
	void Uninit( void );
	void Update( void );
	LPDIRECT3DDEVICE9 GetDevice( void );
	LPD3DXFONT GetFont( void );

	static CRenderer *GetInstance( void );

	bool BeginRender( void );
	void EndRender( void );

private:
	LPDIRECT3D9 m_pD3D;															//Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;												//�f�o�C�X�I�u�W�F�N�g

	CRenderer();
	CRenderer( const CRenderer &renderer );
	~CRenderer();
};

#endif

/* ----- EOF ----- */