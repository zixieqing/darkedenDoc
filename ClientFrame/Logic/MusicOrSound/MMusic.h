//----------------------------------------------------------------------
// MMusic.h
//----------------------------------------------------------------------
/*

  notifyó�� ���

  ������ �ڵ�(g_hWnd)�� ������ �����̸�..
  �� ������� MM_MCINOTIFY�� ����.

	case MM_MCINOTIFY :
		{
			// Mid�� �� ���ֵǾ��ٴ� ���̴�.
			if (wParam==MCI_NOTIFY_SUCCESSFUL)
			{
				// �ݺ��ؼ� �����Ѵ�.
				g_Music.RePlay();
			}
		}
*/
//----------------------------------------------------------------------
#ifndef __MMUSIC_H__
#define __MMUSIC_H__

//#include <MMSystem.h>


// Ŭ����
class MMusic
{
protected:
	HWND		m_hwnd;


	LPSTR		MIDI_ERROR_MSG[80];				// ���� �޼��� ���� 

public:
	bool		m_bInit;
	bool		m_bLoad;						// ȭ���� �ε�������?
	bool		m_bPlay;						// ������ ����������?
	bool		m_bPause;						// �������׳�?
	WORD		m_Volume;

	
protected:
	bool		ErrorMsg();						// �޼��� ���


public:
	MMusic();
	~MMusic();
	
	bool		Init(HWND);
	void		UnInit();

	bool		IsInit() const		{ return m_bInit; }

	bool		IsPlay() const		{ return m_bPlay; }
	bool		IsPause() const		{ return m_bLoad && m_bPause; }//m_bLoad && !m_bPlay; }

	bool		Play(LPCSTR filename);
	bool		Stop();
	bool		Pause();
	bool		Resume();
	bool		RePlay();

	void		SetVolume(WORD volume);
	WORD		GetVolume()			{ return m_Volume; }

};

extern MMusic		g_Music;

#endif