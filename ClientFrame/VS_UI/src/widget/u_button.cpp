// u_button.cpp

#include "client_PCH.h"

#include "u_button.h"

#ifndef _LIB
EventButton *g_EventButton = NULL;
#endif

//-----------------------------------------------------------------------------
// EventButton
//
// 
//-----------------------------------------------------------------------------
EventButton::EventButton(int _x, int _y, int _w, int _h, id_t id, Exec * pC_exec_handler, Button::ClickOption co) :
										Button(_x, _y, _w, _h, id, pC_exec_handler, co)
{
	m_bl_prev_focus = false;
}

EventButton::~EventButton()
{
}

//-----------------------------------------------------------------------------
// InitState
//
// 
//-----------------------------------------------------------------------------
void EventButton::InitState()
{ 
	ButtonBase::InitState();

	m_bl_prev_focus = false; 
}

//-----------------------------------------------------------------------------
// EventButton::MouseControl
//
// �Է��̺�Ʈ�� ���ǵ� method�� �����ϹǷν� �˸���.
//-----------------------------------------------------------------------------
bool EventButton::MouseControl(UINT message, int _x, int _y)
{
	switch (message)
	{
		//
		// M_MOVING
		//
		// focus of/off
		//
		case M_MOVING:
			if (IsInRect(_x, _y))
			{
				if (!m_bl_prev_focus)
				{
					m_bl_prev_focus = true;
					EventFocusOn();
				}
			}
			else if (m_bl_prev_focus)
			{
				m_bl_prev_focus = false;
				EventFocusOff();
			}
			break;

		//
		// M_LEFTBUTTON_DOWN, M_LB_DOUBLECLICK
		//
		// button press down.
		//
		case M_LEFTBUTTON_DOWN:
		case M_LB_DOUBLECLICK:
			if (IsInRect(_x, _y)) 
			{
				m_bl_prev_focus = true; // move focus ���� �� ��츦 �����ؼ�.
				EventPressDown();
			}
			break;

		//
		// M_LEFTBUTTON_UP
		//
		// button press up.
		//
		case M_LEFTBUTTON_UP:
			if (GetFocusState()) // focus: yes
			{
				if (GetPressState()) // press: yes
				{
					EventPressUp();
				}
			}
			break;

#ifndef _LIB
		case M_RIGHTBUTTON_UP:
			if (GetFocusState()) // focus: yes
				g_EventButton = this;
			break;
#endif
	}

	return Button::MouseControl(message, _x, _y); // left up�� GetPressState()�� Ȯ���� �� ����.
}

ButtonBase::ButtonBase()
{
	InitState();
}

ButtonBase::~ButtonBase()
{
#ifndef _LIB
	if(g_EventButton == this)g_EventButton = NULL;
#endif

}

void ButtonBase::InitState()
{
	m_bl_focused = false;
	m_bl_pressed = false;
}

void ButtonBase::FocusOn()
{
	m_bl_focused = true;
}

void ButtonBase::FocusOff()
{
	m_bl_focused = false;
}

void ButtonBase::PressDown()
{
	m_bl_pressed = true;
}

void ButtonBase::PressUp()
{
	m_bl_pressed = false;
}

bool ButtonBase::GetFocusState() const
{
	return m_bl_focused;
}

bool ButtonBase::GetPressState() const
{
	return m_bl_pressed;
}

//-----------------------------------------------------------------------------
// Button (Constructor)
//
// 
//-----------------------------------------------------------------------------
Button::Button(int _x, int _y, int _w, int _h, id_t id, Exec * pC_exec_handler, ClickOption co)
{
	Set(_x, _y, _w, _h);
	m_id = id;
	m_pC_exec_handler = pC_exec_handler;
	m_click_option = co;
}

Button::Button()
{

}

//-----------------------------------------------------------------------------
// ~Button (Destructor)
//
// 
//-----------------------------------------------------------------------------
Button::~Button()
{

}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void Button::Run()
{
	if (m_pC_exec_handler) // set handler?
		m_pC_exec_handler->Run(m_id);
}

void Button::SetExecHandler(Exec * pC_exec_handler)
{
	m_pC_exec_handler = pC_exec_handler;
}

void Button::SetID(id_t id)
{
	m_id = id;
}

//-----------------------------------------------------------------------------
// MouseControl
//
// Button input interface.
// 
// focus, press ���´� ���������� �����Ѵ�. �̰��� ButtonBase���� ������ ��
// �ִ�. button down�̸� false�� ��ȯ�ϰ� �׷��� ������ true�� ��ȯ�Ѵ�.
//
// Example:
//				if (button->MouseControl()) // false�̸� ������ �Է��� ó������ �ʴ´�.
//					if (button->MouseControl())
//						...
//
//
// message�� i_signal.h�� ���ǵǾ� �ִ� ���̴�.
//
// History:
//				[2000.8.5. 3:15pm]
//
//				rect ������ �ִ� �Է��̸� true�� ��ȯ�ϰ�, �׷��������� false�� ��ȯ
//				�ϵ��� �Ͽ��µ�, focus ������ �߻��Ͽ���. �װ��� ������ ���� ���¸�
//				���ؼ� ���ʿ��� ó���� ���ֱ� ���� ���̾���.
//
//				if (m_p_button_ok->MouseControl(message, x, y) == false)
//					if (m_p_button_cancel->MouseControl(message, x, y) == false)
//						...
//
//				�׷��� �̷��� ���� ��, cancel�� focus�� �� ������ ok�� focus�Ǹ�,
//				cancel�� focus�� ��ҵ��� �ʴ´�. ���� Button::MouseControl()����
//				�� ������ ����� ���� �ְ�����, �׷��� ��� �ڵ尡 �ᱹ ���ʿ��ϴٴ�
//				���� �����Ͽ���.
//
//				������ ����, ���� button�� �ٸ� �Ͱ� ��ĥ ��� ��� button�� ����
//				�ȴٴ� ���̴�. ���� ��ġ�� �ʵ��� �Ͽ����Ѵ�. ��ġ�� ���� �߸���
//				���̹Ƿ� Button�� �̰Ϳ� ���� ���� �ȴ�.
//
//
//				[2000.8.5. 3:35pm]
//
//				Window �ȿ� button�� �ְ� �� Window�� mouse�� ��� �̵��� �� �ִ�
//				���̶��, �ݵ�� button�� �Է»��¸� �� �� �־���Ѵ�. �׷���������
//				button�� �������¿��� Window�� �̵��� �� �ְ� �ȴ�.
//				�̰��� �ذ��ϱ� ���� button down�� ��쿡�� false�� ��ȯ�ϵ��� �Ѵ�.
//				false�� ��ȯ�ϴ� ������ MouseControl()�� ó���ϴ� �κ��� ����ȭ�ϱ�
//				���ؼ���.
//-----------------------------------------------------------------------------
bool Button::MouseControl(UINT message, int _x, int _y)
{
	switch (message)
	{
		//
		// M_MOVING
		//
		// focus of/off
		//
		case M_MOVING:
			if (IsInRect(_x, _y))
			{
				FocusOn();
			}
			else
			{
				FocusOff();
			}
			break;

		//
		// M_LEFTBUTTON_DOWN, M_LB_DOUBLECLICK
		//
		// button press down.
		//
		case M_LEFTBUTTON_DOWN:
		case M_LB_DOUBLECLICK:
			if (IsInRect(_x, _y))
			{
				PressDown();

				if (m_click_option == RUN_WHEN_PUSH)
					Run();

				return false;
			}
			break;

		//
		// M_LEFTBUTTON_UP
		//
		// button press up -> execution!
		//
		case M_LEFTBUTTON_UP:
			if (GetFocusState()) // focus: yes
			{
				if (GetPressState()) // press: yes
				{
					PressUp();

					if (m_click_option == RUN_WHEN_PUSHUP)
						Run();
				}
				else // press: no
				{
					// no code!
				}
			}
			else // focus: no
			{
				if (GetPressState()) // press: yes
				{
					PressUp();
				}
				else // press: no
				{
					// no code!
				}
			}
	}

	return true;
}