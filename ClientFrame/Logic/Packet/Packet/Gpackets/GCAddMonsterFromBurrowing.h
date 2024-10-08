//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddMonsterFromBurrowing.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_MONSTER_FROM_BURROWING_H__
#define __GC_ADD_MONSTER_FROM_BURROWING_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromBurrowing;
////////////////////////////////////////////////////////////////////

class GCAddMonsterFromBurrowing : public Packet 
{
public:
	GCAddMonsterFromBurrowing() throw( Error );
	virtual ~GCAddMonsterFromBurrowing() throw( Error );
	
public:
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );
	void execute ( Player * pPlayer ) throw ( ProtocolException , Error );
	PacketID_t getPacketID () const throw () { return PACKET_GC_ADD_MONSTER_FROM_BURROWING; }
	PacketSize_t getPacketSize () const throw () 
	{ 
		return szObjectID + // object id
			szMonsterType + // monster type
			szBYTE + // monster name length
			m_MonsterName.size() + // monster name
			szColor + // monster main color
			szColor +  // monster sub color
			szCoord + // x coord
			szCoord + // y coord
			szDir +  // direction
			m_pEffectInfo->getSize() + // effects info on monster
			szHP * 2; // current & max hp
	}

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const throw () { return "GCAddMonsterFromBurrowing"; }
		std::string toString () const throw ();
	#endif

public:
	ObjectID_t getObjectID () const throw () { return m_ObjectID; }
	void setObjectID ( ObjectID_t creatureID ) throw () { m_ObjectID = creatureID; }

	MonsterType_t getMonsterType () const throw () { return m_MonsterType; }
	void setMonsterType ( MonsterType_t monsterType ) throw () { m_MonsterType = monsterType; }

	std::string getMonsterName() const throw() { return m_MonsterName; }
	void setMonsterName(std::string name) throw() { m_MonsterName = name; }

	Color_t getMainColor () const throw () { return m_MainColor; }
	void setMainColor ( Color_t color ) throw () { m_MainColor = color; }

	Color_t getSubColor () const throw () { return m_SubColor; }
	void setSubColor ( Color_t color ) throw () { m_SubColor = color; }

	Coord_t getX () const throw () { return m_X; }
	void setX ( Coord_t x ) throw () { m_X = x; }
	
	Coord_t getY () const throw () { return m_Y; }
	void setY ( Coord_t y ) throw () { m_Y = y; }

	Dir_t getDir () const throw () { return m_Dir; }
	void setDir ( Dir_t dir ) throw () { m_Dir = dir; }

	EffectInfo * getEffectInfo() const throw() { return m_pEffectInfo; }
	void setEffectInfo( EffectInfo * pEffectInfo ) throw() { m_pEffectInfo = pEffectInfo; }

	HP_t getMaxHP() const throw() { return m_MaxHP; }
	void setMaxHP( HP_t MaxHP ) throw() { m_MaxHP = MaxHP; }

	HP_t getCurrentHP() const throw() { return m_CurrentHP; }
	void setCurrentHP( HP_t CurrentHP ) throw() { m_CurrentHP = CurrentHP; }

private :
    ObjectID_t    m_ObjectID;    // object id
	MonsterType_t m_MonsterType; // monster type
	std::string        m_MonsterName; // monster name
	Color_t       m_MainColor;   // monster main color
	Color_t       m_SubColor;    // monster sub color
   	Coord_t       m_X;           // x coord.
	Coord_t       m_Y;           // y coord.
	Dir_t         m_Dir;         // monster direction
	EffectInfo*   m_pEffectInfo; // effects info on monster
	HP_t          m_CurrentHP;   // current hp
	HP_t          m_MaxHP;       // maximum hp

};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromBurrowingFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFromBurrowingFactory : public PacketFactory 
{
public:
	Packet * createPacket () throw () { return new GCAddMonsterFromBurrowing(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName () const throw () { return "GCAddMonsterFromBurrowing"; }
	#endif

	PacketID_t getPacketID () const throw () { return Packet::PACKET_GC_ADD_MONSTER_FROM_BURROWING; }
	PacketSize_t getPacketMaxSize () const throw () 
	{ 
		return szObjectID               // object id
			+ szMonsterType             // monster type
			+ szBYTE                    // monster name length
			+ 32                        // monster namx max
			+ szColor + szColor         // monster main & sub color 
			+ szCoord + szCoord + szDir // monster x, y coord & direction
			+ EffectInfo::getMaxSize()  // effects info on monster
			+ szHP * 2;                 // current & max hp
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddMonsterFromBurrowingHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddMonsterFromBurrowingHandler 
{
public:
	static void execute ( GCAddMonsterFromBurrowing * pPacket , Player * pPlayer ) throw ( Error );

};

#endif
