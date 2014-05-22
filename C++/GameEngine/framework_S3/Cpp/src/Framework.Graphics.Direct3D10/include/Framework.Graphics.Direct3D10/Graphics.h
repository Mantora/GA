#pragma once

// Disable deprecation warnings of macro redefinitions
#pragma warning(disable : 4005)

// Platform specific includes
#include <d3d10.h>
#include <d3dx10.h>
#include <Windows.h>

// Framework specific includes
#include "Framework.Core\Macros.h"
#include "Framework.Core\DataTypes.h"
#include "Framework.Core\Size.h"
#include "Framework.Core\IWindow.h"
#include "Framework.Core\IGraphics.h"
#include "Framework.Core\ByteBuffer.h"

namespace Framework { namespace Graphics { namespace Direct3D10 {

  using Framework::Core::uint8;
  using Framework::Core::uint16;
  using Framework::Core::uint32;
  using Framework::Core::int32;
  using Framework::Core::float32;
  using Framework::Core::IWindow;
  using Framework::Core::IGraphics;
  using Framework::Core::ByteBuffer;
  using Framework::Core::Color;
  using Framework::Core::Size;

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

    /// @brief The window used for output.
    ///
    IWindow* window;

    /// @brief A pointer to the device ID3D11Device object.
    ///
    ID3D10Device* device;    

    /// @brief A pointer to the backbuffer ID3D11RenderTargetView object.
    ///
    ID3D10RenderTargetView* backBufferView;

    /// @brief A pointer to the depth-stencil-buffer ID3D11DepthStencilView object.
    ///
    ID3D10DepthStencilView* depthStencilBufferView;

    /// @brief A pointer to the swap-chain IDXGISwapChain object.
    ///
    IDXGISwapChain* swapChain; 
  };

  /// @brief The entry point of this module.
  ///
  __declspec(dllexport) IGraphics* CreateGraphics(Size<uint32> resolution, IWindow* window)
  {
    return new Graphics(resolution, window);
  }

}}}