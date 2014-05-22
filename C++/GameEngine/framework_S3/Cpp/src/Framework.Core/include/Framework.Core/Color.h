#pragma once

// Framework specific includes
#include "Datatypes.h"

namespace Framework { namespace Core {

  /// @brief Represents a 32 bit RGBA color.
  ///
  struct Color
  {
    // -------------------------------------------------------------------------
    // MEMBERS
    // -------------------------------------------------------------------------

    union
    {
      struct
      {
        /// @brief The red channel.
        ///
        uint8 r;

        /// @brief The green channel.
        ///
        uint8 g;

        /// @brief The blue channel.
        ///
        uint8 b;

        /// @brief The alpha channel.
        ///
        uint8 a;
      } data;

      uint8 buffer[4];
    } color;


    // -------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------

    /// @brief Creates an instance of Color.
    ///
    inline Color()
    {
      this->color.data.r = 0;
      this->color.data.g = 0;
      this->color.data.b = 0;
      this->color.data.a = 255;
    }

    /// @brief (Copy constructor) Creates an instance of Color.
    ///
    inline Color(Color& color)
    {
      this->color.data.r = color.color.data.r;
      this->color.data.g = color.color.data.g;
      this->color.data.b = color.color.data.b;
      this->color.data.a = color.color.data.a;
    }

    /// @brief Creates an instance of Color.
    ///
    /// @param r The red channel value.
    /// @param g The green channel value.
    /// @param b The blue channel value.
    /// @param a The alpha channel value.
    ///
    inline Color(uint8 r, uint8 g, uint8 b, uint8 a)
    {
      this->color.data.r = r;
      this->color.data.g = g;
      this->color.data.b = b;
      this->color.data.a = a;
    }

    /// @brief Creates an instance of Color.
    ///
    /// @param rgba A 32-bit color value encoded as an unsigned int.
    ///
    inline Color(uint32 rgba)
    {
      this->color.data.r = (uint8)(rgba >> 24); 
      this->color.data.g = (uint8)(rgba >> 16);
      this->color.data.b = (uint8)(rgba >> 8);
      this->color.data.a = (uint8)rgba;
    }

    // -------------------------------------------------------------------------
    // PUBLIC METHODS
    // -------------------------------------------------------------------------

    /// @brief Gets the red channels value.
    ///
    /// @returns The red channels value.
    ///
    inline uint8 GetR() { return this->color.data.r; }

    /// @brief Gets the green channels value.
    ///
    /// @returns The green channels value.
    ///
    inline uint8 GetG() { return this->color.data.g; }

    /// @brief Gets the blue channels value.
    ///
    /// @returns The blue channels value.
    ///
    inline uint8 GetB() { return this->color.data.b; }

    /// @brief Gets the alpha channels value.
    ///
    /// @returns The alpha channels value.
    ///
    inline uint8 GetA() { return this->color.data.a; }


    // -------------------------------------------------------------------------
    // OPERATORS
    // -------------------------------------------------------------------------

    inline operator uint8*()
    {
      return &this->color.buffer[0];
    }

    inline operator uint32()
    {
      return (uint32)this->color.data.r << 24 | (uint32)this->color.data.g << 16 | 
        (uint32)this->color.data.b << 8 | this->color.data.a;
    }


    // -------------------------------------------------------------------------
    // STATIC FUNCTIONS
    // -------------------------------------------------------------------------

    /// @brief Converts the specified color to a 32-bit ARGB value.
    ///
    /// @param color A color.
    ///
    /// @returns A 32-bit ARGB value.
    ///
    static uint32 ToARGB(Color& color)
    {
      return (uint32)color.color.data.a << 24 | (uint32)color.color.data.r << 16 | 
        (uint32)color.color.data.g << 8 | color.color.data.b;
    }

    /// @brief Converts the specified color to a 32-bit RGBA value.
    ///
    /// @param color A color.
    ///
    /// @returns A 32-bit RGBA value.
    ///
    static uint32 ToRGBA(Color& color)
    {
      return (uint32)color.color.data.r << 24 | (uint32)color.color.data.g << 16 | (uint32)color.color.data.b << 8 | color.color.data.a;
    }

    /// @brief Converts the specified color to a 32-bit BGRA value.
    ///
    /// @param color A color.
    ///
    /// @returns A 32-bit BGRA value.
    ///
    static uint32 ToBGRA(Color& color)
    {
      return (uint32)color.color.data.b << 24 | (uint32)color.color.data.g << 16 | (uint32)color.color.data.r << 8 | color.color.data.a ;
    }

    /// @brief Converts the specified color to a 32-bit ABGR value.
    ///
    /// @param color A color.
    ///
    /// @returns A 32-bit ABGR value.
    ///
    static uint32 ToABGR(Color& color)
    {
      return (uint32)color.color.data.a << 24 | (uint32)color.color.data.b << 16 | (uint32)color.color.data.g << 8 | color.color.data.r ;
    }

    /// @brief Converts the specified color to a 16-bit R5G6B5 value.
    ///
    /// @param color A color.
    ///
    /// @returns A 16-bit R5G6B5 value.
    ///
    static uint16 ToR5G6B5(Color& color)
    {
      uint8 g = color.color.data.g & 0x3F;
      uint8 b = color.color.data.b & 0x1F;

      return (uint16)color.color.data.r << 11 | (uint16)g << 5 | b;
    }

    /// @brief Converts the specified color to a 16-bit B5G6R5 value.
    ///
    /// @param color A color.
    ///
    /// @returns A 16-bit B5G6R5 value.
    ///
    static uint16 ToB5G6R5(Color& color)
    {
      uint8 g = color.color.data.g & 0x3F;
      uint8 r = color.color.data.r & 0x1F;

      return (uint16)color.color.data.b << 11 | (uint16)g << 5 | r;
    }


    // -------------------------------------------------------------------------
    // STATIC CONST MEMBERS - KNOWN COLORS
    // -------------------------------------------------------------------------

    static const uint32 Black = 0x000000FF;
    static const uint32 White = 0xFFFFFFFF;
    static const uint32 Red = 0xFF0000FF;
    static const uint32 Green = 0x00FF00FF;
    static const uint32 Blue = 0x0000FFFF;
    static const uint32 Turquoise = 0x00FFFFFF;
    static const uint32 Yellow = 0xFFFF00FF;
    static const uint32 Purple = 0xFF00FFFF;
  };
}}