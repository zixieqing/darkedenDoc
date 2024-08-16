//----------------------------------------------------------------------
// AddonDef.h
//----------------------------------------------------------------------
// Addon.cfpk�� ��� �ִ� ������ �ǹ��Ѵ�.
//----------------------------------------------------------------------

#ifndef	__ADDONDEF_H__
#define	__ADDONDEF_H__


//----------------------------------------------------------------------
// Addon����
//----------------------------------------------------------------------
/*
enum ADDONID
{
	ADDONID_HAIR1,		// �Ӹ�1
	ADDONID_HAIR2,		// �Ӹ�2
	ADDONID_HAIR3,		// �Ӹ�3
	ADDONID_HELM1,		// ����1
	ADDONID_HELM2,		// ����2	
	ADDONID_COAT1,		// ����1
	ADDONID_COAT2,		// ����2		
	ADDONID_TROUSER1,	// ����1
	ADDONID_TROUSER2,	// ����2	
	ADDONID_SWORD,		// ��	
	ADDONID_BLADE,		// ��	
	ADDONID_GUN_TR,		// ��1 - ���ݿ���(TR)
	ADDONID_GUN_SG,		// ��2 - ����(SG)	
	ADDONID_GUN_AR,		// ��3 - ����(AR)
	ADDONID_GUN_SMG,		// ��4 - �ڵ�����(SMG)	
	ADDONID_SHIELD,		// ����	
	ADDONID_CROSS,		// ���ڰ�
	ADDONID_MOTORCYCLE,	// �������	
	MAX_ADDONID
};
*/
	

#ifdef __EXPO_CLIENT__
	//----------------------------------------------------------------------
	// ���� Slayer
	//----------------------------------------------------------------------
	enum ADDONID_MALE
	{
		ADDONID_HELM1_MALE,			// ����1
		ADDONID_COAT1_MALE,			// ����1
		ADDONID_TROUSER1_MALE,		// ����1
		ADDONID_GUN_SMG_MALE,			// ��4 - �ڵ�����(SMG)	
		ADDONID_BLADE_MALE,		// ��
		ADDONID_SHIELD1_MALE,		// ����
		ADDONID_GUN_SG_MALE,			// ��2 - ����(SG)
		ADDONID_SWORD_MALE,		// ��	
		ADDONID_GUN_AR_MALE,			// ��3 - ����(AR)
		ADDONID_HAIR1_MALE,			// �Ӹ�1
		ADDONID_HAIR2_MALE,			// �Ӹ�2
		ADDONID_HAIR3_MALE,			// �Ӹ�3
		ADDONID_HELM2_MALE,			// ����2
		ADDONID_COAT2_MALE,			// ����2
		ADDONID_TROUSER2_MALE,		// ����2
		ADDONID_CROSS_MALE,			// ���ڰ�
		ADDONID_GUN_TR_MALE,			// ��1 - ���ݿ���(TR)		
		ADDONID_MOTORCYCLE_MALE,	// �������
		MAX_ADDONID_MALE
	};

	//----------------------------------------------------------------------
	// ���� Slayer
	//----------------------------------------------------------------------
	enum ADDONID_FEMALE
	{
		ADDONID_HELM1_FEMALE,			// ����1
		ADDONID_COAT1_FEMALE,			// ����1
		ADDONID_TROUSER1_FEMALE,		// ����1
		ADDONID_GUN_SMG_FEMALE,			// ��4 - �ڵ�����(SMG)	
		ADDONID_BLADE_FEMALE,		// ��
		ADDONID_SHIELD_FEMALE,		// ����
		ADDONID_GUN_SG_FEMALE,			// ��2 - ����(SG)
		ADDONID_SWORD_FEMALE,		// ��	
		ADDONID_GUN_AR_FEMALE,			// ��3 - ����(AR)
		ADDONID_HAIR1_FEMALE,			// �Ӹ�1
		ADDONID_HAIR2_FEMALE,			// �Ӹ�2
		ADDONID_HAIR3_FEMALE,			// �Ӹ�3
		ADDONID_HELM2_FEMALE,			// ����2
		ADDONID_COAT2_FEMALE,			// ����2
		ADDONID_TROUSER2_FEMALE,		// ����2
		ADDONID_CROSS_FEMALE,			// ���ڰ�
		ADDONID_GUN_TR_FEMALE,			// ��1 - ���ݿ���(TR)		
		ADDONID_MOTORCYCLE_FEMALE,	// �������
		MAX_ADDONID_FEMALE
	};

#else

	//----------------------------------------------------------------------
	// ���� Slayer
	//----------------------------------------------------------------------
	enum ADDONID_MALE
	{
		ADDONID_HELM1_MALE = 0,
		ADDONID_COAT1_MALE,
		ADDONID_TROUSER1_MALE,
		ADDONID_GUN_SMG_MALE,		// �ڵ�����(SMG)
		ADDONID_BLADE_MALE,			// ��
		ADDONID_SHIELD1_MALE,
		ADDONID_SHIELD2_MALE,		// �巡�����
		ADDONID_SHIELD3_MALE,		// ��������
		ADDONID_GUN_SG_MALE,
		ADDONID_SWORD_MALE,	// ��
		ADDONID_GUN_AR_MALE, 
		ADDONID_HAIR1_MALE,
		ADDONID_HAIR2_MALE,
		ADDONID_HAIR3_MALE,
		ADDONID_HELM2_MALE,
		ADDONID_COAT2_MALE,
		ADDONID_TROUSER2_MALE, 
		ADDONID_CROSS_MALE,
		ADDONID_GUN_SR_MALE,
		ADDONID_MOTORCYCLE_MALE,
		ADDONID_COAT0_MALE,
		ADDONID_TROUSER0_MALE,
		ADDONID_COAT3_MALE,
		ADDONID_TROUSER3_MALE,
		ADDONID_MACE_MALE,
	
		//----------------------------------------------------------------------
		// ���� Slayer
		//----------------------------------------------------------------------
		ADDONID_HELM1_FEMALE,
		ADDONID_COAT1_FEMALE,
		ADDONID_TROUSER1_FEMALE,
		ADDONID_GUN_SMG_FEMALE,		// �ڵ�����(SMG)
		ADDONID_BLADE_FEMALE,			// ��
		ADDONID_SHIELD1_FEMALE,
		ADDONID_SHIELD2_FEMALE,		// �巡�����
		ADDONID_SHIELD3_FEMALE,		// ��������
		ADDONID_GUN_SG_FEMALE,
		ADDONID_SWORD_FEMALE,	// ��
		ADDONID_GUN_AR_FEMALE, 
		ADDONID_HAIR1_FEMALE,
		ADDONID_HAIR2_FEMALE,
		ADDONID_HAIR3_FEMALE,
		ADDONID_HELM2_FEMALE,
		ADDONID_COAT2_FEMALE,
		ADDONID_TROUSER2_FEMALE, 
		ADDONID_CROSS_FEMALE,
		ADDONID_GUN_SR_FEMALE,
		ADDONID_MOTORCYCLE_FEMALE,
		ADDONID_COAT0_FEMALE,
		ADDONID_TROUSER0_FEMALE,
		ADDONID_COAT3_FEMALE,
		ADDONID_TROUSER3_FEMALE,
		ADDONID_MACE_FEMALE,

		MAX_ADDONID_SLAYER
	};


#endif


#endif