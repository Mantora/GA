#ifndef SAMPLEAPPLICATION_H_INCLUDED
#define SAMPLEAPPLICATION_H_INCLUDED

#include "D3dApplication.h"
#include <d3dx9.h>


class CSampleApplication : public CD3dApplication
{
public:

	CSampleApplication();
	~CSampleApplication();


private:
	
	void CreateScene();						// create geometry, textures etc.
	void DestroyScene();					// releases geometry, textures etc.

	void UpdateScene(float fDeltaTime);		// updates animation, transformation etc.
	void RenderScene() const;				// renders geometry

	void AutoLoadEffectTextures(ID3DXEffect* pEffect) const;


	float			m_fTime;

	D3DXMATRIX		m_mWorld;
	D3DXMATRIX		m_mView;
	D3DXMATRIX		m_mProjection;


	// geometry
	int				m_iNumTriangles;
	int				m_iNumVertices;
	int				m_iVertexSize;

	IDirect3DVertexDeclaration9*	m_pVertexDeclaration;
	IDirect3DVertexBuffer9*			m_pVertexBuffer;
	IDirect3DIndexBuffer9*			m_pIndexBuffer;

	IDirect3DTexture9*				m_pTexture;

	ID3DXEffect*					m_pEffect;
};

#endif // SAMPLEAPPLICATION_H_INCLUDED
