//----------------------------------------------------------------------
// WhisperManager.h
//----------------------------------------------------------------------
// �ٸ� ����ڿ��� �ӼӸ��� ��~ �����ϱ� ����...
// 
// �������� IP�� ��� P2P ����.
/*

	//---------------------------------------------------------
	// [0] �ӼӸ��� Keyboard�Է¿� ���ؼ� ���۵ȴ�.
	//---------------------------------------------------------
	UI_INPUT --(whisper)--> [1] WhisperManager::Send(name, message)

	//---------------------------------------------------------
	// [1] �ӼӸ� ���� ��
	//---------------------------------------------------------
	WhisperManager::SendMessage(toUser, message)
	{
		if (has toUser's IP in RUM)		// RUM = RequestUserManager
		{			
			RequestClientManager --(CRWhisper)--> RequestServer(toUser) [2]			
		}
		else
		{
			CGWhisper --> GameServer [3]
		}
	}

	//---------------------------------------------------------
	// [2] RequestClientManager --> RequestServer
	//---------------------------------------------------------
	RequestClientManager::ConnectForOnePacket(toUser, IP, packet)
	{
		if (connect(toUser, IP))
		{
			sendPacket(packet) --> toUser [5]			
		}
		else
		{
			// ���� �����ϸ� -_-;
			RequestUserManager::RemoveRequestUser( toUser )
		}
	}

	//---------------------------------------------------------
	// [3] GameServer received CGWhisper
	//---------------------------------------------------------
	CGWhisperHandler(fromUser, toUser)
	{
		if (exist toUser in current GameServer 
			|| exist toUser in CurrentConnectedUser)
		{
			GCRequestedIP(toUser's ip) --> client(fromUser) [4]
		}
		else
		{
			GCWhisperFailed --> client(fromUser)
		}
	}

	//---------------------------------------------------------
	// [4] GCRequestedIP
	//---------------------------------------------------------
	GCRequestedIPHandler(toUser, IP)
	{
		RequestUserManager::addRequestUser( toUser, IP )

		if (WhisperManager::HasMessage(toUser))
		{
			RequestClientManager --(CRWhisper)--> RequestServer(toUser) [2]			
		}
	}
	
	//---------------------------------------------------------
	// [5] RequestServer(toUser)
	//---------------------------------------------------------
	RequestServer::Receive(fromUser, toUser, packet)
	{
		if (toUser != me)
		{
			send RCWhisperFailed --> fromUser [6]
		}

		// �ѹ� packet�� ������ ���������.
		disconnect()
	}

	//---------------------------------------------------------
	// [6] RequestClient(fromUser)
	//---------------------------------------------------------
	RequestClient::RCWhisperFailed(toUser)
	{
		// toUser�� �ٸ� ����̴�.
		RequestUserManager::RemoveRequestUser( toUser )
	}


//--------------------------------------------------------------------*/

#ifndef __WHISPER_MANAGER_H__
#define __WHISPER_MANAGER_H__

#pragma warning(disable:4786)

#include <windows.h>
#include <map>
#include <string>
#include <list>

struct WHISPER_MESSAGE
{
	std::string msg;
	DWORD color;
};

//----------------------------------------------------------------------
// WhisperInfo
//----------------------------------------------------------------------
// �ӼӸ��� ���� ����(�޴»��, ��������)
//----------------------------------------------------------------------
class WhisperInfo {
	public :
		std::string					Name;
		std::list<WHISPER_MESSAGE>	Messages;

		int							TryingCount;	// ���� �õ� ȸ��

	public :
		WhisperInfo()
		{
			TryingCount = 0;
		}

		void		SendToGameServer() const;
};

//----------------------------------------------------------------------
// WhisperManager
//----------------------------------------------------------------------
// �ӼӸ� ����...
//----------------------------------------------------------------------
class WhisperManager {
	public :
		typedef std::map<std::string, WhisperInfo*>		WHISPER_INFO_MAP;

	public :
		WhisperManager();
		~WhisperManager();

		//--------------------------------------------------------------
		// Release
		//--------------------------------------------------------------
		void		Release();

		//--------------------------------------------------------------
		// Message
		//--------------------------------------------------------------
		bool		HasWhisperMessage(const char* pName) const;
		const std::list<WHISPER_MESSAGE>*	GetWhisperMessages(const char* pName) const;

		void		SendWhisperMessage(const char* pName, const char* pMessage, DWORD color);

		void		AddWhisperMessage(const char* pName, const char* pMessage, DWORD color);		
		bool		RemoveWhisperMessage(const char* pName);
		void		TryToSendWhisperMessage(const char* pName);

		//--------------------------------------------------------------
		// Update
		//--------------------------------------------------------------
		void		Update();

	protected :
		//----------------------------------------------------------------------
		// Lock / Unlock
		//----------------------------------------------------------------------
		void		Lock()					{ EnterCriticalSection(&m_Lock); }
		void		Unlock()				{ LeaveCriticalSection(&m_Lock); }

	private :
		CRITICAL_SECTION		m_Lock;

		WHISPER_INFO_MAP		m_WhisperInfos;
};


extern WhisperManager*		g_pWhisperManager;


#endif

