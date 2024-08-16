//----------------------------------------------------------------------
// MMovingEffect.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MEffect.h"
#include "MathTable.h"
#include "MSkipEffect.h"
#include "MTopView.h"

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------

MSkipEffect::MSkipEffect(BYTE bltType)
: MEffect(bltType)
{
	m_nSkipValue = 3;
}

MSkipEffect::~MSkipEffect()
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
MSkipEffect::Update()
{
	if (g_CurrentFrame < m_EndFrame-4)
	{
		if((rand()%m_nSkipValue))
			SetDrawSkip(true);
		else
			SetDrawSkip(false);
		
		NextFrame();
	
		if (m_BltType == BLT_EFFECT)
		{
			m_Light = g_pTopView->m_EffectAlphaFPK[m_FrameID][m_Direction][m_CurrentFrame].GetLight();
		}

		return true;
	}
	
	return false;
}