//////////////////////////////////////////////////////////////////////
// 
// Filename    :  GCSkillFailed2.h 
// Written By  :  elca@ewestsoft.com
// Description :  �

//                
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_FAILED_2_H__
#define __GC_SKILL_FAILED_2_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class  GCSkillFailed2;
//
//////////////////////////////////////////////////////////////////////

class GCSkillFailed2 : public Packet {

public :
	
	// constructor
	GCSkillFailed2 () throw ();
	
	// destructor
	~GCSkillFailed2 () throw ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_SKILL_FAILED_2; }
	
	// get packet size
	PacketSize_t getPacketSize () const throw () { return szObjectID + szObjectID + szSkillType + szBYTE; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "GCSkillFailed2"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif
	
	// get/set ObjectID
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID( ObjectID_t ObjectID ) throw() { m_ObjectID = ObjectID; }

	// get/set TargetObjectID
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID( ObjectID_t TargetObjectID ) throw() { m_TargetObjectID = TargetObjectID; }

	// get/set SkillType
	SkillType_t getSkillType() const throw() { return m_SkillType; }
	void setSkillType( SkillType_t SkillType ) throw() { m_SkillType = SkillType; }
	
	BYTE		getGrade()	const throw() { return m_Grade; }
	void		setGrade(BYTE grade) throw() { m_Grade = grade; }

private : 

	// ObjectID
	ObjectID_t m_ObjectID;

	// TaragetObjectID
	ObjectID_t m_TargetObjectID;

	// SkillType
	SkillType_t m_SkillType;

	BYTE		m_Grade;

};


//////////////////////////////////////////////////////////////////////
//
// class  GCSkillFailed2Factory;
//
// Factory for  GCSkillFailed2
//
//////////////////////////////////////////////////////////////////////

class  GCSkillFailed2Factory : public PacketFactory {

public :
	
	// constructor
	 GCSkillFailed2Factory () throw () {}
	
	// destructor
	virtual ~GCSkillFailed2Factory () throw () {}

	
public :
	
	// create packet
	Packet * createPacket () throw () { return new GCSkillFailed2(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCSkillFailed2"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_SKILL_FAILED_2; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return  szObjectID + szObjectID + szSkillType + szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class  GCSkillFailed2Handler;
//
//////////////////////////////////////////////////////////////////////

class  GCSkillFailed2Handler {

public :

	// execute packet's handler
	static void execute (  GCSkillFailed2 * pGCSkillFailed2 , Player * pPlayer ) throw ( Error );

};

#endif	// __GC_SKILL_FAILED_2_H__
