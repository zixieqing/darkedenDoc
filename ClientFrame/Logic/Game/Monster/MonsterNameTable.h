//----------------------------------------------------------------------
// MonsterNameTable.h
//----------------------------------------------------------------------

#ifndef __MONSTER_NAME_TABLE_H__
#define	__MONSTER_NAME_TABLE_H__

#include <Windows.h>
#include "MString.h"
#include "CTypeTable.h"

class MonsterNameTable {
	public :
		typedef CTypeTable<MString>		STRING_TABLE;

	public :
		MonsterNameTable();
		~MonsterNameTable();

		//------------------------------------------------------------
		// Get Name
		//------------------------------------------------------------
		int			GetFirstNameSize() const	{ return m_FirstNames.GetSize(); }
		int			GetMiddleNameSize() const	{ return m_MiddleNames.GetSize(); }
		int			GetLastNameSize() const		{ return m_LastNames.GetSize(); }

		const char*	GetFirstName(int n) const	{ return ( n<m_FirstNames.GetSize()? m_FirstNames[n].GetString() : NULL ); }	// ������ ���ٰ� ����. - -;
		const char*	GetMiddleName(int n) const	{ return ( n<m_MiddleNames.GetSize()? m_MiddleNames[n].GetString() : NULL ); }
		const char*	GetLastName(int n) const	{ return ( n<m_LastNames.GetSize()? m_LastNames[n].GetString() : NULL ); }

		//------------------------------------------------------------
		// File I/O
		//------------------------------------------------------------
		//void		SaveToFile(class ofstream& file);	// �������� �о�°� ���ٴ� �����Ͽ�.. 
		void		LoadFromFile(class ifstream& file);

	public :
		STRING_TABLE	m_FirstNames;
		STRING_TABLE	m_MiddleNames;
		STRING_TABLE	m_LastNames;
};

extern MonsterNameTable*			g_pMonsterNameTable;

#endif

