//-----------------------------------------------------------------------------
// MPriceManager.h
//-----------------------------------------------------------------------------

#ifndef __MPRICEMANAGER_H__
#define __MPRICEMANAGER_H__

class MItem;

// ������ type�� ���� number��.
struct STAR_ITEM_PRICE {
	int type;
	int number;
};

class MPriceManager {
	public :
		enum TRADE_TYPE
		{
			NPC_TO_PC,		// player�� ���� �춧, m_MarketCondSell
			PC_TO_NPC,		// player�� ���� �ȶ�, m_MarketCondBuy
			REPAIR,			// player�� ���� repair�� ��,
			SILVERING,		// player�� ���ǿ� �ǹ������� ��,
		};

	public :
		MPriceManager(); 	
		~MPriceManager();

		//-------------------------------------------------------		
		// Get Item Price
		//-------------------------------------------------------		
		int			GetItemPrice(MItem* pItem, TRADE_TYPE type, bool bMysterious=false);
		void		GetItemPrice(MItem* pItem, STAR_ITEM_PRICE& price);
		int			GetMysteriousPrice(MItem* pItem) const;

		//-------------------------------------------------------		
		// �ü�
		//-------------------------------------------------------		
		// NPC �������� buy, sell
		void		SetMarketCondBuy(int buy)			{ m_MarketCondBuy = buy; }
		void		SetMarketCondSell(int sell)			{ m_MarketCondSell = sell; }

		int			GetMarketCondBuy() const			{ return m_MarketCondBuy; }
		int			GetMarketCondSell() const			{ return m_MarketCondSell; }

		void		SetEventItemPrice(int Price)		{ m_EventFixPrice = Price; }

	protected :
		
		// �ü�
		int					m_MarketCondBuy;		// NPC�� �춧(25)
		int					m_MarketCondSell;		// NPC�� �ȶ�(100)
		int					m_EventFixPrice;		// �������� �����ִ� �̺�Ʈ ������ ����
};

extern MPriceManager*		g_pPriceManager;

#endif

