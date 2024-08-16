//----------------------------------------------------------------------
// MonsterNameTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MonsterNameTable.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MonsterNameTable*			g_pMonsterNameTable = NULL;

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MonsterNameTable::MonsterNameTable()
{
}

MonsterNameTable::~MonsterNameTable()
{
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void
MonsterNameTable::LoadFromFile(class ifstream& file)
{
	m_FirstNames.LoadFromFile( file );
	m_MiddleNames.LoadFromFile( file );
	m_LastNames.LoadFromFile( file );
}