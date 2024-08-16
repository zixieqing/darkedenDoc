	//----------------------------------------------------------------------
// MSlayerGear.h
//----------------------------------------------------------------------
// Slayer�� Gear�� ���� class
//----------------------------------------------------------------------
/*
	//---------------------------------
	// �ʱ�ȭ �Ѵ�.
	//---------------------------------
	g_SlayerGear.Init();

	MItem* pNewItem;

	//--------------------------------------------------------
	// �׽�Ʈ�� Item ����
	//--------------------------------------------------------
	pNewItem = MItem::NewItem( ITEM_CLASS_BLADE );
	pNewItem->SetID( 3 );
	pNewItem->SetItemType( 0 );
	g_SlayerGear.AddItem( pNewItem );


	pNewItem = MItem::NewItem( ITEM_CLASS_SWORD );
	pNewItem->SetID( 1 );
	pNewItem->SetItemType( 0 );
	g_SlayerGear.AddItem( pNewItem );

	pNewItem = MItem::NewItem( ITEM_CLASS_BELT );
	pNewItem->SetID( 2 );
	pNewItem->SetItemType( 0 );
	g_SlayerGear.AddItem( pNewItem );

	pNewItem = MItem::NewItem( ITEM_CLASS_RING );
	pNewItem->SetID( 4 );
	pNewItem->SetItemType( 0 );
	g_SlayerGear.AddItem( pNewItem );

	pNewItem = MItem::NewItem( ITEM_CLASS_SHIELD );
	pNewItem->SetID( 5 );
	pNewItem->SetItemType( 0 );
	g_SlayerGear.AddItem( pNewItem );

	pNewItem = MItem::NewItem( ITEM_CLASS_HELM );
	pNewItem->SetID( 6 );
	pNewItem->SetItemType( 0 );
	g_SlayerGear.AddItem( pNewItem );

	pNewItem = MItem::NewItem( ITEM_CLASS_RING );
	pNewItem->SetID( 7 );
	pNewItem->SetItemType( 0 );
	g_SlayerGear.AddItem( pNewItem );

	//--------------------------------------------------------
	// Remove test
	//--------------------------------------------------------
  	g_SlayerGear.RemoveItem( MSlayerGear::GEAR_SLAYER_LEFTHAND );


	//--------------------------------------------------------
	// ��¹��1
	//--------------------------------------------------------
	// Item�� �ѹ��� ���
	//--------------------------------------------------------
	g_SlayerGear.SetBegin();
	while (g_SlayerGear.IsNotEnd())
	{
		const MItem* pItem = g_SlayerGear.Get();

		DEBUG_ADD_FORMAT("[ID=%d] name=%s, slot=%d", 
			pItem->GetID(),
			pItem->GetName(),
			pItem->GetItemSlot()
			);

		g_SlayerGear.Next();
	}

*/
//----------------------------------------------------------------------


#ifndef	__MSLAYERGEAR_H__
#define	__MSLAYERGEAR_H__

#include "MPlayerGear.h"
class MMagazine;


class MSlayerGear : public MPlayerGear	{
	public :
		//----------------------------------------------------
		// QuickItem Slot�� Slot ID
		//----------------------------------------------------
		// (!) ID�� �ٲٸ� s_GearSlotCheckTable�� ������ �ٲ���� �Ѵ�.
		//----------------------------------------------------
		enum GEAR_SLAYER 
		{
			GEAR_SLAYER_HELM = 0,			// ����
			GEAR_SLAYER_NECKLACE,			// �����
			GEAR_SLAYER_COAT,				// ����
			GEAR_SLAYER_LEFTHAND,			// �޼�
			GEAR_SLAYER_RIGHTHAND,			// ������
			GEAR_SLAYER_GLOVE,				// �尩
			GEAR_SLAYER_BELT,				// ����
			GEAR_SLAYER_TROUSER,			// ����			
			GEAR_SLAYER_BRACELET1,			// ����1
			GEAR_SLAYER_BRACELET2,			// ����2
			GEAR_SLAYER_RING1,				// ����1
			GEAR_SLAYER_RING2,				// ����2
			GEAR_SLAYER_RING3,				// ����3
			GEAR_SLAYER_RING4,				// ����4
			GEAR_SLAYER_SHOES,				// �Ź�
		
			GEAR_SLAYER_ZAP1,				// ��1 - ���� �����̴� ������
			GEAR_SLAYER_ZAP2,				// ��2
			GEAR_SLAYER_ZAP3,				// ��3
			GEAR_SLAYER_ZAP4,				// ��4

			GEAR_SLAYER_PDA,			// ������ �㸮���
	        GEAR_SLAYER_SHOULDER,			// ������ �尩?

			GEAR_SLAYER_BLOOD_BIBLE1,				// ���� ���̺� ���� 1
			GEAR_SLAYER_BLOOD_BIBLE2,				// ���� ���̺� ���� 2
			GEAR_SLAYER_BLOOD_BIBLE3,				// ���� ���̺� ���� 3
			GEAR_SLAYER_BLOOD_BIBLE4,				// ���� ���̺� ���� 4
			GEAR_SLAYER_BLOOD_BIBLE5,				// ���� ���̺� ���� 5
			GEAR_SLAYER_BLOOD_BIBLE6,				// ���� ���̺� ���� 6

			MAX_GEAR_SLAYER
		};

		//----------------------------------------------------
		// Ư���� ������ ������ �� �ִ� Item���� Ȯ��
		//----------------------------------------------------
		inline static bool		IsGearSlotHelm(MItem* pItem);
		inline static bool		IsGearSlotNecklace(MItem* pItem);
		inline static bool		IsGearSlotCoat(MItem* pItem);
		inline static bool		IsGearSlotLeftHand(MItem* pItem);
		inline static bool		IsGearSlotRightHand(MItem* pItem);
		inline static bool		IsGearSlotGlove(MItem* pItem);
		inline static bool		IsGearSlotBelt(MItem* pItem);
		inline static bool		IsGearSlotTrouser(MItem* pItem);
		inline static bool		IsGearSlotBracelet(MItem* pItem);
		inline static bool		IsGearSlotRing(MItem* pItem);
		inline static bool		IsGearSlotShoes(MItem* pItem);
		inline static bool		IsGearSlotCoreZap(MItem* pItem);
		inline static bool		IsGearSlotBloodBible(MItem* pItem);
		inline static bool		IsGearSlotPDA(MItem* pItem);
		inline static bool		IsGearSlotShoulder(MItem* pItem);
		


	public :
		MSlayerGear();
		~MSlayerGear();

		//------------------------------------------------
		// �����ϰ�~ �ʱ�ȭ ���� �ش�.
		//------------------------------------------------
		void			Init();

		//------------------------------------------------
		// AddItem : slot(n)�� pItem�� �߰��Ѵ�.
		//------------------------------------------------
		bool			AddItem(MItem* pItem);
		bool			AddItem(MItem* pItem, GEAR_SLAYER n);

		//------------------------------------------------
		// GetItem : slot(n)�� item�� �о�´�.
		//------------------------------------------------
		MItem*			GetItem(GEAR_SLAYER n) const { return MSlotItemManager::GetItem( (BYTE)n ); }
		
		//------------------------------------------------
		// RemoveItem : slot(n)�� item�� �����Ѵ�.
		//------------------------------------------------
		MItem*			RemoveItem(GEAR_SLAYER n);

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
		// Get FitSlot
		//------------------------------------------------------		
		bool			GetFitSlot(MItem* pItem, GEAR_SLAYER& n);	// pItem�� �� �� �ִ� ������ slot��ġ�� ���Ѵ�.

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
		static FUNCTION_GEARSLOT_CHECK		s_GearSlotCheckTable[MAX_GEAR_SLAYER];

		BYTE		m_Gilles_CoreZap;
		BYTE		m_bBloodBibleOpenCount;
};


extern MSlayerGear*		g_pSlayerGear;

extern MMagazine*		g_pCurrentMagazine;

#endif

