//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGGuildChat.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_GUILD_CHAT_H__
#define __CG_GUILD_CHAT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CGGuildChat;
//
//////////////////////////////////////////////////////////////////////

class CGGuildChat : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_GUILD_CHAT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw()
	{
		return szBYTE + // type 1: union chat
				szuint +				// text color
			   szBYTE +				// message size
			   m_Message.size();	// chatting message
	}

#ifdef __DEBUG_OUTPUT__
	// get packet name
	std::string getPacketName() const throw() { return "CGGuildChat"; }
	
	// get packet's debug std::string
	std::string toString() const throw();
#endif

	// get/set text color
	uint getColor() const throw() { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }

	// get/set chatting message
	std::string getMessage() const throw() { return m_Message; }
	void setMessage(const std::string msg) throw() { m_Message = msg; }
	
	void SetType( BYTE bType) { m_bType = bType;}
	BYTE GetType() { return m_bType; }

private :
	BYTE m_bType;
	// text color
	uint m_Color;

	// chatting message
	std::string m_Message;
	
};


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// class CGGuildChatFactory;
//
// Factory for CGGuildChat
//
//////////////////////////////////////////////////////////////////////

class CGGuildChatFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CGGuildChat(); }

	// get packet name
	std::string getPacketName() const throw() { return "CGGuildChat"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_GUILD_CHAT; }

	// get packet's max body size
	// message �� �ִ� ũ�⿡ ���� ������ �ʿ��ϴ�.
	PacketSize_t getPacketMaxSize() const throw()
	{
		return szBYTE +	// type 1: union chat
				szuint +			// text color
			   szBYTE +			// message size
			   128;				// chatting message
	}

};
#endif

#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////
//
// class CGGuildChatHandler;
//
//////////////////////////////////////////////////////////////////////

class CGGuildChatHandler {

public:

	// execute packet's handler
	static void execute(CGGuildChat* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};
#endif

#endif
