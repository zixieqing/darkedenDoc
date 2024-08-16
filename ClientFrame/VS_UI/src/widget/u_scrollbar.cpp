// u_scrollbar.cpp
#include "client_PCH.h"
#include "u_scrollbar.h"
#include <assert.h>


Scrollbar::Scrollbar()
{
	Init();
}

Scrollbar::~Scrollbar()
{

}

//-----------------------------------------------------------------------------
// Init
//
// 
//-----------------------------------------------------------------------------
void Scrollbar::Init()
{
	m_dw_amount_for_scroll = 0;
	m_dw_amount_to_scroll = 0;
}

//-----------------------------------------------------------------------------
// IncreaseAmountToScroll
//
// m_dw_amount_to_scroll�� 1 ������Ų��.
//-----------------------------------------------------------------------------
void Scrollbar::IncreaseAmountToScroll()
{
	if (m_dw_amount_to_scroll < m_dw_amount_for_scroll)
		m_dw_amount_to_scroll++;
}

//-----------------------------------------------------------------------------
// DecreaseAmountToScroll
//
// m_dw_amount_to_scroll�� 1 ���ҽ�Ų��.
//-----------------------------------------------------------------------------
void Scrollbar::DecreaseAmountToScroll()
{
	if (m_dw_amount_to_scroll > 0)
		m_dw_amount_to_scroll--;
}

//-----------------------------------------------------------------------------
// SetAmountForScroll
//
// m_dw_amount_to_scroll�� �״�� ���д�. �ܺο��� �˾Ƽ� �ؾ��Ѵ�.
//-----------------------------------------------------------------------------
void Scrollbar::SetAmountForScroll(DWORD amount_for_scroll)
{
//	assert(m_dw_amount_to_scroll <= amount_for_scroll);

	m_dw_amount_for_scroll = amount_for_scroll;
}

//-----------------------------------------------------------------------------
// SetAmountToScroll
//
// 
//-----------------------------------------------------------------------------
void Scrollbar::SetAmountToScroll(DWORD amount_to_scroll)
{
	assert(amount_to_scroll <= m_dw_amount_for_scroll);

	m_dw_amount_to_scroll = amount_to_scroll;
}

//-----------------------------------------------------------------------------
// SetAmountToScrollByPercent
//
// percent�� scroll�� ���� ���Ѵ�.
//-----------------------------------------------------------------------------
void Scrollbar::SetAmountToScrollByPercent(double percent)
{
	assert(percent <= PERCENTAGE);

	double val = Proportion(percent, PERCENTAGE, m_dw_amount_for_scroll);

	// �Ҽ� ù° �ڸ� �ݿø��Ѵ�.
	val += 0.5;
	m_dw_amount_to_scroll = (DWORD)floor(val);
}

//-----------------------------------------------------------------------------
// NoScroll
//
// scroll�� ���� �ʾ����� true�� ��ȯ�ϰ�, �׷��� ������ false�� ��ȯ�Ѵ�.
//-----------------------------------------------------------------------------
bool Scrollbar::NoScroll()
{
	return (GetPercentToScroll() == 0.);
}

//-----------------------------------------------------------------------------
// GetPercentToScroll
//
// scroll�� ���� percent�� �ٲپ� ��ȯ�Ѵ�.
//
// �������� ���Ͽ� double type���� �Ѵ�.
//-----------------------------------------------------------------------------
int Scrollbar::GetPercentToScroll() const
{
	assert(m_dw_amount_to_scroll <= m_dw_amount_for_scroll);

	double percent = Percentage(m_dw_amount_to_scroll, m_dw_amount_for_scroll);

	// �Ҽ� ù° �ڸ� �ݿø��Ѵ�.
	percent += 0.5;
	int integer = (int)floor(percent);

	return integer;
}

//-----------------------------------------------------------------------------
// GetAmountToScroll
//
// 
//-----------------------------------------------------------------------------
DWORD	Scrollbar::GetAmountToScroll() const
{
	return m_dw_amount_to_scroll;
}

//-----------------------------------------------------------------------------
// GetAmountForScroll
//
// 
//-----------------------------------------------------------------------------
DWORD	Scrollbar::GetAmountForScroll() const
{
	return m_dw_amount_for_scroll;
}
