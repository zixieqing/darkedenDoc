//----------------------------------------------------------------------
// MAttackCreatureParabolaEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MAttackCreatureParabolaEffectGenerator.h"
#include "MParabolaEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "MEffectSpriteTypeTable.h"
#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MAttackCreatureParabolaEffectGenerator	g_AttackCreatureParabolaEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MAttackCreatureParabolaEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].FrameID;

	// creature�� ��ǥ
	int cx, cy, cz;	

	// ��ǥ ��ġ Pixel��ǥ
	MCreature* pCreature = g_pZone->GetCreature( egInfo.creatureID );

	if (pCreature == NULL)
	{
		return false;
	}
	
	// Creture�� ��ǥ�� ��ǥ��ǥ�� �����Ѵ�.
	cx = g_pTopView->MapToPixelX( pCreature->GetX() );
	cy = g_pTopView->MapToPixelY( pCreature->GetY() );
	cz = pCreature->GetZ() + TILE_Y;	// �� Ÿ������ ���� ���ش�.

	// ������ Effect����
	MParabolaEffect* pEffect = new MParabolaEffect(bltType);	
	
	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);
	
	pEffect->SetFrameID( frameID, maxFrame );

	// �߻� ��ġ Pixel��ǥ	- �� Ÿ������ ���� ���ش�.
	pEffect->SetPixelPosition( egInfo.x0, egInfo.y0, egInfo.z0+TILE_Y );	
					
	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	// ��ǥ ��ġ Pixel��ǥ
	pEffect->SetTarget( cx,cy,cz, egInfo.step );

	// ���ӵǴ� Frame (��ǥ�� �ִٸ� ���� ���� ���� - -;)
	pEffect->SetCount( egInfo.count, egInfo.linkCount );

	// ����
	pEffect->SetPower(egInfo.power);
	
	// ���� ���
	//pEffect->SetLight( light );

	if (g_pZone->AddEffect( pEffect ))
	{
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );

		return true;
	}

	return false;

}
