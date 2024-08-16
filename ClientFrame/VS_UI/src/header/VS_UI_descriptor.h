/*-----------------------------------------------------------------------------

	VS_UI_Descriptor.h

	Descriptor class.

	��ü�� ���� ���� �Ǵ� ������ ����ϴ� ��ü�̴�.

	2000.7.3. KJTINC
	2000.12.9.

-----------------------------------------------------------------------------*/

#ifndef __VS_UI_DESCRIPTOR_H__
#define __VS_UI_DESCRIPTOR_H__

#include "VS_UI_Base.h"

struct DESCRIBED_UNIT
{
	id_t		id;
	bool		bl_immediate; // immediate(true)/delay(false)
	void		(*fp_rect_calculator)(void (*fp_show)(Rect, void *, long, long), int, int, void *, long, long);
	void		(*fp_show)(Rect, void *, long, long);
};

//-----------------------------------------------------------------------------
// class DescriptorManager
//
// > tool-tip�� ���� �ϳ��� ���� info-box�� description�̶� �����Ѵ�.
//
// DESCRIBED_UNIT�� �ϳ��� ���ϵ� description�� ���� group(descriptor)�� �ǹ��Ѵ�.
// � ���� ��� description�Ǳ� ���ϰ�����, � ���� delay�� ���Ѵ�.
// �� �̷��� Ư¡�� �ϳ��� group�� ���� �� �ִ� ���̴�. �̰��� �׵鸸�� format����
// ����� �� �ְ�, rect�� ����� �� �ִ�.
//
// ����>
//				AddDescribeUnit���� �߰��Ѵ�. �ű⿡ ù��°���ڷ� ������ id�� group��
//				�����ϴµ� �ʿ��ϴ�.
//				Set�� �ϸ� description�� ��µ� �غ� ��� �����Ѵ�. rect�� ����ϰ�
//				�� ������ ��� m_fp_show_param�� �����ϸ� �ش� show fp ptr�� m_fp_show��
//				�����ϹǷν� �ٷ� �������� �Ѵ�.
//
//				description�� �����ϱ� ���ؼ��� �ܼ��� unset�� �����ϸ� �ȴ�.
//-----------------------------------------------------------------------------
class DescriptorManager : public SimpleDataList<DESCRIBED_UNIT *>
{
private:
	//
	// m_fp_show
	//
	// ���� ����� descrition show ptr.
	// �̰��� null�� �ƴ� ������ ��� ����ؾ� �Ѵ�.
	//
	void							(*m_fp_show)(Rect, void *, long, long);

	struct FP_SHOW_PARAM
	{
		Rect						rect;
		void *					void_ptr;
		long						left;
		long						right;
	};

	FP_SHOW_PARAM				m_fp_show_param;

public:
	DescriptorManager();
	~DescriptorManager();

	void	Set(id_t id, int x, int y, void * void_ptr, long left=0, long right=0);
	//void	Unset();

	// ���� ������ pointer�� ��츸 �����Ѵ�.
	void	Unset(void* pPtr=NULL);	// by sigi

	void	Show();

	void	AddDescribedUnit(id_t id, void (*fp_rect_calculator)(void (*fp_show)(Rect, void *, long, long), int, int, void *, long, long), void (*fp_show)(Rect, void *, long, long), bool bl_immediate=true);
	void	RectCalculationFinished(void (*fp_show)(Rect, void *, long, long), Rect rect, void * void_ptr, long left, long right);
};

extern DescriptorManager	g_descriptor_manager;

#endif