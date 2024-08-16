//----------------------------------------------------------------------
// MRippleZoneWideEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MRippleZoneWideEffectGenerator.h"
#include "MEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "MCreature.h"
#include "MEffectSpriteTypeTable.h"
#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MRippleZoneWideEffectGenerator	g_RippleZoneWideEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MRippleZoneWideEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	bool bOK = false;

	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[egInfo.effectSpriteType].FrameID;

	//---------------------------------------------
	// pixel��ǥ�� Map�� ��ǥ�� �ٲ��ش�.
	//---------------------------------------------
	TYPE_SECTORPOSITION	sX, sY;
	sX = g_pTopView->PixelToMapX(egInfo.x0);
	sY = g_pTopView->PixelToMapY(egInfo.y0);

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);

	MEffect*	pEffect;
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	int i;
	int n=(egInfo.power<<1) - 1;

	// �ϴ� �� ĭ �����δ�.
	TYPE_SECTORPOSITION x=sX, y=sY;
	int cX, cY;
	MCreature::GetPositionToDirection(x,y, egInfo.direction);
	
	// ���⿡ ���� Ȯ��� ��ǥ�� �޸��Ѵ�.
	switch (egInfo.direction)
	{
		case DIRECTION_LEFT : case DIRECTION_RIGHT :			
			y = y-(egInfo.power-1);
			cX	= 0;
			cY	= 1;			
		break;

		case DIRECTION_UP : case DIRECTION_DOWN :
			x = x-(egInfo.power-1);			
			cX	= 1;
			cY	= 0;
		break;

		case DIRECTION_LEFTUP : case DIRECTION_RIGHTDOWN :
			x = x-(egInfo.power-1);
			y = y+(egInfo.power-1);
			cX	= 1;
			cY	= -1;			
		break;

		case DIRECTION_LEFTDOWN : case DIRECTION_RIGHTUP :
			x = x-(egInfo.power-1);
			y = y-(egInfo.power-1);
			cX	= 1;
			cY	= 1;			
		break;
	}

	// Effec����
	for (i=0; i<n; i++)
	{
		// Zone�� ������ ����� ���..
		if (x<0 || y<0 || x>=g_pZone->GetWidth() || y>=g_pZone->GetHeight())
			continue;

		pEffect = new MEffect(bltType);

		pEffect->SetFrameID( frameID, maxFrame );	

		// ���� ��ǥ�� ���Ѵ�.			
		pEffect->SetPosition(x, y);		// Sector ��ǥ		
		
		// ���� ����
		pEffect->SetDirection( egInfo.direction );

		pEffect->SetZ(egInfo.z0);			
		pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
		pEffect->SetCount( egInfo.count, egInfo.linkCount );			// ���ӵǴ� Frame

		// ����
		pEffect->SetPower(egInfo.power+1);

		// ���� ���
		//pEffect->SetLight( light );

		// Zone�� �߰��Ѵ�.
		bool bAdd = g_pZone->AddEffect( pEffect );

		if (bAdd)
		{
			if (i==(egInfo.power-1))
			{
				bOK = true;
					
				pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );
			}
			else
			{
				pEffect->SetLink( egInfo.nActionInfo, NULL );
			}
		}


		// ���� ��ǥ
		x += cX;
		y += cY;
	}


	return bOK;
}
