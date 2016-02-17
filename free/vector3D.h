//=============================================================================
//
// 3Dベクトル [vector3D.h]
//
//=============================================================================

//------------------------------------------------------------------------------
//	クラス定義
//------------------------------------------------------------------------------
struct VECTOR3D
{
public:
    VECTOR3D(){};
    VECTOR3D( float x, float y, float z );

    VECTOR3D& operator += ( const VECTOR3D& );
    VECTOR3D& operator -= ( const VECTOR3D& );
    VECTOR3D& operator *= ( float );
    VECTOR3D& operator /= ( float );

    VECTOR3D operator + () const;
    VECTOR3D operator - () const;

    VECTOR3D operator + ( const VECTOR3D& ) const;
    VECTOR3D operator - ( const VECTOR3D& ) const;
    VECTOR3D operator * ( float ) const;
    VECTOR3D operator / ( float ) const;

	float x, y, z;
};