//----------------------------------------------------------------------
// MShop.h
//----------------------------------------------------------------------
// Shop�� Shelf�� �𿩼� �̷������.
//
// --> Shelf�� array
//
// SetShelf�� �ܺο��� new�� shelf�� �߰��ϸ� �ǰ�..
// delete�� MShop ���ο��� �ϰ� �ȴ�.
//
// current�� �����ؼ� ���翡 ������� shelf�� ������ �� �ִ�.
//----------------------------------------------------------------------
/*

	MShop*		pShop;
	MShopShelf*	pShelf;

	//----------------------------------------------------
	// 3���� shelf�� ���� ����
	//----------------------------------------------------
	pShop = new MShop;
	pShop->Init( 3 );		

	//----------------------------------------------------
	// [0] Fixed Shelf
	//----------------------------------------------------
	pShelf = new MShopFixedShelf;
	.....	// pShelf�� ���� �ʱ�ȭ..
	if (!pShop->SetShelf(0, pShelf))
	{
		// �߰��� �� �� ���� �ܺο��� delete����� �Ѵ�.
		// shelf ��ȣ�� ���� ��ü �������� ū ��쿡 �߰� ���д�..
		delete pShelf;
	}
  
	//----------------------------------------------------
	// [1] Special Shelf
	//----------------------------------------------------
	pShelf = new MShopSpecialShelf;
	.....
	pShop->SetShelf(0, pShelf);

	//----------------------------------------------------
	// [2] Unknown Shelf
	//----------------------------------------------------
	pShelf = new MShopUnknownShelf;
	.....
	pShop->SetShelf(0, pShelf);

	
	//----------------------------------------------------
	// ����
	//----------------------------------------------------
	for (int i=0; i<pShop->GetSize(); i++)
	{
		// [i]��° shelf�� �о�´�.
		MShopShelf* pShelf = pShop->GetShelf(i);		

		pShelf->GetName(); // �� shelf�� �̸�
	}
	
	//----------------------------------------------------
	// ���� shelf �����ϱ�
	//----------------------------------------------------
	pShop->SetCurrent( 1 );		// special shelf�� �����Ѵ�.
	MShopShelf* pShelf = pShop->GetCurrentShelf();		// ���� ������� shelf�о����

	....
*/
//----------------------------------------------------------------------

#ifndef __MSHOP_H__
#define	__MSHOP_H__

class MShopShelf;

class MShop {
	public :
		enum SHOP_TYPE
		{
			SHOP_NORMAL,
			SHOP_EVENT_STAR
		};

	public :
		MShop();
		~MShop();

		//-------------------------------------------------------
		// Init / Release
		//-------------------------------------------------------
		void				Init(unsigned int shopType);
		void				Release();
	
		//-------------------------------------------------------		
		// Shop Type
		//-------------------------------------------------------		
		SHOP_TYPE			GetShopType() const				{ return m_ShopType; }
		void				SetShopType(SHOP_TYPE type)		{ m_ShopType = type; }

		//-------------------------------------------------------		
		// Size
		//-------------------------------------------------------		
		unsigned int		GetSize() const		{ return m_Size; }

		//-------------------------------------------------------
		// Shelf
		//-------------------------------------------------------		
		bool				SetShelf(unsigned int shopType, MShopShelf* pShelf);
		MShopShelf*			GetShelf(unsigned int shopType) const;

		//-------------------------------------------------------		
		// ���� ���� ���� shelf
		//-------------------------------------------------------		
		void				SetCurrent(unsigned int shopType);
		unsigned int		GetCurrent() const			{ return m_CurrentShelf; }
		MShopShelf*			GetCurrentShelf() const		{ return m_pShelf[m_CurrentShelf]; }


	protected :
		unsigned int		m_Size;			// ��ü shelf ����
		MShopShelf**		m_pShelf;

		// ���� ������� shelf
		unsigned int		m_CurrentShelf;

		// ������ ����
		SHOP_TYPE			m_ShopType;
};

#endif


