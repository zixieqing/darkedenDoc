//////////////////////////////////////////////////////////////////////
//
// Filename    : GCCannotAddHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCCannotAdd.h"
#include "ClientDef.h"
#include "UIFunction.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCCannotAddHandler::execute ( GCCannotAdd * pPacket , Player * pPlayer )
	 throw ( ProtocolException, Error )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	//-----------------------------------------------------------------
	// ó���ҷ��� item buffer�� ���¿� ����..
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	// Pickup to Inventory
	//-----------------------------------------------------------------
	if (g_pPlayer->IsItemCheckBufferPickupToInventory())
	{
		DEBUG_ADD("Can't Drop Item to Inventory");
		
		// inventory�� �� �ִ� ���..
		// buffer�� ���Ž�Ű�� �ȴ�.
		g_pPlayer->ClearItemCheckBuffer();
	}
	//-----------------------------------------------------------------
	// Pickup to Mouse
	//-----------------------------------------------------------------
	else if (g_pPlayer->IsItemCheckBufferPickupToMouse())
	{
		DEBUG_ADD("Can't Pickup Item to Mouse");
		
		// buffer�� ���Ž�Ű�� �ȴ�.
		g_pPlayer->ClearItemCheckBuffer();
	}
	//-----------------------------------------------------------------
	// Drop to Zone
	//-----------------------------------------------------------------
	else if (g_pPlayer->IsItemCheckBufferDropToZone())
	{
		DEBUG_ADD("Can't Drop Item to Zone");
		
		// �ٽ� item�� mouse�� ���δ�.
		MItem* pItem = g_pPlayer->GetItemCheckBuffer();

		UI_PickUpItem( pItem );

		// buffer ����		
		g_pPlayer->ClearItemCheckBuffer();
	}
	//-----------------------------------------------------------------
	// inventory���� �������� �� �и��Ѵٰ� ����.
	//-----------------------------------------------------------------
	else if (g_pPlayer->IsItemCheckBufferPickupSomeFromInventory())
	{
		DEBUG_ADD("Can't PIckupSome From Inventory");

		g_pPlayer->ClearItemCheckBuffer();		
	}
	//-----------------------------------------------------------------
	// Drop to RelicTable
	//-----------------------------------------------------------------
	else if (g_pPlayer->IsItemCheckBufferDropToRelicTable())
	{
		DEBUG_ADD("Can't Drop to RelicTable");

		g_pPlayer->ClearItemCheckBuffer();		
	}
	//-----------------------------------------------------------------
	// Drop to Creature
	//-----------------------------------------------------------------
	else if (g_pPlayer->IsItemCheckBufferDropToCreature())
	{
		DEBUG_ADD("Can't Drop to Creature");

		g_pPlayer->ClearItemCheckBuffer();		
	}
	//-----------------------------------------------------------------
	// �ٸ� ���..
	//-----------------------------------------------------------------
	else
	{
		DEBUG_ADD("Else.. what?");

		g_pPlayer->ClearItemCheckBuffer();		
	}


#endif

	__END_CATCH
}
