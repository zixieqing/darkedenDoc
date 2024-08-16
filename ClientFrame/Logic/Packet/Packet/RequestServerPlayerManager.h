//--------------------------------------------------------------------------------
// RequestServerPlayerManager.h
//--------------------------------------------------------------------------------
//
// Init( port )�ϸ� Request�� �޾Ƶ��� �غ� �ϰ� �ȴ�.
//                  ���ο��� Thread�� �����ؼ� 
//                  WaitRequest()�� ȣ���ؼ� accept�� ó���Ѵ�.
//
// �׳� WaitRequest()�� ȣ���ϸ� �ȵȴ�.. - -;
//
// Update()�� WaitRequest()���� �޾Ƶ��� RequestServerPlayer���� ó���Ѵ�.
//
//
//--------------------------------------------------------------------------------

#ifndef __REQUEST_SERVER_PLAYER_MANAGER_H__
#define __REQUEST_SERVER_PLAYER_MANAGER_H__

#pragma warning(disable:4786)

#include <windows.h>
#include <list>
#include "RequestServerPlayer.h"
#include "ServerSocket.h"


class RequestServerPlayerManager {
	public :
		typedef std::list<RequestServerPlayer*>	RequestServerPlayer_LIST;

	public :
		RequestServerPlayerManager();
		~RequestServerPlayerManager();

		//----------------------------------------------------------------------
		// Init / Wait
		//----------------------------------------------------------------------
		void		Init(int port=9650);
		void		Release();

		//----------------------------------------------------------------------
		// Wait Request
		//----------------------------------------------------------------------
		void		WaitRequest();

		//----------------------------------------------------------------------
		// Update
		//----------------------------------------------------------------------
		void		Update();

		//----------------------------------------------------------------------
		// Disconnect
		//----------------------------------------------------------------------
		void		Disconnect(const char* pName);

		//----------------------------------------------------------------------
		// broadcast
		//----------------------------------------------------------------------
		void		Broadcast(Packet* pPacket);

		
		int			GetSize() const			{ return m_listRequestServerPlayer.size(); }		

	protected :
		//----------------------------------------------------------------------
		// Lock / Unlock
		//----------------------------------------------------------------------
		void		Lock()					{ EnterCriticalSection(&m_Lock); }
		void		Unlock()				{ LeaveCriticalSection(&m_Lock); }

		//----------------------------------------------------------------------
		// RequestServerPlayer
		//----------------------------------------------------------------------
		bool		AddRequestServerPlayer(RequestServerPlayer* pRequestServerPlayer);

		//----------------------------------------------------------------------
		// Process Mode
		//----------------------------------------------------------------------
		void		ProcessMode(RequestServerPlayer* pPlayer);	

	
	protected :
		ServerSocket*			m_pServerSocket;

		HANDLE					m_hRequestThread;
		
		CRITICAL_SECTION		m_Lock;
		RequestServerPlayer_LIST		m_listRequestServerPlayer;
};

extern RequestServerPlayerManager*	g_pRequestServerPlayerManager;

#endif

