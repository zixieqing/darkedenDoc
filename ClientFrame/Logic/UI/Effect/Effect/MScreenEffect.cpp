//----------------------------------------------------------------------
// MScreenEffect.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MEffect.h"
#include "MScreenEffect.h"
#include "MTopView.h"

//----------------------------------------------------------------------
// static
//----------------------------------------------------------------------
int		MScreenEffect::m_ScreenBasisX	= 0;
int		MScreenEffect::m_ScreenBasisY	= 0;


//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------

MScreenEffect::MScreenEffect(BYTE bltType)
: MEffect(bltType)
{
	//m_ObjectType	= TYPE_EFFECT;

	//m_EffectType	= EFFECT_SCREEN;

}

MScreenEffect::~MScreenEffect()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Set Screen Basis
//----------------------------------------------------------------------
// ȭ�� ������
//----------------------------------------------------------------------
void		
MScreenEffect::SetScreenBasis(int bx, int by)
{
	m_ScreenBasisX = bx;
	m_ScreenBasisY = by;
}

//----------------------------------------------------------------------
// Set Screen Position
//----------------------------------------------------------------------
// ȭ�鿡���� ��ǥ
//----------------------------------------------------------------------
void		
MScreenEffect::SetScreenPosition(int x, int y)
{
	// ��ǥ �������� �����Ѵ�.
	m_PixelX = x - m_ScreenBasisX;
	m_PixelY = y - m_ScreenBasisY;
}

//----------------------------------------------------------------------
// Update
//----------------------------------------------------------------------
// m_Count�� 0�϶����� -1 ���ָ鼭 Frame�� �ٲ۴�.
//----------------------------------------------------------------------
bool
MScreenEffect::Update()
{
	if (g_CurrentFrame < m_EndFrame)
	{
		// Frame�� �ٲ��ش�.
		NextFrame();
		
		if (m_BltType == BLT_EFFECT)
		{
			m_Light = g_pTopView->m_EffectAlphaFPK[m_FrameID][m_Direction][m_CurrentFrame].GetLight();
		}
		
		return true;
	}
	
	return false;
}