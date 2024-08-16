//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNotifyWin.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NOTIFY_WIN_H__
#define __GC_NOTIFY_WIN_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWin;
// NPC �� ��縦 �ֺ��� PC �鿡�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

class GCNotifyWin : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_NOTIFY_WIN; }
	PacketSize_t getPacketSize() const throw() { return szDWORD + szBYTE + m_Name.size(); }
	
#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const throw() { return "GCNotifyWin"; }
	std::string toString() const throw();
#endif

	DWORD getGiftID() const throw() { return m_GiftID; }
	void setGiftID(DWORD gID) throw() { m_GiftID = gID; }

	std::string getName() const throw() { return m_Name; }
	void setName(const std::string & msg) throw() { m_Name = msg; }

private:
	DWORD		m_GiftID; // NPC's object id
	std::string		m_Name;  // chatting message
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWinFactory;
//////////////////////////////////////////////////////////////////////////////


class GCNotifyWinFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNotifyWin(); }
	std::string getPacketName() const throw() { return "GCNotifyWin"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_NOTIFY_WIN; }
	PacketSize_t getPacketMaxSize() const throw() { return szDWORD + szBYTE + 2048 ; }
};


//////////////////////////////////////////////////////////////////////////////
// class GCNotifyWinHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNotifyWinHandler 
{
public:
	static void execute(GCNotifyWin* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
