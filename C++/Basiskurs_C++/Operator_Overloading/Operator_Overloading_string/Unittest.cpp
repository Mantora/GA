// StringClass.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <assert.h>
#include "CString.h"

using namespace std;

int main(int argc, char* argv[])
{
	CString TestString;
	
//ToDel 4 CJ:
/*	TestString = "Mama";
	cout << TestString.getArray() << endl;
	cout << TestString[0] << endl;
	TestString[0] = 'D';
*/
//	assert(strcmp(TestString.getArray(), "") == 0);
//	TestString.test();
///////////////////////////////////////////////////////////

	assert(strcmp(TestString, "") == 0);
	assert(TestString.GetLength()==0);
	assert(TestString.IsEmpthy());
	
	TestString = "Mama";

	cout << "Ich bin der \"TestString\" : " << TestString << endl;
	assert(TestString.GetLength() == 4);
	assert(TestString.IsEmpthy() == false);
	assert(TestString[0] == 'M');
	assert(TestString[1] == 'a');
	assert(TestString[2] == 'm');
	assert(TestString[3] == 'a');	
	assert(strcmp(TestString, "Mama") == 0);

	TestString[0] = 'B';
	TestString[1] = 'i';
	TestString[2] = 'e';
	TestString[3] = 'r';
	assert(strcmp(TestString, "Bier") == 0);
	CString TestString2 = "Bier";
	cout << "Ich bin der \"TestString2\" : " << TestString2 << endl;
	assert(strcmp(TestString,TestString2) == 0 && TestString == TestString2);
	assert(strcmp(TestString,TestString2) == 0 && TestString <= TestString2);
	assert(strcmp(TestString,TestString2) == 0 && TestString >= TestString2);
	assert((TestString != TestString2) == false);
	CString TestString3 = TestString2;
	cout << "Ich bin der \"TestString3\" : " << TestString3 << endl;
	TestString2 = "Bier2";
	assert(strcmp(TestString3, "Bier") == 0);
	assert(TestString3 == CString("Bier"));
	assert(strcmp(TestString, TestString2) == -1 && TestString < TestString2);
	assert(strcmp(TestString2, TestString) == 1 && TestString2 > TestString);
	assert(strcmp(TestString, TestString2) == -1 && TestString <= TestString2);
	assert(strcmp(TestString2, TestString) == 1 && TestString2 >= TestString);
	assert(TestString != TestString2);
	
	assert(strcmp(TestString+TestString, "BierBier") == 0);
	assert(strcmp(TestString+=TestString, "BierBier") == 0);
	assert(strcmp(TestString3+"Bier", "BierBier") == 0);
	assert(strcmp(TestString3+="Bier", "BierBier") == 0);

	TestString2 = "HalloTestIchSucheBiBiBier";
	assert(TestString2.Find("Bier") == 21);
	assert(TestString2.Find("BierBier") == -1);
	assert(TestString2.Find("Mama") == -1);
	assert(TestString2.Find("") == -1);
	
	assert(TestString2.Contains("BiBier"));
	assert(TestString2.Contains("BierBier") == false);
	assert(TestString2.Contains("Mama") == false);
		
	TestString2.Reverse();
	cout << "Ich bin der \"TestString2\" : " << TestString2 << endl;
	assert(strcmp(TestString2, "reiBiBiBehcuShcItseTollaH") == 0);
	
	assert(TestString.IsEmpthy() == false);
	TestString.Clear();
	assert(TestString.IsEmpthy());

	system("pause");

	return 0;
}

