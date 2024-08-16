//----------------------------------------------------------------------
// MNPC.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MNPC.h"
#include "MNPCTable.h"
#include "MShopTemplateTable.h"
#include "MShopShelf.h"
#include "MPlayer.h"

//----------------------------------------------------------------------
// 
// constructor / destructor
//
//----------------------------------------------------------------------
MNPC::MNPC()
{
	m_NPCID = 0;

	m_pShop = NULL;
}

MNPC::~MNPC()
{
	if (m_pShop!=NULL)
	{
		delete m_pShop;
	}
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Get NPC Info
//----------------------------------------------------------------------
NPC_INFO*			
MNPC::GetNPCInfo(TYPE_OBJECTID id) const
{
	return (*g_pNPCTable).GetData( id ); 
}

//----------------------------------------------------------------------
// Set Shop
//----------------------------------------------------------------------
void				
MNPC::SetShop(MShop* pShop)
{
	// ������ �ִ��� �����.
	if (m_pShop!=NULL)
	{
		delete m_pShop;
	}

	m_pShop = pShop;
}

//-----------------------------------------------------------------------------
// CreateItemFromShopTemplate
//-----------------------------------------------------------------------------
BOOL
MNPC::CreateFixedShelf(bool bMysterious)
{
	NPC_INFO* pInfo = (*g_pNPCTable).GetData( m_NPCID );

	//-----------------------------------------------------------
	// NPC�� ������ ��´�.
	//-----------------------------------------------------------
	MShop* pShop = m_pShop;

	if (pShop==NULL)
	{
		// ������ ������ ������ �����.
		pShop = new MShop;
		pShop->Init( MShopShelf::MAX_SHELF );

		// NPC�� ���� ����..
		m_pShop = pShop;
	}

	MShopShelf::SHELF_TYPE shelfType;

	if (bMysterious)
	{
		shelfType = MShopShelf::SHELF_UNKNOWN;
	}
	else
	{
		shelfType = MShopShelf::SHELF_FIXED;
	}

	//-----------------------------------------------------------
	// NPC������ �ִ°�?
	//-----------------------------------------------------------
	if (pInfo==NULL)
	{
		// ������... �׳� �� ���� ����
		MShopShelf* pShopShelf = MShopShelf::NewShelf( shelfType );

		pShop->SetShelf( shelfType, pShopShelf );	

		return false;
	}

	//-----------------------------------------------------------
	// Normal Item ������ ��´�.
	//-----------------------------------------------------------
	MShopShelf* pShopShelf = pShop->GetShelf( shelfType );

	//-----------------------------------------------------------
	// ������ �����Ѵ�.
	//-----------------------------------------------------------
	if (pShopShelf==NULL)
	{
		// normal shelf�� �����Ѵ�.
		pShopShelf = MShopShelf::NewShelf( shelfType );

		pShop->SetShelf( shelfType, pShopShelf );	
	}
	else
	{
		pShopShelf->Release();
	}

	bool bEnable = false;

	//-----------------------------------------------------------
	// NPC�� ���� ShopTemplate ID���� �� ó���Ѵ�.
	//-----------------------------------------------------------
	//
	// Item�������� �̿��ؼ� pShopShelf�� Item�� �߰��ϸ� �ȴ�.
	//
	//-----------------------------------------------------------
	NPC_INFO::SHOPTEMPLATEID_LIST::iterator iID = pInfo->ListShopTemplateID.begin();

	while (iID != pInfo->ListShopTemplateID.end())
	{
		unsigned int id = *iID;

		//-----------------------------------------------------------
		// id�� ShopTemplate�� ã�´�.
		//-----------------------------------------------------------
		MShopTemplate* pShopTemplate = (*g_pShopTemplateTable).GetData( id );

		if (pShopTemplate!=NULL)
		{
			//-----------------------------------------------------------
			// Normal Item�� ��츸 ó���Ѵ�.
			//-----------------------------------------------------------
			if ((MShopShelf::SHELF_TYPE)pShopTemplate->Type == shelfType)
			{	
				int minType	= pShopTemplate->MinType;	
				int	maxType	= pShopTemplate->MaxType;

				//-----------------------------------------------------------
				// min~max Type�� item���� �����Ѵ�. (min, max����)
				//-----------------------------------------------------------
				for (int type=minType; type<=maxType; type++)
				{
					// item ����
					ITEM_CLASS itemClass = (ITEM_CLASS)pShopTemplate->Class;
					MItem* pItem = MItem::NewItem( itemClass );
					bEnable = true;

					if(bMysterious && g_pPlayer->IsFemale() && 
						(
							itemClass == ITEM_CLASS_COAT ||
							itemClass == ITEM_CLASS_TROUSER ||
							itemClass == ITEM_CLASS_VAMPIRE_COAT
						)
					)
						type++;

					pItem->SetItemType( type );
					pItem->SetGrade( 4 );
					if(bMysterious)
						pItem->UnSetIdentified();

					// durability max
					pItem->SetCurrentDurability( pItem->GetMaxDurability() );

					//-----------------------------------------------------------
					// Charge�� item�� ��� --> �� ä���.
					//-----------------------------------------------------------
					if (pItem->IsChargeItem())
					{
						pItem->SetNumber( pItem->GetMaxNumber() );
					}

					//-----------------------------------------------------------
					// vampire portal�� ��� default�� ����
					//-----------------------------------------------------------
					if (pItem->GetItemClass()==ITEM_CLASS_VAMPIRE_PORTAL_ITEM)
					{
						switch(type)
						{
						case 3:
						case 4:
						case 5:
							{
								MVampirePortalItem* pPortalItem = (MVampirePortalItem*)pItem;
								
								// ���丮 ����
								pPortalItem->SetZone( 1003, 50, 70 );
								
							}
							break;

						case 6:
						case 7:
						case 8:
							{
								MVampirePortalItem* pPortalItem = (MVampirePortalItem*)pItem;
								
								// ������ ����
								pPortalItem->SetZone( 1007, 62, 65 );
								
							}
							break;
							
						case 9:
						case 10:
						case 11:
							{
								MVampirePortalItem* pPortalItem = (MVampirePortalItem*)pItem;
								
								// ��γ� ����
								pPortalItem->SetZone( 61, 102, 220 );
								
							}
							break;
						}
					}


					// pItem->SetItemOption( 0 ); // default�� 0�̹Ƿ� �� �ʿ� ����.
	
					// ����  - -;;				
					// item option
					//pShopTemplate->MinOption;
					//pShopTemplate->MaxOption;

					//------------------------------------------------------
					// ������ item�� shelf�� �߰��Ѵ�.
					//------------------------------------------------------
					// ������� �߰���Ű�� �ȴ�.
					//------------------------------------------------------
					pShopShelf->AddItem( pItem );
				}				
			}
		}


		iID++;
	}

//	if(bMysterious)
	{
		if(bEnable)
			pShopShelf->SetEnable();
		else
			pShopShelf->SetDisable();
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
// Action
//-----------------------------------------------------------------------------
void
MNPC::Action()
{
	MCreature::Action();

	// ���丮�� ���
	if (m_CreatureType==217
		// �������� ���
		|| m_CreatureType==366)
	{
		//--------------------------------------------------------
		// ������ �ٲ� �ʿ䰡 ���� ��쿡..
		// �ɽ��Ҷ����� �ѹ��� ���� �ٲ��ֱ�.. - -;
		//--------------------------------------------------------			
		if (//Player�� �ƴϰ�
			m_CreatureType >= 4
			// ��� �ְ�..
			&& m_bAlive
			// ���������̰�
			&& m_Action==ACTION_STAND
			// �����ϰ��� ����
			&& m_listMoveBuffer.size()==0
			// ���������� ����..
			&& m_ActionCount>=m_ActionCountMax-1
			// random�ϰ�.. - -;
			&& (rand() % 5)==0)
		{
			// �����ϰ� player�� �ٶ󺻴�.
			SetDirectionToPosition( g_pPlayer->GetX(), g_pPlayer->GetY() );
		}
	}
	if(m_CreatureType >= 636 && m_CreatureType <= 639 )
	{
		if(m_ActionCount == 0 && !m_listEffect.empty())
		{
			ATTACHEFFECT_LIST::iterator itr = m_listEffect.begin();
			ATTACHEFFECT_LIST::iterator endItr = m_listEffect.end();
			
			while(itr != endItr )
			{
				MAttachEffect *pEffect =  *itr;
				
				pEffect->SetFrameID( pEffect->GetFrameID(), pEffect->GetMaxFrame() );
				itr++;
			}
		}
	}	
}