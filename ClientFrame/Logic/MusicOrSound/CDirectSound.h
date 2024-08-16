//----------------------------------------------------------------------
// CDirectSound.h
//----------------------------------------------------------------------

#ifndef __CDirectSound_H__
#define __CDirectSound_H__

#pragma warning(disable:4786)

#include <Windows.h>
#include <MMSystem.h>
#include <DSound.h>
#include <list>

typedef	std::list<LPDIRECTSOUNDBUFFER>	LPDIRECTSOUNDBUFFER_LIST;

class CDirectSound
{

	public:		// �Լ�
		CDirectSound();
		~CDirectSound();

		//---------------------------------------------------------
		// Init / Release
		//---------------------------------------------------------
		bool					Init(HWND);									// �ʱ�ȭ 
		void					Release();									// ����
		void					ReleaseDuplicateBuffer();

		bool					IsInit() const		{ return m_bInit; }

		//---------------------------------------------------------
		// Load / Release / Duplicate
		//---------------------------------------------------------
		LPDIRECTSOUNDBUFFER		LoadWav(LPSTR filename);					// ȭ�� �ε�(*,wav)
		LPDIRECTSOUNDBUFFER		CreateBuffer(LPVOID sdat, DWORD size, DWORD caps, LPWAVEFORMATEX wfx);
		void					Release(LPDIRECTSOUNDBUFFER);				// ���� ���� ����
		LPDIRECTSOUNDBUFFER		DuplicateSoundBuffer(LPDIRECTSOUNDBUFFER, bool bAutoRelease=true);	// ���� ���� ����	

		//---------------------------------------------------------
		// Play / Stop
		//---------------------------------------------------------
		bool					IsPlay(LPDIRECTSOUNDBUFFER) const;								// �������ΰ�?
		bool					NewPlay(LPDIRECTSOUNDBUFFER, bool bLoop=false);	// ���� �÷���(ó������ �ٽ� ����)
		bool					Play(LPDIRECTSOUNDBUFFER, bool bLoop=false, bool bDuplicate=true);		// ���� �÷���(���������� ��ٸ�)
		bool					Stop(LPDIRECTSOUNDBUFFER);					// ���� ����
		void					ReleaseTerminatedDuplicateBuffer();

		//---------------------------------------------------------
		// Mute
		//---------------------------------------------------------
		bool					IsMute() const	{ return m_bMute; }
		void					SetMute()		{ m_bMute = true; }
		void					UnSetMute()		{ m_bMute = false; }

		//---------------------------------------------------------
		// Frequency
		//---------------------------------------------------------
		bool					AddFrequency(LPDIRECTSOUNDBUFFER, int);		// ���ļ� �ø���				
		bool					SubFrequency(LPDIRECTSOUNDBUFFER, int);		// ���ļ� ������				
	
		//---------------------------------------------------------
		// Volume
		//---------------------------------------------------------
		bool					SetMaxVolume(LPDIRECTSOUNDBUFFER buffer);
		bool					AddVolume(LPDIRECTSOUNDBUFFER, int);		// ���� ����
		bool					SubVolume(LPDIRECTSOUNDBUFFER, int);		// ���� ����				
		bool					SubVolumeFromMax(LPDIRECTSOUNDBUFFER, int);	// Max���� ���� ����				
		void					SetVolumeLimit(LONG volume);
		LONG					GetVolumeLimit() const	{ return m_MaxVolume; }

		//---------------------------------------------------------
		// Pan
		//---------------------------------------------------------
		bool					RightPan(LPDIRECTSOUNDBUFFER, int);			// ������ ��
		bool					LeftPan(LPDIRECTSOUNDBUFFER, int);			// ���� ��
		bool					CenterToRightPan(LPDIRECTSOUNDBUFFER, int);			// center���� ������ ��
		bool					CenterToLeftPan(LPDIRECTSOUNDBUFFER, int);			// center���� ���� ��
		bool					CenterPan(LPDIRECTSOUNDBUFFER);				// ��� ��				
		bool					ChangePan(LPDIRECTSOUNDBUFFER buffer, int pan);	// -10000 ~ 10000

		LPDIRECTSOUND			GetDS() const		{ return m_pDS;	}

		

	protected:
		bool					DirectSoundFailed(const char *str);		


	protected :
		LPDIRECTSOUND			m_pDS;										// ���̷�Ʈ ���� ������Ʈ
		bool					m_bInit;

		bool					m_bMute;			// �Ҹ��� ���� �ʴ´�.

		LONG					m_MaxVolume;		// ������ �ִ� �Ҹ� ũ��

		LPDIRECTSOUNDBUFFER_LIST	m_listDuplicatedBuffer;


	friend class CDirectMusic;
	friend class CDirectSoundStream;
};

extern	CDirectSound		g_DXSound;

#endif