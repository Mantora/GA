#include "Application.h"
#include <assert.h>

//---------------------------------------------------------------------------------------------------------------------
CApplication* CApplication::ms_pxApplication;
//---------------------------------------------------------------------------------------------------------------------
// constructor
CApplication::CApplication()
:	m_hAppInstance	(NULL),
	m_hAppWindow	(NULL)
{
	// set the static pointer to the application
	assert(ms_pxApplication == NULL);
	ms_pxApplication = this;
}
//---------------------------------------------------------------------------------------------------------------------
// destructor
CApplication::~CApplication()
{
	// reset the static application pointer
	assert(ms_pxApplication == this);
	ms_pxApplication = NULL;
}
//---------------------------------------------------------------------------------------------------------------------
void 
CApplication::Run(HINSTANCE hInstance)
{
	m_hAppInstance = hInstance;

	Initialize();
	MessageLoop();
	Shutdown();
}
//---------------------------------------------------------------------------------------------------------------------
void
CApplication::MessageLoop()
{
	assert(m_hAppWindow && "application window has not been created!");

	MSG xMessage = {0, 0, 0, 0, 0, 0}; 
	while (xMessage.message != WM_QUIT)
	{
		if (PeekMessage(&xMessage, NULL, 0U, 0U, PM_REMOVE) != 0)
		{
			TranslateMessage(&xMessage);
			DispatchMessage(&xMessage);
		}
		else
		{
			float fDeltaTime = GetDeltaTime();
			OnIdle(fDeltaTime);
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
// returns the time since that elapsed since the last call of GetDeltaTime
float
CApplication::GetDeltaTime()
{
	static __int64 i64LastCounter;

    if (i64LastCounter == 0)
    {
    	QueryPerformanceCounter((LARGE_INTEGER*)&i64LastCounter);
    }

	__int64 i64Counter;
    BOOL b;
    b = QueryPerformanceCounter((LARGE_INTEGER*)&i64Counter);
    assert(b && "QueryPerformanceCounter failed");

	__int64 i64CounterFrq;
	b = QueryPerformanceFrequency((LARGE_INTEGER*)&i64CounterFrq);
    assert(b && "QueryPerformanceCounter failed");


	float fDeltaTime = (float)(((double)(i64Counter - i64LastCounter)) / ((double)i64CounterFrq));

    i64LastCounter = i64Counter;

	return fDeltaTime;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
// MessageHandler - recieves windows messages
LRESULT 
WINAPI CApplication::MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN:
			if (ms_pxApplication)
				ms_pxApplication->OnKeyDown(wParam);
            return 0;

        default:
            return DefWindowProc(hWindow, msg, wParam, lParam);
    }
}
//---------------------------------------------------------------------------------------------------------------------
void 
CApplication::CreateAppWindow(int iWidth, int iHeight)
{
    // 1) register window class
	WNDCLASS xWindowClass = {
        CS_CLASSDC, MessageHandler, 0L, 0L,
		m_hAppInstance, NULL, NULL, NULL, NULL,
        "d3dframework"
    };

    RegisterClass(&xWindowClass);


	// calculate window rect by client rect
	RECT rctClientRect = {0, 0, iWidth, iHeight};
	AdjustWindowRect(&rctClientRect, WS_OVERLAPPEDWINDOW, FALSE);


    // 3) create window
    m_hAppWindow = CreateWindow(
        "d3dframework", "direct3d framework",
		WS_OVERLAPPEDWINDOW, 50, 50, 
		rctClientRect.right - rctClientRect.left, 
		rctClientRect.bottom - rctClientRect.top, 
		GetDesktopWindow(), NULL, m_hAppInstance, NULL);

    ShowWindow(m_hAppWindow, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------------------------------------------------
void 
CApplication::DestroyAppWindow()
{
    // unregister window class
	UnregisterClass("d3dframework", m_hAppInstance);
}
//---------------------------------------------------------------------------------------------------------------------
void 
CApplication::Initialize()
{
	CreateAppWindow(800, 600);
}
//---------------------------------------------------------------------------------------------------------------------
void 
CApplication::Shutdown()
{
	DestroyAppWindow();
}
//---------------------------------------------------------------------------------------------------------------------
HINSTANCE
CApplication::GetInstanceHandle() const
{
	return m_hAppInstance;
}
//---------------------------------------------------------------------------------------------------------------------
HWND
CApplication::GetWindowHandle() const
{
	return m_hAppWindow;
}
//---------------------------------------------------------------------------------------------------------------------
