//==============================================================================
//
// FineName [ linkedList.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �N���X�錾
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

	// �擾
	T *get( int i )
	{
		CExtra *list = _top;
		CExtra *listNext = NULL;

		// �T�C�Y��肨�Ȃ��Ƃ�
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

	// �ǉ�
	void add( T *t )
	{
		CExtra *listLast = NULL;
		CExtra *work = NULL;

		work = NEW CExtra;

		// ���X�g�̐擪��NULL�̂Ƃ�
		if( _top == NULL )
		{
			_top = work;
			_last = _top;
			_last->_prev = NULL;

		}
		// ���X�g�̐擪��NULL�łȂ��Ƃ�
		else
		{
			listLast = _last;														// ���X�g�̃A�h���X���擾

			_last = work;															// ���X�g�Ɏ��g�̒ǉ�

			_last->_prev = listLast;												// ���X�g�̑O��ݒ�
			_last->_prev->_next = _last;											// ���X�g�O�̎��Ɏ��g�̒ǉ�
		}

		_last->_next = NULL;														// ���X�g�̎���NULL
		_last->_tmpClass = t;														// ���g�����X�g�ɂ���

		_size++;
	}

	// ���
	void remove( T *t )
	{
		CExtra *list = NULL;
		bool del = false;

		// ���g�݂̂����X�g�ɂ���Ƃ�
		if( ( _top->getClass() == t ) && ( _last->getClass() == t ) )
		{
			SafeDelete( _top->_tmpClass );
			_top->_next = NULL;
			_top->_prev = NULL;
			SafeDelete( _top );														// ���g�̔j��

			_top = NULL;															// �擪��NULL�ɂ���
			_last = NULL;															// ���X�g��NULL�ɂ���

			del = true;
		}
		// ���g���擪�̂Ƃ�
		else if( _top->getClass() == t )
		{
			list = _top->_next;														// ���g�̎����|�C���^�Ɋi�[

			SafeDelete( _top->_tmpClass );											// ���g�̔j��
			_top->_next = NULL;
			_top->_prev = NULL;
			SafeDelete( _top );

			_top = list;															// �擪���|�C���^�̃A�h���X�ɂ���

			list->_prev = NULL;														// ���g��NULL�ɂ���

			del = true;
		}
		// ���g�����X�g�̂Ƃ�
		else if( _last->getClass() == t )
		{
			list = _last->_prev;													// ���g�̑O���|�C���^�Ɋi�[

			SafeDelete( _last->_tmpClass );											// ���g�̔j��
			_last->_next = NULL;
			_last->_prev = NULL;
			SafeDelete( _last );

			_last = list;															// ���X�g���|�C���^�̃A�h���X�ɂ���

			list->_next = NULL;														// ���g��NULL�ɂ���

			del = true;
		}
		// ���g�����X�g�ł��擪�ł��Ȃ��Ƃ�
		else
		{
			list = getLinkedList(t);
			CExtra *listNext = list->_next;											// ���g�̎����|�C���^��

			list->_prev->_next = listNext;
			listNext->_prev = list->_prev;

			SafeDelete( list->_tmpClass );
			list->_next = NULL;
			list->_prev = NULL;
			SafeDelete( list );

			del = true;
		}

		// �폜�����Ƃ�
		if( del ) _size--;
	}

	void removeList( T *t )
	{
		CExtra *list = NULL;
		CExtra *delC = NULL;
		bool del = false;

		// ���g�݂̂����X�g�ɂ���Ƃ�
		if( ( _top->getClass() == t ) && ( _last->getClass() == t ) )
		{
			delC = _top;

			_top->_tmpClass = NULL;
			_top->_next = NULL;
			_top->_prev = NULL;
			_last->_tmpClass = NULL;

			_top = NULL;															// �擪��NULL�ɂ���
			_last = NULL;															// ���X�g��NULL�ɂ���

			del = true;
		}
		// ���g���擪�̂Ƃ�
		else if( _top->getClass() == t )
		{
			delC = _top;
			list = _top->_next;														// ���g�̎����|�C���^�Ɋi�[

			_top->_tmpClass = NULL;
			_top->_next = NULL;
			_top->_prev = NULL;

			_top = list;															// �擪���|�C���^�̃A�h���X�ɂ���

			list->_prev = NULL;														// ���g��NULL�ɂ���

			del = true;
		}
		// ���g�����X�g�̂Ƃ�
		else if( _last->getClass() == t )
		{
			delC = _last;
			list = _last->_prev;													// ���g�̑O���|�C���^�Ɋi�[

			_last->_tmpClass = NULL;
			_last->_next = NULL;
			_last->_prev = NULL;

			_last = list;															// ���X�g���|�C���^�̃A�h���X�ɂ���

			list->_next = NULL;														// ���g��NULL�ɂ���

			del = true;
		}
		// ���g�����X�g�ł��擪�ł��Ȃ��Ƃ�
		else
		{
			list = getLinkedList(t);
			delC = list;

			// NULL�łȂ��Ƃ�
			if( list != NULL )
			{
				CExtra *listNext = list->_next;										// ���g�̎����|�C���^��

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

	// �N���A
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

	// ���X�g�̎擾
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