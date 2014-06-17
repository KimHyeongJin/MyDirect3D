#include "StdAfx.h"
#include "cXFile_Animation.h"

cXFile_Animation::cXFile_Animation(void)
:m_pRootBone(NULL), m_pCurrentAni(NULL), m_pAnimControl(NULL), m_fFrame(0), m_dwNowAni(0)
{
}

cXFile_Animation::~cXFile_Animation(void)
{
}
														
void BONEMESH::clear(void)
{
	Name						= NULL;
	MeshData.pPMesh 			= NULL;
	pMaterials					= NULL;
	pEffects					= NULL;
	pAdjacency					= NULL;
	pSkinInfo					= NULL;
	pNextMeshContainer			= NULL;
	m_sXFileInfo.pMesh			= NULL;
	m_AttributeTable			= NULL;
	m_BoneMatrixPtrs			= NULL;
	m_BoneOffsetMatrices		= NULL;
	m_CurrentBoneMatrices		= NULL;

	m_NumAttributeGroups = NumMaterials = 0;

	MeshData.Type = D3DXMESHTYPE_MESH;					// 매쉬데이터타입은 일반매쉬사용
}

HRESULT	BONE_HIERARCHY::FileNameCopy(LPSTR* lppszDest, LPCSTR lpszSrc)
{
	if( lpszSrc )
	{
		size_t szLength = strlen(lpszSrc) + 1;
		*lppszDest = new CHAR[szLength];

		if( lppszDest == NULL )
			return E_OUTOFMEMORY;								// 메모리할당실패

		strcpy_s(*lppszDest, szLength, lpszSrc);
	}
	else
		lppszDest = NULL;

	return S_OK;
}

HRESULT BONE_HIERARCHY::CreateFrame(LPCSTR lpszName, LPD3DXFRAME* ppNewFrame)
{
	BONE *pBone = new BONE;
	pBone->Name = NULL;
	pBone->pFrameFirstChild = NULL;
	pBone->pFrameSibling = NULL;
	pBone->pMeshContainer = NULL;
	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->m_matCombinedFrame);

	FileNameCopy(&pBone->Name, lpszName);				// 프레임명복사

	*ppNewFrame = (D3DXFRAME*)pBone;

	return S_OK;
}

HRESULT BONE_HIERARCHY::CreateMeshContainer(LPCSTR lpszName,
											CONST D3DXMESHDATA *pMeshData,
											CONST D3DXMATERIAL *pMaterials,
											CONST D3DXEFFECTINSTANCE *pEffectInstances,
											DWORD NumMaterials,
											CONST DWORD *pAdjacency,
											LPD3DXSKININFO pSkinInfo,
											LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	BONEMESH* pBoneMesh = new BONEMESH;
	pBoneMesh->clear();

	pBoneMesh->m_sXFileInfo.pMesh = pMeshData->pMesh;
	pBoneMesh->m_sXFileInfo.pMesh->AddRef();			

	FileNameCopy(&pBoneMesh->Name,lpszName);

	pBoneMesh->NumMaterials = NumMaterials;

	for( size_t i = 0 ; i < NumMaterials ; i++)
	{
		// 여기부터 재질정보 저장하기
		D3DMATERIAL9 TempMtrl;
		memcpy(&TempMtrl, &pMaterials[i].MatD3D, sizeof(D3DMATERIAL9));		
		TempMtrl.Ambient	= TempMtrl.Diffuse;
		pBoneMesh->m_sXFileInfo.vecMaterials.push_back(TempMtrl);				

		// 여기까지 재질정보 저장하기

		// 여기부터 텍스쳐정보 저장하기
		LPDIRECT3DTEXTURE9		pTexture = NULL;

		if( pMaterials[i].pTextureFilename )
		{
			D3DXCreateTextureFromFile(
				m_pd3dDevice, 
				pMaterials[i].pTextureFilename, 
				&pTexture);
		}

		pBoneMesh->m_sXFileInfo.vecTextures.push_back(pTexture);		// Temp에 저장된 텍스쳐 저장
	}
	// 여기까지 텍스쳐정보 저장하기

	LPDIRECT3DDEVICE9 pd3dDevice = NULL;
	pMeshData->pMesh->GetDevice(&pd3dDevice);			// 매쉬 디바이스 얻기
	
	if( pSkinInfo )
	{
		// 본매쉬스킨정보에 스킨정보 저장
		pBoneMesh->pSkinInfo = pSkinInfo;	
		pBoneMesh->pSkinInfo->AddRef();		
		
		pMeshData->pMesh->CloneMeshFVF(D3DXMESH_MANAGED, pMeshData->pMesh->GetFVF(), 
			pd3dDevice, &pBoneMesh->MeshData.pMesh);	// 매쉬 데이터 읽어오기
		pBoneMesh->MeshData.Type = pMeshData->Type;

		// 본 갯수만큼 할당
		size_t nBone = pSkinInfo->GetNumBones();
		pBoneMesh->m_BoneOffsetMatrices		= new D3DXMATRIXA16[nBone];
		pBoneMesh->m_CurrentBoneMatrices	= new D3DXMATRIXA16[nBone];
		
		// 본 오프셋 복사
		for( size_t i = 0 ; i < nBone ; i++ )
			pBoneMesh->m_BoneOffsetMatrices[i] = *(pBoneMesh->pSkinInfo->GetBoneOffsetMatrix(i));
	}

	*ppNewMeshContainer = pBoneMesh;		// 본메쉬 저장

	pd3dDevice->Release();					// 매쉬디바이스 삭제

	return S_OK;
}
HRESULT BONE_HIERARCHY::DestroyFrame(LPD3DXFRAME pFrameToFree) 
{
	delete [] pFrameToFree->Name;
	delete pFrameToFree;

	return S_OK; 
}
HRESULT BONE_HIERARCHY::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	BONEMESH *boneMesh = (BONEMESH*)pMeshContainerBase;

	delete [] boneMesh->Name;
	delete [] boneMesh->pAdjacency;
	delete [] boneMesh->m_BoneMatrixPtrs;
	delete [] boneMesh->m_BoneOffsetMatrices;
	delete [] boneMesh->m_CurrentBoneMatrices;
	delete [] boneMesh->m_AttributeTable;
	delete [] boneMesh->pMaterials;

	// 텍스쳐 삭제
	for(UINT i=0;i < boneMesh->m_sXFileInfo.vecTextures.size();i++)
	{
		if( boneMesh->m_sXFileInfo.vecTextures[i] )
		{
			boneMesh->m_sXFileInfo.vecTextures[i]->Release();
		}
	}

	// 매쉬정보 삭제
	boneMesh->MeshData.pMesh->Release();
	boneMesh->pSkinInfo->Release();
	boneMesh->m_sXFileInfo.pMesh->Release();

	delete boneMesh;

	return S_OK;
}

HRESULT cXFile_Animation::Load( LPDIRECT3DDEVICE9 pd3dDevice, std::string strFileName, float fFrame, D3DXMATRIXA16* pmatParent)
{
	if( strFileName.c_str() == NULL || 
		pd3dDevice == NULL )
	{
		return S_FALSE;
	}

	m_szFileName	= strFileName;
	m_pd3dDevice	= pd3dDevice;

	BONE_HIERARCHY	Bone_Hierarchy;

	HRESULT hr = D3DXLoadMeshHierarchyFromXA(
		m_szFileName.c_str(), 
		D3DXMESH_MANAGED, 
		m_pd3dDevice,
		&Bone_Hierarchy, 
		NULL, 
		&m_pRootBone, 
		&m_pAnimControl );

	if( hr == D3DERR_INVALIDCALL ||
		hr == E_OUTOFMEMORY )		
	{
		return hr;
	}

	m_pMatParent = pmatParent;

	SetUpBoneTree((BONE*)m_pRootBone);

	if( m_pAnimControl )
	{
		m_pAnimControl->AdvanceTime(0, NULL);		
	}
													
	UpdateMatrix((BONE*)m_pRootBone, m_pMatParent);

	SetAniMation(0);

	m_fFrame = fFrame / 10000000;

	return S_OK;
}
void		cXFile_Animation::SetAniMation(DWORD dwTrack)
{
	if( m_pAnimControl == NULL )
	{
		return;
	}

	if ( m_pAnimControl->GetNumAnimationSets() <= (unsigned)dwTrack ) 
	{
		return;
	}

	m_pAnimControl->GetAnimationSet(dwTrack, &m_pCurrentAni);				// 애니메이션 컨테이너 지정
	
	m_nCurrentAniPeriod = (int)m_pCurrentAni->GetPeriod();

	m_pAnimControl->SetTrackAnimationSet(0, m_pCurrentAni);
	m_pAnimControl->SetTrackPosition(0, 0.0f);
	m_pAnimControl->ResetTime();

	m_dwNowAni = dwTrack;
}

DWORD		cXFile_Animation::GetAniMation(void)
{
	return m_dwNowAni;
}


void		cXFile_Animation::AnimTransLoop(float fDT)
{
 	if( m_pAnimControl )
	{
 		m_pAnimControl->AdvanceTime(fDT, NULL);
	}

	UpdateMatrix((BONE*)m_pRootBone, m_pMatParent);
}

HRESULT	cXFile_Animation::Render(float fDT, BONE* pBone)
{
	AnimTransLoop(m_fFrame / fDT);

	if( pBone == NULL )
	{
		pBone = (BONE*)m_pRootBone;
	}

	// 랜더하기전에 애니메이션에 따른 변환부터.
	if(pBone->pMeshContainer)
	{
		BONEMESH* pBoneMesh = (BONEMESH*)pBone->pMeshContainer;

		if( pBoneMesh->pSkinInfo )
		{
			size_t nBone = pBoneMesh->pSkinInfo->GetNumBones();

			// 본 행렬 변환
			for( size_t i = 0 ; i < nBone ; i++ )
			{
				pBoneMesh->m_CurrentBoneMatrices[i]	=	
					pBoneMesh->m_BoneOffsetMatrices[i] * (*pBoneMesh->m_BoneMatrixPtrs[i]);
			}

			// 매쉬 업데이트
			void	*Src	= NULL;
			void	*Dest	= NULL;

			pBoneMesh->m_sXFileInfo.pMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&Src);
			
			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&Dest);

			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->m_CurrentBoneMatrices, NULL, Src, Dest);

			pBoneMesh->m_sXFileInfo.pMesh->UnlockVertexBuffer();
		}

		for( size_t i = 0 ; i < pBoneMesh->m_sXFileInfo.vecMaterials.size() ; ++i )
		{
			if(FAILED(m_pd3dDevice->SetMaterial( &pBoneMesh->m_sXFileInfo.vecMaterials[i])))							return E_FAIL;
			if(FAILED(m_pd3dDevice->SetTexture(0, pBoneMesh->m_sXFileInfo.vecTextures[i])))							return E_FAIL;

			if( pBoneMesh->pSkinInfo )
			{	
				SetMatrix();
				pBoneMesh->MeshData.pMesh->DrawSubset( i );
			}
			else
			{
				m_pd3dDevice->SetTransform( D3DTS_WORLD, &pBone->m_matCombinedFrame);
				pBoneMesh->m_sXFileInfo.pMesh->DrawSubset( i );
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////////////
	if(pBone->pFrameSibling)	
	{
		Render( fDT,(BONE*)pBone->pFrameSibling );
	}

	if(pBone->pFrameFirstChild)	
	{
		Render( fDT,(BONE*)pBone->pFrameFirstChild );
	}

	return m_pd3dDevice->SetTexture(0, NULL);
}

void		cXFile_Animation::UpdateMatrix(BONE* pBone, D3DXMATRIXA16* pmatParent)
{
	if( pBone == NULL )
		return;

	if( pmatParent == NULL )
	{
		pBone->m_matCombinedFrame	=	pBone->TransformationMatrix;
	}
	else
	{
		pBone->m_matCombinedFrame	=	pBone->TransformationMatrix * (*pmatParent);
	}

	////////////////////////////////////////////////////////////////////////////////////
	if(pBone->pFrameSibling)		
	{
		UpdateMatrix((BONE*)pBone->pFrameSibling, pmatParent);
	}

	if(pBone->pFrameFirstChild)		
	{
		UpdateMatrix((BONE*)pBone->pFrameFirstChild, &pBone->m_matCombinedFrame);
	}
}

void		cXFile_Animation::SetUpBoneTree(BONE* pBone)
{
	if( pBone->pMeshContainer )
	{
		BONEMESH* pBoneMesh = (BONEMESH*)pBone->pMeshContainer;

		if( pBoneMesh->pSkinInfo )
		{
			size_t nBone = pBoneMesh->pSkinInfo->GetNumBones();
			
			pBoneMesh->m_BoneMatrixPtrs = new D3DXMATRIXA16*[nBone];

			for( size_t i = 0 ; i < nBone ; i++ )
			{
				BONE* pTemp = (BONE*)D3DXFrameFind(m_pRootBone, pBoneMesh->pSkinInfo->GetBoneName(i));
				if( pTemp )	
				{
					pBoneMesh->m_BoneMatrixPtrs[i] = &pTemp->m_matCombinedFrame;
				}

				else		
				{
					pBoneMesh->m_BoneMatrixPtrs[i] = NULL;
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	// 프레임 순환
	if( pBone->pFrameSibling )		
	{
		SetUpBoneTree((BONE*)pBone->pFrameSibling);
	}

	if( pBone->pFrameFirstChild )	
	{
		SetUpBoneTree((BONE*)pBone->pFrameFirstChild);
	}
}

void		cXFile_Animation::Release(void)
{
	if ( m_pRootBone )
	{
		BONE_HIERARCHY boneHierarchy;
		D3DXFrameDestroy( m_pRootBone, &boneHierarchy);
	}

	m_pRootBone = NULL;

	SAFE_RELEASE(m_pCurrentAni);
	SAFE_RELEASE(m_pAnimControl);
}

void		cXFile_Animation::SetFrame(float fFrame)
{
	m_fFrame = fFrame / 10000000;
}