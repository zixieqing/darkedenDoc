//----------------------------------------------------------------------
// MStorage.h
//----------------------------------------------------------------------
// 
// �������̴�.
//
// current�� �����ؼ� ���翡 ������� ��~�� ������ �� �ִ�.
//----------------------------------------------------------------------
/*

	= �������� 3���� �ִٰ� �����ϰ�... 

	MStorage*	pStorage = ....;


	[ ������ �ٲ� �� ]

		pStorage->SetCurrent( n );		// n��° �����Կ� �����Ѵ�.


	[ ���� �������� �����Թ�ȣ �˾Ƴ��� ]

		int n = pStorage->GetCurrent();


	[ �������� �������� slot�� �ִ� item �о���� ]
	
		const MItem* pItem = pStorage->GetItem( slot );

*/
//----------------------------------------------------------------------

#ifndef __MSTORAGE_H__
#define	__MSTORAGE_H__

#include "MItem.h"
#include "MGameDef.h"
#include "MMoneyManager.h"

class MStorage {
	public :
		MStorage();
		~MStorage();

		//-------------------------------------------------------
		// Init / Release
		//-------------------------------------------------------
		void				Init(unsigned int size);
		void				Release();

		//-------------------------------------------------------		
		// Active - �������� ���ִ� �����ΰ�?
		//-------------------------------------------------------		
		bool				IsActive() const	{ return m_bActive; }
		void				SetActive()			{ m_bActive = true; }
		void				UnSetActive()		{ m_bActive = false; }
	
		//-------------------------------------------------------		
		// Size
		//-------------------------------------------------------		
		unsigned int		GetSize() const		{ return m_Size; }

		//-------------------------------------------------------
		// Item
		//-------------------------------------------------------		
		bool				SetItem(unsigned int slot, MItem* pItem);
		MItem*				RemoveItem(unsigned int slot);
		const MItem*		GetItem(unsigned int slot) const;

		//-------------------------------------------------------		
		// ���� ���� ���� shelf
		//-------------------------------------------------------		
		void				SetCurrent(unsigned int n);
		unsigned int		GetCurrent() const			{ return m_CurrentStorage; }		

		void				SetPersnalMessage(char * str) { m_pPersnalMsg = str;}
		char *				GetPersnalMessage() { return m_pPersnalMsg; }		

		void				SetCuropenid(DWORD id) { m_curopenid = id;}
		DWORD				GetCuropenid() { return m_curopenid; }		


		//-------------------------------------------------------		
		// Money
		//-------------------------------------------------------		
		MMoneyManager*		GetMoneyManager() const		{ return m_pMoneyManager; }

	protected :
		bool				m_bActive;		// ������ �۵����ΰ�?

		unsigned int		m_Size;			// ��ü ������ ����

		MItem***			m_pStorage;		// item������

		// ���� ������� storage
		unsigned int		m_CurrentStorage;

		// ��
		MMoneyManager*		m_pMoneyManager;
		char		*	    m_pPersnalMsg;
		DWORD				m_curopenid;
};

extern MStorage*		g_pStorage;
extern MStorage*		g_pStorage2;
extern MStorage*		g_pStorageTemp;

#endif


