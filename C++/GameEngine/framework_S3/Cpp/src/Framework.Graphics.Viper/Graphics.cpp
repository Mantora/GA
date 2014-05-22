#include "include\Framework.Graphics.Viper\Graphics.h"

namespace Framework { namespace Graphics { namespace Viper {

  // **************************************************************************
  // **************************************************************************
  Graphics::Graphics(Size<uint32> resolution, IWindow* window)
  {
    this->resolution = resolution;
    this->bpp = 3;
    this->window = window;

    // Create graphics buffer
    this->buffer = new ByteBuffer(this->resolution.Width * this->resolution.Height * this->bpp);

    this->hwnd = (HWND)window->GetHandle();

    this->hdc = GetDC(this->hwnd);

    this->info.bmiHeader.biSize = sizeof(this->info.bmiHeader);
    this->info.bmiHeader.biBitCount = 8 * this->bpp;
    this->info.bmiHeader.biWidth = this->resolution.Width;
    this->info.bmiHeader.biHeight = this->resolution.Height;
    this->info.bmiHeader.biPlanes = 1;
    this->info.bmiHeader.biClrImportant = 0;
    this->info.bmiHeader.biClrUsed = 0;
    this->info.bmiHeader.biCompression = BI_RGB;
    this->info.bmiHeader.biSizeImage = this->resolution.Width * this->resolution.Height * this->bpp;
    this->info.bmiHeader.biXPelsPerMeter = 0;
    this->info.bmiHeader.biYPelsPerMeter = 0;   
  }

  // **************************************************************************
  // **************************************************************************
  Graphics::~Graphics()
  {
    if(this->buffer != 0)
      delete this->buffer;

    if(this->hdc != 0)
      ReleaseDC(this->hwnd, this->hdc);
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Clear(Color& color)
  {
    this->buffer->SetPosition(0);
    for(uint32 i = 0; i < this->buffer->GetSize() / this->bpp; i++)
    {
      this->buffer->Put(color.GetB());
      this->buffer->Put(color.GetG());
      this->buffer->Put(color.GetR());
    }
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Clear(uint32 color)
  {
    this->buffer->SetPosition(0);
    for(uint32 i = 0; i < this->buffer->GetSize() / this->bpp; i++)
    {
      this->buffer->Put((uint8)(color >> 8));
      this->buffer->Put((uint8)(color >> 16));
      this->buffer->Put((uint8)(color >> 24));
    }
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::DrawPixel(int32 x, int32 y, Color& color)
  {
    if(x >= 0 && x < (int32)this->resolution.Width && y >= 0 && y < (int32)this->resolution.Height)
    {
      uint32 index = (x + y * this->resolution.Width) * this->bpp;

      this->buffer->Poke(index, color.GetB());
      this->buffer->Poke(index + 1, color.GetG());
      this->buffer->Poke(index + 2, color.GetR());
    }
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::DrawPixel(int32 x, int32 y, uint32 color)
  {
    if(x >= 0 && x < (int32)this->resolution.Width && y >= 0 && y < (int32)this->resolution.Height)
    {
      uint32 index = (x + y * this->resolution.Width) * this->bpp;

      this->buffer->Poke(index, (uint8)(color >> 8));
      this->buffer->Poke(index + 1, (uint8)(color >> 16));
      this->buffer->Poke(index + 2, (uint8)(color >> 24));
    }
  }

  // **************************************************************************
  // **************************************************************************
  void Graphics::Present()
  {
    RECT client;

    GetClientRect(this->hwnd, &client);

    StretchDIBits(this->hdc, 0, client.bottom - 1, client.right - client.left, (client.bottom - client.top) * -1, 0, 0, 
      this->resolution.Width, this->resolution.Height, this->buffer->GetBuffer(), &this->info, DIB_RGB_COLORS, SRCCOPY);
  }
}}}