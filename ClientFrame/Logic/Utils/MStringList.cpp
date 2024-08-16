//----------------------------------------------------------------------
// MStringList.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MStringList.h"

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MStringList::MStringList()
{
}

MStringList::~MStringList()
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
void
MStringList::Release()
{
	iterator iString = begin();

	while (iString != end())
	{
		MString* pString = *iString;

		if (pString!=NULL)
		{
			delete pString;
		}

		iString++;
	}

	clear();
}

//----------------------------------------------------------------------
// Add String
//----------------------------------------------------------------------
// list�� ���� str�� �߰��Ѵ�.
//----------------------------------------------------------------------
void			
MStringList::AddString(const char* str)
{
	MString* pString = new MString(str);

	push_back( pString );
}

//----------------------------------------------------------------------
// Get Iterator
//----------------------------------------------------------------------
// index��° iterator�� ��´�.
// 0-based
//----------------------------------------------------------------------
MStringList::STRING_LIST::iterator		
MStringList::GetIterator(unsigned int index)
{
	// �Ѱ踦 �Ѿ�� ���
	if (index>=size())
	{
		return end();
	}

	iterator iString = begin();

	for (int i=0; i<index; i++)
	{
		iString++;
	}

	return iString;
}