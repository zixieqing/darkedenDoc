//----------------------------------------------------------------------
// MAttachZoneSelectableEffectGenerator.cpp
//----------------------------------------------------------------------
// Tile�� �º��� Effect���� �����Ѵ�.
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MAttachZoneSelectableEffectGenerator.h"
#include "MEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"
#include "DebugInfo.h"
//#define	new			DEBUG_NEW

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MAttachZoneSelectableEffectGenerator	g_StopZoneEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MAttachZoneSelectableEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	int est = egInfo.effectSpriteType;
	
	//---------------------------------------------
	// pixel��ǥ�� Map�� ��ǥ�� �ٲ��ش�.
	//---------------------------------------------
	/*
	int	sX, sY;
	sX = g_pTopView->PixelToMapX(egInfo.x0);
	sY = g_pTopView->PixelToMapY(egInfo.y0);

	//---------------------------------------------
	// Map��ǥ�� �ٽ� pixel��ǥ�� �ٲ۴�.
	//---------------------------------------------
	POINT pixelPoint;
	pixelPoint = g_pTopView->MapToPixel(sX, sY);
	*/
	// 2001.10.6
	POINT pixelPoint = { egInfo.x0, egInfo.y0 };

	
	//----------------------------------------------------------------
	// �ٴڿ� �������� �� ���� �����ϰ�.. �ϵ� �ڵ�.. ����~
	//----------------------------------------------------------------
	if (est==EFFECTSPRITETYPE_BLOOD_GROUND_2_1)
	{
		est = EFFECTSPRITETYPE_BLOOD_GROUND_2_1 + rand()%4;

		pixelPoint.x += (rand()%g_TILE_X_HALF) - (g_TILE_X_HALF>>1);
		pixelPoint.y += (rand()%g_TILE_Y_HALF) - (g_TILE_Y_HALF>>1);
	}
	else if (est==EFFECTSPRITETYPE_BLOOD_GROUND_1_1)
	{
		est = EFFECTSPRITETYPE_BLOOD_GROUND_1_1 + rand()%5;

		pixelPoint.x += (rand()%g_TILE_X_HALF) - (g_TILE_X_HALF>>1);
		pixelPoint.y += (rand()%g_TILE_Y_HALF) - (g_TILE_Y_HALF>>1);
	}

	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[est].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[est].FrameID;



	//---------------------------------------------
	// MaxFrame�� ���� �˾ƿ´�.
	//---------------------------------------------
	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	MEffect*	pEffect;
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	pEffect = new MSelectableEffect(bltType);

	
	pEffect->SetFrameID( frameID, maxFrame );	

	pEffect->SetPixelPosition(pixelPoint.x, pixelPoint.y, egInfo.z0);		// pixel��ǥ		

	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.

	pEffect->SetCount( egInfo.count, egInfo.linkCount );			// ���ӵǴ� Frame

	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	// ����
	pEffect->SetPower(egInfo.power);

	// ���� ���
	//pEffect->SetLight( light );

	
	// Ground Effect��..
	// Zone�� �߰��Ѵ�.
	if (g_pZone->AddGroundEffect( pEffect ))
	{
		// ���� Effect ���� ����
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );

		return true;
	}

	return false;
}
