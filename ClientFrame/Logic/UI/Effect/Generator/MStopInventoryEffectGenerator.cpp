//----------------------------------------------------------------------
// MStopInventoryEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MStopInventoryEffectGenerator.h"
#include "MScreenEffect.h"
#include "MTopView.h"
#include "MScreenEffectManager.h"
#include "UIFunction.h"
#include "MInventory.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"
#include "DebugInfo.h"
#include "VS_UI_GameCommon.h"

//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

extern MScreenEffectManager*	g_pInventoryEffectManager;

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MStopInventoryEffectGenerator	g_StopInventoryEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MStopInventoryEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	int est = egInfo.effectSpriteType;

	int invenX = egInfo.x1;
	int invenY = egInfo.y1;
	
	POINT grid_plus = { 0, 0 };
	
//	if (est==EFFECTSPRITETYPE_IDENTIFY_1x1
//		|| est==EFFECTSPRITETYPE_ENCHANT_1x1)
//	{
		const MItem* pItem = g_pInventory->GetItem( invenX, invenY );

		//---------------------------------------------------------------
		// �������� ������ ũ�⿡ ���� ����Ʈ�� �ٲ��.
		//---------------------------------------------------------------
		if (pItem!=NULL)
		{
			grid_plus.x = (pItem->GetGridWidth()-1)*C_VS_UI_INVENTORY::GRID_UNIT_PIXEL_X/2;
			grid_plus.y = (pItem->GetGridHeight()-1)*C_VS_UI_INVENTORY::GRID_UNIT_PIXEL_Y/2;
//			const int gridMax = 4;
//			const int estIdentify[gridMax] =
//			{
//				EFFECTSPRITETYPE_IDENTIFY_1x1,		// 0
//				EFFECTSPRITETYPE_IDENTIFY_1x3,		// 1
//				EFFECTSPRITETYPE_IDENTIFY_2x2,		// 2
//				EFFECTSPRITETYPE_IDENTIFY_2x3,		// 3
//			};
//
//			const int estEnchant[gridMax] =
//			{
//				EFFECTSPRITETYPE_ENCHANT_1x1,		// 0
//				EFFECTSPRITETYPE_ENCHANT_1x3,		// 1
//				EFFECTSPRITETYPE_ENCHANT_2x2,		// 2
//				EFFECTSPRITETYPE_ENCHANT_2x3,		// 3
//			};
//
//			int gridX = pItem->GetGridWidth();
//			int gridY = pItem->GetGridHeight();
//
//			// īī...
//			int gridValue = (gridX-1)*2 + (gridY==3);
//
//			if (gridValue < gridMax)
//			{
//				if (est==EFFECTSPRITETYPE_IDENTIFY_1x1)
//				{
//					est = estIdentify[gridValue];
//				}
//				else //if (frameID==EFFECTSPRITETYPE_ENCHANT_1x1
//				{
//					est = estEnchant[gridValue];
//				}
//				
//			}
		}
//	}
//*/
	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[est].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[est].FrameID;


	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	MScreenEffect*	pEffect;
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	pEffect = new MScreenEffect(bltType);

	pEffect->SetFrameID( frameID, maxFrame );	

	// ������ ����..(!!!!!!!!!!)
	//---------------------------------------------
	// ���� inventory�� ��ġ...
	//---------------------------------------------
	POINT point;
	
	point = UI_GetInventoryPosition();
	pEffect->SetScreenBasis(point.x, point.y);

	// SetPosition�� ���� ����� �Ѵ�. �ȿ��� Map��ǥ�� ��ȯ�ϴ°� ���� ��縮����.
	pEffect->SetPosition( egInfo.x1, egInfo.y1 );

	//---------------------------------------------
	// ȭ�鿡�� Effect�� ��ġ
	//---------------------------------------------
	point = UI_GetInventoryGridPosition(egInfo.x1, egInfo.y1);	
	pEffect->SetScreenPosition(point.x+grid_plus.x, point.y+grid_plus.y);


	pEffect->SetStepPixel(0);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
	pEffect->SetCount( egInfo.count, egInfo.linkCount );			// ���ӵǴ� Frame

	// ���� ����
	pEffect->SetDirection( 0 );

	// ����
	pEffect->SetPower(egInfo.power);

	// ���� ���
	//pEffect->SetLight( light );

	// Inventory�� �߰��Ѵ�.
	
	//if (
	g_pInventoryEffectManager->AddEffect( pEffect );
	//)
	{
		// ���� Effect ���� ����
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );	
	}

	return true;
}
