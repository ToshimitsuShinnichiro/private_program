/*
	window.cpp
*/

#include <Windows.h>
#include "window.h"

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

// �R���X�g���N�^
CWindow::CWindow(HINSTANCE instance, WNDCLASSEX* pwcex) : instance(instance), pwcex(pwcex)
{
	SettingPram();
	hWnd = Create();

	if(hWnd == NULL)
	{
		return;
	}

	//�E�B���h�E�̕\��
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
}

// �f�X�g���N�^
CWindow::~CWindow()
{
	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass( "WindowSet", wcex.hInstance );
}

// �E�B���h�E�̐���
HWND CWindow::Create()
{
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx( pwcex );

	//�E�B���h�E����
	return CreateWindowEx
			( 
				0,
				"WindowSet",																//�N���X��
				WINDOW_NAME,																//�E�B���h�E��
				WS_OVERLAPPEDWINDOW,														//���
				CW_USEDEFAULT,																//�\���ʒu�w
				CW_USEDEFAULT,																//�\���ʒu�x
				SCREEN_WIDTH,																//��
				SCREEN_HEIGHT,																//����
				NULL,																		//�e�E�B���h�E�n���h��
				NULL,																		//���j���[�n���h��
				instance,																	//�C���X�^���X�n���h��
				NULL																		//���̑��쐬�f�[�^
			);
}

// �v���V�[�W������
LRESULT CALLBACK WndProc( HWND hWnd, UINT umsg, WPARAM wParam, LPARAM lParam )
{
	int nID = 0;																			//ID�p�ϐ�

	switch( umsg )
	{
		/*-----------------------
		|	�L�[�̉������擾	|
		-----------------------*/
		case WM_KEYDOWN :

			switch( wParam )
			{
				/*-----------------------------------------------
				|	ESCAPE�������ꂽ�Ƃ��ɃE�B���h�E��j������	|
				-----------------------------------------------*/
				case VK_ESCAPE :					
					nID = MessageBox( hWnd, "�Q�[�����I�����܂����H", "�E�B���h�E�j��", MB_YESNO );

					if( nID == IDYES )
					{
						DestroyWindow( hWnd );												//�E�B���h�E�j��
					}

					break;
			}

			break;

		/*-------------------------------
		|	�E�B���h�E���j�������Ƃ�	|
		-------------------------------*/
		case WM_DESTROY :

			//�E�B���h�E��j������
			PostQuitMessage( 0 );

			break;
	}

	return DefWindowProc( hWnd, umsg, wParam, lParam );										//�v���V�[�W���[��Ԃ�
}

// �p�����[�^�[�̐ݒ�
void CWindow::SettingPram()
{
	//�E�B���h�E�N���X�̏���ݒ�
	pwcex->cbSize = sizeof( WNDCLASSEX );													// �\���̃T�C�Y
	pwcex->style = CS_CLASSDC;																// �X�^�C��
	pwcex->lpfnWndProc = WndProc;															// �E�B���h�E�v���V�[�W��
	pwcex->hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1);									// �E�B���h�E�w�i						
	pwcex->hInstance = instance;															// �C���X�^���X�n���h��
	pwcex->cbClsExtra = 0;																	// �g�����P
	pwcex->cbWndExtra = 0;																	// �g�����Q
	pwcex->hCursor = LoadCursor( NULL, IDC_ARROW );											// �}�E�X�J�[�\��
	pwcex->hIcon = NULL;																	// �A�C�R��
	pwcex->hIconSm = NULL;
	pwcex->lpszClassName = "WindowSet";														// �E�B���h�E�N���X��
	pwcex->lpszMenuName = NULL;																// ���j���[��
}