//----------------------------------------------------------------------
// MOustersGear.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MItem.h"
#include "MOustersGear.h"
#include "MQuickSlot.h"

#ifdef __GAME_CLIENT__
	#include "UIFunction.h"
	#include "ClientFunction.h"
	#include "MPlayer.h"
#endif
#include "MTimeItemManager.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MOustersGear*		g_pOustersGear = NULL;

//----------------------------------------------------------------------
// static
//----------------------------------------------------------------------
MOustersGear::FUNCTION_GEARSLOT_CHECK
MOustersGear::s_GearSlotCheckTable[MAX_GEAR_OUSTERS] =
{
	IsGearSlotCirclet,			// ��Ŭ��
	IsGearSlotCoat,				// ��
	IsGearSlotLeftHand,			// �޼�
	IsGearSlotRightHand,			// ������
	IsGearSlotBoots,				// �Ź�
	IsGearSlotArmsBand,			// �Ͻ����1
	IsGearSlotArmsBand,			// �Ͻ����2
	IsGearSlotRing,				// ��1
	IsGearSlotRing,				// ��2
	IsGearSlotPendent,			// �����1
	IsGearSlotPendent,			// �����2
	IsGearSlotPendent,			// �����3
	IsGearSlotStone,			// ���ɼ�1
	IsGearSlotStone,			// ���ɼ�2
	IsGearSlotStone,			// ���ɼ�3
	IsGearSlotStone,			// ���ɼ�4
	IsGearSlotCoreZap,			// �ھ���1
	IsGearSlotCoreZap,			// �ھ���2
	IsGearSlotCoreZap,			// �ھ���3
	IsGearSlotCoreZap,			// �ھ���4
	IsGearSlotFascia,			// �㸮���
	IsGearSlotMitten,			// �尩
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
bool		MOustersGear::IsGearSlotCirclet(MItem* pItem)		{ return pItem->IsGearSlotOustersCirclet(); }
bool		MOustersGear::IsGearSlotCoat(MItem* pItem)			{ return pItem->IsGearSlotOustersCoat(); }
bool		MOustersGear::IsGearSlotLeftHand(MItem* pItem)		{ return pItem->IsGearSlotOustersLeftHand(); }
bool		MOustersGear::IsGearSlotRightHand(MItem* pItem)		{ return pItem->IsGearSlotOustersRightHand(); }
bool		MOustersGear::IsGearSlotBoots(MItem* pItem)			{ return pItem->IsGearSlotOustersBoots(); }
bool		MOustersGear::IsGearSlotArmsBand(MItem* pItem)		{ return pItem->IsGearSlotOustersArmsBand(); }
bool		MOustersGear::IsGearSlotRing(MItem* pItem)			{ return pItem->IsGearSlotOustersRing(); }
bool		MOustersGear::IsGearSlotPendent(MItem* pItem)		{ return pItem->IsGearSlotOustersPendent(); }
bool		MOustersGear::IsGearSlotStone(MItem* pItem)			{ return pItem->IsGearSlotOustersStone(); }
bool		MOustersGear::IsGearSlotCoreZap(MItem* pItem)		{ return pItem->IsGearSlotOustersCoreZap(); }	// �ھ���
bool		MOustersGear::IsGearSlotFascia(MItem* pItem)		{ return pItem->IsGearSlotOustersFascia(); }	// �ھ���
bool		MOustersGear::IsGearSlotMitten(MItem* pItem)		{ return pItem->IsGearSlotOustersMitten(); }	// �ھ���
bool		MOustersGear::IsGearSlotBloodBible(MItem* pItem)	{ return pItem->IsGearSlotOustersBloodBible(); }	// ���� ���̺�

//----------------------------------------------------------------------
//
// constructor
// 
//----------------------------------------------------------------------
MOustersGear::MOustersGear()
{
	g_pArmsBand1 = NULL;
	g_pArmsBand2 = NULL;
	m_bBloodBibleOpenCount = 0;
}

MOustersGear::~MOustersGear()
{
	g_pArmsBand1 = NULL;
	g_pArmsBand2 = NULL;
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Init 
//----------------------------------------------------------------------
// MAX_GEAR_OUSTERS��ŭ�� Slot�� �����Ѵ�.
//----------------------------------------------------------------------
void
MOustersGear::Init()
{
	// slot ����
	MPlayerGear::Init(MAX_GEAR_OUSTERS);
	m_Gilles_CoreZap = 4;
	m_bBloodBibleOpenCount = 0;
}

//----------------------------------------------------------------------
// Check AffectStatus
//----------------------------------------------------------------------
// Ư�� �������� ���� ���� ���θ� üũ�Ѵ�.
//----------------------------------------------------------------------
void			
MOustersGear::CheckAffectStatus(MItem* pItem)
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
MOustersGear::AddItem(MItem* pItem)
{
	for (int i=0; i<MAX_GEAR_OUSTERS; i++)
	{
		// �߰�������..
		if (AddItem( pItem, (enum GEAR_OUSTERS)i ))
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
MOustersGear::CanReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{	
	// ��ġ ������� �ʴ� �������� ������� �ʴ´�
	if(pItem->IsAffectStatus() == false&& !pItem->IsQuestItem())
		return false;

	pOldItem = NULL;

	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsOustersItem())
	{
		return false;
	}
	if(n>=GEAR_OUSTERS_BLOOD_BIBLE1 && n<=GEAR_OUSTERS_BLOOD_BIBLE6) // ���� ���̺��� ������ ����.
		return false;

	
		
	// bycsm 2004.12.31

		if(n == GEAR_OUSTERS_FASCIA)
	{
		if(pItem->IsGearSlotOustersFascia() == true)
		{
			if (m_ItemSlot[GEAR_OUSTERS_FASCIA]==NULL)
				return true;
			else
			{
				pOldItem = m_ItemSlot[GEAR_OUSTERS_FASCIA];
				return true;
			}
		}

	}

	if(n == GEAR_OUSTERS_MITTEN)
	{
		if(pItem->IsGearSlotOustersMitten()== true)
		{
			
			if (m_ItemSlot[GEAR_OUSTERS_MITTEN]==NULL)
				return true;
			else
			{
				pOldItem = m_ItemSlot[GEAR_OUSTERS_MITTEN];
				return true;
			}
		}
		
	}


	
	//-------------------------------------------------
	//
	// �տ� �����ҷ��� ���
	//
	//-------------------------------------------------
	if (n==GEAR_OUSTERS_LEFTHAND || n==GEAR_OUSTERS_RIGHTHAND)	
	{
		//-------------------------------------------------
		// [ ��� Item ] �� ���
		//-------------------------------------------------
		if (pItem->IsGearSlotTwoHand())
		{			
			//-------------------------------------------------
			// ����� Slot�� ��� ����ִ� ��� 
			//-------------------------------------------------			
			if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]==NULL
					&& m_ItemSlot[GEAR_OUSTERS_LEFTHAND]==NULL)
			{
				return true;
			}
			
			//-------------------------------------------------
			// ��տ� �� ���� �ִ� ���
			//-------------------------------------------------
			if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]!=NULL 
				&& m_ItemSlot[GEAR_OUSTERS_LEFTHAND]!=NULL)
			{
				//-------------------------------------------------
				// ��տ� �ִ°� ���ٸ�..
				//-------------------------------------------------
				if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]==m_ItemSlot[GEAR_OUSTERS_LEFTHAND])
				{
					pOldItem = m_ItemSlot[GEAR_OUSTERS_RIGHTHAND];
					return true;
				}
				
				return false;				
			}

			//-------------------------------------------------
			// �����տ��� ���� �ִ� ���
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]!=NULL)
			{
				pOldItem = m_ItemSlot[GEAR_OUSTERS_RIGHTHAND];
				return true;
			}

			//-------------------------------------------------
			// �޼տ������� �ִ� ���
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_OUSTERS_LEFTHAND]!=NULL)
			{			
				pOldItem = m_ItemSlot[GEAR_OUSTERS_LEFTHAND];
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
			pOldItem = m_ItemSlot[GEAR_OUSTERS_RIGHTHAND];
			return true;
		}
		
		//-------------------------------------------------				
		// [ �޼� Item ] �� ���
		//-------------------------------------------------
		else if (pItem->IsGearSlotLeftHand())
		{
			pOldItem = m_ItemSlot[GEAR_OUSTERS_LEFTHAND];
			return true;
		}

		// �տ� �����ϴ°� �ƴ� ���
		return false;
	}

	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if (n >= GEAR_OUSTERS_STONE1 && n <= GEAR_OUSTERS_STONE4)	
	{
		if (pItem->IsGearSlotOustersStone())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]==NULL) // �ھ����� ����� ���ɼ��� ���� �� ����
			{
				pOldItem = m_ItemSlot[n];
				return true;
			}
		}
		else
		if (pItem->IsGearSlotOustersCoreZap())
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
	else if(n >= GEAR_OUSTERS_ZAP1 && n <= GEAR_OUSTERS_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
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
MOustersGear::AddItem(MItem* pItem, GEAR_OUSTERS n)
{	
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	
	if (n>=m_Size || !pItem->IsOustersItem())
	{
		return false;
	}

	//-------------------------------------------------
	// ��� Item�� ���� ���� üũ���ش�.
	//-------------------------------------------------
	if ((n==GEAR_OUSTERS_LEFTHAND || n==GEAR_OUSTERS_RIGHTHAND) &&
		pItem->IsGearSlotTwoHand())
	{
		// ����� Slot�� ��� ����ִ� ���¿��� �߰� �����ϴ�.
		if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]==NULL
				&& m_ItemSlot[GEAR_OUSTERS_LEFTHAND]==NULL)
		{
			// �����տ� �߰��Ѵ�.			
			if (MPlayerGear::AddItem( pItem, GEAR_OUSTERS_RIGHTHAND ))
			{
				// �޼տ��� �߰����ش�.
				m_ItemSlot[GEAR_OUSTERS_LEFTHAND] = pItem;

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
	if (n >= GEAR_OUSTERS_STONE1 && n <= GEAR_OUSTERS_STONE4)	
	{
		if (pItem->IsGearSlotOustersStone())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]==NULL&&m_ItemSlot[n]==NULL) // ���ɼ��� ���� �ھ����� ����� ���� ���� �� ����
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
		if (pItem->IsGearSlotOustersCoreZap())
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
//	else if(n >= GEAR_OUSTERS_ZAP1 && n <= GEAR_OUSTERS_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
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

		//-------------------------------------------------
		// ����� �߰��� ��� --> sound���
		//-------------------------------------------------
		if (bAdd)
		{
			#ifdef __GAME_CLIENT__		
				PlaySound( pItem->GetGearSoundID() );
				g_pPlayer->CalculateStatus();
			#endif

			if( n == GEAR_OUSTERS_ARMSBAND1	)
			{
				g_pArmsBand1 = (MOustersArmsBand*)pItem;
				#ifdef __GAME_CLIENT__		
				UI_ResetQuickItemSlot();
				#endif
			}
			else if ( n == GEAR_OUSTERS_ARMSBAND2 )
			{
				g_pArmsBand2 = (MOustersArmsBand*)pItem;
				#ifdef __GAME_CLIENT__		
				UI_ResetQuickItemSlot();
				#endif
			}
			
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
MOustersGear::RemoveItem(GEAR_OUSTERS n)
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
		n = GEAR_OUSTERS_RIGHTHAND;
	}
	/***********************************************************	
				�ھ��� ���� ó��
	***********************************************************/
	if(n>=GEAR_OUSTERS_STONE1 && n<= GEAR_OUSTERS_STONE4) 
	{
		if(NULL != m_ItemSlot[n+m_Gilles_CoreZap]) // �ھ����� �پ� ������ �ھ����� ����
			n = (GEAR_OUSTERS)(n + m_Gilles_CoreZap); // �ھ��� ��ġ
	}
//	else if(n >= GEAR_OUSTERS_ZAP1 && n <= GEAR_OUSTERS_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
//		return false;

	pItem = MPlayerGear::RemoveItem( (BYTE)n );

	//-----------------------------------------------------
	// ���� ���
	//-----------------------------------------------------
	if (pItem==NULL)
	{
		return NULL;
	}

	if( n == GEAR_OUSTERS_ARMSBAND1 || n == GEAR_OUSTERS_ARMSBAND2 )
	{
		if( n == GEAR_OUSTERS_ARMSBAND1 )
			g_pArmsBand1 = NULL;
		else
			g_pArmsBand2 = NULL;
		
	}

	//-----------------------------------------------------
	// ��� Item�� ��� ����� Slot�� ��� ��������� �Ѵ�.
	//-----------------------------------------------------
	if (pItem->IsGearSlotTwoHand())
	{
		m_ItemSlot[GEAR_OUSTERS_LEFTHAND] = NULL;
		m_ItemSlot[GEAR_OUSTERS_RIGHTHAND] = NULL;
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
MOustersGear::RemoveItem(TYPE_OBJECTID id)
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
		m_ItemSlot[GEAR_OUSTERS_LEFTHAND] = NULL;
		m_ItemSlot[GEAR_OUSTERS_RIGHTHAND] = NULL;
	}
	if( pItem->GetItemClass() == ITEM_CLASS_OUSTERS_ARMSBAND )
	{
		if( pItem->GetItemSlot()== GEAR_OUSTERS_ARMSBAND1 )
			g_pArmsBand1 = NULL;
		else
			g_pArmsBand2 = NULL;		
	}


	#ifdef __GAME_CLIENT__
		g_pPlayer->CalculateStatus();
	#endif

	// ��~����...
	return pItem;
}

//----------------------------------------------------------------------
// ReplaceItem : pItem�� �߰��ϰ� ���� �ִٸ� Item��ȯ
//----------------------------------------------------------------------
bool			
MOustersGear::ReplaceItem(MItem* pItem, BYTE n, MItem*& pOldItem)
{
	//---------------------------------------------------------
	// ItemSlot ������ �Ѿ�� ���..
	//---------------------------------------------------------	

	if (n>=m_Size || !pItem->IsOustersItem())
	{
		return false;
	}


	if(n == GEAR_OUSTERS_FASCIA)
	{
		if(pItem->IsGearSlotOustersFascia() == true)
		{
			if (m_ItemSlot[GEAR_OUSTERS_FASCIA]==NULL)
			{
				MPlayerGear::ReplaceItem( pItem, GEAR_OUSTERS_FASCIA, pOldItem );
				return true;
			}
			else
				return false;
		}
	}
	
	if(n == GEAR_OUSTERS_MITTEN)
	{
		if(pItem->IsGearSlotOustersMitten() == true)
		{
			if (m_ItemSlot[GEAR_OUSTERS_MITTEN]==NULL)
			{
				MPlayerGear::ReplaceItem( pItem, GEAR_OUSTERS_MITTEN, pOldItem );
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
	if (n==GEAR_OUSTERS_LEFTHAND || n==GEAR_OUSTERS_RIGHTHAND)	
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
			if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]==NULL
					&& m_ItemSlot[GEAR_OUSTERS_LEFTHAND]==NULL)
			{
				// �׳� �߰��Ѵ�.
				pOldItem = NULL;
				if (MPlayerGear::AddItem( pItem, GEAR_OUSTERS_RIGHTHAND ))
				{
					//-------------------------------------------------
					// item�� ������ ���� ����
					//-------------------------------------------------
					CheckItemStatus( pItem, GEAR_OUSTERS_RIGHTHAND );

					pItem->SetItemSlot( GEAR_OUSTERS_RIGHTHAND );
					m_ItemSlot[GEAR_OUSTERS_LEFTHAND] = pItem;
					m_ItemSlot[GEAR_OUSTERS_RIGHTHAND] = pItem;

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
			if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]!=NULL 
				&& m_ItemSlot[GEAR_OUSTERS_LEFTHAND]!=NULL)
			{
				//-------------------------------------------------
				// ��տ� �ִ°� ���ٸ�..
				//-------------------------------------------------
				if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]==m_ItemSlot[GEAR_OUSTERS_LEFTHAND])
				{
					// ��� ����� ��ü�ϴ� ����̴�.
					if (MPlayerGear::ReplaceItem( pItem, 
													GEAR_OUSTERS_RIGHTHAND, 
													pOldItem ))
					{
						//-------------------------------------------------
						// item�� ������ ���� ����
						//-------------------------------------------------
						CheckItemStatus( pItem, GEAR_OUSTERS_RIGHTHAND );

						//pItem->SetItemSlot( GEAR_OUSTERS_RIGHTHAND );
						m_ItemSlot[GEAR_OUSTERS_LEFTHAND] = pItem;
						//m_ItemSlot[GEAR_OUSTERS_RIGHTHAND] = pItem;

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
			else if (m_ItemSlot[GEAR_OUSTERS_RIGHTHAND]!=NULL)
			{
				bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_OUSTERS_RIGHTHAND, 
													pOldItem );
			}		

			//-------------------------------------------------
			// �޼տ� ���� �ִ� ���
			//-------------------------------------------------
			// �޼��� Item�� Replace�Ѵ�.
			//-------------------------------------------------
			else if (m_ItemSlot[GEAR_OUSTERS_LEFTHAND]!=NULL)
			{
				bAdd = MPlayerGear::ReplaceItem( pItem, 
													GEAR_OUSTERS_LEFTHAND, 
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
				CheckItemStatus( pItem, GEAR_OUSTERS_RIGHTHAND );
				
				pItem->SetItemSlot( GEAR_OUSTERS_RIGHTHAND );
				m_ItemSlot[GEAR_OUSTERS_LEFTHAND] = pItem;
				m_ItemSlot[GEAR_OUSTERS_RIGHTHAND] = pItem;
		
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
													GEAR_OUSTERS_RIGHTHAND, 
													pOldItem );

			//-------------------------------------------------
			// ��ȯ�Ǿ� ���� Item�� ����� ���
			//-------------------------------------------------
			if (pOldItem!=NULL)
			{
				if (pOldItem->IsGearSlotTwoHand())
				{
					// �޼��� ����д�.
					m_ItemSlot[GEAR_OUSTERS_LEFTHAND] = NULL;
				}

			}

			if (bAdd)
			{
				//-------------------------------------------------
				// item�� ������ ���� ����
				//-------------------------------------------------
				CheckItemStatus( pItem, GEAR_OUSTERS_RIGHTHAND );

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
													GEAR_OUSTERS_LEFTHAND, 
													pOldItem );
			//-------------------------------------------------
			// ��ȯ�Ǿ� ���� Item�� ����� ���
			//-------------------------------------------------
			if (pOldItem!=NULL)
			{
				if (pOldItem->IsGearSlotTwoHand())
				{
					// �������� ����д�.
					m_ItemSlot[GEAR_OUSTERS_RIGHTHAND] = NULL;
				}

			}

			if (bAdd)
			{
				//-------------------------------------------------
				// item ���� ����
				//-------------------------------------------------
				CheckItemStatus( pItem, GEAR_OUSTERS_LEFTHAND );
				
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
	if (n >= GEAR_OUSTERS_STONE1 && n <= GEAR_OUSTERS_STONE4)	
	{
		if (pItem->IsGearSlotOustersStone())
		{			
			if (m_ItemSlot[n+m_Gilles_CoreZap]!=NULL) // �ھ����� ������ �� ����
				return false;
		}
		else
		if (pItem->IsGearSlotOustersCoreZap())
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
	//	return false;
	}
//	else if(n >= GEAR_OUSTERS_ZAP1 && n <= GEAR_OUSTERS_ZAP4) // �ھ��� ������ ������ �ʴ´�. -_-?? 
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

			if( n == GEAR_OUSTERS_ARMSBAND1	)
			{
				g_pArmsBand1 = (MOustersArmsBand*)pItem;
				#ifdef __GAME_CLIENT__		
				UI_ResetQuickItemSlot();
				#endif
			}
			else if ( n == GEAR_OUSTERS_ARMSBAND2 )
			{
				g_pArmsBand2 = (MOustersArmsBand*)pItem;
				#ifdef __GAME_CLIENT__		
				UI_ResetQuickItemSlot();
				#endif
			}
			return true;
		}

		return false;
	}

	return false;
}

MItem*	MOustersGear::GetGearItem_PickUp(int &n) const	
{
	int Slot = n;
//	if(Slot>=GEAR_OUSTERS_BLOOD_BIBLE1 && Slot<=GEAR_OUSTERS_BLOOD_BIBLE6) // ���� ���̺��� ������ ����.
//		return NULL;
	if(Slot>=GEAR_OUSTERS_STONE1 && Slot<=GEAR_OUSTERS_STONE4)
	{
		if(m_ItemSlot[Slot+m_Gilles_CoreZap]!=NULL)
		{
			n = n+m_Gilles_CoreZap;
			return MSlotItemManager::GetItem( (BYTE)(Slot+m_Gilles_CoreZap) ); 
		}
	}
	
	return MSlotItemManager::GetItem( (BYTE)Slot ); 
}


MItem*	MOustersGear::GetGearCoreZapItem(int slot) const	
{
	if(slot>=GEAR_OUSTERS_STONE1 && slot<=GEAR_OUSTERS_STONE4)
	{
		if(m_ItemSlot[slot+m_Gilles_CoreZap]!=NULL)
		{
			if(m_ItemSlot[slot+m_Gilles_CoreZap]->GetItemClass() == ITEM_CLASS_CORE_ZAP)
				return MSlotItemManager::GetItem( (BYTE)(slot+m_Gilles_CoreZap) ); 
		}
	}
	
	return NULL;
}


MItem*	MOustersGear::GetGearCoreZapedItem(int slot) const	
{
	if(slot>=GEAR_OUSTERS_ZAP1 && slot<=GEAR_OUSTERS_ZAP4)
	{
		if(slot-m_Gilles_CoreZap<0)
			return NULL;
		if(m_ItemSlot[slot-m_Gilles_CoreZap]!=NULL)
		{
			if(m_ItemSlot[slot-m_Gilles_CoreZap]->GetItemClass() == ITEM_CLASS_OUSTERS_STONE)
				return MSlotItemManager::GetItem( (BYTE)(slot-m_Gilles_CoreZap) ); 
		}
	}
	
	return NULL;
}

const bool	MOustersGear::IsHasAllCoreZap(int CoreZapType) const	
{
	BYTE bType[4] = {0,};
	if(CoreZapType == 0) // ���巹 �ھ� �� �� ���
	{
		MItem* pItem;
		for(int i = 0; i<4; i++)
		{
			pItem = m_ItemSlot[GEAR_OUSTERS_ZAP1+i];
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

const bool	MOustersGear::IsCloseBloodBibleSlot(int slot) const	
{
	if(slot>=GEAR_OUSTERS_BLOOD_BIBLE1 && slot<=GEAR_OUSTERS_BLOOD_BIBLE6)
	{
		int TempSlot = slot - GEAR_OUSTERS_BLOOD_BIBLE1 + 1;
		if(TempSlot > m_bBloodBibleOpenCount)
			return true;
	}
	return false;
}
