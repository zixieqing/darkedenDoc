//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUnburrow.h 
// Written By  : crazydog
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_UNBURROW_H__
#define __CG_UNBURROW_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGUnburrow;
//
//////////////////////////////////////////////////////////////////////

class CGUnburrow : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_CG_UNBURROW; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static CGUnburrowPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketSize () const throw () { return szCoord + szCoord + szDir; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "CGUnburrow"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif	
	
public :

	// get/set X Coordicate
	Coord_t getX () const throw () { return m_X; }
	void setX ( Coord_t x ) throw () { m_X = x; }

	// get/set Y Coordicate
	Coord_t getY () const throw () { return m_Y; }
	void setY ( Coord_t y ) throw () { m_Y = y; }

	// get/set Direction
	Dir_t getDir () const throw () { return m_Dir; }
	void setDir ( Dir_t dir ) throw () { m_Dir = dir; }
	
private :
	
	Coord_t m_X;			// X 좌표
	Coord_t m_Y;			// Y 좌표
	Dir_t m_Dir;			// 방향

};


//////////////////////////////////////////////////////////////////////
//
// class CGUnburrowFactory;
//
// Factory for CGUnburrow
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGUnburrowFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new CGUnburrow(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "CGUnburrow"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_CG_UNBURROW; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static CGUnburrowPacketSize 를 정의해서 리턴하라.
	PacketSize_t getPacketMaxSize () const throw () { return szCoord + szCoord + szDir; }

};

#endif


//////////////////////////////////////////////////////////////////////
//
// class CGUnburrowHandler;
//
//////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGUnburrowHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGUnburrow * pPacket , Player * player ) throw ( ProtocolException , Error );
	};
#endif

#endif
