
#include "word_error.h"
#include <stdio.h>

namespace word
{
	void ErrHandler(HRESULT hr, EXCEPINFO excep)
	{
		if(hr==DISP_E_EXCEPTION)
		{
			TCHAR errMsg[512];
            _stprintf(errMsg, 512, TEXT("Run-time error %d:\n\n %s"),
					excep.scode & 0x0000FFFF,  //Lower 16-bits of SCODE
					excep.bstrDescription);    //Text error description
			::MessageBox(NULL, errMsg, TEXT("Server Error"), MB_SETFOREGROUND |
						 MB_OK);
		}
		else
		{
			LPVOID lpMsgBuf;
			::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
							FORMAT_MESSAGE_FROM_SYSTEM |
							FORMAT_MESSAGE_IGNORE_INSERTS, NULL, hr,
							MAKELANGID(LANG_NEUTRAL,
							SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,
							0, NULL);
			::MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("COM Error"),
						 MB_OK | MB_SETFOREGROUND);
			::LocalFree( lpMsgBuf );
		}
	}

}