//--------------------------------------------------------------------------
// MString.cpp
//--------------------------------------------------------------------------

#include "Client_PCH.h"
#include <stdarg.h>
#include "MString.h"

//#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//--------------------------------------------------------------------------
// static
//--------------------------------------------------------------------------
char MString::s_pBuffer[MAX_BUFFER_LENGTH];

//--------------------------------------------------------------------------
//
// constructor / destructor
//
//--------------------------------------------------------------------------
MString::MString()
{
	m_Length = 0;
	m_pString = NULL;
}

MString::MString(const MString& str)
{
	m_Length = 0;
	m_pString = NULL;
	*this = str;
}

MString::MString(const char* str)
{
	m_Length = 0;
	m_pString = NULL;
	*this = str;
}

MString::~MString()
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;		
	}		
}

//--------------------------------------------------------------------------
//
// member functions
//
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// Init( len )
//--------------------------------------------------------------------------
// size��ŭ memoryȮ��
//--------------------------------------------------------------------------
void	
MString::Init(int len)
{
	Release();

	m_Length = 0;
	m_pString = new char [len + 1];
	m_pString[0] = NULL;
}

//--------------------------------------------------------------------------
// Relase
//--------------------------------------------------------------------------
// memory���� ����
//--------------------------------------------------------------------------
void	
MString::Release()
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;
		m_pString = NULL;
		m_Length = 0;
	}
}

//--------------------------------------------------------------------------
// Assign operator =
//--------------------------------------------------------------------------
void	
MString::operator = (const char* str)
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;
		m_pString = NULL;
	}

	if (str==NULL)
	{
		m_Length = 0;
	}
	else
	{
		m_Length = strlen(str);

		if (m_Length!=0)
		{
			m_pString = new char [m_Length + 1];
			strcpy( m_pString, str );
		}
	}
}

//--------------------------------------------------------------------------
// Assign operator =
//--------------------------------------------------------------------------
void
MString::operator = (const MString& str)
{
	//--------------------------------
	// ���̰� 0�� ���..
	//--------------------------------
	if (str.m_Length==0)
	{
		if (m_pString!=NULL)
		{
			delete [] m_pString;			
			m_pString	= NULL;
			m_Length	= 0;			
		}		
	}
	//--------------------------------
	// ���̰� 0 �̻��� ���...
	//--------------------------------
	else
	{
		if (m_pString!=NULL)
		{
			delete [] m_pString;
		}			
		
		m_Length = str.m_Length;
		m_pString = new char [m_Length + 1];
		
		strcpy(m_pString, str.m_pString);
	}
}

//--------------------------------------------------------------------------
// Format
//--------------------------------------------------------------------------
// ������ �������� string�� �����.
//--------------------------------------------------------------------------
void
MString::Format(const char* format, ...)
{
	va_list		vl;

    va_start(vl, format);
    vsprintf(s_pBuffer, format, vl);
    va_end(vl);

	*this = s_pBuffer;
}

//--------------------------------------------------------------------------
// Save To File
//--------------------------------------------------------------------------
void		
MString::SaveToFile(class ofstream& file)
{
	file.write((const char*)&m_Length, 4);

	// length�� 0�� �ƴ� ��쿡��..
	if (m_Length!=0)
	{
		file.write((const char*)m_pString, static_cast<int>(m_Length));
	}
}

//--------------------------------------------------------------------------
// Load From File
//--------------------------------------------------------------------------
void		
MString::LoadFromFile(class ifstream& file)
{
	if (m_pString!=NULL)
	{
		delete [] m_pString;
		m_pString = NULL;		
	}

	file.read((char*)&m_Length, 4);

	// len�� 0�� �ƴ� ��쿡��...
	if (m_Length!=0)
	{
		m_pString = new char [m_Length + 1];
		file.read((char*)m_pString, static_cast<int>(m_Length));
		m_pString[m_Length] = NULL;
	}
}
