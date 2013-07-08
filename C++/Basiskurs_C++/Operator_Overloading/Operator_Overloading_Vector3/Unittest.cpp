// Vectorclass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vectorclass.h"
#include <iostream>
#include <assert.h>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Test CVector3" << endl;
	
	CVector3 X(-1,0,0);
	CVector3 Y(0,-2,0);

	CVector3 A(1,0,0);
	CVector3 B(0,2,0);
	
	assert(X.x == -1 && X.y == 0 && X.z == 0);
	assert(Y.x == 0 && Y.y == -2 && Y.z == 0);
	assert(A.x == 1 && A.y == 0 && A.z == 0);
	assert(B.x == 0 && B.y == 2 && B.z == 0);

	CVector3 C(X);
	assert(C.x == -1 && C.y == 0 && C.z == 0);
	
	X = CVector3(1,0,0);
	Y = CVector3(0,2,0);

	A = CVector3(-1,0,0);
	B = CVector3(0,-2,0);

#ifdef WITHPRINT	
	cout << endl << "X-Vector"; 
	X.Print();

	cout << endl << "Y-Vector";
	Y.Print();

	cout << endl << "A-Vector"; 
	A.Print();

	cout << endl << "B-Vector";
	B.Print();
#endif

	assert(X.x == 1 && X.y == 0 && X.z == 0);
	assert(Y.x == 0 && Y.y == 2 && Y.z == 0);
	assert(A.x == -1 && A.y == 0 && A.z == 0);
	assert(B.x == 0 && B.y == -2 && B.z == 0);

	CVector3 result;

//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "Addition" << endl;
	
	result = X + Y;
#ifdef WITHPRINT	
	cout << endl << "Result X+Y = "; 
	result.Print();
#endif
	assert(result.x == 1 && result.y == 2 && result.z == 0);

	result = A + B;
#ifdef WITHPRINT	
	cout << endl << "Result A+B = "; 
	result.Print();
#endif
	assert(result.x == -1 && result.y == -2 && result.z == 0);

	result = X + A;
#ifdef WITHPRINT	
	cout << endl << "Result X+A = "; 
	result.Print();
#endif
	assert(result.x == 0 && result.y == 0 && result.z == 0);
	
//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "substration" << endl;

	result = X - Y;
#ifdef WITHPRINT	
	cout << endl << "Result X-Y = "; 
	result.Print();
#endif
	assert(result.x == 1 && result.y == -2 && result.z == 0);

	result = A - B;
#ifdef WITHPRINT	
	cout << endl << "Result A-B = "; 
	result.Print();
#endif
	assert(result.x == -1 && result.y == 2 && result.z == 0);

	result = X - A;
#ifdef WITHPRINT	
	cout << endl << "Result X-A = "; 
	result.Print();
#endif
	assert(result.x == 2 && result.y == 0 && result.z == 0);

//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "Skalierung" << endl;

	result = X * 2.5f;
#ifdef WITHPRINT	
	cout << endl << "Result * 2,5 = "; 
	result.Print();
#endif
	assert(result.x == 2.5&& result.y == 0 && result.z == 0);

	result = Y * 1.5f;
#ifdef WITHPRINT	
	cout << endl << "Result Y * 1,5 = "; 
	result.Print();
#endif	
	assert(result.x == 0 && result.y == 3 && result.z == 0);

//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "assignment" << endl;

	result = A;
#ifdef WITHPRINT	
	cout << endl << "Result = A = "; 
	result.Print();
#endif
	assert(result.x == -1 && result.y == 0 && result.z == 0);

	result = X;
#ifdef WITHPRINT	
	cout << endl << "Result = X = "; 
	result.Print();
#endif
	assert(result.x == 1 && result.y == 0 && result.z == 0);


//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "substration and assignment" << endl;

	X -= Y;
#ifdef WITHPRINT	
	cout << endl << "X-=Y = "; 
	X.Print();
#endif
	assert(X.x == 1 && X.y == -2 && X.z == 0);

	A -= B;
#ifdef WITHPRINT	
	cout << endl << "A-=B = "; 
	A.Print();
#endif
	assert(A.x == -1 && A.y == 2 && A.z == 0);

	X -=B;
#ifdef WITHPRINT	
	cout << endl << "X-=B = "; 
	X.Print();
#endif
	assert(X.x == 1 && X.y == 0 && X.z == 0);

	
//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "Addition and assignment" << endl;

	X += Y;
#ifdef WITHPRINT	
	cout << endl << "X+=Y = "; 
	X.Print();
#endif
	assert(X.x == 1 && X.y == 2 && X.z == 0);

	A += B;
#ifdef WITHPRINT	
	cout << endl << "A+=B = "; 
	A.Print();
#endif
	assert(A.x == -1 && A.y == 0 && A.z == 0);

	X +=B;
#ifdef WITHPRINT	
	cout << endl << "X+=B = "; 
	X.Print();	
#endif
	assert(X.x == 1 && X.y == 0 && X.z == 0);

//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "Skalierung and assignment" << endl;

	X *= 2.5f;
#ifdef WITHPRINT	
	cout << endl << "X*=2.5f = "; 
	X.Print();
#endif
	assert(X.x == 2.5 && X.y == 0 && X.z == 0);

	Y *= 1.5f;
#ifdef WITHPRINT	
	cout << endl << "Y*=1.5f = "; 
	Y.Print();
#endif
	assert(Y.x == 0 && Y.y == 3 && Y.z == 0);
	
	float scalar = 0.f;
//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "dot product" << endl;
	
	scalar = X * Y;
#ifdef WITHPRINT	
	cout << endl << "Result X*Y = " << scalar; 
#endif
	assert(scalar == 0);

	scalar = A * B;
#ifdef WITHPRINT	
	cout << endl << "Result A*B = " << scalar; 
#endif
	assert(scalar == 0);

	scalar = X * A;
#ifdef WITHPRINT	
	cout << endl << "Result X*A = " << scalar; 
#endif
	assert(scalar == -2.5f);

	
//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "cross product" << endl;

	result = X ^ Y;
#ifdef WITHPRINT	
	cout << endl << "Result X^Y = "; 
	result.Print();
#endif
	assert(result.x == 0 && result.y == 0 && result.z == 7.5f);

	result = A ^ B;
#ifdef WITHPRINT	
	cout << endl << "Result A^B = "; 
	result.Print();
#endif
	assert(result.x == 0 && result.y == 0 && result.z == 2);

	result = X ^ A;
#ifdef WITHPRINT	
	cout << endl << "Result X^A = "; 
	result.Print();
#endif
	assert(result.x == 0 && result.y == 0 && result.z == 0);


//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "cross product and assignment" << endl;

	X ^= Y;
#ifdef WITHPRINT	
	cout << endl << "X^=Y = "; 
	result.Print();
#endif
	assert(X.x == 0 && X.y == 0 && X.z == 7.5f);

	A ^= B;
#ifdef WITHPRINT	
	cout << endl << "Result A^=B = "; 
	result.Print();
#endif
	assert(A.x == 0 && A.y == 0 && A.z == 2);

	X ^= A;
#ifdef WITHPRINT	
	cout << endl << "X^=A = "; 
	result.Print();
#endif
	assert(X.x == 0 && X.y == 0 && X.z == 0);


	bool bResult = false;
//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "Vector compare" << endl;

	bResult = (X == Y);
#ifdef WITHPRINT	
	cout << endl << "Result X==Y = " << bResult; 
#endif
	assert(bResult == false);

	bResult = (A == B);
#ifdef WITHPRINT	
	cout << endl << "Result A==B = " << bResult; 
#endif
	assert(bResult == false);

	bResult = (A == A);
#ifdef WITHPRINT	
	cout << endl << "Result A==A = " << bResult; 
#endif
	assert(bResult == true);


//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "Vector compare not equal" << endl;

	bResult = (X != Y);
#ifdef WITHPRINT	
	cout << endl << "Result X!=Y = " << bResult; 
#endif
	assert(bResult == true);

	bResult = (A != B);
#ifdef WITHPRINT	
	cout << endl << "Result A!=B = " << bResult; 
#endif
	assert(bResult == true);

	bResult = (A != A);
#ifdef WITHPRINT	
	cout << endl << "Result A!=A = " << bResult; 
#endif
	assert(bResult == false);


//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "negate" << endl;

	-X;
#ifdef WITHPRINT	
	cout << endl << "negate X = "; 
	X.Print();
#endif
	assert(X.x == 0 && X.y == 0 && X.z == 0);

	-A;
#ifdef WITHPRINT	
	cout << endl << "negate A = "; 
	A.Print();
#endif
	assert(A.x == 0 && A.y == 0 && A.z == -2);

	-B;
#ifdef WITHPRINT	
	cout << endl << "negate B = "; 
	B.Print();
#endif
	assert(B.x == 0 && B.y == 2 && B.z == 0);

//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "normalize" << endl;

	Y.Normalize();
#ifdef WITHPRINT	
	cout << endl << "normalize Y = "; 
	Y.Print();
#endif
	assert(Y.x == 0 && Y.y == 1 && Y.z == 0);

	A.Normalize();
#ifdef WITHPRINT	
	cout << endl << "normalize A = "; 
	A.Print();
#endif
	assert(A.x == 0 && A.y == 0 && A.z == -1);

	B.Normalize();
#ifdef WITHPRINT	
	cout << endl << "normalize B = "; 
	B.Print();
#endif
	assert(B.x == 0 && B.y == 1 && B.z == 0);


	float länge = 0.f;
//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "get length" << endl;

	länge  = X.GetLength();
#ifdef WITHPRINT	
	cout << endl << "laenge X = " << länge;
#endif
	assert(länge == 0);

	länge = A.GetLength();
#ifdef WITHPRINT	
	cout << endl << "laenge A = " << länge; 
#endif
	assert(länge == 1);

	länge = Y.GetLength();
#ifdef WITHPRINT	
	cout << endl << "laenge Y = " << länge; 
#endif
	assert(länge == 1);

//--------------------------------------------------------------------------------
	cout << endl << "//------------------------------------------------------------------------------";
	cout << "get length quadrat" << endl;

	länge  = X.GetLengthSquared();
#ifdef WITHPRINT	
	cout << endl << "laenge X = " << länge; 
#endif
	assert(länge == 0);

	länge = A.GetLengthSquared();
#ifdef WITHPRINT	
	cout << endl << "laenge A = " << länge; 
#endif
	assert(länge == 1);

	länge = Y.GetLengthSquared();
#ifdef WITHPRINT	
	cout << endl << "laenge Y = " << länge; 
#endif
	assert(länge == 1);

	return 0;
};



