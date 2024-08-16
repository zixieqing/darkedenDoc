//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTakeOutOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_TAKE_OUT_OK_H__
#define __GC_TAKE_OUT_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutOK;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutOK : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_TAKE_OUT_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize() const throw() { return szObjectID; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "GCTakeOutOK"; }
	
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
// class GCTakeOutOKFactory;
//
// Factory for GCTakeOutOK
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCTakeOutOK(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "GCTakeOutOK"; }
#endif
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_TAKE_OUT_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCTakeOutOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCTakeOutOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCTakeOutOKHandler {
	
public :

	// execute packet's handler
	static void execute(GCTakeOutOK* pPacket, Player* player) throw(ProtocolException, Error);
};

#endif
