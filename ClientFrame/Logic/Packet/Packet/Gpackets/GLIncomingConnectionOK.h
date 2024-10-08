//////////////////////////////////////////////////////////////////////
// 
// Filename    : GLIncomingConnectionOK.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GL_INCOMING_CONNECTION_OK_H__
#define __GL_INCOMING_CONNECTION_OK_H__

// include files
#include "DatagramPacket.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOK;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOK : public DatagramPacket {

public :
	
    // Datagram 객체에서부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( Datagram & iDatagram ) throw ( ProtocolException , Error );
		    
    // Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
    void write ( Datagram & oDatagram ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GL_INCOMING_CONNECTION_OK; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szBYTE + m_PlayerID.size() 
				+ szuint
				+ szDWORD; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GLIncomingConnectionOK"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

public :

	// get/set player id
	std::string getPlayerID () const throw () { return m_PlayerID; }
	void setPlayerID ( std::string playerID ) throw () { m_PlayerID = playerID; }

	// get/set tcp port
	uint getTCPPort () const throw () { return m_TCPPort; }
	void setTCPPort ( uint tcpPort ) throw () { m_TCPPort = tcpPort; }

	// get/set auth key
	DWORD getKey () const throw () { return m_Key; }
	void setKey ( DWORD key ) throw () { m_Key = key; }

private :

	// 어떤 플레이어에게 LCReconnect 패킷을 보내야 하는지는 알아야 한다.
	std::string m_PlayerID;

	// 게임 서버가 자신의 TCP 포트를 알려줌으로써 
	// 로그인 서버는 게임 서버의 TCP 포트를 몰라도 무방하다.
	uint m_TCPPort;

	// 게임 서버에서 생성한 인증 키
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOKFactory;
//
// Factory for GLIncomingConnectionOK
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GLIncomingConnectionOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GLIncomingConnectionOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GL_INCOMING_CONNECTION_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GLIncomingConnectionOKPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize () const throw () 
	{ 
		return szBYTE + 20
				+ szuint
				+ szDWORD; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GLIncomingConnectionOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GLIncomingConnectionOKHandler {
	
public :

	// execute packet's handler
	static void execute ( GLIncomingConnectionOK * pPacket ) throw ( ProtocolException , Error );

};

#endif
