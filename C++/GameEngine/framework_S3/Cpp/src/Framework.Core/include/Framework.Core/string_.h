#pragma once

// Disable deprecation warnings of function wcsncpy(...)
#pragma warning(disable : 4996)

// Platform specific includes
#include <iostream>

// Framework specific includes
#include "Datatypes.h"
#include "Macros.h"

namespace Framework { namespace Core {

  /*!
  * @brief A string class.
  */
  class string
  {
    // ------------------------------------------------------------------------
    // PUBLIC
    // ------------------------------------------------------------------------

  public:

    /*!
    * @brief Creates an instance of string.
    *
    * @remarks An empty string will be created ("") with a length of 1.
    */
    inline string()
    {
      this->pwChar = new wchar_t[1];
      this->pwChar[0] = 0;
      this->pChar = 0;
    }

    /*!
    * @brief Creates an instance of string.
    *
    * @param val A 32-bit integer.
    */
    inline string(uint32 val)
    { 
      this->pwChar = new wchar_t[3];

      this->pwChar[0] = (wchar_t)(val >> 16);
      this->pwChar[1] = (wchar_t)val;
      this->pwChar[2] = 0;
      this->pChar = 0;
    }

    /*!
    * @brief Creates an instance of string.
    *
    * @param val A 64-bit integer.
    */
    inline string(uint64 val)
    { 
      this->pwChar = new wchar_t[5];

      this->pwChar[0] = (wchar_t)(val >> 48);
      this->pwChar[1] = (wchar_t)(val >> 32);
      this->pwChar[2] = (wchar_t)(val >> 16);
      this->pwChar[3] = (wchar_t)val;
      this->pwChar[4] = 0;
      this->pChar = 0;
    }

    /*!
    * @brief Creates an instance of string and initializes
    * this instance with the given string.
    *
    * @param val A string with which to initialize this string.
    */
    inline string(const char* val)
    {
      uint32 len = (uint32)strlen(val);

      this->pwChar = new wchar_t[len+1];

      for(uint32 i=0; i<len; i++)
        this->pwChar[i] = val[i];

      this->pwChar[len] = 0;
      this->pChar = 0;
    }

    /*!
    * @brief Creates an instance of string and initializes
    * this instance with the given string.
    *
    * @param val A string with which to initialize this string.
    */
    inline string(const wchar_t* val)
    {
      uint32 len = (uint32)wcslen(val);

      this->pwChar = new wchar_t[len+1];

      wcsncpy(this->pwChar, val, len);

      this->pwChar[len] = 0;
      this->pChar = 0;
    }

    /*!
    * @brief Creates an instance of a string an copies the given
    * string to the new instance.
    *
    * @param val A string.
    */
    inline string(const string& val)
    {
      this->pwChar = new wchar_t[val.Length() + 1];

      wcsncpy(this->pwChar, val.pwChar, val.Length());

      this->pwChar[val.Length()] = 0;
      this->pChar = 0;
    }

    /*!
    * @brief Creates an instance of a string.
    *
    * @param val A pointer to a string.
    */
    inline string(const string* val)
    {
      this->pwChar = val->pwChar;
      this->pChar = val->pChar;
    }

    /*!
    * @brief Destructor.
    */
    ~string()
    {
      if(this->pwChar != 0)
        delete this->pwChar;

      if(this->pChar != 0)
        delete this->pChar;
    }

    /*!
    * @brief Returns a reference to this instance of string.
    *
    * @remarks The return value is not an independent copy of this instance; it
    * is simply another view of the same data. Use string::Copy() method to 
    * create a seperate string or use the '=' operator.
    *
    * @returns The instance of string.
    */
    inline string* Clone()
    {
      return this;
    }

    /*!
    * @brief Compares this string with a given string.
    *
    * @param val A string.
    *
    * @returns <0 if instance<val, >0 if instance>val, 0 if instance==val.
    */
    uint32 CompareTo(const string& val);

    /*!
    * @brief Copies a specified number of characters from a specified position in
    * this instance to a specified position in an array of characters.
    *
    * @param srcIdx A character position in this instance.
    * @param dst An array of characters.
    * @param dstIdx An array element in dst.
    * @param count The number of characters in this instance to copy to dst.
    */
    void CopyTo(uint32 srcIdx, wchar_t* dst, uint32 dstIdx, uint32 count);

    /*!
    * @brief Determines whether the specified string occurs within this string.
    *
    * @param val A string.
    *
    * @returns TRUE if val occurs within this string, else FALSE.
    */
    bool Contains(const string& val);

    /*!
    * @brief Concatenates a given string to this instance.
    *
    * @param a A string.
    */
    void Concat(const string& a);

    /*!
    * @brief Determines whether the end of this instance matches a specified string.
    *
    * @param val A string.
    *
    * @returns TRUE if match, else FALSE.
    */
    bool EndsWith(const string& val);

    /*!
    * @brief Determines whether this instance and another specified string object 
    * have the same value.
    *
    * @param val A string.
    *
    * @returns TRUE if equal, else FALSE.
    */
    inline bool Equals(const string& val) const
    {
      if(this->Length() != val.Length())
        return false;

      uint32 len = min(this->Length(), val.Length());

      for(uint32 i=0; i<len; i++)
      {
        if(this->pwChar[i] != val.pwChar[i])
          return false;
      }

      return true;
    }

    /*!
    * @brief Returns the hash code for this string.
    *
    * @returns A 32-bit signed integer hash code.
    */
    uint32 GetHashCode();

    /*!
    * @brief Reports the index of the first occurence of the specified string
    * in this instance.
    *
    * @param val The string to seek.
    *
    * @returns The index position of val if that string is found, or -1 if it is not.
    * If val is empty, the return value is 0.
    */
    uint32 IndexOf(const string& val);

    /*!
    * @brief Reports the index of the first occurence of the specified string
    * in this instance. The search starts at the specified character position.
    *
    * @param val The string to seek.
    * @param startIdx The search starting position.
    *
    * @returns The index position of val if that string is found, or -1 if it is not.
    * If val is empty, the return value is 0.
    */
    uint32 IndexOf(const string& val, uint32 startIdx);

    /*!
    * @brief Reports the index of the first occurence in this instance of any
    * character in a specified string.
    *
    * @param anyOf A string containing one or more characters to seek.
    *
    * @returns The index position of the first occurence in this instance where any
    * character in anyOf was found; otherwise, -1 if no character in anyOf was found.
    */
    uint32 IndexOfAny(const string& anyOf);

    /*!
    * @brief Reports the index of the first occurence in this instance of any
    * character in a specified string. 
    * The search starts at a specified character position.
    *
    * @param anyOf A string containing one or more characters to seek.
    * @param startIdx The search starting position.
    *
    * @returns The index position of the first occurence in this instance where any
    * character in anyOf was found; otherwise, -1 if no character in anyOf was found.
    */
    uint32 IndexOfAny(const string& anyOf, uint32 startIdx);

    /*!
    * @brief Inserts a specified instance of string at a specified index position
    * in this instance.
    *
    * @param startIdx The index position of the insertion.
    * @param val The string to insert.
    *
    * @returns A new string equivalent to this instance but with val inserted
    * at position startIdx.
    */
    string Insert(uint32 startIdx, const string& val);

    /*!
    * @brief Gets the length of this string.
    *
    * @returns The length of this string.
    */
    inline uint32 Length() const
    {
      if(this->pwChar != 0)
        return (uint32)wcslen(this->pwChar);

      return 0;
    }

    /*!
    * @brief Reports the index of the last occurence of the specified string
    * in this instance.
    *
    * @param val The string to seek.
    *
    * @returns The index position of val if that string is found, or -1 if it is not.
    * If val is empty, the return value is 0.
    */
    uint32 LastIndexOf(const string& val);

    /*!
    * @brief Reports the index of the last occurence of the specified string
    * in this instance. The search starts at the specified character position.
    *
    * @param val The string to seek.
    * @param startIdx The search starting position.
    *
    * @returns The index position of val if that string is found, or -1 if it is not.
    * If val is empty, the return value is 0.
    */
    uint32 LastIndexOf(const string& val, uint32 startIdx);

    /*!
    * @brief Reports the index of the last occurence in this instance of any
    * character in a specified string.
    *
    * @param anyOf A string containing one or more characters to seek.
    *
    * @returns The index position of the last occurence in this instance where any
    * character in anyOf was found; otherwise, -1 if no character in anyOf was found.
    */
    uint32 LastIndexOfAny(const string& anyOf);

    /*!
    * @brief Reports the index of the last occurence in this instance of any
    * character in a specified string. 
    * The search starts at a specified character position.
    *
    * @param anyOf A string containing one or more characters to seek.
    * @param startIdx The search starting position.
    *
    * @returns The index position of the last occurence in this instance where any
    * character in anyOf was found; otherwise, -1 if no character in anyOf was found.
    */
    uint32 LastIndexOfAny(const string& anyOf, uint32 startIdx);

    /*!
    * @brief Right-aligns the characters in this instance, padding with spaces
    * on the left for a specific length.
    *
    * @param length The number of spaces to pad this instance to the right.
    *
    * @returns A new string that is equivalent to this instance, but right-aligned
    * and padded on the left with as many spaces as needed to create a total length of
    * length.
    */
    string PadLeft(uint32 length);

    /*!
    * @brief Left-aligns the characters in this instance, padding with spaces
    * on the right for a specific length.
    *
    * @param length The number of spaces to pad this instance to the left.
    *
    * @returns A new string that is equivalent to this instance, but left-aligned
    * and padded on the right with as many spaces as needed to create a total length of
    * length.
    */
    string PadRight(uint32 length);

    /*!
    * @brief Deletes all the characters from this instance beginning at a specified
    * position continuing through the last position.
    *
    * @param startIdx The position to begin deleting characters.
    *
    * @returns A new string object that is equivalent to this string less the
    * removed characters.
    */
    string Remove(uint32 startIdx);

    /*!
    * @brief Deletes a specified number of characters from this instance beginning 
    * at a specified position.
    *
    * @param startIdx The position to begin deleting characters.
    * @param count The number of characters to delete.
    *
    * @returns A new string object that is equivalent to this string less count
    * number of characters.
    */
    string Remove(uint32 startIdx, uint32 count);

    /*!
    * @brief Replaces all occurances of a specified character or string in
    * this instance, with another specified character or string.
    *
    * @parame oldVal A string to be replaced.
    * @parame newVal A string to replace all occurendes of oldVal.
    *
    * @returns A string equivalent to this instance but with all instances of
    * oldVal replaced with newVal.
    */
    string Replace(const string& oldVal, const string& newVal);

    /*!
    * @brief Determines whether the beginning of this instance matches a 
    * specified string.
    *
    * @param val A string.
    *
    * @returns TRUE if match, else FALSE.
    */
    bool StartsWith(const string& val);

    /*!
    * @brief Retrieves a substring from this instance. The substring starts at a
    * specified character position.
    *
    * @param startIdx The start index.
    *
    * @returns A substring from this instance.
    */
    string Substring(uint32 startIdx);

    /*!
    * @brief Retrieves a substring from this instance. The substring starts at a
    * specified character position and has a specified lenght.
    *
    * @param startIdx The start index.
    * @param length The length of the substring to retrieve.
    *
    * @returns A substring from this instance.
    */
    string Substring(uint32 startIdx, uint32 length);

    string* Split(const char& separator, uint32* numElements);

    /*!
    * @brief Gets the number of how many times the specified character exists
    * in this instance of string.
    *
    * @param value A single character.
    *
    * @returns The number of how many times the specified character exists
    * in this instance of string.
    */
    uint32 NumberOf(const char& value);

    /*!
    * @brief Creates a new character array and copies the characters in this instance 
    * to the new character array.
    *
    * @returns A character array whose elements are the individual characters of this
    * instance. If this instance is an empty string, the returned character array is empty.
    */
    const char* ToChar();

    /*!
    * @brief Creates a new character array and copies the characters in a specified
    * supstring in this instance to the new character array.
    *
    * @param startIdx The starting position of a substring in this instance.
    * @param length The length of the substring in this instance.
    *
    * @returns A character array whose elements are the length number of characters in this
    * instance starting from character position startIdx.
    */
    const char* ToChar(uint32 startIdx, uint32 length);

    /*!
    * @brief Creates an upper-case copy of this instance.
    *
    * @returns An upper-case copy of this instance.
    */
    string ToUpper();

    /*!
    * @brief Creates a lower-case copy of this instance.
    *
    * @returns A lower-case copy of this instance.
    */
    string ToLower();

    /*!
    * @brief Removes all occurences of white space characters at the beginning
    * of this instance.
    *
    * @returns The string that remains after all occurences of white space
    * characters are removed from the beginning.
    */
    string TrimStart();

    /*!
    * @brief Removes all occurences of white space characters at the end
    * of this instance.
    *
    * @returns The string that remains after all occurences of white space
    * characters are removed from the end.
    */
    string TrimEnd();

    /*!
    * @brief Removes all occurendes of a space character at the beginning and 
    * at the end of this instance.
    *
    * @returns The string that remains after all occurences of white space
    * characters are removed from the beginning and from the end of this instance.
    */
    string Trim();

    // ------------------------------------------------------------------------
    // STATIC MEMBERS
    // ------------------------------------------------------------------------

    static string Create(uint32 length)
    {
      string result;

      delete result.pwChar;

      result.pwChar = new wchar_t[length + 1];
      result.pwChar[length] = 0;

      for(uint32 i=0; i<length;i++)
        result.pwChar[i] = 32;

      return result;
    }

    /*!
    * @brief Concatenates two specified instances of string.
    *
    * @param val1 The first string.
    * @param val2 The second string.
    *
    * @returns The concatenation of val1 and val2.
    */
    static string Concat(const string& val1, const string& val2)
    {
      uint32 lenA = val1.Length();
      uint32 lenB = val2.Length();

      uint32 totalLen = lenA + lenB + 1;

      wchar_t* tmp = new wchar_t[totalLen];

      wcsncpy(tmp, val1.pwChar, lenA);

      wcsncpy(&tmp[lenA], val2.pwChar, lenB + 1);

      string result = tmp;

      delete tmp;

      return result;
    }

    /*!
    * @brief Compares two specified string objects.
    *
    * @param val1 First string.
    * @param val2 Second string.
    *
    * @returns <0 if val1 < val2, >0 if val1 > val2, 0 if val1 == val2.
    */
    static uint32 Compare(const string& val1, const string& val2)
    {
      return wcscmp(val1.pwChar, val2.pwChar);
    }

    /*!
    * @brief Creates a new instance of string with the same value 
    * as a specified string.
    *
    * @param val The string to copy.
    *
    * @returns A new string with the same value as val.
    */
    static string Copy(const string& val)
    {
      string result = val;

      return result;
    }

    /*!
    * @brief Converts a specified string to a float value.
    *
    * @param val A string.
    *
    * @returns A float.
    */
    static float ConvertToFloat(string& val)
    {
      return (float)atof(val);
    }

    /*!
    * @brief Converts a specified string to a double value.
    *
    * @param val A string.
    *
    * @returns A double.
    */
    static double ConvertToDouble(string& val)
    {
      return strtod(val, 0);
    }

    /*!
    * @brief Converts a specified string to a 32-bit integer value.
    *
    * @param val A string.
    *
    * @returns A 32-bit integer.
    */
    static uint32 ConvertToInt32(string& val)
    {
      return atoi(val);
    }

    /*!
    * @brief Indicates whether the specified string object is null
    * reference or an empty string.
    *
    * @param A string reference.
    *
    * @returns TRUE if the val parameter is a null reference or an 
    * empty string (""); otherwise, FALSE.
    */
    static bool IsNullOrEmpty(const string& val)
    {
      if(val.pwChar == 0)
        return true;

      if(val.Length() == 0)
        return true;

      return false;
    }

    // ------------------------------------------------------------------------
    // OPERATORS
    // ------------------------------------------------------------------------

    /*!
    * @brief Returns the internal character pointer.
    */
    inline operator const wchar_t*(void)
    { 
      return this->pwChar;
    }

    /*!
    * @brief Creates a new character array and returns the character 
    * array pointer.
    */
    inline operator const char*(void)
    { 
      return this->ToChar();
    }

    /*!
    * @brief Assigns a given string to this instance.
    *
    * @param val A string.
    *
    * @returns This instance with the new string value.
    */
    inline string operator=(const string& val)
    {
      if(this != &val)
      {
        if(this->pwChar != 0)
          delete this->pwChar;

        uint32 len = (uint32)wcslen(val.pwChar);

        this->pwChar = new wchar_t[len+1];
        wcsncpy(this->pwChar, val.pwChar, len+1);
      }

      return *this;
    }

    /*!
    * @brief Concatenates the specified string to the current instance.
    *
    * @param val A string.
    *
    * @returns The concatenation of the current instance and val.
    */
    inline string& operator+=(const string& val)
    {
      this->Concat(val);

      return *this;
    }

    /*!
    * @brief Concatenates two specified instances of string.
    *
    * @param val1 The first string.
    * @param val2 The second string.
    *
    * @returns The concatenation of val1 and val2.
    */
    inline friend string operator+(string& val1, const string& val2)
    {
      val1 += val2;

      return val1;
    }

    /*!
    * @brief Concatenates a char string with a string.
    *
    * @param val1 A char string.
    * @param val2 A string.
    *
    * @returns The concatenation of val1 and val2.
    */
    inline friend string operator+(const char* val1, const string& val2)
    {
      string tmp = val1;

      return tmp += val2;
    }

    /*!
    * @brief Determines if two specified string objects are equal.
    *
    * @param val1 The first string.
    * @param val2 The second string.
    *
    * @returns TRUE if val1 equals val2, else FALSE.
    */
    inline friend bool operator==(const string& val1, const string& val2)
    {
      return val1.Equals(val2);
    }

    /*!
    * @brief Determines if two specified string objects are not equal.
    *
    * @param val1 The first string.
    * @param val2 The second string.
    *
    * @returns TRUE if val1 is not equal val2, else FALSE.
    */
    inline friend bool operator!=(const string& val1, const string& val2)
    {
      return !val1.Equals(val2);
    }

    /*!
    * @brief Compares two specified string objects.
    *
    * @param val1 First string.
    * @param val2 Second string.
    *
    * @returns TRUE if val1 < val2, FALSE if val1 > val2 or if val1 == val2.
    */
    inline friend bool operator<(string& val1, string& val2)
    {
      uint32 result = val1.CompareTo(val2);

      if(result < 0)
        return true;

      return false;
    }

    /*!
    * @brief Compares two specified string objects.
    *
    * @param val1 First string.
    * @param val2 Second string.
    *
    * @returns TRUE if val1 > val2, FALSE if val1 < val2 or if val1 == val2.
    */
    inline friend bool operator>(string& val1, string& val2)
    {
      return !(val1<val2);
    }

    /*!
    * @brief Writes a specified string into the specified stream.
    *
    * @param outStream The output stream.
    * @param string The string to write to outStream.
    */
    inline friend std::ostream& operator<<(std::ostream& outStream, string& val)
    {
      outStream << (const char*) val;

      return outStream;
    }

    /*!
    * @brief Reads a specified string into the specified stream.
    *
    * @remarks A memory amount of 128 bytes may be used for input!
    *
    * @param inStream The input stream.
    * @param string The string to read to outStream.
    */
    inline friend std::istream& operator>>(std::istream& inStream, string& val)
    {
      if(val.pChar != 0)
        delete val.pChar;

      // Create a large memory amount for reading strings
      val.pChar = new char[128];      

      // Write stream to string
      inStream >> val.pChar;

      // Update pwChar
      uint32 len = (uint32)strlen(val.pChar);

      if(val.pwChar != 0)
        delete val.pwChar;

      val.pwChar = new wchar_t[len + 1];

      for(uint32 i=0;i<len;i++)
        val.pwChar[i] = val.pChar[i];

      val.pwChar[len] = 0;

      return inStream;
    }


    // ------------------------------------------------------------------------
    // PRIVATE
    // ------------------------------------------------------------------------

  private:

    /*!
    * @brief A temporary pointer to a character array which is used to convert
    * a wchar_t string to a char string.
    *
    * @remarks The following methods are using this pointer:
    * - ToChar
    * - operator>>
    * - operator<<
    */
    char* pChar;

    /*!
    * @brief A pointer to a wchar_t string representing the contents of this
    * instance.
    */
    wchar_t* pwChar;
  };
}}