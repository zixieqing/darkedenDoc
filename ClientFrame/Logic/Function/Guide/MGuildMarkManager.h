//----------------------------------------------------------------------
// MGuildMarkManager.h
//----------------------------------------------------------------------
/*

  [ file ���� ]

	CSpritePack			guildMarkSPK;			// ��� ��ũ �׸���
	SpriteIDMapper		guildMarkSpriteMapper;	// ���ID --> SpriteID�� mapping

	* ���ID�� guildMarkSpriteMapper���� ã����.. ���õ� SpriteID�� �� �� �ִ�.
	  guildMarkSPKIndex���� �� SpriteID�� �� ���Sprite�� SpriteIndex�� 
	  �� �� �����Ƿ�.. �ٷ� Load�ؿ� �� �ִ�.

	* �����Ҷ���.. guildMarkSPK(+SPKIndex)�� �߰��ϰ� �� ���� ID��
	  �� ���ID�� �����ؼ� guildMarkSpriteMapper�� �߰��صθ� �ȴ�.

	* guildMarkSpriteMapper�� mapping�� ���� �ʴ� guildMarkSprite�� ��������.
	  �뷮�� �׸� ũ�� �����Ƿ� �����ϴ� �ð��� ���̴°� ���ٰ� �Ǵ��ؼ��̴�.

	* Ŭ���̾�Ʈ���� guildMarkSPK�� guildMarkSpriteMapper�� �ٸ� �� �ִ�.



  [ memory ���� ]

	map< ���ID, ��帶ũSprite* >

	// ��� ��ũ�� �����ϴ� ���(
	bool		CreateGuildMark(���ID, *.bmp || *.jpg);

	// ��� ��ũ�� �߰��ϴ� ���
	bool		AddGuildMark(���ID, CSprite*);

	// ��� ��ũ�� ����Ϸ��� sprite�� ��� ���
	CSprite*	GetGuildMark(���ID);

	// ��� ��ũ�� ȭ�Ͽ��� �а�/����
	bool		LoadGuildMark(���ID);
	bool		SaveGuildMark(���ID);



	//-------------------------------------------------
	// guild mark ��� ����
	//-------------------------------------------------
	int guildID = ...

	//-------------------------------------------------
	// load�Ǿ� �ִ��� ����.
	//-------------------------------------------------
	CSprite* pSprite = g_pGuildMarkManager->GetGuildMark(guildID);

	if (pSprite==NULL)
	{		
		//-------------------------------------------------
		// file�� �ִ��� ����.
		//-------------------------------------------------
		g_pGuildMarkManager->LoadGuildMark(guildID);

		//-------------------------------------------------
		// file���� load�Ǿ����� �ٽ� üũ
		//-------------------------------------------------
		pSprite = g_pGuildMarkManager->GetGuildMark(guildID);

		//-------------------------------------------------
		// file���� ���� ���..
		// guildMark��������?���� �޾ƿ´�.
		//-------------------------------------------------
		if (pSprite==NULL)
		{
			// ���⼭��.. �ӽ÷� ȭ�Ͽ��� �����Ѵ�.
			char str[256];
			sprintf(str, "Data\\Guild\\Guild%d.bmp", guildID);
			g_pGuildMarkManager->CreateGuildMark( guildID, str );
		}
	}
	else
	{			
		// �����ŵ� �� �� ����.
		CSprite* pSpriteSmall = g_pGuildMarkManager->GetGuildMarkSmall(guildID);

		m_pSurface->Lock();

		POINT point = { 100, 100 };

		m_pSurface->BltSprite(&point, pSprite);

		if (pSpriteSmall!=NULL)
		{
			point.x = 150;
			point.y = 100;
			m_pSurface->BltSprite(&point, pSpriteSmall);
		}

		m_pSurface->Unlock();
	}	
*/
//----------------------------------------------------------------------

#ifndef __MGUILD_MARK_MANAGER_H__
#define __MGUILD_MARK_MANAGER_H__

#pragma warning(disable:4786)

#include "CSprite.h"
#include "CSpritePack.h"
#include "MString.h"
#include "RaceType.h"

#define GRADE_MARK_MAX 50
//----------------------------------------------------------------------
// MGuildMarkManager
//----------------------------------------------------------------------
class MGuildMarkManager {
	public :
		struct GUILD_SPRITES
		{
			GUILD_SPRITES(CSprite* _pSprite=NULL, CSprite* _pSpriteSmall=NULL)
			{
				pSprite = _pSprite;
				pSpriteSmall = _pSpriteSmall;
			}

			CSprite* pSprite;
			CSprite* pSpriteSmall;
		};

		typedef std::map<WORD, GUILD_SPRITES>		GUILDMARK_MAP;
		
	public :
		MGuildMarkManager(	const char* pGuildMarkSPKFilename, 
							const char* pGuildMarkSpriteIDMapperFilename,
							const char *pSlayerGradeMarkSPKFilename,
							const char *pVampireGradeMarkSPKFilename,
							const char *pOustersGradeMarkSPKFilename,
							const char *pLevelMarkSPKFilename
							);
		~MGuildMarkManager();

		bool			IsInit() const		{ return (m_GuildMarkSPKFilename.GetLength()+m_GuildMarkSpriteMapperFilename.GetLength())!=0; }

		//----------------------------------------------------------
		// Release
		//----------------------------------------------------------
		void			Release();

		//----------------------------------------------------------
		// Create( guildID, pFilename�� *.bmp || *.jpg )
		//----------------------------------------------------------
		bool			CreateGuildMark(WORD guildID, const char* pFilename);
		static bool		CreateGuildMark(const char* pFilename, CSprite *&pSprite, CSprite *&pSpriteSmall);

		//----------------------------------------------------------
		// Add / Get
		//----------------------------------------------------------
		bool			HasGuildMark(WORD guildID) const;
		bool			AddGuildMark(WORD guildID, CSprite* pSprite, CSprite* pSpriteSmall);
		CSprite*		GetGuildMark(WORD guildID);
		CSprite*		GetGuildMarkSmall(WORD guildID);

		CSprite*		GetGradeMark(WORD gradeID, Race race);
		CSprite*		GetGradeMarkSmall(WORD gradeID, Race race);

		CSprite*		GetLevelMark(WORD level);
		CSprite*		GetLevelMarkSmall(WORD level);

		//----------------------------------------------------------
		// File I/O
		//----------------------------------------------------------
		bool			LoadGuildMark(WORD guildID);
		bool			SaveGuildMark(WORD guildID, CSprite* pSprite, CSprite* pSpriteSmall);
		static bool		MergeGuildMark(const char* pSPKFilenameOrg, const char* pIDMapperFilenameOrg,
										const char* pSPKFilenameApp, const char* pIDMapperFilenameApp);
//		bool			LoadGradeMark(WORD gradeSpriteID);

	protected :
		MString						m_GuildMarkSPKFilename;
		MString						m_GuildMarkSpriteMapperFilename;
		GUILDMARK_MAP				m_GuildMarks;

//		MString						m_SlayerGradeMarkSPKFilename;
//		MString						m_VampireGradeMarkSPKFilename;
		CSpritePack					m_GradeMarks[RACE_MAX];
		CSpritePack					m_LevelMarks;
};

//----------------------------------------------------------------------
// global
//----------------------------------------------------------------------
extern MGuildMarkManager* g_pGuildMarkManager;

#endif

