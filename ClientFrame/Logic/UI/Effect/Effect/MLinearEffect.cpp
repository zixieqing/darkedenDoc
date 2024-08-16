//----------------------------------------------------------------------
// MLinearEffect.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include <math.h>
#include "MTopView.h"
#include "MTypeDef.h"
#include "MMovingEffect.h"
#include "MLinearEffect.h"
#include "SkillDef.h"
//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------

MLinearEffect::MLinearEffect(BYTE bltType)
: MMovingEffect(bltType)
{
	//m_ObjectType	= TYPE_EFFECT;
	//m_EffectType	= EFFECT_LINEAR;

	m_TargetX		= 0;
	m_TargetY		= 0;
	m_TargetZ		= 0;

	// �� ���� �̵��ϴ� pixel��
	m_StepX			= 0;
	m_StepY			= 0;
	m_StepZ			= 0;
	m_StepPixel		= 0;

	m_Len			= 0;
}

MLinearEffect::~MLinearEffect()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Set Target
//----------------------------------------------------------------------
// �Է¹��� ��ǥ ��ġ�� ���ؼ�
// ���� ��ġ�κ��� ��ǥ ��ġ���� �̵��ϴµ� ���� 
// speed��ŭ �̵��Ѵ�.
//----------------------------------------------------------------------
void
MLinearEffect::SetTarget(int x, int y, int z, WORD stepPixel)
{
	//--------------------------------------------------
	// ��ǥ ��ġ ����
	//--------------------------------------------------
	m_TargetX = x;
	m_TargetY = y;
	m_TargetZ = z;

	//--------------------------------------------------
	// ������ ���������� pixel���� ����Ѵ�.
	//--------------------------------------------------
	float	moveX = m_TargetX - m_PixelX,
			moveY = m_TargetY - m_PixelY,
			moveZ = m_TargetZ - m_PixelZ;


	// �̵��ϴ� ���� ����
	m_Direction = MTopView::GetDirectionToPosition((int)m_PixelX, (int)m_PixelY, (int)m_TargetX, (int)m_TargetY);

	//--------------------------------------------------
	// �ѹ��� �̵��ϴ� pixel��
	//--------------------------------------------------
	// �̵��ؾ��ϴ� ����
	m_Len = (float)sqrt(moveX*moveX + moveY*moveY + moveZ*moveZ);

	if (m_Len==0)
	{
		m_StepX = 0;
		m_StepY = 0;
		m_StepZ = 0;
	}
	else
	{
		// ���� ���̷� ������ �Ѵ�.
		m_StepX = moveX/m_Len * stepPixel;
		m_StepY = moveY/m_Len * stepPixel;
		m_StepZ = moveZ/m_Len * stepPixel;
	}


	m_StepPixel = stepPixel;
}

//----------------------------------------------------------------------
// Update
//----------------------------------------------------------------------
// m_Count�� 0�϶����� -1 ���ָ鼭 Frame�� �ٲ۴�.
// Pixel��ǥ �̵��� �ؾ��Ѵ�. 
// �翬�� Sector��ǥ�� ����� �Ѵ�.
//
// ��ǥ Pixel��ġ���� ���� Pixel�� �̵��ϰ� �ȴ�.
//
// return 
//    true  - ��� �����δ�...
//    false - �̹��� ������ �������̶�� �ǹ�
//----------------------------------------------------------------------
bool
MLinearEffect::Update()
{
	// ��� Update�ص� �Ǵ°�?
	if (g_CurrentFrame < m_EndFrame)
	{
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
			// 2004, 12, 30, sobeit add start
			if(GetActionInfo() == SKILL_HALO) // 0.5�ʰ� ���� ��ġ�� ���
			{
				if(m_EndFrame>g_CurrentFrame+8)
					m_EndFrame = g_CurrentFrame+8;
			}
			else
			// 2004, 12, 30, sobeit add end
			{	
				m_EndFrame = 0;
				return false;
			}
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
