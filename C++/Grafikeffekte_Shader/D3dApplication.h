#ifndef D3DAPPLICATION_H_INCLUDED
#define D3DAPPLICATION_H_INCLUDED

#include <d3d9.h>
#include "Application.h"


class CD3dApplication : public CApplication
{
public:

	CD3dApplication();
	~CD3dApplication();


protected:

	void Initialize();
	void Shutdown();
	void OnIdle(float fDeltaTime);
	void Render() const;

	void InitializeDirect3D();
	void ShutdownDirect3D();

	IDirect3DDevice9*	m_pD3dDevice;


	virtual void CreateScene();
	virtual void DestroyScene();
	virtual void UpdateScene(float fDeltaTime);
	virtual void RenderScene() const;
};


#endif // D3DAPPLICATION_H_INCLUDED