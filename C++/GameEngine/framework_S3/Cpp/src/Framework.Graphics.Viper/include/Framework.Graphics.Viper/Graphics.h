#pragma once

// Platform specific includes
#include <Windows.h>

// Framework specific includes
#include "Framework.Core\DataTypes.h"
#include "Framework.Core\Size.h"
#include "Framework.Core\IWindow.h"
#include "Framework.Core\IGraphics.h"
#include "Framework.Core\ByteBuffer.h"

namespace Framework { namespace Graphics { namespace Viper {

  using Framework::Core::uint8;
  using Framework::Core::uint16;
  using Framework::Core::uint32;
  using Framework::Core::int32;
  using Framework::Core::IWindow;
  using Framework::Core::IGraphics;
  using Framework::Core::ByteBuffer;
  using Framework::Core::Color;
  using Framework::Core::Size;

  /// @brief Implements the ::Framework::Core::IGraphics interface used as a 
  /// software rasterizer.
  ///
  class Graphics : public IGraphics
  {

    // -------------------------------------------------------------------------
    // PUBLIC MEMBERS
    // -------------------------------------------------------------------------

  public:

    /// @brief Creates an instance of Graphics.
    ///
    /// @param resolution The resolution. 
    /// @param window The window to which will be drawn at.
    ///
    Graphics(Size<uint32> resolution, IWindow* window);

    /// @brief Destructor.
    ///
    ~Graphics();

    /// @brief Clears the view with the specified color.
    ///
    /// @param color A 32 bit RGBA color.
    ///
    void Clear(Color& color);

    /// @brief Clears the view with the specified color.
    ///
    /// @param color A 32 bit RGBA color.
    ///
    void Clear(uint32 color);

    /// @brief Draws a pixel at the specified x and y coordinates with specified color.
    ///
    /// @param x The x coordinate.
    /// @param y The y coordinate.
    /// @param color A 32-bit RGBA.
    ///
    void DrawPixel(int32 x, int32 y, Color& color);

    /// @brief Draws a pixel at the specified x and y coordinates with specified color.
    ///
    /// @param x The x coordinate.
    /// @param y The y coordinate.
    /// @param color A 32-bit RGBA color.
    ///
    void DrawPixel(int32 x, int32 y, uint32 color);

    /// @brief Presents the contents of the video buffer onto screen.
    ///
    void Present();

    // -------------------------------------------------------------------------
    // PRIVATE MEMBERS
    // -------------------------------------------------------------------------

  private:

    /// @brief The resolution.
    ///
    Size<uint32> resolution;

    /// @brief Bytes per pixel.
    ///
    uint16 bpp;

    /// @brief A pointer to the graphics buffer.
    ///
    ByteBuffer* buffer;

    /// @brief The window used for output.
    ///
    IWindow* window;

    /// @brief The device context of the current window.
    ///
    HDC hdc;

    /// @brief The handle of the current window.
    ///
    HWND hwnd;

    /// @brief A BITMAPINFO containing information about how to render
    /// the final screen.
    ///
    BITMAPINFO info;
  };

  /// @brief The entry point of this module.
  ///
  __declspec(dllexport) IGraphics* CreateGraphics(Size<uint32> resolution, IWindow* window)
  {
    return new Graphics(resolution, window);
  }
}}}