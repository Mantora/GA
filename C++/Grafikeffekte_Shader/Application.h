#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <windows.h>


// basic application class
class CApplication
{
public:

	// construction/destruction
	CApplication();
	virtual ~CApplication();


	void Run(HINSTANCE hInstance);


protected:

	// overloadable virtual functions
	virtual void Initialize();						// initializes the application
	virtual void Shutdown();						// shuts the application down

	virtual void OnIdle(float fDeltaTime) {};		// callback function that is triggered when the application is idle
	virtual void OnKeyDown(WPARAM wVirtualKey) {};	// callback function that is triggered when a key is down


	// window creation
	void CreateAppWindow(int iWidth, int iHeight);	// creates the application window
	void DestroyAppWindow();						// destroys the application window


	// accessor functions
	HINSTANCE	GetInstanceHandle() const;			// returns the instance handle of the application
	HWND		GetWindowHandle() const;			// returns the handle of the application's window


private:

	HINSTANCE	m_hAppInstance;						// instance handle of the application
	HWND		m_hAppWindow;						// handle of the application window


	void MessageLoop();								// message loop (main loop)

	float GetDeltaTime();							// utility function that measures the time


	// windows message proc + static application pointer (needed by message proc)
	static LRESULT WINAPI MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
	static CApplication* ms_pxApplication;
};

#endif // APPLICATION_H_INCLUDED