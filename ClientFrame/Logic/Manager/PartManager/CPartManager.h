//----------------------------------------------------------------------
// CPartManager.h
//----------------------------------------------------------------------
// index(IndexType)���� �߿��� 
// �Ϻ�(PartIndexType)�� memory�� ��Ƽ� DataType���� ����ϵ��� �Ѵ�.
//
//----------------------------------------------------------------------
//  Index : PartIndex    PartIndex : Data        : ����Index
//----------------------------------------------------------------------
//	    0 : .					 0 : DataType[4] : 4
//	    1 : .					 1 : DataType[2] : 2
//	    2 : 1					 2 : DataType[3] : 3
//	    3 : 2					 
//	    4 : 0					
//	    5 : .					
//----------------------------------------------------------------------
//
// [�ʿ伺]
//
// �ϳ��� Data�� 1K�̰� ����ҷ��� Data�� Array�� 1�������..
// �� 10M�� �޸𸮰� �ʿ��ϴ�. 
//
// �׷���, ������ 10M�� �޸𸮸� �� Data���� ���ؼ� �Ҵ����ִ°� ������
// 1M������ ������ �־ 1M�� ����Ѵٸ�..??
//
// 1M�� �ش��ϴ� ����(õ��=PartIndexType)��ŭ�� 
// DataType���� �޸𸮸� ��Ƶΰ�
// ������ ��ü Data������ �ش��ϴ� ��ŭ�� Array�� ��Ƶΰ�
// �̰��� ���� Index(����)�� PartIndex(õ��)�� ����Ű���� �Ѵ�.
// ��, ����Index�� ���� PartIndex�� ���ؼ� PartIndex�� �ش��ϴ� 
// Data�� ���� �� �ִ�. 
//
//
// [���� ���] 
//
// �׷��ٸ�, ��� õ��(1M)�� �̿��ؼ� ����(10M)�� ������ ����� �� ������?
//
// �ϴ�.. ��뿡 �ʿ��ϴٴ� ��û�� ���ؼ� 
// PartIndex�� Data�� õ���� Data�� �����Ѵ�.
// (��) Index 1�� Data�� �ʿ��ϴٸ�, 
//      Index 1�� ���� .. PartIndex�� ������ �� PartIndex�� Data�� ����Ѵ�.
//      PartIndex�� ���ٸ�, �� Data�� ���� ����̹Ƿ� Load�ؾ� �Ѵ�.
//      PartIndex�� �� á�ٸ�.. ���� ���� ���� ���� �ϳ� ���־� �ϴµ�,
//      �̶� LRU(Least Recently Used) ����� �̿��Ѵ�.
//      ���Ŵ���� �� PartIndex�� ����Index�� PartIndex���� INDEX_NULL ǥ��
//		...
//
// LRU�� ��� �����ұ�?
//      //���� �������� ����� ���� �˾Ƴ��� �Ѵ�.
//      //Data����� �� ����.. �� index�� '�ֱٽð�' ǥ�ø� �� �д�.
//      //LRU�� ã�ƾ� �� ����.. '�ֱ� �ð�'�� ���� �������ΰ� �����Ѵ�.
//      //��, �̷��Ը� �����ϸ� LRU�� ã�� ��, ��� �� �� �� �ۿ� ���� T_T
//
//      //�ð��� ���� Priority Queue�� ����ϸ� �� ������?
//      //�׷���, �Ϲ����� �߰��ð��� �ӵ��� ���غ��µ�...
//
//      LRU list�� ����Ѵ�.
//
//      PartIndex data�� �̿ܿ� LRU list�� ������ .. ������ ���� ������ �����Ѵ�.
//      LRU list :  MRU ----> LRU 
//
//      �� ���, PartIndexIterator�� �ּ� ���� list�� �ڱ� node�� ����Ű���� �ؾ��Ѵ�.
//
//      [����Ҷ�] partIndex�� iterator�� LRU list�� �����ؼ� �� node�� front�� �ű��.
//      [LRU ã��] LRU list�� back�� LRU index�̴�.
//      [ó�� ������] list�� front�� �߰��ϰ� partIndexIterator�� iterator�� �����Ѵ�.
//
//----------------------------------------------------------------------

#ifndef	__CPARTMANAGER_H__
#define	__CPARTMANAGER_H__

#include <Windows.h>
#include <list>
#include "DebugInfo.h"

template <class IndexType, class PartIndexType, class DataType>
class CPartManager {
	public :
		typedef	std::list<PartIndexType>	PARTINDEX_LIST;				// PartIndex�� ID
		typedef	PARTINDEX_LIST::iterator	PARTINDEX_LIST_ITERATOR;
		
	public :
		CPartManager();
		~CPartManager();

		//-------------------------------------------------------
		// Init/Release
		//-------------------------------------------------------
		void			Init(IndexType maxIndex, PartIndexType maxPart);
		void			Release();

		//-------------------------------------------------------
		// �� index�� ���õ� data�� �����Ǿ� �ִ°�?
		//-------------------------------------------------------
		bool			IsDataNULL(IndexType index)		{ return m_pPartIndex[index]==m_PartIndexNULL; }
		bool			IsDataNotNULL(IndexType index)	{ return m_pPartIndex[index]!=m_PartIndexNULL; }

		//-------------------------------------------------------
		// Get / Set		
		//-------------------------------------------------------
		void			SetData(IndexType index, const DataType& data);
		// return���� bReplace�̴�. ��, ���� ������ �־�����.. true
		IndexType		SetData(IndexType index, const DataType& data, DataType& oldData);
		bool			GetData(IndexType index, DataType& data);

		// ����� PartIndex ����
		PartIndexType	GetUsed() const					{ return m_nPartUsed; }
		IndexType		GetMaxIndex() const				{ return m_nIndex; }
		PartIndexType	GetMaxPartIndex() const			{ return m_nPart; }

	protected :
		//-------------------------------------------------------
		// Least_Recently_Used PartIndex�� ã�Ƴ���.
		//-------------------------------------------------------
		PartIndexType	GetLRU() const;
		DataType&		GetPartData(PartIndexType partIndex)	{ return m_pData[partIndex]; }


	protected :
		//-------------------------------------------------------
		// [Index] ( PartIndex )
		//-------------------------------------------------------
		IndexType			m_nIndex;			// ��ü index ����		
		PartIndexType*		m_pPartIndex;		// Part �ϳ��� ����Ű�� index

		//-------------------------------------------------------
		// [PartIndex] ( Data : ParentIndex : LastTime )
		//-------------------------------------------------------
		PartIndexType		m_nPart;			// Part�� ����
		PartIndexType		m_nPartUsed;		// �̹� ����� Part�� ����
		DataType*			m_pData;			// ���� Data
		IndexType*			m_pParentIndex;		// ������ index
		DWORD*				m_pLastTime;		// ���� ��� �ð�

		//-------------------------------------------------------
		// LRU list
		//-------------------------------------------------------
		PARTINDEX_LIST				m_listLRU;			// LRU list
		PARTINDEX_LIST_ITERATOR*	m_pPartIterator;	// iterator for LRU list
		
		//-------------------------------------------------------
		// ��Ÿ �ʿ��� ��
		//-------------------------------------------------------
		IndexType			m_IndexNULL;		// index NULL ��
		PartIndexType		m_PartIndexNULL;	// part index NULL ��

		//-------------------------------------------------------
		// count
		//-------------------------------------------------------
		DWORD				m_Counter;
};


//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------
template <class IndexType, class PartIndexType, class DataType>
CPartManager<IndexType, PartIndexType, DataType>::CPartManager()
{
	m_nIndex = 0;
	m_pPartIndex = NULL;

	m_nPart = 0;
	m_nPartUsed = 0;
	m_pData = NULL;
	m_pParentIndex = NULL;
	m_pLastTime = NULL;

	// LRU
	m_pPartIterator = NULL;

	// Null��
	m_IndexNULL	= (IndexType)0xFFFFFFFF;
	m_PartIndexNULL = (PartIndexType)0xFFFFFFFF;

	// timer
	m_Counter = 0;
}

template <class IndexType, class PartIndexType, class DataType>
CPartManager<IndexType, PartIndexType, DataType>::~CPartManager()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Init(maxIndex, maxPart)
//----------------------------------------------------------------------
template <class IndexType, class PartIndexType, class DataType>
void		
CPartManager<IndexType, PartIndexType, DataType>::Init(IndexType maxIndex, PartIndexType maxPart)
{
	Release();

	//------------------------------------------------------
	// �κ��� ��ü���� Ŭ���� �����Ƿ�...
	//------------------------------------------------------
	if (maxPart > maxIndex)
	{
		maxPart = maxIndex;
	}

	//------------------------------------------------------
	// PartIndexType�� m_nIndex�� �����Ѵ�.
	//------------------------------------------------------
	m_nIndex = maxIndex;
	m_pPartIndex = new PartIndexType [m_nIndex];

	for (int i=0; i<m_nIndex; i++)
	{
		m_pPartIndex[i] = m_PartIndexNULL;
	}

	//------------------------------------------------------
	// PartIndex���� �κ� ����
	//------------------------------------------------------
	m_nPart			= maxPart;
	m_nPartUsed		= 0;
	m_pData			= new DataType [m_nPart];
	m_pParentIndex	= new IndexType [m_nPart];	// ������ index
	m_pLastTime		= new DWORD [m_nPart];		// ���� ��� �ð�
	
	//------------------------------------------------------
	// LRU list
	//------------------------------------------------------
	m_listLRU.clear();
	m_pPartIterator		= new PARTINDEX_LIST_ITERATOR [m_nPart];	// iterator

	for (i=0; i<m_nPart; i++)
	{
		m_pData[i] = NULL;
		m_pParentIndex[i] = m_IndexNULL;
		m_pLastTime[i] = 0;

		m_pPartIterator[i] = m_listLRU.end();
	}

	m_Counter = 0;
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
template <class IndexType, class PartIndexType, class DataType>
void		
CPartManager<IndexType, PartIndexType, DataType>::Release()
{
	if (m_pPartIndex!=NULL)
	{
		delete [] m_pPartIndex;
		m_pPartIndex = NULL;
		m_nIndex = 0;
	}

	if (m_pData!=NULL)
	{
		delete [] m_pData;
		m_pData = NULL;
		m_nPart = 0;
		m_nPartUsed = 0;
	}

	if (m_pParentIndex!=NULL)
	{
		delete [] m_pParentIndex;
		m_pParentIndex = NULL;
	}

	if (m_pLastTime!=NULL)
	{
		delete [] m_pLastTime;
		m_pLastTime = NULL;
	}
	
	if (m_pPartIterator!=NULL)
	{
		delete [] m_pPartIterator;
		m_pPartIterator = NULL;
	}

	m_listLRU.clear();
}

//----------------------------------------------------------------------
// Set Data
//----------------------------------------------------------------------
// index��° data�� �߰���Ų��.
// �̹� ������ΰ� �ִ��� ���������.
//----------------------------------------------------------------------
template <class IndexType, class PartIndexType, class DataType>
void
CPartManager<IndexType, PartIndexType, DataType>::SetData(IndexType index, const DataType& data)
{
	// �߰��� ��ġ
	PartIndexType	newPartIndex = GetLRU();

	//------------------------------------------------------------
	// ���� �ִ��� ����
	//------------------------------------------------------------		
	IndexType oldIndex = m_pParentIndex[newPartIndex];
	if (oldIndex != m_IndexNULL)
	{
		// ������ PartIndex�� �����ִ� index�� null�� �ٲ۴�.		
		m_pPartIndex[oldIndex] = m_PartIndexNULL;
		m_pParentIndex[newPartIndex] = m_IndexNULL;	
	}

	//------------------------------------------------------------
	// ���� ����
	//------------------------------------------------------------
	// link ����
	m_pPartIndex[index] = newPartIndex;
	m_pParentIndex[newPartIndex] = index;

	// data ����
	m_pData[newPartIndex] = data;

	// ���� ��� �ð� : counter�� ������ų �ʿ�� ����.
	m_pLastTime[newPartIndex] = m_Counter;

	//------------------------------------------------------------
	// LRU list
	//------------------------------------------------------------
	// front�� ���� �ֱٿ� ���� ���̴�.
	// m_pPartIterator[]���� �� partIndex�� iterator�� �����Ѵ�.
	m_listLRU.push_front( newPartIndex );
	m_pPartIterator[newPartIndex] = m_listLRU.begin();
	
	// ����� ���� ����
	if (m_nPartUsed < m_nPart) 
		m_nPartUsed++;
}

//----------------------------------------------------------------------
// Set Data
//----------------------------------------------------------------------
// index��° data�� �߰���Ų��.
// �̹� ������ΰ� ������ �Ѱ��ش�.
//
// return���� ���ŵǴ� data�� index�̴�.
// m_IndexNULL�̸� ���� ��..
//----------------------------------------------------------------------
template <class IndexType, class PartIndexType, class DataType>
IndexType
CPartManager<IndexType, PartIndexType, DataType>::SetData(IndexType index, const DataType& data, DataType& oldData)
{
	// �߰��� ��ġ
	PartIndexType	newPartIndex = GetLRU();

	//bool bReplace = false;
	//------------------------------------------------------------
	// ���� �ִ��� ����
	//------------------------------------------------------------	
	IndexType oldIndex = m_pParentIndex[newPartIndex];
	if (oldIndex != m_IndexNULL)
	{
		// ������ PartIndex�� �����ִ� index�� null�� �ٲ۴�.		
		m_pPartIndex[oldIndex] = m_PartIndexNULL;
		m_pParentIndex[newPartIndex] = m_IndexNULL;

		// ���� �ִ��� �Ѱ��ش�.
		oldData = m_pData[newPartIndex];

		//bReplace = true;
	}

	//------------------------------------------------------------
	// ���� ����
	//------------------------------------------------------------
	// link ����
	m_pPartIndex[index] = newPartIndex;
	m_pParentIndex[newPartIndex] = index;

	// data ����
	m_pData[newPartIndex] = data;

	// ���� ��� �ð� 
	m_pLastTime[newPartIndex] = m_Counter++;

	//------------------------------------------------------------
	// LRU list
	//------------------------------------------------------------
	// front�� ���� �ֱٿ� ���� ���̴�.
	// m_pPartIterator[]���� �� partIndex�� iterator�� �����Ѵ�.
	if (m_pPartIterator[newPartIndex]!=m_listLRU.end())
	{
		m_listLRU.erase( m_pPartIterator[newPartIndex] );		// ����
	}
	m_listLRU.push_front( newPartIndex );
	m_pPartIterator[newPartIndex] = m_listLRU.begin();
	
	//---------------------------------------------------
	// [ TEST CODE ]
	/*
	PARTINDEX_LIST_ITERATOR	iIndex = m_listLRU.begin();

	char str[1024] = "[SetData] ";
	char str2[256];
	while (iIndex != m_listLRU.end())
	{
		sprintf(str2, "%d ", *iIndex);
		strcat(str, str2);

		iIndex++;
	}
	DEBUG_ADD(str);
	*/
	//---------------------------------------------------
	
	// ����� ���� ����
	if (m_nPartUsed < m_nPart) 
		m_nPartUsed++;

	//return bReplace;

	return oldIndex;
}


//----------------------------------------------------------------------
// Get Data
//----------------------------------------------------------------------
// �ܺο��� index��° data�� ��´�.
// ���� ������? LRU�� �����Ѵ�.
//----------------------------------------------------------------------
template <class IndexType, class PartIndexType, class DataType>
bool
CPartManager<IndexType, PartIndexType, DataType>::GetData(IndexType index, DataType& data)
{
	PartIndexType partIndex = m_pPartIndex[index];

	//------------------------------------------------------
	// ������� Data�� ���� ��� return���ش�.
	//------------------------------------------------------
	if (partIndex==m_PartIndexNULL)
	{
		return false;
	}

	// ��� �ð� check
	m_pLastTime[partIndex] = m_Counter++;

	//------------------------------------------------------
	// LRU list���� ���� partIndex�� 
	// ���� �ֱٿ� ����� �ɷ� �ٲ۴�.
	//------------------------------------------------------
	// iterator�� �̿��ؼ� ������ �ٲ۴�.
	if (m_pPartIterator[partIndex]!=m_listLRU.end())
	{
		m_listLRU.erase( m_pPartIterator[partIndex] );		// ����
	}
	m_listLRU.push_front( partIndex );				// �߰�
	m_pPartIterator[partIndex] = m_listLRU.begin();		// iterator �ٽ� ����

	//---------------------------------------------------
	// [ TEST CODE ]
	/*
	PARTINDEX_LIST_ITERATOR	iIndex = m_listLRU.begin();

	char str[1024] = "[GetData] ";
	char str2[256];
	while (iIndex != m_listLRU.end())
	{
		sprintf(str2, "%d ", *iIndex);
		strcat(str, str2);

		iIndex++;
	}
	DEBUG_ADD(str);
	*/
	//---------------------------------------------------


	//------------------------------------------------------
	// counter�� ���̸�.. ����~~
	//------------------------------------------------------
	if (m_Counter==0xFFFFFFFF)
	{
		// ���� ������ �ð��� ã�Ƽ�...
		// �� �ð��� 0���� �����. --> ��� �� �ð���ŭ ����.
		int leastTimeIndex = 0;
		int maxTimeIndex = 0;
		for (int i=1; i<m_nPart; i++)
		{
			// ���� ���� �ð�
			if (m_pLastTime[i] < m_pLastTime[leastTimeIndex])
			{
				leastTimeIndex = i;
			}

			// ���� ū �ð�
			if (m_pLastTime[i] > m_pLastTime[maxTimeIndex])
			{
				maxTimeIndex = i;
			}
		}

		// ��� ���� ���� �ð���ŭ ����.
		int leastTime = m_pLastTime[leastTimeIndex];
		for (i=0; i<m_nPart; i++)
		{
			m_pLastTime[i] -= m_pLastTime[leastTimeIndex];
		}

		// Counter�� ���粨 �߿��� ���� ū �ð��� ���̴�.
		m_Counter = m_pLastTime[maxTimeIndex];
	}

	// �Ѱ��� data����
	data = m_pData[partIndex];

	return true;
}

//----------------------------------------------------------------------
// Get LRU
//----------------------------------------------------------------------
// ���� �������� ���� ���� PartIndex�� return�Ѵ�.
//----------------------------------------------------------------------
template <class IndexType, class PartIndexType, class DataType>
PartIndexType
CPartManager<IndexType, PartIndexType, DataType>::GetLRU() const
{
	//---------------------------------------------------
	// m_nPart�� �߿��� ���� �� �� ���°� �ƴϸ�...
	// ������� ������ PartIndex�� �Ѱ��ش�.
	//---------------------------------------------------
	if (m_nPartUsed < m_nPart)
	{	
		//DEBUG_ADD_FORMAT("[LRU] %d", m_nPartUsed);
		return m_nPartUsed;		
	}

	//---------------------------------------------------
	// LRU list�� tail�� LRU index�̴�.
	//---------------------------------------------------
	PartIndexType leastTimeIndex = *m_listLRU.rbegin();


	//---------------------------------------------------
	// [ TEST CODE ]
	/*
	PARTINDEX_LIST::const_iterator	iIndex = m_listLRU.begin();

	char str[1024] = "[GetLRU] ";
	char str2[256];
	while (iIndex != m_listLRU.end())
	{
		sprintf(str2, "%d ", *iIndex);
		strcat(str, str2);

		iIndex++;
	}
	DEBUG_ADD(str);
	*/
	//---------------------------------------------------

	//---------------------------------------------------
	// ��ü�� �˻��ؼ� ���� �������� ���� �� ã�´�.
	//---------------------------------------------------
	/*
	PartIndexType leastTimeIndex = 0;

	for (int i=1; i<m_nPart; i++)
	{
		// ���� ���� �ð�
		if (m_pLastTime[i] < m_pLastTime[leastTimeIndex])
		{
			leastTimeIndex = i;
		}
	}
	*/

	//---------------------------------------------------
	// ���� �������� ���� ���� PartIndex
	//---------------------------------------------------
	//DEBUG_ADD_FORMAT("[LRU] %d", leastTimeIndex);
	return leastTimeIndex;
}


#endif
