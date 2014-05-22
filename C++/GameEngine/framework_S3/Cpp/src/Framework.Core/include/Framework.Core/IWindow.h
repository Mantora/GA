#pragma once

// Framework specific includes
#include "DataTypes.h"
#include "Size.h"
#include "Point.h"
#include "string_.h"
#include "Object.h"

namespace Framework { namespace Core {

  /// @brief Base interface for a window.
  ///
  struct IWindow : public virtual Object
  { 
    /// @brief Gets the window position in screen coordinates.
    ///
    /// @returns The position in screen coordinates.
    ///
    virtual Point<uint32> GetPosition() = 0;

    /// @brief Gets the window handle.
    ///
    /// @returns The window handle.
    ///
    virtual uint32 GetHandle() = 0;

    /// @brief Indicates whether the window is in fullscreen mode.
    ///
    /// @returns TRUE if fullscreen; else FALSE.
    ///
    virtual bool IsFullscreen() = 0;

    /// @brief Gets the window aspect ratio.
    ///
    /// @returns The window aspect ratio.
    ///
    virtual float32 AspectRatio() = 0;

    /// @brief Gets the window size in screen coordinates.
    ///
    /// @returns The size in screen coordinates.
    ///
    virtual Size<uint32> GetSize() = 0;

    /// @brief Displays the window onto screen.
    ///
    virtual void Show() = 0;

    /// @brief Hides the window.
    ///
    virtual void Hide() = 0;

    /// @brief Gets the window title.
    ///
    /// @returns The window title.
    ///
    virtual string GetTitle() = 0;

    /// @brief Virtual destructor.
    ///
    virtual ~IWindow(){}
  };
}}