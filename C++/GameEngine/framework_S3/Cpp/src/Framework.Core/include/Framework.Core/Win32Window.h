#pragma once

// Platform specific includes
#include <Windows.h>

// Framework specific includes
#include "IWindow.h"

namespace Framework { namespace Core {

  /// @brief The window procedure.
  ///
  LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
    switch(message)
    {
    case WM_KEYDOWN:
      switch(wParam)
      {
      case VK_ESCAPE:
        PostQuitMessage(0);
        break;
      }
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
  }

  /// @brief Implements the creation and handling of a Win32 window.
  ///
  class Win32Window : public IWindow
  {

    // -------------------------------------------------------------------------
    // PUBLIC MEMBERS
    // -------------------------------------------------------------------------

  public:

    /// @brief Creates an instance of Win32Window.
    /// 
    /// @param size The size.
    /// @param isFullscreen Indicates whether the window is in fullscreen mode.
    /// @param title The window title.
    ///
    Win32Window(Size<uint32> size, bool isFullscreen, string title)
    {
      WNDCLASS wc;
      RECT clientRect;
      uint32 screenWidth, screenHeight, captionHeight;

      this->position = position;
      this->size = size;
      this->isFullscreen = isFullscreen;
      this->instance = (HINSTANCE) GetModuleHandle(NULL);
      this->title = title;

      ZeroMemory(&wc, sizeof(WNDCLASS));
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hIcon = LoadIcon(this->instance, IDI_APPLICATION);
      wc.hInstance = this->instance;
      wc.lpfnWndProc = WndProc;
      wc.lpszClassName = title;
      wc.lpszMenuName = 0;
      wc.style = CS_HREDRAW | CS_VREDRAW;

      RegisterClass(&wc);

      // Get the screen dimension and the height of the title bar
      screenWidth = GetSystemMetrics(SM_CXSCREEN);
      screenHeight = GetSystemMetrics(SM_CYSCREEN);
      captionHeight = GetSystemMetrics(SM_CYCAPTION);

      // Calculate the top-left position of the window
      this->position.X = screenWidth / 2 - this->size.Width / 2;
      this->position.Y = screenHeight / 2 - (this->size.Height + captionHeight) / 2;

      clientRect.top = 0;
      clientRect.left = 0;
      clientRect.right = this->size.Width;
      clientRect.bottom = this->size.Height;
      AdjustWindowRect(&clientRect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);

      DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

      if(this->isFullscreen)
        style = WS_POPUP;

      this->hwnd = (uint32)CreateWindow(wc.lpszClassName, wc.lpszClassName, 
        style, this->position.X, this->position.Y, 
        clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
        0, 0, this->instance, 0);
    }

    /// @brief Gets the window position in screen coordinates.
    ///
    /// @returns The position in screen coordinates.
    ///
    Point<uint32> GetPosition()
    {
      return this->position;
    }

    /// @brief Gets the window handle.
    ///
    /// @returns The window handle.
    ///
    uint32 GetHandle()
    {
      return (uint32)this->hwnd;
    }

    /// @brief Indicates whether the window is in fullscreen mode.
    ///
    /// @returns TRUE if fullscreen; else FALSE.
    ///
    bool IsFullscreen()
    {
      return this->isFullscreen;
    }

    /// @brief Gets the window aspect ratio.
    ///
    /// @returns The window aspect ratio.
    ///
    float32 AspectRatio()
    {
      return (float32)this->size.Width / this->size.Height;
    }

    /// @brief Gets the window size in screen coordinates.
    ///
    /// @returns The size in screen coordinates.
    ///
    Size<uint32> GetSize()
    {
      return this->size;
    }

    /// @brief Displays the window onto screen.
    ///
    void Show()
    {
      if(this->isFullscreen)
        ShowWindow((HWND)this->hwnd, SHOW_FULLSCREEN);
      else
        ShowWindow((HWND)this->hwnd, SW_NORMAL);
    }

    /// @brief Hides the window.
    ///
    void Hide()
    {
      ShowWindow((HWND)this->hwnd, SW_HIDE);
    }

    /// @brief Gets the window title.
    ///
    /// @returns The window title.
    ///
    string GetTitle()
    {
      return this->title;
    }


    // -------------------------------------------------------------------------
    // PRIVATE MEMBERS
    // -------------------------------------------------------------------------

  private:

    /// @brief The window position in screen coordinates.
    ///
    Point<uint32> position;

    /// @brief The window size in screen coordinates.
    ///
    Size<uint32> size;

    /// @brief Indicates whether the window is in fullscreen mode.
    ///
    bool isFullscreen;

    /// @brief The window handle.
    ///
    uint32 hwnd;

    /// @brief The application instance.
    ///
    HINSTANCE instance;

    /// @brief The window title.
    ///
    string title;
  };
}}