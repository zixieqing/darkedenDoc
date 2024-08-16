//////////////////////////////////////////////////////////////////////
// 
// Filename    : LCRegisterPlayerError.h 
// Written By  : Reiot
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LC_REGISTER_PLAYER_ERROR_H__
#define __LC_REGISTER_PLAYER_ERROR_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerError;
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerError : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_LC_REGISTER_PLAYER_ERROR; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return szBYTE; }
	
	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "LCRegisterPlayerError"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif
	
	BYTE getErrorID() const throw() { return m_ErrorID; }
	void setErrorID( BYTE ErrorID ) throw() { m_ErrorID = ErrorID; }

private : 

	// ���� ID
	BYTE m_ErrorID;

};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerErrorFactory;
//
// Factory for LCRegisterPlayerError
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerErrorFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new LCRegisterPlayerError(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "LCRegisterPlayerError"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_LC_REGISTER_PLAYER_ERROR; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw () { return szBYTE; }
	
};


//////////////////////////////////////////////////////////////////////
//
// class LCRegisterPlayerErrorHandler;
//
//////////////////////////////////////////////////////////////////////

class LCRegisterPlayerErrorHandler {

public :

	// execute packet's handler
	static void execute ( LCRegisterPlayerError * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
