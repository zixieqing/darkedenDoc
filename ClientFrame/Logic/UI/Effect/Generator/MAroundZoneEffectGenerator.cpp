//----------------------------------------------------------------------
// MAroundZoneEffectGenerator.cpp
//----------------------------------------------------------------------
// Tile�� �º��� Effect���� �����Ѵ�.
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MAroundZoneEffectGenerator.h"
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
//MAroundZoneEffectGenerator	g_StopZoneEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MAroundZoneEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	bool bOK = false;

	MEffectTarget* pTarget = egInfo.pEffectTarget;

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

	int num = 0;
	int dwWaitCount = 0;
	if(est == EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2)
		num = 1;
	else if(est == EFFECTSPRITETYPE_INSTALL_TURRET_SCRAP1)
		num = 5;
	else if(est == EFFECTSPRITETYPE_SPIT_STREAM)
		num = 6;
	else if(est == EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW)
		num = 3;
	else
		num = rand()%2 + 2;
	
	for (int TempCount=0; TempCount<num; TempCount++)
	{
		dwWaitCount = 0;
		POINT pixelPoint = { egInfo.x1, egInfo.y1 };

		if (egInfo.effectSpriteType == EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2)
		{
			est = egInfo.effectSpriteType + rand()%2;

			switch(egInfo.step%4)
			{
			case 0:
				pixelPoint.x = pixelPoint.x - rand()%(TILE_X<<1) - g_TILE_X_HALF;
				pixelPoint.y = pixelPoint.y - rand()%(TILE_Y<<1) - g_TILE_Y_HALF;
				break;

			case 1:
				pixelPoint.x = pixelPoint.x - rand()%(TILE_X<<1) - g_TILE_X_HALF;
				pixelPoint.y = pixelPoint.y + rand()%(TILE_Y<<1) + g_TILE_Y_HALF;
				break;

			case 2:
				pixelPoint.x = pixelPoint.x + rand()%(TILE_X<<1) + g_TILE_X_HALF;
				pixelPoint.y = pixelPoint.y - rand()%(TILE_Y<<1) - g_TILE_Y_HALF;
				break;

			case 3:
				pixelPoint.x = pixelPoint.x + rand()%(TILE_X<<1) + g_TILE_X_HALF;
				pixelPoint.y = pixelPoint.y + rand()%(TILE_Y<<1) + g_TILE_Y_HALF;
				break;

			}

		}
		
		//----------------------------------------------------------------
		// �ٴڿ� Ƣ�� ����..
		//----------------------------------------------------------------
		///*
		else if (est==EFFECTSPRITETYPE_GUN_DUST_1)
		{
			switch (rand()%3)
			{
				case 0 :
					est = EFFECTSPRITETYPE_GUN_DUST_1;
				break;
			
				case 1 :
					est = EFFECTSPRITETYPE_GUN_DUST_2;
				break;

				case 2 :
					est = EFFECTSPRITETYPE_GUN_DUST_3;
				break;
			}

			//pixelPoint.x += (rand()%g_TILE_X_HALF) - (g_TILE_X_HALF>>1);
			//pixelPoint.y += (rand()%g_TILE_Y_HALF) - (g_TILE_Y_HALF>>1);
			pixelPoint.x += (rand()%(TILE_X<<1)) - TILE_X;
			pixelPoint.y += (rand()%(TILE_Y<<1)) - TILE_Y;
		} 
		else if (est==EFFECTSPRITETYPE_MOLE_SHOT_1 )
		{
			est = EFFECTSPRITETYPE_MOLE_SHOT_1+(rand()%5);
			pixelPoint.x += (rand()%(TILE_X<<1)) - TILE_X;
			pixelPoint.y += (rand()%(TILE_Y<<1)) - TILE_Y;
		}
		else if( est == EFFECTSPRITETYPE_INSTALL_TURRET_SCRAP1)
		{
			est = EFFECTSPRITETYPE_INSTALL_TURRET_SCRAP1+(rand()%5);
			pixelPoint.x += (rand()%(TILE_X<<1))/* - TILE_X*/;
			pixelPoint.y += (rand()%(TILE_Y<<1))/* - TILE_Y*/;
		}
		else if(est == EFFECTSPRITETYPE_SPIT_STREAM)
		{
			int DirX = 0, DirY = 0;
			pixelPoint.x = egInfo.x0;
			pixelPoint.y = egInfo.y0;
			switch (egInfo.direction)
			{
				case DIRECTION_LEFTDOWN		: DirX = -1;	DirY = +1;	break;
				case DIRECTION_RIGHTUP		: DirX = +1;	DirY = -1;	break;
				case DIRECTION_LEFTUP		: DirX = -1;	DirY = -1;	break;
				case DIRECTION_RIGHTDOWN	: DirX = +1;	DirY = +1;	break;
				case DIRECTION_LEFT			: DirX = -1;				break;
				case DIRECTION_DOWN			:				DirY = +1;	break;
				case DIRECTION_UP			:				DirY = -1;	break;
				case DIRECTION_RIGHT		: DirX = +1;				break;
			}
//			pixelPoint.x += ((((TempCount)*(g_TILE_X_HALF))*DirX)+1);
//			pixelPoint.y += ((((TempCount)*(g_TILE_Y_HALF))*DirY)+1);
			pixelPoint.x += ((((TempCount+1)*(g_TILE_X_HALF))*DirX));
			pixelPoint.y += ((((TempCount+1)*(g_TILE_Y_HALF))*DirY));
			dwWaitCount = (TempCount);
		}
		else if(est == EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW)
		{
			pixelPoint.x = egInfo.x0; 
			pixelPoint.y = egInfo.y0;
		}
		
		//*/

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
		pEffect = new MEffect(bltType);

		pEffect->SetFrameID( frameID, maxFrame );	

		pEffect->SetPixelPosition(pixelPoint.x, pixelPoint.y, egInfo.z0);		// pixel��ǥ		

		pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.

		pEffect->SetCount( maxFrame, egInfo.linkCount );			// ���ӵǴ� Frame

		// ���� ����
		if(est == EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW) 
		{
			pEffect->SetMulti(true);
			pEffect->SetDirection((egInfo.direction + (TempCount-1) + 8)%8);
		}
		else
			pEffect->SetDirection( egInfo.direction );

		// ����
		pEffect->SetPower(egInfo.power);
		
		// ���� ���
		//pEffect->SetLight( light );
		
		if(dwWaitCount)
		{
			pEffect->SetWaitFrame(dwWaitCount);
			pEffect->SetCount( dwWaitCount+maxFrame, egInfo.linkCount );
			pEffect->SetMulti(true);
		}
		// Zone�� �߰��Ѵ�.
		if (g_pZone->AddEffect( pEffect, dwWaitCount))
		{
			if (!bOK)
			{
				// ���� Effect ���� ����
				pEffect->SetLink( egInfo.nActionInfo, pTarget );

				bOK = true;
			}
			else
			{
				if (pTarget==NULL)
				{
					pEffect->SetLink( egInfo.nActionInfo, NULL );
				}
				else
				{
					MEffectTarget* pEffectTarget2 = new MEffectTarget( *pTarget );
					pEffect->SetLink( egInfo.nActionInfo, pEffectTarget2 );
					pEffectTarget2->Set( egInfo.x1, egInfo.y1, egInfo.z1, egInfo.creatureID );
				}
			}
		}
	}
	
	return bOK;
}
