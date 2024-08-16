//----------------------------------------------------------------------
// MItemTable.h
//----------------------------------------------------------------------
// Item�� ������ ���� ������ �����ϴ� class
//----------------------------------------------------------------------
//
// [ �������� �ִ� ���� ] 
//
// - Tile������ FrameID
// - Inventory������ SpriteID
// - �̸�... ���...
// 
//
// (*g_pItemTable)[class][type] ���� �ϳ��� Item������ ���� �����ϴ�.
//
//----------------------------------------------------------------------
//
// Value1 ~ 4�� �������̴�..
// Item�� ������ ���� Ư���� value�� ��� ���� ��ǥ�� �� �ִ�.
//
// MotorCycle				: ������(1), ��ݰ��ɹ���(2), Def(6)
// GearItem					: ������(1), Protection(2), Def(6)
// Belt						: ������(1), Protection(2), ���ϼ�(3), Def(6)
// HolyWater, ����, ��ź	: MinDam(1)~MaxDam(2)
// Potion					: ȸ����ġ(1)
// ��,��					: ������(1), Protection(?), MinDam(3)~MaxDam(4), Speed(7)
// ���ڰ�					: ������(1), Protection(?), MinDam(3)~MaxDam(4), MP����(5), Speed(7)
// ��						: ������(1), Protection(?), MinDam(3)~MaxDam(4), �����Ÿ�(5), Speed(7)
// źâ						: Maxźâ��(1)
//----------------------------------------------------------------------

#ifndef	__MITEMTABLE_H__
#define	__MITEMTABLE_H__

#pragma warning(disable:4786)

#include "CTypeTable.h"
#include "DrawTypeDef.h"
#include "MTypeDef.h"
#include "MString.h"
#include "SoundDef.h"
//#include "SkillDef.h"
#include <list>

//----------------------------------------------------------------------
// �ʿ�ɷ�ġ Flag
//----------------------------------------------------------------------
#define	REQUIRE_STR							0x01
#define	REQUIRE_DEX							0x02
#define	REQUIRE_INT							0x04
#define	REQUIRE_LEVEL						0x08

extern COLORREF g_ELEMENTAL_COLOR[5];
extern int g_ELEMENTAL_STRING_ID[5];

//----------------------------------------------------------------------
//
// �� ������ Item�� ���� ����
//
//----------------------------------------------------------------------
class ITEMTABLE_INFO {
	public :
		enum ELEMENTAL_TYPE
		{
			ELEMENTAL_TYPE_ANY = -1,
			ELEMENTAL_TYPE_FIRE,
			ELEMENTAL_TYPE_WATER,
			ELEMENTAL_TYPE_EARTH,
			ELEMENTAL_TYPE_WIND,
			ELEMENTAL_TYPE_SUM,

			ELEMENTAL_TYPE_MAX,
		};

		MString					HName;				// Item �ѱ� �̸�
		MString					EName;				// Item ���� �̸�
		MString					Description;		// Item�� ���� ����
		
	 	// Frame ID
		TYPE_FRAMEID			TileFrameID;		// Tile������ FrameID
		TYPE_FRAMEID			InventoryFrameID;	// Inventory������ Frame ID
		TYPE_FRAMEID			GearFrameID;		// Gear������ Frame ID
		TYPE_FRAMEID			AddonMaleFrameID;	// �������� ���� ���� FrameID - ����
		TYPE_FRAMEID			AddonFemaleFrameID;	// �������� ���� ���� FrameID - ����
		TYPE_FRAMEID			DropFrameID;		// item�� �ٴڿ� ����߷����� FrameID

		// 2005, 1, 14, sobeit add start - ItemDescription.spk ���� ���� frameID
		TYPE_FRAMEID			DescriptionFrameID;	// Description������ FrameID
		// 2005, 1, 14, sobeit add end
		
		// Sound ID
		TYPE_SOUNDID			UseSoundID;			// Item ��� SoundID			
		TYPE_SOUNDID			TileSoundID;		// Item �ݱ� SoundID
		TYPE_SOUNDID			InventorySoundID;	// Inventory������ Sound
		TYPE_SOUNDID			GearSoundID;		// Gear������ Sound

		bool					bMaleOnly;
		bool					bFemaleOnly;
		
		// inventory������ Gridũ��
		BYTE					GridWidth;
		BYTE					GridHeight;

		// item ��ü�� ���� ������ ����
		TYPE_ITEM_WEIGHT		Weight;				// ����	
		TYPE_ITEM_PRICE			Price;
		int						SilverMax;			// ������.. 0�̸� ���ϴ°Ŵ�.
		int						ToHit;				// ToHit

		// ����.. --> Protection, ���ݷ�, �����Ÿ�...
		int						Value1;
		int						Value2;
		int						Value3;				
		int						Value4;
		int						Value5;
		int						Value6;
		int						Value7;

		// �⺻ ���� ActionInfo
		TYPE_ACTIONINFO			UseActionInfo;	

		// �ִ밪 ����
		TYPE_ITEM_NUMBER		MaxNumber;

		// critical
		int						CriticalHit;
		std::list<TYPE_ITEM_OPTION>	DefaultOptionList;
		int						ItemStyle;
		
		// ousters info
		ELEMENTAL_TYPE			ElementalType;
		WORD					Elemental;
		BYTE					Race;
		
	//protected :	
	public:
		// ��밡���� ���Ѵɷ�
		BYTE					RequireSTR;
		BYTE					RequireDEX;
		BYTE					RequireINT;		
		BYTE					RequireLevel;
		BYTE					RequireAdvancementLevel; // �ʿ� ���� ����
		WORD					RequireSUM;		// �ɷ�ġ ����

	public :
		ITEMTABLE_INFO();
		~ITEMTABLE_INFO();

		//-------------------------------------------------------
		// Set
		//-------------------------------------------------------
		void	SetSoundID(TYPE_SOUNDID tile, TYPE_SOUNDID inventory, TYPE_SOUNDID gear, TYPE_SOUNDID use);
		void	SetFrameID(TYPE_FRAMEID tile, TYPE_FRAMEID inventory, TYPE_FRAMEID gear);
		void	SetDropFrameID(TYPE_FRAMEID drop);
		void	SetAddonFrameID(TYPE_FRAMEID male, TYPE_FRAMEID female);
		void	SetGrid(BYTE width, BYTE height);
		void	SetValue(int v1, int v2=-1, int v3=-1, int v4=-1, int v5=-1, int v6=-1, int v7=-1);
		void	SetDescriptionFrameID(TYPE_FRAMEID fID) { DescriptionFrameID = fID;}

		//-------------------------------------------------------
		// �ʿ�ɷ�ġ ����
		//-------------------------------------------------------
		void	SetRequireSTR(BYTE str=0)			{ RequireSTR = str; }
		void	SetRequireDEX(BYTE dex=0)			{ RequireDEX = dex; }
		void	SetRequireINT(BYTE intel=0)			{ RequireINT = intel; }
		void	SetRequireSUM(WORD sum=0)			{ RequireSUM = sum; }
		void	SetRequireLevel(BYTE level=0)		{ RequireLevel = level; }		
		void	SetRequireAdvancementLevel(BYTE level=0)		{ RequireAdvancementLevel = level; }		

		//-------------------------------------------------------
		// Get
		//-------------------------------------------------------
		BYTE		GetRequireSTR()	const				{ return RequireSTR; }
		BYTE		GetRequireDEX()	const				{ return RequireDEX; }
		BYTE		GetRequireINT()	const				{ return RequireINT; }
		WORD		GetRequireSUM()	const				{ return RequireSUM; }
		BYTE		GetRequireLevel() const				{ return RequireLevel; }		
		BYTE		GetRequireAdvancementLevel() const	{ return RequireAdvancementLevel; }		

		//-------------------------------------------------------
		// ����
		//-------------------------------------------------------
		bool		IsGenderForMale() const				{ return bMaleOnly; }
		bool		IsGenderForFemale() const			{ return bFemaleOnly; }
		bool		IsGenderForAll() const				{ return !bMaleOnly && !bFemaleOnly; }
		

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);		
		void			LoadFromFile(class ifstream& file);		
};


//--------------------------------------------------------------------------
// �ϳ��� class�� ���� type���� ����
//--------------------------------------------------------------------------
class ITEMTYPE_TABLE : public CTypeTable<ITEMTABLE_INFO>
{
public :
	void	LoadFromFile(class ifstream& file);

	int		GetAveragePrice() const	{ return m_AveragePrice; }

private :
	int		m_AveragePrice;
};

//----------------------------------------------------------------------
//
// ItemClass�� ���� Table
//
//  :  (*g_pItemTable)[ itemClass ][ itemType ]
//
//----------------------------------------------------------------------
class ITEMCLASS_TABLE : public CTypeTable<ITEMTYPE_TABLE> {

	public :
		ITEMCLASS_TABLE();
		~ITEMCLASS_TABLE();

		//-------------------------------------------------------
		// �� classType�� �´� ������ �ʱ�ȭ�Ѵ�.
		//-------------------------------------------------------
		void		InitClass( int c, int size );
		void		InitItem2();
};

extern	ITEMCLASS_TABLE	*	g_pItemTable;


#endif
