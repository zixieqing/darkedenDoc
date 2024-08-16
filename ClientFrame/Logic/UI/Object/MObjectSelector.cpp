//----------------------------------------------------------------------
// MObjectSelector.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MObjectSelector.h"
#include "MPlayer.h"
#include "MJusticeAttackManager.h"
#include "CDirectInput.h"
#include "MEventManager.h"
#include "MWarManager.h"
#include "MZone.h"
#include "GuildWarInfo.h"
#include "RaceWarInfo.h"
#include "MZoneTable.h"
#include "MGuildType.h"
#include "UserInformation.h"
//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MObjectSelector* g_pObjectSelector = NULL;

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MObjectSelector::MObjectSelector()
{
	m_SelectTarget	= SELECT_ALL;
	m_SelectBy		= SELECT_BY_RACE;
}

MObjectSelector::~MObjectSelector()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Can Select (MCreature*)
//----------------------------------------------------------------------
BOOL
MObjectSelector::CanSelect(MCreature* pCreature)
{
	// ���������̸� �ƹ��� ���� ����..
	// SelectAll�̸� �ƹ��� ���ð����ϴ�.
	// �ҷ�~�ɷ�����..	
	// SelectByRace�̸� SelectEnemy�̸� (������ ����) ������ ĳ���͸� �����Ѵ�.
	//                  SelectFriend�̸� (������ ����) �������� ���� ĳ���͸� �����Ѵ�.	
	// SelectByGuild�̸�  SelectEnemy�̸� (��忡 ����) ������ ĳ���͸� �����Ѵ�.
	//                    SelectFriend�̸� (��忡 ����) �������� ���� ĳ���͸� �����Ѵ�.
	// ��������� �����Ǵ� ���
	// �������϶� ��� ����ΰ��
	
	WORD CurZoneID = g_pZone->GetID();
	// 2004, 9, 15, sobeit add start
	bool	IsAvailablePK = true;
//	if( g_pUserInformation->IsNonPK && NULL != pCreature )
//	{
//		int spriteType = (*g_pCreatureTable)[pCreature->GetCreatureType()].SpriteType;
//		if((*g_pCreatureSpriteTable)[spriteType].IsPlayerOnlySprite() && !pCreature->IsNPC())
//		{
//			if( g_pPlayer->GetCreatureTribe() != pCreature->GetCreatureTribe() || g_pDXInput->KeyDown(DIK_LSHIFT))
//				IsAvailablePK = false;
//		}
//	}
	// 2004, 9, 15, sobeit add end
	return	(g_pDXInput->KeyDown(DIK_LSHIFT)

			|| g_pPlayer->HasEffectStatus(EFFECTSTATUS_HALLUCINATION)

			|| m_SelectTarget==SELECT_ALL

			|| (m_SelectBy==SELECT_BY_RACE 
					&& (m_SelectTarget==SELECT_ENEMY && g_pPlayer->CanAttackTribe( pCreature )
						|| m_SelectTarget==SELECT_FRIEND && !g_pPlayer->CanAttackTribe( pCreature )
						)
				)

			|| (m_SelectBy==SELECT_BY_GUILD
					&& (m_SelectTarget==SELECT_ENEMY && g_pPlayer->CanAttackGuild( pCreature )
						|| m_SelectTarget==SELECT_FRIEND && !g_pPlayer->CanAttackGuild( pCreature )
						)
				)

			|| g_pJusticeAttackManager->HasCreature( pCreature->GetName() )

			|| pCreature->IsNPC()
			|| IsWarEnemy( pCreature )
		//	|| g_pZone->GetPKType() == PK_TYPE_ALL
			|| (g_pPlayer->GetCreatureType() == CREATURETYPE_SLAYER_OPERATOR || g_pPlayer->GetCreatureType() == CREATURETYPE_VAMPIRE_OPERATOR || g_pPlayer->GetCreatureType() == CREATURETYPE_OUSTERS_OPERATOR )
			)
			&& IsAvailablePK
			
			;

}

//----------------------------------------------------------------------
// Can Attack (MCreature*)
//----------------------------------------------------------------------
// �����̳�, ��忡 ����.. ������ ����ΰ�?
//----------------------------------------------------------------------
BOOL	
MObjectSelector::CanAttack(MCreature* pCreature)
{
	// ���� �����̰ų�..
	// �ҷ�~�ɷ�����..
	// SelectByRace�̸�	CanAttackTribe�� üũ
	// SelectByGuild�̸� CanAttackGuild�� üũ
	// ��������� �����Ǵ� ���
	// NPC�� ������ ���� �����ϴ�.
	WORD CurZoneID = g_pZone->GetID();

//	bool bFreePKZone = g_pZoneTable->Get( g_pZone->GetID() )->FreePK;
	// 2004, 9, 15, sobeit add start

	bool	IsAvailablePK = true;

	if(NULL == pCreature)return FALSE;
	if( g_pUserInformation->IsNonPK && NULL != pCreature )
	{
		int spriteType = (*g_pCreatureTable)[pCreature->GetCreatureType()].SpriteTypes[0];
		if((*g_pCreatureSpriteTable)[spriteType].IsPlayerOnlySprite()&& !pCreature->IsNPC())
			IsAvailablePK = false;
	}
	// 2004, 9, 15, sobeit add end
	
	return (
				g_pDXInput->KeyDown(DIK_LSHIFT)
				|| g_pPlayer->HasEffectStatus(EFFECTSTATUS_HALLUCINATION)
				|| m_SelectBy==SELECT_BY_RACE 
						&& g_pPlayer->CanAttackTribe(pCreature)
				|| m_SelectBy==SELECT_BY_GUILD
						&& g_pPlayer->CanAttackGuild(pCreature)
				|| g_pJusticeAttackManager->HasCreature( pCreature->GetName() )
				|| IsWarEnemy( pCreature )
			)

			&& IsAvailablePK;
		//|| g_pZone->GetPKType() == PK_TYPE_ALL;
	
}
//BOOL	
//MObjectSelector::IsAblePKbyZone(MCreature* pCreature)
//{
//	if(pCreature == NULL || g_pZone == NULL)
//		return FALSE;
//	DWORD CreatureType = pCreature->GetCreatureType();
//	if(CreatureType <4 || CreatureType == 651) // ���� ����, ���� ����, �ƿ콺���� �϶���
//	{
//		BYTE PkType = g_pZone->GetPKType();
//		if(PkType != PK_TYPE_NULL)	// �׳� �Ϲ� ��
//		{
//			if(PkType == PK_TYPE_DISABLE)		// �� �츮��..-_-; pk ����
//				return FALSE;
//			else if(PkType == PK_TYPE_ALL)		// �� ���� �� ��
//				return TRUE;
//			else if(PkType == PK_TYPE_GUILD)	// �츮 ��� ���� �� ��..
//			{
//				int myGuildID = g_pPlayer->GetGuildNumber();	
//				int OtherGuildID = pCreature->GetGuildNumber();	
//				if( myGuildID		== GUILDID_VAMPIRE_DEFAULT ||
//					myGuildID		== GUILDID_SLAYER_DEFAULT ||
//					myGuildID		== GUILDID_OUSTERS_DEFAULT ||
//					OtherGuildID	== GUILDID_VAMPIRE_DEFAULT ||
//					OtherGuildID	== GUILDID_SLAYER_DEFAULT ||
//					OtherGuildID	== GUILDID_OUSTERS_DEFAULT ) // ��尡 ���� �༮ ����..
//					return TRUE; // ȥ�� �ο���..-_-;
//
//				if(myGuildID == OtherGuildID)
//					return FALSE; // �츮 ���...
//				else
//					return TRUE;
//			}
//		}
//
//	}
//	return TRUE;
//}
//--------------------------------------------------------------
// IsWarEnemy - ���￡ ���õ� ���ΰ�?
//--------------------------------------------------------------
BOOL	
MObjectSelector::IsWarEnemy(MCreature* pCreature)
{
	BOOL bWarSelect = FALSE;

	if(pCreature == NULL || g_pZone == NULL)
		return bWarSelect;

	// ���� ���� ���� ���ΰ�? �������� ���� ������ �ƴ��� ��������... ���������� �ٲپ�� �Ѵ�.
	WORD CurrentZoneID = g_pZone->GetID();
	if(g_pZone!=NULL && pCreature != NULL)
	{
		if(g_pZone->GetPKType() == PK_TYPE_ALL)
			return TRUE;
		else if(g_pZone->GetPKType() == PK_TYPE_SIEGE)
		{
			// 2004, 11, 8, sobeit add start - pCreature�� ���Ἲ Ȯ��
			if(pCreature->GetObjectType() != MObject::TYPE_CREATURE || !pCreature->IsAvailableEffectStatus())
				return FALSE;
			// 2004, 11, 8, sobeit add end

			// ������ ���� �϶�
			if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_DEFENDERL)||g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_REINFORCE))
			{
				if(!pCreature->HasEffectStatus(EFFECTSTATUS_SIEGE_DEFENDERL)&&!pCreature->HasEffectStatus(EFFECTSTATUS_SIEGE_REINFORCE))
					return TRUE;
			}
			if(g_pPlayer->GetUnionGuildID() > 0 && (g_pPlayer->GetUnionGuildID() == pCreature->GetUnionGuildID()))
			{
				return FALSE;
			}
			if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_1) && !pCreature->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_1))
				return TRUE;
			else if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_2) && !pCreature->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_2))
				return TRUE;
			else if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_3) && !pCreature->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_3))
				return TRUE;
			else if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_4) && !pCreature->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_4))
				return TRUE;
			else if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_5) && !pCreature->HasEffectStatus(EFFECTSTATUS_SIEGE_ATTACKER_5))
				return TRUE;
		}
	}
//	// 2004, 5, 14 sobeit add start
//	DWORD CreatureType = pCreature->GetCreatureType();
//	if(CreatureType <4 || CreatureType == 651) // ���� ����, ���� ����, �ƿ콺���� �϶���
//	{
//		BYTE PkType = g_pZone->GetPKType();
//		if(PkType != PK_TYPE_NULL)	// �׳� �Ϲ� ��
//		{
//			if(PkType == PK_TYPE_DISABLE)		// �� �츮��..-_-; pk ����
//				return FALSE;
//			else if(PkType == PK_TYPE_ALL)		// �� ���� �� ��
//				return TRUE;
//			else if(PkType == PK_TYPE_GUILD)	// �츮 ��� ���� �� ��..
//			{
//				int myGuildID = g_pPlayer->GetGuildNumber();	
//				int OtherGuildID = pCreature->GetGuildNumber();	
//				if( myGuildID		== GUILDID_VAMPIRE_DEFAULT ||
//					myGuildID		== GUILDID_SLAYER_DEFAULT ||
//					myGuildID		== GUILDID_OUSTERS_DEFAULT ||
//					OtherGuildID	== GUILDID_VAMPIRE_DEFAULT ||
//					OtherGuildID	== GUILDID_SLAYER_DEFAULT ||
//					OtherGuildID	== GUILDID_OUSTERS_DEFAULT ) // ��尡 ���� �༮ ����..
//					return TRUE; // ȥ�� �ο���..-_-;
//
//				if(myGuildID == OtherGuildID)
//					return FALSE; // �츮 ���...
//				else
//					return TRUE;
//			}
//		}
//	}
//	// 2004, 5, 14 sobeit add end

	if( g_pWarManager->IsExist( CurrentZoneID ) && g_pWarManager->getSize() > 0)		// �������̸�(�ƴ��Ǽ������� üũ��)
	{
//		if(g_pWarManager->IsHolyLand( CurrentZoneID ) )									// �����ΰ� �ƴ� �ƴ��� �����ΰ��
//		{																				// ��� ���� ���ؼ� �˻��Ѵ�.
//			const WarInfoMap&			info = g_pWarManager->getWarInfoList();
//			WarInfoMap::const_iterator	itr = info.begin();
//			bool						creatureGuildCheck = false;						// ���ԵǾ� ���� ������� ũ���ı�尡 �����忡 ���ԵǾ��ִ��� ����
//
//			while(itr != info.end() && bWarSelect == FALSE)
//			{
//				WarInfo *info = (*itr).second;
//				if(info->getWarType() == WAR_GUILD)												// ���-_- ����...��.. �� enum ���� �ؼ� �Ѱ�����..
//				{
//					GuildWarInfo *pInfo = (GuildWarInfo *)info;
//
//					int myGuildID = g_pPlayer->GetGuildNumber();			
//					GuildWarInfo::GuildIDList joinGuild = pInfo->getJoinGuilds();
//					list<GuildID_t>::const_iterator	itr = joinGuild.Begin();					
//					
//					for(int i=0;i<joinGuild.getSize();i++,itr++)						// �� ��尡 ���� ��忡 ���ԵǾ� ������ ����� �ܿ� �ٸ� ���� ��� ��
//					{				
//						if( *itr == myGuildID )
//						{
//							if( pCreature->GetGuildNumber() != myGuildID )
//								bWarSelect = TRUE;
//							break;
//						}
//						if( *itr == pCreature->GetGuildNumber() )						// �ش� ũ���� �����̵� ���� ���̵� �����ִ°�
//							creatureGuildCheck = true;
//					}					
//				}
//				itr++;
//			}
//			if(bWarSelect == FALSE && creatureGuildCheck == true)				// ��忡 ���ԵǾ� ���� ������ ���� ��忡 ���Ե� ��常 ��.
//				bWarSelect = TRUE;
//		} else
		{								// �ش� ���� ���ؼ��� �˻��Ѵ�.				
			WarInfo *info = g_pWarManager->GetWarInfo( CurrentZoneID );
			
			if(info == NULL)
				return FALSE;

			GuildWarInfo *pInfo = (GuildWarInfo *)info;

			if(info->getWarType() == WAR_GUILD)// || info->getWarType() == 2)				// ���-_- ����...��.. �� enum ���� �ؼ� �Ѱ�����..
			{																	// 2���� ���߿�... ����� ��� �߰��Ҷ��� ����ؼ�..
				int myGuildID = g_pPlayer->GetGuildNumber();			
				GuildWarInfo::GuildIDList joinGuild = pInfo->getJoinGuilds();
				std::list<GuildID_t>::const_iterator	itr = joinGuild.Begin();
				bool	creatureGuildCheck = false;								// ���ԵǾ� ���� ������� ũ���ı�尡 �����忡 ���ԵǾ��ִ��� ����
				
				for(int i=0;i<joinGuild.getSize();i++,itr++)					// �� ��尡 ���� ��忡 ���ԵǾ� ������ ����� �ܿ� �ٸ� ���� ��� ��
				{				
					if( *itr == myGuildID )
					{
						if( pCreature->GetGuildNumber() != myGuildID )
							bWarSelect = TRUE;
						break;
					}
					if( *itr == pCreature->GetGuildNumber() )
						creatureGuildCheck = true;
				}
				if(bWarSelect == FALSE && creatureGuildCheck == true)				// ��忡 ���ԵǾ� ���� ������ ���� ��忡 ���Ե� ��常 ��.
					bWarSelect = TRUE;
			}			
		}		
	}
	
	return bWarSelect;
}