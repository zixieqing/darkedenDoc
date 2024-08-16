//------------------------------------------------------------------------
// CToken.h
//------------------------------------------------------------------------
//													Made by ������(9684050)
//													Coding : 1998.11.
//													Modify : 1998.11.20
//------------------------------------------------------------------------
#ifndef	__CTOKEN_H__
#define	__CTOKEN_H__

#include <string.h>


class CToken {
	public :
		// constructor/destructor
		CToken(const char* str=NULL);
		~CToken();

		// set string
		void SetString(const char* str);

		// ������ ������ ������ �����Ѵ�.
		void SkipSpace();


		// delimiter�� ���ؼ� ������ token string�� ���Ѵ�.
		const char* GetToken(const char* delimiter=" ");

		// ���� ��ġ���� �������� string�� �Ѱ��ش�.
		const char* GetEnd();



	//------------------------------------
	// private member functions
	private :

		// �޸� ����
		void Release();



	//------------------------------------
	// data members
	protected :

		// token���� �������� string
		char* m_pString;

		// m_pString������ ������ ��ġ
		char* m_pCurrent;
};

#endif


