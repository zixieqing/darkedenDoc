//////////////////////////////////////////////////////////////////////
// 
// Filename    : CLSelectWorld.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CL_SELECT_WORLD_H__
#define __CL_SELECT_WORLD_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class CLSelectWorld;
//
//////////////////////////////////////////////////////////////////////

class CLSelectWorld : public Packet {

public:
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_SELECT_WORLD; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szWorldID; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const throw() { return "CLSelectWorld"; }
		
		// get packet's debug std::string
		std::string toString() const throw() { return "CLSelectWorld"; }
	#endif

	// get / set WorldID
	WorldID_t getWorldID() const throw() { return m_WorldID; }
	void setWorldID(WorldID_t WorldID) throw() { m_WorldID = WorldID; }
	

private :

	WorldID_t m_WorldID;

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectWorldFactory;
//
// Factory for CLSelectWorld
//
//////////////////////////////////////////////////////////////////////

class CLSelectWorldFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLSelectWorld(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName() const throw() { return "CLSelectWorld"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_SELECT_WORLD; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw() { return szWorldID; }

};


//////////////////////////////////////////////////////////////////////
//
// class CLSelectWorldHandler;
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_CLIENT__
	class CLSelectWorldHandler {

	public:

		// execute packet's handler
		static void execute(CLSelectWorld* pPacket, Player* player) throw(ProtocolException, Error);

	};
#endif

#endif
