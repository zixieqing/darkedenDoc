//////////////////////////////////////////////////////////////////////
//
// Filename    : GCGuildMemberListHandler.cpp
// Written By  : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCGuildMemberList.h"
#include "clientdef.h"
#include "UIFunction.h"
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void GCGuildMemberListHandler::execute ( GCGuildMemberList * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	UI_ShowGuildMemberList(pPacket);
#endif

	__END_CATCH
}
