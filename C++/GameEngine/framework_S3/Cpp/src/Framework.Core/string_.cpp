#include "include\Framework.Core\string_.h"

namespace Framework { namespace Core {

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::CompareTo(const string& val)
  {
    return wcscmp(this->pwChar, val.pwChar);
  }

  // ***************************************************************************
  // ***************************************************************************
  void string::CopyTo(uint32 srcIdx, wchar_t* dst, uint32 dstIdx, uint32 count)
  {
    wcsncpy(&dst[dstIdx], &this->pwChar[srcIdx], count);
  }

  // ***************************************************************************
  // ***************************************************************************
  bool string::Contains(const string& val)
  {
    uint32 len = min(this->Length(), val.Length());

    for(uint32 x=0; x<len; x++)
    {
      string tmp = this->Substring(x);

      if(tmp.StartsWith(val))
        return true;
    }

    return false;
  }

  // ***************************************************************************
  // ***************************************************************************
  void string::Concat(const string& val)
  {
    uint32 lenA = val.Length();
    uint32 lenB = this->Length();

    uint32 totalLen = lenA+lenB+1;

    wchar_t* tmp = new wchar_t[totalLen];

    wcsncpy(tmp, this->pwChar, lenB);

    wcsncpy(&tmp[lenB], val.pwChar, lenA + 1);

    delete this->pwChar;

    this->pwChar = tmp;
  }

  // ***************************************************************************
  // ***************************************************************************
  bool string::EndsWith(const string& val)
  {
    string tmp = this->Substring(this->Length() - val.Length());

    return tmp.Equals(val);
  }


  // ***************************************************************************
  // ***************************************************************************
  uint32 string::GetHashCode()
  {
    uint32 hashCode = 0;
    uint32 mod = 10102;
    uint32 shift = 29;

    for(uint32 i = 0; i < this->Length(); i++)
      hashCode = ((shift*hashCode)%mod+this->pwChar[i])%mod;

    return hashCode;
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::IndexOf(const string& val)
  {
    return this->IndexOf(val, 0);
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::IndexOf(const string& val, uint32 startIdx)
  {
    uint32 len = this->Length();
    uint32 lenVal = val.Length();

    if(lenVal == 0 || lenVal > len || startIdx >= len)
      return -1;

    for(uint32 x = startIdx; x < len; x++)
    {
      if((uint32)this->pwChar[x] == (uint32)val.pwChar[0])
      {
        string substring = this->Substring(x, lenVal);

        if(substring.Equals(val))
          return x;
      }
    }

    return -1;
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::IndexOfAny(const string& anyOf)
  {
    return this->IndexOfAny(anyOf, 0);
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::IndexOfAny(const string& anyOf, uint32 startIdx)
  {
    uint32 len = this->Length();
    uint32 lenAnyOf = anyOf.Length();

    if(lenAnyOf == 0 || startIdx >= len)
      return -1;

    for(uint32 x = startIdx; x < len; x++)
    {
      for(uint32 i = 0; i < lenAnyOf; i++)
      {
        if((uint32)this->pwChar[x] == (uint32)anyOf.pwChar[i])
        {        
          return x;
        }
      }
    }

    return -1;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::Insert(uint32 startIdx, const string& val)
  {
    // Calculate total length of resulting string
    uint32 lenTotal = this->Length() + val.Length();

    // Create a temporary buffer that contains the resulting string
    wchar_t* tmp = new wchar_t[lenTotal + 1];

    // Copy current string into temprary buffer
    wcsncpy(tmp, this->pwChar, this->Length());

    // Copy val into buffer at specified position
    wcsncpy(&tmp[startIdx], val.pwChar, val.Length());

    // Copy the rest of the current string into temporary buffer
    wcsncpy(&tmp[startIdx + val.Length()], &this->pwChar[startIdx], this->Length() - startIdx);

    // Add terminating zero
    tmp[lenTotal] = 0;

    // Create new string from temporary buffer
    string result = tmp;

    delete tmp;

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::LastIndexOf(const string& val)
  {
    return this->LastIndexOf(val, 0);
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::LastIndexOf(const string& val, uint32 startIdx)
  {
    uint32 len = this->Length();
    uint32 lenVal = val.Length();

    if(lenVal == 0 || lenVal > len || startIdx >= len)
      return -1;

    for(uint32 x = len; x > 0; x--)
    {
      if((uint32)this->pwChar[x] == (uint32)val.pwChar[0])
      {
        string substring = this->Substring(x, lenVal);

        if(substring.Equals(val))
          return x;
      }
    }

    return -1;
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::LastIndexOfAny(const string& anyOf)
  {
    return this->LastIndexOfAny(anyOf, 0);
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::LastIndexOfAny(const string& anyOf, uint32 startIdx)
  {
    uint32 len = this->Length();
    uint32 lenAnyOf = anyOf.Length();

    if(lenAnyOf == 0 || startIdx >= len)
      return -1;

    for(uint32 x = len; x > 0; x--)
    {
      for(uint32 i = 0; i < lenAnyOf; i++)
      {
        if((uint32)this->pwChar[x] == (uint32)anyOf.pwChar[i])
        {        
          return x;
        }
      }
    }

    return -1;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::PadLeft(uint32 length)
  {
    string result = string::Create(length);

    return result.Insert(length, *this);
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::PadRight(uint32 length)
  {
    string result = this->Insert(this->Length() - 1, string::Create(length));

    return result; 
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::Remove(uint32 startIdx)
  {
    return this->Remove(startIdx, this->Length() - startIdx);
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::Remove(uint32 startIdx, uint32 count)
  {
    wchar_t* tmp = new wchar_t[(this->Length() - count) + 1];

    if(startIdx + count < this->Length())
    {
      uint32 lenCpy = this->Length() - (startIdx + count);

      wcsncpy(tmp, this->pwChar, startIdx);
      wcsncpy(&tmp[startIdx], &this->pwChar[startIdx + count], lenCpy);

      tmp[startIdx + lenCpy] = 0;
    }
    else
    {
      wcsncpy(tmp, this->pwChar, startIdx);

      tmp[startIdx] = 0;
    }

    string result = tmp;

    delete tmp;

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::Replace(const string& oldVal, const string& newVal)
  {
    uint32 len = this->Length();
    uint32 lenOldVal = oldVal.Length();
    uint32 lenNewVal = newVal.Length();

    string result = this->pwChar;

    for(uint32 x = 0; x < len / lenOldVal; x += lenOldVal)
    {
      uint32 idx = result.IndexOf(oldVal, x);

      if(idx < 0)
        break;

      result = result.Remove(idx, lenOldVal);
      result = result.Insert(idx, newVal);
    }

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  bool string::StartsWith(const string& val)
  {
    string tmp = this->Substring(0, val.Length());

    return tmp.Equals(val);
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::Substring(uint32 startIdx)
  {
    string result = &this->pwChar[startIdx];

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::Substring(uint32 startIdx, uint32 length)
  {
    string result = &this->pwChar[startIdx];

    result = result.Remove(length);

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  string* string::Split(const char& separator, uint32* numElements)
  {
    *numElements = this->NumberOf(separator) + 1;
    string* splitted = new string[*numElements + 1];

    uint32 idx = 0;
    uint32 prev_i = 0;
    for(uint32 i=0; i<this->Length(); i++)
    {
      if(this->pwChar[i] == separator)
      {        
        splitted[idx] = this->Substring(prev_i, i - prev_i);        
        prev_i = i + 1;
        idx++;

        if(idx >= *numElements - 1)
        {
          splitted[idx] = this->Substring(prev_i, this->Length() - prev_i);  
          break;
        }
      }
    }

    return splitted;
  }

  // ***************************************************************************
  // ***************************************************************************
  uint32 string::NumberOf(const char& value)
  {
    uint32 count = 0;

    for(uint32 i=0; i<this->Length(); i++)
    {
      if(this->pwChar[i] == value)
      {
        count++;
      }
    }

    return count;
  }

  // ***************************************************************************
  // ***************************************************************************
  const char* string::ToChar()
  {
    if(this->pChar != 0)
      delete this->pChar;

    uint32 len = this->Length();

    this->pChar = new char[len + 1];

    for(uint32 i=0; i < len; i++)
      this->pChar[i] = (char)this->pwChar[i];

    this->pChar[len] = 0;

    return this->pChar;
  }

  // ***************************************************************************
  // ***************************************************************************
  const char* string::ToChar(uint32 startIdx, uint32 length)
  {
    if(this->pChar != 0)
      delete this->pChar;

    string tmp = this->Substring(startIdx, length);

    uint32 len = this->Length();

    this->pChar = new char[len + 1];

    for(uint32 i=0; i < len; i++)
      this->pChar[i] = (char)tmp.pwChar[i];

    this->pChar[len] = 0;

    return this->pChar;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::ToUpper()
  {
    string result = *this;

    for(uint32 i=0;i<result.Length();i++)
    {
      if((uint32)result.pwChar[i] >= 97 && (uint32)result.pwChar[i] <= 122)
      {
        result.pwChar[i] -= 32;
      }
    }

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::ToLower()
  {
    string result = *this;

    for(uint32 i=0;i<result.Length();i++)
    {
      if((uint32)result.pwChar[i] >= 65 && (uint32)result.pwChar[i] <= 90)
      {
        result.pwChar[i] += 32;
      }
    }

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::TrimStart()
  {
    uint32 numElementsToRemove = 0;
    uint32 len = this->Length();

    for(uint32 i=0;i<len;i++)
    {
      if((uint32)this->pwChar[i] != 32)
        break;

      numElementsToRemove++;
    }

    string result = *this;

    result = result.Remove(0, numElementsToRemove);

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::TrimEnd()
  {
    uint32 numElementsToRemove = 0;
    uint32 len = this->Length();

    for(uint32 i=len-1;i>0;i--)
    {
      if((uint32)this->pwChar[i] != 32)
        break;

      numElementsToRemove++;
    }

    string result = *this;

    result = result.Remove(len - numElementsToRemove, numElementsToRemove);

    return result;
  }

  // ***************************************************************************
  // ***************************************************************************
  string string::Trim()
  {
    string a = this->TrimStart();
    return a.TrimEnd();
  }
}}