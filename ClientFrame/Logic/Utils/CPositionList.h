//----------------------------------------------------------------------
// CPositionList.h
//----------------------------------------------------------------------
// 
// (X,Y)��ǥ�� ���� �ִ� class�̴�.
//
// (X,Y)���� 
// ������ �ǹ��ϰ�����,
// PositionList class�� ���� �� ��ǥ�� ��Ƶ� ���� ���̴�.
//
// PositionList�� list�� �����Ѵ�.
//
//----------------------------------------------------------------------

#ifndef	__CPOSITIONLIST_H__
#define	__CPOSITIONLIST_H__

#include <Windows.h>
#include <list>
//#include <fstream.h>



//----------------------------------------------------------------------
//
// POSITION_NODE class  -  (X,Y) ��ǥ�� �ǹ��Ѵ�.
//
//----------------------------------------------------------------------
template <class Type>
class POSITION_NODE {
	public :
		void	operator = (const POSITION_NODE& node)
		{
			X = node.X;
			Y = node.Y;
		}

		bool	operator == (const POSITION_NODE& node)
		{
			return X==node.X && Y==node.Y;
		}

		bool	operator > (const POSITION_NODE& node)
		{
			if (X > node.X) return true;
			if (X < node.X) return false;
			if (Y > node.Y) return true;
			return false;
		}

		bool	operator < (const POSITION_NODE& node)
		{
			if (X < node.X) return true;
			if (X > node.X) return false;
			if (Y < node.Y) return true;
			return false;
		}

	public :
		Type			X;
		Type			Y;
};



//----------------------------------------------------------------------
//
// CPositionList class  -  POSITION_NODE�� list�̴�.
//
//----------------------------------------------------------------------
template <class Type>
class CPositionList {
	public :
		//----------------------------------------------------------------------
		// IMAGEOBJECT_INFO_LIST�� �����Ѵ�.
		//----------------------------------------------------------------------
		typedef	POSITION_NODE<Type>				POSITION_NODE_TYPE;
		typedef	std::list<POSITION_NODE_TYPE>	POSITION_LIST;

	public :
		CPositionList();
		~CPositionList(); 

		//--------------------------------------------------------------
		// Release
		//--------------------------------------------------------------
		void		Release();

		//--------------------------------------------------------------
		// Add    : (x,y)�� �߰�. �̹� �ִ��� check�غ��� �Ѵ�.
		//--------------------------------------------------------------
		bool		Add(Type x, Type y);

		//--------------------------------------------------------------
		// Remove : (x,y)�� ����
		//--------------------------------------------------------------
		bool		Remove(Type x, Type y);

		//--------------------------------------------------------------
		// Get 
		//--------------------------------------------------------------
		int								GetSize() const		{ return m_listPosition.size(); }
		POSITION_LIST::const_iterator	GetIterator() const	{ return m_listPosition.begin(); }


		//--------------------------------------------------------------
		// File I/O
		//--------------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

	

	protected :
		POSITION_LIST		m_listPosition;

		
		static BYTE			s_SizeOfPositionType;
};


//----------------------------------------------------------------------
// CPositionList.cpp
//----------------------------------------------------------------------

//#include "CPositionList.h"

//----------------------------------------------------------------------
// Init Static Member
//----------------------------------------------------------------------
template <class Type>
BYTE	CPositionList<Type>::s_SizeOfPositionType	= sizeof(Type);

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------
template <class Type>
CPositionList<Type>::CPositionList()
{
}

template <class Type>
CPositionList<Type>::~CPositionList()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
template <class Type>
void
CPositionList<Type>::Release()
{
	m_listPosition.clear();
}

//----------------------------------------------------------------------
// Add(x,y)
//----------------------------------------------------------------------
// (x,y)�� �߰� : �̹� �ִ��� check�غ��� �Ѵ�.
// ���ǻ�.. X, Y������ Sort�ؼ� �߰��Ѵ�.
//----------------------------------------------------------------------
template <class Type>
bool
CPositionList<Type>::Add(Type x, Type y)
{
	// node����
	POSITION_NODE<Type>	node;
	node.X = x;
	node.Y = y;

	POSITION_LIST::iterator iPosition = m_listPosition.begin();

	// �̹� list�� ����ִ� ��� position�� ���غ���
	// ������ ���� �� �߰��Ѵ�.
	while (iPosition != m_listPosition.end())
	{
		// ���� ����ִ°� �߰��ҷ��°ͺ��� Ŭ ���,
		// ���� ��ġ�� �߰��ϸ� �ȴ�.
		if (*iPosition > node)
		{
			m_listPosition.insert(iPosition, node);
			return true;
		}

		// �̹� �ִ� ���̸�
		// �߰����� �ʴ´�.
		if (*iPosition==node)
		{
			return false;
		}

		iPosition++;
	}	

	// list�� ��� ���ҵ麸�� ũ�Ƿ� 
	// list�� ���� �߰��Ѵ�.
	m_listPosition.push_back( node );

	return true;
}

//----------------------------------------------------------------------
// Remove
//----------------------------------------------------------------------
// (x,y)�� ����
//----------------------------------------------------------------------
template <class Type>
bool		
CPositionList<Type>::Remove(Type x, Type y)
{
	// node����
	POSITION_NODE<Type>	node;
	node.X = x;
	node.Y = y;

	POSITION_LIST::iterator iPosition = m_listPosition.begin();

	// list�� POSITION_NODE���� ������ ������ �����.
	while (iPosition != m_listPosition.end())
	{		
		// ���� ���̸� �����.
		if (*iPosition==node)
		{
			m_listPosition.erase(iPosition);
			return true;
		}
		
		// ���� ��ġ�� �ִ� ���� Position���� ũ�ٸ�
		// ��� ū ���� �����Ƿ� Position���� ���� ���̴�.
		if (*iPosition > node)
		{			
			return false;
		}

		iPosition++;
	}	

	// ���� ���
	return false;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
// list�� ���󰡸鼭 ��� position���� file�� �����Ѵ�.
//----------------------------------------------------------------------
template <class Type>
void		
CPositionList<Type>::SaveToFile(class ofstream& file)
{
	//----------------------------------------
	// Size����
	//----------------------------------------
	WORD size = m_listPosition.size();

	file.write((const char*)&size, 2);

	// �ƹ��͵� ������ return
	if (size==0)
		return;


	POSITION_LIST::iterator iPosition = m_listPosition.begin();

	POSITION_NODE<Type>	node;

	//----------------------------------------
	// ������ POSITION_NODE�� �����Ѵ�.
	//----------------------------------------
	while (iPosition != m_listPosition.end())
	{		
		node = *iPosition;

		file.write((const char*)&node.X, s_SizeOfPositionType);
		file.write((const char*)&node.Y, s_SizeOfPositionType);

		iPosition++;
	}	
	
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
template <class Type>
void		
CPositionList<Type>::LoadFromFile(class ifstream& file)
{
	// ������ �ִ� list�� ����
	Release();

	WORD size;

	//----------------------------------------
	// size�� �о�´�.
	//----------------------------------------
	file.read((char*)&size, 2);

	// �ƹ��͵� ������ return
	if (size==0)
		return;

	POSITION_NODE<Type> node;

	//----------------------------------------
	// size������ŭ POSITION_NODE�� �о���鼭
	// list�� �߰���Ų��.
	//----------------------------------------
	for (int i=0; i<size; i++)
	{		
		file.read((char*)&node.X, s_SizeOfPositionType);
		file.read((char*)&node.Y, s_SizeOfPositionType);

		m_listPosition.push_back( node );
	}
}


//----------------------------------------------------------------------
// Test Code
//----------------------------------------------------------------------
/*
template <class Type>
void		
CPositionList<Type>::Print()
{

	POSITION_LIST::iterator iPosition = m_listPosition.begin();

	POSITION_NODE<Type> node;

	while (iPosition != m_listPosition.end())
	{
		node = *iPosition;

		cout << "( " << node.X << ", " << node.Y << " )" << endl;

		iPosition++;
	}
}


void main()
{
	CPositionList<int>	list;
	
	list.Add(10,10);	
	list.Add(16,17);
	list.Add(10,12);
	list.Add(12,17);
	list.Remove(12,16);
	list.Add(10,12);	
	list.Add(11,15);
	list.Add(10,11);
	list.Remove(10,10);
	list.Add(11,15);
	list.Add(10,11);
	list.Remove(12,17);
	list.Add(11,9);
	list.Remove(11,9);
	list.Add(11,9);	
	list.Add(10,7);

	list.Print();
}


//----------
// Result 
//----------
( 10, 7 )
( 10, 11 )
( 10, 12 )
( 11, 9 )
( 11, 15 )
( 16, 17 )


*/


#endif