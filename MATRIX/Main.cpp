// VECTOR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MY_D3DXMATRIX.h"

using namespace std;

void ShowMetrix( MY_D3DXMATRIX &m )
{
	
	for ( int row = 0 ; row < 4 ; row++ )
	{
		for ( int col = 0 ; col < 4 ; col++ )
		{
			cout<<setw(5)<<"[_"<<row+1<<""<<col+1<<"] : "<<setw(4)<<m.m[row][col]<<"   ";
		}
		cout<<endl;
	}
	cout<<endl;
}



int _tmain(int argc, _TCHAR* argv[])
{
	MY_D3DXMATRIX mat1(0,0,3,0,
		1,2,3,4,
		5,6,7,8,
		9,10,11,12);
	MY_D3DXMATRIX mat2(0,3,0,1,
		3,4,1,6,
		0,0,0,0,
		1,2,1,1);
	MY_D3DXMATRIX destMat;

	MY_D3DXMATRIX cpy = mat2;
	ShowMetrix(cpy);
	destMat = mat1+mat2;

	ShowMetrix(destMat);

	//sMY_D3DXMATRIX destMat2;
	destMat /= 5;
	//D3DXMatrixTranslation(&destMat, 10,20,30);
	ShowMetrix(destMat);


	float flt = 100;
	float flt2 = flt/0;
	cout<<flt2<<endl;

	int arr[5]={1,2,3,4,5};
	float* pFlt = (float *)&arr[0];//시작 주소를 float*로 캐스팅후 float* 포인터에 할당
	printf("float %f  %f  %f",pFlt[0],pFlt[1],pFlt[2]);//그리고 float*에 할당 된후 int형이 float형으로 바뀜
	//"float* 포인터가 가리키는건 float형이다" 라는 단순한 원리???.
	//arr 배열의 모든 원소를 float형으로 형변환 하지 않고서도 모든 원소가 형변환이 된거같은 효과~!
	return 0;
}
/*
1.#INF means +∞. If you divide by 0, that is the result

lim (±n/x) = ±∞
x→0

0(Theta) : 기존에 알고 있던 각도
a : Theta에서 추가된 각도

Z축 정점의 회전(Rotation)
x	= r*cos(0+a)
	= r*( cos(0)*cos(a) - sin(0)*sin(a) )  
	= x*( r*cos(a)) - y*(r*sin(a) )

결과 적으로 r*cos(0), y*sin(0)는 기존의 (x, y) 좌표를 나타낸다.
그러므로 x*cos(a) - y*sin(a) 방정식이 나오고 이런 방정식이 나올수 있는 4*4행렬을 유추해보면 아래와 같다.
(x, y, 0, 0)
* 
cos(a)	0	0	0
-sin(a)	1	0	0
0		0	1	0
0		0	0	1

y	= r*sin(0+a)
	= r*( sin(0)*cos(a) + cos(0)*sin(a) )
	= y*( r*cos(a)) + x*(r*sin(a) )
결과 적으로 r*cos(0), r*sin(0) 는 기존의 (x, y) 좌표를 나타낸다.
(x, y, 0, 0)
* 
cos(a)	sin(a)	0	0
-sin(a)	cos(0)	0	0
0		0		1	0
0		0		0	1

이렇게 점을 0만큼 회전시킬때 위 행렬을 적용하여 사용할 수 있다.
                z
cos(a)	sin(a)	0	0
-sin(a)	cos(0)	0	0
0		0		1	0 z
0		0		0	1

z축 회전일경우 z 행과 열은 비워둔다.
y축 회전일경우 y 행과 열도 비워돈다.
x축도 마찬가지
*/

