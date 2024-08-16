//-----------------------------------------------------------------------------
// MTradeManager.h
//-----------------------------------------------------------------------------
// ��ȯ ���~
//
// Init�ϸ� �� ���� (inventory�� moneymanager)�� �����Ѵ�.
// 
// �ϳ��� ����.. �ϳ��� ����..
//
// * Get .... () �ؼ� �ܺο��� ó���ϰ�..
//
// item�� add/remove�ǰų�.. money�� �ٲ�� .. AcceptTrade�� �����ؾ��Ѵ�.
//
// MyAcceptTrade && OtherAcceptTrade�� ��츸 trade �����ϴ�.
//
// CanTrade()�� üũ�غ��� trade�����ϸ� Trade()�Ѵ�.
//-----------------------------------------------------------------------------

#ifndef __MTRADEMANAGER_H__
#define __MTRADEMANAGER_H__

#include "MInventory.h"
#include "MMoneyManager.h"

class MTradeManager {
	public :
		MTradeManager();
		~MTradeManager();

		//-------------------------------------------------------
		// Init / Release
		//-------------------------------------------------------
		void				Init();
		void				Release();

		//-------------------------------------------------------
		// inventory ���
		//-------------------------------------------------------
		MInventory*			GetMyInventory() const			{ return m_pMyInventory; }
		MInventory*			GetOtherInventory() const		{ return m_pOtherInventory; }

		//-------------------------------------------------------
		// money manager ���
		//-------------------------------------------------------
		MMoneyManager*		GetMyMoneyManager() const		{ return m_pMyMoney; }
		MMoneyManager*		GetOtherMoneyManager() const	{ return m_pOtherMoney; }

		//-------------------------------------------------------
		// Trade OK ?
		//-------------------------------------------------------
		bool				IsAcceptTime() const;
		void				SetNextAcceptTime();		// ���� ��ȯ ������ �ð� ����

		bool				IsAcceptMyTrade() const				{ return m_bAcceptMyTrade; }
		bool				IsAcceptOtherTrade() const			{ return m_bAcceptOtherTrade; }

		void				AcceptMyTrade()						{ m_bAcceptMyTrade = true; }
		void				AcceptOtherTrade()					{ m_bAcceptOtherTrade = true; }

		void				RefuseMyTrade();
		void				RefuseOtherTrade();

		//-------------------------------------------------------
		// Trade
		//-------------------------------------------------------
		bool				CanTrade() const;		// trade �����Ѱ�?
		bool				Trade();				// ��ȯ!
		bool				CancelTrade();			// ��ȯ ����

		//-------------------------------------------------------
		// ��ȯ�ҷ��� ����� ����
		//-------------------------------------------------------
		void				SetOtherID(TYPE_OBJECTID otherID)	{ m_OtherID = otherID; }
		TYPE_OBJECTID		GetOtherID() const					{ return m_OtherID; }
		void				SetOtherName(const char* pName)		{ m_OtherName = pName; }
		const char*			GetOtherName() const				{ return m_OtherName.GetString(); }

	protected :
		TYPE_OBJECTID		m_OtherID;				// �ٸ� ��� ID
		MString				m_OtherName;			// �ٸ� ��� �̸�

		MInventory*			m_pMyInventory;			// ����
		MInventory*			m_pOtherInventory;		// ����

		MMoneyManager*		m_pMyMoney;				// �� ��
		MMoneyManager*		m_pOtherMoney;			// �� ��

		bool				m_bAcceptMyTrade;			// ���� ��ȯȮ��
		bool				m_bAcceptOtherTrade;		// ���� ����Ȯ��

		DWORD				m_NextAcceptTime;		// OK ���� �� �ִ� �ð�
};

extern MTradeManager*		g_pTradeManager;

#endif

