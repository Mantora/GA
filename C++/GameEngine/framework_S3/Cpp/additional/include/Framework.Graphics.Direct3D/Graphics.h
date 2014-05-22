#pragma once

// Platform specific includes
#include <Windows.h>
#include <D3D11.h>
#include <D3DX10.h>
#include <D3DX11.h>
#include <D3Dcompiler.h>
#include <xnamath.h>


// Framework specific includes
#include "Framework.Core\DataTypes.h"
#include "Framework.Core\Size.h"
#include "Framework.Core\IWindow.h"
#include "Framework.Core\IGraphics.h"
#include "Framework.Core\ByteBuffer.h"
#include "Framework.Core\string_.h"

namespace Framework { namespace Graphics { namespace Direct3D {

  using Framework::Core::uint8;
  using Framework::Core::uint16;
  using Framework::Core::uint32;
  using Framework::Core::int32;
  using Framework::Core::IWindow;
  using Framework::Core::IGraphics;
  using Framework::Core::ByteBuffer;
  using Framework::Core::Color;
  using Framework::Core::Size;
  using Framework::Core::string;

  /// @brief Implements the ::Framework::Core::IGraphics interface used as a 
  /// software rasterizer.
  ///
  class Graphics : public IGraphics
  {

    // -------------------------------------------------------------------------
    // PUBLIC MEMBERS
    // -------------------------------------------------------------------------

  public:
    // ------------------------------------------------------------------------
    // Constructors (public)
    // ------------------------------------------------------------------------

    /// @brief Creates an instance of Graphics3D.
    ///
    /// @param hwnd The application window handle.
    /// @param width The application window resolution.
    ///
    Graphics(Size<uint32> resolution, IWindow* window);

    // ------------------------------------------------------------------------
    // Destructor
    // ------------------------------------------------------------------------

    /// @brief The destructor.
    ///
    ~Graphics();

    // ------------------------------------------------------------------------
    // Methods (public)
    // ------------------------------------------------------------------------

    /// @brief Gets the application window resolution.
    ///
    /// @return The application window resolution.
    ///
    SIZE GetResolution();

    /// @brief Gets a pointer to the device instance.
    ///
    /// @returns A pointer to the device instance.
    ///
    ID3D11Device* GetDevice();

    /// @brief Gets a pointer to the context instance.
    ///
    /// @returns A pointer to the context instance.
    ///
    ID3D11DeviceContext* GetContext();

    /// @brief Gets a pointer to the swap-chain instance.
    ///
    /// @returns A pointer to the swap-chain instance.
    ///
    IDXGISwapChain* GetSwapChain();

    /// @brief Gets a pointer to the ID3D11RenderTargetView instance.
    ///
    /// @returns A pointer to the ID3D11RenderTargetView instance.
    ///
    ID3D11RenderTargetView* GetBackBufferView();

    /// @brief Gets a pointer to the depth-stencil-buffer-view instance.
    ///
    /// @returns A pointer to the depth-stencil-buffer-view instance.
    ///
    ID3D11DepthStencilView* GetDepthStencilBufferView();/// @brief Clears the view with the specified color.
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

  private:
    bool CompileD3DShader(string filePath, string entry, string shaderModel, ID3DBlob** buffer);

    /// @brief The resolution.
    ///
    Size<uint32> resolution;

    /// @brief A pointer to the device ID3D11Device object.
    ///
    ID3D11Device* device;    

    /// @brief A pointer to the ID3D11DeviceContext object.
    ///
    ID3D11DeviceContext* context;

    /// @brief A pointer to the backbuffer ID3D11RenderTargetView object.
    ///
    ID3D11RenderTargetView* backBufferView;

    /// @brief A pointer to the depth-stencil-buffer ID3D11DepthStencilView object.
    ///
    ID3D11DepthStencilView* depthStencilBufferView;

    /// @brief A pointer to the swap-chain IDXGISwapChain object.
    ///
    IDXGISwapChain* swapChain; 

    D3D_DRIVER_TYPE driverType;

    D3D_FEATURE_LEVEL featureLevel;

    ID3D11VertexShader* solidColorVS;

    ID3D11PixelShader* solidColorPS;

    ID3D11InputLayout* inputLayout;

    ID3D11Buffer* vertexBuffer;

    HWND hwnd;
    IWindow *window;
   };

  /// @brief The entry point of this module.
  ///
  __declspec(dllexport) IGraphics* CreateGraphics(Size<uint32> resolution, IWindow* window)
  {
    return new Graphics(resolution, window);
  }
}}}