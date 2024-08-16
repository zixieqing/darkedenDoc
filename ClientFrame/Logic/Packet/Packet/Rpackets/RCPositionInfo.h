//----------------------------------------------------------------------
// 
// Filename    : RCPositionInfo.h 
// Written By  : Reiot
// Description : 
// 
//----------------------------------------------------------------------

#ifndef __RC_POSITION_INFO_H__
#define __RC_POSITION_INFO_H__

// include files
#include "Client_PCH.h"
#include "DatagramPacket.h"
#include "PacketFactory.h"


//----------------------------------------------------------------------
//
// class RCPositionInfo;
//
// ���� �ٸ� Ŭ���̾�Ʈ���� ���ϴ� ��Ŷ
//
//----------------------------------------------------------------------

class RCPositionInfo : public DatagramPacket {

public :
	RCPositionInfo();
	
    // Datagram ��ü�������� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( Datagram & iDatagram ) throw ( ProtocolException , Error );
		    
    // Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( Datagram & oDatagram ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_RC_POSITION_INFO; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szBYTE + m_Name.size() + szZoneID + szCoord + szCoord;			
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "RCPositionInfo"; }
		
		// get packet's debug string
		std::string toString () const throw ();
	#endif

public :
	// get/set ZoneID
	ZoneID_t getZoneID () const throw () { return m_ZoneID; }
	void setZoneID ( const ZoneID_t & zoneID ) throw () { m_ZoneID = zoneID; }

	// get / set ZoneX
	Coord_t getZoneX() const throw() { return m_ZoneX; }
	void setZoneX( Coord_t ZoneX ) { m_ZoneX = ZoneX; }

	// get / set ZoneY
	Coord_t getZoneY() const throw() { return m_ZoneY; }
	void setZoneY( Coord_t ZoneY ) { m_ZoneY = ZoneY; }

	// get/set chatting Name
	std::string getName () const throw () { return m_Name; }
	void setName ( const std::string & msg ) throw () { m_Name = msg; }

protected :
	std::string		m_Name;

	ZoneID_t	m_ZoneID;	

	// ��Ÿ�� ��ǥ�� �밭�� ��ġ
	Coord_t m_ZoneX;
	Coord_t m_ZoneY;	
};


//////////////////////////////////////////////////////////////////////
//
// class RCPositionInfoFactory;
//
// Factory for RCPositionInfo
//
//////////////////////////////////////////////////////////////////////

class RCPositionInfoFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new RCPositionInfo(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "RCPositionInfo"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_RC_POSITION_INFO; }

	PacketSize_t getPacketMaxSize () const throw () 
	{ 
		return szBYTE + 20 + szZoneID + szCoord + szCoord;	
	}

};


//////////////////////////////////////////////////////////////////////
//
// class RCPositionInfoHandler;
//
//////////////////////////////////////////////////////////////////////

class RCPositionInfoHandler {
	
public :

	// execute packet's handler
	static void execute ( RCPositionInfo * pPacket ) throw ( ProtocolException , Error );

};

#endif
