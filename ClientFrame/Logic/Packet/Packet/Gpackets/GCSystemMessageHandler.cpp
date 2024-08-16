//////////////////////////////////////////////////////////////////////
//
// Filename    : GCSystemMessageHandler.cc
// Written By  : elca
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCSystemMessage.h"
#include "ClientDef.h"
#include "UIFunction.h"
#include "MGameStringTable.h"
#include "Client.h"
//////////////////////////////////////////////////////////////////////
//
// Ŭ���̾�Ʈ���� �����κ��� �޽����� �޾����� ����Ǵ� �޽���̴�.
//
//////////////////////////////////////////////////////////////////////
void GCSystemMessageHandler::execute ( GCSystemMessage * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	static char previous1[128] = { NULL, };
	switch(pPacket->getType())
	{ 
		case SYSTEM_MESSAGE_HOLY_LAND :		// �ƴ��� ���� ����
			if(g_pUserOption->DoNotShowHolyLandMsg)
				return;
			break;

		case SYSTEM_MESSAGE_NORMAL:
			break;

		case SYSTEM_MESSAGE_OPERATOR:	// ��� ����
			break;
	
		case SYSTEM_MESSAGE_MASTER_LAIR:	// ������ ���� ����
			if(g_pUserOption->DoNotShowLairMsg)
				return;
			break;

		case SYSTEM_MESSAGE_COMBAT:		// ���� ����
			if(g_pUserOption->DoNotShowWarMsg)
				return;
			break;
	
		case SYSTEM_MESSAGE_INFO: 		// Ư���� ���� ����
			break;
			
		case SYSTEM_MESSAGE_RANGER_CHAT:
			{
				char* message = (char*)pPacket->getMessage().c_str();
				if(NULL != message)
				{
					UI_SetRangerChatString(message);
				}
			}
			return;
	
		case SYSTEM_MESSAGE_PLAYER:	    // add by Coffee 2007-8-2 ������ҷ��͹���
			char* message = (char*)pPacket->getMessage().c_str();

			if (NULL != message)
			{
				message = (char*)pPacket->getMessage().c_str();
// 				if (strcmp(previous1, message)==0)
// 				{
// 					BOOL bExist = FALSE;
// 
// 					//--------------------------------------------------------------------
// 					// �̹� �ִ� �޼������� �˻��Ѵ�.
// 					//--------------------------------------------------------------------
// 					for (int i=0; i<g_pPlayerMessage->GetSize(); i++)
// 					{
// 						if (strcmp((*g_pPlayerMessage)[i], message)==0)
// 						{
// 							bExist = TRUE;
// 						}
// 					}
// 
// 					//--------------------------------------------------------------------
// 					// ���°Ÿ� �߰��Ѵ�.		
// 					//--------------------------------------------------------------------
// 					if (!bExist)
// 					{
// 						g_pPlayerMessage->Add( message );
// 					}
// 				}
// 				//--------------------------------------------------------------------
// 				// ���ο� �޼����̸� �߰��Ѵ�.
// 				//--------------------------------------------------------------------
// 				else
// 				{
					g_pPlayerMessage->Add( message );

					strcpy( previous1, pPacket->getMessage().c_str() );
//				}
			}
			return;

			
	}

	static char previous[128] = { NULL, };

	const char* message = pPacket->getMessage().c_str();
	// add by Coffee 2007-8-2 ����ϵͳ��Ϣ����
		char *pMsg = NULL;
		if (message!=NULL && pPacket->getType() != SYSTEM_MESSAGE_PLAYER )
		{
			pMsg = new char[strlen(message)+20];
			sprintf(pMsg,(*g_pGameStringTable)[UI_STRING_MESSAGE_SYSTEM].GetString(),message);
			pPacket->setMessage(pMsg);
			SAFE_DELETE_ARRAY( pMsg );
		}
		message = pPacket->getMessage().c_str();
	// add end by Coffee 2007-8-2
	//--------------------------------------------------------------------
	// system message�� ���
	//--------------------------------------------------------------------
	if (strcmp(previous, message)==0)
	{
		BOOL bExist = FALSE;

		//--------------------------------------------------------------------
		// �̹� �ִ� �޼������� �˻��Ѵ�.
		//--------------------------------------------------------------------
		for (int i=0; i<g_pSystemMessage->GetSize(); i++)
		{
			if (strcmp((*g_pSystemMessage)[i], message)==0)
			{
				bExist = TRUE;
			}
		}

		//--------------------------------------------------------------------
		// ���°Ÿ� �߰��Ѵ�.		
		//--------------------------------------------------------------------
		if (!bExist)
		{
			g_pSystemMessage->Add( message );
		}
	}
	//--------------------------------------------------------------------
	// ���ο� �޼����̸� �߰��Ѵ�.
	//--------------------------------------------------------------------
	else
	{
		g_pSystemMessage->Add( message );

		strcpy( previous, pPacket->getMessage().c_str() );
	}

#endif

	__END_CATCH
}
