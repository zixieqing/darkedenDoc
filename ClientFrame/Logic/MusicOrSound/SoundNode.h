//----------------------------------------------------------------------
// SoundNode.h
//----------------------------------------------------------------------
// ��� �������� ���� �Ҹ�
//----------------------------------------------------------------------

#ifndef	__SOUNDNODE_H__
#define	__SOUNDNODE_H__

#include <Windows.h>
#include "MTypeDef.h"

class SOUND_NODE {
	public :
		//------------------------------------------------------
		// delay�ð� �Ŀ� sid�� play�ϰ� �Ѵٴ� �ǹ�.
		//------------------------------------------------------
		SOUND_NODE(TYPE_SOUNDID sid, DWORD delay, int x, int y)	{ Set(sid, delay, x,y); }

		//------------------------------------------------------
		// set
		//------------------------------------------------------
		void			Set(TYPE_SOUNDID sid, DWORD delay, int x, int y);

		//------------------------------------------------------
		// get
		//------------------------------------------------------
		DWORD			GetPlayTime() const			{ return m_PlayTime; }
		TYPE_SOUNDID	GetSoundID() const			{ return m_SoundID; }
		int				GetX() const				{ return m_X; }
		int				GetY() const				{ return m_Y; }

	protected :
		DWORD			m_PlayTime;
		TYPE_SOUNDID	m_SoundID;
		
		// �Ҹ��� ���� ��ġ
		int				m_X;
		int				m_Y;
};

#endif
