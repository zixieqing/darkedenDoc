//----------------------------------------------------------------------
// MVampireGear.h
//----------------------------------------------------------------------
// Vampire�� Gear�� ���� class
//----------------------------------------------------------------------

#ifndef	__MVAMPIREGEAR_H__
#define	__MVAMPIREGEAR_H__

#include "MPlayerGear.h"

class MVampireGear : public MPlayerGear	{
	public :
		//----------------------------------------------------
		// QuickItem Slot�� Slot ID
		//----------------------------------------------------
		// (!) ID�� �ٲٸ� s_GearSlotCheckTable�� ������ �ٲ���� �Ѵ�.
		//----------------------------------------------------
		enum GEAR_VAMPIRE 
		{
			GEAR_VAMPIRE_NECKLACE,			// �����
			GEAR_VAMPIRE_COAT,				// ����
			GEAR_VAMPIRE_BRACELET1,			// ����1
			GEAR_VAMPIRE_BRACELET2,			// ����2
			GEAR_VAMPIRE_RING1,				// ����1
			GEAR_VAMPIRE_RING2,				// ����2
			GEAR_VAMPIRE_RING3,				// ����3
			GEAR_VAMPIRE_RING4,				// ����4
			GEAR_VAMPIRE_EARRING1,			// �Ͱ���1
			GEAR_VAMPIRE_EARRING2,			// �Ͱ���2
			GEAR_VAMPIRE_LEFTHAND,			// �޼�
			GEAR_VAMPIRE_RIGHTHAND,			// ������
			GEAR_VAMPIRE_AMULET1,			// �ƹķ�1
			GEAR_VAMPIRE_AMULET2,			// �ƹķ�2
			GEAR_VAMPIRE_AMULET3,			// �ƹķ�3
			GEAR_VAMPIRE_AMULET4,			// �ƹķ�4
			
			GEAR_VAMPIRE_ZAP1,				// ��1 - ������ �����̴� ������
			GEAR_VAMPIRE_ZAP2,				// ��2
			GEAR_VAMPIRE_ZAP3,				// ��3
			GEAR_VAMPIRE_ZAP4,				// ��4

			GEAR_VAMPIRE_PERSONA,		// ������ �丣�ҳ�
			GEAR_VAMPIRE_DERMIS,		// ������ ����?
			
 			
			GEAR_VAMPIRE_BLOOD_BIBLE1,				// ���� ���̺� ���� 1
			GEAR_VAMPIRE_BLOOD_BIBLE2,				// ���� ���̺� ���� 2
			GEAR_VAMPIRE_BLOOD_BIBLE3,				// ���� ���̺� ���� 3
			GEAR_VAMPIRE_BLOOD_BIBLE4,				// ���� ���̺� ���� 4
			GEAR_VAMPIRE_BLOOD_BIBLE5,				// ���� ���̺� ���� 5
			GEAR_VAMPIRE_BLOOD_BIBLE6,				// ���� ���̺� ���� 6
			
			MAX_GEAR_VAMPIRE
		};

		//----------------------------------------------------
		// Ư���� ������ ������ �� �ִ� Item���� Ȯ��
		//----------------------------------------------------
		inline static bool		IsGearSlotNecklace(MItem* pItem);
		inline static bool		IsGearSlotCoat(MItem* pItem);
		inline static bool		IsGearSlotBracelet(MItem* pItem);
		inline static bool		IsGearSlotRing(MItem* pItem);
		inline static bool		IsGearSlotEarRing(MItem* pItem);
		inline static bool		IsGearSlotLeftHand(MItem* pItem);
		inline static bool		IsGearSlotRightHand(MItem* pItem);
		inline static bool		IsGearSlotAmulet(MItem* pItem);
		inline static bool		IsGearSlotCoreZap(MItem* pItem);
		inline static bool		IsGearSlotBloodBible(MItem* pItem);
		inline static bool		IsGearSlotDermis(MItem* pItem);
		inline static bool		IsGearSlotPersona(MItem* pItem);
		


	public :
		MVampireGear();
		~MVampireGear();

		//------------------------------------------------
		// �����ϰ�~ �ʱ�ȭ ���� �ش�.
		//------------------------------------------------
		void			Init();

		//------------------------------------------------
		// AddItem : slot(n)�� pItem�� �߰��Ѵ�.
		//------------------------------------------------
		bool			AddItem(MItem* pItem);
		bool			AddItem(MItem* pItem, GEAR_VAMPIRE n);

		//------------------------------------------------
		// GetItem : slot(n)�� item�� �о�´�.
		//------------------------------------------------
		MItem*			GetItem(GEAR_VAMPIRE n ) const	{ return MSlotItemManager::GetItem( (BYTE)n ); }
		
		//------------------------------------------------
		// RemoveItem : slot(n)�� item�� �����Ѵ�.
		//------------------------------------------------
		MItem*			RemoveItem(GEAR_VAMPIRE n);

		//------------------------------------------------
		// RemoveItem : id�� ���� item�� �����Ѵ�.
		//------------------------------------------------
		MItem*			RemoveItem(TYPE_OBJECTID id);

		//------------------------------------------------
		// ReplaceItem : pItem�� �߰��ϰ� ���� �ִٸ� Item��ȯ
		//------------------------------------------------
		bool			ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem);

		//------------------------------------------------
		// Can ReplaceItem : (n) slot�� pItem�� �߰��ϰų� 
		//						���� �ִ� Item�� ��ü�� �����Ѱ�?
		//------------------------------------------------
		bool			CanReplaceItem(MItem* pItem, GEAR_VAMPIRE n, MItem*& pOldItem);

		//------------------------------------------------------
		// ���� ��밡���Ѱǰ�?
		//------------------------------------------------------
		void			CheckAffectStatus(MItem* pItem);	// Ư�� ������

		//------------------------------------------------
		// GetItem : ��� â���� pick �Ҷ��� ��� slot(n)�� item�� �о�´�.
		//------------------------------------------------
		MItem*			GetGearItem_PickUp(int &n) const ;
		//------------------------------------------------
		// GetItem : �ھ��� �������� ���ٿ��� �ִ��� �˻�
		//------------------------------------------------
		MItem*			GetGearCoreZapItem(int slot) const	;
		//------------------------------------------------
		// GetItem : �ھ��� ������ ���� �������� �˻�
		//------------------------------------------------
		MItem*			GetGearCoreZapedItem(int slot) const	;
		//------------------------------------------------
		// GetItem : �ھ����� �� ��Ҵ���..
		//------------------------------------------------
		const bool			IsHasAllCoreZap(int CoreZapType) const	;
		//------------------------------------------------
		// bool : ���� ���â�� ���ȴ���.
		//------------------------------------------------
		void			SetBloodBibleOpenSlot(int Num) { m_bBloodBibleOpenCount = Num;	}
		BYTE			GetBloodBibleOpenSlot() { return m_bBloodBibleOpenCount;	}
		const bool		IsCloseBloodBibleSlot(int slot) const	;


	protected :
		//------------------------------------------------
		// IsGearSlot...()�� ���� function pointer
		//------------------------------------------------
		typedef bool (*FUNCTION_GEARSLOT_CHECK)(MItem*);

		//------------------------------------------------
		// �� �������� IsGearSlot...()�� ���� function pointer
		//------------------------------------------------
		static FUNCTION_GEARSLOT_CHECK		s_GearSlotCheckTable[MAX_GEAR_VAMPIRE];

		BYTE			m_Gilles_CoreZap;
		BYTE		m_bBloodBibleOpenCount;
};


extern MVampireGear	*	g_pVampireGear;

#endif

