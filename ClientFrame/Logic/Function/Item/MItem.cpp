//----------------------------------------------------------------------
// MItem.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#pragma warning(disable:4786)

#include "MItem.h"
#include "MItemTable.h"
#include "MItemOptionTable.h"
#include "UserInformation.h"
#include "ClientConfig.h"
#include "MTimeItemManager.h"
#include "MGameStringTable.h"
#include "MCreatureTable.h"
#include "MFakeCreature.h"

#ifdef __GAME_CLIENT__
	#include "Client.h"
	#include "SkillDef.h"
	#include "MSkillManager.h"
	#include "ClientFunction.h"
	#include "MGameStringTable.h"
	#include "MInventory.h"
	#include "MSlayerGear.h"
	#include "ServerInfo.h"
	#include "UIFunction.h"
	#include "MZone.h"
	#include "MZoneTable.h"
	#include "MPlayer.h"
	#include "packet\CPackets\CGUseItemFromGear.h"
	#include "packet/CPackets/CGUsePotionFromInventory.h"
	#include "packet/CPackets/CGUsePotionFromQuickSlot.h"

	#include "FL2.h"
	#include "VS_UI_GameCommon.h"
	#include "vs_ui.h"
	#include "UIDialog.h"
#endif

#include <fstream.h>
#include <algorithm>

#ifdef __GAME_CLIENT__
	#include "DebugInfo.h"
	#include "MCreature.h"
	#include "MTopView.h"	
#endif

extern DWORD g_CurrentFrame;
extern bool g_bHolyLand;
extern bool g_bZoneSafe;

//----------------------------------------------------------------------
// �ִ� ��
//----------------------------------------------------------------------
//#define MAX_FIRE_CRACKER_PILE_NUMBER	9
//#define	MAX_POTION_PILE_NUMBER			9
//#define	MAX_MAGAZINE_PILE_NUMBER		20
//#define	MAX_EVENT_STAR_PILE_NUMBER		50
//#define	MAX_MONEY_NUMBER				100000000
//#define	MAX_SKULL_NUMBER				9
//#define	MAX_WATER_NUMBER				20
//#define	MAX_HOLY_WATER_NUMBER			20
//#define	MAX_BOMB_MATERIAL_NUMBER		20
//#define	MAX_BOMB_NUMBER					20
//#define	MAX_MINE_NUMBER					20
//#define MAX_EFFECT_ITEM_NUMBER			20
//#define	MAX_VAMPIRE_ETC_NUMBER			9
//#define	MAX_SERUM_NUMBER				9
//#define MAX_RESURRECT_SCROLL_NUMBER		9
//#define MAX_MIXING_ITEM_NUMBER			9
//#define MAX_OUSTERS_GEM_NUMBER			50
//#define MAX_OUSTERS_LARVA_NUMBER		9
//#define MAX_MOON_CARD_NUMBER			99
//#define MAX_LUCKY_BAG_NUMBER			50
//
//#define MAX_SLAYER_ATTR_OLD				200
//#define MAX_SLAYER_ATTR_SUM_OLD			300
//#define MAX_VAMPIRE_LEVEL_OLD			100
//
//#define	MAX_SLAYER_ATTR					295
//#define	MAX_SLAYER_ATTR_SUM				435
//#define MAX_VAMPIRE_LEVEL				150
//#define MAX_OUSTERS_LEVEL				150
//#define MAX_PET_ENCHANT_PILE_NUMBER		50
//#define MAX_PET_FOOD_PILE_NUMBER		9

#define MAX_FIRE_CRACKER_PILE_NUMBER	9
#define	MAX_POTION_PILE_NUMBER			30
#define	MAX_MAGAZINE_PILE_NUMBER		20
#define	MAX_EVENT_STAR_PILE_NUMBER		50
#define	MAX_MONEY_NUMBER				100000000
#define	MAX_SKULL_NUMBER				9
#define	MAX_WATER_NUMBER				50
#define	MAX_HOLY_WATER_NUMBER			50
#define	MAX_BOMB_MATERIAL_NUMBER		20
#define	MAX_BOMB_NUMBER					20
#define	MAX_MINE_NUMBER					20
#define MAX_EFFECT_ITEM_NUMBER			20
#define	MAX_VAMPIRE_ETC_NUMBER			20
#define	MAX_SERUM_NUMBER				30
#define MAX_RESURRECT_SCROLL_NUMBER		9
#define MAX_MIXING_ITEM_NUMBER			9
#define MAX_OUSTERS_GEM_NUMBER			50
#define MAX_OUSTERS_LARVA_NUMBER		30
#define MAX_MOON_CARD_NUMBER			99
#define MAX_LUCKY_BAG_NUMBER			50

#define MAX_SLAYER_ATTR_OLD				200
#define MAX_SLAYER_ATTR_SUM_OLD			300
#define MAX_VAMPIRE_LEVEL_OLD			100

#define	MAX_SLAYER_ATTR					295
#define	MAX_SLAYER_ATTR_SUM				435
#define MAX_VAMPIRE_LEVEL				150
#define MAX_OUSTERS_LEVEL				150
#define MAX_PET_ENCHANT_PILE_NUMBER		50
#define MAX_PET_FOOD_PILE_NUMBER		9
//----------------------------------------------------------------------
//
// static members
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// �ѱ��� ����ϴ°�?
//----------------------------------------------------------------------
bool	MItem::s_bUseKorean	= true;

//----------------------------------------------------------------------
// Item ����߸����� ���̵�..
//----------------------------------------------------------------------
int		MItem::s_DropHeight[MAX_DROP_COUNT] = 
{
	36, 49, 64, 36, 16, 4
};

//----------------------------------------------------------------------
// ItemClass�� �°� �޸𸮸� ����ִ� class table�� ����..
//----------------------------------------------------------------------
MItem::FUNCTION_NEWITEMCLASS
MItem::s_NewItemClassTable[MAX_ITEM_CLASS] =
{
	MMotorcycle::NewItem,
	MPotion::NewItem,
	MWater::NewItem,
	MHolyWater::NewItem,
	MMagazine::NewItem,
	MBombMaterial::NewItem,
	MItemETC::NewItem,
	MKey::NewItem,
	MRing::NewItem,
	MBracelet::NewItem,
	MNecklace::NewItem,
	MCoat::NewItem,
	MTrouser::NewItem,
	MShoes::NewItem,
	MSword::NewItem,
	MBlade::NewItem,
	MShield::NewItem,
	MCross::NewItem,
	MGlove::NewItem,
	MHelm::NewItem,
	MGunSG::NewItem,
	MGunSMG::NewItem,
	MGunAR::NewItem,
	MGunTR::NewItem,
	MBomb::NewItem,
	MMine::NewItem,
	MBelt::NewItem,
	MLearningItem::NewItem,
	MMoney::NewItem,
	MCorpse::NewItem,
	//MSkull::NewItem,

	// vampire�� item
	MVampireRing::NewItem,
	MVampireBracelet::NewItem,
	MVampireNecklace::NewItem,
	MVampireCoat::NewItem,

	// skull
	MSkull::NewItem,

	// mace�߰� - 2001/3/26
	MMace::NewItem,

	MSerum::NewItem,

	// 2001.8.21
	MVampireETC::NewItem,

	// 2001.10.22
	MSlayerPortalItem::NewItem,
	MVampirePortalItem::NewItem,

	// 2001.12.10
	MEventGiftBoxItem::NewItem,
	MEventStarItem::NewItem,

	MVampireEarRing::NewItem,

	// 2002.6.7
	MRelic::NewItem,

	// 2002.8.18
	MVampireWeapon::NewItem,
	MVampireAmulet::NewItem,

	// 2002.9.7
	MQuestItem::NewItem,

	// 2002.12.9
	MEventTreeItem::NewItem,
	MEventEtcItem::NewItem,

	// 2003.1.29
	MBloodBible::NewItem,
	
	// 2003.2.12
	MCastleSymbol::NewItem,

	MCoupleRing::NewItem,
	MVampireCoupleRing::NewItem,
	
	MEventItem::NewItem,
	MDyePotionItem::NewItem,
	MResurrectItem::NewItem,
	MMixingItem::NewItem,

	MOustersArmsBand::NewItem,
	MOustersBoots::NewItem,
	MOustersChakram::NewItem,
	MOustersCirclet::NewItem,
	MOustersCoat::NewItem,
	MOustersPendent::NewItem,
	MOustersRing::NewItem,
	MOustersStone::NewItem,
	MOustersWristlet::NewItem,

	MOustersLarva::NewItem,					// 66
	MOustersPupa::NewItem,					// 67
	MOustersComposMei::NewItem,				// 68
	MOustersSummonGem::NewItem,				// 69
	MEffectItem::NewItem,					// 70
	MCodeSheetItem::NewItem,				// 71
	MMoonCardItem::NewItem,
	
	MSweeperItem::NewItem,
	MPetItem::NewItem,
	MPetFood::NewItem,
	MPetEnchantItem::NewItem,
	MLuckyBag::NewItem,
	MSms_item::NewItem,
	MCoreZap::NewItem,
	MGQuestItem::NewItem,
	MTrapItem::NewItem,
	MBloodBibleSign::NewItem,
	MWarItem::NewItem,
		//by csm 2�� ���� ������ Ŭ���� �߰� 
	MCarryingReceiver::NewItem,
	MShoulderArmor::NewItem,
	MDermis::NewItem,
	MPersona::NewItem,
	MFascia::NewItem,
	MMitten::NewItem,
	
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		MSubInventory::NewItem,
	#endif

};

//----------------------------------------------------------------------
// new functions
//----------------------------------------------------------------------
/*	
MItem*	MMotorcycle::NewItem()		{ return new MMotorcycle; }
MItem*	MPotion::NewItem()			{ return new MPotion; }	
MItem*	MWater::NewItem()			{ return new MWater; }
MItem*	MHolyWater::NewItem()		{ return new MHolyWater; }
MItem*	MMagazine::NewItem()		{ return new MMagazine; }
MItem*	MBombMaterial::NewItem()	{ return new MBombMaterial; }
MItem*	MItemETC::NewItem()			{ return new MItemETC; }
MItem*	MKey::NewItem()				{ return new MKey; }
MItem*	MRing::NewItem()			{ return new MRing; }
MItem*	MBracelet::NewItem()		{ return new MBracelet; }
MItem*	MNecklace::NewItem()		{ return new MNecklace; }
MItem*	MCoat::NewItem()			{ return new MCoat; }
MItem*	MTrouser::NewItem()			{ return new MTrouser; }
MItem*	MShoes::NewItem()			{ return new MShoes; }
MItem*	MSword::NewItem()			{ return new MSword; }
MItem*	MBlade::NewItem()			{ return new MBlade; }
MItem*	MShield::NewItem()			{ return new MShield; }
MItem*	MCross::NewItem()			{ return new MCross; }
MItem*	MGlove::NewItem()			{ return new MGlove; }
MItem*	MHelm::NewItem()			{ return new MHelm; }
MItem*	MGunSG::NewItem()			{ return new MGunSG; }
MItem*	MGunSMG::NewItem()			{ return new MGunSMG; }
MItem*	MGunAR::NewItem()			{ return new MGunAR; }
MItem*	MGunTR::NewItem()			{ return new MGunTR; }
MItem*	MBomb::NewItem()			{ return new MBomb; }
MItem*	MMine::NewItem()			{ return new MMine; }
MItem*	MBelt::NewItem()			{ return new MBelt; }
MItem*	MLearningItem::NewItem()	{ return new MLearningItem; }
MItem*	MMoney::NewItem()			{ return new MMoney; }
MItem*	MCorpse::NewItem()			{ return new MCorpse; }

// vampire�� item
MItem*	MVampireRing::NewItem()		{ return new MVampireRing; }
MItem*	MVampireBracelet::NewItem()	{ return new MVampireBracelet; }
MItem*	MVampireNecklace::NewItem()	{ return new MVampireNecklace; }
MItem*	MVampireCoat::NewItem()		{ return new MVampireCoat; }
MItem*	MVampireShoes::NewItem()	{ return new MVampireShoes; }
*/

//----------------------------------------------------------------------
// New Item
//----------------------------------------------------------------------
// itemClass�� �´� class�� ��ü�� �����ؼ�(new) �Ѱ��ش�.
//----------------------------------------------------------------------
MItem*		
MItem::NewItem(ITEM_CLASS itemClass)
{
	return (MItem*)(*s_NewItemClassTable[itemClass])();
};

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------

MItem::MItem()
{
	m_ObjectType	= TYPE_ITEM;

	// 
	m_Number		= 1;

	//m_ItemClass		= ITEMCLASS_NULL;
	m_ItemType		= 0;//ITEMTYPE_NULL;
//	m_ItemOption	= 0;

	m_bDropping		= FALSE;	// �������� �ִ� ��
	m_DropCount		= 0;		// ���� count

	// identify
	m_bIdentified	= TRUE;

	m_pName = NULL;

	m_bAffectStatus = true;

	m_Silver = 0;

	m_Grade = -1;
	m_EnchantLevel = 0;
	m_Speed = 0;
	m_Quest = 0;
	m_ItemColorSet = 0xFFFF;
	m_persnal_price = -1;
	m_persnal = false;
}

MItem::~MItem()
{
	if (m_pName!=NULL)
	{
		delete [] m_pName;
	}
}


//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Is Insert To Item ( pItem )
//----------------------------------------------------------------------
// pItem�� �߰��� �� �ִ°�?
//----------------------------------------------------------------------
bool		
MItem::IsInsertToItem(const MItem* pItem) const
{
	if (pItem==NULL) 
	{
		return false;
	}

	//-------------------------------------------------
	// ���̴� Item�̰� 
	// class�� type�� ���ƾ� ���δ�.	
	// ���� ������ �Ѱ踦 ���� ���� ��� 
	// --> �߰� ����
	//-------------------------------------------------

	// (!)������ ���̰� �ϸ� �ȵȴ�.

	///*
	if (pItem->IsPileItem() 
		&& GetItemClass()==pItem->GetItemClass()
		&& GetItemType()==pItem->GetItemType())
		//&& pItem->GetNumber() < pItem->GetMaxNumber())
	{
		return true;
	}
	//*/

	return false;
}

//----------------------------------------------------------------------
// Get Name
//----------------------------------------------------------------------
const char *
MItem::GetName()
{
	//---------------------------------------------------------
	// ������ �̸��� ���� ���ٸ�.. ������ �̸� return
	//---------------------------------------------------------
	if (m_pName==NULL)
	{
		//if (s_bUseKorean) 
		{
			// ƾ�����ΰ�� XXX�Ӹ��� XXX�ҿ� ����� ǥ���Ѵ�.
			if(g_pUserInformation->GoreLevel == false && GetItemClass() == ITEM_CLASS_SKULL)
			{
//				static char sz_temp[256];
				m_pName = new char[strlen((*g_pItemTable)[GetItemClass()][m_ItemType].HName)+1+5];
				strcpy(m_pName, (*g_pItemTable)[GetItemClass()][m_ItemType].HName);

				char *psz_temp = &m_pName[strlen(m_pName)-4];
				if(psz_temp != NULL)
				{
					strcpy(psz_temp, (*g_pGameStringTable)[STRING_MESSAGE_SOUL_STONE].GetString());
					return m_pName;
				}
			}

			return (*g_pItemTable)[GetItemClass()][m_ItemType].HName; 
		}
		//else 
//		{
		//	return (*g_pItemTable)[GetItemClass()][m_ItemType].EName; 
//		}
	}
	
	return m_pName;
}

//----------------------------------------------------------------------
// Get EnglishName
//----------------------------------------------------------------------
const char *
MItem::GetEName() const
{
	//---------------------------------------------------------
	// ������ �̸��� ���� ���ٸ�.. ������ �̸� return
	//---------------------------------------------------------
//	if (m_pName==NULL)
	{
		// ƾ�����ΰ�� XXXHead�Ǵ� XXXSkull�� XXXSoul Stone�� ǥ���Ѵ�.
		if(g_pUserInformation->GoreLevel == false && GetItemClass() == ITEM_CLASS_SKULL)
		{
			static char sz_temp[256];
			strcpy(sz_temp, (*g_pItemTable)[GetItemClass()][m_ItemType].EName);
			
			char *psz_temp = strstr(sz_temp, "Head");

			if(psz_temp == NULL)psz_temp = strstr(sz_temp, "Skull");

			if(psz_temp != NULL)
			{
				strcpy(psz_temp, (*g_pGameStringTable)[STRING_MESSAGE_SOUL_STONE].GetString());
				return sz_temp;
			}
		}
		return (*g_pItemTable)[GetItemClass()][m_ItemType].EName; 		
	}
	

	
	return m_pName;
}

//----------------------------------------------------------------------
// Set Name
//----------------------------------------------------------------------
// m_pName�� �̸��� ���سִ´�.
//----------------------------------------------------------------------
void
MItem::SetName(const char* pName)
{
	if (m_pName!=NULL)
	{
		delete [] m_pName;
		m_pName = NULL;
	}

	if (pName==NULL)
	{
		return;
	}

	//---------------------------------------------
	// ����..
	//---------------------------------------------
	m_pName = new char[strlen(pName) + 1];

	strcpy(m_pName, pName);
}

//----------------------------------------------------------------------
// Get Description
//----------------------------------------------------------------------
const char*				
MItem::GetDescription() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].Description;
}

//----------------------------------------------------------------------
// Get Weight
//----------------------------------------------------------------------
TYPE_ITEM_WEIGHT		
MItem::GetWeight() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].Weight;
}

//----------------------------------------------------------------------
// Get Weight
//----------------------------------------------------------------------
TYPE_ITEM_PRICE
MItem::GetPrice() const
{
	TYPE_ITEM_PRICE price;
	if( GetGrade() > 0 &&  GetGrade() <= 10 && IsGearItem() )
		price = (*g_pItemTable)[GetItemClass()][m_ItemType].Price * ( 100 + (GetGrade()-4)*5 ) / 100;
	else
		price = (*g_pItemTable)[GetItemClass()][m_ItemType].Price;
	return price;
}

//----------------------------------------------------------------------
// Get GridWidth
//----------------------------------------------------------------------
BYTE					
MItem::GetGridWidth() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].GridWidth;
}

//----------------------------------------------------------------------
// Get GridHeight
//----------------------------------------------------------------------
BYTE					
MItem::GetGridHeight() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].GridHeight;
}

//----------------------------------------------------------------------
// Get TileFrameID
//----------------------------------------------------------------------
TYPE_FRAMEID			
MItem::GetTileFrameID() const
{
	// ƾ������ ��� �Ӹ��� �������� ǥ���Ѵ�.
	if(g_pUserInformation->GoreLevel == false && GetItemClass() == ITEM_CLASS_SKULL)
		return 271;

	return (*g_pItemTable)[GetItemClass()][m_ItemType].TileFrameID;
}

//----------------------------------------------------------------------
// Get InventoryFrameID
//----------------------------------------------------------------------
TYPE_FRAMEID			
MItem::GetInventoryFrameID() const
{
	// ƾ������ ��� �Ӹ��� �������� ǥ���Ѵ�.
	if(g_pUserInformation->GoreLevel == false && GetItemClass() == ITEM_CLASS_SKULL)
		return 285;

	return (*g_pItemTable)[GetItemClass()][m_ItemType].InventoryFrameID;
}

//----------------------------------------------------------------------
// Get GearFrameID
//----------------------------------------------------------------------
TYPE_FRAMEID			
MItem::GetGearFrameID() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].GearFrameID;
}


//----------------------------------------------------------------------
// Get DropFrameID
//----------------------------------------------------------------------
TYPE_FRAMEID			
MItem::GetDropFrameID() const
{
	if(GetItemClass() == ITEM_CLASS_EVENT_GIFT_BOX && GetItemType() == 2)
	{
		int frameID = (*g_pItemTable)[GetItemClass()][m_ItemType].DropFrameID;
	}
	// ƾ������ ��� �Ӹ��� �������� ǥ���Ѵ�.
	if(g_pUserInformation->GoreLevel == false && GetItemClass() == ITEM_CLASS_SKULL)
		return 271;

	return (*g_pItemTable)[GetItemClass()][m_ItemType].DropFrameID;
}

//----------------------------------------------------------------------
// Get AddonMaleFrameID
//----------------------------------------------------------------------
TYPE_FRAMEID			
MItem::GetAddonMaleFrameID() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].AddonMaleFrameID;
}

//----------------------------------------------------------------------
// Get AddonFemaleFrameID
//----------------------------------------------------------------------
TYPE_FRAMEID			
MItem::GetAddonFemaleFrameID() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].AddonFemaleFrameID;
}

//----------------------------------------------------------------------
// Get UseSoundID
//----------------------------------------------------------------------
TYPE_SOUNDID			
MItem::GetUseSoundID() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].UseSoundID;
}

//----------------------------------------------------------------------
// Get TileSoundID
//----------------------------------------------------------------------
TYPE_SOUNDID			
MItem::GetTileSoundID() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].TileSoundID;
}

//----------------------------------------------------------------------
// Get InventorySoundID
//----------------------------------------------------------------------
TYPE_SOUNDID			
MItem::GetInventorySoundID() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].InventorySoundID;
}

//----------------------------------------------------------------------
// Get GearSoundID
//----------------------------------------------------------------------
TYPE_SOUNDID			
MItem::GetGearSoundID() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].GearSoundID;
}

//----------------------------------------------------------------------
// Is Gender For Male
//----------------------------------------------------------------------
bool		
MItem::IsGenderForMale() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].IsGenderForMale();
}

//----------------------------------------------------------------------
// Is Gender For Female
//----------------------------------------------------------------------
bool		
MItem::IsGenderForFemale() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].IsGenderForFemale();
}

//----------------------------------------------------------------------
// Is Gender For All
//----------------------------------------------------------------------
bool		
MItem::IsGenderForAll() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].IsGenderForAll();
}

int	
MItem::IsQuestItem() const
{
	if( g_pTimeItemManager != NULL && (g_pTimeItemManager->IsExist( GetID() ) || m_Quest ) )
		return 1;

	return 0;
}

bool				
MItem::IsSpecialColorItem() const
{	
	if( IsUniqueItem() || IsQuestItem() )
		return true;
	
	return false;
}

//----------------------------------------------------------------------
// Potion :: Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MPotion::GetMaxNumber() const	
{ 
	return MAX_POTION_PILE_NUMBER; 
}

//----------------------------------------------------------------------
// Magazine :: Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MMagazine::GetMaxNumber() const	
{ 
	return MAX_MAGAZINE_PILE_NUMBER; 
}

//----------------------------------------------------------------------
// Money :: Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MMoney::GetMaxNumber() const	
{ 
	return MAX_MONEY_NUMBER; 
}

//----------------------------------------------------------------------
// MWater - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MWater::GetMaxNumber() const
{
	return MAX_WATER_NUMBER;
}

//----------------------------------------------------------------------
// MHolyWater - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MHolyWater::GetMaxNumber() const
{
	return MAX_HOLY_WATER_NUMBER;	
}

//----------------------------------------------------------------------
// MBombMaterial - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MBombMaterial::GetMaxNumber() const
{
	return MAX_BOMB_MATERIAL_NUMBER;	
}

//----------------------------------------------------------------------
// MBomb - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MBomb::GetMaxNumber() const
{
	return MAX_BOMB_NUMBER;	
}

//----------------------------------------------------------------------
// MMine - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MMine::GetMaxNumber() const
{
	return MAX_MINE_NUMBER;	
}

//----------------------------------------------------------------------
// MVampireETC - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MVampireETC::GetMaxNumber() const
{
	return MAX_VAMPIRE_ETC_NUMBER;
}

//----------------------------------------------------------------------
// MSerum - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MSerum::GetMaxNumber() const
{
	return MAX_SERUM_NUMBER;
}

//----------------------------------------------------------------------
// MSkull - Get MaxNumber
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MSkull::GetMaxNumber() const
{
	return MAX_SKULL_NUMBER;
}

TYPE_ITEM_NUMBER
MEventEtcItem::GetMaxNumber() const
{
	return MAX_FIRE_CRACKER_PILE_NUMBER;
}

//----------------------------------------------------------------------
// MGearItem::Get MaxDurability
//----------------------------------------------------------------------
int	
MGearItem::GetMaxDurability() const	
{ 
	int maxDur = (*g_pItemTable)[GetItemClass()][m_ItemType].Value1; 

	maxDur += (GetGrade()-4)*1000;

	int plus_point = 100;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		ITEMOPTION_INFO& optionInfo = (*g_pItemOptionTable)[*itr];
		
		if (optionInfo.Part == ITEMOPTION_TABLE::PART_DURABILITY)
		{
			plus_point += optionInfo.PlusPoint-100;
		}

		itr++;
	}

	if(plus_point != 0)
		maxDur = maxDur * plus_point / 100;

	return max( min( 65000, maxDur ), 1000 );
}

int
MWeaponItem::GetMinDamage() const
{
	return max(1, (*g_pItemTable)[GetItemClass()][m_ItemType].Value3 + (GetGrade()-4) );
}	// �ּ� ���ݷ�

int
MWeaponItem::GetMaxDamage() const
{
	return max(1, (*g_pItemTable)[GetItemClass()][m_ItemType].Value4 + (GetGrade()-4) );
}	// �ִ� ���ݷ�		

int
MWeaponItem::GetToHit() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].ToHit;
}		// �ִ� ���ݷ�		

int
MWeaponItem::GetCriticalHit() const
{
	return max( 0, (*g_pItemTable)[GetItemClass()][m_ItemType].CriticalHit + (GetGrade()-4)*2 );
}

int
MArmorItem::GetProtectionValue() const
{
	return max( 0, MGearItem::GetProtectionValue() + (GetGrade()-4) );
}

int
MArmorItem::GetDefenseValue() const
{
	return max( 0, MGearItem::GetDefenseValue() + (GetGrade()-4)*2 );
}
int 
MArmorItem2::GetProtectionValue() const
{
	return max( 0, MGearItem::GetProtectionValue() + ((GetGrade()-4)/2) );
}

int
MArmorItem2::GetDefenseValue() const
{
	return max( 0, MGearItem::GetDefenseValue() + (GetGrade()-4) );
}
int	
MArmorItem2::GetMaxDurability() const	
{ 
	int maxDur = (*g_pItemTable)[GetItemClass()][m_ItemType].Value1; 

	maxDur += (GetGrade()-4)*500;

	int plus_point = 100;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		ITEMOPTION_INFO& optionInfo = (*g_pItemOptionTable)[*itr];
		
		if (optionInfo.Part == ITEMOPTION_TABLE::PART_DURABILITY)
		{
			plus_point += optionInfo.PlusPoint-100;
		}

		itr++;
	}

	if(plus_point != 0)
		maxDur = maxDur * plus_point / 100;

	return max( min( 65000, maxDur ), 1000 );
}

int
MAccessoryItem::GetLucky() const
{
	return  (GetGrade()-4);
}

//----------------------------------------------------------------------
// MMotorcycle::Get MaxDurability
//----------------------------------------------------------------------
int
MMotorcycle::GetMaxDurability() const	
{ 
	int maxDur = (*g_pItemTable)[ITEM_CLASS_MOTORCYCLE][m_ItemType].Value1; 

	int plus_point = 100;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		ITEMOPTION_INFO& optionInfo = (*g_pItemOptionTable)[*itr];
		
		if (optionInfo.Part == ITEMOPTION_TABLE::PART_DURABILITY)
		{
			plus_point += optionInfo.PlusPoint-100;
		}

		itr++;
	}

	if(plus_point != 0)
		maxDur = maxDur * plus_point / 100;

	return min( 65000, maxDur );
}

//----------------------------------------------------------------------
// Get ItemOption Part
//----------------------------------------------------------------------
BYTE					
MItem::GetItemOptionPart(int OptionNum) const
{
	if(m_ItemOptionList.empty()) return (*g_pItemOptionTable)[0].Part;

	int count = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end() && count < OptionNum)
	{
		count++;
		itr++;
	}

	if(itr != m_ItemOptionList.end())
		return (*g_pItemOptionTable)[*itr].Part;
	else
		return (*g_pItemOptionTable)[0].Part;
}

//----------------------------------------------------------------------
// Get ItemOption Name
//----------------------------------------------------------------------
const char*				
MItem::GetItemOptionName(int OptionNum) const
{
	if(m_ItemOptionList.empty()) return(*g_pItemOptionTable)[0].Name;

	int count = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end() && count < OptionNum)
	{
		count++;
		itr++;
	}

	if(itr != m_ItemOptionList.end() && *itr < g_pItemOptionTable->GetSize())
		return (*g_pItemOptionTable)[*itr].Name;
	else
		return (*g_pItemOptionTable)[0].Name;
}

//----------------------------------------------------------------------
// Get ItemOption Name
//----------------------------------------------------------------------
const char*				
MItem::GetItemOptionEName(int OptionNum) const
{
	if(m_ItemOptionList.empty()) return (*g_pItemOptionTable)[0].EName;

	int count = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end() && count < OptionNum)
	{
		count++;
		itr++;
	}

	if(itr != m_ItemOptionList.end() && *itr < g_pItemOptionTable->GetSize())
		return (*g_pItemOptionTable)[*itr].EName;
	else
		return (*g_pItemOptionTable)[0].EName;
}

//----------------------------------------------------------------------
// Get ItemOption PlusPoint
//----------------------------------------------------------------------
BYTE					
MItem::GetItemOptionPlusPoint(int OptionNum) const
{
	if(m_ItemOptionList.empty()) return (*g_pItemOptionTable)[0].PlusPoint;

	int count = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end() && count < OptionNum)
	{
		count++;
		itr++;
	}

	if(itr != m_ItemOptionList.end())
		return (*g_pItemOptionTable)[*itr].PlusPoint;
	else
		return (*g_pItemOptionTable)[0].PlusPoint;
}

//----------------------------------------------------------------------
// Get ItemOption PlusRequireAbility
//----------------------------------------------------------------------
/*
BYTE					
MItem::GetItemOptionPlusRequireAbility() const
{
	return (*g_pItemOptionTable)[m_ItemOption].PlusRequireAbility;
}
*/

//----------------------------------------------------------------------
// Get ItemOption PriceMultiplier
//----------------------------------------------------------------------
DWORD					
MItem::GetItemOptionPriceMultiplier() const
{
	int re = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		re += (*g_pItemOptionTable)[*itr].PriceMultiplier;
		itr++;
	}

	return re;
}

//----------------------------------------------------------------------
// Get ItemOption ColorSet
//----------------------------------------------------------------------
WORD					
MItem::GetItemOptionColorSet(int OptionNum)
{	
	if(GetItemClass() == ITEM_CLASS_PET_ITEM)
	{
#ifdef __GAME_CLIENT__
		g_pPlayer->CheckAffectStatus(this);
#endif
		if(GetItemColorSet() == 0xFFFF)
		{
			if(GetSilver() > 0)	// �Ӽ��� �ִ� ���� �� ǥ��
			{
				ITEMOPTION_TABLE::ITEMOPTION_PART optionPart = static_cast<ITEMOPTION_TABLE::ITEMOPTION_PART>(GetEnchantLevel());

				int size = g_pItemOptionTable->GetSize();

				for(int i = 1; i < size; i++)
				{
					ITEMOPTION_INFO &optionInfo = g_pItemOptionTable->Get(i);
					if(optionInfo.Part == optionPart && optionInfo.UpgradeOptionType == 0)
					{
						SetItemColorSet(optionInfo.ColorSet);
						
						break;
					}
				}
			}
			else
			{
				SetItemColorSet((*g_pItemOptionTable)[0].ColorSet);
			}
		}

		return GetItemColorSet();
	}
	
	if(IsQuestItem() )
		return QUEST_ITEM_COLOR;

	if(IsUniqueItem())
		return UNIQUE_ITEM_COLOR;
	
	if(m_ItemOptionList.empty()) return (*g_pItemOptionTable)[0].ColorSet;

	int count = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end() && count < OptionNum)
	{
		count++;
		itr++;
	}

	if(itr != m_ItemOptionList.end())
		return (*g_pItemOptionTable)[*itr].ColorSet;
	else
		return (*g_pItemOptionTable)[0].ColorSet;
}

//----------------------------------------------------------------------
// Get ItemOption ColorSet
//----------------------------------------------------------------------
int					
MItem::GetItemOptionRequireSTR() const
{	
	int re = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		re += (*g_pItemOptionTable)[*itr].RequireSTR;
		itr++;
	}

	return re;
}

//----------------------------------------------------------------------
// Get ItemOption ColorSet
//----------------------------------------------------------------------
int					
MItem::GetItemOptionRequireDEX() const
{	
	int re = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		re += (*g_pItemOptionTable)[*itr].RequireDEX;
		itr++;
	}

	return re;
}

//----------------------------------------------------------------------
// Get ItemOption ColorSet
//----------------------------------------------------------------------
int					
MItem::GetItemOptionRequireINT() const
{	
	int re = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		re += (*g_pItemOptionTable)[*itr].RequireINT;
		itr++;
	}

	return re;
}

//----------------------------------------------------------------------
// Get ItemOption ColorSet
//----------------------------------------------------------------------
int					
MItem::GetItemOptionRequireLevel() const
{	
	int re = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		re += (*g_pItemOptionTable)[*itr].RequireLevel;
		itr++;
	}

	return re;
}

//----------------------------------------------------------------------
// Get ItemOption ColorSet
//----------------------------------------------------------------------
int					
MItem::GetItemOptionRequireSUM() const
{	
	int re = 0;

	std::list<TYPE_ITEM_OPTION>::const_iterator itr = m_ItemOptionList.begin();

	while(itr != m_ItemOptionList.end())
	{
		re += (*g_pItemOptionTable)[*itr].RequireSUM;
		itr++;
	}

	return re;
}

//----------------------------------------------------------------------
// Get Require STR
//----------------------------------------------------------------------
BYTE					
MItem::GetRequireSTR() const
{
	int original = (*g_pItemTable)[GetItemClass()][m_ItemType].GetRequireSTR();
	int maxValue = 0;

	if (original==0 || IsQuestItem() )
	{
		return 0;
	}

	if( original <= MAX_SLAYER_ATTR_OLD)
		maxValue = MAX_SLAYER_ATTR_OLD;
	else
		maxValue = MAX_SLAYER_ATTR;
	
	original += (GetItemOptionRequireSUM()<<1);

	if( IsOustersItem() )
		return original;
	
	return min(original, maxValue);
	
	// option�� ���� ����ġ
	//return max(original, GetItemOptionRequireSTR());
		//(*g_pItemOptionTable)[m_ItemOption].PlusRequireAbility;
}

//----------------------------------------------------------------------
// Get Require DEX
//----------------------------------------------------------------------
BYTE					
MItem::GetRequireDEX() const
{
	int original = (*g_pItemTable)[GetItemClass()][m_ItemType].GetRequireDEX();
	int maxValue = 0;

	if (original==0 || IsQuestItem() )
	{
		return 0;
	}

	if( original <= MAX_SLAYER_ATTR_OLD )
		maxValue = MAX_SLAYER_ATTR_OLD;
	else
		maxValue = MAX_SLAYER_ATTR;

	original += (GetItemOptionRequireSUM()<<1);
	
	if( IsOustersItem() )
		return original;

	return min(original, maxValue);

	// option�� ���� ����ġ
	//return max(original, GetItemOptionRequireDEX());
	//+ (*g_pItemOptionTable)[m_ItemOption].PlusRequireAbility;
}

//----------------------------------------------------------------------
// Get Require INT
//----------------------------------------------------------------------
BYTE					
MItem::GetRequireINT() const
{
	int original = (*g_pItemTable)[GetItemClass()][m_ItemType].GetRequireINT();
	int maxValue = 0;

	if (original==0 || IsQuestItem() )
	{
		return 0;
	}

	if( original <= MAX_SLAYER_ATTR_OLD)
		maxValue = MAX_SLAYER_ATTR_OLD;
	else
		maxValue = MAX_SLAYER_ATTR;

	original += (GetItemOptionRequireSUM()<<1);

	if( IsOustersItem() )
		return original;

	return min(original, maxValue);

	// option�� ���� ����ġ
	//return max(original, GetItemOptionRequireINT());
	//+ (*g_pItemOptionTable)[m_ItemOption].PlusRequireAbility;
}

//----------------------------------------------------------------------
// Get Require SUM
//----------------------------------------------------------------------
WORD					
MItem::GetRequireSUM() const
{
	int original = (*g_pItemTable)[GetItemClass()][m_ItemType].GetRequireSUM();
	int maxValue = 0;

	if (original==0 || IsQuestItem() )
	{
		return 0;
	}
	if( original <= MAX_SLAYER_ATTR_SUM_OLD )
		maxValue = MAX_SLAYER_ATTR_SUM_OLD;
	else
		maxValue = MAX_SLAYER_ATTR_SUM;
	original += GetItemOptionRequireSUM();

	if( IsOustersItem() )
		return original;

	return min(original, maxValue);

	// option�� ���� ����ġ
	//return max(original, GetItemOptionRequireSUM());
	//+ (*g_pItemOptionTable)[m_ItemOption].PlusRequireAbility;
}

//----------------------------------------------------------------------
// Get Require Level
//----------------------------------------------------------------------
BYTE					
MItem::GetRequireLevel() const
{
	int original = (*g_pItemTable)[GetItemClass()][m_ItemType].GetRequireLevel();
	int maxValue = 0;
	
	if(original == 0 || IsQuestItem() )
		return 0;

	if( original <= 100 )
		maxValue = MAX_VAMPIRE_LEVEL_OLD;
	else
		maxValue = MAX_VAMPIRE_LEVEL;

	// option�� ���� ����ġ
	original += GetItemOptionRequireLevel();

	if( IsOustersItem() )
		return original;

	return min(original, maxValue);
	//return max(original, GetItemOptionRequireLevel());
	//+ (*g_pItemOptionTable)[m_ItemOption].PlusRequireAbility;
}

//----------------------------------------------------------------------
// Get UseActionInfo
//----------------------------------------------------------------------
TYPE_ACTIONINFO 
MItem::GetUseActionInfo() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].UseActionInfo;
}

//----------------------------------------------------------------------
// Get Original Speed
//----------------------------------------------------------------------
int			
MItem::GetOriginalSpeed() const
{
	return (*g_pItemTable)[GetItemClass()][m_ItemType].Value7;
}

//----------------------------------------------------------------------
// Get Speed
//----------------------------------------------------------------------
int
MItem::GetSpeed() const		
{ 
	return m_Speed; 
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
/*
void	
MItem::SaveToFile(ofstream& file)
{
	MObject::SaveToFile(file);		
	file.write((const char*)&m_SpriteID, SIZE_SPRITEID);	
}
		
//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void	
MItem::LoadFromFile(ifstream& file)
{
	MObject::LoadFromFile(file);
	file.read((char*)&m_SpriteID, SIZE_SPRITEID);	
}
*/

//----------------------------------------------------------------------
// Set Dropping
//----------------------------------------------------------------------
void		
MItem::SetDropping()
{
	TYPE_FRAMEID dropID = GetDropFrameID();
	// ���õ� frame�� ���� ���
	if (dropID==FRAMEID_NULL)
	{
		return;
	}

#ifdef __GAME_CLIENT__
	CAnimationFrame::SetFrameID( dropID, g_pTopView->m_ItemDropFPK[dropID].GetSize() );
#endif

	m_DropCount = 0;
	m_bDropping = TRUE;
}

//----------------------------------------------------------------------
// Next Drop Frame
//----------------------------------------------------------------------
void		
MItem::NextDropFrame()
{
	CAnimationFrame::NextFrame();

	if (++m_DropCount >= MAX_DROP_COUNT)
	{
		m_CurrentFrame = m_MaxFrame - 1;	// ������ frame����..
		m_DropCount--;						// �ϳ� ����� �ϴ� �� - -;
		m_bDropping = FALSE;
	}
}


void
MItem::RemoveItemOption(TYPE_ITEM_OPTION option)
{
	std::list<TYPE_ITEM_OPTION>::iterator itr = std::find(m_ItemOptionList.begin(), m_ItemOptionList.end(), option);

	if(itr != m_ItemOptionList.end())
		m_ItemOptionList.erase(itr);
}

void							
MItem::AddItemOption(TYPE_ITEM_OPTION option)
{
	if(option == 0)
		return;

	m_ItemOptionList.push_back(option);
}

void							
MItem::ChangeItemOption(TYPE_ITEM_OPTION ori_option, TYPE_ITEM_OPTION new_option)
{
	if(new_option == 0)
		RemoveItemOption(ori_option);

	std::list<TYPE_ITEM_OPTION>::iterator itr = std::find(m_ItemOptionList.begin(), m_ItemOptionList.end(), ori_option);

	if(itr != m_ItemOptionList.end())
	{
		*itr = new_option;
	}
}

// ����ũ ������ �����ϴ°�
int
MItem::GetUniqueItemColorset()
{
	int grade = g_CurrentFrame%28;	// 15*2-2
	if(grade > 14)
		grade = 28-grade;
	return g_pClientConfig->UniqueItemColorSet+grade;
}

int
MItem::GetQuestItemColorset()
{
	int grade = g_CurrentFrame % 28;

	if ( grade > 14 )
		grade = 28 - grade;
	
	return g_pClientConfig->QuestItemColorSet+grade;
}

int					
MItem::GetSpecialColorItemColorset()
{
	if(IsQuestItem() )
	{
		return GetQuestItemColorset();
	} else
	if(IsUniqueItem() )
	{
		return GetUniqueItemColorset();
	}
	
	return 0xffff;
}

int					
MItem::GetSpecialColorItemColorset(unsigned short srcColor)
{
	switch( srcColor )
	{
	case UNIQUE_ITEM_COLOR :
		return GetUniqueItemColorset();
		break;
	case QUEST_ITEM_COLOR :
		return GetQuestItemColorset();
		break; 
	}
	
	return 0xffff;	
}

// ���� ������ �����ϴ°�
int	MItem::GetRareItemColorset()
{
/*
	int ColorSet = g_CurrentFrame % (28*GetItemOptionListCount());
	int percent = g_CurrentFrame%28;

	ColorSet = GetItemOptionColorSet(ColorSet/28);
	int grade = ColorSet%15;
	ColorSet = ColorSet - grade;

	if(percent > 14)
		percent = 28 - percent;
*/

	return GetItemOptionColorSet();//ColorSet+grade;//*percent/14;
}

//----------------------------------------------------------------------
//
//						MCorpse
// 
//----------------------------------------------------------------------
MCorpse::MCorpse()
{ 
	m_pCreature=NULL; 
}

MCorpse::~MCorpse() 
{ 
#ifdef __GAME_CLIENT__
	if (m_pCreature!=NULL) 
	{		
		delete m_pCreature; 		
	}
#endif
}


//----------------------------------------------------------------------
//
//						MBelt
// 
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Set ItemType
//----------------------------------------------------------------------
// ItemType�� �����Ҷ� SlotItemManager�� �ʱ�ȭ�ؾ��Ѵ�.
//----------------------------------------------------------------------
void				
MBelt::SetItemType(TYPE_ITEMTYPE type)		
{ 
	m_ItemType = type; 

	MSlotItemManager::Init( GetPocketNumber() );
}

//----------------------------------------------------------------------
// AddItem ( pItem )
//----------------------------------------------------------------------
// ������ slot�� pItem�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MBelt::AddItem(MItem* pItem)
{
	//---------------------------------------------------------------
	// ����ִ� slot�� ã�Ƽ� item�� �߰��Ѵ�.
	//---------------------------------------------------------------
	for (int n=0; n<m_Size; n++)
	{
		if (m_ItemSlot[n]==NULL)
		{
			return AddItem( pItem, n );
		}
	}

	return false;
}

//----------------------------------------------------------------------
// AddItem ( pItem, n )
//----------------------------------------------------------------------
// slot(n)�� pItem�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MBelt::AddItem(MItem* pItem, BYTE n)
{
	if (n >= m_Size)
	{
		return false;
	}

	//---------------------------------------------------------------
	// Quick item�̾���� belt�� �߰��� �� �ִ�.
	//---------------------------------------------------------------
	if (pItem->IsQuickItem())
	{
		return MSlotItemManager::AddItem( pItem, n );
	}

	return false;	
}

//----------------------------------------------------------------------
// ReplaceItem
//----------------------------------------------------------------------
// pItem�� �߰��ϰ� ���� �ִٸ� Item��ȯ
//----------------------------------------------------------------------
bool			
MBelt::ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	if (n >= m_Size || pItem == NULL)
	{
		return false;
	}

	//---------------------------------------------------------------
	// ��� �ִ� slot�̸� �׳� �߰�
	//---------------------------------------------------------------
	if (m_ItemSlot[n]==NULL)
	{
		return AddItem( pItem, n );
	}
	
	//---------------------------------------------------------------
	// ���� �ִٸ� replace�ؾ� �Ѵ�.
	// �ٲܷ��� Item�� quickItem�� ��츸 ��ü..
	//---------------------------------------------------------------	
	if (pItem->IsQuickItem())
	{
		return MSlotItemManager::ReplaceItem( pItem, n, pOldItem );
	}

	return false;
}


//----------------------------------------------------------------------
// Can ReplaceItem : (n) slot�� pItem�� �߰��ϰų� 
//						���� �ִ� Item�� ��ü�� �����Ѱ�?
//----------------------------------------------------------------------
bool			
MBelt::CanReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size)
	{		
		// NULL�� �����Ѵ�.
		pOldItem = NULL;

		return false;
	}

	//---------------------------------------------------------	
	// QuickItem�ΰ�?
	//---------------------------------------------------------	
	if (pItem->IsQuickItem())
	{		
		pOldItem = m_ItemSlot[n];

		return true;
	}

	pOldItem = NULL;

	return false;
}

//----------------------------------------------------------------------
// Find Slot To Add Item
//----------------------------------------------------------------------
// return���� �ڸ��� �ִ���(true) / ������(false)
// true�� ��쿡.. pItem�� �� �� �ִ� �ڸ��� slot�̴�.
//----------------------------------------------------------------------
bool			
MBelt::FindSlotToAddItem(MItem* pItem, int &slot) const
{
	if (!pItem->IsQuickItem())
	{
		return false;
	}

	//---------------------------------------------------------
	// ��� �� �� ������?
	//---------------------------------------------------------
	for (int i=0; i<m_Size; i++)
	{
		const MItem* pQuickItem = m_ItemSlot[i];

		//---------------------------------------------------------
		// �ƹ��͵� ���� ���̸� �׳� ������ �ȴ�.
		//---------------------------------------------------------
		if (pQuickItem==NULL)
		{
			slot = i;
			return true;
		}
		//---------------------------------------------------------
		// ���� ������.. �װ��� ���� �� �ִ��� �˾ƺ���.
		//---------------------------------------------------------
		if (pQuickItem->GetItemClass()==pItem->GetItemClass()
			&& pQuickItem->GetItemType()==pItem->GetItemType())
		{
			//----------------------------------------------------
			// ���� ������ max�� ���� �ʾƾ� �Ѵ�.
			//----------------------------------------------------
			int addTotal = pQuickItem->GetNumber() + pItem->GetNumber();

			if ( addTotal <= pQuickItem->GetMaxNumber() )
			{
				slot = i;
				return true;
			}
		}		
	}

	// �� ���� ����.
	return false;
}

//----------------------------------------------------------------------
//
//						MMagazine
// 
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Is Insert To Item
//----------------------------------------------------------------------
// �ٸ� Item�� �߰��� �� �ִ°�?
//----------------------------------------------------------------------
bool		
MMagazine::IsInsertToItem(const MItem* pItem) const
{
	if (pItem==NULL)
	{
		return false;
	}

	//------------------------------------------------
	// ���� ���
	//------------------------------------------------
	if (pItem->IsGunItem())
	{
		// �� źâ�� ������ �� �ִ� ���� ���..
		if (GetGunClass()==pItem->GetItemClass())
		{
			return true;
		}

		return false;
	}
	
	// ���� źâ�� ��� üũ..
	return MItem::IsInsertToItem( pItem );	
}

//----------------------------------------------------------------------
// 
//						MSlayer PortalItem
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Get MaxNumber - Charge����
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MSlayerPortalItem::GetMaxNumber() const
{
	return (*g_pItemTable)[ITEM_CLASS_SLAYER_PORTAL_ITEM][m_ItemType].MaxNumber;
}

//----------------------------------------------------------------------
// Set EnchantLevel
// �����δ� Charge ������ �����Ѵ�.
//----------------------------------------------------------------------
void				
MSlayerPortalItem::SetEnchantLevel(WORD s)
{
	m_Number = s;
}

//----------------------------------------------------------------------
// 
//						MVampire PortalItem
//
//----------------------------------------------------------------------
MVampirePortalItem::MVampirePortalItem()
{ 
	m_Number = 0; 

	m_ZoneID = 0;//OBJECTID_NULL;
	m_ZoneX = SECTORPOSITION_NULL;
	m_ZoneY = SECTORPOSITION_NULL;
}

//----------------------------------------------------------------------
// Is Marked
//----------------------------------------------------------------------
bool				
MVampirePortalItem::IsMarked() const
{
	return m_ZoneID!=0 && m_ZoneID!=OBJECTID_NULL;
}

//----------------------------------------------------------------------
// Get MaxNumber - Charge����
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MVampirePortalItem::GetMaxNumber() const
{
	return (*g_pItemTable)[ITEM_CLASS_VAMPIRE_PORTAL_ITEM][m_ItemType].MaxNumber;
}

//----------------------------------------------------------------------
// Set Zone
//----------------------------------------------------------------------
void				
MVampirePortalItem::SetZone(int zoneID, TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y)
{
	m_ZoneID	= zoneID;
	m_ZoneX		= x;
	m_ZoneY		= y;
}

//----------------------------------------------------------------------
// Set EnchantLevel
// �����δ� Charge ������ �����Ѵ�.
//----------------------------------------------------------------------
void				
MVampirePortalItem::SetEnchantLevel(WORD s)
{
	m_Number = s;
}

//----------------------------------------------------------------------
// Set Silver
//----------------------------------------------------------------------
void				
MVampirePortalItem::SetSilver(int s)
{
	m_ZoneID = s;
}

//----------------------------------------------------------------------
// Set Current Durability
//----------------------------------------------------------------------
void				
MVampirePortalItem::SetCurrentDurability(TYPE_ITEM_DURATION d)
{
	m_ZoneX = (d >> 8) & 0xFF;		// 0xFF�� ��� �� ��..
	m_ZoneY = (d & 0xFF);
}

//----------------------------------------------------------------------
// Get Max Number
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MEventStarItem::GetMaxNumber() const
{
	return MAX_EVENT_STAR_PILE_NUMBER;
}

//----------------------------------------------------------------------
// Get Max Number
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MPetEnchantItem::GetMaxNumber() const
{
	return MAX_PET_ENCHANT_PILE_NUMBER;
}

//----------------------------------------------------------------------
// Get Max Number
//----------------------------------------------------------------------
TYPE_ITEM_NUMBER	
MPetFood::GetMaxNumber() const
{
	return MAX_PET_FOOD_PILE_NUMBER;
}
TYPE_ITEM_NUMBER	
MItemETC::GetMaxNumber() const
{
	return MAX_RESURRECT_SCROLL_NUMBER;
}

TYPE_ITEM_NUMBER
MResurrectItem::GetMaxNumber() const
{
	return MAX_RESURRECT_SCROLL_NUMBER;
}

TYPE_ITEM_NUMBER
MMixingItem::GetMaxNumber() const 
{
	return MAX_MIXING_ITEM_NUMBER;
}

//----------------------------------------------------------------------
// Is BombMaterial
//----------------------------------------------------------------------
// �̰Ŵ� ���߿� �ʻ�~������ �ʿ��ϴ�.
// BombMaterial�� member�� �ֵ���.. 
// Bomb / Mine Material�� �и��ϵ���....
//----------------------------------------------------------------------
bool
IsBombMaterial(const MItem* pItem)
{
	return pItem->GetItemClass()==ITEM_CLASS_BOMB_MATERIAL
			&& pItem->GetItemType() <= 4;
}

//----------------------------------------------------------------------
// Is MineMaterial
//----------------------------------------------------------------------
// �̰Ŵ� ���߿� �ʻ�~������ �ʿ��ϴ�.
// BombMaterial�� member�� �ֵ���.. 
// Bomb / Mine Material�� �и��ϵ���....
//----------------------------------------------------------------------
bool
IsMineMaterial(const MItem* pItem)
{
	return pItem->GetItemClass()==ITEM_CLASS_BOMB_MATERIAL
			&& pItem->GetItemType() >= 5;
}

TYPE_ITEM_NUMBER
MOustersSummonGem::GetMaxNumber() const 
{
	return (*g_pItemTable)[ITEM_CLASS_OUSTERS_SUMMON_ITEM][m_ItemType].MaxNumber;
}

TYPE_ITEM_NUMBER
MOustersLarva::GetMaxNumber() const
{
	return MAX_OUSTERS_LARVA_NUMBER;
}

TYPE_ITEM_NUMBER
MOustersPupa::GetMaxNumber() const
{
	return MAX_OUSTERS_LARVA_NUMBER;
}

TYPE_ITEM_NUMBER
MOustersComposMei::GetMaxNumber() const
{
	return MAX_OUSTERS_LARVA_NUMBER;
}

//----------------------------------------------------------------------
// Set EnchantLevel
// �����δ� Charge ������ �����Ѵ�.
//----------------------------------------------------------------------
void				
MOustersSummonGem::SetEnchantLevel(WORD s)
{
	m_Number = s;
}
//----------------------------------------------------------------------
//
//						MOustersArmsBand
// 
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Set ItemType
//----------------------------------------------------------------------
// ItemType�� �����Ҷ� SlotItemManager�� �ʱ�ȭ�ؾ��Ѵ�.
//----------------------------------------------------------------------
void				
MOustersArmsBand::SetItemType(TYPE_ITEMTYPE type)		
{ 
	m_ItemType = type; 

	MSlotItemManager::Init( GetPocketNumber() );
}

//----------------------------------------------------------------------
// AddItem ( pItem )
//----------------------------------------------------------------------
// ������ slot�� pItem�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MOustersArmsBand::AddItem(MItem* pItem)
{
	//---------------------------------------------------------------
	// ����ִ� slot�� ã�Ƽ� item�� �߰��Ѵ�.
	//---------------------------------------------------------------
	for (int n=0; n<m_Size; n++)
	{
		if (m_ItemSlot[n]==NULL)
		{
			return AddItem( pItem, n );
		}
	}

	return false;
}

//----------------------------------------------------------------------
// AddItem ( pItem, n )
//----------------------------------------------------------------------
// slot(n)�� pItem�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MOustersArmsBand::AddItem(MItem* pItem, BYTE n)
{
	if (n >= m_Size)
	{
		return false;
	}

	//---------------------------------------------------------------
	// Quick item�̾���� belt�� �߰��� �� �ִ�.
	//---------------------------------------------------------------
	if (pItem->IsQuickItem())
	{
		return MSlotItemManager::AddItem( pItem, n );
	}

	return false;	
}

//----------------------------------------------------------------------
// ReplaceItem
//----------------------------------------------------------------------
// pItem�� �߰��ϰ� ���� �ִٸ� Item��ȯ
//----------------------------------------------------------------------
bool			
MOustersArmsBand::ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	if (n >= m_Size || pItem == NULL)
	{
		return false;
	}

	//---------------------------------------------------------------
	// ��� �ִ� slot�̸� �׳� �߰�
	//---------------------------------------------------------------
	if (m_ItemSlot[n]==NULL)
	{
		return AddItem( pItem, n );
	}
	
	//---------------------------------------------------------------
	// ���� �ִٸ� replace�ؾ� �Ѵ�.
	// �ٲܷ��� Item�� quickItem�� ��츸 ��ü..
	//---------------------------------------------------------------	
	if (pItem->IsQuickItem())
	{
		return MSlotItemManager::ReplaceItem( pItem, n, pOldItem );
	}

	return false;
}


//----------------------------------------------------------------------
// Can ReplaceItem : (n) slot�� pItem�� �߰��ϰų� 
//						���� �ִ� Item�� ��ü�� �����Ѱ�?
//----------------------------------------------------------------------
bool			
MOustersArmsBand::CanReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size)
	{		
		// NULL�� �����Ѵ�.
		pOldItem = NULL;

		return false;
	}

	//---------------------------------------------------------	
	// QuickItem�ΰ�?
	//---------------------------------------------------------	
	if (pItem->IsQuickItem())
	{		
		pOldItem = m_ItemSlot[n];

		return true;
	}

	pOldItem = NULL;

	return false;
}

//----------------------------------------------------------------------
// Find Slot To Add Item
//----------------------------------------------------------------------
// return���� �ڸ��� �ִ���(true) / ������(false)
// true�� ��쿡.. pItem�� �� �� �ִ� �ڸ��� slot�̴�.
//----------------------------------------------------------------------
bool			
MOustersArmsBand::FindSlotToAddItem(MItem* pItem, int &slot) const
{
	if (!pItem->IsQuickItem())
	{
		return false;
	}

	//---------------------------------------------------------
	// ��� �� �� ������?
	//---------------------------------------------------------
	for (int i=0; i<m_Size; i++)
	{
		const MItem* pQuickItem = m_ItemSlot[i];

		//---------------------------------------------------------
		// �ƹ��͵� ���� ���̸� �׳� ������ �ȴ�.
		//---------------------------------------------------------
		if (pQuickItem==NULL)
		{
			slot = i;
			return true;
		}
		//---------------------------------------------------------
		// ���� ������.. �װ��� ���� �� �ִ��� �˾ƺ���.
		//---------------------------------------------------------
		if (pQuickItem->GetItemClass()==pItem->GetItemClass()
			&& pQuickItem->GetItemType()==pItem->GetItemType())
		{
			//----------------------------------------------------
			// ���� ������ max�� ���� �ʾƾ� �Ѵ�.
			//----------------------------------------------------
			int addTotal = pQuickItem->GetNumber() + pItem->GetNumber();

			if ( addTotal <= pQuickItem->GetMaxNumber() )
			{
				slot = i;
				return true;
			}
		}		
	}

	// �� ���� ����.
	return false;
}

TYPE_ITEM_NUMBER	
MEffectItem::GetMaxNumber() const	
{ 
	return MAX_EFFECT_ITEM_NUMBER; 
}

TYPE_ITEM_NUMBER		
MMoonCardItem::GetMaxNumber() const
{
	return MAX_MOON_CARD_NUMBER;	
}

TYPE_ITEM_NUMBER		
MLuckyBag::GetMaxNumber() const
{
	return MAX_LUCKY_BAG_NUMBER;	
}





///////////////////////////////////////////////////////////////////////////
//
//	Item Use
//
///////////////////////////////////////////////////////////////////////////
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MUsePotionItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MUsePotionItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	CGUsePotionFromInventory _CGUsePotionFromInventory;
	_CGUsePotionFromInventory.setObjectID( GetID() );
	_CGUsePotionFromInventory.setX( GetGridX() );
	_CGUsePotionFromInventory.setY( GetGridY() );

	g_pSocket->sendPacket( &_CGUsePotionFromInventory );

	
	// �ϴ�(!) �׳� ���ְ� ����.
	//(*g_pInventory).RemoveItem( pItem->GetID() );

	//----------------------------------------------------
	// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
	//----------------------------------------------------
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MWater::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MWater::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	bool bUseOK = false;
	bool bCreateHolyWater = GetItemType() >= 0 && GetItemType() <= 2;
	bool bCreateHolyPotion = GetItemType() >= 3 && GetItemType() <= 6;

	TYPE_ACTIONINFO useSkill = ACTIONINFO_NULL;

	if( bCreateHolyWater )
		useSkill = MAGIC_CREATE_HOLY_WATER;
	else if (bCreateHolyPotion )
		useSkill = SKILL_CREATE_HOLY_POTION;

	if ( useSkill != ACTIONINFO_NULL && 
		g_pSkillAvailable->IsEnableSkill( (ACTIONINFO) useSkill ) &&
		(*g_pSkillInfoTable)[useSkill].IsAvailableTime() )
	{
		bUseOK = true;
	}

	//----------------------------------------------------
	// skill�� ����� ������ ���
	//----------------------------------------------------
	if (bUseOK)//playerSkill < (*g_pActionInfoTable).GetMinResultActionInfo())
	{
		//if ((*g_pActionInfoTable)[playerSkill].IsTargetItem())
		{
			//----------------------------------------------------
			// ���� ������ ���� ���..
			//----------------------------------------------------
			if (!g_pPlayer->IsWaitVerify()
				&& g_pPlayer->IsItemCheckBufferNULL())							
			{	
				POINT fitPoint;			// ������ �� �ڸ�

				if( bCreateHolyWater )
				{
//								if (GetMakeItemFitPosition(pItem, 
//															ITEM_CLASS_HOLYWATER, 
//															pItem->GetItemType(), 
//															fitPoint))
					{
						CGSkillToInventory _CGSkillToInventory;
						_CGSkillToInventory.setObjectID( GetID() );
						_CGSkillToInventory.setX( GetGridX() );
						_CGSkillToInventory.setY( GetGridY() );
						_CGSkillToInventory.setTargetX( GetGridX() );
						_CGSkillToInventory.setTargetY( GetGridY() );
						_CGSkillToInventory.setSkillType( useSkill );

						g_pSocket->sendPacket( &_CGSkillToInventory );								
					
						// �ϴ�(!) �׳� ���ְ� ����.
						//(*g_pInventory).RemoveItem( pItem->GetID() );

						//----------------------------------------------------
						// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
						//----------------------------------------------------
						g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_SKILL_SUCCESS );
						g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY );								

						(*g_pSkillInfoTable)[useSkill].SetNextAvailableTime();

						//----------------------------------------------------
						// ��� ��� �õ� ����
						//----------------------------------------------------
						AddNewInventoryEffect( GetID(),
											useSkill, //+ (*g_pActionInfoTable).GetMinResultActionInfo(),
											g_pClientConfig->FPS*3	// 3��
										);
					}
//								else
//								{
//									// g_pGameMessage( "�ڸ��� ������~" );
//								}
				}
				else if (bCreateHolyPotion )
				{
					if (GetMakeItemFitPosition(this, 
												ITEM_CLASS_POTION, 
												(*g_pItemTable)[GetItemClass()][GetItemType()].Value3 , 
												fitPoint))
					{
						CGSkillToInventory _CGSkillToInventory;

						_CGSkillToInventory.setObjectID( GetID() );
						_CGSkillToInventory.setObjectID( GetID() );
						_CGSkillToInventory.setX( GetGridX() );
						_CGSkillToInventory.setY( GetGridY() );
						_CGSkillToInventory.setTargetX( fitPoint.x );
						_CGSkillToInventory.setTargetY( fitPoint.y );
						_CGSkillToInventory.setSkillType( useSkill );

						g_pSocket->sendPacket( &_CGSkillToInventory );

						g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_SKILL_SUCCESS );
						g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY );
						
						(*g_pSkillInfoTable)[useSkill].SetNextAvailableTime();
						
						AddNewInventoryEffect( GetID(),
							useSkill,
							g_pClientConfig->FPS*3
							);
					}
					else
					{
					}
				}						
			}
		}
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MMagazine::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MMagazine::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	bool		bPossible = false;

	int value = (*g_pItemTable)[ GetItemClass() ][ GetItemType() ].Value3;

	if( value <= 0 )
		bPossible = true;
	else
	{
		if( value > 0 && value < g_pActionInfoTable->GetSize() )
			bPossible = g_pSkillAvailable->IsEnableSkill( (ACTIONINFO) value );
	}

	if( bPossible == false )
	{
		g_pSystemMessage->Add((*g_pGameStringTable)[UI_STRING_MESSAGE_CANNOT_RELOAD_BY_VIVID_MAGAZINE].GetString() );
		return;
	}

	const MItem* pHandItem = (*g_pSlayerGear).GetItem( MSlayerGear::GEAR_SLAYER_RIGHTHAND );

	if (pHandItem!=NULL && pHandItem->IsGunItem())
	{
		const MGunItem* pGunItem = (const MGunItem*)pHandItem;

		// ���� �ѿ� ������ �� �ִ� źâ�ΰ�?
		if (IsInsertToItem( pGunItem ))	
		{
			CGReloadFromInventory _CGReloadFromInventory;
			_CGReloadFromInventory.setObjectID( GetID() );
			_CGReloadFromInventory.setX( GetGridX() );
			_CGReloadFromInventory.setY( GetGridY() );

			g_pSocket->sendPacket( &_CGReloadFromInventory );

			
			// �ϴ�(!) �׳� ���ְ� ����.
			//(*g_pInventory).RemoveItem( GetID() );

			//----------------------------------------------------
			// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
			//----------------------------------------------------
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
		}
		else
		{
			// [����] �Ѿ��� �� �´� ���
//			__BEGIN_HELP_EVENT
//				ExecuteHelpEvent( HE_ITEM_DIFFERENT_BULLET_TYPE );
//			__END_HELP_EVENT

			DEBUG_ADD("Magazine is not fit to Gun");
		}
	}
	else
	{
		DEBUG_ADD("Weapon is not Gun");
	}
#endif
}

void	MMagazine::UseQuickItem()
{
#ifdef __GAME_CLIENT__
	const MItem* pHandItem = (*g_pSlayerGear).GetItem( MSlayerGear::GEAR_SLAYER_RIGHTHAND );

	if (pHandItem!=NULL && pHandItem->IsGunItem())
	{
		const MGunItem* pGunItem = (const MGunItem*)pHandItem;

		//----------------------------------------------------
		// ���� �ѿ� ������ �� �ִ� źâ�ΰ�?
		//----------------------------------------------------
		if (IsInsertToItem( pGunItem ))	
		{
			CGReloadFromQuickSlot _CGReloadFromQuickSlot;
			_CGReloadFromQuickSlot.setObjectID( GetID() );
			_CGReloadFromQuickSlot.setSlotID( GetItemSlot() );							

			g_pSocket->sendPacket( &_CGReloadFromQuickSlot );

			
			//----------------------------------------------------
			// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
			//----------------------------------------------------
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);

			//----------------------------------------------------
			// ��Ʈ �� ���ֵ���..
			//----------------------------------------------------
			UI_LockGear();

//			__BEGIN_HELP_EVENT
//				// [����] źâ ���
//				ExecuteHelpEvent( HE_ITEM_USE_MAGAZINE );	
//				// [����] ��Ʈ�� ������ ���
//				ExecuteHelpEvent( HE_ITEM_USE_BELT_ITEM );	
//			__END_HELP_EVENT
		}
		else
		{
			// [����] �Ѿ��� �� �´� ���
//			__BEGIN_HELP_EVENT
//				ExecuteHelpEvent( HE_ITEM_DIFFERENT_BULLET_TYPE );
//			__END_HELP_EVENT

			PlaySound( SOUND_ITEM_NO_MAGAZINE );

			// źâ�� �� �´� ���
			DEBUG_ADD("[Can't use Magazine] Wrong Magazine");
		}
	}
	else
	{
		//PlaySound( SOUND_ITEM_NO_MAGAZINE );

		// ���� ���� ���
		DEBUG_ADD("[Can't use Magazine] No Gun");
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MBombMaterial::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MBombMaterial::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	//int playerSkill = g_pPlayer->GetSpecialActionInfo();
	bool bUseOK = false;

	int currentItemType = GetItemType();

	ACTIONINFO			useSkill;
	ITEM_CLASS	itemClass;
	int					itemType;

	//-------------------------------------------
	// ��ź�̳� ���ڳ�...
	//-------------------------------------------
	// �ϵ��ڵ� -_-;
	//-------------------------------------------
	if (currentItemType < 5)
	{
		useSkill	= SKILL_MAKE_BOMB;
		itemClass	= ITEM_CLASS_BOMB;
		itemType	= currentItemType;
	}
	else
	{
		useSkill	= SKILL_MAKE_MINE;
		itemClass	= ITEM_CLASS_MINE;
		itemType	= currentItemType - 5;
	}

	if (g_pSkillAvailable->IsEnableSkill( useSkill )
		&& (*g_pSkillInfoTable)[useSkill].IsAvailableTime())
	{
		bUseOK = true;
	}

	//----------------------------------------------------
	// skill�� ����� ������ ���
	//----------------------------------------------------
	if (bUseOK)//playerSkill < (*g_pActionInfoTable).GetMinResultActionInfo())
	{				
		//----------------------------------------------------
		// ���� ������ ���� ���..
		//----------------------------------------------------
		if (!g_pPlayer->IsWaitVerify()
			&& g_pPlayer->IsItemCheckBufferNULL())							
		{	
			POINT fitPoint;			// ��ź�� �� �ڸ�						
			
			if (GetMakeItemFitPosition(this, itemClass, itemType, fitPoint))
			{
				CGSkillToInventory _CGSkillToInventory;
				_CGSkillToInventory.setObjectID( GetID() );
				_CGSkillToInventory.setX( GetGridX() );
				_CGSkillToInventory.setY( GetGridY() );
				_CGSkillToInventory.setTargetX( fitPoint.x );
				_CGSkillToInventory.setTargetY( fitPoint.y );
				_CGSkillToInventory.setSkillType( useSkill );

				g_pSocket->sendPacket( &_CGSkillToInventory );								
			
				// �ϴ�(!) �׳� ���ְ� ����.
				//(*g_pInventory).RemoveItem( GetID() );

				//----------------------------------------------------
				// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
				//----------------------------------------------------
				g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_SKILL_SUCCESS );
				g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY );

				// ����� �õ� �߿� �̹� delay��ŭ �ð��� ������.
				//(*g_pSkillInfoTable)[useSkill].SetNextAvailableTime();

				//----------------------------------------------------
				// ��� ��� �õ� ����
				//----------------------------------------------------
				AddNewInventoryEffect( GetID(),
									useSkill, //+ (*g_pActionInfoTable).GetMinResultActionInfo(),
									g_pClientConfig->FPS*3	// 3��
								);
			}
			else
			{
				// g_pGameMessage( "�ڸ��� ������~" );
			}
		}
	}
#endif
}

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MMoney::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MMoney::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	// 2�� �̻� �־�� �и� �ȴ�.
	if(GetNumber() > 1)
	{
		// ������ �и�
		CGAddInventoryToMouse _CGAddInventoryToMouse;
		_CGAddInventoryToMouse.setObjectID( 0 );	// �и��Ѵٴ� �ǹ�
		_CGAddInventoryToMouse.setX( GetGridX() );
		_CGAddInventoryToMouse.setY( GetGridY() );
		
		g_pSocket->sendPacket( &_CGAddInventoryToMouse );				
		
		//----------------------------------------------------
		// Inventory���� item�� � ��� �� �����޴´�.
		// �ϴ��� 1���� �鸮���� �Ѵ�.
		//----------------------------------------------------
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY);
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MMine::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MMine::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	bool bUseOK = true;
	ACTIONINFO useSkill;					
		
	//----------------------------------------------------
	// ��밡���Ѱ�?
	//----------------------------------------------------			
	useSkill = SKILL_INSTALL_MINE;					

	if (//g_pPlayer->GetSpecialActionInfo()==useSkill ||
		g_pSkillAvailable->IsEnableSkill( useSkill )
		&& (*g_pSkillInfoTable)[useSkill].IsAvailableTime()
		&& g_pPlayer->GetMoveDevice() != MCreature::MOVE_DEVICE_RIDE)
	{
		bUseOK = true;
	}
	else
	{
		bUseOK = false;
	}			

	if (bUseOK)
	{
		CGSkillToInventory _CGSkillToInventory;
		_CGSkillToInventory.setObjectID( GetID() );
		_CGSkillToInventory.setX( GetGridX() );
		_CGSkillToInventory.setY( GetGridY() );
		// ���� �ɴ� ����
		_CGSkillToInventory.setTargetX( g_pPlayer->GetDirection() );
		_CGSkillToInventory.setSkillType( useSkill );

		g_pSocket->sendPacket( &_CGSkillToInventory );
		
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);

		g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_SKILL_SUCCESS );
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY );

		(*g_pSkillInfoTable)[useSkill].SetNextAvailableTime();

		//----------------------------------------------------
		// ��� ��� �õ� ����
		//----------------------------------------------------
		/*
		if (useSkill == MAGIC_BLOODY_MARK)
		{
			AddNewInventoryEffect( GetID(),
								useSkill,
								14
							);
		}
		*/
	
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MSlayerPortalItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MSlayerPortalItem::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	if(g_bHolyLand == false					// ������ �ƴϾ�� �ϰ�
		&& g_pZoneTable->Get( g_pZone->GetID() )->CannotUseSpecialItem == false		// ���� ���� ����� �������� ����� �� �־�� �ϰ�
		&& IsAffectStatus()						// ���� �����ؾ� �ϰ�
		&& IsChargeItem() && GetNumber() > 0	// �����������̸� ���ڰ� 0���� Ŀ�� �Ѵ�.
		&& g_pZone->GetHelicopter( g_pPlayer->GetID() ) == NULL// ��⸦ �ҷ����� �ȵȴ�.
		&& !g_pPlayer->HasEffectStatus(EFFECTSTATUS_INSTALL_TURRET))	
	{
		// slayer�� item����ϴ°Ŵ�
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		if(0 != SubInventoryItemID)
			_CGUseItemFromInventory.setInventoryItemObjectID( SubInventoryItemID );
	#else

	#endif
		g_pSocket->sendPacket( &_CGUseItemFromInventory );

		
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MVampirePortalItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MVampirePortalItem::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	if(g_bHolyLand == false					// ������ �ƴϾ�� �ϰ�
		&& g_pZoneTable->Get( g_pZone->GetID() )->CannotUseSpecialItem == false		// ���� ���� ����� �������� ����� �� �־�� �ϰ�
		&& IsAffectStatus()						// ���� �����ؾ� �ϰ�
		&& IsChargeItem() && GetNumber() > 0	// �����������̸� ���ڰ� 0���� Ŀ�� �Ѵ�.
		)
	{
		ACTIONINFO useSkill;					
		
		if (IsMarked())
		{
			useSkill = MAGIC_BLOODY_TUNNEL;
		}
		else
		{
			useSkill = MAGIC_BLOODY_MARK;
		}

		if(g_pSkillAvailable->IsEnableSkill( useSkill )
			&& (*g_pSkillInfoTable)[useSkill].IsAvailableTime())
		{
			// vampire�� ��� ����ϴ°Ŵ�
			CGSkillToInventory _CGSkillToInventory;
			_CGSkillToInventory.setObjectID( GetID() );
			_CGSkillToInventory.setX( GetGridX() );
			_CGSkillToInventory.setY( GetGridY() );
			_CGSkillToInventory.setSkillType( useSkill );
			//_CGSkillToInventory.setCEffectID( 0 );	// -_-;;							

			g_pSocket->sendPacket( &_CGSkillToInventory );
				
			g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_SKILL_SUCCESS );
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY );

			(*g_pSkillInfoTable)[useSkill].SetNextAvailableTime();

			//----------------------------------------------------
			// ��� ��� �õ� ����
			//----------------------------------------------------
			if (useSkill == MAGIC_BLOODY_MARK)
			{
				AddNewInventoryEffect( GetID(),
									useSkill,
									14
								);
			}
		}

	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MEventStarItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MEventStarItem::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	// 2�� �̻� �־�� �и� �ȴ�.
	if(GetNumber() > 1)
	{
		// ������ �и�
		CGAddInventoryToMouse _CGAddInventoryToMouse;
		_CGAddInventoryToMouse.setObjectID( 0 );	// �и��Ѵٴ� �ǹ�
		_CGAddInventoryToMouse.setX( GetGridX() );
		_CGAddInventoryToMouse.setY( GetGridY() );
		
		g_pSocket->sendPacket( &_CGAddInventoryToMouse );				
		
		//----------------------------------------------------
		// Inventory���� item�� � ��� �� �����޴´�.
		// �ϴ��� 1���� �鸮���� �Ѵ�.
		//----------------------------------------------------
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY);
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MMixingItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MMixingItem::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	if( GetItemType() >= 0 && GetItemType() <= 8 )
	{
		if( GetNumber() > 1 )	// ������ �и�
		{
			CGAddInventoryToMouse _CGAddInventoryToMouse;
			_CGAddInventoryToMouse.setObjectID( 0 );
			_CGAddInventoryToMouse.setX( GetGridX() );
			_CGAddInventoryToMouse.setY( GetGridY() );
			
			g_pSocket->sendPacket( &_CGAddInventoryToMouse );
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY );
		}
		else
		{
			C_VS_UI_MIXING_FORGE::FORGE_CLASS fc;
			C_VS_UI_MIXING_FORGE::FORGE_TYPE  ft;
			
			if(GetItemType() >= 0 && GetItemType() <= 2)
			{
				fc = C_VS_UI_MIXING_FORGE::CLASS_WEAPON;
				ft = C_VS_UI_MIXING_FORGE::FORGE_TYPE(C_VS_UI_MIXING_FORGE::TYPE_A + GetItemType());
			} else
			if(GetItemType() >= 3 && GetItemType() <= 5)
			{
				fc = C_VS_UI_MIXING_FORGE::CLASS_ARMOR;
				ft = C_VS_UI_MIXING_FORGE::FORGE_TYPE(C_VS_UI_MIXING_FORGE::TYPE_A + (GetItemType()-3));
			} else
			if(GetItemType() >= 6 && GetItemType() <= 8 )
			{
				fc = C_VS_UI_MIXING_FORGE::CLASS_ACCESSORY;
				ft = C_VS_UI_MIXING_FORGE::FORGE_TYPE(C_VS_UI_MIXING_FORGE::TYPE_A + (GetItemType()-6));
			}
			gC_vs_ui.RunMixingForge(fc,ft);
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_MIXING_ITEM );			
		}
	} else
	if( GetItemType() >= 9 && GetItemType() <= 18 )
	{
		// Puritas �� ��Ŭ���ϸ� �и��Ѵ�.
		CGAddInventoryToMouse _CGAddInventoryToMouse;
		_CGAddInventoryToMouse.setObjectID( 0 );
		_CGAddInventoryToMouse.setX( GetGridX() );
		_CGAddInventoryToMouse.setY( GetGridY() );

		g_pSocket->sendPacket( &_CGAddInventoryToMouse );
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY );
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void MEffectItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void MEffectItem::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	// add by Coffee 2007-8-5 
	if (GetItemType() >= 10 && GetItemType() <= 12)
	{
		gC_vs_ui.RunBulletinBoardWindow(this);
		return;
	}
	
	// Ȯ���ⰰ����..
	CGUseItemFromInventory _CGUseItemFromInventory;
	
	_CGUseItemFromInventory.setObjectID( GetID() );
	_CGUseItemFromInventory.setX( GetGridX() );
	_CGUseItemFromInventory.setY( GetGridY() );
	g_pSocket->sendPacket( &_CGUseItemFromInventory );
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY );
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void MItemETC::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void MItemETC::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	if(GetItemType() == 1 )
	{
		CGUseItemFromInventory _CGUseItemFromInventory;						
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
		g_pSocket->sendPacket( &_CGUseItemFromInventory );				
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void MVampireETC::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void MVampireETC::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	//----------------------------------------------------
	//
	//					���ſ� ������ - vampire�� ���
	//
	//----------------------------------------------------
	if (g_pZoneTable->Get( g_pZone->GetID() )->CannotUseSpecialItem == false )
	{				
		ACTIONINFO useSkill;// = g_pPlayer->GetSpecialActionInfo();

		if ( GetItemClass() == ITEM_CLASS_SKULL )						// ���� �Ӹ�
		{
			useSkill = SKILL_TRANSFORM_TO_WERWOLF;
		}
		else if (GetItemType()==0)
		{
			useSkill = MAGIC_TRANSFORM_TO_WOLF;
		}
		else if (GetItemType()==1)
		{
			useSkill = MAGIC_TRANSFORM_TO_BAT;
		}
		else
		{
			// - -;
			if( GetItemType() == 2)
			{
				
				CGUseItemFromInventory _CGUseItemFromInventory;						
				_CGUseItemFromInventory.setObjectID( GetID() );
				_CGUseItemFromInventory.setX( GetGridX() );
				_CGUseItemFromInventory.setY( GetGridY() );

				g_pSocket->sendPacket( &_CGUseItemFromInventory );

				g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
			}
			return;					
		}

		//----------------------------------------------------
		// skill�� ����� ������ ���
		//----------------------------------------------------
		if (useSkill != ACTIONINFO_NULL)
		{
			if (//(*g_pActionInfoTable)[playerSkill].IsTargetItem()
				g_pSkillAvailable->IsEnableSkill( useSkill )
				&& (*g_pSkillInfoTable)[useSkill].IsAvailableTime())					
			{
				//----------------------------------------------------
				// ���� ������ ���� ���..
				//----------------------------------------------------
				if (!g_pPlayer->IsWaitVerify()
					&& g_pPlayer->IsItemCheckBufferNULL())
				{					
					CGSkillToInventory _CGSkillToInventory;
					_CGSkillToInventory.setObjectID( GetID() );
					_CGSkillToInventory.setX( GetGridX() );
					_CGSkillToInventory.setY( GetGridY() );
					_CGSkillToInventory.setSkillType( useSkill );
					//_CGSkillToInventory.setCEffectID( 0 );	// -_-;;							
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
					if(0 != SubInventoryItemID)
						_CGSkillToInventory.setInventoryItemObjectID( SubInventoryItemID );
	#endif
					g_pSocket->sendPacket( &_CGSkillToInventory );

					
					// �ϴ�(!) �׳� ���ְ� ����.
					//(*g_pInventory).RemoveItem( GetID() );

					//----------------------------------------------------
					// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
					//----------------------------------------------------
					g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_SKILL_SUCCESS );
				#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
					g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY, SubInventoryItemID );
				#else
					g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY );
				#endif
					

					(*g_pSkillInfoTable)[useSkill].SetNextAvailableTime();

					//----------------------------------------------------
					// ��� ��� �õ� ����
					//----------------------------------------------------
					AddNewInventoryEffect( GetID(),
										useSkill, //+ (*g_pActionInfoTable).GetMinResultActionInfo(),
										g_pClientConfig->FPS*3	// 3��
									);								
				}
			}
		}
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MSkull::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MSkull::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	//----------------------------------------------------
	//
	//					���ſ� ������ - vampire�� ���
	//
	//----------------------------------------------------
	if (g_pZoneTable->Get( g_pZone->GetID() )->CannotUseSpecialItem == false )
	{				
		ACTIONINFO useSkill;// = g_pPlayer->GetSpecialActionInfo();

		if ( GetItemClass() == ITEM_CLASS_SKULL && GetItemType() == 39)						// ���� �Ӹ�
		{
			useSkill = SKILL_TRANSFORM_TO_WERWOLF;
		}
		else if (GetItemType()==0)
		{
			useSkill = MAGIC_TRANSFORM_TO_WOLF;
		}
		else if (GetItemType()==1)
		{
			useSkill = MAGIC_TRANSFORM_TO_BAT;
		}
		else
		{
			// - -;
			if( GetItemType() == 2)
			{
				
				CGUseItemFromInventory _CGUseItemFromInventory;						
				_CGUseItemFromInventory.setObjectID( GetID() );
				_CGUseItemFromInventory.setX( GetGridX() );
				_CGUseItemFromInventory.setY( GetGridY() );

				g_pSocket->sendPacket( &_CGUseItemFromInventory );

				g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
			}
			return;					
		}

		//----------------------------------------------------
		// skill�� ����� ������ ���
		//----------------------------------------------------
		if (useSkill != ACTIONINFO_NULL)
		{
			if (//(*g_pActionInfoTable)[playerSkill].IsTargetItem()
				g_pSkillAvailable->IsEnableSkill( useSkill )
				&& (*g_pSkillInfoTable)[useSkill].IsAvailableTime())					
			{
				//----------------------------------------------------
				// ���� ������ ���� ���..
				//----------------------------------------------------
				if (!g_pPlayer->IsWaitVerify()
					&& g_pPlayer->IsItemCheckBufferNULL())
				{					
					CGSkillToInventory _CGSkillToInventory;
					_CGSkillToInventory.setObjectID( GetID() );
					_CGSkillToInventory.setX( GetGridX() );
					_CGSkillToInventory.setY( GetGridY() );
					_CGSkillToInventory.setSkillType( useSkill );
					//_CGSkillToInventory.setCEffectID( 0 );	// -_-;;							

					g_pSocket->sendPacket( &_CGSkillToInventory );

					
					// �ϴ�(!) �׳� ���ְ� ����.
					//(*g_pInventory).RemoveItem( GetID() );

					//----------------------------------------------------
					// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
					//----------------------------------------------------
					g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_SKILL_SUCCESS );
					g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY );

					(*g_pSkillInfoTable)[useSkill].SetNextAvailableTime();

					//----------------------------------------------------
					// ��� ��� �õ� ����
					//----------------------------------------------------
					AddNewInventoryEffect( GetID(),
										useSkill, //+ (*g_pActionInfoTable).GetMinResultActionInfo(),
										g_pClientConfig->FPS*3	// 3��
									);								
				}
			}
		}
	}
#endif
}

// �ش� ũ������ �ֺ��� ���ϴ� ��ü�� �ִ��� �˻��Ѵ�.
extern bool IsExistCorpseFromPlayer(MCreature* OriginCreature, int creature_type);

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MKey::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MKey::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	// �ֺ��� ����� ����� �Ѵ�.
	if( !IsExistCorpseFromPlayer( dynamic_cast<MCreature*>(g_pPlayer), 670 ) )
	{
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
		
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		if(0 != SubInventoryItemID)
			_CGUseItemFromInventory.setInventoryItemObjectID( SubInventoryItemID );
	#endif
		g_pSocket->sendPacket( &_CGUseItemFromInventory );

	//modify by viva for notice : i don't understand it :(
//	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
//		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY, SubInventoryItemID );
//	#else
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
//	#endif
	//end
		
	} else
	{
		g_pSystemMessage->Add((*g_pGameStringTable)[UI_STRING_MESSAGE_CANNOT_ACTION_MOTORCYCLE_FLAG].GetString() );
	}
	
#endif
}
void	MKey::UseQuickItem()
{
#ifdef __GAME_CLIENT__
	// 2004, 12, 16, sobeit add start - �ν��� �ͷ� ���¿��� ������̸� Ÿ�� ���� ����..���� �׷��� ����
	if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_INSTALL_TURRET))
	{
		return ;
	}
	// 2004, 12, 16, sobeit add end
	CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
	_CGUsePotionFromQuickSlot.setObjectID( GetID() );
	_CGUsePotionFromQuickSlot.setSlotID( GetItemSlot() );							

	g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );

	UI_LockGear();
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);
	// �ϴ�(!) �׳� ���ְ� ����.
	//(*g_pInventory).RemoveItem( GetID() );

	//----------------------------------------------------
	// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
	//----------------------------------------------------
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);
	//----------------------------------------------------
	// ��Ʈ �� ���ֵ���..
	//----------------------------------------------------
	UI_LockGear();

#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MEventTreeItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MEventTreeItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	if(GetItemType() == 12 ||
		GetItemType() >= 26 && GetItemType() <= 28)
	{
		bool bUseOK = true;

		bool bMasterWords = g_pPlayer->GetCreatureType()==CREATURETYPE_SLAYER_OPERATOR
					|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_OPERATOR
					|| g_pPlayer->GetCreatureType()==CREATURETYPE_OUSTERS_OPERATOR;
		
		if(IsPlayerInSafePosition() || g_pZone != NULL && (g_pZone->GetID() == 1104 || g_pZone->GetID() == 1106 || g_pZone->GetID() == 1114 || g_pZone->GetID() == 1115))
			// ��������� ������ ������� ������
		{				
			// �� ���� �ƴϸ鼭 ��ڰ� �ƴϸ�
			if( !( g_pZone->GetID() >= 1201 && g_pZone->GetID() <= 1206 ) && !bMasterWords )
			{				
				bUseOK = false;
				g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NOT_USE_SAFETY_POSITION].GetString() );
				return;
			}
		}

		if( g_pPlayer->GetMoveDevice()==MCreature::MOVE_DEVICE_RIDE )
		{				
			if( g_pPlayer->IsSlayer() )
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_CANNOT_USE_RIDE_MOTORCYCLE].GetString() );
			else if (g_pPlayer->IsOusters() )
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_CANNOT_USE_SUMMON_SYLPH].GetString() );

			return;
		}
		
		int playerX = g_pPlayer->GetX(), playerY = g_pPlayer->GetY();
		
		for(int y = playerY-3; y <= playerY+3; y++)
		{
			for(int x = playerX-2; x <= playerX+2; x++)
			{
				if(x < 0 || y < 0 || x >= g_pZone->GetWidth() || y >= g_pZone->GetHeight())
					continue;

				MItem *pItem = g_pZone->GetSector(x, y).GetItem();
				MCreature *pCreature = NULL;
				
				if(pItem != NULL)
				{
					if(GetItemClass() == ITEM_CLASS_CORPSE)
					{
						MCorpse *pCorpse = (MCorpse *)pItem;
						pCreature = pCorpse->GetCreature();
						
						if(pCreature != NULL && pCreature->GetCreatureType() == 482 || pCreature->GetCreatureType() == 650)
						{
							bUseOK = false;
							if(GetItemType() == 12)	// ũ���� ���� Ʈ��
							{
								g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_XMAS_TREE_CANNOT_USE].GetString() );
							}
							else					// �Խ���
							{
								g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_BULLETIN_BOARD_CANNOT_USE].GetString() );
							}
							return;
						}
					}
				}
			}
		}
		if (bUseOK)
		{
			if(GetItemType() == 12)		// ũ�������� Ʈ��
			{
				gC_vs_ui.RunXmasCardWindow(this);
			}
			else						// �Խ���
			{
				gC_vs_ui.RunBulletinBoardWindow(this);
			}
		}
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MEventEtcItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MEventEtcItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	bool bUseOK = true;

	if(IsPlayerInSafePosition() == 2 
		&& GetItemType() != 14 
		&& GetItemType()!=15
		&& GetItemType()!=16
		&& GetItemType()!=17) // 14�� �ӽó�..����..�� �����..
	{
		bUseOK = false;
		g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NOT_USE_SAFETY_ZONE].GetString() );
		return;
	}
		
	if (bUseOK)
	{
		if(GetItemType() == 14||
		GetItemType() == 15||
		GetItemType() == 16||
		GetItemType() == 17) // ������, + ����
		{
			CGUsePotionFromInventory _CGUsePotionFromInventory;
			_CGUsePotionFromInventory.setObjectID( GetID() );
			_CGUsePotionFromInventory.setX( GetGridX() );
			_CGUsePotionFromInventory.setY( GetGridY() );
			g_pSocket->sendPacket( &_CGUsePotionFromInventory );
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);

		}
		else
		{
			CGUseItemFromInventory _CGUseItemFromInventory;
			_CGUseItemFromInventory.setObjectID( GetID() );
			_CGUseItemFromInventory.setX( GetGridX() );
			_CGUseItemFromInventory.setY( GetGridY() );
			g_pSocket->sendPacket( &_CGUseItemFromInventory );
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);

		}
		
	}
#endif
}
void	MEventEtcItem::UseQuickItem()
{
#ifdef __GAME_CLIENT__
	if(GetItemType() == 14||
		GetItemType() == 15||
		GetItemType() == 16||
		GetItemType() == 17) // ������, + ����
	{
		if( g_pPlayer->IsOusters() )
		{
			CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
			_CGUsePotionFromQuickSlot.setObjectID( GetID() );
			int slotID = GetItemSlot();

			if( g_pArmsBand1 != NULL )	// 1�� �Ͻ���尡 ������ �׳�
			{
				if(g_pArmsBand1->GetItem( slotID ) == this)
					_CGUsePotionFromQuickSlot.setSlotID( slotID );
				else
					_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
			}
			else						// 1�� �Ͻ���尡 ������ 2�� +3 �� ���ش�
			{
				_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
			}
				
		//					_CGUsePotionFromQuickSlot.setSlotID( slotID );
			g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);
		//	DEBUG_ADD_FORMAT("[ Ousters Item Use From QuickSlot ] %d %d",slotID, GetID() );
			
			//----------------------------------------------------
			// ��Ʈ �� ���ֵ���..
			//----------------------------------------------------
			UI_LockGear();
		}
		else
		{
			CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
			_CGUsePotionFromQuickSlot.setObjectID( GetID() );
			_CGUsePotionFromQuickSlot.setSlotID( GetItemSlot() );							

			g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );

			
			// �ϴ�(!) �׳� ���ְ� ����.
			//(*g_pInventory).RemoveItem( GetID() );

			//----------------------------------------------------
			// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
			//----------------------------------------------------
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);

			//----------------------------------------------------
			// ��Ʈ �� ���ֵ���..
			//----------------------------------------------------
			UI_LockGear();
		}
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MDyePotionItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MDyePotionItem::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	// �ƿ콺����� ���� ���� ������ ����ȯ �������� ����� �� ����
	if( g_pPlayer->IsOusters() && GetItemType() == 48 )
	{
		UI_PopupMessage(STRING_MESSAGE_CANNOT_USE_OUSTERS);
	}
	else
	{
		// edit by sonic 2006.10.29  ȥ����ת����ʹ�øı����ɫ����

			/*	
				// 2005, 2, 22, sobeit add start
				if(g_pPlayer->IsAdvancementClass() && GetItemType() >= 58 && GetItemType() <= 61)
				{ // ���� ������ ������ ����Ʈ ���� �ٲٴ� �������� ������ �Ѵٳ�..�ͱ�...?
					UI_PopupMessage(UI_STRING_MESSAGE_CANNOT_USE_ADVANCEMENTCLASS);
					return;
				}
				// 2005, 2, 22, sobeit add end
			*/

		// 2006.10.29,Sonic edit end
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
		
		g_pSocket->sendPacket( &_CGUseItemFromInventory );			
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);				
	}
#endif
}
//
//void	MDyePotionItem::UseQuickItem()
//{
//#ifdef __GAME_CLIENT__
//	
//	if( g_pPlayer->IsOusters() )
//	{
//		// �ƿ콺����� ���� ���� ������ ����ȯ �������� ����� �� ����
//		if(GetItemType() == 48)
//			UI_PopupMessage(STRING_MESSAGE_CANNOT_USE_OUSTERS);
//		else
//		{
//			CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
//			_CGUsePotionFromQuickSlot.setObjectID( GetID() );
//			int slotID = GetItemSlot();
//
//			if( g_pArmsBand1 != NULL )	// 1�� �Ͻ���尡 ������ �׳�
//			{
//				if(g_pArmsBand1->GetItem( slotID ) == this)
//					_CGUsePotionFromQuickSlot.setSlotID( slotID );
//				else
//					_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
//			}
//			else						// 1�� �Ͻ���尡 ������ 2�� +3 �� ���ش�
//			{
//				_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
//			}
//				
//		//					_CGUsePotionFromQuickSlot.setSlotID( slotID );
//			g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );
//			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);
//		//	DEBUG_ADD_FORMAT("[ Ousters Item Use From QuickSlot ] %d %d",slotID, GetID() );
//			
//			//----------------------------------------------------
//			// ��Ʈ �� ���ֵ���..
//			//----------------------------------------------------
//			UI_LockGear();
//		}
//	}
//	else
//	{
//		CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
//		_CGUsePotionFromQuickSlot.setObjectID( GetID() );
//		_CGUsePotionFromQuickSlot.setSlotID( GetItemSlot() );							
//
//		g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );
//
//		
//		// �ϴ�(!) �׳� ���ְ� ����.
//		//(*g_pInventory).RemoveItem( GetID() );
//
//		//----------------------------------------------------
//		// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
//		//----------------------------------------------------
//		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);
//
//		//----------------------------------------------------
//		// ��Ʈ �� ���ֵ���..
//		//----------------------------------------------------
//		UI_LockGear();
//	}
//#endif
//}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MOustersSummonGem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MOustersSummonGem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	if( IsChargeItem() && GetNumber() > 0 && IsAffectStatus() && !g_bZoneSafe &&
		!g_pPlayer->IsInSafeSector() && g_pPlayer->IsStop() && !g_pPlayer->HasEffectStatus( EFFECTSTATUS_HAS_FLAG) )
	{
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		if(0 != SubInventoryItemID)
			_CGUseItemFromInventory.setInventoryItemObjectID( SubInventoryItemID );
	#endif

		g_pSocket->sendPacket( &_CGUseItemFromInventory );

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY, SubInventoryItemID);
	#else
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
	#endif
		
		(*g_pSkillInfoTable)[SKILL_SUMMON_SYLPH].SetAvailableTime( 4000 );
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MCodeSheetItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MCodeSheetItem::UseInventory()
	#endif

{
#ifdef __GAME_CLIENT__
	if( GetItemType() == 0 && GetItemOptionListCount() == 30)
	{
		gC_vs_ui.RunQuestInventory(this);
	}
#endif
}

void	MPotion::UseQuickItem()
{
#ifdef __GAME_CLIENT__
	CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
	_CGUsePotionFromQuickSlot.setObjectID( GetID() );
	_CGUsePotionFromQuickSlot.setSlotID( GetItemSlot() );							

	g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );

	
	// �ϴ�(!) �׳� ���ְ� ����.
	//(*g_pInventory).RemoveItem( GetID() );

	//----------------------------------------------------
	// Inventory���� item�� ����ϴ� �� �����ޱ⸦ ��ٸ���.
	//----------------------------------------------------
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);

	//----------------------------------------------------
	// ��Ʈ �� ���ֵ���..
	//----------------------------------------------------
	UI_LockGear();

	// [����] ��Ʈ�� ������ ���
//	__BEGIN_HELP_EVENT
///		ExecuteHelpEvent( HE_ITEM_USE_BELT_ITEM );	
//	__END_HELP_EVENT
#endif
}

void	MOustersPupa::UseQuickItem()
{
#ifdef __GAME_CLIENT__
	CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
	_CGUsePotionFromQuickSlot.setObjectID( GetID() );
	int slotID = GetItemSlot();

	if( g_pArmsBand1 != NULL )	// 1�� �Ͻ���尡 ������ �׳�
	{
		if(g_pArmsBand1->GetItem( slotID ) == this)
			_CGUsePotionFromQuickSlot.setSlotID( slotID );
		else
			_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
	}
	else						// 1�� �Ͻ���尡 ������ 2�� +3 �� ���ش�
	{
		_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
	}
		
//					_CGUsePotionFromQuickSlot.setSlotID( slotID );
	g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);
//	DEBUG_ADD_FORMAT("[ Ousters Item Use From QuickSlot ] %d %d",slotID, GetID() );
	
	//----------------------------------------------------
	// ��Ʈ �� ���ֵ���..
	//----------------------------------------------------
	UI_LockGear();
#endif
}

void	MOustersComposMei::UseQuickItem()
{
#ifdef __GAME_CLIENT__
	CGUsePotionFromQuickSlot _CGUsePotionFromQuickSlot;
	_CGUsePotionFromQuickSlot.setObjectID( GetID() );
	int slotID = GetItemSlot();

	if( g_pArmsBand1 != NULL )	// 1�� �Ͻ���尡 ������ �׳�
	{
		if(g_pArmsBand1->GetItem( slotID ) == this)
			_CGUsePotionFromQuickSlot.setSlotID( slotID );
		else
			_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
	}
	else						// 1�� �Ͻ���尡 ������ 2�� +3 �� ���ش�
	{
		_CGUsePotionFromQuickSlot.setSlotID( slotID + 3);
	}
		
//					_CGUsePotionFromQuickSlot.setSlotID( slotID );
	g_pSocket->sendPacket( &_CGUsePotionFromQuickSlot );
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT);
//	DEBUG_ADD_FORMAT("[ Ousters Item Use From QuickSlot ] %d %d",slotID, GetID() );
	
	//----------------------------------------------------
	// ��Ʈ �� ���ֵ���..
	//----------------------------------------------------
	UI_LockGear();
#endif
}

void	MCoupleRing::UseGear()
{
#ifdef __GAME_CLIENT__
	CGUseItemFromGear _CGUseItemFromGear;
	
	_CGUseItemFromGear.setObjectID ( GetID() );
	_CGUseItemFromGear.setPart ( GetItemSlot() );
	
	g_pSocket->sendPacket( &_CGUseItemFromGear );
	
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_GEAR );
#endif
}

void	MVampireCoupleRing::UseGear()
{
#ifdef __GAME_CLIENT__
	CGUseItemFromGear _CGUseItemFromGear;
	
	_CGUseItemFromGear.setObjectID ( GetID() );
	_CGUseItemFromGear.setPart ( GetItemSlot() );
	
	g_pSocket->sendPacket( &_CGUseItemFromGear );
	
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_GEAR );
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MPetItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MPetItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
// ���� ���� ������ ���� ȣ������ ���ϵ��� ������ ���� ���ٶ��� ���� ����ϹǷ� �ּ�ó������
// � ���������� ���� ȣ���ߴ��� �����ۿ� ǥ�����ִ°͵�....������̵� ���ϴϱ� ��

//	if(g_pPlayer->GetPetID() == OBJECTID_NULL)
//	{
	if(GetCurrentDurability() > 0)
	{
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		if(0 != SubInventoryItemID)
			_CGUseItemFromInventory.setInventoryItemObjectID( SubInventoryItemID );
	#endif

		g_pSocket->sendPacket( &_CGUseItemFromInventory );

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY, SubInventoryItemID);
	#else
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
	#endif
		
	}
//	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MPetFood::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MPetFood::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	const TYPE_OBJECTID petID = g_pPlayer->GetPetID();

	if(g_pPlayer != NULL && petID != OBJECTID_NULL
		)
	{
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
		
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		if(0 != SubInventoryItemID)
			_CGUseItemFromInventory.setInventoryItemObjectID( SubInventoryItemID );
	#endif
		g_pSocket->sendPacket( &_CGUseItemFromInventory );

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY, SubInventoryItemID);
	#else
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
	#endif
		
	}
	else
	{
		// 2�� �̻� �־�� �и� �ȴ�.
		if(GetNumber() > 1)
		{
			// ������ �и�
			CGAddInventoryToMouse _CGAddInventoryToMouse;
			_CGAddInventoryToMouse.setObjectID( 0 );	// �и��Ѵٴ� �ǹ�
			_CGAddInventoryToMouse.setX( GetGridX() );
			_CGAddInventoryToMouse.setY( GetGridY() );
			
			g_pSocket->sendPacket( &_CGAddInventoryToMouse );				
			
			//----------------------------------------------------
			// Inventory���� item�� � ��� �� �����޴´�.
			// �ϴ��� 1���� �鸮���� �Ѵ�.
			//----------------------------------------------------
			g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY);
		}
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MSms_item::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MSms_item::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	if(g_pPlayer != NULL )
	{
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
		
		g_pSocket->sendPacket( &_CGUseItemFromInventory );
		
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MPetEnchantItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MPetEnchantItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	// 2�� �̻� �־�� �и� �ȴ�.
	if(GetNumber() > 1)
	{
		// ������ �и�
		CGAddInventoryToMouse _CGAddInventoryToMouse;
		_CGAddInventoryToMouse.setObjectID( 0 );	// �и��Ѵٴ� �ǹ�
		_CGAddInventoryToMouse.setX( GetGridX() );
		_CGAddInventoryToMouse.setY( GetGridY() );
		
		g_pSocket->sendPacket( &_CGAddInventoryToMouse );				
		
		//----------------------------------------------------
		// Inventory���� item�� � ��� �� �����޴´�.
		// �ϴ��� 1���� �鸮���� �Ѵ�.
		//----------------------------------------------------
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY);
	}
#endif
}

MPetItem::MPetItem()
{
	m_UpdateTime = timeGetTime();
	m_PetKeepedDay = 0;
	m_bCanGamble = false;
	m_bCutHead = false;
	m_bCanAttack = false;
}

std::string MPetItem::GetPetOptionName()
{
	std::string petOptionName;
	if(GetSilver() > 0/* && GetEnchantLevel()!=0xFFFF by viva */)
	{
		ITEMOPTION_TABLE::ITEMOPTION_PART optionPart = static_cast<ITEMOPTION_TABLE::ITEMOPTION_PART>(GetEnchantLevel());
		int optionLevel = (GetNumber()-10)/10;

		int size = g_pItemOptionTable->GetSize();
		bool bFound = false;

		for(int i = 1; i < size; i++)
		{
			ITEMOPTION_INFO &optionInfo = g_pItemOptionTable->Get(i);
			if(optionInfo.Part == optionPart)
			{
				bFound = true;
				if(optionLevel == 0)
				{
					petOptionName = optionInfo.Name;
					petOptionName += " ";
					break;
				}
				else
				{
					optionLevel--;
				}
			}
		}
		if(optionLevel != 0 && bFound == true)	// �ٸ� �ɼ� ��Ʈ�� ��������
		{
			switch(optionPart)
			{
			case ITEMOPTION_TABLE::PART_LUCK:
				petOptionName = (*g_pGameStringTable)[STRING_MESSAGE_OPTION_NAME_LUCK_3+optionLevel].GetString();
				petOptionName += " ";
				break;

			case ITEMOPTION_TABLE::PART_ALL_ATTR:
				petOptionName = (*g_pGameStringTable)[STRING_MESSAGE_OPTION_NAME_ATTR_3+optionLevel].GetString();
				petOptionName += " ";
				break;
			}
		}
	}

	return petOptionName;
}

std::string MPetItem::GetPetOptionEName()
{
	std::string petOptionName;
	if(GetSilver() > 0)
	{
		ITEMOPTION_TABLE::ITEMOPTION_PART optionPart = static_cast<ITEMOPTION_TABLE::ITEMOPTION_PART>(GetEnchantLevel());
		int optionLevel = (GetNumber()-10)/10;

		int size = g_pItemOptionTable->GetSize();
		bool bFound = false;

		for(int i = 1; i < size; i++)
		{
			ITEMOPTION_INFO &optionInfo = g_pItemOptionTable->Get(i);
			if(optionInfo.Part == optionPart)
			{
				bFound = true;
				if(optionLevel == 0)
				{
					petOptionName = optionInfo.EName;
					petOptionName += " ";
					break;
				}
				else
				{
					optionLevel--;
				}
			}
		}
		if(optionLevel != 0 && bFound == true)	// �ٸ� �ɼ� ��Ʈ�� ��������
		{
			switch(optionPart)
			{
			case ITEMOPTION_TABLE::PART_LUCK:
				petOptionName = (*g_pGameStringTable)[STRING_MESSAGE_OPTION_ENAME_LUCK_3+optionLevel].GetString();
				petOptionName += " ";
				break;

			case ITEMOPTION_TABLE::PART_ALL_ATTR:
				petOptionName = (*g_pGameStringTable)[STRING_MESSAGE_OPTION_ENAME_ATTR_3+optionLevel].GetString();
				petOptionName += " ";
				break;
			}
		}
	}

	return petOptionName;
}

std::string MPetItem::GetPetName()
{
	std::string petName = GetPetOptionName();
	switch(GetItemType())
	{
	case 1:
		petName += (*g_pCreatureTable)[688].Name.GetString();
		break;

	case 2:
		petName += (*g_pCreatureTable)[693].Name.GetString();
		break;

	case 3:
		petName += (*g_pCreatureTable)[700].Name.GetString();
		break;
	
	case 4:
		petName += (*g_pCreatureTable)[706].Name.GetString();
		break;

	case 5:
		petName += (*g_pCreatureTable)[711].Name.GetString();
		break;
		// add by coffee 2006-12-22
	case 6:
		petName += (*g_pCreatureTable)[400].Name.GetString();
		break;
		// end 2006-12-22
	
	}

	return petName;
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void	MEventGiftBoxItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void	MEventGiftBoxItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	if(GetItemType() >= 6)
	{
		CGUseItemFromInventory _CGUseItemFromInventory;
		_CGUseItemFromInventory.setObjectID( GetID() );
		_CGUseItemFromInventory.setX( GetGridX() );
		_CGUseItemFromInventory.setY( GetGridY() );
		
		g_pSocket->sendPacket( &_CGUseItemFromInventory );
		
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
	}
#endif
}
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void MMoonCardItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void MMoonCardItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	// 2�� �̻� �־�� �и� �ȴ�.
	// edit by sonic 2006.11.1  ����Ҷ����Ϊ�ɷֿ�
	//if(GetItemType() == 2 && GetNumber() > 1 && GetNumber() < GetMaxNumber())
	if(GetItemType() == 2 || GetItemType() ==3 && GetNumber() > 1 && GetNumber() < GetMaxNumber())
	{
		// ������ �и�
		CGAddInventoryToMouse _CGAddInventoryToMouse;
		_CGAddInventoryToMouse.setObjectID( 0 );	// �и��Ѵٴ� �ǹ�
		_CGAddInventoryToMouse.setX( GetGridX() );
		_CGAddInventoryToMouse.setY( GetGridY() );
		
		g_pSocket->sendPacket( &_CGAddInventoryToMouse );				
		
		//----------------------------------------------------
		// Inventory���� item�� � ��� �� �����޴´�.
		// �ϴ��� 1���� �鸮���� �Ѵ�.
		//----------------------------------------------------
		g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY);
	}
#endif
}

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
void MTrapItem::UseInventory(TYPE_OBJECTID SubInventoryItemID)
	#else
void MTrapItem::UseInventory()
	#endif
{
#ifdef __GAME_CLIENT__
	CGUseItemFromInventory _CGUseItemFromInventory;
	_CGUseItemFromInventory.setObjectID( GetID() );
	_CGUseItemFromInventory.setX( GetGridX() );
	_CGUseItemFromInventory.setY( GetGridY() );
	
	g_pSocket->sendPacket( &_CGUseItemFromInventory );
	
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
#endif
}
	

#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�

void MSubInventory::UseInventory(TYPE_OBJECTID SubInventoryItemID)
{
#ifdef __GAME_CLIENT__
	CGUseItemFromInventory _CGUseItemFromInventory;
	_CGUseItemFromInventory.setObjectID( GetID() );
	_CGUseItemFromInventory.setX( GetGridX() );
	_CGUseItemFromInventory.setY( GetGridY() );
	
	g_pSocket->sendPacket( &_CGUseItemFromInventory );
	
	g_pPlayer->SetItemCheckBuffer( this, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
#endif
}

void
MSubInventory::SetItemType(TYPE_ITEMTYPE type)
{
	switch(type)
	{
	case 0:	// 2*4 pack
		MGridItemManager::Init(2, 4);   
		break;
	
	//  2005.08.15 Sjheon 4x6 �� Add	
	case 1:	// 4*6 pack
		MGridItemManager::Init(4, 6); 
		break;
	//  2005.08.15 Sjheon 4x6 �� End

	default:
		MGridItemManager::Init(2, 4);
		break;
	}
	m_ItemType = type; 
}
//----------------------------------------------------------------------
// AddItem ( pItem )
//----------------------------------------------------------------------
// ������ slot�� pItem�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MSubInventory::AddItem(MItem* pItem)
{
	bool re = MGridItemManager::AddItem( pItem );
	SetEnchantLevel(MGridItemManager::GetItemNum()); // Enchant level�� ������ ������ ����� ����.
	return re;
}

//----------------------------------------------------------------------
// AddItem ( pItem, n )
//----------------------------------------------------------------------
// slot(n)�� pItem�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MSubInventory::AddItem(MItem* pItem, BYTE X, BYTE Y)
{
	bool re = MGridItemManager::AddItem( pItem, X, Y );
	SetEnchantLevel(MGridItemManager::GetItemNum()); // Enchant level�� ������ ������ ����� ����.
	return re;
}

//----------------------------------------------------------------------
// ReplaceItem
//----------------------------------------------------------------------
// pItem�� �߰��ϰ� ���� �ִٸ� Item��ȯ
//----------------------------------------------------------------------
bool			
MSubInventory::ReplaceItem(MItem* pItem, BYTE X, BYTE Y, MItem*& pOldItem)
{
	bool re =  MGridItemManager::ReplaceItem( pItem, X, Y, pOldItem );
	SetEnchantLevel(MGridItemManager::GetItemNum()); // Enchant level�� ������ ������ ����� ����.
	return re;
}


//----------------------------------------------------------------------
// Can ReplaceItem : (n) slot�� pItem�� �߰��ϰų� 
//						���� �ִ� Item�� ��ü�� �����Ѱ�?
//----------------------------------------------------------------------
bool			
MSubInventory::CanReplaceItem(MItem* pItem, BYTE X, BYTE Y, MItem*& pOldItem)
{
	return MGridItemManager::CanReplaceItem( pItem, X, Y, pOldItem );
}

#endif
