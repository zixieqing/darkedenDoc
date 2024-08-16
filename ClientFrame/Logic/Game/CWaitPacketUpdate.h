//-----------------------------------------------------------------------------
// CWaitPacketUpdate.h
//-----------------------------------------------------------------------------
// Server���� �޽����� ���⸦ ��ٸ��� Loop
//-----------------------------------------------------------------------------

#ifndef	__CWAITPACKETUPDATE_H__
#define	__CWAITPACKETUPDATE_H__

#include "CWinUpdate.h"

class CWaitPacketUpdate : public CWinUpdate {
	public :
		CWaitPacketUpdate()	{ m_DelayLimit = 0xFFFFFFFF; }
		~CWaitPacketUpdate() {}

		// �ʱ�ȭ
		void		Init();

		// Update�ϴ� �Ѱ� �ð��� �����Ѵ�.
		void		SetDelay(DWORD delay);		

		// update
		void		Update();		

	protected :				
		DWORD		m_DelayLimit;	// ��ٸ��� �Ѱ� �ð�
};


extern CWaitPacketUpdate*	g_pCWaitPacketUpdate;

#endif
