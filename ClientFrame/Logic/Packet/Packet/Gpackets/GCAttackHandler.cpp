//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAttackHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCAttack.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAttackHandler::execute ( GCAttack * pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__

	// message

	//------------------------------------------------------
	// Zone�� ���� �������� ���� ���
	//------------------------------------------------------
	if (g_pZone==NULL)
	{
		// message
		DEBUG_ADD("[Error] Zone is Not Init.. yet.");			
	}
	//------------------------------------------------------
	// ����.. 
	//------------------------------------------------------
	else
	{
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		if (pCreature != NULL)
		{
			// ���� �ٶ󺸱�
			pCreature->SetDirectionToPosition(pPacket->getX(), pPacket->getY());

			pCreature->PacketAttackNormal(	pPacket->getX(),
											pPacket->getY(),
											pPacket->getDir());
		}
	}	

#endif

	__END_CATCH
}
