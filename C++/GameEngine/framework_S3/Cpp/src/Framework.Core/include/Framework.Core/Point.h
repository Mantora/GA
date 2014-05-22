#pragma once

// Framework specific includes
#include "Datatypes.h"

namespace Framework { namespace Core {

  template<class T>
  struct Point
  {
    // -------------------------------------------------------------------------
    // MEMBERS
    // -------------------------------------------------------------------------

    /// @brief The x position.
    ///
    T X;

    /// @brief The y position.
    ///
    T Y;

    // -------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------

    /// @brief Creates an instance of Point.
    ///
    inline Point()
    {
      this->X = 0;
      this->Y = 0;
    }

    /// @brief (Copy constructor) Creates an instance of Point.
    ///
    /// @param point A point.
    ///
    inline Point(const Point<T> &point)
    {
      this->X = point.X;
      this->Y = point.Y;
    }

    /// @brief Creates an instance of Point.
    ///
    /// @param x The x position.
    /// @param y The y position.
    //
    inline Point(T x, T y)
    {
      this->X = x;
      this->Y = y;
    }
  };
}}