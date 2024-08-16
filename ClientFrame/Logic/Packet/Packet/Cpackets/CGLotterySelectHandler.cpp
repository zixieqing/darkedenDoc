//////////////////////////////////////////////////////////////////////////////
// Filename    : CGLotterySelectHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGLotterySelect.h"

#ifdef __GAME_SERVER__

#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "NPC.h"

#include "Gpackets/GCNoticeEvent.h"

#include <cstdio>

#endif	// __GAME_SERVER__

void CGLotterySelectHandler::execute (CGLotterySelect* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY 
		
#ifdef __GAME_SERVER__

	GamePlayer* pGP = dynamic_cast<GamePlayer*>( pPlayer );
	Assert( pGP != NULL );
		
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGP->getCreature());
	Assert( pPC != NULL );

	switch ( pPacket->getType() )
	{
		case TYPE_SELECT_LOTTERY:
			{
				GCNoticeEvent gcNE;
				gcNE.setCode( NOTICE_EVENT_RESULT_LOTTERY );
				gcNE.setParameter( (uint)rand()%2 );
				pGP->sendPacket( &gcNE );
			}
			break;
		case TYPE_FINISH_SCRATCH:
			{
				// Ȯ���ϰ� ��� �����ϱ�
				// ��Ŷ ���� �ÿ��忡 ��ε�ĳ�������ֱ�
				// ���� ����Ʈ �ٿ��ֱ�..

			}
			break;
		case TYPE_OVER_ENDING:
			{
				// ���δ�.
				pPC->setHP(0);
			}
			break;
	}


#endif	// __GAME_SERVER__
		
	__END_CATCH
}

