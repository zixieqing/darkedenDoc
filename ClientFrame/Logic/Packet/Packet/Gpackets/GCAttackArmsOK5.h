//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK5.h 
// Written By  : elca@ewestsoft.com
// Description : 기술 사용자는 볼 수 있고, 피해자는 볼 수 없는 사람에게 보내는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_ATTACK_ARMS_OK_5_H__
#define __GC_ATTACK_ARMS_OK_5_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK5;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK5 : public Packet {

public :
	
	// constructor
	GCAttackArmsOK5 () throw ();
	
	// destructor
	~GCAttackArmsOK5 () throw ();

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_ATTACK_ARMS_OK_5; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize () const throw () { return szSkillType + szObjectID + szObjectID + szbool; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "GCAttackArmsOK5"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

	// get / set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) throw() { m_ObjectID = ObjectID; }

	// get / set ObjectID
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID( ObjectID_t TargetObjectID ) throw() { m_TargetObjectID = TargetObjectID; }
//	Coord_t getTargetX() const throw() { return m_X;}
//	Coord_t getTargetY() const throw() { return m_Y;}
//	void setTargetXY( Coord_t X, Coord_t Y) throw() { m_X = X; m_Y = Y;}

	// get / set success
	bool getSkillSuccess() const throw() { return m_bSuccess;}
	void setSkillSuccess( bool bSuccess) throw() { m_bSuccess = bSuccess;}
	
	void setSkillType( SkillType_t		SkillType ) { m_SkillType = SkillType; }
	SkillType_t getSkillType() const throw() { return m_SkillType; }		

private :
	
	// ObjectID
	ObjectID_t m_ObjectID;
//	Coord_t m_X, m_Y;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;

	// bool
	bool m_bSuccess;
	SkillType_t m_SkillType;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK5Factory;
//
// Factory for GCAttackArmsOK5
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK5Factory : public PacketFactory {

public :
	
	// constructor
	GCAttackArmsOK5Factory () throw () {}
	
	// destructor
	virtual ~GCAttackArmsOK5Factory () throw () {}

	
public :
	
	// create packet
	Packet * createPacket () throw () { return new GCAttackArmsOK5(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCAttackArmsOK5"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_ATTACK_ARMS_OK_5; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize () const throw () { return szSkillType+szObjectID + szObjectID+ szbool; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCAttackArmsOK5Handler;
//
//////////////////////////////////////////////////////////////////////

class GCAttackArmsOK5Handler {

public :

	// execute packet's handler
	static void execute ( GCAttackArmsOK5 * pGCAttackArmsOK5 , Player * pPlayer ) throw ( Error );

};

#endif
