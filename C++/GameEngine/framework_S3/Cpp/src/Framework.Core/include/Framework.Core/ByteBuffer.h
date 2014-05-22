#pragma once

// Framework specific includes
#include "Datatypes.h"
#include "Object.h"

namespace Framework { namespace Core {

  class ByteBuffer : public virtual Object
  {
    // -------------------------------------------------------------------------
    // PUBLIC MEMBERS
    // -------------------------------------------------------------------------

  public:

    /// @brief Creates an instance of ByteBuffer.
    ///
    /// @param size The size of the buffer in bytes.
    ///
    ByteBuffer(uint32 size)
    {      
      this->position = 0;

      this->size = size;

      this->buffer = new uint8[this->size];
    }

    /// @brief Destructor.
    ///
    ~ByteBuffer()
    {
      if(this->buffer != 0)
        delete this->buffer;
    }

    /// @brief Gets a pointer to the internal byte array.
    ///
    /// @returns A pointer to the internal byte array.
    ///
    uint8* GetBuffer()
    {
      return this->buffer;
    }

    void Reset()
    {
      this->position = 0;
    }

    uint32 GetSize()
    {
      return this->size;
    }

    void SetPosition(uint32 position)
    {
      this->position = position;
    }

    void Put(uint8 value)
    {
      this->buffer[this->position] = value;

      this->position += 1;
    }

    uint8 Get()
    {
      uint8 val = this->buffer[this->position];

      this->position -= 1;

      return val;
    }

    uint8 Peek(uint32 index)
    {
      return this->buffer[index];
    }

    uint16 Peek2B(uint32 index)
    {
      return (uint16)this->buffer[index] << 8 | (uint16)this->buffer[index + 1];
    }

    uint32 Peek4B(uint32 index)
    {
      return (uint32)this->buffer[index] << 24 | (uint32)this->buffer[index + 1] << 16 |
        (uint32)this->buffer[index + 2] << 8 | (uint32)this->buffer[index + 3];
    }

    void Poke(uint32 index, uint8 value)
    {
      this->buffer[index] = value;
    }

    void Poke2B(uint32 index, uint16 value)
    {
      this->buffer[index] = value >> 8;
      this->buffer[index + 1] = (uint8)value;
    }

    void Poke4B(uint32 index, uint32 value)
    {
      this->buffer[index] = (uint8)(value >> 24);
      this->buffer[index + 1] = (uint8)(value >> 16);
      this->buffer[index + 2] = (uint8)(value >> 8);
      this->buffer[index + 3] = (uint8)value;
    }


    // -------------------------------------------------------------------------
    // PRIVATE MEMBERS
    // -------------------------------------------------------------------------

  private:

    /// @brief Pointer to the internal byte array.
    ///
    uint8* buffer;

    /// @brief The total size of the byte array.
    ///
    uint32 size;

    /// @brief The current position pointer.
    //
    uint32 position;
  };
}}