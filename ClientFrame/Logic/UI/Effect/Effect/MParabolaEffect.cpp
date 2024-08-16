//----------------------------------------------------------------------
// MParabolaEffect.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include <math.h>
#include "MTopView.h"
#include "MLinearEffect.h"
#include "MParabolaEffect.h"
#include "MathTable.h"
#include "EffectSpriteTypeDef.h"
#include "MEffectSpriteTypeTable.h"
#include "PacketFunction.h"
#include "SkillDef.h"
//----------------------------------------------------------------------
// 
// constructor/destructor
//
//----------------------------------------------------------------------

MParabolaEffect::MParabolaEffect(BYTE bltType)
: MLinearEffect(bltType)
{
	//m_EffectType	= EFFECT_PARABOLA;

	m_RadCurrent = 0;
	m_RadStep = 0;
	m_TargetTileX = 0;
	m_TargetTileY = 0;
}

MParabolaEffect::~MParabolaEffect()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// ��ǥ�� �����Ѵ�.
//----------------------------------------------------------------------
void		
MParabolaEffect::SetTarget(int x, int y, int z, WORD speed)
{
	// ��ǥ ����..
	MLinearEffect::SetTarget(x, y, z, speed);

	//--------------------------------------------------
	// Grenade�� �� �������� Z���� ���̰� �޶�����.
	//--------------------------------------------------
	int steps = (int)m_Len / speed;	// ��� �������� ��ǥ �����ΰ�?

	//m_RadStep = (float)PI / steps;	// �Ź� �����϶����� �޶����� theta
	m_RadStep = MathTable::FPI / (float)steps;
	m_RadCurrent = 0;
}
void
MParabolaEffect::MakeCannonadeSmoke()
{
	MEffect*	pEffect;
	BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CANNONADE_SMOKE].BltType;
	TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CANNONADE_SMOKE].FrameID;
	int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);
	//---------------------------------------------
	// Effect ����
	//---------------------------------------------
	pEffect = new MEffect(bltType);
			
	pEffect->SetFrameID( frameID, maxFrame );	

	pEffect->SetPixelPosition( m_PixelX, m_PixelY, m_PixelZ);
	pEffect->SetZ(m_PixelZ);			
//	pEffect->SetStepPixel(egInfo.step);		// ������ ���������� ������, ���� Effect�� ���ؼ� �������ش�.
	pEffect->SetCount( 9 );			// ���ӵǴ� Frame
			
	// ���� ����
	pEffect->SetDirection( GetDirection());
	pEffect->SetMulti(true);
	g_pZone->AddEffect( pEffect,10);
	return;
}

//----------------------------------------------------------------------
// Move
//----------------------------------------------------------------------
// �� �������� StepX~Z�� �޶�����.
//----------------------------------------------------------------------
bool
MParabolaEffect::Update()
{	
	if (g_CurrentFrame < m_EndFrame)
	{
		//--------------------------------
		// Pixel ��ǥ�� �ٲ۴�.
		//--------------------------------
		// ������ ���⿡ ���ؼ� Step��ŭ �̵����ش�.
		m_PixelX += m_StepX;
		m_PixelY += m_StepY;
		m_PixelZ += m_StepZ;

		m_RadCurrent += m_RadStep;			// ���� Radian�� ��ȭ

		m_PixelZ += ((MathTable::FCos(m_RadCurrent)*m_StepPixel)>>16);	// Z��ǥ ��ȭ

		
		if(GetActionInfo() == SKILL_CANNONADE)
			MakeCannonadeSmoke();
		//------------------------------------------
		// �� ������ ��츦 �����غ��� �Ѵ�.
		//------------------------------------------
		if (fabs(m_PixelX-m_TargetX)<m_StepPixel &&
			fabs(m_PixelY-m_TargetY)<m_StepPixel &&
			//fabs(m_PixelZ-m_TargetZ)<m_StepPixel &&
			m_RadCurrent >= MathTable::FPI			
			|| m_PixelZ < m_TargetZ	// �ٴڿ� ������ ���.
			
			)
		{
			m_PixelX = (float)m_TargetX;
			m_PixelY = (float)m_TargetY;
			m_PixelZ = (float)m_TargetZ;

			m_StepX = 0;
			m_StepY = 0;
			m_StepZ = 0;

			//------------------------------------------
			// �� ������ �ʿ䰡 ���� ����̴�.			
			//------------------------------------------
			m_EndFrame = 0;

		//	if(GetFrameID() == EFFECTSPRITETYPE_CANNONADE_BALL)
			if(GetActionInfo() == SKILL_CANNONADE)
			{
				ExecuteActionInfoFromMainNode(RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB,m_TargetTileX, m_TargetTileY, 0,0,	0,	
						m_TargetTileX, m_TargetTileY, 0, 1000, NULL, false);		

			}
			return false;
		}

		//--------------------------------
		// Sector ��ǥ�� �����.
		//--------------------------------
		AffectPosition();

		//--------------------------------
		// Frame�� �ٲ��ش�.
		//--------------------------------
		NextFrame();

		if (m_BltType == BLT_EFFECT)
		{
			m_Light = g_pTopView->m_EffectAlphaFPK[m_FrameID][m_Direction][m_CurrentFrame].GetLight();
		}

		//--------------------------------
		// Counter�� �ϳ� ���δ�.
		//--------------------------------
		//m_Count--;

		return true;
	}

	// ��~

	return false;

}
