//----------------------------------------------------------------------
// MStopZoneRandomEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MStopZoneRandomEffectGenerator.h"
#include "MEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "MEffectSpriteTypeTable.h"

#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MStopZoneRandomEffectGenerator	g_StopZoneRandomEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MStopZoneRandomEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	bool bOK;

	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].FrameID;

	//---------------------------------------------
	// pixel��ǥ�� Map�� ��ǥ�� �ٲ��ش�.
	//---------------------------------------------
	TYPE_SECTORPOSITION	sX, sY;
	sX = g_pTopView->PixelToMapX(egInfo.x0);
	sY = g_pTopView->PixelToMapY(egInfo.y0);

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	int x, y;

	MEffect*	pEffect;
	//---------------------------------------------
	// Effect ���� - Left Up
	//---------------------------------------------
	x = sX - (rand()%3 + 1);
	y = sY - (rand()%3 + 1);
	pEffect = new MEffect(bltType);

	pEffect->SetFrameID( frameID, maxFrame );	

	pEffect->SetPosition(x, y);		// Sector ��ǥ		
	pEffect->SetZ(egInfo.z0);			
	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
	pEffect->SetCount( egInfo.count, egInfo.linkCount );			// ���ӵǴ� Frame

	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	// ����
	pEffect->SetPower(egInfo.power);

	// ���� ���
	//pEffect->SetLight( light );

	// Zone�� �߰��Ѵ�.
	bOK = g_pZone->AddEffect( pEffect );

	if (bOK)
	{
		// ���� Effect ���� ����
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );	
	}

	MEffectTarget*	pEffectTarget2;
	//---------------------------------------------
	// Effect ���� - Right Up
	//---------------------------------------------
	x = sX + (rand()%3 + 1);
	y = sY - (rand()%3 + 1);
	pEffect = new MEffect(bltType);
	
	
	pEffect->SetFrameID( frameID, maxFrame );	

	pEffect->SetPosition(x, y);		// Sector ��ǥ	
	pEffect->SetZ(egInfo.z0);			
	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.	
	pEffect->SetCount( egInfo.count , egInfo.linkCount );			// ���ӵǴ� Frame

	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	// ����
	pEffect->SetPower(egInfo.power);

	// ���� ���
	//pEffect->SetLight( light );

	// Zone�� �߰��Ѵ�.
	if (g_pZone->AddEffect( pEffect ))
	{
		// ���� Effect ���� ����
		if (egInfo.pEffectTarget == NULL)
		{
			pEffect->SetLink( egInfo.nActionInfo, NULL );
		}
		else
		{
			pEffectTarget2 = new MEffectTarget(*egInfo.pEffectTarget);
			pEffect->SetLink( egInfo.nActionInfo, pEffectTarget2 );
			//pEffectTarget2->Set( egInfo.x0-TILE_X, egInfo.y0, z0, egInfo.creatureID );
		}			
	}


	//---------------------------------------------
	// Effect ���� - Right Down
	//---------------------------------------------
	x = sX + (rand()%3 + 1);
	y = sY + (rand()%3 + 1);
	pEffect = new MEffect(bltType);


	pEffect->SetFrameID( frameID, maxFrame );	

	pEffect->SetPosition(x, y);		// Sector ��ǥ						
	pEffect->SetZ(egInfo.z0);			
	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.	
	pEffect->SetCount( egInfo.count , egInfo.linkCount );			// ���ӵǴ� Frame

	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	// ����
	pEffect->SetPower(egInfo.power);

	// ���� ���
	//pEffect->SetLight( light );

	// Zone�� �߰��Ѵ�.
	if (g_pZone->AddEffect( pEffect ))
	{
		// ���� Effect ���� ����
		if (egInfo.pEffectTarget == NULL)
		{
			pEffect->SetLink( egInfo.nActionInfo, NULL );
		}
		else
		{
			pEffectTarget2 = new MEffectTarget(*egInfo.pEffectTarget);
			pEffect->SetLink( egInfo.nActionInfo, pEffectTarget2 );
		}

	}

	//---------------------------------------------
	// Effect ���� - Left Down
	//---------------------------------------------
	x = sX - (rand()%3 + 1);
	y = sY + (rand()%3 + 1);

	pEffect = new MEffect(bltType);


	pEffect->SetFrameID( frameID, maxFrame );	

	pEffect->SetPosition(x, y);		// Sector ��ǥ						
	pEffect->SetZ(egInfo.z0);			
	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.	
	pEffect->SetCount( egInfo.count , egInfo.linkCount );			// ���ӵǴ� Frame

	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	// ����
	pEffect->SetPower(egInfo.power);

	// ���� ���
	//pEffect->SetLight( light );

	// Zone�� �߰��Ѵ�.
	if (g_pZone->AddEffect( pEffect ))
	{
		// ���� Effect ���� ����
		if (egInfo.pEffectTarget == NULL)
		{
			pEffect->SetLink( egInfo.nActionInfo, NULL );
		}
		else
		{
			pEffectTarget2 = new MEffectTarget(*egInfo.pEffectTarget);
			pEffect->SetLink( egInfo.nActionInfo, pEffectTarget2 );
		}
	}


	return bOK;
}
