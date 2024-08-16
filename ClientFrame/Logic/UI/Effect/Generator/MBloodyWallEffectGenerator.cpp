//----------------------------------------------------------------------
// MBloodyWallEffectGenerator.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MBloodyWallEffectGenerator.h"
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
//MBloodyWallEffectGenerator	g_BloodyWallEffectGenerator;

//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
bool
MBloodyWallEffectGenerator::Generate( const EFFECTGENERATOR_INFO& egInfo )
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

	//---------------------------------------------
	// pixel��ǥ�� Map�� ��ǥ�� �ٲ��ش�.
	//---------------------------------------------
	int	tx, ty;
	
	tx = egInfo.x1;
	ty = egInfo.y1;

	// (sX0, sY0)���� (sX1, sY1)�� �ٶ󺸴� ������ ����.
	int lookDirection = egInfo.direction;//MTopView::GetDirectionToPosition(sX0, sY0, sX1, sY1);

	//---------------------------------------------
	// ���⿡ ����... { ���ۺ���X, ���ۺ���Y, ��ȭpixelX, ��ȭpixelY }
	//---------------------------------------------
	// 5�� ���
	/*
	const int dirValue[8][4] = { 
		{		0,	-12*2,		0,		12 },		// left���� up
		{	-24*2,	-12*2,		24,		12 },		// leftdown
		{	-24*2,		0,		24,		0 },		// down
		{	24*2,	-12*2,		-24,	12 },		// rightdown
		{		0,	-24*2,		0,		24 },		// right
		{	-24*2,	-12*2,		24,		12 },		// rightup
		{	-24*2,		0,		24,		0 },		// up
		{	-24*2,	12*2,		24,		-12 }		// leftup
	};	

	//---------------------------------------------
	// ���� ��
	//---------------------------------------------
	int sx = tx + dirValue[lookDirection][0];
	int sy = ty + dirValue[lookDirection][1];
	int cx = dirValue[lookDirection][2];
	int cy = dirValue[lookDirection][3];
	int z  = egInfo.z0;
	*/

	const POINT dirValue[8][5] =
	{
		{ { 0, -2 }, { 0, -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 } },	// left
		{ { -1, -1 }, { -1, 0 }, { 0, 0 }, { 0, 1 }, { 1, 1 } },		// leftdown
		{ { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 } },			// down
		{ { 1, -1 }, { 1, 0 }, { 0, 0 }, { 0, 1 }, { -1, 1 } },			// rightdown
		{ { 0, -2 }, { 0, -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 } },			// right
		{ { 1, 1 }, { 1, 0 }, { 0, 0 }, { 0, -1 }, { -1, -1 } },		// rightup
		{ { -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 } },	// up
		{ { 1, -1 }, { 0, -1 }, { 0, 0 }, { -1, 0 }, { -1, 1 } },	// leftup
	};

	TYPE_SECTORPOSITION	tX, tY;
	tX = g_pTopView->PixelToMapX(egInfo.x0);
	tY = g_pTopView->PixelToMapY(egInfo.y0);

	int sX, sY;
	int sx, sy;
	int z  = egInfo.z0;

	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);	

	MEffect*	pEffect;
	
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	for (int i=0; i<5; i++)
	{		
		sX = tX + dirValue[lookDirection][i].x;
		sY = tY + dirValue[lookDirection][i].y;
		sx = tx + dirValue[lookDirection][i].x * TILE_X;
		sy = ty + dirValue[lookDirection][i].y * TILE_Y;

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
				// ���� Effect ���� ����
				if (egInfo.pEffectTarget == NULL)
				{
					pEffect->SetLink( egInfo.nActionInfo, NULL );
				}
				else
				{
					MEffectTarget* pEffectTarget2 = new MEffectTarget(*egInfo.pEffectTarget);
					pEffect->SetLink( egInfo.nActionInfo, pEffectTarget2 );
					pEffectTarget2->Set( sx, sy, z, egInfo.creatureID );
				}			
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
