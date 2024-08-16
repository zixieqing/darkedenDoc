//---------------------------------------------------------------------------
// MHelpDisplayer.cpp
//---------------------------------------------------------------------------
#include "Client_PCH.h"
#include "MHelpDisplayer.h"
#include "MHelpStringTable.h"
#include "CMessageArray.h"

//---------------------------------------------------------------------------
// Global
//---------------------------------------------------------------------------
MHelpDisplayer*		g_pHelpDisplayer = NULL;

extern DWORD			g_CurrentTime;
extern CMessageArray*	g_pHelpMessage;

//---------------------------------------------------------------------------
// Define
//---------------------------------------------------------------------------
// �޼��� ���� �ð�
#define	DELAY_HELP_OUTPUT_LAST		10000		// 10�� = 20*1000 

//---------------------------------------------------------------------------
//
// constructor / destructor
//
//---------------------------------------------------------------------------
MHelpDisplayer::MHelpDisplayer()
{
	m_DelayTime = 0;
}

MHelpDisplayer::~MHelpDisplayer()
{
}

//---------------------------------------------------------------------------
//
// member functions
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// OutputHelp (HELP_OUTPUT)
//---------------------------------------------------------------------------
// HELP_OUTPUT �ϳ��� ����ϴµ�..
// ����� �ȵ� ���� �ִ�. - -;
// ���ÿ� �ʹ� ���� message���� ��µǸ� ���ž��� ������..
// �ð��밡 ��ġ�� message���� �����ع�����.
//---------------------------------------------------------------------------
void	
MHelpDisplayer::OutputHelp(HELP_OUTPUT ho)
{
	if (ho < g_pHelpStringTable->GetSize())
	{
		if (g_CurrentTime > m_DelayTime)
		{
			if (g_pHelpStringTable->IsDisplayed(ho))
			{			
				// �̹� ����ߴ� �Ÿ�.. �����Ѵ�. - -;
			}
			else
			{
				MString& helpString = (*g_pHelpStringTable)[ho];

				g_pHelpMessage->Add( helpString.GetString() );

				m_DelayTime = g_CurrentTime + DELAY_HELP_OUTPUT_LAST;
			}					
		}	
		else
		{
			// ������ ����ѰŶ� �ð��� ���ļ� �����ϴ� ��� -_-;
		}
	}
}

