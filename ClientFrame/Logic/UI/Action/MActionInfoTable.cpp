//----------------------------------------------------------------------
// MActionInfoTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MActionInfoTable.h"
#include "EffectSpriteTypeDef.h"
#include "SkillDef.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MActionInfoTable*			g_pActionInfoTable = NULL;


//----------------------------------------------------------------------
//
//					ACTION_INFO_NODE class
//
//----------------------------------------------------------------------

//-------------------------------------------------------
// �ֵ� ����.. -_-;
//-------------------------------------------------------
void			
ACTION_INFO_NODE::SetChildMode()
{
	// ��...�ϵ��ڵ�-_-;
	if(EffectSpriteType >= EFFECTSPRITETYPE_BLOOD_DRAIN_1 &&
		EffectSpriteType <= EFFECTSPRITETYPE_BLOOD_DRAIN_3)
	{
		EffectSpriteType += EFFECTSPRITETYPE_GREEN_BLOOD_DRAIN_1 - EFFECTSPRITETYPE_BLOOD_DRAIN_1;
	}
	else if(EffectSpriteType >= EFFECTSPRITETYPE_BLOOD_GROUND_1_1 &&
		EffectSpriteType <= EFFECTSPRITETYPE_BLOOD_GROUND_2_4)
	{
		EffectSpriteType += EFFECTSPRITETYPE_GREEN_BLOOD_GROUND_1_1 - EFFECTSPRITETYPE_BLOOD_GROUND_1_1;
	}
	else if(EffectSpriteType >= EFFECTSPRITETYPE_BLOOD_SLAYER_1 &&
		EffectSpriteType <= EFFECTSPRITETYPE_BLOOD_SLAYER_3)
	{
		EffectSpriteType = EFFECTSPRITETYPE_GREEN_BLOOD_SLAYER_1+((EffectSpriteType-EFFECTSPRITETYPE_BLOOD_SLAYER_1)+2)%3;
	}
	else if(EffectSpriteType >= EFFECTSPRITETYPE_BLOOD_GUN_1_1 &&
		EffectSpriteType <= EFFECTSPRITETYPE_BLOOD_HORIZONTAL_3)
	{
		EffectSpriteType += EFFECTSPRITETYPE_GREEN_BLOOD_GUN_1_1 - EFFECTSPRITETYPE_BLOOD_GUN_1_1;
	}
	else if(EffectSpriteType >= EFFECTSPRITETYPE_BLOOD_VERTICAL_1 &&
		EffectSpriteType <= EFFECTSPRITETYPE_BLOOD_VERTICAL_4)
	{
		EffectSpriteType += EFFECTSPRITETYPE_GREEN_BLOOD_VERTICAL_1 - EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	}
	else if(EffectSpriteType >= EFFECTSPRITETYPE_TRANSFUSION_1 && EffectSpriteType <= EFFECTSPRITETYPE_TRANSFUSION_3)
	{
		EffectSpriteType += EFFECTSPRITETYPE_GREEN_TRANSFUSION_1 - EFFECTSPRITETYPE_TRANSFUSION_1;
	}
	else if(EffectSpriteType >= EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1 && EffectSpriteType <= EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4)
	{
		EffectSpriteType -= EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1 - EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_TEEN_1;
	}

//	if (EffectSpriteType >=	EFFECTSPRITETYPE_BLOOD_GUN_1_1
//		&&	EffectSpriteType <= EFFECTSPRITETYPE_BLOOD_DRAIN_3)
//	{
//		EffectSpriteType = EFFECTSPRITETYPE_NULL;
//	}
}

//----------------------------------------------------------------------
// Save
//----------------------------------------------------------------------
void			
ACTION_INFO_NODE::SaveToFile(class ofstream& file)
{			
	file.write((const char*)&EffectGeneratorID, SIZE_EFFECTGENERATORID);			
	file.write((const char*)&EffectSpriteType, SIZE_EFFECTSPRITETYPE);
	file.write((const char*)&Step, 2);
	file.write((const char*)&Count, 2);
	file.write((const char*)&LinkCount, 2);
	file.write((const char*)&SoundID, SIZE_SOUNDID);
	//file.write((const char*)&Light, 1);
	file.write((const char*)&bDelayNode, 1);	
	file.write((const char*)&bResultTime, 1);	
}

//----------------------------------------------------------------------
// Load
//----------------------------------------------------------------------
void			
ACTION_INFO_NODE::LoadFromFile(class ifstream& file)
{			
	file.read((char*)&EffectGeneratorID, SIZE_EFFECTGENERATORID);			
	file.read((char*)&EffectSpriteType, SIZE_EFFECTSPRITETYPE);
	file.read((char*)&Step, 2);
	file.read((char*)&Count, 2);
	file.read((char*)&LinkCount, 2);
	file.read((char*)&SoundID, SIZE_SOUNDID);
	//file.read((char*)&Light, 1);
	file.read((char*)&bDelayNode, 1);
	file.read((char*)&bResultTime, 1);
}


//----------------------------------------------------------------------
//
//					ActionInfo class
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
MActionInfo::MActionInfo()
{ 
	m_bAdvancementClassSkill = false;
	m_bNonAdvancementClassSkill = false;

	m_CastingActionInfo = ACTIONINFO_NULL;	// casting Action Info�� ���ش�.
	m_bCastingAction = false;				// casting ������ �ƴ϶�� ����..

	m_fUserType = FLAG_ACTIONINFO_USER_ALL;
	m_fWeaponType = 0;//FLAG_ACTIONINFO_WEAPON_ALL;
	m_fCurrentWeapon = 0;	// ���� ��� �ִ� ������ ������ �޴°�?
	m_MainNode = MAIN_NODE_NULL;
	m_bAttack = TRUE;			// �⺻������ ���ݱ���� ����

	m_bUseRepeatFrame = false;

	for (int i=0; i<3; i++)
	{
		m_CastingStartFrame[i] = 0;	// casting effect�� ���� frame
		m_CastingFrames[i]		= 0;	// casting effect�� ���� frame
		
		m_StartFrame[i] = 0xFFFF;	// max���� �ƴ�����. �� ������ ���.. ������.

		m_RepeatStartFrame[i] = m_RepeatEndFrame[i] = -1;
	}

	m_RepeatLimit = 0xFFFF;
	

	m_PacketType = ACTIONINFO_PACKET_NONE;

	m_ActionEffectSpriteTypeFemale = EFFECTSPRITETYPE_NULL;

	// 
	m_fOption = 0;

	m_EffectStatus = EFFECTSTATUS_NULL;

	// ��� id
	m_ActionResultID	= ACTIONRESULTNODE_NULL;
	m_ActionResultValue	= 0;

	m_PlusActionInfo = 0;

	m_bCastingEffectToSelf = true;

	m_fSelectCreature = FLAG_ACTIONINFO_SELECT_ALL;
	m_bUseGrade = false;
	m_bUseActionStep = false;
	
	for( i = 0 ; i< MAX_ACTION_STEP ;i ++ )
	{
		m_ActionStep[i] = 0;
	}
	m_bAttachSelf = false;
	m_Parent = ACTIONINFO_NULL;
	
	m_MasterySkillStep = 0;
	m_bIgnoreFailDelay = false;
}

//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
MActionInfo::~MActionInfo()
{
}


//-------------------------------------------------------
// �ֵ� ����.. -_-;
//-------------------------------------------------------
void			
MActionInfo::SetChildMode()
{
	// ��...�ϵ��ڵ�-_-;

	// male
	if(m_ActionEffectSpriteType >= EFFECTSPRITETYPE_BLOOD_GUN_1_1 &&
		m_ActionEffectSpriteType <= EFFECTSPRITETYPE_BLOOD_HORIZONTAL_3)
	{
		m_ActionEffectSpriteType += EFFECTSPRITETYPE_GREEN_BLOOD_GUN_1_1 - EFFECTSPRITETYPE_BLOOD_GUN_1_1;
	}
	else if(m_ActionEffectSpriteType >= EFFECTSPRITETYPE_BLOOD_VERTICAL_1 &&
		m_ActionEffectSpriteType <= EFFECTSPRITETYPE_BLOOD_VERTICAL_4)
	{
		m_ActionEffectSpriteType += EFFECTSPRITETYPE_GREEN_BLOOD_VERTICAL_1 - EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	}
//	else if(m_ActionEffectSpriteType >= EFFECTSPRITETYPE_BLOOD_DRAIN_1 &&
//		m_ActionEffectSpriteType <= EFFECTSPRITETYPE_BLOOD_DRAIN_3)
//	{
//		m_ActionEffectSpriteType += EFFECTSPRITETYPE_GREEN_BLOOD_DRAIN_1 - EFFECTSPRITETYPE_BLOOD_DRAIN_1;
//	}
	
	// female
	if(m_ActionEffectSpriteTypeFemale >= EFFECTSPRITETYPE_BLOOD_GUN_1_1 &&
		m_ActionEffectSpriteTypeFemale <= EFFECTSPRITETYPE_BLOOD_HORIZONTAL_3)
	{
		m_ActionEffectSpriteTypeFemale += EFFECTSPRITETYPE_GREEN_BLOOD_GUN_1_1 - EFFECTSPRITETYPE_BLOOD_GUN_1_1;
	}
	else if(m_ActionEffectSpriteTypeFemale >= EFFECTSPRITETYPE_BLOOD_VERTICAL_1 &&
		m_ActionEffectSpriteTypeFemale <= EFFECTSPRITETYPE_BLOOD_VERTICAL_4)
	{
		m_ActionEffectSpriteTypeFemale += EFFECTSPRITETYPE_GREEN_BLOOD_VERTICAL_1 - EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	}
//	else if(m_ActionEffectSpriteTypeFemale >= EFFECTSPRITETYPE_BLOOD_DRAIN_1 &&
//		m_ActionEffectSpriteTypeFemale <= EFFECTSPRITETYPE_BLOOD_DRAIN_3)
//	{
//		m_ActionEffectSpriteTypeFemale += EFFECTSPRITETYPE_GREEN_BLOOD_DRAIN_1 - EFFECTSPRITETYPE_BLOOD_DRAIN_1;
//	}

//	if (m_ActionEffectSpriteType >=	EFFECTSPRITETYPE_BLOOD_GUN_1_1
//		&&	m_ActionEffectSpriteType <= EFFECTSPRITETYPE_BLOOD_DRAIN_3)
//	{
//		m_ActionEffectSpriteType = EFFECTSPRITETYPE_NULL;
//	}
//
//	if (m_ActionEffectSpriteTypeFemale >=	EFFECTSPRITETYPE_BLOOD_GUN_1_1
//		&&	m_ActionEffectSpriteTypeFemale <= EFFECTSPRITETYPE_BLOOD_DRAIN_3)
//	{
//		m_ActionEffectSpriteTypeFemale = EFFECTSPRITETYPE_NULL;
//	}

	for (int i=0; i<m_Size; i++)
	{
		m_pTypeInfo[i].SetChildMode();
	}	
}

//----------------------------------------------------------------------
// Save
//----------------------------------------------------------------------
void			
MActionInfo::SaveToFile(class ofstream& file)
{
	// �ӽ÷� ���.. - -;
	// startframe�� ���� ��ŭ delay�� �پ���
	/*
	if (m_StartFrame==0xFFFF)
	{
		m_Delay = 0;
	}
	else 
	{
		int minusDelay = m_StartFrame * 1000 / 16;

		if (m_Delay < minusDelay)
		{
			m_Delay = 0;
		}
		else
		{
			m_Delay -= minusDelay;
		}
	}
	*/
	m_Name.SaveToFile( file );

	file.write((const char*)&m_Action, 1);
	file.write((const char*)&m_ActionEffectSpriteType, SIZE_EFFECTSPRITETYPE);
	file.write((const char*)&m_ActionEffectSpriteTypeFemale, SIZE_EFFECTSPRITETYPE);

	file.write((const char*)&m_bUseRepeatFrame, 1);

	for (int i=0; i<3; i++)
	{
		file.write((const char*)&m_StartFrame[i], 4);

		file.write((const char*)&m_CastingStartFrame[i], 4);
		file.write((const char*)&m_CastingFrames[i], 4);		

		file.write((const char*)&m_RepeatStartFrame[i], 4);	
		file.write((const char*)&m_RepeatEndFrame[i], 4);	

	}
	file.write((const char*)&m_RepeatLimit, 2);	

	file.write((const char*)&m_bCastingEffectToSelf, 1);
	file.write((const char*)&m_CastingActionInfo, 4);
	file.write((const char*)&m_bCastingAction, 1);

	file.write((const char*)&m_Range, 1);
	file.write((const char*)&m_fTarget, 1);	
	file.write((const char*)&m_fStart, 1);
	file.write((const char*)&m_fUserType, 1);
	file.write((const char*)&m_fWeaponType, 2);
	file.write((const char*)&m_fCurrentWeapon, 1);
	file.write((const char*)&m_fOption, 1);
	file.write((const char*)&m_PlusActionInfo, 4);

	BYTE pt = (BYTE)m_PacketType;
	file.write((const char*)&pt, 1);		

	file.write((const char*)&m_Delay, 2);
	file.write((const char*)&m_Value, 4);
	file.write((const char*)&m_SoundID, SIZE_SOUNDID);
	file.write((const char*)&m_MainNode, 4);
	
	// ��� 
	file.write((const char*)&m_ActionResultID, SIZE_ACTIONRESULTID);
	file.write((const char*)&m_ActionResultValue, 4);

	WORD es = m_EffectStatus;
	file.write((const char*)&es, 2);
	

	bool bAttack = (m_bAttack==TRUE);
	file.write((const char*)&bAttack, 1);
	file.write((const char*)&m_fSelectCreature, 1);	

	char flag = 0;	
	if( m_bUseGrade )
		flag |= 0x1;
	if( m_bUseActionStep )
		flag |= 0x2;
	if( m_bAttachSelf )
		flag |= 0x4;
	file.write((const char*)&flag, sizeof(char) );
	if( m_bUseActionStep )
	{
		for( i = 0;i<MAX_ACTION_STEP; i++)
		{
			file.write((const char*)&m_ActionStep[i],sizeof( TYPE_ACTIONINFO ) );
		}
	}

	file.write((const char*)&m_Parent, sizeof(TYPE_ACTIONINFO ) );
	file.write((const char*)&m_MasterySkillStep, 1 );
	file.write((const char*)&m_bIgnoreFailDelay, 1 );

	flag = 0;
/*	
	if( m_bAdvancementClassSkill ) flag |= 0x1;
	if( m_bNonAdvancementClassSkill ) flag |= 0x2;
	file.write( (const char*)&flag, sizeof( char ) );
*/	
	// �� �ܰ迡 ���� ����
	CTypeTable<ACTION_INFO_NODE>::SaveToFile(file);
}

//----------------------------------------------------------------------
// Load
//----------------------------------------------------------------------
void			
MActionInfo::LoadFromFile(class ifstream& file)
{
	m_Name.LoadFromFile( file );

	file.read((char*)&m_Action, 1);
	file.read((char*)&m_ActionEffectSpriteType, SIZE_EFFECTSPRITETYPE);
	file.read((char*)&m_ActionEffectSpriteTypeFemale, SIZE_EFFECTSPRITETYPE);

	file.read((char*)&m_bUseRepeatFrame, 1);

	for (int i=0; i<3; i++)
	{
		file.read((char*)&m_StartFrame[i], 4);

		file.read((char*)&m_CastingStartFrame[i], 4);	
		file.read((char*)&m_CastingFrames[i], 4);

		file.read((char*)&m_RepeatStartFrame[i], 4);	
		file.read((char*)&m_RepeatEndFrame[i], 4);	
	}
	file.read((char*)&m_RepeatLimit, 2);	

	file.read((char*)&m_bCastingEffectToSelf, 1);
	file.read((char*)&m_CastingActionInfo, 4);
	file.read((char*)&m_bCastingAction, 1);

	file.read((char*)&m_Range, 1);
	file.read((char*)&m_fTarget, 1);
	file.read((char*)&m_fStart, 1);
	file.read((char*)&m_fUserType, 1);
	file.read((char*)&m_fWeaponType, 2);
	file.read((char*)&m_fCurrentWeapon, 1);
	file.read((char*)&m_fOption, 1);
	file.read((char*)&m_PlusActionInfo, 4);

	BYTE pt;
	file.read((char*)&pt, 1);
	m_PacketType = (ACTIONINFO_PACKET)pt;


	file.read((char*)&m_Delay, 2);
	file.read((char*)&m_Value, 4);
	file.read((char*)&m_SoundID, SIZE_SOUNDID);
	file.read((char*)&m_MainNode, 4);
	
	// ��� 
	file.read((char*)&m_ActionResultID, SIZE_ACTIONRESULTID);
	file.read((char*)&m_ActionResultValue, 4);

	WORD es;
	file.read((char*)&es, 2);
	m_EffectStatus = (EFFECTSTATUS)es;
	bool bAttack;
	file.read((char*)&bAttack, 1);
	m_bAttack = bAttack;
	file.read((char*)&m_fSelectCreature, 1);

	char flag = 0;
	file.read((char*)&flag, sizeof(char) );

	m_bUseGrade = (flag & 0x1) != 0;
	m_bUseActionStep = (flag & 0x2) != 0;
	m_bAttachSelf = (flag & 0x4) != 0;		
	
	if( m_bUseActionStep )
	{
		for( i = 0;i<MAX_ACTION_STEP; i++)
		{
			file.read((char*)&m_ActionStep[i],sizeof( TYPE_ACTIONINFO ) );
		}
	}
	file.read((char*)&m_Parent, sizeof(TYPE_ACTIONINFO ) );
	file.read((char*)&m_MasterySkillStep, 1 );
	file.read((char*)&m_bIgnoreFailDelay, 1 );
/*
	file.read((char*)&flag, sizeof( char ) );

	m_bAdvancementClassSkill = (flag & 0x1 ) != 0;
	m_bNonAdvancementClassSkill = (flag & 0x2) != 0;
*/
	// �� �ܰ迡 ���� ����
	CTypeTable<ACTION_INFO_NODE>::LoadFromFile(file);
}

void		MActionInfo::SetActionStep(BYTE step,  TYPE_ACTIONINFO action)
{
	if(!IsUseActionStep() )
		return;

	if(step < 0 || step >= MAX_ACTION_STEP )
		return;

	m_ActionStep[step] = action;
}

TYPE_ACTIONINFO	MActionInfo::GetActionStep(BYTE step)
{
	if(!IsUseActionStep() || step < 0 || step >= MAX_ACTION_STEP )
		return ACTIONINFO_NULL;

	return m_ActionStep[step];
}

void		MActionInfo::SetParentActionInfo( TYPE_ACTIONINFO Parent )
{
	m_Parent = Parent;
}

TYPE_ACTIONINFO	MActionInfo::GetParentActionInfo()
{
	return m_Parent;
}

//----------------------------------------------------------------------
//
//							MActionInfoTable
//
//----------------------------------------------------------------------
MActionInfoTable::MActionInfoTable()
{
	m_nMinResultActionInfo = 0;
	m_nMaxResultActionInfo = 0;
}

MActionInfoTable::~MActionInfoTable()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// �� ���� ���..
//----------------------------------------------------------------------
void			
MActionInfoTable::SetChildMode()
{
	for (int i=0; i<m_Size; i++)
	{
		m_pTypeInfo[i].SetChildMode();
	}

	m_pTypeInfo[RESULT_VAMPIRE_DIE].SetStartFrameAll( 8 );	
	m_pTypeInfo[RESULT_VAMPIRE_DIE].SetCastingStartFrameAll( 8 );
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
MActionInfoTable::SaveToFile(class ofstream& file)
{
	file.write((const char*)&m_nMinResultActionInfo, 4);
	file.write((const char*)&m_nMaxResultActionInfo, 4);

	CTypeTable<MActionInfo>::SaveToFile( file );
}
		
//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void		
MActionInfoTable::LoadFromFile(class ifstream& file)
{
	file.read((char*)&m_nMinResultActionInfo, 4);
	file.read((char*)&m_nMaxResultActionInfo, 4);

	CTypeTable<MActionInfo>::LoadFromFile( file );
}
