//----------------------------------------------------------------------
// MZone.h
//----------------------------------------------------------------------
//
// Creature : ID�� �����ȴ�. ���� �����δ�. - -;;
// Item     : ID�� �����ȴ�. ������ٰ�(creature�� pickup) ����⵵ �Ѵ�(drop)
// Obstacle : Sector�� �����ȴ�. �������� �ʴ´�.
// ImageObject : ??
//
//----------------------------------------------------------------------
// File�� ����� ����
//----------------------------------------------------------------------
//
// [ MapData : Filename.MD ]   - Zone���� Load�Ѵ�.
//   ���� size, ���� size
//   Zone ID
//   �Ӽ�
//   ����size * ����size ���� Sector����(TileSpriteID, Flag)
//   Obstacle��, Obstacle�� * Obstacle ����
//   ImageObject��, ImageObject�� * (ImageObject, ImageObjectSectorInfo)
//
//
//----------------------------------------------------------------------
// On-line Update
//----------------------------------------------------------------------
//
// File�� �ϳ��� �����ϰ� �Ǹ�, 
// File�� �߰��� data�� �߰��� �� �����Ƿ� File��ü�� Load�ߴٰ�
// Memory���� Update�ϰ� File��ü�� Save�ؾ��Ѵ�.
// (!)�ӵ� ������ ���� �� �ִ�.
//
// �׷��ٰ�, ������ Data�κе��� ���� file�� �θ� �������ϴ�. - -;
// Zone �ϳ��� �����Ǿ��� ��, �� �̻� data�� �ٲ��� �ʴ´ٰ� �ϸ�..
// �ϳ��� File�� ����ص� ������ ���� ���̴�.
//
//----------------------------------------------------------------------

#ifndef	__MZONE_H__
#define	__MZONE_H__

#pragma warning(disable:4786)

#include <Windows.h>
#include <list>
#include <map>
#include <vector>
#include "MTypeDef.h"
class ofstream;
class ifstream;
#include "MSector.h"
class MObstacle;
class MItem;
class MCreature;
class MEffect;
class MPlayer;
class MImageObject;
class CSpriteSetManager;
#include "MHelicopterManager.h"
#include "CPositionList.h"
#include "ZoneFileHeader.h"
#include "SoundNode.h"

struct UI_PORTAL_FLAG
{
	int zone_id, x, y, portal_x, portal_y;
};
typedef std::list<UI_PORTAL_FLAG> UI_PORTAL_LIST;
typedef std::vector<UI_PORTAL_LIST> UI_PORTAL_VECTOR;

//----------------------------------------------------------------------
//
// Zone class�� Sector�� 2���� �迭�̴�.
//
//----------------------------------------------------------------------
class MZone {
	//--------------------------------------------------------------		
	// typedef
	//--------------------------------------------------------------	
	public :
		// building map
		typedef std::map<TYPE_OBJECTID, MImageObject*>				IMAGEOBJECT_MAP;

		// IMAGEOBJECT_POSITION_LIST�� �����Ѵ�.
		typedef	CPositionList<TYPE_SECTORPOSITION>							IMAGEOBJECT_POSITION_LIST;

		// IMAGEOBJECT_POSITION_LIST�� map�̴�.
		typedef	std::map<TYPE_OBJECTID, IMAGEOBJECT_POSITION_LIST*>	IMAGEOBJECT_POSITION_LIST_MAP;


		// creature map
		typedef std::map<TYPE_OBJECTID, MCreature*>		CREATURE_MAP;

		// Item map	
		typedef std::map<TYPE_OBJECTID, MItem*>			ITEM_MAP;

		// Obstacle list
		//typedef std::list<MObstacle*>					OBSTACLE_LIST;

		// Effect list
		typedef std::map<TYPE_OBJECTID, MEffect*>		EFFECT_MAP;

		// Sound list
		typedef std::list<SOUND_NODE*>					SOUND_NODE_LIST;

		// 2004, 8, 31, sobeit add start - WaitEffectList
		// Wiait Effect list
		typedef std::list<MEffect*>						WAIT_EFFECT_LIST;
		// 2004, 8, 31, sobeit add end - WaitEffectList
	public :
		MZone(TYPE_SECTORPOSITION width=0, TYPE_SECTORPOSITION height=0);
		~MZone();

		//--------------------------------------------------------------		
		// init / release
		//--------------------------------------------------------------		
		void		Init(TYPE_SECTORPOSITION width, TYPE_SECTORPOSITION height);
		void		Release();
		
		//--------------------------------------------------------------
		// Update
		//--------------------------------------------------------------
		void		Update();

		//--------------------------------------------------------------
		// Release Object
		//--------------------------------------------------------------
		void		ReleaseObject();


		//--------------------------------------------------------------
		// file I/O
		//--------------------------------------------------------------		
		bool		LoadFromFile(class ifstream& file);

		bool		SaveToFileSectorSound(class ofstream& file);
		bool		LoadFromFileSectorSound(class ifstream& file);

		//--------------------------------------------------------------		
		// Zone File Header �κ�
		//--------------------------------------------------------------		
		const MString&	GetVersion() const			{ return m_Info.ZoneVersion; } // ���� ������Ʈ�� ��¥
		WORD			GetID() const				{ return m_Info.ZoneID; }			//	�� ���̵�
		WORD			GetGroupID() const			{ return m_Info.ZoneGroupID; }	//	�� �׷� ���̵�
		const MString&	GetName() const				{ return m_Info.ZoneName; }		// �� �̸�
		BYTE			GetType() const				{ return m_Info.ZoneType; }		//	���� Ÿ��
		BYTE			GetLevel() const			{ return m_Info.ZoneLevel; }		//	���� ������ ������ ����. 1-10 ����.
		const MString&	GetDescription() const		{ return m_Info.Description; }	//	��	



		//--------------------------------------------------------------
		//
		// Creature
		//
		//--------------------------------------------------------------
		void		SetPlayer();//MPlayer* pPlayer);
		void		RemovePlayer();
		
		// Creature Map : Zone�� �����ϴ� ��ü creature ��
		int			GetCreatureNumber() const		{ return m_mapCreature.size(); }
		CREATURE_MAP::const_iterator GetCreatureBegin()		{ return m_mapCreature.begin(); }

		// Move
		void		UpdateAllCreature();

		// player�� �þ߸� ����� Object���� �����Ѵ�.
		void		KeepObjectInSight(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y, BYTE sight);

		// (x,y) sector�� �� �� �ִ°�?
		bool		CanMove(BYTE creatureType, TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);
		void		SetServerBlock(BYTE creatureType, TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);
		void		UnSetServerBlock(BYTE creatureType, TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);

		// (xo,yo)�� �ִ� Creature�� (xn,yn)���� �ű��.		
		bool		MoveGroundCreature(MCreature* pCreature, TYPE_SECTORPOSITION xo, TYPE_SECTORPOSITION yo, TYPE_SECTORPOSITION xn, TYPE_SECTORPOSITION yn);
		bool		MoveFlyingCreature(MCreature* pCreature, TYPE_SECTORPOSITION xo, TYPE_SECTORPOSITION yo, TYPE_SECTORPOSITION xn, TYPE_SECTORPOSITION yn);
		bool		MoveUndergroundCreature(MCreature* pCreature, TYPE_SECTORPOSITION xo, TYPE_SECTORPOSITION yo, TYPE_SECTORPOSITION xn, TYPE_SECTORPOSITION yn);

		// (x,y) Sector�� �ִ� Creature�� ID�� �Ѱ��ش�.
		
		TYPE_OBJECTID		GetCreatureID(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);
		TYPE_OBJECTID		GetFlyingCreatureID(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);
		TYPE_OBJECTID		GetUndergroundCreatureID(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);

		TYPE_OBJECTID		GetCreatureID(const char* pName, int flag = 0) const;

		// other creatures : Add, Get, Remove
		bool		AddCreature(MCreature* pCreature);	// Zone�� Creature �߰�
		bool		RemoveCreature(TYPE_OBJECTID	id);			// Zone���� Creature ����
		MCreature*	GetCreature(TYPE_OBJECTID id);				// Zone�� Creature �о����
		MCreature*	GetCreatureOnly(TYPE_OBJECTID id);

		// 2004, 8, 12 sobeit add start
		MCreature*  GetCreatureBySector(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);
		// 2004, 8, 12 sobeit add end
		//MCreature*	GetUndergroundCreature(TYPE_OBJECTID id);				// Zone�� UndergroundCreature �о����
		//MCreature*	GetFlyingCreature(TYPE_OBJECTID id);				// Zone�� FlyingCreature �о����

		// Sector���� Creature ����
		void		RemoveUndergroundCreature(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, TYPE_OBJECTID id)	{ m_ppSector[sY][sX].RemoveUndergroundCreature(id); }
		void		RemoveGroundCreature(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, TYPE_OBJECTID id)		{ m_ppSector[sY][sX].RemoveGroundCreature(id); }
		void		RemoveFlyingCreature(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, TYPE_OBJECTID id)		{ m_ppSector[sY][sX].RemoveFlyingCreature(id); }

		// Hallu����
		void		ChangeToHalluCreature();
		void		RemoveHalluCreature();


		//--------------------------------------------------------------
		//
		//							Item
		//
		//--------------------------------------------------------------
		bool		AddItem(MItem* pItem, BOOL bDropping=false);				// Zone�� Item �߰�, bDropping�� �������� �����ϴ°��ΰ�?�� ��Ÿ��..
		bool		RemoveItem(TYPE_OBJECTID	id);	// Zone���� Item ����(delete����)
		bool		PickupItem(TYPE_OBJECTID	id);	// Zone���� Item ����
		MItem*		GetItem(TYPE_OBJECTID id);			// Zone�� Item �о����
		MItem*		GetCorpseKilledByMe(int limitItemCount = 0);				// Zone���� ���� ���� ���� �ϳ� �Ѱ��ش�.
		
		// (x,y) Sector�� �ִ� Item�� ID�� �Ѱ��ش�.
		TYPE_OBJECTID		GetItemID(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);	

		// Creature�� ��ü�� ���ϴ� ��... - -;
		//bool		AddCorpseFromCreature(MCreature* pCreature);
		bool		AddCorpseFromCreature(TYPE_OBJECTID id);

		// Item Map : Zone�� �����ϴ� ��ü Item ��
		int			GetItemNumber() const		{ return m_mapItem.size(); }
		ITEM_MAP::const_iterator GetItemBegin()		{ return m_mapItem.begin(); }

		// update item
		void		UpdateItem();


		//--------------------------------------------------------------
		//
		//							ImageObject
		//
		//--------------------------------------------------------------
		bool		AddImageObject(MImageObject* pImageObject);	// Zone�� ImageObject �߰�
		bool		RemoveImageObject(TYPE_OBJECTID	id);			// Zone���� ImageObject ����
		MImageObject*	GetImageObject(TYPE_OBJECTID id);				// Zone�� ImageObject �о����
		void		SetImageObjectSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, TYPE_OBJECTID id);	// ImageObject Sector
		void		UnSetImageObjectSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, TYPE_OBJECTID id);	// Unset ImageObject Sector	

		//--------------------------------------------------------------
		//
		//							Obstacle
		//
		//--------------------------------------------------------------
		//bool		AddObstacle(MObstacle* pObstacle);	// Zone�� Obstacle �߰�
		//bool		RemoveObstacle(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);	// Zone���� Obstacle ����
		//void		ChangeFrameObstacle();				// Frame��ȭ (�ӽ��Լ�!!!)

		//--------------------------------------------------------------
		//
		//							 Effect
		//
		//--------------------------------------------------------------
		bool		AddEffect(MEffect* pEffect, DWORD dwWaitCount = 0);	// Zone�� Effect �߰�	
		bool		RemoveEffect(TYPE_OBJECTID id);
		void		UpdateEffects();				// Frame��ȭ (�ӽ��Լ�!!!)
		// 2004, 8, 31, sobeit add start
		void		UpdateWaitEffects();
		// 2004, 8, 31, sobeit add end
		MEffect*	GetEffect(TYPE_OBJECTID id) const;
		int			GetEffectCount()				{ return m_mapEffect.size(); }
		EFFECT_MAP::const_iterator GetEffects()		{ return m_mapEffect.begin(); }
		bool		RemoveTileEffect(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, int effectStatus, int serverID=0);
		bool		RemoveTileEffect(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, TYPE_EFFECTSPRITETYPE type, int serverID=0);
		void		ChangeSwapViceType(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, TYPE_EFFECTSPRITETYPE type, WORD wDelay = 0xffff);
		void		RemoveSwapViceType();
		//--------------------------------------------------------------
		//						Ground Effect - Tile�� ����..
		//--------------------------------------------------------------
		bool		AddGroundEffect(MEffect* pEffect);	// Zone�� Effect �߰�	
		bool		RemoveGroundEffect(TYPE_OBJECTID id);
		MEffect*	GetGroundEffect(TYPE_OBJECTID id) const;
		void		UpdateGroundEffects();				// Frame��ȭ (�ӽ��Լ�!!!)
		int			GetGroundEffectCount()				{ return m_mapGroundEffect.size(); }
		EFFECT_MAP::const_iterator GetGroundEffects()	{ return m_mapGroundEffect.begin(); }
		EFFECT_MAP::const_iterator GetGroundEffectsEnd()	{ return m_mapGroundEffect.end(); }

		//--------------------------------------------------------------
		//
		//						 Item
		//
		//--------------------------------------------------------------
		void		AddSound(SOUND_NODE* pNode);	// �Ҹ� �߰�
		void		UpdateSound();					// �Ҹ� ���


		//--------------------------------------------------------------
		//
		//							Sector
		//
		//--------------------------------------------------------------		
		bool		IsPositionInZone(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y)	{ return x<m_Width && y<m_Height; }

		void		SetSector(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y, const MSector& sector)	{ m_ppSector[y][x]=sector; }

		void		SetBlockAllSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)				{ m_ppSector[sY][sX].SetBlockAll(); }		// All Block sector�� �����.
		void		UnSetBlockAllSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)			{ m_ppSector[sY][sX].UnSetBlockAll(); }	// All Block sector�� �����.

		void		SetBlockUndergroundSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)		{ m_ppSector[sY][sX].SetBlockUnderground(); }		// UndergroundBlock sector ����
		void		UnSetBlockUndergroundSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)	{ m_ppSector[sY][sX].UnSetBlockUnderground(); }	// UndergroundBlock sector ����

		void		SetBlockGroundSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)			{ m_ppSector[sY][sX].SetBlockGround(); }	// Ground Block sector ����
		void		UnSetBlockGroundSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)		{ m_ppSector[sY][sX].UnSetBlockGround(); }	// Ground Block sector ����

		void		SetBlockFlyingSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)	{ m_ppSector[sY][sX].SetBlockFlying(); }					// Flying Block sector�� �����.
		void		UnSetBlockFlyingSector(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)	{ m_ppSector[sY][sX].UnSetBlockFlying(); }			// Flying Block sector�� �����.

		void		SetVisitedFlag(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)				{ m_ppSector[sY][sX].SetVisitedFlag(); }
		void		UnSetVisitedFlag(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)			{ m_ppSector[sY][sX].UnSetVisitedFlag(); }
		const bool	IsVisitedFlag(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY) const		{ return m_ppSector[sY][sX].IsVisitedFlag(); }
		
		//--------------------------------------------------------------		
		//
		//		get
		//
		//--------------------------------------------------------------		
		TYPE_SECTORPOSITION			GetWidth() const				{ return m_Width; }
		TYPE_SECTORPOSITION			GetHeight()	const				{ return m_Height; }
		const MSector&	GetSector(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y) const	{ return m_ppSector[y][x]; }
		//const MPlayer&	GetPlayer()	const				{ return *m_pPlayer; }
	
		long						GetTileFilePosition() const			{ return m_fpTile; }
		long						GetImageObjectFilePosition() const	{ return m_fpImageObject; }

		//--------------------------------------------------------------
		// Tile SpriteID ���
		//--------------------------------------------------------------
		void						GetNearSpriteSet(CSpriteSetManager& TileSSM, CSpriteSetManager& ImageObjectSSM, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY) const;


		//--------------------------------------------------------------		
		//
		// portal
		//
		//--------------------------------------------------------------		
		void						AddPortal(int type, int zoneID, const RECT& rect);

		//--------------------------------------------------------------		
		//
		// Safe
		//
		//--------------------------------------------------------------		
		void						SetSafeSector( const RECT& safeRect, BYTE fSafe );


		//--------------------------------------------------------------
		//
		// Fake Creature
		//
		//--------------------------------------------------------------
		// Creature Map : Zone�� �����ϴ� ��ü creature ��
		int			GetFakeCreatureNumber() const		{ return m_mapFakeCreature.size(); }
		CREATURE_MAP::const_iterator GetFakeCreatureBegin()		{ return m_mapFakeCreature.begin(); }

		// Move
		void		UpdateFakeCreature();

		// other creatures : Add, Get, Remove
		bool		AddFakeCreature(MCreature* pCreature);	// Zone�� Creature �߰�
		bool		RemoveFakeCreature(TYPE_OBJECTID id);			// Zone���� Creature ����
		MCreature*	GetFakeCreature(TYPE_OBJECTID id);				// Zone�� Creature �о����		
	
		//--------------------------------------------------------------
		// ZoneSound
		//--------------------------------------------------------------
		bool		IsZoneSoundLoaded() const		{ return m_bZoneSoundLoaded; }

		//--------------------------------------------------------------
		// HelicopterManager
		//--------------------------------------------------------------
		bool			AddHelicopter(TYPE_OBJECTID creatureID, int x0, int y0);
		MHelicopter*	GetHelicopter(TYPE_OBJECTID creatureID) const;
		void			RemoveHelicopter(TYPE_OBJECTID creatureID);
		UI_PORTAL_VECTOR &	GetHorn() { return m_horn; }
		
		void			SetCurrentZoneID( WORD id ) { m_Info.ZoneID = id; }			// �ƾƾ� �� map �� zoneid �� ����ִ°ž�!!

		BYTE			GetPKType();

		
	protected :
		// Zone File Header
		FILEINFO_ZONE_HEADER	m_Info;

		TYPE_SECTORPOSITION					m_Width;		// Zone�� ���� ũ��
		TYPE_SECTORPOSITION					m_Height;		// Zone�� ���� ũ��
		MSector**				m_ppSector;		// ������ Sector

		// Other Creature
		CREATURE_MAP			m_mapCreature;	// other creatures	

		// Other Creature
		ITEM_MAP				m_mapItem;		// Item map

		// ImageObjects
		IMAGEOBJECT_MAP			m_mapImageObject;	// ImageObject map

		// Obstacle
		//OBSTACLE_LIST			m_listObstacle;	// Obstacle List

		// Effects
		EFFECT_MAP				m_mapEffect;	// Effect map

		// Effects
		EFFECT_MAP				m_mapGroundEffect;	// Effect map

		// Zone�� �ʿ��� �׸� ������ ���� File Position
		long					m_fpTile;
		long					m_fpImageObject;

		SOUND_NODE_LIST			m_listSoundNode;

		// client������ ���ư��� ���񽺿� creature - -;;
		CREATURE_MAP			m_mapFakeCreature;

		// sound�� load�Ǿ���.. ����..
		bool					m_bZoneSoundLoaded;

		MHelicopterManager		m_HelicopterManager;
		UI_PORTAL_VECTOR		m_horn;
		
		// 2004, 8, 31, sobeit add start
		WAIT_EFFECT_LIST		m_listWaitEffect;
		// 2004, 8, 31, sobeit add end
};

// Zone
extern MZone*						g_pZone;

#endif


