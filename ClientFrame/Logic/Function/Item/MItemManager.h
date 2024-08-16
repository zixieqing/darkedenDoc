//----------------------------------------------------------------------
// MItemManager.h
//----------------------------------------------------------------------
// MItem�� pointer�� �����ϰ� �ٷ�� class�̴�.
// stl�� map�� �̿��Ѵ�.
// 
//		AddItem()�� �߰��ϰ�
//
//		GetItem()���� ������ ���
//
//		RemoveItem()�� �����Ѵ�.
// 
// pointer�� �����ϰ� �ֱ� ������.. new / delete �� �ܺο��� ����� �Ѵ�.
//----------------------------------------------------------------------

#ifndef	__MITEMMANAGER_H__
#define	__MITEMMANAGER_H__

#pragma warning(disable:4786)

#include "MTypeDef.h"
#include <map>
class MItem;
class MItemFinder;

//----------------------------------------------------------------------
// MItemManager
//----------------------------------------------------------------------
class MItemManager {
	public :
		typedef	std::map<TYPE_OBJECTID, MItem*>		ITEM_MAP;

	public :
		MItemManager();
		~MItemManager();

		//------------------------------------------------------
		// Release
		//------------------------------------------------------
		void			Release();

		//------------------------------------------------------
		// Add / Get / Remove
		//------------------------------------------------------
		bool			AddItem(MItem* pItem);				// Item �߰�
		MItem*			GetItem(TYPE_OBJECTID id) const;	// Item �о����
		MItem*			RemoveItem(TYPE_OBJECTID id);		// ItemManager���� Item ����

		//------------------------------------------------------
		// Iterator
		//------------------------------------------------------
		int				GetItemNum()		{ return m_mapItem.size(); }
		void			SetBegin()			{ m_iterator = m_mapItem.begin(); }
		MItem*			Get()				{ return (*m_iterator).second; }
		void			Next()				{ m_iterator++; }		
		bool			IsEnd() const		{ return m_iterator==m_mapItem.end(); }
		bool			IsNotEnd() const	{ return m_iterator!=m_mapItem.end(); }

	//protected :
		MItem*			GetItemToModify(TYPE_OBJECTID id);		
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		MItem*			GetItemToModifyAll(TYPE_OBJECTID id , MItem*& pSubInventoryItem);
	#endif
				

		//------------------------------------------------------
		// ��밡������ üũ�Ѵ�.
		//------------------------------------------------------
		void			CheckAffectStatusAll();
		virtual void	CheckAffectStatus(MItem* pItem);

		//------------------------------------------------------
		// ������ ã��
		//------------------------------------------------------
		MItem*			FindItem( MItemFinder& itemFinder ) const;
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		MItem*			FindItemAll( MItemFinder& itemFinder, MItem*& pSubInventoryItem) const;
	#endif
		
		
	protected :
		ITEM_MAP::const_iterator	m_iterator;
		ITEM_MAP					m_mapItem;
};

#endif

