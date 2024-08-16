//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPhoneSay.h 
// Written By  : elca 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PHONE_SAY_H__
#define __GC_PHONE_SAY_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSay;
//
// ���� ������ Ư�� �÷��̾��� PhoneSay �� �ٸ� �÷��̾�鿡�� ��ε�ĳ��Ʈ
// �� �� �����ϴ� ��Ŷ�̴�. ���ο� ĳ���͸�� PhoneSay ��Ʈ���� ����Ÿ
// �ʵ�� ������ �ִ�.
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSay : public Packet {

public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_PHONE_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () { return szSlotID + szBYTE + m_Message.size(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCPhoneSay"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

	// get/set SlotID
	SlotID_t getSlotID() const throw() { return m_SlotID; }
	void setSlotID( SlotID_t SlotID ) throw() { m_SlotID = SlotID; }

	// get/set chatting message
	std::string getMessage () const throw () { return m_Message; }
	void setMessage ( const std::string & msg ) throw () { m_Message = msg; }
	

private :

	// SlotID
	SlotID_t m_SlotID;
	
	// chatting message
	std::string m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSayFactory;
//
// Factory for GCPhoneSay
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSayFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCPhoneSay(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCPhoneSay"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_PHONE_SAY; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPhoneSayPacketMaxSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize () const throw () { return szSlotID + szBYTE + 128 ; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPhoneSayHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPhoneSayHandler {
	
public :
	
	// execute packet's handler
	static void execute ( GCPhoneSay * pPacket , Player * pPlayer ) throw ( ProtocolException , Error );

};

#endif
