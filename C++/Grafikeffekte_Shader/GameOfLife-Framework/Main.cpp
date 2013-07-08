#include "GameOfLifeApplication.h"

#include <crtdbg.h>

//---------------------------------------------------------------------------------------------------------------------
// entry point for console applications
int
main(int iArgCount, const char** ppcArguments)
{
#ifdef _DEBUG
	_CrtMemState xMemState;
	_CrtMemCheckpoint(&xMemState);										// take memory snapshot to detect memory leaks
#endif // _DEBUG


	CApplication* pxApplication = new CGameOfLifeApplication();			// create application and run it
	pxApplication->Run(GetModuleHandle(NULL));
	delete pxApplication;


#ifdef _DEBUG
	_CrtMemDumpAllObjectsSince(&xMemState);								// print all undeleted objects to debug output
#endif // _DEBUG
}

//---------------------------------------------------------------------------------------------------------------------
// entry point windows applications
INT 
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	return main(0, NULL);
}
//---------------------------------------------------------------------------------------------------------------------
