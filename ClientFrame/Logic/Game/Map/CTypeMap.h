//----------------------------------------------------------------------
// CTypeMap.h
//----------------------------------------------------------------------
// DataType�� pointer type�̾�� �Ѵ�.
//----------------------------------------------------------------------

#ifndef __CTYPEMAP_H__
#define	__CTYPEMAP_H__

#pragma warning(disable:4786)

#include <map>
#include <fstream.h>

//----------------------------------------------------------------------
// CTypeMap (id, DataType*)�� map
//----------------------------------------------------------------------
template <class DataType>
class CTypeMap : public std::map<unsigned int, DataType*> {
	public :
		typedef	std::map<unsigned int, DataType*>	TYPE_MAP;

	public :
		CTypeMap();
		virtual ~CTypeMap();

		//-----------------------------------------------------
		// Release
		//-----------------------------------------------------
		virtual void		Release();

		//-----------------------------------------------------
		// Item Info
		//-----------------------------------------------------
		virtual bool		AddData( unsigned int id, DataType* pData );
		virtual DataType*	GetData( unsigned int id );
		virtual bool		RemoveData( unsigned int id );

		//-----------------------------------------------------
		// File I/O
		//-----------------------------------------------------
		virtual void		SaveToFile(class ofstream& file);
		virtual void		LoadFromFile(class ifstream& file);

	protected :
};



//----------------------------------------------------------------------
//
// CTypeMap
//
//----------------------------------------------------------------------
template <class DataType>
CTypeMap<DataType>::CTypeMap()
{
}

template <class DataType>		
CTypeMap<DataType>::~CTypeMap()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
template <class DataType>
void
CTypeMap<DataType>::Release()
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
CTypeMap<DataType>::AddData( unsigned int id, DataType* pData )
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
CTypeMap<DataType>::GetData( unsigned int id )
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
// Remove NPC Info
//----------------------------------------------------------------------
template <class DataType>
bool				
CTypeMap<DataType>::RemoveData( unsigned int id )
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

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
template <class DataType>
void		
CTypeMap<DataType>::SaveToFile(class ofstream& file)
{
	TYPE_MAP::iterator iData = begin();

	//-----------------------------------------------------
	// ���� ����
	//-----------------------------------------------------
	int infoSize = size();
	file.write((const char*)&infoSize, 4);

	//-----------------------------------------------------
	// �� info ����
	//-----------------------------------------------------
	while (iData != end())
	{
		unsigned int	id		= (*iData).first;
		DataType*		pData	= (*iData).second;		

		file.write((const char*)&id, 4);	// id ����
		pData->SaveToFile( file );			// NPC info ����

		iData ++;
	}
}
		
//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
template <class DataType>
void		
CTypeMap<DataType>::LoadFromFile(class ifstream& file)
{
	//-----------------------------------------------------
	// ������ �ִ��� ����
	//-----------------------------------------------------
	Release();

	//-----------------------------------------------------
	// size 
	//-----------------------------------------------------
	int infoSize;
	file.read((char*)&infoSize, 4);

	//-----------------------------------------------------
	// �� info
	//-----------------------------------------------------
	unsigned int id;
	for (int i=0; i<infoSize; i++)
	{		
		file.read((char*)&id, 4);
		DataType*	pData = new DataType;

		pData->LoadFromFile( file );

		//-----------------------------------------------------
		// map�� �߰��Ѵ�.
		//-----------------------------------------------------
		if (!AddData( id, pData ))
		{
			delete pData;
		}
	}
}



#endif

