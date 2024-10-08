//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddHelicopter.h 
// Written By  : excel96
// Description :
// 슬레이어가 무전기를 사용해, 헬기를 호출했을 경우에 날아가는 패킷
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_HELICOPTER_H__
#define __GC_ADD_HELICOPTER_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddHelicopter;
//////////////////////////////////////////////////////////////////////////////

class GCAddHelicopter : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_HELICOPTER; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "GCAddHelicopter"; }
		std::string toString() const throw();
	#endif

public:
	ObjectID_t getObjectID(void) const { return m_ObjectID; }
	void setObjectID(ObjectID_t d) { m_ObjectID = d; }

	BYTE getCode(void) const { return m_Code; }
	void setCode(BYTE code) { m_Code = code; }
	
private:
	ObjectID_t  m_ObjectID; // 헬기를 호출한 슬레이어의 오브젝트 ID
	BYTE        m_Code;     // 0이 호출, 1이 제거
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddHelicopterFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddHelicopterFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddHelicopter(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "GCAddHelicopter"; }
	#endif

	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_HELICOPTER; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szBYTE; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddHelicopterHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddHelicopterHandler 
{
public:
	static void execute(GCAddHelicopter* pGCAddHelicopter, Player* pPlayer) throw(Error);
};

#endif
