#pragma once

/// Platform specific includes
#include <time.h>

// Framework specific includes
#include "Datatypes.h"
#include "string_.h"

namespace Framework { namespace Core {

  /// @brief Base class for all framework sepcific classes.
  ///
  /// @remarks Must be used if ::Framework::Core::Ptr is used!
  ///
  class Object
  {
    // -------------------------------------------------------------------------
    // PUBLIC MEMBERS
    // -------------------------------------------------------------------------

  public:
    
    inline Object()
    {
      time(&this->timestamp);

      this->count = 0;
    }

    virtual ~Object()
    {
      // Nothing to do here ;)
    }

    inline void AddRef()
    {
      this->count++;
    }

    inline void ReleaseRef()
    {
      this->count--;

      if(this->count <= 0)
        this->Dispose();
    }

    virtual uint64 GetHashCode()
    {
      return ((this->timestamp % 64) << 1) + this->count;
    }

    virtual string ToString()
    {
      return "Framewor.Core.Object";
    }


    // -------------------------------------------------------------------------
    // PROTECTED MEMBERS
    // -------------------------------------------------------------------------

  protected:

    virtual void Dispose()
    {
      delete this;      
    }


    // -------------------------------------------------------------------------
    // PRIVATE MEMBERS
    // -------------------------------------------------------------------------

  private:

    /// @brief Reference counter.
    ///
    uint32 count;

    /// @brief The creation time in seconds (elapsed since 1970).
    ///
    time_t timestamp;
  };

}}