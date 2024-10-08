//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLReconnectLogin.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_RECONNECT_LOGIN_H__
#define __CL_RECONNECT_LOGIN_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLogin;
//
// 클라이언트가 서버에게 보내는 연결 패킷이다.
// 서버간 이동에 사용되며, 이전 서버가 준 Key 를 새 서버에게 전송해서
// 인증을 받는다. 또한, 새 서버에서 사용할 크리처 아이디를 담고 있다.
//
//////////////////////////////////////////////////////////////////////

class CLReconnectLogin : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_CL_RECONNECT_LOGIN; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szDWORD+szBYTE; 						// authentication key
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "CLReconnectLogin"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

public :

	// get/set key
	DWORD getKey () const throw () { return m_Key; }
	void setKey ( DWORD key ) throw () { m_Key = key; }

	void SetLoginMode(BYTE n) { m_LoginMode = n;}
	BYTE GetLoginMode() { return m_LoginMode;}
private :
	
	// authentication key
	DWORD m_Key;
	// Login mode
	BYTE m_LoginMode;

};


//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLoginFactory;
//
// Factory for CLReconnectLogin
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CLReconnectLoginFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new CLReconnectLogin(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "CLReconnectLogin"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_CL_RECONNECT_LOGIN; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw ()
	{ 
		return szDWORD+szBYTE; 			// authentication key
	}

};

#endif

//////////////////////////////////////////////////////////////////////
//
// class CLReconnectLoginHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CLReconnectLoginHandler {

	public :

		// execute packet's handler
		static void execute ( CLReconnectLogin * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

	};
#endif

#endif
