//----------------------------------------------------------------------
// MObjectSelector
//----------------------------------------------------------------------
// mouse�� ������ �����Ҷ�..
// �����ص� �ǳ�?����?�� �����Ѵ�.
//
// -er�ΰ� -or�ΰ� - -;
//----------------------------------------------------------------------

#ifndef __MOBJECTSELECTOR__
#define __MOBJECTSELECTOR__

class MCreature;

class MObjectSelector {
	public :
		enum SELECT_TARGET
		{
			SELECT_ALL,
			SELECT_FRIEND,
			SELECT_ENEMY
		};

		enum SELECT_BY
		{
			SELECT_BY_RACE,
			SELECT_BY_GUILD,
		};


	public :
		MObjectSelector();
		~MObjectSelector();

		//--------------------------------------------------------------
		// ���� ����
		//--------------------------------------------------------------
		void	SelectAll()			{ m_SelectTarget = SELECT_ALL; }		
		void	SelectFriend()		{ m_SelectTarget = SELECT_FRIEND; }
		void	SelectEnemy()		{ m_SelectTarget = SELECT_ENEMY; }

		//--------------------------------------------------------------
		// ���� ����
		//--------------------------------------------------------------
		void	SelectByRace()		{ m_SelectBy = SELECT_BY_RACE; }
		void	SelectByGuild()		{ m_SelectBy = SELECT_BY_GUILD; }

		//--------------------------------------------------------------
		// Can Select - ������ �� �ִ°�?
		//--------------------------------------------------------------
		BOOL	CanSelect(MCreature* pCreature);

		//--------------------------------------------------------------
		// Can Attack - ������ �� �ִ°�?
		//--------------------------------------------------------------
		BOOL	CanAttack(MCreature* pCreature);

		//--------------------------------------------------------------
		// IsWarEnemy - ���￡ ���õ� ���ΰ�?
		//--------------------------------------------------------------
		BOOL	IsWarEnemy(MCreature* pCreature);

		// pk�� ������ zone ����..-> player���� ���ؼ�
//		BOOL	IsAblePKbyZone(MCreature* pCreature);

	protected :
		SELECT_TARGET		m_SelectTarget;
		SELECT_BY			m_SelectBy;
};

extern MObjectSelector* g_pObjectSelector;

#endif

