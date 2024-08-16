//----------------------------------------------------------------------
// TempInformation.h
//----------------------------------------------------------------------
// Client�� ���� �߿��� ���� �� �ִ� ��
//----------------------------------------------------------------------

#ifndef	__TEMPINFORMATION_H__
#define	__TEMPINFORMATION_H__

#include <Windows.h>

class TempInformation {
	public :
		enum TEMP_MODE
		{
			MODE_NULL,
			MODE_SKILL_LEARN,		// (domainType, maxLevel, skillType)
			MODE_SHOP_BUY,			// (shelfType, index, x, y, MShop*)
			MODE_SHOP_SELL,			// (MItem*)
			MODE_SHOP_SELL_ALL_SKULL,		// nothing.. (�ذ� �� �ȱ�)
			MODE_SHOP_REPAIR,		// (MItem*)
			MODE_SHOP_SILVERING,	// (MItem*)
			MODE_STORAGE_BUY,		// (price)
			MODE_STORAGE_BUY_WAIT,	// (nothing.. - -)

			MODE_TRADE_REQUEST,		// (ID)
			MODE_TRADE_VERIFY_DROP_TO_INVENTORY,		// (ID, x, y, MItem*)
			MODE_TRADE_VERIFY_INSERT_TO_INVENTORY,
			MODE_TRADE_VERIFY_PICKUP_FROM_INVENTORY,	// (ID, x, y, MItem*)
			MODE_TRADE_VERIFY_PICKUP_TO_QUICKSLOT,		// (slot,     MItem*)

			MODE_TRADE_VERIFY_CANCEL,					// OK�Ѱ� ���
			MODE_TRADE_VERIFY_CLOSE,					// ���� ���� ��
			MODE_TRADE_VERIFY_ADD_MONEY,				// (money)
			MODE_TRADE_VERIFY_REMOVE_MONEY,				// (money)
			MODE_TRADE_VERIFY_ADD_ITEM,					// (ID, x, y, MItem*)
			MODE_TRADE_VERIFY_REMOVE_ITEM,				// (ID, x, y, MItem*)

			MODE_PARTY_REQUEST,		// (ID)

			MODE_SKILL_MAKE_ITEM,	// (itemClass, itemType)

			MODE_BONUSPOINT_USE,	// (part(0,1,2=str,dex,int))
	
			MODE_WAIT_RESURRECT,	// UI�� ��ٸ��� ���

			MODE_ITEM_TO_ITEM,		// � �����ۿ� ���� ������ �ߴ°�?
			MODE_WAIT_BRING_FEE,	// ���� �����°� ���� ��Ŷ�� �ö�����..
			MODE_INPUT_NAME,		// �̸� �Է����̸� �Ķ���Ϳ� �ش� NPC ID ��.
			MODE_SELECT_QUEST,		// ��ų ����
			MODE_ITEM_MIXING,		// ������ �ͽ�
			MODE_ITEM_CODE_SHEET,	// �ڵ� ��Ʈ�� ������ ������ Ÿ��

			MODE_PETITEM_MOVETO_INVENTORY, // �� ������ -> �κ�
			MODE_PETITEM_MOVETO_PETSTORAGE, //  �κ� -> �� ������

			MODE_SMS_ADD_ADDRESS,	// sms �ּ� �߰�
			MODE_SMS_DELETE_ADDRESS,// sms �ּ� ����
			
			MODE_NICKNAME_CHANGE_CUSTOM, // Ŀ���� �г��� ����
			MODE_NICKNAME_SELECT_NICK, // �г��� ���� ����

			MAX_MODE
		};

	public :
		TempInformation();
		~TempInformation();

		//--------------------------------------------------------
		// File I/O
		//--------------------------------------------------------
		//void	SaveToFile(const char* filename);
		//bool	LoadFromFile(const char* filename);
		TEMP_MODE		Mode;

	public :
		void			SetMode(TEMP_MODE mode);
		const TEMP_MODE GetMode() const;

		int				Value1;
		int				Value2;
		int				Value3;
		int				Value4;

		int				PartyInviter;	// ���� ���� ó���Ǵ°Ŷ󼭸�.. - -;

		void*			pValue;
};


extern	TempInformation*		g_pTempInformation;

#endif

