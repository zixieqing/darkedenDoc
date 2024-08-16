//--------------------------------------------------------------------------------
//
// Filename    : GCReconnectLoginHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "GCReconnectLogin.h"
#include "ClientDef.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLReconnectLogin.h"
	#include "UserInformation.h"
	//add by viva
	#include "Cpackets/CGConnectSetKey.h"
	//end
#endif
//add by viva
bool UpdateSocketOutput();
//end
//--------------------------------------------------------------------------------
// �α��μ����κ��� ���� ������ �ּҿ� ��Ʈ, �׸��� ����Ű�� ���� ���
// ���� ������ ������ ��, ����Ű�� ���� CGConnect ��Ŷ�� �����Ѵ�.
//--------------------------------------------------------------------------------
void GCReconnectLoginHandler::execute ( GCReconnectLogin * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

#ifdef __GAME_CLIENT__

 
	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	// �α��� �������� ������ �����Ѵ�
	// �̶� �α��� ������ LCReconnect ��Ŷ�� �����鼭 ������ �����Ѵٴ� ��ǿ� �����϶�.
	
	pClientPlayer->disconnect();

	// GCReconnectLogin ��Ŷ�� ����ִ� ������ ����ؼ�, login ������ �����Ѵ�.
	DEBUG_ADD_FORMAT("Reconnecting to %s:%d", 
									pPacket->getLoginServerIP().c_str(), 
									pPacket->getLoginServerPort());
	
	try {

		pClientPlayer->getSocket()->reconnect( pPacket->getLoginServerIP() , pPacket->getLoginServerPort() );

		// reconnect�ϰ� �Ǹ� ������ ���� ��������� �ȴ�.
		// ����, �� ���� ���� �ɼ��� ���� ��������� �Ѵ�.
		pClientPlayer->getSocket()->setNonBlocking();
		pClientPlayer->getSocket()->setLinger(0);

	} catch ( ConnectException & ce ) {
		throw Error(ce.toString());
	}

	// ������ �̷������, �ٷ� CLReconnectLogin ��Ŷ�� �����Ѵ�.
	// ������ Select �� PC�� Ÿ�԰� �̸��� Ŭ���̾�Ʈ �÷��̾� ��ü�� �����صд�.
	DEBUG_ADD_FORMAT("Sending CLReconnectLogin with Key(%ld)", 	pPacket->getKey());
		
	//add by viva	
	CGConnectSetKey cgConnectSetKey;
	cgConnectSetKey.setEncryptKey(rand());
	cgConnectSetKey.setHashKey(rand());
	pClientPlayer->delKey();
	pClientPlayer->sendPacket(&cgConnectSetKey);
	UpdateSocketOutput();
	Sleep(500);
	cgConnectSetKey.execute(pClientPlayer);
	//end

	// ������..
	CLReconnectLogin _CLReconnectLogin;
	_CLReconnectLogin.setKey( pPacket->getKey() );
	_CLReconnectLogin.SetLoginMode(g_pUserInformation->IsAutoLogIn);
	
	pClientPlayer->sendPacket( &_CLReconnectLogin );
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_GET_PC_LIST );	

	// pc std::list�� ��ٸ���.
	SetMode( MODE_WAIT_PCLIST  );

#endif
	__END_CATCH
}
