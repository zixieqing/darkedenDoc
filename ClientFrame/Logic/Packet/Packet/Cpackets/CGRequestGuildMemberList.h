//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestGuildMemberList.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_REQUER_GUILD_MEMBER_LIST_H__
#define __CG_REQUER_GUILD_MEMBER_LIST_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildMemberList;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildMemberList : public Packet
{
public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_REQUEST_GUILD_MEMBER_LIST; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szGuildID; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "CGRequestGuildMemberList"; }

	// get packet's debug std::string
	std::string toString() const throw();
#endif

	// get/set GuildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }


private :

	// Guild ID
	GuildID_t m_GuildID;
	
};

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildMemberListFactory;
//
// Factory for CGRequestGuildMemberList
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildMemberListFactory : public PacketFactory {

public:
	
	// constructor
	CGRequestGuildMemberListFactory() throw() {}
	
	// destructor
	virtual ~CGRequestGuildMemberListFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGRequestGuildMemberList(); }

	// get packet name
	std::string getPacketName() const throw() { return "CGRequestGuildMemberList"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_REQUEST_GUILD_MEMBER_LIST; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szGuildID; }
};
#endif

#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGRequestGuildMemberListHandler;
//
//////////////////////////////////////////////////////////////////////

class CGRequestGuildMemberListHandler {

public:

	// execute packet's handler
	static void execute(CGRequestGuildMemberList* pCGRequestGuildMemberList, Player* pPlayer) throw(Error);

};
#endif

#endif
