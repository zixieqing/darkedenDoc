//--------------------------------------------------------------------------------
//
// Filename    : GCNoticeEventHandler.cpp
// Written By  : elca, Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "GCNoticeEvent.h"
#include "MEventManager.h"
#include "MGameStringTable.h"
#include "CMessageArray.h"
#include "MWarManager.h"
#include "UserInformation.h"
#include "MPlayer.h"

#ifdef __GAME_CLIENT__
#include "ClientPlayer.h"
#include "MZoneTable.h"
#include "MZone.H"
#include "UiFunction.h"
#include "PacketFunction.h"
#endif

#include "DebugInfo.h"
#include "UIDialog.h"
#include "MPriceManager.h"
#include "VS_UI.h"
extern void	SetFlagTo( bool bTae );


extern CMessageArray*				g_pSystemMessage;
extern bool							g_bZoneSafe;
extern bool							g_bEventQuestEnding;
extern CMessageArray*				g_pNoticeMessage;

extern int		g_LeftPremiumDays;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCNoticeEventHandler::execute ( GCNoticeEvent * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

//	char szBuffer[256];

//	wsprintf(szBuffer,"%d : 0x%x",pPacket->getCode(), pPacket->getParameter() );
//	_MinTrace( szBuffer );
		
#ifdef __GAME_CLIENT__

	MEvent event;

	if(NULL == pPacket) return;

	
	switch(pPacket->getCode())
	{
	case NOTICE_EVENT_SHOP_TAX_CHANGE :
		event.eventID = EVENTID_TAX_CHANGE;
		event.eventType = EVENTTYPE_ZONE;
		event.eventDelay = -1;
		event.parameter1 = pPacket->getParameter();
		g_pEventManager->AddEvent(event);
		break;
		
	case NOTICE_EVENT_MASTER_COMBAT_TIME:
		event.eventID = EVENTID_COMBAT_MASTER;
		event.eventType = EVENTTYPE_ZONE;
		event.eventFlag = EVENTFLAG_SHOW_DELAY;
		event.eventDelay = pPacket->getParameter()*1000;
		g_pEventManager->AddEvent(event);
		break;
		
	case NOTICE_EVENT_MASTER_COMBAT_END:
		g_pEventManager->RemoveEvent(EVENTID_COMBAT_MASTER);
		break;
		
	case NOTICE_EVENT_KICK_OUT_FROM_ZONE:
		event.eventID = EVENTID_KICK_OUT_FROM_ZONE;
		event.eventType = EVENTTYPE_ZONE;
		event.eventFlag = EVENTFLAG_SHOW_DELAY | EVENTFLAG_SHAKE_SCREEN | EVENTFLAG_SHOW_DELAY_STRING;
		event.eventDelay = pPacket->getParameter()*1000;
		event.parameter3 = 5;
		event.m_StringsID.push_back(STRING_MESSAGE_DISMISS_AFTER_SECOND);
		g_pEventManager->AddEvent(event);
		g_pEventManager->RemoveEvent(EVENTID_COMBAT_MASTER);
		break;
		
	case NOTICE_EVENT_CONTINUAL_GROUND_ATTACK:
		event.eventID = EVENTID_CONTINUAL_GROUND_ATTACK;
		event.eventType = EVENTTYPE_ZONE;
		event.eventFlag = EVENTFLAG_FADE_SCREEN | EVENTFLAG_SHAKE_SCREEN;
		event.parameter2 = 30 << 16;
		event.parameter3 = 5;
		event.eventDelay = pPacket->getParameter()*1000;
		g_pEventManager->AddEvent(event);
		break;
		
	case NOTICE_EVENT_CONTINUAL_GROUND_ATTACK_END:
		g_pEventManager->RemoveEvent(EVENTID_CONTINUAL_GROUND_ATTACK);
		break;
		
	case NOTICE_EVENT_PREMIUM_HALF_START:			// �����̾� ����ڴ� ����/��û �ݰ�
		event.eventID = EVENTID_PREMIUM_HALF;
		event.eventType = EVENTTYPE_ZONE;
		event.eventDelay = -1;
		g_pEventManager->AddEvent(event);
		if(g_pPlayer->IsSlayer())
			g_pSystemMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_PREMIUM_HALF_SLAYER].GetString() );
		else
			g_pSystemMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_PREMIUM_HALF_VAMPIRE].GetString() );
		//			g_pPlayer->AddEffectStatus(EFFECTSTATUS_SHARP_SHIELD_1, 0xffff);
		break;
		
	case NOTICE_EVENT_PREMIUM_HALF_END:				// �̺�Ʈ ��
		g_pEventManager->RemoveEvent(EVENTID_PREMIUM_HALF);
		if(g_pPlayer->IsSlayer())
			g_pSystemMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_PREMIUM_HALF_SLAYER_END].GetString() );
		else
			g_pSystemMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_PREMIUM_HALF_VAMPIRE_END].GetString() );
		//			g_pPlayer->RemoveEffectStatus(EFFECTSTATUS_SHARP_SHIELD_1);
		break;

	case NOTICE_EVENT_WAR_OVER :					// ���ﳡ		
		if( g_pWarManager->IsExist( g_pZone->GetID()) )
		{
			// �������� ���� ����Ʈ�� ������ �������� �ٽ� ����.
			g_bZoneSafe = g_pZoneTable->Get(g_pZone->GetID())->Safety;
		}
		g_pWarManager->RemoveWar(pPacket->getParameter());
		break;

	case NOTICE_EVENT_RACE_WAR_OVER:
		if(g_pWarManager != NULL)
			g_pWarManager->ClearRaceWar();
//		UI_SetBloodBibleStatusTimer(30);
//		UI_CloseBloodBibleStatus();
		UI_DeleteNotice(6);
		break;

	case NOTICE_EVENT_WELCOME_MESSAGE :
		UI_RunWelcomeMessage();		
		break;
		
	case NOTICE_EVENT_MEET_GRANDMA :					// �ҸӴ� ��ȭ
		break;

	case NOTICE_EVENT_MEET_FISHSHOP_MASTER :			// ���������� ��ȭ
		break;			

	case NOTICE_EVENT_START_QUEST_ENDING :			// ����Ʈ ���� ����
		{
			g_bEventQuestEnding = true;
		}
		break;

	case NOTICE_EVENT_RESULT_LOTTERY :
		UI_LotteryResult(  pPacket->getParameter() > 0 );
		break;
		
	case NOTICE_EVENT_RUN_HORN:
		UI_RunHorn(g_pZone->GetID());
		break;

	case NOTICE_EVENT_MASTER_LAIR_OPEN :
	case NOTICE_EVENT_MASTER_LAIR_CLOSED :
	case NOTICE_EVENT_MASTER_LAIR_COUNT :
		// ���� ���� �ð�, �������� ZoneID
		UI_MasterLairMessage(BYTE(pPacket->getCode() - NOTICE_EVENT_MASTER_LAIR_OPEN), HIWORD(pPacket->getParameter()), LOWORD( pPacket->getParameter() ) );
		break;
	
	case NOTICE_EVENT_CONTRACT_GNOMES_HORN :          // �ÿ������� ���� ����� �����ž� ����Ͻ� �� �ֽ��ϴ�.
		UI_PopupMessage( STRING_MESSAGE_CONTRACT_GNOMES_HORN );
		break;
    
	case NOTICE_EVENT_NOT_ENOUGH_MONEY :              // ���� ���ڶ��ϴ�.
		UI_PopupMessage( STRING_MESSAGE_WAR_NOT_ENOUGH_MONEY );
		break;		
	
	case NOTICE_EVENT_MINI_GAME:
		UI_RunMinigame(pPacket->getParameter());
		break;
	
	case NOTICE_EVENT_GET_RIFINIUM :					// ���ǴϿ��� ȹ���Ͽ����ϴ�.
		UI_PopupMessage(STRING_MESSAGE_GET_RIFINIUM);
		break;
	
	case NOTICE_EVENT_INVENTORY_FULL :				// �κ��丮 ���� ���� ������ �����մϴ�.
		UI_PopupMessage(UI_STRING_MESSAGE_INVENTORY_FULL_MONSTER_KILL_QUEST);
		break;
		
	case NOTICE_EVENT_FLAG_WAR_READY :                // 5�еڿ� Capture the Flag! �̺�Ʈ�� �ǽ��մϴ�.
		g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_FLAG_WAR_READY].GetString() );
		UI_RunNotice(2, pPacket->getParameter());
		break;

    case NOTICE_EVENT_FLAG_WAR_START :                // Capture the Flag! �̺�Ʈ�� ���۵Ǿ����ϴ�.
		g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_FLAG_WAR_START].GetString() );		
		break;

	case NOTICE_EVENT_FLAG_WAR_FINISH:               // Capture the Flag! �̺�Ʈ�� %s�� �¸��� �������ϴ�. 3�� �� �������� �����ϴ�.
		{
			int raceString[3] = {STRING_MESSAGE_SLAYER, STRING_MESSAGE_VAMPIRE, STRING_MESSAGE_OUSTERS};
			g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_FLAG_WAR_FINISH].GetString() );
			g_pNoticeMessage->AddFormat( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_FLAG_WAR_WINNER].GetString(), (*g_pGameStringTable)[raceString[min(2,max(0,HIWORD(pPacket->getParameter())))]].GetString() ,  LOWORD(pPacket->getParameter()));
			g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_FLAG_WILL_POUR_ITEM_AFTER_3MIN].GetString() );
			
			MEvent event;
			event.eventID = EVENTID_POUR_ITEM;
			event.eventDelay = 180000;
			event.eventFlag = EVENTFLAG_SHOW_DELAY_STRING;
			event.eventType = EVENTTYPE_ZONE;
			event.m_StringsID.push_back(STRING_MESSAGE_POUR_ITEM_AFTER_SECOND);

			g_pEventManager->AddEvent(event);
		}
		UI_CloseCTFStatusWindow();
		UI_DeleteNotice(2);
		break;

	case NOTICE_EVENT_FLAG_POURED_ITEM :
		g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_FLAG_POURED_ITEM].GetString() );
		break;

	case NOTICE_EVENT_ENTER_BEGINNER_ZONE :
		UI_RunNotice(1, pPacket->getParameter());
		break;

	case NOTICE_EVENT_LOGIN_JUST_NOW:
		if( g_pNoticeMessage != NULL && g_pGameStringTable != NULL && g_LeftPremiumDays != 0xFFFE && g_LeftPremiumDays >= 0 && g_LeftPremiumDays <=5 )
		{
			g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EXPIRE_PREMIUM_SERVICE_MESSAGE_1].GetString() );
			g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EXPIRE_PREMIUM_SERVICE_MESSAGE_2].GetString() );
			g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EXPIRE_PREMIUM_SERVICE_MESSAGE_3].GetString() );
		}
		// �Ӹ������� ������ �����Ѵ�
		g_pUserInformation->HeadPrice = (int)pPacket->getParameter();
		SendCrashReport();
		break;

	case NOTICE_EVENT_LEVEL_WAR_ARRANGED :            // �� ������ ������ ���۵˴ϴ�.
//		UI_RunLevelWarArranged( pPacket->getParameter() );
		UI_RunNotice(3, pPacket->getParameter());
		break;

	case NOTICE_EVENT_LEVEL_WAR_STARTED :             // ������ ������ ���۵Ǿ����ϴ�.
//		UI_RunLevelWarStarted( pPacket->getParameter() );
		UI_RunNotice(4, pPacket->getParameter());
		UI_DeleteNotice(3);
		break;
		
	case NOTICE_EVENT_RACE_WAR_SOON:
		UI_RunNotice(5, pPacket->getParameter());
		break;
		
	case NOTICE_EVENT_LEVEL_WAR_OVER:
		g_pWarManager->RemoveWar(g_pZone->GetID());
		break;
		
	case NOTICE_EVENT_NETMARBLE_CARD_FULL:
		g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_NETMARBLE_1].GetString() );
		g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_NETMARBLE_2].GetString() );
		g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_NETMARBLE_3].GetString() );
		g_pNoticeMessage->Add( (*g_pGameStringTable)[STRING_MESSAGE_EVENT_NETMARBLE_4].GetString() );
		break;
		
	case NOTICE_EVENT_HOLYDAY:
		SetFlagTo( pPacket->getParameter() != 0 );
		break;
		
	case NOTICE_EVENT_CAN_PET_QUEST :
		UI_RunNotice(7, 0);
		break;
	case  NOTICE_EVENT_SEND_SMS:
		UI_RunNotice(8, 0);
		break;
	case NOTICE_EVENT_GDR_LAIR_ENDING_1: // ���巹�� 1�� ���� - 5�ʰ� ȭ�� ���� �� 10�ʰ� ��ο���
		event.eventID = EVENTID_GDR_PRESENT;
		event.eventType = EVENTTYPE_ZONE;
		event.eventFlag = EVENTFLAG_SHAKE_SCREEN;
		event.parameter3 = 2;
		event.eventDelay =5000; // 5 ��
		g_pEventManager->AddEvent(event);
		//SetFadeStart(31, -1, 1, 0,0,0, 4);
		break;
	case NOTICE_EVENT_GOLD_MEDALS:
		{
			char szBuf[128];
			sprintf(szBuf, (*g_pGameStringTable)[UI_STRING_NOTICE_EVENT_GOLD_MEDALS].GetString(), pPacket->getParameter());
			g_pSystemMessage->Add( szBuf );
		}
		break;
	
	case NOTICE_EVENT_CROWN_PRICE:
		{
			int Value = pPacket->getParameter();
			g_pPriceManager->SetEventItemPrice( Value );
			char szBuf[128];
			sprintf(szBuf, (*g_pGameStringTable)[UI_STRING_CHANGE_EVENTITEM_PRICE].GetString(), Value);
			g_pSystemMessage->Add( szBuf );
		}
		break;
	case NOTICE_EVENT_GIVE_PRESENT_1:                // ���� 1 �������� ����ϴ�.
			//g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_1].GetString());
			gC_vs_ui.RunPopupMessage((*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_1].GetString(),C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
			//UI_PopupMessage(STRING_MESSAGE_DAUM_EVENT_1); 
		break;
    case NOTICE_EVENT_GIVE_PRESENT_2:                // ���� 2 �������� ����ϴ�.
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_2].GetString(), 5,(*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_BOX2].GetString());
			//g_pUIDialog->PopupFreeMessageDlg(szBuf);
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
		}
		break;
    case NOTICE_EVENT_GIVE_PRESENT_3:                // ���� 3 �������� ����ϴ�.
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_2].GetString(), 10,(*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_BOX3].GetString());
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
		}
		break;
    case NOTICE_EVENT_GIVE_PRESENT_4:                // ���� 4 �������� ����ϴ�.
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_2].GetString(), 15,(*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_BOX4].GetString());
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
		}
		break;
    case NOTICE_EVENT_GIVE_PRESENT_5:                // ���� 5 �������� ����ϴ�.
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_2].GetString(), 20,(*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_BOX5].GetString());
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
		}
		break;
    case NOTICE_EVENT_GIVE_PRESENT_6:                // ���� 6 �������� ����ϴ�
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_2].GetString(), 25,(*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_BOX6].GetString());
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
		}
		break;
    case NOTICE_EVENT_GIVE_PRESENT_7:                // ���� 7 �������� ����ϴ�.
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_2].GetString(), 30,(*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_BOX7].GetString());
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
		}
		break;
    case NOTICE_EVENT_GIVE_PRESENT_8:                // ���� 8 �������� ����ϴ�.
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_2].GetString(), 35,(*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_BOX8].GetString());
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_LARGE);
		}
		break;
    case NOTICE_EVENT_CAN_OPEN_PRESENT_8:            // ���� 8 �������� �� �� �ֽ��ϴ�.
		{
			char szBuf[1024];
			sprintf(szBuf, (*g_pGameStringTable)[STRING_MESSAGE_DAUM_EVENT_3].GetString(), 40);
			gC_vs_ui.RunPopupMessage(szBuf,C_VS_UI_POPUP_MESSAGE::POPUP_NORMAL);
		}
		break;
		
	case NOTICE_EVENT_RACE_WAR_IN_5:
		{
			MEvent event;
			event.eventID = EVENTID_WAR_EFFECT;
			event.eventType = EVENTTYPE_NULL;
			event.eventFlag = EVENTFLAG_SHAKE_SCREEN | EVENTFLAG_FADE_SCREEN;
			event.parameter2 = RGB( -30, -30, 0 );
			event.parameter3 = 1;
			event.eventDelay = -1;
			event.showTime = 2000;
			event.totalTime = 30000;
			g_pEventManager->AddEvent( event );
		}
		break;
	case NOTICE_EVENT_RACE_WAR_STARTED_IN_OTHER_SERVER:
		UI_PopupMessage( STRING_MESSAGE_RACE_WAR_STARTED_IN_OTHER_SERVER );
		break;
	case NOTICE_EVENT_CANNOT_FIND_STORE:             // �ش� �Ǹ��ڸ� ã�� �� �����ϴ�.
		UI_PopupMessage ( UI_STRING_MESSAGE_CANNOT_FIND_STORE );
		break;
    case NOTICE_EVENT_STORE_CLOSED:                  // ������ �̹� �������ϴ�.
		UI_PopupMessage ( UI_STRING_MESSAGE_STORE_CLOSED );
		break;
    case NOTICE_EVENT_ITEM_NOT_FOUND:                // �ش� �������� �̹� �ǸŵǾ��ų� �Ǹ��ڿ� ���� öȸ�Ǿ����ϴ�.
		UI_PopupMessage ( UI_STRING_MESSAGE_ITEM_NOT_FOUND );
		break;
    case NOTICE_EVENT_TOO_MUCH_MONEY:                // �Ǹ��ڰ� �ʹ� ���� ���� ������ �־ �� �� �����ϴ�.
		UI_PopupMessage ( UI_STRING_MESSAGE_TOO_MUCH_MONEY );
		break;
	case NOTICE_EVENT_NO_INVENTORY_SPACE:           // �κ��丮�� �� �ڸ��� �����ϴ�.
		UI_PopupMessage ( UI_STRING_MESSAGE_INVENTORY_FULL_MONSTER_KILL_QUEST );
		break;
    case NOTICE_EVENT_ALREADY_DISPLAYED:             // �̹� ������ �������Դϴ�.
		UI_PopupMessage ( UI_STRING_MESSAGE_ALREADY_DISPLAYED );
		break;
    case NOTICE_EVENT_CANNOT_SELL:                   // �� �� ���� �������Դϴ�.
		UI_PopupMessage ( STRING_MESSAGE_CANNOT_SELL );
		break;

	}
#endif
	
	__END_DEBUG
		__END_CATCH
}
