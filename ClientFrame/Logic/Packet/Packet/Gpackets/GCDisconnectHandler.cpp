//////////////////////////////////////////////////////////////////////
//
// Filename    : GCDisconnectHandler.cpp
// Written By  : Reiot
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCDisconnect.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCDisconnectHandler::execute ( GCDisconnect * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	
	#if	defined(OUTPUT_DEBUG) && defined(__DEBUG_OUTPUT__)
		//cout << pPacket->toString() << endl;
	#endif

#endif

	__END_CATCH
}
