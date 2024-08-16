// heckSystem.cpp: implementation of the CheckSystem class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "checkSystemVer.h"
#include "heckSystem.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CheckSystem::CheckSystem()
{

}

CheckSystem::~CheckSystem()
{

}

BOOL CheckSystem::GetSystem()
{
	OSVERSIONINFO OsInfo;
	OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&OsInfo))
	{
		// platform
		switch (OsInfo.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_WINDOWS:
			if(OsInfo.dwMajorVersion == 3)
				//MessageBox(0,"����ϵͳ:WIN95","��Ϣ",MB_OK);
				//strcpy(sys.chSystem,"����ϵͳ:WIN95");
				//return FALSE;
			else if(OsInfo.dwMajorVersion == 4)
				//MessageBox(0,"����ϵͳ:WIN98","��Ϣ",MB_OK);
				//return FALSE;
				//strcpy(sys.chSystem,"����ϵͳ:WIN98");
			break;
		case VER_PLATFORM_WIN32_NT:
			if(OsInfo.dwMajorVersion == 5)
				//MessageBox(0,"����ϵͳ:WIN2000","��Ϣ",MB_OK);
				//return TRUE;
				//strcpy(sys.chSystem,"����ϵͳ:WIN2000");
			else
				//return TRUE;
				//MessageBox(0,"����ϵͳ:WINNT","��Ϣ",MB_OK);
				//strcpy(sys.chSystem,"����ϵͳ:WINNT");
			break;
		default:
			//return FALSE;
			//strcpy(sys.chSystem,"δ֪ϵͳ!!");
			break;
		}
		// version and language
	}
	return FALSE;
}
