//--------------------------------------------------------------------------------
//
// Filename    : GCAddGearToZoneHandler.cpp
// Written By  : crazydog
//
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "GCAddGearToZone.h"
#include "ClientDef.h"
#include "MSlayerGear.h"
#include "MVampireGear.h"
#include "MOustersGear.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCAddGearToZoneHandler::execute ( GCAddGearToZone * pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	//----------------------------------------------------------------------
	// Slayer�� ���	
	//----------------------------------------------------------------------
	switch(g_pPlayer->GetRace())
	{
		case RACE_SLAYER:
			{
				const MItem* pItem = g_pSlayerGear->GetItem( (MSlayerGear::GEAR_SLAYER)pPacket->getSlotID() );
				
				//----------------------------------------------------------------------
				// �׷� id�� ���� item�� ���� ���
				//----------------------------------------------------------------------
				if (pItem==NULL)
				{
					DEBUG_ADD_FORMAT("[Error] Item does not exist in SlayerGear! slot=%d", (int)pPacket->getSlotID());
				}
				//----------------------------------------------------------------------
				// item�� �ִ� ��� --> Gear���� �����ؼ� Zone�� �߰��Ѵ�.
				//----------------------------------------------------------------------
				else
				{
					MItem* pRemovedItem = g_pSlayerGear->RemoveItem( pItem->GetID() );
					
					if (g_pZone==NULL)
					{
						DEBUG_ADD("[Error] Zone is Not Init!");
						
						delete pItem;
					}
					else
					{
						// ����߸��� ������� pItem�� Zone�� �߰��Ѵ�.
						g_pZone->AddItem( pRemovedItem, TRUE );
					}
				}
			}
			break;
			
		case RACE_VAMPIRE:
			{
				const MItem* pItem = g_pVampireGear->GetItem( (MVampireGear::GEAR_VAMPIRE)pPacket->getSlotID() );
				
				//----------------------------------------------------------------------
				// �׷� id�� ���� item�� ���� ���
				//----------------------------------------------------------------------
				if (pItem==NULL)
				{
					DEBUG_ADD_FORMAT("[Error] Item does not exist in VampireGear! slot=%d", (int)pPacket->getSlotID());
				}
				//----------------------------------------------------------------------
				// item�� �ִ� ��� --> Gear���� �����ؼ� Zone�� �߰��Ѵ�.
				//----------------------------------------------------------------------
				else
				{
					MItem* pRemovedItem = g_pVampireGear->RemoveItem( pItem->GetID() );
					
					if (g_pZone==NULL)
					{
						DEBUG_ADD("[Error] Zone is Not Init!");
						
						delete pItem;
					}
					else
					{
						// ����߸��� ������� pItem�� Zone�� �߰��Ѵ�.
						g_pZone->AddItem( pRemovedItem, TRUE );
					}
				}
				
			}
			break;
			
		case RACE_OUSTERS:
			{
				const MItem* pItem = g_pOustersGear->GetItem( (MOustersGear::GEAR_OUSTERS)pPacket->getSlotID() );
				
				//----------------------------------------------------------------------
				// �׷� id�� ���� item�� ���� ���
				//----------------------------------------------------------------------
				if (pItem==NULL)
				{
					DEBUG_ADD_FORMAT("[Error] Item does not exist in OustersGear! slot=%d", (int)pPacket->getSlotID());
				}
				//----------------------------------------------------------------------
				// item�� �ִ� ��� --> Gear���� �����ؼ� Zone�� �߰��Ѵ�.
				//----------------------------------------------------------------------
				else
				{
					MItem* pRemovedItem = g_pOustersGear->RemoveItem( pItem->GetID() );
					
					if (g_pZone==NULL)
					{
						DEBUG_ADD("[Error] Zone is Not Init!");
						
						delete pItem;
					}
					else
					{
						// ����߸��� ������� pItem�� Zone�� �߰��Ѵ�.
						g_pZone->AddItem( pRemovedItem, TRUE );
					}
				}
				
			}
			break;
			
	}

#endif

	__END_CATCH
}
