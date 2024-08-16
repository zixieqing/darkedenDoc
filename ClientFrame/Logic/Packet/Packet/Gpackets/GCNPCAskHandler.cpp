//////////////////////////////////////////////////////////////////////
//
// Filename    : GCNPCAskHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCNPCAsk.h"
#include "ClientDef.h"
#include "TalkBox.h"
#include "UIDialog.h"
#include "MNPCScriptTable.h"
#include "TempInformation.h"
#include "SystemAvailabilities.h"

//////////////////////////////////////////////////////////////////////
//
// 클라이언트에서 서버로부터 메시지를 받았을때 실행되는 메쏘드이다.
//
//////////////////////////////////////////////////////////////////////
void GCNPCAskHandler::execute ( GCNPCAsk * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	if (g_pPlayer==NULL
		|| g_pZone==NULL
		|| g_pNPCScriptTable==NULL
		|| g_pUIDialog==NULL
		|| g_pPCTalkBox==NULL)
	{
		DEBUG_ADD("[Error] Some Object is NULL");
		return;
	}


	if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_NPC_ASK)
	{
		g_pPlayer->SetWaitVerifyNULL();
		
		// NPC
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );
		
//		pPacket->

		if (pCreature!=NULL || pPacket->getNPCID() >= 634 && pPacket->getNPCID() <= 637 )
		{		
			unsigned int CreatureType;

			if(pPacket->getNPCID() >= 634 && pPacket->getNPCID() <= 637 )
			{
				CreatureType = pPacket->getNPCID();
			} else
			{
				CreatureType= pCreature->GetCreatureType();
			}
			
			//---------------------------------------------------
			// g_PCTalkBox에 추가하면 된다.
			//---------------------------------------------------
			// 기존에 있던것 제거
			g_pPCTalkBox->Release();

			DEBUG_ADD("TalkBoxRel");

			//---------------------------------------------------
			// normal
			//---------------------------------------------------
			g_pPCTalkBox->SetType( PCTalkBox::NORMAL );

			
			int scriptID = pPacket->getScriptID();

			//---------------------------------------------------
			// PC Talk Box의 정보 설정
			//---------------------------------------------------
			// SetContent라고 이름이 되어있지만.. Subject이다. - -;
			g_pPCTalkBox->SetContent( g_pNPCScriptTable->GetSubject(scriptID, 0) );
			g_pPCTalkBox->SetNPCID( pPacket->getObjectID() );
			g_pPCTalkBox->SetCreatureType( CreatureType );
			g_pPCTalkBox->SetScriptID( scriptID );

			DEBUG_ADD("SetScript");

			//---------------------------------------------------
			// 각 std::string 추가
			//---------------------------------------------------
			int contentSize = g_pNPCScriptTable->GetContentSize( scriptID );

			g_pPCTalkBox->m_AnswerIDMap.clear();

			int idnum=0;
			
			for (int i=0; i<contentSize; i++)
			{
				// g_PCTalkBox에 추가
				if( g_pSystemAvailableManager->ScriptFiltering( scriptID, i ) )
				{
					g_pPCTalkBox->AddString( g_pNPCScriptTable->GetContent( scriptID, i ) );
					g_pPCTalkBox->m_AnswerIDMap.push_back( i );
				}				
			}

			DEBUG_ADD("SetContent");
			
			g_pUIDialog->PopupPCTalkDlg();
		}

		//---------------------------------------------------
		// Dialog를 띄운다.
		//---------------------------------------------------
		//POINT point = ConvertPositionMapToScreen(pCreature->GetX(), pCreature->GetY());

		//point.y -= pCreature->GetHeight();

		//g_pUIDialog->PopupPCTalkDlg(point.x, point.y - size*20-100);							
	}
	else
	{
		DEBUG_ADD("[Error] WaitVerifyMode is Not WAIT_VERIFY_NPC_ASK");
	}

	
#endif

	__END_CATCH
}
