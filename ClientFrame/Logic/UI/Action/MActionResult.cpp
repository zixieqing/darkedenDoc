//----------------------------------------------------------------------
// MActionResult.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MActionResult.h"
#include "MTopView.h"
#include "ClientDef.h"
#include "MEffectGeneratorTable.h"
#include "UIFunction.h"
#include "MCreatureTable.h"
#include "VS_UI.h"
#include "MEventManager.h"
#include "MItemOptionTable.h"

#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

#define SAFE_DELETE(x)		{ if(x!=NULL) delete x; x=NULL; }

extern int g_MorphCreatureType;

// [�����]
void		SkillShadowDancing(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID);

//----------------------------------------------------------------------
// 
// ActionResultNode :: constructor/destructor
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//
// ActionResultNode - ActionInfo
//
//----------------------------------------------------------------------
MActionResultNodeActionInfo::MActionResultNodeActionInfo(TYPE_ACTIONINFO nActionInfo, TYPE_OBJECTID uid, TYPE_OBJECTID tid, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, DWORD delayFrame, BYTE temp)
{ 
	m_UserID		= uid;
	m_TargetID		= tid;
	m_nActionInfo	= nActionInfo;
	m_DelayFrame	= delayFrame;

	m_sX			= sX;
	m_sY			= sY;

	m_Temp			= temp;
}

//----------------------------------------------------------------------
// ActionResultNode - ActionInfo::Execute
//----------------------------------------------------------------------
void
MActionResultNodeActionInfo::Execute()
{
	DEBUG_ADD_FORMAT("ActionResultNodeAIExecute. u=%d, t=%d", m_UserID, m_TargetID);
	///*
	//POINT point;
	if (g_pZone==NULL)
	{
		return;
	}


	//--------------------------------------------------------
	// ��ǥ ��ġ Pixel��ǥ
	//--------------------------------------------------------
	MCreature*	pTargetCreature = g_pZone->GetCreature( m_TargetID );
	MCreature*	pUserCreature	= g_pZone->GetCreature( m_UserID );

	// ĳ���Ͱ� ������... ��~
	if (pTargetCreature==NULL)// || pUserCreature==NULL)
	{
		//MItem* pItem = g_pZone->GetItem( m_TargetID );	
		
		return;		
	}

	TYPE_ACTIONINFO nUsedActionInfo = m_nActionInfo;

/*
	point = MTopView::MapToPixel(pTargetCreature->GetX(), pTargetCreature->GetY());

	
	if ((*g_pActionInfoTable)[nUsedActionInfo].GetSize()!=0)
	{
		//--------------------------------------------------------
		//
		//					Effect ��ǥ ����
		//
		//--------------------------------------------------------
		MEffectTarget* pEffectTarget = new MEffectTarget( (*g_pActionInfoTable)[nUsedActionInfo].GetSize() );

		pEffectTarget->Set( point.x, point.y, pTargetCreature->GetZ(), pTargetCreature->GetID() );		

		//--------------------------------------------------------
		//
		//					���� ��ġ�� �����Ѵ�.
		//
		//--------------------------------------------------------
		int x,y,z, direction;

		//--------------------------------------------------------
		// User ��ġ���� �����ϴ� ���
		//--------------------------------------------------------
		if ((*g_pActionInfoTable)[nUsedActionInfo].IsStartUser())
		{
			point = MTopView::MapToPixel(pUserCreature->GetX(), pUserCreature->GetY());

			x			= point.x;
			y			= point.y;
			z			= pUserCreature->GetZ();//+60;
		}
		//--------------------------------------------------------
		// Target ��ġ���� �����ϴ� ���
		//--------------------------------------------------------
		else if ((*g_pActionInfoTable)[nUsedActionInfo].IsStartTarget())
		{
			x			= point.x;
			y			= point.y;
			z			= pUserCreature->GetZ();//+60;			
		}

		//--------------------------------------------------------
		// ���߿��� �����ϴ� ���
		//--------------------------------------------------------
		if ((*g_pActionInfoTable)[nUsedActionInfo].IsStartSky())
		{
			z	= pUserCreature->GetZ() + (*g_pActionInfoTable)[nUsedActionInfo].GetValue();

			direction	= DIRECTION_DOWN;
		}
		//--------------------------------------------------------
		// ���󿡼� �����ϴ� ���
		//--------------------------------------------------------
		else
		{
			direction	= pUserCreature->GetDirection();
		}

		//--------------------------------------------------------
		//
		//                   Effect����		
		//
		//--------------------------------------------------------
		g_EffectGeneratorTable.Generate(
				x,y,z,				// ���� ��ġ
				direction, 			// ����
				1,					// power
				nUsedActionInfo,	//	ActionInfoTable����,
				pEffectTarget		// ��ǥ ����
		);
	}
	*/
	//--------------------------------------------------------
	// ����� �Ǵ� ĳ���ʹ� Ư���� Action�� ���ϰ� �ȴ�.
	//--------------------------------------------------------
	//pTargetCreature->SetStop();
	//pTargetCreature->SetAction( (*g_pActionInfoTable)[nUsedActionInfo].GetAction() );

	int resultActionInfo;
	resultActionInfo = nUsedActionInfo + (*g_pActionInfoTable).GetMinResultActionInfo();	// ���

	switch( nUsedActionInfo )
	{
	case SKILL_SHADOW_DANCING :
		resultActionInfo = SKILL_SINGLE_BLOW + (*g_pActionInfoTable).GetMinResultActionInfo();
		break;
	// add by Coffee 2007-4-15
//	case SKILL_ILLUSION_INVERSION:
		//resultActionInfo = RESULT_TEMP_SKILL_ILLUSION_INVERSION;
		//break;
	// end by Coffee
	case SKILL_ILLENDUE :

		resultActionInfo = SKILL_LIGHT_BALL + (*g_pActionInfoTable).GetMinResultActionInfo();
		break;

	case SKILL_BLAZE_WALK :
		resultActionInfo = SKILL_BLAZE_WALK_ATTACK + (*g_pActionInfoTable).GetMinResultActionInfo();
		break;
	}
	
	if( resultActionInfo >= g_pActionInfoTable->GetSize() )
	{
		DEBUG_ADD_FORMAT("[Execute-ResultActionInfo] exceed resultAction %d/%d",nUsedActionInfo,
			resultActionInfo);
		return;
	}
	
	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD_FORMAT("[Execute-ResultActionInfo] ID=%d, ai=%d", m_TargetID, resultActionInfo);
		}
	#endif

	// [�����]

	
	pTargetCreature->SetEffectDelayFrame(resultActionInfo, m_DelayFrame );

 	if( pUserCreature != NULL)
 	{
		if(nUsedActionInfo == MAGIC_BLOODY_ZENITH)
			pUserCreature->SetBloodyZenith(8);
//		else if( nUsedActionInfo == SKILL_SET_AFIRE)
//			pUserCreature->SetBloodyZenith(20);
//		pUserCreature->SetActionDelay( 16 );
//		if( pUserCreature == g_pPlayer )
//			g_pPlayer->SetDelay( 2000 );
 	}
	
	if(nUsedActionInfo == SKILL_BLITZ_SLIDING_ATTACK )
	{
		if( pUserCreature != NULL )
		{
			pUserCreature->PacketSpecialActionResult( resultActionInfo, m_TargetID, m_sX, m_sY );
		}
	}
	else
	{
		if( (*g_pActionInfoTable)[nUsedActionInfo].IsUseActionGrade() && m_Temp != 0 )
			pTargetCreature->PacketSpecialActionResult( resultActionInfo, m_TargetID, m_sX, m_sY, m_Temp );
		else
			pTargetCreature->PacketSpecialActionResult( resultActionInfo, m_TargetID, m_sX, m_sY);
	}
	
	//--------------------------------------------------------
	// ����� ���ۿ� �´� sound�� ������ش�.
	//--------------------------------------------------------
	//g_Sound.Play( g_SoundTable[(*g_pActionInfoTable)[nUsedActionInfo].GetSoundID()].pDSBuffer );
	//PlaySound( (*g_pActionInfoTable)[nUsedActionInfo].GetSoundID(),
	//			false,
	//			pTargetCreature->GetX(),
	//			pTargetCreature->GetY());

	//--------------------------------------------------------
	// Effect���̴� ����̸� ..
	//--------------------------------------------------------
	/*
	EFFECTSTATUS	status		= (*g_pActionInfoTable)[resultActionInfo].GetEffectStatus();

	if (status!=EFFECTSTATUS_NULL)
	{
		// �ð��� ���� �ִ� ��쿡��...
		if (m_DelayFrame > 0)
		{
			pTargetCreature->AddEffectStatus( status, m_DelayFrame );
		}
	}
	*/
}


//----------------------------------------------------------------------
//
// ActionResultNode - ChangePosition
//
//----------------------------------------------------------------------
MActionResultNodeChangePosition::MActionResultNodeChangePosition(TYPE_OBJECTID uid, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY)
{ 
	m_UserID	= uid;
	m_X			= sX;
	m_Y			= sY;
}

//----------------------------------------------------------------------
// ActionResultNode - ChangePosition::Execute
//----------------------------------------------------------------------
void
MActionResultNodeChangePosition::Execute()
{
	if (g_pPlayer==NULL
		|| g_pZone==NULL)
	{
		return;
	}

	//-----------------------------------------------------------
	// Player�� ���
	//-----------------------------------------------------------
	if (m_UserID==g_pPlayer->GetID())
	{
		g_pPlayer->MovePosition( m_X, m_Y );
		g_pPlayer->SetServerPosition( m_X, m_Y );
	}
	//-----------------------------------------------------------
	// �ٸ� �ֵ��� ���
	//-----------------------------------------------------------
	else
	{
		MCreature* pCreature = g_pZone->GetCreature( m_UserID );

		// player�� ��츦 ���� üũ�ؾ� �ұ�??

		if (pCreature!=NULL)
		{
			//------------------------------------------------
			// ������ MoveBuffer�� �� ���Ž�Ų��.
			//------------------------------------------------
			pCreature->ReleaseMoveBuffer();

			// ��ǥ�� �ٲ۴�.
			pCreature->MovePosition( m_X, m_Y );
			pCreature->SetServerPosition( m_X, m_Y );
			//pCreature->SetStop();
		}
	}
}

//----------------------------------------------------------------------
//
// ActionResultNode - ChangeStatus
//
//----------------------------------------------------------------------
MActionResultNodeChangeStatus::MActionResultNodeChangeStatus(TYPE_OBJECTID tid, MStatus* pStatus)
{
	m_TargetID = tid;
	m_pStatus = pStatus;
}

MActionResultNodeChangeStatus::~MActionResultNodeChangeStatus()
{
	if (m_pStatus != NULL)
	{
		delete m_pStatus;
	}
		
}

//----------------------------------------------------------------------
// ActionResultNode - ChangeStatus::Execute
//----------------------------------------------------------------------
void
MActionResultNodeChangeStatus::Execute()
{
	if (g_pPlayer==NULL)
	{
		return;
	}

	//---------------------------------------------------------
	// Player�� MStatus�� ������ �ִ�.. - -;;
	// �׷��ٸ�.. m_TargetID�� �ʿ���µ�.. ��.. - -;; 
	//---------------------------------------------------------
	if (m_TargetID==g_pPlayer->GetID()
		&& m_pStatus!=NULL)
	{
		g_pPlayer->ApplyStatus( *m_pStatus );		
	}
}

//----------------------------------------------------------------------
// ActionResultNodeCreatureDie - CreatureDie::Execute
//----------------------------------------------------------------------
void
MActionResultNodeCreatureDie::Execute()
{
	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

	//---------------------------------------------------------
	// Player �� ���
	//---------------------------------------------------------
	if (m_TargetID == g_pPlayer->GetID())
	{
		g_pPlayer->SetDead();
	}
	//---------------------------------------------------------
	// �ٸ� Creature�� ���
	//---------------------------------------------------------
	else
	{
		MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );

		//---------------------------------------------------------
		// ĳ���Ͱ� ������... �ǹ̾�����..
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			return;
		}
		
		//---------------------------------------------------------
		// ���δ�. - -;
		//---------------------------------------------------------		
		pCreature->SetDead();	
	}
}

//----------------------------------------------------------------------
// ActionResultNodeCreatureBurrow - CreatureBurrow::Execute
//----------------------------------------------------------------------
void
MActionResultNodeCreatureBurrow::Execute()
{
	if (g_pPlayer==NULL
		|| g_pZone==NULL)
	{
		return;
	}

	//---------------------------------------------------------
	// Player �� ���
	//---------------------------------------------------------
	if (m_TargetID == g_pPlayer->GetID())
	{
		// Underground Creature�� �����.
		g_pPlayer->SetUndergroundCreature();

		// [����] burrow
//		__BEGIN_HELP_EVENT
//			ExecuteHelpEvent( HE_EFFECT_BURROW );
//		__END_HELP_EVENT
	}
	//---------------------------------------------------------
	// �ٸ� Creature�� ���
	//---------------------------------------------------------
	else
	{
		MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );

		//---------------------------------------------------------
		// ĳ���Ͱ� ������... �ǹ̾�����..
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			return;
		}
		
		//---------------------------------------------------------
		// �����. 
		//---------------------------------------------------------		
		pCreature->SetUndergroundCreature();
	}
}

//----------------------------------------------------------------------
// ActionResultNodeCreatureInvisible - CreatureInvisible::Execute
//----------------------------------------------------------------------
void
MActionResultNodeCreatureInvisible::Execute()
{
	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

	//---------------------------------------------------------
	// Player �� ���
	//---------------------------------------------------------
	if (m_TargetID == g_pPlayer->GetID())
	{
		// Underground Creature�� �����.
		g_pPlayer->SetInvisible();

		// [����] burrow
//		__BEGIN_HELP_EVENT
//			ExecuteHelpEvent( HE_EFFECT_BURROW );
//		__END_HELP_EVENT
	}
	//---------------------------------------------------------
	// �ٸ� Creature�� ���
	//---------------------------------------------------------
	else
	{
		MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );

		//---------------------------------------------------------
		// ĳ���Ͱ� ������... �ǹ̾�����..
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			return;
		}
		
		//---------------------------------------------------------
		// invisible
		//---------------------------------------------------------		
		pCreature->SetInvisible();
	}
}

//----------------------------------------------------------------------
// ActionResultNodeCreatureVisible - CreatureVisible::Execute
//----------------------------------------------------------------------
void
MActionResultNodeCreatureVisible::Execute()
{
	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

	//---------------------------------------------------------
	// Player �� ���
	//---------------------------------------------------------
	if (m_TargetID == g_pPlayer->GetID())
	{
		// Underground Creature�� �����.
		g_pPlayer->SetVisible();

		// [����] burrow
//		__BEGIN_HELP_EVENT
//			//ExecuteHelpEvent( HE_EFFECT_BURROW );
//		__END_HELP_EVENT
	}
	//---------------------------------------------------------
	// �ٸ� Creature�� ���
	//---------------------------------------------------------
	else
	{
		MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );

		//---------------------------------------------------------
		// ĳ���Ͱ� ������... �ǹ̾�����..
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			return;
		}
		
		//---------------------------------------------------------
		// invisible
		//---------------------------------------------------------		
		pCreature->SetVisible();
	}
}

//----------------------------------------------------------------------
// ActionResultNodeCreatureSnipping - CreatureSnipping::Execute
//----------------------------------------------------------------------
void
MActionResultNodeCreatureSnipping::Execute()
{
	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD_FORMAT("[Execute-CreatureSnipping] ID=%d", m_TargetID);
		}
	#endif

	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

	//---------------------------------------------------------
	// Player �� ���
	//---------------------------------------------------------
	if (m_TargetID == g_pPlayer->GetID())
	{		
		g_pPlayer->AddEffectStatus( EFFECTSTATUS_SNIPPING_MODE, 0xFFFF );
		g_pPlayer->SetInvisible();

		// [����] burrow
//		__BEGIN_HELP_EVENT
//			//ExecuteHelpEvent( HE_EFFECT_BURROW );
//		__END_HELP_EVENT
	}
	//---------------------------------------------------------
	// �ٸ� Creature�� ���
	//---------------------------------------------------------
	else
	{
		MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );

		//---------------------------------------------------------
		// ĳ���Ͱ� ������... �ǹ̾�����..
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			return;
		}
		
		//---------------------------------------------------------
		// invisible
		//---------------------------------------------------------		
		pCreature->AddEffectStatus( EFFECTSTATUS_SNIPPING_MODE, 0xFFFF );
		pCreature->SetInvisible();
	}
}

//----------------------------------------------------------------------
// ActionResultNodeCreatureTurning - CreatureTurning::Execute
//----------------------------------------------------------------------
void
MActionResultNodeCreatureTurning::Execute()
{
	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

	//---------------------------------------------------------
	// Player �� ���
	//---------------------------------------------------------
	if (m_TargetID == g_pPlayer->GetID())
	{
		// Underground Creature�� �����.
		g_pPlayer->SetTurning( m_TurnFrame );
	}
	//---------------------------------------------------------
	// �ٸ� Creature�� ���
	//---------------------------------------------------------
	else
	{
		MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );

		//---------------------------------------------------------
		// ĳ���Ͱ� ������... �ǹ̾�����..
		//---------------------------------------------------------
		if (pCreature==NULL)
		{
			return;
		}
		
		//---------------------------------------------------------
		// invisible
		//---------------------------------------------------------		
		pCreature->SetTurning( m_TurnFrame );
	}
}

//----------------------------------------------------------------------
// ActionResultNodeAddEffectStatus
//----------------------------------------------------------------------
void
MActionResultNodeAddEffectStatus::Execute()
{
	if (g_pZone==NULL)
	{
		return;
	}

	MCreature*	pTargetCreature = g_pZone->GetCreature( m_TargetID );

	// ĳ���Ͱ� ������... ��~
	if (pTargetCreature==NULL)// || pUserCreature==NULL)
		return;

	//--------------------------------------------------------
	// EffectStatus�� ���δ�.
	//--------------------------------------------------------
	pTargetCreature->AddEffectStatus(m_EffectStatus, m_DelayFrame);	
}

//----------------------------------------------------------------------
//
// ActionResultNode - ChangeCreatureType
//
//----------------------------------------------------------------------
MActionResultNodeChangeCreatureType::MActionResultNodeChangeCreatureType(TYPE_OBJECTID tid, int ctype)
{
	m_TargetID = tid;
	m_CreatureType = ctype;
}

MActionResultNodeChangeCreatureType::~MActionResultNodeChangeCreatureType()
{
}

//----------------------------------------------------------------------
// ActionResultNode - ChangeStatus::Execute
//----------------------------------------------------------------------
void
MActionResultNodeChangeCreatureType::Execute()
{
	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

	MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );
	
	// ĳ���Ͱ� ������... ��~
	if (pCreature==NULL)
		return;


	if (pCreature->IsUndergroundCreature())
	{
		// �׳� ����д�. - -;
	}
	else
	{
		// ������ �ٽ� ��������� �Ѵ�.
		bool bMale = pCreature->IsMale();
		WORD cs1 = pCreature->GetBodyColor1();
		WORD cs2 = pCreature->GetBodyColor2();

		pCreature->SetCreatureType( m_CreatureType );

		pCreature->SetMale( bMale );
		if( m_CreatureType == CREATURETYPE_WER_WOLF )
			pCreature->SetBodyColor1( cs2 );
		else
			pCreature->SetBodyColor1( cs1 );

		pCreature->SetBodyColor2( cs2 );

		// �̵������ ����..
		if ((*g_pCreatureTable)[m_CreatureType].IsFlyingCreature())
		{
			pCreature->SetFlyingCreature();
		}
		else
		{
			pCreature->SetGroundCreature();
		}
	}

	// player�� ���� skill���
	if (m_TargetID == g_pPlayer->GetID())
	{
		int selectSkill = ACTIONINFO_NULL;

		switch (m_CreatureType)
		{
			case CREATURETYPE_BAT :
				selectSkill = MAGIC_UN_TRANSFORM;
			break;
		
			case CREATURETYPE_WOLF :
				selectSkill = MAGIC_EAT_CORPSE;
			break;

			case CREATURETYPE_WER_WOLF :
				selectSkill = MAGIC_UN_TRANSFORM;
			break;
			
			// 2004, 9, 13, sobeit add start - �ѽ� 130 skill
			case CREATURETYPE_INSTALL_TURRET:
				selectSkill = MAGIC_UN_TRANSFORM;
			break;
			// 2004, 9, 13, sobeit add end
		}
		
		if (selectSkill!=ACTIONINFO_NULL)
		{
			gC_vs_ui.SelectSkill( selectSkill );
		}
		else
		{
			gC_vs_ui.UnselectSkill();
		}

		// ������ �����صа� ���ش�.
//		if (g_MorphCreatureType==m_CreatureType)
		{
			g_MorphCreatureType = 0;
		}
	}
}


//----------------------------------------------------------------------
// [�����]
//----------------------------------------------------------------------
MActionResultNodeSummonCasket::MActionResultNodeSummonCasket(TYPE_OBJECTID tid, int casketType)
{
	m_TargetID = tid;
	m_CasketType = casketType;
}

MActionResultNodeSummonCasket::~MActionResultNodeSummonCasket()
{
}

//----------------------------------------------------------------------
// ActionResultNode - SummonCasket::Execute
//----------------------------------------------------------------------
void
MActionResultNodeSummonCasket::Execute()
{
	if (g_pZone==NULL)
	{
		return;
	}

	MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );
	
	// ĳ���Ͱ� ������... ��~
	if (pCreature==NULL)
		return;

	//
	if (!pCreature->IsInCasket())
	{
		pCreature->SetStop();
		pCreature->MovePosition( pCreature->GetServerX(), pCreature->GetServerY() );
		pCreature->AddCasket( m_CasketType );
	}
}

//----------------------------------------------------------------------
// ActionResultNode - OpenCasket::Execute
//----------------------------------------------------------------------
void
MActionResultNodeOpenCasket::Execute()
{
	if (g_pZone==NULL)
	{
		return;
	}

	MCreature*	pCreature = g_pZone->GetCreature( m_TargetID );
	
	// ĳ���Ͱ� ������... ��~
	if (pCreature==NULL)
		return;

	if (pCreature->IsInCasket())
	{
		pCreature->RemoveCasket();
	}
}

//----------------------------------------------------------------------
// ActionResultNode - OpenCasket::Execute
//----------------------------------------------------------------------
void
MActionResultNodeRemoveItemInInventory::Execute()
{
	if (g_pInventory==NULL)
	{
		return;
	}

	MItem* pRemovedItem = g_pInventory->RemoveItem( m_TargetID );
	SAFE_DELETE( pRemovedItem );

	MItem*	pMouseItem = NULL;

	if(g_pPlayer->IsItemCheckBufferItemToItem())
	{

		pMouseItem = g_pPlayer->GetItemCheckBuffer();

		g_pPlayer->ClearItemCheckBuffer();

		if(pMouseItem != NULL)
			delete pMouseItem;
	}
	
}

//----------------------------------------------------------------------
// ActionResultNode - OpenCasket::Execute
//----------------------------------------------------------------------
void
MActionResultNodeChangeItemOptionInInventory::Execute()
{
	if (g_pInventory==NULL)
	{
		return;
	}

	MItem*	pInvenItem = g_pInventory->GetItem(m_TargetID);
	MItem*	pMouseItem = NULL;

	bool bSecondPetEnchant = false;
	bool bRevivalPet = false;
	bool bRemovePetOption = false;
	bool bGradePlus = false;
	if(g_pPlayer->IsItemCheckBufferItemToItem())
	{

		pMouseItem = g_pPlayer->GetItemCheckBuffer();

		g_pPlayer->ClearItemCheckBuffer();

		if(pMouseItem != NULL)
		{
			if(pMouseItem->GetItemClass() == ITEM_CLASS_PET_ENCHANT_ITEM)
			{
				if(pMouseItem->GetItemType() == 13 ||
					pMouseItem->GetItemType() == 14)	// �� ��Ȱ ¥��~
				{
					bRevivalPet = true;
				}

				if(pMouseItem->GetItemType() == 15)
				bSecondPetEnchant = true;
			}
			if(pMouseItem->GetItemClass() == ITEM_CLASS_MIXING_ITEM &&
				pMouseItem->GetItemType() >= 9 && pMouseItem->GetItemType() <= 18)
			{
				bRemovePetOption = true;
			}

			if(pMouseItem->GetItemClass() == ITEM_CLASS_EVENT_STAR &&
				pMouseItem->GetItemType() == 23) // ���ο� ���
			{
				bGradePlus = true;
			}
			delete pMouseItem;
		}
	}
	
	// �������� ������... ��~
	if (pInvenItem==NULL)
		return;

	bool bSucces = false;

	if(bRemovePetOption)
	{
		pInvenItem->ClearItemOption();
		bSucces = true;
	}
	else if(bGradePlus)
	{
		pInvenItem->SetGrade(m_Type);
		bSucces = true;
	}
	else if(pInvenItem->GetItemClass() == ITEM_CLASS_PET_ITEM)
	{
		if(bRevivalPet == true)
		{
			pInvenItem->SetCurrentDurability(m_Type);
			bSucces = true;
		}
		else
		if(bSecondPetEnchant == false)
		{
			// �� 1�� ��þƮ �ʻ�! �Ӽ� ���̱�
			WORD AttrType = HIWORD(m_Type);
			WORD AttrLevel = LOWORD(m_Type);
			pInvenItem->SetEnchantLevel(AttrType);	// Attr Type
			pInvenItem->SetSilver(AttrLevel);	// AttrLevel
			pInvenItem->SetItemColorSet(0xFFFF);
			bSucces = true;
		}
		else
		{
			// �� 2�� ��þƮ �ɼ� ���̱�, �Ʒ� �ڵ� �״�� �ᵵ �ɰ� ������ �籺�� �̶���.-��-
			pInvenItem->ClearItemOption();	// �ϴ� �Ӱ� ������ �𸣴� ����� ����-0-
			pInvenItem->AddItemOption(m_Type);
			bSucces = true;
		}
	}
	else
	{

		DWORD Option = m_Type;
	//	int Option2 = LOWORD(m_Type);

	//	if(oriOption < newOption)
		for(; Option != NULL; Option >>= 16)	// 2����Ʈ ����Ʈ �ϸ� LOWORD, HIWORD������ �ǳ�
		{
			int oriOption = (Option & 0xff00) >> 8;
			int newOption = (Option & 0xff);

			if(newOption == NULL && oriOption == NULL)
				continue;

	//			continue;
			
			if(oriOption)
				pInvenItem->ChangeItemOption(oriOption, newOption);
			else
				pInvenItem->AddItemOption(newOption);

			if((*g_pItemOptionTable)[oriOption].UpgradeOptionType == newOption)
				bSucces |= true;
		}
	}

	if(bSucces)
		PlaySound(SOUND_EVENT_FANFARE);

}

//----------------------------------------------------------------------
// ActionResultNodeFakeDie - FakeDie::Execute
//----------------------------------------------------------------------
void
MActionResultNodeFakeDie::Execute()
{
	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

}

//----------------------------------------------------------------------
// ActionResultNodeEvent - Event::Execute
//----------------------------------------------------------------------
void
MActionResultNodeEvent::Execute()
{
	if (g_pZone==NULL
		|| g_pPlayer==NULL)
	{
		return;
	}

}

//----------------------------------------------------------------------
// 
// MActionResult :: constructor/destructor
//
//----------------------------------------------------------------------
MActionResult::MActionResult()
{
}

MActionResult::~MActionResult()
{
	ACTIONRESULTNODE_LIST::iterator	iNode = m_List.begin();

	// ��� node�� delete���ش�.
	while (iNode != m_List.end())
	{
		MActionResultNode* pResultNode = *iNode;
		
		// ��� ����..
		//pResultNode->Execute();

		delete pResultNode;
		
		iNode++;
	}

	m_List.clear();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void
MActionResult::Release()
{
	ACTIONRESULTNODE_LIST::iterator	iNode = m_List.begin();

	// ��� node�� delete���ش�.
	while (iNode != m_List.end())
	{
		MActionResultNode* pResultNode = *iNode;
		
		delete pResultNode;
		
		iNode++;
	}

	m_List.clear();
}

//----------------------------------------------------------------------
// Add : ��� �ϳ��� �߰��Ѵ�.
//----------------------------------------------------------------------
void		
MActionResult::Add(MActionResultNode* pNode)
{
	if (pNode==NULL)
		return;

	// list�� �߰�
	m_List.push_back( pNode );
}

//----------------------------------------------------------------------
// ExecuteResult
//----------------------------------------------------------------------
// ActionInfo(Effect)�� ���� ����� �����Ѵ�.
//----------------------------------------------------------------------
void
MActionResult::Execute()
{
	//------------------------------------------------
	// ���~~ ó���Ѵ�.
	//------------------------------------------------
	while (!m_List.empty())
	{	
		MActionResultNode* pResultNode = m_List.front();
		
		m_List.pop_front();

		if (pResultNode!=NULL)
		{
			pResultNode->Execute();

			delete pResultNode;
		}
	}
}

//----------------------------------------------------------------------
// ActionResultNode - OpenCasket::Execute
//----------------------------------------------------------------------
void
MActionResultNodeChangeItemGenderInInventory::Execute()
{
	if (g_pInventory==NULL)
	{
		return;
	}

	MItem*	pInvenItem = g_pInventory->GetItem(m_TargetID);
	MItem*	pMouseItem = NULL;

	if(g_pPlayer->IsItemCheckBufferItemToItem())
	{
		pMouseItem = g_pPlayer->GetItemCheckBuffer();

		g_pPlayer->ClearItemCheckBuffer();
		if(pMouseItem != NULL)
			delete pMouseItem;
	}
	
	// �������� ������... ��~
	if (pInvenItem==NULL)
		return;

	pInvenItem->SetItemType( pInvenItem->GetItemType() ^ 0x1 );

	g_pInventory->CheckAffectStatus( pInvenItem );
	PlaySound(SOUND_EVENT_FANFARE);
}
