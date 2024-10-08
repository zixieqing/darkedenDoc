//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTypeStringList.h 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TYPE_STRING_LIST_H__
#define __CG_TYPE_STRING_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"

#include <list>

#define MAX_STRING_LENGTH 50
#define MAX_STRING_NUM 20

//////////////////////////////////////////////////////////////////////////////
// class CGTypeStringList;
//////////////////////////////////////////////////////////////////////////////

class CGTypeStringList : public Packet 
{
public:
	enum StringType
	{
		STRING_TYPE_WAIT_FOR_MEET,
		STRING_TYPE_WAIT_FOR_APART,
		STRING_TYPE_FORCE_APART_COUPLE,
	};
public:
	CGTypeStringList() throw();
	~CGTypeStringList() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_TYPE_STRING_LIST; }
	PacketSize_t getPacketSize() const throw()
	{
		PacketSize_t ret = szBYTE;
		ret+=szBYTE;

		std::list<std::string>::const_iterator itr = m_StringList.begin();
		for( ; itr != m_StringList.end(); ++itr )
		{
			ret += szBYTE + (*itr).size();
		}
		ret += szDWORD;

		return ret; 
	}
#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const throw() { return "CGTypeStringList"; }
	std::string toString() const throw();
#endif
	
public:
	void	setType( StringType type ) { m_StringType = type; }
	BYTE	getType() const { return m_StringType; }

	void	addString( std::string str ) { m_StringList.push_back( str ); }
	void	clearString() { m_StringList.clear(); }
	int		getSize() const { return m_StringList.size(); }
	std::string	popString() { std::string ret = m_StringList.front(); m_StringList.pop_front(); return ret; }

	void	setParam( DWORD param ) { m_Param = param; }
	DWORD	getParam() const		{ return m_Param; }

private:
	BYTE			m_StringType;
	std::list<std::string>	m_StringList;
	DWORD			m_Param;
};

//////////////////////////////////////////////////////////////////////////////
// class CGTypeStringListFactory;
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGTypeStringListFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGTypeStringList(); }
	std::string getPacketName() const throw() { return "CGTypeStringList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_TYPE_STRING_LIST; }
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE+szBYTE + ( szBYTE + MAX_STRING_LENGTH ) * MAX_STRING_NUM + szDWORD; }
};
#endif

#ifndef __GAME_CLIENT__
//////////////////////////////////////////////////////////////////////////////
// class CGTypeStringListHandler;
//////////////////////////////////////////////////////////////////////////////

class CGTypeStringListHandler 
{
public:
	static void execute(CGTypeStringList* pPacket, Player* player) throw(ProtocolException, Error);

private:
	static void executeWaitForMeet(CGTypeStringList* pPacket, Player* player) throw(ProtocolException, Error);
	static void executeWaitForApart(CGTypeStringList* pPacket, Player* player) throw(ProtocolException, Error);
};
#endif

#endif
