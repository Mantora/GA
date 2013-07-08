#include "D3dApplication.h"

#include <d3d9.h>
#include <stdio.h>

//---------------------------------------------------------------------------------------------------------------------
CD3dApplication::CD3dApplication()
{
	m_pD3dDevice = NULL;
}

//---------------------------------------------------------------------------------------------------------------------
CD3dApplication::~CD3dApplication()
{
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::Initialize()
{
	CApplication::Initialize();
	InitializeDirect3D();
	CreateScene();
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::Shutdown()
{
	DestroyScene();
	ShutdownDirect3D();
	CApplication::Shutdown();
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::InitializeDirect3D()
{
	IDirect3D9* pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);

	// print some data about the graphics cards in the system
	printf("number of graphics cards: %d\n", pDirect3d->GetAdapterCount());
	for (int i = 0; i < (int)pDirect3d->GetAdapterCount(); i++)
	{
		D3DADAPTER_IDENTIFIER9 xIdentifier;
		pDirect3d->GetAdapterIdentifier(i, 0, &xIdentifier);
		printf("\t%s\n", xIdentifier.Description);

		D3DCAPS9 xDeviceCaps;
		pDirect3d->GetDeviceCaps(i, D3DDEVTYPE_HAL, &xDeviceCaps);
		printf("\t\tsupports alpha textures: %s\n", (xDeviceCaps.TextureCaps & D3DPTEXTURECAPS_ALPHA) ? "Yes" : "No");
		printf("\t\tmax texture size: %dx%d\n", xDeviceCaps.MaxTextureWidth, xDeviceCaps.MaxTextureHeight);
	}


	// create device interface
	D3DPRESENT_PARAMETERS xParameters;	// data structure that contains swap chain parameters
	ZeroMemory(&xParameters, sizeof(xParameters));
	xParameters.BackBufferFormat = D3DFMT_X8R8G8B8;					// 32 bit true color, 8 bit per channel
	xParameters.BackBufferCount = 2;								// triple buffering
	xParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;					// allow gpu to take a new backbuffer for every frame
	xParameters.hDeviceWindow = GetWindowHandle();
	xParameters.Windowed = true;									// start in window mode
	xParameters.EnableAutoDepthStencil = true;						// create depth sencil buffer automatically
	xParameters.AutoDepthStencilFormat = D3DFMT_D24S8;				// 24 bit depth, no stencil buffer
	xParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// vsync enabled	

	HRESULT hr = pDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetWindowHandle(), 
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&xParameters,
									&m_pD3dDevice);

	pDirect3d->Release();
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::ShutdownDirect3D()
{
	m_pD3dDevice->Release();
	m_pD3dDevice = NULL;
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::OnIdle(float fDeltaTime)
{
	CApplication::OnIdle(fDeltaTime);

	UpdateScene(fDeltaTime);
	Render();
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::CreateScene()
{
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::DestroyScene()
{
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::UpdateScene(float fDeltaTime)
{
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::RenderScene() const
{
}

//---------------------------------------------------------------------------------------------------------------------
void 
CD3dApplication::Render() const
{
	m_pD3dDevice->BeginScene();

	// clear background
	m_pD3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00306090, 1.0f, 0);
//	m_pD3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

	// draw polygons
	RenderScene();


	m_pD3dDevice->EndScene();

	// swap back and front buffer
	m_pD3dDevice->Present(NULL, NULL, NULL, NULL);
}

//---------------------------------------------------------------------------------------------------------------------
