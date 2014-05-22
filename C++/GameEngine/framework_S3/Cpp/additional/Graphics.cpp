#include "include\Framework.Graphics.Direct3D\Graphics.h"

namespace Framework { namespace Graphics { namespace Direct3D {

    struct VertexPos
    {
        XMFLOAT3 pos;
    };

  // **************************************************************************
  // **************************************************************************
  Graphics::Graphics(Size<uint32> resolution, IWindow* window)
  {
    this->resolution = resolution;
    this->window = window;

    RECT dimensions;
    GetClientRect((HWND)this->window->GetHandle(), &dimensions );

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
    };

    unsigned int totalDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    unsigned int totalFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));
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
    swapChainDescription.Windowed = true;
    swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDescription.Flags = 0;

    unsigned int creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT result;
    unsigned int driver = 0;

    for( driver = 0; driver < totalDriverTypes; ++driver )
    {
        result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0, creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDescription, &this->swapChain, &this->device, &this->featureLevel, &this->context );

        if( SUCCEEDED( result ) )
        {
            driverType = driverTypes[driver];
            break;
        }
    }

    if( FAILED( result ) )
    {
        throw("Failed to create the Direct3D device!");
    }

    ID3D11Texture2D* backBufferTexture;

    result = swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&backBufferTexture );

    if( FAILED( result ) )
    {
        throw( "Failed to get the swap chain back buffer!" );
    }

    result = this->device->CreateRenderTargetView( backBufferTexture, 0, &this->backBufferView );

    if( backBufferTexture )
        backBufferTexture->Release( );

    if( FAILED( result ) )
    {
        throw( "Failed to create the render target view!" );
    }

    this->context->OMSetRenderTargets( 1, &this->backBufferView, 0 );

    D3D11_VIEWPORT viewport;
    viewport.Width = static_cast<float>(resolution.Width);
    viewport.Height = static_cast<float>(resolution.Height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;

    this->context->RSSetViewports( 1, &viewport );

    ID3DBlob* vsBuffer = 0;

    bool compileResult = CompileD3DShader("VertexShader.hlsl", "main", "vs_4_0", &vsBuffer );

    if( compileResult == false )
    {
        MessageBox( 0, L"Error loading vertex shader!", L"Compile Error", MB_OK );
    }

    HRESULT d3dResult;

    d3dResult = this->device->CreateVertexShader(vsBuffer->GetBufferPointer(),
        vsBuffer->GetBufferSize(), 0, &solidColorVS);

    if( FAILED( d3dResult ) )
    {
        if( vsBuffer )
            vsBuffer->Release( );
    }

    D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    unsigned int totalLayoutElements = ARRAYSIZE( solidColorLayout );

    d3dResult = this->device->CreateInputLayout( solidColorLayout, totalLayoutElements,
        vsBuffer->GetBufferPointer( ), vsBuffer->GetBufferSize( ), &inputLayout);

    vsBuffer->Release( );

    if( FAILED( d3dResult ) )
    {
        throw ("Could not create input layout!");
    }

    ID3DBlob* psBuffer = 0;

    compileResult = CompileD3DShader( "PixelShader.hlsl", "main", "ps_4_0", &psBuffer );

    if( compileResult == false )
    {
        MessageBox( 0, L"Error loading pixel shader!", L"Compile Error", MB_OK );
    }

    d3dResult = this->device->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), 0, &solidColorPS);
    
    psBuffer->Release( );

    if( FAILED( d3dResult ) )
    {
        throw ("Could not create pixel shader from resource!");
    }
  }

  // **************************************************************************
  // **************************************************************************
  Graphics::~Graphics()
  {
    SAFE_RELEASE(this->solidColorVS);
    SAFE_RELEASE(this->solidColorPS);
    SAFE_RELEASE(this->inputLayout);
    SAFE_RELEASE(this->vertexBuffer);
    SAFE_RELEASE(this->backBufferView);
    SAFE_RELEASE(this->depthStencilBufferView);
    SAFE_RELEASE(this->context);
    SAFE_RELEASE(this->swapChain);
    SAFE_RELEASE(this->device);
  }

  // ************************************************************************
  // ************************************************************************
  ID3D11Device* Graphics::GetDevice()
  {    
    return this->device;
  }

  // ************************************************************************
  // ************************************************************************
  ID3D11DeviceContext* Graphics::GetContext()
  {
    return this->context;
  }

  // ************************************************************************
  // ************************************************************************
  IDXGISwapChain* Graphics::GetSwapChain()
  {    
    return this->swapChain;
  }

  // ************************************************************************
  // ************************************************************************
  ID3D11RenderTargetView* Graphics::GetBackBufferView()
  {
    return this->backBufferView;
  }

  // ************************************************************************
  // ************************************************************************
  ID3D11DepthStencilView* Graphics::GetDepthStencilBufferView()
  {
    return this->depthStencilBufferView;
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Clear(Color& color)
  {
    float clearColor[4] = { color.GetR(), color.GetG(), color.GetB(), color.GetA() };
    context->ClearRenderTargetView(this->backBufferView, clearColor);
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Clear(uint32 color)
  {
    Color convertedColor = Color(color);

    ID3D11RenderTargetView* renderTarget[1] = { this->backBufferView };
    context->OMSetRenderTargets(1, renderTarget, NULL);

    float clearColor[4] = { convertedColor.GetR(), convertedColor.GetG(), convertedColor.GetB(), convertedColor.GetA() };
    context->ClearRenderTargetView(this->backBufferView, clearColor);
  }


  // **************************************************************************
  // **************************************************************************
  void Graphics::DrawPixel(int32 x, int32 y, Color& color)
  {
    float realX = (static_cast<float>(x) + static_cast<float>(this->resolution.Width)) / (static_cast<float>(this->resolution.Width) * 2.0f);
    float realY = (static_cast<float>(y) + static_cast<float>(this->resolution.Height)) / (static_cast<float>(this->resolution.Height) * 2.0f);

    VertexPos vertices[] =
    {
        XMFLOAT3(x,  y, 0.0f),
        //XMFLOAT3(0.5f, -0.5f, 0.5f),
        //XMFLOAT3(-0.5f, -0.5f, 0.5f)
    };

    D3D11_BUFFER_DESC vertexDesc;
    ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
    vertexDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.ByteWidth = sizeof(VertexPos) * ARRAYSIZE(vertices);

    D3D11_SUBRESOURCE_DATA resourceData;
    ZeroMemory( &resourceData, sizeof(resourceData));
    resourceData.pSysMem = vertices;

    HRESULT d3dResult = this->device->CreateBuffer( &vertexDesc, &resourceData, &vertexBuffer);

    if(FAILED(d3dResult))
    {
        throw ("Could not create buffer object!");
    }
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::DrawPixel(int32 x, int32 y, uint32 color)
  {
      float realX = (static_cast<float>(x) + static_cast<float>(this->resolution.Width / 2)) / (static_cast<float>(this->resolution.Width) * 1.0f);
      float realY = (static_cast<float>(y) + static_cast<float>(this->resolution.Height / 2)) / (static_cast<float>(this->resolution.Height) * 1.0f);
      
      realX = (realX * 2.0f) - 2.0f;
      realY = ((realY * 2.0f) - 2.0f) * (-1.0f);

    VertexPos vertices[] =
    {
        XMFLOAT3(realX,  realY, 0.0f),
        //XMFLOAT3(0.5f, -0.5f, 0.5f),
        //XMFLOAT3(-0.5f, -0.5f, 0.5f)
    };

    D3D11_BUFFER_DESC vertexDesc;
    ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
    vertexDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.ByteWidth = sizeof(VertexPos) * ARRAYSIZE(vertices);

    D3D11_SUBRESOURCE_DATA resourceData;
    ZeroMemory( &resourceData, sizeof(resourceData));
    resourceData.pSysMem = vertices;

    HRESULT d3dResult = this->device->CreateBuffer( &vertexDesc, &resourceData, &vertexBuffer);

    if(FAILED(d3dResult))
    {
        throw ("Could not create buffer object!");
    }
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Present()
  {
    ID3D11RenderTargetView* renderTarget[1] = { this->backBufferView };
    context->OMSetRenderTargets(1, renderTarget, NULL);

    unsigned int stride = sizeof( VertexPos );
    unsigned int offset = 0;

    this->context->IASetInputLayout(this->inputLayout);
    this->context->IASetVertexBuffers( 0, 1, &this->vertexBuffer, &stride, &offset );
    this->context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_POINTLIST );

    this->context->VSSetShader(this->solidColorVS, 0, 0 );
    this->context->PSSetShader(this->solidColorPS, 0, 0 );
    this->context->Draw( 1, 0 );

    this->swapChain->Present(0, 0);
  }

    bool Graphics::CompileD3DShader(string filePath, string entry, string shaderModel, ID3DBlob** buffer)
    {
        DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
        shaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ID3DBlob* errorBuffer = 0;
        HRESULT result;

        result = D3DX11CompileFromFile( filePath, 0, 0, entry, shaderModel, shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

        if( FAILED( result ) )
        {
            if( errorBuffer != 0 )
            {
                OutputDebugStringA((char*)errorBuffer->GetBufferPointer( ) );
                errorBuffer->Release( );
            }

            return false;
        }
    
        if( errorBuffer != 0 )
        {
            errorBuffer->Release( );
        }

        return true;
    }
}}}