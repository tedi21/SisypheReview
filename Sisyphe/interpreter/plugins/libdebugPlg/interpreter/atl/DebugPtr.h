#ifndef _DEBUG_PTR_H_
#define _DEBUG_PTR_H_

template <class T>
class CDebugPtr
{
private:
    T* p;
    
    void copy(T* lp)
    {
      p = lp;
      if (p != NULL)
      {
        p->AddRef();
      }
    }
    void tidy()
    {
      if (p)
      {
        p->Release();
      }
    }
    T* operator=(T* lp) throw();

public:
    CDebugPtr() throw()
    {
      copy(NULL);
    }
    CDebugPtr(T* lp) throw()
    {
      copy(lp);
    }
    CDebugPtr(const CDebugPtr<T>& lp) throw()
    {
      copy(lp.p);
    }
    ~CDebugPtr() throw()
    {
      tidy();
    }
    operator T*() const throw()
    {
        return p;
    }
    T& operator*() const
    {
        return *p;
    }
    T** operator&() throw()
    {
        return &p;
    }
    T* operator->() const throw()
    {
        return p;
    }
    bool operator!() const throw()
    {	
        return (p == NULL);
    }
    CDebugPtr<T>& operator=(const CDebugPtr<T>& lp) throw()
    {
        if (lp.p != p)
        {
            tidy();
            copy(lp.p);
        }
        return *this;
    }
    void reset(T* lp) throw()
    {
        if (lp != p)
        {
            tidy();
            copy(lp);
        }
    }
};


#endif // _DEBUG_PTR_H_
