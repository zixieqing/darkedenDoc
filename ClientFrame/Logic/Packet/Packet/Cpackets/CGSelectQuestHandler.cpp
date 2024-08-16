//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectQuestHandler.cpp
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGSelectQuest.h"

#ifdef __GAME_SERVER__

#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "mission/QuestManager.h"
#include "mission/QuestInfoManager.h"

#include "Gpackets/GCNPCResponse.h"

#include <cstdio>

#endif	// __GAME_SERVER__

void CGSelectQuestHandler::execute (CGSelectQuest* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY 
		
#ifdef __GAME_SERVER__

	GamePlayer* pGP = dynamic_cast<GamePlayer*>( pPlayer );
	Assert( pGP != NULL );
		
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGP->getCreature());

	GCNPCResponse gcNPCR;
	gcNPCR.setCode( NPC_RESPONSE_QUEST );

	Creature* pCreature = pPC->getZone()->getCreature( pPacket->getNPCObjectID() );
	if ( pCreature == NULL || !pCreature->isNPC() )
	{
		gcNPCR.setParameter( (uint)START_FAIL_CANNOT_APPLY_QUEST );
		pPlayer->sendPacket( &gcNPCR );

		return;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pCreature);
	if ( pNPC == NULL )
	{
		gcNPCR.setParameter( (uint)START_FAIL_CANNOT_APPLY_QUEST );
		pPlayer->sendPacket( &gcNPCR );

		return;
	}

	QuestInfoManager* pQIM = pNPC->getQuestInfoManager();
	if ( pQIM == NULL )
	{
		gcNPCR.setParameter( (uint)START_FAIL_CANNOT_APPLY_QUEST );
		pPlayer->sendPacket( &gcNPCR );

		return;
	}

	pPC->getQuestManager()->adjustQuestStatus();
	QuestMessage code = pQIM->startQuest( pPacket->getQuestID(), pPC );

	gcNPCR.setParameter( (uint)code );

	pPlayer->sendPacket( &gcNPCR );

	if ( code == START_SUCCESS )
	{
		pPC->sendCurrentQuestInfo();

		//cout << "Quest ���� " << pPC->getName() << " " << pPacket->getQuestID() << endl;
	}
	else
	{
		//cout << "Quest ���� ���� " << pPC->getName() << " " << (int)code << endl;
	}

#endif	// __GAME_SERVER__
		
	__END_CATCH
}

