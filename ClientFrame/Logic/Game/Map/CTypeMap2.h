//----------------------------------------------------------------------
// CTypeMap2.h
//----------------------------------------------------------------------
// DataType�� pointer type�̾�� �Ѵ�.
//
// fstream.h�� fstream�� �浹�� ���ؼ�..
// �ӽ÷�...
// fstream�� ������� �ʴ� version�̴�. - -;
//----------------------------------------------------------------------

#ifndef __CTYPEMAP2_H__
#define	__CTYPEMAP2_H__

#pragma warning(disable:4786)

#include <map>

//----------------------------------------------------------------------
// CTypeMap2 (id, DataType*)�� map
//----------------------------------------------------------------------
template <class DataType>
class CTypeMap2 : public std::map<unsigned int, DataType*> {
	public :
		typedef	std::map<unsigned int, DataType*>	TYPE_MAP;

	public :
		CTypeMap2();
		virtual ~CTypeMap2();

		//-----------------------------------------------------
		// Release
		//-----------------------------------------------------
		virtual void		Release();

		//-----------------------------------------------------
		// Item Info
		//-----------------------------------------------------
		virtual bool		AddData( unsigned int id, DataType* pData );
		virtual DataType*	GetData( unsigned int id );
		virtual const DataType*	GetData( unsigned int id ) const;
		virtual bool		RemoveData( unsigned int id );

	protected :
};



//----------------------------------------------------------------------
//
// CTypeMap2
//
//----------------------------------------------------------------------
template <class DataType>
CTypeMap2<DataType>::CTypeMap2()
{
}

template <class DataType>		
CTypeMap2<DataType>::~CTypeMap2()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
template <class DataType>
void
CTypeMap2<DataType>::Release()
{
	TYPE_MAP::iterator iData = begin();

	while (iData != end())
	{
		DataType*	pData	= (*iData).second;		

		delete pData;

		iData ++;
	}

	clear();
}

//----------------------------------------------------------------------
// Add Data
//----------------------------------------------------------------------
template <class DataType>
bool				
CTypeMap2<DataType>::AddData( unsigned int id, DataType* pData )
{
	TYPE_MAP::iterator	iData = find( id );

	if (iData != end())
	{
		// �̹� �ִ� ���
		// pData�� �ܺο��� ��������Ѵ�.
		return false;
	}

	//------------------------------------------------------
	// ���� ��� --> �߰�
	//------------------------------------------------------
	insert(TYPE_MAP::value_type(id, pData));

	return true;
}

//----------------------------------------------------------------------
// Get Data
//----------------------------------------------------------------------
template <class DataType>
DataType*	
CTypeMap2<DataType>::GetData( unsigned int id )
{
	TYPE_MAP::iterator	iData = find( id );

	if (iData == end())
	{
		// ���� ��� 
		return NULL;
	}

	// �ִ� ���
	return (*iData).second;
}

//----------------------------------------------------------------------
// Get Data
//----------------------------------------------------------------------
template <class DataType>
const DataType*	
CTypeMap2<DataType>::GetData( unsigned int id ) const
{
	TYPE_MAP::const_iterator	iData = find( id );

	if (iData == end())
	{
		// ���� ��� 
		return NULL;
	}

	// �ִ� ���
	return (*iData).second;
}

//----------------------------------------------------------------------
// Remove NPC Info
//----------------------------------------------------------------------
template <class DataType>
bool				
CTypeMap2<DataType>::RemoveData( unsigned int id )
{
	TYPE_MAP::iterator	iData = find( id );

	if (iData == end())
	{
		// ���� ��� 
		return false;
	}

	// ������ ������� �Ѵ�.
	delete (*iData).second;

	erase( iData );

	return true;
}


#endif

