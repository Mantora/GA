#pragma once

// Framework specific headers
#include "Datatypes.h"
#include "Vector3F.h"

namespace Framework { namespace Core {

  /// @brief Represents a 4x4 32-bit floating point precission matrix.
  /// 
  struct Matrix4F
  {
    // ---------------------------------------------------------------------------------------------
    // Members
    // ---------------------------------------------------------------------------------------------

    union
    {
      struct
      {
        float32 M11, M12, M13, M14,	
          M21, M22, M23, M24,
          M31, M32, M33, M34,
          M41, M42, M43, M44;
      };
			
      float32	MATRIX16[16];				    		
    };

    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------

    /// @brief Creates a new instance of Matrix4F (identity).
    /// 
    inline Matrix4F() : 
    M11(1.0f), M12(0.0f), M13(0.0f), M14(0.0f),
      M21(0.0f), M22(1.0f), M23(0.0f), M24(0.0f),
      M31(0.0f), M32(0.0f), M33(1.0f), M34(0.0f),
      M41(0.0f), M42(0.0f), M43(0.0f), M44(1.0f)
    {
    };

    /// @brief Creates a new instance of Matrix4F.   
    /// 
    /// @param _m11 Value for Row: 1 Col: 1
    /// @param _m12 Value for Row: 1 Col: 2
    /// @param _m13 Value for Row: 1 Col: 3
    /// @param _m14 Value for Row: 1 Col: 4
    /// @param _m21 Value for Row: 2 Col: 1
    /// @param _m22 Value for Row: 2 Col: 2
    /// @param _m23 Value for Row: 2 Col: 3
    /// @param _m24 Value for Row: 2 Col: 4
    /// @param _m31 Value for Row: 3 Col: 1
    /// @param _m32 Value for Row: 3 Col: 2
    /// @param _m33 Value for Row: 3 Col: 3
    /// @param _m34 Value for Row: 3 Col: 4
    /// @param _m41 Value for Row: 4 Col: 1
    /// @param _m42 Value for Row: 4 Col: 2
    /// @param _m43 Value for Row: 4 Col: 3
    /// @param _m44 Value for Row: 4 Col: 4
    /// 
    inline Matrix4F(float32 _m11, float32 _m12, float32 _m13, float32 _m14, float32 _m21, float32 _m22, float32 _m23, float32 _m24, float32 _m31, float32 _m32, float32 _m33, float32 _m34, float32 _m41, float32 _m42, float32 _m43, float32 _m44) : 
    M11(_m11), M12(_m12), M13(_m13), M14(_m14), M21(_m21), M22(_m22), M23(_m23), M24(_m24), M31(_m31), M32(_m32), M33(_m33), M34(_m34), M41(_m41), M42(_m42), M43(_m43), M44(_m44)
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Operators
    // ---------------------------------------------------------------------------------------------

    inline operator float32* ()	const
    {
      return (float32*)(this->MATRIX16);
    }

    inline Matrix4F operator +(const Matrix4F& m) const	
    {
      return Matrix4F(
        M11 + m.M11, M12 + m.M12, M13 + m.M13, M14 + m.M14, 
        M21 + m.M21, M22 + m.M22, M23 + m.M23, M24 + m.M24, 
        M31 + m.M31, M32 + m.M32, M33 + m.M33, M34 + m.M34, 
        M41 + m.M41, M42 + m.M42, M43 + m.M43, M44 + m.M44);
    }

    inline Matrix4F operator !() const			
    {
      return Matrix4F(-M11, -M12, -M13, -M14, -M21, -M22, -M23, -M24, -M31, -M32, -M33, -M34, -M41, -M42, -M43, -M44);
    }

    inline Matrix4F operator *(const Matrix4F& m) const
    {
      return Matrix4F(
        m.M11 * M11 + m.M21 * M12 + m.M31 * M13 + m.M41 * M14,
        m.M12 * M11 + m.M22 * M12 + m.M32 * M13 + m.M42 * M14,
        m.M13 * M11 + m.M23 * M12 + m.M33 * M13 + m.M43 * M14,
        m.M14 * M11 + m.M24 * M12 + m.M34 * M13 + m.M44 * M14,
        m.M11 * M21 + m.M21 * M22 + m.M31 * M23 + m.M41 * M24,
        m.M12 * M21 + m.M22 * M22 + m.M32 * M23 + m.M42 * M24,
        m.M13 * M21 + m.M23 * M22 + m.M33 * M23 + m.M43 * M24,
        m.M14 * M21 + m.M24 * M22 + m.M34 * M23 + m.M44 * M24,
        m.M11 * M31 + m.M21 * M32 + m.M31 * M33 + m.M41 * M34,
        m.M12 * M31 + m.M22 * M32 + m.M32 * M33 + m.M42 * M34,
        m.M13 * M31 + m.M23 * M32 + m.M33 * M33 + m.M43 * M34,
        m.M14 * M31 + m.M24 * M32 + m.M34 * M33 + m.M44 * M34,
        m.M11 * M41 + m.M21 * M42 + m.M31 * M43 + m.M41 * M44,
        m.M12 * M41 + m.M22 * M42 + m.M32 * M43 + m.M42 * M44,
        m.M13 * M41 + m.M23 * M42 + m.M33 * M43 + m.M43 * M44,
        m.M14 * M41 + m.M24 * M42 + m.M34 * M43 + m.M44 * M44);
    }

    inline Matrix4F operator *(const float32 f) const
    {
      return Matrix4F(
        M11 * f, M12 * f, M13 * f, M14 * f,
        M21 * f, M22 * f, M23 * f, M24 * f,
        M31 * f, M32 * f, M33 * f, M34 * f,
        M41 * f, M42 * f, M43 * f, M44 * f);
    }

    inline Vector3F operator *(const Vector3F& vec) const
    {
      return Vector3F(
        vec.X * M11 + vec.Y * M21 + vec.Z * M31 + M41,
        vec.X * M12 + vec.Y * M22 + vec.Z * M32 + M42,
        vec.X * M13 + vec.Y * M23 + vec.Z * M33 + M43);
    }

    inline friend Vector3F operator *(const Vector3F& vec, const Matrix4F& m)
    {
      return Vector3F(
        vec.X * m.M11 + vec.Y * m.M21 + vec.Z * m.M31 + m.M41,
        vec.X * m.M12 + vec.Y * m.M22 + vec.Z * m.M32 + m.M42,
        vec.X * m.M13 + vec.Y * m.M23 + vec.Z * m.M33 + m.M43);
    }

    inline Matrix4F operator /(const Matrix4F& m) const 
    {
      return *this *Matrix4F::Invert(m);
    }

    inline friend Matrix4F operator *(const float32 f, const Matrix4F& m) 
    {
      return Matrix4F(
        m.M11 * f, m.M12 * f, m.M13 * f, m.M14 * f,
        m.M21 * f, m.M22 * f, m.M23 * f, m.M24 * f,
        m.M31 * f, m.M32 * f, m.M33 * f, m.M34 * f,
        m.M41 * f, m.M42 * f, m.M43 * f, m.M44 * f);
    }

    inline Matrix4F operator +=(const Matrix4F& m)
    {
      M11 += m.M11; M12 += m.M12; M13 += m.M13; M14 += m.M14;
      M21 += m.M21; M22 += m.M22; M23 += m.M23; M24 += m.M24;
      M31 += m.M31; M32 += m.M32; M33 += m.M33; M34 += m.M34;
      M41 += m.M41; M42 += m.M42; M43 += m.M43; M44 += m.M44;

      return *this;
    }

    inline Matrix4F operator *=(const Matrix4F& m) 
    {
      *this = *this * m; 

      return *this;
    }

    inline Matrix4F operator *=(const float32 f)
    {
      M11 *= f; M12 *= f; M13 *= f; M14 *= f;
      M21 *= f; M22 *= f; M23 *= f; M24 *= f;
      M31 *= f; M32 *= f; M33 *= f; M34 *= f;
      M41 *= f; M42 *= f; M43 *= f; M44 *= f;

      return *this;
    }

    inline bool operator ==(const Matrix4F& m) const
    {
      if(M11 != m.M11) return false;
      if(M12 != m.M12) return false;
      if(M13 != m.M13) return false;
      if(M14 != m.M14) return false;
      if(M21 != m.M21) return false;
      if(M22 != m.M22) return false;
      if(M23 != m.M23) return false;
      if(M24 != m.M24) return false;
      if(M31 != m.M31) return false;
      if(M32 != m.M32) return false;
      if(M33 != m.M33) return false;
      if(M34 != m.M34) return false;
      if(M41 != m.M41) return false;
      if(M42 != m.M42) return false;
      if(M43 != m.M43) return false;

      return M44 == m.M44;
    }

    inline bool operator !=(const Matrix4F& m) const
    {
      if(M11 != m.M11) return true;
      if(M12 != m.M12) return true;
      if(M13 != m.M13) return true;
      if(M14 != m.M14) return true;
      if(M21 != m.M21) return true;
      if(M22 != m.M22) return true;
      if(M23 != m.M23) return true;
      if(M24 != m.M24) return true;
      if(M31 != m.M31) return true;
      if(M32 != m.M32) return true;
      if(M33 != m.M33) return true;
      if(M34 != m.M34) return true;
      if(M41 != m.M41) return true;
      if(M42 != m.M42) return true;
      if(M43 != m.M43) return true;

      return M44 != m.M44;
    }


    // ---------------------------------------------------------------------------------------------
    // Methods / Static
    // ---------------------------------------------------------------------------------------------

    /// @brief Creates an identity matrix.
    /// 
    /// @returns An identity matrix.
    /// 
    inline static const Matrix4F Identity()
    {
      return Matrix4F(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    }

     
    /// @brief Multiplies the given two matrices.
    ///
    /// @param mat1 The first matrix.
    /// @param mat2 The second matrix.
    ///
    /// @returns A matrix representing the result of the multiplication.
    ///
    inline static Matrix4F Multiply(const Matrix4F& mat1, const Matrix4F& mat2) 
    {
      return Matrix4F(
        mat1.M11 * mat2.M11 + mat1.M21 * mat2.M12 + mat1.M31 * mat2.M13 + mat1.M41 * mat2.M14,
        mat1.M12 * mat2.M11 + mat1.M22 * mat2.M12 + mat1.M32 * mat2.M13 + mat1.M42 * mat2.M14,
        mat1.M13 * mat2.M11 + mat1.M23 * mat2.M12 + mat1.M33 * mat2.M13 + mat1.M43 * mat2.M14,
        mat1.M14 * mat2.M11 + mat1.M24 * mat2.M12 + mat1.M34 * mat2.M13 + mat1.M44 * mat2.M14,
        mat1.M11 * mat2.M21 + mat1.M21 * mat2.M22 + mat1.M31 * mat2.M23 + mat1.M41 * mat2.M24,
        mat1.M12 * mat2.M21 + mat1.M22 * mat2.M22 + mat1.M32 * mat2.M23 + mat1.M42 * mat2.M24,
        mat1.M13 * mat2.M21 + mat1.M23 * mat2.M22 + mat1.M33 * mat2.M23 + mat1.M43 * mat2.M24,
        mat1.M14 * mat2.M21 + mat1.M24 * mat2.M22 + mat1.M34 * mat2.M23 + mat1.M44 * mat2.M24,
        mat1.M11 * mat2.M31 + mat1.M21 * mat2.M32 + mat1.M31 * mat2.M33 + mat1.M41 * mat2.M34,
        mat1.M12 * mat2.M31 + mat1.M22 * mat2.M32 + mat1.M32 * mat2.M33 + mat1.M42 * mat2.M34,
        mat1.M13 * mat2.M31 + mat1.M23 * mat2.M32 + mat1.M33 * mat2.M33 + mat1.M43 * mat2.M34,
        mat1.M14 * mat2.M31 + mat1.M24 * mat2.M32 + mat1.M34 * mat2.M33 + mat1.M44 * mat2.M34,
        mat1.M11 * mat2.M41 + mat1.M21 * mat2.M42 + mat1.M31 * mat2.M43 + mat1.M41 * mat2.M44,
        mat1.M12 * mat2.M41 + mat1.M22 * mat2.M42 + mat1.M32 * mat2.M43 + mat1.M42 * mat2.M44,
        mat1.M13 * mat2.M41 + mat1.M23 * mat2.M42 + mat1.M33 * mat2.M43 + mat1.M43 * mat2.M44,
        mat1.M14 * mat2.M41 + mat1.M24 * mat2.M42 + mat1.M34 * mat2.M43 + mat1.M44 * mat2.M44);
    }

     
    /// @brief Multiplies the given matrix with the given scalar.
    ///
    /// @param mat The matrix.
    /// @param val The scalar.
    ///
    /// @returns A matrix representing the result of the multiplication.
    ///
    inline static Matrix4F Multiply(const Matrix4F& mat, const float32 val)
    {
      return Matrix4F(
        mat.M11 * val, mat.M12 * val, mat.M13 * val, mat.M14 * val,
        mat.M21 * val, mat.M22 * val, mat.M23 * val, mat.M24 * val,
        mat.M31 * val, mat.M32 * val, mat.M33 * val, mat.M34 * val,
        mat.M41 * val, mat.M42 * val, mat.M43 * val, mat.M44 * val);
    }

     
    /// @brief Multiplies the given vector with the given matrix.
    ///
    /// @param mat The matrix.
    /// @param val The vector.
    ///
    /// @returns A matrix representing the result of the multiplication.
    ///
    inline static Vector3F Multiply(const Matrix4F& mat, const Vector3F& vec)
    {
      return Vector3F(
        vec.X * mat.M11 + vec.Y * mat.M21 + vec.Z * mat.M31 + mat.M41,
        vec.X * mat.M12 + vec.Y * mat.M22 + vec.Z * mat.M32 + mat.M42,
        vec.X * mat.M13 + vec.Y * mat.M23 + vec.Z * mat.M33 + mat.M43);
    }

     
    /// @brief Transforms the given vector by the given matrix.
    ///
    /// @param mat The matrix.
    /// @param val The vector.
    ///
    /// @returns A matrix representing the result of the transformation.
    ///
    inline static Vector3F Transform(const Matrix4F& mat, const Vector3F& vec)
    {
      return Vector3F(
        vec.X * mat.M11 + vec.Y * mat.M21 + vec.Z * mat.M31 + mat.M41,
        vec.X * mat.M12 + vec.Y * mat.M22 + vec.Z * mat.M32 + mat.M42,
        vec.X * mat.M13 + vec.Y * mat.M23 + vec.Z * mat.M33 + mat.M43);
    }

     
    /// @brief Divides the given two matrices.
    ///
    /// @param mat1 The first matrix.
    /// @param mat2 The second matrix.
    ///
    /// @returns A matrix representing the result of the division.
    ///
    inline static Matrix4F Divide(const Matrix4F& mat1, const Matrix4F& mat2)
    {
      return mat1 * Matrix4F::Invert(mat2);
    }

     
    /// @brief Divides the given matrix using the given scalar.
    ///
    /// @param mat The matrix.
    /// @param val The scalar.
    ///
    /// @returns A matrix representing the result of the division.
    ///
    inline static Matrix4F Divide(const Matrix4F& mat, const float32 val)
    {
      return Matrix4F(
        mat.M11 / val, mat.M12 / val, mat.M13 / val, mat.M14 / val,
        mat.M21 / val, mat.M22 / val, mat.M23 / val, mat.M24 / val,
        mat.M31 / val, mat.M32 / val, mat.M33 / val, mat.M34 / val,
        mat.M41 / val, mat.M42 / val, mat.M43 / val, mat.M44 / val);
    }

     
    /// @brief Creates a translation matrix.
    ///
    /// @param vec A vector indication the translation.
    ///
    /// @returns A translation matrix.
    ///
    inline static Matrix4F Translation(const Vector3F& vec)
    {
      return Matrix4F(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        vec.X, vec.Y, vec.Z, 1.0f);
    }

     
    /// @brief Creates a rotation matrix around the x-axis.
    ///
    /// @param angle An angle in radians.
    ///
    /// @returns A rotation matrix around the x-axis.
    ///
    inline static Matrix4F RotationX(const float32 angle)
    {
      Matrix4F result;

      result.M11 = 1.0f; result.M12 = 0.0f; result.M13 = 0.0f; result.M14 = 0.0f;
      result.M21 = 0.0f;                                       result.M24 = 0.0f;
      result.M31 = 0.0f;                                       result.M34 = 0.0f;
      result.M41 = 0.0f; result.M42 = 0.0f; result.M43 = 0.0f; result.M44 = 1.0f;

      result.M22 = result.M33 = cosf(angle);
      result.M23 = sinf(angle);
      result.M32 = -result.M23;

      return result;
    }

     
    /// @brief Creates a rotation matrix around the y-axis.
    ///
    /// @param angle An angle in radians.
    ///
    /// @returns A rotation matrix around the y-axis.
    ///
    inline static Matrix4F RotationY(const float32 angle)
    {
      Matrix4F result;

      result.M12 = 0.0f;                    result.M14 = 0.0f;
      result.M21 = 0.0f; result.M22 = 1.0f; result.M23 = 0.0f; result.M24 = 0.0f;
      result.M32 = 0.0f;                    result.M34 = 0.0f;
      result.M41 = 0.0f; result.M42 = 0.0f; result.M43 = 0.0f; result.M44 = 1.0f;

      result.M11 = result.M33 = cosf(angle);
      result.M31 = sinf(angle);
      result.M13 = -result.M31;

      return result;
    }

    
    /// @brief Creates a rotation matrix around the z-axis.
    ///
    /// @param angle An angle in radians.
    ///
    /// @returns A rotation matrix around the z-axis.
    ///
    inline static Matrix4F RotationZ(const float32 angle)
    {
      Matrix4F result;

      result.M13 = 0.0f; result.M14 = 0.0f;
      result.M23 = 0.0f; result.M24 = 0.0f;
      result.M31 = 0.0f; result.M32 = 0.0f; result.M33 = 1.0f; result.M34 = 0.0f;
      result.M41 = 0.0f; result.M42 = 0.0f; result.M43 = 0.0f; result.M44 = 1.0f;

      result.M11 = result.M22 = cosf(angle);
      result.M12 = sinf(angle);
      result.M21 = -result.M12;

      return result;
    }

     
    /// @brief Creates a rotation matrix around the x, y and z-axis.
    ///
    /// @param angleX An angle in radians for the x-axis.
    /// @param angleY An angle in radians for the y-axis.
    /// @param angleZ An angle in radians for the z-axis.
    ///
    /// @returns A rotation matrix around the x, y and z-axis.
    ///
    inline static Matrix4F Rotation(const float32 angleX, const float32 angleY, const float32 angleZ)
    {
      return Matrix4F::RotationZ(angleZ) * Matrix4F::RotationX(angleX) * Matrix4F::RotationY(angleY);
    }

     
    /// @brief Creates a rotation matrix around an axis defined 
    /// by a given vector.
    ///
    /// @param vec A vector indicating the axis.
    /// @param angle An angle in radians.
    ///
    /// @returns A rotation matrix around an axis defined by vec.
    ///
    inline static Matrix4F RotationAxis(const Vector3F& vec, const float32 angle)
    {      
      float32 fSin(sinf((float32)-angle));
      float32 fCos(cosf((float32)-angle));

      Vector3F vAxis = Vector3F::Normalize(vec);

      return Matrix4F(
        (vAxis.X * vAxis.X) * (1.0f - fCos) + fCos,
        (vAxis.X * vAxis.Y) * (1.0f - fCos) - (vAxis.Z * fSin),
        (vAxis.X * vAxis.Z) * (1.0f - fCos) + (vAxis.Y * fSin),
        0.0f,
        (vAxis.Y * vAxis.X) * (1.0f - fCos) + (vAxis.Z * fSin),
        (vAxis.Y * vAxis.Y) * (1.0f - fCos) + fCos,
        (vAxis.Y * vAxis.Z) * (1.0f - fCos) - (vAxis.X * fSin),
        0.0f,
        (vAxis.Z * vAxis.X) * (1.0f - fCos) - (vAxis.Y * fSin),
        (vAxis.Z * vAxis.Y) * (1.0f - fCos) + (vAxis.X * fSin),
        (vAxis.Z * vAxis.Z) * (1.0f - fCos) + fCos,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    }

     
    /// @brief Creates a scaling matrix.
    ///
    /// @param factor The scale factor.
    ///
    /// @returns A scaling matrix.
    ///
    inline static Matrix4F Scale(const float32 factor)
    {
      return Matrix4F(
        factor, 0.0f, 0.0f, 0.0f,
        0.0f, factor, 0.0f, 0.0f,
        0.0f, 0.0f, factor, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    }

     
    /// @brief Creates a scaling matrix.
    ///
    /// @param vec A vector indication the scaling factor (x/y/z direction).
    ///
    /// @returns A scaling matrix.
    ///
    inline static Matrix4F Scale(const Vector3F& vec)
    {
      return Matrix4F(
        vec.X, 0.0f, 0.0f, 0.0f,
        0.0f, vec.Y, 0.0f, 0.0f,
        0.0f, 0.0f, vec.Z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
    }

     
    /// @brief Creates a matrix given by the three axis.
    ///
    /// @param vXAxis A vector indication the x-axis.
    /// @param vYAxis A vector indication the y-axis.
    /// @param vZAxis A vector indication the z-axis.
    ///
    /// @returns A matrix.
    ///
    inline static Matrix4F Axes(const Vector3F& vXAxis, const Vector3F& vYAxis, const Vector3F& vZAxis)
    {
      return Matrix4F(
        vXAxis.X, vXAxis.Y, vXAxis.Z, 0.0f,
        vYAxis.X, vYAxis.Y, vYAxis.Z, 0.0f,
        vZAxis.X, vZAxis.Y, vZAxis.Z, 0.0f,
        0.0f,     0.0f,     0.0f,     1.0f);
    }

     
    /// @brief Calculates the determinant for the given matrix.
    ///
    /// @param mat The matrix to calculate the determinant of.
    ///
    /// @returns The determinant of the given matrix.
    ///
    inline static float32 Determinant(const Matrix4F& mat)
    {
      float32 a =  mat.M11 * (
        (mat.M22 * mat.M33 * mat.M44) + (mat.M23 * mat.M34 * mat.M42) + (mat.M24 * mat.M32 * mat.M43) -
        (mat.M24 * mat.M33 * mat.M42) - (mat.M23 * mat.M32 * mat.M44) - (mat.M22 * mat.M34 * mat.M43));

      float32 b =  mat.M21 * (
        (mat.M12 * mat.M33 * mat.M44) + (mat.M32 * mat.M34 * mat.M42) + (mat.M14 * mat.M32 * mat.M43) -
        (mat.M14 * mat.M33 * mat.M42) - (mat.M13 * mat.M32 * mat.M44) - (mat.M12 * mat.M34 * mat.M43));

      float32 c =  mat.M31 * (
        (mat.M12 * mat.M23 * mat.M44) + (mat.M13 * mat.M24 * mat.M42) + (mat.M14 * mat.M22 * mat.M43) -
        (mat.M14 * mat.M23 * mat.M42) - (mat.M13 * mat.M22 * mat.M44) - (mat.M12 * mat.M24 * mat.M43));

      float32 d =  mat.M41 * (
        (mat.M12 * mat.M23 * mat.M34) + (mat.M13 * mat.M24 * mat.M32) + (mat.M14 * mat.M22 * mat.M33) -
        (mat.M14 * mat.M23 * mat.M32) - (mat.M13 * mat.M22 * mat.M34) - (mat.M12 * mat.M24 * mat.M33));

      return a - b + c - d;
    }

     
    /// @brief Inverts the given matrix.
    ///
    /// @param mat The matrix to invert.
    ///
    /// @returns The inverted matrix of the given matrix.
    ///
    inline static Matrix4F Invert(const Matrix4F& mat)
    {    
      Matrix4F result;

      float32 invDet = 1.0f / Matrix4F::Determinant(mat);

      result.M11 = invDet * (mat.M23*mat.M34*mat.M42 - mat.M24*mat.M33*mat.M42 + mat.M24*mat.M32*mat.M43 - mat.M22*mat.M34*mat.M43 - mat.M23*mat.M32*mat.M44 + mat.M22*mat.M33*mat.M44);
      result.M12 = invDet * (mat.M14*mat.M33*mat.M42 - mat.M13*mat.M34*mat.M42 - mat.M14*mat.M32*mat.M43 + mat.M12*mat.M34*mat.M43 + mat.M13*mat.M32*mat.M44 - mat.M12*mat.M33*mat.M44);
      result.M13 = invDet * (mat.M13*mat.M24*mat.M42 - mat.M14*mat.M23*mat.M42 + mat.M14*mat.M22*mat.M43 - mat.M12*mat.M24*mat.M43 - mat.M13*mat.M22*mat.M44 + mat.M12*mat.M23*mat.M44);
      result.M14 = invDet * (mat.M14*mat.M23*mat.M32 - mat.M13*mat.M24*mat.M32 - mat.M14*mat.M22*mat.M33 + mat.M12*mat.M24*mat.M33 + mat.M13*mat.M22*mat.M34 - mat.M12*mat.M23*mat.M34);
      result.M21 = invDet * (mat.M24*mat.M33*mat.M41 - mat.M23*mat.M34*mat.M41 - mat.M24*mat.M31*mat.M43 + mat.M21*mat.M34*mat.M43 + mat.M23*mat.M31*mat.M44 - mat.M21*mat.M33*mat.M44);
      result.M22 = invDet * (mat.M13*mat.M34*mat.M41 - mat.M14*mat.M33*mat.M41 + mat.M14*mat.M31*mat.M43 - mat.M11*mat.M34*mat.M43 - mat.M13*mat.M31*mat.M44 + mat.M11*mat.M33*mat.M44);
      result.M23 = invDet * (mat.M14*mat.M23*mat.M41 - mat.M13*mat.M24*mat.M41 - mat.M14*mat.M21*mat.M43 + mat.M11*mat.M24*mat.M43 + mat.M13*mat.M21*mat.M44 - mat.M11*mat.M23*mat.M44);
      result.M24 = invDet * (mat.M13*mat.M24*mat.M31 - mat.M14*mat.M23*mat.M31 + mat.M14*mat.M21*mat.M33 - mat.M11*mat.M24*mat.M33 - mat.M13*mat.M21*mat.M34 + mat.M11*mat.M23*mat.M34);
      result.M31 = invDet * (mat.M22*mat.M34*mat.M41 - mat.M24*mat.M32*mat.M41 + mat.M24*mat.M31*mat.M42 - mat.M21*mat.M34*mat.M42 - mat.M22*mat.M31*mat.M44 + mat.M21*mat.M32*mat.M44);
      result.M32 = invDet * (mat.M14*mat.M32*mat.M41 - mat.M12*mat.M34*mat.M41 - mat.M14*mat.M31*mat.M42 + mat.M11*mat.M34*mat.M42 + mat.M12*mat.M31*mat.M44 - mat.M11*mat.M32*mat.M44);
      result.M33 = invDet * (mat.M12*mat.M24*mat.M41 - mat.M14*mat.M22*mat.M41 + mat.M14*mat.M21*mat.M42 - mat.M11*mat.M24*mat.M42 - mat.M12*mat.M21*mat.M44 + mat.M11*mat.M22*mat.M44);
      result.M34 = invDet * (mat.M14*mat.M22*mat.M31 - mat.M12*mat.M24*mat.M31 - mat.M14*mat.M21*mat.M32 + mat.M11*mat.M24*mat.M32 + mat.M12*mat.M21*mat.M34 - mat.M11*mat.M22*mat.M34);
      result.M41 = invDet * (mat.M23*mat.M32*mat.M41 - mat.M22*mat.M33*mat.M41 - mat.M23*mat.M31*mat.M42 + mat.M21*mat.M33*mat.M42 + mat.M22*mat.M31*mat.M43 - mat.M21*mat.M32*mat.M43);
      result.M42 = invDet * (mat.M12*mat.M33*mat.M41 - mat.M13*mat.M32*mat.M41 + mat.M13*mat.M31*mat.M42 - mat.M11*mat.M33*mat.M42 - mat.M12*mat.M31*mat.M43 + mat.M11*mat.M32*mat.M43);
      result.M43 = invDet * (mat.M13*mat.M22*mat.M41 - mat.M12*mat.M23*mat.M41 - mat.M13*mat.M21*mat.M42 + mat.M11*mat.M23*mat.M42 + mat.M12*mat.M21*mat.M43 - mat.M11*mat.M22*mat.M43);
      result.M44 = invDet * (mat.M12*mat.M23*mat.M31 - mat.M13*mat.M22*mat.M31 + mat.M13*mat.M21*mat.M32 - mat.M11*mat.M23*mat.M32 - mat.M12*mat.M21*mat.M33 + mat.M11*mat.M22*mat.M33);

      return result;
    }

     
    /// @brief Transposes the given matrix.
    ///
    /// @param mat The matrix to transpose.
    ///
    /// @returns The transposed matrix of the given matrix.
    ///
    inline static Matrix4F Transpose(const Matrix4F& mat)
    {
      return Matrix4F(
        mat.M11, mat.M21, mat.M31, mat.M41,
        mat.M12, mat.M22, mat.M32, mat.M42,
        mat.M13, mat.M23, mat.M33, mat.M43,
        mat.M14, mat.M24, mat.M34, mat.M44);
    }

     
    /// @brief Calculates a left-handed view matrix (virtual camera).
    ///
    /// @param pos The position of the virtual camera.
    /// @param look The look direction of the virtual camera.
    /// @param up The up vector of the virtual camera.
    ///
    /// @returns A left-handed view matrix (virtual camera).
    ///
    inline static Matrix4F ViewLH(const Vector3F& pos, const Vector3F& look, const Vector3F& up)
    {      
      Vector3F zAxis = Vector3F::Normalize(pos - look);
      Vector3F xAxis = Vector3F::Normalize(Vector3F::Cross(up, zAxis)); 
      Vector3F yAxis = Vector3F::Normalize(Vector3F::Cross(zAxis, xAxis)); 

      return Matrix4F(
        xAxis.X, yAxis.X, zAxis.X, 0.0f,
        xAxis.Y, yAxis.Y, zAxis.Y, 0.0f,
        xAxis.Z, yAxis.Z, zAxis.Z, 0.0f,
        -1 * Vector3F::Dot(xAxis, pos), 
        -1 * Vector3F::Dot(yAxis, pos), 
        -1 * Vector3F::Dot(zAxis, pos), 1.0f);
    }

     
    /// @brief Calculates a right-handed view matrix (virtual camera).
    ///
    /// @param pos The position of the virtual camera.
    /// @param look The look direction of the virtual camera.
    /// @param up The up vector of the virtual camera.
    ///
    /// @returns A right-handed view matrix (virtual camera).
    ///
    inline static Matrix4F ViewRH(const Vector3F& pos, const Vector3F& look, const Vector3F& up)
    {      
      Vector3F zAxis = Vector3F::Normalize(look - pos);
      Vector3F xAxis = Vector3F::Normalize(Vector3F::Cross(up, zAxis)); 
      Vector3F yAxis = Vector3F::Normalize(Vector3F::Cross(zAxis, xAxis)); 

      return Matrix4F(
        xAxis.X, yAxis.X, zAxis.X, 0.0f,
        xAxis.Y, yAxis.Y, zAxis.Y, 0.0f,
        xAxis.Z, yAxis.Z, zAxis.Z, 0.0f,
        -1 * Vector3F::Dot(xAxis, pos), 
        -1 * Vector3F::Dot(yAxis, pos), 
        -1 * Vector3F::Dot(zAxis, pos), 1.0f);
    }

     
    /// @brief Calculates a left-handed perspective projection matrix 
    /// by taking the field of view (fov) into account.
    ///
    /// @param fov The field of view.
    /// @param aspect The aspect ratio (screen_width / screen_height).
    /// @param zNear The near plane.
    /// @param zFar The far plane.
    ///
    /// @returns A left-handed perspective projection matrix.
    ///
    inline static Matrix4F ProjectionPerspectiveFovLH(const float32 fov,	const float32 aspect, const float32 zNear, const float32 zFar)
    {
      float32 xScale = 1.0f / tan(fov / 2.0f);
      float32 yScale = xScale / aspect;

      return Matrix4F(
        yScale, 0.0f, 0.0f, 0.0f,
        0.0f, xScale, 0.0f, 0.0f,
        0.0f, 0.0f, zFar / (zFar - zNear), 1.0f,
        0.0f, 0.0f, (-zNear * zFar) / (zFar - zNear), 0.0f);
    }

     
    /// @brief Calculates a right-handed perspective projection matrix 
    /// by taking the field of view (fov) into account.
    ///
    /// @param fov The field of view.
    /// @param aspect The aspect ratio (screen_width / screen_height).
    /// @param zNear The near plane.
    /// @param zFar The far plane.
    ///
    /// @returns A right-handed perspective projection matrix.
    ///
    inline static Matrix4F ProjectionPerspectiveFovRH(const float32 fov,	const float32 aspect, const float32 zNear, const float32 zFar)
    {
      float32 xScale = 1.0f / tan(fov / 2.0f);
      float32 yScale = xScale / aspect;

      return Matrix4F(
        yScale, 0.0f, 0.0f, 0.0f,
        0.0f, xScale, 0.0f, 0.0f,
        0.0f, 0.0f, zFar / (zNear - zFar), -1.0f,
        0.0f, 0.0f, (zNear * zFar) / (zNear - zFar), 0.0f);
    }

     
    /// @brief Calculates a left-handed perspective projection matrix. 
    ///
    /// @param width The width of the viewport (screen).
    /// @param height The height of the viewport (screen).
    /// @param zNear The near plane.
    /// @param zFar The far plane.
    ///
    /// @returns A left-handed perspective projection matrix.
    ///
    inline static Matrix4F ProjectionPerspectiveLH(const float32 width,	const float32 height, const float32 zNear, const float32 zFar)
    {
      return Matrix4F(
        (2.0f * zNear) / width, 0.0f, 0.0f, 0.0f,
        0.0f, (2.0f * zNear) / height, 0.0f, 0.0f,
        0.0f, 0.0f, zFar / (zFar - zNear), 1.0f,
        0.0f, 0.0f, (zNear * zFar) / (zNear - zFar), 0.0f);
    }

     
    /// @brief Calculates a right-handed perspective projection matrix. 
    ///
    /// @param width The width of the viewport (screen).
    /// @param height The height of the viewport (screen).
    /// @param zNear The near plane.
    /// @param zFar The far plane.
    ///
    /// @returns A right-handed perspective projection matrix.
    ///
    inline static Matrix4F ProjectionPerspectiveRH(const float32 width,	const float32 height, const float32 zNear, const float32 zFar)
    {
      return Matrix4F(
        (2.0f * zNear) / width, 0.0f, 0.0f, 0.0f,
        0.0f, (2.0f * zNear) / height, 0.0f, 0.0f,
        0.0f, 0.0f, zFar / (zNear - zFar), -1.0f,
        0.0f, 0.0f, (zNear * zFar) / (zNear - zFar), 0.0f);
    }

     
    /// @brief Calculates a left-handed orthogonal projection matrix.
    ///
    /// @param width The width of the viewport (screen).
    /// @param height The height of the viewport (screen).
    /// @param zNear The near plane.
    /// @param zFar The far plane.
    ///
    /// @returns A left-handed perspective projection matrix.
    ///
    inline static Matrix4F ProjectionOrthogonalLH(float32 width, float32 height, float32 zNear, float32 zFar)
    {
      float32 farNear = zFar - zNear;      

      return Matrix4F(
        2.0f / width, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / height, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / farNear, 0.0f,
        0.0f, 0.0f, -zNear / farNear, 1.0f);
    }

     
    /// @brief Calculates a right-handed orthogonal projection matrix.
    ///
    /// @param width The width of the viewport (screen).
    /// @param height The height of the viewport (screen).
    /// @param zNear The near plane.
    /// @param zFar The far plane.
    ///
    /// @returns A right-handed perspective projection matrix.
    ///
    inline static Matrix4F ProjectionOrthogonalRH(float32 width, float32 height, float32 zNear, float32 zFar)
    {
      float32 nearFar = zNear - zFar;

      return Matrix4F(
        2.0f / width, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / height, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f / nearFar, 0.0f,
        0.0f, 0.0f, zNear / nearFar, 1.0f);
    }    
  };

}}