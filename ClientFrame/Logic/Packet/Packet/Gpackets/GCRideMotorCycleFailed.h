//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRideMotorCycleFailed.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RIDE_MOTORCYCLE_FAILED_H__
#define __GC_RIDE_MOTORCYCLE_FAILED_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailed;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailed : public Packet {

public :
	
	// constructor
	GCRideMotorCycleFailed () throw ();
	
	// destructor
	~GCRideMotorCycleFailed () throw ();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_RIDE_MOTORCYCLE_FAILED; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize () const throw () { return szObjectID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "GCRideMotorCycleFailed"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) throw() { m_ObjectID = ObjectID; }

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailedFactory;
//
// Factory for GCRideMotorCycleFailed
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailedFactory : public PacketFactory {

public :
	
	// constructor
	GCRideMotorCycleFailedFactory () throw () {}
	
	// destructor
	virtual ~GCRideMotorCycleFailedFactory () throw () {}

	
public :
	
	// create packet
	Packet * createPacket () throw () { return new GCRideMotorCycleFailed(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCRideMotorCycleFailed"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_RIDE_MOTORCYCLE_FAILED; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const throw () { return szObjectID; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCRideMotorCycleFailedHandler;
//
//////////////////////////////////////////////////////////////////////
class GCRideMotorCycleFailedHandler {

public :

	// execute packet's handler
	static void execute ( GCRideMotorCycleFailed * pGCRideMotorCycleFailed , Player * pPlayer ) throw ( Error );

};

#endif
