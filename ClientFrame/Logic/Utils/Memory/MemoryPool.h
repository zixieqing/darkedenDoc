/********************************************************************
created:	2003/12/05
created:	5:12:2003   13:20
filename: 	MemoryPool.h
file ext:	h
author:		sonee

purpose:	memory pool
			������ ũ�⸦ ����ϰ� new/delete �ϴ� ��� �޸� Ǯ�� ����ϸ�
			�޸� ����ȭ�� ���� �� �ִ�.

			�޸� leak ������ ���� �� �ִ�.

			Debug ����� ��쿡�� �޸𸮰� MEMORY_POOL_GARBAGE ������
			ä������.
*********************************************************************/

#pragma		once

class MemoryPool
{
public :
	MemoryPool( int BlockSize, int BlockCount );
	~MemoryPool();

	void*					Alloc();
	void					Free( void *pMem );

	bool					IsPtrInPool( void *pMem );				// MemoryPool�� �ش� Ptr �� �ִ°�.
	bool					IsAvailablePtr( void *pMem );			// �ش� �������� ��ȿ��

private :
	class CBlock
	{
	public :
		CBlock				*m_pPrev;
		int					m_leftBlocks;
		unsigned char		*m_pNextBlock;
	};

	class CFreeBlock												// Free �� ���� ���� �����͸� �ʿ��ϹǷ�.
	{
	public :
		CFreeBlock			*m_pPrev;
	};

	CBlock					*m_pCurrentBlock;
	CFreeBlock				*m_pFreeBlockList;

	int						m_BlockSize;
	int						m_BlockCount;

};

extern MemoryPool g_CreatureMemoryPool;
extern MemoryPool g_CreatureWearMemoryPool;
extern MemoryPool g_NPCCreatureMemoryPool;
extern MemoryPool g_FakeCreatureMemoryPool;