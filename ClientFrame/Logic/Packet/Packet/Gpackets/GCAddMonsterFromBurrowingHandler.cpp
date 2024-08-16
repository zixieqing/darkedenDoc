//////////////////////////////////////////////////////////////////////
//
// Filename    : GCAddMonsterFromBurrowingHandler.cpp
// Written By  : elca@ewestsoft.com
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCAddMonsterFromBurrowing.h"
#include "ClientDef.h"
#include "SkillDef.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCAddMonsterFromBurrowingHandler::execute ( GCAddMonsterFromBurrowing * pPacket , Player * pPlayer )
	 throw ( Error )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__

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

		// 2004, 9, 1, sobeit add start - �������� Ʈ���� ��� ������������ ������ �ʴ´�.
		WORD wMonsterType = pPacket->getMonsterType();
		if( wMonsterType == 738 ||
			wMonsterType == 739 ||
			wMonsterType == 740 ||
			wMonsterType == 741 )
		{
			EffectInfo* pTempEffectInfo = pPacket->getEffectInfo();
			
			if(NULL != pTempEffectInfo)
			{
				if(pTempEffectInfo->getListNum()>0)
				{
					std::list<WORD> TemList = pTempEffectInfo->GetList();
					
					std::list<WORD>::iterator itr = TemList.begin();
					bool bCheck = true;
					while(itr != TemList.end())
					{
						if(bCheck)
						{
							EFFECTSTATUS	status		= (EFFECTSTATUS)*itr;
							
							if(status == EFFECTSTATUS_HIDE_TO_ATTACKER)
							{
								if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_1) || 
									g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_2) || 
									g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_3) || 
									g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_4) || 
									g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_5) )
									return;
							}
						}
						bCheck = !bCheck;

						itr ++ ;
					}
				}			

			}
		}
		// 2004, 9, 1, sobeit add end - �������� Ʈ���� ��� ������������ ������ �ʴ´�.
		//--------------------------------------------------
		// ���ο� Creature�̸� �߰�
		//--------------------------------------------------
		if (pCreature==NULL)
		{
			pCreature = new MCreature;

			pCreature->SetZone( g_pZone );

			//pCreature->SetCreatureType( 0 );
			pCreature->SetCreatureType( pPacket->getMonsterType() );
			pCreature->SetGroundCreature();
			pCreature->SetID(pPacket->getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			// [ TEST CODE ]
			// �̸� ����
			//char str[20];
			//sprintf(str, "ID=%d", pCreature->GetID());
			//pCreature->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
			pCreature->SetName( pPacket->getMonsterName().c_str() );

			// �ӽ÷�..
			pCreature->SetGuildNumber( 1 );

			// �̸�
			//pCreature->SetName( pPacket->getName().toString().c_str() );

			// ���� ����
			

			if (!g_pZone->AddCreature( pCreature ))
			{
				delete pCreature;
				pCreature = NULL;
			}
			else
			{				
				//------------------------------------------------------------
				// Load���� �ʾ����� load�Ѵ�.
				//------------------------------------------------------------
//				LoadCreatureType( pPacket->getMonsterType() );			
			}
		}
		//--------------------------------------------------
		// �̹� �ִ� Creature�� ���
		//--------------------------------------------------
		else
		{
			//pCreature->SetCreatureType( 0 );
			pCreature->SetCreatureType( pPacket->getMonsterType() );
			pCreature->SetGroundCreature();
			pCreature->SetID(pPacket->getObjectID());
			//pCreature->SetAction(ACTION_MOVE);
			pCreature->MovePosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
			pCreature->SetDirection( pPacket->getDir() );
			pCreature->SetCurrentDirection( pPacket->getDir() );
			pCreature->SetAction( ACTION_STAND );

			pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
			pCreature->SetStatus( MODIFY_CURRENT_HP, pPacket->getCurrentHP() );

			// [ TEST CODE ]
			// �̸� ����
			//char str[20];
			//sprintf(str, "ID=%d", pCreature->GetID());
			//pCreature->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
			pCreature->SetName( pPacket->getMonsterName().c_str() );

			// �ӽ÷�..
			pCreature->SetGuildNumber( 1 );

			// �̸�
			//pCreature->SetName( pPacket->getName().toString().c_str() );

			// ���� ����

			//------------------------------------------------------------
			// Load���� �ʾ����� load�Ѵ�.
			//------------------------------------------------------------
//			LoadCreatureType( pPacket->getMonsterType() );			
		}

		//--------------------------------------------------
		// Effect ���̱�..
		//--------------------------------------------------
		if (pCreature!=NULL)
		{
			SetEffectInfo( pCreature, pPacket->getEffectInfo() );		
			// 2004, 8, 31, sobeit add start - Ʈ���� ����Ʈ ����
			switch(pCreature->GetCreatureType())
			{
				case 739: // Ʈ�� - ���� ����
					ExecuteActionInfoFromMainNode(SKILL_CLIENT_LAND_MINE_LIGHT,pCreature->GetX(), pCreature->GetY(), 0,pCreature->GetDirection(),	pCreature->GetID(),	
								pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
					break;
				case 738: // Ʈ�� - �÷��� �����̼�
					ExecuteActionInfoFromMainNode(SKILL_CLIENT_PLEASUER_STATION_LIGHT,pCreature->GetX(), pCreature->GetY(), 0,pCreature->GetDirection(),	pCreature->GetID(),	
								pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
					break;
			}
			// 2004, 8, 31, sobeit add end -
			//--------------------------------------------------
			// Burrow���� ���������� Effect == Burrowing�ϴ� Effect
			//--------------------------------------------------		
			ExecuteActionInfoFromMainNode(
				RESULT_MAGIC_HIDE,										// ��� ��� ��ȣ
			
				pCreature->GetX(), pCreature->GetY(), 0,
				pCreature->GetDirection(),														// ��� ����
				
				OBJECTID_NULL,												// ��ǥ�� ���� ����
				pCreature->GetX(), pCreature->GetY(), 0, 
				
				0,													// ����� (����) ���� �ð�		
				
				NULL,
				
				false);			// ��� ÷���� �����Ѵ�.
		}
	}

	// [����] ���� ��Ÿ����
//	__BEGIN_HELP_EVENT
////		ExecuteHelpEvent( HE_CREATURE_APPEAR_MONSTER );
//	__END_HELP_EVENT

#endif

	__END_CATCH
}
