//==============================================================================
//
// FineName [ singletom.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// クラス宣言
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

	// コピーコンストラクタを防ぐ
	CSingleton( const CSingleton& single ){};
	const CSingleton& operator = ( const CSingleton& single ){};
};

//template <typename T> T* CSingleton<T>::_instance = NULL;

// コメントアウトをはずした場合のシングルトンは自身のタイミングでdelteする必要がある

#endif

/* ----- EOF ----- */