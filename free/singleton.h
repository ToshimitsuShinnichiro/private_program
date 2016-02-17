//==============================================================================
//
// FineName [ singletom.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �N���X�錾
//------------------------------------------------------------------------------
template<typename T> class CSingleton
{
public:
	static T* GetInstance( void )
	{ 
		//if( _instance == NULL ) _instance = new T(); 
		static T _instance;
		return &_instance;
	}

protected:
	CSingleton( void ){};
	virtual ~CSingleton( void ){};

private:
	//static T* _instance;

	// �R�s�[�R���X�g���N�^��h��
	CSingleton( const CSingleton& single ){};
	const CSingleton& operator = ( const CSingleton& single ){};
};

//template <typename T> T* CSingleton<T>::_instance = NULL;

// �R�����g�A�E�g���͂������ꍇ�̃V���O���g���͎��g�̃^�C�~���O��delte����K�v������

#endif

/* ----- EOF ----- */