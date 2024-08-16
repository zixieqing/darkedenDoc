//----------------------------------------------------------------------
//
// Filename    : LCWorldListHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "LCWorldList.h"
#include "ClientDef.h"
#include "ServerInformation.h"
#include "DebugInfo.h"
#include "UIFunction.h"

//----------------------------------------------------------------------
// �����κ��� ĳ���� ����Ʈ�� �޾Ҵ�. 
// ���� ĳ���� ���� �������̽��� ������ ���� ���۹��� ���� ���� �־
// �������.
//----------------------------------------------------------------------
void LCWorldListHandler::execute ( LCWorldList * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

	//-----------------------------------------------------------
	// Server Information �ʱ�ȭ
	//-----------------------------------------------------------
	if (g_pServerInformation==NULL)
	{
		g_pServerInformation = new ServerInformation;
	}
	else
	{
		g_pServerInformation->Release();
	}

	int currentID = pPacket->getCurrentWorldID();
	
	bool bExistDefault = false;

	//-----------------------------------------------------------
	// Server���� ����
	//-----------------------------------------------------------
	int groupNum = pPacket->getListNum();
	int firstID = 0;

	for (int i=0; i<groupNum; i++)
	{
		WorldInfo* pWorldInfo = pPacket->popFrontListElement();

		if (pWorldInfo!=NULL)
		{
			if (i==0)
			{
				firstID = pWorldInfo->getID();
			}

			if (pWorldInfo->getID()==currentID)
			{
				bExistDefault = true;
			}

			//--------------------------------------------------------------
			// ���ο� ServerGroup�� ���� ����
			//--------------------------------------------------------------
			ServerGroup* pNewGroup = g_pServerInformation->GetData( pWorldInfo->getID() );
			
			if (pNewGroup==NULL)
			{
				pNewGroup = new ServerGroup;
				g_pServerInformation->AddData( pWorldInfo->getID(), pNewGroup );
			}

			// Group�� ���� ����			
			pNewGroup->SetGroupName( pWorldInfo->getName().c_str() );
			pNewGroup->SetGroupStatus( (int)pWorldInfo->getStat() );
			
			//--------------------------------------------------------------
			// ������ Server�� ���� ���� ����
			//--------------------------------------------------------------
			/*
			int serverNum = pWorldInfo->getListNum();

			for (int j=0; j<serverNum; j++)
			{
				SubServerInfo* pServerInfo = pWorldInfo->popFrontListElement();
				
				if (pServerInfo!=NULL)
				{
					//--------------------------------------------------------------
					// ServerGroup�� Server �߰�
					//--------------------------------------------------------------
					SERVER_INFO* pNewServer = new SERVER_INFO;

					pNewServer->ServerName		= pServerInfo->getServerName().c_str();
					pNewServer->ServerStatus	= (SERVER_INFO::SERVER_STATUS)pServerInfo->getServerStat();
					
					pNewGroup->AddData( pServerInfo->getServerID(), pNewServer );					

					delete pServerInfo;
				}
				else
				{
					DEBUG_ADD( "[Error] SubServerGroupInfo is NULL" );
				}
			}
			*/

			delete pWorldInfo;
		}
		else
		{
			DEBUG_ADD( "[Error] ServerGroupInfo is NULL" );
		}	
	}

	// default ����
	if (currentID==0 || !bExistDefault)
	{
		g_pServerInformation->SetServerGroupID( firstID );
	}
	else
	{
		g_pServerInformation->SetServerGroupID( currentID );
	}

	UI_SetWorldList();

	SetMode( MODE_WAIT_SELECT_WORLD );

#endif
		
	__END_CATCH
}
