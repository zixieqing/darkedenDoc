//--------------------------------------------------------------------------------
// 
// Filename    : RequestClientPlayer.cpp 
// Written By  : sigi
// 
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "RequestClientPlayer.h"
#include "Assert.h"
#include "Packet.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "ClientDef.h"
#include "RequestFileManager.h"
#include "ClientConfig.h"
#include "DebugInfo.h"

#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
	extern CMessageArray*		g_pGameMessage;
#endif

#define	EXPIRE_DELAY	60000		//60*1000	// 1��


	void	SendBugReport(const char *bug, ...);

//--------------------------------------------------------------------------------
//
// constructor
//
//--------------------------------------------------------------------------------
RequestClientPlayer::RequestClientPlayer ( Socket * pSocket )
	 throw ( Error )
: Player(pSocket), m_PlayerStatus(CPS_NONE)
{
	m_RequestMode = REQUEST_CLIENT_MODE_NULL;

	m_ExpireTime = g_CurrentTime + EXPIRE_DELAY;
}

//--------------------------------------------------------------------------------
// get InputStream Length
//--------------------------------------------------------------------------------
uint 
RequestClientPlayer::getInputStreamLength () const
	throw()
{
	return m_pInputStream->length();
}

//--------------------------------------------------------------------------------
// read InputStream
//--------------------------------------------------------------------------------
// file�����Ҷ� �̷��� �� �� �ۿ� ������.. ����..
//--------------------------------------------------------------------------------
uint 
RequestClientPlayer::readInputStream ( char * buf , uint len )
	throw ( ProtocolException , Error )
{
	uint nRead = m_pInputStream->read( buf, len );

	return nRead;
}

//--------------------------------------------------------------------------------
//
// destructor
//
//--------------------------------------------------------------------------------
RequestClientPlayer::~RequestClientPlayer ()
	 throw ( Error )
{
	__BEGIN_TRY
	
	#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
		if (g_pGameMessage!=NULL)
			g_pGameMessage->AddFormat("Disonnected From %s", m_RequestServerName.c_str());
	#endif

	// �� � �÷��̾� ��ü�� ������ ������, �� ���´� �α׾ƿ��̾�� �Ѵ�.
	// �� � �÷��̾ ���� ���� ��Ű����, �� ���¸� �α׾ƿ����� ������ �Ѵ�.
	Assert( m_PlayerStatus == CPS_END_SESSION );

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// parse packet and execute handler for the packet
//
//--------------------------------------------------------------------------------
void RequestClientPlayer::processCommand () 
     throw ( IOException , Error )
{
	__BEGIN_TRY

	//-----------------------------------------------------------------------
	// RequestMode�� ���� ó��
	//-----------------------------------------------------------------------
	switch (m_RequestMode)
	{
		//-----------------------------------------------------------------
		// Profile�� ������ ��..
		//-----------------------------------------------------------------
		case REQUEST_CLIENT_MODE_PROFILE :
			if (g_pRequestFileManager->ReceiveMyRequest(m_RequestServerName, this))
			{
				// ȭ���� ������ ���̹Ƿ� processCommand()�� �ʿ����.
				m_ExpireTime = g_CurrentTime + EXPIRE_DELAY;
				return;
			}			
		break;
	}	

	Packet * pPacket;

	try {
		try {

			// ����� �ӽ������� ���� ����
			char header[szPacketHeader];
			PacketID_t packetID;
			PacketSize_t packetSize;
			pPacket = NULL;

			//---------------------------------------------------------
			// �̹� Loop���� ó���� packet�� ����
			//---------------------------------------------------------
			// packet�� �ʹ� ���� ���.. 
			// �� ó���ϴٺ��� .. �ð��� ���� �ɷ��� client�� �� ���ư���
			// �׷��� ���� ������ ó���Ѵ�.
			//---------------------------------------------------------
			int maxProcessPacket = g_pClientConfig->MAX_PROCESS_PACKET;
			int processedPacket = 0;

			// �Է¹��ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
			while ( true ) {
			
				// �Է½�Ʈ������ ��Ŷ���ũ�⸸ŭ �о��.
				// ���� ������ ũ�⸸ŭ ��Ʈ������ ���� �� ���ٸ�,
				// Insufficient ���ܰ� �߻��ϰ�, ������ ����������.
				m_pInputStream->peek( header , szPacketHeader );

				// ��Ŷ���̵� �� ��Ŷũ�⸦ �˾Ƴ���.
				// �̶� ��Ŷũ��� ����� �����Ѵ�.
				memcpy( &packetID   , &header[0] , szPacketID );	
				memcpy( &packetSize , &header[szPacketID] , szPacketSize );

				//#ifdef	__DEBUG_OUTPUT__
					//	DEBUG_ADD_FORMAT("ID=%d (%s), size=%d", packetID, g_pPacketFactoryManager->getPacketName( packetID ), packetSize);
				//#else
					//	DEBUG_ADD_FORMAT("ID=%d, size=%d", packetID, packetSize);
				//#endif
				
				// ��Ŷ ���̵� �̻��ϸ� �������� ������ �����Ѵ�.
				if ( packetID >= Packet::PACKET_MAX )
				{
					DEBUG_ADD_FORMAT("[PacketError-RequestClientPlayer::processCommand] exceed MAX=%d. packetID=%d", Packet::PACKET_MAX, packetID);		
					SendBugReport("RCP,Exceed PacketID:%d",packetID);
					
					throw InvalidProtocolException("[PacketError-RequestClientPlayer::processCommand] exceed MAX packetID");
				}

				#ifdef __DEBUG_OUTPUT__
					DEBUG_ADD_FORMAT("[RECEIVE] [ID=%d] %s", packetID, g_pPacketFactoryManager->getPacketName(packetID).c_str());
				#endif
				
				BOOL bExecute = TRUE;

				if ( ! g_pPacketValidator->isValidPacketID( getPlayerStatus() , packetID ) )
				{
					DEBUG_ADD("[PacketError] invalid packet ORDER");

					//---------------------------------------------------------------
					// Logout�ؼ� ĳ���� ����ȭ������ ���� ���
					//---------------------------------------------------------------
					if (getPlayerStatus()==CPS_WAITING_FOR_GC_RECONNECT_LOGIN)
					{
						// �о�� execute�� ���� �ʴ´�.
						bExecute = FALSE;
						
						// ������.. ����~~ -_-;
						maxProcessPacket = 0xFFFF;
					}
					//---------------------------------------------------------------
					// �Ϲ����� ���� ������ ���´�.
					//---------------------------------------------------------------
					else
					{
						throw InvalidProtocolException("invalid packet ORDER");
					}				
				}

				// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
				if ( packetSize > g_pPacketFactoryManager->getPacketMaxSize( packetID ) )
				{
					DEBUG_ADD_FORMAT("[PacketError] too large packet SIZE: %d/%d", (int)packetSize, (int)g_pPacketFactoryManager->getPacketMaxSize( packetID ));		
					throw InvalidProtocolException("too large packet SIZE");
				}
				
				// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
				// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
				if ( m_pInputStream->length() < szPacketHeader + packetSize )
				{
					DEBUG_ADD_FORMAT("[PacketError] InsufficientDataException: %d/%d", m_pInputStream->length(), szPacketHeader + packetSize);
		
					throw InsufficientDataException();
				}

				if (g_Mode!=MODE_GAME)	
					throw InvalidProtocolException("not MODE_GAME");

				
				// ������� �Դٸ� �Է¹��ۿ��� ������ ��Ŷ �ϳ� �̻��� ����ִٴ� ���̴�.
				// ��Ŷ���丮�Ŵ����κ��� ��Ŷ���̵� ����ؼ� ��Ŷ ��Ʈ��ó�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ���丮�Ŵ������� ó���Ѵ�.
				pPacket = g_pPacketFactoryManager->createPacket( packetID );

				// ���� �� ��Ŷ��Ʈ��ó�� �ʱ�ȭ�Ѵ�.
				// ��Ŷ����Ŭ������ ���ǵ� read()�� virtual ��Ŀ���� ���ؼ� ȣ��Ǿ�
				// �ڵ������� �ʱ�ȭ�ȴ�.
				m_pInputStream->read( pPacket );
				
				// ���� �� ��Ŷ��Ʈ��ó�� ������ ��Ŷ�ڵ鷯�� �����ϸ� �ȴ�.
				// ��Ŷ���̵� �߸��� ���� ��Ŷ�ڵ鷯�Ŵ������� ó���Ѵ�.			

				if (bExecute)
				{
					#ifdef __DEBUG_OUTPUT__
						DEBUG_ADD(pPacket->toString().c_str());
					#endif

					pPacket->execute( this );

					//DEBUG_ADD_FORMAT("[Executed] %s", pPacket->toString().c_str());
					DEBUG_ADD("[PacketExecute OK]");				
				}				
				
				delete pPacket;
				pPacket = NULL;


				m_ExpireTime = g_CurrentTime + EXPIRE_DELAY;

				//---------------------------------------------------------	
				// �ѹ��� ó���ϴ� packet�� �Ѱ� ������ �Ѿ ���
				// �������� ���� turn�� ó���Ѵ�.
				//---------------------------------------------------------
				if (++processedPacket > maxProcessPacket)
				{
					DEBUG_ADD_FORMAT("[PacketSkip] So many Packets. at RequestClientPlayer");

					break;
				}
				
				//---------------------------------------------------------
				// ȭ�� �޴� packet ��������
				// data���� �¸���~ �Ѿ�´�.
				//---------------------------------------------------------
				if (packetID==Packet::PACKET_RC_REQUESTED_FILE)
				{
					break;
				}
			}

		} catch ( InsufficientDataException ) {

			// ���� ������ Ż�� ������ ���̴�. ������ ������ �ʿ�� ����.
			if (g_CurrentTime > m_ExpireTime)
			{
				throw InvalidProtocolException("timeout - -;;");			
			}
		}
	} catch (Throwable)	{
		if (pPacket!=NULL)
		{
			delete pPacket;
			pPacket = NULL;
		}

		throw;
	}

	__END_CATCH
}
		    

//--------------------------------------------------------------------------------
// disconnect player
//--------------------------------------------------------------------------------
void RequestClientPlayer::disconnect ( bool bDisconnected )
	throw ( Error )
{
	__BEGIN_TRY

	// file��û���̴��� ������ �����Ѵ�.
	if (g_pRequestFileManager!=NULL
		&& g_pRequestFileManager->HasMyRequest(m_RequestServerName.c_str()))
	{
		g_pRequestFileManager->RemoveMyRequest(m_RequestServerName.c_str());
	}

	if ( bDisconnected == UNDISCONNECTED ) {

		// Ŭ���̾�Ʈ���� GCDisconnect ��Ŷ�� �����Ѵ�.
		//GCDisconnect gcDisconnect;
		//sendPacket( gcDisconnect );

		// ��� ���ۿ� �����ִ� ����Ÿ�� �����Ѵ�.
		m_pOutputStream->flush();		
	}

	// ���� ������ �ݴ´�.
	m_pSocket->close();

	// �÷��̾��� ���¸� �α׾ƿ����� �����.
	//cout<< "PlayerStatus : " << (int)m_PlayerStatus << endl;
	// 2001.10.5 �ּ�ó�� ..����..
	//Assert( m_PlayerStatus != CPS_END_SESSION );
	m_PlayerStatus = CPS_END_SESSION;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// get debug string
//
//--------------------------------------------------------------------------------
std::string RequestClientPlayer::toString () const
       throw ( Error )
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "RequestClientPlayer("
		<< "SocketID:" << m_pSocket->getSOCKET() 
		<< ",Host:" << m_pSocket->getHost() 
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
