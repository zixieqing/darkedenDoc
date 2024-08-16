//----------------------------------------------------------------------
// MGuidanceEffect.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include <math.h>
#include "MLinearEffect.h"
#include "MGuidanceEffect.h"
#include "MCreature.h"
#include "MZone.h"
#include "MTopView.h"

//----------------------------------------------------------------------
// 
// constructor/destructor
//
//----------------------------------------------------------------------

MGuidanceEffect::MGuidanceEffect(BYTE bltType)
: MLinearEffect(bltType)
{
	//m_EffectType	= EFFECT_GUIDANCE;

	m_CreatureID	= OBJECTID_NULL;
}

MGuidanceEffect::~MGuidanceEffect()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Move
//----------------------------------------------------------------------
// �� �������� StepX~Z�� �޶�����.
//----------------------------------------------------------------------
void				
MGuidanceEffect::SetTraceCreatureID(TYPE_OBJECTID id)
{ 
	m_CreatureID = id; 

	if (id!=OBJECTID_NULL)
	{
		TraceCreature();	
	}
}

//----------------------------------------------------------------------
// TraceCreature
//----------------------------------------------------------------------
bool
MGuidanceEffect::TraceCreature()
{
	MCreature* pCreature = g_pZone->GetCreature( m_CreatureID );

	// Creature�� ������� ���..
	if (pCreature == NULL)
	{
		m_CreatureID = OBJECTID_NULL;
		m_EndFrame = 0;
		return false;
	}

	// ������ ��ǥ�� �о�´�.
	POINT point;// = MTopView::MapToPixel(pCreature->GetX(), pCreature->GetY());
	//point.x += pCreature->GetSX();
	//point.y += pCreature->GetSY();	
	point.x = pCreature->GetPixelX();
	point.y = pCreature->GetPixelY();

	// ���ο� ������ ����
	MLinearEffect::SetTarget( point.x, point.y, 
								pCreature->GetZ(),
								m_StepPixel);

	return true;
}

//----------------------------------------------------------------------
// Update
//----------------------------------------------------------------------
bool
MGuidanceEffect::Update()
{	
	if (g_CurrentFrame < m_EndFrame)
	{
		if (!TraceCreature())
			return false;

		//--------------------------------
		// Pixel ��ǥ�� �ٲ۴�.
		//--------------------------------
		// ������ ���⿡ ���ؼ� Step��ŭ �̵����ش�.
		m_PixelX += m_StepX;
		m_PixelY += m_StepY;
		m_PixelZ += m_StepZ;

		//------------------------------------------
		// �� ������ ��츦 �����غ��� �Ѵ�.
		//------------------------------------------
		if (fabs(m_PixelX-m_TargetX)<m_StepPixel &&
			fabs(m_PixelY-m_TargetY)<m_StepPixel &&
			fabs(m_PixelZ-m_TargetZ)<m_StepPixel)
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
