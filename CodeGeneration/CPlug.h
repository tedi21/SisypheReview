#ifndef _CPLUG_H_
#define _CPLUG_H_

#include <stdexcept>
#include <stdarg.h>

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
    template <class Plug>
    class CPlug
    {
    private:
        CPlug(const CPlug &rPlug);
        void operator=(const CPlug&);
    public:
        CPlug():m_pPlug(NULL),m_hDLL(NULL){}
        CPlug(LPCTSTR szFileName):m_pPlug(NULL),m_hDLL(NULL),m_bLoad(false)
        {
            if(!LoadPlugin(szFileName))
                throw std::invalid_argument("Nom de DLl Incorrect");
        }
        ~CPlug()
        {
            FreePlugin();
        }
        void FreePlugin() // libération du plugin
        {
            if(m_bLoad)
            {
                FreeLibrary(m_hDLL);
                m_hDLL = NULL;
                m_pPlug = NULL;
            }
            m_bLoad = false;
        }
        bool LoadPlugin(LPCTSTR szFileName)// lecture plugin
        {
            //
            FreePlugin();
            m_hDLL = LoadLibrary(szFileName);
            if(m_hDLL<(HINSTANCE)0x20)
            {
                return false;
            }
            m_bLoad = true;
            return true;
        }

        Plug *GetPlugIn( int amount, ... )// recuperation d'une instance de la classe du plugin.
        {
            //
            if(m_pPlug) return m_pPlug;

            if(!m_bLoad) return NULL;
            typedef void (*LPDLLFUNC)(va_list, Plug **);
            LPDLLFUNC lpfnDllFunc = NULL;
            lpfnDllFunc = (LPDLLFUNC)::GetProcAddress(m_hDLL, "PlugInit");
            if (!lpfnDllFunc)
            {
                //TRACE(_T("\nPas de Fonction PlugInit dans la DLL!!"));
                FreePlugin();
                return NULL;
            }
            va_list vl;
            va_start(vl,amount);
            lpfnDllFunc(vl, &m_pPlug);
            va_end(vl);

            return m_pPlug;
        }

        void ReleasePlugIn()// libère une instance de la classe du plugin.
        {
            //
            if(m_pPlug && m_bLoad) {
                typedef void (*LPDLLFUNC)(Plug **);
                LPDLLFUNC lpfnDllFunc = NULL;
                lpfnDllFunc = (LPDLLFUNC)::GetProcAddress(m_hDLL, "PlugTerm");
                if (!lpfnDllFunc)
                {
                    //TRACE(_T("\nPas de Fonction PlugTerm dans la DLL!!"));
                    FreePlugin();
                }
                lpfnDllFunc(&m_pPlug);
                m_pPlug = NULL;
            }
        }

    protected:
        Plug            *m_pPlug;
        HINSTANCE        m_hDLL;
        bool             m_bLoad;
    };
#else
#include <unistd.h>
#include <dlfcn.h>

    template <class Plug>
    class CPlug {
    private:
        CPlug(const CPlug &rPlug);
        void operator=(const CPlug&);
    public:
        CPlug():m_pPlug(NULL),m_dlHandle(NULL),m_bLoad(false){}
        CPlug(const char* szFileName)
        {
            if(!LoadPlugin(szFileName))
                throw std::invalid_argument("Nom de DLl Incorrect");
        }
        ~CPlug()
        {
            FreePlugin();
        }
        void FreePlugin()
        {
            if(m_bLoad)
            {
                dlclose(m_dlHandle);
                m_dlHandle = NULL;
                m_pPlug = NULL;
            }
            m_bLoad = false;
        }
        bool LoadPlugin(const char* szFileName)
        {
            FreePlugin();
            m_dlHandle = dlopen(szFileName, RTLD_NOW);
            if(m_dlHandle == NULL)
            {
                return false;
            }
            m_bLoad = true;
            return true;
        }
        Plug *GetPlugIn( int amount, ... )
        {
            if(m_pPlug) return m_pPlug;

            if(!m_bLoad) return NULL;
            typedef void (*LPDLLFUNC)(va_list, Plug **);
            LPDLLFUNC lpfnDllFunc = NULL;
            lpfnDllFunc = (LPDLLFUNC)dlsym(m_dlHandle, "PlugInit");
            if (!lpfnDllFunc)
            {
                FreePlugin();
                return NULL;
            }
            va_list vl;
            va_start(vl,amount);
            lpfnDllFunc(vl, &m_pPlug);
            va_end(vl);

            return m_pPlug;
        }
        void ReleasePlugIn()
        {
            if(m_pPlug && m_bLoad) {
                typedef void (*LPDLLFUNC)(Plug **);
                LPDLLFUNC lpfnDllFunc = NULL;
                lpfnDllFunc = (LPDLLFUNC)dlsym(m_dlHandle, "PlugTerm");
                if (!lpfnDllFunc)
                {
                    FreePlugin();
                }
                lpfnDllFunc(&m_pPlug);
                m_pPlug = NULL;
            }
        }
    protected:
        Plug            *m_pPlug;
        void            *m_dlHandle;
        bool             m_bLoad;
    };
#endif



#endif
