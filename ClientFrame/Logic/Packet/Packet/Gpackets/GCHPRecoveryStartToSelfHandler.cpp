//////////////////////////////////////////////////////////////////////
//
// Filename    : GCHPRecoveryToOhtersHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCHPRecoveryStartToSelf.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToSelfHandler::execute ( GCHPRecoveryStartToSelf * pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY
		

	// item ��� ����
	//UseItemOK();

	if (g_pPlayer!=NULL)
	{
		DWORD delay = ConvertDurationToMillisecond( pPacket->getDelay() );
	
		g_pPlayer->SetRecoveryHP( pPacket->getQuantity(),
									pPacket->getPeriod(),
									delay );
	}	


	__END_CATCH
}
