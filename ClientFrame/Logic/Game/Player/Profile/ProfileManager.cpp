//----------------------------------------------------------------------
// ProfileManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include <direct.h>
#include <io.h>
#include "CDirectDraw.h"
#include "CSpritePack.h"
#include "UserInformation.h"
//#include "MFileDef.h"

#ifdef __GAME_CLIENT__
	#include "Properties.h"
#else
	#include "..\client\packet\Properties.h"
#endif

#include "UtilityFunction.h"
#include "ProfileManager.h"

#ifdef __GAME_CLIENT__
	#include "RequestUserManager.h"

	#include "packet\Cpackets\CGRequestIP.h"

	#include "ServerInfo.h"
	#include "RequestClientPlayerManager.h"
#endif

#include "DebugInfo.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
ProfileManager*		g_pProfileManager = NULL;

#define	PROFILE_NULL	"NULL"

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
ProfileManager::ProfileManager()
{
	InitializeCriticalSection(&m_Lock);
}

ProfileManager::~ProfileManager()
{
	Release();

	DeleteCriticalSection(&m_Lock);
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void
ProfileManager::Release()
{
	m_Profiles.clear();

	ReleaseRequire();
}

//----------------------------------------------------------------------
// Release Require
//----------------------------------------------------------------------
void			
ProfileManager::ReleaseRequire()
{
	Lock();
	m_Requires.clear();
	Unlock();
}

//----------------------------------------------------------------------
// Has Profile
//----------------------------------------------------------------------
bool
ProfileManager::HasProfile(const char* pName) const
{
	PROFILE_MAP::const_iterator iProfile = m_Profiles.find( std::string(pName) );

	if (iProfile!=m_Profiles.end())
	{
		if (iProfile->second==PROFILE_NULL)
		{
			return false;
		}

		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// Add Profile
//----------------------------------------------------------------------
// �̹� �ְų� ���ų� �������.
//----------------------------------------------------------------------
void
ProfileManager::AddProfile(const char* pName, const char* pFilename)
{
	m_Profiles[std::string(pName)] = std::string(pFilename);
}

//----------------------------------------------------------------------
// Add ProfileNULL
//----------------------------------------------------------------------
// ������ �ƿ� Profile�� ���� ���
//----------------------------------------------------------------------
void
ProfileManager::AddProfileNULL(const char* pName)
{
	m_Profiles[std::string(pName)] = PROFILE_NULL;
}

//----------------------------------------------------------------------
// Has ProfileNULL
//----------------------------------------------------------------------
// ������ �ƿ� Profile�� ���°�?
//----------------------------------------------------------------------
bool			
ProfileManager::HasProfileNULL(const char* pName) const
{
	PROFILE_MAP::const_iterator iProfile = m_Profiles.find( std::string(pName) );

	if (iProfile!=m_Profiles.end())
	{
		if (iProfile->second==PROFILE_NULL)
		{
			return true;
		}
	}

	return false;	
}

//----------------------------------------------------------------------
// Remove Profile
//----------------------------------------------------------------------
bool
ProfileManager::RemoveProfile(const char* pName)
{
	PROFILE_MAP::iterator iProfile = m_Profiles.find( std::string(pName) );

	if (iProfile!=m_Profiles.end())
	{
		m_Profiles.erase( iProfile );

		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// Get UserInfo
//----------------------------------------------------------------------
const char*
ProfileManager::GetFilename(const char* pName) const
{
	PROFILE_MAP::const_iterator iProfile = m_Profiles.find( std::string(pName) );

	if (iProfile!=m_Profiles.end())
	{
		// NULL�� ������ �Ŵ� �ƿ� Profile�� ���� ����̴�.
		if (iProfile->second==PROFILE_NULL)
		{
			return NULL;
		}

		return iProfile->second.c_str();
	}

	return NULL;
}

//----------------------------------------------------------------------
// RequestProfile
//----------------------------------------------------------------------
void			
ProfileManager::RequestProfile(const char* pName)
{
	if(pName == NULL)
		return;

	if (!HasRequire(pName))
	{
		AddRequire( pName );
	}

	/*
	// Update���� ó���Ѵ�.
#ifdef __GAME_CLIENT__
	//-------------------------------------------------------
	// �������̰ų� ���� �õ� ���� ���..
	//-------------------------------------------------------
	if (g_pRequestClientPlayerManager->HasConnection(pName)
		|| g_pRequestClientPlayerManager->HasTryingConnection(pName))
	{
	}
	//-------------------------------------------------------
	// �������� �ƴ� ���
	//-------------------------------------------------------
	else
	{
		RequestUserInfo* pUserInfo = g_pRequestUserManager->GetUserInfo(pName);

		//-------------------------------------------------------
		// ����� ������ �ִٸ� ���� �õ��� �Ѵ�.
		//-------------------------------------------------------
		if (pUserInfo!=NULL)
		{
			g_pRequestClientPlayerManager->Connect(pUserInfo->IP.c_str(), 
													pName, 
													REQUEST_CLIENT_MODE_PROFILE);
		}
		//-------------------------------------------------------
		// ����� ������ ���ٸ� ... ������ IP�� ��û�Ѵ�.
		//-------------------------------------------------------
		else
		{
			if (!g_pRequestUserManager->HasRequestingUser( pName ))
			{
				#ifdef CONNECT_SERVER
					// ������ IP�� ��û�Ѵ�.
					CGRequestIP _CGRequestIP;
					_CGRequestIP.setName( pName );

					g_pSocket->sendPacket( &_CGRequestIP );			
				#endif
	
				// ��û�صθ� IP�� ���� ��, ProfileManager�� üũ�ϰ� �ȴ�.
				g_pRequestUserManager->AddRequestingUser( pName, RequestUserManager::REQUESTING_FOR_PROFILE );
			}
		}
	}	
#endif
	*/
}

//----------------------------------------------------------------------
// Add Require
//----------------------------------------------------------------------
void			
ProfileManager::AddRequire(const char* pName)
{
	Lock();

	if (!HasProfile(pName)
		&& !HasProfileNULL(pName))
	{
		m_Requires[std::string(pName)] = 0;
	}

	Unlock();
}

//----------------------------------------------------------------------
// Has Require
//----------------------------------------------------------------------
bool			
ProfileManager::HasRequire(const char* pName) const
{
	if (m_Requires.find( std::string(pName) )==m_Requires.end())
	{
		return false;
	}

	return true;
}

//----------------------------------------------------------------------
// Remove Require
//----------------------------------------------------------------------
bool			
ProfileManager::RemoveRequire(const char* pName)
{
	Lock();

	REQUIRE_MAP::iterator iRequire = m_Requires.find( std::string(pName) );

	if (iRequire==m_Requires.end())
	{
		Unlock();
		return false;
	}

	m_Requires.erase( iRequire );

	Unlock();
	return true;
}

//----------------------------------------------------------------------
// Update
//----------------------------------------------------------------------
void			
ProfileManager::Update()
{
#ifdef __GAME_CLIENT__
	if (g_pRequestClientPlayerManager==NULL 
		|| g_pRequestUserManager==NULL)
	{				
		m_Requires.clear();
		return;
	}
#endif

	Lock();

	//--------------------------------------------------------------
	// request
	//--------------------------------------------------------------
	REQUIRE_MAP::iterator iRequire = m_Requires.begin();

	while (iRequire != m_Requires.end())
	{
		const char* pName = iRequire->first.c_str();

		//-------------------------------------------------------
		// profile�� ���� ���
		//-------------------------------------------------------
		if (HasProfile(pName)
			|| HasProfileNULL(pName))
		{
			REQUIRE_MAP::iterator iTemp = iRequire;
			iRequire ++;
			m_Requires.erase( iTemp );
			
			continue;
		}

		#ifdef __GAME_CLIENT__
			//-------------------------------------------------------
			// �������̰ų� ���� �õ� ���� ���..
			//-------------------------------------------------------
			if (g_pRequestClientPlayerManager->HasConnection(pName)
				|| g_pRequestClientPlayerManager->HasTryingConnection(pName)
				|| g_pRequestUserManager->HasRequestingUser( pName ))
			{				
			}
			//-------------------------------------------------------
			// �������� �ƴ� ���
			//-------------------------------------------------------
			else
			{
				RequestUserInfo* pUserInfo = g_pRequestUserManager->GetUserInfo(pName);

				//-------------------------------------------------------
				// ����� ������ �ִٸ� ���� �õ��� �Ѵ�.
				//-------------------------------------------------------
				if (pUserInfo!=NULL)
				{
					if( g_pUserInformation->bKorean == true )	// �ѱ� ������ p2p
					{
						g_pRequestClientPlayerManager->Connect(pUserInfo->IP.c_str(), 
																pName, 
																REQUEST_CLIENT_MODE_PROFILE);				
					}
				}
				//-------------------------------------------------------
				// ����� ������ ���ٸ� ... ������ IP�� ��û�Ѵ�.
				//-------------------------------------------------------
				else
				{
					if (!g_pRequestUserManager->HasRequestingUser( pName ))
					{
						if( g_pUserInformation->bKorean == true )
						{
							// ������ IP�� ��û�Ѵ�.
							CGRequestIP _CGRequestIP;
							_CGRequestIP.setName( pName );

							g_pSocket->sendPacket( &_CGRequestIP );			
			
						// ��û�صθ� IP�� ���� ��, ProfileManager�� üũ�ϰ� �ȴ�.
						g_pRequestUserManager->AddRequestingUser( pName, RequestUserManager::REQUESTING_FOR_PROFILE );
						}
					}
				}
			}	
		#endif

		iRequire ++;
	}

	Unlock();
}


//----------------------------------------------------------------------
// Init Profiles
//----------------------------------------------------------------------
// ���α׷��� ����� �� �ѹ� ��������ָ� �ȴ�.
//
// Profile/*.bmp �� �о Profile/*.spr�� �ٲ��ָ� �ȴ�.
//----------------------------------------------------------------------
void		
ProfileManager::InitProfiles()
{
	//-----------------------------------------------------------------
	// Profile Directory�� ������ �����Ѵ�.
	//-----------------------------------------------------------------
	char CWD[_MAX_PATH];

	if (_getcwd( CWD, _MAX_PATH )!=NULL)
	{	
		if (_chdir( g_pFileDef->getProperty("DIR_PROFILE").c_str()) == 0)
		{
			// �ִٸ�.. �ٽ� ���� DIR��..
			_chdir( CWD );
		}
		else
		{
			// DIR_PROFILE�� ���ٸ�.. ����..
			_mkdir( g_pFileDef->getProperty("DIR_PROFILE").c_str() );
		}		
	}

	char profileFiles[256];
	sprintf(profileFiles, "%s\\*.*", g_pFileDef->getProperty("DIR_PROFILE").c_str());
	
	char bmpFilename[256];

	struct _finddata_t	FileData;
	long				hFile;

	//-----------------------------------------------------------------
	// *.spr file�� ã�´�.
	//-----------------------------------------------------------------
	if ( (hFile = _findfirst( profileFiles, &FileData )) != -1L )
	{
		CSpritePack SPK;

		// [0]�� ������ (30, 38)
		// [1]�� ū�� (110, 139)		
		SPK.Init( 2);

		CDirectDrawSurface surface;
		
		const POINT bigSize = { 55, 70 };
		const POINT smallSize = { 30, 38 };

		surface.InitOffsurface( bigSize.x, bigSize.y, DDSCAPS_SYSTEMMEMORY );
		
		RECT destBigRect = { 0, 0, bigSize.x, bigSize.y };
		RECT destSmallRect = { 0, 0, smallSize.x, smallSize.y };

		do
		{
			sprintf(bmpFilename, "%s\\%s", g_pFileDef->getProperty("DIR_PROFILE").c_str(), FileData.name);
	
			//---------------------------------------------------------
			// bmp�� �о sprite�� �ٲ۴�.
			//---------------------------------------------------------
			char charName[256], spkFilename[256], spkiFilename[256];
			int lenFilename = strlen(FileData.name);

			// "�̸�.bmp"
			if (lenFilename< 8)
			{
				continue;
			}

			strncpy( charName, FileData.name, lenFilename-4 );	// .bmp�� ¥����.
			charName[lenFilename-4] = '\0';

			CDirectDrawSurface bmpSurface;

			if (LoadImageToSurface(bmpFilename, bmpSurface))
			{
				WORD* lpSurface;
				unsigned short pitch;

				// surface�� ũ�Ⱑ default Profileũ��� �ٸ��ٸ�
				// size�� ���������� �Ѵ�..	
				RECT bmpRect = { 0, 0, bmpSurface.GetWidth(), bmpSurface.GetHeight() };
				
				// SmallSize
				surface.Blt(&destSmallRect, &bmpSurface, &bmpRect);
				surface.LockW(lpSurface, pitch);				
				SPK[0].SetPixelNoColorkey(lpSurface, pitch, smallSize.x, smallSize.y);
				surface.Unlock();

				// BigSize
				surface.FillSurface( 0 );
				surface.Blt(&destBigRect, &bmpSurface, &bmpRect);
				surface.LockW(lpSurface, pitch);				
				SPK[1].SetPixelNoColorkey(lpSurface, pitch, bigSize.x, bigSize.y);
				surface.Unlock();
				
				// filename.spk
				int lenBmpFilename = strlen(bmpFilename);
				strncpy(spkFilename, bmpFilename, lenBmpFilename-3);
				spkFilename[lenBmpFilename-3] = '\0';
				strcat(spkFilename, "spk");

				// filename.spki
				strcpy(spkiFilename, spkFilename);
				strcat(spkiFilename, "i");

				class ofstream	spkFile(spkFilename, ios::binary);	
				class ofstream	spkiFile(spkiFilename, ios::binary);	
				SPK.SaveToFile( spkFile, spkiFile );
				spkFile.close();
				spkiFile.close();

				g_pProfileManager->AddProfile( charName, spkFilename );
			}
		}
		while (_findnext( hFile, &FileData ) == 0);

		_findclose( hFile );
	}
}

//----------------------------------------------------------------------
// Delete Profiles
//----------------------------------------------------------------------
// ���α׷��� ����� �� �ѹ� ��������ָ� �ȴ�.
//
// Profile/*.spr ȭ���� ��� ����� �ȴ�.
//----------------------------------------------------------------------
void		
ProfileManager::DeleteProfiles()
{
	char profileFiles[256], tempProfileFiles[256];
	sprintf(profileFiles, "%s\\*.spk*", g_pFileDef->getProperty("DIR_PROFILE").c_str());
	sprintf(tempProfileFiles, "%s\\*-spk*", g_pFileDef->getProperty("DIR_PROFILE").c_str());
	
	char spkFilename[256];

	struct _finddata_t	FileData;
	long				hFile;

	//-----------------------------------------------------------------
	// *.spk file�� ã�´�.
	//-----------------------------------------------------------------
	if ( (hFile = _findfirst( profileFiles, &FileData )) != -1L )
	{
		do
		{
			sprintf(spkFilename, "%s\\%s", g_pFileDef->getProperty("DIR_PROFILE").c_str(), FileData.name);			
			remove(spkFilename);
		}
		while (_findnext( hFile, &FileData ) == 0);

		_findclose( hFile );			
	}

	//-----------------------------------------------------------------
	// *.spk.tmp file�� ã�´�.
	//-----------------------------------------------------------------
	if ( (hFile = _findfirst( tempProfileFiles, &FileData )) != -1L )
	{
		do
		{
			sprintf(spkFilename, "%s\\%s", g_pFileDef->getProperty("DIR_PROFILE").c_str(), FileData.name);			
			remove(spkFilename);
		}
		while (_findnext( hFile, &FileData ) == 0);

		_findclose( hFile );			
	}
}

