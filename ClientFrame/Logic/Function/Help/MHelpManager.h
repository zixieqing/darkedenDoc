//---------------------------------------------------------------------------
// MHelpManager.h
//---------------------------------------------------------------------------
/*

	//---------------------------------------------------------------------------
	// �ϳ��� HelpEvent ���� ����
	//---------------------------------------------------------------------------
	pHelpNode = new MCompareHelpNode( HC_PICKED_UP_ITEM );
		// ������ �ֿ����� �ִٸ�
		pHelpNode->SetTrue( new MCompareHelpNode( HC_USE_ALT_FOR_ITEM ) );
			// ALT�� ����� ���� ���� ���
			pHelpNode->GetTrue()->SetFalse( new MOutputHelpNode( HO_ALT_TO_PICKUP ) );

		// ������ �ֿ����� ���ٸ�
		pHelpNode->SetFalse( new MCompareHelpNode( HC_USE_ALT_FOR_ITEM ) );
			// ALT�� ����� ���� �ִٸ�
			pHelpNode->GetFalse()->SetTrue( new MOutputHelpNode( HO_CLICK_TO_PICKUP ) );
			// ALT�� ��������� ���ٸ�
			pHelpNode->GetFalse()->SetFalse( new MOutputHelpNode( HO_ALT_TO_PICKUP ) );

	g_pHelpManager[HE_APPEAR_ITEM] = pHelpNode;


	//---------------------------------------------------------------------------
	// event�� ������ ��, event����..
	//---------------------------------------------------------------------------
	g_pHelpManager->ProcessEvent( HE_APPEAR_ITEM );

*/
//---------------------------------------------------------------------------

#ifndef __MHELPMANAGER_H__
#define	__MHELPMANAGER_H__

#pragma warning(disable:4786)

#include "CTypeTable.h"
#include "MHelpDef.h"
#include "Client_PCH.h"
#ifdef __GAME_CLIENT__
	#include "UserOption.h"
#endif


//---------------------------------------------------------------------------
//
//							MHelpNode
//
//---------------------------------------------------------------------------
class MHelpNode {
	public :
		enum NODE_TYPE
		{
			TYPE_NULL = 0,
			TYPE_COMPARE,
			TYPE_OUTPUT,

			MAX_NODE_TYPE
		};

	public :
		MHelpNode() {}
		virtual ~MHelpNode() {}
	
		virtual NODE_TYPE	GetType() const	= 0;

		//------------------------------------------------------
		// File I/O
		//------------------------------------------------------
		virtual void		SaveToFile(class ofstream& file) = 0;
		virtual void		LoadFromFile(class ifstream& file) = 0;

	public :
		// NewItem()�� ���� functions pointer
		typedef MHelpNode*	(*FUNCTION_NEWNODE)();

		//-------------------------------------------------------
		// ���ϴ� class�� Item�� ��ü�� �����Ѵ�.
		//-------------------------------------------------------
		static MHelpNode*	NewNode(MHelpNode::NODE_TYPE nodeType);

		// �� class���� NewItem()�� ���� function pointer
		static FUNCTION_NEWNODE		s_NewNodeClassTable[MAX_NODE_TYPE];
};

//---------------------------------------------------------------------------
//
//							MCompareHelpNode
//
//---------------------------------------------------------------------------
// CompareType�� ���� True / False�� ������.
//---------------------------------------------------------------------------
class MCompareHelpNode : public MHelpNode {
	public :
		MCompareHelpNode(HELP_COMPARE ct=HC_RANDOM)
		{
			m_pCompareType = ct;
			m_pTrue = m_pFalse = NULL;
		}	

		virtual ~MCompareHelpNode()
		{
			if (m_pTrue!=NULL)	{ delete m_pTrue; }
			if (m_pFalse!=NULL)	{ delete m_pFalse; }
		}

		//-----------------------------------------------------------
		// Get Type
		//-----------------------------------------------------------
		virtual MHelpNode::NODE_TYPE	GetType() const	{ return MHelpNode::TYPE_COMPARE; }

		//-----------------------------------------------------------
		// Get Next
		//-----------------------------------------------------------
		MHelpNode*			GetNext() const;

		//-----------------------------------------------------------
		// Get/Set Compare Node
		//-----------------------------------------------------------
		HELP_COMPARE		GetCompareType() const		{ return m_pCompareType; }
		void				SetTrue(MHelpNode* pNode);
		void				SetFalse(MHelpNode* pNode);
		MHelpNode*			GetTrue() const				{ return m_pTrue; }
		MHelpNode*			GetFalse() const			{ return m_pFalse; }

		//------------------------------------------------------
		// File I/O
		//------------------------------------------------------
		virtual void		SaveToFile(class ofstream& file);
		virtual void		LoadFromFile(class ifstream& file);	

	public :
		static MHelpNode*	NewNode()					{ return new MCompareHelpNode; }

	protected :
		HELP_COMPARE		m_pCompareType;			// �˻��غ����� ����
		MHelpNode*			m_pTrue;				// ������ �����ϴ� ���
		MHelpNode*			m_pFalse;				// ������ �������� ���ϴ� ���
};

//---------------------------------------------------------------------------
//
//							MOutputHelpNode
//
//---------------------------------------------------------------------------
// ����� ������ ��Ÿ����.
//---------------------------------------------------------------------------
class MOutputHelpNode : public MHelpNode, public std::list<HELP_OUTPUT> {
	public :
		typedef std::list<HELP_OUTPUT>		OUTPUT_LIST;

	public :
		MOutputHelpNode() {}
		virtual ~MOutputHelpNode() {}

		//-----------------------------------------------------------
		// Get Type
		//-----------------------------------------------------------
		virtual MHelpNode::NODE_TYPE	GetType() const		{ return MHelpNode::TYPE_OUTPUT; }

		//-----------------------------------------------------------
		// Get 
		//-----------------------------------------------------------
		HELP_OUTPUT			GetOutputType() const;
		
		//------------------------------------------------------
		// File I/O
		//------------------------------------------------------
		virtual void		SaveToFile(class ofstream& file);
		virtual void		LoadFromFile(class ifstream& file);	

	public :
		static MHelpNode*	NewNode()					{ return new MOutputHelpNode; }
};


//---------------------------------------------------------------------------
//
//							MHelpManager
//
//---------------------------------------------------------------------------
class MHelpManager : public CTypeTable<MHelpNode*> {
	public :
		MHelpManager();
		~MHelpManager();

		//------------------------------------------------------
		// Init / Release
		//------------------------------------------------------
		void		Init(int size);		
		void		Release();
		
		//------------------------------------------------------
		// Event Occured
		//------------------------------------------------------
		void		ClearEventOccured();
		bool		IsEventOccured(HELP_EVENT he)		{ return m_EventOccured[he]; }

		//------------------------------------------------------
		// Execute Event
		//------------------------------------------------------
		void		ExecuteEvent(HELP_EVENT he);

		//------------------------------------------------------
		// File I/O
		//------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);	

	protected :
		CTypeTable<bool>		m_EventOccured;
};

//---------------------------------------------------------------------------
// Global
//---------------------------------------------------------------------------
extern MHelpManager*		g_pHelpManager;

//-----------------------------------------------------------------------------
// Execute Help Event
//-----------------------------------------------------------------------------
extern void		ExecuteHelpEvent(HELP_EVENT he);

#if defined(__GAME_CLIENT__) && defined(OUTPUT_DEBUG)
	#define __BEGIN_HELP_EVENT 		if (g_pUserOption!=NULL && g_pUserOption->UseHelpEvent) {
	#define __END_HELP_EVENT		}
	#define __USE_HELP_EVENT
#else
	#define __BEGIN_HELP_EVENT 		((void)0);
	#define __END_HELP_EVENT 		((void)0);
#endif

#endif

