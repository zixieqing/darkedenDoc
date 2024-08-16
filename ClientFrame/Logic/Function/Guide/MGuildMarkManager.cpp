//----------------------------------------------------------------------
// MGuildMarkManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MGuildMarkManager.h"
#include "MGuildInfoMapper.h"
#include "CSprite555.h"
#include "CSprite565.h"
#include "UtilityFunction.h"

#if defined(__GAME_CLIENT__) || defined(__GUILD_MANAGER_TOOL__)
	#include "UtilityFunction.h"
	#include "AppendPatchInfo.h"
	#include "DebugInfo.h"
#endif

//----------------------------------------------------------------------
// global
//----------------------------------------------------------------------
MGuildMarkManager* g_pGuildMarkManager = NULL;

extern bool g_bUseProgressBar;


//----------------------------------------------------------------------
//
//						MGuildMarkManager
//
//----------------------------------------------------------------------
MGuildMarkManager::MGuildMarkManager(const char* pGuildMarkSPKFilename, 
									const char* pGuildInfoMapperFilename,
									const char* pSlayerGradeMarkSPKFilename,
									const char* pVampireGradeMarkSPKFilename,
									const char* pOustersGradeMarkSPKFilename,
									const char* pLevelMarkSPKFilename)
{
	m_GuildMarkSPKFilename = pGuildMarkSPKFilename;

//	m_SlayerGradeMarkSPKFilename = pSlayerGradeMarkSPKFilename;
//	m_VampireGradeMarkSPKFilename = pVampireGradeMarkSPKFilename;

	// SpriteIDMapper�� ȭ�Ͽ��� �о���δ�.
	if (pGuildInfoMapperFilename!=NULL)
	{
		m_GuildMarkSpriteMapperFilename = pGuildInfoMapperFilename;		
	}

//	m_GradeMarks.Init(GRADE_MARK_MAX<<2, CDirectDraw::Is565());
	m_GradeMarks[RACE_SLAYER].LoadFromFileRunning(pSlayerGradeMarkSPKFilename);
	m_GradeMarks[RACE_VAMPIRE].LoadFromFileRunning(pVampireGradeMarkSPKFilename);
	m_GradeMarks[RACE_OUSTERS].LoadFromFileRunning(pOustersGradeMarkSPKFilename);
	m_LevelMarks.LoadFromFileRunning(pLevelMarkSPKFilename);
}

MGuildMarkManager::~MGuildMarkManager()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void		
MGuildMarkManager::Release()
{
	GUILDMARK_MAP::iterator iMark = m_GuildMarks.begin();

	while (iMark != m_GuildMarks.end())
	{
		CSprite* pSprite = iMark->second.pSprite;
		CSprite* pSpriteSmall = iMark->second.pSpriteSmall;

		if (pSprite!=NULL)
		{
			delete pSprite;
		}

		if (pSpriteSmall!=NULL)
		{
			delete pSpriteSmall;
		}

		iMark++;
	}
	m_GuildMarks.clear();
}

//----------------------------------------------------------------------
// Create GuildMark( guildID, pFilename )
//
// pFilename�� *.bmp�̰ų� *.jpg
//
// imageȭ���� pFilename�� �о
// CSprite�� ���� ��, 
// guildMarkSPK(+SPKIndex)�� �߰��ϰ� �� ���� ID��
// guildID�� �����ؼ� guildMarkSpriteMapper�� �߰��صθ� �ȴ�.
//----------------------------------------------------------------------
bool		
MGuildMarkManager::CreateGuildMark(WORD guildID, const char* pFilename)
{
#if defined(__GAME_CLIENT__) || defined(__GUILD_MANAGER_TOOL__)
	if (pFilename==NULL)
	{
		return false;
	}

	//-----------------------------------------------------
	// pFilename�� Surface�� load�Ѵ�.
	//-----------------------------------------------------
	CDirectDrawSurface bmpSurface;
	if (!LoadImageToSurface(pFilename, bmpSurface))
	{
		return false;
	}
	
	const POINT bigSize = { 40, 40 };
	const POINT smallSize = { 20, 20 };
	
	CDirectDrawSurface surface;
	surface.InitOffsurface( bigSize.x, bigSize.y, DDSCAPS_SYSTEMMEMORY );
		
	RECT destBigRect = { 0, 0, bigSize.x, bigSize.y };
	RECT destSmallRect = { 0, 0, smallSize.x, smallSize.y };
	
	//-----------------------------------------------------
	// CSprite����
	//-----------------------------------------------------
	CSprite* pSprite = NULL;
	CSprite* pSpriteSmall = NULL;

	if (CDirectDraw::Is565())
	{
		pSprite = new CSprite565;
		pSpriteSmall = new CSprite565;
	}
	else
	{
		pSprite = new CSprite555;
		pSpriteSmall = new CSprite555;
	}

	//-----------------------------------------------------
	// surface --> CSprite
	//-----------------------------------------------------
	WORD* lpSurface;
	unsigned short pitch;

	RECT bmpRect = { 0, 0, bmpSurface.GetWidth(), bmpSurface.GetHeight() };

	// �Ķ����� ������̴�.
	CSprite::SetColorkey( 0x001F );

	// BigSize
	surface.FillSurface( 0 );
	surface.Blt(&destBigRect, &bmpSurface, &bmpRect);
	surface.LockW(lpSurface, pitch);
	pSprite->SetPixel(lpSurface, pitch, bigSize.x, bigSize.y);
	surface.Unlock();	

	// SmallSize
	surface.FillSurface( 0 );
	surface.Blt(&destSmallRect, &bmpSurface, &bmpRect);
	surface.LockW(lpSurface, pitch);				
	pSpriteSmall->SetPixel(lpSurface, pitch, smallSize.x, smallSize.y);
	surface.Unlock();	

	//-----------------------------------------------------
	// add
	//-----------------------------------------------------
	AddGuildMark(guildID, pSprite, pSpriteSmall);
#endif
	return true;
}

//----------------------------------------------------------------------
// A GuildMark
//----------------------------------------------------------------------
bool		
MGuildMarkManager::AddGuildMark(WORD guildID, CSprite* pSprite, CSprite* pSpriteSmall)
{
	if (!SaveGuildMark(guildID, pSprite, pSpriteSmall))
	{
		// ���� �ȵŵ� �ϴ� memory�� ������ �� �� �ִ�.		
		//return false;
	}

	GUILDMARK_MAP::iterator iMark = m_GuildMarks.find(guildID);

	// �̹� �ִٸ� �������� delete�ؾ� �Ѵ�.
	if (iMark != m_GuildMarks.end())
	{
		CSprite* pSprite = iMark->second.pSprite;
		CSprite* pSpriteSmall = iMark->second.pSpriteSmall;

		if (pSprite!=NULL)
		{
			delete pSprite;
		}

		if (pSpriteSmall!=NULL)
		{
			delete pSpriteSmall;
		}
	}

	m_GuildMarks[guildID] = GUILD_SPRITES( pSprite, pSpriteSmall );

	return true;
}

//----------------------------------------------------------------------
// Get GuildMark
//----------------------------------------------------------------------
CSprite*	
MGuildMarkManager::GetGuildMark(WORD guildID)
{
	GUILDMARK_MAP::iterator iMark = m_GuildMarks.find(guildID);

	if (iMark != m_GuildMarks.end())
	{
		return m_GuildMarks[guildID].pSprite;
	}

	return NULL;
}

//----------------------------------------------------------------------
// Get GuildMarkSmall
//----------------------------------------------------------------------
CSprite*	
MGuildMarkManager::GetGuildMarkSmall(WORD guildID)
{
	GUILDMARK_MAP::iterator iMark = m_GuildMarks.find(guildID);

	if (iMark != m_GuildMarks.end())
	{
		return m_GuildMarks[guildID].pSpriteSmall;
	}

	return NULL;
}

//----------------------------------------------------------------------
// Has GuildMark
//----------------------------------------------------------------------
bool			
MGuildMarkManager::HasGuildMark(WORD guildID) const
{
	GUILDMARK_MAP::const_iterator iMark = m_GuildMarks.find(guildID);

	if (iMark != m_GuildMarks.end())
	{
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// Load GuildMark
//----------------------------------------------------------------------
// ���ID�� guildMarkSpriteMapper���� ã����.. ���õ� SpriteID�� �� �� �ִ�.
// guildMarkSPKIndex���� �� SpriteID�� �� ���Sprite�� SpriteIndex�� 
// �� �� �����Ƿ�.. �ٷ� Load�ؿ� �� �ִ�.
//----------------------------------------------------------------------
bool		
MGuildMarkManager::LoadGuildMark(WORD guildID)
{
	// �̹� ������ load ���Ѵ�.
	GUILDMARK_MAP::iterator iMark = m_GuildMarks.find(guildID);

	if (iMark != m_GuildMarks.end())
	{
		return true;
	}

	MGuildInfoMapper::const_iterator iMapper = g_pGuildInfoMapper->find( guildID );

	if (iMapper!=g_pGuildInfoMapper->end())
	{
		GUILD_INFO* pInfo		= iMapper->second;
		TYPE_SPRITEID spriteID	= pInfo->GetSpriteID();

		//---------------------------------------------------------
		// file�̸� �غ�..
		//---------------------------------------------------------
		char spkiFilename[256];

		// filename.spki
		strcpy(spkiFilename, m_GuildMarkSPKFilename.GetString());
		strcat(spkiFilename, "i");

		class ifstream spkFile(m_GuildMarkSPKFilename.GetString(), ios::binary | ios::nocreate);
		class ifstream spkiFile(spkiFilename, ios::binary | ios::nocreate);

		TYPE_SPRITEID maxSpkSize = 0;

		if (spkFile.is_open()
			&& spkiFile.is_open())
		{			
			//---------------------------------------------------------
			// Sprite�� ������ �˾Ƴ���.
			//---------------------------------------------------------
			spkiFile.seekg( 0, ios::beg );
			spkiFile.read((char*)&maxSpkSize, 2);			

			if (spriteID < maxSpkSize)	// spriteIDüũ
			{
				long fp = 0;

				//-----------------------------------------------------
				// ��� ������� ã��
				//-----------------------------------------------------
				spkiFile.seekg( 2 + spriteID*sizeof(long), ios::beg );
				spkiFile.read((char*)&fp, 4);				
				spkiFile.close();

				spkFile.seekg( fp, ios::beg );

				//-----------------------------------------------------
				// CSprite����
				//-----------------------------------------------------
				CSprite* pSprite = NULL;
				CSprite* pSpriteSmall = NULL;

				if (CDirectDraw::Is565())
				{
					pSprite = new CSprite565;
					pSpriteSmall = new CSprite565;
				}
				else
				{
					pSprite = new CSprite555;
					pSpriteSmall = new CSprite555;
				}

				//-----------------------------------------------------
				// Load �ؼ� 
				//-----------------------------------------------------
				pSprite->LoadFromFile( spkFile );
				pSpriteSmall->LoadFromFile( spkFile );	
				
				spkFile.close();

				m_GuildMarks[guildID] = GUILD_SPRITES( pSprite, pSpriteSmall );

				return true;
			}
		}		
	}

	// ȭ�Ͽ� ���ٴ� ���ϱ�..
	// �ٽ� üũ���ϵ��� NULL�� �־�д�.
	m_GuildMarks[guildID] = GUILD_SPRITES( NULL, NULL );

	return false;
}

//----------------------------------------------------------------------
// Save GuildMark
//----------------------------------------------------------------------
// m_GuildMarkSPKFilename���� max SpriteID�� ã�ƺ���..
// ȭ���� ���� CSprite�� �߰��Ѵ�.
// m_GuildMarkSPKIndexFilename���� �߰��ؾߵȴ�..
//
// ��� �߰��� spriteID�� return�ϸ� �ȴ�.
//----------------------------------------------------------------------
bool		
MGuildMarkManager::SaveGuildMark(WORD guildID, CSprite* pSprite, CSprite* pSpriteSmall)
{
	if (IsInit()
		&& pSprite!=NULL
		&& pSpriteSmall!=NULL)
	{
		//---------------------------------------------------------
		// file�̸� �غ�..
		//---------------------------------------------------------
		char spkiFilename[256];

		// filename.spki
		strcpy(spkiFilename, m_GuildMarkSPKFilename.GetString());
		strcat(spkiFilename, "i");

		
		//---------------------------------------------------------
		// file�� sprite�� �߰��Ѵ�.
		// index�� �߰��ؾ� �Ѵ�.
		//---------------------------------------------------------
		class ifstream spkInputFile(m_GuildMarkSPKFilename.GetString(), ios::binary | ios::nocreate);

		TYPE_SPRITEID maxSpkSize = 0;

		if (spkInputFile.is_open())
		{			
			//---------------------------------------------------------
			// Sprite�� ������ �˾Ƴ���.
			//---------------------------------------------------------
			spkInputFile.seekg( 0, ios::beg );
			spkInputFile.read((char*)&maxSpkSize, 2);
			spkInputFile.close();
		}

		
		class ofstream spkFile(m_GuildMarkSPKFilename.GetString(), ios::binary | ios::ate);
		class ofstream spkiFile(spkiFilename, ios::binary | ios::ate);
		
		if (spkFile.is_open()
			&& spkiFile.is_open())
		{
			//---------------------------------------------------------
			//
			//					SpritePack
			//
			//---------------------------------------------------------			

			//---------------------------------------------------------
			// sprite���� ����
			//---------------------------------------------------------
			TYPE_SPRITEID newSpkSize = maxSpkSize + 2;
			
			spkFile.seekp( 0, ios::beg );
			spkFile.write((const char*)&newSpkSize, 2);
			
			//---------------------------------------------------------
			// Spriteȭ���� ���� CSprite�� �߰��Ѵ�.			
			//---------------------------------------------------------
			spkFile.seekp( 0, ios::end );

			long fp = spkFile.tellp();		// index file�� ������ fp			
			pSprite->SaveToFile( spkFile );

			long fpSmall = spkFile.tellp();		// index file�� ������ fp
			pSpriteSmall->SaveToFile( spkFile );

			
			//---------------------------------------------------------
			//
			//					SpritePack Index
			//
			//---------------------------------------------------------					
			// SpriteIndex file ���� ����
			//---------------------------------------------------------
			spkiFile.seekp( 0, ios::beg );
			spkiFile.write((const char*)&newSpkSize, 2);

			//---------------------------------------------------------
			// SpriteIndex file�� fp�� �����Ѵ�.
			//---------------------------------------------------------
			spkiFile.seekp( 0, ios::end );
			spkiFile.write((const char*)&fp, 4);
			spkiFile.write((const char*)&fpSmall, 4);
	
			spkFile.close();
			spkiFile.close();

			//---------------------------------------------------------
			//
			//					GuildSpriteIDMapper
			//
			//---------------------------------------------------------
			// BigSpriteID = maxSpkSize
			// SmallSpriteID = maxSpkSize + 1
			GUILD_INFO* pInfo = g_pGuildInfoMapper->Get(guildID);

			if (pInfo!=NULL)
			{
				pInfo->SetSpriteID( maxSpkSize );
			}
			else
			{
				// ������ ����			
				pInfo = new GUILD_INFO;

				// default
//				pInfo->SetGuildName("Guild");
//				pInfo->SetLeaderName("Leader");				
				pInfo->SetSpriteID( maxSpkSize );

				g_pGuildInfoMapper->Set(guildID, pInfo);
			}			
			
			// file���� guildID�κи� newSpriteID�� �ٲٸ� �ȴ�.
			//class fstream mapperFile(m_GuildMarkSpriteMapperFilename.GetString(), ios::binary | ios::ate | ios::in | ios::out);
			//g_pGuildInfoMapper->ChangeValueToFile(m_GuildMarkSpriteMapperFilename.GetString(), guildID);

			class ofstream file(m_GuildMarkSpriteMapperFilename.GetString(), ios::binary);

			if (file.is_open())
			{
				g_pGuildInfoMapper->SaveToFile(file);
			}

			// GuildSpriteIDMapper ���� ����
			
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------
// MergeGuildMark
//----------------------------------------------------------------------
// org�� app�� �߰��ϰ�
// app�� �����.
//----------------------------------------------------------------------
bool		
MGuildMarkManager::MergeGuildMark(const char* pSPKFilenameOrg, 
									const char* pIDMapperFilenameOrg,
									const char* pSPKFilenameApp, 
									const char* pIDMapperFilenameApp)
{
	#if defined(__GAME_CLIENT__) || defined(__GUILD_MANAGER_TOOL__)
		if (pSPKFilenameOrg==NULL
			|| pIDMapperFilenameOrg==NULL
			|| pSPKFilenameApp==NULL
			|| pIDMapperFilenameApp==NULL)
		{
			return false;
		}

		//---------------------------------------------------------
		// file�̸� �غ�..
		//---------------------------------------------------------
		char pSPKIFilenameOrg[256];
		char pSPKIFilenameApp[256];

		sprintf(pSPKIFilenameOrg, "%si", pSPKFilenameOrg);
		sprintf(pSPKIFilenameApp, "%si", pSPKFilenameApp);
		

		//---------------------------------------------------------
		// SPKOrg�� maxSprite������ ����صд�.
		// (SPKApp�� 0 --> orgSize�� �ȴ�)
		// (SPKAppIndex�� 0 --> fpOrg-2(size�κ�)�� �ȴ�.)
		//---------------------------------------------------------
		class ifstream spkInputFile(pSPKFilenameOrg, ios::binary | ios::nocreate);
		class ifstream spkInputFileApp(pSPKFilenameApp, ios::binary | ios::nocreate);
		class ifstream spkiInputFileApp(pSPKIFilenameApp, ios::binary | ios::nocreate);

		TYPE_SPRITEID orgSize = 0;			// ���� ����
		TYPE_SPRITEID appSize = 0;			// �߰��� ����
		TYPE_SPRITEID orgiSize = 0;			// ���� ����
		TYPE_SPRITEID appiSize = 0;			// �߰��� ����
		long orgFP = 0;						// ���� file�� ũ��
		long appFP = 0;						// ���� file�� ũ��

		if (!spkInputFileApp.is_open()
			|| !spkiInputFileApp.is_open())	// �߰��Ұ� ���� ���
		{
			return false;
		}

		//---------------------------------------------------------
		// Sprite�� ������ �˾Ƴ���.
		//---------------------------------------------------------
		if (spkInputFile.is_open())
		{				
			spkInputFile.read((char*)&orgSize, 2);		

			spkInputFile.seekg( 0, ios::end );		
			orgFP = spkInputFile.tellg();

			spkInputFile.close();		
		}

		//---------------------------------------------------------
		// Sprite App�� ������ �˾Ƴ���.
		//---------------------------------------------------------
		spkInputFileApp.read((char*)&appSize, 2);
		spkiInputFileApp.read((char*)&appiSize, 2);

		spkInputFileApp.seekg( 0, ios::end );		
		appFP = spkInputFileApp.tellg();

		spkInputFileApp.close();
		spkiInputFileApp.close();

		if (appSize <= 0
			|| appSize!=appiSize)		
		{
			return false;
		}

		//-----------------------------------------------------------------------------
		// SpritePack Append
		//-----------------------------------------------------------------------------
		AppendPatch ap;
		
		ap.SetOriginalInfo( pSPKFilenameOrg, orgFP, orgSize );
		ap.AddAppendInfo( pSPKFilenameApp, appFP, appSize );
		ap.SetFinalInfo( orgFP+appFP-2, orgSize+appSize );

		int errorCode = 0;	
		
		g_bUseProgressBar = false;	// execute patch�Ҷ� dialog �� ���� - -;

		if (ap.ExecutePatch())
		{
			if (!ap.CheckFinalInfo())
			{
				errorCode = 2;
			}
		}
		else
		{
			errorCode = 1;
		}

		g_bUseProgressBar = true;

		if (errorCode)
		{
			DEBUG_ADD_FORMAT("[Error] GuildMarkPatch Terrible! code=%d", errorCode); 
		}

		//-----------------------------------------------------------------------------
		// GuildMark.spki �� �����ؼ� �߰��Ѵ�.
		//-----------------------------------------------------------------------------
		class ofstream spkiFileOrg(pSPKIFilenameOrg, ios::binary | ios::ate);
		class ifstream spkiFileApp(pSPKIFilenameApp, ios::binary | ios::nocreate);

		TYPE_SPRITEID newSize = orgSize + appSize;

		// ���� ����
		spkiFileOrg.seekp( 0, ios::beg );
		spkiFileOrg.write((char*)&newSize, 2);
		
		spkiFileOrg.seekp( 0, ios::end );		// ������
		spkiFileApp.seekg( 2 );					// size�κ� �ǳʶ�� fp �κ��� ó������

		long fp;
		long addFP = orgFP - 2;					// size�κ� ���� ���� ȭ��(org) ��ŭ �ڷ�.
		for (int i=0; i<appiSize; i++)
		{
			spkiFileApp.read((char*)&fp, 4);

			fp += addFP;

			spkiFileOrg.write((char*)&fp, 4);
		}

		spkiFileOrg.close();
		spkiFileApp.close();
		
		//-----------------------------------------------------------------------------
		// MapperOrg, MapperApp�� load�ϰ�
		//
		// MapperApp�� �� spriteID�� spriteID + maxSpkSize�� �����ؼ�
		// MapperOrg�� �߰�(����)�Ѵ�.
		//-----------------------------------------------------------------------------
		MGuildInfoMapper mapperOrg;
		MGuildInfoMapper mapperApp;

		class ifstream mapperFileOrg(pIDMapperFilenameOrg, ios::binary | ios::nocreate);
		class ifstream mapperFileApp(pIDMapperFilenameApp, ios::binary | ios::nocreate);

		if (mapperFileOrg.is_open())
		{
			mapperOrg.LoadFromFile( mapperFileOrg );
			mapperFileOrg.close();
		}

		if (mapperFileApp.is_open())
		{
			mapperApp.LoadFromFile( mapperFileApp );
			mapperFileApp.close();
		}

		// app�� org�� �߰��Ѵ�.
		MGuildInfoMapper::const_iterator iMapper = mapperApp.begin();

		while (iMapper != mapperApp.end())
		{
			WORD guildID				= iMapper->first;
			GUILD_INFO*		pAppInfo	= iMapper->second;
			TYPE_SPRITEID	newSpriteID = pAppInfo->GetSpriteID() + orgSize;

			// �ִ��� üũ..
			GUILD_INFO* pInfo = mapperOrg.Get(guildID);

			if (pInfo!=NULL)
			{
				// sprite ID ����
				pInfo->SetSpriteID( newSpriteID );
			}
			else
			{
				// ������ ����			
				pInfo = new GUILD_INFO;

				*pInfo = *pAppInfo;

				// sprite ID ����
				pInfo->SetSpriteID( newSpriteID );

				mapperOrg.Set( guildID, pInfo );
			}		

			iMapper ++;
		}

		// MapperOrg�� �ٽ� �����Ѵ�.
		class ofstream mapperOutputFileOrg(pIDMapperFilenameOrg, ios::binary);
		mapperOrg.SaveToFile( mapperOutputFileOrg );
		mapperOutputFileOrg.close();

		//-----------------------------------------------------------------------------
		// SPKApp, MapperApp�� �����.
		//-----------------------------------------------------------------------------
		//remove(pSPKFilenameApp);		// append�ϸ鼭 ��������.
		remove(pSPKIFilenameApp);
		remove(pIDMapperFilenameApp);
	#endif

	return true;
}


////----------------------------------------------------------------------
//// Load GradeMark
////----------------------------------------------------------------------
//bool		
//MGuildMarkManager::LoadGradeMark(WORD gradeSpriteID)
//{
//	// �̹� �ִ� ���� ����
//	if(m_GradeMarks[gradeSpriteID].IsInit())
//		return true;
//
//	MString *filename = NULL;
//	int fileSpriteID = 0;
//
//	// �����̾�� �����̾��� GradeMark�� ���ε��� ���ִ�.
//	if(gradeSpriteID < GRADE_MARK_MAX*2)
//	{
//		filename = &m_SlayerGradeMarkSPKFilename;
//		fileSpriteID = gradeSpriteID;
//	}
//	else
//	{
//		filename = &m_VampireGradeMarkSPKFilename;
//		fileSpriteID = gradeSpriteID - GRADE_MARK_MAX*2;
//	}
//
//	// �����̸��� ������ retuen false;
//	if(filename->GetLength() == 0)
//		return false;
//	
//	//---------------------------------------------------------
//	// file�̸� �غ�..
//	//---------------------------------------------------------
//	char spkiFilename[256];
//	
//	// filename.spki
//	strcpy(spkiFilename, filename->GetString());
//	strcat(spkiFilename, "i");
//	
//	m_GradeMarks.LoadFromFileSprite(gradeSpriteID, fileSpriteID, filename->GetString(), spkiFilename);
//
//	return true;
//}

//----------------------------------------------------------------------
// Get GradeMark
//----------------------------------------------------------------------
CSprite*	
MGuildMarkManager::GetGradeMark(WORD gradeID, Race race)
{
	if(race >= RACE_MAX)
		return NULL;

	return &m_GradeMarks[race][gradeID*2];
}

//----------------------------------------------------------------------
// Get GradeMarkSmall
//----------------------------------------------------------------------
CSprite*	
MGuildMarkManager::GetGradeMarkSmall(WORD gradeID, Race race)
{
	if(race >= RACE_MAX)
		return NULL;
	
	return &m_GradeMarks[race][gradeID*2+1];
}

//----------------------------------------------------------------------
// Get LevelMark
//----------------------------------------------------------------------
CSprite*	
MGuildMarkManager::GetLevelMark(WORD level)
{
	return &m_LevelMarks[level*2];
}

//----------------------------------------------------------------------
// Get LevelMarkSmall
//----------------------------------------------------------------------
CSprite*	
MGuildMarkManager::GetLevelMarkSmall(WORD level)
{
	return &m_LevelMarks[level*2+1];
}



bool		
MGuildMarkManager::CreateGuildMark(const char* pFilename, CSprite *&pSprite, CSprite *&pSpriteSmall)
{
	if (pFilename==NULL)
	{
		return false;
	}

	//-----------------------------------------------------
	// pFilename�� Surface�� load�Ѵ�.
	//-----------------------------------------------------
	CDirectDrawSurface bmpSurface;
	if (!LoadImageToSurface(pFilename, bmpSurface))
	{
		return false;
	}
	
	const POINT bigSize = { 40, 40 };
	const POINT smallSize = { 20, 20 };
	
	CDirectDrawSurface surface;
	surface.InitOffsurface( bigSize.x, bigSize.y, DDSCAPS_SYSTEMMEMORY );
		
	RECT destBigRect = { 0, 0, bigSize.x, bigSize.y };
	RECT destSmallRect = { 0, 0, smallSize.x, smallSize.y };
	
	//-----------------------------------------------------
	// CSprite����
	//-----------------------------------------------------
	if (CDirectDraw::Is565())
	{
		pSprite = new CSprite565;
		pSpriteSmall = new CSprite565;
	}
	else
	{
		pSprite = new CSprite555;
		pSpriteSmall = new CSprite555;
	}

	//-----------------------------------------------------
	// surface --> CSprite
	//-----------------------------------------------------
	WORD* lpSurface;
	unsigned short pitch;

	RECT bmpRect = { 0, 0, bmpSurface.GetWidth(), bmpSurface.GetHeight() };

	// �Ķ����� ������̴�.
	CSprite::SetColorkey( 0x001F );

	// BigSize
	surface.FillSurface( 0 );
	surface.Blt(&destBigRect, &bmpSurface, &bmpRect);
	surface.LockW(lpSurface, pitch);
	pSprite->SetPixel(lpSurface, pitch, bigSize.x, bigSize.y);
	surface.Unlock();	

	// SmallSize
	surface.FillSurface( 0 );
	surface.Blt(&destSmallRect, &bmpSurface, &bmpRect);
	surface.LockW(lpSurface, pitch);				
	pSpriteSmall->SetPixel(lpSurface, pitch, smallSize.x, smallSize.y);
	surface.Unlock();	

	//-----------------------------------------------------
	// add
	//-----------------------------------------------------
//	AddGuildMark(guildID, pSprite, pSpriteSmall);
	return true;
}