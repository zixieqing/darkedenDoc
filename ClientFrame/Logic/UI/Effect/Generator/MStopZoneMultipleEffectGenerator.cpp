//----------------------------------------------------------------------
// MStopZoneMultipleEffectGenerator.cpp
//----------------------------------------------------------------------
// 4���� Effect�� ���߿��� ��������.
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MStopZoneMultipleEffectGenerator.h"
#include "MTopView.h"
#include "MZone.h"
#include "MEffectSpriteTypeTable.h"
#include "DebugInfo.h"
#include "SkillDef.h"
#include "MEventManager.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MMultipleFallingEffectGenerator	g_StopZoneCrossEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MStopZoneMultipleEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].FrameID;

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	bool bOK = false;

	MEffect*	pEffect;
	int x, y;


	MEffectTarget*	pEffectTarget2;
	
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	int numEffectPhase = 4;

	int randY = 50;
	int randX = TILE_X;
	const int numEffect = 4;

	if(egInfo.nActionInfo == SKILL_ACID_STORM_WIDE || egInfo.nActionInfo == SKILL_POISON_STORM_WIDE)
	{
		randY = 100;
		randX = TILE_X*2;
		numEffectPhase = 6;
	}

	MEvent event;
	event.eventID = EVENTID_METEOR_SHAKE;
	event.eventType = EVENTTYPE_ZONE;
	event.eventDelay = 2300;
	event.eventFlag = EVENTFLAG_SHAKE_SCREEN;
	event.parameter3 = 1;
	g_pEventManager->AddEvent(event);

	int ex[numEffect];
	int ey[numEffect];

	const int phaseUpper = 150;	// �� �ܰ迡�� ���� �� �ö󰡴� ��ǥ ����

	int effectCount = 0;

	// numEffectPhase * numEffect ���� effect�� �����Ѵ�.
	for (int i=0; i<numEffectPhase; i++)
	{
		int n = 0;
	
		ex[n] = egInfo.x0 - rand()%randX - g_TILE_X_HALF;
		ey[n] = egInfo.y0 - rand()%randY;

		n++;
		ex[n] = egInfo.x0 - rand()%randX - g_TILE_X_HALF;
		ey[n] = egInfo.y0 + rand()%randY;

		n++;
		ex[n] = egInfo.x0 + rand()%randX + g_TILE_X_HALF;
		ey[n] = egInfo.y0 - rand()%randY;

		n++;
		ex[n] = egInfo.x0 + rand()%randX + g_TILE_X_HALF;
		ey[n] = egInfo.y0 + rand()%randY;

		for (int j=0; j<numEffect; j++)
		{
			x = ex[j];
			y = ey[j];

			pEffect = new MEffect(bltType);
			pEffect->SetDelayFrame(effectCount);
			
			pEffect->SetFrameID( frameID, maxFrame );	

			// �߻� ��ġ Pixel��ǥ	
			pEffect->SetPixelPosition( x, y, egInfo.z0 );	

			// ���� ����
			pEffect->SetDirection( egInfo.direction );
							
//			// ��ǥ ��ġ Pixel��ǥ
//			pEffect->SetTarget( x, y, zt, egInfo.step );

			// ���ӵǴ� Frame (��ǥ�� �ִٸ� ���� ���� ���� - -;)
			pEffect->SetCount( egInfo.count+effectCount, egInfo.linkCount );
			pEffect->SetMulti( true );
			
			effectCount += 2;

			// ����
			pEffect->SetPower(egInfo.power);

			// Zone�� �߰��Ѵ�.
			if (g_pZone->AddEffect( pEffect ))
			{
				if (!bOK)
				{
					pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );
					bOK = true;
				}
				else
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
						pEffectTarget2->Set( x, y, egInfo.z0, egInfo.creatureID );
					}
				}
			}
		}
	}



	return bOK;
}
