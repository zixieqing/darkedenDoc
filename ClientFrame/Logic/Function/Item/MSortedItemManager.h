//----------------------------------------------------------------------
// MSortedItemManager.h
//----------------------------------------------------------------------

#ifndef __MSORTEDITEMMANAGER_H__
#define __MSORTEDITEMMANAGER_H__

#pragma warning(disable:4786)

class MItem;

class MSortedItemManager : public std::map<ULONGLONG, MItem*> {
	public :
		typedef std::map<ULONGLONG, MItem*>		ITEM_MAP;
		typedef ITEM_MAP::iterator				iterator;
		typedef ITEM_MAP::const_iterator		const_iterator;

	public :
		MSortedItemManager();
		~MSortedItemManager();

		void		Release();											// ��� delete�ϰ� map�� �����.
		void		Clear()		{ m_NumTwoByTwo = 0; clear(); }			// map���� �׳� �����.

		//----------------------------------------------------------
		// 2 x 2�� ����
		//----------------------------------------------------------
		void		SetTwoByTwoNumber(int n);
		int			GetTwoByTwoNumber() const	{ return m_NumTwoByTwo; }

		//----------------------------------------------------------
		// item �߰�
		//----------------------------------------------------------
		bool		AddItem(MItem* pItem);

		//----------------------------------------------------------
		// map�߰�
		//----------------------------------------------------------
		//void		Merge(const MSortedItemManager& sim);

	protected :
		//void		ChangeTwoByTwoPriority(int n);

	protected :
		ULONGLONG	GetKey(MItem* pItem);
		int			m_NumTwoByTwo;
		int			m_NumTwoByTwoTemp;				// �ӽ� - GetKey���� �ʼ�!
};

#endif


