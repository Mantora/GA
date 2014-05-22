#pragma once

// Framework specific includes
#include "IApplication.h"
#include "IGraphics.h"

namespace Framework { namespace Core {

  class Win32Application : public IApplication
  {

    // -------------------------------------------------------------------------
    // PUBLIC MEMBERS
    // -------------------------------------------------------------------------

  public:

    /// @brief Creates an instance of Win32Application.
    ///
    /// @param window The window.
    /// @param graphicsID The graphics module ID.
    /// 0x01 = ViperGraphics software renderer
    /// 0x02 = Direct3D renderer
    /// 0x03 = OpenGL renderer
    ///
    Win32Application(IWindow* window, IGraphics* graphics)
    {
      this->window = window;

      this->graphics = graphics;

      this->quit = false;
    }

    /// @brief Gets the application window.
    ///
    /// @returns The application window.
    ///
    IWindow* GetWindow()
    {
      return this->window;
    }

    /// @brief Gets the applications' graphics interface.
    ///
    /// @returns The applications' graphics interface.
    ///
    IGraphics* GetGraphics()
    {
      return this->graphics;
    }

    /// @brief Runs the application.
    ///
    void Run()
    {
      MSG msg;        
      
      if(this->OnInitialize != nullptr)
        this->OnInitialize();

      // Check if a console window exists
      if(GetConsoleWindow() != nullptr)
        FreeConsole();

      // Display main window
      this->window->Show();

      // Enter application loop
      while(!this->quit)
      {
        if(PeekMessage(&msg, 0, 0, 0,PM_REMOVE))
        {
          TranslateMessage(&msg);
          DispatchMessage(&msg);

          if(msg.message == WM_QUIT)
            this->quit = true;
        }

        if(this->OnUpdate != nullptr)
          this->OnUpdate();

        if(this->OnRender != nullptr)
          this->OnRender(this->graphics);
      }

      if(this->OnExit != 0)
        this->OnExit();
    }

    /// @brief Exists the application.
    ///
    void Exit()
    {
      this->quit = true;
    }


    // -------------------------------------------------------------------------
    // PRIVATE MEMBERS
    // -------------------------------------------------------------------------

  private:

    /// @brief The windw.
    ///
    IWindow* window;

    /// @brief A pointer to the graphics interface.
    ///
    IGraphics* graphics;

    /// @brief Indicates whether to quit the application.
    ///
    bool quit;
  };
}}