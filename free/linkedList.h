//==============================================================================
//
// FineName [ linkedList.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// クラス宣言
//------------------------------------------------------------------------------
template <class T> class CLinkedList
{
public:
	struct CExtra
	{
		CExtra() : _tmpClass( NULL ), _prev( NULL ), _next( NULL ){}
		~CExtra(){}

		T *getClass( void )
		{ 
			if( _tmpClass != NULL )
			{ 
				return _tmpClass;
			}
			else
			{ 
				return NULL;
			} 
		}

		CExtra *getNext( void ){ return _next; }

		CExtra *_prev;
		CExtra *_next;

		T *_tmpClass;
	};

	CLinkedList() : _top( NULL ), _last( NULL ), _size( 0 ){}
	~CLinkedList(){}

	// 取得
	T *get( int i )
	{
		CExtra *list = _top;
		CExtra *listNext = NULL;

		// サイズよりおなじとき
		if( _size <= i )
		{
			return NULL;
		}

		for( int j = 0; j <= i; j++ )
		{
			listNext = list->_next;

			if( j == i )
			{
				return list->getClass();
			}

			list = listNext;
		}

		return NULL;
	}

	// 追加
	void add( T *t )
	{
		CExtra *listLast = NULL;
		CExtra *work = NULL;

		work = NEW CExtra;

		// リストの先頭がNULLのとき
		if( _top == NULL )
		{
			_top = work;
			_last = _top;
			_last->_prev = NULL;

		}
		// リストの先頭がNULLでないとき
		else
		{
			listLast = _last;														// ラストのアドレスを取得

			_last = work;															// ラストに自身の追加

			_last->_prev = listLast;												// ラストの前を設定
			_last->_prev->_next = _last;											// ラスト前の次に自身の追加
		}

		_last->_next = NULL;														// ラストの次をNULL
		_last->_tmpClass = t;														// 自身をラストにする

		_size++;
	}

	// 解放
	void remove( T *t )
	{
		CExtra *list = NULL;
		bool del = false;

		// 自身のみがリストにあるとき
		if( ( _top->getClass() == t ) && ( _last->getClass() == t ) )
		{
			SafeDelete( _top->_tmpClass );
			_top->_next = NULL;
			_top->_prev = NULL;
			SafeDelete( _top );														// 自身の破棄

			_top = NULL;															// 先頭をNULLにする
			_last = NULL;															// ラストをNULLにする

			del = true;
		}
		// 自身が先頭のとき
		else if( _top->getClass() == t )
		{
			list = _top->_next;														// 自身の次をポインタに格納

			SafeDelete( _top->_tmpClass );											// 自身の破棄
			_top->_next = NULL;
			_top->_prev = NULL;
			SafeDelete( _top );

			_top = list;															// 先頭をポインタのアドレスにする

			list->_prev = NULL;														// 自身をNULLにする

			del = true;
		}
		// 自身がラストのとき
		else if( _last->getClass() == t )
		{
			list = _last->_prev;													// 自身の前をポインタに格納

			SafeDelete( _last->_tmpClass );											// 自身の破棄
			_last->_next = NULL;
			_last->_prev = NULL;
			SafeDelete( _last );

			_last = list;															// ラストをポインタのアドレスにする

			list->_next = NULL;														// 自身をNULLにする

			del = true;
		}
		// 自身がラストでも先頭でもないとき
		else
		{
			list = getLinkedList(t);
			CExtra *listNext = list->_next;											// 自身の次をポインタに

			list->_prev->_next = listNext;
			listNext->_prev = list->_prev;

			SafeDelete( list->_tmpClass );
			list->_next = NULL;
			list->_prev = NULL;
			SafeDelete( list );

			del = true;
		}

		// 削除したとき
		if( del ) _size--;
	}

	void removeList( T *t )
	{
		CExtra *list = NULL;
		CExtra *delC = NULL;
		bool del = false;

		// 自身のみがリストにあるとき
		if( ( _top->getClass() == t ) && ( _last->getClass() == t ) )
		{
			delC = _top;

			_top->_tmpClass = NULL;
			_top->_next = NULL;
			_top->_prev = NULL;
			_last->_tmpClass = NULL;

			_top = NULL;															// 先頭をNULLにする
			_last = NULL;															// ラストをNULLにする

			del = true;
		}
		// 自身が先頭のとき
		else if( _top->getClass() == t )
		{
			delC = _top;
			list = _top->_next;														// 自身の次をポインタに格納

			_top->_tmpClass = NULL;
			_top->_next = NULL;
			_top->_prev = NULL;

			_top = list;															// 先頭をポインタのアドレスにする

			list->_prev = NULL;														// 自身をNULLにする

			del = true;
		}
		// 自身がラストのとき
		else if( _last->getClass() == t )
		{
			delC = _last;
			list = _last->_prev;													// 自身の前をポインタに格納

			_last->_tmpClass = NULL;
			_last->_next = NULL;
			_last->_prev = NULL;

			_last = list;															// ラストをポインタのアドレスにする

			list->_next = NULL;														// 自身をNULLにする

			del = true;
		}
		// 自身がラストでも先頭でもないとき
		else
		{
			list = getLinkedList(t);
			delC = list;

			// NULLでないとき
			if( list != NULL )
			{
				CExtra *listNext = list->_next;										// 自身の次をポインタに

				list->_prev->_next = listNext;
				listNext->_prev = list->_prev;

				list->_tmpClass = NULL;
				list->_next = NULL;
				list->_prev = NULL;

				del = true;
			}
		}

		delC->_tmpClass = NULL;
		SafeDelete( delC );

		if( del ) _size--;
	}

	int getSize( void ){ return _size; }

	CExtra *getTop( void ){ return _top; }
	CExtra *getLast( void ){ return _last; }

	// クリア
	void clear( void )
	{
		CExtra *list = _top;
		CExtra *listNext = NULL;

		while( list != NULL )
		{
			listNext = list->getNext();

			remove( list->_tmpClass );

			list = listNext;
		}

		_last = NULL;
	}

private:

	int _size;
	CExtra *_top;
	CExtra *_last;

	// リストの取得
	CExtra *getLinkedList( T *t )
	{
		CExtra *listNow = _top;
		CExtra *listNext = NULL;

		for( int i = 0; i < _size; i++ )
		{
			listNext = listNow->_next;

			if( listNow->_tmpClass == t )
			{
				return listNow;
			}

			listNow = listNext;
		}

		return NULL;
	}
};

#endif

/* ----- EOF ----- */