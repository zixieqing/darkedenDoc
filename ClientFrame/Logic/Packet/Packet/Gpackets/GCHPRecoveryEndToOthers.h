//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryEndToOthers.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_HP_RECOVERY_END_TO_OTHERS_H__
#define __GC_HP_RECOVERY_END_TO_OTHERS_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToOthers;
//
////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToOthers : public Packet {

public :

	GCHPRecoveryEndToOthers() throw( Error );

	virtual ~GCHPRecoveryEndToOthers() throw( Error );
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_HP_RECOVERY_END_TO_OTHERS; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToOthersPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szObjectID + szHP; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "GCHPRecoveryEndToOthers"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

public :

	// get/set creature ID 
	ObjectID_t getObjectID () const throw () { return m_ObjectID; }
	void setObjectID ( ObjectID_t creatureID ) throw () { m_ObjectID = creatureID; }

	// get /set CurrentHP
	HP_t getCurrentHP() const throw() { return m_CurrentHP; }
	void setCurrentHP( HP_t CurrentHP ) throw() { m_CurrentHP = CurrentHP; }

private :
	
    // 존 레벨에서 유니크한 아이디로 객체 구분을 위해서 사용한다.
    ObjectID_t m_ObjectID;

	// 현재 체력
	HP_t m_CurrentHP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToOthersFactory;
//
// Factory for GCHPRecoveryEndToOthers
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToOthersFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCHPRecoveryEndToOthers(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCHPRecoveryEndToOthers"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_HP_RECOVERY_END_TO_OTHERS; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCHPRecoveryEndToOthersPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize () const throw () 
	{ 
		return szObjectID + szHP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCHPRecoveryEndToOthersHandler;
//
//////////////////////////////////////////////////////////////////////

class GCHPRecoveryEndToOthersHandler {

public :

	// execute packet's handler
	static void execute ( GCHPRecoveryEndToOthers * pPacket , Player * pPlayer ) throw ( Error );

};

#endif
