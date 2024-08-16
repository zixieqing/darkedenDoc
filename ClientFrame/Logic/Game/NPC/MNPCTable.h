//----------------------------------------------------------------------
// MNPCTable.h
//----------------------------------------------------------------------
/*
	int numberOfNPC;
	{
		int currentNPCID;
		
		int numberOfShopTemplate
		{
			int eachShopTemplateID
		} // �ݺ�
		
		int DescriptionLength; // ������ ����
		string Description; // ���� ����
		
	} // �ݺ�

	����� ������ ���� ����� numberOfShopTemplate�� 0�̴�.
*/
//----------------------------------------------------------------------

#ifndef __MNPCTABLE_H__
#define	__MNPCTABLE_H__

#pragma warning(disable:4786)

#include "CtypeMap.h"
#include <list>
class ofstream;
class ifstream;
#include "MString.h"

//----------------------------------------------------------------------
// NPC_INFO
//----------------------------------------------------------------------
class NPC_INFO {
	public :
		typedef std::list<unsigned int>		SHOPTEMPLATEID_LIST;

	public :
		MString					Name;
		SHOPTEMPLATEID_LIST		ListShopTemplateID;

		MString					Description;
		int						SpriteID;

		//-----------------------------------------------------
		// Release
		//-----------------------------------------------------
		void		Release();

		//-----------------------------------------------------
		// File I/O
		//-----------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);
};

//----------------------------------------------------------------------
// MNPCTable (NPCID, NPC_INFO*)�� map
//----------------------------------------------------------------------
class MNPCTable : public CTypeMap<NPC_INFO> {
	public :
		MNPCTable();
		~MNPCTable();

	protected :
};

class	SERVERNPC_INFO {
	public :
		typedef std::list<unsigned int>		SHOPTEMPLATEID_LIST;

	public :
		SHOPTEMPLATEID_LIST		ListShopTemplateID;

		MString					Name;
		MString					Description;		

		//-----------------------------------------------------
		// Release
		//-----------------------------------------------------
		void		Release();

		//-----------------------------------------------------
		// File I/O
		//-----------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);
};


class MServerNPCTable : public CTypeMap<SERVERNPC_INFO> {
private :
	std::map<int,int>			NPCSPRITEID;
	
public :
	MServerNPCTable();
	~MServerNPCTable();

	int	AffectToNPCTable(MNPCTable* npc);
};


extern	MNPCTable*		g_pNPCTable;

#endif

