//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCVersionCheckError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_VERSION_CHECK_ERROR_H__
#define __LC_VERSION_CHECK_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckError;
//
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckError : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_LC_VERSION_CHECK_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return 0; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "LCVersionCheckError"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckErrorFactory;
//
// Factory for LCVersionCheckError
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckErrorFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new LCVersionCheckError(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "LCVersionCheckError"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_LC_VERSION_CHECK_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw () { return 0; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCVersionCheckErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCVersionCheckErrorHandler {

public :

	// execute packet's handler
	static void execute ( LCVersionCheckError * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
