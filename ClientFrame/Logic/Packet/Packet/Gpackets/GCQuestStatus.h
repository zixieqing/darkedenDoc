//////////////////////////////////////////////////////////////////////////////
// Filename    : GCMonsterKillQuestStatus.h 
// Written By  : elca@ewestsoft.com
// Description : 
// ����� ���������� ������ ��Ŷ�� ���� Ŭ���� ����
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_MONSTER_KILL_QUEST_STATUS_H__
#define __GC_MONSTER_KILL_QUEST_STATUS_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestStatus;
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatus : public Packet 
{
public:
	GCQuestStatus() throw();
	~GCQuestStatus() throw();
	
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_QUEST_STATUS; }
	PacketSize_t getPacketSize() const throw() { return szWORD + szWORD + szDWORD; }

#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const throw() { return "GCQuestStatus"; }
	std::string toString() const throw();
#endif

public:
	WORD getQuestID() const throw() { return m_QuestID; }
	void setQuestID(WORD e) throw() { m_QuestID = e; }
	
	WORD getCurrentNum() const throw() { return m_CurrentNum; }
	void setCurrentNul(WORD n) throw() { m_CurrentNum = n; }

	DWORD getRemainTime() const throw() { return m_Time; }
	void setRemainTime(DWORD d) throw() { m_Time = d; }
	
private :
	WORD m_QuestID;
	WORD m_CurrentNum;
	DWORD m_Time;
};


//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestStatusFactory;
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatusFactory : public PacketFactory 
{
public :
	GCQuestStatusFactory() throw() {}
	virtual ~GCQuestStatusFactory() throw() {}
	
public:
	Packet* createPacket() throw() { return new GCQuestStatus(); }
#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const throw() { return "GCQuestStatus"; }
#endif
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_QUEST_STATUS; }
	PacketSize_t getPacketMaxSize() const throw() { return szWORD + szWORD + szDWORD; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCMonsterKillQuestStatusHandler;
//////////////////////////////////////////////////////////////////////////////

class GCQuestStatusHandler 
{
public:
	static void execute(GCQuestStatus* pGCQuestStatus, Player* pPlayer) throw(Error);

};

#endif
