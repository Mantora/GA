#pragma once


// ****************************************************************************
// FRAMEWORK INCLUDE
// ****************************************************************************

#include "Macros.h"
#include "Datatypes.h"
#include "Vector3F.h"
#include "Matrix4F.h"
#include "string_.h"
#include "Object.h"
#include "Ptr.h"
#include "Color.h"
#include "ByteBuffer.h"
#include "Size.h"
#include "Point.h"
#include "IWindow.h"
#include "IApplication.h"
#include "IGraphics.h"


// ****************************************************************************
// FRAMEWORK DEBUG MEMORY DUMP DEFINITIONS
// ****************************************************************************

#if defined (CDX_FRAMEWORK_DEBUG)

  #define _CRTDBG_MAP_ALLOC
  #include <crtdbg.h>

  #define CDX_FRAMEWORK_DEBUG_BEGIN {
  #define CDX_FRAMEWORK_DEBUG_END }_CrtDumpMemoryLeaks();

#else

  #define CDX_FRAMEWORK_DEBUG_BEGIN {
  #define CDX_FRAMEWORK_DEBUG_END };

#endif


// ****************************************************************************
// FRAMEWORK PREFIX DEFINITIONS
// ****************************************************************************

#ifdef CDX_FRAMEWORK_PREFIX

#define cdx_uint8 ::Framework::Core::uint8
#define cdx_int8 ::Framework::Core::int8
#define cdx_uint16 ::Framework::Core::uint16
#define cdx_int16 ::Framework::Core::int16
#define cdx_uint32 ::Framework::Core::uint32
#define cdx_int32 ::Framework::Core::int32
#define cdx_float32 ::Framework::Core::float32
#define cdx_float64 ::Framework::Core::float64
#define cdx_string ::Framework::Core::string
#define cdx_Object ::Framework::Core::Object
#define cdx_Ptr ::Framework::Core::Ptr
#define cdx_Color ::Framework::Core::Color
#define cdx_ByteBuffer ::Framework::Core::ByteBuffer
#define cdx_IWindow ::Framework::Core::IWindow
#define cdx_IApplication ::Framework::Core::IApplication
#define cdx_IGraphics ::Framework::Core::IGraphics
#define cdx_SizeI ::Framework::Core::Size<::Framework::Core::uint32>
#define cdx_PointI ::Framework::Core::Point<::Framework::Core::uint32>
#define cdx_SizeF ::Framework::Core::Size<::Framework::Core::float32>
#define cdx_PointF ::Framework::Core::Point<::Framework::Core::float32>
#define cdx_SizeD ::Framework::Core::Size<::Framework::Core::float64>
#define cdx_PointD ::Framework::Core::Point<::Framework::Core::float64>
#define cdx_Vector3F ::Framework::Core::Vector3F
#define cdx_Matrix4F ::Framework::Core::Matrix4F

#endif


// ****************************************************************************
// FUNCTION POINTER TYPE DEFINITIONS
// ****************************************************************************

typedef ::Framework::Core::IGraphics* (*CREATE_GRAPHICS_FUNCTION) (
  ::Framework::Core::Size<::Framework::Core::uint32> resolution, ::Framework::Core::IWindow* window);


// ****************************************************************************
// FRAMEWORK PLATFORM DEFINITIONS AND INCLUDES
// ****************************************************************************

#if defined(WIN32) || defined(_WIN32)

  #define CDX_PLATFORM_WIN32

  #include <Windows.h>
  #include "Win32Window.h"
  #include "Win32Application.h"

#elif defined(__APPLE__) || defined(__APPLE_CC__)

  #define CDX_PLATFORM_OSX

  #include "OSXWindow.h"

#else

  #error Unsupported Platform!

#endif


// ****************************************************************************
// FRAMEWORK CREATE-FUNCTIONS
// ****************************************************************************

  /// @brief Creates a platform specific application window with specified settings.
  ///
  /// @param position The start location of the window.
  /// @param size The window size.
  /// @param isFullScreen Indicates whether the window is fullscreen.
  ///
  /// @returns A pointer to a ::Framework::Core::IWindow.
  ///
  ::Framework::Core::IWindow* cdx_CreateApplicationWindow(
    ::Framework::Core::Size<::Framework::Core::uint32> size, bool isFullScreen, ::Framework::Core::string title)
  {
#if defined(CDX_PLATFORM_WIN32)

    return new ::Framework::Core::Win32Window(size, isFullScreen, title);

#elif defined(CDX_PLATFORM_OSX)

    #error Unsupported Platform!

#else

    #error Unsupported Platform!

#endif
  }


  /// @brief Creates a platform specific graphics interface with specified settings.
  ///
  /// @param resolution The graphics resolution.
  /// @param window The window on which to draw.
  /// @param moduleName The name of the graphics module to use.
  ///
  /// @returns A pointer to a ::Framework::Core::IGraphics.
  ///
  ::Framework::Core::IGraphics* cdx_CreateApplicationGraphics(::Framework::Core::Size<::Framework::Core::uint32> resolution, 
    ::Framework::Core::IWindow* window, ::Framework::Core::string moduleName)
  {
#if defined(CDX_PLATFORM_WIN32)

    HMODULE module = 0;

    module = LoadLibrary(moduleName);
    
    CREATE_GRAPHICS_FUNCTION function = (CREATE_GRAPHICS_FUNCTION)GetProcAddress(module, "CreateGraphics");

    return function(resolution, window);

#elif defined(CDX_PLATFORM_OSX)

    #error Unsupported Platform!

#else

    #error Unsupported Platform!

#endif
  }


  /// @brief Creates a platform specific application with specified settings.
  ///
  /// @param window A pointer to a ::Framework::Core::IWindow that will be used by the application as the main output window.
  /// @param graphics A pointer to a ::Framework::Core::Graphics that will be used by the application for graphics output.
  ///
  /// @returns A pointer to a ::Framework::Core::IApplication.
  ///
  ::Framework::Core::IApplication* cdx_CreateApplication(::Framework::Core::IWindow* window, 
    ::Framework::Core::IGraphics* graphics)
  {
#if defined(CDX_PLATFORM_WIN32)

    return new ::Framework::Core::Win32Application(window, graphics);

#elif defined(CDX_PLATFORM_OSX)

    #error Unsupported Platform!

#else

    #error Unsupported Platform!

#endif    
  }