
//////////////////////////////////////////////////////////////////////
//
// Filename    : GCNotifyWinHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCNotifyWin.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCNotifyWinHandler::execute ( GCNotifyWin * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY 
	
#ifdef __GAME_CLIENT__
	UI_RunImageNotice( pPacket->getName().c_str(), pPacket->getGiftID() );
#endif

	__END_CATCH
}
