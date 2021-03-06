#pragma once

class cMtlTex;

struct ST_BONE : public D3DXFRAME
{
	//D3DXMATRIX matWorldTM;
	D3DXMATRIX CombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<cMtlTex*>	vecMtlTex;
	LPD3DXMESH				pOrigMesh;				// 원본 메쉬

	LPD3DXMESH				pWorkMesh;				// 작푳E메쉬 CloneMeshFVF로 복퍊E
	D3DXMATRIX**			ppBoneMatrixPtrs;		// 이 메쉬에 영향을 주는 프레임'탛E의 월드매트릭스 포인터 배열
	D3DXMATRIX*				pBoneOffsetMatrices;	// 원본 메쉬를 로컬스페이스로 보내는 매트릭스탛E
	D3DXMATRIX*				pCurrentBoneMatrices;	// 각 본의 계퍊E?월드매트릭스
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
protected:
	std::string m_sFolder;

public:
	cAllocateHierarchy(void);
	~cAllocateHierarchy(void);

	void SetFolder(std::string sFolder) { m_sFolder = sFolder; }

	// ID3DXAllocateHierarchy

	//------------------------------------------------------------------------
	// CreateFrame:
	// ------------
	// Requests allocation of a frame object.
	//
	// Parameters:
	//  Name
	//		Name of the frame to be created
	//	ppNewFrame
	//		Returns the created frame object
	//
	//------------------------------------------------------------------------
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, 
		LPD3DXFRAME *ppNewFrame);

	//------------------------------------------------------------------------
	// CreateMeshContainer:
	// --------------------
	// Requests allocation of a mesh container object.
	//
	// Parameters:
	//  Name
	//		Name of the mesh
	//	pMesh
	//		Pointer to the mesh object if basic polygon data found
	//	pPMesh
	//		Pointer to the progressive mesh object if progressive mesh data found
	//	pPatchMesh
	//		Pointer to the patch mesh object if patch data found
	//	pMaterials
	//		Array of materials used in the mesh
	//	pEffectInstances
	//		Array of effect instances used in the mesh
	//	NumMaterials
	//		Num elements in the pMaterials array
	//	pAdjacency
	//		Adjacency array for the mesh
	//	pSkinInfo
	//		Pointer to the skininfo object if the mesh is skinned
	//	pBoneNames
	//		Array of names, one for each bone in the skinned mesh. 
	//		The numberof bones can be found from the pSkinMesh object
	//	pBoneOffsetMatrices
	//		Array of matrices, one for each bone in the skinned mesh.
	//
	//------------------------------------------------------------------------
	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	//------------------------------------------------------------------------
	// DestroyFrame:
	// -------------
	// Requests de-allocation of a frame object.
	//
	// Parameters:
	//  pFrameToFree
	//		Pointer to the frame to be de-allocated
	//
	//------------------------------------------------------------------------
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree); 

	//------------------------------------------------------------------------
	// DestroyMeshContainer:
	// ---------------------
	// Requests de-allocation of a mesh container object.
	//
	// Parameters:
	//  pMeshContainerToFree
	//		Pointer to the mesh container object to be de-allocated
	//
	//------------------------------------------------------------------------
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree); 
};

