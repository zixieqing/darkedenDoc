//---------------------------------------------------------------------------
// MNPCScriptTable.cpp
//---------------------------------------------------------------------------

#include "Client_PCH.h"
#include "MNPCScriptTable.h"

#include "DebugInfo.h"
#include "Packet.h"
//#include "ScriptParameter.h"


#define		SCRIPT_MARK_START	"%("
#define		SCRIPT_MARK_END		")"
//---------------------------------------------------------------------------
// global
//---------------------------------------------------------------------------
MNPCScriptTable*		g_pNPCScriptTable = NULL;

//---------------------------------------------------------------------------
// 
// constructor / destructor
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//
// member functions
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Save To File
//---------------------------------------------------------------------------
void				
NPC_SCRIPT::SaveToFile(class ofstream& file)
{
	//file.write((const char*)&ScriptID, 4);
	OwnerID.SaveToFile( file );

	SubjectTable.SaveToFile( file );
	ContentTable.SaveToFile( file );
}

//---------------------------------------------------------------------------
// Load From File
//---------------------------------------------------------------------------
void				
NPC_SCRIPT::LoadFromFile(class ifstream& file)
{
	//file.read((char*)&ScriptID, 4);
	OwnerID.LoadFromFile( file );

	SubjectTable.LoadFromFile( file );
	ContentTable.LoadFromFile( file );
}


//---------------------------------------------------------------------------
//
// MNPCScriptTable
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Get Subject Size
//---------------------------------------------------------------------------
int			
MNPCScriptTable::GetSubjectSize(int scriptID) const
{
	const NPC_SCRIPT* pScript = GetData( scriptID );
	
	if (pScript==NULL)
	{
		return 0;
	}

	return pScript->SubjectTable.GetSize();
}

//---------------------------------------------------------------------------
// Get Content Size
//---------------------------------------------------------------------------
int			
MNPCScriptTable::GetContentSize(int scriptID) const
{
	const NPC_SCRIPT* pScript = GetData( scriptID );

	if (pScript==NULL)
	{
		return 0;
	}

	return pScript->ContentTable.GetSize();
}

//---------------------------------------------------------------------------
// Get Subject
//---------------------------------------------------------------------------
const char*	
MNPCScriptTable::GetSubject(int scriptID, int subjectID) const
{
	const NPC_SCRIPT* pScript = GetData( scriptID );

	if (pScript==NULL)
	{
		return NULL;
	}

	if (subjectID >= pScript->GetSubjectSize())
	{
		return NULL;
	}

	return pScript->SubjectTable[subjectID].GetString();
}

//---------------------------------------------------------------------------
// Get Content
//---------------------------------------------------------------------------
const char*	
MNPCScriptTable::GetContent(int scriptID, int contentID) const
{
	const NPC_SCRIPT* pScript = GetData( scriptID );

	if (pScript==NULL)
	{
		return NULL;
	}

	if (contentID >= pScript->GetContentSize())
	{
		return NULL;
	}

	return pScript->ContentTable[contentID].GetString();
}


//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
MNPCScriptTable::SaveToFile(class ofstream& file)
{
	TYPE_MAP::iterator iData = begin();

	//-----------------------------------------------------
	// ���� ����
	//-----------------------------------------------------
	int infoSize = size();
	file.write((const char*)&infoSize, 4);

	//-----------------------------------------------------
	// �� info ����
	//-----------------------------------------------------
	while (iData != end())
	{
		unsigned int	id		= (*iData).first;
		NPC_SCRIPT*		pData	= (*iData).second;		

		file.write((const char*)&id, 4);	// id ����
		pData->SaveToFile( file );			// NPC info ����

		iData ++;
	}
}
		
//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void		
MNPCScriptTable::LoadFromFile(class ifstream& file)
{
	//-----------------------------------------------------
	// ������ �ִ��� ����
	//-----------------------------------------------------
	Release();

	//-----------------------------------------------------
	// size 
	//-----------------------------------------------------
	int infoSize;
	file.read((char*)&infoSize, 4);

	//-----------------------------------------------------
	// �� info
	//-----------------------------------------------------
	unsigned int id;
	for (int i=0; i<infoSize; i++)
	{		
		file.read((char*)&id, 4);
		NPC_SCRIPT*	pData = new NPC_SCRIPT;

		pData->LoadFromFile( file );

		//-----------------------------------------------------
		// map�� �߰��Ѵ�.
		//-----------------------------------------------------
		if (!AddData( id, pData ))
		{
			delete pData;
		}
	}
}

void
MNPCScriptTable::GetContentParameter(int scriptID, int contentID,HashMapScriptParameter para,std::string& str)
{
	str = GetContent(scriptID, contentID);	

	if(str.empty())
		return;
	
	
/*	-_- �ߺ� �˻� �ȵǵ��� �ǵ�ǵ�..��.��
	while(1)
	{
		str_s = str.find(SCRIPT_MARK_START,str_s);
		if(str_s == -1)
			break;
		
		str_e = str.find(SCRIPT_MARK_END,str_s);
		if(str_e == -1)
			break;
		
		std::string scriptName;
		memset(temp,0,sizeof(temp));
		memcpy(temp,str.c_str()+str_s+2,str_e-(str_s+2));
		scriptName = temp;

		// ScriptName �� Parameter �� ���Ѵ�.

		if(para.find(scriptName) != para.end())
		{
			str.replace(str.begin()+str_s, str.begin()+str_e,para[scriptName]->getValue().begin(),para[scriptName]->getValue().end());		
		} 
	}*/

	int i=0;
	HashMapScriptParameter::const_iterator itr = para.begin();

	while(itr != para.end())
	{
		std::string key;
		key = "%(";
		key+= (*itr).first;
		key+= ")";

		while((i=str.find(key)) != -1)
			str.replace(str.begin()+i,str.begin()+i+key.size(),(*itr).second->getValue());
		itr++;
	}
}

void
MNPCScriptTable::GetSubjectParameter(int scriptID, int subjectID,HashMapScriptParameter para,std::string &str)
{
	str = GetSubject(scriptID, subjectID);	

	if(str.empty())
		return;
	
	/* �ߺ��˻� �ȵǵ��� �ǵ�ǵ�..��.��
	int str_s = 0;
	int str_e = 0;
	char temp[512];

	while(1)
	{
		str_s = str.find(SCRIPT_MARK_START,str_s);
		if(str_s == -1)
			break;
		
		str_e = str.find(SCRIPT_MARK_END,str_s);
		if(str_e == -1)
			break;
		
		std::string scriptName;
		memset(temp,0,sizeof(temp));
		memcpy(temp,str.c_str()+str_s+2,str_e-(str_s+2));
		scriptName = temp;

		// ScriptName �� Parameter �� ���Ѵ�.

//		if(scriptName == para->getName())
		if(para.find(scriptName) != para.end())
			str.replace(str.begin()+str_s, str.begin()+str_e,para[scriptName]->getValue().begin(),para[scriptName]->getValue().end());				
	}*/

	int i=0;
	HashMapScriptParameter::const_iterator itr = para.begin();

	while(itr != para.end())
	{
		std::string key;
		key = "%(";
		key+= (*itr).first;
		key+= ")";

		while((i=str.find(key)) != -1)
			str.replace(str.begin()+i,str.begin()+i+key.size(),(*itr).second->getValue());
		itr++;
	}
}
