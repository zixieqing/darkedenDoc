//---------------------------------------------------------------------------
// MCompareManager.h
//---------------------------------------------------------------------------

#ifndef __MCOMPAREMANAGER_H__
#define	__MCOMPAREMANAGER_H__

#include <Windows.h>
#include "MHelpDef.h"

//---------------------------------------------------------------------------
//
//							MCompareManager
//
//---------------------------------------------------------------------------
class MCompareManager {
	public :
		typedef BOOL (MCompareManager::*COMPARE_FUNCTION)();


	public :
		MCompareManager();
		~MCompareManager();

		//-----------------------------------------------------------
		// �ʱ�ȭ - �ʼ�~~
		//-----------------------------------------------------------
		void			Init();

		//-----------------------------------------------------------
		// ���� �˻�
		//-----------------------------------------------------------
		BOOL			Compare(HELP_COMPARE hc);
		
	protected :
		//-----------------------------------------------------------
		// ������ messageó���ϴ� �Լ���
		//-----------------------------------------------------------
		BOOL	Execute_HC_RANDOM();
		BOOL	Execute_HC_PLAYER_IN_SHOP();
		BOOL	Execute_HC_PLAYER_IN_REPAIR();
		BOOL	Execute_HC_PLAYER_IN_STORAGE();
		BOOL	Execute_HC_PLAYER_IN_TRADE();
		BOOL	Execute_HC_PLAYER_IN_NORMAL_GAME_MODE();
		BOOL	Execute_HC_PLAYER_IS_SLAYER();
		BOOL	Execute_HC_PLAYER_IS_VAMPIRE();
		BOOL	Execute_HC_NO_SKILL_SELECTED();
		BOOL	Execute_HC_NO_SKILL_FUNCTION_KEY_DEFINED();
		BOOL	Execute_HC_HAS_HEAL_POTION_IN_BELT();
		BOOL	Execute_HC_HAS_HEAL_POTION_IN_INVENTORY();
		BOOL	Execute_HC_HAS_MANA_POTION_IN_BELT();
		BOOL	Execute_HC_HAS_MANA_POTION_IN_INVENTORY();
		BOOL	Execute_HC_RECEIVE_FIRST_BONUS_POINT();
		BOOL	Execute_HC_DIDNOT_WHISPER_YET();
		BOOL	Execute_HC_ITEM_PICKED_UP();
		BOOL	Execute_HC_USED_ALT_FOR_ITEM();
		BOOL	Execute_HC_USED_FUNCTION_KEY_FOR_QUICKITEM();
		BOOL	Execute_HC_EMPTY_BULLET();

	protected :
		COMPARE_FUNCTION		m_CompareFunction[MAX_HELP_COMPARE];
};

//---------------------------------------------------------------------------
// Global
//---------------------------------------------------------------------------
extern MCompareManager*		g_pCompareManager;

#endif

