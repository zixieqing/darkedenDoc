//--------------------------------------------------------------------------------
// 
// Filename    : GCAddWolf.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_ADD_WOLF_H__
#define __GC_ADD_WOLF_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "types\GuildTypes.h"

//--------------------------------------------------------------------------------
//
// class GCAddWolf;
//
// �þ� �ȿ� Wolf �� ������ ���, �� ��Ŷ�� Wolf ������ ��Ƽ� ���۹޴´�.
//
//--------------------------------------------------------------------------------
class GCAddWolf : public Packet 
{

public :

	// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
			
	// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_WOLF; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddWolfPacketSize �� ����, �����϶�.
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID 
			+ szBYTE + m_Name.size() 
//			+ szSpriteType 
//			+ szColor + szColor
			+ szItemType
			+ szCoord + szCoord + szDir
			+ szHP*2
			+ szGuildID
			+ szColor
			;
	}

	#ifdef __DEBUG_OUTPUT__	
		// get packet's name
		std::string getPacketName() const throw() { return "GCAddWolf"; }
	
		// get packet's debug std::string
		std::string toString() const throw();
	#endif


public :

	// get/set object id
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	// get/set name
	std::string getName() const throw() { return m_Name; }
	void setName(std::string name) throw() { m_Name = name; }

/*
	// get/set sprite type
	SpriteType_t getSpriteType() const throw() { return m_SpriteType; }
	void setSpriteType(SpriteType_t spriteType) throw() { m_SpriteType = spriteType; }

	// get/set main color
	Color_t getMainColor() const throw() { return m_MainColor; }
	void setMainColor(Color_t color) throw() { m_MainColor = color; }

	// get/set sub color
	Color_t getSubColor() const throw() { return m_SubColor; }
	void setSubColor(Color_t color) throw() { m_SubColor = color; }
*/
	// get/set X
	Coord_t getX() const throw() { return m_X; }
	void setXYDir(Coord_t x, Coord_t y, Dir_t Dir) throw() { m_X = x; m_Y = y; m_Dir = Dir; }
	
	// get/set Y
	Coord_t getY() const throw() { return m_Y; }

	// get/set Dir
	Dir_t getDir() const throw() { return m_Dir; }

	// get /set MaxHP
	HP_t getMaxHP() const throw() { return m_MaxHP; }
	void setMaxHP(HP_t MaxHP) throw() { m_MaxHP = MaxHP; }

	// get /set CurrentHP
	HP_t getCurrentHP() const throw() { return m_CurrentHP; }
	void setCurrentHP(HP_t CurrentHP) throw() { m_CurrentHP = CurrentHP; }

	// get/set ItemType
	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType; }

	// get/set GuildID
	GuildID_t getGuildID() const throw() { return m_GuildID; }
	void setGuildID(GuildID_t GuildID) throw() { m_GuildID = GuildID; }

	Color_t getColor() const throw() { return m_MainColor; }
	void setColor( Color_t color ) { m_MainColor = color; }

private :
	
	// �� �������� ����ũ�� ���̵�� ��ü ������ ���ؼ� ����Ѵ�.
	ObjectID_t m_ObjectID;

	// Wolf�� �̸�
	std::string m_Name;
	
	// ���� �������� ����
	ItemType_t m_ItemType;

/*
	// ��������Ʈ Ÿ��
	SpriteType_t m_SpriteType;

	// ���� ����
	Color_t m_SubColor;
*/
	Color_t m_MainColor;
	
	// X, Y �� ����
	Coord_t m_X;
	Coord_t m_Y;
	Dir_t m_Dir;

	HP_t m_CurrentHP;
	HP_t m_MaxHP;
	GuildID_t m_GuildID;

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddWolfFactory;
//
// Factory for GCAddWolf
//
//////////////////////////////////////////////////////////////////////

class GCAddWolfFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddWolf(); }

	#ifdef __DEBUG_OUTPUT__	
		// get packet name
		std::string getPacketName() const throw() { return "GCAddWolf"; }
	#endif
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_WOLF; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCAddWolfPacketSize �� ����, �����϶�.
	PacketSize_t getPacketMaxSize() const throw() 
	{
		return szObjectID 
			+ szBYTE + 20 
//			+ szSpriteType 
//			+ szColor + szColor
			+ szItemType
			+ szCoord + szCoord + szDir
			+ szHP*2
			+ szGuildID
			+ szColor
			;
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCAddWolfHandler;
//
//////////////////////////////////////////////////////////////////////

class GCAddWolfHandler {

public :

	// execute packet's handler
	static void execute(GCAddWolf* pPacket, Player* pPlayer) throw(Error);

};

#endif
