#ifndef _DIA_PTR_H_
#define _DIA_PTR_H_

template <class T>
class CDiaPtr
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
    CDiaPtr() throw()
    {
      copy(NULL);
    }
    CDiaPtr(T* lp) throw()
    {
      copy(lp);
    }
    CDiaPtr(const CDiaPtr<T>& lp) throw()
    {
      copy(lp.p);
    }
    ~CDiaPtr() throw()
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
    CDiaPtr<T>& operator=(const CDiaPtr<T>& lp) throw()
    {
        if (lp.p != p)
        {
            tidy();
            copy(lp.p);
        }
    }
    void reset(T* lp) throw()
    {
        if (lp != p)
        {
            tidy();
            copy(lp);
        }
    }
    T* get() throw()
    {
        return p;
    }
};


#endif // _DIA_PTR_H_
