#pragma once

// Disable warnings of nonstandard extension used
#pragma warning(disable : 4201)

// Platform specific includes
#include <math.h>

// Framework specific includes
#include "Datatypes.h"

namespace Framework { namespace Core {

  /// @brief A 3D vector with 32-bit floating point precission.
  ///
  struct Vector3F
  {
    // -------------------------------------------------------------------------
    // MEMBERS
    // -------------------------------------------------------------------------

    union
    {
      struct
      {
        float32 X;
        float32 Y;
        float32 Z;
      };

      float32 VECTOR[3];
    };


    // -------------------------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------------------------

    inline Vector3F()
    {
      this->X = this->Y = this->Z = 0.0f;
    }

    inline Vector3F(const Vector3F& vec)
    {
      this->X = vec.X;
      this->Y = vec.Y;
      this->Z = vec.Z;
    }

    inline Vector3F(float32 x, float32 y, float32 z)
    {
      this->X = x;
      this->Y = y;
      this->Z = z;
    }


    // -------------------------------------------------------------------------
    // METHODS
    // -------------------------------------------------------------------------

    /// @brief Gets the length of this vector.
    ///
    /// @returns The length.
    ///
    inline float32 Length() const
    {
      return sqrt(this->Length());
    }

    /// @brief Gets the squared length of this vector.
    ///
    /// @returns The squared length.
    ///
    inline float32 LengthSqrt() const
    {
      return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
    }

    /// @brief Normalizes this vector.
    ///
    inline void Normalized()
    {
      float32 length = this->Length();

      if(length > 0.0f || length < -0.0f)
      {
        this->X /= length;
        this->Y /= length;
        this->Z /= length;
      }
    }

    // -------------------------------------------------------------------------
    // OPERATORS
    // -------------------------------------------------------------------------

    inline operator float32*() const
    {
      return (float32*)this->VECTOR;
    }

    inline Vector3F operator+(const Vector3F& vec) const
    {
      return Vector3F(this->X + vec.X, this->Y + vec.Y, this->Z + vec.Z);
    }

    inline Vector3F operator-(const Vector3F& vec) const
    {
      return Vector3F(this->X - vec.X, this->Y - vec.Y, this->Z - vec.Z);
    }

    inline Vector3F operator*(const Vector3F& vec) const
    {
      return Vector3F(this->X * vec.X, this->Y * vec.Y, this->Z * vec.Z);
    }

    inline Vector3F operator*(const float32& vec) const
    {
      return Vector3F(this->X * vec, this->Y * vec, this->Z * vec);
    }

    inline Vector3F operator*=(const Vector3F& vec)
    {
      this->X *= vec.X;
      this->Y *= vec.Y;
      this->Z *= vec.Z;

      return *this;
    }

    inline Vector3F operator*=(const float32& vec)
    {
      this->X *= vec;
      this->Y *= vec;
      this->Z *= vec;

      return *this;
    }

    inline Vector3F operator+=(const Vector3F& vec)
    {
      this->X += vec.X;
      this->Y += vec.Y;
      this->Z += vec.Z;

      return *this;
    }

    inline Vector3F operator+=(const float32& vec)
    {
      this->X += vec;
      this->Y += vec;
      this->Z += vec;

      return *this;
    }

    inline Vector3F operator-=(const Vector3F& vec)
    {
      this->X -= vec.X;
      this->Y -= vec.Y;
      this->Z -= vec.Z;

      return *this;
    }

    inline Vector3F operator-=(const float32& vec)
    {
      this->X -= vec;
      this->Y -= vec;
      this->Z -= vec;

      return *this;
    }

    inline Vector3F operator=(const Vector3F& vec)
    {
      this->X = vec.X;
      this->Y = vec.Y;
      this->Z = vec.Z;

      return *this;
    }

    inline bool operator==(const Vector3F& vec)
    {
      if(this->X != vec.X)
        return false;

      if(this->Y != vec.Y)
        return false;

      return this->Z == vec.Z;
    }

    inline bool operator!=(const Vector3F& vec)
    {
      if(this->X == vec.X)
        return false;

      if(this->Y == vec.Y)
        return false;

      return this->Z != vec.Z;
    }

    inline Vector3F operator!()
    {
      this->X *= -1.0f;
      this->Y *= -1.0f;
      this->Z *= -1.0f;

      return *this;
    }

    // -------------------------------------------------------------------------
    // STATIC METHODS
    // -------------------------------------------------------------------------

    /// @brief Calculates the dot product of the two specified vectors.
    ///
    /// @param vec1 The first vector.
    /// @param vec2 The second vector.
    ///
    /// @returns The dot product of the two specified vectors.
    ///
    inline static float32 Dot(const Vector3F& vec1, const Vector3F& vec2)
    {
      return vec1.X * vec2.X + vec1.Y * vec2.Y + vec1.Z * vec2.Z;
    }

    /// @brief Calculates the cross product of the two specified vectors.
    ///
    /// @param vec1 The first vector.
    /// @param vec2 The second vector.
    ///
    /// @returns A vector that is perpendicular to the two specified vectors.
    ///
    inline static Vector3F Cross(const Vector3F& vec1, const Vector3F& vec2)
    {
      return Vector3F(
        vec1.Y * vec2.Z - vec1.Z * vec2.Y,
        vec1.Z * vec2.X - vec1.X * vec2.Z,
        vec1.X * vec2.Y - vec1.Y * vec2.X);
    }

    /// @brief Normalizes the specified vector.
    ///
    /// @param vec The vector to normalize.
    ///
    /// @returns The normalized vector of the specified vector.
    ///
    inline static Vector3F Normalize(const Vector3F& vec)
    {
      Vector3F res = vec;

      res.Normalized();

      return res;
    }


    // -------------------------------------------------------------------------
    // STATIC MEMBERS
    // -------------------------------------------------------------------------

    /// @brief A zero vector.
    ///
    static const Vector3F Zero;
    
    /// @brief The unit vector along the x-axis.
    ///
    static const Vector3F UnitX;

    /// @brief The unit vector along the y-axis.
    ///
    static const Vector3F UnitY;

    /// @brief The unit vector along the z-axis.
    ///
    static const Vector3F UnitZ;
  };

}}