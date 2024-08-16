//----------------------------------------------------------------------
// MWorkThread.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MWorkThread.h"

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MWorkThread::MWorkThread()
{
	m_hWorkThread = 0;

	m_hHasWorkEvent = 0;
	m_hEndWorkEvent = 0;
	m_hStopWorkEvent = 0;
	//m_hDequeLock = 0;
	//m_hCurrentLock = 0;

	m_pCurrentWork = NULL;
}

MWorkThread::~MWorkThread()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Init
//----------------------------------------------------------------------
void
MWorkThread::Init(LPTHREAD_START_ROUTINE FileThreadProc, int priority)
{
	if (m_hWorkThread!=0)
	{
		Release();
	}

	DWORD	dwChildThreadID;

	//-----------------------------------------------------------
	// Create Event
	//-----------------------------------------------------------
	m_hHasWorkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	// non-signaled
	m_hEndWorkEvent = CreateEvent(NULL, TRUE, TRUE, NULL);	// signaled
	m_hStopWorkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	// non-signaled
	//m_hDequeLock = CreateEvent(NULL, TRUE, FALSE, NULL);	// non-signaled
	//m_hCurrentLock = CreateEvent(NULL, TRUE, FALSE, NULL);	// non-signaled


	//-----------------------------------------------------------
	// Create Thread
	//-----------------------------------------------------------
	m_hWorkThread = CreateThread(NULL, 
								0,	// default stack size
								(LPTHREAD_START_ROUTINE)FileThreadProc,
								NULL,
								NULL,
								&dwChildThreadID);

	SetThreadPriority(m_hWorkThread, 
						priority
						);


	//-----------------------------------------------------------
	// critical section object
	//-----------------------------------------------------------
	InitializeCriticalSection(&m_csDeque);
	InitializeCriticalSection(&m_csCurrent);	

 
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void
MWorkThread::Release()
{
	ReleaseWork();

	//-------------------------------------------------------------
	// �۾� ���� event�� ���������� ��ٸ�
	//-------------------------------------------------------------
	while (IsStopWork());

	//--------------------------------------------
	// event ����
	//--------------------------------------------
	CloseHandle(m_hHasWorkEvent);
	CloseHandle(m_hEndWorkEvent);
	CloseHandle(m_hStopWorkEvent);
	//CloseHandle(m_hDequeLock);
	//CloseHandle(m_hCurrentLock);
	DeleteCriticalSection(&m_csDeque);
	DeleteCriticalSection(&m_csCurrent);

	//--------------------------------------------
	// thread ����
	//--------------------------------------------
	TerminateThread(m_hWorkThread, 0);
	CloseHandle( m_hWorkThread );

	m_hHasWorkEvent = 0;	
	m_hEndWorkEvent = 0;	
	m_hStopWorkEvent = 0;	
	//m_hDequeLock = 0;
	//m_hCurrentLock = 0;
}

//----------------------------------------------------------------------
// ReleaseWork
//----------------------------------------------------------------------
void
MWorkThread::ReleaseWork()
{
	//-------------------------------------------------------------
	// �۾� ���� event
	//-------------------------------------------------------------
	SetEvent( m_hStopWorkEvent );

	//------------------------------------------------------------
	// ���� �۾����� ���� ������..
	//------------------------------------------------------------
	if (!IsFinishCurrentWork())
	{
		//WaitUnlockCurrent();
		LockCurrent();

		if (m_pCurrentWork!=NULL)		// ���� ���� ������ ���
		{
			// �ߴ�			
			m_pCurrentWork->Stop();
		}

		UnlockCurrent();
	}

	//------------------------------------------------------------
	// ���� ���������� ��ٸ���.
	//------------------------------------------------------------
	while (IsWorking());

	//-------------------------------------------------------------
	// deque�� WorkNode���� ��� �����.
	//-------------------------------------------------------------
	//WaitUnlockDeque();
	LockDeque();

	WORKNODE_DEQUE::iterator iNode = m_dequeWorkNode.begin();

	while (iNode != m_dequeWorkNode.end())
	{
		MWorkNode* pNode = *iNode;

		delete pNode;

		iNode ++;
	}

	m_dequeWorkNode.clear();

	UnlockDeque();

	//-------------------------------------------------------------
	// �۾� ���� event����
	//-------------------------------------------------------------
	ResetEvent( m_hStopWorkEvent );
}


//----------------------------------------------------------------------
// Execute
//----------------------------------------------------------------------
void				
MWorkThread::Execute()
{
	MWorkNode* pToRemove = NULL;

	while (1)
	{
		//------------------------------------------------------
		// �� ���� ���� ������ ��ٸ���.
		//------------------------------------------------------
		WaitForSingleObject(m_hHasWorkEvent, INFINITE);

		//------------------------------------------------------
		// deque�� �ϵ��� ��� ó���Ѵ�.
		//------------------------------------------------------
		//WaitUnlockDeque();
		LockDeque();

		int queueSize = m_dequeWorkNode.size();

		UnlockDeque();

		while (queueSize!=0)
		{
			//------------------------------------------------------
			// �� �����Ѵٰ� ǥ��
			//------------------------------------------------------
			ResetEvent( m_hEndWorkEvent );

			//------------------------------------------------------
			// ���� �۾��ϴ� WorkNode�� ����
			//------------------------------------------------------
			//WaitUnlockDeque();
			LockDeque();

			//WaitUnlockCurrent();
			LockCurrent();

			m_pCurrentWork = m_dequeWorkNode.front();

			UnlockCurrent();

			// ���� WorkNode�� �����.
			m_dequeWorkNode.pop_front();

			UnlockDeque();

			//------------------------------------------------------
			// ����
			//------------------------------------------------------
			// execute ���߿� �ߴܵ� ���� �ִ�. (Stop()�� ���ؼ�)
			MWorkNode* pRemainNode = NULL;
			
			if (m_pCurrentWork->Execute(pRemainNode))
			{
				//------------------------------------------------
				// ���������� ��� �۾��� ���� ���
				//------------------------------------------------				
			}
			else
			{
				//------------------------------------------------
				// ������������ �۾��� �ߴܵ� ���
				//------------------------------------------------
				// ������ ����ų�


				//------------------------------------------------
				// Stop�� ����� �� �ִ�. - ���� ���� �ִ� ���
				//------------------------------------------------
				if (pRemainNode!=NULL)
				{
					//------------------------------------------------
					// �ߴܵ� ���				
					// ���� ���� �ٽ� node�� �߰��Ѵ�.
					//------------------------------------------------
					//WaitUnlockDeque();
					LockDeque();

					m_dequeWorkNode.push_front( pRemainNode );			

					UnlockDeque();
				}
			}

			//------------------------------------------------------
			// �۾� ���� ���� �����ٰ� ǥ��
			//------------------------------------------------------
			SetEvent( m_hEndWorkEvent );

			//------------------------------------------------------
			// ������ �������Ƿ� �����Ѵ�.
			//------------------------------------------------------
			pToRemove = m_pCurrentWork;
		
			//WaitUnlockCurrent();
			LockCurrent();

			m_pCurrentWork = NULL;			

			UnlockCurrent();
			
			//-------------------------------------------------------------
			// �۾� ���� event üũ
			//-------------------------------------------------------------
			if (IsStopWork())
			{
				break;
			}

			delete pToRemove;
			pToRemove = NULL;

			//-------------------------------------------------------------
			// �����ִ°� üũ
			//-------------------------------------------------------------
			//WaitUnlockDeque();
			LockDeque();

			queueSize = m_dequeWorkNode.size();

			UnlockDeque();
		}
		
		//------------------------------------------------------
		// ���� ���´ٰ� ǥ��..
		//------------------------------------------------------
		ResetEvent( m_hHasWorkEvent );

		if (pToRemove!=NULL)
		{
			delete pToRemove;
			pToRemove = NULL;
		}
	}
}

//----------------------------------------------------------------------
// Remove
//----------------------------------------------------------------------
// type�� ������ �ִ� �۾����� �ߴ��Ѵ�.
//----------------------------------------------------------------------
void				
MWorkThread::Remove(int type)
{
	//-------------------------------------------------------------
	// �۾� ���� event
	//-------------------------------------------------------------
	SetEvent( m_hStopWorkEvent );

	//------------------------------------------------------------
	// ���� �۾����� �� üũ
	//------------------------------------------------------------
	if (!IsFinishCurrentWork())
	{
		//WaitUnlockCurrent();
		LockCurrent();

		if (m_pCurrentWork!=NULL)
		{
			if (m_pCurrentWork->IsTypeOf(type))
			{
				// ����
				m_pCurrentWork->Stop();
			}
		}

		UnlockCurrent();
	}

	//------------------------------------------------------------
	// ���� ���������� ��ٸ���.
	//------------------------------------------------------------
	while (IsWorking());

	//-------------------------------------------------------------
	// type�� ������ �ִ� deque�� WorkNode���� ��� �����.
	//-------------------------------------------------------------
	//WaitUnlockDeque();
	LockDeque();

	WORKNODE_DEQUE::iterator iNode = m_dequeWorkNode.begin();
	WORKNODE_DEQUE::iterator iNodeTemp;

	while (iNode != m_dequeWorkNode.end())
	{
		MWorkNode* pNode = *iNode;

		//------------------------------------------
		// ���� type�̸� �����.
		//------------------------------------------
		if (pNode->IsTypeOf(type))
		{
			delete pNode;		

			iNodeTemp = iNode;

			iNode ++;

			m_dequeWorkNode.erase( iNodeTemp );
		}
		else
		{
			iNode ++;
		}
	}

	UnlockDeque();

	//-------------------------------------------------------------
	// �ٽ� �� ����..
	//-------------------------------------------------------------
	SetEvent( m_hHasWorkEvent );
}

//----------------------------------------------------------------------
// Add First
//----------------------------------------------------------------------
// ���� �켱 ������ ���� work�μ� �߰���Ų��.
// �ܺο��� new�ؾ� �Ѵ�.
//
// ���� ���� ���� �۾��� �ߴܽ�Ű�� �� �� ���� ���� �ٽ� list�� �߰��ϰ�
// pNode�� �켱������ �����Ѵ�.
//----------------------------------------------------------------------
void				
MWorkThread::AddFirst(MWorkNode* pNode)
{
	if (pNode==NULL)
	{
		return;
	}

	//-------------------------------------------------------------
	// �۾� ���� event
	//-------------------------------------------------------------
	SetEvent( m_hStopWorkEvent );

	//------------------------------------------------------------
	// ���� �۾����� ���� ������..
	//------------------------------------------------------------
	if (!IsFinishCurrentWork())
	{
		//WaitUnlockCurrent();
		LockCurrent();

		if (m_pCurrentWork!=NULL)		// ���� ���� ������ ���
		{
			// �ߴ�			
			m_pCurrentWork->Stop();
		}

		UnlockCurrent();
	}

	//------------------------------------------------------------
	// ���� ���������� ��ٸ���.
	//------------------------------------------------------------
	while (IsWorking());

	//------------------------------------------------------------
	// deque�� ó���� �߰��Ѵ�.
	//------------------------------------------------------------
	//WaitUnlockDeque();
	LockDeque();

	m_dequeWorkNode.push_front( pNode );

	UnlockDeque();

	//------------------------------------------------------------
	// ���� �ִٰ� thread�� �˸���.
	//------------------------------------------------------------
	SetEvent( m_hHasWorkEvent );
}

//----------------------------------------------------------------------
// Add Last
//----------------------------------------------------------------------
// ���� �߰�..
// �ܺο��� new�ؾ� �Ѵ�.
//----------------------------------------------------------------------
void				
MWorkThread::AddLast(MWorkNode* pNode)
{
	if (pNode==NULL)
	{
		return;
	}

	//------------------------------------------------------------
	// ���� ������.. size�� 0�� ���� ��ٸ���.
	//------------------------------------------------------------
	//WaitUnlockDeque();
	LockDeque();

	if (IsFinishCurrentWork() && m_dequeWorkNode.size()==0)
	{
		while (IsWorking());
	}

	//------------------------------------------------------------
	// deque�� ���� �߰��Ѵ�.
	//------------------------------------------------------------
	m_dequeWorkNode.push_back( pNode );

	UnlockDeque();

	
	//------------------------------------------------------------
	// ���� �ִٰ� thread�� �˸���.
	//------------------------------------------------------------
	SetEvent( m_hHasWorkEvent );
}
