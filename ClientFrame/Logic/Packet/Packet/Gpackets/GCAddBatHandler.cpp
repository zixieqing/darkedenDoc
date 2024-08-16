//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddBatHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCAddBat.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddBatHandler::execute ( GCAddBat * pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	int batCreatureType = 185;

	_MinTrace("%d\n", pPacket->getBatColor() );

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
		//AfxMessageBox( pPacket->toString().c_str() );
		MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());

		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreatureWear;

			pCreature->SetZone( g_pZone );
			
			//pCreature->SetCreatureType( 0 );
			pCreature->SetCreatureType( batCreatureType );


			pCreature->SetName( pPacket->getName().c_str() );

			// �ӽ÷�
			pCreature->SetGuildNumber( pPacket->getGuildID() );

			pCreature->SetFlyingCreature();

			pCreature->SetID(pPacket->getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );

			
			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			//pPacket->getName()
			// ���� ����
			
			if( pPacket->getBatColor() != 0 )
				pCreature->SetBatColor( pPacket->getBatColor() );
			else
				pCreature->SetBatColor( 0xFFFF );
			

			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
			}
		}
		//--------------------------------------------------
		// �̹� �ִ� Creature�� ���
		//--------------------------------------------------
		else
		{
			//pCreature->SetCreatureType( batCreatureType );
			pCreature->SetFlyingCreature();
			
			// �ӽ÷�
			pCreature->SetGuildNumber( pPacket->getGuildID() );

			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			//pCreature->SetAction( ACTION_STAND );			

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			if( pPacket->getBatColor() != 0 )
				pCreature->SetBatColor( pPacket->getBatColor() );
			else
				pCreature->SetBatColor( 0xFFFF );

			//--------------------------------------------------
			// ����� �����ϴ� ���
			//--------------------------------------------------
			MActionResult* pResult = new MActionResult;

			pResult->Add( new MActionResultNodeChangeCreatureType( pCreature->GetID(), batCreatureType ) );

			//--------------------------------------------------
			// ���� ���� 
			//--------------------------------------------------								
			ExecuteActionInfoFromMainNode(
				RESULT_MAGIC_TRANSFORM_TO_BAT,										// ��� ��� ��ȣ
			
				pCreature->GetX(), pCreature->GetY(), 0,
				pCreature->GetDirection(),														// ��� ����
				
				OBJECTID_NULL,												// ��ǥ�� ���� ����
				pCreature->GetX(), pCreature->GetY(), 0, 
				
				0,													// ����� (����) ���� �ð�		
				
				pResult, //NULL,
				
				false);			// ��� ÷���� �����Ѵ�.

			//pCreature->SetDelay( 1000 );
		}	
	}

	// [����] Vampire�� ��Ÿ����
//	__BEGIN_HELP_EVENT
//		//ExecuteHelpEvent( HE_CREATURE_APPEAR_VAMPIRE );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
