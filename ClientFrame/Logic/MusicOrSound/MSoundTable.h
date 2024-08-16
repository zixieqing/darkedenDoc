//----------------------------------------------------------------------
// MSoundTable.h
//----------------------------------------------------------------------
// Sound Loading�ÿ� Sound���� �ʿ��� ������ �����ϴ� class
//----------------------------------------------------------------------
//
// [ Sound���� Loadind�� �ʿ��� ���� ] 
//
// - file�̸�
// 
//----------------------------------------------------------------------

#ifndef	__MSOUNDTABLE_H__
#define	__MSOUNDTABLE_H__

#include "MTypeDef.h"
#include "CTypeTable.h"
#include "MString.h"
#include "SoundDef.h"


//----------------------------------------------------------------------
//
// �� ������ Sound�� ���� ����
//
//----------------------------------------------------------------------
class SOUNDTABLE_INFO {
	public :
		SOUNDTABLE_INFO()
		{
			//pDSBuffer = NULL;			
		}

		~SOUNDTABLE_INFO()
		{
			//if (pDSBuffer != NULL)			
			//{
			//	delete pDSBuffer;
			//}			
		}

	public :
		MString						Filename;	// Sound File�̸�
		//LPDIRECTSOUNDBUFFER		pDSBuffer;		// load�� wav

	public :
		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);		
		void			LoadFromFile(class ifstream& file);		
};

typedef CTypeTable<SOUNDTABLE_INFO>		SOUND_TABLE;
extern 	SOUND_TABLE*		g_pSoundTable;


#endif
