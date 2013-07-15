#pragma once

#include <iostream>
#include <math.h>
using namespace std;

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

		//operator overloading
		CVector3 operator +(const CVector3& other);
		CVector3 operator -(const CVector3& other);
		CVector3 operator *(const float fScaling);
		void operator -=(const CVector3& other);
		void operator +=(const CVector3& other);
		void operator *=(const float fScaling);
		float operator *(const CVector3& other); //dot
		CVector3 operator ^(const CVector3& other); //cross
		void operator ^=(const CVector3& other); //cross and assignment
		bool operator ==(const CVector3& other);
		bool operator !=(const CVector3& other);
		CVector3& operator -();

		void Normalize();
		float GetLength();
		float GetLengthSquared();
};

//dot-product(V1, V2) = X1*X2 + Y1*Y2 + Z1*Z2
//vector product(V1, V2) = 
//CVector3(
//			V1.y * V2.z - V1.z * V2.y
//			V1.z * V2.x - V1.x * V2.z
//			V1.x * V2.y - V1.y * V2.x 
//		)