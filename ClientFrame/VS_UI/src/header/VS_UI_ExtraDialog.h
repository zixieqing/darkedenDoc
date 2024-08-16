/*-----------------------------------------------------------------------------

	VS_UI_ExtraDialog.h

	2000.12.6. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __VS_UI_EXTRADIALOG_H__
#define __VS_UI_EXTRADIALOG_H__

#include "VS_UI_Widget.h"
#include "VS_UI_Util.h"
#include "VS_UI_GameCommon.h"
#include "VS_UI_Dialog.h"
#include "VS_UI_DESC.h"

//-----------------------------------------------------------------------------
// class C_VS_UI_DESC_DIALOG
//
// Item �Ǵ� Skill����
//
//-----------------------------------------------------------------------------
class C_VS_UI_DESC_DIALOG : public Window, public C_VS_UI_DESC, public Exec, public ButtonVisual
{
private :
	bool m_bl_main_help;

private:
	ButtonGroup *				m_pC_button_group;
	C_VS_UI_SCROLL_BAR			*m_pC_scroll_bar;

	enum EXEC_ID
	{
		CLOSE_ID,
	};

public:
	enum INTERFACE_HELP_ID
	{
		MAIN,
		CHATTING,
		SKILL,
		BATTLE,
		INVENTORY,
		GEAR,
		INFO,
		OTHER_INFO,
		SHOP,
		STORAGE,
		EXCHANGE,
		PARTY_MANAGER,
		GUILD,
		TRACE_WINDOW,
		OUSTERS_SKILL_INFO,
		MINI_GAME_ARROW_TILE,
		MINI_GAME_CRAZY_MINE,
		CTF_WINDOW,
		NICK_NAME_WINDOW,
	};

	bool	IsMainHelp()	{ return m_bl_main_help; }
	
	C_VS_UI_DESC_DIALOG(id_t type, void * void_ptr, void* void_ptr2 = NULL);
	~C_VS_UI_DESC_DIALOG();

	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	Start();
	void	Finish();

	void	Show();
};


//-----------------------------------------------------------------------------
// class C_VS_UI_FILE_DIALOG
//
// file ����
//
//-----------------------------------------------------------------------------
class C_VS_UI_FILE_DIALOG : public Window, public Exec, public ButtonVisual
{
private:

	enum EXEC_ID
	{
		OK_ID,
		CANCEL_ID,
	};
	
	enum FILEICON_ID
	{
		FOLDER_ID,
		UPFOLDER_ID,
		OPENFOLDER_ID,
		HDDRIVE_ID,
		CDDRIVE_ID,
		MYCOMPUTER_ID,
	};

	C_SPRITE_PACK *m_p_image_spk;
	C_SPRITE_PACK *m_p_icon_spk;

	C_VS_UI_SCROLL_BAR			*m_pC_scroll_bar;

	ButtonGroup *				m_pC_button_group;

//	int m_scroll_x, m_scroll_y, m_scroll_h;
//	int m_scroll;

	std::vector<std::string>	m_filter;
	std::vector<std::string>	m_vs_file_list;
	std::vector<DWORD>			m_vs_file_list_attr;
	std::string					m_filename;
	std::vector<int>			m_select_file_num;

	int		m_string_x, m_string_y, m_string_gap;
	int		m_scroll_max;
	int		m_select, m_tempselect;
	bool	m_bl_open_drive;
	bool	m_flag_preview_image;

	int		STAY_FOLDER;
	//DWORD	m_stay_openfolder;
	DWORD	m_show_long_name;
	
	char **mp_open_current_directory;
	int  mi_open_drive_count;
	int  mi_open_drive_index;
	int m_mode;
	CDirectDrawSurface m_temp_face;


public:
	enum MODE
	{
		MODE_PROFILE_SELECT,
		MODE_SENDFILE_SELECT,
	};

	// �ش� ��ȣ�� ���� ���� ����
	static const std::string GetFileNameInString(char *str,int n);
	// �����̸����� ������ �� ����
	static int GetSizeFileInString(char *str);

	C_VS_UI_FILE_DIALOG(MODE Mode = MODE_PROFILE_SELECT);
	~C_VS_UI_FILE_DIALOG();

	int		GetMode();
	void	Process();
	void	UnacquireMouseFocus();
	bool	IsPixel(int _x, int _y);
	void	Run(id_t id);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);

	void	RefreshFileList(char *sz_dirname);
	void	ChangeDir(char *sz_cur_dirname, char *sz_pathname);
	bool	GetParentDir(char *sz_name);

	const char *	GetFileName()	{ if(m_filename.empty())return NULL; return m_filename.c_str(); }
	void	Start(char *type);
	void	Finish();

	void	Show();
	char Upperchar(char str){if(!(str>='a'&&str<='z')) return str;else return str-32;}

	bool	Timer(bool reset);
};


//-----------------------------------------------------------------------------
// class C_VS_UI_EDIT_DIALOG
//
// Dialog box���� ��(digit only)�� �Է��� �� �ִ� dialog box�̴�.
//
// ! �������� ������ ���ǻ�� �������� ����.
//-----------------------------------------------------------------------------
class C_VS_UI_EDIT_DIALOG : public C_VS_UI_DIALOG
{
private:
	LineEditorVisual			m_lev_value;

	C_SPRITE_PACK *			m_p_image_spk;

	enum IMAGE_SPK_INDEX
	{
		BUY_DIALOG,

		SLAYER_BUTTON_UP,
		SLAYER_BUTTON_DOWN,
		SLAYER_BUTTON_UP_HILIGHTED,
		SLAYER_BUTTON_DOWN_HILIGHTED,
		SLAYER_BUTTON_UP_HILIGHTED_PUSHED,
		SLAYER_BUTTON_DOWN_HILIGHTED_PUSHED,

		VAMPIRE_BUTTON_UP,
		VAMPIRE_BUTTON_DOWN,
		VAMPIRE_BUTTON_UP_HILIGHTED,
		VAMPIRE_BUTTON_DOWN_HILIGHTED,
		VAMPIRE_BUTTON_UP_HILIGHTED_PUSHED,
		VAMPIRE_BUTTON_DOWN_HILIGHTED_PUSHED,
	};

	enum
	{
		SCROLL_BUTTON_WIDTH = 28,
		SCROLL_BUTTON_HEIGHT = 13,
		SCROLL_BUTTON_OFFSET_X = 39,
		SCROLL_BUTTON1_OFFSET_Y = 0,
		SCROLL_BUTTON2_OFFSET_Y = 13,
	};

	int								m_default_val;
	Point							m_buy_dialog_pt;
	Rect							m_scroll_button_up_rt;
	Rect							m_scroll_button_down_rt;

	bool							m_bl_up_pushed;
	bool							m_bl_down_pushed;
	bool							m_bl_up_focused;
	bool							m_bl_down_focused;

	char *				m_sz_question_msg[1];

	void	ScrollButton(bool up);

	int								m_max_val;

public:
	C_VS_UI_EDIT_DIALOG(int _x, int _y, int center_x, int center_y, void (*exec_fp)(C_VS_UI_DIALOG *, id_t), WORD dd_button, int cur_val = 1, int max_val = 9);
	~C_VS_UI_EDIT_DIALOG();

	void	Start();
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Show();
	int	GetValue() const;
};

//-----------------------------------------------------------------------------
// class C_VS_UI_MONEY_DIALOG
//
// ���� ������ dialog box�̴�.
//-----------------------------------------------------------------------------
class C_VS_UI_MONEY_DIALOG : public C_VS_UI_DIALOG
{
public :
	enum TYPE_MONEY_DIALOG {		// by sigi
		MONEY_DROP,
		MONEY_DEPOSIT,
		MONEY_WITHDRAW,
		MONEY_EXCHANGE,
		MONEY_WITHDRAW_FROM_EXCHANGE,
		MONEY_BRING_FEE,
		MODIFY_TAX,
		MONEY_SELL_ITEM,
		MONEY_CAMPAIGN_HELP,

		MAX_MONEY_DIALOG_TYPE,
	};

private:
	LineEditorVisual			m_lev_value;
	bool					m_bPrintMessage;

//	C_SPRITE_PACK *			m_p_image_spk;

//	enum IMAGE_SPK_INDEX
//	{
//		MONEY_DIALOG,
//	};

	Point							m_money_dialog_pt;

	//static char *				m_sz_question_msg[1];	// �ּ�ó�� by sigi
	//static char *				m_sz_question_msg_for_storage[1];	// �ּ�ó�� by sigi
	char *					m_sz_question_msg[MAX_MONEY_DIALOG_TYPE][1];		// by sigi

	TYPE_MONEY_DIALOG		m_type;	// dialog type	 by sigi
	
	void	ScrollButton(bool up);

public:
	C_VS_UI_MONEY_DIALOG(int _x, int _y, int center_x, int center_y, void (*exec_fp)(C_VS_UI_DIALOG *, id_t), WORD dd_button, int digit_count, TYPE_MONEY_DIALOG type); // type �߰�  by sigi
	~C_VS_UI_MONEY_DIALOG();

	void	Start();
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Show();
	int	GetValue() const;
	
};


//-----------------------------------------------------------------------------
// class C_VS_UI_ASK_DIALOG
//
// message������ OK/NO�� �����ϴ� dialog
//
//-----------------------------------------------------------------------------
class C_VS_UI_ASK_DIALOG : public C_VS_UI_DIALOG
{
public :
	enum TYPE_ASK_DIALOG {		// by sigi
		ASK_STORAGE_BUY,
		ASK_EXCHANGE,
		ASK_EXCHANGE_CANCEL,
//		ASK_TUTORIAL_EXIT,		// by larosel
		ASK_PARTY_REQUEST,
		ASK_PARTY_INVITE,
		ASK_PARTY_CANCEL,
		ASK_NO_SEARCH_RESULT,
		ASK_ENCHANT,
		ASK_DEPOSIT_LIMIT,
		ASK_WITHDRAW_LIMIT,
		ASK_BRINGFEE_LIMIT,
		ASK_TRANS_ITEM,
		ASK_USE_PET_FOOD,
		ASK_KEEP_PETITEM,		// ���� ���� �Ͻðڽ��ϱ�?
		ASK_GET_KEEP_PETITEM,	// "%s ���� ã���ðڽ��ϱ�?";
		ASK_USE_SMSITEM,		// sms item �� ����Ͻðڽ��ϱ�?
		ASK_USE_NAMINGITEM,		// ���̹� �������� ��� �ϰڽ��ϱ�?
		ASK_GET_EVENT_ITEM,		// �̺�Ʈ �������� �����ðڽ��ϱ�?
		//add by viva : ask_friend_request
		ASK_FRIEND_REQUEST,
		ASK_FRIEND_REFUSE,
		ASK_FRIEND_WAIT,
		ASK_FRIEND_EXIST,
		ASK_FRIEND_BLACK,
		ASK_FRIEND_DELETE,

		MAX_ASK_DIALOG_TYPE
	};

private:
	TYPE_ASK_DIALOG			m_type;

	char *						m_sz_question_msg_temp[2];
	char *						m_sz_question_msg[MAX_ASK_DIALOG_TYPE][5];
	
	DWORD	m_dwTemporayValue;
	void*	m_pTemporayValue;

public:
	C_VS_UI_ASK_DIALOG(int _x, int _y, int center_x, int center_y, void (*exec_fp)(C_VS_UI_DIALOG *, id_t), WORD dd_button, TYPE_ASK_DIALOG type, int value=0, void* pValue=NULL);
	~C_VS_UI_ASK_DIALOG();

	DWORD	GetdwTemporayValue() { return m_dwTemporayValue;}
	void*	GetpTemporayValue() { return m_pTemporayValue; }
	TYPE_ASK_DIALOG		GetAskType() { return m_type; }
	void	InitString();

	void	Start();
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);	
};


//-----------------------------------------------------------------------------
// class C_VS_UI_NPC_DIALOG
//
// DIALOG�� ������ NPC�� ������ ������ �ִ�.
//
//-----------------------------------------------------------------------------
class C_VS_UI_NPC_DIALOG : public C_VS_UI_DIALOG
{
private :

private:
	int				m_id;
	int				m_iSprite;
	CSpritePack		m_p_NPCFace;
	MString			m_name;
	
public:
	C_VS_UI_NPC_DIALOG(void (*exec_fp)(C_VS_UI_DIALOG *, id_t), int sprite_num, const char* pname,WORD dd_button=DIALOG_NO_BUTTON);
	C_VS_UI_NPC_DIALOG(void (*exec_fp)(C_VS_UI_DIALOG *, id_t), int sprite_num, const char* pname, int Width, int Height, WORD dd_button=DIALOG_NO_BUTTON, bool IsShowItem = false);
	~C_VS_UI_NPC_DIALOG();

	void	InitNpcDlg(int sprite_num, const char* pname, bool IsShowItem = false);
	void	Show();
	void	Start();
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);	
};

#endif