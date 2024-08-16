#ifndef	__MODIFYDEF_H__
#define	__MODIFYDEF_H__



enum ModifyType {

	MODIFY_BASIC_STR = 0,        // �⺻ STR�� ����
	MODIFY_CURRENT_STR,          // ���� STR�� ����
	MODIFY_MAX_STR,              // �ƽ� STR�� ����
	MODIFY_STR_EXP_REMAIN,              // STR ����ġ�� ����

	MODIFY_BASIC_DEX,            // �⺻ DEX�� ����
	MODIFY_CURRENT_DEX,          // ���� DEX�� ����
	MODIFY_MAX_DEX,              // �ƽ� DEX�� ����
	MODIFY_DEX_EXP_REMAIN,              // DEX ����ġ�� ����

	MODIFY_BASIC_INT,            // �⺻ INT�� ����
	MODIFY_CURRENT_INT,          // ���� INT�� ����
	MODIFY_MAX_INT,              // �ƽ� INT�� ����
	MODIFY_INT_EXP_REMAIN,              // INT ����ġ�� ����

	MODIFY_CURRENT_HP,           // ���� HP�� ����
	MODIFY_MAX_HP,               // �ƽ� HP�� ����

	MODIFY_CURRENT_MP,           // ���� MP�� ����
	MODIFY_MAX_MP,               // �ƽ� MP�� ����

	MODIFY_MIN_DAMAGE,           // �ּ� �������� ����
	MODIFY_MAX_DAMAGE,           // �ƽ� �������� ����

	MODIFY_DEFENSE,              // ���潺�� ����
	MODIFY_PROTECTION,           // �����ؼ��� ����
	MODIFY_TOHIT,                // ���߷��� ����

	MODIFY_VISION,               // �þ߸� ����
	MODIFY_FAME,                 // ���� ����
	MODIFY_GOLD,                 // �������� ����

	MODIFY_SWORD_DOMAIN_LEVEL,   // �� �迭 ������ ����
	MODIFY_SWORD_DOMAIN_EXP_REMAIN,     // �� �迭 ������ ����
	MODIFY_SWORD_DOMAIN_GOAL_EXP,// �� �迭 ������ ����
	MODIFY_BLADE_DOMAIN_LEVEL,   // �� �迭 ������ ����
	MODIFY_BLADE_DOMAIN_EXP_REMAIN,     // �� �迭 ������ ����
	MODIFY_BLADE_DOMAIN_GOAL_EXP,// �� �迭 ������ ����
	MODIFY_HEAL_DOMAIN_LEVEL,    // �� �迭 ������ ����
	MODIFY_HEAL_DOMAIN_EXP_REMAIN,      // �� �迭 ������ ����
	MODIFY_HEAL_DOMAIN_GOAL_EXP, // �� �迭 ������ ����
	MODIFY_ENCHANT_DOMAIN_LEVEL, // ��æƮ �迭 ������ ����
	MODIFY_ENCHANT_DOMAIN_EXP_REMAIN,   // ��æƮ �迭 ������ ����
	MODIFY_ENCHANT_DOMAIN_GOAL_EXP, // ��æƮ �迭 ������ ����
	MODIFY_GUN_DOMAIN_LEVEL,     // �� �迭 ������ ����
	MODIFY_GUN_DOMAIN_EXP_REMAIN,       // �� �迭 ������ ����
	MODIFY_GUN_DOMAIN_GOAL_EXP,  // �� �迭 ������ ����
	MODIFY_ETC_DOMAIN_LEVEL,     // ��Ÿ �迭 ������ ����
	MODIFY_ETC_DOMAIN_EXP_REMAIN,       // ��Ÿ �迭 ������ ����
	MODIFY_ETC_DOMAIN_GOAL_EXP,  // ��Ÿ �迭 ������ ����

	MODIFY_SKILL_LEVEL,          // Ư�� ��ų ������ ����
	MODIFY_LEVEL,                // �����̾� ������ ����
	MODIFY_EFFECT_STAT,          // ����Ʈ ���¸� ����
	MODIFY_DURATION,             // ����Ʈ ���� �ð��� ����
	MODIFY_BULLET,               // ��� �ִ� �Ѿ��� �Ѿ� ���� ����
	MODIFY_BONUS_POINT,          // �����̾��� ���ʽ� ����Ʈ�� ����
	MODIFY_DURABILITY,           // ��� �ִ� ������ �� �ϳ��� �������� ����
	MODIFY_NOTORIETY,            // �Ǹ�ġ�� ����
	MODIFY_VAMP_EXP_REMAIN,             // �����̾��� ����ġ�� ����

	MODIFY_SILVER_DAMAGE,        // �� �������� ����
	MODIFY_ATTACK_SPEED,         // ���� �ӵ��� ����
	MODIFY_ALIGNMENT,			// ����

	MODIFY_SILVER_DURABILITY,	// ������ ������..

	MODIFY_REGEN_RATE,           // ���� �ð��� �������� ���� �ϴܽ�-_-
	MODIFY_GUILDID,					// ��� ���̵� �ٲ�����

	MODIFY_RANK,				 // ��� �ܰ�
	MODIFY_RANK_EXP_REMAIN,			 // ��� ����ġ

	MODIFY_OUSTERS_EXP_REMAIN,          // �ƿ콺�ͽ��� ����ġ�� ����
	MODIFY_SKILL_BONUS_POINT,    // �ƿ콺�ͽ��� ��ų ���ʽ� ����Ʈ�� ����
	
	MODIFY_ELEMENTAL_FIRE,
	MODIFY_ELEMENTAL_WATER,
	MODIFY_ELEMENTAL_EARTH,
	MODIFY_ELEMENTAL_WIND,
	
	MODIFY_SKILL_EXP,			// ��ų ����ġ ����
	
    MODIFY_PET_HP,
    MODIFY_PET_EXP_REMAIN,               // �� ����
	
	MODIFY_LAST_TARGET,

	// 2004, 10, 19, sobeit add start
	MODIFY_UNIONID,
	MODIFY_UNIONGRADE,
	// 2004, 10, 19, sobeit add end
	
    MODIFY_ADVANCEMENT_CLASS_LEVEL, // ���� ����
    MODIFY_ADVANCEMENT_CLASS_GOAL_EXP,  // ���� ����ġ

	MODIFY_MAX
};


#define	MAX_MODIFY		MODIFY_MAX
#define	MODIFY_NULL		0xFFFFFFFF

#endif