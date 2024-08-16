//----------------------------------------------------------------------
// MSlotItemManager.h
//----------------------------------------------------------------------
// Ư���� Slot ������~~�� MItem�� ����~�ؼ� ����� �� �ְ� �Ѵ�.
//
// �� Slot���� �ϳ��� Item�� �� �� �ִ�.
//----------------------------------------------------------------------

#ifndef	__MSLOTITEMMANAGER_H__
#define	__MSLOTITEMMANAGER_H__


#include "MItemManager.h"


class MSlotItemManager : public MItemManager {
	public :
		MSlotItemManager();
		~MSlotItemManager();

		//------------------------------------------------------
		// Init / Release
		//------------------------------------------------------
		void		Init(BYTE size);
		void		Release();

		//------------------------------------------------------
		// get
		//------------------------------------------------------
		BYTE		GetSize() const	{ return m_Size; }
	
		//------------------------------------------------------
		// Add / Get / Remove
		//------------------------------------------------------		
		bool			AddItem(MItem* pItem, BYTE n);		// slot(n)�� pItem�� �߰��Ѵ�.

		MItem*			GetItem(BYTE n) const;				// slot(n)�� item�� �о�´�.
		
		MItem*			RemoveItem(BYTE n);					// slot(n)�� item�� �����Ѵ�.
		MItem*			RemoveItem(TYPE_OBJECTID id);		// id�� ���� item�� �����Ѵ�.

		bool			ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem);	// (n)��ġ�� Item��ȯ

		bool			CanReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem);


	protected :
		BYTE			m_Size;
		MItem**			m_ItemSlot;
};

#endif


