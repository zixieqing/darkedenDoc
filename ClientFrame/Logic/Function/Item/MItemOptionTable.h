//----------------------------------------------------------------------
// MItemOptionTable.h
//----------------------------------------------------------------------
// Item�� Option�� ������ ���� ������ �����ϴ� class
//----------------------------------------------------------------------

#ifndef	__MITEMOPTIONTABLE_H__
#define	__MITEMOPTIONTABLE_H__

#include "CTypeTable.h"
#include "MTypeDef.h"
#include "MString.h"
class ofstream;
class ifstream;

//#define	MAX_PARTNAME_LENGTH		48
#define UNIQUE_ITEM_COLOR		0xffff
#define QUEST_ITEM_COLOR		0xfffe

//----------------------------------------------------------------------
//
// �� ������ Item�� ���� ����
//
//----------------------------------------------------------------------
class ITEMOPTION_INFO {
	public :
	public :
		MString					EName;					// ItemOption ���� �̸�		
		MString					Name;					// ItemOption �̸�
		int						Part;					// ItemOption Part				
		int						PlusPoint;				// ����ġ
		int						PriceMultiplier;		// ��ġ	(%�� �Ǿ� �����Ƿ�, 100���� ������� ��)	
		//int						PlusRequireAbility;		// �ʿ� �ɷ� ����ġ		

		// �ʿ� �ɷ�ġ
		int						RequireSTR;
		int						RequireDEX;
		int						RequireINT;
		int						RequireSUM;		// �ɷ�ġ ����
		int						RequireLevel;
		
		int						ColorSet;				// �� ��ȣ
		int						UpgradeOptionType;		// ���׷��̵� �Ǹ� ��-_-���ϴ� Ÿ�� 0�̸� ��-_-�� ����
		int						PreviousOptionType;		// ���׷��̵� �����ؼ� ��-_-���ϴ� Ÿ�� 0�̸� ��-_-�� ����

	public :
		ITEMOPTION_INFO();
		~ITEMOPTION_INFO();

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);		
		void			LoadFromFile(class ifstream& file);		
};


//--------------------------------------------------------------------------
// �ϳ��� class�� ���� type���� ����
//--------------------------------------------------------------------------
class ITEMOPTION_TABLE:public CTypeTable<ITEMOPTION_INFO>
{
public:
	enum ITEMOPTION_PART
	{
		PART_STR = 0,      // increase STR
		PART_DEX,          // increase DEX 
		PART_INT,          // increase INT 
		PART_HP,           // increase HP 
		PART_MP,           // increase MP 
		PART_HP_STEAL,     // steal HP 
		PART_MP_STEAL,     // steal MP 
		PART_HP_REGEN,     // regenerate hp over time
		PART_MP_REGEN,     // regenerate mp over time
		PART_TOHIT,        // increase tohit
		PART_DEFENSE,      // increase defense
		PART_DAMAGE,       // increase damage 
		PART_PROTECTION,   // increase protection
		PART_DURABILITY,   // increase item durability
		PART_POISON,       // increase poison resistence
		PART_ACID,         // increase acid resistence
		PART_CURSE,        // increase curse resistence
		PART_BLOOD,        // increase blood resistence
		PART_VISION,       // increase vision range
		PART_ATTACK_SPEED, // increase attack speed
		PART_CRITICAL_HIT,
			
		// 2002.10.21�� �߰�
		PART_LUCK,         // increase looting item type
		PART_ALL_RES,      // increase all registance
		PART_ALL_ATTR,     // increase all attributes(str, dex, int)

		// 2002.12.03�� �߰�
		PART_STR_TO_DEX,   // STR to DEX
		PART_STR_TO_INT,   // STR to INT
		PART_DEX_TO_STR,   // DEX to STR
		PART_DEX_TO_INT,   // DEX to INT
		PART_INT_TO_STR,   // INT to STR
		PART_INT_TO_DEX,   // INT to DEX

		// 2003.2.12
		PART_CONSUME_MP,       // decrease consume mana
		PART_TRANS,        // translate race language
		PART_MAGIC_DAMAGE,  // increase magic damage
		PART_PHYSIC_DAMAGE, // increase physical damage
		PART_GAMBLE_PRICE, // decrease gamble price
		PART_POTION_PRICE, // decrease gamble price
 
		OPTION_MAGIC_PRO,	// ���� ����
		OPTION_PHYSIC_PRO,	// ���� ����

		MAX_PART
	};

	// option part�� name string
	MString ITEMOPTION_PARTNAME[MAX_PART];
	MString ITEMOPTION_PARTENAME[MAX_PART];
		

	void	LoadFromFile(class ifstream& file);
};

extern	ITEMOPTION_TABLE*		g_pItemOptionTable;


#endif
