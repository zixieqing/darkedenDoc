//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGModifyGuildIntro.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_MODIFY_GUILD_INTRO_H__
#define __CG_MODIFY_GUILD_INTRO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildIntro;
//
//////////////////////////////////////////////////////////////////////

class CGModifyGuildIntro : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_MODIFY_GUILD_INTRO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw()
	{ 
		return szGuildID + szBYTE + m_GuildIntro.size();
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "CGModifyGuildIntro"; }

	// get packet's debug std::string
	std::string toString() const throw();
#endif

	// get/set GuildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t guildID ) throw() { m_GuildID = guildID; }

	// get/set intro
	const std::string& getGuildIntro() const throw() { return m_GuildIntro; }
	void setGuildIntro( const std::string& intro ) throw() { m_GuildIntro = intro; }

private :

	// GuildID
	GuildID_t m_GuildID;

	// Guild Intro
	std::string m_GuildIntro;

};


//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildIntroFactory;
//
// Factory for CGModifyGuildIntro
//
//////////////////////////////////////////////////////////////////////

#ifdef __DEBUG_OUTPUT__
class CGModifyGuildIntroFactory : public PacketFactory {

public:
	
	// constructor
	CGModifyGuildIntroFactory() throw() {}
	
	// destructor
	virtual ~CGModifyGuildIntroFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGModifyGuildIntro(); }

	// get packet name
	std::string getPacketName() const throw() { return "CGModifyGuildIntro"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_MODIFY_GUILD_INTRO; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szGuildID + szBYTE + 255; }
};
#endif

//////////////////////////////////////////////////////////////////////
//
// class CGModifyGuildIntroHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
class CGModifyGuildIntroHandler {

public:

	// execute packet's handler
	static void execute(CGModifyGuildIntro* pCGModifyGuildIntro, Player* pPlayer) throw(Error);

};
#endif

#endif
