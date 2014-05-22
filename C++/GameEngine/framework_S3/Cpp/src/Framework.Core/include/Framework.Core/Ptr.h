#pragma once

namespace Framework { namespace Core {

  /// @brief A simple but very effective smart pointer.
  ///
  /// @remarks Works only with objects that derive from ::Framework::Core::Object!
  ///
  template<class T>
  class Ptr
  {
  public:

    inline Ptr()
    {
      this->object = nullptr;
    }

    inline Ptr(const Ptr<T>& ptr)
    {
      if(ptr.object != nullptr)
        ptr.object->AddRef();

      this->object = ptr.object;
    }

    inline Ptr(T* object)
    {
      if(object != nullptr)
        object->AddRef();

      this->object = object;
    }

    ~Ptr()
    {
      if(this->object != nullptr)
        this->object->ReleaseRef();
    }

    inline Ptr<T>& operator=(T* object)
    {
      if(object != nullptr)
        object->AddRef();

      if(this->object != nullptr)
        this->object->ReleaseRef();

      this->object = object;

      return *this;
    }

    inline Ptr<T>& operator=(Ptr<T>& ptr)
    {
      if(ptr.object != nullptr)
        ptr.object->AddRef();

      if(this->object != nullptr)
        this->object->ReleaseRef();

      this->object = ptr.object;

      return *this;
    }

    inline operator T*() const
    {
      return this->object;
    }

    inline T* operator->() const
    {
      return this->object;
    }


  private:

    T* object;
  };

}}