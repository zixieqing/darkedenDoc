//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCVisibleFail.h 
// Written By  : crazydog
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_VISIBLE_FAIL_H__
#define __GC_VISIBLE_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCVisibleFail;
//
//////////////////////////////////////////////////////////////////////

class GCVisibleFail : public Packet {

public :

	// constructor
	GCVisibleFail () throw () {}
	

public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_VISIBLE_FAIL; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return 0; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "GCVisibleFail"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif
	

public :


private : 


};


//////////////////////////////////////////////////////////////////////
//
// class  GCVisibleFailFactory;
//
// Factory for  GCVisibleFail
//
//////////////////////////////////////////////////////////////////////

class  GCVisibleFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCVisibleFail(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCVisibleFail"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_VISIBLE_FAIL; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw () { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class  GCVisibleFailHandler;
//
//////////////////////////////////////////////////////////////////////

class  GCVisibleFailHandler {

public :

	// execute packet's handler
	static void execute ( GCVisibleFail * pPacket , Player * pPlayer ) throw ( Error);

};

#endif
