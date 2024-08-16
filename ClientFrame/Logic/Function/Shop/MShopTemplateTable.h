//-----------------------------------------------------------------------------
// MShopTemplateTable.h
//-----------------------------------------------------------------------------
// ShopTemplateTable�� ShopTemplate�� array - map�� �������...
//-----------------------------------------------------------------------------

#ifndef __MSHOPTEMPLATE_H__
#define __MSHOPTEMPLATE_H__

#include "CTypeMap.h"

//-----------------------------------------------------------------------------
//		MShopTemplate
//-----------------------------------------------------------------------------
class MShopTemplate {
	public :
		MShopTemplate();
		~MShopTemplate();

		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

	public :
		//UINT				m_ID;

		BYTE				Type;				// ���� type

		// item class
		int					Class;
		
		// item type
		WORD				MinType;			
		WORD				MaxType;

		// item option
		BYTE				MinOption;
		BYTE				MaxOption;
		
};

//-----------------------------------------------------------------------------
//	MShopTemplateTable
//-----------------------------------------------------------------------------
class MShopTemplateTable : public CTypeMap<MShopTemplate> {
	public :
		MShopTemplateTable();
		~MShopTemplateTable();

	protected :

};

extern MShopTemplateTable*		g_pShopTemplateTable;

#endif

