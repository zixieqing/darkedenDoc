//----------------------------------------------------------------------
// MGridItemManager.h
//----------------------------------------------------------------------
// width * height ��ŭ�� grid�� ������.
//
// �� grid�� MItem*�� �̷���� �ִ�.
//
// MItem�� ũ��(GridWidth()*GridHeight)�� ����
// ������ ������ grid�� �����ϰ� �ȴ�.
//
// Item���� MItemManager�� map���� �߰��ϰ�
// grid�� ũ�⸸ŭ m_ItemGrid���� ������ grid�� ǥ�����ش�.
//----------------------------------------------------------------------
/*
 = Init(9, 5)

	   012345678
	  +---------+
	0 |         |
	1 |         |
	2 |         |
	3 |         |
	4 |         |
	  +---------+


 = AddItem( ũ�Ⱑ 2x2�ΰ�, (1,1)�� )

  	   012345678
	  +---------+
	0 |         |
	1 | AA      |
	2 | AA      |
	3 |         |
	4 |         |
	  +---------+


 = AddItem( ũ�Ⱑ 3x2�� �� ) - ������ ��ġ�� �߰�

   	   012345678
	  +---------+
	0 |   BBB   |
	1 | AABBB   |
	2 | AA      |
	3 |         |
	4 |         |
	  +---------+


 = GetItem( 2,2 ) --> A
 = GetItem( 4,1 ) --> B



*/
//----------------------------------------------------------------------

#ifndef	__MGridItemManager_H__
#define	__MGridItemManager_H__

#include "MItemManager.h"


class MGridItemManager : public MItemManager {
	public :
		MGridItemManager();
		~MGridItemManager();

		//------------------------------------------------------
		// Init / Release
		//------------------------------------------------------
		void		Init(BYTE width, BYTE height);
		void		Release();

		//------------------------------------------------------
		// get
		//------------------------------------------------------
		BYTE		GetWidth() const	{ return m_Width; }
		BYTE		GetHeight() const	{ return m_Height; }
		
		//------------------------------------------------------
		// Add / Get / Remove
		//------------------------------------------------------		
		bool			AddItem(MItem* pItem);					// ������ grid�� �߰��Ѵ�.
		bool			AddItem(MItem* pItem, BYTE x, BYTE y);	// grid(x,y)�� pItem�� �߰��Ѵ�.

		MItem*			GetItem(BYTE x, BYTE y) const;			// grid(x,y)�� item�� �о�´�.
		MItem*			GetItem(TYPE_OBJECTID id) const;
		
		MItem*			RemoveItem(BYTE x, BYTE y);				// grid(x,y)�� item�� �����Ѵ�.
		MItem*			RemoveItem(TYPE_OBJECTID id);			// id�� ���� item�� �����Ѵ�.

		bool			ReplaceItem(MItem* pItem, BYTE x, BYTE y, MItem*& pOldItem);	// (x,y)��ġ�� Item��ȯ

		//------------------------------------------------------		
		// Can Replace Item (������ Add or Replace�� check�Ѵ�.)
		//------------------------------------------------------		
		bool			CanReplaceItem(MItem* pItem, BYTE x, BYTE y, MItem*& pOldItem);

		//------------------------------------------------------		
		// Get FitPosition
		//------------------------------------------------------		
		bool			GetFitPosition(MItem* pItem, POINT& point);	// pItem�� �� �� �ִ� ������ grid��ġ�� ���Ѵ�.

		//------------------------------------------------------		
		// FindItemGridOrder
		//------------------------------------------------------		
		MItem*			FindItemGridOrder( MItemFinder& itemFinder ) const;

	protected :
		BYTE			m_Width;
		BYTE			m_Height;
		MItem***		m_ItemGrid;
};

#endif

