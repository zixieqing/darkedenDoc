/*-----------------------------------------------------------------------------

	pi_core.h

	Program Interface core.

	2000.9.18. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __PI_CORE_H__
#define __PI_CORE_H__

#include "SimpleDataList.h"

//-----------------------------------------------------------------------------
// PI_Processor
//
// Object start/finish/process.
//
// <����>
//
// �̰��� ������ �ʰ� ����Ǵ� object�̴�. Start�� object�� ������ �˸���. ��, 
// �̶����� Process�� ����ȴ�. ���� object�� �ʱ�ȭ�� �����ϴ� ���ҵ� �Ѵ�.
// Finish�� Process�� �����Ѵ�.
//-----------------------------------------------------------------------------
class PI_Processor
{
private:
	bool							m_bl_running;

public:
	//
	// constructor/destructor�� object�� ź��/������ ����ȴٸ�, 
	// �̰͵��� �װ��� ������ �����ϰ� ������ ���̴�. �̰��� object�� ���۰� ����
	// ������ interface�̴�.
	//
	// Finish()�� ������ Process�� �׸��ΰ� �� ���̴�. override�Ͽ� ����� ������
	// �ݵ�� ���������� �Ѵ�.
	//
	// !Process�� �����ؼ� ������Ű�� ������� Start(), Finish()�� �ſ� �߿��ϴ�.
	//
	virtual void	Start() { m_bl_running = true; }
	virtual void	Finish() { m_bl_running = false; }

	//
	// BaseInterface�� ��ӹ��� object�� instance�� ������ �� �� pointer�� ��������ν�
	// background���� ���������� Process()�� �ڵ����� ����ȴ�. Start()�� ����ǰ����
	// ����Ǹ�, Finish()�� ����Ǹ� ������� �ʴ´�.
	//
	virtual void	Process() {}; // no pure

	bool	Running() const { return m_bl_running; }

	PI_Processor();
	~PI_Processor();
};

//-----------------------------------------------------------------------------
// PI_ProcessRunner
//
//
//-----------------------------------------------------------------------------
class PI_ProcessRunner : public SimpleDataList<PI_Processor *>
{
public:
	void	Process();
};

//-----------------------------------------------------------------------------
// PI_Visual
//
//
//-----------------------------------------------------------------------------
class PI_Visual : public PI_Processor
{
public:
	virtual void	Show() = 0;
};

// [note] PI_Control�� �������� �ʴ´�. �ֳ��ϸ� �̰��� ��Ȳ�� ���� �޶��� �� �ִ� ��Ұ�
//			 ���� �����̴�.

extern PI_ProcessRunner *	gpC_process_runner;

#endif