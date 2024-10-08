//////////////////////////////////////////////////////////////////////////////
// Filename    :  GCSkillFailed1.h 
// Written By  :  elca@ewestsoft.com
// Description :  �

//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SKILL_FAILED_1_H__
#define __GC_SKILL_FAILED_1_H__

#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class  GCSkillFailed1;
//////////////////////////////////////////////////////////////////////////////

class GCSkillFailed1 : public ModifyInfo 
{
public:
	GCSkillFailed1() throw();
	~GCSkillFailed1() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SKILL_FAILED_1; }
	PacketSize_t getPacketSize() const throw() { return szSkillType + ModifyInfo::getPacketSize()+ szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "GCSkillFailed1"; }
		std::string toString() const throw();
	#endif

public:
	SkillType_t getSkillType(void) const { return m_SkillType; }
	void setSkillType(SkillType_t SkillType) { m_SkillType = SkillType; }
	
private: 
	SkillType_t m_SkillType;
	BYTE		m_Grade;
};


//////////////////////////////////////////////////////////////////////
//
// class  GCSkillFailed1Factory;
//
// Factory for  GCSkillFailed1
//
//////////////////////////////////////////////////////////////////////

class  GCSkillFailed1Factory : public PacketFactory 
{
public:
	GCSkillFailed1Factory() throw() {}
	virtual ~GCSkillFailed1Factory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCSkillFailed1(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "GCSkillFailed1"; }
	#endif

	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SKILL_FAILED_1; }
	PacketSize_t getPacketMaxSize() const throw() { return szSkillType + ModifyInfo::getPacketMaxSize() + szBYTE; }
};


//////////////////////////////////////////////////////////////////////
//
// class  GCSkillFailed1Handler;
//
//////////////////////////////////////////////////////////////////////

class  GCSkillFailed1Handler 
{
public:
	static void execute( GCSkillFailed1* pGCSkillFailed1, Player* pPlayer) throw(Error);
};

#endif	// __GC_SKILL_FAILED_1_H__
