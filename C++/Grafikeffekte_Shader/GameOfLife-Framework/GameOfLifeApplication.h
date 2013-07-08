#ifndef SAMPLEAPPLICATION_H_INCLUDED
#define SAMPLEAPPLICATION_H_INCLUDED

#include <d3dx9.h>
#include "D3DApplication.h"

// ----------------------------------------------------------------------------
class CGameOfLifeApplication : public CD3DApplication
{
public:

	CGameOfLifeApplication();
	~CGameOfLifeApplication();


private:

	virtual void CreateScene();
	virtual void DestroyScene();
	virtual void RenderScene();
	virtual void UpdateScene(float fDeltaTime);

	virtual void OnKeyDown(WPARAM wVirtualKey);


	void AutoLoadShaderTexture(ID3DXEffect* pEffect);
	void SetTextureAsRenderTarget(int iRtIndex, IDirect3DTexture9* pTexture, bool bClear, DWORD dwClearColor);
	void RenderQuad(const char* pcTechnique);


	IDirect3DTexture9*	m_pStartTexture;

	IDirect3DTexture9*	m_pGameOfLifeRT1;
	IDirect3DTexture9*	m_pGameOfLifeRT2;

	int					m_iTextureWidth;
	int					m_iTextureHeight;


	ID3DXEffect*		m_pEffect;


	int					m_iSimulationStepIndex;
	int					m_iSimulationStepInTexture;
};

// ----------------------------------------------------------------------------

#endif // SAMPLEAPPLICATION_H_INCLUDED