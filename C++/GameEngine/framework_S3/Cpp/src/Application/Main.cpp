#define CDX_FRAMEWORK_DEBUG
#define CDX_FRAMEWORK_PREFIX

#include <Framework.Core\Framework.Core.h>


void Initialize();
void Update();
void Render(cdx_IGraphics*);
void Exit();


int main()
{    
  CDX_FRAMEWORK_DEBUG_BEGIN

  cdx_Ptr<cdx_IWindow> window = cdx_CreateApplicationWindow(cdx_SizeI(720, 480), false, "Titel");

  cdx_Ptr<cdx_IGraphics> graphics = cdx_CreateApplicationGraphics(cdx_SizeI(720, 480), window, "Framework.Graphics.Viper.dll");

  cdx_Ptr<cdx_IApplication> application = cdx_CreateApplication(window, graphics);

  application->OnInitialize = Initialize;
  application->OnUpdate = Update;
  application->OnRender = Render;
  application->OnExit = Exit;

  application->Run();

  CDX_FRAMEWORK_DEBUG_END

  return 0;
}


void Initialize()
{
}


void Update()
{
}


void Render(cdx_IGraphics* graphics)
{
  graphics->Clear(cdx_Color::Red);
  graphics->DrawPixel(10, 10, cdx_Color::Green);
  graphics->Present();
}


void Exit()
{
}