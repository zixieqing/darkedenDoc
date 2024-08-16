//////////////////////////////////////////////////////////////////////
//
// Filename    : GCShopSellOKHandler.cpp
// Written By  : �輺��
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCShopSellOK.h"
#include "ClientDef.h"
#include "MInventory.h"
#include "TempInformation.h"
#include "MMoneyManager.h"
#include "UIFunction.h"
#include "MStorage.h"
#include "Client.h"
// PacketFunction.cpp�� �ִ�. compile �ð� �����..
void	CheckItemForSkillIcon(const MItem* pItem);

void GCShopSellOKHandler::execute ( GCShopSellOK * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	//--------------------------------------------------------------
	//
	// Item �Ĵ� packet�� �޴°� �³�?
	//
	//--------------------------------------------------------------

	if(pPacket->getShopVersion() == -1 && g_pStorage2!=NULL)
	{
		int current_storage = g_pStorage2->GetCurrent();
		const int storage_size = g_pStorage2->GetSize();
		const int storage_max = STORAGE_SLOT;
		
		for(int j = 0; j < storage_size; j++)
		{
			g_pStorage2->SetCurrent(0);
			 
			for(int i = 0; i < storage_max; i++)
			{
				const MItem *p_slot_item = g_pStorage2->GetItem(i);
				
				// ������ ������� ��~ �ִ´�
				if(NULL != p_slot_item)
				{
					if(p_slot_item->GetID() == pPacket->getObjectID())
					{ 
						MItem* pRemovedItem = g_pStorage2->RemoveItem( i );
						SAFE_DELETE(pRemovedItem);
						break;
					}
				}
			}
			current_storage ++;
			if(current_storage >= storage_size)
				current_storage = 0;
		}

		// inventory���� ����
		MItem *TempItem = g_pInventory->RemoveItem( (TYPE_OBJECTID)pPacket->getItemObjectID() );
		// item���� ����
		UI_RemoveDescriptor( (void*)TempItem );
		// memory���� ����
		SAFE_DELETE(TempItem);

		g_pMoneyManager->AddMoney(pPacket->getPrice());
		g_pTempInformation->SetMode(TempInformation::MODE_NULL);
		UI_UnlockItemTrade();
		return;
	
	}
	if(pPacket->getShopVersion() == -1 && g_pStorage2==NULL)
	{
		MItem *TempItem = g_pInventory->RemoveItem( (TYPE_OBJECTID)pPacket->getItemObjectID() );
		UI_RemoveDescriptor( (void*)TempItem );
		// memory���� ����
		SAFE_DELETE(TempItem);

		g_pMoneyManager->AddMoney(pPacket->getPrice());
		g_pTempInformation->SetMode(TempInformation::MODE_NULL);
		UI_UnlockItemTrade();
		return;

	}

	if (g_pTempInformation->GetMode() == TempInformation::MODE_SHOP_SELL)
	{
		MItem* pCheckItem = (MItem*)g_pTempInformation->pValue;		
		
		const MItem* pItem = g_pInventory->GetItem( pCheckItem->GetGridX(), pCheckItem->GetGridY() );

		// ID ������ �Ѵ�.
		if (pCheckItem->GetID()==pItem->GetID())
		{
			// ShopVersion_t getShopVersion(); -_-;;

			MItem* pRemovedItem = g_pInventory->RemoveItem( (TYPE_OBJECTID)pItem->GetID() );

			if (pRemovedItem!=NULL)
			{
				PlaySound( pRemovedItem->GetInventorySoundID() );

				CheckItemForSkillIcon( pRemovedItem );

				// item���� ����
				UI_RemoveDescriptor( (void*)pRemovedItem );

				delete pRemovedItem;
			}
			else
			{
				DEBUG_ADD("[Error] Item is NULL");
			}

			//--------------------------------------------------------------
			// ���� �ٲ��ش�.
			//--------------------------------------------------------------
			if (!g_pMoneyManager->SetMoney( pPacket->getPrice() ))
			{
				DEBUG_ADD_FORMAT("[Error] Can't Set Money=%d, Price=%d", g_pMoneyManager->GetMoney(), pPacket->getPrice());
			}
		}
		else
		{
			DEBUG_ADD_FORMAT("[Error] Different ID. Packet(%d)!=ClientTemp(%d)", pPacket->getItemObjectID(), pItem->GetID());
		}

		// mode�� ���ش�.
		g_pTempInformation->SetMode(TempInformation::MODE_NULL);
		
		// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
		UI_UnlockItemTrade();
	}
	//--------------------------------------------------------------
	//
	// ��� �ذ��� �� �Ĵ� ���
	//
	//--------------------------------------------------------------
	else if (g_pTempInformation->GetMode() == TempInformation::MODE_SHOP_SELL_ALL_SKULL)
	{
		MItem* pSkull = g_pInventory->FindItem( ITEM_CLASS_SKULL );

		//--------------------------------------------------------------
		// �Ҹ� �ѹ��� ���ش�.
		//--------------------------------------------------------------
		if (pSkull!=NULL)
		{
			PlaySound( pSkull->GetInventorySoundID() );
		}				

		//--------------------------------------------------------------
		// ��� �ذ��� �� �����ش�.
		//--------------------------------------------------------------
		while (pSkull!=NULL)
		{
			MItem* pRemovedItem = g_pInventory->RemoveItem( (TYPE_OBJECTID)pSkull->GetID() );

			if (pRemovedItem!=NULL)
			{
				// item���� ����
				UI_RemoveDescriptor( (void*)pRemovedItem );

				delete pRemovedItem;
			}

			//--------------------------------------------------------------
			// �ذ��� �� �ִ��� �˻�..
			//--------------------------------------------------------------
			pSkull = g_pInventory->FindItem( ITEM_CLASS_SKULL );
		}

		//--------------------------------------------------------------
		// ���� �ٲ��ش�.
		//--------------------------------------------------------------
		if (!g_pMoneyManager->SetMoney( pPacket->getPrice() ))
		{
			DEBUG_ADD_FORMAT("[Error] Can't Set Money=%d, Price=%d", g_pMoneyManager->GetMoney(), pPacket->getPrice());
		}

		// mode�� ���ش�.
		g_pTempInformation->SetMode(TempInformation::MODE_NULL);

		// �ŷ��� �ٽ� Ȱ��ȭ�Ѵ�.
		UI_UnlockItemTrade();
	}	
	//--------------------------------------------------------------
	//
	// ���� �߸��� ���
	//
	//--------------------------------------------------------------
	else
	{
		DEBUG_ADD("[Error] Sell? -_-; No Temp Information!");
	}
#endif

	__END_CATCH
}
