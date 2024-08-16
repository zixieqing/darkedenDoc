//----------------------------------------------------------------------
// MEventManager.h
//----------------------------------------------------------------------

#ifndef __MEVENT_MANAGER_H__
#define __MEVENT_MANAGER_H__

#pragma warning(disable:4786)

#include "ctypetable.h"
#include "CDirectDrawSurface.h"

#define	EVENTFLAG_SHOW_STRING				0x00000001		// ȭ�鿡 string�� ǥ���Ѵ�
#define EVENTFLAG_SHOW_DELAY				0x00000002		// DelayŸ���� ȭ�鿡 ǥ���Ѵ�
#define	EVENTFLAG_SHOW_DELAY_STRING			0x00000003		// DelayŸ���� �ִ� string�� ǥ���Ѵ�
#define	EVENTFLAG_SHAKE_SCREEN				0x00000004		// event���� ȭ���� ����. parameter3�� ����Ѵ�
#define	EVENTFLAG_FADE_SCREEN				0x00000008		// event���� ȭ����� �ٲ۴�. parameter2�� ����Ѵ�
#define	EVENTFLAG_NOT_DRAW_BACKGROUND		0x00000010		// event���� ����� ���� �ʴ´�
#define	EVENTFLAG_EVENT_BACKGROUND			0x00000020		// event���� �̺�Ʈ�� �޹���� ����Ѵ�
#define	EVENTFLAG_ONLY_EVENT_BACKGROUND		0x00000030		// event���� ����� ���� �ʰ� �޹���� ����Ѵ�
#define EVENTFLAG_QUEST_INFO				0x00000040		// ���� ����Ʈ ����
#define EVENTFLAG_NOT_DRAW_UI				0x00000080		// �������̽� ������
#define EVENTFLAG_NOT_DRAW_CREATURE			0x00000100		// ũ���� ������
#define EVENTFLAG_NOT_DRAW_INFORMATION		0x00000200		// ȭ�� ���� ������
#define EVENTFLAG_NOT_DRAW_CREATURE_SHADOW	0x00000400		// ũ���� �׸��� ������
#define EVENTFLAG_NOT_DRAW_ITEM				0x00000800		// ������ ������
#define EVENTFLAG_NOT_DRAW_EFFECT			0x00001000		// ����Ʈ ������
#define EVENTFLAG_NOT_DRAW_MOUSE_POINTER	0x00002000		// ���콺 ������ ������
#define EVENTFLAG_DENY_INPUT_MOUSE			0x00004000		// ���콺 �Է� �ȹ��� ����!
#define EVENTFLAG_DENY_INPUT_KEYBOARD		0x00008000		// Ű���� �Է� �ȹ��� ����!
#define EVENTFLAG_DENY_INPUT				0x0000c000		// �Է� �ȹ��� ����!
#define EVENTFLAG_NOT_FADE_SCREEN			0x00010000		// DrawFade����
#define EVENTFLAG_NOT_PLAY_SOUND			0x00020000		// SoundPlay����
#define EVENTFLAG_CLOUD_BACKGROUND			0x00040000		// Ÿ�� ���ʿ� ���� �̹����� �ѷ��ش�..

enum EVENT_ID
{
	EVENTID_NULL,
	EVENTID_HALLUCINATION,			// Hallu�� �ɷȴ�
	EVENTID_KICK_OUT_FROM_ZONE,		// ������ �߹��ϴ� �ð�(��)
	EVENTID_CONTINUAL_GROUND_ATTACK,	// ������ �������� ������ �Ͼ�� ���(��)
	EVENTID_COMBAT_MASTER,				// �����Ϳ� �ο��
	EVENTID_METEOR,						// ���׿� �����Ҷ� ��, ��� �ٲٱ�
	EVENTID_METEOR_SHAKE,				// ���׿� ���� �������� ����
	EVENTID_PREMIUM_HALF,				// �����̾� ����ڴ� ����/��û �ݰ�
	EVENTID_TAX_CHANGE,					// ���� ���� �ٲ�
	EVENTID_LOGOUT,						// ?�� �Ŀ� �α׾ƿ� �մϴ�.
	EVENTID_LOVECHAIN,					// ?�� �Ŀ� �̵� �մϴ�.
	EVENTID_FORCE_LOGOUT_BY_PREMIUM,	// ���� ����ڰ� �ƴ϶� �����Ŀ� �α׾ƿ��� 
	EVENTID_MONSTER_KILL_QUEST,			// ���� ���̱� ���� ����Ʈ ����
	EVENTID_OUSTERS_FIN,
	EVENTID_QUEST_FIN,					// ����Ʈ ��������
	EVENTID_POUR_ITEM,					// %d �� �Ŀ� ����������� �������� �����ϴ�.
	EVENTID_RESURRECT,					// %d �� �Ŀ� ��Ȱ�մϴ�.
	EVENTID_GDR_PRESENT,				// ���巹 ���� 10�ʰ� ��鸲->10�ʰ� ��ο���
	EVENTID_BG_CLOUD,					// ��׶��忡 ����..-_-Ÿ�� ���ʿ�..
	EVENTID_WAR_EFFECT,
	//add by zdj
	EVENTID_ADVANCEMENT_QUEST_ENDING,
	EVENTID_MAX,
};

enum EVENT_TYPE
{
	EVENTTYPE_NULL,		// 
	EVENTTYPE_ZONE,		// Zone�� ���� �Ǹ� ���� �ٲ�� �������.
	EVENTTYPE_EFFECT,	// Effect�� ���� �Ǹ� Effect�� ������� �������. parameter1�� ����Ѵ�

	EVENTTYPE_MAX
};	

enum EVENTBACKGROUND_ID
{
	EVENTBACKGROUNDID_COSMOS,
	EVENTBACKGROUNDID_OUSTERS_SLAYER,
	EVENTBACKGROUNDID_OUSTERS_VAMPIRE,
	EVENTBACKGROUNDID_QUEST_2,
	EVENTBACKGROUNDID_CLOUD,
	
	EVENTBACKGROUNDID_MAX,
};

class MEvent
{
	public:
		MEvent();
		~MEvent();

	public:
		EVENT_ID				eventID;
		EVENT_TYPE				eventType;
		DWORD					eventStartTickCount;
		int						eventDelay;			// ���� : 1/1000��, event�� ���ӽð��̸� 0�� �Ǹ� �̺�Ʈ�� ����ȴ�. -1 : delay����
		int						showTime;
		int						totalTime;
		DWORD					eventFlag;			// event�� Flag
		DWORD					parameter1;			// EVENT_TYPE�� ����(effect id)
		DWORD					parameter2;			// FADE_SCREEN�� ����
		DWORD					parameter3;			// SHAKE_SCREEN�� ����
		DWORD					parameter4;			// EVENT_BACKGROUND�� ����
		std::vector<int>		m_StringsID;		// GameString�� StringID�� ����.

		const bool IsShowTime() const;
};

class MEventManager
{
	public:
		MEventManager();
		~MEventManager();

		void			ProcessEvent();

		void			AddEvent(MEvent &event);

		const bool		IsEmptyEvent() const				{ return m_Events.empty(); }
		const int		GetEventCount() const				{ return m_Events.size(); }
		const MEvent*	GetEvent(EVENT_ID id);

		const bool		IsEmptyEventByFlag(DWORD flag);
		const MEvent*	GetEventByFlag(DWORD flag, int count = 0);
		const int		GetEventCountByFlag(DWORD flag);

		bool			IsEvent(EVENT_ID id);

		void			RemoveEvent(EVENT_ID id);
		void			RemoveAllEvent();
		void			RemoveAllEventByType(EVENT_TYPE type);

		bool					AssertEventBackground(EVENTBACKGROUND_ID id);
		CDirectDrawSurface*		GetEventBackground(EVENTBACKGROUND_ID id) { AssertEventBackground(id); return &m_EventBackGround[id]; }
		
		typedef std::map<EVENT_ID, MEvent>		EVENT_MAP;
		
	protected :
		EVENT_MAP		m_Events;
		CTypeTable<CDirectDrawSurface>	m_EventBackGround;	// �̺�Ʈ ���׸�...
		
};

//----------------------------------------------------------------------
// global
//----------------------------------------------------------------------
extern MEventManager* g_pEventManager;

#endif