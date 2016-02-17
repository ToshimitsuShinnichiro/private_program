//==============================================================================
//
// FineName [ RandLCG.h ]
// Author : Shinichiro Toshimitsu
//
//==============================================================================
#ifndef _RANDLCG_H_
#define _RANDLCG_H_

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
class CRandLCG
{
public:
	CRandLCG();
	~CRandLCG();

	int getRand( int min, int max );

private:
	unsigned int a, b;
	unsigned int seed;
};

#endif

/* ----- EOF ----- */