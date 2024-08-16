//----------------------------------------------------------------------
// MInteractionObjectTable.h
//----------------------------------------------------------------------
// InteractionObject�� ������ ���� ������ �����ϴ� class
//----------------------------------------------------------------------
//
// [ �������� �ִ� ���� ] 
//
// - Type ID
// - Action�� �����ϴ� FrameID
// - �̸�... ���...
// 
//----------------------------------------------------------------------

#ifndef	__MINTERACTIONOBJECTTABLE_H__
#define	__MINTERACTIONOBJECTTABLE_H__


#include "MObject.h"
#include "CTypeTable.h"
#include "DrawTypeDef.h"
#include "MTypeDef.h"
class ifstream;
class ofstream;

//----------------------------------------------------------------------
//
// �� ������ InteractionObject�� ���� ����
//
//----------------------------------------------------------------------
class INTERACTIONOBJECTTABLE_INFO {
	public :
		BYTE					Type;			// InteractionObject Type
		TYPE_FRAMEID			FrameID;		// FrameID		
		int						Property;		// �Ӽ�
		TYPE_SOUNDID			SoundID;		// ���¸� �������� ���� SoundID

	public :
		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);		
		void			LoadFromFile(class ifstream& file);
		
};


typedef CTypeTable<INTERACTIONOBJECTTABLE_INFO>		INTERACTIONOBJECT_TABLE;
extern INTERACTIONOBJECT_TABLE* 	g_pInteractionObjectTable;

#endif

