//----------------------------------------------------------------------
// MPlayerGear.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MPlayerGear.h"
#include "MItem.h"
#include "MHelpManager.h"
#include "debuginfo.h"

#ifdef __GAME_CLIENT__
	#include "ClientConfig.h"
#endif

//----------------------------------------------------------------------
// 
// constructor / destructor
//
//----------------------------------------------------------------------
MPlayerGear::MPlayerGear()
{
	m_nBrokenItem = 0;
	m_pItemStatus = NULL;
}

MPlayerGear::~MPlayerGear()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Init ItemStatus ( n�� )
//----------------------------------------------------------------------
void			
MPlayerGear::Init(BYTE size)
{
	MSlotItemManager::Init( size );

	//--------------------------------------------------------
	// Item ���¸� ��� OK�� �����Ѵ�.
	//--------------------------------------------------------
	if (m_pItemStatus!=NULL)
	{
		delete [] m_pItemStatus;
	}

	m_pItemStatus = new ITEM_STATUS [size];

	for (int i=0; i<size; i++)
	{
		m_pItemStatus[i] = ITEM_STATUS_OK;
	}

	m_nBrokenItem = 0;
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void			
MPlayerGear::Release()
{
	MSlotItemManager::Release();

	if (m_pItemStatus!=NULL)
	{
		delete [] m_pItemStatus;
		m_pItemStatus = NULL;
	}
}

//----------------------------------------------------------------------
// Add Item
//----------------------------------------------------------------------
bool			
MPlayerGear::AddItem(MItem* pItem, BYTE n)
{
	bool bOK = MSlotItemManager::AddItem(pItem, n);

	if (bOK)
	{
		CheckItemStatus( pItem, n );
	}

	return bOK;
}


//----------------------------------------------------------------------
// Get Item
//----------------------------------------------------------------------
// get get get~
//----------------------------------------------------------------------
MItem*
MPlayerGear::GetItem(BYTE n) const
{
	return MSlotItemManager::GetItem( n );	// ���� ����..
}

//----------------------------------------------------------------------
// Remove Item ( slot )
//----------------------------------------------------------------------
MItem*			
MPlayerGear::RemoveItem(BYTE n)
{
	MItem* pItem = MSlotItemManager::RemoveItem( n );

	if (pItem!=NULL)
	{
		// �����Ѵٴ� �ǹ��̴�.
		SetItemStatusOK( n );
	}

	return pItem;
}

//----------------------------------------------------------------------
// Remove Item ( id )
//----------------------------------------------------------------------
MItem*			
MPlayerGear::RemoveItem(TYPE_OBJECTID id)
{
	MItem* pItem = MSlotItemManager::RemoveItem( id );

	if (pItem!=NULL)
	{
		// �����Ѵٴ� �ǹ��̴�.
		SetItemStatusOK( pItem->GetItemSlot() );
	}

	return pItem;
}

//----------------------------------------------------------------------
// Replace Item
//----------------------------------------------------------------------
bool			
MPlayerGear::ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	bool bAdded = MSlotItemManager::ReplaceItem( pItem, n, pOldItem );

	if (bAdded)
	{
		if (pOldItem!=NULL)
		{
			SetItemStatusOK( pOldItem->GetItemSlot() );		// �ϴ� OK���·�..
		}
		
		// Replace�� ������ �� ���Ƽ� ��ӹ������� ó���ؾ� �Ѵ�.
		//CheckItemStatus( pItem, n );	// ���ο� item�� ���� üũ				
	}

	return bAdded;
}

//----------------------------------------------------------------------
// Set ItemStatus OK ( slot )
//----------------------------------------------------------------------
// slot��°�� ���� ������ �������̴�..��� �Ѵ�. - -;
// Remove�� ���... �׳� OK��� �ϱ� ���ؼ���.
//----------------------------------------------------------------------
void			
MPlayerGear::SetItemStatusOK(int slot)
{
	//----------------------------------------------------------
	// �μ����� item�� ���...
	//----------------------------------------------------------
	if (m_pItemStatus[slot]!=ITEM_STATUS_OK)
	{
		m_pItemStatus[slot] = ITEM_STATUS_OK;

		if (--m_nBrokenItem < 0)
		{
			m_nBrokenItem = 0;
		}
	}
}

//----------------------------------------------------------------------
// Check ItemStatus
//----------------------------------------------------------------------
// pItem�� ���¸� slot�� �����Ѵ�.
//----------------------------------------------------------------------
void			
MPlayerGear::CheckItemStatus(const MItem* pItem, int slot)
{
	ITEM_STATUS oldStatus = m_pItemStatus[slot];

	TYPE_ITEM_DURATION	maxDur = pItem->GetMaxDurability();
	TYPE_ITEM_DURATION	curDur = pItem->GetCurrentDurability();

	// ������ ����.. % 
	TYPE_ITEM_DURATION	itemStatusPer = 0;

	if(maxDur <= 0 ||pItem->IsSpecialColorItem() || pItem->IsDurationAlwaysOkay())
		itemStatusPer = 100; 
	else
		itemStatusPer = curDur*100 / maxDur;


	//----------------------------------------------------------
	// �������� ����		
	//----------------------------------------------------------
	if (itemStatusPer > 
#ifdef __GAME_CLIENT__
		g_pClientConfig->PERCENTAGE_ITEM_SOMEWHAT_BROKEN
#else
		25
#endif
		)
	{
		m_pItemStatus[slot] = ITEM_STATUS_OK;

		//----------------------------------------------------------
		// �μ����ٰ� ������ �����̴�.
		//----------------------------------------------------------
		if (oldStatus!=ITEM_STATUS_OK)
		{
			if (--m_nBrokenItem < 0)
			{
				m_nBrokenItem = 0;
			}
		}
	}
	//----------------------------------------------------------
	// �μ��� ���..
	//----------------------------------------------------------
	else
	{
		//----------------------------------------------------------
		// ���� �μ������� ���� --> ������
		//----------------------------------------------------------
		if (itemStatusPer <= 
#ifdef __GAME_CLIENT__
			g_pClientConfig->PERCENTAGE_ITEM_ALMOST_BROKEN
#else
			10
#endif
			)
		{
			m_pItemStatus[slot] = ITEM_STATUS_ALMOST_BROKEN;
		}
		//----------------------------------------------------------
		// �ణ? �μ��� ����			
		//----------------------------------------------------------
		else
		{
			m_pItemStatus[slot] = ITEM_STATUS_SOMEWHAT_BROKEN;
		}

		//----------------------------------------------------------
		// �������ٰ� �μ�������..
		//----------------------------------------------------------
		if (oldStatus==ITEM_STATUS_OK)
		{
			m_nBrokenItem++;	// �Ѱ踦 ���� �� ������? - -;			
		}
	}		
}


//----------------------------------------------------------------------
// Modify Durability ( slot, ���簪 )
//----------------------------------------------------------------------
// ������ '��ȭ��'�̾��µ�.. '���簪'���� �����Ѵ�.
//----------------------------------------------------------------------
bool			
MPlayerGear::ModifyDurability(BYTE n, int changeValue)
{
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size)
	{
		return false;
	}

	MItem* pItem = m_ItemSlot[n];

	if (pItem==NULL)
	{
		return false;
	}

	//int currentDurability	= pItem->GetCurrentDurability();
	int maxDurability		= pItem->GetMaxDurability();

	int modifyDurability = changeValue;//currentDurability + changeValue;

	//---------------------------------------------------------	
	// max�� �Ѿ�� ���
	//---------------------------------------------------------	
	if ( modifyDurability > maxDurability)
	{
		pItem->SetCurrentDurability( maxDurability );
	}
	//---------------------------------------------------------	
	// 0���� ���� ���
	//---------------------------------------------------------	
	else if (modifyDurability < 0)
	{
		pItem->SetCurrentDurability( 0 );
	}
	//---------------------------------------------------------	
	// ���������� �ٲ�� ���
	//---------------------------------------------------------	
	else
	{
		pItem->SetCurrentDurability( modifyDurability );
	}

	//---------------------------------------------------------	
	// Item���� üũ
	//---------------------------------------------------------	
	ITEM_STATUS oldStatus = m_pItemStatus[n];
	
	CheckItemStatus( pItem, n );
#ifdef __GAME_CLIENT__
//#ifdef __USE_HELP_EVENT
//	__BEGIN_HELP_EVENT	
//		// OK���µ�.. OK�� �ƴϰ� �Ǵ� ���
		if (oldStatus==ITEM_STATUS_OK && m_pItemStatus[n]!=ITEM_STATUS_OK)
		{
			// [����] �������� �μ������� ���
			ExecuteHelpEvent( HELP_EVENT_ITEM_REPAIR );
		}
//	__END_HELP_EVENT
//#endif
#endif	
	return true;
}

//----------------------------------------------------------------------
// Check ItemStatus All
//----------------------------------------------------------------------
// ��� item�� item���¸� üũ�Ѵ�.
//----------------------------------------------------------------------
void			
MPlayerGear::CheckItemStatusAll()
{
	for (BYTE i=0; i<m_Size; i++)
	{
		m_pItemStatus[i] = ITEM_STATUS_OK;
	}

	m_nBrokenItem = 0;

	//---------------------------------------------------
	// ��� üũ
	//---------------------------------------------------
	for (i=0; i<m_Size; i++)
	{
		if (m_ItemSlot[i]!=NULL)
		{
			CheckItemStatus( m_ItemSlot[i], i );
		}
	}
}
