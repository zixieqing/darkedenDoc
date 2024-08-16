//----------------------------------------------------------------------
// MAttackCreatureEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MAttackCreatureEffectGenerator.h"
#include "MGuidanceEffect.h"
#include "MTopView.h"
#include "MCreature.h"
#include "MZone.h"
#include "MEffectSpriteTypeTable.h"
#include "DebugInfo.h"
#include "SkillDef.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//#include "MPlayer.h"
//extern	MPlayer	g_pPlayer->

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MAttackCreatureEffectGenerator	g_AttackCreatureEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MAttackCreatureEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].FrameID;

	// creature�� ��ǥ
	int cx, cy, cz, effectCount = 0;	

	if( egInfo.nActionInfo == STEP_SKILL_KASAS_ARROW_2 || egInfo.nActionInfo == STEP_SKILL_BLAZE_BOLT_2 ||
		egInfo.nActionInfo == STEP_SKILL_EARTHS_TEETH_2 )
		effectCount = 1;
	else
	if( egInfo.nActionInfo == STEP_SKILL_KASAS_ARROW_3 || egInfo.nActionInfo == STEP_SKILL_BLAZE_BOLT_3 ||
		egInfo.nActionInfo == STEP_SKILL_EARTHS_TEETH_3 )
		effectCount = 2;

	// ��ǥ ��ġ Pixel��ǥ
	MCreature* pCreature = g_pZone->GetCreature( egInfo.creatureID );

	if (pCreature == NULL)
	{
		return false;
	}

	//-----------------------------------
	// [ TEST CODE ]
	//-----------------------------------
	//if (pCreature->GetID() != g_pPlayer->GetID())
	//{
	//	pCreature->PacketSpecialAction( nActionInfo, g_pPlayer->GetX(), g_pPlayer->GetY(), g_pPlayer->GetZ(), g_pPlayer->GetID());
	//}
	
	// Creture�� ��ǥ�� ��ǥ��ǥ�� �����Ѵ�.
	cx = g_pTopView->MapToPixelX( pCreature->GetX() );
	cy = g_pTopView->MapToPixelY( pCreature->GetY() );
	cz = pCreature->GetZ();

	MGuidanceEffect* pEffect = new MGuidanceEffect(bltType);	
	
	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);
	
	pEffect->SetFrameID( frameID, maxFrame );		// 0�� Effect, Max 3 Frame					

	// �߻� ��ġ Pixel��ǥ	
	pEffect->SetPixelPosition( egInfo.x0, egInfo.y0, egInfo.z0 );

	pEffect->SetDirection( egInfo.direction );
	
	// ��ǥ Creature
	pEffect->SetTraceCreatureID( egInfo.creatureID );
	pEffect->SetStepPixel( egInfo.step );
	

	// ���ӵǴ� Frame (��ǥ�� �ִٸ� ���� ���� ���� - -;)
	pEffect->SetCount( egInfo.count, egInfo.linkCount );

	// ����
	pEffect->SetPower(egInfo.power);
	// ���� ���
	//pEffect->SetLight( light );
	if (g_pZone->AddEffect( pEffect ))
	{
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );

		if( effectCount == 0)
			return true;
	} else
		return false;
	if( effectCount > 0)
	{
		int z=-12;
		while(effectCount)
		{
			MGuidanceEffect* pEffect = new MGuidanceEffect(bltType);
			pEffect->SetFrameID( frameID, maxFrame );

//			if( egInfo.direction == 5 )
//			{
//				if(!( egInfo.nActionInfo == STEP_SKILL_EARTHS_TEETH_2 || egInfo.nActionInfo == STEP_SKILL_EARTHS_TEETH_3) )
//					pEffect->SetPixelPosition( egInfo.x0, egInfo.y0, egInfo.z0 + z );
//			} else
			if( egInfo.direction == 2 || egInfo.direction == 6 )
			{
				pEffect->SetPixelPosition( egInfo.x0+z, egInfo.y0, egInfo.z0 );
			} else
				pEffect->SetPixelPosition( egInfo.x0, egInfo.y0, egInfo.z0 - z );
			z+=24;
			pEffect->SetDirection( egInfo.direction );
			pEffect->SetTraceCreatureID( egInfo.creatureID );
			pEffect->SetStepPixel( egInfo.step );
			pEffect->SetCount( egInfo.count, egInfo.linkCount );
			pEffect->SetPower( egInfo.power );

			if( g_pZone->AddEffect( pEffect ) )
			{
				if( egInfo.pEffectTarget != NULL )
				{
					MEffectTarget *pTarget = new MEffectTarget ( *egInfo.pEffectTarget );								
					pEffect->SetLink( egInfo.nActionInfo, pTarget );				
				}
			} else
				return false;
			effectCount--;
		}
		return true;
	}

	return false;
}
