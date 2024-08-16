//----------------------------------------------------------------------
// MShopShelf.h
//----------------------------------------------------------------------
// ������ ���� �ϳ�.. - -;
//
// ���� �ϳ����� run-time version�� �ִ�.
//----------------------------------------------------------------------

#ifndef __MSHOPSHELF_H__
#define	__MSHOPSHELF_H__

#include "MGameDef.h"
#include "MItem.h"

class MShopShelf {
	public :
		enum SHELF_TYPE
		{			
			SHELF_FIXED,			// ������ item list�� ���� shelf
			SHELF_SPECIAL,			// special item
			SHELF_UNKNOWN,			// unknown item
			MAX_SHELF,				// max��
			SHELF_BASE				// ��� �� ��
			
		};

	public :
		MShopShelf();
		virtual ~MShopShelf();

		//----------------------------------------------------------
		// class
		//----------------------------------------------------------
		virtual SHELF_TYPE	GetShelfType() const	{ return SHELF_BASE; }

		//----------------------------------------------------------
		// Release
		//----------------------------------------------------------
		void		Release();

		//----------------------------------------------------------
		// Name
		//----------------------------------------------------------
		void		SetName(const char*name)		{ m_Name = name; }
		const char*	GetName() const					{ return m_Name.GetString(); }

		//----------------------------------------------------------
		// Is...
		//----------------------------------------------------------
		bool		IsEnable() const		{ return m_bShelfEnable; }
		bool		IsEmptySlot(unsigned int  slot);

		void		SetEnable()				{ m_bShelfEnable = true; }
		void		SetDisable()			{ m_bShelfEnable = false; }
		
		//----------------------------------------------------------
		// Get 
		//----------------------------------------------------------
		int			GetVersion() const			{ return m_Version; }
		MItem*		GetItem(unsigned int  slot) const;

		
		//----------------------------------------------------------
		// Set
		//----------------------------------------------------------
		void		SetVersion(int version)		{ m_Version = version; }
		bool		AddItem(MItem* pItem);		// �� ���� �߰��Ѵ�.
		bool		SetItem(unsigned int  slot, MItem* pItem);	// ������ �ִ��� �����ش�.

	
		//----------------------------------------------------------
		// Remove - Shelf���� �����ؼ� return���ش�.(�ܺο��� delete�ؾ��Ѵ�.)
		//----------------------------------------------------------
		MItem*		RemoveItem(unsigned int slot);

		//----------------------------------------------------------
		// Delete - Shelf ���ο� �ִ°� �����ش�.
		//----------------------------------------------------------
		void		DeleteItem(unsigned int slot);

	protected :
		bool		m_bShelfEnable;				// ���� ��밡���� Shelf�ΰ�?

		MString		m_Name;						// Shelf Name

		int			m_Version;					// run-time version
	
		MItem*		m_pItems[SHOP_SHELF_SLOT];


	public :
		// NewItem()�� ���� functions pointer
		typedef MShopShelf* (*FUNCTION_NEWSHELFCLASS)();

		//-------------------------------------------------------
		// ���ϴ� class�� Item�� ��ü�� �����Ѵ�.
		//-------------------------------------------------------
		static MShopShelf*		NewShelf(MShopShelf::SHELF_TYPE shelfType);

		// �� class���� NewItem()�� ���� function pointer
		static FUNCTION_NEWSHELFCLASS		s_NewShelfClassTable[MAX_SHELF];
};


//----------------------------------------------------------------------
// MShopFixedShelf.h
//----------------------------------------------------------------------
// ������ Item List�� ���� ���� ����
//----------------------------------------------------------------------
class MShopFixedShelf : public MShopShelf {
	public :
		MShopFixedShelf();
		~MShopFixedShelf();

		//----------------------------------------------------------
		// class
		//----------------------------------------------------------
		virtual SHELF_TYPE	GetShelfType() const	{ return SHELF_FIXED; }

		//------------------------------------------------------------
		// Init
		//------------------------------------------------------------
		//bool		InitFromFixedItemTable(unsigned int tableID);

		//------------------------------------------------------------
		// new Shelf
		//------------------------------------------------------------
		static MShopShelf*	NewShelf()				{ return new MShopFixedShelf; }

	protected :

};

//----------------------------------------------------------------------
// MShopSpecialShelf.h
//----------------------------------------------------------------------
// ������ Item List�� ���� ���� ����
//----------------------------------------------------------------------
class MShopSpecialShelf : public MShopShelf {
	public :
		MShopSpecialShelf();
		~MShopSpecialShelf();

		//----------------------------------------------------------
		// class
		//----------------------------------------------------------
		virtual SHELF_TYPE	GetShelfType() const	{ return SHELF_SPECIAL; }

		//------------------------------------------------------------
		// new Shelf
		//------------------------------------------------------------
		static MShopShelf*	NewShelf()				{ return new MShopSpecialShelf; }

	protected :

};


//----------------------------------------------------------------------
// MShopUnknownShelf.h
//----------------------------------------------------------------------
// ������ Item List�� ���� ���� ����
//----------------------------------------------------------------------
class MShopUnknownShelf : public MShopShelf {
	public :
		MShopUnknownShelf();
		~MShopUnknownShelf();

		//----------------------------------------------------------
		// class
		//----------------------------------------------------------
		virtual SHELF_TYPE	GetShelfType() const	{ return SHELF_UNKNOWN; }

		//------------------------------------------------------------
		// new Shelf
		//------------------------------------------------------------
		static MShopShelf*	NewShelf()				{ return new MShopUnknownShelf; }

	protected :

};

#endif
