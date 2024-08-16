////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItem.h 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////

#ifndef __CG_TRADE_REMOVE_ITEM_H__
#define __CG_TRADE_REMOVE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItem;
//
////////////////////////////////////////////////////////////////////////////////

class CGTradeRemoveItem : public Packet 
{
public:
	void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
	void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );
	PacketID_t getPacketID () const throw () { return PACKET_CG_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketSize () const throw () { return szObjectID*2; }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const throw () { return "CGTradeRemoveItem"; }
		std::string toString () const throw ();
	#endif
	
public:
	ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t id) throw() { m_TargetObjectID = id; }

	ObjectID_t getItemObjectID() const throw() { return m_ItemObjectID; }
	void setItemObjectID(ObjectID_t id) throw() { m_ItemObjectID = id; }

private:
	ObjectID_t m_TargetObjectID; // ��ȯ�� ���ϴ� ������ ObjectID
	ObjectID_t m_ItemObjectID;   // ��ȯ ����Ʈ�� �߰��� �������� OID

};


////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemFactory;
//
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGTradeRemoveItemFactory : public PacketFactory {
public:
	Packet * createPacket () throw () { return new CGTradeRemoveItem(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const throw () { return "CGTradeRemoveItem"; }
	#endif

	PacketID_t getPacketID () const throw () { return Packet::PACKET_CG_TRADE_REMOVE_ITEM; }
	PacketSize_t getPacketMaxSize () const throw () { return szObjectID*2; }
};
#endif

////////////////////////////////////////////////////////////////////////////////
//
// class CGTradeRemoveItemHandler;
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_CLIENT__
	class CGTradeRemoveItemHandler 
	{
	public:
		static void execute ( CGTradeRemoveItem * pPacket , Player * player ) throw ( ProtocolException , Error );
		static void executeSlayer ( CGTradeRemoveItem * pPacket , Player * player ) throw ( ProtocolException , Error );
		static void executeVampire ( CGTradeRemoveItem * pPacket , Player * player ) throw ( ProtocolException , Error );
		static void executeError ( CGTradeRemoveItem * pPacket , Player * player, BYTE ErrorCode ) throw ( ProtocolException , Error );
	};
#endif

#endif
