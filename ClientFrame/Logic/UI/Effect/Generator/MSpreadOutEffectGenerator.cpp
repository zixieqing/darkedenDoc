//----------------------------------------------------------------------
// MSpreadOutEffectGenerator.cpp
//----------------------------------------------------------------------
// (�ϴ���) 8�������� ����� Effect
//
// step�� count�� �����δ�.
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MSpreadOutEffectGenerator.h"
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
//MSpreadOutEffectGenerator	g_SpreadOutEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MSpreadOutEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	bool bOK = false;

	int est = egInfo.effectSpriteType;

	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[est].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[est].FrameID;
	
	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);		

	MEffectTarget* pTarget = egInfo.pEffectTarget;

	// ���� ��ǥ
	int sx = egInfo.x0;
	int sy = egInfo.y0;
	int sz = 0;//egInfo.z0;

	int cx, cy;
	int tx, ty, tz=sz;	// ��ǥ ��ǥ
	

	MLinearEffect*	pEffect;
		
	//------------------------------------------------------------
	// ��ǥ�������°� �ƴ϶�.. ������ pixel�� ��ŭ �����Ѵ�?
	//------------------------------------------------------------
	// �� �ܰ� �̵�..
	for (int d=0; d<8; d++)
	{
		int movePixel = egInfo.step;// * egInfo.count;
	
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
		MCreature::GetPositionToDirection(x,y, d);

		//---------------------------------------------
		// (x,y)�� �ٽ� pixel��ǥ�� �ٲ۴�.
		//---------------------------------------------
		tx = g_pTopView->MapToPixelX( x );
		ty = g_pTopView->MapToPixelY( y );

		cx = sx - tx;
		cy = sy - ty;		

		int currentPixel = sqrt(cx*cx + cy*cy);

		float basis = ((cx==0)? 0 : (float)cy / (float)cx);

		if (currentPixel==0)
		{
		}
		else
		{
			movePixel = (float)movePixel * (1.0f - fabs((float)cy / (float)(2.0f*currentPixel)));
		
			/*
			if (pTarget!=NULL && pTarget->GetCurrentPhase()==1)
			{
				movePixel *= 3;
			}
			*/

			int movePixelStep = movePixel * egInfo.count;
			
			tx = sx - (cx * movePixelStep / currentPixel);
			ty = sy - (cy * movePixelStep / currentPixel);
		}

		//---------------------------------------------
		// Effect ����
		//---------------------------------------------
		pEffect = new MLinearEffect(bltType);


		pEffect->SetFrameID( frameID, maxFrame );	

		pEffect->SetPixelPosition( sx, sy, sz );
		pEffect->SetTarget( tx, ty, tz, egInfo.step );

		pEffect->SetStepPixel( egInfo.step );		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
		pEffect->SetCount( egInfo.count, egInfo.linkCount );			// ���ӵǴ� Frame

		// ���� ����
		pEffect->SetDirection( d );

		// ����
		pEffect->SetPower(egInfo.power);

		// ���� ���
		//pEffect->SetLight( light );

		// Zone�� �߰��Ѵ�.
		if (d==0)
		{
			bOK = g_pZone->AddEffect( pEffect );

			
			if (bOK)
			{
				// ���� Effect ���� ����
				if (pTarget == NULL)
				{
					pEffect->SetLink( egInfo.nActionInfo, NULL );
				}
				else
				{
					// ���� Effect ���� ����
					pEffect->SetLink( egInfo.nActionInfo, pTarget );			
					pTarget->Set( tx, ty, tz, egInfo.creatureID );
				}
			}			
		}
		else
		{
			if (g_pZone->AddEffect( pEffect ))
			{
				if (pTarget==NULL)
				{
					pEffect->SetLink( egInfo.nActionInfo, NULL );
				}
				else
				{
					MEffectTarget* pEffectTarget2 = new MEffectTarget( *pTarget );
					pEffect->SetLink( egInfo.nActionInfo, pEffectTarget2 );
					pEffectTarget2->Set( tx, ty, tz, egInfo.creatureID );
				}
			}			
		}
	}


	return bOK;
}
