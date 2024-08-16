//----------------------------------------------------------------------
// MPlayerGear.cpp
//----------------------------------------------------------------------
// Player�� Gear�� ���� class
//----------------------------------------------------------------------

#ifndef __MPLAYERGEAR_H__
#define __MPLAYERGEAR_H__

#include "MSlotItemManager.h"

class MPlayerGear : public MSlotItemManager {
	public :
		enum ITEM_STATUS
		{
			ITEM_STATUS_OK,					// ���� ����
			ITEM_STATUS_SOMEWHAT_BROKEN,		// �ణ �μ��� - -;
			ITEM_STATUS_ALMOST_BROKEN		// ���� �μ���
		};

	public :
		MPlayerGear();
		~MPlayerGear();

		//------------------------------------------------------
		// Init / Release
		//------------------------------------------------------
		void			Init(BYTE size);
		void			Release();

		//------------------------------------------------------
		// Add / Get / Remove
		//------------------------------------------------------		
		bool			AddItem(MItem* pItem, BYTE n);		// slot(n)�� pItem�� �߰��Ѵ�.

		MItem*			GetItem(BYTE n) const;				// slot(n)�� item�� �о�´�.
		
		MItem*			RemoveItem(BYTE n);					// slot(n)�� item�� �����Ѵ�.
		MItem*			RemoveItem(TYPE_OBJECTID id);		// id�� ���� item�� �����Ѵ�.

		bool			ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem);	// (n)��ġ�� Item��ȯ

		//------------------------------------------------------
		// Item ��ȭ
		//------------------------------------------------------
		bool			ModifyDurability(BYTE n, int changeValue);

		//------------------------------------------------------
		// �μ������� �������� �ִ°�?
		//------------------------------------------------------
		ITEM_STATUS		GetItemStatus(int slot) const	{ return m_pItemStatus[slot]; }
		BOOL			HasBrokenItem() const			{ return m_nBrokenItem!=0; }
		void			CheckItemStatusAll();

	protected :
		//virtual void	CheckItemStatusAll() = 0;	// �ʿ� ���� ��..
		void			SetItemStatusOK(int slot);	// slot��°�� ��~���� �����.
		void			CheckItemStatus(const MItem* pItem, int slot);
		
	protected :
		int				m_nBrokenItem;	// �μ��� item�� ����
		ITEM_STATUS*	m_pItemStatus;
};

#endif

