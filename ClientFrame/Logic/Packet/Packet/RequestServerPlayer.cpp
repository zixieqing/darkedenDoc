//--------------------------------------------------------------------------------
// 
// Filename    : RequestServerPlayer.cpp 
// Written By  : sigi
// 
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "RequestServerPlayer.h"
#include "Assert.h"
#include "Packet.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "ClientConfig.h"
#include "RequestFileManager.h"
#include "ClientDef.h"
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
RequestServerPlayer::RequestServerPlayer ( Socket * pSocket )
	 throw ( Error )
: Player(pSocket), m_PlayerStatus(CPS_NONE)
{
	m_RequestMode = REQUEST_CLIENT_MODE_NULL;

	m_ExpireTime = g_CurrentTime + EXPIRE_DELAY;
}


//--------------------------------------------------------------------------------
//
// destructor
//
//--------------------------------------------------------------------------------
RequestServerPlayer::~RequestServerPlayer ()
	 throw ( Error )
{
	__BEGIN_TRY
	
	#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
		if (g_pGameMessage!=NULL)
			g_pGameMessage->AddFormat("Close Connection to %s", m_Name.c_str() );
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
void RequestServerPlayer::processCommand () 
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
			if (g_pRequestFileManager->SendOtherRequest(m_Name, this))
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
					DEBUG_ADD_FORMAT("[PacketError-RequestServerPlayer::processCommand] exceed MAX=%d. packetID=%d", Packet::PACKET_MAX, packetID);		
					
					SendBugReport("RSP,Exceed PacketID:%d",packetID);
					
					throw InvalidProtocolException("[PacketError-RequestServerPlayer::processCommand] exceed MAX packetID");
				}

				#ifdef __DEBUG_OUTPUT__
					DEBUG_ADD_FORMAT("[RECEIVE] [ID=%d] InputStream(%s)", m_pInputStream->toString().c_str() );
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
				
				//if (g_Mode!=MODE_GAME)	
					//throw InvalidProtocolException("not MODE_GAME");

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
					DEBUG_ADD_FORMAT("[PacketSkip] So many Packets. at RequestServerPlayer");

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
void RequestServerPlayer::disconnect ( bool bDisconnected )
	throw ( Error )
{
	__BEGIN_TRY

	
	// file��û���̴��� ������ �����Ѵ�.
	if (g_pRequestFileManager!=NULL
		&& g_pRequestFileManager->HasOtherRequest(m_Name.c_str()))
	{
		g_pRequestFileManager->RemoveOtherRequest(m_Name.c_str());
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

uint
RequestServerPlayer::send(const char* pBuffer, uint nBytes) 
	throw( ProtocolException , Error )
{
	__BEGIN_TRY

	#ifdef __DEBUG_OUTPUT__
		DEBUG_ADD_FORMAT("[Send] %d bytes", nBytes);
	#endif

	return m_pOutputStream->write( pBuffer, nBytes );

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// get debug string
//
//--------------------------------------------------------------------------------
std::string RequestServerPlayer::toString () const
       throw ( Error )
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "RequestServerPlayer("
		<< "SocketID:" << m_pSocket->getSOCKET() 
		<< ",Host:" << m_pSocket->getHost() 
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
