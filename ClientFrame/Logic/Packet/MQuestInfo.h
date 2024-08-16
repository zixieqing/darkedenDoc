#ifndef __QUEST_INFO_HEADER__
#define __QUEST_INFO_HEADER__

enum QUEST_INFO_TYPE
{
	QUEST_INFO_MONSTER_KILL = 0,
	QUEST_INFO_MEET_NPC,
	QUEST_INFO_GATHER_ITEM,
	QUEST_INFO_MINI_GAME,
	
	QUEST_INFO_TYPE_MAX,
	QUEST_INFO_TYPE_NULL
};

class MQuestInfo
{
public  :
	MQuestInfo();
	~MQuestInfo();

	DWORD			GetID() {return m_ID;}
	void			SetID(DWORD id) { m_ID = id; }
	QUEST_INFO_TYPE	GetType() { return m_Type; }
	DWORD			GetTimeLimit() { return m_TimeLimit; }
	
	void			SetTimeLimit(DWORD time) { m_TimeLimit = time; }
	
	void			LoadFromFile(class ifstream& file);
	void			SaveToFile(class ofstream& file );
	void			SetType(QUEST_INFO_TYPE type) { m_Type = type; }
	
protected :
	DWORD			m_ID;						// ����Ʈ ���̵�
	QUEST_INFO_TYPE	m_Type;						// ����Ʈ Ÿ��
	DWORD			m_TimeLimit;				// �ð� ����
};

#endif
