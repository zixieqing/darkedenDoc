//----------------------------------------------------------------------
// MSortedItemManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MSortedItemManager.h"
#include "MItem.h"

#define	TWO_BY_TWO_PACKING_SIZE		12

//----------------------------------------------------------------------
//
// constructor / destructor
// 
//----------------------------------------------------------------------
MSortedItemManager::MSortedItemManager()
{
	m_NumTwoByTwo = 0;
	m_NumTwoByTwoTemp = 0;
}

MSortedItemManager::~MSortedItemManager()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
// ��� delete�ϰ� map�� �����.
//----------------------------------------------------------------------
void		
MSortedItemManager::Release()
{
	ITEM_MAP::iterator iItem = begin();

	while (iItem != end())
	{
		MItem* pItem = iItem->second;

		if (pItem!=NULL)
		{
			delete pItem;
		}

		iItem++;
	}

	clear();
}

//----------------------------------------------------------------------
// Set Two By Two Number
//----------------------------------------------------------------------
void		
MSortedItemManager::SetTwoByTwoNumber(int n)
{ 
	m_NumTwoByTwo = n; 
	m_NumTwoByTwoTemp = (n/3) * 3;
}

//----------------------------------------------------------------------
// Add Item
//----------------------------------------------------------------------
bool		
MSortedItemManager::AddItem(MItem* pItem)
{
	ULONGLONG key = GetKey( pItem );

	ITEM_MAP::const_iterator iItem = find( key );	// �ǹ� ������ - -;

	// ������ �߰��Ѵ�.
	if (iItem == end())
	{
		insert( ITEM_MAP::value_type( key, pItem ) );

		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// Get Key
//----------------------------------------------------------------------
//
// key�� 8 byte�̰� ����byte����..
//
// 4 Byte : gridWidth*gridHeight
// 4 Byte : ItemObjectID
//
// �� ǥ���ȴ�.
//----------------------------------------------------------------------
// m_NumTwoByTwoTemp���� �켱 ������ ������ 
//							2x2�������� ������ �����Ǿ�� �Ѵ�.
//----------------------------------------------------------------------
ULONGLONG		
MSortedItemManager::GetKey(MItem* pItem)
{
	TYPE_OBJECTID itemObjectID= pItem->GetID();

	// item�� grid ũ��
	int gridWidth		= pItem->GetGridWidth();
	int gridHeight		= pItem->GetGridHeight();
	int gridSize		= gridWidth*gridHeight;
	
	if (gridSize==4)	//gridWidth==2 && gridHeight==2)
	{
		if (m_NumTwoByTwoTemp > 0)
		{
			m_NumTwoByTwoTemp --;

			gridSize = TWO_BY_TWO_PACKING_SIZE;	// 2x2 3���� ���̸� 12�� �ȴ�.
		}
	}

	// ū�ͺ��� sort�ϱ� ���ؼ�...
	gridSize = 0xFF - gridSize;

	// item�� grid���� ��ǥ
	//int gridX			= pItem->GetGridX();
	//int gridY			= pItem->GetGridY();

	ULONGLONG key = gridSize;	//(gridSize << 16) | (gridX << 8) | gridY;

	key = (key << 32) | itemObjectID;

	return key;
}

//----------------------------------------------------------------------
// Merge
//----------------------------------------------------------------------
// �ٸ� map�� �߰��Ѵ�.
//----------------------------------------------------------------------
/*
void		
MSortedItemManager::Merge(const MSortedItemManager& sim)
{
	//----------------------------------------------------------------
	//
	//		2x2 size �������� ���� �Ǵ�
	//
	//----------------------------------------------------------------
	// ������ �������� �ʰ� �����ִ� 2x2 size�� ������ ����
	//----------------------------------------------------------------
	int numOldReminder = m_NumTwoByTwo%3;		// ������ �ִ��� �߿���.. 
	
	int numNewReminder = sim.m_NumTwoByTwo%3;	// ���� �߰��Ǵ� �� �߿���..

	//----------------------------------------------------------------
	// �� map�� ��������.. 3�� �̻��� ���´ٸ�.. 	
	//----------------------------------------------------------------
	if (numOldReminder+numNewReminder >= 3)
	{		
		// ������ �ִ� map���� ������ ��� ����� �Ѵ�.
		ChangeTwoByTwoPriority( numOldReminder );
	}

	//----------------------------------------------------------------
	// ���� �߰��Ҷ�.. 2x2�������� ���� ����..
	//----------------------------------------------------------------
	m_NumTwoByTwoTemp = (sim.m_NumTwoByTwo/3)*3 + (3-numOldReminder);

	//----------------------------------------------------------------
	// this�� sim�� �����۵��� �߰���Ų��.
	//----------------------------------------------------------------
	ITEM_MAP::const_iterator iItem = sim.begin();

	while (iItem != sim.end())
	{
		ULONGLONG	key		= iItem->first;
		MItem*		pItem	= iItem->second;

		//AddItem( pItem ); 

		// �ӵ��� ���ؼ�.. �̰Ÿ� �θ��°� ���� - -;
		insert( ITEM_MAP::value_type( key, pItem ) );					

		iItem++;
	}

	//----------------------------------------------------------------
	// ���� �ٽ� ����
	//----------------------------------------------------------------
	m_NumTwoByTwo = m_NumTwoByTwo + sim.m_NumTwoByTwo;
}
*/

//----------------------------------------------------------------------
// ChangeTwoByTwoPriority ( ���� )
//----------------------------------------------------------------------
// TwoByTwo �����۵��� ã�Ƽ� Priority�� ������Ų��. - -;
//----------------------------------------------------------------------
/*
void
MSortedItemManager::ChangeTwoByTwoPriority(int n)
{	
	//-------------------------------------------------
	// ����..
	//-------------------------------------------------
	if (n <= 0)
	{
		return;
	}

	//-------------------------------------------------
	// default 2x2 ������ size
	//-------------------------------------------------
	const ULONGLONG TwoByTwoGridSize = 0xFF - 2*2;
	const ULONGLONG TwoByTwoPackingGridSize = 0xFF - TWO_BY_TWO_PACKING_SIZE;
	
	ITEM_MAP::iterator iItem = begin();
	ITEM_MAP::iterator iItemTemp;

	while (n>0 && iItem != end())
	{
		ULONGLONG	key		= iItem->first;
		MItem*		pItem	= iItem->second;

		//-------------------------------------------------
		// 2x2 �̸�...
		//-------------------------------------------------
		if ((key >> 32) == TwoByTwoGridSize)
		{
			iItemTemp = iItem;

			iItem++;

			//-------------------------------------------------
			// ���� �ߴٰ�
			//-------------------------------------------------
			erase( iItemTemp );

			key = (TwoByTwoPackingGridSize << 32) | (key & 0xFFFFFFFF);

			//-------------------------------------------------
			// �ٽ� �߰�
			//-------------------------------------------------
			// �߰��ɶ���.. �켱 ������ �����Ƿ�
			// ���� iterating������ ������ ����..�� ���� - -;
			insert( ITEM_MAP::value_type(key, pItem) );			

			//-------------------------------------------------
			// ���� ����
			//-------------------------------------------------
			n--;
		}
		else
		{
			iItem++;
		}
	}
}
*/