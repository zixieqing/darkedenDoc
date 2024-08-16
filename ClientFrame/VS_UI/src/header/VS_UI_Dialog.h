/*-----------------------------------------------------------------------------

	VS_UI_Dialog.h

	�Ϲ����� Dialog box�� �����Ѵ�. ������ Widget�� scroll bar,	Button�̴�.
	�� ��ü�� �����Ǿ� ���������� ���ȴ�.

	2000.11.2. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __VS_UI_DIALOG_H__
#define __VS_UI_DIALOG_H__

#include "Unicorn.h"
#include "VS_UI_Widget.h"
#include <vector>
#include <string>


//-----------------------------------------------------------------------------
// Dialog �ϴܿ� ������ ���ǵ� ��ư.
//-----------------------------------------------------------------------------
#define DIALOG_NO_BUTTON				0x0000
#define DIALOG_OK						0x0001
#define DIALOG_CANCEL					0x0002
#define DIALOG_FRIEND_BLACK				0x0004		//add by viva
//-----------------------------------------------------------------------------
// Dialog ���ǵ� ��ư exec id.
//-----------------------------------------------------------------------------
#define DIALOG_EXECID_EXIT				0xFFFF0000
#define DIALOG_EXECID_OK				0xFFFF0001
#define DIALOG_EXECID_CANCEL			0xFFFF0002
#define DIALOG_EXECID_SCROLL_UP		0xFFFF0003
#define DIALOG_EXECID_SCROLL_DOWN	0xFFFF0004
#define DIALOG_EXECID_FRIEND_BLACK			0xFFFF0005		//add by viva

//-----------------------------------------------------------------------------
// Dialog menu struct.
//-----------------------------------------------------------------------------
struct DIALOG_MENU
{
	char *		sz_menu_str;
	id_t		exec_id;
};

struct DIALOG_MENU_INNER	// ���ο��� ����
{
	std::vector<std::string>	sz_menu_str;
	id_t		exec_id;
};

//-----------------------------------------------------------------------------
// DIALOG_BUTTON_X
//
// Button�� ��ġ�� ��ư�� ������ ���� �޶������� �⺻������ box�� ���� ����
// ���ĵȴ�. button�� 2���� ��� button_n = 1�̸� ���� �����̰� 2�̸� �� �����̴�.
// ������� Ok button�� Cancel button�� ���� ��� ��ġ�� �ٲ��.
//-----------------------------------------------------------------------------
#define DIALOG_BUTTON_EXTRA_HGAP		10

#define DIALOG_BUTTON_X(n)				(m_client_rect.Right()-DIALOG_BUTTON_WIDTH*(n)+35)
#define DIALOG_BUTTON_Y					(m_client_rect.Down()-DIALOG_BUTTON_HEIGHT-12)

#define DIALOG_BUTTON_POS(x)			DIALOG_BUTTON_X(m_button_count-(x))

#define TEXT_EXTRA_HGAP					8
#define MSG_EXTRA_HGAP					5

enum BUTTON_SEQUENCE
{
	BS_OK = 0,
	BS_CANCEL = 1,
	BS_FRIEND_BLACK = 2,	//add by viva
};

//-----------------------------------------------------------------------------
// SetMessage mode option
//-----------------------------------------------------------------------------
enum SETMESSAGE_MODE_OPTION
{
	SMO_FIT,	// Msg rect�� ��Ȯ�� ���߰� �������� �ʴ´�. ���� �ʿ��ϴٸ� scroll bar�� �����Ѵ�.
	SMO_NOFIT, // Msg rect ������ ��/�Ʒ� ��� ������ �ϸ� scroll bar�� �������� �ʴ´�.
};

//-----------------------------------------------------------------------------
// C_VS_UI_DIALOG
//
// format>
//
//				+----------------------------+
//				|			Message			 | -> Message�� �������� ũ�� scroll bar�� �ٴ´�.
//				|							 |
//				+----------------------------+
//				|							 |
//				|	Menu 1.					 |
//				|	Menu 2. 				 |
//				|							 |
//				|	Button 1.   Button 2.	 |
//				+----------------------------+
//
// �⺻������ �ܺο��� box�� size�� �����Ѵ�. �װ��� �� ���������� ���� �� ������
// ���� �����̴�. Button, Menu�� ��ġ�ǰ� Message area�� ������ �ڵ����� scroll bar��
// �����Ѵ�.
//
// !box�� �ʹ� ������ Menu �� Button�� �� ���� �� �ִ�.
//
// ����>
//				// func�� menu�� �����Լ��̴�.
//				C_VS_UI_DIALOG m_pC_dialog = new C_VS_UI_DIALOG(50, 20, 6, 2, func, DIALOG_OK);
//
//				DIALOG_MENU d_menu[] = {
//					{"���", 0},
//					{"�ȱ�", 1},
//					{"������", DIALOG_EXECID_EXIT},
//				};
//				m_pC_dialog->SetMenu(d_menu, 3);
//
//				static char * pp_dmsg[] = { // Message�� �ݵ�� static or global�� �ؾ� �Ѵ�.
//					"line 1",
//					"line 2",
//				};
//
//				m_pC_dialog->SetMessage(pp_dmsg, sizeof(pp_dmsg)/sizeof(char *));//, SMO_NOFIT);
//
//-----------------------------------------------------------------------------
class C_VS_UI_DIALOG : public Window, public Exec, public ButtonVisual
{
protected:
	BOOL						m_flag_menu;
	void							(*m_exec_fp)(C_VS_UI_DIALOG *, id_t);

	//
	// center (x, y)
	//
	// �����ڽ��� x, y center ����.
	// default�� ���� 2�� ���� 2���� �ְ� center�� �����̹����� ������ �ø� �� �ִ�.
	//
//	int							m_width, m_height;

	WORD							m_ddb;

	DIALOG_MENU_INNER *				m_p_menu;
	UINT							m_menu_count;

	std::vector<std::string>		m_vs_msg;

	UINT							m_line_count;
	UINT							m_print_line_count;
	SETMESSAGE_MODE_OPTION	m_message_mode;
	int							m_nofit_mode_msg_y; // no fit mode�� ��� msg�� y.

	C_VS_UI_SCROLL_BAR			* m_pC_msg_scroll_bar,*m_pC_menu_scroll_bar;
//	Scrollbar					m_scrollbar;
//	int							m_remained_track;
//	bool							m_available_tag;
//	bool							m_tag_pushed;
//	int							m_prev_tag_y;
//	int							m_tag_up_limit, m_tag_down_limit;

	int							DIALOG_BUTTON_WIDTH;
	int							DIALOG_BUTTON_HEIGHT;

	int							m_menu_str_height;
	int							m_msg_str_height;
	//
	// rect
	//
	// Box���� Message rect�� Menu rect�̴�. �̰��� �ϴ� Button�� ������ �����̴�.
	// Button -> Menu -> Message ������ rect�� �����ϴ� ��, ������ ������ �װͿ� �ش��ϴ�
	// ���� ��µ��� �ʴ´�. Button�� �ּ� box size������ �����ϸ� ���� �ϴ��� �����Ѵ�.
	//
	Rect							m_msg_rect;
	Rect							m_menu_rect;
	Rect							m_client_rect;
//	Rect							m_tag_rect;

	int							m_button_count;
	int								*m_button_y_list;		// ��ũ�� �ɶ� y ũ�⸦ �˱� ����.
	int								m_menu_y_size,m_temp_menu_rect_y;	// �޴� Rect ������ ����� ����� y ũ��



	int							m_TempValue1;


	enum
	{
		DECORATE_GAP = 20,
	};

	ButtonGroup *				m_pC_button_group;

	int	GetButtonGap() const;
	bool						m_bOkOnly;
protected:
	void	CancelPushState();
	void	UnacquireMouseFocus();
	void	AcquireDisappear() {}
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	Process();
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	virtual bool	MouseControl(UINT message, int _x, int _y);
	virtual void	KeyboardControl(UINT message, UINT key, long extra);
	virtual void	Show();

public:
	C_VS_UI_DIALOG(int _x, int _y, int width, int height, void (*exec_fp)(C_VS_UI_DIALOG *, id_t) = NULL, WORD dd_button=DIALOG_NO_BUTTON);
	virtual ~C_VS_UI_DIALOG();

	void	Run(id_t id);
	virtual void	Start();
	void	Finish();

	void	SetMessage(char ** sz_msg, UINT line_count, SETMESSAGE_MODE_OPTION mode=SMO_FIT);
	void	SetMenu(const DIALOG_MENU * p_dialog_menu, UINT menu_count, bool menu_only=true);

	void	StartByPinMode();

	int		GetScrollPos();
	void	ProcessMenuScrollBar();

	void	SetOkOnly(bool bFlag) { m_bOkOnly = bFlag;}
	// 2005, 1, 18, sobeit add start - �ҿ��̿����� ���� �̺�Ʈ���� ���� �������� ��� ���� ���� üũ �ϱ� ����
	int GetTempValue() { return m_TempValue1;}
	void SetTempValue(int TempValue) { m_TempValue1 = TempValue;}
	// 2005, 1, 18, sobeit add end - �ҿ��̿����� ���� �̺�Ʈ���� ���� �������� ��� ���� ���� üũ �ϱ� ����
};
//
// exec function prototype
//
// void VS_UI_DialogRun(C_VS_UI_DIALOG * p_this_dialog, id_t id);
//

#endif