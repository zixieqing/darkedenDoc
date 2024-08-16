//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeAddItemHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCTradeAddItem.h"
#include "ClientDef.h"
#include "MTradeManager.h"
#include "MItem.h"

void GCTradeAddItemHandler::execute ( GCTradeAddItem * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	//------------------------------------------------------------------------
	// TradeManager�� �������� ���� ��� --> -_-;;
	//------------------------------------------------------------------------
	if (g_pTradeManager==NULL)
	{
		DEBUG_ADD( "[Error] TradeManager is NULL");
		
		return;
	}

	//------------------------------------------------------------------------
	// �߰��Ǵ� ������ ����
	//------------------------------------------------------------------------
	MItem* pItem = MItem::NewItem( (ITEM_CLASS)pPacket->getItemClass() );

	pItem->SetID( pPacket->getItemObjectID() );
	
	pItem->SetItemType( pPacket->getItemType() );
	pItem->SetItemOptionList( pPacket->getOptionType() );
	pItem->SetCurrentDurability( pPacket->getDurability() );
	pItem->SetSilver( pPacket->getSilver() );	
	pItem->SetGrade( pPacket->getGrade() );	
	
	//ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }

	//------------------------------------------------------------------------
	// ����
	//------------------------------------------------------------------------
	// ���� ���
	//------------------------------------------------------------------------
	if (pItem->IsGunItem())
	{
		MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

		// �ǹ� ���� - -;
		pMagazine->SetID( 0 );

		// �̰Ŵ� �ѿ� ���缭 ����ߵȴ�.
		for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
		{
			pMagazine->SetItemType(	j );

			if (pMagazine->IsInsertToItem( pItem ))
			{
				break;
			}
		}

		// �ǹ� ����
		pMagazine->ClearItemOption();
	
		// źâ ����
		pMagazine->SetNumber( pPacket->getItemNum() );

		//------------------------------------
		// źâ ����
		//------------------------------------
		MGunItem* pGunItem = (MGunItem*)pItem;
		pGunItem->SetMagazine( pMagazine );
	}		
	//------------------------------------------------------------------------
	// ���� �ƴ� ���
	//------------------------------------------------------------------------
	else
	{
		pItem->SetNumber( pPacket->getItemNum() );
	}

	pItem->SetEnchantLevel( pPacket->getEnchantLevel() );

	//------------------------------------------------------------------------
	//
	// Item�� �ٸ� item���� ����ִ� ���
	//
	//------------------------------------------------------------------------
	if (pPacket->getListNum()!=0)
	{
		DEBUG_ADD_FORMAT("This Item has Sub item(s) : size=%d", pPacket->getListNum());
		
		//------------------------------------------
		// Belt�� ���
		//------------------------------------------
		if (pItem->GetItemClass()==ITEM_CLASS_BELT)
		{
			MBelt* pBelt = (MBelt*)pItem;

			int size = pPacket->getListNum();
			
			for (int i=0; i<size; i++)
			{
				SubItemInfo * pSubItemInfo = pPacket->popListElement();

				if (pSubItemInfo==NULL)
				{
					DEBUG_ADD("[Error] Sub Item is NULL");
				}
				else
				{
					//------------------------------------------
					// Sub Item�� ������ �����Ѵ�.
					//------------------------------------------
					MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
					pSubItem->SetItemType( pSubItemInfo->getItemType() );
					//pItem->SetItemOption( pSubItemInfo->getOptionType() );

					pSubItem->SetID( pSubItemInfo->getObjectID() );		

					pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

					//------------------------------------------
					// Belt�� ������ slot�� item�� �߰���Ų��.
					//------------------------------------------
					pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );

					delete pSubItemInfo;
				}
			} 
		}else if (pItem->GetItemClass()==ITEM_CLASS_OUSTERS_ARMSBAND)
		{
			MOustersArmsBand* pBelt = (MOustersArmsBand*)pItem;
			
			int size = pPacket->getListNum();
			
			for (int i=0; i<size; i++)
			{
				SubItemInfo * pSubItemInfo = pPacket->popListElement();
				
				if (pSubItemInfo==NULL)
				{
					DEBUG_ADD("[Error] Sub Item is NULL");
				}
				else
				{
					//------------------------------------------
					// Sub Item�� ������ �����Ѵ�.
					//------------------------------------------
					MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
					pSubItem->SetItemType( pSubItemInfo->getItemType() );
					//pItem->SetItemOption( pSubItemInfo->getOptionType() );
					
					pSubItem->SetID( pSubItemInfo->getObjectID() );		
					
					pSubItem->SetNumber( pSubItemInfo->getItemNum() );			
					
					//------------------------------------------
					// Belt�� ������ slot�� item�� �߰���Ų��.
					//------------------------------------------
					pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );
					
					delete pSubItemInfo;
				}
			}
		}
		else
		{
			DEBUG_ADD_FORMAT("This Item can't have Sub item : class=%d", (int)pItem->GetItemClass());
		}
	}

	
	int gridX = pPacket->getX();
	int gridY = pPacket->getY();

	//------------------------------------------------------------------------
	// other Inventory�� �߰��Ѵ�..
	// �߰� �ȵǸ�.. �ᰡ��.. - -;
	//------------------------------------------------------------------------
	if (!g_pTradeManager->GetOtherInventory()->AddItem( pItem, gridX, gridY ))
	{
		DEBUG_ADD_FORMAT("[Error] Can't add item to OtherInventory:id=%d (%d, %d)", pItem->GetID(), gridX, gridY);
		
		delete pItem;
	}

	//-----------------------------------------------------------
	// ���� �ٲ�ٸ�... OK���
	//-----------------------------------------------------------
	g_pTradeManager->RefuseOtherTrade();
	g_pTradeManager->RefuseMyTrade();

#endif

	__END_CATCH
}
