//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTakeOutFail.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_TAKE_OUT_FAIL_H__
#define __GC_TAKE_OUT_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFail;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFail : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_TAKE_OUT_FAIL; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutFailPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "GCTakeOutFail"; }
	
	// get packet's debug std::string
	std::string toString() const throw();
#endif
	
public :

	// get / set ObjectID
	ObjectID_t getObjectID() throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFailFactory;
//
// Factory for GCTakeOutFail
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFailFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCTakeOutFail(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "GCTakeOutFail"; }
#endif
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TAKE_OUT_FAIL; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutFailPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutFailHandler {
	
public :

	// execute packet's handler
	static void execute(GCTakeOutFail* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
