//#define NETMARBLE_DEBUG
#include "Client_PCH.h"
#include <windows.h>
#include "Assert.h"
#include "NMCrypt.h"
#include "MString.h"

namespace
{
	MString g_NetmarbleCommandLine = "";
};

struct NETMARBLE_INFO
{
	MString ID;
	MString Password;
	int WorldID;
	int ServerID;
	bool bGore;
};

// 2004, 7, 14, sobeit add start
struct REALSERVER_INFO
{
	bool bMode;		// 0: ��������, 1:��������
	int WorldID;	// 0: ���, 1: �緹��
	MString ID;		// id
	MString Key;	// Key
};
// 2004, 7, 14, sobeit add end
std::string g_ServIP;//     = arg[0];					// ���� IP
DWORD g_ServPort;//   = (UINT)::atoi(arg[1]);	// ���� Port
std::string g_AuthCookie;// = arg[2];					// ���� ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
std::string g_DataCookie;// = arg[3];					// ������ ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
std::string g_CpCookie;//   = arg[4];					// CP��Ű		- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
std::string g_SpareParam;///*= arg[5];					// ������ ����(CP���ӵ�� ���)*/

char* _StrTok(const char* str, const char sep)
{
	// strtok()�� ���� ����� �Լ������� separator�� 1���� �ް�
	// ���ڰ� ����ִ� ��쵵 ���ڷ� ������

	static const int TOK_BUFSIZE = 1024*40;

	static char* pnow = NULL;
	static char buf[TOK_BUFSIZE];
	static char token[TOK_BUFSIZE];

	if(str) {
		int slen = strlen(str);
//		assert(slen < TOK_BUFSIZE);		// ASSERT
		strcpy(buf, str);
		pnow = buf;
	}

	if(!pnow || *pnow == 0)
		return NULL;

	int tlen = 0;
	char* porg = pnow;
	while(*pnow != 0)
	{
		if(*pnow == sep) {
			++pnow;
			break;
		}

		++tlen;
		++pnow;
	}

	if(tlen > 0) {
		strncpy(token, porg, tlen);
		token[tlen] = 0;
	}
	else {
		token[0] = 0;
	}

	return token;
}

BOOL AnalyzeArgument(char *key)
{
	//
	// Ŭ������ ���� ���� ��Ģ(������ ���ڴ� �ĸ�(,)�� ���еǸ� ���� ������ ������ ����)
	// ���� ������ ���� : ServerIP,Port,AuthCookie,DataCookie,CpCookie,SpareParam (���ڴ� ��ȣȭ�Ǿ� �ִ�)
	// - �ݸ��� ���ӿ����� CpCookie�� �������� �ʴ´�
	// - CP ���ӿ����� AuthCookie, DataCookie�� �������� �ʴ´�(��� CP������ ����)
	// - Extra ���ڴ� �����Ǳ⵵ �Ѵ�
	//

	char buf[1024*20] = {0,};	// ���۴� ����� ũ�� ��´�

	// Ŭ�����忡�� ���� �����͸� �о�´�(�ѹ� ������ ������)
	if(!GetNMClipData(buf, sizeof(buf)-1, key, true))
		return FALSE;

	if(strlen(buf)==0)
		return FALSE;

	char arg[6][1024*2] = {0,};

	int argcnt = 0;
	char* token = _StrTok(buf, ',');
	while(token && argcnt < 6)
	{
		strcpy(arg[argcnt], token);
		argcnt++;
		token = _StrTok(NULL, ',');
	}

	// ���ڰ� �ּ��� 5���� �Ǿ�� �Ѵ�
	if(argcnt < 5)
		return FALSE;

	// IP�ּҰ� �ùٸ��� �˻�
	if(strlen(arg[0]) > 16)
		return FALSE;

	// CP ������ �Ʒ��κ��� ���� ����
	g_ServIP     = arg[0];					// ���� IP
	g_ServPort   = (UINT)::atoi(arg[1]);	// ���� Port
	g_AuthCookie = arg[2];					// ���� ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
	g_DataCookie = arg[3];					// ������ ��Ű	- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
	g_CpCookie   = arg[4];					// CP��Ű		- ���� ũ�⸦1024*2 ������ ��ƾ� �Ѵ�
	g_SpareParam = arg[5];					// ������ ����(CP���ӵ�� ���)
	
	return TRUE;
}

int HexStringToDec(char *str)
{
	int dec = 0;
	const int strLen = strlen(str);

	for(int i = strLen-1, multi = 1; i >= 0; i--, multi *= 16)
	{
		int num;
		if(str[i] >= '0' && str[i] <= '9')
			num = str[i] - '0';
		else
		if(str[i] >= 'A' && str[i] <= 'F')
			num = str[i] - 'A' + 10;
		else
			return -1;

		dec += num*multi;
	}
	return dec;
}

// �ݸ����
//-----------------------------------------------------------------------
// ParsingNetmarble
//-----------------------------------------------------------------------
// DarkEden.exe ID&PASS&WORLDID&SERVERID
//-----------------------------------------------------------------------
bool
ParsingNetmarble(const char* pCommandLine, NETMARBLE_INFO &info)
{
#ifdef NETMARBLE_DEBUG
	MessageBox(NULL,pCommandLine,"CommandLine",MB_OK);
#endif
	char szTemp[4096];

	const char *pString = strchr(pCommandLine, ' ');
	if(pString == NULL)
	{
		return false;
	}

	strcpy(szTemp, pString+1);
		
	BOOL bResult = AnalyzeArgument( szTemp );

	if( bResult == FALSE )
	{
		MessageBox( NULL, "�ݸ��� Ȩ�������� ���ؼ� �ٽ� �������ּ���.","NetmarbleDarkEden",MB_OK);
		exit(0);
		Assert( bResult );
	}

	info.WorldID = g_ServPort/10;
	info.ServerID = g_ServPort%10;

//	sprintf( szTemp, "%d %d", info.WorldID, info.ServerID );
//	MessageBox( NULL, szTemp, szTemp, MB_OK );
	
	info.ID = g_CpCookie.c_str();
	info.Password = "test";

//	strcpy( szTemp, g_NetmarbleCommandLine.GetString() );
////	strcpy( szTemp, "2,20,netmetro3,netmetro3NM00011EB7BA45");
//
//	char *pszTemp, *pszTemp2;
////	char* pStr;
//	
//	pszTemp = szTemp;
//
//	//-------------------------------------------------
//	// Teen ����
//	//-------------------------------------------------
////	pszTemp = pszTemp2+1;
//	pszTemp2 = strchr(pszTemp, ',');
//
//	// �Ľ̿� &�� ã�� ���ϸ� ����!
//	if(pszTemp2 == NULL)
//		return false;
//
//	*pszTemp2 = '\0';
//
//	if(strlen(pszTemp) != 1)
//		return false;
//
//	switch(atoi(pszTemp))
//	{
//	case 0:
//	case 1:
////		g_pUserInformation->GoreLevel = false;
//		info.bGore = false;
//		break;
//	
//	case 2:
////		g_pUserInformation->GoreLevel = true;
//		info.bGore = true;
//		break;
//	}
//
//	//-------------------------------------------------
//	// WorldID ����
//	//-------------------------------------------------
//	pszTemp = pszTemp2+1;
//	pszTemp2 = strchr(pszTemp, ',');
//
//	// �Ľ̿� &�� ã�� ���ϸ� ����!
//	if(pszTemp2 == NULL)
//	{
//		return false;
//	}
//
//	*pszTemp2 = '\0';
//
//	if(strlen(pszTemp) != 2)
//	{
//		return false;
//	}
//	
//	int num = atoi(pszTemp);
////	g_pUserInformation->NetmarbleWorldID = num/10;
////	g_pUserInformation->NetmarbleServerID = num%10;
//	info.WorldID = num/10;
//	info.ServerID = num%10;
//
//	//-------------------------------------------------
//	// ID ����
//	//-------------------------------------------------
//	// 2,10,larosellarosel,larosellaroselNM000076B17852
//	pszTemp = pszTemp2+1;
//	pszTemp2 = strchr(pszTemp, ',');
//
//	// �Ľ̿� &�� ã�� ���ϸ� ����!
//	if(pszTemp2 == NULL)
//	{
//		return false;
//	}
//
//	*pszTemp2 = '\0';
//	// ID�� 12byte �̻��̸� ����!
//	if(strlen(pszTemp) > 24)
//	{
//		return false;
//	}
//
////	g_pUserInformation->NetmarbleID = szTemp;

//	g_pUserInformation->NetmarbleID = g_CpCookie.c_str();
//	
//	//-------------------------------------------------
//	// Password ����
//	//-------------------------------------------------
//	pszTemp = pszTemp2+1;
//	pszTemp2 = pszTemp+strlen(pszTemp);
//
//	// ID��ŭ ������.
//	pszTemp += info.ID.GetLength();
//
////	pszTemp2 = strchr(pszTemp, ',');
//
//	// �Ľ̿� &�� ã�� ���ϸ� ����!
////	if(pszTemp2 == NULL)
////		return false;
//
//	*pszTemp2 = '\0';
//
//	// ID�� 5byte �����̸� ����!
//	if(strlen(pszTemp) != 14)
//	{
//		return false;
//	}
//
//	switch(HexStringToDec(pszTemp+12))
//	{
//	case 'M':
//	case 'E':
//	case 'T':
//	case 'R':
//	case 'O':
//	case 'C':
//	case 'H':
//		break;
//
//	default:
//		return false;
//	}
//
//	*(pszTemp2-2) = '\0';
//
//	if(pszTemp[0] != 'N' || pszTemp[1] != 'M')
//	{
//		return false;
//	}
//
//	int uniID = HexStringToDec(pszTemp+2);
//	if(uniID == -1)
//	{
//		return false;
//	}
//
//	sprintf(szTemp, "%d", uniID);
//	int skip = 12 - strlen(szTemp);
//	
//	sprintf(szTemp, "NM0000000000");
//	sprintf(szTemp+skip, "%d", uniID);
//	info.Password = szTemp;
//
////	g_pUserInformation->NetmarblePassword = pszTemp;
//	g_pUserInformation->NetmarblePassword = "test";

	return true;
}



/* old version
char* _StrTok(const char* str, const char sep)
{
	// strtok()�� ���� ����� �Լ������� separator�� 1���� �ް�
	// ���ڰ� ����ִ� ��쵵 ���ڷ� ������

	static const int TOK_BUFSIZE = 4096;

	static char* pnow = NULL;
	static char buf[TOK_BUFSIZE];
	static char token[TOK_BUFSIZE];

	if(str) {
		int slen = strlen(str);
		Assert(slen < TOK_BUFSIZE);		// ASSERT

		strcpy(buf, str);
		pnow = buf;
	}

	if(!pnow || *pnow == 0)
		return NULL;

	int tlen = 0;
	char* porg = pnow;
	while(*pnow != 0)
	{
		if(*pnow == sep) {
			++pnow;
			break;
		}

		++tlen;
		++pnow;
	}

	if(tlen > 0) {
		strncpy(token, porg, tlen);
		token[tlen] = 0;
	}
	else {
		token[0] = 0;
	}

	return token;
}
 


BOOL AnalizeArgument(const char *strarg)
{
#ifdef NETMARBLE_DEBUG
	MessageBox(NULL,strarg,strarg,MB_OK);
#endif
	//
	// ���� ���� ��Ģ(������ ���ڴ� �ĸ�(,)�� ���еǸ� ���� ������ ������ ����)
	// ���� ������ ���� : ServerIP,Port,UserID,Pass,Extra (���ڴ� ��ȣȭ�Ǿ� �ִ�)
	// - Extra ���ڴ� �����Ǳ⵵ �Ѵ�
	//

	// arg[0],arg[1],arg[2],arg[2]arg[3]arg[4]
	// 2,10,larosellarosel,larosellaroselNM000076B17852

	// ���ڰ� �ʹ� ��� �ȵȴ�
	if(strlen(strarg) >= 4096)
		return FALSE;

	char key[1024] = {0,};
	char buf[4096] = {0,};

	// ��ȣ �ص� Ű�� ���´�(�ѹ� ������ ������)
	if(!GetCryptKey(key, 1024-1, false)) 
	{
		return FALSE;
	}

	// ��ȣȭ �������� �˻�
	if(CRYPT_SUCCESS != DecryptString(strarg, key, buf))
	{
		return FALSE;
	}

	// -_- netmarble ���� �����ִ� extra �ڵ�� �Ⱦ���.
	char *endchar = strstr(buf,",NM");

	if( endchar != NULL )
		*endchar = NULL;

	buf[ strlen(buf) - 1 ] = '\0';
	
	g_NetmarbleCommandLine = buf;

//	char arg[5][1024] = {0,};
//
//	int argcnt = 0;
//	char* token = _StrTok(buf, ',');
//	while(token && argcnt<5)
//	{
//		strcpy(arg[argcnt], token);
//		argcnt++;
//		token = _StrTok(NULL, ',');
//	}

	// ���ڰ� �ּ��� 4���� �Ǿ�� �Ѵ�
//	if(argcnt < 4)
//		return FALSE;

	// IP�ּҰ� �ùٸ��� �˻�
//	if(strlen(arg[0]) > 16)
//		return FALSE;

	// CP ������ �Ʒ��κ��� ���� ����
//	g_ServIP    = arg[0];		// ���� IP
//	g_ServPort  = (UINT)::atoi(arg[1]);	// ���� Port
//	g_LoginID   = arg[2];		// �α��� ID
//	g_LoginPass = arg[3];		// �α��� �н�����(CP�����̶�� ����ũ �ѹ�)
//	g_Extra     = arg[4];		// ������ ����(CP���ӵ�� ���)
	
	return TRUE;
}
*/
