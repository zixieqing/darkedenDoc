//----------------------------------------------------------------------
// MRippleZonePixelEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MRippleZonePixelEffectGenerator.h"
#include "MEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "MCreature.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"
#include "UserInformation.h"

//#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MRippleZonePixelEffectGenerator	g_RippleZoneEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MRippleZonePixelEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	//------------------------------------------------------------
	// �̹����� ������ǥ(sx,sy)�� Effect�� ����ϰ�
	// �������� (tx,ty)�� Effect�� ����ϰ� �ȴ�.
	// MEffectTarget�� �����ϸ� �����ϴ�.
	//------------------------------------------------------------
	MEffectTarget* pTarget = egInfo.pEffectTarget;

	// ���� ��ǥ
	int sx = egInfo.x0;
	int sy = egInfo.y0;
	int sz = 0;//egInfo.z0;

	// ��ǥ ��ǥ
	int tx = egInfo.x1; 
	int ty = egInfo.y1;
	int tz = 0;//egInfo.z1;

	int tx2 = tx;
	int ty2 = ty;

	int est = egInfo.effectSpriteType;

	//------------------------------------------------------------
	// �ϵ��ڵ�.. ����
	//------------------------------------------------------------
	bool bPixelStepMove = false;
	bool bGroundEffect = false;
	bool bResetTarget = true;
	int startMoveStep = 0;

	//------------------------------------------------------------
	// Power of Land
	//------------------------------------------------------------
	if (est==EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1)
	{
		// 1~3���̿� �ϳ��� �����Ѵ�.
		est = EFFECTSPRITETYPE_POWER_OF_LAND_STONE_2 + rand()%3;
		
		bGroundEffect = true;
		bPixelStepMove = true;
		startMoveStep = 1;
		bResetTarget = false;
	}
	//------------------------------------------------------------
	// Earthquake
	//------------------------------------------------------------
	else if (est==EFFECTSPRITETYPE_EARTHQUAKE_1)
	{
		// 1~3���̿� �ϳ��� �����Ѵ�.
		est = EFFECTSPRITETYPE_EARTHQUAKE_1 + rand()%3;
		
		bGroundEffect = true;
		bPixelStepMove = true;
		startMoveStep = 3;
	}
	//------------------------------------------------------------
	// Transfusion
	//------------------------------------------------------------
	else if (est==EFFECTSPRITETYPE_TRANSFUSION_1 || est==EFFECTSPRITETYPE_GREEN_TRANSFUSION_1)
	{
		MCreature* pCreature = g_pZone->GetCreature( egInfo.creatureID );

		int targetX, targetY;

		// ����Ʈ(egInfo.xy0 + size)��  
		// ĳ����(pt + size)�� �浹�ϸ�
		// ����Ʈ �׸� �׸���..
		POINT pt;

 		if (pCreature==NULL)
		{
			targetX = egInfo.x1;
			targetY = egInfo.y1;

//			pt.x = targetX;
//			pt.y = targetY;
		}
		else
		{
			targetX = pCreature->GetX();
			targetY = pCreature->GetY();

		}
		pt = MTopView::MapToPixel( targetX, targetY );

		RECT rectEffect = 
		{
			egInfo.x0 + (g_TILE_X_HALF>>1),
			egInfo.y0 + (g_TILE_Y_HALF>>1),
			egInfo.x0 + g_TILE_X_HALF,
			egInfo.y0 + g_TILE_Y_HALF,
		};
		
		RECT rectChar =
		{
			pt.x,
			pt.y,
			pt.x + g_TILE_X_HALF,
			pt.y + g_TILE_Y_HALF
		};

		if (rectChar.left <= rectEffect.right
			&& rectChar.right >= rectEffect.left
			&& rectChar.top <= rectEffect.bottom
			&& rectChar.bottom >= rectEffect.top)
		{
			return false;
		}

		// 1~3���̿� �ϳ��� �����Ѵ�.
		if(g_pUserInformation->GoreLevel == false)
			est = EFFECTSPRITETYPE_GREEN_TRANSFUSION_1 + rand()%3;
		else
			est = EFFECTSPRITETYPE_TRANSFUSION_1 + rand()%3;

		bGroundEffect = true;
		bPixelStepMove = true;
		startMoveStep = 1;
	}

	if (bPixelStepMove)
	{
		// ��ǥ�������°� �ƴ϶�.. ������ pixel�� ��ŭ �����Ѵ�?
		// �� �ܰ� �̵�..
		int movePixel = egInfo.step;// * egInfo.count;

		int cx = sx-tx;
		int cy = sy-ty;

		if (bResetTarget && (cx==0 || cy==0))
		{
			//---------------------------------------------
			// pixel��ǥ�� Map�� ��ǥ�� �ٲ��ش�.
			//---------------------------------------------
			TYPE_SECTORPOSITION	sX, sY;
			sX = g_pTopView->PixelToMapX( sx );
			sY = g_pTopView->PixelToMapY( sy );

			//---------------------------------------------
			// ������ �������� ���� ��ǥ�� ���Ѵ�.	
			//---------------------------------------------
			TYPE_SECTORPOSITION x=sX, y=sY;
			MCreature::GetPositionToDirection(x,y, egInfo.direction);

			//---------------------------------------------
			// (x,y)�� �ٽ� pixel��ǥ�� �ٲ۴�.
			//---------------------------------------------
			tx = g_pTopView->MapToPixelX( x );
			ty = g_pTopView->MapToPixelY( y );

			// �ٽ� ���..
			cx = sx - tx;
			cy = sy - ty;
		}

		int currentPixel = sqrt(cx*cx + cy*cy);

		float basis = ((cx==0)? 0 : (float)cy / (float)cx);

		if (currentPixel==0)
		{			
		}
		else
		{
			movePixel = (float)movePixel * (1.0f - fabs((float)cy / (float)(2.0f*currentPixel)));
		
			if (pTarget!=NULL && pTarget->GetCurrentPhase()==1)
			{
				movePixel *= startMoveStep;
			}

			int movePixel2 = movePixel<<1;
			
			tx = sx - (cx * movePixel / currentPixel);
			ty = sy - (cy * movePixel / currentPixel);

			tx2 = sx - (cx * movePixel2 / currentPixel);
			ty2 = sy - (cy * movePixel2 / currentPixel);
		}
	}

	//-----------------------------------------------------
	// MEffectTarget�� ��ǥ ��ġ�� �ٽ� �����ؾ��Ѵ�.
	//-----------------------------------------------------	
	if (pTarget!=NULL && bResetTarget)
	{
		pTarget->Set(tx2, ty2, tz, pTarget->GetID());		
	}


	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[est].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[est].FrameID;

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	MEffect*	pEffect;
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	pEffect = new MEffect(bltType);

	pEffect->SetFrameID( frameID, maxFrame );	

	//pEffect->SetPosition(x, y);		// Sector ��ǥ(�ǹ� ���� ��)

	pEffect->SetPixelPosition(tx, ty, tz);		// pixel ��ǥ		
	
	// ���� ����
	pEffect->SetDirection( egInfo.direction );

	//pEffect->SetZ( sz );			
	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
	pEffect->SetCount( egInfo.count, egInfo.linkCount );			// ���ӵǴ� Frame

	// ����
	pEffect->SetPower(egInfo.power);

	// ���� ���
	//pEffect->SetLight( light );

	bool bAdd = false;
	// Zone�� �߰��Ѵ�.		
	if (bGroundEffect)
	{
		bAdd = g_pZone->AddGroundEffect( pEffect );
	}	
	else
	{
		bAdd = g_pZone->AddEffect( pEffect );
	}

	if (bAdd)
	{
		// ���� Effect ���� ����
		pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );	
	}

	return bAdd;
}
