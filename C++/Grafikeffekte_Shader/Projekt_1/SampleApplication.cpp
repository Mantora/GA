#include "SampleApplication.h"
#include "objects.h"
#include <stdio.h>

//---------------------------------------------------------------------------------------------------------------------
CSampleApplication::CSampleApplication()
{
	m_fTime = 0;
	D3DXMatrixIdentity(&m_mWorld);
}

//---------------------------------------------------------------------------------------------------------------------
CSampleApplication::~CSampleApplication()
{
}

//---------------------------------------------------------------------------------------------------------------------
void 
CSampleApplication::AutoLoadEffectTextures(ID3DXEffect* pEffect) const
{
	D3DXEFFECT_DESC xEffectDesc;
	pEffect->GetDesc(&xEffectDesc);

	for (int iParameterIdx = 0; iParameterIdx < (int)xEffectDesc.Parameters; iParameterIdx++)
	{
		D3DXHANDLE hParameter = pEffect->GetParameter(NULL, iParameterIdx);
		D3DXPARAMETER_DESC xParameterDesc;
		pEffect->GetParameterDesc(hParameter, &xParameterDesc);

		if (xParameterDesc.Type == D3DXPT_TEXTURE ||   xParameterDesc.Type == D3DXPT_TEXTURE1D ||
			xParameterDesc.Type == D3DXPT_TEXTURE2D || xParameterDesc.Type == D3DXPT_TEXTURE3D ||
			xParameterDesc.Type == D3DXPT_TEXTURECUBE)
		{
			D3DXHANDLE hAnnotation =
				pEffect->GetAnnotationByName(hParameter, "SasResourceAddress");

			if (hAnnotation != NULL)
			{
				const char* pcFileName;
				pEffect->GetString(hAnnotation, &pcFileName);

				D3DXIMAGE_INFO xImageInfo;
				HRESULT hr = D3DXGetImageInfoFromFile(pcFileName, &xImageInfo);
				if (FAILED(hr))
					MessageBox(GetWindowHandle(), pcFileName, "failed to load texture!", MB_ICONERROR);

				IDirect3DBaseTexture9* pTexture = NULL;

				switch (xImageInfo.ResourceType)
				{
				case D3DRTYPE_TEXTURE :			D3DXCreateTextureFromFile(m_pD3dDevice, pcFileName, (IDirect3DTexture9**)&pTexture);				break;
				case D3DRTYPE_CUBETEXTURE :		D3DXCreateCubeTextureFromFile(m_pD3dDevice, pcFileName, (IDirect3DCubeTexture9**)&pTexture);		break;
				case D3DRTYPE_VOLUMETEXTURE :	D3DXCreateVolumeTextureFromFile(m_pD3dDevice, pcFileName, (IDirect3DVolumeTexture9**)&pTexture);	break;
				}

				m_pEffect->SetTexture(hParameter, pTexture);
				pTexture->Release();
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------
void 
CSampleApplication::CreateScene()
{
	//*
	CreateTorus(m_pD3dDevice,
			60, 40, 0.5f, 0.25f,
			&m_iNumVertices, &m_iNumTriangles, &m_iVertexSize,
			&m_pVertexDeclaration, &m_pVertexBuffer, &m_pIndexBuffer);
	/*/
	CreateCube(m_pD3dDevice,
			&m_iNumVertices, &m_iNumTriangles, &m_iVertexSize,
			&m_pVertexDeclaration, &m_pVertexBuffer, &m_pIndexBuffer);
	/**/


	D3DXCreateTextureFromFile(m_pD3dDevice, "earth_diffuse.dds", &m_pTexture);

	/*
	int iTextureSize = 1024;
	m_pD3dDevice->CreateTexture(iTextureSize, iTextureSize, 0, 0, 
								D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
								&m_pTexture, NULL);

	D3DCOLOR axColors[] = { 0x00FF0000, 0x0000FF00, 0x000000FF, 0x0000FFFF, 
							0x00FF00FF, 0x00FFFF00, 0x007F7F7F, 0x00FFFFFF,
							0x007F00FF, 0x00FF7F00, 0x00007FFF, 0x007F007F };

	int iMipLevel = 0;
	while ((iTextureSize >> iMipLevel) != 0)
	{
		int iMipLevelSize = iTextureSize >> iMipLevel;

		D3DLOCKED_RECT xPixelData;
		m_pTexture->LockRect(iMipLevel, &xPixelData, NULL, 0);
		
		for (int iY = 0; iY < iMipLevelSize; iY++)
		{
			D3DCOLOR* pLineData = (D3DCOLOR*)((BYTE*)xPixelData.pBits + iY * xPixelData.Pitch);

			for (int iX = 0; iX < iMipLevelSize; iX++)
			{
	//			pLineData[iX] = (iX / 8 + iY / 8) & 1 ? 0x00FF0000 : 0x00FFFF00;
	//			pLineData[iX] = rand() + (rand() << 15);

				float f = (float)iY / iMipLevelSize;
				if (fmodf(f, 0.1f) < 0.05f)
					pLineData[iX] = axColors[iMipLevel];
				else
					pLineData[iX] = ~axColors[iMipLevel];
			}
		}

		m_pTexture->UnlockRect(iMipLevel);
		iMipLevel++;
	}
	*/


	// create effect
	ID3DXBuffer* pErrorMessages;
	HRESULT hr = 
		D3DXCreateEffectFromFile(m_pD3dDevice, "simple.fx", 
								NULL, NULL, 0, NULL, 
								&m_pEffect, &pErrorMessages);

	if (FAILED(hr) || pErrorMessages != NULL)
	{
		MessageBox(GetWindowHandle(), 
				pErrorMessages != NULL ? (char*)pErrorMessages->GetBufferPointer()
										: "no error messages returned.",
				"Failed to load effect!",
				MB_ICONINFORMATION);
		exit(-1);
	}

	AutoLoadEffectTextures(m_pEffect);
}

//---------------------------------------------------------------------------------------------------------------------
void 
CSampleApplication::DestroyScene()
{
	m_pTexture->Release();
	m_pTexture = NULL;

	m_pEffect->Release();
	m_pEffect = NULL;

	m_pIndexBuffer->Release();
	m_pIndexBuffer = NULL;

	m_pVertexBuffer->Release();
	m_pVertexBuffer = NULL;	

	m_pVertexDeclaration->Release();
	m_pVertexDeclaration = NULL;
}

//---------------------------------------------------------------------------------------------------------------------
void 
CSampleApplication::UpdateScene(float fDeltaTime)
{
	m_fTime += fDeltaTime;


	// update object rotation
	D3DXMATRIX mRotation;
	D3DXMatrixRotationAxis(&mRotation, &D3DXVECTOR3(1, 2, 3), fDeltaTime);
	m_mWorld = mRotation * m_mWorld;


	// update camera matrices
	D3DXMatrixLookAtLH(&m_mView,
						&D3DXVECTOR3(0, 0, -2.5f),
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 1, 0));

	D3DXMatrixPerspectiveFovLH(&m_mProjection,
						45.0f / 180.0f * D3DX_PI,
						800.0f / 600.0f,
						0.1f, 1000.0f);
}

//---------------------------------------------------------------------------------------------------------------------
void 
CSampleApplication::RenderScene() const
{
	m_pEffect->SetFloat("g_fTime", m_fTime);

	m_pEffect->SetMatrix("g_mWorld", &m_mWorld);
	m_pEffect->SetMatrix("g_mView", &m_mView);
	m_pEffect->SetMatrix("g_mProjection", &m_mProjection);

	D3DXMATRIX mViewInverse;
	D3DXMatrixInverse(&mViewInverse, NULL, &m_mView);
	m_pEffect->SetMatrix("g_mViewInverse", &mViewInverse);



	D3DXVECTOR4 vPlane(0, 0.05f, 1, -0.95f);
	m_pD3dDevice->SetClipPlane(0, vPlane);

	RECT xRect = { 100, 100, 500, 500 };
	m_pD3dDevice->SetScissorRect(&xRect);


	// activate vertex declaration
	m_pD3dDevice->SetVertexDeclaration(m_pVertexDeclaration);
	m_pD3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);
	m_pD3dDevice->SetIndices(m_pIndexBuffer);


	m_pEffect->SetTechnique("MyTechnique");



	// activate effect
	int iNumPasses;
	m_pEffect->Begin((UINT*)&iNumPasses, 0);

	// for each pass
	for (int iPass = 0; iPass < iNumPasses; iPass++)
	{
		// activate pass
		m_pEffect->BeginPass(iPass);

		// draw geometry
		m_pD3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
											m_iNumVertices, 0, m_iNumTriangles);

		// deactivate pass
		m_pEffect->EndPass();
	}

	// deactivate effect
	m_pEffect->End();
}

//---------------------------------------------------------------------------------------------------------------------
