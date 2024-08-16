//-----------------------------------------------------------------------------
// MTradeManager.cpp
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include "MTradeManager.h"
#include "MSortedItemManager.h"
#include "MGameDef.h"
#include "DebugInfo.h"

#define SAFE_DELETE(x)		{ if(x!=NULL) delete x; x=NULL; }

#ifdef __GAME_CLIENT__
	#include "PacketDef.h"
	#include "ClientConfig.h"
	extern DWORD	g_CurrentTime;
#endif

//-----------------------------------------------------------------------------
// Item��ġ�� ����ϱ� ���� ��..
//-----------------------------------------------------------------------------
class ItemPosition {
	public :
		MItem*			pItem;
		int				gridX;
		int				gridY;

	public :
		ItemPosition(MItem* _pItem, int _gridX, int _gridY)
		{
			pItem	= _pItem;
			gridX	= _gridX;
			gridY	= _gridY;
		}
};

class ItemPositionMap : public std::map<TYPE_OBJECTID, ItemPosition*> {
	public :
		ItemPositionMap() {}
		~ItemPositionMap()
		{
			iterator iItemPosition = begin();

			while (iItemPosition!=end())
			{
				ItemPosition* pItemPosition = iItemPosition->second;

				delete pItemPosition;

				iItemPosition++;
			}
		}
};


//-----------------------------------------------------------------------------
// Global
//-----------------------------------------------------------------------------
MTradeManager*		g_pTradeManager = NULL;

//-----------------------------------------------------------------------------
//
// constructor / destructor
//
//-----------------------------------------------------------------------------
MTradeManager::MTradeManager()
{
	m_OtherID	= OBJECTID_NULL;

	m_pMyInventory = NULL;
	m_pOtherInventory = NULL;
	
	m_pMyMoney = NULL;
	m_pOtherMoney = NULL;

	m_bAcceptMyTrade = false;
	m_bAcceptOtherTrade = false;
	
	m_NextAcceptTime = 0;
}

MTradeManager::~MTradeManager()
{
	Release();
}

//-----------------------------------------------------------------------------
// Init
//-----------------------------------------------------------------------------
void				
MTradeManager::Init()
{
	Release();

	//--------------------------------------------------------------
	// Inventory �ʱ�ȭ
	//--------------------------------------------------------------
	m_pMyInventory = g_pInventory;	//new MInventory;
	m_pOtherInventory = new MInventory;
	
	//m_pMyInventory->Init(TRADE_INVENTORY_WIDTH, TRADE_INVENTORY_HEIGHT);
	m_pOtherInventory->Init(TRADE_INVENTORY_WIDTH, TRADE_INVENTORY_HEIGHT);


	//--------------------------------------------------------------
	// Money Manager
	//--------------------------------------------------------------
	m_pMyMoney = new MMoneyManager;
	m_pOtherMoney = new MMoneyManager;

	m_bAcceptMyTrade = false;
	m_bAcceptOtherTrade = false;

	m_OtherID	= OBJECTID_NULL;
}

//-----------------------------------------------------------------------------
// Release
//-----------------------------------------------------------------------------
void				
MTradeManager::Release()
{
	//if (m_pMyInventory != NULL)
	//{
	//	delete m_pMyInventory;
	//	m_pMyInventory = NULL;
	//}

	if (m_pOtherInventory != NULL)
	{
		delete m_pOtherInventory;
		m_pOtherInventory = NULL;
	}

	if (m_pMyMoney != NULL)
	{
		delete m_pMyMoney;
		m_pMyMoney = NULL;
	}

	if (m_pOtherMoney != NULL)
	{
		delete m_pOtherMoney;
		m_pOtherMoney = NULL;
	}

	m_bAcceptMyTrade = false;
	m_bAcceptOtherTrade = false;

	m_NextAcceptTime = 0;
}

//-----------------------------------------------------------------------------
// Is AcceptTime
//-----------------------------------------------------------------------------
bool				
MTradeManager::IsAcceptTime() const
{
	#ifdef __GAME_CLIENT__
		return g_CurrentTime >= m_NextAcceptTime;
	#else
		return true;
	#endif
}

//-----------------------------------------------------------------------------
// Set NextAcceptTime
//-----------------------------------------------------------------------------
void
MTradeManager::SetNextAcceptTime()
{
	#ifdef __GAME_CLIENT__
		m_NextAcceptTime = g_CurrentTime + g_pClientConfig->TRADE_ACCEPT_DELAY_TIME;
	#endif
}

//-----------------------------------------------------------------------------
// Refuse MyTrade
//-----------------------------------------------------------------------------
void				
MTradeManager::RefuseMyTrade()						
{ 
	if (m_bAcceptMyTrade)
	{
		#ifdef __GAME_CLIENT__
			SetNextAcceptTime();
		#endif

		m_bAcceptMyTrade = false; 
	}
}

//-----------------------------------------------------------------------------
// Refuse OtherTrade
//-----------------------------------------------------------------------------
void				
MTradeManager::RefuseOtherTrade()					
{ 
	if (m_bAcceptOtherTrade)
	{
		#ifdef __GAME_CLIENT__
			SetNextAcceptTime();
		#endif

		m_bAcceptOtherTrade = false; 
	}
}

//-----------------------------------------------------------------------------
// Can Trade
//-----------------------------------------------------------------------------
// ������ item�� ���� �� inventory�� ��� ���� �ִ��� üũ�Ѵ�.
//-----------------------------------------------------------------------------
bool				
MTradeManager::CanTrade() const
{
	if (m_pOtherInventory==NULL)
	{
		return false;
	}

	//-----------------------------------------------------------
	// �� �׼� üũ
	//-----------------------------------------------------------
	if (!g_pMoneyManager->CanAddMoney( m_pOtherMoney->GetMoney() ))
	{
		// �� �Ѱ踦 �Ѿ ��ȯ�� �ȵǴ� ���
		return false;
	}

	//-----------------------------------------------------------
	// ������ üũ : ���� �Ѱ踦 �Ѿ ��.
	// ��, �� inventory�� ���� ����.. gridWidth*gridHeight�� �Ѵ� ���
	//-----------------------------------------------------------
	// ���� ��ȯ�ҰŴ� ����� �Ѵ�.
	//if (g_pInventory->GetItemNum() + m_pOtherInventory->GetItemNum()
		//> g_pInventory->GetWidth()*g_pInventory->GetHeight())
	//{
	//	return false;
	//}

	//-----------------------------------------------------------
	//
	//			���� Temp Inventory�� �����.
	//
	//-----------------------------------------------------------
	

	MInventory	tempInventory;
	
	tempInventory.Init( g_pInventory->GetWidth(), g_pInventory->GetHeight() );

	//-----------------------------------------------------------
	// g_pInventory ---> tempInventory
	//-----------------------------------------------------------
	// pointer�� ��� �����صд�.
	//-----------------------------------------------------------
	bool bOK = true;		// ����� �� ���°�?

	g_pInventory->SetBegin();

	while ( g_pInventory->IsNotEnd() )
	{
		const MItem* pItem = g_pInventory->Get();

		//-----------------------------------------------------------
		// �� inventory�� ������ �߿���.. 
		// ��ȯ ���� ���� �͵鸸 temp inventory�� �߰��Ѵ�.
		//-----------------------------------------------------------
		if (!pItem->IsTrade())
		{
			//-----------------------------------------------------------
			// �̰� �ȵ� ���� ������?? - -;
			//-----------------------------------------------------------
			if (!tempInventory.AddItem( (MItem*)pItem, pItem->GetGridX(), pItem->GetGridY() ))
			{
				bOK = false;
				break;
			}
		}

		g_pInventory->Next();
	}

	//-----------------------------------------------------------
	// m_pOtherInventory�� ���� ��ġ�� ����ص־� �Ѵ�.
	//-----------------------------------------------------------	
	ItemPositionMap		mapItemPosition;	

	//-----------------------------------------------------------
	//
	// ���� inventory�� ��� item�� 
	// �� inventory(tempInventory)�� �� �� �ִ��� üũ�Ѵ�.
	//
	//-----------------------------------------------------------
	if (bOK)
	{			
		MSortedItemManager	SIM;

		//-----------------------------------------------------------
		// m_pOtherInventory�� ���� ��ġ�� ����ص־� �Ѵ�.
		// ���ÿ�.. ũ�⺰�� Sort�Ѵ�.
		//-----------------------------------------------------------
		m_pOtherInventory->SetBegin();

		while ( m_pOtherInventory->IsNotEnd() )
		{
			MItem* pItem = m_pOtherInventory->Get();

			ItemPosition* pItemPosition = new ItemPosition( (MItem*)pItem, pItem->GetGridX(), pItem->GetGridY() );
			mapItemPosition.insert( ItemPositionMap::value_type(pItem->GetID(), pItemPosition) );

			//---------------------------------------------------
			// ũ�⺰�� sort�Ѵ�.
			//---------------------------------------------------
			SIM.AddItem( pItem );

			m_pOtherInventory->Next();
		}	

		//---------------------------------------------------------------
		//
		//			SIM --> tempInventory
		//
		//---------------------------------------------------------------
		MSortedItemManager::iterator iItem = SIM.begin();

		while (iItem != SIM.end())
		{
			MItem* pItem = iItem->second;

			//-----------------------------------------------------
			// �߰��� �� �ȴٸ�.. �ڸ��� ��� ��ȯ �Ұ���
			//-----------------------------------------------------
			if (!tempInventory.AddItem( pItem ))
			{				
				bOK = false;
				
				break;
			}

			iItem ++;
		}

		SIM.Clear();
	}

	//-----------------------------------------------------------
	//
	//		tempInventory�� ����� �Ѵ�.
	//
	//-----------------------------------------------------------
	tempInventory.SetBegin();

	while ( tempInventory.IsNotEnd() )
	{
		const MItem* pItem = tempInventory.Get();

		tempInventory.Next();

		//-----------------------------------------------------------
		// �̰� �ȵ� ���� ������?? - -;
		//-----------------------------------------------------------
		if (!tempInventory.RemoveItem( pItem->GetGridX(), pItem->GetGridY() ))
		{			
			// �ȵǹ� �����̴�.

			// �̰Ŵ� �׳� pointer�� �����Ѱű� ������
			// delete�ϸ� �ȵȴ�.
		}
	}

	//-----------------------------------------------------------
	// ���� inventory�� �����۵��� 
	// ���� ��ġ�� �ǵ�����.
	//-----------------------------------------------------------
	m_pOtherInventory->SetBegin();

	while ( m_pOtherInventory->IsNotEnd() )
	{
		const MItem* pItem = m_pOtherInventory->Get();

		//-----------------------------------------------------------
		// m_pOtherInventory�� ���� ��ġ�� ����ص־� �Ѵ�.
		//-----------------------------------------------------------
		ItemPositionMap::iterator iItemPosition = mapItemPosition.find( pItem->GetID() );

		if (iItemPosition == mapItemPosition.end())
		{
			// �������� �� �ٲ�Ŷ�� ���� �ȴ�..
			break;
		}

		ItemPosition* pItemPosition = iItemPosition->second;

		MItem* pOriginalItem = pItemPosition->pItem;
		pOriginalItem->SetGridXY( pItemPosition->gridX, pItemPosition->gridY );

		m_pOtherInventory->Next();
	}

	// tempInventory���� �ƹ��͵� ����� �Ѵ�.

	return bOK;
}

//-----------------------------------------------------------------------------
// Trade
//-----------------------------------------------------------------------------
// ������ item�� �� inventory�� �ִ´�.
//-----------------------------------------------------------------------------
bool				
MTradeManager::Trade()
{
	if (// ��ȯȮ����... �Ѹ��̶� �� �����ų�
		!m_bAcceptMyTrade || !m_bAcceptOtherTrade
		// init�ȵ� ���
		|| m_pMyInventory==NULL
		|| m_pOtherInventory==NULL
		|| m_pMyMoney==NULL
		|| m_pOtherMoney==NULL)
	{
		#ifdef OUTPUT_DEBUG
			DEBUG_ADD_FORMAT("[Error] Trade Failed! %d %d %d %d %d %d"
								,!m_bAcceptMyTrade
								,!m_bAcceptOtherTrade
								,m_pMyInventory==NULL
								,m_pOtherInventory==NULL
								,m_pMyMoney==NULL
								,m_pOtherMoney==NULL);			
		#endif

		// trade�ɸ��� ����.
		return false;
	}

	//---------------------------------------------------------------
	//
	//				��ȯ�� �ȵǴ� ���
	//
	//---------------------------------------------------------------
	if (!CanTrade())
	{
		DEBUG_ADD("[Error] Can't Trade");			
		
		return false;
	}

	MSortedItemManager	SIM;

	//---------------------------------------------------------------
	//
	//	�� inventory���� ��ȯ�ҷ��� �������� ��� �����Ѵ�.
	//
	//---------------------------------------------------------------
	DEBUG_ADD("[Trade] Remove Trading Items");
	
	m_pMyInventory->SetBegin();

	while ( m_pMyInventory->IsNotEnd() )
	{
		const MItem* pItem = m_pMyInventory->Get();

		m_pMyInventory->Next();

		//-----------------------------------------------------------
		// ������ �����Ѵ�.
		//-----------------------------------------------------------
		if (pItem->IsTrade())
		{
			DEBUG_ADD_FORMAT("[Trade] Remove: id=%d. xy=(%d, %d)", pItem->GetID(), pItem->GetX(), pItem->GetY() );
			
			MItem* pRemovedItem = m_pMyInventory->RemoveItem( pItem->GetGridX(), pItem->GetGridY() );

			if (pRemovedItem!=NULL)
			{
				delete pRemovedItem;
			}
			else
			{
				// �ᰡ��~~
				DEBUG_ADD("[Error] Remove Error");				
			}

		}				
	}

	//---------------------------------------------------------------
	//
	//		m_pOtherInventory --> SortedItemManager
	//
	//---------------------------------------------------------------
	DEBUG_ADD("[Trade] Move OtherInventory --> SortedItemManager");
	
	m_pOtherInventory->SetBegin();

	while ( m_pOtherInventory->IsNotEnd() )
	{
		const MItem* pItem = m_pOtherInventory->Get();
		
		m_pOtherInventory->Next();

		//-----------------------------------------------------------
		// OtherInventory���� ������ �����Ѵ�.
		//-----------------------------------------------------------
		MItem* pRemovedItem = m_pOtherInventory->RemoveItem( pItem->GetGridX(), pItem->GetGridY() );

		if (pRemovedItem!=NULL)
		{
			//-----------------------------------------------------------
			// player�� inventory�� �߰��Ѵ�.
			//-----------------------------------------------------------
			if (SIM.AddItem( pRemovedItem ))
			{
				//-------------------------------------------------------
				// ����� �߰��� ���
				//-------------------------------------------------------				
			}
			else
			{
				// -_-;; ��å���� ���
				delete pRemovedItem;	// memory leak�̳� ���� - -;;
			}
		}
		else	
		{
			// �ᰡ�� - -;;
			// ��å����.. ���ȴ�.. - -;;
		}

	}

	//---------------------------------------------------------------
	//
	//			SIM --> g_pInventory
	//
	//---------------------------------------------------------------
	DEBUG_ADD("[Trade] SIM --> Inventory");
		
	MSortedItemManager::iterator iItem = SIM.begin();

	while (iItem != SIM.end())
	{
		MItem* pItem = iItem->second;

		if (g_pInventory->AddItem( pItem ))
		{
			pItem->UnSetTrade();	// -_-;

			// Event GiftBox �������� ���� ��� --> ����������
			if (pItem->GetItemClass()==ITEM_CLASS_EVENT_GIFT_BOX)
			{
				if(pItem->GetItemType()==0)
				{
					pItem->SetItemType( 1 );
				}
				else if(pItem->GetItemType() >= 2 && pItem->GetItemType() <= 5)
				{
					pItem->SetItemType(6);
				}
				// 2004, 4, 28 sobeit add ���� �̺�Ʈ �ڽ� start
				else if(pItem->GetItemType() >= 16 && pItem->GetItemType() <= 18)
				{  
					int TempItemType = pItem->GetItemType() + 3; // ������ �ڽ��� �ٲٱ� ���� 
					pItem->SetItemType(TempItemType);
				}
				// 2004, 4, 28 sobeit add ���� �̺�Ʈ �ڽ� end
			}
		}
		else
		{
			// - -;
//			delete pItem;
			SAFE_DELETE( pItem );
		}

		iItem ++;
	}

	SIM.Clear();


	//-----------------------------------------------------------
	//
	//				�� ��ȯ
	//
	//-----------------------------------------------------------
	DEBUG_ADD("[Trade] Money");
		

	if (g_pMoneyManager->AddMoney( m_pOtherMoney->GetMoney() ))
	{
		m_pOtherMoney->SetMoney( 0 );
		m_pMyMoney->SetMoney( 0 );
	}
	else
	{
		// �� �Ѱ� �Ѵ� ���.. - -;
	}

	m_bAcceptMyTrade = false;
	m_bAcceptOtherTrade = false;
	
	return true;
}

//-----------------------------------------------------------------------------
// Cancel Trade 
//-----------------------------------------------------------------------------
// ��ȯ�� ��ҵǴ� ���
//
// 
//-----------------------------------------------------------------------------
bool
MTradeManager::CancelTrade()
{
	//---------------------------------------------------------
	// ���� �� ���� �ٽ� �����´�.
	//---------------------------------------------------------
	if (g_pMoneyManager->AddMoney( m_pMyMoney->GetMoney() ))
	{
		m_pOtherMoney->SetMoney( 0 );
		m_pMyMoney->SetMoney( 0 );
	}
	/*
	int x, y;

	MSortedItemManager	SIM;
	
	MInventory*			pInventory;
	
	//--------------------------------------------------
	// 2 x 2 �������� ������ �˾Ƴ���. �κ��丮
	//--------------------------------------------------
	int numTwoByTwo = 0;
	
	for (int i=0; i<2; i++)
	{
		if (i==0)
		{
			pInventory = g_pInventory;
		}
		else
		{
			pInventory = g_pTradeManager->GetMyInventory();
		}
		
		pInventory->SetBegin();

		while (pInventory->IsNotEnd())
		{
			const MItem* pItem = pInventory->Get();

			if (pItem!=NULL)
			{
				if (pItem->GetGridWidth()==2 
					&& pItem->GetGridHeight()==2)
				{
					numTwoByTwo++;
				}
			}	
			
			pInventory->Next();
		}
	}

	SIM.SetTwoByTwoNumber( numTwoByTwo );	// 2 x 2�� ������ ���� ����
	
	//--------------------------------------------------
	// ���� Inventory���� Item�����ؼ� SIM�� �߰��Ѵ�.
	//--------------------------------------------------
	pInventory	= g_pInventory;
	
	for (x=0; x<10; x++)
	{
		for (y=0; y<6; y++)
		{
			const MItem* pItem = pInventory->GetItem( x, y );

			if (pItem != NULL)
			{
				MItem* pRemovedItem = pInventory->RemoveItem( pItem->GetID() );
			
				if (pRemovedItem!=NULL)
				{
					SIM.AddItem( pRemovedItem );
				}							
			}
		}
	}

	//--------------------------------------------------
	// ���� ��Trade���� Item�����ؼ� SIM�� �߰��Ѵ�.
	//--------------------------------------------------
	pInventory	= g_pTradeManager->GetMyInventory();
	
	for (x=0; x<10; x++)
	{
		for (y=0; y<6; y++)
		{
			const MItem* pItem = pInventory->GetItem( x, y );

			if (pItem != NULL)
			{
				MItem* pRemovedItem = pInventory->RemoveItem( pItem->GetID() );
			
				if (pRemovedItem!=NULL)
				{
					SIM.AddItem( pRemovedItem );
				}							
			}
		}
	}

	//--------------------------------------------------
	// Inventory�� �ٽ� �ʱ�ȭ�Ѵ�.
	//--------------------------------------------------
	g_pTradeManager->GetMyInventory()->Init( 10, 6 );
	g_pInventory->Init( 10, 6 );

	MSortedItemManager::iterator iItem = SIM.begin();

	while (iItem != SIM.end())
	{
		MItem* pItem = iItem->second;

		g_pInventory->AddItem( pItem );

		iItem ++;
	}

	//--------------------------------------------------
	// InventorySIM�� ���� Clear������� �Ѵ�.
	//--------------------------------------------------
	SIM.Clear();
	*/
	return true;
}