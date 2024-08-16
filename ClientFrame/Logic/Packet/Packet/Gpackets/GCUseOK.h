//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseOK.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_USE_OK_H__
#define __GC_USE_OK_H__

// include files
#include "Packet.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCUseOK;
//
//////////////////////////////////////////////////////////////////////

class GCUseOK : public ModifyInfo {

public :

	// Constructor
	GCUseOK() throw();

	// Desctructor
	~GCUseOK() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_USE_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize () const throw () { return ModifyInfo::getPacketSize(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCUseOK"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKFactory;
//
// Factory for GCUseOK
//
//////////////////////////////////////////////////////////////////////

class GCUseOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCUseOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCUseOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_USE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const throw () { return 255; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCUseOKHandler {
	
public :

	// execute packet's handler
	static void execute ( GCUseOK * pPacket , Player * player ) throw ( ProtocolException , Error );
};



//-------------------------------------------GCUseSkillCardOK----------------

//////////////////////////////////////////////////////////////////////
//
// class GCUseSkillCardOK;
//
//////////////////////////////////////////////////////////////////////

class GCUseSkillCardOK : public Packet {

public :

	// Constructor
	GCUseSkillCardOK() throw();

	// Desctructor
	~GCUseSkillCardOK() throw();
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	void setCardType(BYTE CardType) throw() {	m_CardType = CardType;  }

	BYTE getCardType() const throw()	{	return m_CardType;	}

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_USE_SKILLCARD_OK; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketSize () const throw () { return szBYTE; }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCUseSkillCardOK"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

public:
	BYTE m_CardType;

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseSkillCardOKFactory;
//
// Factory for GCUseSkillCardOK
//
//////////////////////////////////////////////////////////////////////

class GCUseSkillCardOKFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCUseSkillCardOK(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCUseSkillCardOK"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_USE_SKILLCARD_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCUseOKPacketSize �� �����ؼ� �����϶�.
	PacketSize_t getPacketMaxSize () const throw () { return szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCUseSkillCardOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCUseSkillCardOKHandler {
	
public :

	// execute packet's handler
	static void execute ( GCUseSkillCardOK * pPacket , Player * player ) throw ( ProtocolException , Error );
};


#endif
