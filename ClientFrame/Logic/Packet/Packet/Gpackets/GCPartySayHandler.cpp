//--------------------------------------------------------------------------------
//
// Filename    : GCPartySayHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "GCPartySay.h"
#include "Player.h"
#include "ClientDef.h"
#include "UserInformation.h"
#include "MChatManager.h"
#include "UIFunction.h"
#include "MGameStringTable.h"

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCPartySayHandler::execute ( GCPartySay * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY 
		
#ifdef __GAME_CLIENT__
	if ((g_Mode==MODE_GAME
			|| g_Mode==MODE_WAIT_UPDATEINFO			// �ε� ���� �ƴϰų�..
			|| g_Mode==MODE_WAIT_SETPOSITION		// ��ǥ ��ٸ��� ���
			)
		&& g_pUserInformation!=NULL
		&& g_pChatManager!=NULL)
	{
		//g_pClientCommunicationManager->sendPacket( pPacket->getHost() , pPacket->getPort() , &glIncomingConnectionOK );
		char str[128];
		char strName[128];
		strcpy(str, pPacket->getMessage().c_str());
		strcpy(strName, pPacket->getName().c_str());

		//bool bMasterWords = (strstr(strName, "GM")!=NULL);
		bool bMasterWords = strncmp( strName, (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetString(), (*g_pGameStringTable)[UI_STRING_MESSAGE_MASTER_NAME].GetLength() ) == 0;

		if (bMasterWords 
			|| g_pChatManager->IsAcceptID( strName ))
		{
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
				g_pChatManager->RemoveCurse( str );

				/*
				// RCSay���� mask�� ������ �ʴ´�.
				#ifndef _DEBUG
					//--------------------------------------------------
					// ������ �ٸ� ���
					//--------------------------------------------------
					bool bVampireSay = pPacket->getRace();
					if (g_pPlayer->IsSlayer() && bVampireSay)
					{
						// INT�� 150�����̹Ƿ�..  
						int percent = min(75, 25+g_pPlayer->GetINT()*100/150);
						g_pChatManager->AddMask(str, percent);
					}
					else if (g_pPlayer->IsVampire() && !bVampireSay)
					{
						// INT�� 300�����̹Ƿ�..  
						int percent = min(75, 25+g_pPlayer->GetINT()*100/300);
						g_pChatManager->AddMask(str, percent);
					}
				#endif
				*/
			}

			//sprintf(str, "<%s> %s", pPacket->getName().c_str(), pPacket->getMessage().c_str());
			// party = 3
			UI_AddChatToHistory( str, strName, 3, pPacket->getColor() );

			// �ӼӸ� ��� ���� ID+' '
			//char strWhisperID[128];
			//sprintf(strWhisperID, "%s ", pPacket->getName().c_str());
			//g_pUserInformation->WhisperID = strWhisperID;

			// [����] �ӼӸ� ���� ��
//			__BEGIN_HELP_EVENT
////				ExecuteHelpEvent( HE_CHAT_WHISPERED );	
//			__END_HELP_EVENT
		}
	}
		
#endif

	__END_CATCH
}
