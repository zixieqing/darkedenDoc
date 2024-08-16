//----------------------------------------------------------------------
// MActionResultDef.h
//----------------------------------------------------------------------

#ifndef __MACTIONRESULTDEF_H__
#define __MACTIONRESULTDEF_H__

//----------------------------------------------------------------------
//
//                       EffectGenerator ����
//
//----------------------------------------------------------------------

typedef	unsigned short TYPE_ACTIONRESULTID;
#define	SIZE_ACTIONRESULTID			2
#define	ACTIONRESULTID_NULL			0xFFFF

	
//------------------------------------------------------
// ActionInfo�� ��� - Server���� ������ ���
//------------------------------------------------------
enum	ACTIONRESULTNODE_TYPE
{
	ACTIONRESULTNODE_NULL = 0,

	ACTIONRESULTNODE_ACTIONINFO,			// �ٸ� ActionInfo�� �����ϴ� ���			
	ACTIONRESULTNODE_CHANGE_POSITION,		// ĳ���� ��ġ�� ���ϰ� �ϴ� ���
	ACTIONRESULTNODE_CHANGE_STATUS,			// ĳ������ ���¸� ���ϰ� �ϴ� ���
	ACTIONRESULTNODE_CREATURE_DIE,			// � ĳ���Ͱ� �״´�.
	ACTIONRESULTNODE_CREATURE_BURROW,		// � ĳ���Ͱ� ���´�.
	ACTIONRESULTNODE_CREATURE_INVISIBLE,	// � ĳ���Ͱ� �� ���δ�.
	ACTIONRESULTNODE_CREATURE_VISIBLE,		// � ĳ���Ͱ� ���δ�.
	ACTIONRESULTNODE_CREATURE_SNIPPING,		// snipping mode��..
	ACTIONRESULTNODE_ADD_EFFECTSTATUS,		// ĳ���Ϳ� effectstatus�� ���δ�.
	ACTIONRESULTNODE_CHANGE_CREATURE_TYPE,	// Creature type�� �ٲ۴�.
	ACTIONRESULTNODE_SUMMON_CASKET,			// �� ��ȯ
	ACTIONRESULTNODE_OPEN_CASKET,			// ������ ������
	ACTIONRESULTNODE_CREATURE_TURNING,		// ĳ���� ������
	ACTIONRESULTNODE_REMOVE_ITEM_IN_INVENTORY,			// �κ��丮 ������ ���ֱ�
	ACTIONRESULTNODE_CHANGE_ITEM_OPTION_IN_INVENTORY,	// �κ��丮 ������ �ɼ� �ٲٱ�
	ACTIONRESULTNODE_FAKE_DIE,				// ��¥ ĳ���Ͱ� �״´�.
	ACTIONRESULTNODE_EVENT,					// �̺�Ʈ�� ���δ�
	ACTIONRESULTNODE_CHANGE_ITEM_GENDER,

	ACTIONRESULTNODE_MAX
};


#endif