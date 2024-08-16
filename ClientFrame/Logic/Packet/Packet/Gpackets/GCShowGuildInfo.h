//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCShowGuildInfo.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_SHOW_GUILD_INFO_H__
#define __GC_SHOW_GUILD_INFO_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildInfo;
//
// Ŭ���̾�Ʈ�� ��� ��� â�� ��쵵�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildInfo : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_SHOW_GUILD_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw()
	{ 
		return szGuildID +				// Guild ID
			   szBYTE +					// Guild Name length
			   m_GuildName.size() +		// Guild Name
			   szGuildState +			// Guild State
			   szBYTE +					// Guild Master length
			   m_GuildMaster.size() +	// Guild Master
			   szBYTE +					// Guild Member Count
			   szBYTE +					// Guild Intro length
			   m_GuildIntro.size() +	// Guild Intro
			   szGold;					// Join Fee
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "GCShowGuildInfo"; }
	
	// get packet's debug std::string
	std::string toString() const throw();
#endif

	// get/set Guild ID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID( GuildID_t GuildID ) throw() { m_GuildID = GuildID; }

	// get/set Guild Name
	const std::string& getGuildName() const throw() { return m_GuildName; }
	void setGuildName( const std::string& GuildName ) throw() { m_GuildName = GuildName; }

	// get/set Guild State
	GuildState_t getGuildState() const throw() { return m_GuildState; }
	void setGuildState( GuildState_t GuildState ) throw() { m_GuildState = GuildState; }

	// get/set Guild Master
	const std::string& getGuildMaster() const throw() { return m_GuildMaster; }
	void setGuildMaster( const std::string& GuildMaster ) throw() { m_GuildMaster = GuildMaster; }

	// get/set Guild Member Count
	BYTE getGuildMemberCount() const throw() { return m_GuildMemberCount; }
	void setGuildMemberCount( BYTE GuildMemberCount ) throw() { m_GuildMemberCount = GuildMemberCount; }

	// get/set Guild Intro
	const std::string& getGuildIntro() const throw() { return m_GuildIntro; }
	void setGuildIntro( const std::string& GuildIntro ) throw() { m_GuildIntro = GuildIntro; }
	
	// get/set Guild Join Fee
	Gold_t getJoinFee() const throw() { return m_JoinFee; }
	void setJoinFee( Gold_t JoinFee ) throw() { m_JoinFee = JoinFee; }

private :
	
	// Guild ID
	GuildID_t m_GuildID;

	// Guild Name
	std::string m_GuildName;

	// Guild State
	GuildState_t m_GuildState;

	// Guild Master
	std::string m_GuildMaster;

	// Guild Member Count
	BYTE m_GuildMemberCount;

	// Guild Intro
	std::string m_GuildIntro;

	// Guild Join Fee
	Gold_t m_JoinFee;
};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildInfoFactory;
//
// Factory for GCShowGuildInfo
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCShowGuildInfo(); }

	// get packet name
	std::string getPacketName() const throw() { return "GCShowGuildInfo"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SHOW_GUILD_INFO; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw()
	{
		return szGuildID +		// Guild ID
			   szBYTE +			// Guild Name length
			   30 +				// Guild Name
			   szGuildState +	// Guild State
			   szBYTE +			// Guild Master length
			   20 +				// Guild Master
			   szBYTE +			// Guild Member Count
			   szBYTE +			// Guild Intro length
			   256 +			// Guild Intro
			   szGold;			// Guild Join Fee
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCShowGuildInfo;
//
//////////////////////////////////////////////////////////////////////

class GCShowGuildInfoHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCShowGuildInfo* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
