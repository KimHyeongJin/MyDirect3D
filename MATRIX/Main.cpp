// VECTOR.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	float* pFlt = (float *)&arr[0];//���� �ּҸ� float*�� ĳ������ float* �����Ϳ� �Ҵ�
	printf("float %f  %f  %f",pFlt[0],pFlt[1],pFlt[2]);//�׸��� float*�� �Ҵ� ���� int���� float������ �ٲ�
	//"float* �����Ͱ� ����Ű�°� float���̴�" ��� �ܼ��� ����???.
	//arr �迭�� ��� ���Ҹ� float������ ����ȯ ���� �ʰ��� ��� ���Ұ� ����ȯ�� �ȰŰ��� ȿ��~!
	return 0;
}
/*
1.#INF means +��. If you divide by 0, that is the result

lim (��n/x) = ����
x��0

0(Theta) : ������ �˰� �ִ� ����
a : Theta���� �߰��� ����

Z�� ������ ȸ��(Rotation)
x	= r*cos(0+a)
	= r*( cos(0)*cos(a) - sin(0)*sin(a) )  
	= x*( r*cos(a)) - y*(r*sin(a) )

��� ������ r*cos(0), y*sin(0)�� ������ (x, y) ��ǥ�� ��Ÿ����.
�׷��Ƿ� x*cos(a) - y*sin(a) �������� ������ �̷� �������� ���ü� �ִ� 4*4����� �����غ��� �Ʒ��� ����.
(x, y, 0, 0)
* 
cos(a)	0	0	0
-sin(a)	1	0	0
0		0	1	0
0		0	0	1

y	= r*sin(0+a)
	= r*( sin(0)*cos(a) + cos(0)*sin(a) )
	= y*( r*cos(a)) + x*(r*sin(a) )
��� ������ r*cos(0), r*sin(0) �� ������ (x, y) ��ǥ�� ��Ÿ����.
(x, y, 0, 0)
* 
cos(a)	sin(a)	0	0
-sin(a)	cos(0)	0	0
0		0		1	0
0		0		0	1

�̷��� ���� 0��ŭ ȸ����ų�� �� ����� �����Ͽ� ����� �� �ִ�.
                z
cos(a)	sin(a)	0	0
-sin(a)	cos(0)	0	0
0		0		1	0 z
0		0		0	1

z�� ȸ���ϰ�� z ��� ���� ����д�.
y�� ȸ���ϰ�� y ��� ���� �������.
x�൵ ��������
*/

