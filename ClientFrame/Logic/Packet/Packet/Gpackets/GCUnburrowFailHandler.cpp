//////////////////////////////////////////////////////////////////////
//
// Filename    : GCUnburrowErrorHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCUnburrowFail.h"
#include "ClientDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCUnburrowFailHandler::execute ( GCUnburrowFail* pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

	
	//------------------------------------------------------------------
	// Player가 기다리던 skill의 성공유무를 검증받았다.
	//------------------------------------------------------------------
	if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_SKILL_SUCCESS)
	{		
		g_pPlayer->SetWaitVerifyNULL();
	}
	else
	{
		DEBUG_ADD("[Error] Player is not WaitVerifySkillSuccess");
	}


#endif

	__END_CATCH
}
