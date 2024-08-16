//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromInventory.h 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_USE_ITEM_FROM_INVENTORY_H__
#define __CG_USE_ITEM_FROM_INVENTORY_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventory;
//////////////////////////////////////////////////////////////////////////////

class CGUseItemFromInventory : public Packet 
{
public:
	CGUseItemFromInventory () throw ();
	~CGUseItemFromInventory () throw ();

    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_USE_ITEM_FROM_INVENTORY; }

	//modify by viva for notice
	//PacketSize_t getPacketSize() const throw() { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
	//end

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "CGUseItemFromInventory"; }
		std::string toString() const throw();
	#endif	
	
public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	ObjectID_t getInventoryItemObjectID() throw() { return m_InventoryItemObjectID; }
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID) throw() { m_InventoryItemObjectID = InventoryItemObjectID; }
	
	CoordInven_t getX() const throw() { return m_InvenX; }
	void setX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getY() const throw() { return m_InvenY; }
	void setY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }

private:
	ObjectID_t   m_ObjectID; // �������� object id 
	// ���� �κ��丮 �������� ������Ʈ ���̵�. 0�̸� ���� �κ��丮���� ���
	ObjectID_t	 m_InventoryItemObjectID;
	CoordInven_t m_InvenX;   // �������� �κ��丮 ��ǥ X
	CoordInven_t m_InvenY;   // �������� �κ��丮 ��ǥ Y
};


//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventoryFactory;
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
class CGUseItemFromInventoryFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGUseItemFromInventory(); }
	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "CGUseItemFromInventory"; }
	#endif
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_USE_ITEM_FROM_INVENTORY; }
	
	//modify by viva
	//PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szObjectID + szCoordInven + szCoordInven; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + szCoordInven + szCoordInven; }
	//end
};
#endif

//////////////////////////////////////////////////////////////////////////////
// class CGUseItemFromInventoryHandler;
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class Item;

#ifndef __GAME_CLIENT__
	class CGUseItemFromInventoryHandler 
	{
	public:
		static void execute(CGUseItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);

	protected:
		static void executePotion(CGUseItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
		static void executeMagazine(CGUseItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
		static void executeETC(CGUseItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
		static void executeSerum(CGUseItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
		static void executeVampireETC(CGUseItemFromInventory* pPacket, Player* player) throw(ProtocolException, Error);
	};
#endif

#endif
