#include "objects.h"

#include <d3d9.h>
#include <d3dx9.h>

//---------------------------------------------------------------------------------------------------------------------
HRESULT
CreateTorus(IDirect3DDevice9* pDevice, 
			int iSegments1, int iSegments2, float fRadius1, float fRadius2, 
			int* piNumVerticesOut, int* piNumTrianglesOut, int* piVertexSizeOut,
			IDirect3DVertexDeclaration9** ppVertexDeclarationOut,
			IDirect3DVertexBuffer9** ppVertexBufferOut,
			IDirect3DIndexBuffer9**	ppIndexBufferOut)
{
	HRESULT hr;

	int iNumVertices = (iSegments1 + 1) * (iSegments2 + 1);
	int iNumTriangles = iSegments1 * iSegments2 * 2;


	struct TTorusVertex
	{
		D3DXVECTOR3 vPosition;
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 vTangent;
		D3DXVECTOR3 vBinormal;
		D3DCOLOR	dwColor;
		D3DXVECTOR2 vTexCoord;
	};

	int iVertexSize = sizeof(TTorusVertex);


	// create vertex declaration
	D3DVERTEXELEMENT9 axVertexElements[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
		{ 0, 36, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		{ 0, 48, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,	  0 },
		{ 0, 52, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	IDirect3DVertexDeclaration9* pVertexDeclaration;
	hr = pDevice->CreateVertexDeclaration(axVertexElements, &pVertexDeclaration);
	if (FAILED(hr)) return hr;


	// create vertex buffer
	IDirect3DVertexBuffer9* pVertexBuffer;
	hr = pDevice->CreateVertexBuffer(
			sizeof(TTorusVertex) * iNumVertices, 
			D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, 
			&pVertexBuffer, NULL);
	if (FAILED(hr)) return hr;

	TTorusVertex* pVertexArray;
	pVertexBuffer->Lock(0, 0, (void**)&pVertexArray, 0);

	int iV = 0;

    for (int i = 0; i <= iSegments1; i++)
	{
		for (int j = 0; j <= iSegments2; j++)
		{
			float fProgress1 = (float)i / iSegments1;
			float fProgress2 = (float)j / iSegments2;

			float fAngle1 = fProgress1 * 3.14159f * 2;
			float fAngle2 = fProgress2 * 3.14159f * 2;

			pVertexArray->vPosition.x = cosf(fAngle1) * (fRadius1 + cosf(fAngle2) * fRadius2);
			pVertexArray->vPosition.y = sinf(fAngle2) * fRadius2;
			pVertexArray->vPosition.z = sinf(fAngle1) * (fRadius1 + cosf(fAngle2) * fRadius2);

			pVertexArray->vNormal.x = cosf(fAngle2) * cosf(fAngle1);
			pVertexArray->vNormal.y = sinf(fAngle2);
			pVertexArray->vNormal.z = cosf(fAngle2) * sinf(fAngle1);

			pVertexArray->vTangent.x = sinf(fAngle1);
			pVertexArray->vTangent.y = 0;
			pVertexArray->vTangent.z = -cosf(fAngle1);

			D3DXVec3Cross(&pVertexArray->vBinormal, &pVertexArray->vTangent, &pVertexArray->vNormal);


			pVertexArray->dwColor = 0;
			if (i & 1) pVertexArray->dwColor |= 0x0000ff00;
			if (j & 1) pVertexArray->dwColor |= 0x00ff0000;
			if (!pVertexArray->dwColor) pVertexArray->dwColor = 0x000000ff;

			pVertexArray->vTexCoord.x = -fProgress1;
			pVertexArray->vTexCoord.y = fProgress2 + 0.5f;

			pVertexArray++;
		}
	}

	pVertexBuffer->Unlock();


	// create index buffer
	IDirect3DIndexBuffer9* pIndexBuffer;
	hr = pDevice->CreateIndexBuffer(
			sizeof(short int) * iNumTriangles * 3, 
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, 
			&pIndexBuffer, NULL);
	if (FAILED(hr)) return hr;


	unsigned short* pIndexArray;
	pIndexBuffer->Lock(0, 0, (void**)&pIndexArray, 0);

	for (int iSeg1 = 0; iSeg1 < iSegments1; iSeg1++)
	{
		for (int iSeg2 = 0; iSeg2 < iSegments2; iSeg2++)
		{
			*pIndexArray++ = (iSeg1 + 0) * (iSegments2 + 1) + (iSeg2 + 1);
			*pIndexArray++ = (iSeg1 + 1) * (iSegments2 + 1) + (iSeg2 + 0);
			*pIndexArray++ = (iSeg1 + 0) * (iSegments2 + 1) + (iSeg2 + 0);
												
			*pIndexArray++ = (iSeg1 + 0) * (iSegments2 + 1) + (iSeg2 + 1);
			*pIndexArray++ = (iSeg1 + 1) * (iSegments2 + 1) + (iSeg2 + 1);
			*pIndexArray++ = (iSeg1 + 1) * (iSegments2 + 1) + (iSeg2 + 0);
		}
	}

	pIndexBuffer->Unlock();


	// set out parameters
	*piNumVerticesOut = iNumVertices;
	*piNumTrianglesOut = iNumTriangles;
	*piVertexSizeOut = iVertexSize;
	*ppVertexDeclarationOut = pVertexDeclaration;
	*ppVertexBufferOut = pVertexBuffer;
	*ppIndexBufferOut = pIndexBuffer;

	return S_OK;
}
//---------------------------------------------------------------------------------------------------------------------
HRESULT
CreateCube(IDirect3DDevice9* pDevice, 
			int* piNumVerticesOut, int* piNumTrianglesOut, int* piVertexSizeOut,
			IDirect3DVertexDeclaration9** ppVertexDeclarationOut,
			IDirect3DVertexBuffer9** ppVertexBufferOut,
			IDirect3DIndexBuffer9**	ppIndexBufferOut)
{
	// create a cube
	int iNumVertices = 24;
	int iNumTriangles = 12;


    struct TCubeVertex
	{
		D3DXVECTOR3 vPosition;
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 vTangent;
		D3DXVECTOR3 vBinormal;
		D3DCOLOR	dwColor;
		D3DXVECTOR2 vTexCoord;
	};

	int iVertexSize = sizeof(TCubeVertex);


	// create vertex declaration
	D3DVERTEXELEMENT9 axVertexElements[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
		{ 0, 36, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		{ 0, 48, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,	  0 },
		{ 0, 52, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	IDirect3DVertexDeclaration9* pVertexDeclaration;
	pDevice->CreateVertexDeclaration(axVertexElements, &pVertexDeclaration);


	// create vertex buffer
	IDirect3DVertexBuffer9* pVertexBuffer;
	pDevice->CreateVertexBuffer(
			sizeof(TCubeVertex) * iNumVertices, 
			D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, 
			&pVertexBuffer, NULL);

	TCubeVertex* pVertexArray;
	pVertexBuffer->Lock(0, 0, (void**)&pVertexArray, 0);

	DWORD aFaceColors[] = {0x00FF0000, 0x0000FF00, 0x000000FF, 0x0000FFFF, 0x00FF00FF, 0x00FFFF00};
	//DWORD aFaceColors[] = {0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF, 0x00FFFFFF};

	for (int iFace = 0; iFace < 6; iFace++)
	{
		D3DXVECTOR3 vNormal(0, 0, 0);
		if (iFace % 3 == 0) vNormal.x = 1;
		if (iFace % 3 == 1) vNormal.y = 1;
		if (iFace % 3 == 2) vNormal.z = 1;
		if (iFace / 3 != 0) vNormal = -vNormal;

		D3DXVECTOR3 vTangent(0, 0, 0);
		if (iFace % 3 == 1) vTangent.x = 1;
		if (iFace % 3 == 2) vTangent.y = 1;
		if (iFace % 3 == 0) vTangent.z = 1;
		if (iFace / 3 != 0) vTangent = -vTangent;

		D3DXVECTOR3 vBiTangent;
		D3DXVec3Cross(&vBiTangent, &vNormal, &vTangent);

		for (int iCorner = 0; iCorner < 4; iCorner++)
		{
			D3DXVECTOR3 vPosition = vNormal;
			if (iCorner % 2 == 0) vPosition += vTangent; else vPosition -= vTangent;
			if (iCorner / 2 == 0) vPosition += vBiTangent; else vPosition -= vBiTangent;

			pVertexArray[iFace * 4 + iCorner].vPosition = vPosition;

			pVertexArray[iFace * 4 + iCorner].vNormal = vNormal;
			pVertexArray[iFace * 4 + iCorner].vTangent = -vTangent;
			pVertexArray[iFace * 4 + iCorner].vBinormal = -vBiTangent;

			pVertexArray[iFace * 4 + iCorner].vTexCoord.x = (float)(iCorner % 2);
			pVertexArray[iFace * 4 + iCorner].vTexCoord.y = (float)(iCorner / 2);

			pVertexArray[iFace * 4 + iCorner].dwColor = aFaceColors[iFace];
		}
	}

	pVertexBuffer->Unlock();


	// create index buffer
	IDirect3DIndexBuffer9* pIndexBuffer;
	pDevice->CreateIndexBuffer(
			sizeof(short int) * iNumTriangles * 3, 
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, 
			&pIndexBuffer, NULL);

	unsigned short* pIndexArray;
	pIndexBuffer->Lock(0, 0, (void**)&pIndexArray, 0);

	for (int iFace = 0; iFace < 6; iFace++)
	{
		pIndexArray[iFace * 6 + 0] = iFace * 4 + 0;
		pIndexArray[iFace * 6 + 1] = iFace * 4 + 1;
		pIndexArray[iFace * 6 + 2] = iFace * 4 + 3;

		pIndexArray[iFace * 6 + 3] = iFace * 4 + 3;
		pIndexArray[iFace * 6 + 4] = iFace * 4 + 2;
		pIndexArray[iFace * 6 + 5] = iFace * 4 + 0;
	}

	pIndexBuffer->Unlock();


	// set out parameters
	*piNumVerticesOut = iNumVertices;
	*piNumTrianglesOut = iNumTriangles;
	*piVertexSizeOut = iVertexSize;
	*ppVertexDeclarationOut = pVertexDeclaration;
	*ppVertexBufferOut = pVertexBuffer;
	*ppIndexBufferOut = pIndexBuffer;

	return S_OK;
}
//---------------------------------------------------------------------------------------------------------------------
