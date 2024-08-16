//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSayHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCSay.h"
#include "ClientDef.h"
#include "UserInformation.h"
#include "MChatManager.h"
#include "MSkillManager.h"
#include "MZoneTable.h"	
#include "MZone.h"	
#include "UIFunction.h"
#include "MGameStringTable.h"

//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCSayHandler::execute ( GCSay * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
//#ifdef __GAME_CLIENT__

	// Debug Message	
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
		//---------------------------------------------------------------
		// ĳ���� �Ӹ� ���� ä���� ����.
		//---------------------------------------------------------------
		//DEBUG_ADD("Zone-GetCreature");

		MCreature*	pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		if (pCreature==NULL)
		{
			// �׷� ĳ���Ͱ� ������ �����Ѵ�.
			DEBUG_ADD("No such Character");
		}
		else
		{			
			bool IsGildre	= pCreature->GetCreatureType() == 717 || 
							  pCreature->GetCreatureType() == 723 ; // ���巹 �϶�
			bool bMasterWords = pCreature->GetCreatureType()==CREATURETYPE_SLAYER_OPERATOR
								|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_OPERATOR
								|| pCreature->GetCreatureType()==CREATURETYPE_OUSTERS_OPERATOR
								|| strncmp( pCreature->GetName(), (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetString(), (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetLength() ) == 0
								|| IsGildre ;
//								|| (strstr(pCreature->GetName(), "GM")!=NULL);

			//DEBUG_ADD_FORMAT("isMasterWords=%d", bMasterWords);

			//-------------------------------------------------
			// �������� ��ȭ
			//-------------------------------------------------
			if (bMasterWords 
				|| g_pChatManager->IsAcceptID( pCreature->GetName() ))
			{
				//DEBUG_ADD("can see");

				// ä��~~
				char str[256];

				bool isPlayerVampire = pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE1
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE1
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE2
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE2
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE3
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE3
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_OPERATOR
										|| pCreature->GetCreatureType()==CREATURETYPE_BAT
										|| pCreature->GetCreatureType()==CREATURETYPE_WOLF
										|| pCreature->GetCreatureType()==CREATURETYPE_WER_WOLF
										// add by coffee 2006.11.24  ��������
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE4
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE4
										//add by viva
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE5
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE5
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE6
										|| pCreature->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE6;
										// add end

				bool isPlayerCharacter = (isPlayerVampire 
											|| pCreature->IsSlayer()
											|| pCreature->IsOusters()
											|| pCreature->GetCreatureType()==CREATURETYPE_SLAYER_OPERATOR);

				//DEBUG_ADD("strcpy");
				
				//---------------------------------------------------------------
				// �ϼ��� --> ������
				//---------------------------------------------------------------
				//UI_WansungToJohap( pPacket->getMessage().c_str(), str );
				strcpy( str, pPacket->getMessage().c_str() );
				bool	bTranslation = g_pSkillAvailable->IsEnableSkill(SKILL_HOLYLAND_BLOOD_BIBLE_HILLEL) || 
					!g_pZoneTable->Get( g_pZone->GetID() )->ChatMaskByRace ||
					g_pPlayer->HasEffectStatus( EFFECTSTATUS_TRANSLATION ) ||
					g_pPlayer->GetCreatureType() == CREATURETYPE_SLAYER_OPERATOR ||
					g_pPlayer->GetCreatureType() == CREATURETYPE_VAMPIRE_OPERATOR ||
					g_pPlayer->GetCreatureType() == CREATURETYPE_OUSTERS_OPERATOR;

				//--------------------------------------------------
				// �� ����
				// ��ڰ� �� ���� �ƴϰ� ���� ��ڰ� �ƴϸ� filter�Ѵ�.
				// --> ����� ���� �� ���̰� ��ڴ� �� ����.
				//--------------------------------------------------
				if (!bMasterWords && !g_pUserInformation->IsMaster 
					&& !g_pPlayer->HasEffectStatus( EFFECTSTATUS_GHOST )
#ifdef __METROTECH_TEST__
				&& !g_bLight
#endif
					)
				{
				
					// player�� ��츸 ���۸� ����
					if (isPlayerCharacter)
					{
						DEBUG_ADD("remove curse");
						g_pChatManager->RemoveCurse( str );

						DEBUG_ADD("has effect");

						if (g_pPlayer->HasEffectStatus(EFFECTSTATUS_HALLUCINATION))
						{
							//DEBUG_ADD("add mask hallu");

							g_pChatManager->AddMask(str, 50);
						}

						//DEBUG_ADD("ok");
					}					 

					#ifndef _DEBUG
						//--------------------------------------------------
						// ������ �ٸ� ���
						//--------------------------------------------------
						if (g_pPlayer->GetRace() != pCreature->GetRace()
							// player�� ��츸.. �� ���..
							//&& isPlayerVampire 
							&& isPlayerCharacter
							&& !bTranslation 
							&& !g_pPlayer->HasEffectStatus( EFFECTSTATUS_GHOST )
#ifdef __METROTECH_TEST__
							&& !g_bLight
#endif
							)
						{
							//DEBUG_ADD("add mask1");

							// INT�� 150�����̹Ƿ�..  
							int percent;
//							if( g_pPlayer->IsOusters() )
//								percent = 70;
//							else
								percent = min(75, 25+g_pPlayer->GetINT()*100/(min(2, g_pPlayer->GetRace()+1)*150));
							
							g_pChatManager->AddMask(str, percent);

							//DEBUG_ADD("ok");
						}
//						else if (g_pPlayer->IsVampire() && pCreature->IsSlayer() && !bTranslation)
//						{
//							//DEBUG_ADD("add mask2");
//
//							// INT�� 300�����̹Ƿ�..  
//							int percent = min(75, 25+g_pPlayer->GetINT()*100/300);
//							g_pChatManager->AddMask(str, percent);
//
//							//DEBUG_ADD("ok");
//						}
						// �ҷ� ���´� ä�õ� ����� �� ���δ�.
						else if (g_pPlayer->HasEffectStatus(EFFECTSTATUS_HALLUCINATION))
						{
							//DEBUG_ADD("add mask3");

							g_pChatManager->AddMask(str, 50);

							//DEBUG_ADD("ok");
						}
					#endif
				}
				
				//DEBUG_ADD("setChat");

				pCreature->SetChatString( str, pPacket->getColor() );

				//DEBUG_ADD("ok");

				// history�� �߰�
				char strName[256];
				//sprintf(temp, "%s> %s", pCreature->GetName(), str);
				

				// ������ �ٸ��� hallu name�� �о�´�
				if(!bMasterWords && !g_pUserInformation->IsMaster && g_pPlayer->GetRace() != pCreature->GetRace() && !bTranslation)
					strcpy(strName, pCreature->GetHalluName());
				else
					strcpy(strName, pCreature->GetName());

				// player�� ��츸 ä��â�� �� �ִ´�.
				if (isPlayerCharacter /*|| IsGildre*/) // ���巹 �ϰ�� �� ä������ �����ٰ� �ؼ� ����..
				{
					//DEBUG_ADD("UI add");
					UI_AddChatToHistory( str, strName, 0, pPacket->getColor() );
					//DEBUG_ADD("UI add");
				}
			}
			//-------------------------------------------------
			// ��ȭ �źη� �����Ǿ� �ִٸ� ��¾��Ѵ�.
			//-------------------------------------------------
			else
			{
				//DEBUG_ADD("no see");
				pCreature->SetChatString( "......", pPacket->getColor() );
			}
		}
	}
//#endif

	__END_CATCH
}
