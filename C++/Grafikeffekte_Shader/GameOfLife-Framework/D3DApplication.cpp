#include "D3DApplication.h"

#include <d3d9.h>
#include <stdio.h>


// ----------------------------------------------------------------------------
CD3DApplication::CD3DApplication()
{
	m_pD3dDevice = NULL;

	m_pDiMouseDevice = NULL;
	m_pDiKeyboardDevice = NULL;
	m_pDiJoystickDevice = NULL;
}

// ----------------------------------------------------------------------------
CD3DApplication::~CD3DApplication()
{
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::Initialize()
{
	CApplication::Initialize();
	InitializeDirect3d();
	InitializeDirectInput();
	CreateScene();
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::Shutdown()
{
	DestroyScene();
	ShutdownDirectInput();
	ShutdownDirect3d();
	CApplication::Shutdown();
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::OnIdle(float fDeltaTime)
{
	CApplication::OnIdle(fDeltaTime);

	ReadInput();
	UpdateScene(fDeltaTime);
	Render();
}

// ----------------------------------------------------------------------------
void
CD3DApplication::InitializeDirect3d()
{
	// 1) query information about the system
	IDirect3D9* pDirect3d = Direct3DCreate9(D3D_SDK_VERSION);

	int iNumberOfGraphicsCards = pDirect3d->GetAdapterCount();
	for (int iCardIdx = 0; iCardIdx < iNumberOfGraphicsCards; iCardIdx++)
	{
		D3DADAPTER_IDENTIFIER9 xIdentifier;
		pDirect3d->GetAdapterIdentifier(iCardIdx, 0, &xIdentifier);
		printf("%s\n", xIdentifier.Description);


		D3DCAPS9 xDeviceCaps;
		pDirect3d->GetDeviceCaps(iCardIdx, D3DDEVTYPE_HAL, &xDeviceCaps);
		printf("max texture size = %d\n", xDeviceCaps.MaxTextureWidth);
	}

	
	// 2) create device interface
	D3DPRESENT_PARAMETERS xPresentParameters;
	xPresentParameters.BackBufferWidth = 800;
	xPresentParameters.BackBufferHeight = 600;
	xPresentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;		// true color
	xPresentParameters.BackBufferCount = 2;						// triple buffering
	xPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;	// disable anti-aliasing
	xPresentParameters.MultiSampleQuality = 0;
	xPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	xPresentParameters.hDeviceWindow = GetWindowHandle();
	xPresentParameters.Windowed = TRUE;
	xPresentParameters.EnableAutoDepthStencil = TRUE;			// automatically create z-buffer
	xPresentParameters.AutoDepthStencilFormat = D3DFMT_D24X8;
	xPresentParameters.Flags = 0;
	xPresentParameters.FullScreen_RefreshRateInHz = 0;			// auto detect monitor refresh rate
	xPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	// v-sync on


	HRESULT hr = pDirect3d->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										GetWindowHandle(),
										D3DCREATE_HARDWARE_VERTEXPROCESSING,
										&xPresentParameters,
										&m_pD3dDevice);


	pDirect3d->Release();
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::ShutdownDirect3d()
{
	m_pD3dDevice->Release();
}

// ----------------------------------------------------------------------------
BOOL
CD3DApplication::InputDeviceEnumerationCallback(
			const DIDEVICEINSTANCE* pDeviceInstance, void* pvRef)
{
	CD3DApplication* pApplication = (CD3DApplication*)pvRef;

	switch (pDeviceInstance->dwDevType & 0x00FF)
	{
	case DI8DEVTYPE_JOYSTICK :
		if (pApplication->m_pDiJoystickDevice == NULL)
		{
			printf("using joystick %s\n", pDeviceInstance->tszProductName);
			pApplication->m_pDirectInput->CreateDevice(
				pDeviceInstance->guidInstance, 
				&pApplication->m_pDiJoystickDevice,
				NULL);
		}
		break;

	case DI8DEVTYPE_MOUSE :
		if (pApplication->m_pDiMouseDevice == NULL)
		{
			printf("using mouse %s\n", pDeviceInstance->tszProductName);
			pApplication->m_pDirectInput->CreateDevice(
				pDeviceInstance->guidInstance, 
				&pApplication->m_pDiMouseDevice,
				NULL);
		}
		break;

	case DI8DEVTYPE_KEYBOARD :
		if (pApplication->m_pDiKeyboardDevice == NULL)
		{
			printf("using keaboard %s\n", pDeviceInstance->tszProductName);
			pApplication->m_pDirectInput->CreateDevice(
				pDeviceInstance->guidInstance, 
				&pApplication->m_pDiKeyboardDevice,
				NULL);
		}
		break;
	}

	return TRUE;
}

// ----------------------------------------------------------------------------
void
CD3DApplication::InitializeDirectInput()
{

	DirectInput8Create(GetInstanceHandle(),
						DIRECTINPUT_VERSION,
						IID_IDirectInput8,
						(void**)&m_pDirectInput,
						NULL);

	m_pDirectInput->EnumDevices(DI8DEVCLASS_ALL,
							InputDeviceEnumerationCallback,
							this,
							DIEDFL_ATTACHEDONLY);

	if (m_pDiJoystickDevice)
	{
		// tell joystick device, that we want to read data with the DIJOYSTATE structure
		m_pDiJoystickDevice->SetDataFormat(&c_dfDIJoystick);
		m_pDiJoystickDevice->SetCooperativeLevel(GetWindowHandle(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	}

	if (m_pDiMouseDevice)
	{
		// tell mouse device, that we want to read data with the DIMOUSESTATE structure
		m_pDiMouseDevice->SetDataFormat(&c_dfDIMouse);
		m_pDiMouseDevice->SetCooperativeLevel(GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	}

	if (m_pDiKeyboardDevice)
	{
		// tell keyboard device, that we want to read data with the BYTE[256] structure
		m_pDiKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
		m_pDiKeyboardDevice->SetCooperativeLevel(GetWindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}
}

// ----------------------------------------------------------------------------
void
CD3DApplication::ReadInput()
{
	if (m_pDiJoystickDevice)
	{
		// read joystick and store current state in member variable
		if (SUCCEEDED(m_pDiJoystickDevice->Acquire()))
		{
			m_pDiJoystickDevice->GetDeviceState(sizeof(m_xJoystickState), &m_xJoystickState);
			//printf("%d %d\n", m_xJoystickState.lX, m_xJoystickState.lY);
		}
	}

	if (m_pDiMouseDevice)
	{
		// read mouse and store current state in member variable
		if (SUCCEEDED(m_pDiMouseDevice->Acquire()))
		{
			m_pDiMouseDevice->GetDeviceState(sizeof(m_xMouseState), &m_xMouseState);
			//printf("%d %d\n", m_xMouseState.lX, m_xMouseState.lY);
		}
	}

	if (m_pDiKeyboardDevice)
	{
		// read keyboard and store current state in member variable
		if (SUCCEEDED(m_pDiKeyboardDevice->Acquire()))
		{
			m_pDiKeyboardDevice->GetDeviceState(sizeof(m_xKeyboardState), &m_xKeyboardState);
			//printf("%d\n", m_xKeyboardState[DIK_RCONTROL]);
		}
	}
}

// ----------------------------------------------------------------------------
void
CD3DApplication::ShutdownDirectInput()
{
	if (m_pDiJoystickDevice)
	{
		m_pDiJoystickDevice->Release();
		m_pDiJoystickDevice = NULL;
	}

	if (m_pDiMouseDevice)
	{
		m_pDiMouseDevice->Release();
		m_pDiMouseDevice = NULL;
	}

	if (m_pDiKeyboardDevice)
	{
		m_pDiKeyboardDevice->Release();
		m_pDiKeyboardDevice = NULL;
	}

	m_pDirectInput->Release();
	m_pDirectInput = NULL;
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::CreateScene()
{
	// TODO
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::DestroyScene()
{
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::RenderScene()
{
}

// ----------------------------------------------------------------------------
void
CD3DApplication::UpdateScene(float fDeltaTime)
{
}

// ----------------------------------------------------------------------------
void 
CD3DApplication::Render()
{
	if (SUCCEEDED(m_pD3dDevice->BeginScene()))
	{
		m_pD3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
							0x00306090, 1.0, 0);

		RenderScene();
		
		m_pD3dDevice->EndScene();
		m_pD3dDevice->Present(NULL, NULL, NULL, NULL);
	}
}

// ----------------------------------------------------------------------------
