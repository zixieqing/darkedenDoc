//----------------------------------------------------------------------
// MSkillManager.h
//----------------------------------------------------------------------
//
// < SKILLINFO_NODE >
//
//		�ϳ��� Skill�� ���� �����μ�
//			- SkillID, Skill�̸�
//			- ��� ��ǥ, ���SpriteID
//			- ������ ��� �� �ִ� �����...���� ������ �ִ�.
//
//
// < SkillInfoTable >
//
//		SKILLINFO_NODE�� array�̴�.
//		ACTIONINFO�� ������ ����(ID)�� ������.
//
//
// < MSkillDomain >
//
//		SkillID(==ACTIONINFO)���� �����̴�.
//		SkillDef.h�� ������ Skill�鿡 ���ؼ� 
//		����/����/������..���� ������ ���� ��.
//		stl�� map�� �̿��ؼ� SkillID�� �����Ѵ�.
//		(!) SkillID�� ���� MSkillInfoTable�� �����ؼ� ������ ���� �� �ִ�.
//
//
// < MSkillManager >
//
//		SkillDomain�� array�̴�.
//
//----------------------------------------------------------------------
//
/*
	//---------------------------------------------------------------------
	//
	// Skill Tree ��ü�� �ʱ�ȭ �ϴ� ���
	//
	//---------------------------------------------------------------------
	g_SkillManager.Init( MAX_SKILLDOMAIN );

	//---------------------------------------------------------------------
	// �⺻ ����κ��� skill tree�� �ʱ�ȭ�Ѵ�.
	//---------------------------------------------------------------------
	g_SkillManager[SKILLDOMAIN_BLADE].SetRootSkill( SKILL_SINGLE_BLOW );
	g_SkillManager[SKILLDOMAIN_SWORD].SetRootSkill( SKILL_DOUBLE_IMPACT );
	g_SkillManager[SKILLDOMAIN_GUN].SetRootSkill( SKILL_SNIPPING );
	g_SkillManager[SKILLDOMAIN_GUN].SetRootSkill( SKILL_SHARP_SHOOTING );
	g_SkillManager[SKILLDOMAIN_ENCHANT].SetRootSkill( MAGIC_CREATE_HOLY_WATER );
	g_SkillManager[SKILLDOMAIN_HEAL].SetRootSkill( MAGIC_CURE_POISON );
	g_SkillManager[SKILLDOMAIN_VAMPIRE].SetRootSkill( MAGIC_HIDE );	


	// ���ο��� �ϹǷ�..	  2001.7.10
	 g_SkillManager.Init()�� �ϸ� �ȴ�.


	class ofstream logFile("log\\sword.txt");

	//---------------------------------------------------------------------
	//
	// g_SkillManager����
	// Sword Domain�� Skill���� ������ �۾��Ѵ�.
	//
	//---------------------------------------------------------------------
	MSkillDomain& swordDomain = g_SkillManager[SKILLDOMAIN_SWORD];

	//---------------------------------------------------------------------
	// ��� skill�� ����ٰ� ǥ���Ѵ�.
	//---------------------------------------------------------------------
	swordDomain.LearnSkill( SKILL_DOUBLE_IMPACT );
	swordDomain.LearnSkill( SKILL_TRIPLE_SLASHER );
	swordDomain.LearnSkill( SKILL_SCREW_SLASHER );
	swordDomain.LearnSkill( SKILL_RAINBOW_SLASHER );
	swordDomain.LearnSkill( SKILL_CRUSH_COMBO );
	swordDomain.LearnSkill( SKILL_CROSS_COUNTER );

	//---------------------------------------------------------------------
	// Sword Domain�� ��� ������� ����Ѵ�.
	//---------------------------------------------------------------------
	swordDomain.SetBegin();
	
	while (swordDomain.IsNotEnd())
	{
		// skill�� id�� status
		ACTIONINFO					id		= swordDomain.GetSkillID();
		MSkillDomain::SKILLSTATUS	status	= swordDomain.GetSkillStatus();

		//---------------------------------------
		// status�� ������ ����. 
		//---------------------------------------
		//	MSkillDomain::SKILLSTATUS_LEARNED		// �����.
		//	MSkillDomain::SKILLSTATUS_NEXT			// ������ ��� �� �ִ�.
		//	MSkillDomain::SKILLSTATUS_OTHER			// ������ ��� �� ����.	
		//---------------------------------------
		
		//---------------------------------------
		// id�� �˸� g_SkillInfoTable���� 
		// �� id�� skill�� ���� ������ ���� �� �ִ�.
		//---------------------------------------
		logFile << "[" << id << "] " << g_SkillInfoTable[id].GetName()
				<< " = " << (int)status << endl;

		// ����
		swordDomain.Next();
	}

	logFile.close();
*/
//----------------------------------------------------------------------

#ifndef	__MSKILLMANAGER_H__
#define	__MSKILLMANAGER_H__

#pragma warning(disable:4786)

#include "SkillDef.h"
#include "MString.h"
#include "CTypeTable.h"
#include "DrawTypeDef.h"
#include "ExpInfo.h"
#include "RaceType.h"

class ifstream;
class ofstream;


//----------------------------------------------------------------------
//
//		SKILLINFO_NODE
//
//----------------------------------------------------------------------
class SKILLINFO_NODE {
	public :
		enum ELEMENTAL_DOMAIN
		{
			ELEMENTAL_DOMAIN_NO_DOMAIN = -1,     // ���Ӽ�
			ELEMENTAL_DOMAIN_FIRE,              // �Ұ迭
			ELEMENTAL_DOMAIN_WATER,             // ���迭
			ELEMENTAL_DOMAIN_EARTH,             // �����迭
			ELEMENTAL_DOMAIN_WIND,              // �ٶ��迭
			ELEMENTAL_DOMAIN_COMBAT,            // ���� �Ϲ� �迭
			ELEMENTAL_DOMAIN_ELEMENTAL_COMBAT,  // ���� ���� �迭
			ELEMENTAL_DOMAIN_ETC,               // ��Ÿ(�迭���о���)
			
			ELEMENTAL_DOMAIN_MAX
		};

		typedef	std::list<ACTIONINFO>		SKILLID_LIST;				
		typedef	std::list<int>				SKILLTYPE_LIST;

	public :
		SKILLINFO_NODE();
		SKILLINFO_NODE(int level, const char* name, int x, int y, TYPE_SPRITEID sid, const char* hname)
		{
			Set(level, name, x,y, sid, hname);
		}

		~SKILLINFO_NODE() {}

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void			Set(int level, const char* name, int x, int y, TYPE_SPRITEID sid, const char* hname)
		{
			m_Level		= level;
			m_Name		= name;
			m_X			= x;
			m_Y			= y;
			m_SpriteID	= sid;
			m_HName		= hname;
		}

		void			SetMP(int mp)				{ m_MP = mp; }

		//------------------------------------------------------
		// Add NextSkill
		//------------------------------------------------------
		bool			AddNextSkill(ACTIONINFO id);
		//bool			RemoveNextSkill(ACTIONINFO id);	// �ʿ� ���� �Լ���..

		//------------------------------------------------------
		// Get
		//------------------------------------------------------
		int					GetLevel() const		{ return m_Level; }		
		const char*			GetName() const				{ return m_Name.GetString(); }
		const char*			GetHName() const			{ return m_HName.GetString(); }
		int					GetX() const				{ return m_X; }
		int					GetY() const				{ return m_Y; }
		TYPE_SPRITEID		GetSpriteID() const			{ return m_SpriteID; }
		const SKILLID_LIST& GetNextSkillList() const	{ return m_listNextSkill; }
		int					GetMP() const				{ return m_MP; }

		//------------------------------------------------------
		// ���� Player�� skill���¿� ���� ����
		//------------------------------------------------------
		void				SetExpLevel(int lev)		{ m_ExpLevel = lev; }
		int					GetExpLevel() const			{ return m_ExpLevel; }
		
		//------------------------------------------------------
		// Passive Skill�ΰ�? - ������ ������ ��� �Ұ� ��ų
		//------------------------------------------------------
		bool			IsPassive() const	{ return m_bPassive; }
		void			SetPassive()		{ m_bPassive = true; }
		void			UnSetPassive()		{ m_bPassive = false; }

		//------------------------------------------------------
		// (Always) Active Skill�ΰ�? - ���⿡ ���ֹ��� �ʰ� �׻� ��� ����
		//------------------------------------------------------
		bool			IsActive() const	{ return m_bActive; }
		void			SetActive()			{ m_bActive = true; }
		void			UnSetActive()		{ m_bActive = false; }

		//------------------------------------------------------
		// skill exp
		//------------------------------------------------------
		void				SetSkillExp(int exp)		{ m_SkillExp = exp; }
		int					GetSkillExp() const			{ return m_SkillExp; }		

		//------------------------------------------------------
		// skill step
		//------------------------------------------------------
		void				SetSkillStep(SKILL_STEP step)	{ m_SkillStep = step; }
		SKILL_STEP			GetSkillStep() const			{ return m_SkillStep; }				

		//------------------------------------------------------
		// Available Level
		//------------------------------------------------------
		void				SetLearnLevel(int lv)	{ m_LearnLevel = lv; }
		int					GetLearnLevel() const	{ return m_LearnLevel; }						

		//------------------------------------------------------
		// ���� ��ų ����
		//------------------------------------------------------
		void				SetVampireSkill()		{ m_eSkillRace = RACE_VAMPIRE; }
		bool				IsVampireSkill()		{ return m_eSkillRace == RACE_VAMPIRE; }
		void				SetSlayerSkill()		{ m_eSkillRace = RACE_SLAYER; }
		bool				IsSlayerSkill()			{ return m_eSkillRace == RACE_SLAYER; }
		void				SetOustersSkill()		{ m_eSkillRace = RACE_OUSTERS; }
		bool				IsOustersSkill()		{ return m_eSkillRace == RACE_OUSTERS; }
		
		//------------------------------------------------------
		// ��� ��� Delay
		//------------------------------------------------------
		void				SetDelayTime(DWORD delay);		// ��� ����� �ٽ� ����� �� �ִ� delay�ð� ����
		DWORD				GetDelayTime() const	{ return m_DelayTime; }

		bool				IsAvailableTime() const;		// ���� ��� �����Ѱ�?
		void				SetAvailableTime(int delay = 0);				// ���� �ٷ� ��� �����ϴ�.
		DWORD				GetAvailableTimeLeft() const;	// ���� ��� �ð�
		
		void				SetNextAvailableTime();			// ���� ��� ������ �ð��� �����Ѵ�.

		//------------------------------------------------------
		// ��� ������ ����ΰ�?
		//------------------------------------------------------
		bool				IsEnable() const		{ return m_bEnable; }
		void				SetEnable(bool enable=true);
		//void				SetDisable();

		//------------------------------------------------------
		// File I/O
		//------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

		//------------------------------------------------------
		// Load / Save SERVER_SKILLINFO
		//------------------------------------------------------
		void		LoadFromFileServerSkillInfo(class ifstream& file);
		void        SaveFromFileServerSkillInfo(ofstream& file);

	protected :
		
		int				m_Level;			// ����� level		

		MString			m_Name;				// ��� �̸�
		MString			m_HName;			// ����� ���� �̸�.

		int				m_X, m_Y;			// ȭ�鿡���� ��� ���� ��ġ
		TYPE_SPRITEID	m_SpriteID;			// ����� Icon Sprite

		int				m_MP;				// MP �Һ�

		SKILLID_LIST	m_listNextSkill;	// ������ ��� �� �ִ� �����		

		bool			m_bPassive;			// passive skill�ΰ�?

		bool			m_bActive;			// �׻� ��밡���� skill�ΰ�?

		//------------------------------------------------------
		// ���� Player�� skill���¿� ���� ����
		//------------------------------------------------------
		int				m_ExpLevel;			// ��ų ����
		int				m_SkillExp;			// ��ų ����ġ

		//------------------------------------------------------
		// Skill�� �ܰ�
		//------------------------------------------------------
		SKILL_STEP		m_SkillStep;

		//------------------------------------------------------
		// ��� ��� �� �ִ� ����
		//------------------------------------------------------
		int				m_LearnLevel;

		//------------------------------------------------------
		// ���� ��� ����
		//------------------------------------------------------
		Race			m_eSkillRace;

		//------------------------------------------------------
		// ��� ��� Delay
		//------------------------------------------------------
		DWORD			m_DelayTime;		// ��� ����� �ٽ� ��밡���� delay
		DWORD			m_AvailableTime;	// �ٽ� ��� ������ �ð�
		
		//------------------------------------------------------
		// ��밡���� ����ΰ�?
		//------------------------------------------------------
		bool			m_bEnable;	

	public :
		int			DomainType;		// �� ����� ��� �����ο� ���ϴ°�.
		int			minDamage;		// �ּ� ������ �Ǵ� ȿ��ġ.
		int			maxDamage;		// �ִ� ������ �Ǵ� ȿ��ġ.
		int			minDelay;		// �ּ� ��� ������.
		int			maxDelay;		// �ִ� ��� ������.
		int			minCastTime;	// �ּ� ĳ���� Ÿ��.
		int			maxCastTime;	// �ִ� ĳ���� Ÿ��.		
		int			minDuration;	// �ּ� ���� �ð�
		int			maxDuration;	// �ִ� ���� �ð�
		int			minRange;		// �ּ� �����Ÿ�
		int			maxRange;		// �ִ� �����Ÿ�
		int			maxExp;			// �� ����� 100% ����ġ. 1 ȸ�� + 1 �� �ö�
		
		// �ƿ콺�����
	public:
		int			SkillPoint;
		int			LevelUpPoint;
		SKILLTYPE_LIST		SkillTypeList;
		int			Fire;
		int			Water;
		int			Earth;
		int			Wind;
		int			Sum;
		int			Wristlet;
		int			Stone1;
		int			Stone2;
		int			Stone3;
		int			Stone4;
		int			ElementalDomain;
		BYTE		CanDelete; // ��ų�� �ƿ� ���� �Ҽ� �ִ���..
		
};

//----------------------------------------------------------------------
//
//	MSkillSet
//
//----------------------------------------------------------------------
// SkillID(==ACTIONINFO)���� �����̴�.
//----------------------------------------------------------------------
const BYTE	FLAG_SKILL_ENABLE		= 1;		// ����(!) ��밡���Ѱ�?

class SKILLID_NODE {
	public :
		ACTIONINFO		SkillID;	
		BYTE			Flag;

	public :
		SKILLID_NODE(ACTIONINFO sid, BYTE f=FLAG_SKILL_ENABLE)
		{
			SkillID = sid;
			Flag	= f;
		}

		void	SetEnable()			{ Flag |= FLAG_SKILL_ENABLE; }
		void	SetDisable()		{ Flag &= ~FLAG_SKILL_ENABLE; }
		BYTE	IsEnable() const	{ return Flag & FLAG_SKILL_ENABLE; }

		void	operator = (const SKILLID_NODE& node)
		{
			SkillID		= node.SkillID;
			Flag		= node.Flag;
		}

};
		
class MSkillSet : public std::map<ACTIONINFO, SKILLID_NODE> {
	public :
		// <SkillID>
		typedef	std::map<ACTIONINFO, SKILLID_NODE>		SKILLID_MAP;
	

	public :
		MSkillSet() {}
		~MSkillSet() {}

		//------------------------------------------------------
		// Skill
		//------------------------------------------------------
		bool			AddSkill(ACTIONINFO id, BYTE flag=FLAG_SKILL_ENABLE);		
		bool			RemoveSkill(ACTIONINFO id);		// SkillID ����
		
		//------------------------------------------------------
		// Enable?
		//------------------------------------------------------
		bool			IsEnableSkill(ACTIONINFO id) const;	// id�� skill�� ��� �����Ѱ�?
		bool			EnableSkill(ACTIONINFO id);		// ��밡��
		bool			DisableSkill(ACTIONINFO id);	// ��� �Ұ���

		//------------------------------------------------------
		// ���� ��밡���� skill�� üũ
		//------------------------------------------------------
		// SetAvailableSkills�ϸ� �ڵ����� CheckMP�� �ȴ�.
		//------------------------------------------------------
		void			SetAvailableSkills();	// ��ü üũ
		void			CheckMP();				// mp check

		void			SetAvailableVampireSkills();

	
	protected :
};

//----------------------------------------------------------------------
//
//	MSkillDomain
//
//----------------------------------------------------------------------
// �� SkillDomain�� �����Ѵ�.
//----------------------------------------------------------------------
class MSkillDomain {
	public :
		enum SKILLSTATUS
		{
			SKILLSTATUS_NULL = 0,		// ���� Skill�̴�.
			SKILLSTATUS_LEARNED,		// �����.
			SKILLSTATUS_NEXT,			// ������ ��� �� �ִ�.
			SKILLSTATUS_OTHER			// ������ ��� �� ����.			
		};

		// <SkillID>�� <Skill���� ����>
		typedef	std::map<ACTIONINFO, SKILLSTATUS>		SKILLID_MAP;
	
		// Skill Step List
		typedef std::vector<ACTIONINFO>					SKILL_STEP_LIST;

		// Skill Step Map
		typedef std::map<SKILL_STEP, SKILL_STEP_LIST*>	SKILL_STEP_MAP;


	public :
		MSkillDomain();
		~MSkillDomain();

		//----------------------------------------------------------------------
		// Add Skill - ������ skill���� ������ domain�� �߰��Ѵ�.
		//----------------------------------------------------------------------
		bool		AddSkill(ACTIONINFO id);

		//------------------------------------------------------
		// Clear
		//------------------------------------------------------
		void			Clear();
		void			ClearSkillList();

		//------------------------------------------------------
		// Set Root Skill - domain�� �ֻ��� skill���� 
		//					���� skill���� �߰��Ѵ�.
		//------------------------------------------------------
		bool			SetRootSkill(ACTIONINFO id, bool reset = true);		

		//------------------------------------------------------
		// Set SkillStatus
		//------------------------------------------------------
		// Skill�� ���� ����
		//bool			SetSkillStatus(ACTIONINFO id, SKILLSTATUS status);	

		//------------------------------------------------------
		// Get SkillStatus
		//------------------------------------------------------
		// Skill�� ���´�?
		SKILLSTATUS		GetSkillStatus(ACTIONINFO id) const;	
		
		//bool			RemoveSkill(ACTIONINFO id);				// Skill ����

		//------------------------------------------------------
		// New Skill
		//------------------------------------------------------
		bool			HasNewSkill() const		{ return m_bNewSkill; }
		void			SetNewSkill()			{ m_bNewSkill = true; }	// ���� ��� skill point�� �����.
		void			UnSetNewSkill()			{ m_bNewSkill = false; }
		
		//------------------------------------------------------
		// Learn Skill
		//------------------------------------------------------
		bool			LearnSkill(ACTIONINFO id);		// skill�� ����.
		bool			UnLearnSkill(ACTIONINFO id);	// ��� skill�� �� ���ɷ� �Ѵ�.

		//------------------------------------------------------
		// Iterator
		//------------------------------------------------------
		void			SetBegin()			{ m_iterator = m_mapSkillID.begin(); }
		ACTIONINFO		GetSkillID()		{ return (*m_iterator).first; }
		SKILLSTATUS		GetSkillStatus()	{ return (*m_iterator).second; }
		void			Next()				{ m_iterator++; }		
		bool			IsEnd() const		{ return m_iterator==m_mapSkillID.end(); }
		bool			IsNotEnd() const	{ return m_iterator!=m_mapSkillID.end(); }
		int				GetSize() const		{ return m_mapSkillID.size(); }

		//------------------------------------------------------
		// Level / Exp
		//------------------------------------------------------
		int			GetDomainLevel() const		{ return m_DomainLevel; }
		void		SetDomainLevel(int dl)		{ m_DomainLevel = dl; }
		DWORD		GetDomainExpRemain() const		{ return m_DomainExpRemain; }
		void		SetDomainExpRemain(DWORD de)		{ m_DomainExpRemain = de; }

		//------------------------------------------------------
		// Skill Step 
		//------------------------------------------------------
		BOOL								IsExistSkillStep(SKILL_STEP ss) const;
		const SKILL_STEP_LIST*				GetSkillStepList(SKILL_STEP ss) const;		
		

		//------------------------------------------------------
		// File I/O
		//------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

		//------------------------------------------------------
		// Load SERVER_SKILLINFO
		//------------------------------------------------------
		void		LoadFromFileServerDomainInfo(class ifstream& file);

		//------------------------------------------------------
		// Exp
		//------------------------------------------------------
		const ExpInfo&	GetExpInfo(int level) const;

		// 2004, 11, 9, sobeit add start - ������ ���� �ִٰ� �����Ѵ�.-_-
		void		AddNextSkillForce(ACTIONINFO id);
		bool		IsAvailableDeleteSkill(ACTIONINFO id);
		// 2004, 11, 9, sobeit add end
	protected :	

		//----------------------------------------------------------------------
		// Remove NextSkill - ������ ��� �� �ְ� ǥ�õ� ������� �����Ѵ�.
		//----------------------------------------------------------------------
		void		RemoveNextSkill(ACTIONINFO id);
		void		AddNextSkill(ACTIONINFO id);

		//------------------------------------------------------
		// Level
		//------------------------------------------------------
		void		SetMaxLevel();

		//------------------------------------------------------
		// Add Skill Step
		//------------------------------------------------------
		// ss�� ai�� �߰��Ѵ�.
		void		AddSkillStep(SKILL_STEP ss, ACTIONINFO ai);


	protected :
		SKILLID_MAP::const_iterator	m_iterator;
		SKILLID_MAP					m_mapSkillID;		
		
		int							m_MaxLevel;			// domain�� �ְ� ��� level
		int							m_MaxLearnedLevel;	// ���� ���� �߿��� MAX skill ID
		ACTIONINFO*					m_pLearnedSkillID;	// ��� skill ID		

		// ���ο� skill�� ��� �� �ִ°�?
		bool				 		m_bNewSkill;

		// Domain Level
		int							m_DomainLevel;
		DWORD						m_DomainExpRemain;

		// SkillStep map
		SKILL_STEP_MAP				m_mapSkillStep;

		//
		ExpTable					m_DomainExpTable;
};


//----------------------------------------------------------------------
//
//	SkillInfoTable
//
//----------------------------------------------------------------------
class MSkillInfoTable : public CTypeTable<SKILLINFO_NODE> {
	public :
		MSkillInfoTable();
		~MSkillInfoTable();

		// �ٲ�� ������ �ʱ�ȭ
		void			Init();

		void			LoadFromFileServerSkillInfo(class ifstream& file);
		void			SaveFromFileServerSkillInfo(class ofstream& file);
};

extern MSkillInfoTable*		g_pSkillInfoTable;


//----------------------------------------------------------------------
//
// SkillManager
//
//----------------------------------------------------------------------
class MSkillManager : public CTypeTable<MSkillDomain>
{
	public :
		MSkillManager();
		~MSkillManager();

		void			Init();
		void			InitSkillList();

		//------------------------------------------------------
		// Load SERVER_SKILLINFO
		//------------------------------------------------------
		void		LoadFromFileServerDomainInfo(class ifstream& file);
};

//----------------------------------------------------------------------
//
//	global
//
//----------------------------------------------------------------------
extern MSkillManager*	g_pSkillManager;

extern MSkillSet*		g_pSkillAvailable;

#define					HOLYLAND_BONUS_MAX	12
#define					SWEEPER_BONUS_MAX	12

extern bool				g_abHolyLandBonusSkills[HOLYLAND_BONUS_MAX];
extern bool				g_abSweeperBonusSkills[SWEEPER_BONUS_MAX];
#endif

