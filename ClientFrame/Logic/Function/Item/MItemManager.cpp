//----------------------------------------------------------------------
// MItemManager.h
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MItemManager.h"
#include "MItem.h"
#include "MItemFinder.h"
#include "MQuickSlot.h"

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MItemManager::MItemManager()
{
}

MItemManager::~MItemManager()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void
MItemManager::Release()
{
	ITEM_MAP::iterator iItem = m_mapItem.begin();

	// ���� map�� Item�� ���� �ִ� ���..
	// memory���� ���Ž�Ų��.
	while (iItem != m_mapItem.end())
	{
		MItem* pItem = (*iItem).second;

		delete pItem;
#ifdef __GAME_CLIENT__
		if(pItem == g_pArmsBand1)
		{
			g_pArmsBand1 = NULL;
		}
		else if(pItem == g_pArmsBand2)
		{
			g_pArmsBand2 = NULL;
		}
		else if(pItem == g_pQuickSlot)
		{
			g_pQuickSlot = NULL;
		}
#endif
		iItem++;
	}

	m_mapItem.clear();
}

//----------------------------------------------------------------------
// Add Item
//----------------------------------------------------------------------
// mapItem�� pointer�� ������� �д�.
//----------------------------------------------------------------------
bool		
MItemManager::AddItem(MItem* pItem)
{
	ITEM_MAP::iterator	iItem;

	iItem = m_mapItem.find(pItem->GetID());
	
	//-----------------------------------------------
	// ���� ���� Item�̸� �߰�	
	//-----------------------------------------------
	if (iItem == m_mapItem.end())
	{
		m_mapItem.insert(ITEM_MAP::value_type(pItem->GetID(), pItem));

		// ���� ���� üũ
		CheckAffectStatus( pItem );			

		return true;
	}

	//-----------------------------------------------
	// �̹� �ִ� Item�̸� false
	//-----------------------------------------------
	return false;
}

//----------------------------------------------------------------------
// Get Item
//----------------------------------------------------------------------
// Item�� pointer�� �Ѱ��ش�.
//----------------------------------------------------------------------
MItem*	
MItemManager::GetItemToModify(TYPE_OBJECTID id)
{
	ITEM_MAP::iterator	iItem;

	//--------------------------------------------------
	// ID�� id�� Item�� ã�´�.
	//--------------------------------------------------
	iItem = m_mapItem.find(id);

	//--------------------------------------------------
	// ���� ��� NULL�� return�Ѵ�.
	//--------------------------------------------------
	if (iItem == m_mapItem.end()) 
	{
		return NULL;
	}

	//--------------------------------------------------
	// ������ �� Item�� return�Ѵ�.
	//--------------------------------------------------
	return (*iItem).second;
}

//----------------------------------------------------------------------
// Get Item (const)
//----------------------------------------------------------------------
// Item�� pointer�� �Ѱ��ش�.
//----------------------------------------------------------------------
MItem*	
MItemManager::GetItem(TYPE_OBJECTID id) const
{
	ITEM_MAP::const_iterator	iItem;

	//--------------------------------------------------
	// ID�� id�� Item�� ã�´�.
	//--------------------------------------------------
	iItem = m_mapItem.find(id);

	//--------------------------------------------------
	// ���� ��� NULL�� return�Ѵ�.
	//--------------------------------------------------
	if (iItem == m_mapItem.end()) 
	{
		return NULL;
	}

	//--------------------------------------------------
	// ������ �� Item�� return�Ѵ�.
	//--------------------------------------------------
	return (*iItem).second;
}

	

//----------------------------------------------------------------------
// Remove Item
//----------------------------------------------------------------------
// mapItem���� �����ϰ� Item�� pointer�� �Ѱ��ش�.
//----------------------------------------------------------------------
MItem*	
MItemManager::RemoveItem(TYPE_OBJECTID id)
{
	ITEM_MAP::iterator	iItem;

	//--------------------------------------------------
	// ID�� id�� Item�� ã�´�.
	//--------------------------------------------------
	iItem = m_mapItem.find(id);
    
	//--------------------------------------------------
	// �׷� id�� ���� Item�� ���� ���
	//--------------------------------------------------
	if (iItem == m_mapItem.end())
	{
		return NULL;
	}

	//--------------------------------------------------
	// ã�� ��� --> ����	
	//--------------------------------------------------
	MItem* pItem = (*iItem).second;
	
	// map���� ����
	m_mapItem.erase( iItem );

	//--------------------------------------------------
	// ��� �ٸ� item���� ��ġ üũ
	//--------------------------------------------------
	CheckAffectStatusAll();

	return pItem;
}

//----------------------------------------------------------------------
// Check AffectStatus
//----------------------------------------------------------------------
// ��밡������ üũ
//----------------------------------------------------------------------
void			
MItemManager::CheckAffectStatusAll()				// ��� ������
{
	ITEM_MAP::iterator iItem = m_mapItem.begin();

	//------------------------------------------------------
	// ��� item���� ��밡������ �ƴ����� üũ�Ѵ�.
	//------------------------------------------------------
	while (iItem != m_mapItem.end())
	{
		MItem* pItem = (*iItem).second;

		CheckAffectStatus( pItem );

		iItem++;
	}
}

//----------------------------------------------------------------------
// Check AffectStatus
//----------------------------------------------------------------------
void			
MItemManager::CheckAffectStatus(MItem* pItem)
{
	// pure virtual�� �ҷ��ٰ�.. �׳� �� ��쵵 �־..
}

//----------------------------------------------------------------------
// Transfer Item To (id, pItemManager)
//----------------------------------------------------------------------
// this�� ID�� id�� MItem�� �����ؼ�
// pItemManager�� �߰���Ų��.
//----------------------------------------------------------------------
/*
bool		
MItemManager::TransferItemTo(TYPE_OBJECTID id, MItemManager& targetItemManager)
{
	MItem* pItem = RemoveItem(id);

	// NULL�� �ƴ� ���..
	if (pItem == NULL)
	{
		return false;
	}
	
	return targetItemManager.AddItem( pItem );
}
*/

//----------------------------------------------------------------------
// ������ ã��
//----------------------------------------------------------------------
MItem*
MItemManager::FindItem( MItemFinder& itemFinder ) const
{
	ITEM_MAP::const_iterator iItem = m_mapItem.begin();

	while (iItem != m_mapItem.end())
	{
		MItem* pItem = iItem->second;
		
		if (itemFinder( pItem ))
		{
			return pItem;
		}
//		else if(pItem->GetItemClass() == ITEM_CLASS_SUB_INVENTORY)
//		{
//			MItem* pTempItem = ((MSubInventory*)pItem)->FindItemGridOrder( itemFinder );
//			if(NULL != pTempItem)
//				return pTempItem;
//		}
		

		iItem++;
	}

	return NULL;
}
#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
//----------------------------------------------------------------------
// ���а�
//----------------------------------------------------------------------
MItem*			
MItemManager::FindItemAll( MItemFinder& itemFinder, MItem*& pSubInventoryItem) const
{
	ITEM_MAP::const_iterator iItem = m_mapItem.begin();

	while (iItem != m_mapItem.end())
	{
		MItem* pItem = iItem->second;
		
		if (itemFinder( pItem ))
		{
			return pItem;
		}
		else if(pItem->GetItemClass() == ITEM_CLASS_SUB_INVENTORY)
		{
			MItem* pTempItem = ((MSubInventory*)pItem)->FindItem( itemFinder );
			if(NULL != pTempItem)
			{
				pSubInventoryItem = pItem;
				return pTempItem;
			}
		}
		iItem++;
	}

	return NULL;

}
#endif

#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�


//----------------------------------------------------------------------
// GetItemToModifyAll
//----------------------------------------------------------------------
// ���� �κ� ���� ������ ������..����
//----------------------------------------------------------------------
	MItem*			
	MItemManager::GetItemToModifyAll( TYPE_OBJECTID id, MItem*& pSubInventoryItem)
	{
		ITEM_MAP::const_iterator iItem = m_mapItem.begin();

		while (iItem != m_mapItem.end())
		{
			MItem* pItem = iItem->second;
			
			if (pItem != NULL && pItem->GetID() == id)
			{
				return pItem;
			}
			else if(pItem->GetItemClass() == ITEM_CLASS_SUB_INVENTORY)
			{
				MItem* pTempItem = ((MSubInventory*)pItem)->GetItemToModify( id );
				if(NULL != pTempItem)
				{
					pSubInventoryItem = pItem;
					return pTempItem;
				}
			}
			iItem++;
		}

		return NULL;

	}

#endif