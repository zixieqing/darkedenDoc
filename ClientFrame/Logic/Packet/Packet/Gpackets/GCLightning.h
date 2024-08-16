//--------------------------------------------------------------------------------
// 
// Filename    : GCLightning.h 
// Written By  : reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_LIGHTNING_H__
#define __GC_LIGHTNING_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCLightning;
//
// ������ ���� ���, �������� �� ���� ��� Ŭ���̾�Ʈ�鿡�� �����ϴ� ��Ŷ�̴�.
// 
//
//////////////////////////////////////////////////////////////////////

class GCLightning : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_LIGHTNING; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCLightningPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize () const throw () { return szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		// get packet's name
		std::string getPacketName () const throw () { return "GCLightning"; }
	
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

public :

	// get/set delay
	BYTE getDelay () const throw () { return m_Delay; }
	void setDelay ( BYTE delay ) throw () { m_Delay = delay; }


private :

	// ������ ģ ��, õ���� �� �������� �����̽ð�
	// 1 -> 0.1��
	BYTE m_Delay;

};


//////////////////////////////////////////////////////////////////////
//
// class GCLightningFactory;
//
// Factory for GCLightning
//
//////////////////////////////////////////////////////////////////////

class GCLightningFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCLightning(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCLightning"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_LIGHTNING; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCLightningPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const throw () { return szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCLightningHandler;
//
//////////////////////////////////////////////////////////////////////

class GCLightningHandler {

public :

	// execute packet's handler
	static void execute ( GCLightning * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
