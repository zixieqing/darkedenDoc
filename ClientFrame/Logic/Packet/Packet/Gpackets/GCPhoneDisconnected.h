//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneDisconnected.h 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_DISCONNECTED_H__
#define __GC_PHONE_DISCONNECTED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnected;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다. (CreatureID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnected : public Packet {

public :
	
	// constructor
	GCPhoneDisconnected () throw ();
	
	// destructor
	~GCPhoneDisconnected () throw ();

	
public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_PHONE_DISCONNECTED; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize () const throw () { return szPhoneNumber + szSlotID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "GCPhoneDisconnected"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

	// get/set PhoneNumber
	PhoneNumber_t getPhoneNumber() const throw() { return m_PhoneNumber; }
	void setPhoneNumber( PhoneNumber_t PhoneNumber ) throw() { m_PhoneNumber = PhoneNumber; }

	// get/set SlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) throw() { m_SlotID = SlotID; }

private :

	// PhoneNumber
	PhoneNumber_t m_PhoneNumber;

	// SlotID
	SlotID_t m_SlotID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnectedFactory;
//
// Factory for GCPhoneDisconnected
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnectedFactory : public PacketFactory {

public :
	
	// constructor
	GCPhoneDisconnectedFactory () throw () {}
	
	// destructor
	virtual ~GCPhoneDisconnectedFactory () throw () {}

	
public :
	
	// create packet
	Packet * createPacket () throw () { return new GCPhoneDisconnected(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCPhoneDisconnected"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_PHONE_DISCONNECTED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szPhoneNumber + szSlotID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneDisconnectedHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneDisconnectedHandler {

public :

	// execute packet's handler
	static void execute ( GCPhoneDisconnected * pGCPhoneDisconnected , Player * pPlayer ) throw ( Error );

};

#endif
