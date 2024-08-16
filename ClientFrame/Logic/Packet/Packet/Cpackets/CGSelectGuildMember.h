//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSelectGuildMember.h 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_GUILD_MEMBER_H__
#define __CG_SELECT_GUILD_MEMBER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGSelectGuildMember;
//
//////////////////////////////////////////////////////////////////////

class CGSelectGuildMember : public Packet
{
public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_SELECT_GUILD_MEMBER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szGuildID + szBYTE + m_Name.size(); }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "CGSelectGuildMember"; }

	// get packet's debug std::string
	std::string toString() const throw();
#endif
	// get/set GuildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set name
	const std::string& getName() const throw() { return m_Name; }
	void setName( const std::string& name ) throw() { m_Name = name; }


private :

	// Guild ID
	GuildID_t m_GuildID;

	// name
	std::string m_Name;
	
};


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// class CGSelectGuildMemberFactory;
//
// Factory for CGSelectGuildMember
//
//////////////////////////////////////////////////////////////////////

class CGSelectGuildMemberFactory : public PacketFactory {

public:
	
	// constructor
	CGSelectGuildMemberFactory() throw() {}
	
	// destructor
	virtual ~CGSelectGuildMemberFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGSelectGuildMember(); }

	// get packet name
	std::string getPacketName() const throw() { return "CGSelectGuildMember"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SELECT_GUILD_MEMBER; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szGuildID + szBYTE + 20; }
};
#endif

#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGSelectGuildMemberHandler;
//
//////////////////////////////////////////////////////////////////////

class CGSelectGuildMemberHandler {

public:

	// execute packet's handler
	static void execute(CGSelectGuildMember* pCGSelectGuildMember, Player* pPlayer) throw(Error);

};
#endif

#endif
