/*-----------------------------------------------------------------------------

	u_scrollbar.h

	Scrollbar Widget.

	2000.6.7. KJTINC
	2000.7.29.

-----------------------------------------------------------------------------*/

#ifndef __U_SCROLLBAR_H__
#define __U_SCROLLBAR_H__

#include "Basics.h"
#include "Mother.h"

//----------------------------------------------------------------------------
// Widget Scrollbar
//
// Design:
//				scroll�� '���'�� scroll��Ű�� '��ġ'�� �����Ѵ�. '���'�� ������
//				�ʴ� �κ� ��, �̷��� scroll�Ǿ� ���� �κ��̴�.
//
//				scroll�� ��ŭ�Ǿ����� �� �� �־�� �Ѵ�.
//				'��ġ'�� ��� ���� ��Ȯ�� �˾ƾ� �Ѵ�. '���'�� ��(amount)���ν�
//				'�������'�� ��Ÿ���� percent�� ��Ÿ�� �� �ִ�.
//
//				�� Widget�� '���'�� ���� �˰� ������, '���'�� ��ȭ��ų �� �ִ�
//				��ȭ���� �����Ѵ�.
//----------------------------------------------------------------------------
class Scrollbar
{
private:

protected:
	DWORD				m_dw_amount_for_scroll; // '���'
	DWORD				m_dw_amount_to_scroll;	// scroll�� amount (x <= m_dw_amount_for_scroll)

public:
	Scrollbar();
	virtual ~Scrollbar();

	void		Init();

	//---------------------------------------
	// Set
	//---------------------------------------
	void		SetAmountForScroll(DWORD amount_for_scroll);
	void		SetAmountToScroll(DWORD amount_to_scroll);
	void		SetAmountToScrollByPercent(double percent);
	void		IncreaseAmountToScroll();
	void		DecreaseAmountToScroll();

	//---------------------------------------
	// Get
	//---------------------------------------
	bool		NoScroll();
	int		GetPercentToScroll() const;
	DWORD		GetAmountToScroll() const;
	DWORD		GetAmountForScroll() const;
};

#endif
