#pragma once

// Framework specific includes
#include "IWindow.h"
#include "IGraphics.h"
#include "Object.h"

namespace Framework { namespace Core {

  struct IApplication : public virtual Object
  {
    /// @brief The application initialization callback.
    ///
    void (*OnInitialize) ();

    /// @brief The application update callback.
    ///
    void (*OnUpdate) ();

    /// @brief The application render callback.
    ///
    void (*OnRender) (IGraphics*);

    /// @brief The application exit callback.
    ///
    void (*OnExit) ();

    /// @brief Gets the window interface.
    ///
    /// @returns The window interface.
    ///
    virtual IWindow* GetWindow() = 0;

    /// @brief Gets the graphics interface.
    ///
    /// @returns The graphics interface.
    ///
    virtual IGraphics* GetGraphics() = 0;

    /// @brief Runs the application (by entering the application loop).
    ///
    virtual void Run() = 0;

    /// @brief Indicates to exit the application (by leaving the application loop).
    ///
    virtual void Exit() = 0;

    /// @brief Virtual destructor.
    ///
    virtual ~IApplication(){}
  };
}}