#include "include\Framework.Graphics.Direct3D10\Graphics.h"

namespace Framework { namespace Graphics { namespace Direct3D10 {

  // **************************************************************************
  // **************************************************************************
  Graphics::Graphics(Size<uint32> resolution, IWindow* window)
  {
    IDXGIDevice* dxgiDevice = 0;
    IDXGIFactory* factory = 0;
    IDXGIAdapter* adapter = 0;
    ID3D10Texture2D* backBuffer = 0;
    ID3D10Texture2D* depthStencilBuffer = 0;
    D3D10_VIEWPORT viewport;
    D3D10_TEXTURE2D_DESC depthStencilDescription;
    DXGI_SWAP_CHAIN_DESC swapChainDescription;

    this->resolution = resolution;
    this->window = window;

    D3D10CreateDevice(0, D3D10_DRIVER_TYPE_HARDWARE, 0, D3D10_CREATE_DEVICE_SINGLETHREADED | 
      D3D10_CREATE_DEVICE_BGRA_SUPPORT, D3D10_SDK_VERSION, &this->device);

    this->device->QueryInterface(__uuidof(IDXGIDevice), (LPVOID*)&dxgiDevice);
    
    dxgiDevice->GetAdapter(&adapter);

    adapter->GetParent(IID_PPV_ARGS(&factory));

    ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));
    swapChainDescription.BufferDesc.Width = this->resolution.Width;
    swapChainDescription.BufferDesc.Height = this->resolution.Height;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
    swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
    swapChainDescription.SampleDesc.Count = 1;
    swapChainDescription.SampleDesc.Quality = 0;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.BufferCount = 1;
    swapChainDescription.OutputWindow = (HWND)this->window->GetHandle();
    swapChainDescription.Windowed = !this->window->IsFullscreen();
    swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDescription.Flags = 0;

    factory->CreateSwapChain(this->device, &swapChainDescription, &this->swapChain);

    this->swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBuffer);

    this->device->CreateRenderTargetView(backBuffer, 0, &this->backBufferView);

    ZeroMemory(&depthStencilDescription, sizeof(D3D10_TEXTURE2D_DESC));
    depthStencilDescription.Width = this->resolution.Width;
    depthStencilDescription.Height = this->resolution.Height;
    depthStencilDescription.MipLevels = 1;
    depthStencilDescription.ArraySize = 1;
    depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDescription.SampleDesc.Count = 1;
    depthStencilDescription.SampleDesc.Quality = 0;
    depthStencilDescription.Usage = D3D10_USAGE_DEFAULT;
    depthStencilDescription.BindFlags = D3D10_BIND_DEPTH_STENCIL;
    depthStencilDescription.CPUAccessFlags = 0;
    depthStencilDescription.MiscFlags = 0;

    this->device->CreateTexture2D(&depthStencilDescription, 0, &depthStencilBuffer);

    this->device->CreateDepthStencilView(depthStencilBuffer, 0, &this->depthStencilBufferView);

    viewport.Width = this->resolution.Width;
    viewport.Height = this->resolution.Height;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;

    this->device->RSSetViewports(1, &viewport);

    SAFE_RELEASE(backBuffer);
    SAFE_RELEASE(depthStencilBuffer);
    SAFE_RELEASE(factory);
    SAFE_RELEASE(adapter);
    SAFE_RELEASE(dxgiDevice);

    this->resolution = resolution;
    this->window = window;
  }

  // **************************************************************************
  // **************************************************************************
  Graphics::~Graphics()
  {
    SAFE_RELEASE(this->swapChain);
    SAFE_RELEASE(this->backBufferView);
    SAFE_RELEASE(this->depthStencilBufferView);
    SAFE_RELEASE(this->device);
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Clear(Color& color)
  {
    float f = 1.0f / 255.0f;

    float32 r = color.GetR() * f;
    float32 g = color.GetG() * f;
    float32 b = color.GetB() * f;
    float32 a = color.GetA() * f;

    float col[4] = {r, g, b, a};

    this->device->ClearRenderTargetView(this->backBufferView, col);
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Clear(uint32 color)
  {
    float f = 1.0f / 255.0f;

    Color c = color;

    float32 r = c.GetR() * f;
    float32 g = c.GetG() * f;
    float32 b = c.GetB() * f;
    float32 a = c.GetA() * f;

    float col[4] = {r, g, b, a};

    this->device->ClearRenderTargetView(this->backBufferView, col);
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::DrawPixel(int32 x, int32 y, Color& color)
  {

  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::DrawPixel(int32 x, int32 y, uint32 color)
  {

  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Present()
  {
    this->swapChain->Present(0,0);
  }

}}}