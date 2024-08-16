//--------------------------------------------------------------------------------
// 
// Filename    : GCDeleteInventoryItem.h 
// Written By  : Reiot
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __GC_DELETE_INVENTORY_ITEM_H__
#define __GC_DELETE_INVENTORY_ITEM_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class GCDeleteInventoryItem;
//
//--------------------------------------------------------------------------------

class GCDeleteInventoryItem : public Packet {

public :

	// constructor
	GCDeleteInventoryItem () throw ()
	{
	}

	GCDeleteInventoryItem ( ObjectID_t objectID ) throw ()
		: m_ObjectID(objectID)
	{
	}


public :
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// execute packet's handler
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );

	// get packet id
	PacketID_t getPacketID () const throw () { return PACKET_GC_DELETE_INVENTORY_ITEM; }
	
	// get packet's body size
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szObjectID; 
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCDeleteInventoryItem"; }
		
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

public :

	// get/set object id
	ObjectID_t getObjectID () const throw () { return m_ObjectID; }
	void setObjectID ( ObjectID_t objectID ) throw () { m_ObjectID = objectID; }

private :

	// object id
	ObjectID_t m_ObjectID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteInventoryItemFactory;
//
// Factory for GCDeleteInventoryItem
//
//////////////////////////////////////////////////////////////////////

class GCDeleteInventoryItemFactory : public PacketFactory {

public :
	
	// create packet
	Packet * createPacket () throw () { return new GCDeleteInventoryItem(); }

	#ifdef __DEBUG_OUTPUT__
		// get packet name
		std::string getPacketName () const throw () { return "GCDeleteInventoryItem"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_DELETE_INVENTORY_ITEM; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize () const throw () 
	{ 
		return szObjectID; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCDeleteInventoryItemHandler;
//
//////////////////////////////////////////////////////////////////////

class GCDeleteInventoryItemHandler {

public :

	// execute packet's handler
	static void execute ( GCDeleteInventoryItem * pPacket , Player * player ) throw ( ProtocolException , Error );

};

#endif
