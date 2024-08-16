//--------------------------------------------------------------------------------
// RequestFunction.cpp
//--------------------------------------------------------------------------------
#include "Client_PCH.h"
#include "RequestServerPlayerManager.h"
#include "RequestClientPlayerManager.h"
#include "DebugInfo.h"


//--------------------------------------------------------------------------------
// Request Connect
//--------------------------------------------------------------------------------
// IP�� ��ǻ�Ϳ� Name�̶� ĳ���Ϳ��� �����Ѵ�.
//--------------------------------------------------------------------------------
void	
RequestConnect(const char* pIP, const char* pName)
{
	DEBUG_ADD_FORMAT("[RequestConnect] ip=%s, name=%s", pIP, pName);

	if (g_pRequestClientPlayerManager!=NULL)
	{
		g_pRequestClientPlayerManager->Connect( pIP, pName );
	}
}

//--------------------------------------------------------------------------------
// Request Disconnect
//--------------------------------------------------------------------------------
// Name�̶� ĳ���ͷκ����� ������ �����Ѵ�.
//--------------------------------------------------------------------------------
void	
RequestDisconnect(const char* pName)
{
	DEBUG_ADD_FORMAT("[RequestDisconnect] name=%d", pName);

	//-------------------------------------------------------------------
	// ���� Name���� ������ �ִ� �� ���´�.
	//-------------------------------------------------------------------
	if (g_pRequestClientPlayerManager!=NULL)
	{
		g_pRequestClientPlayerManager->Disconnect( pName );
	}

	//-------------------------------------------------------------------
	// Name�� ������ ������ �ִ°� ���´�.
	//-------------------------------------------------------------------
	if (g_pRequestServerPlayerManager!=NULL)
	{
		g_pRequestServerPlayerManager->Disconnect( pName );
	}
}