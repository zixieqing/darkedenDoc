//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGPartySay 
// Written By  :
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CG_PARTY_SAY_H__
#define __CG_PARTY_SAY_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class CGPartySay; //
//////////////////////////////////////////////////////////////////////

class CGPartySay : public Packet {

public:
	
	// constructor
	CGPartySay() throw();
	
	// destructor
	~CGPartySay() throw();

	
public:
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CG_PARTY_SAY; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Message.size() + szuint; }

#ifdef __DEBUG_OUTPUT__
	// get packet name
	string getPacketName() const throw() { return "CGPartySay"; }
	
	// get packet's debug string
	string toString() const throw();
#endif
public:
	void	setMessage( const string& msg ) { m_Message = msg; }
	string	getMessage() const { return m_Message; }

	uint getColor() const throw() { return m_Color; }
	void setColor( uint color ) throw() { m_Color = color; }
	
private :
	uint	m_Color;
	string	m_Message;
	
};


//////////////////////////////////////////////////////////////////////
//
// class CGPartySayFactory;
//
// Factory for CGPartySay
//
//////////////////////////////////////////////////////////////////////

class CGPartySayFactory : public PacketFactory {

public:
	
	// constructor
	CGPartySayFactory() throw() {}
	
	// destructor
	virtual ~CGPartySayFactory() throw() {}

	
public:
	
	// create packet
	Packet* createPacket() throw() { return new CGPartySay(); }

	// get packet name
	string getPacketName() const throw() { return "CGPartySay"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_PARTY_SAY; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 128 + szuint; }

};

//////////////////////////////////////////////////////////////////////
//
// class CGPartySayHandler;
//
//////////////////////////////////////////////////////////////////////

class CGPartySayHandler {
	
public:

	// execute packet's handler
	static void execute(CGPartySay* pCGPartySay, Player* player) throw(Error);
};

#endif
