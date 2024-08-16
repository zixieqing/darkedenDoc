//----------------------------------------------------------------------
// MBloodyWaveEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MBloodyWaveEffectGenerator.h"
#include "MEffect.h"
#include "MTopView.h"
#include "MZone.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"

#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
//MBloodyWaveEffectGenerator	g_BloodyWaveEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MBloodyWaveEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
{
	bool bOK = false;

	int est = egInfo.effectSpriteType;

	// �ϵ� �ϵ�~
	if (est>=EFFECTSPRITETYPE_BLOODY_WALL_1
		&& est<=EFFECTSPRITETYPE_BLOODY_WALL_3)
	{
		est = EFFECTSPRITETYPE_BLOODY_WALL_1 + rand()%3;
	}


	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[est].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[est].FrameID;
	bool			repeatFrame	= (*g_pEffectSpriteTypeTable)[est].RepeatFrame;

	static int lastPhase = 0;

	int currentPhase = (egInfo.pEffectTarget==NULL? lastPhase +1 : egInfo.pEffectTarget->GetCurrentPhase());
	lastPhase = currentPhase;
	
	//---------------------------------------------
	// ��ǥ ���氪
	//---------------------------------------------
	std::vector<POINT> v_cp;
	POINT p;

	switch (currentPhase)
	{
		// ��, ��, ��, ��
		case 1 :
		{
			p.x = 0; p.y = -1;
			v_cp.push_back(p);
			p.x = 0; p.y = 1;
			v_cp.push_back(p);
			p.x = 1; p.y = 0;
			v_cp.push_back(p);
			p.x = -1; p.y = 0;
			v_cp.push_back(p);
		}
		break;

		// �밢�� ���� 4��
		case 2 :
		{
			p.x = 1; p.y = -1;
			v_cp.push_back(p);
			p.x = 1; p.y = 1;
			v_cp.push_back(p);
			p.x = -1; p.y = -1;
			v_cp.push_back(p);
			p.x = -1; p.y = 1;
			v_cp.push_back(p);
		}
		break;

		// ���� �¿�.. ��ĭ�� �ǳʼ� 4��
		case 3 :
		{
			p.x = 0; p.y = -2;
			v_cp.push_back(p);
			p.x = 0; p.y = 2;
			v_cp.push_back(p);
			p.x = 2; p.y = 0;
			v_cp.push_back(p);
			p.x = -2; p.y = 0;
			v_cp.push_back(p);
		}
		break;

		// �밢�� 4���� 2����
		case 4 :
		{
			p.x = 1; p.y = -2;
			v_cp.push_back(p);
			p.x = 2; p.y = -1;
			v_cp.push_back(p);
			p.x = 1; p.y = 2;
			v_cp.push_back(p);
			p.x = 2; p.y = 1;
			v_cp.push_back(p);
			p.x = -1; p.y = -2;
			v_cp.push_back(p);
			p.x = -2; p.y = -1;
			v_cp.push_back(p);
			p.x = -1; p.y = 2;
			v_cp.push_back(p);
			p.x = -2; p.y = 1;
			v_cp.push_back(p);
		}
		break;

		// ���� �¿�.. ��ĭ�� �ǳʼ� 4��
		default:
		{
			p.x = 0; p.y = -3;
			v_cp.push_back(p);
			p.x = 0; p.y = 3;
			v_cp.push_back(p);
			p.x = 3; p.y = 0;
			v_cp.push_back(p);
			p.x = -3; p.y = 0;
			v_cp.push_back(p);
		}
		break;
	}

	TYPE_SECTORPOSITION	tX, tY;
	tX = g_pTopView->PixelToMapX(egInfo.x1);
	tY = g_pTopView->PixelToMapY(egInfo.y1);

	int sX, sY;
	int z  = egInfo.z1;

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);	

	MEffect*	pEffect;
	
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	for (int i=0; i<v_cp.size(); i++)
	{		
		sX = tX + v_cp[i].x;
		sY = tY + v_cp[i].y;
		
		pEffect = new MEffect(bltType);
		
		pEffect->SetFrameID( frameID, maxFrame );	

		//pEffect->SetPixelPosition(sx, sy, z);		// Sector ��ǥ		
		pEffect->SetPosition( sX, sY );
		pEffect->SetZ( z );			
		pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
		pEffect->SetCount( egInfo.count , egInfo.linkCount );			// ���ӵǴ� Frame

		// ���� ����
		pEffect->SetDirection( egInfo.direction );

		// ����
		pEffect->SetPower(egInfo.power);

		// Zone�� �߰��Ѵ�.
		bool bAdd = g_pZone->AddEffect( pEffect );

		if (bAdd)
		{
			// ó������ �߰��� effect�� ���ؼ� link����
			if (!bOK)
			{
				pEffect->SetLink( egInfo.nActionInfo, egInfo.pEffectTarget );

				bOK = true;
			}		
			// ó������ �߰��ȰŴ� �ƴ����� ����� �� ���
			else
			{
				// 1�� �̿ܿ��� ���� Effect ���� ������ ����..
				// ������ effect 4������ �� ���� effect�� �����ϸ� �ȵǱ� �����̴�.
				pEffect->SetLink( egInfo.nActionInfo, NULL );
			}
		}

		//---------------------------------------------
		// �ݺ��Ǵ� frame�̸�..
		// ���� frame�� �ٸ��� �Ѵ�.
		//---------------------------------------------
		if (bAdd && repeatFrame)
		{
			int num = rand() % maxFrame;
			
			for (int nf=0; nf<num; nf++)
			{
				pEffect->NextFrame();
			}
		}

		//
		//sx += cx;
		//sy += cy;

		// ���� �׸�
		if (est>=EFFECTSPRITETYPE_BLOODY_WALL_1
			&& est<=EFFECTSPRITETYPE_BLOODY_WALL_3)
		{
			if (++est > EFFECTSPRITETYPE_BLOODY_WALL_3)
			{
				est = EFFECTSPRITETYPE_BLOODY_WALL_1;
			}
		}

		frameID	= (*g_pEffectSpriteTypeTable)[est].FrameID;
		maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);	
	}

	return bOK;
}
