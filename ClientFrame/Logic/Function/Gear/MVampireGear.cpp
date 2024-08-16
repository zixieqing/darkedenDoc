//----------------------------------------------------------------------
// MVampireGear.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MItem.h"
#include "MVampireGear.h"

#ifdef __GAME_CLIENT__
	#include "ClientFunction.h"
	#include "MPlayer.h"
#endif
#include "MTimeItemManager.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MVampireGear*		g_pVampireGear = NULL;

//----------------------------------------------------------------------
// static
//----------------------------------------------------------------------
MVampireGear::FUNCTION_GEARSLOT_CHECK
MVampireGear::s_GearSlotCheckTable[MAX_GEAR_VAMPIRE] =
{
	IsGearSlotNecklace,			// �����
	IsGearSlotCoat,				// ����
	IsGearSlotBracelet,			// ����1
	IsGearSlotBracelet,			// ����2
	IsGearSlotRing,				// ����1
	IsGearSlotRing,				// ����2
	IsGearSlotRing,				// ����3
	IsGearSlotRing,				// ����4
	IsGearSlotEarRing,			// �Ͱ���1
	IsGearSlotEarRing,			// �Ͱ���2
	IsGearSlotLeftHand,			// �޼�
	IsGearSlotRightHand,		// ������
	IsGearSlotAmulet,			// ����1
	IsGearSlotAmulet,			// ����2
	IsGearSlotAmulet,			// ����3
	IsGearSlotAmulet,			// ����4
	IsGearSlotCoreZap,			// �ھ���1
	IsGearSlotCoreZap,			// �ھ���2
	IsGearSlotCoreZap,			// �ھ���3
	IsGearSlotCoreZap,			// �ھ���4
	IsGearSlotDermis,			// ������ ����?
	IsGearSlotPersona,			// ������ �丣�ҳ�
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
bool		MVampireGear::IsGearSlotNecklace(MItem* pItem) 	{ return pItem->IsGearSlotVampireNecklace(); }	// �����
bool		MVampireGear::IsGearSlotCoat(MItem* pItem) 		{ return pItem->IsGearSlotVampireCoat(); }		// ����
bool		MVampireGear::IsGearSlotBracelet(MItem* pItem) 	{ return pItem->IsGearSlotVampireBracelet(); }	// ����
bool		MVampireGear::IsGearSlotRing(MItem* pItem) 		{ return pItem->IsGearSlotVampireRing(); }		// ����
bool		MVampireGear::IsGearSlotEarRing(MItem* pItem) 	{ return pItem->IsGearSlotVampireEarRing(); }	// �Ͱ���
bool		MVampireGear::IsGearSlotLeftHand(MItem* pItem) 	{ return pItem->IsGearSlotVampireLeftHand(); }	// �޼�
bool		MVampireGear::IsGearSlotRightHand(MItem* pItem) { return pItem->IsGearSlotVampireRightHand(); }	// ������
bool		MVampireGear::IsGearSlotAmulet(MItem* pItem)	{ return pItem->IsGearSlotVampireAmulet(); }	// ������
bool		MVampireGear::IsGearSlotCoreZap(MItem* pItem)	{ return pItem->IsGearSlotVampireCoreZap(); }	// �ھ���
bool		MVampireGear::IsGearSlotDermis(MItem* pItem)	{ return pItem->IsGearSlotVampireDermis(); }	// ����
bool		MVampireGear::IsGearSlotPersona(MItem* pItem)	{ return pItem->IsGearSlotVampirePersona(); }	// �丣��
bool		MVampireGear::IsGearSlotBloodBible(MItem* pItem){ return pItem->IsGearSlotVampireBloodBible(); }	// ���� ���̺�

//----------------------------------------------------------------------
//
// constructor
// 
//----------------------------------------------------------------------
MVampireGear::MVampireGear()
{
	m_bBloodBibleOpenCount = 0;
}

MVampireGear::~MVampireGear()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Init 
//----------------------------------------------------------------------
// MAX_GEAR_VAMPIRE��ŭ�� Slot�� �����Ѵ�.
//----------------------------------------------------------------------
void
MVampireGear::Init()
{
	// slot ����
	MPlayerGear::Init(MAX_GEAR_VAMPIRE);
	m_Gilles_CoreZap = 12;
	m_bBloodBibleOpenCount = 0;
}

//----------------------------------------------------------------------
// Check AffectStatus
//----------------------------------------------------------------------
// Ư�� �������� ���� ���� ���θ� üũ�Ѵ�.
//----------------------------------------------------------------------
void			
MVampireGear::CheckAffectStatus(MItem* pItem)
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
MVampireGear::AddItem(MItem* pItem)
{
	for (int i=0; i<MAX_GEAR_VAMPIRE; i++)
	{
		// �߰�������..
		if (AddItem( pItem, (enum GEAR_VAMPIRE)i ))
		{
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------
// Can Replace Item ( pItem, n )
//----------------------------------------------------------------------
// slot(n)�� pItem�� �߰��Ѵ�.
// �߰��� �� �ִ� slot���� Ȯ���ؾ� �Ѵ�.
//
// pOldItem���� ��ü�� ���� �ִ� ��쿡 �װ� ����.
//----------------------------------------------------------------------
bool			
MVampireGear::CanReplaceItem(MItem* pItem, GEAR_VAMPIRE n, MItem*& pOldItem)
{	
	// ��ġ ������� �ʴ� �������� ������� �ʴ´�
	if(pItem->IsAffectStatus() == false&& !pItem->IsQuestItem())
		return false;

	pOldItem = NULL;

	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsVampireItem())
	{
		return false;
	}

	if(n>=GEAR_VAMPIRE_BLOOD_BIBLE1 && n<=GEAR_VAMPIRE_BLOOD_BIBLE6) // ���� ���̺��� ������ ����.
		return false;
	//-------------------------------------------------
	//
	// �տ� �����ҷ��� ���
	//
	//-------------------------------------------------
	if (n==GEAR_VAMPIRE_LEFTHAND || n==GEAR_VAMPIRE_RIGHTHAND)	
	{
		//-------------------------------------------------
		// [ ��� Item ] �� ���
		//-------------------------------------------------
		if (pItem->IsGearSlotTwoHand())
		{			
			//-------------------------------------------------
			// ����� Slot�� ��� ����ִ� ��� 
			//-------------------------------------------------			
			if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]==NULL
					&& m_ItemSlot[GEAR_VAMPIRE_LEFTHAND]==NULL)
			{
				return true;
			}
			
			//-------------------------------------------------
			// ��տ� �� ���� �ִ� ���
			//-------------------------------------------------
			if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]!=NULL 
				&& m_ItemSlot[GEAR_VAMPIRE_LEFTHAND]!=NULL)
			{
				//-------------------------------------------------
				// ��տ� �ִ°� ���ٸ�..
				//-------------------------------------------------
				if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]==m_ItemSlot[GEAR_VAMPIRE_LEFTHAND])
				{
					pOldItem = m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND];
					return true;
				}
				
				return false;				
			}

			//-------------------------------------------------
			// �����տ��� ���� �ִ� ���
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]!=NULL)
			{
				pOldItem = m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND];
				return true;
			}

			//-------------------------------------------------
			// �޼տ������� �ִ� ���
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_VAMPIRE_LEFTHAND]!=NULL)
			{			
				pOldItem = m_ItemSlot[GEAR_VAMPIRE_LEFTHAND];
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
			pOldItem = m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND];
			return true;
		}
		
		//-------------------------------------------------				
		// [ �޼� Item ] �� ���
		//-------------------------------------------------
		else if (pItem->IsGearSlotLeftHand())
		{
			pOldItem = m_ItemSlot[GEAR_VAMPIRE_LEFTHAND];
			return true;
		}

		// �տ� �����ϴ°� �ƴ� ���
		return false;
	}
	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if (n >= GEAR_VAMPIRE_RING1 && n <= GEAR_VAMPIRE_RING4)	
	{
		if (pItem->IsGearSlotVampireRing())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]==NULL) // �ھ����� ����� ���� ���� �� ����
			{
				pOldItem = m_ItemSlot[n];
				return true;
			}
		}
		else
		if (pItem->IsGearSlotVampireCoreZap())
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
		return false;
	}
	else if(n >= GEAR_VAMPIRE_ZAP1 && n <= GEAR_VAMPIRE_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
		return false;

	//----------------------------------------------------
	// ������ Slot���� Ȯ���ؾ� �Ѵ�.
	//----------------------------------------------------	
	if (pItem->IsGearItem()	&&				// pItem�� GearItem���� Ȯ��..
		(*s_GearSlotCheckTable[n])(pItem))	// ������ Slot���� Ȯ��
	{
		// n��° slot�� pItem�� �߰��Ѵ�.
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
MVampireGear::AddItem(MItem* pItem, GEAR_VAMPIRE n)
{	
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsVampireItem())
	{
		return false;
	}

	//-------------------------------------------------
	// ��� Item�� ���� ���� üũ���ش�.
	//-------------------------------------------------
	if ((n==GEAR_VAMPIRE_LEFTHAND || n==GEAR_VAMPIRE_RIGHTHAND) &&
		pItem->IsGearSlotTwoHand())
	{
		// ����� Slot�� ��� ����ִ� ���¿��� �߰� �����ϴ�.
		if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]==NULL
				&& m_ItemSlot[GEAR_VAMPIRE_LEFTHAND]==NULL)
		{
			// �����տ� �߰��Ѵ�.			
			if (MPlayerGear::AddItem( pItem, GEAR_VAMPIRE_RIGHTHAND ))
			{
				// �޼տ��� �߰����ش�.
				m_ItemSlot[GEAR_VAMPIRE_LEFTHAND] = pItem;

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
	if (n >= GEAR_VAMPIRE_RING1 && n <= GEAR_VAMPIRE_RING4)	
	{
		if (pItem->IsGearSlotVampireRing())
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
		if (pItem->IsGearSlotVampireCoreZap())
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
//	else if(n >= GEAR_VAMPIRE_ZAP1 && n <= GEAR_VAMPIRE_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
//		return false;
	//----------------------------------------------------
	// ������ Slot���� Ȯ���ؾ� �Ѵ�.
	//----------------------------------------------------	
	if (m_ItemSlot[n]==NULL &&				// n��° slot�� ����ִ��� Ȯ��
		pItem->IsGearItem()	&&				// pItem�� GearItem���� Ȯ��..
		(*s_GearSlotCheckTable[n])(pItem))	// ������ Slot���� Ȯ��
	{
		// slot�� ������ �ȴ�.
		// n��° slot�� pItem�� �߰��Ѵ�.
		bool bAdd = MPlayerGear::AddItem( pItem, n );

		//-------------------------------------------------
		// ����� �߰��� ��� --> sound���
		//-------------------------------------------------
		if (bAdd)
		{
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

//----------------------------------------------------------------------
// Remove Item ( n)
//----------------------------------------------------------------------
MItem*			
MVampireGear::RemoveItem(GEAR_VAMPIRE n)
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
		n = GEAR_VAMPIRE_RIGHTHAND;
	}
	
	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if(n>=GEAR_VAMPIRE_RING1 && n<= GEAR_VAMPIRE_RING4) 
	{
		if(NULL != m_ItemSlot[n+m_Gilles_CoreZap]) // �ھ����� �پ� ������ �ھ����� ����
			n = (GEAR_VAMPIRE)(n + m_Gilles_CoreZap); // �ھ��� ��ġ
	}
//	else if(n >= GEAR_VAMPIRE_ZAP1 && n <= GEAR_VAMPIRE_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
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
	// ��� Item�� ��� ����� Slot�� ��� ��������� �Ѵ�.
	//-----------------------------------------------------
	if (pItem->IsGearSlotTwoHand())
	{
		m_ItemSlot[GEAR_VAMPIRE_LEFTHAND] = NULL;
		m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND] = NULL;
	}
	
	#ifdef __GAME_CLIENT__
		g_pPlayer->CalculateStatus();
	#endif

	// ������...
	return pItem;
}

//----------------------------------------------------------------------
// RemoveItem : id�� ���� item�� �����Ѵ�.
//----------------------------------------------------------------------
MItem*			
MVampireGear::RemoveItem(TYPE_OBJECTID id)
{ 
	MItem* pItem = MPlayerGear::RemoveItem( id ); 

	//-----------------------------------------------------
	// ���� ���
	//-----------------------------------------------------
	if (pItem==NULL)
	{
		return NULL;
	}

	//-----------------------------------------------------
	// ��� Item�� ��� ����� Slot�� ��� ��������� �Ѵ�.
	//-----------------------------------------------------
	if (pItem->IsGearSlotTwoHand())
	{
		m_ItemSlot[GEAR_VAMPIRE_LEFTHAND] = NULL;
		m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND] = NULL;
	}


	#ifdef __GAME_CLIENT__
		g_pPlayer->CalculateStatus();
	#endif

	// ������...
	return pItem;
}

//----------------------------------------------------------------------
// ReplaceItem : pItem�� �߰��ϰ� ���� �ִٸ� Item��ȯ
//----------------------------------------------------------------------
bool			
MVampireGear::ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsVampireItem())
	{
		return false;
	}

	//-------------------------------------------------
	//
	// �տ� �����ҷ��� ���
	//
	//-------------------------------------------------
	if (n==GEAR_VAMPIRE_LEFTHAND || n==GEAR_VAMPIRE_RIGHTHAND)	
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
			if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]==NULL
					&& m_ItemSlot[GEAR_VAMPIRE_LEFTHAND]==NULL)
			{
				// �׳� �߰��Ѵ�.
				pOldItem = NULL;
				if (MPlayerGear::AddItem( pItem, GEAR_VAMPIRE_RIGHTHAND ))
				{
					//-------------------------------------------------
					// item�� ������ ���� ����
					//-------------------------------------------------
					CheckItemStatus( pItem, GEAR_VAMPIRE_RIGHTHAND );

					pItem->SetItemSlot( GEAR_VAMPIRE_RIGHTHAND );
					m_ItemSlot[GEAR_VAMPIRE_LEFTHAND] = pItem;
					m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND] = pItem;

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
			if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]!=NULL 
				&& m_ItemSlot[GEAR_VAMPIRE_LEFTHAND]!=NULL)
			{
				//-------------------------------------------------
				// ��տ� �ִ°� ���ٸ�..
				//-------------------------------------------------
				if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]==m_ItemSlot[GEAR_VAMPIRE_LEFTHAND])
				{
					// ��� ����� ��ü�ϴ� ����̴�.
					if (MPlayerGear::ReplaceItem( pItem, 
													GEAR_VAMPIRE_RIGHTHAND, 
													pOldItem ))
					{
						//-------------------------------------------------
						// item�� ������ ���� ����
						//-------------------------------------------------
						CheckItemStatus( pItem, GEAR_VAMPIRE_RIGHTHAND );

						//pItem->SetItemSlot( GEAR_VAMPIRE_RIGHTHAND );
						m_ItemSlot[GEAR_VAMPIRE_LEFTHAND] = pItem;
						//m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND] = pItem;

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
			else if (m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND]!=NULL)
			{
				bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_VAMPIRE_RIGHTHAND, 
													pOldItem );
			}		

			//-------------------------------------------------
			// �޼տ� ���� �ִ� ���
			//-------------------------------------------------
			// �޼��� Item�� Replace�Ѵ�.
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_VAMPIRE_LEFTHAND]!=NULL)
			{
				bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_VAMPIRE_LEFTHAND, 
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
				CheckItemStatus( pItem, GEAR_VAMPIRE_RIGHTHAND );
				
				pItem->SetItemSlot( GEAR_VAMPIRE_RIGHTHAND );
				m_ItemSlot[GEAR_VAMPIRE_LEFTHAND] = pItem;
				m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND] = pItem;
		
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
													GEAR_VAMPIRE_RIGHTHAND, 
													pOldItem );

			//-------------------------------------------------
			// ��ȯ�Ǿ� ���� Item�� ����� ���
			//-------------------------------------------------
			if (pOldItem!=NULL)
			{
				if (pOldItem->IsGearSlotTwoHand())
				{
					// �޼��� ����д�.
					m_ItemSlot[GEAR_VAMPIRE_LEFTHAND] = NULL;
				}

			}

			if (bAdd)
			{
				//-------------------------------------------------
				// item�� ������ ���� ����
				//-------------------------------------------------
				CheckItemStatus( pItem, GEAR_VAMPIRE_RIGHTHAND );

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
													GEAR_VAMPIRE_LEFTHAND, 
													pOldItem );
			//-------------------------------------------------
			// ��ȯ�Ǿ� ���� Item�� ����� ���
			//-------------------------------------------------
			if (pOldItem!=NULL)
			{
				if (pOldItem->IsGearSlotTwoHand())
				{
					// �������� ����д�.
					m_ItemSlot[GEAR_VAMPIRE_RIGHTHAND] = NULL;
				}

			}

			if (bAdd)
			{
				//-------------------------------------------------
				// item ���� ����
				//-------------------------------------------------
				CheckItemStatus( pItem, GEAR_VAMPIRE_LEFTHAND );
				
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
	if (n >= GEAR_VAMPIRE_RING1 && n <= GEAR_VAMPIRE_RING4)	
	{
		if (pItem->IsGearSlotVampireRing())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]!=NULL) // �ھ����� ������ �� ����
				return false;
		}
		else
		if (pItem->IsGearSlotVampireCoreZap())
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
//	else if(n >= GEAR_VAMPIRE_ZAP1 && n <= GEAR_VAMPIRE_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
//		return false;
	
	//----------------------------------------------------
	// ������ Slot���� Ȯ���ؾ� �Ѵ�.
	//----------------------------------------------------	
	if (//m_ItemSlot[n]==NULL &&				// n��° slot�� ����ִ��� Ȯ��
		pItem->IsGearItem()	&&				// pItem�� GearItem���� Ȯ��..
		(*s_GearSlotCheckTable[n])(pItem))	// ������ Slot���� Ȯ��
	{
		// n��° slot�� pItem�� �߰��Ѵ�.
		if (MPlayerGear::ReplaceItem( pItem, n, pOldItem ))
		{
			//-------------------------------------------------
			// item ���� ����
			//-------------------------------------------------
			CheckItemStatus( pItem, n );			

			//-------------------------------------------------
			// ����� �߰��� ��� --> sound���
			//-------------------------------------------------
			#ifdef __GAME_CLIENT__
				PlaySound( pItem->GetGearSoundID() );
			#endif

			#ifdef __GAME_CLIENT__
				g_pPlayer->CalculateStatus();
			#endif

			return true;
		}

		return false;
	}

	return false;
}


MItem*	MVampireGear::GetGearItem_PickUp(int &n) const	
{
	int Slot = n;
//	if(Slot>=GEAR_VAMPIRE_BLOOD_BIBLE1 && Slot<=GEAR_VAMPIRE_BLOOD_BIBLE6) // ���� ���̺��� ������ ����.
//		return NULL;
	if(Slot>=GEAR_VAMPIRE_RING1 && Slot<=GEAR_VAMPIRE_RING4)
	{
		if(m_ItemSlot[Slot+m_Gilles_CoreZap]!=NULL)
		{
			n = n+m_Gilles_CoreZap;
			return MSlotItemManager::GetItem( (BYTE)(Slot+m_Gilles_CoreZap) ); 
		}
	}
	
	return MSlotItemManager::GetItem( (BYTE)Slot ); 
}



MItem*	MVampireGear::GetGearCoreZapItem(int slot) const	
{
	if(slot>=GEAR_VAMPIRE_RING1 && slot<=GEAR_VAMPIRE_RING4)
	{
		if(m_ItemSlot[slot+m_Gilles_CoreZap]!=NULL)
		{
			if(m_ItemSlot[slot+m_Gilles_CoreZap]->GetItemClass() == ITEM_CLASS_CORE_ZAP)
				return MSlotItemManager::GetItem( (BYTE)(slot+m_Gilles_CoreZap) ); 
		}
	}
	
	return NULL;
}


MItem*	MVampireGear::GetGearCoreZapedItem(int slot) const	
{
	if(slot>=GEAR_VAMPIRE_ZAP1 && slot<=GEAR_VAMPIRE_ZAP4)
	{
		if(slot-m_Gilles_CoreZap<0)
			return NULL;
		if(m_ItemSlot[slot-m_Gilles_CoreZap]!=NULL)
		{
			if(m_ItemSlot[slot-m_Gilles_CoreZap]->GetItemClass() == ITEM_CLASS_VAMPIRE_RING)
				return MSlotItemManager::GetItem( (BYTE)(slot-m_Gilles_CoreZap) ); 
		}
	}
	
	return NULL;
}

const bool	MVampireGear::IsHasAllCoreZap(int CoreZapType) const	
{
	BYTE bType[4] = {0,};
	if(CoreZapType == 0) // ���巹 �ھ� �� �� ���
	{
		MItem* pItem;
		for(int i = 0; i<4; i++)
		{
			pItem = m_ItemSlot[GEAR_VAMPIRE_ZAP1+i];
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

const bool	MVampireGear::IsCloseBloodBibleSlot(int slot) const	
{
	if(slot>=GEAR_VAMPIRE_BLOOD_BIBLE1 && slot<=GEAR_VAMPIRE_BLOOD_BIBLE6)
	{
		int TempSlot = slot - GEAR_VAMPIRE_BLOOD_BIBLE1 + 1;
		if(TempSlot > m_bBloodBibleOpenCount)
			return true;
	}
	return false;
}
