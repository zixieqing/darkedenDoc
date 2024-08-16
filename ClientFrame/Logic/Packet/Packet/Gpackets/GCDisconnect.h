//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCDisconnect.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_DISCONNECT_H__
#define __GC_DISCONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCDisconnect;
//
//////////////////////////////////////////////////////////////////////

class GCDisconnect : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_DISCONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return szBYTE + m_Message.size(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCDisconnect"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

	// get/set chatting message
	std::string getMessage () const throw () { return m_Message; }
	void setMessage ( const std::string & msg ) throw () { m_Message = msg; }

private :
	
	// chatting message
	std::string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCDisconnectFactory;
//
// Factory for GCDisconnect
//
//////////////////////////////////////////////////////////////////////

class GCDisconnectFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCDisconnect(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCDisconnect"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_DISCONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCDisconnectPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const throw () { return szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCDisconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDisconnectHandler {
	
public :
	
	// execute packet's handler
	static void execute ( GCDisconnect * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
