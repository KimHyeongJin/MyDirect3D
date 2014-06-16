#pragma once
//d3dx9math.h 선언
//D3DX10math.inl 정의

//typedef unsigned int UINT;

typedef struct tagMatrix
{
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
}MY_D3DMATRIX;

const float EPSILON = 0.001f;

typedef struct MY_D3DXMATRIX : public MY_D3DMATRIX
{
public:
	MY_D3DXMATRIX(void);
	MY_D3DXMATRIX( const float *);
	MY_D3DXMATRIX( const MY_D3DXMATRIX& );
	MY_D3DXMATRIX( float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44 );

	//접근 허가
	float& operator()(unsigned int Row, unsigned int Col);
	float operator()(unsigned int Row, unsigned int Col) const;

	//형 변환
	operator float*();
	operator const float*() const;

	//할당 연산자
	MY_D3DXMATRIX& operator +=( const MY_D3DXMATRIX& );
	MY_D3DXMATRIX& operator -=( const MY_D3DXMATRIX& );
	MY_D3DXMATRIX& operator *=( float );
	MY_D3DXMATRIX& operator /=( float );

	//단항 연산자
	MY_D3DXMATRIX operator +() const;
	MY_D3DXMATRIX operator -() const;

	//이항 연산자
	MY_D3DXMATRIX operator +( const MY_D3DXMATRIX& ) const;
	MY_D3DXMATRIX operator -( const MY_D3DXMATRIX& ) const;
	MY_D3DXMATRIX operator *( float ) const;
	MY_D3DXMATRIX operator /( float ) const;

	bool operator == (const MY_D3DXMATRIX& ) const;
	bool operator != (const MY_D3DXMATRIX& ) const;

	friend MY_D3DXMATRIX operator*(float, const MY_D3DXMATRIX& );

}MY_D3DXMATRIX, *LPMY_D3DXMATRIX;

MY_D3DXMATRIX::MY_D3DXMATRIX(void)
{
	//memcpy( &_11, 0, sizeof(MY_D3DXMATRIX) );
}

MY_D3DXMATRIX::MY_D3DXMATRIX( const float * p)
{	
	memcpy( &_11, p, sizeof(MY_D3DXMATRIX) );
}

MY_D3DXMATRIX::MY_D3DXMATRIX( const MY_D3DXMATRIX& m)
{
	memcpy( &_11, &m, sizeof(MY_D3DXMATRIX) );
}

MY_D3DXMATRIX::MY_D3DXMATRIX( float _11, float _12, float _13, float _14,
							 float _21, float _22, float _23, float _24,
							 float _31, float _32, float _33, float _34,
							 float _41, float _42, float _43, float _44 )
{
	m[0][0] =_11;
	m[0][1] =_12;
	m[0][2] =_13;
	m[0][3] =_14;

	m[1][0] =_21;
	m[1][1] =_22;
	m[1][2] =_23;
	m[1][3] =_24;

	m[2][0] =_31;
	m[2][1] =_32;
	m[2][2] =_33;
	m[2][3] =_34;

	m[3][0] =_41;
	m[3][1] =_42;
	m[3][2] =_43;
	m[3][3] =_44;
}



//접근 허가
float& MY_D3DXMATRIX::operator()(unsigned int Row, unsigned int Col)
{
	return m[Row][Col];
}
float MY_D3DXMATRIX::operator()(unsigned int Row, unsigned int Col) const
{
	return m[Row][Col];
}


//형 변환
MY_D3DXMATRIX::operator float*()
{
	return (float *)&_11;
}

MY_D3DXMATRIX::operator const float*() const
{
	return (const float *)&_11;
}

//할당 연산자
MY_D3DXMATRIX& MY_D3DXMATRIX::operator +=( const MY_D3DXMATRIX& mat)
{
	m[0][0] +=mat._11;
	m[0][1] +=mat._12;
	m[0][2] +=mat._13;
	m[0][3] +=mat._14;

	m[1][0] +=mat._21;
	m[1][1] +=mat._22;
	m[1][2] +=mat._23;
	m[1][3] +=mat._24;

	m[2][0] +=mat._31;
	m[2][1] +=mat._32;
	m[2][2] +=mat._33;
	m[2][3] +=mat._34;

	m[3][0] +=mat._41;
	m[3][1] +=mat._42;
	m[3][2] +=mat._43;
	m[3][3] +=mat._44;
	return *this;
}
MY_D3DXMATRIX& MY_D3DXMATRIX::operator -=( const MY_D3DXMATRIX& mat )
{
	m[0][0] -=mat._11;
	m[0][1] -=mat._12;
	m[0][2] -=mat._13;
	m[0][3] -=mat._14;

	m[1][0] -=mat._21;
	m[1][1] -=mat._22;
	m[1][2] -=mat._23;
	m[1][3] -=mat._24;

	m[2][0] -=mat._31;
	m[2][1] -=mat._32;
	m[2][2] -=mat._33;
	m[2][3] -=mat._34;

	m[3][0] -=mat._41;
	m[3][1] -=mat._42;
	m[3][2] -=mat._43;
	m[3][3] -=mat._44;
	return *this;
}
MY_D3DXMATRIX& MY_D3DXMATRIX::operator *=( float f )
{
	m[0][0] *=f;
	m[0][1] *=f;
	m[0][2] *=f;
	m[0][3] *=f;

	m[1][0] *=f;
	m[1][1] *=f;
	m[1][2] *=f;
	m[1][3] *=f;

	m[2][0] *=f;
	m[2][1] *=f;
	m[2][2] *=f;
	m[2][3] *=f;

	m[3][0] *=f;
	m[3][1] *=f;
	m[3][2] *=f;
	m[3][3] *=f;
	return *this;
}
MY_D3DXMATRIX& MY_D3DXMATRIX::operator /=( float f )
{
	float fInv = 1.0f / f;
	clock_t start_time, end_time;      // clock_t 
	start_time = clock();              // Start_Time	
	m[0][0] *=fInv;
	m[0][1] *=fInv;
	m[0][2] *=fInv;
	m[0][3] *=fInv;

	m[1][0] *=fInv;
	m[1][1] *=fInv;
	m[1][2] *=fInv;
	m[1][3] *=fInv;

	m[2][0] *=fInv;
	m[2][1] *=fInv;
	m[2][2] *=fInv;
	m[2][3] *=fInv;

	m[3][0] *=fInv;
	m[3][1] *=fInv;
	m[3][2] *=fInv;
	m[3][3] *=fInv;

	//m[0][0] /=f;
	//m[0][1] /=f;
	//m[0][2] /=f;
	//m[0][3] /=f;

	//m[1][0] /=f;
	//m[1][1] /=f;
	//m[1][2] /=f;
	//m[1][3] /=f;

	//m[2][0] /=f;
	//m[2][1] /=f;
	//m[2][2] /=f;
	//m[2][3] /=f;

	//m[3][0] /=f;
	//m[3][1] /=f;
	//m[3][2] /=f;
	//m[3][3] /=f;
	end_time = clock();
	printf("Time : %d  %d\n", end_time, start_time); 
	printf("Time : %f\n", ((double)(end_time-start_time))/* / CLOCKS_PER_SEC*/); 

	return *this;
}

//단항 연산자
MY_D3DXMATRIX MY_D3DXMATRIX::operator +() const
{
	return *this;
}

MY_D3DXMATRIX MY_D3DXMATRIX::operator -() const
{
	return MY_D3DXMATRIX(-_11, -_12, -_13, -_14, 
							-_21, -_22, -_23, -_24,
							-_31, -_32, -_33, -_34,
							-_41, -_42, -_43, -_44);
}

//이항 연산자
MY_D3DXMATRIX MY_D3DXMATRIX::operator +( const MY_D3DXMATRIX& mat ) const
{
	return MY_D3DXMATRIX(_11+mat._11, _12+mat._12, _13+mat._13, _14+mat._14,
						_21+mat._21, _22+mat._22, _23+mat._23, _24+mat._24,
						_31+mat._31, _32+mat._32, _33+mat._33, _34+mat._34,
						_41+mat._41, _42+mat._42, _43+mat._43, _44+mat._44);
}
MY_D3DXMATRIX MY_D3DXMATRIX::operator -( const MY_D3DXMATRIX& mat ) const
{
	return MY_D3DXMATRIX(_11-mat._11, _12-mat._12, _13-mat._13, _14-mat._14,
						_21-mat._21, _22-mat._22, _23-mat._23, _24-mat._24,
						_31-mat._31, _32-mat._32, _33-mat._33, _34-mat._34,
						_41-mat._41, _42-mat._42, _43-mat._43, _44-mat._44);
}
MY_D3DXMATRIX MY_D3DXMATRIX::operator *( float f ) const
{
	return MY_D3DXMATRIX(_11*f, _12*f, _13*f, _14*f,
						_21*f, _22*f, _23*f, _24*f,
						_31*f, _32*f, _33*f, _34*f,
						_41*f, _42*f, _43*f, _44*f);
}
MY_D3DXMATRIX MY_D3DXMATRIX::operator /( float f ) const
{
	float fInv = 1.0f/f;
	return MY_D3DXMATRIX(_11*fInv, _12*fInv, _13*fInv, _14*fInv,
						_21*fInv, _22*fInv, _23*fInv, _24*fInv,
						_31*fInv, _32*fInv, _33*fInv, _34*fInv,
						_41*fInv, _42*fInv, _43*fInv, _44*fInv);
}

bool MY_D3DXMATRIX::operator == ( const MY_D3DXMATRIX& mat ) const
{
	return 0 == memcmp( this, &mat, sizeof(MY_D3DXMATRIX) );
}
bool MY_D3DXMATRIX::operator != (const MY_D3DXMATRIX& mat ) const
{
	return 0 != memcmp( this, &mat, sizeof(MY_D3DXMATRIX) );
}

MY_D3DXMATRIX operator*(float f, const MY_D3DXMATRIX& mat )
{
	return MY_D3DXMATRIX(f*mat._11, f*mat._12, f*mat._13, f*mat._14,
						f*mat._21, f*mat._22, f*mat._23, f*mat._24,
						f*mat._31, f*mat._32, f*mat._33, f*mat._34,
						f*mat._41, f*mat._42, f*mat._43, f*mat._44);
}


MY_D3DXMATRIX* D3DXMatrixTranslation( MY_D3DXMATRIX* pOut, float x, float y, float z)
{
	MY_D3DXMATRIX temp = *pOut;
	MY_D3DXMATRIX normalize(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1);

	pOut->_11 = temp._11 * normalize._11 + 
				temp._12 * normalize._21 +
				temp._13 * normalize._31 + 
				temp._14 * normalize._41;


	pOut->_12 = temp._11 * normalize._12 + 
				temp._12 * normalize._22 +
				temp._13 * normalize._32 + 
				temp._14 * normalize._42;

	pOut->_13 = temp._11 * normalize._13 + 
				temp._12 * normalize._23 +
				temp._13 * normalize._33 + 
				temp._14 * normalize._43;

	pOut->_14 = temp._11 * normalize._14 + 
				temp._12 * normalize._24 +
				temp._13 * normalize._34 + 
				temp._14 * normalize._44;

	pOut->_21 = temp._11 * normalize._11 + 
				temp._12 * normalize._21 +
				temp._13 * normalize._31 + 
				temp._14 * normalize._41;


	pOut->_22 = temp._21 * normalize._12 + 
				temp._22 * normalize._22 +
				temp._23 * normalize._32 + 
				temp._24 * normalize._42;

	pOut->_23 = temp._21 * normalize._13 + 
				temp._22 * normalize._23 +
				temp._23 * normalize._33 + 
				temp._24 * normalize._43;

	pOut->_24 = temp._21 * normalize._14 + 
				temp._22 * normalize._24 +
				temp._23 * normalize._34 + 
				temp._24 * normalize._44;

	pOut->_31 = temp._31 * normalize._11 + 
				temp._32 * normalize._21 +
				temp._33 * normalize._31 + 
				temp._34 * normalize._41;


	pOut->_32 = temp._31 * normalize._12 + 
				temp._32 * normalize._22 +
				temp._33 * normalize._32 + 
				temp._34 * normalize._42;

	pOut->_33 = temp._31 * normalize._13 + 
				temp._32 * normalize._23 +
				temp._33 * normalize._33 + 
				temp._34 * normalize._43;

	pOut->_34 = temp._31 * normalize._14 + 
				temp._32 * normalize._24 +
				temp._33 * normalize._34 + 
				temp._34 * normalize._44;

	pOut->_41 = temp._41 * normalize._11 + 
				temp._42 * normalize._21 +
				temp._43 * normalize._31 + 
				temp._44 * normalize._41;


	pOut->_42 = temp._41 * normalize._12 + 
				temp._42 * normalize._22 +
				temp._43 * normalize._32 + 
				temp._44 * normalize._42;

	pOut->_43 = temp._41 * normalize._13 + 
				temp._42 * normalize._23 +
				temp._43 * normalize._33 + 
				temp._44 * normalize._43;

	pOut->_44 = temp._41 * normalize._14 + 
				temp._42 * normalize._24 +
				temp._43 * normalize._34 + 
				temp._44 * normalize._44;

	return pOut;
}