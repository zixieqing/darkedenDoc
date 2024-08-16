//--------------------------------------------------------------------------------
// ClientCommunicationManager.h
//--------------------------------------------------------------------------------
// �ٸ� Ŭ���̾�Ʈ�κ����� ������ �޾Ƶ�� 
//--------------------------------------------------------------------------------

#ifndef __CLIENT_COMMUNICATION_MANAGER_H__
#define __CLIENT_COMMUNICATION_MANAGER_H__

#include <Windows.h>
#include "Types.h"
#include "Exception.h"
#include "DatagramSocket.h"

class Datagram;
class DatagramPacket;

class ClientCommunicationManager {
	public :
		ClientCommunicationManager();
		~ClientCommunicationManager();

		//------------------------------------------------------------------
		// Update
		//------------------------------------------------------------------
		void	Update();

		//------------------------------------------------------------------
		// send
		//------------------------------------------------------------------
		void	sendDatagram ( Datagram * pDatagram ) throw ( ConnectException , Error );
		void	sendPacket ( const std::string& host , uint port , DatagramPacket * pPacket ) throw ( ConnectException , Error );

	private :
		// UDP ���� ����
		DatagramSocket *	m_pDatagramSocket;
};


extern ClientCommunicationManager*	g_pClientCommunicationManager;

#endif
