#pragma once

#include <iostream>

#define MAX_CHARAKTERS 256

using namespace std;

class CString
{
	private:
		char data[MAX_CHARAKTERS];
		friend bool operator ==(const CString &left, const CString &right );

	public:
		CString();
		CString(const char* cstr);

		void operator =( const char* cstr);

		//ToDel 4 dev:
//		char* getArray();
		/////////////////

		CString operator +( const CString& anotherCString);

		char& operator []( const int index );

		bool IsEmpthy();
		int GetLength();

		operator char*();

		bool operator ==(const CString &other );
		bool operator <=(const CString &other );
		bool operator >=(const CString &other );

		bool operator !=(const CString &other );

		int operator <(const CString &other );
		int operator >(const CString &other );

		CString operator +=(const CString &other );
		CString operator +(const char* cstr );
		CString operator +=(const char* cstr );

		int Find(const char* cstr );

		bool Contains(const char* cstr );

		void Reverse();

		void Clear();

		////////////////custom <cstring> funktion//////////////////
		void CString_cpy( char* dest, const char* src );
		void CString_cat( char* dest, const char* src );
		int CString_len( const char* str );
		int CString_cmp( const char* dest, const char* src );
		bool CString_contain( const char* dest, const char* src );
		///////////////////////////////////////////////////////////

		void test();
};
