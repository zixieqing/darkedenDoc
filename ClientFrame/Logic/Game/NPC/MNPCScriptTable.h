//---------------------------------------------------------------------------
// MNPCScriptTable.h
//---------------------------------------------------------------------------
/*
	int TotalNumberofScript; // �� ��ũ��Ʈ�� ��
	{
		int    ScriptID; 
		int    OwnerIDSize;
		string OwnerID;

		int TotalNumberOfSubject;
		{
			int    SubjectSize;
			string Subject;
		}

		int TotalNumberOfContent;
		{
			int    ContentSize;
			string Content;
		}
	}

	{} ���̴� �ݺ�
*/
//---------------------------------------------------------------------------

#ifndef __MNPCSCRIPTTABLE_H__
#define	__MNPCSCRIPTTABLE_H__

#include "CTypeTable.h"
#include "CTypeMap2.h"
#include "MString.h"
#include "ScriptParameter.h"

typedef std::map<std::string,ScriptParameter*>			HashMapScriptParameter;


//---------------------------------------------------------------------------
// NPC_SCRIPT
//---------------------------------------------------------------------------
class NPC_SCRIPT {
	public :
		typedef CTypeTable<MString>		STRING_TABLE;		

	public :		// public public ����~~
		MString				OwnerID;

		STRING_TABLE		SubjectTable;	
		STRING_TABLE		ContentTable;

	public :
		int					GetSubjectSize() const	{ return SubjectTable.GetSize(); }
		int					GetContentSize() const	{ return ContentTable.GetSize(); }

		void				SaveToFile(class ofstream& file);
		void				LoadFromFile(class ifstream& file);
};

//---------------------------------------------------------------------------
// MNPCScriptTable
//---------------------------------------------------------------------------
class MNPCScriptTable : public CTypeMap2<NPC_SCRIPT> {
	public :	
		
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

		int			GetSubjectSize(int scriptID) const;
		int			GetContentSize(int scriptID) const;
	
		const char*	GetSubject(int scriptID, int subjectID) const;
		const char*	GetContent(int scriptID, int contentID) const;

		// �ش� ��ũ��Ʈ ���̵� �Ķ���Ͱ��� replace �Ѵ�.
		void GetContentParameter(int scriptID, int contentID,HashMapScriptParameter para,std::string &str);
		void GetSubjectParameter(int scriptID, int subjectID,HashMapScriptParameter para,std::string &str);
};


//---------------------------------------------------------------------------
// global
//---------------------------------------------------------------------------
extern MNPCScriptTable*		g_pNPCScriptTable;

#endif
