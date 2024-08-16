//------------------------------------------------------------------------
// CToken.cpp
//------------------------------------------------------------------------
#include "Client_PCH.h"
#include "CToken.h"


//------------------------------------------------------------------------
//
// constructor/destructor
//
//------------------------------------------------------------------------
CToken::CToken(const char* str)
{
   m_pString = NULL;
   m_pCurrent = NULL;

   SetString(str);
}

CToken::~CToken()
{
   Release();
}


//------------------------------------------------------------------------
//
// member functions
//
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �޸� ����
//------------------------------------------------------------------------
void
CToken::Release()
{
   if (m_pString!=NULL)
      delete [] m_pString;
}

//------------------------------------------------------------------------
// string�� �ٽ� �����Ѵ�.
//------------------------------------------------------------------------
void
CToken::SetString(const char *str)
{
	Release();
	  
   if (str!=NULL)
   {
      // �޸� ���
      m_pString = new char [strlen(str)+1];

      strcpy(m_pString, str);

      m_pCurrent = m_pString;
   }
}

//------------------------------------------------------------------------
// delimiter�� ���ؼ� ������ token string�� ���Ѵ�.
//------------------------------------------------------------------------
const char*
CToken::GetToken(const char* delimiter)
{
	if (m_pCurrent==NULL)
	{
		return NULL;
	}

	SkipSpace();

   char* pTemp = m_pCurrent;

   // delimiter�� ���ʷ� ��Ÿ���� pointer�� ���Ѵ�.
   char* pFound = strpbrk(m_pCurrent, delimiter);

   // last token
   if (pFound==NULL)
   {
      m_pCurrent = NULL;
   }
   // else
   else
   {
      *pFound = '\0';

      m_pCurrent = pFound+1;
   }

   return pTemp;
}

//------------------------------------------------------------------------
// ���� ��ġ���� �������� string�� �Ѱ��ش�.
//------------------------------------------------------------------------
const char*
CToken::GetEnd()
{
   SkipSpace();

   char* pTemp = m_pCurrent;

   m_pCurrent = NULL;

   return pTemp;
}

//------------------------------------------------------------------------
// ������ ������ ������ �����Ѵ�.
//------------------------------------------------------------------------
void
CToken::SkipSpace()
{
	while (m_pCurrent!=NULL && m_pCurrent!='\0' && *m_pCurrent == ' ')
    {
        m_pCurrent += 1;
    }
}

