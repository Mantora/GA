#include "CVector3.h"

CVector3::CVector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

CVector3::CVector3(int iX, int iY, int iZ)
{
	this->x = (float)iX;
	this->y = (float)iY;
	this->z = (float)iZ;
}

CVector3::CVector3(float fX, float fY, float fZ)
{
	this->x = fX;
	this->y = fY;
	this->z = fZ;
}

CVector3::CVector3(const CVector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

//print funktion f�r consolen debug
void CVector3::Print()
{
	cout << "(" << this->x << "|" << this->y << "|" << this->z << ")" << endl;
}

//operator overloading
CVector3 CVector3::operator +(const CVector3& other) const
{
	CVector3 tmp;

	tmp.x = this->x + other.x;
	tmp.y = this->y + other.y;
	tmp.z = this->z + other.z;

	return tmp;
}

CVector3 CVector3::operator -(const CVector3& other) const
{
	CVector3 tmp;

	tmp.x = this->x - other.x;
	tmp.y = this->y - other.y;
	tmp.z = this->z - other.z;

	return tmp;
}

CVector3 CVector3::operator *(const CVector3& other) const
{
	CVector3 tmp;

	tmp.x = this->x * other.x;
	tmp.y = this->y * other.y;
	tmp.z = this->z * other.z;

	return tmp;
}

CVector3 CVector3::operator /(const CVector3& other) const
{
	CVector3 tmp;

	tmp.x = this->x / other.x;
	tmp.y = this->y / other.y;
	tmp.z = this->z / other.z;

	return tmp;
}

CVector3 CVector3::operator +(const float fScaling)
{
	CVector3 tmp;

	tmp.x = this->x + fScaling;
	tmp.y = this->y + fScaling;
	tmp.z = this->z + fScaling;

	return tmp;
}

CVector3 CVector3::operator -(const float fScaling)
{
	CVector3 tmp;

	tmp.x = this->x - fScaling;
	tmp.y = this->y - fScaling;
	tmp.z = this->z - fScaling;

	return tmp;
}

CVector3 CVector3::operator *(const float fScaling)
{
	CVector3 tmp;

	tmp.x = this->x * fScaling;
	tmp.y = this->y * fScaling;
	tmp.z = this->z * fScaling;

	return tmp;
}

CVector3 CVector3::operator /(const float fScaling)
{
	CVector3 tmp;

	tmp.x = this->x / fScaling;
	tmp.y = this->y / fScaling;
	tmp.z = this->z / fScaling;

	return tmp;
}

void CVector3::operator -=(const CVector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
}

void CVector3::operator +=(const CVector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void CVector3::operator *=(const float fScaling)
{
	this->x *= fScaling;
	this->y *= fScaling;
	this->z *= fScaling;
}

//cross
CVector3 CVector3::operator ^(const CVector3& other)
{
	CVector3 tmp;

	tmp.x = this->y*other.z - this->z*other.y;
	tmp.y = this->z*other.x - this->x*other.z;
	tmp.z = this->x*other.y - this->y*other.x;

	return tmp;
}

//cross and assignment
void CVector3::operator ^=(const CVector3& other)
{
	float f_tmpX = this->y*other.z - this->z*other.y;
	float f_tmpY = this->z*other.x - this->x*other.z;
	float f_tmpZ = this->x*other.y - this->y*other.x;

	this->x = f_tmpX;
	this->y = f_tmpY;
	this->z = f_tmpZ;
}

bool CVector3::operator ==(const CVector3& other)
{
	bool result;

	if( this->x == other.x &&
		this->y == other.y &&
		this->z == other.z )
		result = true;
	else
		result = false;

	return result;
}

bool CVector3::operator !=(const CVector3& other)
{
	bool result;

	if( this->x != other.x ||
		this->y != other.y ||
		this->z != other.z )
		result = true;
	else
		result = false;

	return result;
}

CVector3& CVector3::operator -()
{
	this->x *= (-1);
	this->y *= (-1);
	this->z *= (-1);

	return *this;
}

void CVector3::Normalize()
{
	CVector3 tmp = CVector3( this->x, this->y, this->z );

	if( tmp.x < 0 ) tmp.x *= (-1);
	if( tmp.y < 0 ) tmp.y *= (-1);
	if( tmp.z < 0 ) tmp.z *= (-1);

	float l = Length( tmp );

	this->x /= l;
	this->y /= l;
	this->z /= l;
}

void CVector3::RotateAroundY(float angle)
{
	CVector3 tmp = CVector3(this->x,this->y,this->z );

	this->x = tmp.x * cos( angle * PI/180.0f ) + tmp.z * sin( angle * PI/180.0f );
	this->z = tmp.x * -sin( angle * PI/180.0f ) + tmp.z * cos( angle * PI/180.0f );
}