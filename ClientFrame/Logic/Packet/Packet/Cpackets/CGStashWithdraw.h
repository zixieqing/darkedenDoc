////////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashWithdraw.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_STASH_WITHDRAW_H__
#define __CG_STASH_WITHDRAW_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashWithdraw;
//
////////////////////////////////////////////////////////////////////////////////

class CGStashWithdraw : public Packet 
{
public :
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );
	PacketID_t getPacketID () const throw () { return PACKET_CG_STASH_WITHDRAW; }
	PacketSize_t getPacketSize () const throw () { return szGold; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const throw () { return "CGStashWithdraw"; }
		std::string toString () const throw ();
	#endif
	
public :
	Gold_t getAmount(void) const throw() { return m_Amount;}
	void setAmount(Gold_t amount) throw() { m_Amount = amount;}

private :
	Gold_t m_Amount;
};


////////////////////////////////////////////////////////////////////////////////
//
// class CGStashWithdrawFactory;
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGStashWithdrawFactory : public PacketFactory 
{
public :
	Packet * createPacket () throw () { return new CGStashWithdraw(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const throw () { return "CGStashWithdraw"; }
	#endif

	PacketID_t getPacketID () const throw () { return Packet::PACKET_CG_STASH_WITHDRAW; }
	PacketSize_t getPacketMaxSize () const throw () { return szGold; }

};
#endif

////////////////////////////////////////////////////////////////////////////////
//
// class CGStashWithdrawHandler;
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	class CGStashWithdrawHandler {
		
	public :

		// execute packet's handler
		static void execute ( CGStashWithdraw * pPacket , Player * player ) throw ( ProtocolException , Error );
	};
#endif
#endif
