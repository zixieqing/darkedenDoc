/*-----------------------------------------------------------------------------

	u_button.h

	Button Widget.

	2000.6.7. KJTINC
	2000.8.4.

-----------------------------------------------------------------------------*/

#ifndef __U_BUTTON_H__
#define __U_BUTTON_H__

#include "Basics.h"

//----------------------------------------------------------------------------
// Widget Button
//
// Design:
//				Button�� ���¸� ���� rect�̴�.
//
//				Button�� ������ ���� event�� �߻��Ѵ�.
//
//				(1) button������ mouse move�� ���� ��/���� ��.
//				(2) button������ ���� ��/�� ��.
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Class ButtonBase
//
// ��ư �� ��ü �� Single Button Object.
//----------------------------------------------------------------------------
class ButtonBase : public Rect
{
private:
	//---------------------------------------
	// Private data
	//---------------------------------------
	bool		m_bl_focused; // button focus state
	bool		m_bl_pressed; // button press state

public:
	ButtonBase();
	virtual ~ButtonBase();

	//---------------------------------------
	// Set
	//---------------------------------------
	void	FocusOn();
	void	FocusOff();
	void	PressDown();
	void	PressUp();
	virtual void	InitState();

	//---------------------------------------
	// Get
	//---------------------------------------
	bool	GetFocusState() const;
	bool	GetPressState() const;
};

//----------------------------------------------------------------------------
// Exec (abstract class)
//
// Button execution interface.
//
// Button�� ����ϴ� class�� �̰��� ��ӹ޾ƾ� �Ѵ�. �׷��� Button�� �����ϸ鼭
// this �����͸� �־� Button������ ���� interface�� ���� exec�� �� �� �ִ�.
//----------------------------------------------------------------------------
class Exec
{
public:
	virtual void Run(id_t id) = 0;
};

//----------------------------------------------------------------------------
// Class Button (abstract class)
//
// Button condition change & execution.
//
// �������� Button Widget.
// �̰��� �Ϲ����� Button�� ������ �����Ѵ�. �̰��� ��¿� ���ؼ��� ��������
// ������, �����������ν� Show()�� ���´�.
//
// [2000.9.25.]
//
// VS UI Project���� Button�� Button group���� �־� �ѹ��� ó���� �� �ֵ��� �ϰ�
// ���� ��µ� ���������� ������� �� �ڽ��� ��ºκ��� ���� �� �ֵ��� �ϱ� ���ؼ�
// pure virtual Show�� ���ʿ��Ͽ���. �׷��� �װ��� �� �ʿ��ϸ� ��¸޼ҵ带
// ������ �߰��ϴ� ������� ����ϱ�� �ϰ�, Button�� instanceȭ �� �� �ֵ��� �ϱ� 
// ���ؼ� pure virtual�� ���� �ʴ´�.
//----------------------------------------------------------------------------
class Button : public ButtonBase
{
public:
	enum ClickOption // Run()�� ���� �����ϴ°�?
	{
		RUN_WHEN_PUSHUP,
		RUN_WHEN_PUSH,
	};

private:
	Exec *						m_pC_exec_handler;	// exec handler
	id_t							m_id;						// own exec id
	ClickOption					m_click_option;

	void	Run();

public:
	//
	// �� ���� ������� �ʱ�ȭ�� �� �ִ�.
	//
	// (1) Button * p = new Button(x, y, w, h, id, this);
	// (2) Button p;
	//		 p.Set(x, y, w, h);
	//		 p.SetID(id);
	//		 p.SetExecHandler(this);
	//		 p.SetClickOption(RUN_WHEN_PUSH);
	//
	Button(int _x, int _y, int _w, int _h, id_t id, Exec * pC_exec_handler, ClickOption co=Button::RUN_WHEN_PUSHUP);
	Button();
	virtual ~Button();

	// rect�� XY(), Set()�� �ִ�.
	// ���� ButtonBase�� InitState()�� ���¸� �ʱ�ȭ�Ѵ�.

	void	SetID(id_t id);
	void	SetExecHandler(Exec * pC_exec_handler);
	void	SetClickOption(ClickOption co) { m_click_option = co; }

	//
	// Button�� ����� ��쿡 ������ MouseControl()�� Event call �Ӽ��� ����
	// ���ο� ����� ������ �� �ִ�. ���� virtual�� �Ѵ�.
	//
	virtual bool	MouseControl(UINT message, int _x, int _y);
	//virtual void	Show() = 0;

	id_t	GetID() const { return m_id; }
};

//-----------------------------------------------------------------------------
// EventButton (abstract class)
//
// NormalButton�� �⺻�� ������, Mouse�Է¸��� ������� event�� �߻����� ����
// �װ��� �� �� �ֵ��� �Ѵ�. �̰��� ������ ������ mouse pointer�� ���ٴ��
// animation�Ǵ� animation button�� ���� ���̴�.
//-----------------------------------------------------------------------------
class EventButton : public Button
{
protected:
	bool			m_bl_prev_focus; // static���� ���� �ʴ´�.

public:
	EventButton(int _x, int _y, int _w, int _h, id_t id, Exec * pC_exec_handler, Button::ClickOption co=Button::RUN_WHEN_PUSHUP);
	virtual ~EventButton();

	virtual void	EventFocusOn() {}
	virtual void	EventFocusOff() {}
	virtual void	EventPressDown() {}
	virtual void	EventPressUp() {}

	bool	MouseControl(UINT message, int _x, int _y);
	void	InitState();
};

#endif