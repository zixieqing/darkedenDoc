//----------------------------------------------------------------------
// MMovingEffect.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MEffect.h"
#include "MMovingEffect.h"
#include "MTopView.h"

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------

MMovingEffect::MMovingEffect(BYTE bltType)
: MEffect(bltType)
{
	//m_ObjectType	= TYPE_EFFECT;

	//m_EffectType	= EFFECT_MOVING;

}

MMovingEffect::~MMovingEffect()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Update
//----------------------------------------------------------------------
// m_Count�� 0�϶����� -1 ���ָ鼭 Frame�� �ٲ۴�.
//----------------------------------------------------------------------
bool
MMovingEffect::Update()
{
	if (g_CurrentFrame < m_EndFrame)
	{
		// Frame�� �ٲ��ش�.
		NextFrame();
		
		if (m_BltType == BLT_EFFECT)
		{
			m_Light = g_pTopView->m_EffectAlphaFPK[m_FrameID][m_Direction][m_CurrentFrame].GetLight();
		}

		// Sector ��ǥ ����
		AffectPosition();
		
		return true;
	}
	
	return false;
}