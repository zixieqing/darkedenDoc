//----------------------------------------------------------------------
// MTopView.h
//----------------------------------------------------------------------
//
// �� Zone�� Ư�� ��ġ�� ������ִ� class�̴�.
//
//----------------------------------------------------------------------
//
// DrawTile()     : ����Surface�� Tile�� �׸���.
//                  m_pTileSurface�� �׷��д�.
//
// DrawZone()	  : ���� Tile�� �̿��ؼ� ����Surface�� Tile�� �׸���
//                  Zone�� ��� �͵��� ǥ�����ش�.
//
// * ���� Tile�� ���ڱ� ��ȭ�Ҷ�(Zone�̵� ��, Teleport��)�� 
//   SetFirstDraw()�� ����ؼ� m_bFirstTileDraw = true�� �����ϸ� 
//   Draw()���� �ѹ��� DrawTile()�� �����ϰ� 
//                     �������ʹ� DrawZone()�� �����Ѵ�.
//
//---------------------------------------------------------------------- 
//
// - ������ Tile�� �����صδ� Surface�� ���� ȭ�� ũ�⺸�� ũ��.
//   (800,600)�� ����ȭ���̹Ƿ�,
//   �����¿�� 3 Tile��  (1152,768)���� Surface�� �����Ѵ�.
//
// - �̷��� �صθ� ������ Tile Surface���� ���� �ʿ��� ������
//   �о�ö�, �о���� ������ ������ Tile Surface�� ���ϸ� 
//   �ٽ� �׷���� �ϴ� �κ��� ���� �� �ִ�.
//   ����, �̷� ��� Tile Surface�� ������ �ʿ䵵 ����.
// 
// - �����̶��, �ٽ� �׷��� �� �׷�����ϴ� �κ��� ����~ �� ũ����
//   ������� �ӵ��� ���ǹǷ� �׸� ������ ���� ���̴�.
//
// * �׽�Ʈ�� ũ�⸦ �����غ�����...
//
//---------------------------------------------------------------------- 
//
// * SpriteSet / FrameSet�� ������ �о�;� �Ѵ�.
//
// [ MapView : Filename.MV ]   - View���� Load�Ѵ�.
//   Tile SpriteSet
//   Obstacle SpriteSet 
//   Obstacle FrameSet
//   ImageObject SpriteSet
//
//---------------------------------------------------------------------- 
//
// ImageObject Map...
//
// ���ʿ�... ��� Tile Scan
// �׸���.. ���� Tile���� ��ȭ�� ��ŭ�� Tile Scan
//
//---------------------------------------------------------------------- 

#ifndef	__MTOPVIEW_H__
#define	__MTOPVIEW_H__

#pragma warning(disable:4786)

#include "DX3D.h"
#include "MViewDef.h"
#include <map>
#include <queue>

//----------------------------------------------------------------------
//
// using class..
//
//----------------------------------------------------------------------
#include "MZone.h"
class MObject;
#include "MImageObject.h"
#include "MCreature.h"
class MMissile;
class MItem;
class MEffect;
#include "SP.h"
#include "FR.h"
//#include "2D.h"
#include "CSpriteTexturePartManager.h"
#include "CTexturePartManager.h"
#include "CShadowPartManager.h"
#include "DrawTextNode.h"
#include "DrawItemNameNode.h"
#include "COrderedList.h"
#include "MRequestMode.h"


//class MZoneInfo;
class TextComparison {
	public :
		// �ð��� �����Ȱ� �����ؾ� �Ѵ�.		
		// true : right�� �����Ѵ�.
		// false : left�� �����Ѵ�.
		bool operator () (DRAWTEXT_NODE * left, DRAWTEXT_NODE * right) const;
};

typedef void (*DrawCreatureExceptionProc)( MCreature* pCreature, int& action, int& frame, int& direction );

//----------------------------------------------------------------------
// �� Surface�� Ư���� Zone�� ���� �׸��� �׷��ִ� class
//----------------------------------------------------------------------
class MTopView : public MRequestMode {
	public :	
		// ��¿� �̿��� ImageObject map
		typedef std::map<QWORD, MImageObject*>			IMAGEOBJECT_OUTPUT_MAP;

		// ��¿� �̿��� Creature map
		typedef std::map<QWORD, MCreature*>				CREATURE_OUTPUT_MAP;

		// ��¿� �̿��� Item map
		typedef std::map<QWORD, MItem*>					ITEM_OUTPUT_MAP;

		// ����� string�� ����� ���� ��..
		//typedef	std::list<DRAWTEXT_NODE*>				DRAWTEXT_LIST;
		typedef std::priority_queue<DRAWTEXT_NODE*, std::vector<DRAWTEXT_NODE*>, TextComparison>	DRAWTEXT_PQ;

		// item�̸� ���
		typedef	std::list<DRAWITEMNAME_NODE*>			DRAWITEMNAME_LIST;

		// int ordered list
		typedef	COrderedList<int>						INT_ORDERED_LIST;

	public :
		MTopView();
		~MTopView();

		//------------------------------------------------------
		//
		// init
		//
		//------------------------------------------------------
		bool		Init();
		bool		InitChanges();	// 2D <--> 3D �ٲ�.. ���� - -;
		bool		IsInit() const		{ return m_bInit; }
		void		Release();
		void		SetSurface(CSpriteSurface*& pSurface);
		void		SetZone(MZone* pZone);
		void		RestoreSurface();
		void		ClearShadowManager();
		const FRAME_ARRAY&	GetCreatureFrameArray(int body, int action, int direction) const	{ return m_CreatureFPK[body][action][direction]; }
		const CIndexSprite*	GetCreatureSprite(int spriteID)		{ return &m_CreatureSPK[ spriteID ]; }

		//------------------------------------------------------
		//
		// Zone���� Load�ؾ� �ϴ� ��
		//
		//------------------------------------------------------		
		void		LoadMinimap(const char* filename);//, MZoneInfo* pZoneInfo=NULL);
		bool		LoadFromFileTileSPKLargeZone(class ifstream & file);	// zone���� spk load
		bool		LoadFromFileImageObjectSPKLargeZone(class ifstream & file);	// zone���� spk load
		bool		LoadFromFileTileSPKSmallZone(class ifstream & file);	// zone���� spk load
		bool		LoadFromFileImageObjectSPKSmallZone(class ifstream & file);	// zone���� spk load
		void		LoadFromFileCreatureSPK(int n);			// creature load		
// 		void		LoadFromFileAddonSPK(int frame, int action);		// addon load		
//		void		LoadFromFileCreatureActionSPK(int frame, int action);		// addon load		
		bool		LoadFromFileTileAndImageObjectSet(const CSpriteSetManager &TileSSM, const CSpriteSetManager &ImageObjectSSM);
		void		ReleaseCreatureSPK(int n);			// creature release
		void		ReleaseTileSPKLargeZone();
		void		ReleaseImageObjectSPKLargeZone();
		void		ReleaseTileSPKSmallZone();
		void		ReleaseImageObjectSPKSmallZone();
		//void		ReleaseAddonSPK(int frame, int action);
//		void		ReleaseCreatureActionSPK(int frame, int action);

		void		ReleaseUselessCreatureSPKExcept(const INT_ORDERED_LIST& listUse);
		void		AddMonsterSpriteTypes(const INT_ORDERED_LIST& liseUse);

//		void		StopLoadImageObjectSPK()	{ m_ImageObjectSPK.SetLoadingStop(); }
//		void		StopLoadTileSPK()			{ m_TileSPK.SetLoadingStop(); }

		// Tile�� ��� �ٽ� �׷�����Ҷ�
		void		SetFirstDraw()			{ m_bFirstTileDraw = true; }
		
		//------------------------------------------------------
		//
		// Draw Functions
		//
		//------------------------------------------------------
		void		Draw(int firstPointX, int firstPointY);

		// Test�� ����
		void		DrawDebugInfo(CDirectDrawSurface* pSurface);			
		void		DrawTestHelp();
		
		void		DrawMinimap(int x, int y, BYTE scale);

		void		DrawAlphaBox(RECT* pRect, BYTE r, BYTE g, BYTE b, BYTE alpha);

		void		DrawEffect(POINT* pPoint, EFFECT_LIST::const_iterator iEffect, BYTE size);
		
		void		DrawInventoryEffect(POINT* pPoint);

		void		DrawTitleEffect(POINT* pPoint);

		void		DrawBloodBibleEffect_InGear(POINT* pPoint);
		
		//------------------------------------------------------
		//
		// Fade In/out
		//
		//------------------------------------------------------
		bool			IsFade() const			{ return m_bFade; }
		void			SetFadeStart(char start, char end, char step, BYTE r=0, BYTE g=0, BYTE b=0, WORD delay = 0);
		void			SetFadeEnd() 			{ m_bFade = false; }
		
		//------------------------------------------------------
		//
		// ��ǥ ��ȯ		
		//
		//------------------------------------------------------
		static POINT	PixelToMap(const int& Xp, const int& Yp)	{ POINT p; p.x=Xp/TILE_X; p.y=Yp/TILE_Y; return p; }//{ POINT p; p.x=Xp>>6; p.y=Yp>>5; return p; }
		static POINT	MapToPixel(const int& Xm, const int& Ym)	{ POINT p; p.x=Xm*TILE_X; p.y=Ym*TILE_Y; return p; }//{ POINT p; p.x=Xm<<6; p.y=Ym<<5; return p; }

		static int		PixelToMapX(const int& Xp)		{ return (Xp/TILE_X); }
		static int		PixelToMapY(const int& Yp)		{ return (Yp/TILE_Y); }
		static int		MapToPixelX(const int& Xm)		{ return (Xm*TILE_X); }	
		static int		MapToPixelY(const int& Ym)		{ return (Ym*TILE_Y); }

		static BYTE		GetDirectionToPosition(int originX, int originY, int destX, int destY);
		static POINT	GetChangeValueToDirection(int direction);

		//------------------------------------------------------
		// TileSize�� 64*32�� ���.. ����ȭ�� ��ǥ ���(Shift�̿�)
		//------------------------------------------------------
		//static POINT	PixelToMap(const int& Xp, const int& Yp)	{ POINT p; p.x=Xp>>6; p.y=Yp>>5; return p; }
		//static POINT	MapToPixel(const int& Xm, const int& Ym)	{ POINT p; p.x=Xm<<6; p.y=Ym<<5; return p; }

		//static int		PixelToMapX(const int& Xp)		{ return (Xp >> 6); }
		//static int		PixelToMapY(const int& Yp)		{ return (Yp >> 5); }
		//static int		MapToPixelX(const int& Xm)		{ return (Xm << 6); }	
		//static int		MapToPixelY(const int& Ym)		{ return (Ym << 5); }


		//------------------------------------------------------
		//
		// View�� ȭ����� ����
		//
		//------------------------------------------------------
		// ȭ�� ���� ��ǥ (x,y)�� Zone������ pixel��ǥ�δ� ��� ���ΰ�?
		POINT			ScreenToPixel(int x, int y);

		// Zone�� pixel��ǥ�� ȭ�� ���� ��� ���ΰ�?
		POINT			MapToScreen(int sX, int sY);
		POINT			PixelToScreen(int x, int y);
		POINT			GetFirstZonePixel()	const		{ return m_FirstZonePixel; }		
		POINT			GetFirstSector() const			{ return m_FirstSector; }

		//------------------------------------------------------
		//
		// Mouse�� �����ϴ� Object
		//
		//------------------------------------------------------
		// Selected Sector
		inline void		SetSelectedSector(int sX, int sY)	{ m_SelectSector.x = sX; m_SelectSector.y = sY; }	
		inline void		SetSelectedSector(const POINT& s)	{ m_SelectSector.x = s.x; m_SelectSector.y = s.y; }
		void			SetSelectedSectorNULL()		{ m_SelectSector.x = m_SelectSector.y = SECTORPOSITION_NULL; }
		POINT			GetSelectedSector(int x, int y);// const;

		// ������ ���� ���� ���
		//void			SetSelectModeAttack()				{ m_bSelectModeAttack = true; }
		//void			SetSelectModeNormal()				{ m_bSelectModeAttack = false; }


		// ȭ����� (x,y)�� �������� ��� ���õ� Object�� return�Ѵ�.
		MObject*		GetSelectedObject(int x, int y);
		MObject*		GetSelectedObjectSprite(int x, int y);

		// Creature ����
//		void			SetSelectedCreature(TYPE_OBJECTID id)	{ m_SelectCreatureID = id; m_SelectItemID = m_SelectInteractionObjectID = m_SelectEffectID = OBJECTID_NULL; }		
		void			SetSelectedCreature(TYPE_OBJECTID id)	{ m_SelectCreatureID = id; m_SelectItemID = m_SelectEffectID = OBJECTID_NULL; }		
		TYPE_OBJECTID	GetSelectedCreature() const				{ return m_SelectCreatureID; }

		// Item ����
//		void			SetSelectedItem(TYPE_OBJECTID id)	{ m_SelectItemID = id;  m_SelectCreatureID = m_SelectInteractionObjectID = m_SelectEffectID = OBJECTID_NULL; }
		void			SetSelectedItem(TYPE_OBJECTID id)	{ m_SelectItemID = id;  m_SelectCreatureID = m_SelectEffectID = OBJECTID_NULL; }
		TYPE_OBJECTID	GetSelectedItemID()					{ return m_SelectItemID; }
		
		// InteractionObject ����
//		void			SetSelectedInteractionObject(TYPE_OBJECTID id)	{ m_SelectInteractionObjectID = id; m_SelectItemID = m_SelectCreatureID = m_SelectEffectID = OBJECTID_NULL; }

		// Effect ����
//		void			SetSelectedEffect(TYPE_OBJECTID id)		{ m_SelectEffectID = id; m_SelectItemID = m_SelectCreatureID = m_SelectInteractionObjectID = OBJECTID_NULL; }
		void			SetSelectedEffect(TYPE_OBJECTID id)		{ m_SelectEffectID = id; m_SelectItemID = m_SelectCreatureID =  OBJECTID_NULL; }
		
		// ���õ� ���� ���� �Ѵ�.
//		void			SetSelectedNULL()				{ m_SelectCreatureID = m_SelectItemID = m_SelectInteractionObjectID = m_SelectEffectID = OBJECTID_NULL;}
		void			SetSelectedNULL()				{ m_SelectCreatureID = m_SelectItemID = m_SelectEffectID = OBJECTID_NULL;}


		//------------------------------------------------------
		//
		// �þ� ����..
		//
		//------------------------------------------------------		
		BYTE			GetDarkBits() const				{ return m_DarkBits; }
		void			SetDarkBits(BYTE DarkBits)		{ if (DarkBits<16) m_DarkBits = DarkBits; }

		// 3D �þ߰���
		void			ClearLightBufferFilter3D();
		void			AddLightFilter3D(int x, int y, BYTE range, bool bMapPixel=true, bool bForceLight=false);
		void			DrawLightBuffer3D();

		// 2D �þ߰���
		void			ClearLightBufferFilter2D();
		void			AddLightFilter2D(int x, int y, BYTE range, bool bMapPixel=true, bool bForceLight=false);
		void			DrawLightBuffer2D();		

		//------------------------------------------------------
		//
		// Creature Output�� ���õ� �͵�
		//
		//------------------------------------------------------
		QWORD			GetOutputImageObjectID(const MImageObject* pImageObject) const
											{ return ((QWORD)pImageObject->GetViewpoint() << 32) | pImageObject->GetID(); }

		//------------------------------------------------------
		//
		// Creature Output�� ���õ� �͵�
		//
		//------------------------------------------------------		
		// [pixel y��ǥ][object id] ,  4 bytes  +  4 bytes  = 8 bytes �� �����Ǿ� �ִ�.
		QWORD			GetOutputCreatureID(const MCreature* pCreature) const	
											{ return ((QWORD)pCreature->GetPixelY() << 32) | pCreature->GetID(); }

		QWORD			GetOutputCreatureID(TYPE_OBJECTID id, int y) const	
											{ return ((QWORD)y << 32) | id; }

		// m_pZone�� Creature map�� ��°��~ �߰�
		void			AddOutputCreatureAll();

		// pCreature�� �߰��Ѵ�.
		bool			AddOutputCreature(MCreature* pCreature);

		// Creature OutputMap�� clear�Ѵ�.
		void			ClearOutputCreature()	{ m_mapCreature.clear(); }

		// id�� �����ִ� creature�� �����Ѵ�.
		bool			RemoveOutputCreature(MCreature* pCreature);

		// id�� �����ִ� creature�� ����(�����ǥ����id)�� Update�Ѵ�.
		bool			UpdateOutputCreature(TYPE_OBJECTID id, int y0, int y1);


		//------------------------------------------------------		
		//
		// ä�� string �� ���..
		//
		//------------------------------------------------------		
		void			ClearTextList();
		void			AddText(DRAWTEXT_NODE* pNode);
		void			DrawTextList();

		//------------------------------------------------------		
		//
		// ItemName  ���..
		//
		//------------------------------------------------------		
		bool			IsDrawItemNameList() const		{ return m_bDrawItemNameList; }
		void			SetDrawItemNameList()			{ m_bDrawItemNameList = true; }
		void			UnSetDrawItemNameList()			{ m_bDrawItemNameList = false; }
		void			ClearItemNameList();
		void			AddItemName(DRAWITEMNAME_NODE* pNode);
		void			DrawItemNameList();
		MItem*			SelectItemName(int x, int y);

		//------------------------------------------------------		
		//
		// Request
		//
		//------------------------------------------------------		
		bool			IsDrawRequest() const			{ return m_bDrawRequest; }
		
		//------------------------------------------------------		
		// Get MaxEffectFrame
		//------------------------------------------------------		
		int				GetMaxEffectFrame(BLT_TYPE bltType, TYPE_FRAMEID frameID) const;
		int				GetEffectLight(BLT_TYPE bltType, TYPE_FRAMEID frameID, int dir, int frame) const;
		int				GetEffectSpriteType(BLT_TYPE bltType, TYPE_FRAMEID frameID) const;

		//------------------------------------------------------		
		// ��Ÿ..
		//------------------------------------------------------		
		int				GetRandomMonsterTypeInZone() const;

//		void			InitMinimapTexture(CSpriteSurface *minimap_surface);			// minimap texture�ʱ�ȭ

	protected :
		//------------------------------------------------------
		//
		// ���������� �ʱ�ȭ�ϴ� �Լ���..
		//
		//------------------------------------------------------
		bool			InitCreatureFrames();		// character ���� �ʱ�ȭ
		bool			InitImageFrames();			// ImageFrames ���� �ʱ�ȭ
		bool			InitAnimationFrames();		// AnimationFrames �ʱ�ȭ
		bool			InitEffectFrames();			// EffectFrames �ʱ�ȭ
		bool			InitSprites();				// Sprites �ʱ�ȭ
		bool			InitSurfaces();				// Surfaces �ʱ�ȭ
		bool			InitFilters();				// Filter�ʱ�ȭ
		//bool	InitSpriteSurfaces();		// SpriteSurfaces �ʱ�ȭ 
		bool			InitColors();				// ����� �ʱ�ȭ
// 		bool			Init3DBoxSurface();
		bool			InitFonts();				// font���� �ʱ�ȭ

		// box surface�� ���� ����
// 		void			Set3DBoxColor(WORD pixel);

		//------------------------------------------------------
		// ȭ�鿡 ���̴� ImageObject ����
		//------------------------------------------------------
		void			DetermineImageObject();
		void			UpdateImageObject(const POINT &newFirstSector);

		//------------------------------------------------------
		// SurfaceLock
		//------------------------------------------------------
		//BOOL			SurfaceLock();
		//BOOL			SurfaceLockForEffect();
		//void			SurfaceLockRestore( BOOL bOldLock );

		//------------------------------------------------------
		// Draw �Լ���..
		//------------------------------------------------------
		void		DrawTileSurface();
		void		DrawZone(int X,int Y);
		void		DrawInformation();		
		void		DrawEventString(int &strX, int &strY);			// �̺�Ʈ �޴������� ��Ʈ������ ������ �κ��� ������ ȭ�鿡 ����ִ� �Լ�
		int			DrawChatString(POINT* pPoint, MCreature* pCreature, COLORREF color, BYTE flag=0);
		void		DrawItem(POINT* pPoint, MItem* pItem);
		void		DrawItemShadow(POINT* pPoint, MItem* pItem);
		void		DrawImageObject(POINT* pPoint, MImageObject* pImageObject);
		void		DrawAttachEffect(POINT* pPoint, ATTACHEFFECT_LIST::const_iterator iEffect, BYTE size, MCreature* pCreature, int type=0);
		void		DrawGroundEffect();
		void		DrawEffect(POINT* pPoint, MEffect* pEffect, bool bSeletable);
		void		DrawItemBroken(int x, int y);
		void		DrawPartyHP(POINT* pPoint, MCreature* pCreature);
// 		void		DrawBox3D(RECT* pRect, WORD pixel);			
		void		DrawFade();

		//------------------------------------------------------
		// Character Draw �Լ���... by sonee   2003.6
		//------------------------------------------------------
		void		DrawCreature(POINT* pPoint, MCreature* pCreature);		
		void		DrawCreatureShadow(POINT* pPoint, MCreature* pCreature);
		void		DrawCreatureName(MCreature* pCreature);
		void		DrawCreatureMyName();
		void		DrawCreatureHPModify(POINT *point, MCreature* pCreature);
		void		DrawUndergroundCreature(POINT *pPoint, MCreature *pCreature);

		void		DrawGuildMarkInSiegeWar(MCreature* pCreature, int YPos); // ��帶ũ ū������ �ѷ�����..��

	protected :		
		bool				m_bInit;

		//------------------------------------------------------
		// ��� ����� �Ǵ� Surface
		//------------------------------------------------------
		CSpriteSurface*		m_pSurface;
		//S_SURFACEINFO		m_SurfaceInfo;
	

		// SpriteSurfacePack
		//CSpriteSurfacePack	m_SpriteSurfacePack;	// �׸���		
		//CSpriteSurface**			m_ppSurface;			// SpriteSurfaces

		//------------------------------------------------------
		//
		//                   Frame
		//
		//------------------------------------------------------
	public :
		//------------------------------------------------------
		// FramePacks
		//------------------------------------------------------		
		CCreatureFramePack		m_CreatureFPK;			// Creature frames
		CCreatureFramePack		m_AddonFPK;				// Player addon frames
		CCreatureFramePack		m_OustersFPK;			// Ousters frames

		CCreatureFramePack		m_AdvancementSlayerManFPK;			// Creature frames
		CCreatureFramePack		m_AdvancementSlayerWomanFPK;			// Creature frames
		CCreatureFramePack		m_AdvancementVampireManFPK;				// Player addon frames
		CCreatureFramePack		m_AdvancementVampireWomanFPK;				// Player addon frames
		CCreatureFramePack		m_AdvancementOustersFPK;			// Ousters frames
		//add by viva 
		CCreatureFramePack		m_NewVampireFPK;
		CCreatureFramePack		m_NewSlayerManFPK;
		CCreatureFramePack		m_NewSlayerWomanFPK;
		//end

		CImageFramePack			m_ItemTileFPK;			// Tile�� �ִ� Item�� ����..
		CAnimationFramePack		m_ItemDropFPK;			// �ٴ����� �������� Item�� ����..
		CAnimationFramePack		m_ItemBrokenFPK;		// �μ����� Item�� ����..
		CAnimationFramePack		m_ImageObjectFPK;		// ImageObject�� ���� frames
		CAnimationFramePack		m_ImageObjectShadowFPK;		// ImageObject�� ���� frames
//		CAnimationFramePack		m_InteractionObjectFPK;		// ImageObject�� ���� frames
		CEffectFramePack		m_EffectAlphaFPK;		// Effect�� ���� frames
		CEffectFramePack		m_EffectNormalFPK;		// Effect�� ���� frames
		CEffectFramePack		m_EffectShadowFPK;		// Effect�� ���� frames
		CEffectFramePack		m_EffectScreenFPK;
		
		CCreatureFramePack		m_CreatureShadowFPK;			// Creature frames
		CCreatureFramePack		m_AddonShadowFPK;			// Player addon frames
		CCreatureFramePack		m_OustersShadowFPK;			// Ousters addon frames

		CCreatureFramePack		m_AdvancementSlayerManShadowFPK;			// Creature frames
		CCreatureFramePack		m_AdvancementSlayerWomanShadowFPK;			// Creature frames
		CCreatureFramePack		m_AdvancementVampireManShadowFPK;			// Player addon frames
		CCreatureFramePack		m_AdvancementVampireWomanShadowFPK;			// Player addon frames
		CCreatureFramePack		m_AdvancementOustersShadowFPK;			// Ousters addon frames

		//add by viva
		CCreatureFramePack		m_NewVampireShadowFPK;
		CCreatureFramePack		m_NewSlayerManShadowFPK;
		CCreatureFramePack		m_NewSlayerWomanShadowFPK;
		//end
		
		
		//------------------------------------------------------
		//
		//                   Sprite
		//
		//------------------------------------------------------
		//------------------------------------------------------
		// SpritePack
		//------------------------------------------------------		
		CSpritePack				m_TileSPK;				// Tile
		CSpritePack				m_ImageObjectSPK;		// ImageObject Sprite��
//		CSpritePack				m_InteractionObjectSPK;		// ImageObject Sprite��
		CIndexSpritePack		m_CreatureSPK;			// Creature Sprite��
		CIndexSpritePack		m_AddonSPK;		// Sprite��		
		CIndexSpritePack		m_OustersSPK;		// Sprite��		

		CIndexSpritePack		m_AdvancementSlayerManSPK;			// Creature Sprite��
		CIndexSpritePack		m_AdvancementSlayerWomanSPK;			// Creature Sprite��
		CIndexSpritePack		m_AdvancementVampireManSPK;		// Sprite��		
		CIndexSpritePack		m_AdvancementVampireWomanSPK;		// Sprite��		
		CIndexSpritePack		m_AdvancementOustersSPK;		// Sprite��	
		
		//add by viva
		CIndexSpritePack		m_NewVampireSPK;
		CIndexSpritePack		m_NewSlayerManSPK;
		CIndexSpritePack		m_NewSlayerWomanSPK;
		//end
		
		//CSpritePack				m_ItemTileSPK;			// Sprite��		
		CIndexSpritePack		m_ItemTileISPK;			// Sprite��		
		CIndexSpritePack		m_ItemDropISPK;			//
		CSpritePack				m_ItemBrokenSPK;		// �μ����� ������
		CSpritePack				m_ItemRealSPK;			// Sprite��				
		CAlphaSpritePalPack		m_EffectAlphaSPK;		// AlphaSprite��
		CSpritePalPack			m_EffectScreenSPK;		// ScreenEffect
		MPalettePack			m_EffectAlphaPPK;		// AlphaEffect
		MPalettePack			m_EffectScreenPPK;		// ScreenEffect
		CSpritePack				m_EffectNormalSPK;		// NormalSprite��
		CShadowSpritePack		m_EffectShadowSPK;		// ShadowSprite��
		CSpritePack				m_WeatherSPK;			// WeatherSprite��
		CSpritePack				m_GuildSPK;				// GuildMark

		

		CSpritePack				m_EtcSPK;				// ��Ÿ...
		CSpritePack				m_OustersFinSPK;				// ��Ÿ...
		CSpritePack				m_AdvacementQuestEnding;				// ��Ÿ...


		//------------------------------------------------------		
		// Shadow SpritePack
		//------------------------------------------------------
		CShadowSpritePack		m_AddonSSPK;			// Sprite��		
		CShadowSpritePack		m_CreatureSSPK;
		CShadowSpritePack		m_OustersSSPK;

		CShadowSpritePack		m_AdvancementSlayerManSSPK;			// Sprite��		
		CShadowSpritePack		m_AdvancementSlayerWomanSSPK;			// Sprite��		
		CShadowSpritePack		m_AdvancementVampireManSSPK;
		CShadowSpritePack		m_AdvancementVampireWomanSSPK;
		CShadowSpritePack		m_AdvancementOustersSSPK;
		//add by viva
		CShadowSpritePack		m_NewVampireSSPK;
		CShadowSpritePack		m_NewSlayerManSSPK;
		CShadowSpritePack		m_NewSlayerWomanSSPK;
		//end

		CShadowSpritePack		m_ImageObjectSSPK;
//		CShadowSpritePack		m_InteractionObjectSSPK;

		//CShadowSpritePack		m_CreatureSSPK;


	protected :

//		CSprite*				m_pMinimapSPR;
//		float					m_SectorToMinimapWidth;
//		float					m_SectorToMinimapHeight;
//		CSpriteSurface*			m_pMinimapTexture;
//		int						m_MinimapTextureWidth;
//		int						m_MinimapTextureHeight;


		//------------------------------------------------------
		//
		//                  Sprite Index
		//
		//------------------------------------------------------
		CFileIndexTable			m_TileSPKI;
		CFileIndexTable			m_ImageObjectSPKI;
//		CFileIndexTable			m_EffectAlphaSPKI;
//		CFileIndexTable			m_EffectScreenSPKI;

		
		//------------------------------------------------------
		// 
		//                  Sprite File
		//
		//------------------------------------------------------
//		class ifstream			m_TileSPKFile;
//		class ifstream			m_ImageObjectSPKFile;
//		class ifstream			m_EffectAlphaSPKFile;
//		class ifstream			m_EffectScreenSPKFile;
//		class ifstream			m_AddonSPKFile;
//		class ifstream			m_AddonSSPKFile;
//		class ifstream			m_CreatureSPKFile;
//		class ifstream			m_CreatureSSPKFile;

		//------------------------------------------------------
		//
		//                   Filter
		//
		//------------------------------------------------------
		//CFilterPack				m_Filter;
		CFilter					m_ImageObjectFilter;

		//------------------------------------------------------
		//
		//               Texture PartManager
		//
		//------------------------------------------------------
		// Texture PartManager
//		CSpriteTexturePartManager*	m_pScreenEffectTextureManager;
//		CNormalSpriteTexturePartManager*	m_pImageObjectTextureManager;
//		CTexturePartManager*		m_pAlphaEffectTextureManager;
//		CShadowPartManager*			m_pImageObjectShadowManager;
//		CShadowPartManager*			m_pAddonShadowManager;
//		CShadowPartManager*			m_pCreatureShadowManager;
//		CShadowPartManager*			m_pOustersShadowManager;
//		CShadowPartManager*			m_pEffectShadowManager;


		//------------------------------------------------------
		// Zone���� ���������� Load�� �͵鿡 ���� ����
		//------------------------------------------------------
		CSpriteFilePositionArray*	m_pTileSFPArrayLargeZone;
		CSpriteFilePositionArray*	m_pImageObjectSFPArrayLargeZone;
		CSpriteFilePositionArray*	m_pTileSFPArraySmallZone;
		CSpriteFilePositionArray*	m_pImageObjectSFPArraySmallZone;


		//------------------------------------------------------
		//
		//                Other Data members
		//
		//------------------------------------------------------

		//------------------------------------------------------
		// Zone
		//------------------------------------------------------
		MZone*				m_pZone;				// ���� ����Ϸ��� Zone

		static int			m_MiddleX;				// zone�� �߰�(pixel X ��ǥ)
		POINT				m_FirstSector;			// ȭ�� ���� ù ���� Zone������ ��ǥ(sector)
		POINT				m_PlusPoint;			// FirstSector�� pixel������ ��ǥ������
		POINT				m_FirstZonePixel;		// ȭ��(0,0)�� ��Ÿ���� Zone���� Pixel��ǥ

		//------------------------------------------------------
		// Mouse�� ���õ� ȭ�� ���� �͵�..
		//------------------------------------------------------
		POINT				m_SelectSector;		
		TYPE_OBJECTID		m_SelectCreatureID;
		TYPE_OBJECTID		m_SelectItemID;
//		TYPE_OBJECTID		m_SelectInteractionObjectID;
		TYPE_OBJECTID		m_SelectEffectID;
		//bool				m_bSelectModeAttack;

		WORD					m_SOMOutlineColor;
		CSpriteOutlineManager	m_SOM;	// ���õ� ���� �ܰ��� ���

		//------------------------------------------------------
		// �þ� ó��
		//------------------------------------------------------		
		POINT					m_FilterPosition;	// Player�� ������ �þ� ó��		
		BYTE					m_DarkBits;
		

		// �þ�ó�� ���� - ���� �ִ� �þߺκ�
		CFilterPack				m_LightFTP;
		CFilter					m_LightBufferFilter;
		CSpriteSurface*			m_pLightBufferTexture;
		int						m_nLight;


		//------------------------------------------------------
		// Fade In/Out ����
		//------------------------------------------------------		
		char				m_FadeValue;	// ���� fade��
		char				m_FadeEnd;		// �� ��
		char				m_FadeInc;		// ��ȭ��
		bool				m_bFade;		// fade ���ΰ�?
		WORD				m_FadeColor;	// fade ��
		WORD				m_delayFrame;	// ��ȭ���� �ٲ� ������ ���� ������
		
		//------------------------------------------------------
		// ���� ȭ���� Tile�� �����ؼ� ������ ����Ҷ� �̿��Ѵ�.
		//------------------------------------------------------
		CSpriteSurface*				m_pTileSurface;
		bool						m_bFirstTileDraw;
		int							m_TileSurfaceFirstZonePixelX, 
									m_TileSurfaceFirstZonePixelY;
		int							m_TileSurfaceFirstSectorX,
									m_TileSurfaceFirstSectorY;

		//------------------------------------------------------
		// ���� ȭ�鿡�� �����ϴ� ImageObject���� ����
		//------------------------------------------------------
		IMAGEOBJECT_OUTPUT_MAP				m_mapImageObject;

		//------------------------------------------------------
		// Creature OutputMap - ��� ������ ����ȴ�.
		//------------------------------------------------------
		CREATURE_OUTPUT_MAP					m_mapCreature;
		bool								m_bTileSearchForCreature;

		//------------------------------------------------------
		// Mouse�� ���õ� Creature�� ä���� ����ϱ� ���� ����
		//------------------------------------------------------
		POINT						m_pointChatString;
		MCreature*					m_pSelectedCreature;

		//------------------------------------------------------
		// Texture Surface
		//------------------------------------------------------
		// Effect
		//CTexturePack				m_EffectTPK;
		//CTexturePack				m_CreatureTPK;
		//CTexturePack				m_ShadowTPK;	// for test
	
		CD3DTextureEffect			m_TextureEffect;
		
		//------------------------------------------------------
		// ����� String�� ���..
		//------------------------------------------------------
		DRAWTEXT_PQ					m_pqDrawText;

		//------------------------------------------------------
		// ItemName ���
		//------------------------------------------------------
		bool						m_bDrawItemNameList;
		DRAWITEMNAME_LIST			m_listDrawItemName;

		//------------------------------------------------------
		// Request mode
		//------------------------------------------------------
		bool						m_bDrawRequest;

		//------------------------------------------------------
		// 3D ����..
		//------------------------------------------------------
//		CSpriteSurface*				m_p3DBoxSurface;
//		WORD						m_3DBoxCurrentPixel;

//		CSpriteSurface*				m_p3DBoxBlackSurface;
//		CSpriteSurface*				m_p3DBoxHPSurface;
		

		//------------------------------------------------------
		// �����..
		//------------------------------------------------------
		// interactionObject
//		WORD		m_ColorOutlineInteractionObject;

		// item
		COLORREF	m_ColorNameItem;
		COLORREF	m_ColorNameItemOption;
		WORD		m_ColorOutlineItem;

		// ������
		COLORREF	m_ColorNameVampire;
		COLORREF	m_ColorNameSlayer;
		COLORREF	m_ColorNameNPC;

		COLORREF	m_ColorNameAlignment[5];	// ����..

		// ���� ����?
		WORD		m_ColorOutlineNPC;
		WORD		m_ColorOutlineAttackPossible;
		WORD		m_ColorOutlineAttackImpossible;

		// hp bar�� ����
		WORD		m_ColorHPBar;

		// ������ ������
		WORD		m_ColorBlackHalf;


		//------------------------------------------------------
		// 2D light���� �� ���� �����ϴ� ȭ���� pixelũ��
		//------------------------------------------------------
		int*		m_p2DLightPixelWidth;
		int*		m_p2DLightPixelHeight;

		//------------------------------------------------------
		// Load�� �� ����
		//------------------------------------------------------
		INT_ORDERED_LIST	m_listLoadedCreatureSprite;
		INT_ORDERED_LIST	m_listLoadedMonsterSprite;
		
	public :
		// ��Light��ǥ�� ȭ�鿡���� ũ��
		static float				s_LightWidth;
		static float				s_LightHeight;
		
		// 2004, 8, 18 sobeit add start - ������ ���� Ÿ���ö����� �������� �߰�..
		enum GENERATE_OPTION{
			GENERATE_ALL = 0,
			GENERATE_EXCEPT_LEFT,	// ���� �ƿ������� ����
			GENERATE_EXCEPT_RIGHT,  // ������ �ƿ������� ����
			GENERATE_EXCEPT_SIDE,	// �� ���̵� �ƿ������� ����
			// -_- ��,�Ʒ��� ����� ���� �ϳ�..-_-;
		};
		// 2004, 8, 18 sobeit add start

	private :
		// -_- ����ó�� �Լ� �����ͷ� ��.
		//DrawCreatureExecptionProc*	m_pExceptionProc;
		void	InitMapingExceptionProc();
		void	RegistExceptionProcFunction( DWORD objectID, DrawCreatureExceptionProc proc );

		// DrawSelectedCharacter
		void	DrawSelectedVampireCreature( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame, int body, int frameindex );
		void	DrawSelectedSlayerCreature( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawSelectedOustersCreature( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );

		void	DrawSelectedAdvancementVampireCreature( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame, int body, int frameindex );
		void	DrawSelectedAdvancementSlayerCreature( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawSelectedAdvancementOustersCreature( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );

		// DrawEffect
		void	DrawInstallTurret( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame, int frameindex );
		void	DrawFadeOut( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawFastMove(POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawInvisible(POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawWeaponFadeOut(POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		
		void	DrawFadeOutForACSlayer( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawFastMoveForACSlayer(POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawInvisibleForACSlayer(POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawWeaponFadeOutForACSlayer(POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		
		// DrawDivineGuidance
		void	DrawDivineGuidanceSlayerCharacter( POINT *pPoint, MCreature* pCreature, int direction );
		void	DrawDivineGuidanceVampireCharacter( POINT *pPoint, MCreature* pCreature, int direction, int body );
		void	DrawDivineGuidanceOustersCharacter( POINT *pPoint, MCreature* pCreature, int direction );
		
		void	DrawDivineGuidanceAdvancementClassSlayerCharacter( POINT *pPoint, MCreature* pCreature, int direction );
		void	DrawDivineGuidanceAdvancementClassVampireCharacter( POINT *pPoint, MCreature* pCreature, int direction, int body );
		void	DrawDivineGuidanceAdvancementClassOustersCharacter( POINT *pPoint, MCreature* pCreature, int direction );
		
		// DrawNormalCharacter
		void	DrawSlayerCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame, int FrameIndex );		
		void	DrawVampireCharacter( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame, int body, int frameindex );
		void	DrawOustersCharacter( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame );
		
		void	DrawShadowSlayerCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawShadowVampireCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame, int body, bool bBlendingShadow , bool bSlayerPet_ShowTurret );
		void	DrawShadowOustersCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame );

		// DrawAdvancementClassCharacter
		void	DrawAdvancementClassSlayerCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame, int FrameIndex );
		void	DrawAdvancementClassOustersCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawAdvancementClassVampireCharacter( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame, int body, int frameindex );

		void	DrawShadowAdvancementClassSlayerCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame );
		void	DrawShadowAdvancementClassVampireCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame, int body, bool bBlendingShadow , bool bSlayerPet_ShowTurret );
		void	DrawShadowAdvancementClassOustersCharacter( POINT *pPoint, MCreature* pCreature, int action, int direction, int frame );

		// 2004, 12, 11, sobeit add start
		void	DrawCentauroTurret( POINT* pPoint, MCreature* pCreature, int action, int direction, int frame , int body);
		// 2004, 12, 11, sobeit add end
		
		// 2005, 1, 20, sobeit add start
		bool	DrawEvent();
		bool	ExcuteOustersFinEvent();
		bool	ExcuteAdvancementQuestEnding(void *pVoid);
		// 2005, 1, 20, sobeit add end
		
		std::map< DWORD, DrawCreatureExceptionProc >	m_ExceptionProcMap;
};

extern MTopView*	g_pTopView;

#endif
