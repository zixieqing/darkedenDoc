//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGJoinGuild.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_JOIN_GUILD_H__
#define __CG_JOIN_GUILD_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGJoinGuild;
//
//////////////////////////////////////////////////////////////////////

class CGJoinGuild : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_JOIN_GUILD; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szGuildID + szGuildMemberRank + szBYTE + m_GuildMemberIntro.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "CGJoinGuild"; }

	// get packet's debug std::string
	std::string toString() const throw();
#endif

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set Guild Member Rank
	GuildMemberRank_t getGuildMemberRank() const throw() { return m_GuildMemberRank; }
	void setGuildMemberRank( GuildMemberRank_t GuildMemberRank ) throw() { m_GuildMemberRank = GuildMemberRank; }

	// get/set Guild Member Intro
	std::string getGuildMemberIntro() const throw() { return m_GuildMemberIntro; }
	void setGuildMemberIntro( const std::string& GuildMemberIntro ) throw() { m_GuildMemberIntro = GuildMemberIntro; }


private :

	// Guild ID
	GuildID_t m_GuildID;

	// Guild Member Rank
	GuildMemberRank_t m_GuildMemberRank;

	// Guild Member Intro
	std::string m_GuildMemberIntro;
	
};

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// class CGJoinGuildFactory;
//
// Factory for CGJoinGuild
//
//////////////////////////////////////////////////////////////////////

class CGJoinGuildFactory : public PacketFactory {

public:
	
	// constructor
	CGJoinGuildFactory() throw() {}
	
	// destructor
	virtual ~CGJoinGuildFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGJoinGuild(); }

	// get packet name
	std::string getPacketName() const throw() { return "CGJoinGuild"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_JOIN_GUILD; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szGuildID + szGuildMemberRank + szBYTE + 256; }
};
#endif

#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGJoinGuildHandler;
//
//////////////////////////////////////////////////////////////////////

class CGJoinGuildHandler {

public:

	// execute packet's handler
	static void execute(CGJoinGuild* pCGJoinGuild, Player* pPlayer) throw(Error);

};
#endif

#endif
