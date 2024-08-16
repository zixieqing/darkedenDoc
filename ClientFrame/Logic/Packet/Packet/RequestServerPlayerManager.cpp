//--------------------------------------------------------------------------------
// RequestServerPlayerManager.cpp
//--------------------------------------------------------------------------------
#include "Client_PCH.h"
#include "RequestServerPlayerManager.h"
//#include "RequestClientPlayerManager.h"
#include "ClientConfig.h"
#include "ClientDef.h"
#include "DebugInfo.h"
#include "ServerInfo.h"

//#include "Rpackets\RCPositionInfo.h"

#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
	extern CMessageArray*		g_pGameMessage;
#endif

#ifdef OUTPUT_DEBUG
	extern CRITICAL_SECTION			g_Lock;
#endif


//--------------------------------------------------------------------------------
// Global
//--------------------------------------------------------------------------------
RequestServerPlayerManager*	g_pRequestServerPlayerManager = NULL;

LONG					WaitRequestThreadProc(LPVOID lpParameter);

//--------------------------------------------------------------------------------
//
// constructor / destructor
//
//--------------------------------------------------------------------------------
RequestServerPlayerManager::RequestServerPlayerManager()
{
	m_pServerSocket		= NULL;
	m_hRequestThread	= NULL;
	
	InitializeCriticalSection(&m_Lock);
}

RequestServerPlayerManager::~RequestServerPlayerManager()
{
	Release();

	DeleteCriticalSection(&m_Lock);
}

//--------------------------------------------------------------------------------
// Release
//--------------------------------------------------------------------------------
void
RequestServerPlayerManager::Release()
{
	// thread ����
	TerminateThread(m_hRequestThread, 0);
	CloseHandle( m_hRequestThread );
	m_hRequestThread = NULL;
	
	try {
		if (m_pServerSocket!=NULL)
		{
			delete m_pServerSocket;
			m_pServerSocket = NULL;
		}
	} catch (Throwable&) {
	}
	
	Lock();

	RequestServerPlayer_LIST::iterator iPlayer = m_listRequestServerPlayer.begin();
		
	while (iPlayer != m_listRequestServerPlayer.end())
	{
		RequestServerPlayer* pPlayer = *iPlayer;

		try {
			delete pPlayer;
		} catch (Throwable&) {
		}
		
		iPlayer++;
	}

	m_listRequestServerPlayer.clear();

	Unlock();
}

//--------------------------------------------------------------------------------
// Add RequestServerPlayer
//--------------------------------------------------------------------------------
bool
RequestServerPlayerManager::AddRequestServerPlayer(RequestServerPlayer* pRequestServerPlayer)
{
	if (1)//g_Mode==MODE_GAME)
	{
		Lock();

		// �� ���� ���� �� �̻� ��û�� �� �޵��� �ؾ��Ѵ�.
		if (m_listRequestServerPlayer.size() < g_pClientConfig->MAX_REQUEST_SERVICE)
		{
			// �ϴ� list�� �־�д�.
			m_listRequestServerPlayer.push_back( pRequestServerPlayer );

			#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
			
				EnterCriticalSection(&g_Lock);
	
				if (g_pGameMessage!=NULL)
				{
					Socket* pSocket = pRequestServerPlayer->getSocket();

					if (pSocket!=NULL)
					{
						const char* addrIP = pSocket->getHost().c_str();
						g_pGameMessage->AddFormat("New Connection From %s", addrIP);
					}
					else
					{
						g_pGameMessage->AddFormat("New Connection From where?");
					}
				}

				LeaveCriticalSection(&g_Lock);
			#endif

			Unlock();
			return true;
		}
		else
		{
			pRequestServerPlayer->disconnect( UNDISCONNECTED );
			delete pRequestServerPlayer;
		}
		
		Unlock();		
	}
	/*
	else
	{
		pRequestServerPlayer->disconnect( UNDISCONNECTED );
		delete pRequestServerPlayer;
	}
	*/

	return false;	
}

//--------------------------------------------------------------------------------
// Disconnect
//--------------------------------------------------------------------------------
void		
RequestServerPlayerManager::Disconnect(const char* pName)
{
	Lock();


	RequestServerPlayer_LIST::iterator iPlayer = m_listRequestServerPlayer.begin();
		
	while (iPlayer != m_listRequestServerPlayer.end())
	{
		RequestServerPlayer* pPlayer = *iPlayer;

		// ���� �̸��� player�� ������ ������Ų��.
		if (pPlayer->getName()==pName)
		{
			pPlayer->disconnect(UNDISCONNECTED);
			delete pPlayer;

			m_listRequestServerPlayer.erase( iPlayer );

			Unlock();
			return;
		}
		
		iPlayer++;
	}


	Unlock();
}

//--------------------------------------------------------------------------------
// Broadcast
//--------------------------------------------------------------------------------
void		
RequestServerPlayerManager::Broadcast(Packet* pPacket)
{
	Lock();

	// ������ ������ ��� player�鿡�� packet�� �����Ѵ�.
	RequestServerPlayer_LIST::iterator iPlayer = m_listRequestServerPlayer.begin();
		
	while (iPlayer != m_listRequestServerPlayer.end())
	{
		RequestServerPlayer* pPlayer = *iPlayer;

		pPlayer->sendPacket( pPacket );
		
		iPlayer++;
	}

	Unlock();
}


//--------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------
void		
RequestServerPlayerManager::ProcessMode(RequestServerPlayer* pPlayer)
{
	/*
	switch (pPlayer->getRequestMode())
	{		
		//------------------------------------------------------
		// ���������� ��ǥ�� ������ ���
		//------------------------------------------------------		
		case REQUEST_CLIENT_MODE_POSITION_REPEATLY :
		{
			static DWORD nextTime = g_CurrentTime;
			static DWORD sendTime = g_CurrentTime;

			static int oldX = -1;
			static int oldY = -1;
			static int oldZoneID = -1;

			if (g_CurrentTime >= nextTime)
			{
				int x		= g_pPlayer->GetX();
				int y		= g_pPlayer->GetY();
				int zoneID	= (g_bZonePlayerInLarge?g_nZoneLarge : g_nZoneSmall);

				// ��ǥ�� �޶������� ������.
				if (oldX!=x || oldY!=y || oldZoneID!=zoneID
					|| g_CurrentTime >= sendTime)
				{
					RCPositionInfo _RCPositionInfo;

					_RCPositionInfo.setZoneX( x );
					_RCPositionInfo.setZoneY( y );
					_RCPositionInfo.setZoneID( zoneID );

					pPlayer->sendPacket( &_RCPositionInfo );

					// ���� ���� ���
					oldX = x;
					oldY = y;
					oldZoneID = zoneID;

					sendTime = g_CurrentTime + 30000;	// 30*1000;  // 30��
				}

				// 1�ʿ� �ѹ� ����
				nextTime = g_CurrentTime + 1000;				
			}
		}
		break;
	}
	*/
}


//--------------------------------------------------------------------------------
// Update
//--------------------------------------------------------------------------------
void		
RequestServerPlayerManager::Update()
{
	if (m_listRequestServerPlayer.empty())
	{
		return;
	}

	Lock();

	try {

		RequestServerPlayer_LIST::iterator iPlayer = m_listRequestServerPlayer.begin();
			
		while (iPlayer != m_listRequestServerPlayer.end())
		{
			RequestServerPlayer* pPlayer = *iPlayer;

			try {

				if (!pPlayer->getSocket()->isValid())
				{
					throw SocketException("sock error");
				}

				ProcessMode( pPlayer );
				
				pPlayer->processInput();
				pPlayer->processCommand();
				pPlayer->processOutput();

			} catch (NonBlockingIOException& t) {

				// ����..
				DEBUG_ADD_ERR( t.toString().c_str() );

			} catch (Throwable &t) 	{
				
				DEBUG_ADD_ERR( t.toString().c_str() );

				// ���� ��û�ϰ� �ִ°͵� ¥����.
				//if (g_pRequestClientPlayerManager!=NULL)
				{
				//	g_pRequestClientPlayerManager->Disconnect( pPlayer->getName().c_str() );
				}

				// exception�� ���� ������ �߶������. --;
				pPlayer->disconnect(UNDISCONNECTED);
				delete pPlayer;

				RequestServerPlayer_LIST::iterator iTemp = iPlayer;
				iPlayer++;

				m_listRequestServerPlayer.erase( iTemp );

				continue;
			}
			
			iPlayer++;
		}

	} catch (Throwable&t) {
		DEBUG_ADD_ERR( t.toString().c_str() );
	}

	Unlock();
}

//--------------------------------------------------------------------------------
// Init
//--------------------------------------------------------------------------------
void
RequestServerPlayerManager::Init(int port)
{
	if (m_pServerSocket!=NULL)
	{
		delete m_pServerSocket;
	}

	m_pServerSocket = new ServerSocket( port );

	DWORD dwChildThreadID;	// �ǹ� ���� -- ;

	m_hRequestThread = CreateThread(NULL, 
								0,	// default stack size
								(LPTHREAD_START_ROUTINE)WaitRequestThreadProc,
								this,
								NULL,
								&dwChildThreadID);

	// priority�� ����
	SetThreadPriority(m_hRequestThread, THREAD_PRIORITY_LOWEST);
}

//--------------------------------------------------------------------------------
// Wait Request
//--------------------------------------------------------------------------------
void
RequestServerPlayerManager::WaitRequest()
{
	Socket* pSocket = m_pServerSocket->accept();

	// request�� ���
	RequestServerPlayer* pRequestServerPlayer = new RequestServerPlayer( pSocket );

	pRequestServerPlayer->setPlayerStatus( CPS_REQUEST_SERVER_BEGIN_SESSION );

	pSocket->setNonBlocking();

	SetThreadPriority(m_hRequestThread, THREAD_PRIORITY_NORMAL);
	
	if (AddRequestServerPlayer( pRequestServerPlayer ))
	{
		// g_pDebugMessage�� lock�ɾ�� �Ѵ�. - -;
		//DEBUG_ADD_FORMAT("[Request] New Connection from %s:%d", pSocket->getHost().c_str(), pSocket->getPort());
	}

	SetThreadPriority(m_hRequestThread, THREAD_PRIORITY_LOWEST);
}

//--------------------------------------------------------------------------------
// WaitRequest
//--------------------------------------------------------------------------------
LONG					
WaitRequestThreadProc(LPVOID lpParameter)
{
	RequestServerPlayerManager* pRequestServerPlayerManager = (RequestServerPlayerManager*)lpParameter;

	while (1)
	{
		if (pRequestServerPlayerManager!=NULL)
		{
			pRequestServerPlayerManager->WaitRequest();
		}
	}

	return 0L;
}
