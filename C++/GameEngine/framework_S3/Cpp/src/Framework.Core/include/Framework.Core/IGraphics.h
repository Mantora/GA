#pragma once

// Framework specific includes
#include "Color.h"
#include "Object.h"

namespace Framework { namespace Core {

  struct IGraphics : public virtual Object
  {
    /// @brief Clears the view with the specified color.
    ///
    /// @param color A 32 bit RGBA color.
    ///
    virtual void Clear(Color& color) = 0;

    /// @brief Clears the view with the specified color.
    ///
    /// @param color A 32 bit RGBA color.
    ///
    virtual void Clear(uint32 color) = 0;

    /// @brief Draws a pixel at the specified x and y coordinates with specified color.
    ///
    /// @param x The x coordinate.
    /// @param y The y coordinate.
    /// @param color A 32-bit RGBA.
    ///
    virtual void DrawPixel(int32 x, int32 y, Color& color) = 0;

    /// @brief Draws a pixel at the specified x and y coordinates with specified color.
    ///
    /// @param x The x coordinate.
    /// @param y The y coordinate.
    /// @param color A 32-bit RGBA.
    ///
    virtual void DrawPixel(int32 x, int32 y, uint32 color) = 0;

    /// @brief Presents the contents of the video buffer onto screen.
    ///
    virtual void Present() = 0;

    /// @brief Virtual destructor.
    ///
    virtual ~IGraphics(){}
  };
}}