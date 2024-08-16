//----------------------------------------------------------------------
// MWorkThread.h
//----------------------------------------------------------------------
//
// [ Init ]
//
//   = Init(LPTHREAD_START_ROUTINE FileThreadProc, int priority);
//
//     FileThreadProc�κ��� MWorkThread.Execute�� �ؾߵȴ�. -_-; 
//     (callback function�� ����� static���� �ؾ��ϴµ�.. ������ ���Ƽ� - -;)
//
//		- �ܺο� �̷��� �Լ��� �ϳ� ���� 
//      - MWorkThread.Init( LoadingThreadProc ); �� �ؾ��Ѵ�.
//
//		long
//		LoadingThreadProc(void* pParam)
//		{
//			g_pLoadingThread->Execute();
//
//			return 0L;
//		}
//
//
// [ Remove ]
//
//   = Ư�� type�� MWorkNode���� '��'���� ���ܽ�Ų��.
//     ó���� �ʿ䰡 ������ ���... ���Ž�Ű�� �ȴ�.
//
//
// [ AddFirst / AddLast ]
//
//	  MWorkNode�� ó���ؾ��� '��'�� �߰���Ų��.
//	  �߰���Ŵ�� ���ÿ� 'Execute'���� �ٷ� ���� ó���ȴ�.
//    (Init���� MWorkThread.Execute�� ��~ ������ �� ���.. *_*;)
//    AddFirst()�� �߰���Ų ���� �ٷ�(!!) ó���ȴ�.
//    AddLast()�� �� ���߿�~ ó���ȴ�.
//
//
// [ SetPriority ]
//
//	  Priority�� �����ؼ� Thread�� ó�� �ӵ�?�� �ٲ� �� �ִ�.
//	  ��. Init�Ҷ��� �̰� �����ؾ� �ȴ�. 
//
//		THREAD_PRIORITY_HIGHEST
//		THREAD_PRIORITY_ABOVE_NORMAL
//		THREAD_PRIORITY_NORMAL
//		THREAD_PRIORITY_BELOW_NORMAL
//		THREAD_PRIORITY_LOWEST
//
//----------------------------------------------------------------------
#ifndef __MWORKTHREAD_H__
#define	__MWORKTHREAD_H__

#include <Windows.h>
#include <deque>
#include "MWorkNode.h"

//----------------------------------------------------------------------
// WorkThread
//----------------------------------------------------------------------
class MWorkThread {
	public :
		typedef std::deque<MWorkNode*>	WORKNODE_DEQUE;

	public :
		MWorkThread();
		~MWorkThread();

		//---------------------------------------------------
		// Init / Release
		//---------------------------------------------------
		void				Init(LPTHREAD_START_ROUTINE FileThreadProc, int priority=THREAD_PRIORITY_NORMAL);
      	void				Release();
		void				ReleaseWork();

		//---------------------------------------------------
		// Execute
		//---------------------------------------------------
		void				Execute();

		//---------------------------------------------------
		// Get Size
		//---------------------------------------------------
		int					GetSize() const				{ return m_dequeWorkNode.size(); }

		//---------------------------------------------------
		// Is...
		//---------------------------------------------------
		BOOL				IsWorking() const			{ return WaitForSingleObject(m_hHasWorkEvent, 0) == WAIT_OBJECT_0; }
		BOOL				IsFinishCurrentWork() const	{ return WaitForSingleObject(m_hEndWorkEvent, 0) == WAIT_OBJECT_0; }
		BOOL				IsStopWork() const			{ return WaitForSingleObject(m_hStopWorkEvent, 0) == WAIT_OBJECT_0; }
		
		//---------------------------------------------------
		// Stop
		//---------------------------------------------------
		void				Remove(int type);

		//---------------------------------------------------
		// Add work
		//---------------------------------------------------
		void				AddFirst(MWorkNode* pNode);
		void				AddLast(MWorkNode* pNode);

		//---------------------------------------------------
		// Set Priority
		//---------------------------------------------------
		void				SetPriority(int priority)	{ SetThreadPriority(m_hWorkThread, priority); }
			
	protected :
		//---------------------------------------------------
		// Lock Deque
		//---------------------------------------------------
		/*
		BOOL				IsLockDeque() const			{ return WaitForSingleObject(m_hDequeLock, 0) == WAIT_OBJECT_0; }
		void				WaitUnlockDeque() const		{ while (IsLockDeque()); }
		void				LockDeque()					{ SetEvent( m_hDequeLock ); }
		void				UnlockDeque()				{ ResetEvent( m_hDequeLock ); }

		HANDLE				m_hDequeLock;		// deque���ٿ� ���� Lock
		*/
		void				LockDeque()					{ EnterCriticalSection(&m_csDeque); }
		void				UnlockDeque()				{ LeaveCriticalSection(&m_csDeque); }

		CRITICAL_SECTION	m_csDeque;					// deque���ٿ� ���� Lock


		//---------------------------------------------------
		// Lock Current
		//---------------------------------------------------
		/*
		BOOL				IsLockCurrent() const			{ return WaitForSingleObject(m_hCurrentLock, 0) == WAIT_OBJECT_0; }
		void				WaitUnlockCurrent() const		{ while (IsLockCurrent()); }
		void				LockCurrent()					{ SetEvent( m_hCurrentLock ); }
		void				UnlockCurrent()				{ ResetEvent( m_hCurrentLock ); }

		HANDLE				m_hCurrentLock;		// m_pCurrent���ٿ� ���� Lock
		*/
		void				LockCurrent()					{ EnterCriticalSection(&m_csCurrent); }
		void				UnlockCurrent()					{ LeaveCriticalSection(&m_csCurrent); }

		CRITICAL_SECTION	m_csCurrent;					// current���ٿ� ���� Lock

	protected :
		HANDLE				m_hWorkThread;
		HANDLE				m_hHasWorkEvent;	// �� ���� �ִٴ� event
		HANDLE				m_hEndWorkEvent;	// �� ���� ���´ٴ� event
		HANDLE				m_hStopWorkEvent;	// �� ���� �����϶�� event
		
		WORKNODE_DEQUE		m_dequeWorkNode;

		// ���� ó���ϰ� �ִ� WorkNode
		MWorkNode*			m_pCurrentWork;
};

#endif


