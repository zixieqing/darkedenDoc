//////////////////////////////////////////////////////////////////////
// 
// Filename    : DatagramPacket.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __DATAGRAM_PACKET_H__
#define __DATAGRAM_PACKET_H__

// include files
#include "Packet.h"
#include "Datagram.h"
#include "SocketAPI.h"


//////////////////////////////////////////////////////////////////////
//
// class DatagramPacket;
//
// 서버간의 UDP 통신에 사용되는 패킷의 베이스 클래스이다.
// 기본적으로 이 패킷들은 보낸 쪽의 주소(address)와 포트(port)를 저장
// 하고 있어야 하며, Datagram에 읽고 쓰는 메쏘드를 override 해야 하기
// 때문에 도입되었다.
//
//////////////////////////////////////////////////////////////////////

class DatagramPacket : public Packet {
	
public :
	
	// destructor
	virtual ~DatagramPacket () throw () {}

	// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
	// 데이터그램 패킷이 TCP 소켓으로 전송되어 왔다면 프로토콜 에러로 간주한다.
	virtual void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error ) 
	{ 
		throw ProtocolException("datagram packet from TCP socket"); 
	}

	// Datagram 객체에서 데이터를 읽어서 패킷을 초기화한다.
	virtual void read ( Datagram & iDatagram ) throw ( ProtocolException , Error ) = 0;
	
	// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
	// 데이터그램 패킷을 TCP 소켓으로 출력할 수 없다.
	virtual void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error )
	{ 
		throw Error("cannot write datagram-packet to TCP-socket-stream"); 
	}

	// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
	virtual void write ( Datagram & oDatagram ) const throw ( ProtocolException , Error ) = 0;
	
	// execute packet's handler
	virtual void execute ( Player * pPlayer ) throw ( ProtocolException , Error ) = 0;
	
	// get packet's DatagramPacketID	
	virtual PacketID_t getPacketID () const throw () = 0;

	// get packet's body size
	virtual PacketSize_t getPacketSize () const throw () = 0;

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		virtual std::string getPacketName () const throw () = 0;
			
		// get packet's debug std::string
		virtual std::string toString () const throw () = 0;
	#endif

	// get/set host
	const std::string& getHost () const throw () { return m_Host; }
	void setHost ( std::string host ) throw () { m_Host = host; }

	// get/set port
	uint getPort () const throw () { return m_Port; }
	void setPort ( uint port ) throw () { m_Port = port; }
	

protected :

	// sender's host
	std::string m_Host;

	// sender's port
	uint m_Port;
	
};

#endif
