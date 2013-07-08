#ifndef D3DAPPLICATION_H_INCLUDED
#define D3DAPPLICATION_H_INCLUDED


#include "Application.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


struct IDirect3DDevice9;

// ----------------------------------------------------------------------------
class CD3DApplication : public CApplication
{
public:

	CD3DApplication();
	virtual ~CD3DApplication();

	
protected:

	virtual void Initialize();
	virtual void Shutdown();
	virtual void OnIdle(float fDeltaTime);


	static BOOL __stdcall InputDeviceEnumerationCallback(const DIDEVICEINSTANCE* pDeviceInstance, void* pvRef);


	void InitializeDirect3d();
	void ShutdownDirect3d();
	void InitializeDirectInput();
	void ShutdownDirectInput();
	void Render();



	virtual void CreateScene();
	virtual void DestroyScene();
	virtual void RenderScene();
	virtual void UpdateScene(float fDeltaTime);

	virtual void ReadInput();


	IDirect3DDevice9*		m_pD3dDevice;


	IDirectInput8*			m_pDirectInput;

	IDirectInputDevice8*	m_pDiMouseDevice;
	IDirectInputDevice8*	m_pDiKeyboardDevice;
	IDirectInputDevice8*	m_pDiJoystickDevice;

	DIMOUSESTATE			m_xMouseState;
	BYTE					m_xKeyboardState[256];
	DIJOYSTATE				m_xJoystickState;
};

// ----------------------------------------------------------------------------

#endif // D3DAPPLICATION_H_INCLUDED