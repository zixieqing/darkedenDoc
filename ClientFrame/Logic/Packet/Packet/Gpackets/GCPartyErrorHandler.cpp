//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPartyErrorHandler.cpp
// Written By  : �輺��
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "GCPartyError.h"
#include "ClientDef.h"
#include "UIDialog.h"
#include "MGameStringTable.h"
#include "TempInformation.h"
#include "UIFunction.h"

void GCPartyErrorHandler::execute (GCPartyError * pPacket , Player * pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__

	if (g_pUIDialog==NULL
		|| g_pPlayer==NULL
		|| g_pTempInformation==NULL)
	{
		DEBUG_ADD("GCPartyErrorHandler Failed");
		return;
	}

	int code = pPacket->getCode();

	//----------------------------------------------------------------------
	//
	//	��Ƽ ��ҵǴ� ����� �������� ó��
	//
	//----------------------------------------------------------------------
	if (code==GC_PARTY_ERROR_TARGET_NOT_EXIST
		|| code==GC_PARTY_ERROR_RACE_DIFFER
		|| code==GC_PARTY_ERROR_NOT_SAFE)
	{	
		if (g_pTempInformation->GetMode() == TempInformation::MODE_PARTY_REQUEST)
		{
			// ��Ƽ����ҷ�?�� �ݴ´�.
			UI_ClosePartyCancel();

			// ���� ����..
			if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_PARTY)
			{
				g_pPlayer->SetWaitVerifyNULL();
			}

			g_pTempInformation->SetMode(TempInformation::MODE_NULL);
		}
	}

	switch (code)
	{
		//----------------------------------------------------------------------
		// ��Ƽ�� �䱸�� ����� �������� �ʴ´�
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_TARGET_NOT_EXIST :						
			// �׷� ��� ����~
			UI_ClosePartyCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_PARTY_NOBODY].GetString());
		break;
		
		
		//----------------------------------------------------------------------
		// ��Ƽ�� �䱸�� ����� �ٸ� �����̴�
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_RACE_DIFFER :
			// ��Ƽ�� �� ����~
			UI_ClosePartyCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_RACE_DIFFER].GetString());
		break;

		//----------------------------------------------------------------------
		// ��Ƽ�� �Ϸ��� �ϴ� ���� ���� ���밡 �ƴϴ�.
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_NOT_SAFE :
			// ��Ƽ�� �� ����~
			UI_ClosePartyCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_PARTY_SAFETY_ZONE_ONLY].GetString());			
		break;		

		//----------------------------------------------------------------------
		// ���� ��
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_NOT_NORMAL_FORM :
			// ��Ƽ�� �� ����~
			UI_ClosePartyCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NOT_NORMAL_FORM].GetString());			
		break;
		

		//----------------------------------------------------------------------
		// ��Ƽ ���̸鼭 �ٽ� ��Ƽ�� �Ϸ��� �Ѵ�
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_ALREADY_INVITING :
			
			UI_ClosePartyCancel();

			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_PARTY_BUSY].GetString());
		break;

		//----------------------------------------------------------------------
		// ��Ƽ ���� �ƴѵ� : ��Ƽ ���� ��Ŷ�� ���ƿԴ�.
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_NOT_INVITING :
			// - -;
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] Server is Not Party Mode");
				}
			#endif
		break;	

		//----------------------------------------------------------------------
		// ��Ƽ���� �߹��� �� �ִ� ������ ����.
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_NO_AUTHORITY :
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_NO_AUTHORITY].GetString());

			#ifdef OUTPUT_DEBUG			
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] GC_PARTY_ERROR_NO_AUTHORITY");
				}
			#endif
		break;

		//----------------------------------------------------------------------
		// �� �� ���� �����̴�...
		//----------------------------------------------------------------------
		case GC_PARTY_ERROR_UNKNOWN :
			
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_ERROR_PARTY].GetString());

			#ifdef OUTPUT_DEBUG			
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] GC_PARTY_ERROR_UNKNOWN");
				}
			#endif
		break;
	}

#endif

	 __END_CATCH
}
