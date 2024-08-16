//----------------------------------------------------------------------
// CUsingColorSetTable.h
//----------------------------------------------------------------------
// CIndexSprite���� ����ϴ� ColorSet �߿���
// � Sprite���� Ư���� ����鸸 ����� �� �ְ� �ϱ� ���ؼ�..
// MAX_COLORSET���� bool�� �����
// ����� �� �ִ� COLORSET���� BOOL�� ǥ���Ѵ�.
//----------------------------------------------------------------------

#ifndef	__CUSINGCOLORSETTABLE_H__
#define	__CUSINGCOLORSETTABLE_H__

#include "CIndexSprite.h"
#include "CTypeTable.h"
class ofstream;
class ifstream;


class USINGCOLORSET_NODE {
	public :
		USINGCOLORSET_NODE();
		~USINGCOLORSET_NODE();

		//-------------------------------------------------
		// Enable / Disable
		//-------------------------------------------------
		void			Enable(int set);
		void			Disable(int set);

		//-------------------------------------------------
		// ���� ������ Enable / Disable 
		//-------------------------------------------------
		void			Enable(int start, int end);
		void			Disable(int start, int end);

		//-------------------------------------------------
		// File I/O
		//-------------------------------------------------
		void			SaveToFile(class ofstream& file);
		bool			LoadFromFile(class ifstream& file);

	protected :
		bool			m_bEnable[MAX_COLORSET];
};


typedef CTypeTable<USINGCOLORSET_NODE>		USINGCOLORSET_TABLE;
extern 	USINGCOLORSET_TABLE*	g_pUsingColorSetTable;


//----------------------------------------------------------------------
// UsingColorSet�� ����...
//----------------------------------------------------------------------
enum USINGCOLORSET
{
	USINGCOLORSET_NONE,
	USINGCOLORSET_ALL,
	USINGCOLORSET_SKIN,
	USINGCOLORSET_ITEM,
	MAX_USINGCOLORSET
};


#endif

