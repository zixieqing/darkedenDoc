/********************************************************************
	created:	2003/12/05
	created:	5:12:2003   13:40
	filename: 	MemoryPool.cpp
	file ext:	cpp
	author:		sonee	// ������ �ٺ�
	
	purpose:	memory pool
				������ ũ�⸦ ����ϰ� new/delete �ϴ� ��� �޸� Ǯ�� ����ϸ�
				�޸� ����ȭ�� ���� �� �ִ�.

				�޸� leak ������ ���� �� �ִ�.

				Debug ����� ��쿡�� �޸𸮰� MEMORY_POOL_GARBAGE ������
				ä������.
*********************************************************************/
#include "Client_PCH.h"
#include <windows.h>
#include <memory.h>
#include "MemoryPool.h"

#include "MNPC.h"
#include "MFakeCreature.h"


MemoryPool g_CreatureMemoryPool( sizeof( MCreature ), 30 );
MemoryPool g_CreatureWearMemoryPool( sizeof( MCreatureWear ), 30 );
MemoryPool g_NPCCreatureMemoryPool( sizeof( MNPC ), 5 );
MemoryPool g_FakeCreatureMemoryPool( sizeof( MFakeCreature ), 30 );

MemoryPool::MemoryPool( int BlockSize, int BlockCount )
: m_pCurrentBlock ( NULL ), m_pFreeBlockList( NULL ), m_BlockSize( BlockSize ), m_BlockCount( BlockCount )
{
	if( BlockSize < sizeof( void* ) )
	{
		// -_- ������ ũ�⺸�� ������ ������ ���� �Ͱ�����-_-;
		m_BlockSize = sizeof( void* );
	}
}

MemoryPool::~MemoryPool()
{
	while( m_pCurrentBlock != NULL )
	{
		CBlock *pPrev = m_pCurrentBlock->m_pPrev;
		free( m_pCurrentBlock );

		m_pCurrentBlock = pPrev;
	}
}

void*		MemoryPool::Alloc()
{
	void *pMem;

	if( m_pFreeBlockList != NULL )					// FreeList �� �����ִ°��� �ִٸ�, �� �޸� �ּҸ� ����.
	{
		pMem = m_pFreeBlockList;

		m_pFreeBlockList = m_pFreeBlockList->m_pPrev;
		return pMem;
	}

	if( m_pCurrentBlock == NULL || m_pCurrentBlock->m_leftBlocks <= 0 )
	{
		// �޸� Pool �� �Ҵ�Ǿ� ���� �ʰų�, �Ҵ��� �޸𸮸� �� ����Ͽ��� ��쿡,
		// ���� �Ҵ��ϰ�, ������ �����͸� ������ ���´�.
		CBlock *pPool = (CBlock*)( ::operator new( sizeof(CBlock) + ( m_BlockSize * m_BlockCount )) );

		if( pPool == NULL )
		{
			return NULL;
		}

#ifdef _DEBUG
//		memset( (unsigned char*)(pPool) + sizeof( CBlock ), MEMORY_POOL_GARBAGE, m_BlockSize * m_BlockCount );
#endif
		pPool->m_pPrev = m_pCurrentBlock;
		pPool->m_leftBlocks = m_BlockCount;
		pPool->m_pNextBlock = reinterpret_cast<unsigned char*>( (pPool + 1) );

		m_pCurrentBlock = pPool;
	}	

	pMem = m_pCurrentBlock->m_pNextBlock;
	m_pCurrentBlock->m_pNextBlock += m_BlockSize;
	m_pCurrentBlock->m_leftBlocks --;

	return pMem;
}

void		MemoryPool::Free( void *pMem )
{
#ifdef _DEBUG
//	memset( pMem, MEMORY_POOL_GARBAGE, m_BlockSize );
#endif
	CFreeBlock *pBlock = reinterpret_cast<CFreeBlock*>(pMem);

	pBlock->m_pPrev = m_pFreeBlockList;
	m_pFreeBlockList = pBlock;
}

bool		MemoryPool::IsPtrInPool( void *pMem )
{
	CBlock *pCurBlock = m_pCurrentBlock;
	
	while( pCurBlock != NULL )
	{
        if( ( (unsigned char*)(pCurBlock) + sizeof( CBlock ) ) <= pMem && 
			( (unsigned char*)(pCurBlock) + sizeof( CBlock ) + m_BlockSize * m_BlockCount ) > pMem )
			return true;

		pCurBlock = pCurBlock->m_pPrev;
	}
	return false;
}

//----------------------------------------------------------------------------------
//
// �Ҵ�� �޸𸮾ȿ� �����鼭, FreeList �� ������ -_- ��ȿ�� �޸��̴�.
//
//----------------------------------------------------------------------------------
bool		MemoryPool::IsAvailablePtr( void *pMem )
{
	CBlock *pCurBlock = m_pCurrentBlock;

	bool bIsInPool = false;
	
	while( pCurBlock != NULL )
	{
		if( ( (unsigned char*)(pCurBlock) + sizeof( CBlock ) <= pMem ) &&
			( (unsigned char*)(pCurBlock) + sizeof( CBlock ) + m_BlockSize * m_BlockCount > pMem ) )
		{
			bIsInPool = true;
			break;
		}

		pCurBlock = pCurBlock->m_pPrev;
	}
	if( !bIsInPool ) return false;
	
	CFreeBlock *pFreeBlock = m_pFreeBlockList;
	
	while( pFreeBlock != NULL )
	{
		if( pFreeBlock <= pMem && (pFreeBlock + m_BlockSize * m_BlockCount) > pMem )
			return false;

		pFreeBlock = pFreeBlock->m_pPrev;
	}

	return true;
}