//----------------------------------------------------------------------
// MOustersGear.h
//----------------------------------------------------------------------
// Ousters�� Gear�� ���� class
//----------------------------------------------------------------------

#ifndef	__MOUSTERSGEAR_H__
#define	__MOUSTERSGEAR_H__

#include "MPlayerGear.h"

class MOustersGear : public MPlayerGear	{
	public :
		//----------------------------------------------------
		// QuickItem Slot�� Slot ID
		//----------------------------------------------------
		// (!) ID�� �ٲٸ� s_GearSlotCheckTable�� ������ �ٲ���� �Ѵ�.
		//----------------------------------------------------
		enum GEAR_OUSTERS
		{
			GEAR_OUSTERS_CIRCLET,			// ��Ŭ��
			GEAR_OUSTERS_COAT,				// ��
			GEAR_OUSTERS_LEFTHAND,			// �޼�
			GEAR_OUSTERS_RIGHTHAND,			// ������
			GEAR_OUSTERS_BOOTS,				// �Ź�
			GEAR_OUSTERS_ARMSBAND1,			// �Ͻ����1
			GEAR_OUSTERS_ARMSBAND2,			// �Ͻ����2
			GEAR_OUSTERS_RING1,				// ��1
			GEAR_OUSTERS_RING2,				// ��2
			GEAR_OUSTERS_PENDENT1,			// �����1
			GEAR_OUSTERS_PENDENT2,			// �����2
			GEAR_OUSTERS_PENDENT3,			// �����3
			GEAR_OUSTERS_STONE1,			// ���ɼ�1
			GEAR_OUSTERS_STONE2,			// ���ɼ�2
			GEAR_OUSTERS_STONE3,			// ���ɼ�3
			GEAR_OUSTERS_STONE4,			// ���ɼ�4
			
			GEAR_OUSTERS_ZAP1,				// ��1 - ���ɼ��� �����̴� ������
			GEAR_OUSTERS_ZAP2,				// ��2
			GEAR_OUSTERS_ZAP3,				// ��3
			GEAR_OUSTERS_ZAP4,				// ��4
			//by csm 2004 12.31 add item slot
			GEAR_OUSTERS_FASCIA,			// ������ �㸮���
	        GEAR_OUSTERS_MITTEN,			// ������ �尩?

			GEAR_OUSTERS_BLOOD_BIBLE1,				// ���� ���̺� ���� 1 - Ŭ���̾�Ʈ ����
			GEAR_OUSTERS_BLOOD_BIBLE2,				// ���� ���̺� ���� 2
			GEAR_OUSTERS_BLOOD_BIBLE3,				// ���� ���̺� ���� 3
			GEAR_OUSTERS_BLOOD_BIBLE4,				// ���� ���̺� ���� 4
			GEAR_OUSTERS_BLOOD_BIBLE5,				// ���� ���̺� ���� 5
			GEAR_OUSTERS_BLOOD_BIBLE6,				// ���� ���̺� ���� 6
			MAX_GEAR_OUSTERS
		};	

		//----------------------------------------------------
		// Ư���� ������ ������ �� �ִ� Item���� Ȯ��
		//----------------------------------------------------
		inline static bool		IsGearSlotCirclet(MItem* pItem);
		inline static bool		IsGearSlotCoat(MItem* pItem);
		inline static bool		IsGearSlotLeftHand(MItem* pItem);
		inline static bool		IsGearSlotRightHand(MItem* pItem);
		inline static bool		IsGearSlotBoots(MItem* pItem);
		inline static bool		IsGearSlotArmsBand(MItem* pItem);
		inline static bool		IsGearSlotRing(MItem* pItem);
		inline static bool		IsGearSlotPendent(MItem* pItem);
		inline static bool		IsGearSlotStone(MItem* pItem);
		inline static bool		IsGearSlotCoreZap(MItem* pItem);
		inline static bool		IsGearSlotBloodBible(MItem* pItem);
		inline static bool		IsGearSlotFascia(MItem* pItem);
		inline static bool		IsGearSlotMitten(MItem* pItem);


	public :
		MOustersGear();
		~MOustersGear();

		//------------------------------------------------
		// �����ϰ�~ �ʱ�ȭ ���� �ش�.
		//------------------------------------------------
		void			Init();

		//------------------------------------------------
		// AddItem : slot(n)�� pItem�� �߰��Ѵ�.
		//------------------------------------------------
		bool			AddItem(MItem* pItem);
		bool			AddItem(MItem* pItem, GEAR_OUSTERS n);

		//------------------------------------------------
		// GetItem : slot(n)�� item�� �о�´�.
		//------------------------------------------------
		MItem*			GetItem(GEAR_OUSTERS n) const { return MSlotItemManager::GetItem( (BYTE)n ); }
		
		//------------------------------------------------
		// RemoveItem : slot(n)�� item�� �����Ѵ�.
		//------------------------------------------------
		MItem*			RemoveItem(GEAR_OUSTERS n);

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
		bool			CanReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem);

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
		static FUNCTION_GEARSLOT_CHECK		s_GearSlotCheckTable[MAX_GEAR_OUSTERS];

		BYTE		m_Gilles_CoreZap;

		BYTE		m_bBloodBibleOpenCount;

};


extern MOustersGear	*	g_pOustersGear;

#endif

