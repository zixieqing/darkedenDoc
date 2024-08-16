//-----------------------------------------------------------------------------
// MMoneyManager.cpp
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include "MMoneyManager.h"

#include "MHelpManager.h"
#include "MHelpDef.h"
//-----------------------------------------------------------------------------
// Global
//-----------------------------------------------------------------------------
MMoneyManager*		g_pMoneyManager = NULL;

//-----------------------------------------------------------------------------
//
// constructor / destructor
//
//-----------------------------------------------------------------------------
MMoneyManager::MMoneyManager()
{
	m_MoneyLimit	= 2000000000;		// 20��
	m_Money			= 0;
}

MMoneyManager::MMoneyManager(const MMoneyManager& mm)
{
	m_MoneyLimit = mm.m_MoneyLimit;
	m_Money = mm.m_Money;
}

MMoneyManager::~MMoneyManager()
{
}

//-----------------------------------------------------------------------------
//
// member functions
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Set Money
//-----------------------------------------------------------------------------
bool
MMoneyManager::SetMoney(int money)
{
	// 0���ϰų� �Ѱ踦 �Ѿ�� �ȵȴ�.
	if (money<0 || money > m_MoneyLimit)
	{
		return false; 
	}

	m_Money = money;

	// 2004, 5, 6, sobeit add start - ���� 10 ���� ������ ������ ����
#ifdef __GAME_CLIENT__
	static bool CanBuyStorage = false;
	if( false == CanBuyStorage && m_Money>100000 )
	{
		ExecuteHelpEvent(HELP_EVENT_STORAGE_BUY);
		CanBuyStorage = true;
	}
#endif
	//2004, 5, 6 sobeit add end
	return true;
}

//-----------------------------------------------------------------------------
// Add Money
//-----------------------------------------------------------------------------
bool
MMoneyManager::AddMoney(int money)
{
	return SetMoney( m_Money + money );
}

//-----------------------------------------------------------------------------
// Remove Money
//-----------------------------------------------------------------------------
bool
MMoneyManager::UseMoney(int money)
{
	return SetMoney( m_Money - money );
}

//-----------------------------------------------------------------------------
// Can Add Money
//-----------------------------------------------------------------------------
bool		
MMoneyManager::CanAddMoney(int money)
{
	int left = m_Money + money;

	if (money > m_MoneyLimit)
	{
		return false; 
	}

	return true;
}

//-----------------------------------------------------------------------------
// Can Use Money
//-----------------------------------------------------------------------------
bool		
MMoneyManager::CanUseMoney(int money)
{
	int left = m_Money - money;

	if (left<0)
	{
		return false; 
	}

	return true;
}