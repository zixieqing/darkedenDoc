//----------------------------------------------------------------------
// MFallingEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MFallingEffectGenerator.h"
#include "MLinearEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "MEffectSpriteTypeTable.h"
#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE


//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MFallingEffectGenerator	g_FallingEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MFallingEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].FrameID;

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	MLinearEffect*	pEffect;
	int z;
	//---------------------------------------------
	// Effect ���� - Left Up
	//---------------------------------------------
	z = 300;
	pEffect = new MLinearEffect(bltType);

	pEffect->SetFrameID( frameID, maxFrame );	

	// �߻� ��ġ Pixel��ǥ	(��ǥ��ġ���� z��ŭ ����)
	// �ٵ� 0���� �Ұ���. 1�� �Ұ���.. ���� �� �ִ� flag�� �ʿ��ϴ�..
	// generator�� ���� �������... 

	//pEffect->SetPixelPosition( egInfo.x0, egInfo.y0, egInfo.z1+z );	
	pEffect->SetPixelPosition( egInfo.x1, egInfo.y1, egInfo.z1+z );	

	// ���� ����
	pEffect->SetDirection( egInfo.direction );
					
	// ��ǥ ��ġ Pixel��ǥ (��ǥ��ġ)
	pEffect->SetTarget( egInfo.x1, egInfo.y1, egInfo.z1, egInfo.step );

	// ���ӵǴ� Frame (��ǥ�� �ִٸ� ���� ���� ���� - -;)
	pEffect->SetCount( egInfo.count, egInfo.linkCount );

	// ����
	pEffect->SetPower(egInfo.power);
	// ���� ���
	//pEffect->SetLight( light );

	// Zone�� �߰��Ѵ�.
	if (g_pZone->AddEffect( pEffect ))
	{
		// ���� Effect ���� ����
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );

		return true;	
	}

	return false;

}
