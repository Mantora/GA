#pragma once

// Framework specific includes
#include "Datatypes.h"

namespace Framework { namespace Core {

  template<class T>
  struct Size
  {
    // -------------------------------------------------------------------------
    // MEMBERS
    // -------------------------------------------------------------------------

    /// @brief The width.
    ///
    T Width;

    /// @brief The height.
    ///
    T Height;


    // -------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------

    /// @brief Creates an instance of Point.
    ///
    inline Size()
    {
      this->Width = 0;
      this->Height = 0;
    }

    /// @brief (Copy constructor) Creates an instance of Size.
    ///
    /// @param point A Size.
    ///
    inline Size(const Size<T> &size)
    {
      this->Width = size.Width;
      this->Height = size.Height;
    }

    /// @brief Creates an instance of Size.
    ///
    /// @param width The width.
    /// @param height The height.
    //
    inline Size(T width, T height)
    {
      this->Width = width;
      this->Height = height;
    }
  };
}}