//----------------------------------------------------------------------
// MInventory.h
//----------------------------------------------------------------------
/*
	//--------------------------------------------------------
	// ���� * ���� = (5 * 4) �� GridInventory ����
	//--------------------------------------------------------
	g_Inventory.Init(5, 4);
	MItem* pNewItem;

	//--------------------------------------------------------
	// �׽�Ʈ�� Item ����
	//--------------------------------------------------------
	pNewItem = MItem::NewItem( ITEM_CLASS_SWORD );
	pNewItem->SetID( 2 );
	pNewItem->SetItemType( 1 );
	g_Inventory.AddItem( pNewItem, 1, 0 );

	
	pNewItem = MItem::NewItem( ITEM_CLASS_POTION );
	pNewItem->SetID( 3 );
	pNewItem->SetItemType( 0 );
	g_Inventory.AddItem( pNewItem, 3, 1 );
	
	
	pNewItem = MItem::NewItem( ITEM_CLASS_SHOES );
	pNewItem->SetID( 1 );
	pNewItem->SetItemType( 0 );
	g_Inventory.AddItem( pNewItem );


	//--------------------------------------------------------
	// �ɽ��ؼ� remove �� ��... - -;;
	//--------------------------------------------------------
	g_Inventory.RemoveItem( 0, 0 );
	g_Inventory.RemoveItem( 1, 3 );
	g_Inventory.RemoveItem( 4, 2 );

	
	//--------------------------------------------------------
	// ��¹��1
	//--------------------------------------------------------
	// Item�� �ѹ��� ���
	//--------------------------------------------------------
	g_Inventory.SetBegin();
	while (g_Inventory.IsNotEnd())
	{
		const MItem* pItem = g_Inventory.Get();

		DEBUG_ADD_FORMAT("[ID=%d] size=(%d, %d) xy=(%d, %d) ", 
			pItem->GetID(),
			pItem->GetGridWidth(), pItem->GetGridHeight(),
			pItem->GetGridX(), pItem->GetGridY()
			);

		g_Inventory.Next();
	}


	//--------------------------------------------------------
	// ��¹��2
	//--------------------------------------------------------
	// �� grid�� �ִ� Item���� �о ���
	//--------------------------------------------------------
	for (int i=0; i<g_Inventory.GetHeight(); i++)
	{
		for (int j=0; j<g_Inventory.GetWidth(); j++)
		{
			const MItem* pItem = g_Inventory.GetItem( j, i );

			if (pItem!=NULL)
			{
				DEBUG_ADD_FORMAT("[ID=%d] size=(%d, %d) xy=(%d, %d) ", 
											pItem->GetID(),
											pItem->GetGridWidth(), pItem->GetGridHeight(),
											pItem->GetGridX(), pItem->GetGridY()
											);
			}
		}
	}
*/
//----------------------------------------------------------------------

#ifndef	__MINVENTORY_H__
#define	__MINVENTORY_H__

#include "MGridItemManager.h"
#include "MItem.h"
#include <list>

/*
#ifdef __GAME_CLIENT__
	class MEffect;
#endif
	*/

class MInventory : public MGridItemManager {
	public :
		MInventory();
		~MInventory();

		//------------------------------------------------------
		// Add
		//------------------------------------------------------		
		bool			AddItem(MItem* pItem);					// ������ grid�� �߰��Ѵ�.
		bool			AddItem(MItem* pItem, BYTE x, BYTE y);	// grid(x,y)�� pItem�� �߰��Ѵ�.
	
		bool			ReplaceItem(MItem* pItem, BYTE x, BYTE y, MItem*& pOldItem);	// (x,y)��ġ�� Item��ȯ
		
		//------------------------------------------------------		
		// Get FitPosition
		//------------------------------------------------------		
		bool			GetFitPosition(MItem* pItem, POINT& point);	// pItem�� �� �� �ִ� ������ grid��ġ�� ���Ѵ�.

		//------------------------------------------------------
		// Find Item
		//------------------------------------------------------		
		MItem*			FindItem( ITEM_CLASS itemClass, TYPE_ITEMTYPE itemType=ITEMTYPE_NULL);

		//------------------------------------------------------
		// ���� ��밡���Ѱǰ�?
		//------------------------------------------------------
		void			CheckAffectStatus();				// ��� ������
		void			CheckAffectStatus(MItem* pItem);	// Ư�� ������

		/*
	#ifdef __GAME_CLIENT__
		public :
			typedef std::list<MEffect*>						EFFECT_LIST;

		public :
			//------------------------------------------------------		
			// Effect
			//------------------------------------------------------
			bool			AddEffect(MEffect* pEffect);
			void			UpdateEffects();
			int				GetEffectCount()				{ return m_listEffect.size(); }
			EFFECT_LIST::const_iterator GetEffects()		{ return m_listEffect.begin(); }

		protected :
			EFFECT_LIST		m_listEffect;
	#endif
	*/

};

extern MInventory*		g_pInventory;



#endif