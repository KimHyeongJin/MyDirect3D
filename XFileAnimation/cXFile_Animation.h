#pragma once

#include <vector>
#include "cXFile_Object.h"


struct BONE : public D3DXFRAME
{
	D3DXMATRIXA16 m_matCombinedFrame;							// 프레임을 구성할 매트릭스
};


struct BONEMESH: public D3DXMESHCONTAINER
{
	tagXFileInfo					m_sXFileInfo;
	DWORD							m_NumAttributeGroups;
	D3DXATTRIBUTERANGE*				m_AttributeTable;
	D3DXMATRIXA16**					m_BoneMatrixPtrs;
	D3DXMATRIXA16*					m_BoneOffsetMatrices;
	D3DXMATRIXA16*					m_CurrentBoneMatrices;

	void	clear(void);															// 초기화
};


class BONE_HIERARCHY: public ID3DXAllocateHierarchy
{
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR lpszName, LPD3DXFRAME* ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR lpszName, CONST D3DXMESHDATA* pMeshData, CONST D3DXMATERIAL* pMaterials, CONST D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials, CONST DWORD* pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);

	HRESULT		FileNameCopy(LPSTR* lppszDest, LPCSTR lpszSrc);		
};

class cXFile_Animation 
	: public cXFile_Object
{
public:
	cXFile_Animation(void);
	virtual ~cXFile_Animation(void);
private:
	D3DXFRAME*					m_pRootBone;			
	ID3DXAnimationSet*			m_pCurrentAni;			
	ID3DXAnimationController*	m_pAnimControl;			

	DWORD						m_dwNowAni;
	int							m_nCurrentAniPeriod;
	
	float						m_fFrame;

private:
	void			SetUpBoneTree(BONE* pBone);
	void			UpdateMatrix(BONE* pBone, D3DXMATRIXA16* pmatParent);
	void			AnimTransLoop(float fDT = 0.0f);
public:
	HRESULT			Load( LPDIRECT3DDEVICE9 pd3dDevice, std::string strFileName, float fFrame = 25.f, D3DXMATRIXA16* pmatParent = NULL); // 파일로드
	void			SetAniMation(DWORD dwTrack);
	DWORD			GetAniMation(void);
	
	virtual			HRESULT		Render(float fDT = 1.0f, BONE* pBone = NULL);
	
	void			Release(void);

	void			SetFrame(float fFrame = 25.0f);				
};
