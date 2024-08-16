//----------------------------------------------------------------------
// MActionResult.h
//----------------------------------------------------------------------
//
// � ActionInfo�� ����� ǥ���Ǵ� �͵鿡 ���� ����
//
// ACTIONRESULT_NODE�� �����ؼ�(new) Add���ְ�
// �ʿ��Ҷ�, GetIterator��.. �о�� �Ѵ�.
//
// delete�� ���ο��� �Ѵ�.
//
//----------------------------------------------------------------------
/*

- �������� Effectǥ�� 
  ��� --> Server���� --> Effectǥ��

- ���������� Tile�� �����ϴ� Effect
  ��� --> Server���� --> Tile�� Effectǥ��

- ȿ�� ����
  ��� --> Server���� --> ��� ȿ�� ǥ��

- Ÿ�� ���� ����
  ��� --> Server���� --> ��� ������

- ���ο�
  ��� --> Server���� --> ��� ������, ĳ���� �̵�



  = ���� ����� ��� : 
    ����ActionInfo�� �����ְ� 
	Server���� ����� ���� ����� �ٿ��� ���ActionInfo�� �����Ѵ�.

  = Ÿ���� ����� ��� :
    ���۰� ����� ���� �����ϴµ�...
	����ActionInfo�� ���ActionInfo+����� �ٿ��� �Ѵ�.

  = ����ActionInfo���� ���ActionInfo�� ���� pointer
	��� ActionInfo���� ����� ���� list


*/
//----------------------------------------------------------------------


#ifndef	__MACTIONRESULT_H__
#define	__MACTIONRESULT_H__

#pragma warning(disable:4786)

#include <Windows.h>
#include "MTypeDef.h"
#include "MStatus.h"
#include "MActionResultDef.h"
#include "MEffectStatusDef.h"
#include <list>

//----------------------------------------------------------------------
// �ϳ��� ����� ���� ������ ��� �ִ� node�� base class
//----------------------------------------------------------------------
class MActionResultNode {
	public :
		MActionResultNode()		{}
		virtual ~MActionResultNode()	{}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		virtual TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_NULL; }
		
		//------------------------------------------------------
		// � �����ΰ�?
		//------------------------------------------------------
		virtual bool		IsNodeActionInfo() const		{ return false; }		
		virtual bool		IsNodeChangePosition() const	{ return false; }
		virtual bool		IsNodeChangeStatus() const		{ return false; }
		virtual bool		IsNodeCreatureDie() const		{ return false; }
		virtual bool		IsNodeCreatureBurrow() const	{ return false; }
		virtual bool		IsNodeCreatureInvisible() const	{ return false; }
		virtual bool		IsNodeCreatureVisible() const	{ return false; }
		virtual bool		IsNodeCreatureSnipping() const	{ return false; }
		virtual bool		IsNodeAddEffectStatus() const		{ return false; }
		virtual bool		IsNodeChangeCreatureType() const	{ return false; }
		virtual bool		IsNodeSummonCasket() const			{ return false; }
		virtual bool		IsNodeOpenCasket() const			{ return false; }
		virtual bool		IsNodeCreatureTurning() const		{ return false; }
		virtual bool		IsNodeRemoveItemInInventory() const			{ return false; }
		virtual bool		IsNodeChangeItemOptionInInventory() const		{ return false; }
		virtual bool		IsNodeFakeDie() const			{ return false; }
		virtual bool		IsNodeEvent() const			{ return false; }


		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		virtual void		Execute() = 0;
};

//----------------------------------------------------------------------
// ����(UserID) ������(TargetID)���� ActionInfo�� ����� ���node
//----------------------------------------------------------------------
class MActionResultNodeActionInfo : public MActionResultNode {
	public :
		MActionResultNodeActionInfo(TYPE_ACTIONINFO nActionInfo=0, TYPE_OBJECTID uid=0, TYPE_OBJECTID tid=0, TYPE_SECTORPOSITION sX=0, TYPE_SECTORPOSITION sY=0, DWORD delayFrame=0, BYTE temp=0);
		~MActionResultNodeActionInfo()		{};

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_ACTIONINFO; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeActionInfo() const		{ return true; }		

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetUserID(TYPE_OBJECTID uid)	{ m_UserID = uid; }
		void		SetTargetID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		void		SetActionInfo(TYPE_ACTIONINFO ai)	{ m_nActionInfo = ai; }
		void		SetDelayFrame(DWORD df)			{ m_DelayFrame = df; }
		void		SetSX(TYPE_SECTORPOSITION sX)	{ m_sX = sX; }
		void		SetSY(TYPE_SECTORPOSITION sY)	{ m_sY = sY; }
	
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();

	public :
		TYPE_ACTIONINFO			m_nActionInfo;
		
		TYPE_OBJECTID			m_UserID;
		TYPE_OBJECTID			m_TargetID;
		TYPE_SECTORPOSITION		m_sX;
		TYPE_SECTORPOSITION		m_sY;

		DWORD					m_DelayFrame;		
		BYTE					m_Temp;
};


//----------------------------------------------------------------------
// ������(ID)�� ��ǥ(sX,sY)�� �ٲٰ� �ϴ� ���node
//----------------------------------------------------------------------
class MActionResultNodeChangePosition : public MActionResultNode {
	public :
		MActionResultNodeChangePosition(TYPE_OBJECTID uid=0, TYPE_SECTORPOSITION sX=0, TYPE_SECTORPOSITION sY=0);
		~MActionResultNodeChangePosition()		{};

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CHANGE_POSITION; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeChangePosition() const	{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetUserID(TYPE_OBJECTID uid)		{ m_UserID = uid; }
		void		SetX(TYPE_SECTORPOSITION x)	{ m_X = x; }
		void		SetY(TYPE_SECTORPOSITION y)	{ m_Y = y; }
	
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_UserID;
		TYPE_SECTORPOSITION		m_X;
		TYPE_SECTORPOSITION		m_Y;
};

//----------------------------------------------------------------------
// ������(ID)�� ���¸� �ٲٰ� �ϴ� ���node
//----------------------------------------------------------------------
class MActionResultNodeChangeStatus : public MActionResultNode {
	public :
		MActionResultNodeChangeStatus(TYPE_OBJECTID tid=0, MStatus* pStatus=NULL);
		~MActionResultNodeChangeStatus();

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CHANGE_STATUS; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeChangeStatus() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetTargetID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		void		SetStatus(MStatus* pStatus)		{ m_pStatus = pStatus; }

		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
		MStatus*				m_pStatus;
};

//----------------------------------------------------------------------
// ������(ID)�� �װ� �ϴ� ���
//----------------------------------------------------------------------
class MActionResultNodeCreatureDie : public MActionResultNode {
	public :
		MActionResultNodeCreatureDie(TYPE_OBJECTID tid=0) { m_TargetID = tid; }
		~MActionResultNodeCreatureDie() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CREATURE_DIE; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeCreatureDie() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
};

//----------------------------------------------------------------------
// ������(ID)�� �� �ӿ� ���� �ϴ� ���
//----------------------------------------------------------------------
class MActionResultNodeCreatureBurrow : public MActionResultNode {
	public :
		MActionResultNodeCreatureBurrow(TYPE_OBJECTID tid=0) { m_TargetID = tid; }
		~MActionResultNodeCreatureBurrow() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CREATURE_BURROW; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeCreatureBurrow() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
};

//----------------------------------------------------------------------
// ������(ID)�� ������� �ϴ� ��� 
//----------------------------------------------------------------------
class MActionResultNodeCreatureInvisible : public MActionResultNode {
	public :
		MActionResultNodeCreatureInvisible(TYPE_OBJECTID tid=0) { m_TargetID = tid; }
		~MActionResultNodeCreatureInvisible() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CREATURE_INVISIBLE; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeCreatureInvisible() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
};

//----------------------------------------------------------------------
// ������(ID)�� ���̰� �ϴ� ��� 
//----------------------------------------------------------------------
class MActionResultNodeCreatureVisible : public MActionResultNode {
	public :
		MActionResultNodeCreatureVisible(TYPE_OBJECTID tid=0) { m_TargetID = tid; }
		~MActionResultNodeCreatureVisible() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CREATURE_VISIBLE; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeCreatureVisible() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
};

//----------------------------------------------------------------------
// ������(ID)�� �� �ӿ� ���� �ϴ� ���
//----------------------------------------------------------------------
class MActionResultNodeAddEffectStatus : public MActionResultNode {
	public :
		MActionResultNodeAddEffectStatus(TYPE_OBJECTID tid, EFFECTSTATUS es, DWORD df) { m_TargetID = tid; m_EffectStatus=es; m_DelayFrame=df; }
		~MActionResultNodeAddEffectStatus() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_ADD_EFFECTSTATUS; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeAddEffectStatus() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		void		SetEffectStatus(EFFECTSTATUS es)	{ m_EffectStatus = es; }
		void		SetCreatureID(DWORD df)				{ m_DelayFrame = df; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID		m_TargetID;				// ���
		EFFECTSTATUS		m_EffectStatus;		// ���̴� effect
		DWORD				m_DelayFrame;		// ���� �ð�		
};

//----------------------------------------------------------------------
// ������(ID)�� snipping mode��..
//----------------------------------------------------------------------
class MActionResultNodeCreatureSnipping : public MActionResultNode {
	public :
		MActionResultNodeCreatureSnipping(TYPE_OBJECTID tid=0) { m_TargetID = tid; }
		~MActionResultNodeCreatureSnipping() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CREATURE_SNIPPING; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeCreatureSnipping() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
};

//----------------------------------------------------------------------
// CreatureType�� �ٲٴ� Result
//----------------------------------------------------------------------
class MActionResultNodeChangeCreatureType : public MActionResultNode {
	public :
		MActionResultNodeChangeCreatureType(TYPE_OBJECTID tid=0, int ctype=0);
		~MActionResultNodeChangeCreatureType();

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CHANGE_CREATURE_TYPE; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeChangeCreatureType() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetTargetID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		void		SetCreatureType(int ctype)		{ m_CreatureType = ctype; }

		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
		int						m_CreatureType;
};

//----------------------------------------------------------------------
// �� ��ȯ (tid�� (x,y)���� �� ��ȯ)
//----------------------------------------------------------------------
class MActionResultNodeSummonCasket : public MActionResultNode {
	public :
		MActionResultNodeSummonCasket(TYPE_OBJECTID tid=0, int casketType=0);
		~MActionResultNodeSummonCasket();

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_SUMMON_CASKET; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeSummonCasket() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetTargetID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		void		SetType(int type)				{ m_CasketType = type; }

		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
		int						m_CasketType;
};

//----------------------------------------------------------------------
// ������ ������
//----------------------------------------------------------------------
class MActionResultNodeOpenCasket : public MActionResultNode {
	public :
		MActionResultNodeOpenCasket(TYPE_OBJECTID tid=0);
		~MActionResultNodeOpenCasket();

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_OPEN_CASKET; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeOpenCasket() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetTargetID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;		
};

//----------------------------------------------------------------------
// ������(ID)�� ������� �ϴ� ��� 
//----------------------------------------------------------------------
class MActionResultNodeCreatureTurning : public MActionResultNode {
	public :
		MActionResultNodeCreatureTurning(TYPE_OBJECTID tid=0, WORD frame=0) { m_TargetID = tid; m_TurnFrame = frame; }
		~MActionResultNodeCreatureTurning() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CREATURE_TURNING; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeCreatureTurning() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
		WORD					m_TurnFrame;
};

//----------------------------------------------------------------------
// �κ��丮 ������(ID)�� ����
//----------------------------------------------------------------------
class MActionResultNodeRemoveItemInInventory : public MActionResultNode {
	public :
		MActionResultNodeRemoveItemInInventory(TYPE_OBJECTID tid=0) { m_TargetID = tid; }
		~MActionResultNodeRemoveItemInInventory() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_REMOVE_ITEM_IN_INVENTORY; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeRemoveItemInInventory() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetItemID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
};

//----------------------------------------------------------------------
// �κ��丮 ������(ID)�� �ɼ��� �ٲ�
//----------------------------------------------------------------------
class MActionResultNodeChangeItemOptionInInventory : public MActionResultNode {
	public :
		MActionResultNodeChangeItemOptionInInventory(TYPE_OBJECTID tid=0, DWORD type = 0) { m_TargetID = tid; m_Type = type; }
		~MActionResultNodeChangeItemOptionInInventory() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_CHANGE_ITEM_OPTION_IN_INVENTORY; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeChangeItemOptionInInventory() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetItemID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		void		SetOption(DWORD type)	{ m_Type = type; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
		DWORD			m_Type;
};

class MActionResultNodeChangeItemGenderInInventory : public MActionResultNode 
{
public :
	MActionResultNodeChangeItemGenderInInventory( TYPE_OBJECTID tid=0, DWORD type = 0 ) { m_TargetID = tid; m_Type = type; }
	~MActionResultNodeChangeItemGenderInInventory() {}

	TYPE_ACTIONRESULTID		GetType() const { return ACTIONRESULTNODE_CHANGE_ITEM_GENDER; }
	bool					IsNodeChangeItemOptionInInventory() const { return false; }

	void					SetItemID(TYPE_OBJECTID tid) { m_TargetID = tid; }
	void					SetOption(DWORD type) { m_Type = type; }

	void					Execute();

public :
	TYPE_OBJECTID			m_TargetID;
	DWORD					m_Type;
};

//----------------------------------------------------------------------
// ������(ID)�� �������(��¥ ĳ���� ������) �ϴ� ���
//----------------------------------------------------------------------
class MActionResultNodeFakeDie : public MActionResultNode {
	public :
		MActionResultNodeFakeDie(TYPE_OBJECTID tid=0) { m_TargetID = tid; }
		~MActionResultNodeFakeDie() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_FAKE_DIE; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeFakeDie() const		{ return true; }

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void		SetCreatureID(TYPE_OBJECTID tid)	{ m_TargetID = tid; }
		
		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		TYPE_OBJECTID			m_TargetID;
};

//----------------------------------------------------------------------
// �̺�Ʈ�� �߰��Ѵ�
//----------------------------------------------------------------------
class MActionResultNodeEvent : public MActionResultNode {
	public :
		MActionResultNodeEvent(int skillID) { m_skillID = skillID; }
		~MActionResultNodeEvent() {}

		//------------------------------------------------------
		// ActionResult�� ����
		//------------------------------------------------------
		TYPE_ACTIONRESULTID		GetType() const		{ return ACTIONRESULTNODE_EVENT; }

		//------------------------------------------------------
		// class type
		//------------------------------------------------------
		bool		IsNodeEvent() const		{ return true; }

		//------------------------------------------------------
		// ����� �����Ų��.
		//------------------------------------------------------
		void		Execute();
		
	public :
		int			m_skillID;
};


//----------------------------------------------------------------------
// ActionInfo�� ���� Server���� �������� ������� list
//----------------------------------------------------------------------
typedef	std::list<MActionResultNode*>	ACTIONRESULTNODE_LIST;


//----------------------------------------------------------------------
// � ActionInfo�� ���ؼ� �߻��� ��� ����� 
// Server�κ��� ������ ���� �Ŀ�.. �װ͵��� ��~ �����ϰ� �ִ� class
//
// destructor���� Execute�ع����� ������
// ������ �ʿ䰡 ���ٸ� Release�ؾ��Ѵ�.
//----------------------------------------------------------------------
class MActionResult {
	public :
		MActionResult();
		~MActionResult();

		//--------------------------------------------------------
		// Release
		//--------------------------------------------------------
		void		Release();

		//--------------------------------------------------------
		// ��� �ϳ��� �߰��Ѵ�.
		//--------------------------------------------------------
		void		Add(MActionResultNode* pNode);

		//--------------------------------------------------------
		// Get
		//--------------------------------------------------------
		bool		IsEmpty() const		{ return m_List.empty(); }
		int			GetSize() const		{ return m_List.size(); }
		ACTIONRESULTNODE_LIST::const_iterator GetIterator() const	{ return m_List.begin(); }

		//--------------------------------------------------------
		// ����� �����Ѵ�.
		//--------------------------------------------------------
		void		Execute();

	protected :
		ACTIONRESULTNODE_LIST		m_List;
};

#endif

