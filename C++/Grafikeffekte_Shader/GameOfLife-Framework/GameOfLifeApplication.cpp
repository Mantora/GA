#include "GameOfLifeApplication.h"
#include <assert.h>
#include <stdio.h>
#include <string>

using std::string;

// ----------------------------------------------------------------------------
CGameOfLifeApplication::CGameOfLifeApplication()
:	m_pStartTexture				(NULL),
	m_pGameOfLifeRT1			(NULL),
	m_pGameOfLifeRT2			(NULL),
	m_iTextureWidth				(0),
	m_iTextureHeight			(0),
	m_pEffect					(NULL),
	m_iSimulationStepIndex		(-1),
	m_iSimulationStepInTexture	(-1)
{
}

// ----------------------------------------------------------------------------
CGameOfLifeApplication::~CGameOfLifeApplication()
{
}

// ----------------------------------------------------------------------------
void
CGameOfLifeApplication::AutoLoadShaderTexture(ID3DXEffect* pEffect)
{
	D3DXEFFECT_DESC xEffectDesc;
	pEffect->GetDesc(&xEffectDesc);

	for (int iParamIdx = 0; iParamIdx < (int)xEffectDesc.Parameters; iParamIdx++)
	{
		D3DXHANDLE hParam = pEffect->GetParameter(NULL, iParamIdx);
		D3DXPARAMETER_DESC xParameterDesc;
		pEffect->GetParameterDesc(hParam, &xParameterDesc); 

		if (xParameterDesc.Type == D3DXPT_TEXTURE || 
			xParameterDesc.Type == D3DXPT_TEXTURE1D || 
			xParameterDesc.Type == D3DXPT_TEXTURE2D || 
			xParameterDesc.Type == D3DXPT_TEXTURE3D || 
			xParameterDesc.Type == D3DXPT_TEXTURECUBE)
		{
			D3DXHANDLE hAnnotation = 
				pEffect->GetAnnotationByName(hParam, "SasResourceAddress");

			if (hAnnotation)
			{
				const char* pcTextureFile;
				pEffect->GetString(hAnnotation, &pcTextureFile);

				D3DXIMAGE_INFO xImageInfo;
				HRESULT hr = D3DXGetImageInfoFromFileA(pcTextureFile, &xImageInfo);
				if (FAILED(hr))
				{
					MessageBoxA(NULL, pcTextureFile, "failed to load texture!", MB_ICONERROR);
					exit(-1);
				}


				IDirect3DBaseTexture9* pTexture;
				switch (xImageInfo.ResourceType)
				{
				case D3DRTYPE_TEXTURE :
					assert(	xParameterDesc.Type == D3DXPT_TEXTURE || 
							xParameterDesc.Type == D3DXPT_TEXTURE1D || 
							xParameterDesc.Type == D3DXPT_TEXTURE2D);
					D3DXCreateTextureFromFileA(m_pD3dDevice, pcTextureFile, (IDirect3DTexture9**)&pTexture);
					break;
				case D3DRTYPE_CUBETEXTURE :
					assert(	xParameterDesc.Type == D3DXPT_TEXTURE || 
							xParameterDesc.Type == D3DXPT_TEXTURECUBE);
					D3DXCreateCubeTextureFromFileA(m_pD3dDevice, pcTextureFile, (IDirect3DCubeTexture9**)&pTexture);
					break;
				case D3DRTYPE_VOLUMETEXTURE :
					assert(	xParameterDesc.Type == D3DXPT_TEXTURE || 
							xParameterDesc.Type == D3DXPT_TEXTURE3D);
					D3DXCreateVolumeTextureFromFileA(m_pD3dDevice, pcTextureFile, (IDirect3DVolumeTexture9**)&pTexture);
					break;
				default:
					assert(false);
				}

				pEffect->SetTexture(hParam, pTexture);
				pTexture->Release();
			}
		}
	}
}

// ----------------------------------------------------------------------------
void 
CGameOfLifeApplication::CreateScene()
{
	HRESULT hr = S_OK;


	// create effect
	ID3DXBuffer* pBuffer;
	hr = D3DXCreateEffectFromFile(m_pD3dDevice, "gameoflife.fx", NULL, 
									NULL, 0, NULL, &m_pEffect, &pBuffer);
	if (FAILED(hr))
	{
		// output message
		MessageBox(GetWindowHandle(), 
			pBuffer ? (char*)pBuffer->GetBufferPointer() : "unknown error (file not found?)", 
			"error while loading shader", MB_ICONERROR);

		if (pBuffer)
			pBuffer->Release();

		exit(-1);
	}

	AutoLoadShaderTexture(m_pEffect);


	// create textures
	hr = D3DXCreateTextureFromFile(m_pD3dDevice, "start.dds", &m_pStartTexture);
	if (FAILED(hr))
	{
		MessageBox(GetWindowHandle(), "failed to load texture", "error", MB_ICONERROR);
		exit(-1);
	}

	D3DSURFACE_DESC xStartTextureDesc;
	m_pStartTexture->GetLevelDesc(0, &xStartTextureDesc);
	m_iTextureWidth = xStartTextureDesc.Width;
	m_iTextureHeight = xStartTextureDesc.Height;


	m_pD3dDevice->CreateTexture(m_iTextureWidth, m_iTextureHeight, 1,
								D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
								&m_pGameOfLifeRT1, NULL);

	m_pD3dDevice->CreateTexture(m_iTextureWidth, m_iTextureHeight, 1,
								D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
								&m_pGameOfLifeRT2, NULL);
}

// ----------------------------------------------------------------------------
void 
CGameOfLifeApplication::DestroyScene()
{
	m_pStartTexture->Release();
	m_pStartTexture = NULL;

	m_pGameOfLifeRT1->Release();
	m_pGameOfLifeRT1 = NULL;

	m_pGameOfLifeRT2->Release();
	m_pGameOfLifeRT2 = NULL;


	m_pEffect->Release();
	m_pEffect = NULL;
}

// ----------------------------------------------------------------------------
void
CGameOfLifeApplication::UpdateScene(float fDeltaTime)
{
	//m_iSimulationStepIndex++;
}

// ----------------------------------------------------------------------------
void 
CGameOfLifeApplication::OnKeyDown(WPARAM wVirtualKey)
{
	if (wVirtualKey == VK_SPACE)
		m_iSimulationStepIndex++;
}

// ----------------------------------------------------------------------------
void
CGameOfLifeApplication::RenderQuad(const char* pcTechnique)
{
	D3DXVECTOR3 axVertices[] =
	{
		D3DXVECTOR3(-1, +1, 0),
		D3DXVECTOR3(+1, +1, 0),
		D3DXVECTOR3(-1, -1, 0),
		D3DXVECTOR3(+1, -1, 0)
	};

	m_pD3dDevice->SetFVF(D3DFVF_XYZ);	// replaces SetVertexDeclaration
	
	m_pEffect->SetTechnique(pcTechnique);

	int iPasses;
	m_pEffect->Begin((UINT*)&iPasses, 0);

	for (int iPass = 0; iPass < iPasses; iPass++)
	{
		m_pEffect->BeginPass(iPass);
		m_pD3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, axVertices, sizeof(axVertices[0]));
		m_pEffect->EndPass();
	}

	m_pEffect->End();
}

// ----------------------------------------------------------------------------
void
CGameOfLifeApplication::SetTextureAsRenderTarget(int iRtIndex, IDirect3DTexture9* pTexture, bool bClear, DWORD dwClearColor)
{
	IDirect3DSurface9* pSurface;
	pTexture->GetSurfaceLevel(0, &pSurface);

	if (bClear)
		m_pD3dDevice->ColorFill(pSurface, NULL, dwClearColor);

	m_pD3dDevice->SetRenderTarget(iRtIndex, pSurface);
	pSurface->Release();
}

// ----------------------------------------------------------------------------
void 
CGameOfLifeApplication::RenderScene()
{
	m_pEffect->SetVector("g_vTextureSize", &D3DXVECTOR4((float)m_iTextureWidth, (float)m_iTextureHeight, 0, 0));

	if (m_iSimulationStepInTexture < m_iSimulationStepIndex)
	{
		SetTextureAsRenderTarget(0, m_pGameOfLifeRT2, false, 0);

		if (m_iSimulationStepIndex == 0)
			m_pEffect->SetTexture("g_tGameOfLifeInput", m_pStartTexture);
		else
			m_pEffect->SetTexture("g_tGameOfLifeInput", m_pGameOfLifeRT1);

		RenderQuad("gameoflife");

		std::swap(m_pGameOfLifeRT1, m_pGameOfLifeRT2);
		m_iSimulationStepInTexture = m_iSimulationStepIndex;

		
		IDirect3DSurface9* pBackBuffer;
		m_pD3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
		m_pD3dDevice->SetRenderTarget(0, pBackBuffer);
		pBackBuffer->Release();

		m_pEffect->SetTexture("g_tGameOfLifeInput", NULL);
	}

	{
		m_pEffect->SetTexture("g_tTexture", m_pGameOfLifeRT1);
		RenderQuad("drawtexture");
		m_pEffect->SetTexture("g_tTexture", NULL);
	}
}

// ----------------------------------------------------------------------------
