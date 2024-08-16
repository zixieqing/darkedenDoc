//--------------------------------------------------------------------------------
//
// Filename    : GCNicknameVerifyHandler.cpp
// Written By  : elca, Reiot
// Description :
//
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "GCNicknameVerify.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
#include "ClientDef.h"
#include "MGameStringTable.h"
#include "UIFunction.h"
#include "TempInformation.h"
#include "VS_UI.h"

#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void GCNicknameVerifyHandler::execute ( GCNicknameVerify * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY 
//	__BEGIN_DEBUG_EX
//	__BEGIN_DEBUG
		
#ifdef __GAME_CLIENT__
	switch(pPacket->getCode())
	{
		case NICKNAME_MODIFY_FAIL_NO_ITEM:
			UI_PopupMessage( STRING_MESSAGE_CANNOT_BUY_NO_ITEM );
			break;
		case NICKNAME_MODIFY_OK:
			if (g_pTempInformation->GetMode()==TempInformation::MODE_NICKNAME_CHANGE_CUSTOM)
			{
				// value1 = �̸�, value2 = item type
				if(g_pTempInformation->Value2 != 0)
				{ 
					//UseItemOK();
					switch(g_pTempInformation->Value2)
					{
					case 22: // �г��� ����
						gC_vs_ui.Change_Custom_Naming(0, (char*)g_pTempInformation->Value1);
						break;
					case 23: // �� �г��� ���� - gc_modify nickname ���� ���� �ǰ���..
						break;
					case 24: // ���� �г��� �߰� - �������� ����Ʈ�������� ����
						break;
					case 25: // �г��� ���� (�ð���)
						gC_vs_ui.Change_Custom_Naming(0, (char*)g_pTempInformation->Value1);
						break;
					}
					
				//	gC_vs_ui.SetChangeableNickName(false);
				}
				else // ����� ���� ��ġ��- gc_modify nickname ���� ���� �ǰ���..
				{
				//	gC_vs_ui.SetChangeablePetNickName(false);
				}
				gC_vs_ui.CloseNamingChange();
				UI_PopupMessage( UI_STRING_MESSAGE_NICKNAME_CHANGE_OK );
			}
			break;
		case NICKNAME_SELECT_FAIL_NO_SUCH:
			UI_PopupMessage( UI_STRING_MESSAGE_SMS_FAIL_NO_SUCH_EID );
			break;
		case NICKNAME_SELECT_OK:
//			g_pTempInformation->SetMode(TempInformation::MODE_NICKNAME_CHANGE_CUSTOM);
//			g_pTempInformation->Value1 = left;
			UI_PopupMessage( UI_STRING_MESSAGE_NICKNAME_CHANGE_OK );
			break;
		case NICKNAME_SELECT_FAIL_FORCED:
			UI_PopupMessage( UI_STRING_MESSAGE_NICKNAME_SELECT_FAIL_FORCED);
			break;
	}

	g_pTempInformation->SetMode(TempInformation::MODE_NULL);
#endif

//	__END_DEBUG
//	__END_DEBUG_EX 
	__END_CATCH
}
