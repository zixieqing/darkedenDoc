/*-----------------------------------------------------------------------------

	u_edit.h

	Edit Widget.

	2000.6.7. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __U_EDIT_H__
#define __U_EDIT_H__

#include <string>
#include "FL2.h"
#include "SimpleDataList.h"

//-----------------------------------------------------------------------------
// LineEditor
//
// Single-line editor.
//
// * ���ڸ� �Է��� �� �ִ� line�� ���簢�� box ���¸� ���Ѵ�. �̰��� edit box�� ����.
//
// < edit box >
//
// edit box�� �Է��ϴ� �� �־ �ð������� ��� ǥ���Ǿ�� �� ������ ������ 
// �����Ѵ�. ���� �� class������ �ٸ� Widget�� ���� ��¿� ���ؼ��� �������� �ʴ´�.
// ���� �̰��� ũ�⸦ ������ �� �ִ� �������� ����������, ������ �׷��� ǥ�õǰų�
// �����ʰų� �ϴ� ���� �� class�� ����ϴ� App�� �޷� �ִ�. font ��µ� �̿� 
// �ش��Ѵ�.
//
// < font size ���� >
//
// LineEditor class�� '���'�� ���� �Ű澲�� �����Ƿ� font size ���濡 ���õ�
// ���뵵 ���ǵ��� �ʴ´�. m_line_buf�� �����ϰ� 'character code'�� �����ϰ� �ִ�.
// ����, m_line_buf�� �Ϻ��� ���ڿ��� font size�� ũ�� �ٲٰ�ʹٸ� �׷��� ������
// �����ϰ� �����ϴ� code�� �ٸ� ���� �ξ�� �Ѵ�.
//
// < cursor >
//
// cursor�� line������ '��ġ(position)'�̴�. cursor�� ��ġ���� ����/����/copy/paste����
// �̷������.
//
// < edit box�� ������ ũ��� �Է����� >
//
// edit box�� ũ�⸦ ���� ���̶�� �ؼ� �Է��� �Ұ����� ���� �ƴϴ�. �̴� ��������
// �Է������� edit box ���ο����� ���� ũ�⿡ ���ؼ� ���ѵ��� �ǹ��Ѵ�.
// �� ���� ũ�Ⱑ edit box���� Ŭ ��� cursor�� ��ġ�� ���� line�� ��ũ�ѵȴ�.
// �Է��� �� �ִ� ���ڼ��� ���Ƶ� ����� ���� ũ��� ���� ���Ѵ�(���ѵȴ�).
// �̰��� font�� ����ϴ� ������ font�� width�� �˻��Ͽ� ������ ������.
//-----------------------------------------------------------------------------
typedef std::basic_string<char_t> String;

class LineEditor
{
protected:
	String						m_string;
	int								m_gap;	// editor����϶� ����� y_gap
	int								m_editor_height;

	//
	// m_logical_size
	//
	// edit box�� ���� ũ���.
	//
	//int							m_logical_size;

	//
	// m_char_input_count
	//
	// �Է��� �� �ִ� ������ ������ �����Ѵ�.
	// �����̸� �Է����� ����.
	//
	int							m_char_input_count;

	//
	// m_cursor
	//
	// cursor�� ���ڰ� �Էµ� ��ġ�� ����Ų��. ��, string�� index�̴�.
	// string������ cursor. cursor�� ������ string�� �� �հ� �� �� �����̴�.
	//
	int							m_scroll;
	int							m_cursor;

	//
	// m_byte_limit
	//
	// byte �Է�����.
	// �̰��� DBCS������ �깰�� ���� 1byte �ѱ� 2byte�� ��쿡 ��Դ� ���̴�.
	// �����̸� ���� ����.
	//
	int							m_byte_limit;
	int							m_reach_limit;

	bool							m_bl_digit_only;
	// m_bl_password_mode
	//
	// �ϳ��� ���ڸ� '*'�� ����Ѵ�.
	//
	bool							m_bl_password_mode;

public:
	LineEditor();
	LineEditor(int logical_size);
	~LineEditor();

	void	Init();

	//----------------------
	// Acquire/Unacquire
	//----------------------
	void	Acquire();
	void	Unacquire();
	bool	IsAcquire() const;

	//----------------------
	// Input
	//----------------------
	void	KeyboardControl(UINT message, UINT key, long extra);
//	void	InsertToCursorPosition(char_t a_char);
//	void	InsertToCursorPositionForIME(char_t a_char);
	void	EditToCursorPosition(char_t a_char);
	void	EditToCursorPositionForIME(char_t a_char);
	void	InsertMark(char_t a_char);
	bool	InsertGap();

	virtual const int GetLineCount() const { return 0; }

	//----------------------
	// Check input limit
	//----------------------
public:
	//virtual bool EndOfLogicalSize() const { return false; } // � font���� ������ LineEditor���� ������ �� ����.
	virtual bool	ReachEndOfBox(char_t will_input_char) const { return false; }
	bool	CheckInputLimit(char_t will_input_char);
	bool	CheckInputCharLimit() const;

	bool	IsPasswordMode() const { return m_bl_password_mode; }

public:

	//----------------------
	// Get
	//----------------------
	const char_t * GetString() const { return m_string.c_str(); }
	const char_t * GetStringScroll() const;
	int	Size() const { return m_string.size(); }
	int	GetCursor() const { return m_cursor; }

	//----------------------
	// Set
	//----------------------
	//void	SetLogicalSize(int logical_size);
	void	SetInputCharCount(int char_count);
	void	SetByteLimit(int byte);
	void	AddString(const char * sz_str);
	void	SetDigitOnlyMode(bool state) { m_bl_digit_only = state; }
	bool	GetDigitOnlyMode() const { return m_bl_digit_only; }

	//----------------------
	// Cursor movement
	//----------------------
	int		IncreaseCursor();
	int		DecreaseCursor();
	bool	HomeCursor();
	bool	EndCursor();

	//----------------------
	// Erase string
	//----------------------
//private:
	bool	EraseCharacterFrontCursor();

public:
	void	EraseAll();
	bool	EraseCharacterBegin();
};

//-----------------------------------------------------------------------------
// LineEditorVisual
//
// LineEditor�� �ð�ȭ��Ų��.
//-----------------------------------------------------------------------------
class LineEditorVisual : public LineEditor
{
private:
	Point							m_xy;
	int							m_abs_width; // edit box�� ���� ����. �����̸� ���Ѵ��̴�.
	COLORREF						m_cursor_color;

	//

	PrintInfo					m_print_info;
	
public:
	LineEditorVisual();
	~LineEditorVisual();

	void	SetAbsWidth(int width);
	void	SetCursorColor(COLORREF color);
	void	SetPosition(int x, int y);
	Point	GetPosition() { return m_xy; }
	void	Show() const;
	void	SetEditorMode(int gap, int height = 0) { m_gap = gap; m_editor_height = height; }

	bool		ReachEndOfBox(char_t will_input_char = 0) const;
	int		ReachSizeOfBox() const;

	//bool	EndOfLogicalSize() const;

	void	PasswordMode(bool enable);
	void	SetPrintInfo(PrintInfo &print_info);
	PrintInfo &GetPrintInfo()	{ return m_print_info; }	// by sigi
	void	SetInputStringColor(COLORREF rgb) { m_print_info.text_color = rgb; }

	const int GetLineCount() const;
	

};

//-----------------------------------------------------------------------------
// DocumentEditor
//
// Multi-line editor
//-----------------------------------------------------------------------------
class DocumentEditor
{
private:
	//LineEditor		m_line_editor[line];

public:
};

//-----------------------------------------------------------------------------
// EditManager
//
// DocumentEditor�� �����Ѵ�.
// Single line�� ����ϴ� edit line�� DocumentEditor�� �����ȴ�. line ������ 1��
// �Ǹ� �������� �����̴�. �׷��� EditManager�� DocumentEditor���� ������ �ʿ䰡
// �ִ�. Ư���� �������� LineEditorVisual�� ����Ѵٸ� EditManager�� ������
// ���� �� ����. �׷��� �Ǹ� ������ �������...
//
// Edit Widget�� �� ���� �ϳ��� ��� �Է��� �� �����Ƿ� �װ��� ó���� ���ָ�,
// �ܺο����� EditManager�� �׵�� ���ϴ� ������ �������̽��� �����Ѵ�.
//-----------------------------------------------------------------------------
/*
class EditManager : public SimpleDataList<DocumentEditor *>
{
private:

public:
	EditManager();
	~EditManager();

	//
	// Register/Unregister
	//
	void	Register(DocumentEditor * p_de);
	void	Unregister(DocumentEditor * p_de);

	void	Show(HDC hdc) const;
};*/

#endif