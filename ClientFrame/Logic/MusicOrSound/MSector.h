//----------------------------------------------------------------------
// MSector.h
//----------------------------------------------------------------------
//
// - Object Map�� ����Ѵ�.
//
// - Effect�� Object�̱� ������, ������..
//   Effect�� List�� ���� �����ϴ°� ����..
//
//----------------------------------------------------------------------
// Flag�� �̿��ؼ� Sector�� ���� �����ϴ� Object���� ������ �����صθ�,
// �ӵ��� ���� ���̴�!
//----------------------------------------------------------------------
// �� Sector���� �������� ImageObject�� ������ �� �ִ�.
// ��, Map�� ������.. ���� ����ÿ� �߰��� ���� ������ �Ǹ� �ȵȴ�.
// 
// 
// list���ٴ� map�� ���� ������??
//
// Ư�� key���� ���ؼ� map�� �߰�/������ �����ϴ�.
//----------------------------------------------------------------------
//
// Map���� ���� Key���� ������ ���� �����Ѵ�.
//
//	1			POSITION_ITEM = 1,					// Item�� �ִ� Node
//	2			POSITION_UNDERGROUNDCREATURE,		// ���� ĳ���Ͱ� �ִ� Node
//	3			POSITION_GROUNDCREATURE,			// ���� ĳ���Ͱ� �ִ� Node
//	4			POSITION_FLYINGCREATURE,			// ���� ĳ���Ͱ� �ִ� Node
//	5			POSITION_PORTAL,					// Zone �̵��� �Ǵ� ���̴�.
//	100 ~255	POSITION_IMAGEOBJECT				// ImageObject���� �ִ� ��
//
//
//----------------------------------------------------------------------
// 
// [�þ�ó���� ���õ� ��]
//
// m_Light�� �� Sector�� ǥ���Ǵ� ���� ��⸦ �ǹ��Ѵ�.
// m_Light�� 0�̸� m_FilterSpriteID�� �̿��ؼ� Fog�� ǥ���ؾ��Ѵ�.
// m_Light�� 1 �̻��϶��� Fog�� ����� �Ѵ�.
//
// m_Light�� �ܼ��� true/false�� �ƴ� ������..
// �� Sector���� �������� ���� ���ÿ� ������ �� �����Ƿ� 
// ��ø�ƴٰ� ������ ��.. ������ �����ϰ� �Ǹ�.. 
// ���� ���� �����ϴµ��� 0�� �� ���� �ֱ� �����̴�.
// 
// ��) [�߰�]������ �繰 + Player�þ� + ����Effect  = 3���� ��
//     1. ������ �繰 ���� = 2���� ��
//     2. ����Effect ���� = 1���� ��
//     3. Player�þ� ���� = 0���� ��
//     4. �������ʹ� FilterSpriteID�� ����ؼ� Fog�� ����ؾ� �Ѵ�.
//
//
// = Sector�� MTopView�� creature�� light���� �κ��� BYTE���� short�� ���ľ��ұ�?
//   - �� Sector�� �ʹ� ���� ���� �������� �Ǹ� ������ �����.
//
//----------------------------------------------------------------------


#ifndef	__MSECTOR_H__
#define	__MSECTOR_H__

#pragma warning(disable:4786)

class ofstream;
class ifstream;
#include "DrawTypeDef.h"
#include "MTypeDef.h"
#include "MObject.h"
#include "SectorSoundInfo.h"

class MItem;
class MCreature;
class MImageObject;
class MEffect;

//----------------------------------------------------------------------
// Flag
//----------------------------------------------------------------------
#define	FLAG_SECTOR_BLOCK_UNDERGROUND		0x01	// ���Ϸ� ������ �� ���� Sector�ΰ�?
#define	FLAG_SECTOR_BLOCK_GROUND			0x02	// �������� ������ �� ���� Sector�ΰ�?
#define	FLAG_SECTOR_BLOCK_FLYING			0x04	// �������� ������ �� ���� Sector�ΰ�?
#define	FLAG_SECTOR_BLOCK_ALL				0x07	// Block ALL
#define	FLAG_SECTOR_ITEM					0x08	// Item�� �����Ѵ�.
#define	FLAG_SECTOR_UNDERGROUNDCREATURE		0x10	// ���� ĳ���Ͱ� �����Ѵ�.
#define	FLAG_SECTOR_GROUNDCREATURE			0x20	// ���� ĳ���Ͱ� �����Ѵ�.
#define	FLAG_SECTOR_FLYINGCREATURE			0x40	// ���� ĳ���Ͱ� �����Ѵ�.
#define	FLAG_SECTOR_PORTAL					0x80	// Zone �̵��� �Ǵ� ���̴�.

//----------------------------------------------------------------------
// Flag2
//----------------------------------------------------------------------
#define	FLAG_SECTOR_SAFE_COMMON				0x01	// ���� �� ������ ��
#define	FLAG_SECTOR_SAFE_SLAYER				0x02	// slayer�� ������ ��
#define	FLAG_SECTOR_SAFE_VAMPIRE			0x04	// vampire�� ������ ��
#define FLAG_SECTOR_SAFE_NO_PK_ZONE			0x08	// �� ������ 
#define	FLAG_SECTOR_SAFE_OUSTERS			0x10	// ousters�� ������ ��
#define FLAG_SECTOR_SAFE_ZONE				0x17
// server�� block�� ��
#define FLAG_SECTOR_BLOCK_SERVER_UNDERGROUND	0x10
#define FLAG_SECTOR_BLOCK_SERVER_GROUND			0x20
#define FLAG_SECTOR_BLOCK_SERVER_FLYING			0x40


// MObject Map
typedef std::map<BYTE, MObject*>		OBJECT_MAP;

// MEffect List
typedef std::list<MEffect*>		EFFECT_LIST;


//----------------------------------------------------------------------
// PORTAL_INFO
//----------------------------------------------------------------------
class PORTAL_INFO
{
	// type�� MPortal�� Type�� ����Ѵ�.
	public :
		int		Type;
		int		ZoneID;	

	public :
		PORTAL_INFO(int type, int zoneID)
		{
			Type = type;
			ZoneID = zoneID;
		}

	public :
		void		operator = (PORTAL_INFO& info)
		{
			Type = info.Type;
			ZoneID = info.ZoneID;
		}
};

// ZoneID List
typedef std::list<PORTAL_INFO>			PORTAL_LIST;

//----------------------------------------------------------------------
// 
// MSector class�� �ϳ��� Object�� ������ �� �ִ�
//                 �� ������ ���� ������ ������ �ִ´�.
//                 Sector�� �ϳ��� �ٴ� Ÿ�Ϸμ� ǥ���ȴ�.
//
//----------------------------------------------------------------------
class MSector {
	public :
		MSector(TYPE_SPRITEID spriteID=0);
		~MSector();


		//------------------------------------------------
		//
		// file I/O
		//
		//------------------------------------------------
		void	SaveToFile(class ofstream& file);
		void	LoadFromFile(class ifstream& file);

		//------------------------------------------------
		//
		// set SpriteID
		//
		//------------------------------------------------
		void				Set(TYPE_SPRITEID spriteID, BYTE fObject=0);
		// get Sprite Info.
		TYPE_SPRITEID		GetSpriteID() const	{ return m_bDisableTileImage?SPRITEID_NULL:m_SpriteID; }

		bool				IsEmpty() const		{ return m_fProperty==0; }

		//------------------------------------------------
		//
		// Block
		//
		//------------------------------------------------
		BYTE	IsBlockAny() const { return (m_fProperty & FLAG_SECTOR_BLOCK_GROUND) ||
											(m_fProperty & FLAG_SECTOR_BLOCK_UNDERGROUND) ||
											(m_fProperty & FLAG_SECTOR_BLOCK_FLYING); }
		// all
		BYTE	IsBlockAll() const	{ return m_fProperty & FLAG_SECTOR_BLOCK_ALL; }
		void	SetBlockAll()		{ m_fProperty |= FLAG_SECTOR_BLOCK_ALL; }
		void	UnSetBlockAll()		{ m_fProperty &= ~FLAG_SECTOR_BLOCK_ALL; }

		// underground
		BYTE	IsBlockUnderground() const	{ return m_fProperty & FLAG_SECTOR_BLOCK_UNDERGROUND; }
		void	SetBlockUnderground()		{ m_fProperty |= FLAG_SECTOR_BLOCK_UNDERGROUND; }
		void	UnSetBlockUnderground()		{ m_fProperty &= ~FLAG_SECTOR_BLOCK_UNDERGROUND; }

		// ground
		BYTE	IsBlockGround() const		{ return m_fProperty & FLAG_SECTOR_BLOCK_GROUND; }
		void	SetBlockGround()			{ m_fProperty |= FLAG_SECTOR_BLOCK_GROUND; }
		void	UnSetBlockGround()			{ m_fProperty &= ~FLAG_SECTOR_BLOCK_GROUND; }

		// flying
		BYTE	IsBlockFlying() const		{ return m_fProperty & FLAG_SECTOR_BLOCK_FLYING; }
		void	SetBlockFlying()			{ m_fProperty |= FLAG_SECTOR_BLOCK_FLYING; }
		void	UnSetBlockFlying()			{ m_fProperty &= ~FLAG_SECTOR_BLOCK_FLYING; }

		// server block underground
		BYTE	IsBlockServerUnderground() const	{ return m_fProperty2 & FLAG_SECTOR_BLOCK_SERVER_UNDERGROUND; }
		void	SetBlockServerUnderground()			{ m_fProperty2 |= FLAG_SECTOR_BLOCK_SERVER_UNDERGROUND; }
		void	UnSetBlockServerUnderground()		{ m_fProperty2 &= ~FLAG_SECTOR_BLOCK_SERVER_UNDERGROUND; }

		// server block Ground
		BYTE	IsBlockServerGround() const	{ return m_fProperty2 & FLAG_SECTOR_BLOCK_SERVER_GROUND; }
		void	SetBlockServerGround()			{ m_fProperty2 |= FLAG_SECTOR_BLOCK_SERVER_GROUND; }
		void	UnSetBlockServerGround()		{ m_fProperty2 &= ~FLAG_SECTOR_BLOCK_SERVER_GROUND; }

		// server block Flying
		BYTE	IsBlockServerFlying() const	{ return m_fProperty2 & FLAG_SECTOR_BLOCK_SERVER_FLYING; }
		void	SetBlockServerFlying()			{ m_fProperty2 |= FLAG_SECTOR_BLOCK_SERVER_FLYING; }
		void	UnSetBlockServerFlying()		{ m_fProperty2 &= ~FLAG_SECTOR_BLOCK_SERVER_FLYING; }

		
		//------------------------------------------------
		//
		// Sector�� Object�� �����ϴ°�?
		//
		//------------------------------------------------
		BYTE	IsExistObject() const	{ return !m_mapObject.empty(); }
		BYTE	IsObjectEmpty() const	{ return m_mapObject.empty(); }

		BYTE	IsExistItem() const					{ return m_fProperty & FLAG_SECTOR_ITEM; }
		BYTE	IsExistUndergroundCreature() const	{ return m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE; }
		BYTE	IsExistGroundCreature() const		{ return m_fProperty & FLAG_SECTOR_GROUNDCREATURE; }
		BYTE	IsExistFlyingCreature() const		{ return m_fProperty & FLAG_SECTOR_FLYINGCREATURE; }		
		BYTE	IsExistImageObject() const			{ return m_nImageObject; }		
		BYTE	IsExistAnyCreature() const			{ return (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE) ||
																(m_fProperty & FLAG_SECTOR_GROUNDCREATURE) ||
																(m_fProperty & FLAG_SECTOR_FLYINGCREATURE); }

		// ImageObject�� ���̱�� �ϴ� ���ε� Block�� �ƴ� ���ΰ�? (������ ó��)
		//BYTE	IsImageObjectAndNotBlock()	const	{ return (m_nImageObject && (m_fProperty & FLAG_SECTOR_BLOCK)); }
		

		//------------------------------------------------
		//
		// Add Object to Sector
		//
		//------------------------------------------------		
		bool	AddItem(const MItem* pItem);
		bool	AddUndergroundCreature(const MCreature* pCreature);
		bool	AddGroundCreature(const MCreature* pCreature);
		bool	AddFlyingCreature(const MCreature* pCreature);
		bool	AddImageObject(const MImageObject* pImageObject);


		//------------------------------------------------
		//
		// Remove Object from Sector
		//
		//------------------------------------------------				
		bool	RemoveItem(MItem*& pItem);
		//bool	RemoveUndergroundCreature(MCreature*& pCreature);
		//bool	RemoveGroundCreature(MCreature*& pCreature);
		//bool	RemoveFlyingCreature(MCreature*& pCreature);		

		// ID check and remove		
		bool	RemoveItem(TYPE_OBJECTID id, MItem*& pItem);
		bool	RemoveUndergroundCreature(TYPE_OBJECTID id, MCreature*& pCreature);
		bool	RemoveGroundCreature(TYPE_OBJECTID id, MCreature*& pCreature);
		bool	RemoveFlyingCreature(TYPE_OBJECTID id, MCreature*& pCreature);
		bool	RemoveImageObject(TYPE_OBJECTID id, MImageObject*& pImageObject);		
		bool	RemoveCreature(TYPE_OBJECTID id, MCreature*& pCreature);

		// ID check and just remove		
		bool	RemoveItem(TYPE_OBJECTID id);
		bool	RemoveUndergroundCreature(TYPE_OBJECTID id);
		bool	RemoveGroundCreature(TYPE_OBJECTID id);
		bool	RemoveFlyingCreature(TYPE_OBJECTID id);
		bool	RemoveCreature(TYPE_OBJECTID id);
		bool	RemoveImageObject(TYPE_OBJECTID id);		

		// just remove		
		bool	RemoveItem();
		//bool	RemoveUndergroundCreature();
		//bool	RemoveGroundCreature();
		//bool	RemoveFlyingCreature();		

		// remove all
		void	RemoveAllObject();


		//------------------------------------------------
		//
		// get Object		
		//
		//------------------------------------------------			
		OBJECT_MAP::iterator		GetObjectEnd()			{ return m_mapObject.end(); }
		OBJECT_MAP::const_iterator	GetObjectEnd() const	{ return m_mapObject.end(); }

		// Object*
		MItem*	const		GetItem() const;

		BYTE					GetUndergroundCreatureSize() const	{ return m_nUndergroundCreature; }
		BYTE					GetGroundCreatureSize() const		{ return m_nGroundCreature; }
		BYTE					GetFlyingCreatureSize() const		{ return m_nFlyingCreature; }
		int						GetCreatureSize() const				{ return (int)m_nGroundCreature+m_nUndergroundCreature+m_nFlyingCreature; }
		OBJECT_MAP::const_iterator	GetCreatureIterator() const;
		OBJECT_MAP::const_iterator	GetUndergroundCreatureIterator() const;
		OBJECT_MAP::const_iterator	GetGroundCreatureIterator() const;
		OBJECT_MAP::const_iterator	GetFlyingCreatureIterator() const;
		OBJECT_MAP::iterator	GetCreatureIterator();
		OBJECT_MAP::iterator	GetUndergroundCreatureIterator();
		OBJECT_MAP::iterator	GetGroundCreatureIterator();
		OBJECT_MAP::iterator	GetFlyingCreatureIterator();

		MCreature* const		GetCreature() const;
		MCreature* const		GetUndergroundCreature() const;
		MCreature* const		GetGroundCreature() const;
		MCreature* const		GetFlyingCreature() const;
		MImageObject* const		GetImageObject(TYPE_OBJECTID id) const;		

		// ����		
		BYTE			GetImageObjectSize() const		{ return m_nImageObject; }

		// iterator�� �Ѱ��ش�.
		OBJECT_MAP::const_iterator	GetImageObjectIterator() const;		
		

		// assign operator
		void	operator = (const MSector& sector);

		//------------------------------------------------
		//
		// Effect ����...
		//
		//------------------------------------------------
		bool		IsExistEffect() const		{ return !m_listEffect.empty(); }
		void		ClearEffect()				{ m_listEffect.clear(); }
		int			GetEffectSize() const		{ return m_listEffect.size(); }

		// �ܺο��� iterator�� �۾��� �� �� �ֵ���..
		EFFECT_LIST::const_iterator GetEffectIterator() const { return m_listEffect.begin(); }

		// Add/Get/Remove
		void		AddEffect(const MEffect* pEffect);
		MEffect*	GetEffect(TYPE_OBJECTID id) const;
		bool		RemoveEffect(TYPE_OBJECTID id, MEffect*& pEffect);
		bool		RemoveEffect(TYPE_OBJECTID id);
		
		// ����� ���� �ҷ��� darkness�� ���� ó���Ѵ�.
		bool		HasDarkness() const			{ return m_bDarkness; }
		void		SetDarkness()				{ m_bDarkness = true; }
		void		UnSetDarkness()				{ m_bDarkness = false; }
		
		// ����� ���� �ҷ��� �������ɵ� ���� ó���Ѵ�.-��-;;;
		bool		HasGroundElemental() const			{ return m_bGroundElemental; }
		void		SetGroundElemental()				{ m_bGroundElemental = true; }
		void		UnSetGroundElemental()				{ m_bGroundElemental = false; }
		
		// ����� ���� �ҷ��� DARKNESS_FORBIDDEN���� ���� ó���Ѵ�.-��-;;;
		bool		HasDarknessForbidden() const			{ return m_bDarknessForbidden; }
		void		SetDarknessForbidden()				{ m_bDarknessForbidden = true; }
		void		UnSetDarknessForbidden()				{ m_bDarknessForbidden = false; }
		
		// [�����] sanctuary�� �߰� --;
		bool		HasSanctuary() const		{ return m_bSanctuary; }
		void		SetSanctuary()				{ m_bSanctuary = true; }
		void		UnSetSanctuary()			{ m_bSanctuary = false; }
		
		//------------------------------------------------
		// Can Stand ?
		//------------------------------------------------
		bool		CanStandUndergroundCreature() const;
		bool		CanStandGroundCreature() const;
		bool		CanStandFlyingCreature() const;


		//------------------------------------------------
		//
		// �þ�/Filter ����
		//
		//------------------------------------------------
		//void			SetFilterSpriteID(TYPE_SPRITEID id)	{ m_FilterSpriteID = id; }
		//TYPE_SPRITEID	GetFilterSpriteID() const			{ return m_FilterSpriteID; }

		// �� ����..
		BYTE			GetLight() const					{ return m_Light; }
		void			AddLight()							{ if (m_Light<0xFF) m_Light++; }
		void			RemoveLight() 						{ if (m_Light>0) m_Light--; }
		
		//------------------------------------------------
		//
		// Portal
		//
		//------------------------------------------------
		BYTE	IsPortal() const		{ return m_fProperty & FLAG_SECTOR_PORTAL; }
		void	SetPortal()				{ m_fProperty |= FLAG_SECTOR_PORTAL; }
		void	UnSetPortal()			{ m_fProperty &= ~FLAG_SECTOR_PORTAL; }
		int							GetPortalSize() const	{ return m_listPortal.size(); }
		PORTAL_LIST::const_iterator	GetPortalBegin() const	{ return m_listPortal.begin(); }
		bool						AddPortal(int type, int zoneID);
		void						ClearPortal();

		//------------------------------------------------
		//
		// SectorSound
		//
		//------------------------------------------------
		const SECTORSOUND_LIST&				GetSectorSoundList() const	{ return m_listSectorSound; }
		int									GetSectorSoundSize() const	{ return m_listSectorSound.size(); }
		SECTORSOUND_LIST::const_iterator	GetSectorSoundBegin() const	{ return m_listSectorSound.begin(); }
		bool								AddSectorSound(int zoneSoundID, TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);
		bool								AddSectorSound(const SECTORSOUND_INFO& info);
		void								ClearSectorSound();

		//------------------------------------------------
		//
		// Safe - ��������
		//
		//------------------------------------------------
		void				SetSafe(BYTE flag)		{ m_fProperty2 = flag; }
		void				AddSafe(BYTE flag)		{ m_fProperty2 |= flag; }
		void				RemoveSafe(BYTE flag)	{ m_fProperty2 &= ~flag; }
		BYTE				GetSafe() const			{ return m_fProperty2; }
		BYTE				IsSafeSlayer() const	{ return (m_fProperty2 & FLAG_SECTOR_SAFE_COMMON) || (m_fProperty2 & FLAG_SECTOR_SAFE_SLAYER); }
		BYTE				IsSafeVampire() const	{ return (m_fProperty2 & FLAG_SECTOR_SAFE_COMMON) || (m_fProperty2 & FLAG_SECTOR_SAFE_VAMPIRE); }
		BYTE				IsSafeOusters() const	{ return (m_fProperty2 & FLAG_SECTOR_SAFE_COMMON) || (m_fProperty2 & FLAG_SECTOR_SAFE_OUSTERS); }
		BYTE				IsSafeComplete() const	{ return (m_fProperty2 & FLAG_SECTOR_SAFE_COMMON); }

		//------------------------------------------------
		//
		// Visited Flag - ��ã���
		//
		//------------------------------------------------
		void				SetVisitedFlag()		{ m_bVisitedFlag = true; }
		void				UnSetVisitedFlag()		{ m_bVisitedFlag = false; }
		const bool			IsVisitedFlag() const	{ return m_bVisitedFlag; }


		// ���� �ƿ� 140 ��ų ǻ�� ���� �� ���� fury of gnome
		bool		HasFuryOfGnome() const			{ return m_bFuryOfGnome; }
		void		SetFuryOfGnome()				{ m_bFuryOfGnome = true; }
		void		UnSetFuryOfGnome()				{ m_bFuryOfGnome = false; }

		// ����Ʈ ���� - Ÿ�� �������� �Ⱥ�������..-_-
		bool		HasDisableTileImage() const			{ return m_bDisableTileImage; }
		void		SetDisableTileImage()				{ m_bDisableTileImage = true; }
		void		UnSetDisableTileImage()				{ m_bDisableTileImage = false; }
	public :
		//----------------------------------------------------------------------
		// Key Value of Map
		//----------------------------------------------------------------------
		// ���� �ణ �Ҿ��ѵ�.. ��.��;;
		enum POSITION_VALUE 
		{				
			POSITION_ITEM = 1,					// Item�� �ִ� Node

			POSITION_UNDERGROUNDCREATURE=2,		// ���� ĳ���Ͱ� �ִ� Node (2~14)
			POSITION_UNDERGROUNDCREATURE_MAX=14,

			POSITION_GROUNDCREATURE=15,			// ���� ĳ���Ͱ� �ִ� Node (15~49)
			POSITION_GROUNDCREATURE_MAX=49,

			POSITION_FLYINGCREATURE=50,			// ���� ĳ���Ͱ� �ִ� Node (50~79)
			POSITION_FLYINGCREATURE_MAX=79,

			POSITION_PORTAL=80,					// Zone �̵��� �Ǵ� ���̴�.
			POSITION_IMAGEOBJECT = 81,			// ImageObject���� �����ϴ� Node(81~149)
			POSITION_EFFECT	= 150				// Effect���� �����ϴ� Node (150~255)	// �Ⱦ��� - -;
		};




	protected :
		// tile sprite�� ���� ����
		TYPE_SPRITEID		m_SpriteID;

		// �� Sector�� ���� �� �ִ� Object�鿡 ���� pointer
		OBJECT_MAP			m_mapObject;

		// �� Sector�� ���� �� �ִ� Effect�鿡 ���� pointer
		EFFECT_LIST			m_listEffect;

		// Filer�� ����� SpriteID
		//TYPE_SPRITEID	m_FilterSpriteID;
	
		PORTAL_LIST			m_listPortal;

		SECTORSOUND_LIST	m_listSectorSound;

		// ĳ���� ������
		BYTE				m_nGroundCreature;
		BYTE				m_nUndergroundCreature;
		BYTE				m_nFlyingCreature;

		// �����ϴ� ImageObject ������ ���� ����
		BYTE				m_nImageObject;			

		// ���� Flag
		BYTE				m_fProperty;

		// ��������
		BYTE				m_fProperty2;

		// ���� ���� ��
		BYTE				m_Light;


		bool				m_bDarkness;
		bool				m_bSanctuary;		// [�����]
		bool				m_bGroundElemental;		// [�����]
		bool				m_bDarknessForbidden;
		bool				m_bVisitedFlag;

		bool				m_bFuryOfGnome;
		bool				m_bDisableTileImage;
};

#endif


