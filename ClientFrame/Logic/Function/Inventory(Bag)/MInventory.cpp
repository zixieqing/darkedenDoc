//----------------------------------------------------------------------
// MInventory.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MItem.h"
#include "MInventory.h"

#include "MHelpManager.h"
#ifdef __GAME_CLIENT__
	#include "ClientFunction.h"
	#include "MPlayer.h"
#endif

/*
#ifdef __GAME_CLIENT__
	#include "MEffect.h"
	#include "MEffectGeneratorTable.h"
#endif
	*/

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MInventory*		g_pInventory = NULL;

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MInventory::MInventory()
{
}

MInventory::~MInventory()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Check AffectStatus
//----------------------------------------------------------------------
// ��밡������ üũ
//----------------------------------------------------------------------
void			
MInventory::CheckAffectStatus(MItem* pItem)	// Ư�� ������
{
#ifdef __GAME_CLIENT__

	g_pPlayer->CheckAffectStatus( pItem );
		
#endif
}

//----------------------------------------------------------------------
// Add item ( pItem )
//----------------------------------------------------------------------
// Inventory�� �߰��� �� �ִ� Item���� ����,..
// ������ grid�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MInventory::AddItem(MItem* pItem)
{
	if (pItem->IsInventoryItem())
	{
		if (MGridItemManager::AddItem( pItem ))
		{
			// ����� �߰��� ��� --> sound���
			#ifdef __GAME_CLIENT__
				PlaySound( pItem->GetInventorySoundID() );
			#endif
		
						
			return true;
		}

		return false;
	}

	return false;
}

//----------------------------------------------------------------------
// Add item ( pItem )
//----------------------------------------------------------------------
// Inventory�� �߰��� �� �ִ� Item���� ����,..
// grid(x,y)�� pItem�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool			
MInventory::AddItem(MItem* pItem, BYTE x, BYTE y)
{
	if (pItem->IsInventoryItem())
	{
		if (MGridItemManager::AddItem( pItem, x, y ))
		{
			// ����� �߰��� ��� --> sound���
			#ifdef __GAME_CLIENT__
				PlaySound( pItem->GetInventorySoundID() );
			#endif

			return true;
		}

		return false;
	}

	return false;
}

//----------------------------------------------------------------------
// Replace item ( pItem,  x,y,  pOldItem )
//----------------------------------------------------------------------
// Inventory�� �߰��� �� �ִ� Item���� ����,..
// �߰��� �� ������ �߰��ϴµ�
// �� ��ġ�� �ٸ� item�� �ִٸ� pOldItem�� ��Ƽ� �Ѱ��ش�.
//----------------------------------------------------------------------
bool			
MInventory::ReplaceItem(MItem* pItem, BYTE x, BYTE y, MItem*& pOldItem)
{
	if (pItem->IsInventoryItem())
	{
		if (MGridItemManager::ReplaceItem(pItem, x,y, pOldItem))
		{
			// ����� �߰��� ��� --> sound���
			#ifdef __GAME_CLIENT__
				PlaySound( pItem->GetInventorySoundID() );
			#endif

			return true;
		}
		
		return false;
	}

	return false;
}

//----------------------------------------------------------------------
// Get Fit Position ( pItem, point )
//----------------------------------------------------------------------
// pItem�� �� �� �ִ� ������ grid��ġ�� ���Ѵ�.
//
// �ϴ�, �׿��� �ߺ��� �� �ִ� Item�� ��츦 üũ�ؾ��Ѵ�.
// ������ �Ѱ�ġ�� �Ѿ ���� ���̴°� �Ұ����� ���� �� ������
// ã���� �ȴ�.
//----------------------------------------------------------------------
bool			
MInventory::GetFitPosition(MItem* pItem, POINT& point)
{
	//--------------------------------------------------------
	// ���̴� item�� ��츸 üũ�Ѵ�.
	//--------------------------------------------------------
	if (pItem->IsPileItem())
	{
		// ��� Item�� üũ�ϸ鼭 ���� �� �ִ����� üũ�Ѵ�.
		// ã�� ������?? -_-;;
		// ID��.. ��.. -_-;;;
		ITEM_MAP::iterator iItem = m_mapItem.begin();

		while (iItem != m_mapItem.end())
		{
			MItem* pInventoryItem = (*iItem).second;

			//--------------------------------------------
			// �����ϰ� ���� �� �ִ� ������ �Ǹ�...
			// ������ item�� ��ǥ�� �Ѱ��ش�.
			//--------------------------------------------
			if (pInventoryItem->GetItemClass()==pItem->GetItemClass()
				&& pInventoryItem->GetItemType()==pItem->GetItemType()
				&& pInventoryItem->GetNumber() + pItem->GetNumber() <= pItem->GetMaxNumber()
				&& !pInventoryItem->IsQuestItem())
			{
				point.x = pInventoryItem->GetGridX();
				point.y = pInventoryItem->GetGridY();

				return true;
			}

			iItem++;
		}
	}

	return MGridItemManager::GetFitPosition( pItem, point );
}

//----------------------------------------------------------------------
// Find Item  (class , type)
//----------------------------------------------------------------------
// inventory���� ������ itemClass�� itemType�� ���� item�� �ϳ� ã�´�.
// itemType�� ������ �� ���� �ִ�.
// �׸���, �ϳ��� ã���� �ǹǷ�... ���� ���� �߰ߵǴ°� �Ѱ��ָ� �ȴ�.
//----------------------------------------------------------------------
MItem*	
MInventory::FindItem( ITEM_CLASS itemClass, TYPE_ITEMTYPE itemType )
{
	ITEM_MAP::iterator iItem = m_mapItem.begin();

	//------------------------------------------------------
	// itemType�� �������� ���� ���
	//------------------------------------------------------
	if (itemType==ITEMTYPE_NULL)
	{
		while (iItem != m_mapItem.end())
		{
			MItem* pItem = (*iItem).second;

			// class�� ��
			if (pItem->GetItemClass()==itemClass)
			{
				return pItem;
			}

			iItem++;
		}
	}
	//------------------------------------------------------
	// class�� type ��� ��
	//------------------------------------------------------
	else
	{
		while (iItem != m_mapItem.end())
		{
			MItem* pItem = (*iItem).second;

			// class�� type ��� ��
			if (pItem->GetItemClass()==itemClass
				&& pItem->GetItemType()==itemType)
			{
				return pItem;
			}

			iItem++;
		}
	}

	return NULL;
}

/*
#ifdef __GAME_CLIENT__
	//----------------------------------------------------------------------
	// Add Effect
	//----------------------------------------------------------------------
	bool			
	MInventory::AddEffect(MEffect* pEffect)
	{
		if (pEffect==NULL)
		{
			return false;
		}

		m_listEffect.push_back( pEffect );

		return true;
	}

	//----------------------------------------------------------------------
	// Update Effects
	//----------------------------------------------------------------------
	void			
	MInventory::UpdateEffects()
	{
		EFFECT_LIST::iterator iEffect = m_listEffect.begin();

		EFFECT_LIST::iterator iTemp;
		
		MEffect* pEffect;
		int count = m_listEffect.size();

		for (int i=0; i<count; i++)	
		{
			pEffect = *iEffect;

			//---------------------------------------
			//
			// update --> ���������� �� ���
			//
			//---------------------------------------
			if (pEffect->Update())
			{
				//-----------------------------------------------
				//
				// �� Effect�� ������ ���� LinkCount�� ���ؼ�
				// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
				//
				// ����Frame�� EndLinkFrame�� �Ѿ ���
				//
				//-----------------------------------------------
				if (g_CurrentFrame >= pEffect->GetEndLinkFrame()
					&& pEffect->GetLinkSize() != 0)
				{
					// GenerateNext���� 
					// pEffect�� EffectTarget�� NULL�� ������ֱ� ������
					// ���⼭ ���� �ʿ� ����.
					g_EffectGeneratorTable.GenerateNext( pEffect );

					// pEffect�� ������ �����ؾ� �ϹǷ� ����� �ȵȴ�.
				}
				
				
				iEffect++;
			}
			//---------------------------------------
			//
			// �� �ż� ���� ���
			//
			//---------------------------------------
			else
			{
				//-----------------------------------------------
				// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
				//-----------------------------------------------
				if (pEffect->GetLinkSize() != 0)
				{
					g_EffectGeneratorTable.GenerateNext( pEffect );
				}

				//-----------------------------------------------
				// ����
				//-----------------------------------------------
				delete pEffect;

				iTemp = iEffect;
				iEffect++;

				// list���� �����Ѵ�.
				m_listEffect.erase(iTemp);
			}
		
		}
	}
#endif
	*/

