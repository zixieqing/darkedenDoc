//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSkillToObjectOK4Handler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCSkillToObjectOK4.h"
#include "ClientDef.h"
#include "PacketFunction2.h"
#include "SkillDef.h"
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK4Handler::execute ( GCSkillToObjectOK4 * pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY
		
#if __GAME_CLIENT__


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
		int skillID = pPacket->getSkillType();

		if( g_pActionInfoTable->GetSize() <= skillID )
		{
			DEBUG_ADD_FORMAT("[Error] Exceed SkillType %d",skillID);
			SendBugReport("[Error:GCSTOOK4H] Exceed SkillType %d(%d)", skillID, pPacket->getPacketID() );
			return;
		}

		if( (*g_pActionInfoTable)[skillID].IsUseActionStep() && pPacket->getGrade() > 0)
			skillID = (*g_pActionInfoTable)[skillID].GetActionStep( pPacket->getGrade() - 1);
		
			MCreature* pTargetCreature = g_pZone->GetCreature( pPacket->getTargetObjectID() );		

		// TargetCreature���� ��� ǥ��
		if (pTargetCreature != NULL)
		{
			// delay frame�� ���
			DWORD delayFrame = ConvertDurationToFrame( pPacket->getDuration() );

			// effect delay����
			pTargetCreature->SetEffectDelayFrame( pPacket->getSkillType(), delayFrame );

			// �ٷ� ��� ǥ��
			pTargetCreature->PacketSpecialActionResult( 
										skillID + (*g_pActionInfoTable).GetMinResultActionInfo(), 
										pTargetCreature->GetID(),
										pTargetCreature->GetX(),
										pTargetCreature->GetY()
			);

			//------------------------------------------------------
			// EffectStatus�� �ִٸ� ���δ�.
			//------------------------------------------------------
			EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();
			
			if (es!=EFFECTSTATUS_NULL)
			{
				pTargetCreature->AddEffectStatus( es, delayFrame );
			}

			if(skillID == SKILL_DRAGON_TORNADO)
			{
				pTargetCreature->SetTurning( 16 );
			}
		}
	}	

#endif

	__END_CATCH
}
