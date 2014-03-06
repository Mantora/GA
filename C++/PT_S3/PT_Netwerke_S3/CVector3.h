#pragma once

#include <iostream>
#include <math.h>
#include <cmath>        // std::abs
using namespace std;

#define PI 3.14159265F

#include <iomanip>// ::std::setw

class CVector3
{
	private:

	public:
		//Variablen
		float x,y,z;

		//construktors
		CVector3();
		CVector3(int iX, int iY, int iZ);
		CVector3(float fX, float fY, float fZ);
		CVector3(const CVector3& other);

		//print funktion für consolen debug
		void Print();
		friend ostream& operator<<(ostream& out, const CVector3& other) // output
		{
			out << right << "(" << setw(10) << fixed << other.x << "|" << setw(10) << fixed << other.y << "|" << setw(10) << fixed << other.z << ")";
			return out;
		}

		//operator overloading
		CVector3 operator +(const CVector3& other) const;
		CVector3 operator -(const CVector3& other) const;
		CVector3 operator *(const CVector3& other) const;
		CVector3 operator /(const CVector3& other) const;

		CVector3 operator +(const float fScaling);
		CVector3 operator -(const float fScaling);
		CVector3 operator *(const float fScaling);
		CVector3 operator /(const float fScaling);

		void operator -=(const CVector3& other);
		void operator +=(const CVector3& other);
		void operator *=(const float fScaling);

		static float Angle( const CVector3& a, const CVector3& b)
		{
			float tmp_o = CVector3::dot(a,b);
			float tmp_u = Length(a) * Length(b);

			float tmp_oDu = tmp_o/tmp_u;

			//float ungenauigkeiten ausgleichen
			if( tmp_oDu < -1.0f ) tmp_oDu = -1.0f;
			if( tmp_oDu > 1.0f ) tmp_oDu = 1.0f;

			return acos( tmp_oDu ) * 180/PI;
		};

		//dot
		static float dot( const CVector3& a, const CVector3& b)
		{
			//dot-product(V1, V2) = X1*X2 + Y1*Y2 + Z1*Z2
			//vector product(V1, V2) = 
			//CVector3(
			//			V1.y * V2.z - V1.z * V2.y
			//			V1.z * V2.x - V1.x * V2.z
			//			V1.x * V2.y - V1.y * V2.x 
			//		)

			float scalar = a.x * b.x + a.y * b.y + a.z * b.z;
			return scalar;
		}

		static float GetYAngle(const CVector3& v)
		{
			CVector3 tmp = v;
			tmp.Normalize();
			float f = acos(tmp.z) * 180 / PI;
			if(tmp.x < 0)
			{
				f = 360 - f;
			}
			return f;
		}

		CVector3 operator ^(const CVector3& other); //cross
		void operator ^=(const CVector3& other); //cross and assignment
		bool operator ==(const CVector3& other);
		bool operator !=(const CVector3& other);
		CVector3& operator -();

		void Normalize();
		static float Length( const CVector3& other )
		{ 
			return sqrt( other.x*other.x + other.y*other.y + other.z*other.z );
		};

		static float Distance( const CVector3& v1, const CVector3& v2 )
		{ 
			return sqrt( (v2.x-v1.x) * (v2.x-v1.x)  + (v2.y-v1.y) * (v2.y-v1.y) + (v2.z-v1.z) * (v2.z-v1.z) );
		};

		void RotateAroundY(float angle);
};

