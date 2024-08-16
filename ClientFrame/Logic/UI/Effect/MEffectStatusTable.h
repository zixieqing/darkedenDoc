//----------------------------------------------------------------------
// MEffectStatusTable.h
//----------------------------------------------------------------------
// ĳ���Ϳ� �ٴ� Effect �߿���
// Ư���� ���¸� ��Ÿ���� �͵鿡 ���� EffectSpriteType�� table.. 
//
// �ϳ��� ���´� �ϳ��� EffectSpriteType���� ��Ÿ���� ����..��� ����.
//
// * ���� --> EffectSpriteType
//
//----------------------------------------------------------------------

#ifndef	__MEFFECTSTATUSTABLE_H__
#define	__MEFFECTSTATUSTABLE_H__

#include "CTypeTable.h"
#include "MTypeDef.h"
//#include "EffectSpriteTypeDef.h"
#include "MEffectStatusDef.h"

//----------------------------------------------------------------------
//
// �� ������ EffectStatus --> EffectSpriteType�� ���� ����
//
//----------------------------------------------------------------------
class EFFECTSTATUS_NODE {
	public :
		EFFECTSTATUS_NODE();

	public :
		bool						bUseEffectSprite;		// EffectSprite�� ����ϳ�?
		bool						bAttachGround;			// ĳ���� �ٴڿ� �ٳ�?

		// union���� �ص� �Ǵµ�.. - -
		TYPE_EFFECTSPRITETYPE		EffectSpriteType;		// sprite���̱�
		WORD						EffectColor;			// ���� �ٲٱ�
		ADDON						EffectColorPart;		// ���� �ٲ�� ����
		
		TYPE_ACTIONINFO				ActionInfo;				// actionInfo�� effect���
		TYPE_ACTIONINFO				OriginalActionInfo;		// EffectStatus�� ActionInfo�� �̾��ش�.
		int							SoundID;				// SoundID
		
	public :
		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);		
		void			LoadFromFile(class ifstream& file);		
};


typedef CTypeTable<EFFECTSTATUS_NODE>	EFFECTSTATUS_TABLE;
extern 	EFFECTSTATUS_TABLE*		g_pEffectStatusTable;


#endif


