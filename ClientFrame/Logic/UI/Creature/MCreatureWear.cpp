//----------------------------------------------------------------------
// MCreatureWear.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MCreatureWear.h"
#include "MItem.h"
#include "AddonDef.h"
#include "SkillDef.h"
#include "DebugInfo.h"
#include "CIndexSprite.h"
#include "ClientConfig.h"
#include "MEffectGeneratorTable.h"
#include "MEffectSpriteTypeTable.h"
#include "EffectSpriteTypeDef.h"
#include "MItemOptionTable.h"
#include "PacketFunction.h"
#include "MinTR.H"
#include "MTopView.h"

int defaultSkinColor		= 410;					
int defaultCoatColor		= 377;//368;	
int defaultTrouserColor	= 377;//489;	


#define	ATTACHEFFECTCOLOR_NULL		0xFFFF


//----------------------------------------------------------------------
// static member
//----------------------------------------------------------------------
// Creature�� ���� ���⿡ ����...
// ���� ������ִ� ������ �ٸ� �� �ִ�.
// �� ���⺰�� �� ������ִ� ������ ���ϴ� �κ��̴�.
int			MCreatureWear::s_AddonOrder[DIRECTION_MAX][ADDON_MAX] = 
{
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND },	// LEFT
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND },	// LEFTDOWN
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// DOWN	
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// RIGHTDOWN	
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// RIGHT
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// RIGHTUP
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND },	// UP
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND }	// LEFTUP
};

int	MCreatureWear::s_ACAddonOrder[ DIRECTION_MAX ][ AC_ADDON_MAX ] =
{
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
};


//----------------------------------------------------------------------
//
//  constructor/destructor
//
//----------------------------------------------------------------------
MCreatureWear::MCreatureWear()
{
	for (int i=0; i<ADDON_MAX; i++)
	{
		ClearAddonInfo( i );
	}

	m_HairFrameID = ADDONID_HAIR1_MALE;
	m_HairColorSet = 0;

	m_ShoulderAddon.bAddon = FALSE;
	m_ShoulderAddon.FrameID	= FRAMEID_NULL;		// ����

	m_ShoulderAddon.ItemClass	= ITEM_CLASS_NULL;	// item class
	m_ShoulderAddon.ItemType	= ITEMTYPE_NULL;			// item type
	m_ShoulderAddon.ColorSet1	= 0;						// colorset1
	m_ShoulderAddon.ColorSet2	= 0;						// colorset2
	m_ShoulderAddon.bEffectColor = FALSE;					// effect color�� �������� �����ΰ�?
	m_ShoulderAddon.EffectColorSet	= 0;				// effectcolorset
}

MCreatureWear::~MCreatureWear()
{
}

//----------------------------------------------------------------------
//
//  member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Clear AddonInfo
//----------------------------------------------------------------------
void			
MCreatureWear::ClearAddonInfo(int Addon)
{
	ADDON_INFO& addon = m_Addon[Addon];

	// �ʱ�ȭ
	addon.bAddon	= FALSE;			// �����߳�?	
	addon.FrameID	= FRAMEID_NULL;		// ����

	addon.ItemClass	= ITEM_CLASS_NULL;	// item class
	addon.ItemType	= ITEMTYPE_NULL;			// item type
	addon.ColorSet1	= 0;						// colorset1
	addon.ColorSet2	= 0;						// colorset2
	addon.bEffectColor = FALSE;					// effect color�� �������� �����ΰ�?
	addon.EffectColorSet	= 0;				// effectcolorset
}

//----------------------------------------------------------------------
// Set Same Wear
//----------------------------------------------------------------------
void				
MCreatureWear::SetSameWear(const MCreatureWear* pCreature)
{
	// ������ ����	
	for (int i=0; i<ADDON_MAX; i++)
	{
		m_Addon[i] = pCreature->m_Addon[i];
	}

	m_HairFrameID = pCreature->m_HairFrameID;
	m_HairColorSet = pCreature->m_HairColorSet;
}

//----------------------------------------------------------------------
// Set Addon ColorSet1
//----------------------------------------------------------------------
void			
MCreatureWear::SetAddonColorSet1(int Addon, WORD colorSet)	
{ 
	if (Addon >= ADDON_MAX)
	{
		return;
	}
	
	// 2004, 5, 4 sobeit add start - �ٸ� ĳ���� �ƿ콺���� ������ �����ϴ� �ڵ尡 ��� ������ �߰�
	if(Addon == ADDON_TROUSER)
		m_Addon[Addon].bAddon = true;
	// 2004, 5, 4 sobeit add end

	if (colorSet < MAX_COLORSET || colorSet == UNIQUE_ITEM_COLOR || colorSet == QUEST_ITEM_COLOR)
	{	
		m_Addon[Addon].ColorSet1 = colorSet; 		
	}
	else
	{
		DEBUG_ADD_FORMAT("[Error] Exceed Maximum ColorSet. addon=%d, set=%d", Addon, colorSet);		
	}
}

//----------------------------------------------------------------------
// Set Addon ColorSet2
//----------------------------------------------------------------------
void			
MCreatureWear::SetAddonColorSet2(int Addon, WORD colorSet)	
{ 
	if (Addon >= ADDON_MAX)
	{
		return;
	}

	// 2004, 5, 4 sobeit add start - �ٸ� ĳ���� �ƿ콺���� ������ �����ϴ� �ڵ尡 ��� ������ �߰�
	if(Addon == ADDON_TROUSER)
		m_Addon[Addon].bAddon = true;
	// 2004, 5, 4 sobeit add end
	
	if (colorSet < MAX_COLORSET || colorSet == UNIQUE_ITEM_COLOR || colorSet == QUEST_ITEM_COLOR)
	{	
		// ��ڴ� set1�̴�. T_T;;
		if (m_CreatureType==CREATURETYPE_SLAYER_OPERATOR
			&& Addon==ADDON_COAT)
		{
			m_ColorBody1 = m_ColorBody2 = colorSet;
		}
		
		m_Addon[Addon].ColorSet2 = colorSet; 		
	}
	else
	{
		DEBUG_ADD_FORMAT("[Error] Exceed Maximum ColorSet. addon=%d, set=%d", Addon, colorSet);
	}
}

//----------------------------------------------------------------------
// New Item From AddonInfo
//----------------------------------------------------------------------
// Addon��° ������ Item�� �����Ѵ�.
// �ܺο��� delete����� �Ѵ�.
//----------------------------------------------------------------------
MItem*
MCreatureWear::NewItemFromAddonInfo(int Addon)
{
	if (Addon >= ADDON_MAX)
	{
		return false;
	}

	ADDON_INFO& addon = m_Addon[Addon];

	//--------------------------------------------------
	// item�� ������ ���
	//--------------------------------------------------
	if (!addon.bAddon || addon.ItemClass==ITEM_CLASS_NULL)
	{
		return NULL;
	}
	
	//--------------------------------------------------
	// item�� ������ �˱����ؼ� �����ؼ� �����Ѵ�.
	//--------------------------------------------------
	MItem* pItem = MItem::NewItem( addon.ItemClass );
	pItem->SetItemType( addon.ItemType );

	return pItem;
}

//----------------------------------------------------------------------
// Remove Addon
//----------------------------------------------------------------------
// Addon�� ��ġ�� ������ ���ش�.
//----------------------------------------------------------------------
bool		
MCreatureWear::RemoveAddon(int Addon)
{ 
	DEBUG_ADD("MCreatureWear::RemoveAddon");
	
	if (Addon >= ADDON_MAX)
	{
		return false;
	}

	ADDON_INFO& addon = m_Addon[Addon];

	//--------------------------------------------------
	// �����Ѱ� ���� ��쿡�� �����. - -;
	//--------------------------------------------------
	if (addon.bAddon)
	{
		MItem* pItem = NewItemFromAddonInfo( Addon );
		
		if (pItem!=NULL)
		{
			//--------------------------------------------------
			// addon Item�� ���忡�� �����Ѵ�.
			//--------------------------------------------------
			bool bRemove = RemoveAddonItem( pItem );

			delete pItem;

			return bRemove;
		}

		//--------------------------------------------------
		// ���� ����..
		//--------------------------------------------------
		ClearAddonInfo( Addon );

		return true;
	}

	return false;
}

//---------------------------------------------------------------------------
// Set AddonItem
//---------------------------------------------------------------------------
// �Ӹ�ī���� �����Ѵ�.
//---------------------------------------------------------------------------
void			
MCreatureWear::SetAddonHair(TYPE_FRAMEID id, WORD cs1)
{
	ADDON_INFO& addon = m_Addon[ADDON_HAIR];

	// �ʱ�ȭ
	addon.bAddon	= TRUE;			// �����߳�?	
	addon.FrameID	= id;		// ����

	addon.ItemClass	= ITEM_CLASS_NULL;	// item class

	addon.ItemType	= ITEMTYPE_NULL;			// item type
	addon.ColorSet1	= cs1;						// colorset1
	addon.ColorSet2	= 0;						// colorset2
	addon.bEffectColor = FALSE;
	addon.EffectColorSet = 0;

	// ������ �д�.
	m_HairFrameID = id;
	m_HairColorSet = cs1;
}

//---------------------------------------------------------------------------
// Set AddonItem
//---------------------------------------------------------------------------
// �����ؼ� ����� �ٲ�� item(AddonItem)�� ���
// Creature�� �����ϰ� ���¸� �ٲ۴�.
//---------------------------------------------------------------------------
bool
MCreatureWear::SetAddonItem(MItem* pItem)
{
	DEBUG_ADD("MCreatureWear::SetAddonItem");
	
	if (pItem==NULL)
	{
		DEBUG_ADD("The Item is NULL");
		
		return false;
	}

	//-------------------------------------------------
	//
	// ������ ������ ��츸 ������ �ٲ� �� �ִ�.
	//
	//-------------------------------------------------
	// player�� �ƴ� ��쳪..
	// ������̸� Ÿ�� ����..
	// �׳� �����ϰ� �� ������. - -;
	if (GetClassType()!=MCreature::CLASS_PLAYER
		|| pItem->GetItemClass()==ITEM_CLASS_MOTORCYCLE)
	{
		SetAction( (m_MoveAction==ACTION_SLAYER_MOTOR_MOVE)? ACTION_SLAYER_MOTOR_STAND : ACTION_STAND );
	}

	if (m_Action==ACTION_STAND 
		|| IsSlayer() && m_Action==ACTION_SLAYER_MOTOR_STAND
		|| IsOusters() && m_Action==ACTION_OUSTERS_FAST_MOVE_STAND )
	{
		//-------------------------------------------------
		// �����ؼ� ����� �ٲ�� Item�� ��쿡�� ó���Ѵ�.
		//-------------------------------------------------
		if (pItem->IsAddonItem() && pItem->IsAffectStatus())
		{
			TYPE_FRAMEID	fid;
			ADDON			Addon = pItem->GetAddonSlot();

			//-------------------------------------------------
			// ������ �ٲ�� ��ġ�� �ִ� ���
			//-------------------------------------------------
			if (pItem->GetAddonSlot()==ADDON_NULL)
			{			
				DEBUG_ADD_FORMAT("[Error] Item doesn't have Addon Slot. id=%d, class=%d, type=%d", 
														pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());
				
			}
			else
			{	
				//-------------------------------------------------
				//
				//			�����ϴ� ��ġ�� ���� ó��..
				//
				//-------------------------------------------------
				switch (Addon)
				{
					//-------------------------------------------------
					// ������̸� ������ ���
					//-------------------------------------------------
					case ADDON_MOTOR :
						//------------------------------------------
						// �����̴� ��� �ٲ�
						//------------------------------------------					
						SetMoveDevice( MCreature::MOVE_DEVICE_RIDE );
					break;

					//-------------------------------------------------
					// �����ҷ��°� �޼չ���?�� ���
					//-------------------------------------------------
					case ADDON_LEFTHAND :
					{
						// ���йۿ� ����. - -;
						// �ʻ� �ϵ��ڵ�.. - -;;;;

						//-------------------------------------------------
						// ������ �ִ� �����չ��Ⱑ ��չ����̸� 
						// ������Addon�� �����Ѵ�.
						//-------------------------------------------------
						MItem* pOldItem = NewItemFromAddonInfo( ADDON_RIGHTHAND );

						// ������ item�� �ִ� ��� �����Ѵ�.
						if (pOldItem!=NULL)
						{	
							if (pOldItem->IsGearSlotTwoHand())
							{
								RemoveAddon( ADDON_RIGHTHAND );
							}

							delete pOldItem;
						}
					}
					break;

					//-------------------------------------------------
					// �����ҷ��°� �����չ���?�� ���
					//-------------------------------------------------
					case ADDON_RIGHTHAND :
					{
						// ��չ����̸� �޼��� ���ش�.
						if (pItem->IsGearSlotTwoHand())
						{
							RemoveAddon( ADDON_LEFTHAND );
						}				
					}	
					break;

					//-------------------------------------------------
					// ����
					//-------------------------------------------------
					// ������ ����
					// ª�� �Ӹ�ī���̶�� ���ش�.
					// ª�� �Ӹ� : ��1, ��123
					//-------------------------------------------------
					case ADDON_HELM :
						if (m_HairFrameID==ADDONID_HAIR1_FEMALE
							|| m_HairFrameID==ADDONID_HAIR1_MALE
							|| m_HairFrameID==ADDONID_HAIR2_MALE
							|| m_HairFrameID==ADDONID_HAIR3_MALE)
						{
							RemoveAddon( ADDON_HAIR );
						}
					break;

					//-------------------------------------------------
					// ����� ���.. �� �ٲٸ� �� ���� �ٲ��.
					//-------------------------------------------------
					case ADDON_COAT :
						if (m_CreatureType==CREATURETYPE_SLAYER_OPERATOR
							|| m_CreatureType==CREATURETYPE_VAMPIRE_OPERATOR
							|| m_CreatureType==CREATURETYPE_OUSTERS_OPERATOR)
						{
//							if(pItem->IsUniqueItem())
//								m_ColorBody1 = m_ColorBody2 = UNIQUE_ITEM_COLOR;
//							else
								m_ColorBody1 = m_ColorBody2 = pItem->GetItemOptionColorSet();
						}
					break;
				}
					
				//-------------------------------------------------
				//
				//			������ ���� FrameID
				//
				//-------------------------------------------------	
				if (IsMale())
				{
					fid = pItem->GetAddonMaleFrameID();
				}			
				else //if (pCreature->IsFemale())
				{
					fid = pItem->GetAddonFemaleFrameID();			
				}
			
				//-------------------------------------------------	
				// Slayer�̸鼭 fid�� ���� ���..
				//-------------------------------------------------					
				if (fid == FRAMEID_NULL && IsSlayer())
				{					
					DEBUG_ADD_FORMAT("[Error] Item doesn't have FrameID. id=%d, class=%d, type=%d", 
										pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());					
				}
				//-------------------------------------------------					
				// �������̰ų�.. Vampire�� ���
				//-------------------------------------------------					
				else
				{	
					//-------------------------------------------------
					// �����Ѵ�.
					//-------------------------------------------------
					ADDON_INFO& addon = m_Addon[Addon];

					// �ʱ�ȭ
					addon.bAddon	= TRUE;
					addon.FrameID	= fid;

					addon.ItemClass	= pItem->GetItemClass();
					addon.ItemType	= pItem->GetItemType();

					// ���� ���߰�
					if(pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_COAT)
					{
						unsigned short nSpecialActionInfo = GetSpecialActionInfo();

						if(m_CreatureType != CREATURETYPE_VAMPIRE_OPERATOR)
						{
							if (m_CreatureType != CREATURETYPE_WOLF && m_CreatureType != CREATURETYPE_BAT )
							{
								if( m_CreatureType == CREATURETYPE_WER_WOLF )
								{
									SetCreatureType( CREATURETYPE_WER_WOLF );
								}								
								else
								{
									if (IsMale())
									{
										SetCreatureType(pItem->GetAddonMaleFrameID());
									}			
									else //if (pCreature->IsFemale())
									{
										SetCreatureType(pItem->GetAddonFemaleFrameID());
										//SetCreatureType(812);
									}
								}
							}
							addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �Ǻ�
//							if(pItem->IsUniqueItem())
//								m_ColorBody2 = UNIQUE_ITEM_COLOR;
//							else
							m_ColorBody2	= pItem->GetItemOptionColorSet();			// option
							if( m_CreatureType == CREATURETYPE_WER_WOLF )
								m_ColorBody1 = m_ColorBody2;
								
						}
						else
						{
							m_ColorBody1 = m_ColorBody2 = pItem->GetItemOptionColorSet();
						}

						SetSpecialActionInfo(nSpecialActionInfo);
					}

					else 
					if (Addon==ADDON_COAT || Addon==ADDON_TROUSER)
					{
						{
							addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �Ǻ�
							//						if(pItem->IsUniqueItem())
							//							addon.ColorSet2	= UNIQUE_ITEM_COLOR;			// option
							//						else
							addon.ColorSet2	= pItem->GetItemOptionColorSet();			// option
							addon.bEffectColor = FALSE;
							addon.EffectColorSet = 0;
							
							// ������ ��츸 ���� �ٲ��.
							//if (Addon==ADDON_COAT)
							{
								//-------------------------------------------------
								// Vampire�� ����ȴ�.
								//-------------------------------------------------
								if (m_CreatureType==CREATURETYPE_VAMPIRE_OPERATOR)
								{
									//								if(pItem->IsUniqueItem())
									//									m_ColorBody1 = m_ColorBody2 = UNIQUE_ITEM_COLOR;
									//								else
									m_ColorBody1 = m_ColorBody2 = pItem->GetItemOptionColorSet();
								}
								else
								{
									//								if(pItem->IsUniqueItem())
									//									m_ColorBody2 = UNIQUE_ITEM_COLOR;
									//								else
									m_ColorBody2 = pItem->GetItemOptionColorSet();
								}
							}
						}
					}
					else
					{
//						if(pItem->IsUniqueItem())
//						{
//							addon.ColorSet1	= UNIQUE_ITEM_COLOR;	// option
//							addon.ColorSet2	= UNIQUE_ITEM_COLOR;//pItem->GetItemColorSet();			// null
//						}
//						else
						{
							addon.ColorSet1	= pItem->GetItemOptionColorSet();	// option
							addon.ColorSet2	= pItem->GetItemOptionColorSet();//pItem->GetItemColorSet();			// null
						}
						addon.bEffectColor = FALSE;
						addon.EffectColorSet = 0;
					}					
				}				
			}
		}			
		else
		{
			DEBUG_ADD_FORMAT("[Error] Item is Not Addon Item. id=%d, class=%d, type=%d", 
									pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());			
		}

		//-------------------------------------------------
		// ������ Item�� 
		// �⺻���ݿ� �������̶��...
		// �⺻����ActionInfo�� �ٲ��� �Ѵ�.
		//-------------------------------------------------
		if (pItem->IsBasicWeapon() && pItem->IsAffectStatus())
		{
			TYPE_ACTIONINFO ai = pItem->GetUseActionInfo();

			//-------------------------------------------------
			// ������ actionInfo�� ���� ���
			//-------------------------------------------------
			if (ai==ACTIONINFO_NULL)
			{
				// �⺻ �Ǽ� ���� �������� ��ȯ�Ѵ�.
				SetBasicActionInfo( SKILL_ATTACK_MELEE );
				
				DEBUG_ADD("[Empty ActionInfo]This Creature's basic attack is Melee");				
			}
			//-------------------------------------------------
			// ������ actionInfo�� �ִٸ�..
			//-------------------------------------------------
			else
			{
				// �⺻ ���� �������� �����Ѵ�.
				SetBasicActionInfo( ai );
				
				DEBUG_ADD_FORMAT("[Set BasicActionInfo] %d", ai);
			}
		}

		//-------------------------------------------------
		// �������� ���������..
		// ������ �Ǽ��̶�� ���� �ȴ�..
		// �ϵ� �ڵ�.. - -;;
		//-------------------------------------------------
		if (!m_Addon[ADDON_RIGHTHAND].bAddon)
		{
			DEBUG_ADD("[Empty RightHand]This Creature's basic attack is Melee");
			
			// �⺻ �Ǽ� ���� �������� ��ȯ�Ѵ�.
			SetBasicActionInfo( SKILL_ATTACK_MELEE );			
		}

		return true;	
		
	}

	//-------------------------------------------------
	//
	// ������ ���°� �ƴ� ���
	//
	//-------------------------------------------------
	DEBUG_ADD_FORMAT("[Error] Not STAND action. id=%d, action=%d", m_ID, m_Action);
	
	// ������ ������ ��, ������ �ٲٵ��� �Ѵ�..
	// �׷��� �Ǵµ�.. ������. - -;;

	return false;	
}

//---------------------------------------------------------------------------
// Remove AddonItem
//---------------------------------------------------------------------------
// AddonItem�� �������� �Ѵ�.
//---------------------------------------------------------------------------
bool
MCreatureWear::RemoveAddonItem( MItem* pItem )
{
	DEBUG_ADD("MCreatureWear::RemoveAddonItem");

	if (pItem==NULL)
	{
		DEBUG_ADD("The Item is NULL");
		
		return false;
	}

	//-------------------------------------------------
	//
	// ������ ������ ��츸 ������ �ٲ� �� �ִ�.
	//
	//-------------------------------------------------
	// player�� �ƴ� ��쳪..
	// ������̸� Ÿ�� ����..
	// �׳� �����ϰ� �� ������. - -;
	if (GetClassType()!=MCreature::CLASS_PLAYER
		|| pItem->GetItemClass()==ITEM_CLASS_MOTORCYCLE)
	{
		SetAction( (m_MoveAction==ACTION_SLAYER_MOTOR_MOVE)? ACTION_SLAYER_MOTOR_STAND : ACTION_STAND );
	}


	if (m_Action==ACTION_STAND
		|| IsSlayer() && m_Action==ACTION_SLAYER_MOTOR_STAND
		|| IsOusters() && m_Action==ACTION_OUSTERS_FAST_MOVE_STAND )
	{
		// ���� ���߰�
		if(pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_COAT)
		{
			if(m_CreatureType != CREATURETYPE_VAMPIRE_OPERATOR)
			{
				if (m_CreatureType != CREATURETYPE_WOLF && m_CreatureType != CREATURETYPE_BAT )
				{
					if( m_CreatureType == CREATURETYPE_WER_WOLF )
					{
						SetCreatureType( CREATURETYPE_WER_WOLF );
						m_ColorBody1 = defaultCoatColor;
					} else
					{
						if (IsMale())	// �ƾ� �ϵ� �ڵ� �ϸ� �ȴ�µ�-��-
						{
							SetCreatureType(2);
						}			
						else //if (pCreature->IsFemale())
						{
							SetCreatureType(3); //by viva
						}
					}
				}
				//						addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �Ǻ�

				m_ColorBody2	= defaultCoatColor;
			}
			else
			{
				m_ColorBody1	= m_ColorBody2	= defaultCoatColor;
			}
		}

		//-------------------------------------------------
		// �����ؼ� ����� �ٲ�� Item�ΰ�?
		//-------------------------------------------------
		// --> ���� ������ �˾Ƴ��� 
		//    �� ������ Addon�� ���־� �Ѵ�.
		//-------------------------------------------------
//		else
		if (pItem->IsAddonItem())
		{						
			enum ADDON add = pItem->GetAddonSlot();

			//-------------------------------------------------
			// ���� ������ Addon�� ���ش�.
			//-------------------------------------------------
			if (add == ADDON_NULL)
			{				
				DEBUG_ADD_FORMAT("[Error] Item doesn't have Addon Slot. id=%d, class=%d, type=%d", 
													pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());				
			}
			else
			{
				//--------------------------------------------------
				// ������ ���� �Ѵ�.
				//--------------------------------------------------
				ClearAddonInfo( add );

				//-------------------------------------------------
				//
				//			�����ϴ� ������ ����
				//
				//-------------------------------------------------	
				switch (add)
				{
					//-------------------------------------------------
					// ���� : �Ǹ��� ��쿡�� �⺻������..
					//-------------------------------------------------
					case ADDON_COAT :
					{
						//MItem* pItem = MItem::NewItem( ITEM_CLASS_TROUSER );
						//pItem->SetItemType( 0 );

						//SetAddonItem( pItem );	

						//delete pItem;
						//-------------------------------------------------
						// �����Ѵ�.
						//-------------------------------------------------						
						ADDON_INFO& addon = m_Addon[ADDON_COAT];

						// �ʱ�ȭ
						addon.bAddon	= TRUE;
						if(GetRace() == RACE_OUSTERS)
						{
							addon.FrameID = 1;
							addon.ColorSet1 = defaultCoatColor;
						}
						else
						{
							addon.FrameID	= IsMale()? ADDONID_COAT0_MALE : ADDONID_COAT0_FEMALE; 
							addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �⺻ �Ǻλ�
						}

						addon.ItemClass	= ITEM_CLASS_COAT;
						addon.ItemType	= 0;	//by viva
						addon.ColorSet2	= defaultCoatColor;
						addon.bEffectColor = FALSE;
						addon.EffectColorSet = 0;
						
						//-------------------------------------------------	
						// Vampire�� ����ȴ�.
						// ��ڵ� ����ǰ���..
						//-------------------------------------------------													
						if (m_CreatureType==CREATURETYPE_VAMPIRE_OPERATOR
							|| m_CreatureType==CREATURETYPE_SLAYER_OPERATOR
							|| m_CreatureType==CREATURETYPE_OUSTERS_OPERATOR
							)
						{
							m_ColorBody1 = m_ColorBody2 = defaultSkinColor;	
						}
						else
						{
							m_ColorBody2 = defaultCoatColor;
						}
						
					}
					break;

					//-------------------------------------------------
					// ���� : �Ǹ��� ��쿡�� �⺻������..
					//-------------------------------------------------
					case ADDON_TROUSER :
					{
						//MItem* pItem = MItem::NewItem( ITEM_CLASS_TROUSER );
						//pItem->SetItemType( 0 );

						//SetAddonItem( pItem );

						//delete pItem;
						//-------------------------------------------------
						// �����Ѵ�.
						//-------------------------------------------------
						ADDON_INFO& addon = m_Addon[ADDON_TROUSER];

						// �ʱ�ȭ
						addon.bAddon	= TRUE;
						addon.FrameID	= IsMale()? ADDONID_TROUSER0_MALE : ADDONID_TROUSER0_FEMALE;

						addon.ItemClass	= ITEM_CLASS_TROUSER;
						addon.ItemType	= 0;
						addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �⺻ �Ǻλ�
						addon.ColorSet2	= defaultTrouserColor;
						addon.bEffectColor = FALSE;
						addon.EffectColorSet = 0;
					}
					break;

					//-------------------------------------------------
					// �������� ����..�̹Ƿ�..
					//-------------------------------------------------				
					case ADDON_RIGHTHAND :
						// �⺻ �Ǽ� ���� �������� ��ȯ�Ѵ�.
						SetBasicActionInfo( SKILL_ATTACK_MELEE );

						// Ư�� ���⿡�� �ɸ��� Effect
						switch (pItem->GetItemClass())
						{
							//-------------------------------------------------	
							// ��
							//-------------------------------------------------	
							case ITEM_CLASS_BLADE :
								if (HasEffectStatus(EFFECTSTATUS_BERSERKER))
								{
									RemoveEffectStatus(EFFECTSTATUS_BERSERKER);
								}
							break;

							//-------------------------------------------------	
							// ���ڰ�
							//-------------------------------------------------	
							case ITEM_CLASS_CROSS :
							case ITEM_CLASS_MACE :
								if (HasEffectStatus(EFFECTSTATUS_HYPNOSIS))
								{
									RemoveEffectStatus(EFFECTSTATUS_HYPNOSIS);
								}
							break;
						}
					break;

					//-------------------------------------------------
					// ������� ���� ����
					//-------------------------------------------------
					case ADDON_MOTOR :
						//------------------------------------------
						// �����̴� ��� �ٲ�
						//------------------------------------------					
						SetMoveDevice( MCreature::MOVE_DEVICE_WALK );
					break;

					//-------------------------------------------------
					// ����
					//-------------------------------------------------
					// ���ڸ� ������ ���� 
					// ª�� �Ӹ�ī���� �ٽ� �ٿ��ش�.
					//-------------------------------------------------
					case ADDON_HELM :
						if (m_HairFrameID==ADDONID_HAIR1_FEMALE
							|| m_HairFrameID==ADDONID_HAIR1_MALE
							|| m_HairFrameID==ADDONID_HAIR2_MALE
							|| m_HairFrameID==ADDONID_HAIR3_MALE)
						{
							SetAddonHair( m_HairFrameID, m_HairColorSet );
						}
					break;
				}
				
			}

			return true;
		}

		// addon item�� �ƴ� ���
		return true;
	}

	//-------------------------------------------------
	//
	// ������ ���°� �ƴ� ���
	//
	//-------------------------------------------------
	DEBUG_ADD_FORMAT("[Error] Not STAND action. id=%d, action=%d", m_ID, m_Action);
	
	// ������ ������ ��, ������ �ٲٵ��� �Ѵ�..
	// �׷��� �Ǵµ�.. ������. - -;;


	return false;
}

//---------------------------------------------------------------------------
// Set Creature Type
//---------------------------------------------------------------------------
// �⺻ ������ ������.
//---------------------------------------------------------------------------
void
MCreatureWear::SetCreatureType(TYPE_CREATURETYPE type)
{
	//-------------------------------------------------
	// type����
	//-------------------------------------------------
	MCreature::SetCreatureType( type );

	//-------------------------------------------------
	// �� �����.
	//-------------------------------------------------
	for (int i=0; i<ADDON_MAX; i++)
	{
		ClearAddonInfo( i );
	}

	if(IsVampire())
	{
		//-------------------------------------------------
		// ���� : �Ǹ��� ��쿡�� �⺻������..
		//-------------------------------------------------
		ADDON_INFO& addon = m_Addon[ADDON_COAT];

		// �ʱ�ȭ
		addon.bAddon	= TRUE;
//		addon.FrameID	= IsMale()? ADDONID_COAT0_MALE : ADDONID_COAT0_FEMALE;
		
		addon.ItemClass	= ITEM_CLASS_VAMPIRE_COAT;
		addon.ItemType	= 0;
		addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �⺻ �Ǻλ�
		addon.ColorSet2	= defaultCoatColor;	
		addon.bEffectColor = FALSE;
		addon.EffectColorSet = 0;
	}
	else
	if(IsOusters())
	{
		//-------------------------------------------------
		// ���� : �Ǹ��� ��쿡�� �⺻������..
		//-------------------------------------------------
		ADDON_INFO& addon = m_Addon[ADDON_COAT];
		
		// �ʱ�ȭ
		addon.bAddon	= TRUE;
		addon.FrameID	= 1;
		//		addon.FrameID	= IsMale()? ADDONID_COAT0_MALE : ADDONID_COAT0_FEMALE;
		
		addon.ItemClass	= ITEM_CLASS_OUSTERS_COAT;
		addon.ItemType	= 0;
		addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �⺻ �Ǻλ�
		addon.ColorSet2	= defaultCoatColor;	
		addon.bEffectColor = FALSE;
		addon.EffectColorSet = 0;
	}
	else
	{
		//-------------------------------------------------
		// ���� : �Ǹ��� ��쿡�� �⺻������..
		//-------------------------------------------------
		ADDON_INFO& addon = m_Addon[ADDON_COAT];

		// �ʱ�ȭ
		addon.bAddon	= TRUE;
		addon.FrameID	= IsMale()? ADDONID_COAT0_MALE : ADDONID_COAT0_FEMALE;
		
		addon.ItemClass	= ITEM_CLASS_COAT;
		addon.ItemType	= 0;
		addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �⺻ �Ǻλ�
		addon.ColorSet2	= defaultCoatColor;	
		addon.bEffectColor = FALSE;
		addon.EffectColorSet = 0;
		
		//-------------------------------------------------
		// ���� : �Ǹ��� ��쿡�� �⺻������..
		//-------------------------------------------------
		ADDON_INFO& addon2 = m_Addon[ADDON_TROUSER];
		
		// �ʱ�ȭ
		addon2.bAddon	= TRUE;
		addon2.FrameID	= IsMale()? ADDONID_TROUSER0_MALE : ADDONID_TROUSER0_FEMALE;
		
		addon2.ItemClass	= ITEM_CLASS_TROUSER;
		addon2.ItemType	= 0;
		addon2.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// �⺻ �Ǻλ�
		addon2.ColorSet2	= defaultTrouserColor;
		addon2.bEffectColor = FALSE;
		addon2.EffectColorSet = 0;
	}
}

//----------------------------------------------------------------------
// Remove EffectStatus
//----------------------------------------------------------------------
// Ư���� EffectSpriteType�� �����Ѵ�.
//----------------------------------------------------------------------
bool
MCreatureWear::RemoveEffectStatus(EFFECTSTATUS status)
{
	DEBUG_ADD_FORMAT("[RemoveEffectStatus] id=%d, status=%d", m_ID, (int)status);
	
	if (status>=g_pEffectStatusTable->GetSize())
	{
		DEBUG_ADD_FORMAT("[Error]EffectStatus exceed Max : %d", (int)status);
		
		return false;
	}

	if (!m_bEffectStatus[status])
	{
		return false;
	}

	m_bEffectStatus[status] = false;

	bool bUseEffectSprite = (*g_pEffectStatusTable)[status].bUseEffectSprite;
	TYPE_EFFECTSPRITETYPE type = (*g_pEffectStatusTable)[status].EffectSpriteType;
	//------------------------------------------------------------
	// effectStatus�� ����.
	//------------------------------------------------------------
	switch (status)
	{
		case EFFECTSTATUS_SUMMON_SYLPH_GREEN :
		case EFFECTSTATUS_SUMMON_SYLPH_ORANGE :
		case EFFECTSTATUS_SUMMON_SYLPH_RED :
		case EFFECTSTATUS_SUMMON_SYLPH_YELLOW :
		case EFFECTSTATUS_SUMMON_SYLPH_WHITE :
		case EFFECTSTATUS_SUMMON_SYLPH_BROWN :
		case EFFECTSTATUS_SUMMON_SYLPH_LILAC :
		case EFFECTSTATUS_SUMMON_SYLPH_BLACK :
		case EFFECTSTATUS_SUMMON_SYLPH:
			SetMoveDevice(MOVE_DEVICE_WALK);
			if(IsAdvancementClass() && status==EFFECTSTATUS_SUMMON_SYLPH)
			{
				type = EFFECTSPRITETYPE_OUSTERS_FASTMOVE_LOOP;
				ExecuteActionInfoFromMainNode(SKILL_CLIENT_ADVANCEMENT_SUMMON_SYLPH_END,GetX(), GetY(), 0,GetDirection(),	GetID(),	
					GetX(), GetY(), 0, 8, NULL, false);
			}
		break;
		case EFFECTSTATUS_BIKE_CRASH:
			SetMoveDevice(MOVE_DEVICE_WALK);
			break;
		//------------------------------------------------------------
		// ���� Ǯ�� ��
		//------------------------------------------------------------
		// add by Coffee 2007-3-21
		case EFFECTSTATUS_SATELLITE_BOMB_AIM :
		// end	
		case EFFECTSTATUS_GUN_SHOT_GUIDANCE_AIM :
			if (m_bAlive)
			{
				SetStop();
				StopGunShotGuidance();
	#ifdef OUTPUT_DEBUG					
			DEBUG_ADD_FORMAT("[GSG] Stop");
	#endif
			}
		break;

		//------------------------------------------------------------
		// ���� Ǯ�� ��
		//------------------------------------------------------------
		case EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS :
		case EFFECTSTATUS_EXPLOSION_WATER :
			if (m_bAlive)
			{
				SetStop();
				StopCauseCriticalWounds();
	#ifdef OUTPUT_DEBUG					
			DEBUG_ADD_FORMAT("[CCW] Stop");
	#endif
			}
		break;

		case EFFECTSTATUS_CURSE_PARALYSIS :
			if (m_bAlive)
			{
				SetStop();
				Remove_Curse_Paralsis_Effect();
			}
		break;

		//------------------------------------------------------------
		// EFFECTSTATUS_SUMMON_CASKET [�����]
		//------------------------------------------------------------
		case EFFECTSTATUS_CASKET :
			// �ٷ� invisible�� �����.
			RemoveCasket();
		break;

		//------------------------------------------------------------
		// invisible ����
		//------------------------------------------------------------
		case EFFECTSTATUS_INVISIBILITY :
		case EFFECTSTATUS_SNIPPING_MODE :
			// invisible�� �����Ѵ�.
			SetVisible();
		break;

		//------------------------------------------------------------
		// EFFECTSTATUS_COMA
		//------------------------------------------------------------
		case EFFECTSTATUS_COMA :
			SetAlive();
			if(IsVampire())
			{
				ExecuteActionInfoFromMainNode(
							BLOOD_RESURRECT,										// ��� ��� ��ȣ
						
							m_X, m_Y, 0,
							(int)m_Direction,														// ��� ����
							
							m_ID,												// ��ǥ�� ���� ����
							m_X, m_Y, 0,
							
							2*16, //5*16, 
							
							NULL,
							
							false,
							
							(int)m_sX, (int)m_sY);	
			}

		case EFFECTSTATUS_GHOST:
			if (!(*g_pCreatureTable)[m_CreatureType].bFlyingCreature)	// ������ ���
				SetGroundCreature();
			break;
		break;
		case EFFECTSTATUS_GLACIER:	
			MCreature::RemoveGlacierEffect();
			break;

		case EFFECTSTATUS_INSTALL_TURRET:
			SetAction( ACTION_STAND );
			SetInstallTurretCount(0);
			SetInstallTurretDirect(2);
			SetDirection( 2 );
			SetCurrentDirection( 2 );
			break;
	}

	//------------------------------------------------------------
	//
	//			EffectSprite�� ǥ���ϴ� ���
	//
	//------------------------------------------------------------
	if (bUseEffectSprite)
	{
		//TYPE_EFFECTSPRITETYPE type = (*g_pEffectStatusTable)[status].EffectSpriteType;
		TYPE_EFFECTSPRITETYPE type2 = EFFECTSPRITETYPE_NULL;

		if(type == EFFECTSPRITETYPE_FAST_MOVE_STOP)
			type2 = EFFECTSPRITETYPE_FAST_MOVE_FLY;

		_MinTrace("remove effectsprite\n");

		//-------------------------------------------------------
		// Creature�� �پ� �ִ� Effect�߿���
		// EffectSpriteType�� type�� ���� �����Ѵ�.
		//-------------------------------------------------------
		if (type < g_pEffectSpriteTypeTable->GetSize())
		{
			if (IsFemale()
				&& (*g_pEffectSpriteTypeTable)[type].FemaleEffectSpriteType!=EFFECTSPRITETYPE_NULL)
			{
				type = (*g_pEffectSpriteTypeTable)[type].FemaleEffectSpriteType;
			}
			

			if (m_bAttachEffect[type])
			{
				//-------------------------------------------------------
				// ���� ���� ���
				//-------------------------------------------------------			
				ATTACHEFFECT_LIST::iterator iEffect = m_listEffect.begin();

				bool re = false;

				while (iEffect != m_listEffect.end())
				{
					MAttachEffect* pEffect = *iEffect;
					
					//-------------------------------------------------------
					// ���� type�� ã�´�.
					//-------------------------------------------------------
					if (pEffect->IsEffectSprite() 
						&& (pEffect->GetEffectSpriteType() == type ||
						type2 != EFFECTSPRITETYPE_NULL && pEffect->GetEffectSpriteType() == type2 ) )
					{						
						// �޸� ����
						delete pEffect;
						pEffect = NULL;
						
						ATTACHEFFECT_LIST::iterator dEffect = iEffect;
						iEffect--;

						// list���� ����
						m_listEffect.erase( dEffect );

						m_bAttachEffect[type] = false;
						
						re = true;
					}					
					
					iEffect++;
				}

				if(re)
					return true;

				//-------------------------------------------------------
				// �ٴڿ� ���� ���
				//-------------------------------------------------------
				iEffect = m_listGroundEffect.begin();

				while (iEffect != m_listGroundEffect.end())
				{
					MAttachEffect* pEffect = *iEffect;
					
					//-------------------------------------------------------
					// ���� type�� ã�´�.
					//-------------------------------------------------------
					if (pEffect->IsEffectSprite() && 
						( pEffect->GetEffectSpriteType() == type || type2 != EFFECTSPRITETYPE_NULL && 
						type2 == pEffect->GetEffectSpriteType()) )
					{
						// �޸� ����
						delete pEffect;

						// list���� ����
						m_listGroundEffect.erase( iEffect );

						m_bAttachEffect[type] = false;
				
						return true;
					} 
					iEffect++;
				}
			}
		}
	}
	//------------------------------------------------------------
	//
	//			EffectColor�� ǥ���ϴ� ���
	//
	//------------------------------------------------------------
	else
	{
		WORD colorSet = (*g_pEffectStatusTable)[status].EffectColor;

		//-------------------------------------------------------
		// Creature�� �پ� �ִ� Effect�߿���
		// EffectColor�� color�� ���� �����Ѵ�.
		//-------------------------------------------------------
		ATTACHEFFECT_LIST::iterator iEffect = m_listEffect.begin();

		while (iEffect != m_listEffect.end())
		{
			MAttachEffect* pEffect = *iEffect;
			
			//-------------------------------------------------------
			// ���� type�� ã�´�.
			//-------------------------------------------------------
			if (pEffect->IsEffectColor() && pEffect->GetEffectColor() == colorSet)
			{
				ADDON	part = pEffect->GetEffectColorPart();

				//------------------------------------------------------------
				// Ư���� ������ ������ �ٲ�� ��쵵 �ִ�.
				//------------------------------------------------------------
				if (part < ADDON_MAX)
				{
					m_Addon[part].bEffectColor = FALSE;
				}
				//------------------------------------------------------------
				// ��� ������ �������...
				//------------------------------------------------------------
				else
				{
					for (int p=0; p<ADDON_MAX; p++)
					{
						m_Addon[p].bEffectColor = FALSE;
					}
				}

				// �޸� ����
				delete pEffect;

				// list���� ����
				m_listEffect.erase( iEffect );

				return true;
			}
			
			iEffect++;
		}		
	}
	
	return false;
}

//----------------------------------------------------------------------
// Update Effect
//----------------------------------------------------------------------
// Creature�� ���� ��� Effect�� Frame�� �ٲ��ְ�..
// �����°� ������ list�� memory���� �����Ѵ�.
//----------------------------------------------------------------------
void		
MCreatureWear::UpdateAttachEffect()
{
	ATTACHEFFECT_LIST::iterator iEffect = m_listEffect.begin();
	ATTACHEFFECT_LIST::iterator iEffectTemp;

	// ���� 0
	//m_MaxEffectLight = 0;

	//---------------------------------------------------------------------
	// ĳ���� ���� �ٲٴ� ��..
	//---------------------------------------------------------------------
	// NULL���̴�.. �ܺο��� üũ�ؾ���..
	m_AttachEffectColor = m_ChangeColorSet;	//ATTACHEFFECTCOLOR_NULL;
	int bShowColor = (HasEffectStatus(EFFECTSTATUS_CURSE_PARALYSIS) 
						|| g_CurrentFrame % g_pClientConfig->FRAME_DRAW_ORIGINAL_SPRITE);	// �� frame���� �ѹ����� ���� ������ �����ش�.

	int bShowColorPart = (g_CurrentFrame & 0x00000004);	// 4 frame�� �����ư��� �� ���
	int numColors = 0;
	BOOL bChangeColor = FALSE;

	BOOL	bAddonColorPart[ADDON_MAX] = { FALSE, };
	WORD	addonColor[ADDON_MAX] = { m_ChangeColorSet, };

	//---------------------------------------------------------------------
	// ��� Effect�� Update�Ѵ�.
	//---------------------------------------------------------------------
	while (iEffect != m_listEffect.end())
	{
		MAttachEffect*	pEffect = *iEffect;
		bool			bErase = false;
		
		int x		= pEffect->GetX();
		int y		= pEffect->GetY();
		int light = pEffect->GetLight();		

		//---------------------------------------------------------------------
		// Update
		//---------------------------------------------------------------------
		// message : find path
		//#ifdef	OUTPUT_DEBUG
			//sprintf(g_pDebugMessage->GetCurrent(), "Before UpdateEffect : Type=%d", pEffect->GetFrameID());	
			//g_pDebugMessage->Next();
		//#endif

		if( pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_FAST_MOVE_FLY ||
			pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_FAST_MOVE_STOP ||
			(
			pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_SUMMON_SYLPH_GREEN_FLY &&
			pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_SUMMON_SYLPH_BLACK_STOP
			)
			)
		{		
			BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FAST_MOVE_STOP].BltType;
			TYPE_EFFECTSPRITETYPE		EffectSpriteType = pEffect->GetEffectSpriteType();
			bool			bNewSummonSylphEffect = false;
			bool			bNewSummonSylphEffectStop = false;
			
			if( EffectSpriteType >= EFFECTSPRITETYPE_SUMMON_SYLPH_GREEN_FLY &&
				EffectSpriteType <= EFFECTSPRITETYPE_SUMMON_SYLPH_BLACK_STOP )
			{
				bNewSummonSylphEffect = true;

				if( (EffectSpriteType - EFFECTSPRITETYPE_SUMMON_SYLPH_GREEN_FLY) & 0x1 )
					bNewSummonSylphEffectStop = true;
			}
			
			if( GetAction() == ACTION_OUSTERS_FAST_MOVE_STAND && (
				EffectSpriteType != EFFECTSPRITETYPE_FAST_MOVE_STOP ||
				( bNewSummonSylphEffect && !bNewSummonSylphEffectStop )
				)
			  )
			{
				TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FAST_MOVE_STOP].FrameID;
				
				if( bNewSummonSylphEffect )
					frameID = (*g_pEffectSpriteTypeTable)[ EffectSpriteType + 1 ].FrameID;

				int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);			
			
				pEffect->SetEffectSprite( EFFECTSPRITETYPE_FAST_MOVE_STOP );
				if( bNewSummonSylphEffect )
					pEffect->SetEffectSprite( EffectSpriteType + 1 );
				pEffect->SetFrameID( frameID, maxFrame );
			}
			else
			if( GetAction() == ACTION_OUSTERS_FAST_MOVE_MOVE && 
				( pEffect->GetEffectSpriteType() != EFFECTSPRITETYPE_FAST_MOVE_FLY ||
				( bNewSummonSylphEffect && bNewSummonSylphEffectStop )
			  ) )
			{
				TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FAST_MOVE_FLY].FrameID;
				if( bNewSummonSylphEffect )
					frameID = (*g_pEffectSpriteTypeTable)[ EffectSpriteType - 1 ].FrameID;

				int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);			

				pEffect->SetEffectSprite( EFFECTSPRITETYPE_FAST_MOVE_FLY );

				if( bNewSummonSylphEffect )
					pEffect->SetEffectSprite( EffectSpriteType - 1 );
				pEffect->SetFrameID( frameID, maxFrame );
			}
		} 
		else if( pEffect->GetEffectSpriteType() >= EFFECTSPRITETYPE_LAR_SLASH_MALE_FAST && pEffect->GetEffectSpriteType() <= EFFECTSPRITETYPE_LAR_SLASH_FEMALE_SLOW )
		{
			if(!(  GetAction() == ACTION_SLAYER_SWORD_2 || GetAction() == ACTION_SLAYER_SWORD_2_SLOW || GetAction() == ACTION_SLAYER_SWORD_2_FAST ) 
				&& m_RepeatCount <= 0 )
			{
				pEffect->SetCount(0);
			}
		}
		else if(		
					(pEffect->GetEffectSpriteType() >= EFFECTSPRITETYPE_REGEN_TOWER_THROW_LIGHT_START &&
					pEffect->GetEffectSpriteType() <= EFFECTSPRITETYPE_REGEN_TOWER_THROW_LIGHT_END &&
					!HasEffectStatus( EFFECTSTATUS_TRYING ) 
					)
			)
		{
			bErase = true;			
		}

		if (bErase == false && pEffect->Update())
		{
			// -_- ���� ���� �ȹٲ۴�..
			if( pEffect->GetEffectSpriteType() != EFFECTSPRITETYPE_ABSORB_SOUL )
				pEffect->SetDirection( m_CurrentDirection );
			// �ְ� ��⸦ ���� Effect�� ��⸦ �����Ѵ�.
//			if (m_MaxEffectLight < pEffect->GetLight())
//			{
//				m_MaxEffectLight = pEffect->GetLight();
//			}

			// ��ġ ����
			pEffect->SetPosition(m_X, m_Y);

			//---------------------------------------------------------------------
			// ��ġ�� �ٲ���ų�
			// ���� ũ��(�þ�)�� �ٲ� ���
			//---------------------------------------------------------------------
			if (x!=pEffect->GetX() || y!=pEffect->GetY()
				|| light != pEffect->GetLight())
			{				
				// �þ� �ٲٱ�
//				g_pZone->UnSetLight(x, y, light);
//				g_pZone->SetLight(pEffect->GetX(), pEffect->GetY(), pEffect->GetLight());

				/*
				// UnSetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "UnSetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
					g_pDebugMessage->Next();
				#endif

				// SetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "SetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), pEffect->GetLight(), pEffect->GetX(), pEffect->GetY());	
					g_pDebugMessage->Next();
				#endif
				*/
			}

			//---------------------------------------------------------------------
			// ĳ���� ���� �ٲٴ� Effect�̸�
			// �ϳ��� �����ؾ� �Ѵ�.
			//---------------------------------------------------------------------
			if (pEffect->IsEffectColor())
			{
				ADDON	part = pEffect->GetEffectColorPart();

				//--------------------------------------------------------
				// �κ������� ���� �ٲ�� effect
				//--------------------------------------------------------
				if (part < ADDON_MAX)
				{
					if (bShowColorPart)
					{
						bAddonColorPart[part] = TRUE;
						addonColor[part] = pEffect->GetEffectColor();

						bChangeColor = TRUE;
					}
				}
				//--------------------------------------------------------
				// ��ü ���� �ٲ�� effect
				//--------------------------------------------------------
				else if (bShowColor)
				{
					numColors++;
					//if (m_AttachEffectColor == ATTACHEFFECTCOLOR_NULL || rand()%numColors==0)
					if (m_AttachEffectColor == m_ChangeColorSet || rand()%numColors==0)
					{
						m_AttachEffectColor = pEffect->GetEffectColor();

						bChangeColor = TRUE;
					}
				}				
			}

			//-----------------------------------------------
			//
			// �� Effect�� ������ ���� LinkCount�� ���ؼ�
			// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
			//
			// ����Frame�� EndLinkFrame�� �Ѿ ���
			//
			//-----------------------------------------------
			if (g_CurrentFrame >= pEffect->GetEndLinkFrame()
				&& pEffect->GetLinkSize() != 0)
			{
				// GenerateNext���� 
				// pEffect�� EffectTarget�� NULL�� ������ֱ� ������
				// ���⼭ ���� �ʿ� ����.
				g_pEffectGeneratorTable->GenerateNext( pEffect );

				// pEffect�� ������ �����ؾ� �ϹǷ� ����� �ȵȴ�.
			}

			// ����� �� ���
			iEffect++;
		}
		//---------------------------------------------------------------------
		// �ð��� �� �ż� ������ ���
		//---------------------------------------------------------------------
		else
		{
			bool bUseEffectSprite = pEffect->IsEffectSprite();

			// flag����
			if (bUseEffectSprite)
			{
				m_bAttachEffect[pEffect->GetEffectSpriteType()] = false;	// flag����
			}


			ADDON	part = pEffect->GetEffectColorPart();

			//------------------------------------------------------------
			// Ư���� ������ ������ �ٲ�� ��쵵 �ִ�.
			//------------------------------------------------------------
			if (part < ADDON_MAX)
			{
				m_Addon[part].bEffectColor = FALSE;
			}
			//------------------------------------------------------------
			// ������� ��� ������.
			//------------------------------------------------------------
			else
			{
				for (int p=0; p<ADDON_MAX; p++)
				{
					m_Addon[p].bEffectColor = FALSE;
				}
			}
		
			//---------------------------------------------------------------------
			//
			// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
			//
			//---------------------------------------------------------------------
			if (pEffect->GetLinkSize() != 0)
			{				
				g_pEffectGeneratorTable->GenerateNext( pEffect );
			}

			// ������ Effect�� �þ߸� ������� �ؾ��Ѵ�.
			//if (pEffect->GetBltType()==BLT_EFFECT)
			{
				//m_nAlphaEffect --;

				// ��� ������Effect�� ��������� �þ߸� ���Ž�Ų��.
				//if (m_nAlphaEffect==0)
				{
//					g_pZone->UnSetLight(x, y, light);

					// UnSet LightSight
					/*
					#ifdef	OUTPUT_DEBUG
						sprintf(g_pDebugMessage->GetCurrent(), "RemoveEffect : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
						g_pDebugMessage->Next();
					#endif
					*/
				}
			}

			DEBUG_ADD_FORMAT("[DeleteAttachEffect] id=%d, esType=%d", m_ID, pEffect->GetEffectSpriteType());
			
			// memory����, list����						
			delete pEffect;						// memory����
			
			DEBUG_ADD("[DeleteAttachEffect] OK");
			
			// list���� �����ϱ� ���ؼ�.. �ӽ÷� ����
			iEffectTemp = iEffect;

			iEffect++;
			m_listEffect.erase( iEffectTemp );	// list���� ����
		}		
	}

	//---------------------------------------------------------------------
	// ���� �ٴ� effect
	//---------------------------------------------------------------------
	// ��� Effect�� Update�Ѵ�.
	//---------------------------------------------------------------------
	iEffect = m_listGroundEffect.begin();
	
	while (iEffect != m_listGroundEffect.end())
	{
		MAttachEffect*	pEffect = *iEffect;
		
		int x		= pEffect->GetX();
		int y		= pEffect->GetY();
		int light = pEffect->GetLight();		

		//---------------------------------------------------------------------
		// Update
		//---------------------------------------------------------------------
		// message : find path
		//#ifdef	OUTPUT_DEBUG
			//sprintf(g_pDebugMessage->GetCurrent(), "Before UpdateEffect : Type=%d", pEffect->GetFrameID());	
			//g_pDebugMessage->Next();
		//#endif

		if (pEffect->Update())
		{
			// �ְ� ��⸦ ���� Effect�� ��⸦ �����Ѵ�.
//			if (m_MaxEffectLight < pEffect->GetLight())
//			{
//				m_MaxEffectLight = pEffect->GetLight();
//			}

			// ��ġ ����
			pEffect->SetPosition(m_X, m_Y);

			//---------------------------------------------------------------------
			// ��ġ�� �ٲ���ų�
			// ���� ũ��(�þ�)�� �ٲ� ���
			//---------------------------------------------------------------------
			if (x!=pEffect->GetX() || y!=pEffect->GetY()
				|| light != pEffect->GetLight())
			{				
				// �þ� �ٲٱ�
//				g_pZone->UnSetLight(x, y, light);
//				g_pZone->SetLight(pEffect->GetX(), pEffect->GetY(), pEffect->GetLight());

				/*
				// UnSetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "UnSetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
					g_pDebugMessage->Next();
				#endif

				// SetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "SetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), pEffect->GetLight(), pEffect->GetX(), pEffect->GetY());	
					g_pDebugMessage->Next();
				#endif
				*/
			}

			//-----------------------------------------------
			//
			// �� Effect�� ������ ���� LinkCount�� ���ؼ�
			// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
			//
			// ����Frame�� EndLinkFrame�� �Ѿ ���
			//
			//-----------------------------------------------
			if (g_CurrentFrame >= pEffect->GetEndLinkFrame()
				&& pEffect->GetLinkSize() != 0)
			{
				// GenerateNext���� 
				// pEffect�� EffectTarget�� NULL�� ������ֱ� ������
				// ���⼭ ���� �ʿ� ����.
				g_pEffectGeneratorTable->GenerateNext( pEffect );

				// pEffect�� ������ �����ؾ� �ϹǷ� ����� �ȵȴ�.
			}

			// ����� �� ���
			iEffect++;
		}
		//---------------------------------------------------------------------
		// �ð��� �� �ż� ������ ���
		//---------------------------------------------------------------------
		else
		{
			bool bUseEffectSprite = pEffect->IsEffectSprite();

			// flag����
			if (bUseEffectSprite)
			{
				m_bAttachEffect[pEffect->GetEffectSpriteType()] = false;	// flag����
			}

			//---------------------------------------------------------------------
			//
			// ���� ����Ǵ� Effect�� ������ �����ؾ� �Ѵ�.
			//
			//---------------------------------------------------------------------
			if (pEffect->GetLinkSize() != 0)
			{				
				g_pEffectGeneratorTable->GenerateNext( pEffect );
			}

			// ������ Effect�� �þ߸� ������� �ؾ��Ѵ�.
			//if (pEffect->GetBltType()==BLT_EFFECT)
			{
				//m_nAlphaEffect --;

				// ��� ������Effect�� ��������� �þ߸� ���Ž�Ų��.
				//if (m_nAlphaEffect==0)
				{
//					g_pZone->UnSetLight(x, y, light);

					// UnSet LightSight
					/*
					#ifdef	OUTPUT_DEBUG
						sprintf(g_pDebugMessage->GetCurrent(), "RemoveEffect : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
						g_pDebugMessage->Next();
					#endif
					*/
				}
			}

			DEBUG_ADD_FORMAT("[DeleteAttachEffect] id=%d, esType=%d", m_ID, pEffect->GetEffectSpriteType());
			

			// memory����, list����						
			delete pEffect;						// memory����
			
			
			DEBUG_ADD("[DeleteAttachEffect] OK");
			

			// list���� �����ϱ� ���ؼ�.. �ӽ÷� ����
			iEffectTemp = iEffect;

			iEffect++;
			m_listGroundEffect.erase( iEffectTemp );	// list���� ����
		}		
	}

	//---------------------------------------------------------------------
	// ���� �ٲ�� �� �����ִ� �����̸�..
	//---------------------------------------------------------------------
	if (bChangeColor)
	{
		//---------------------------------------------------------------------
		// ��ü ���� �ٲ�� Effect�� ���� ���
		//---------------------------------------------------------------------	
		if (m_AttachEffectColor == m_ChangeColorSet)//ATTACHEFFECTCOLOR_NULL)
		{
			for (int p=0; p<ADDON_MAX; p++)
			{
				if (bAddonColorPart[p])
				{
					// �� �κи� �ٲ�� �����..
					m_Addon[p].bEffectColor		= TRUE;
					m_Addon[p].EffectColorSet	= addonColor[p];
				}		
				else
				{
					// ���� �����..
					m_Addon[p].bEffectColor		= FALSE;
				}
			}
		}
		//---------------------------------------------------------------------
		// ��ü ���� �ٲ�� Effect�� �ִ� ���
		//---------------------------------------------------------------------
		else
		{
			for (int p=0; p<ADDON_MAX; p++)
			{
				m_Addon[p].bEffectColor		= TRUE;

				if (bAddonColorPart[p])
				{
					// �� �κи� �ٲ�� �����..			
					m_Addon[p].EffectColorSet	= addonColor[p];
				}		
				else
				{
					// ��ü �ٲ�� �����..				
					m_Addon[p].EffectColorSet	= m_AttachEffectColor;
				}
			}
		}
	}
	//---------------------------------------------------------------------
	// ���� �ٲ�°� �� �����ִ� ����...
	//---------------------------------------------------------------------
	else
	{
		for (int p=0; p<ADDON_MAX; p++)
		{
			m_Addon[p].bEffectColor		= FALSE;
		}
	}
}

const MCreatureWear::ADDON_INFO&	MCreatureWear::GetACAddonInfo(int Addon) const
{ 
	switch( Addon )
	{
	case AC_ADDON_BODY :
		return m_Addon[ ADDON_COAT ];
		
	case AC_ADDON_HELM :
		return m_Addon[ ADDON_HELM ];

	case AC_ADDON_LEFTHAND :
		return m_Addon[ ADDON_LEFTHAND ];

	case AC_ADDON_RIGHTHAND :
		return m_Addon[ ADDON_RIGHTHAND ];

	case AC_ADDON_MOTOR :
		return m_Addon[ ADDON_MOTOR ];
	}

	return m_ShoulderAddon;
}
