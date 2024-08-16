//----------------------------------------------------------------------
// MEffectSpriteTypeTable.h
//----------------------------------------------------------------------
// EffectSpriteType�� ������ ���� ������ �����ϴ� class
//----------------------------------------------------------------------
//
// [ �������� �ִ� ���� ] 
//
// - Tile������ FrameID
// - Inventory������ SpriteID
// - �̸�... ���...
// 
//----------------------------------------------------------------------

#ifndef	__MEFFECTSPRITETYPETABLE_H__
#define	__MEFFECTSPRITETYPETABLE_H__

#pragma warning(disable:4786)

#include "MTypeDef.h"
#include "DrawTypeDef.h"
#include "CTypeTable.h"
//#include "EffectSpriteTypeDef.h"
class ifstream;
class ofstream;

//----------------------------------------------------------------------
//
// �� ������ EffectSpriteType�� ���� ����
//
//----------------------------------------------------------------------
class EFFECTSPRITETYPETABLE_INFO {
	public :
		typedef std::list<TYPE_FRAMEID>		FRAMEID_LIST;

	public :
		BLT_TYPE					BltType;				// �������
		TYPE_FRAMEID				FrameID;				// Frame ID	
		bool						RepeatFrame;			// �ݺ��Ǵ� frame�ΰ�?
		TYPE_FRAMEID				ActionEffectFrameID;	// action ���� �ٸ� frame�� ��������ϴ� effect�ΰ�?
		//TYPE_FRAMEID				PairFrameID;			// ���ÿ� ��µǾ�� �ϴ� ¦~�̴�.
		FRAMEID_LIST				PairFrameIDList;		// ���ÿ� ��µǾ�� �ϴ� ����Ʈ��~�̴�.
		bool						bPairFrameBack;			// ���ÿ� ��µǴ� ����Ʈ�� �ڿ� ��µǴ°�
		TYPE_EFFECTSPRITETYPE		FemaleEffectSpriteType;	// ���ڿ�..

	public :
		EFFECTSPRITETYPETABLE_INFO();
		//-------------------------------------------------------
		// Save
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);	
		void			LoadFromFile(class ifstream& file);
		
};

typedef CTypeTable<EFFECTSPRITETYPETABLE_INFO>	EFFECTSPRITETYPE_TABLE;


//----------------------------------------------------------------------
//
// Action�� �´� EffectSpriteType
//
//----------------------------------------------------------------------
class FRAME_TYPE {
	public :
		TYPE_FRAMEID		FrameID;

	public :
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);
};

typedef CTypeTable<FRAME_TYPE>	FRAMEID_ARRAY;
class ACTION_FRAMEID_ARRAY : public FRAMEID_ARRAY {
	public :
		ACTION_FRAMEID_ARRAY();
		~ACTION_FRAMEID_ARRAY();
};

typedef CTypeTable<ACTION_FRAMEID_ARRAY>	ACTION_FRAMEID_TABLE;

class MActionEffectSpriteTypeTable : public ACTION_FRAMEID_TABLE {
	public :
		MActionEffectSpriteTypeTable();
		~MActionEffectSpriteTypeTable();
};


extern	EFFECTSPRITETYPE_TABLE*			g_pEffectSpriteTypeTable;
extern	MActionEffectSpriteTypeTable*	g_pActionEffectSpriteTypeTable;

#endif

