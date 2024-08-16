//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCQueryResultPlayerID.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_QUERY_RESULT_PLAYER_ID_H__
#define __LC_QUERY_RESULT_PLAYER_ID_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultPlayerID;
//
// Ŭ���̾�Ʈ�� �α��� �������� ���ʿ� �����ϴ� ��Ŷ�̴�.
// ���̵�� �н����尡 ��ȣȭ�Ǿ� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultPlayerID : public Packet {

public :

	// constructor
	LCQueryResultPlayerID () throw () : m_bExist(false) {}

public :

    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_LC_QUERY_RESULT_PLAYER_ID; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szbool
			+ szBYTE + m_PlayerID.size(); 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "LCQueryResultPlayerID"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

public :

	// get/set player id
	std::string getPlayerID () const throw () { return m_PlayerID; }
	void setPlayerID ( const std::string & playerID ) throw () { m_PlayerID = playerID; }

	// get/set player id's existence
	bool isExist () const throw () { return m_bExist; }
	void setExist ( bool bExist = true ) throw () { m_bExist = bExist; }

private :

	// player id
	std::string m_PlayerID;

	// player id's existence
	bool m_bExist;

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultPlayerIDFactory;
//
// Factory for LCQueryResultPlayerID
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultPlayerIDFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new LCQueryResultPlayerID(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "LCQueryResultPlayerID"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_LC_QUERY_RESULT_PLAYER_ID; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw ()
	{ 
		return szbool
			+ szBYTE + 20; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class LCQueryResultPlayerIDHandler;
//
//////////////////////////////////////////////////////////////////////

class LCQueryResultPlayerIDHandler {

public :

	// execute packet's handler
	static void execute ( LCQueryResultPlayerID * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
