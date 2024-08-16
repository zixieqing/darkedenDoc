//----------------------------------------------------------------------
// MSlayerGear.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MItem.h"
#include "MSlayerGear.h"
#include "MQuickSlot.h"

#ifdef __GAME_CLIENT__
	#include "UIFunction.h"
	#include "ClientFunction.h"
	#include "MPlayer.h"
	#include "DebugInfo.h"
#endif
#include "MTimeItemManager.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MSlayerGear*		g_pSlayerGear = NULL;

MMagazine*		g_pCurrentMagazine = NULL;

//----------------------------------------------------------------------
// static
//----------------------------------------------------------------------
MSlayerGear::FUNCTION_GEARSLOT_CHECK
MSlayerGear::s_GearSlotCheckTable[MAX_GEAR_SLAYER] =
{
	IsGearSlotHelm,				// ����
	IsGearSlotNecklace,			// �����
	IsGearSlotCoat,				// ����
	IsGearSlotLeftHand,			// �޼�
	IsGearSlotRightHand,		// ������
	IsGearSlotGlove,			// �尩
	IsGearSlotBelt,				// ����
	IsGearSlotTrouser,			// ����			
	IsGearSlotBracelet,			// ����1
	IsGearSlotBracelet,			// ����2
	IsGearSlotRing,				// ����1
	IsGearSlotRing,				// ����2
	IsGearSlotRing,				// ����3
	IsGearSlotRing,				// ����4
	IsGearSlotShoes,			// �Ź�
	IsGearSlotCoreZap,			// �ھ���1
	IsGearSlotCoreZap,			// �ھ���2
	IsGearSlotCoreZap,			// �ھ���3
	IsGearSlotCoreZap,			// �ھ���4
	IsGearSlotPDA,				// PDA
	IsGearSlotShoulder,			// ���
	IsGearSlotBloodBible,		// ���� ���̺� 1
	IsGearSlotBloodBible,		// ���� ���̺� 2
	IsGearSlotBloodBible,		// ���� ���̺� 3
	IsGearSlotBloodBible,		// ���� ���̺� 4
	IsGearSlotBloodBible,		// ���� ���̺� 5
	IsGearSlotBloodBible,		// ���� ���̺� 6

};

//----------------------------------------------------------------------
// Ư�� ������ pItem�� ������ �� �ִ����� check�Ѵ�.
//----------------------------------------------------------------------
bool		MSlayerGear::IsGearSlotHelm(MItem* pItem)		{ return pItem->IsGearSlotHelm(); }		// ����
bool		MSlayerGear::IsGearSlotNecklace(MItem* pItem) 	{ return pItem->IsGearSlotNecklace(); }	// �����
bool		MSlayerGear::IsGearSlotCoat(MItem* pItem) 		{ return pItem->IsGearSlotCoat(); }		// ����
bool		MSlayerGear::IsGearSlotLeftHand(MItem* pItem)	{ return pItem->IsGearSlotLeftHand(); }	// �޼�	
bool		MSlayerGear::IsGearSlotRightHand(MItem* pItem)	{ return pItem->IsGearSlotRightHand(); }	// ������
bool		MSlayerGear::IsGearSlotGlove(MItem* pItem) 		{ return pItem->IsGearSlotGlove(); }	// �尩		
bool		MSlayerGear::IsGearSlotBelt(MItem* pItem) 		{ return pItem->IsGearSlotBelt(); }		// ����
bool		MSlayerGear::IsGearSlotTrouser(MItem* pItem) 	{ return pItem->IsGearSlotTrouser(); }	// ����		
bool		MSlayerGear::IsGearSlotBracelet(MItem* pItem) 	{ return pItem->IsGearSlotBracelet(); }	// ����
bool		MSlayerGear::IsGearSlotRing(MItem* pItem) 		{ return pItem->IsGearSlotRing(); }		// ����
bool		MSlayerGear::IsGearSlotShoes(MItem* pItem)		{ return pItem->IsGearSlotShoes(); }	// �Ź�	
bool		MSlayerGear::IsGearSlotCoreZap(MItem* pItem)	{ return pItem->IsGearSlotCoreZap(); }	// �ھ���
bool		MSlayerGear::IsGearSlotPDA(MItem* pItem)		{ return pItem->IsGearSlotPDA(); }// PDA
bool		MSlayerGear::IsGearSlotShoulder(MItem* pItem)	{ return pItem->IsGearSlotShoulder(); }// Shoulder

bool		MSlayerGear::IsGearSlotBloodBible(MItem* pItem)	{ return pItem->IsGearSlotBloodBible(); }// ���� ���̺�


//----------------------------------------------------------------------
//
// constructor
// 
//----------------------------------------------------------------------
MSlayerGear::MSlayerGear()
{
	g_pQuickSlot = NULL;
	m_bBloodBibleOpenCount = 0;
}

MSlayerGear::~MSlayerGear()
{
	g_pQuickSlot = NULL;
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Init 
//----------------------------------------------------------------------
// MAX_GEAR_SLAYER��ŭ�� Slot�� �����Ѵ�.
//----------------------------------------------------------------------
void
MSlayerGear::Init()
{
	// slot ����
	MPlayerGear::Init(MAX_GEAR_SLAYER);

	g_pCurrentMagazine = NULL;
	m_Gilles_CoreZap = 5;
	m_bBloodBibleOpenCount = 0;
}


//----------------------------------------------------------------------
// Check AffectStatus
//----------------------------------------------------------------------
// Ư�� �������� ���� ���� ���θ� üũ�Ѵ�.
//----------------------------------------------------------------------
void			
MSlayerGear::CheckAffectStatus(MItem* pItem)
{
	#ifdef __GAME_CLIENT__

		g_pPlayer->CheckAffectStatus( pItem );

	#endif
}

//----------------------------------------------------------------------
// Add Item ( pItem )
//----------------------------------------------------------------------
// pItem�� ������(?) slot�� �߰���Ų��.
//----------------------------------------------------------------------
bool			
MSlayerGear::AddItem(MItem* pItem)
{
	for (int i=0; i<MAX_GEAR_SLAYER; i++)
	{
		// �߰�������..
		if (AddItem( pItem, (enum GEAR_SLAYER)i ))
		{
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------
// Can Replace Item
//----------------------------------------------------------------------
// �����δ� Add or Replace�� �ǹ��Ѵ�.
// (n)�� pItem�� ���� �� �ְų�
// (n)�� ������ ��, �ٸ� �� �ϳ��� ��ü�� �� ���� true�̴�.
// pOldItem���� ��ü�� ���� �ִ� ��쿡 �װ� ����.
//----------------------------------------------------------------------
bool			
MSlayerGear::CanReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	// ��ġ ������� �ʴ� �������� ������� �ʴ´�
	if(pItem->IsAffectStatus() == false && !pItem->IsQuestItem() )
		return false;

	pOldItem = NULL;

	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsSlayerItem())
	{
		return false;
	}
	
	if(n>=GEAR_SLAYER_BLOOD_BIBLE1 && n<=GEAR_SLAYER_BLOOD_BIBLE6) // ���� ���̺��� ������ ����.
		return false;
	
	
	if(n == GEAR_SLAYER_PDA)
	{
		if(pItem->IsGearSlotPDA() == true)
		{
			if (m_ItemSlot[GEAR_SLAYER_PDA]==NULL)
				return true;
			else
			{
				pOldItem = m_ItemSlot[GEAR_SLAYER_PDA];
				return true;
			}
		}

	}

	if(n == GEAR_SLAYER_SHOULDER)
	{
		if(pItem->IsGearSlotShoulder()== true)
		{
			
			if (m_ItemSlot[GEAR_SLAYER_SHOULDER]==NULL)
				return true;
			else
			{
				pOldItem = m_ItemSlot[GEAR_SLAYER_SHOULDER];
				return true;
			}
		}
		
	}
	//-------------------------------------------------
	//
	// �տ� �����ҷ��� ���
	//
	//-------------------------------------------------
	if (n==GEAR_SLAYER_LEFTHAND || n==GEAR_SLAYER_RIGHTHAND)	
	{
		//-------------------------------------------------
		// [ ��� Item ] �� ���
		//-------------------------------------------------
		if (pItem->IsGearSlotTwoHand())
		{			
			//-------------------------------------------------
			// ����� Slot�� ��� ����ִ� ��� 
			//-------------------------------------------------			
			if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]==NULL
					&& m_ItemSlot[GEAR_SLAYER_LEFTHAND]==NULL)
			{
				return true;
			}
			
			//-------------------------------------------------
			// ��տ� �� ���� �ִ� ���
			//-------------------------------------------------
			if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]!=NULL 
				&& m_ItemSlot[GEAR_SLAYER_LEFTHAND]!=NULL)
			{
				//-------------------------------------------------
				// ��տ� �ִ°� ���ٸ�..
				//-------------------------------------------------
				if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]==m_ItemSlot[GEAR_SLAYER_LEFTHAND])
				{
					pOldItem = m_ItemSlot[GEAR_SLAYER_RIGHTHAND];
					return true;
				}
				
				return false;				
			}

			//-------------------------------------------------
			// �����տ��� ���� �ִ� ���
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]!=NULL)
			{
				pOldItem = m_ItemSlot[GEAR_SLAYER_RIGHTHAND];
				return true;
			}

			//-------------------------------------------------
			// �޼տ������� �ִ� ���
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_SLAYER_LEFTHAND]!=NULL)
			{			
				pOldItem = m_ItemSlot[GEAR_SLAYER_LEFTHAND];
				return true;
			}

			// �̷� ��찡 ���� �� ������? - -;;
			return false;
		}

		//-------------------------------------------------
		// [ ������ Item ] �� ���
		//-------------------------------------------------				
		else if (pItem->IsGearSlotRightHand())
		{
			// NULL�̰ų� ���ų� �׳� �־��ָ� �ȴ�.
			pOldItem = m_ItemSlot[GEAR_SLAYER_RIGHTHAND];
			return true;
		}
		
		//-------------------------------------------------				
		// [ �޼� Item ] �� ���
		//-------------------------------------------------
		else if (pItem->IsGearSlotLeftHand())
		{
			pOldItem = m_ItemSlot[GEAR_SLAYER_LEFTHAND];
			return true;
		}

		// �տ� �����ϴ°� �ƴ� ���
		return false;
	}
	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if (n >= GEAR_SLAYER_RING1 && n <= GEAR_SLAYER_RING4)	
	{
		if (pItem->IsGearSlotRing())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]==NULL) // �ھ����� ����� ���� ���� �� ����
			{
				pOldItem = m_ItemSlot[n];
				return true;
			}
		}
		else
		if (pItem->IsGearSlotCoreZap())
		{			
			if (m_ItemSlot[n]!=NULL) // �ھ����� ���� �־�� ���� �� �ִ�. 
			{
				if (m_ItemSlot[n]!=NULL) // �ھ����� ���� �־�� ���� �� �ִ�. 
				{
					if(m_ItemSlot[n+m_Gilles_CoreZap]!=NULL)
						pOldItem = m_ItemSlot[n+m_Gilles_CoreZap];
					else
						pOldItem = NULL;
					return true;
				}
			}
		}
		return false;
	}
	else if(n >= GEAR_SLAYER_ZAP1 && n <= GEAR_SLAYER_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
		return false;
	//----------------------------------------------------
	// ������ Slot���� Ȯ���ؾ� �Ѵ�.
	//----------------------------------------------------	
	if (pItem->IsGearItem()	&&				// pItem�� GearItem���� Ȯ��..
		(*s_GearSlotCheckTable[n])(pItem))	// ������ Slot���� Ȯ��
	{
		// ��ġ�� ������ ��ȯ�ǰų� �߰��� �� �ִ�.
		pOldItem = m_ItemSlot[n];
		return true;
	}

	return false;
}

//----------------------------------------------------------------------
// Add Item ( pItem, n )
//----------------------------------------------------------------------
// slot(n)�� pItem�� �߰��Ѵ�.
// �߰��� �� �ִ� slot���� Ȯ���ؾ� �Ѵ�.
//----------------------------------------------------------------------
bool			
MSlayerGear::AddItem(MItem* pItem, GEAR_SLAYER n)
{
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsSlayerItem())
	{
		return false;
	}

	//-------------------------------------------------
	// ��� Item�� ���� ���� üũ���ش�.
	//-------------------------------------------------
	if ((n==GEAR_SLAYER_LEFTHAND || n==GEAR_SLAYER_RIGHTHAND) &&
		pItem->IsGearSlotTwoHand())
	{
		// ����� Slot�� ��� ����ִ� ���¿��� �߰� �����ϴ�.
		if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]==NULL
				&& m_ItemSlot[GEAR_SLAYER_LEFTHAND]==NULL)
		{
			// �����տ� �߰��Ѵ�.			
			if (MPlayerGear::AddItem( pItem, GEAR_SLAYER_RIGHTHAND ))
			{
				// �޼տ��� �߰����ش�.
				m_ItemSlot[GEAR_SLAYER_LEFTHAND] = pItem;

				//-------------------------------------------------
				// ���̸� ���� źâ ����
				//-------------------------------------------------
				if (pItem->IsGunItem())
				{
					MGunItem* pGunItem = (MGunItem*)pItem;
					g_pCurrentMagazine = pGunItem->GetMagazine();
				}

				//-------------------------------------------------
				// ����� �߰��� ��� --> sound���
				//-------------------------------------------------
				#ifdef __GAME_CLIENT__
					PlaySound( pItem->GetGearSoundID() );
					g_pPlayer->CalculateStatus();	
				#endif

				return true;
			}

			return false;
		}

		return false;
	}
	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if (n >= GEAR_SLAYER_RING1 && n <= GEAR_SLAYER_RING4)	
	{
		if (pItem->IsGearSlotRing())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]==NULL&&m_ItemSlot[n]==NULL) // ���� ���� �ھ����� ����� ���� ���� �� ����
			{
				if (MPlayerGear::AddItem( pItem, n ))	
				{
					//-------------------------------------------------
					// ����� �߰��� ��� --> sound���
					//-------------------------------------------------
					#ifdef __GAME_CLIENT__
						PlaySound( pItem->GetGearSoundID() );
						g_pPlayer->CalculateStatus();	
					#endif

					return true;
				}
			}
		}
		else 
		if (pItem->IsGearSlotCoreZap())
		{
			if (m_ItemSlot[n-m_Gilles_CoreZap]!=NULL && m_ItemSlot[n]==NULL) // �ش���ġ�� ���� �ְ� �ھ����� ���� ��츸 �ھ��� �߰�
			{		
				if (MPlayerGear::AddItem( pItem, n + m_Gilles_CoreZap ))// �ھ��� ��ġ�� �߰�
				{
					//-------------------------------------------------
					// ����� �߰��� ��� --> sound���
					//-------------------------------------------------
					#ifdef __GAME_CLIENT__
						PlaySound( pItem->GetGearSoundID() );
						g_pPlayer->CalculateStatus();	
					#endif

					return true;
				}

			}
		}

		return false;
	}
//	else if(n >= GEAR_SLAYER_ZAP1 && n <= GEAR_SLAYER_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
//		return false;
	//----------------------------------------------------
	// ������ Slot���� Ȯ���ؾ� �Ѵ�.
	//----------------------------------------------------	
	if (m_ItemSlot[n]==NULL &&				// n��° slot�� ����ִ��� Ȯ��
		pItem->IsGearItem()	&&				// pItem�� GearItem���� Ȯ��..
		(*s_GearSlotCheckTable[n])(pItem))	// ������ Slot���� Ȯ��
	{
		// n��° slot�� pItem�� �߰��Ѵ�.
		bool bAdd = MPlayerGear::AddItem( pItem, n );

		//--------------------------------------------
		// ����� �־�����..
		//--------------------------------------------
		if (bAdd)
		{
			//--------------------------------------------
			// belt�� ���
			//--------------------------------------------
			// QuickSlot�� ���� ����̴�.
			//--------------------------------------------
			if (n==GEAR_SLAYER_BELT)
			{
				if (pItem->GetItemClass()==ITEM_CLASS_BELT)
				{
					g_pQuickSlot = (MBelt*)pItem;
					
					#ifdef __GAME_CLIENT__
						UI_ResetQuickItemSlot();
					#endif
				}
				else
				{
					// �̷� ���� ���� �� ���� �ʹ�.					
				}
			}
			else
			{
				//-------------------------------------------------
				// ���̸� ���� źâ ����
				//-------------------------------------------------
				if (pItem->IsGunItem())
				{
					MGunItem* pGunItem = (MGunItem*)pItem;
					g_pCurrentMagazine = pGunItem->GetMagazine();
				}
			}

			//-------------------------------------------------
			// ����� �߰��� ��� --> sound���
			//-------------------------------------------------
			#ifdef __GAME_CLIENT__
				PlaySound( pItem->GetGearSoundID() );
				g_pPlayer->CalculateStatus();	
			#endif

			return true;
		}
		
		//--------------------------------------------
		// ������ ���..
		//--------------------------------------------
		return false;		
	}

	return false;
}

//----------------------------------------------------------------------
// Remove Item ( n)
//----------------------------------------------------------------------
MItem*			
MSlayerGear::RemoveItem(GEAR_SLAYER n)
{ 
	MItem* pItem = m_ItemSlot[n];
		
	//-----------------------------------------------------
	// ���� ���
	//-----------------------------------------------------
	if (pItem==NULL)
	{
		return NULL;
	}

	//-----------------------------------------------------
	// ��� �����̸� ���������� �����Ѵ�.
	//-----------------------------------------------------
	if (pItem->IsGearSlotTwoHand())
	{
		n = GEAR_SLAYER_RIGHTHAND;
	}
	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if(n>=GEAR_SLAYER_RING1 && n<= GEAR_SLAYER_RING4) 
	{
		if(NULL != m_ItemSlot[n+m_Gilles_CoreZap]) // �ھ����� �پ� ������ �ھ����� ����
			n = (GEAR_SLAYER)(n + m_Gilles_CoreZap); // �ھ��� ��ġ
	}
//	else if(n >= GEAR_SLAYER_ZAP1 && n <= GEAR_SLAYER_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
//		return false;

	pItem = MPlayerGear::RemoveItem( (BYTE)n );

	//-----------------------------------------------------
	// ���� ���
	//-----------------------------------------------------
	if (pItem==NULL)
	{
		return NULL;
	}

	//-----------------------------------------------------
	// Belt�� ���
	//-----------------------------------------------------
	// QuickSlot�� ���ŵ� ����̴�.
	//-----------------------------------------------------
	if (n==GEAR_SLAYER_BELT)
	{
		g_pQuickSlot = NULL;

		#ifdef __GAME_CLIENT__
			g_pPlayer->CalculateStatus();
		#endif

		return pItem;
	}

	//-----------------------------------------------------
	// ��� Item�� ��� ����� Slot�� ��� ��������� �Ѵ�.
	//-----------------------------------------------------
	if (pItem->IsGearSlotTwoHand())
	{
		m_ItemSlot[GEAR_SLAYER_LEFTHAND] = NULL;
		m_ItemSlot[GEAR_SLAYER_RIGHTHAND] = NULL;
	}
	
	//-------------------------------------------------
	// ���̸� ���� źâ ����
	//-------------------------------------------------
	if (pItem->IsGunItem())
	{
		g_pCurrentMagazine = NULL;
	}

	#ifdef __GAME_CLIENT__
		g_pPlayer->CalculateStatus();
	#endif

	return pItem;
}

//----------------------------------------------------------------------
// RemoveItem : id�� ���� item�� �����Ѵ�.
//----------------------------------------------------------------------
MItem*			
MSlayerGear::RemoveItem(TYPE_OBJECTID id)
{ 
	MItem* pItem = MPlayerGear::RemoveItem( id ); 

	//-----------------------------------------------------
	// ���� ���
	//-----------------------------------------------------
	if (pItem==NULL)
	{
		return NULL;
	}

	// ������...

	//-----------------------------------------------------
	// Belt�� ���
	//-----------------------------------------------------
	// QuickSlot�� ���ŵ� ����̴�.
	//-----------------------------------------------------
	if (pItem->GetItemClass()==ITEM_CLASS_BELT)
	{
		g_pQuickSlot = NULL;

		#ifdef __GAME_CLIENT__
			g_pPlayer->CalculateStatus();
		#endif

		return pItem;
	}

	//-----------------------------------------------------
	// ��� Item�� ��� ����� Slot�� ��� ��������� �Ѵ�.
	//-----------------------------------------------------
	if (pItem->IsGearSlotTwoHand())
	{
		m_ItemSlot[GEAR_SLAYER_LEFTHAND] = NULL;
		m_ItemSlot[GEAR_SLAYER_RIGHTHAND] = NULL;
	}

	//-------------------------------------------------
	// ���̸� ���� źâ ����
	//-------------------------------------------------
	if (pItem->IsGunItem())
	{
		g_pCurrentMagazine = NULL;
	}

	#ifdef __GAME_CLIENT__
		g_pPlayer->CalculateStatus();
	#endif

	return pItem;
}

//----------------------------------------------------------------------
// ReplaceItem : pItem�� �߰��ϰ� ���� �ִٸ� Item��ȯ
//----------------------------------------------------------------------
bool			
MSlayerGear::ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsSlayerItem())
	{
		pOldItem = NULL;
		return false;
	}

	
	if(n == GEAR_SLAYER_PDA)
	{
		if(pItem->IsGearSlotPDA()== true)
		{
		if (m_ItemSlot[GEAR_SLAYER_PDA]==NULL)
		{
			MPlayerGear::ReplaceItem( pItem, GEAR_SLAYER_PDA, pOldItem );
			return true;
		}
		else
			return false;
		}
	}

	if(n == GEAR_SLAYER_SHOULDER)
	{
		if(pItem->IsGearSlotShoulder()== true)
		{
			if (m_ItemSlot[GEAR_SLAYER_SHOULDER]==NULL)
			{
				MPlayerGear::ReplaceItem( pItem, GEAR_SLAYER_SHOULDER, pOldItem );
				return true;
			}
			else
				return false;
		}	
	}
	
	//-------------------------------------------------
	//
	// �տ� �����ҷ��� ���
	//
	//-------------------------------------------------
	if (n==GEAR_SLAYER_LEFTHAND || n==GEAR_SLAYER_RIGHTHAND)	
	{
		bool bAdd = false;
			
		//-------------------------------------------------
		// [ ��� Item ] �� ���
		//-------------------------------------------------
		if (pItem->IsGearSlotTwoHand())
		{			
			//-------------------------------------------------
			// ����� Slot�� ��� ����ִ� ���
			//-------------------------------------------------
			// �׳� �߰��Ѵ�.
			//-------------------------------------------------
			if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]==NULL
					&& m_ItemSlot[GEAR_SLAYER_LEFTHAND]==NULL)
			{
				// �׳� �߰��Ѵ�.
				pOldItem = NULL;
				if (MPlayerGear::AddItem( pItem, GEAR_SLAYER_RIGHTHAND ))
				{
					//-------------------------------------------------
					// item�� ������ ���� ����
					//-------------------------------------------------
					CheckItemStatus( pItem, GEAR_SLAYER_RIGHTHAND );

					pItem->SetItemSlot( GEAR_SLAYER_RIGHTHAND );
					m_ItemSlot[GEAR_SLAYER_LEFTHAND] = pItem;
					m_ItemSlot[GEAR_SLAYER_RIGHTHAND] = pItem;

					//-------------------------------------------------
					// ���̸� ���� źâ ����
					//-------------------------------------------------
					if (pItem->IsGunItem())
					{
						MGunItem* pGunItem = (MGunItem*)pItem;
						g_pCurrentMagazine = pGunItem->GetMagazine();

						//------------------------------------------
						// �Ѿ��� ���� ���
						//------------------------------------------
						if (g_pCurrentMagazine==NULL)
						{
							MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

							// �ǹ� ���� - -;
							pMagazine->SetID( 0 );

							// �̰Ŵ� �ѿ� ���缭 ����ߵȴ�.
							for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
							{
								pMagazine->SetItemType(	j );

								if (pMagazine->IsInsertToItem( pItem ))
								{
									break;
								}
							}

							// �ǹ� ����
							pMagazine->ClearItemOption();
						
							// źâ ����
							pMagazine->SetNumber( 0 );

							// źâ ����
							pGunItem->SetMagazine( pMagazine );
						}
					}				

					//-------------------------------------------------
					// ����� �߰��� ��� --> sound���
					//-------------------------------------------------
					#ifdef __GAME_CLIENT__
						PlaySound( pItem->GetGearSoundID() );						
						g_pPlayer->CalculateStatus();			
					#endif

					return true;
				}

				return false;
			}
			
			//-------------------------------------------------
			// ��տ� �� ���� �ִ� ���
			//-------------------------------------------------
			if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]!=NULL 
				&& m_ItemSlot[GEAR_SLAYER_LEFTHAND]!=NULL)
			{
				//-------------------------------------------------
				// ��տ� �ִ°� ���ٸ�..
				//-------------------------------------------------
				if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]==m_ItemSlot[GEAR_SLAYER_LEFTHAND])
				{
					// ��� ����� ��ü�ϴ� ����̴�.
					if (MPlayerGear::ReplaceItem( pItem, 
													GEAR_SLAYER_RIGHTHAND, 
													pOldItem ))
					{
						//-------------------------------------------------
						// item�� ������ ���� ����
						//-------------------------------------------------
						CheckItemStatus( pItem, GEAR_SLAYER_RIGHTHAND );

						//pItem->SetItemSlot( GEAR_SLAYER_RIGHTHAND );
						m_ItemSlot[GEAR_SLAYER_LEFTHAND] = pItem;
						//m_ItemSlot[GEAR_SLAYER_RIGHTHAND] = pItem;

						//-------------------------------------------------
						// ���ŵ� ���� ���� ���
						//-------------------------------------------------
						if (pOldItem!=NULL && pOldItem->IsGunItem())
						{
							g_pCurrentMagazine = NULL;
						}

						//-------------------------------------------------
						// ���̸� ���� źâ ����
						//-------------------------------------------------
						if (pItem->IsGunItem())
						{
							MGunItem* pGunItem = (MGunItem*)pItem;
							g_pCurrentMagazine = pGunItem->GetMagazine();
						}
					
						//-------------------------------------------------
						// ����� �߰��� ��� --> sound���
						//-------------------------------------------------
						#ifdef __GAME_CLIENT__
							PlaySound( pItem->GetGearSoundID() );
							g_pPlayer->CalculateStatus();	
						#endif	

						return true;
					}

					return false;
				}
				
				//-------------------------------------------------
				// ��տ� �ִ°� �ٸ��ٸ�..
				//-------------------------------------------------
				pOldItem = NULL;
				return false;
				
			}

			//-------------------------------------------------
			// �����տ� ���� �ִ� ���
			//-------------------------------------------------
			// �������� Item�� Replace�Ѵ�.
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_SLAYER_RIGHTHAND]!=NULL)
			{
				bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_SLAYER_RIGHTHAND, 
													pOldItem );
			}		

			//-------------------------------------------------
			// �޼տ� ���� �ִ� ���
			//-------------------------------------------------
			// �޼��� Item�� Replace�Ѵ�.
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_SLAYER_LEFTHAND]!=NULL)
			{
				bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_SLAYER_LEFTHAND, 
													pOldItem );					
			}

			//-----------------------------------------------------
			// ����� Slot�� ��� ����..
			//-----------------------------------------------------
			if (bAdd)
			{
				//-------------------------------------------------
				// item�� ������ ���� ����
				//-------------------------------------------------
				CheckItemStatus( pItem, GEAR_SLAYER_RIGHTHAND );
				
				pItem->SetItemSlot( GEAR_SLAYER_RIGHTHAND );
				m_ItemSlot[GEAR_SLAYER_LEFTHAND] = pItem;
				m_ItemSlot[GEAR_SLAYER_RIGHTHAND] = pItem;

				//-------------------------------------------------
				// ���ŵ� ���� ���� ���
				//-------------------------------------------------
				if (pOldItem!=NULL && pOldItem->IsGunItem())
				{
					g_pCurrentMagazine = NULL;
				}

				//-------------------------------------------------
				// ���̸� ���� źâ ����
				//-------------------------------------------------
				if (pItem->IsGunItem())
				{
					MGunItem* pGunItem = (MGunItem*)pItem;
					g_pCurrentMagazine = pGunItem->GetMagazine();
				}				
		
				//-------------------------------------------------
				// ����� �߰��� ��� --> sound���
				//-------------------------------------------------
				#ifdef __GAME_CLIENT__
					PlaySound( pItem->GetGearSoundID() );
					g_pPlayer->CalculateStatus();
				#endif

				return true;
			}

			return false;
		}
		//-------------------------------------------------
		// [ ������ Item ] �� ���
		//-------------------------------------------------		
		else if (pItem->IsGearSlotRightHand())
		{
			bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_SLAYER_RIGHTHAND, 
													pOldItem );

			//-------------------------------------------------
			// ��ȯ�Ǿ� ���� Item�� ����� ���
			//-------------------------------------------------
			if (pOldItem!=NULL)
			{
				if (pOldItem->IsGearSlotTwoHand())
				{
					// �޼��� ����д�.
					m_ItemSlot[GEAR_SLAYER_LEFTHAND] = NULL;
				}

				//-------------------------------------------------
				// ���̸� ���� źâ ����
				//-------------------------------------------------
				if (pOldItem->IsGunItem())
				{
					g_pCurrentMagazine = NULL;
				}
			}

			if (bAdd)
			{
				//-------------------------------------------------
				// item�� ������ ���� ����
				//-------------------------------------------------
				CheckItemStatus( pItem, GEAR_SLAYER_RIGHTHAND );

				//-------------------------------------------------
				// ����� �߰��� ��� --> sound���
				//-------------------------------------------------
				#ifdef __GAME_CLIENT__
					PlaySound( pItem->GetGearSoundID() );
					g_pPlayer->CalculateStatus();
				#endif

				return true;
			}

			return false;
		}
		//-------------------------------------------------
		// [ �޼� Item ] �� ���
		//-------------------------------------------------
		else if (pItem->IsGearSlotLeftHand())
		{
			bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_SLAYER_LEFTHAND, 
													pOldItem );
			//-------------------------------------------------
			// ��ȯ�Ǿ� ���� Item�� ����� ���
			//-------------------------------------------------
			if (pOldItem!=NULL)
			{
				if (pOldItem->IsGearSlotTwoHand())
				{
					// �������� ����д�.
					m_ItemSlot[GEAR_SLAYER_RIGHTHAND] = NULL;
				}

				//-------------------------------------------------
				// ���̸� ���� źâ ����
				//-------------------------------------------------
				if (pOldItem->IsGunItem())
				{
					g_pCurrentMagazine = NULL;
				}
			}

			if (bAdd)
			{
				//-------------------------------------------------
				// item ���� ����
				//-------------------------------------------------
				CheckItemStatus( pItem, GEAR_SLAYER_LEFTHAND );
				
				//-------------------------------------------------
				// ����� �߰��� ��� --> sound���
				//-------------------------------------------------
				#ifdef __GAME_CLIENT__
					PlaySound( pItem->GetGearSoundID() );
					g_pPlayer->CalculateStatus();
				#endif	

				return true;
			}

			return false;
		}
		
		//-------------------------------------------------
		// �տ� �����ҷ��µ�
		// �տ� ������ �� �ִ� Item�� �ƴ� ���
		//-------------------------------------------------
		pOldItem = NULL;
		return false;
		
	}
	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if (n >= GEAR_SLAYER_RING1 && n <= GEAR_SLAYER_RING4)	
	{
		if (pItem->IsGearSlotRing())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]!=NULL) // �ھ����� ������ �� ����
				return false;
		}
		else
		if (pItem->IsGearSlotCoreZap())
		{			
			if (m_ItemSlot[n]!=NULL) // �ھ����� ���� �־�� ���� �� �ִ�. 
			{
				bool bAdd = false;
				if(m_ItemSlot[n+m_Gilles_CoreZap] == NULL)// ���� �ھ����� ������
				{
					pOldItem = NULL;
					bAdd = MPlayerGear::AddItem( pItem, n+m_Gilles_CoreZap );	// �� �߰�
				}
				else // ���� �ھ����� ������ ��ȯ
				{
					bAdd = MPlayerGear::ReplaceItem( pItem, n+m_Gilles_CoreZap, pOldItem );	
					
					if (bAdd)
					{
						CheckItemStatus( pItem, n+m_Gilles_CoreZap );
					}			
				}

				if (bAdd) // �� �߰� ������ 
				{
					#ifdef __GAME_CLIENT__
						PlaySound( pItem->GetGearSoundID() );
						g_pPlayer->CalculateStatus();
					#endif
					return true;
				}
				else 
					return false;
			}
			return false;
		}
	
	}
//	else if(n >= GEAR_SLAYER_ZAP1 && n <= GEAR_SLAYER_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
//		return false;
	
	//----------------------------------------------------
	// ������ Slot���� Ȯ���ؾ� �Ѵ�.
	//----------------------------------------------------	
	if (pItem->IsGearItem()	&&				// pItem�� GearItem���� Ȯ��..
		(*s_GearSlotCheckTable[n])(pItem))	// ������ Slot���� Ȯ��
	{
		bool bAdd;
		//----------------------------------------------------
		// �ٸ� Item�� ���� ��� --> �׳� �߰�
		//----------------------------------------------------	
		if (m_ItemSlot[n]==NULL)				// n��° slot�� ����ִ��� Ȯ��
		{
			pOldItem = NULL;
			// n��° slot�� pItem�� �߰��Ѵ�.
			bAdd = MPlayerGear::AddItem( pItem, n );			
		}
		//----------------------------------------------------	
		// ��ȯ �ؾ� �Ǵ� ���
		//----------------------------------------------------	
		else
		{
			//-----------------------------------------------------
			// n��° slot�� Item�� ��ȯ�Ѵ�.
			//-----------------------------------------------------
			bAdd = MPlayerGear::ReplaceItem( pItem, n, pOldItem );	
			
			//-------------------------------------------------
			// item�� ������ ���� ����
			//-------------------------------------------------
			if (bAdd)
			{
				CheckItemStatus( pItem, n );
			}			
		}

		//--------------------------------------------
		// ����� �־�����..
		//--------------------------------------------
		if (bAdd)
		{
			//--------------------------------------------
			// belt�� ���
			//--------------------------------------------
			// QuickSlot�� ���� ����̴�.
			//--------------------------------------------
			if (n==GEAR_SLAYER_BELT)
			{
				if (pItem->GetItemClass()==ITEM_CLASS_BELT)
				{
					g_pQuickSlot = (MBelt*)pItem;				
				}
				else
				{
					// �̷� ���� ���� �� ���� �ʹ�.					
				}
			}
			else
			{
				//-------------------------------------------------
				// ���� ������ ���
				// ������ ���� ���� üũ�ϹǷ�..
				// ��.. ���ɼ��� ���� �ڵ��.. - -;;
				//-------------------------------------------------
				if (pOldItem!=NULL && pOldItem->IsGunItem())
				{
					g_pCurrentMagazine = NULL;
				}

				//-------------------------------------------------
				// ���̸� ���� źâ ����
				//-------------------------------------------------
				if (pItem->IsGunItem())
				{
					MGunItem* pGunItem = (MGunItem*)pItem;
					g_pCurrentMagazine = pGunItem->GetMagazine();
				}	
			}

			//-------------------------------------------------
			// ����� �߰��� ��� --> sound���
			//-------------------------------------------------
			#ifdef __GAME_CLIENT__
				PlaySound( pItem->GetGearSoundID() );
				g_pPlayer->CalculateStatus();
			#endif

			return true;
		}
	}

	return false;
}

MItem*	MSlayerGear::GetGearItem_PickUp(int &n) const	
{
	int Slot = n;
//	if(Slot>=GEAR_SLAYER_BLOOD_BIBLE1 && Slot<=GEAR_SLAYER_BLOOD_BIBLE6) // ���� ���̺��� ������ ����.
//		return NULL;
	if(Slot>=GEAR_SLAYER_RING1 && Slot<=GEAR_SLAYER_RING4)
	{
		if(m_ItemSlot[Slot+m_Gilles_CoreZap]!=NULL)
		{
			n = n+m_Gilles_CoreZap;
			return MSlotItemManager::GetItem( (BYTE)(Slot+m_Gilles_CoreZap) ); 
		}
	}
	
	return MSlotItemManager::GetItem( (BYTE)Slot ); 
}


MItem*	MSlayerGear::GetGearCoreZapItem(int slot) const	
{
	if(slot>=GEAR_SLAYER_RING1 && slot<=GEAR_SLAYER_RING4)
	{
		if(m_ItemSlot[slot+m_Gilles_CoreZap]!=NULL)
		{
			if(m_ItemSlot[slot+m_Gilles_CoreZap]->GetItemClass() == ITEM_CLASS_CORE_ZAP)
				return MSlotItemManager::GetItem( (BYTE)(slot+m_Gilles_CoreZap) ); 
		}
	}
	
	return NULL;
}



MItem*	MSlayerGear::GetGearCoreZapedItem(int slot) const	
{
	if(slot>=GEAR_SLAYER_ZAP1 && slot<=GEAR_SLAYER_ZAP4)
	{
		if(slot-m_Gilles_CoreZap<0)
			return NULL;
		if(m_ItemSlot[slot-m_Gilles_CoreZap]!=NULL)
		{
			if(m_ItemSlot[slot-m_Gilles_CoreZap]->GetItemClass() == ITEM_CLASS_RING)
				return MSlotItemManager::GetItem( (BYTE)(slot-m_Gilles_CoreZap) ); 
		}
	}
	
	return NULL;
}

const bool	MSlayerGear::IsHasAllCoreZap(int CoreZapType) const	
{
	BYTE bType[4] = {0,};
	if(CoreZapType == 0) // ���巹 �ھ� �� �� ���
	{
		MItem* pItem;
		for(int i = 0; i<4; i++)
		{
			pItem = m_ItemSlot[GEAR_SLAYER_ZAP1+i];
			if(pItem != NULL)
			{
				if(pItem->GetItemType()>3)
					return false;
				if(bType[pItem->GetItemType()]!= 0)
					return false;
				bType[pItem->GetItemType()] = 1;
			}
			else
				return false;
		}
		if(bType[0]+bType[1]+bType[2]+bType[3] == 4)
			return true;
	}
	
	return false;
}

const bool	MSlayerGear::IsCloseBloodBibleSlot(int slot) const	
{
	if(slot>=GEAR_SLAYER_BLOOD_BIBLE1 && slot<=GEAR_SLAYER_BLOOD_BIBLE6)
	{
			int TempSlot = slot - GEAR_SLAYER_BLOOD_BIBLE1 + 1;
		if(TempSlot > m_bBloodBibleOpenCount)
			return true;
	}
	return false;
}
