//////////////////////////////////////////////////////////////////////
//
// Filename    : GCRealWearingInfoHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
// include files
#include "GCRealWearingInfo.h"
#include "ClientDef.h"
#include "MSlayerGear.h"
#include "MVampireGear.h"
#include "MOustersGear.h"
#include "MSkillManager.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void GCRealWearingInfoHandler::execute ( GCRealWearingInfo * pPacket , Player * pPlayer )
	 throw ( ProtocolException, Error )
{
	__BEGIN_TRY
		
#ifdef __GAME_CLIENT__


	DWORD flag = pPacket->getInfo();

	if (g_pPlayer==NULL)
	{
		DEBUG_ADD("[Error] g_pPlayer is NULL");
	}
	else
	{

		//------------------------------------------------------------
		// Slayer
		//------------------------------------------------------------
		switch(g_pPlayer->GetRace())
		{
		case RACE_SLAYER:
		{
			bool bResetSkills = false;

			MItem *pWeapon = g_pSlayerGear->GetItem(MSlayerGear::GEAR_SLAYER_RIGHTHAND);
			
			if(pWeapon != NULL)
			{
				if(flag & 0x10)	// ���� ��ġ�� ����Ǵ� ���
				{
					if(pWeapon->IsAffectStatus() == false)
						bResetSkills = true;
				}
				else	// ���� ��ġ�� ������� �ʴ� ���
				{
					if(pWeapon->IsAffectStatus() == true)
						bResetSkills = true;
				}
			}

			int num = (int)MSlayerGear::MAX_GEAR_SLAYER;
			DWORD bit = 1;

			//-------------------------------------------------------
			// �� Slot�� ���ؼ� item�� ��ġ ���� ���θ� �Ǵ��Ѵ�.
			//-------------------------------------------------------
			for (int i=0; i<num; i++)
			{
				const MItem* pItem = g_pSlayerGear->GetItem( (MSlayerGear::GEAR_SLAYER)i );
				
				if (pItem!=NULL)
				{
					// 2004, 10, 26, sobeit add start
					if(pItem->GetItemClass() == ITEM_CLASS_BLOOD_BIBLE_SIGN)
						continue;
					// 2004, 10, 26, sobeit add end

					int itemID = pItem->GetID();

					MItem* pModifyItem = g_pSlayerGear->GetItemToModify( itemID );

					if (pModifyItem!=NULL)
					{
						//-------------------------------------------------------
						// ����� ��ġ�� ����Ǵ� ���
						//-------------------------------------------------------
						if (flag & bit)
						{
							pModifyItem->SetAffectStatus();
							g_pPlayer->SetAddonItem(pModifyItem);
						}
						//-------------------------------------------------------
						// ����� ��ġ�� ������� �ʴ� ���
						//-------------------------------------------------------
						else
						{
							pModifyItem->UnSetAffectStatus();
							g_pPlayer->RemoveAddonItem(pModifyItem);
						}
					}
				}

				bit <<= 1;
			}

			if(bResetSkills)
				g_pSkillAvailable->SetAvailableSkills();

		}
		break;

		case RACE_VAMPIRE:
		//------------------------------------------------------------
		// Vampire
		//------------------------------------------------------------
		{
			int num = (int)MVampireGear::MAX_GEAR_VAMPIRE;
			DWORD bit = 1;

			//-------------------------------------------------------
			// �� Slot�� ���ؼ� item�� ��ġ ���� ���θ� �Ǵ��Ѵ�.
			//-------------------------------------------------------
			for (int i=0; i<num; i++)
			{
				const MItem* pItem = g_pVampireGear->GetItem( (MVampireGear::GEAR_VAMPIRE)i );

				if (pItem!=NULL)
				{
					// 2004, 10, 26, sobeit add start
					if(pItem->GetItemClass() == ITEM_CLASS_BLOOD_BIBLE_SIGN)
						continue;
					// 2004, 10, 26, sobeit add end
					int itemID = pItem->GetID();

					MItem* pModifyItem = g_pVampireGear->GetItemToModify( itemID );

					if (pModifyItem!=NULL)
					{
						//-------------------------------------------------------
						// ����� ��ġ�� ����Ǵ� ���
						//-------------------------------------------------------
						if (flag & bit)
						{
							pModifyItem->SetAffectStatus();
						}
						//-------------------------------------------------------
						// ����� ��ġ�� ������� �ʴ� ���
						//-------------------------------------------------------
						else
						{
							pModifyItem->UnSetAffectStatus();
						}
					}
				}

				bit <<= 1;
			}
		}
		break;

		case RACE_OUSTERS:
			{
				int num = (int)MOustersGear::MAX_GEAR_OUSTERS;
				DWORD bit = 1;
				
				//-------------------------------------------------------
				// �� Slot�� ���ؼ� item�� ��ġ ���� ���θ� �Ǵ��Ѵ�.
				//-------------------------------------------------------
				for (int i=0; i<num; i++)
				{
					const MItem* pItem = g_pOustersGear->GetItem( (MOustersGear::GEAR_OUSTERS)i );
					
					if (pItem!=NULL)
					{
						// 2004, 10, 26, sobeit add start
						if(pItem->GetItemClass() == ITEM_CLASS_BLOOD_BIBLE_SIGN)
							continue;
						// 2004, 10, 26, sobeit add end
						int itemID = pItem->GetID();
						
						MItem* pModifyItem = g_pOustersGear->GetItemToModify( itemID );
						
						if (pModifyItem!=NULL)
						{
							//-------------------------------------------------------
							// ����� ��ġ�� ����Ǵ� ���
							//-------------------------------------------------------
							if (flag & bit)
							{
								pModifyItem->SetAffectStatus();
							}
							//-------------------------------------------------------
							// ����� ��ġ�� ������� �ʴ� ���
							//-------------------------------------------------------
							else
							{
								pModifyItem->UnSetAffectStatus();
							}
						}
					}
					
					bit <<= 1;
				}
			}
			break;
		}
	}
	
	g_pPlayer->CalculateStatus();

#endif

	__END_CATCH
}
