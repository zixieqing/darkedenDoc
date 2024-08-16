//---------------------------------------------------------------------------
// MHelpDef.h"
//---------------------------------------------------------------------------

#ifndef __MHELPDEF_H__
#define __MHELPDEF_H__

//---------------------------------------------------------------------------
// HELP_EVENT
//---------------------------------------------------------------------------
enum HELP_EVENT
{
//	HE_TIME_PASSED,					// �ð��� ���� �� -_-;
//	HE_CREATURE_APPEAR_MONSTER,		// ���� ��Ÿ����
//	HE_CREATURE_APPEAR_NPC,			// NPC ��Ÿ����
//	HE_CREATURE_APPEAR_VAMPIRE,		// Vampire ��Ÿ����
//	HE_CREATURE_APPEAR_SLAYER,		// Slayer�� ��Ÿ����	
//	HE_SKILL_CAN_LEARN_SWORD,		// �� Skill�� ��� �� ���� ��
//	HE_SKILL_CAN_LEARN_BLADE,		// �� Skill�� ��� �� ���� ��
//	HE_SKILL_CAN_LEARN_GUN,		// �� Skill�� ��� �� ���� ��
//	HE_SKILL_CAN_LEARN_HEAL,		// �� Skill�� ��� �� ���� ��
//	HE_SKILL_CAN_LEARN_ENCHANT,		// ��æƮ Skill�� ��� �� ���� ��
//	HE_SKILL_CAN_LEARN_VAMPIRE,		// �����̾� SKill�� ��� �� ���� ��
//	HE_SKILL_LEARNED,				// Skill�� ����� ��
//	HE_SKILL_ICON_CHANGE,			// ��� ������ �ٲ� ��	
//	HE_EFFECT_BLOOD_DRAIN,			// ���� ������ ��
//	HE_EFFECT_GREEN_POISON,			// Green Poison�ɷ��� ��
//	HE_EFFECT_YELLOW_POISON,		// Yellow Poison�ɷ��� ��
//	HE_EFFECT_PURPLE_WALL,			// Purple Wall�ɷ��� ��
//	HE_EFFECT_BLESS,				// Bless�ɷ��� ��
//	HE_EFFECT_STRIKING,				// Striking�ɷ��� ��
//	HE_EFFECT_BURROW,				// Burrow�ϰ� ����
//	HE_STATUS_HP_LOW,				// HP�� ���� ��
//	HE_STATUS_MP_LOW,				// MP�� ���� ��
//	HE_STATUS_BONUS_POINT,			// ���ʽ� point��������		
//	HE_TRADE_REQUESTED,				// ��ȯ��û ���� ��
//	HE_TRADE_REQUEST,				// ��ȯ��û �ϰ� ����
//	HE_TRADE_ITEM_ADD,				// ��ȯ�߿� ������ �߰�
//	HE_TRADE_ITEM_REMOVE,			// ��ȯ�߿� ������ ����	
//	HE_CHAT_WHISPERED,				// �ӼӸ� ���� ��
//	HE_CHAT_WHISPER,				// �ӼӸ� �� ��
//	HE_CHAT_SHOUTED,				// ��ġ�� ���� ��
//	HE_CHAT_SHOUT,					// ��ġ�� �� ��
//	HE_CHAT_REJECT,					// ��ȭ�ź�
//	HE_CHAT_REJECT_USER,			// ��ȭ�ź� �� ��
//	HE_ITEM_APPEAR,					// ��ó�� �������� ��Ÿ������,
//	HE_ITEM_PICKUP,					// �������� �ֿ��� ��	
//	HE_ITEM_USE_BELT_ITEM,			// ��Ʈ ������ ����� ��
//	HE_ITEM_USE_MAGAZINE,			// źâ ����� ��		
//	HE_ITEM_APPEAR_HOLY_WATER,		// ���� ������ ��		
//	HE_ITEM_EMPTY_BULLET,			// �Ѿ� �� ���� ��
//	HE_ITEM_DIFFERENT_BULLET_TYPE,	// �ٸ� �Ѿ��� ���� ��
//	HE_ITEM_DURABILITY_LOW,			// ������ �������� ���� ��
//	HE_ITEM_BROKEN,					// �������� �μ��� ��
//	HE_ITEM_BUY_MOTORCYCLE,			// ������� ��� ����
//	HE_ITEM_RIDE_MOTORCYCLE,		// ������� Ż ��	
//	HE_ITEM_WEAR_BELT,				// ��Ʈ ������ ��
//	HE_ITEM_WEAR_GUN,				// �� ������ ��
//	HE_ITEM_WEAR_SWORD,				// �� ������ ��
//	HE_ITEM_WEAR_BLADE,				// �� ������ ��
//	HE_ITEM_WEAR_CROSS,				// ���ڰ� ������ ��
//	HE_ITEM_WEAR_MACE,				// mace ������ ��
//	HE_ITEM_PICKUP_MONEY,			// �� �ֿ��� ��
//	HE_ITEM_DROP_MONEY,				// �� ������ ��
//	HE_ITEM_APPEAR_CORPSE,			// ��ü�� ������ ��	
//	HE_PRESSED_ALT,					// ALT������
//	HE_PRESSED_FUNCTION_KEY_FOR_QUICKITEM,	// ����Ű�� quickitem����	

	// 2004, 4, 7 sobeit add
	HELP_EVENT_CHAT,				// �۾��� ó�� ���� ������ ��
	HELP_EVENT_INTERFACE,			// �������̽� �⺻ ����
	HELP_EVENT_USE_POTION,			// ������� 30% ������ ��
	HELP_EVENT_GET_ITEM,			// ó�� �������� ȹ�� ���� ��
	HELP_EVENT_USE_SHOP,			// ���� npc�� Ŭ�� ���� ��
	HELP_EVENT_GET_BELT,			// ��Ʈ ������ �����
	HELP_EVENT_ITEM_REPAIR,			// ������ ���� �̹����� �� ��
	// 2004, 4, 7 sobeit end

	// 2004, 5, 3 sobeit add start
	HELP_EVENT_EQUIP_ITEM,			// �κ��丮 ó�� ���� �� ��(���� ����)
	HELP_EVENT_STORAGE_BUY,			// �κ��� �ڸ��� ���ڶ� �� Ȥ�� ���� 10���� �Ѿ��� ��(������ ���� ����)
	HELP_EVENT_FAME,				// ó�� ������ ���� ���� ��
	HELP_EVENT_PARTY,				// ó�� ��Ƽ�� �ξ��� ��
	HELP_EVENT_DIE,					// ó�� �׾��� ��
	HELP_EVENT_KILL,				// ó�� �׿��� ��(���� ����)
	HELP_EVENT_ABSORB_SOUL,			// ��ų ������ �䱸 EP ���� ��(�� ����)
	HELP_EVENT_DRAIN_BLOOD,			// �����̾ ���� ������ ��
	HELP_EVENT_BEGINNER_ZONE,		// �ʺ��� �����- �κ��丮 ���� �ݾ��� ��
	HELP_EVENT_LEARN_SKILL,			// ó�� ��ų ���� ���� �� - ������ 5�� �Ǿ��� ��
	// 2004, 5, 3 sobeit add end

	// 2004, 6, 8 sobeit add start
	HELP_EVENT_LEVEL_30,			// ������30�� �Ǿ����� - ���� Ư��
	HELP_EVENT_LEVEL_31,			// ������31�� �Ǿ����� - ���� �ý���
	HELP_EVENT_LEVEL_32,			// ������32�� �Ǿ����� - �� �ý���
	// 2004, 6, 8 sobeit add end

	// 2004, 9, 14, sobeit add start
	HELP_EVENT_CAMPAIGN,			// ķ���� - �α��� ���ڸ���
	HELP_EVENT_EVENT,				// �̺�Ʈ - �α��� ���ڸ���
	// 2004, 9, 14, sobeit add end
	MAX_HELP_EVENT,

	HELP_EVENT_NULL
};
//	ExecuteHelpEvent( HELP_EVENT_STORAGE_BUY );
//---------------------------------------------------------------------------
// HELP_COMPARE
//---------------------------------------------------------------------------
enum HELP_COMPARE
{
	HC_RANDOM,
	HC_PLAYER_IN_SHOP,
	HC_PLAYER_IN_REPAIR,
	HC_PLAYER_IN_STORAGE,
	HC_PLAYER_IN_TRADE,
	HC_PLAYER_IN_NORMAL_GAME_MODE,
	HC_PLAYER_IS_SLAYER,
	HC_PLAYER_IS_VAMPIRE,
	HC_NO_SKILL_SELECTED,
	HC_NO_SKILL_FUNCTION_KEY_DEFINED,
	HC_HAS_HEAL_POTION_IN_BELT,
	HC_HAS_HEAL_POTION_IN_INVENTORY,
	HC_HAS_MANA_POTION_IN_BELT,
	HC_HAS_MANA_POTION_IN_INVENTORY,
	HC_RECEIVE_FIRST_BONUS_POINT,
	HC_DIDNOT_WHISPER_YET,
	HC_ITEM_PICKED_UP,
	HC_USED_ALT_FOR_ITEM,
	HC_USED_FUNCTION_KEY_FOR_QUICKITEM,
	HC_EMPTY_BULLET,

	MAX_HELP_COMPARE,

	HELP_COMPARE_NULL
};

//---------------------------------------------------------------------------
// HELP_OUTPUT
//---------------------------------------------------------------------------
enum HELP_OUTPUT
{
	HO_ALT_TO_PICKUP_ITEM,
	HO_ALT_TO_TRADE,
	HO_ATTACK_SLAYER_TO_DRAIN,
	HO_BELT_TOGGLE_KEY,
	HO_BETTER_TO_LEARN_FAST_RELOAD_SKILL,
	HO_BROKEN_ITEM_CANNOT_BE_RESTORE,
	HO_CANCEL_TO_CANCEL_TRADE,
	HO_CLICK_BAR_TO_CHANGE_ITEM_TYPE,
	HO_CLICK_ITEM_TO_BUY,
	HO_CLICK_ITEM_TO_REPAIR,
	HO_CLICK_MONSTER_TO_ATTACK,
	HO_CLICK_NPC_TO_TRADE,
	HO_CLICK_PRESS_TO_AUTO_ACTION,
	HO_CLICK_TO_PICKUP,
	HO_CLICK_TO_PLUS_STATUS,
	HO_CTRL_H_TO_BASIC_HELP,
	HO_CTRL_TILDE_TO_QUICKSLOT,
	HO_EACH_GUN_NEED_OWN_MAGAZINE,
	HO_EFFECT_BLESS,
	HO_EFFECT_BURROW,
	HO_EFFECT_GREEN_POISON,
	HO_EFFECT_PURPLE_WALL,
	HO_EFFECT_STRIKING,
	HO_EFFECT_YELLOW_POISON,
	HO_HEAL_POTION_CAN_HEAL,
	HO_HOLY_WATER_DAMAGE_DECIDED_WHEN_CREATE,
	HO_HOW_TO_ACCEPT_CHAT,
	HO_HOW_TO_ACCEPT_CHAT_ALL,
	HO_HOW_TO_CURE_BLOOD_DRAIN,
	HO_HOW_TO_CURE_GREEN_POISON,
	HO_HOW_TO_CURE_PURPLE_WALL,
	HO_HOW_TO_CURE_YELLOW_POISON,
	HO_HOW_TO_GET_HEAL_POTION,
	HO_HOW_TO_GET_MANA_POTION,
	HO_HOW_TO_REJECT_CHAT,
	HO_HOW_TO_SHOUT,
	HO_HOW_TO_UNBURROW,
	HO_HOW_TO_USE_SKILL,
	HO_HOW_TO_WHISPER,
	HO_INVENTORY_MONEY_WILL_AUTO_INCREASE_,
	HO_ITEM_CAN_BE_BROKEN,
	HO_KEEP_MOTORCYCLE_KEY,
	HO_LEFTCLICK_TO_CORPSE_TO_LOOT,
	HO_LEFTCLICK_TO_MOTORCYCLE_TO_RIDE,
	HO_MANA_POTION_CAN_FILL_MANA,
	HO_MONEY_AND_HIGH_LIGHTED_ITEM_AND_OTHER_INVENTORY_ITEM_WILL_TRADE,
	HO_MOVE_ITEM_TO_BELT,
	HO_NEED_RELOAD_TO_USE_GUN,
	HO_NORMAL_ITEM_IS_BASIC_ITEM,
	HO_NPC_OUTLINE_COLOR_IS_GREEN,
	HO_OK_TO_ACCEPT_TRADE,
	HO_ONLY_HIGH_LIGHTED_ITEM_WILL_TRADE,
	HO_ONLY_POTION_AND_MAGAZINE_CAN_STOCK_IN_BELT,
	HO_RECLICK_ITEM_TO_REMOVE_TRADE,
	HO_RELOAD_TIME_IS_LONG,
	HO_REPAIR_COST_IS_UP_TO_DURABILITY,
	HO_RIGHTCLICK_ITEM_TO_ADD_TRADE,
	HO_RIGHTCLICK_ITEM_TO_SHOW,
	HO_SLASH_TO_QUICK_WHISPER,
	HO_SPECIAL_ITEM_IS_GOOD,
	HO_THERE_IS_MONEY,
	HO_THERE_IS_SOME_ITEMS_IN_CORPSE,
	HO_TIME_RESTRICT_SHOUT,
	HO_USE_BLADE_TO_INCREASE_BLADE_SKILL,
	HO_USE_CROSS_TO_INCREASE_HEAL_SKILL,
	HO_USE_FUNCTION_KEY_FOR_QUICKITEM,
	HO_USE_FUNCTION_KEY_TO_SELECT_SKILL,
	HO_USE_GUN_TO_INCREASE_GUN_SKILL,
	HO_USE_HP_POTION_IN_BELT,
	HO_USE_HP_POTION_IN_INVENTORY,
	HO_USE_MACE_TO_INCREASE_ENCHANT_SKILL,
	HO_USE_MAGAZINE_IN_INVENTORY_TO_RELOAD,
	HO_USE_MANA_POTION_IN_BELT,
	HO_USE_MANA_POTION_IN_INVENTORY,
	HO_USE_SWORD_TO_INCREASE_SWORD_SKILL,
	HO_VAMPIRE_IS_DANGEROUS,
	HO_VAMPIRE_IS_OTHER_PLAYER,
	HO_WHERE_CAN_LEARN_BLADE_SKILL,
	HO_WHERE_CAN_LEARN_ENCHANT_SKILL,
	HO_WHERE_CAN_LEARN_GUN_SKILL,
	HO_WHERE_CAN_LEARN_HEAL_SKILL,
	HO_WHERE_CAN_LEARN_SWORD_SKILL,
	HO_WHERE_CAN_LEARN_VAMPIRE_SKILL,
	HO_WHERE_TO_REPAIR,
	HO_YOU_CANNOT_ANY_ACTION_WHEN_RIDE_MOTORCYCLE,
	HO_YOU_CANNOT_USE_RED_ITEM,
	HO_YOU_CANNOT_USE_SHIELD_WITH_BLADE,
	HO_YOU_CANNOT_USE_SHIELD_WITH_CROSS,
	HO_YOU_CANNOT_USE_SHIELD_WITH_MACE,
	HO_YOU_CANT_USE_SKILL_LACK_OF_MANA,
	HO_YOU_CAN_DROP_MONEY_WITH_ICON_IN_INVENTORY,
	HO_YOU_CAN_THROW_HOLY_WATER_WITH_SKILL_SELECT,
	HO_YOU_CAN_USE_SHIELD_WITH_SWORD,
	HO_YOU_MORPH_TO_VAMPIRE_IN_12_HOURS,
	HO_YOU_MUST_REPAIR_ITEM_BEFORE_BROKEN,
	HO_YOU_WILL_DIE_WHEN_HP_ZERO,

	MAX_HELP_OUTPUT,

	HELP_OUTPUT_NULL
};


#endif