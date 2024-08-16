//-----------------------------------------------------------------------------
// GameMain.cpp
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include <MMSystem.h>
#include <process.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <direct.h>
#include "Client.h"
#include "UIFunction.h"
//#include "MFileDef.h"
#include "Properties.h"
#include "GameObject.h"
#include "ServerInfo.h"
#include "DebugInfo.h"
#include "PacketDef.h"
#include "SoundNode.h"
#include "AddonDef.h"
#include "UIDialog.h"
#include "MusicDef.h"
#include "MPortal.h"
#include "ServerInformation.h"
#include "UserInformation.h"
#include "TempInformation.h"

#include "COpeningUpdate.h"
#include "CWaitUIUpdate.h"
#include "CWaitPacketUpdate.h"
#include "CGameUpdate.h"
#include "COrderedList.h"
#include "SpriteIDDef.h"
#include "MMusic.h"
#include "CDirectSoundStream.h"
#include "MChatManager.h"
#include "MGameStringTable.h"
#include "MHelpManager.h"
#include "CSoundPartManager.h"
#include "MParty.h"
#include "MZoneSound.h"
#include "MZoneSoundManager.h"
#include "SoundDef.h"
#include "RequestServerPlayerManager.h"
#include "RequestClientPlayerManager.h"
#include "ClientCommunicationManager.h"
#include "RequestUserManager.h"
#include "WhisperManager.h"
#include "RequestFileManager.h"
#include "MJusticeAttackManager.h"
#include "WavePackFileManager.h"
#include "PCConfigTable.h"
#include "Profiler.h"
#include "CMP3.h"
#include "MEventManager.h"
#include "MNpc.h"
#include "packet\Cpackets\CGVerifyTime.h"
#include "UtilityFunction.h"

// 2002.6.28 [UDP����]
#include "packet\Cpackets\CGPortCheck.h"

//#include "MZoneInfo.h"

#include "MWarManager.h"
#include "MTimeItemManager.h"

#include "VS_UI.h"

#include "MGuildType.h"
#include "MFakeCreature.h"

#include "MTestDef.h"
#include "SoundSetting.h"

#include "SXml.h"

//add by zdj 2005.5.17
extern void	ExecuteLogout();
extern BOOL g_MyFull;
extern RECT g_GameRect;
DWORD g_dSHGetTime = 0;
DWORD g_dSHTimerTime = 0;
DWORD g_dSHGetTime1 = 0;
DWORD g_dSHCurrentTime = 0;

int	  g_iSHFakeCount = 0;
bool  g_bCheckHack = true;
#define MAX_INVALID_PROCESS 20
std::string g_strBadProcessList[MAX_INVALID_PROCESS]=
{
	"����",
	"����",
	"fpe",
	"��ɽ����",
	"game master",
	"gameice",
	"gamehack",
	"��Ϸ�޸Ĵ�ʦ",
	"��������",
	"accelerat",
	"wpe",
	"winsock expert",
	"a speeder",
	"����",
	"���",
	"����",
	"ʱ������",
	"ʱ��������׼��",
	"������",
	"flyodbg",
};



#if defined(OUTPUT_DEBUG) && defined(__METROTECH_TEST__)
//	#define OUTPUT_DEBUG_UPDATE_LOOP
#endif

extern BOOL g_bSetHotKey;
extern CSoundPartManager*	g_pSoundManager;


extern bool g_bGoodFPS;


// ����� �����緯 �Ҹ�.. - -;
extern BOOL g_bPlayPropeller;

#ifdef OUTPUT_DEBUG
	extern bool g_bSlideScreenShot;
	extern bool g_bSaveSlideScreenShot;
	extern RECT g_rectScreenShot;
#endif

//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

//-----------------------------------------------------------------------------
// Global
//-----------------------------------------------------------------------------
// mp3
//CMySound*			g_pMP3 = NULL;

// Avi
CAVI				*g_pAvi = NULL;

// Volume ����
IVolume				*g_pMasterVolume = NULL;
IVolume				*g_pWaveVolume = NULL;
DWORD				g_MasterVolumeOriginal = 0;
DWORD				g_WaveVolumeOriginal = 0;

int g_previousSoundID = SOUNDID_NULL;

	
// Sound PartManager
CSoundPartManager*	g_pSoundManager = NULL;

// Cursor Surface
CStorageSurface*	g_pCursorSurface = NULL;

// mouse cursor
POINT				g_SelectSector = { SECTORPOSITION_NULL, SECTORPOSITION_NULL };
BOOL				g_bLButtonDown = FALSE;
BOOL				g_bRButtonDown = FALSE;
BOOL				g_bCButtonDown = FALSE;
BOOL				g_bUIInput		= FALSE;
//Edit by sonic 2006.7.27  �޸ļ��ٵ�ַ
//g_UpdateDelay		= DELAY_UPDATE_GAME

int					g_UpdateDelay		= 0;

// Zone
WORD				g_ZoneCreatureColorSet = 0xFFFF;
WORD				g_MyBatColorSet = 0xFFFF;
bool				g_bZoneSafe = false;
bool				g_bHolyLand = false;
int					g_nZoneLarge = ZONEID_NULL;
int					g_nZoneSmall = ZONEID_NULL;
bool				g_bZoneLargeLoadImage = false;
bool				g_bZoneSmallLoadImage = false;
MZone*				g_pZoneLarge = NULL;				
MZone*				g_pZoneSmall = NULL;
bool				g_bZonePlayerInLarge = true;
DWORD				g_ZoneRandomSoundTime = 0;
bool				g_bWatchMode = false;


// effectManager
MScreenEffectManager*	g_pInventoryEffectManager = NULL;

// DirectDraw
CSpriteSurface*			g_pBack		= NULL;
CSpriteSurface*			g_pLast		= NULL;
int						g_ScreenShotNumber = 0;

CDirectSoundStream*		g_pDXSoundStream = NULL;
CMP3*					g_pMP3 = NULL;
int						g_SoundPerSecond = 0;

// Chat string
#ifdef	OUTPUT_DEBUG
	CMessageArray*		g_pDebugMessage = NULL;
#endif

bool				g_bPutMessage = false;		// ȭ�鿡 debug�޼����� ����ұ�?

bool				g_bNewDraw = false;			// ȭ���� �ٽ� �׷ȴ°�? (Ŀ�� ����)
bool				g_bSmoothCursor = false;	// �ε巯��(?) cursor�� ����� �� �ֳ�?
bool				g_bNetStatusGood = true;		// ��Ʈ�� ���°� ������?

CMessageArray*		g_pSystemMessage = NULL;
CMessageArray*		g_pPlayerMessage = NULL;
CMessageArray*		g_pNoticeMessage = NULL;
CMessageArray*		g_pGameMessage = NULL;

CMessageArray*		g_pHelpMessage = NULL;

// socket
ClientPlayer*		g_pSocket = NULL;

// Thread
MWorkThread*		g_pLoadingThread = NULL;
//HANDLE				g_hFileThread = 0;
//HANDLE				g_hFileEvent;
//THREADJOB			g_ThreadJob;
	

// Server IP
//char				g_ServerIP[80];
bool				g_bFullScreen	= false;
int					g_MaxNPC		= MAX_NPC;
bool				g_bHAL			= true;
bool				g_bMusicSW		= true;
extern int			g_MorphCreatureType;

//--------------------------------------------
// ������ Client Mode�� ���� ����..
//--------------------------------------------
enum CLIENT_MODE	g_Mode = MODE_NULL;
enum CLIENT_MODE	g_ModeNext = MODE_NULL;

CWinUpdate*				g_pUpdate = NULL;

extern MCreature*		AddClientCreature();
extern void Add_GDR_Effect(int nEffect, bool bAppearBossMonster);
extern void Add_GDR_Potal_Effect(int nMapID);
//---------------------------------------------------------------------------
// Update Socket Input
//---------------------------------------------------------------------------
bool
UpdateSocketInput()
{

	//DEBUG_ADD("-PS-");
	
	try {
		
		if (g_pSocket != NULL)
		{
			g_pSocket->processInput();
			g_pSocket->processCommand();
//			g_pSocket->processOutput();
		}

	} catch (Throwable &t) 	{

		if( strstr( t.toString().c_str(), "InvalidProtocolException") != NULL )
		{
			if( !strstr( t.toString().c_str(), "(datagram)" ) == NULL )
				SendBugReport( t.toString().c_str() );
		}
		
		DEBUG_ADD( t.toString().c_str() );
		DEBUG_ADD_ERR("[Error] UpdateSocketInput");			
		DEBUG_ADD(t.toString().c_str());
		
		//InitFail("Server���� ������ ���������ϴ�.");
		SetMode( MODE_MAINMENU );
		UpdateDisconnected();


		return false;
	}


	//----------------------------------------------------------------
	// RequestServerPlayerManager�� ó���Ѵ�.
	//----------------------------------------------------------------
	static DWORD nextTime = g_CurrentTime;

	if (nextTime <= g_CurrentTime)
	{	
		#ifdef OUTPUT_DEBUG_UPDATE_LOOP
			DEBUG_ADD( "RequestUpdate" );
		#endif

		if (g_pRequestUserManager!=NULL)
		{
			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RUM" );
			#endif

			g_pRequestUserManager->Update();

			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RUM ok" );
			#endif
		}

		if (g_pRequestServerPlayerManager!=NULL)
		{
			//int numRequest = g_pRequestServerPlayerManager->GetSize();
			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RSPM" );
			#endif

			g_pRequestServerPlayerManager->Update();

			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RSPM ok" );
			#endif
		}

		if (g_pRequestClientPlayerManager!=NULL)
		{
			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RCPM" );
			#endif

			g_pRequestClientPlayerManager->Update();

			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RCPM ok" );
			#endif
		}

		if (g_pClientCommunicationManager!=NULL)
		{
			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "CCMu" );
			#endif

			g_pClientCommunicationManager->Update();

			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "CCMu ok" );
			#endif
		}

		if (g_pWhisperManager!=NULL)
		{
			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "WMu" );
			#endif

			g_pWhisperManager->Update();

			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "WMu ok" );
			#endif
		}

		if (g_pRequestFileManager!=NULL)
		{
			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RFM" );
			#endif

			g_pRequestFileManager->Update();

			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "RFM ok" );
			#endif
		}

		if (g_pProfileManager!=NULL)
		{
			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "PfM" );
			#endif

			g_pProfileManager->Update();

			#ifdef OUTPUT_DEBUG_UPDATE_LOOP
				DEBUG_ADD( "PfM ok" );
			#endif
		}

		// �ʴ� 3�� update�Ѵ�.
		nextTime = g_CurrentTime + 330;
	}

	//DEBUG_ADD("-OK-");
	

	return true;
}

//---------------------------------------------------------------------------
// Update Socket Output
//---------------------------------------------------------------------------
bool
UpdateSocketOutput()
{

	//DEBUG_ADD("-PS-");
	
	try {
		
		if (g_pSocket != NULL)
		{
			//g_pSocket->processInput();
			//g_pSocket->processCommand();
			g_pSocket->processOutput();
		}

	} catch (Throwable &t) 	{

		if( strstr( t.toString().c_str(), "InvalidProtocolException") != NULL )
			if( !strstr( t.toString().c_str(), "(datagram)" ) == NULL )
				SendBugReport( t.toString().c_str() );
		
		DEBUG_ADD_ERR("[Error] UpdateSocketInput");
		DEBUG_ADD(t.toString().c_str());
		
		//InitFail("Server���� ������ ���������ϴ�.");
		SetMode( MODE_MAINMENU );
		UpdateDisconnected();


		return false;
	}

	// DEBUG_ADD("-OK-");
	
 
	return true;
}

//---------------------------------------------------------------------------
// Check Time
//---------------------------------------------------------------------------
// speedhacküũ�� ���ؼ� 1�и��� �ѹ��� ��Ŷ�� ������.
//---------------------------------------------------------------------------
void
CheckTime()
{
	
	if (g_pSocket!=NULL)
	{
		/*
		static DWORD nextTime = g_CurrentTime + 60000;
		
		//------------------------------------------------------------------
		// 1�� ���� �ѹ��� garbarge packet�� ������.
		//------------------------------------------------------------------
		if (g_CurrentTime > nextTime)		// 60 * 1000
		{
			CGVerifyTime _CGVerifyTime;
			
			g_pSocket->sendPacket( &_CGVerifyTime );					
			
			nextTime = timeGetTime() + 60000;//g_CurrentTime;
			
		}
		*/
		
		
		//���¿�ʼ���ٵļ�鹤��	
		SYSTEMTIME curTime;
		DWORD dTimer;
		
		GetLocalTime(&curTime);
		dTimer = curTime.wHour*1000*60*60 + curTime.wMinute*1000*60 + curTime.wSecond*1000 + curTime.wMilliseconds;
		
		g_dSHCurrentTime = dTimer;
		
		static DWORD nextHackTime = g_dSHCurrentTime + 1000;
		
		if ( (g_dSHCurrentTime > nextHackTime) && g_bCheckHack)
		{
			//������μ��ʱ��Ƭ
			DWORD dCount,dCount1;
			dCount = timeGetTime();
			dCount1 = GetTickCount();
			
			if ((g_dSHGetTime > 0) && (g_dSHGetTime1 > 0))
			{
				if (abs((dCount1 - g_dSHGetTime1) - (dTimer - g_dSHTimerTime)) > 70)
					g_iSHFakeCount ++;
				else if (abs((dCount - g_dSHGetTime) - (dTimer - g_dSHTimerTime)) > 70)
					g_iSHFakeCount ++;
				else
					g_iSHFakeCount = 0;
				
				if (g_iSHFakeCount > 4)
				{
					g_bCheckHack = false;
//					MessageBox(g_hWnd,"��ʹ���˲����ʵ���ҳ���,��������Ͽ�����!",NULL,MB_OK);
//					ExecuteLogout();
					g_bNeedUpdate = TRUE;
					SetMode(MODE_QUIT);
					g_ModeNext = MODE_QUIT;
					g_bCheckHack = true;
				}
			}
			
			g_dSHGetTime = dCount;
			g_dSHGetTime1 = dCount1;
			g_dSHTimerTime = dTimer;
			
			nextHackTime = g_dSHCurrentTime + 1000;
			
			
			//������μ��Ƿ�����
			if (g_bCheckHack)
			{
				HWND hCurrentWindow;
				char szText[255];
				hCurrentWindow = GetWindow(g_hWnd,GW_HWNDFIRST);
				while (hCurrentWindow != NULL)
				{
					if (GetWindowText(hCurrentWindow, szText, 255)>0)
					{
						int iLen = strlen(szText);
						for (int j=0;j<iLen;j++)
						{
							if(isupper(szText[j]) != 0)
								szText[j] = tolower(szText[j]);
						}
						
						std::string strTemp = szText;
						
						if( FindWindow("PROCEXPL", "") != NULL )
						{
								g_bCheckHack = false;
								//yckou
//								abort();
//								MessageBox(g_hWnd,"��ʹ���˲����ʵ���ҳ���,����������Ͽ�����!",NULL,MB_OK);
//								ExecuteLogout();
								g_bNeedUpdate = TRUE;
								SetMode(MODE_QUIT);
								g_ModeNext = MODE_QUIT;
								g_bCheckHack = true;
						}
						
						for (int i=0;i<MAX_INVALID_PROCESS;i++)
						{
							if ((strTemp.find(g_strBadProcessList[i]) != -1) &&
								(strTemp.find("microsoft internet explorer") == -1) &&
								(strTemp.find("myie") == -1) &&
								(strTemp.find("dudu") == -1) &&
								(strTemp.find("����") == -1) )
							{
								g_bCheckHack = false;
								//yckou
//								abort();
//								MessageBox(g_hWnd,"��ʹ���˲����ʵ���ҳ���,����������Ͽ�����!",NULL,MB_OK);
//								ExecuteLogout();
								g_bNeedUpdate = TRUE;
								SetMode(MODE_QUIT);
								g_ModeNext = MODE_QUIT;
								g_bCheckHack = true;
							}

						}
					}
					hCurrentWindow = GetWindow(hCurrentWindow, GW_HWNDNEXT);
				}
			}
		}
	}
}

//���Ƿ����� yckou
bool CheckInvalidProcess()
{
	//������μ��Ƿ�����
	if (g_bCheckHack)
	{
		HWND hCurrentWindow;
		char szText[255];
		hCurrentWindow = GetWindow(g_hWnd,GW_HWNDFIRST);
		while (hCurrentWindow != NULL)
		{
			if (GetWindowText(hCurrentWindow, szText, 255)>0)
			{
				int iLen = strlen(szText);
				for (int j=0;j<iLen;j++)
				{
					if(isupper(szText[j]) != 0)
						szText[j] = tolower(szText[j]);
				}
				
				std::string strTemp = szText;
				
				for (int i=0;i<MAX_INVALID_PROCESS;i++)
				{
					if ((strTemp.find(g_strBadProcessList[i]) != -1) &&
						(strTemp.find("microsoft internet explorer") == -1) &&
						(strTemp.find("myie") == -1) &&
						(strTemp.find("dudu") == -1) &&
						(strTemp.find("����") == -1) )
					{
						g_bCheckHack = false;
//						MessageBox(g_hWnd,"��ʹ���˲����ʵ���ҳ���,����������Ͽ�����!",NULL,MB_OK);
//						ExecuteLogout();
//						abort();
						// client�� update�ؾ��Ѵ�.
						g_bNeedUpdate = TRUE;
						SetMode(MODE_QUIT);
						g_ModeNext = MODE_QUIT;
						g_bCheckHack = true;
						return false;
					}
				}
			}
			hCurrentWindow = GetWindow(hCurrentWindow, GW_HWNDNEXT);
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Client�� ���� Mode�� �����Ѵ�.
//-----------------------------------------------------------------------------
// game ���� ����� 
// UI�� mode������ ó���Ѵ�.
//
// (!)�ٸ� ��~������ game���º����̳� UI mode������ ó������ �ʵ��� �ؾ��Ѵ�.
//-----------------------------------------------------------------------------
void		
SetMode(enum CLIENT_MODE mode)
{
	g_Mode = mode;

	// �Է��� �ʱ�ȭ�Ѵ�.
	if (g_pDXInput!=NULL)
	{
		g_pDXInput->UpdateInput();
		g_pDXInput->Clear();
	
		// acquire
		g_pDXInput->SetAcquire(true);			
		
		// �Է��� �ʱ�ȭ�Ѵ�.
		g_pDXInput->Clear();
	}

	g_bLButtonDown = FALSE;
	g_bRButtonDown = FALSE;
	g_bCButtonDown = FALSE;


	switch (g_Mode)
	{
		//------------------------------------------------------
		// �ʱ� ȭ��
		//------------------------------------------------------
		case MODE_OPENING :
			// Debug Message
			DEBUG_ADD("[ SetMode ]  OPENING");
			
			UnInitSound();		// ��� Sound ����

			g_pCOpeningUpdate->PlayMPG("test.mpg");

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_pUpdate = g_pCOpeningUpdate;
			g_pCOpeningUpdate->Init();
		break;

		//------------------------------------------------------
		// ���� option�� �ٲ۴�. - -;
		//------------------------------------------------------
		case MODE_CHANGE_OPTION :			
			if (// 3D���� ���ε�.. ���� ���� ���
				CDirect3D::IsHAL() && !g_pUserOption->Use3DHAL
				// 3D���� �ƴѵ�.. ���� �ϴ� ���
				|| !CDirect3D::IsHAL() && g_pUserOption->Use3DHAL)
			{
				//if (g_pTopView!=NULL)
				{
				//	delete g_pTopView;//->Release();
				//	g_pTopView = NULL;
				}			
				//--------------------------------------------------
				// ���� �����.
				//--------------------------------------------------
				if (g_pUserOption->PlayWaveMusic)
				{
#ifdef __USE_MP3__
					DEBUG_ADD("MP3 STOP1");
					g_pMP3->Stop();
					DEBUG_ADD("MP3 STOP1 OK");
//					g_pDXSoundStream->Stop();
#else
					if( g_DXSound.IsInit() )
						g_pOGG->streamClose();
#endif
				}
				else
				{
					g_Music.Stop();
				}


				if (CDirect3D::IsHAL())
				{
					CDirect3D::Release();
				}

				CDirectDraw::RestoreGammaRamp();
				CDirectDraw::ReleaseAll();

				InitDraw();
				InitSurface();
				
				//-----------------------------------------------------------------
				// ��� ��ٷ� �޶�� ���..
				//-----------------------------------------------------------------
				g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[STRING_MESSAGE_WAIT].GetString(), -1, -1, 0 );
				
				gC_vs_ui.Process();
				gC_vs_ui.Show();

//				if (CDirect3D::IsHAL())
//				{
//				}
//				else
				{
					//-----------------------------------------------------------------
					// Last�� Back���� copy - 3D HAL�� �ƴ� ��츸..
					//-----------------------------------------------------------------
					POINT point = { 0, 0 };
					RECT rect = { 0, 0, g_GameRect.right, g_GameRect.bottom };

					g_pBack->BltNoColorkey( &point, g_pLast, &rect );	
				}

				CDirectDraw::Flip();

				//-----------------------------------------------------------------
				// g_pTopView : 2D <--> 3D �ٲ�..
				//-----------------------------------------------------------------
				if (g_pTopView!=NULL)
				{
					g_pTopView->InitChanges();
				}
				
				g_pUIDialog->CloseMessageDlg();
			}			

			// �ٷ� ������ MAINMENU��.. - -;
			SetMode( MODE_MAINMENU );
		break;

		//------------------------------------------------------
		// Login ���� ����..
		//------------------------------------------------------
		case MODE_MAINMENU :
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MAINMENU");
			
			// acquire
			g_pDXInput->SetAcquire(g_bActiveGame==TRUE);


			//------------------------------------------------------
			// Socket ����..
			//------------------------------------------------------
			if(NULL == g_pUserInformation->pLogInClientPlayer &&
				true == g_pUserInformation->IsAutoLogIn)// �� �α��̰� �ѹ��� �α��� ���� �ʾ������
				ReleaseSocket();


			//------------------------------------------------------
			// [ TEST CODE ]
			// ���⼭ sound�� �ʱ�ȭ�ص� �ǳ�??
			//------------------------------------------------------
			InitSound();			

			g_CurrentFrame		= 0;

			g_bSetHotKey	= FALSE;

			//------------------------------------------------------
			// ui dialog
			//------------------------------------------------------
			g_pUIDialog->HidePCTalkDlg();


			//------------------------------------------------------
			// ��� ��ȭ ���
			//------------------------------------------------------
			g_pChatManager->ClearID();
			g_pChatManager->SetAcceptMode();

			// Titleȭ�� UI����
			//gC_vs_ui.EndTitle();
			gC_vs_ui.StartTitle();	
		
			gC_vs_ui.DropItem();

			g_bUIInput = FALSE;			

			// �ӼӸ� �� ��������... �� -- ;
			if (g_pUserInformation!=NULL)
			{
				// �ӼӸ� ����� �����ش�.
				g_pUserInformation->WhisperID.Release();

				g_pUserInformation->CharacterID.Release();
			}

			//----------------------------------------------
			// message ����
			//----------------------------------------------
			g_pSystemMessage->Clear();
			g_pPlayerMessage->Clear();
			g_pGameMessage->Clear();
			g_pNoticeMessage->Clear();

			//UpdateDisconnected();

			//------------------------------------------------------
			// ���� ����
			//------------------------------------------------------
			if (g_pUserOption->PlayWaveMusic)
			{
//				g_pDXSoundStream->Stop();
				DEBUG_ADD("MP3 STOP2");
#ifdef __USE_MP3__
				g_pMP3->Stop();
#else
				
				if( g_DXSound.IsInit() )
				{
					if( g_pSoundBufferForOGG == NULL )
						g_pSoundBufferForOGG = new CDirectSoundBuffer(g_hWnd, SOUND_STEREO, SOUND_44K, SOUND_16BIT);

					if( g_pOGG == NULL )
#ifdef _MT
						g_pOGG = new COGGSTREAM(g_hWnd, g_pSoundBufferForOGG, 44100, 11025, 8800);
#else
						g_pOGG = new COGGSTREAM(g_hWnd, g_pSoundBufferForOGG, 44100, 11025, 8800,1);
#endif						

					g_pOGG->streamClose();
				}
#endif
				DEBUG_ADD("MP3 STOP2 OK");

				if (g_pUserOption->PlayMusic)
				{
					int musicID = g_pClientConfig->MUSIC_THEME;

					if (musicID!=MUSICID_NULL)
					{
#ifdef __USE_MP3__
						DEBUG_ADD("MP3 OPEM");
						g_pMP3->Open( (*g_pMusicTable)[ musicID ].FilenameWav );
						DEBUG_ADD("MP3 OPEM OK");
						DEBUG_ADD("MP3 PLAY1");
						g_pMP3->Play( false );
						DEBUG_ADD("MP3 PLAY1 OK");
//						g_pDXSoundStream->Load( (*g_pMusicTable)[ musicID ].FilenameWav );
//						g_pDXSoundStream->Play( FALSE );
#else
						if( g_oggfile != NULL )
							fclose(g_oggfile);

						g_oggfile = NULL;
						
						if( g_DXSound.IsInit() )
						{
							g_oggfile = fopen( (*g_pMusicTable)[ musicID ].FilenameWav ,"rb");
							g_pOGG->streamLoad( g_oggfile, NULL );
							g_pOGG->streamPlay(SOUND_PLAY_ONCE);
							int volume = (g_pUserOption->VolumeMusic - 15) * 250;
							g_pOGG->streamVolume( max( -10000, min( -1, volume ) ) );
						}
#endif
					}
				}
			}
			else
			{
				g_Music.Stop();

				if (g_pUserOption->PlayMusic)
				{
					int musicID = g_pClientConfig->MUSIC_THEME;

					if (musicID!=MUSICID_NULL)
					{
						g_Music.Play( (*g_pMusicTable)[ musicID ].Filename );
					}
				}
			}

			//g_pDXSoundStream->Load( "music.wav" );//(*g_pMusicTable)[ g_pClientConfig->MUSIC_THEME ].Filename );
			//g_pDXSoundStream->Play(TRUE);

			//g_DXMusic.SetOriginalTempo();
			//g_DXMusic.Stop();			

			//g_DXMusic.Play( (*g_pMusicTable)[ g_pClientConfig->MUSIC_THEME ].Filename );
		
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_LOGIN;	
			g_pUpdate = g_pCWaitUIUpdate;
			g_pCWaitUIUpdate->Init();
		break;

		//------------------------------------------------------
		// PC�� �����ϱ� ���� ������ ��ٸ���.
		//------------------------------------------------------
		case MODE_NEWUSER :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_NEWUSER");
			
			//----------------------------------------------
			// Player�� ���� �ʱ�ȭ
			//----------------------------------------------
			//g_pPlayer->SetCreatureType( 0 );			
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_LOGIN;	
			g_pUpdate = g_pCWaitUIUpdate;
			g_pCWaitUIUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// Login�� �����Ǳ⸦ ��ٸ���.
		//------------------------------------------------------
		// (ID, Password)�� ������
		// Login�� ���� �Ǳ⸦ ��ٸ���.
		//------------------------------------------------------
		case MODE_WAIT_LOGINOK :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_LOGINOK");
			
			//------------------------------------------------------
			// Loading ����
			//------------------------------------------------------
			//StopFileThread();

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;			
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );			
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// MODE_WAIT_WORLD_LIST
		//------------------------------------------------------
		case MODE_WAIT_WORLD_LIST :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_WORLD_LIST");

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;			
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );			
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// MODE_WAIT_SELECT_WORLD
		//------------------------------------------------------
		case MODE_WAIT_SELECT_WORLD :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_SELECT_WORLD");

			g_pUserInformation->KeepConnection = FALSE;			

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_LOGIN;	
			g_pUpdate = g_pCWaitUIUpdate;
			g_pCWaitUIUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// MODE_WAIT_SERVER_LIST
		//------------------------------------------------------
		case MODE_WAIT_SERVER_LIST :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_SERVER_LIST");
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;			
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );			
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// MODE_WAIT_SELECT_SERVER
		//------------------------------------------------------
		case MODE_WAIT_SELECT_SERVER :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_SELECT_SERVER");

			g_pUserInformation->KeepConnection = FALSE;			

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_LOGIN;	
			g_pUpdate = g_pCWaitUIUpdate;
			g_pCWaitUIUpdate->Init();
		}
		break;

		
		//------------------------------------------------------
		// �߸� �Է��� ����̴�.
		//------------------------------------------------------
		case MODE_LOGIN_WRONG :
		{
			//gC_vs_ui.InvalidIdPasswordMessage();

			/*
			//InitFail("Server�� �������� �ʽ��ϴ�.");
			//InitFail("Server���� ������ ���������ϴ�.");
			g_pBack->GDI_Text(101,201, "ID�� Password�� Ʋ�Ƚ��ϴ�.", RGB(0,0,0));
			g_pBack->GDI_Text(100,200, "ID�� Password�� Ʋ�Ƚ��ϴ�.", RGB(220,220,220));

			g_pBack->GDI_Text(101,221, "[ESC]�� ��������.", RGB(0,0,0));
			g_pBack->GDI_Text(100,220, "[ESC]�� ��������.", RGB(220,220,220));

			CDirectDraw::Flip();

			// return�� ���� ������...
			while (1)
			{
				UpdateInput();
				
				if (g_pDXInput->KeyDown(DIK_ESCAPE))
				{
					break;
				}
			}
			*/
			
			// �ٽ� mainmenu��..

			g_Mode = MODE_MAINMENU;

			//-----------------------
			// Socket ����..
			//-----------------------
			ReleaseSocket();

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_LOGIN;	
			g_pUpdate = g_pCWaitUIUpdate;
			g_pCWaitUIUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// Register�Ǳ⸦ ��ٸ���.
		//------------------------------------------------------		
		case MODE_WAIT_REGISTERPLAYEROK :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_REGISTERPLAYEROK");
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;			
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// PC�� �����ϱ� ���� ������ ��ٸ���.
		//------------------------------------------------------
		case MODE_WAIT_PCLIST :
		{			
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_PCLIST");				
			
			//------------------------------------------------------------
			// Characer ���� â�� ����� �Ѵ�.
			//------------------------------------------------------------
			// LCPCListHandler���� �ϰ� �ߴ�.
			//UI_StartCharacterManager();				

			g_ZoneRandomSoundTime = g_CurrentTime;

			//------------------------------------------------------------
			// server name ����
			//------------------------------------------------------------
			/*
			int serverID = g_pServerInformation->GetServerGroupID();
			int status = g_pServerInformation->GetServerGroupStatus();

			char str[80];

			if (g_pServerInformation->GetServerGroupName()!=NULL)
			{
				strcpy(str, g_pServerInformation->GetServerGroupName());

				//gC_vs_ui.SetServerName( str );
				DEBUG_ADD_FORMAT("[ SetMode ]  MODE_WAIT_PCLIST - ServerName[%d]=%s", serverID, str);
			}
			
//			gC_vs_ui.SetServerDefault( str, serverID, (C_VS_UI_CHAR_MANAGER::SERVER_STATUS)status );

//			gC_vs_ui.CharManagerDisable();
			*/

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;		
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// PC�� �����ϱ� ���� ������ ��ٸ���.
		//------------------------------------------------------
		case MODE_WAIT_SELECTPC :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_SELECTPC");
			
			//----------------------------------------------
			// Player�� ���� �ʱ�ȭ
			//----------------------------------------------
			//g_pPlayer->SetCreatureType( 0 );	
			g_pUserInformation->KeepConnection = FALSE;
			
//			gC_vs_ui.CharManagerEnable();

			SelectLastSelectedCharacter();

			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_MorphCreatureType = 0;
			g_UpdateDelay = DELAY_UPDATE_LOGIN;	
			g_pUpdate = g_pCWaitUIUpdate;
			g_pCWaitUIUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// PC�� ����� �����Ǿ���?
		//------------------------------------------------------
		case MODE_WAIT_CREATEPCOK :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_CREATEPCOK");
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;		
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// PC�� ����� �����Ǿ���?
		//------------------------------------------------------
		case MODE_WAIT_DELETEPCOK :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_DELETEPCOK");
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;		
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// GameServer�� �����ϱ� ���ؼ�...
		//------------------------------------------------------
		case MODE_WAIT_RECONNECT :
		{				
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_RECONNECT");
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;		
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// GameServer���� LoginServer�� �������ϱ� ���ؼ�...
		//------------------------------------------------------
		case MODE_WAIT_RECONNECT_LOGIN :
		{				
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_RECONNECT_LOGIN");

			// �ӼӸ� �� ��������... �� -- ;
			if (g_pUserInformation!=NULL)
			{
				g_pUserInformation->CharacterID.Release();
			}
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;		
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// UpdateInfo�� �޴´�.
		//------------------------------------------------------
		case MODE_WAIT_UPDATEINFO :
		{	
			//--------------------------------------------------
			// Player �ʱ�ȭ
			//--------------------------------------------------
			if (g_pPlayer!=NULL)
			{
				if (g_pZone!=NULL)
				{
					g_pZone->RemoveCreature( g_pPlayer->GetID() );
				}
				
				delete g_pPlayer;//->SetSpecialActionInfoNULL();
				g_pPlayer = NULL;
			}

			//--------------------------------------------------
			// ������� �ʱ�ȭ
			//--------------------------------------------------
			g_pJusticeAttackManager->Release();

			//--------------------------------------------------
			//
			// Skill Tree �ʱ�ȭ - �ӽ÷�.. - -;;
			//
			//--------------------------------------------------
			g_pSkillManager->Init();

			//------------------------------
			// ���� UI �� �����Ѵ�.
			//------------------------------
			UI_SetCharInfoName(g_pUserInformation->CharacterID);
			DEBUG_ADD("[ SetMode ] SET CHARINFO");
			UI_StartGame();

			DEBUG_ADD("[ SetMode ] UI FINISH");

			g_ZoneRandomSoundTime = g_CurrentTime;

			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_UPDATEINFO");
			
			//----------------------------------------------
			// update �Լ� ����
			//----------------------------------------------
			g_UpdateDelay = DELAY_UPDATE_WAITING;		
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();			
		}
		break;

		//------------------------------------------------------
		// Player�� ��ǥ�� �ޱ� ���ؼ� ��ٸ���.
		//------------------------------------------------------
		case MODE_WAIT_SETPOSITION :
		{
			// Debug Message
			DEBUG_ADD("[ SetMode ]  MODE_WAIT_SETPOSITION");
			
			//--------------------------------------------------
			// Option ����
			//--------------------------------------------------
			if (g_pUserOption!=NULL)
			{
				g_pUserOption->SaveToFile( g_pFileDef->getProperty("FILE_INFO_USEROPTION").c_str());
			}
			
			// ����..
			g_pPlayer->SetStop();
			g_pPlayer->SetAction( ACTION_STAND );

			// Ű �Է� ����
			g_pDXInput->Clear();

			g_bLButtonDown = FALSE;
			g_bRButtonDown = FALSE;
			g_bCButtonDown = FALSE;

			// [ TEST CODE ]
			InitSound();

			static int first = 1;
			if (first)
			{
				g_pSystemMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_HELP_KEY].GetString());
				first = 0;
			}

			//--------------------------------------------------
			// ���� ������ CGReady ��Ŷ�� ������.
			//--------------------------------------------------
				CGReady cgReady;
				g_pSocket->sendPacket( &cgReady );
				g_pSocket->setPlayerStatus( CPS_WAITING_FOR_GC_SET_POSITION );

				// �ٷ� ������.
				UpdateSocketOutput();

				// 2002.6.28 [UDP����]
				// ������ UDP port�� �˷��ֱ� ���ؼ�
//				CGPortCheck cgPortCheck;
//				cgPortCheck.setPCName( g_pUserInformation->CharacterID.GetString() );
//				
//				string ServerAddress = g_pConfig->getProperty("LoginServerAddress");
//				uint ServerPort = g_pConfig->getPropertyInt("LoginServerCheckPort");
//
//				g_pClientCommunicationManager->sendPacket( ServerAddress,
//															ServerPort,
//															&cgPortCheck );

			//
			g_SelectSector.x = 0;
			g_SelectSector.y = 0;


			if (g_pTopView!=NULL)
			{
				g_pTopView->ClearShadowManager();
						
				g_pTopView->SetSelectedNULL();
			}
		
			// update �Լ�
			g_UpdateDelay = DELAY_UPDATE_WAITING;			
			g_pUpdate = g_pCWaitPacketUpdate;
			g_pCWaitPacketUpdate->SetDelay( g_pClientConfig->MAX_WAIT_PACKET );
			g_pCWaitPacketUpdate->Init();
		}
		break;

		//------------------------------------------------------
		// ������ �����Ѵ�.
		//------------------------------------------------------
		case MODE_GAME :
			DEBUG_ADD("---------- Start Game ---------- ");
			
			DEBUG_ADD("CDirectDraw::RestoreAllSurfaces()");
			CDirectDraw::RestoreAllSurfaces();

			DEBUG_ADD("CDirect3D::Restore()");
			CDirect3D::Restore();

			DEBUG_ADD("TempInformation");

			//-----------------------------------------------------------
			// temp information����
			//-----------------------------------------------------------
			g_pTempInformation->SetMode(TempInformation::MODE_NULL);

			DEBUG_ADD("UserInformation");
			//-----------------------------------------------------------
			// Logout �ð� ����
			//-----------------------------------------------------------
			g_pUserInformation->LogoutTime = 0;
		
			//-----------------------------------------------------------
			// hot key�� �����Ѵ�.
			//-----------------------------------------------------------
			DEBUG_ADD("SaveHotKey");
			UI_SaveHotKeyToServer();			

			//-----------------------------------------
			// Button �ʱ�ȭ
			//-----------------------------------------
			g_bLButtonDown = FALSE;
			g_bRButtonDown = FALSE;
			g_bCButtonDown = FALSE;

			//-----------------------------------------
			// UI Dialog���� �Է� ������ Ǯ����..
			//-----------------------------------------
			DEBUG_ADD("UIDialog");
			UIDialog::UnSetLockInputPCTalk();
			UIDialog::UnSetLockInputMessage();

			// ��Ȱ ��ư ���ֱ�
			// �̰Ŵ� GCUpdateInfoHandler���� �ؾ��ϴµ�.. �ϴ�. - -;
			DEBUG_ADD("FinishRequestDie");
			gC_vs_ui.FinishRequestDie();
			gC_vs_ui.FinishRequestResurrect();
			gC_vs_ui.CloseRequestShrineMinimap();


//			//-----------------------------------------
//			// ��ũ ����..
//			//-----------------------------------------
//			if (g_pPlayer!=NULL
//				&& g_pPlayer->IsSlayer()
//				&& g_pInventory!=NULL
//				&& g_pSlayerGear!=NULL
//				&& g_pPlayer->GetSTR()+g_pPlayer->GetDEX()+g_pPlayer->GetINT()==30
//				&& g_pInventory->GetItemNum()==0
//				&& g_pSlayerGear->GetItemNum()==0)
//			{
//				gC_vs_ui.AddChatToHistory((*g_pGameStringTable)[STRING_MESSAGE_HOW_TO_GET_BASIC_WEAPON].GetString(), 
//											(*g_pGameStringTable)[UI_STRING_MESSAGE_HELP_MESSAGE].GetString(), 
//											CLD_INFO, RGB(130, 230, 230));
//			}
//Edit by sonic 2006.7.27  �޸ļ��ٵ�ַ
			//g_UpdateDelay = DELAY_UPDATE_GAME;
			g_UpdateDelay = 100 ^ 90;
			
			DEBUG_ADD("SetUpdate");
			g_pUpdate = g_pCGameUpdate;
			g_pCGameUpdate->Init();
			
			ExecuteHelpEvent( HELP_EVENT_INTERFACE );
//			if(!g_pUserInformation->IsNetmarble)
//			{
//				ExecuteHelpEvent( HELP_EVENT_CAMPAIGN );
//				ExecuteHelpEvent( HELP_EVENT_EVENT );
//			}

		break;

		
		//------------------------------------------------------
		// Program�� ������.
		//------------------------------------------------------
		case MODE_QUIT :
			// Logout�� ������.
				if (g_pSocket!=NULL)
				{
					//--------------------------------------------------
					// update�ҷ��� �����ϴ� ���� CLLogout�� ������.
					//--------------------------------------------------
					if (g_bNeedUpdate)
					{
						//--------------------------------------------------
						// Login ������ CLLogout ��Ŷ�� ������.
						//--------------------------------------------------
							CLLogout clLogout;
						
							g_pSocket->sendPacket( &clLogout );
							//g_pSocket->setPlayerStatus( CPS_END_SESSION );

					}
					//--------------------------------------------------
					// game�߿� �����ϴ� ���.. CG Logout
					//--------------------------------------------------
					else
					{
						CGLogout cgLogout;
					
						g_pSocket->sendPacket( &cgLogout );

						#ifdef __DEBUG_OUTPUT__
							DEBUG_ADD(cgLogout.toString().c_str());					
						#endif
					}
				}

			//--------------------------------------------------
			// Thread Loading ����..
			//--------------------------------------------------
			StopLoadingThread();

			// Update�Լ� ����
			g_pUpdate = NULL;

			g_bUIInput = FALSE;

			// window �ݱ�
			g_bActiveApp = FALSE;
			PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		break;
	}

	// �Է��� �ʱ�ȭ�Ѵ�.
	g_pDXInput->Clear();
}

//-----------------------------------------------------------------------------
// Check Activate
//-----------------------------------------------------------------------------
// ���α׷��� ���������� �ƴ����� ���� ó��..
// ALT + TAB �� ������ ���. - -;
//-----------------------------------------------------------------------------
void
CheckActivate(BOOL bActiveGame)
{
	//static BOOL musicPause = FALSE; //g_Music.IsPause();

	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage != NULL)
		{
			if (bActiveGame)
			{
				if (g_bActiveApp)
				{
					DEBUG_ADD("[CheckActivate] ActiveGame, ActiveApp");
				}
				else
				{
					DEBUG_ADD("[CheckActivate] ActiveGame, DeactiveApp");
				}
			}
			else
			{
				if (g_bActiveApp)
				{
					DEBUG_ADD("[CheckActivate] DeactiveGame, ActiveApp");
				}
				else
				{
					DEBUG_ADD("[CheckActivate] DeactiveGame, DeactiveApp");
				}
			}
		}
	#endif

	if (g_pDXInput!=NULL)
	{
		// acquire
		g_pDXInput->SetAcquire(bActiveGame==TRUE);			
		
		// �Է��� �ʱ�ȭ�Ѵ�.
		g_pDXInput->Clear();
	}
	
	//----------------------------------------------------
	// ���α׷� ����..
	//----------------------------------------------------
	g_bActiveGame = FALSE;

	extern bool	g_bTestMode;
	if (g_bActiveApp
#ifdef OUTPUT_DEBUG
		|| g_bTestMode
#endif
		)
	{
		//CDirectDraw::RestoreAllSurfaces();
		
		CDirectDraw::RestoreGammaRamp();

		if (bActiveGame)
		{
			CDirectDraw::RestoreAllSurfaces();

			DEBUG_ADD("WM_ACTIVATEAPP : Restore Surfaces");
			

			//----------------------------------------------------
			// global setting
			//----------------------------------------------------
			g_bActiveGame = TRUE;

			if (CDirect3D::IsHAL())
			{
				//CDirect3D::Restore();

				DEBUG_ADD("IsHAL : Before CDirect3D::Release()");
				
				CDirect3D::Release();

				DEBUG_ADD("IsHAL : Before CDirect3D::Init()");
				
				CDirect3D::Init();		// �ٽ�... 

				
				DEBUG_ADD("IsHAL : Before CDirect3D::Restore()");
				
				CDirect3D::Restore();
			}

			if (g_bFullScreen)
			{				
				DEBUG_ADD("FullScreen : Before DD::SetDisplayMode()");
				if(g_MyFull)
				{
					CDirectDraw::GetDD()->SetDisplayMode(1024, 768, 16, 0, 0);
				}
				else
				{
					CDirectDraw::GetDD()->SetDisplayMode(800, 600, 16, 0, 0);
				}
				// end
			}

			DEBUG_ADD("Before Restore All Surfaces");
			
			CDirectDraw::RestoreAllSurfaces();
			
			DEBUG_ADD("Before Restore");
			
			CDirect3D::Restore();
			
			DEBUG_ADD("if g_pTopView");
			
			if (g_pTopView!=NULL && g_pTopView->IsInit())
			{
				DEBUG_ADD("Before g_pTopView->RestoreSurface");
				
				g_pTopView->RestoreSurface();
				
				DEBUG_ADD("After g_pTopView->RestoreSurface");
				
				g_pTopView->SetFirstDraw();
			}

			//--------------------------------------------------------
			// ������ �� ����
			//--------------------------------------------------------
			if (g_pUserOption!=NULL
				&& g_pClientConfig!=NULL)				
			{
				if (g_pUserOption->UseGammaControl
					&& g_pUserOption->GammaValue!=100)
				{
					CDirectDraw::SetGammaRamp( g_pUserOption->GammaValue );
				}
				
				//------------------------------------
				// �������̸�.. �ߴ�..
				//------------------------------------
				if (g_pUserOption->PlayMusic)
				{
					if (g_pUserOption->PlayWaveMusic)
					{
						if (g_Mode==MODE_GAME)
						{													
							PlayMusicCurrentZone();
						}
						else
						{
							int musicID = g_pClientConfig->MUSIC_THEME;

							if (musicID!=MUSICID_NULL
#ifdef __USE_MP3__
								&& g_pMP3 != NULL)
#else
								&& g_pOGG != NULL)
#endif
//								&& g_pDXSoundStream!=NULL)
							{
#ifdef __USE_MP3__
								DEBUG_ADD("MP3 OPEM");
								g_pMP3->Open( (*g_pMusicTable)[ musicID ].FilenameWav );
								DEBUG_ADD("MP3 OPEM OK");
								DEBUG_ADD("MP3 PLAY2");
								g_pMP3->Play( false );
								DEBUG_ADD("MP3 PLAY2 OK");
//								g_pDXSoundStream->Load( (*g_pMusicTable)[ musicID ].FilenameWav );
//								g_pDXSoundStream->Play( FALSE );
#else
								if( g_DXSound.IsInit() )
								{
									g_pOGG->streamClose();
									if( g_oggfile != NULL )
										fclose(g_oggfile);
									g_oggfile = fopen( (*g_pMusicTable)[ musicID ].FilenameWav ,"rb");
									if( g_oggfile != NULL )
									{
										g_pOGG->streamLoad( g_oggfile, NULL );
										g_pOGG->streamPlay(SOUND_PLAY_ONCE);
										int volume = (g_pUserOption->VolumeMusic - 15) * 250;
										g_pOGG->streamVolume( max( -10000, min( -1, volume ) ) );
									}
								}
#endif
							}
						}
					}
					else
					{
						if (g_Music.IsPlay())
						{
							g_Music.Resume();
						}
						else if (g_Mode==MODE_GAME)
						{													
							PlayMusicCurrentZone();
						}
						else
						{
							int musicID = g_pClientConfig->MUSIC_THEME;

							if (musicID!=MUSICID_NULL
								&& g_pMusicTable!=NULL)
							{
								g_Music.Play( (*g_pMusicTable)[ musicID ].Filename );
							}
						}
					}
				}
				//------------------------------------
				// �������� �ƴ� ���
				//------------------------------------
				else
				{
					// nothing - -;
				}
			}

			if (g_Mode!=MODE_WAIT_UPDATEINFO)
			{
				g_DXSound.UnSetMute();
			}

			//--------------------------------
			// mouse ��ư ���� ���� ����
			//--------------------------------
			g_bLButtonDown = FALSE;
			g_bRButtonDown = FALSE;
			g_bCButtonDown = FALSE;

			if (g_pPlayer!=NULL)
			{
				g_pPlayer->UnSetLockMode();
			}

			
			// UI���� alt+tabó��
			DEBUG_ADD("UI_RestoreWhenActivateGame");

			gC_vs_ui.RestoreWhenActivateGame();

			DEBUG_ADD("UI_Restore_ok");
		}
		//----------------------------------------------------
		// ����..
		//----------------------------------------------------
		else
		{
			if (g_bFullScreen)
			{
				//CDirectDraw::RestoreGammaRamp();
				CDirectDraw::GetDD()->RestoreDisplayMode();
				//CDirectDraw::RestoreGammaRamp();
			}

			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage != NULL)
					DEBUG_ADD("WM_ACTIVATEAPP : Stop Music");
			#endif
			//g_DXMusic.Pause();
			//musicPause = g_Music.IsPause();

			if (g_pUserOption->PlayWaveMusic)
			{
#ifdef __USE_MP3__
				if (g_pMP3 != NULL)
				{
					DEBUG_ADD("MP3 STOP3");
					g_pMP3->Stop();
					DEBUG_ADD("MP3 STOP3 OK");
				}
//				if (g_pDXSoundStream!=NULL)
//				{
//					g_pDXSoundStream->Stop();
//				}
#else
				if( g_pOGG != NULL )
				{
					if( g_DXSound.IsInit() )
						g_pOGG->streamClose();
				}
#endif
			}
			else
			{
				g_Music.Stop();
			}
			
			if (g_Mode!=MODE_WAIT_UPDATEINFO)
			{
				g_DXSound.SetMute();			
			}
			
			// �ݺ� ���� ����
			if (g_pPlayer!=NULL)
			{
				g_pPlayer->UnSetRepeatAction();
			}
		}
	}

}

//-----------------------------------------------------------------------------
// File Thread Proc
//-----------------------------------------------------------------------------
/*
LONG
FileThreadProc(LPVOID lpParameter)
{
	class ifstream file;

	while ( 1 )
	{		
		WaitForSingleObject(g_hFileEvent, INFINITE);

		#ifdef OUTPUT_DEBUG
			//		DEBUG_ADD("[Thread Job] Start");
		#endif
	
		bool bLoad = true;
			
		switch (g_ThreadJob)
		{
			//--------------------------------------------------------
			// Large Zone�� ImageObject�� Loading�Ѵ�.
			//--------------------------------------------------------
			case THREADJOB_LOAD_IMAGEOBJECT_LARGEZONE :	
				g_bZoneLargeLoadImage = false;
				file.open((*g_pZoneTable).Get(g_nZoneLarge)->Filename, ios::binary);

				// Tile Loading
				if (g_ThreadJob==THREADJOB_LOAD_IMAGEOBJECT_LARGEZONE)
				{
					#ifdef OUTPUT_DEBUG
						//DEBUG_ADD("[Thread Job] Load Tile LargeZone");
					#endif
					file.seekg(g_pZone->GetTileFilePosition(), ios::beg);
					if (!g_pTopView->LoadFromFileTileSPKLargeZone( file ))	// tile�� load
					{
						#ifdef OUTPUT_DEBUG
						//		DEBUG_ADD("[Thread Job] Stop Loading Tile");
						#endif
						file.close();
						break;
					}
				}
			
				// ImageObject Loading
				if (bLoad && g_ThreadJob==THREADJOB_LOAD_IMAGEOBJECT_LARGEZONE)
				{
					#ifdef OUTPUT_DEBUG
						//	DEBUG_ADD("[Thread Job] Load Imageobject LargeZone");
					#endif
					file.seekg(g_pZone->GetImageObjectFilePosition(), ios::beg);				
					// ��� load�� ����̸�..
					if (g_pTopView->LoadFromFileImageObjectSPKLargeZone( file ))
					{
						#ifdef OUTPUT_DEBUG
							//	DEBUG_ADD("[Thread Job] Stop Loading ImageObject");
						#endif
						file.close();
						break;
					}
				}

				if (bLoad && g_ThreadJob==THREADJOB_LOAD_IMAGEOBJECT_LARGEZONE)
				{
					#ifdef OUTPUT_DEBUG
						//	DEBUG_ADD("[Thread Job] Complete Load");
					#endif
					g_bZoneLargeLoadImage = true;
				}

				file.close();
			break;

			//--------------------------------------------------------
			// Small Zone�� ImageObject�� Loading�Ѵ�.
			//--------------------------------------------------------
			case THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE :
				g_bZoneSmallLoadImage = false;
				file.open((*g_pZoneTable).Get(g_nZoneSmall)->Filename, ios::binary);

				// Tile Loading
				if (g_ThreadJob==THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE)
				{
					#ifdef OUTPUT_DEBUG
					//		DEBUG_ADD("[Thread Job] Load Tile SmallZone");
					#endif

					file.seekg(g_pZone->GetTileFilePosition(), ios::beg);
					if (!g_pTopView->LoadFromFileTileSPKLargeZone( file ))	// tile�� load
					{
						#ifdef OUTPUT_DEBUG
								//DEBUG_ADD("[Thread Job] Stop Loading Tile");
						#endif
						file.close();
						break;
					}
				}
			

				// ImageObject Loading
				if (bLoad && g_ThreadJob==THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE)
				{
					#ifdef OUTPUT_DEBUG
						//	DEBUG_ADD("[Thread Job] Load ImageObject SmallZone");
					#endif
					file.seekg(g_pZone->GetImageObjectFilePosition(), ios::beg);
					if (!g_pTopView->LoadFromFileImageObjectSPKSmallZone( file ))
					{
						#ifdef OUTPUT_DEBUG
							//	DEBUG_ADD("[Thread Job] Stop Loading ImageObject");
						#endif
						file.close();
						break;
					}
				}

				if (bLoad && g_ThreadJob==THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE)
				{
					g_bZoneSmallLoadImage = true;
				}

				file.close();
			break;

			//--------------------------------------------------------
			// Creature�� Loading�Ѵ�.
			//--------------------------------------------------------
			case THREADJOB_LOAD_CREATURE :
				g_pTopView->LoadFromFileCreatureSPK( 0 );
				g_pTopView->LoadFromFileCreatureSPK( 1 );
			break;
		}

		#ifdef OUTPUT_DEBUG
			//	DEBUG_ADD("[Thread Job] End");
		#endif

		ResetEvent(g_hFileEvent);
	}

	return 0L;
}
*/

//-----------------------------------------------------------------------------
// Stop File Thread
//-----------------------------------------------------------------------------
/*
void
StopFileThread()
{	
	#ifdef OUTPUT_DEBUG
	//		DEBUG_ADD("[Thread Job] StopFileThread");
	#endif

	switch (g_ThreadJob)
	{
		case THREADJOB_LOAD_IMAGEOBJECT_LARGEZONE :
			//g_nZoneLarge = ZONEID_NULL;

			// ImageObject Loading�� �ߴ��Ѵ�.
			g_pTopView->StopLoadTileSPK();
			g_pTopView->StopLoadImageObjectSPK();
			g_bZoneLargeLoadImage = false;
			
			// �켱 ������ ���� ���...
			SetThreadPriority(g_hFileThread, 
								THREAD_PRIORITY_HIGHEST);
		break;
		
		case THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE :
			//g_nZoneSmall = ZONEID_NULL;

			// ImageObject Loading�� �ߴ��Ѵ�.
			g_pTopView->StopLoadTileSPK();
			g_pTopView->StopLoadImageObjectSPK();	
			g_bZoneSmallLoadImage = false;

			// �켱 ������ ���� ���...
			SetThreadPriority(g_hFileThread, 
								THREAD_PRIORITY_HIGHEST);
		break;
		
		case THREADJOB_LOAD_CREATURE :

			//g_pTopView->StopLoadCreature();

			// ĳ���� �׸� Load���ΰ�?
			// �켱 ������ ���� ���...
			SetThreadPriority(g_hFileThread, 
								THREAD_PRIORITY_HIGHEST);
		break;
	}

	g_ThreadJob = THREADJOB_NONE;

	#ifdef OUTPUT_DEBUG
	//		DEBUG_ADD("[Thread Job] Wait for Stopping thread");
	#endif

	while (WaitForSingleObject(g_hFileEvent, 0) == WAIT_OBJECT_0);

		// Thread�� �ϴ� Loading�� ���������� ��ٸ���.
	#ifdef OUTPUT_DEBUG
	//		DEBUG_ADD("[Thread Job] Stop File Thread");
	#endif
	

	// ������ �� �����.
	SetThreadPriority(g_hFileThread, 
						THREAD_PRIORITY_BELOW_NORMAL);
}
*/

//-----------------------------------------------------------------------------
// Load Creature
//-----------------------------------------------------------------------------
// n��° Creature Type ID�� Sprite�� load�Ѵ�.
//-----------------------------------------------------------------------------
BOOL
LoadCreature(int spriteType)
{
	// Debug Message
	DEBUG_ADD_FORMAT("LoadCreature : %d", spriteType);
	
	g_pTopView->LoadFromFileCreatureSPK( spriteType );

	return TRUE;
}

//-----------------------------------------------------------------------------
// Load CreatureType
//-----------------------------------------------------------------------------
// creature type�� ���� sprite�� load�Ѵ�.
//-----------------------------------------------------------------------------
BOOL
LoadCreatureType(int creatureType)
{
	// Debug Message
	DEBUG_ADD_FORMAT("LoadCreatureType : %d", creatureType);
	
	int spriteType = (*g_pCreatureTable)[creatureType].SpriteTypes[0];

	if (!(*g_pCreatureSpriteTable)[spriteType].bLoad)
	{
		//if (spriteType==9)
		//{
		//	int a = 9;
		//}

		LoadCreature( spriteType );

		return TRUE;
	}

	DEBUG_ADD_FORMAT("Don't need to LoadCreatureType : %d", creatureType);
	
	return FALSE;
}

//-----------------------------------------------------------------------------
// ReleaseUselessCreatureSPKExcept
//-----------------------------------------------------------------------------
void		
ReleaseUselessCreatureSPKExcept(const COrderedList<int>& listUse)
{
	DEBUG_ADD("ReleaseUselessCreatureSPKExcept");
	
	g_pTopView->ReleaseUselessCreatureSPKExcept( listUse );
}

//-----------------------------------------------------------------------------
// Release GameObject
//-----------------------------------------------------------------------------
// game�� ���õ� object���� ���Ž�Ų��.
//-----------------------------------------------------------------------------
void
ReleaseGameObject()
{
	//------------------------------------------------------
	// ���� ����
	//------------------------------------------------------
	g_pWeather->Release();

	g_pParty->Release();

	g_pEventManager->RemoveAllEvent();
	g_pWarManager->ClearWar();
	g_pTimeItemManager->clear();

	//------------------------------------------------------
	// Zone���� Player���� / Zone ����
	//------------------------------------------------------
	if (g_pZone!=NULL)
	{
		DEBUG_ADD("[ SetZone NULL ] Remove Player & Set Zone to NULL");
		g_pZone->RemovePlayer();				
		g_pZone->ReleaseObject();
		g_pZone = NULL;

		if (g_pZoneSoundTable)
		{
			delete g_pZoneSoundTable;
			g_pZoneSoundTable = NULL;
		}

		if (g_pZoneSoundManager)
		{
			delete g_pZoneSoundManager;
			g_pZoneSoundManager = NULL;
		}
	}

	//------------------------------------------------------
	// Small Zone ����
	//------------------------------------------------------
	/*
	if (g_pZoneSmall != NULL)
	{
		DEBUG_ADD("[ delete SmallZone ]");
		delete g_pZoneSmall;	
		g_pZoneSmall = NULL;
		g_nZoneSmall = ZONEID_NULL;	
		g_bZoneSmallLoadImage = false;
	}			
	*/

	//------------------------------------------------------
	// Large Zone ����
	//------------------------------------------------------
	/*
	if (g_pZoneLarge != NULL)
	{
		DEBUG_ADD("[ delete LargeZone ]");
		delete g_pZoneLarge;	
		g_pZoneLarge = NULL;
		g_nZoneLarge = ZONEID_NULL;	
		g_bZoneLargeLoadImage = false;
	}
	*/

	//------------------------------------------------------
	// player����
	//------------------------------------------------------
	if (g_pPlayer!=NULL)
	{
		DEBUG_ADD("[ delete Player ]");
		
		if (g_pZone!=NULL)
		{
			g_pZone->RemoveCreature( g_pPlayer->GetID() );
		}

		delete g_pPlayer;
		g_pPlayer = NULL;
	}

	if (g_pTradeManager!=NULL)
	{
		delete g_pTradeManager;
		g_pTradeManager = NULL;
	}

	if (g_pStorage!=NULL)
	{
		delete g_pStorage;
		g_pStorage = NULL;
	}
	
	if (g_pStorage2!=NULL)
	{
		delete g_pStorage2;
		g_pStorage2 = NULL;
	}
			

	DEBUG_ADD("[ delete GameObject OK ]");
}

//-----------------------------------------------------------------------------
// Load Zone
//-----------------------------------------------------------------------------
// n��° zone�� load�Ѵ�.
//-----------------------------------------------------------------------------
BOOL
LoadZone(int n)
{	
	//------------------------------------------------
	// Zone�� ����(size)�� ���� ó	��
	//------------------------------------------------
	// 
	// ���� ����(size)�� ���� Zone�� Load�� �ؾ��Ѵ�.
	//
	//------------------------------------------------
	ZONETABLE_INFO* pZoneInfo = g_pZoneTable->Get( n );

	if (pZoneInfo==NULL)
	{
		DEBUG_ADD_FORMAT("[Error] Wrong Zone ID=%d", n);	
		
		return FALSE;
	}

	//------------------------------------------------
	// ��� ���带 �����ع�����.
	//------------------------------------------------
	if (g_pSoundManager!=NULL)
	{
		g_pSoundManager->Stop();		
		g_bPlayPropeller = FALSE;
	}
	g_DXSound.ReleaseDuplicateBuffer();


	// Debug Message
	DEBUG_ADD_FORMAT("LoadZone : ID=%d, Filename=%s", pZoneInfo->ID, pZoneInfo->Filename.GetString());		
	
	//------------------------------------------------
	// Music ����...
	//------------------------------------------------
	//BOOL bMusicPause = g_DXMusic.IsPause();
	//g_DXMusic.Stop();

	//BOOL bMusicPause = g_Music.IsPause();

	if (g_pUserOption->PlayWaveMusic)
	{
#ifdef __USE_MP3__
		if (g_pMP3 != NULL)
		{
			DEBUG_ADD("MP3 STOP4");
			g_pMP3->Stop();
			DEBUG_ADD("MP3 STOP4 OK");
		}
#else
		if( g_pOGG != NULL )
		{
			if( g_DXSound.IsInit() )
				g_pOGG->streamClose();
		}
#endif
//		if (g_pDXSoundStream!=NULL)
//		{
//			g_pDXSoundStream->Stop();
//		}
//		g_pDXSoundStream->Update();
	}
	else
	{
		g_Music.Stop();
	}

	//------------------------------------------------
	// Fade Out ����
	//------------------------------------------------
		/*
	if (g_pZone!=NULL && g_Mode==MODE_GAME )
	{
		g_pTopView->SetFadeOut(6);

		while(g_pTopView->IsFade())
		{
			g_CurrentTime = timeGetTime();
			g_pUpdate->Update();
		}

		// ���� ����
		//g_Music.Stop();
	}
	*/

	//------------------------------------------------
	// Fade In ����
	//------------------------------------------------
	//g_pTopView->SetFadeIn(10);


	//------------------------------------------------
	// ���� �ٸ� Zone�� Loading���̶��
	//------------------------------------------------
	/*
	if  (WaitForSingleObject(g_hFileEvent, 0) == WAIT_OBJECT_0)
	{
		StopFileThread();		
	}
	*/
	//g_pLoadingThread->Remove( 1 );

	//-------------------------------------------------------------
	// Loading ���̴��� ��� ����
	//-------------------------------------------------------------
	StopLoadingThread();

	// priority�� �ִ��� �����.
	if (g_pLoadingThread!=NULL)
	{
		g_pLoadingThread->SetPriority( THREAD_PRIORITY_IDLE );
	}

	//----------------------------------------------------------------------
	// ���� Zone�� object�� ����
	//----------------------------------------------------------------------
	if (g_pZone!=NULL)
	{
		g_pZone->ReleaseObject();
	}

	//----------------------------------------------------------------------
	// �ٷ� ���� �ִ� zone�� ����
	//----------------------------------------------------------------------
	ZONETABLE_INFO* pPreviousZoneInfo = (*g_pZoneTable).Get( (g_bZonePlayerInLarge?g_nZoneLarge : g_nZoneSmall) );		

	//----------------------------------------------------------------------
	//
	//					Small Zone
	//
	//----------------------------------------------------------------------
	if (pZoneInfo->Property & FLAG_ZONESIZE_SMALL)
	{	
		//ZONETABLE_INFO* pOldZoneInfo = (*g_pZoneTable).Get( g_nZoneSmall );

		//-------------------------------------------
		// ������ LargeZone�� �־��ٸ�.. 
		// �׸��� �ٽ� ����
		//-------------------------------------------
		if (g_bZonePlayerInLarge)
		{
			g_pTopView->ClearShadowManager();
		}
		
		//-------------------------------------------
		// �ٽ� load�� �ʿ䰡 ���� ���
		//-------------------------------------------
		if (g_nZoneSmall==n && g_pZoneSmall!=NULL)
		{
			DEBUG_ADD("ReleaseObject in SmallZone");
			
			// object�� ����
			g_pZoneSmall->ReleaseObject();

			DEBUG_ADD("OK");
			
			// �׸��� Load���� ���� ���¸�..
			/*
			if (!g_bZoneSmallLoadImage)
			{
				// Thread�� ������ ����				
				g_ThreadJob = THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE;				
				SetEvent(g_hFileEvent);
			}
			*/

			// SmallZone�� pointer�� ����
			g_pZone	= g_pZoneSmall;

			UI_DrawProgress( 95 );
		}
		//-------------------------------------------
		// �ٽ� Load�ؾߵ� ���
		//-------------------------------------------
		else
		{
			// Load�� Zone�� ����(size)�� ���
			g_nZoneSmall = n;	

			DEBUG_ADD("[Load Zone] Release Old Tile&ImageObject SPK");
			
			// ���� Zone�� �ִ� Sprite���� �����ش�.
			g_pTopView->ReleaseTileSPKSmallZone();		
			g_pTopView->ReleaseImageObjectSPKSmallZone();	
			
			// SmallZone�� �ʱ�ȭ�Ѵ�.
			if (g_pZoneSmall != NULL)
			{
				DEBUG_ADD( "Delete old ZoneSmall");
				
				delete g_pZoneSmall;
			}				

			DEBUG_ADD( "New ZoneSmall");
			
			g_pZoneSmall = new MZone;

			// SmallZone�� pointer�� ����
			g_pZone	= g_pZoneSmall;

			// ƾ�����ΰ�� ƾ������ ������ �ε�
			MString filename = pZoneInfo->Filename;
			if(g_pUserInformation->GoreLevel == false)
			{
				if(pZoneInfo->TeenFilename.GetLength() > 0)
					filename = pZoneInfo->TeenFilename;
			}

			class ifstream file;
			if (!FileOpenBinary(filename, file))
			{
				// priority�� ��������
				if (g_pLoadingThread!=NULL)
				{
					g_pLoadingThread->SetPriority( THREAD_PRIORITY_LOWEST );
				}

				return FALSE; 
			}

			DEBUG_ADD("[Load Zone] Load Zone Data");
			
			UI_DrawProgress( 80 );

			// Zone loading ����?
			if (!g_pZone->LoadFromFile( file ))
			{
				SetMode( MODE_QUIT );

				// priority�� ��������
				if (g_pLoadingThread!=NULL)
				{
					g_pLoadingThread->SetPriority( THREAD_PRIORITY_LOWEST );
				}
				return FALSE;
			}

			g_pZone->SetCurrentZoneID( n );
		
			//g_pTopView->LoadFromFileTileSPKLargeZone( file );	// tile�� load
			//g_pTopView->LoadFromFileImageObjectSPKLargeZone( file );
			file.close();			
			
			
			
			UI_DrawProgress( 90 );

			//-------------------------------------------------------
			// Player�� ��ǥ ��ó�� Sprite���� Load�Ѵ�.
			//-------------------------------------------------------
			DEBUG_ADD("[Load Zone] Find Tile&ImageObject ID");
			
			CSpriteSetManager TileSSM;
			CSpriteSetManager ImageObjectSSM;
			g_pZone->GetNearSpriteSet(TileSSM, ImageObjectSSM, g_pPlayer->GetX(), g_pPlayer->GetY());
			g_pTopView->LoadFromFileTileAndImageObjectSet(TileSSM, ImageObjectSSM);

			DEBUG_ADD("[Load Zone] Find Tile&ImageObject ID.. OK");
			
			UI_DrawProgress( 95 );
		}
		
		//-------------------------------------------------------
		// LoadingThread�� ������ ����			
		//-------------------------------------------------------
		//g_ThreadJob = THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE;				
		//SetEvent(g_hFileEvent);
		// ƾ�����ΰ�� ƾ������ ������ �ε�
		MString filename = (*g_pZoneTable).Get(g_nZoneSmall)->Filename;
		if(g_pUserInformation->GoreLevel == false)
		{
			if((*g_pZoneTable).Get(g_nZoneSmall)->TeenFilename.GetLength() > 0)
				filename = (*g_pZoneTable).Get(g_nZoneSmall)->TeenFilename;
		}

		class ifstream file;
		file.open(filename, ios::binary);

		file.seekg(g_pZone->GetTileFilePosition(), ios::beg);
		g_pTopView->LoadFromFileTileSPKSmallZone( file );

		file.seekg(g_pZone->GetImageObjectFilePosition(), ios::beg);				
		g_pTopView->LoadFromFileImageObjectSPKSmallZone( file );

		file.close();		
		
		BOOL NeedMusicLoad = TRUE;

		DEBUG_ADD("[Load Zone] Before Music Check");
		
		DEBUG_ADD("[Load Zone] Before Music Play");
		
		//------------------------------------------
		// ���� �����ؾ� �Ǵ� ����̸�
		//------------------------------------------
		/*
		if (g_pUserOption->PlayMusic)
		{
			//------------------------------------------
			// ������ ���� ������ �޶�����.
			//------------------------------------------
			TYPE_MUSICID	newMusicID = 0;

			if (g_pPlayer!=NULL && g_pPlayer->IsSlayer())
			{		
				newMusicID = pZoneInfo->MusicIDSlayer;
			}
			else
			{
				newMusicID = pZoneInfo->MusicIDVampire;
			}

			//g_DXMusic.SetOriginalTempo();
			//g_DXMusic.Play( (*g_pMusicTable)[ newMusicID ].Filename );			
			int musicID = newMusicID;

			if (musicID!=MUSICID_NULL)
			{
				if (g_pUserOption->PlayWaveMusic)
				{
					g_pDXSoundStream->Load( (*g_pMusicTable)[ musicID ].FilenameWav );
					g_pDXSoundStream->Play( TRUE );
				}
				else
				{
					g_Music.Play( (*g_pMusicTable)[ musicID ].Filename );
				}
			}
		}
		*/
	
		/*
		if (g_pMP3 != NULL)
		{
			g_pMP3->Pause();
			delete g_pMP3;
		}

		g_pMP3 = new CMySound( (*g_pMusicTable)[ (*g_pZoneTable)[g_nZoneSmall].MusicID ].Filename );
		g_pMP3->Play();
		*/
					
		g_bZonePlayerInLarge = false;
	}

	//----------------------------------------------------------------------
	//
	//					Large Zone
	//
	//----------------------------------------------------------------------
	else
	{
		//ZONETABLE_INFO* pOldZoneInfo = (*g_pZoneTable).Get( g_nZoneLarge );

		//-------------------------------------------
		// ������ SmallZone�� �־��ٸ�.. 
		// �׸��� �ٽ� ����
		//-------------------------------------------
		if (!g_bZonePlayerInLarge)
		{
			g_pTopView->ClearShadowManager();
		}

		//-----------------------------------------------
		// �ٽ� Load�ؾ��� �ʿ䰡 ���� ���
		//-----------------------------------------------
		if (g_nZoneLarge==n && g_pZoneLarge!=NULL)
		{
			DEBUG_ADD("ReleaseObject in LargeZone");
			
			// object�� ����
			g_pZoneLarge->ReleaseObject();
			
			DEBUG_ADD("OK");
			
			// �׸��� Load���� ���� ���¸�..
			/*
			if (!g_bZoneLargeLoadImage)
			{
				// Thread�� ������ ����				
				g_ThreadJob = THREADJOB_LOAD_IMAGEOBJECT_LARGEZONE;				
				SetEvent(g_hFileEvent);
			}
			*/

			// LargeZone�� pointer�� ����
			g_pZone	= g_pZoneLarge;

			UI_DrawProgress( 95 );
		}
		//-----------------------------------------------
		// �ٽ� Load�ؾߵ� ���
		//-----------------------------------------------
		else
		{
			// Load�� Zone�� ����(size)�� ���
			g_nZoneLarge = n;	

			DEBUG_ADD("[Load Zone] Release Old Tile&ImageObject SPK");
			
			// ���� Zone�� �ִ� Sprite���� �����ش�.
			g_pTopView->ReleaseTileSPKLargeZone();		
			g_pTopView->ReleaseImageObjectSPKLargeZone();	
			
			// LargeZone�� �ʱ�ȭ�Ѵ�.
			if (g_pZoneLarge != NULL)
			{
				DEBUG_ADD( "Delete old ZoneLarge");
				
				delete g_pZoneLarge;
			}			
			
			DEBUG_ADD( "New ZoneLarge");
			
			g_pZoneLarge = new MZone;

			// LargeZone�� pointer�� ����
			g_pZone	= g_pZoneLarge;			
			
			// ƾ�����ΰ�� ƾ������ ������ �ε�
			MString filename = pZoneInfo->Filename;
			if(g_pUserInformation->GoreLevel == false)
			{
				if(pZoneInfo->TeenFilename.GetLength() > 0)
					filename = pZoneInfo->TeenFilename;
			}
			
			class ifstream file;
			if (!FileOpenBinary(filename, file))
			{
				// priority�� ��������
				if (g_pLoadingThread!=NULL)
				{
					g_pLoadingThread->SetPriority( THREAD_PRIORITY_LOWEST );
				}

				return FALSE; 
			}

			DEBUG_ADD("[Load Zone] Load Zone Data");
			
			UI_DrawProgress( 80 );

			// Zone loading ����?
			if (!g_pZone->LoadFromFile( file ))
			{
				SetMode( MODE_QUIT );

				// priority�� ��������
				if (g_pLoadingThread!=NULL)
				{
					g_pLoadingThread->SetPriority( THREAD_PRIORITY_LOWEST );
				}

				return FALSE;
			}

			//g_pTopView->LoadFromFileTileSPKLargeZone( file );	// Tile�� load
			//g_pTopView->LoadFromFileImageObjectSPKLargeZone( file );
			file.close();

			UI_DrawProgress( 90 );
			
			//-------------------------------------------------------
			// Player�� ��ǥ ��ó�� Sprite���� Load�Ѵ�.
			//-------------------------------------------------------
			DEBUG_ADD("[Load Zone] Find Tile&ImageObject ID");
			
			CSpriteSetManager TileSSM;
			CSpriteSetManager ImageObjectSSM;
			g_pZone->GetNearSpriteSet(TileSSM, ImageObjectSSM, g_pPlayer->GetX(), g_pPlayer->GetY());
			g_pTopView->LoadFromFileTileAndImageObjectSet(TileSSM, ImageObjectSSM);
			
			DEBUG_ADD("[Load Zone] Find Tile&ImageObject ID.. OK");
				
			UI_DrawProgress( 95 );
		}

		//-------------------------------------------------------
		// LoadingThread�� ������ ����			
		//-------------------------------------------------------
		//g_ThreadJob = THREADJOB_LOAD_IMAGEOBJECT_SMALLZONE;				
		//SetEvent(g_hFileEvent);
		MString filename = (*g_pZoneTable).Get(g_nZoneLarge)->TeenFilename;
		if(g_pUserInformation->GoreLevel == false)
		{
			if((*g_pZoneTable).Get(g_nZoneLarge)->TeenFilename.GetLength() > 0)
				filename = (*g_pZoneTable).Get(g_nZoneLarge)->TeenFilename;
		}

		class ifstream file;
		file.open(filename, ios::binary);

		file.seekg(g_pZone->GetTileFilePosition(), ios::beg);
		g_pTopView->LoadFromFileTileSPKLargeZone( file );

		file.seekg(g_pZone->GetImageObjectFilePosition(), ios::beg);				
		g_pTopView->LoadFromFileImageObjectSPKLargeZone( file );

		file.close();		

		
		BOOL NeedMusicLoad = TRUE;

		
		DEBUG_ADD("[Load Zone] Before Music Play");
		
		//------------------------------------------
		// ���� �����ؾ� �Ǵ� ����̸�
		//------------------------------------------
		/*
		if (g_pUserOption->PlayMusic)
		{
			//------------------------------------------
			// ������ ���� ������ �޶�����.
			//------------------------------------------
			//TYPE_MUSICID	oldMusicID = 0;
			TYPE_MUSICID	newMusicID = 0;

			DEBUG_ADD("[Load Zone] Before Music Check");
			
			if (g_pPlayer!=NULL && g_pPlayer->IsSlayer())
			{		
				newMusicID = pZoneInfo->MusicIDSlayer;
			}
			else
			{
				newMusicID = pZoneInfo->MusicIDVampire;
			}

			//g_DXMusic.SetOriginalTempo();
			//g_DXMusic.Play( (*g_pMusicTable)[ newMusicID ].Filename );			

			int musicID = newMusicID;

			if (musicID!=MUSICID_NULL)
			{
				if (g_pUserOption->PlayWaveMusic)
				{
					g_pDXSoundStream->Load( (*g_pMusicTable)[ musicID ].FilenameWav );
					g_pDXSoundStream->Play( TRUE );
				}
				else
				{
					g_Music.Play( (*g_pMusicTable)[ musicID ].Filename );
				}
			}
		}
		*/
	
		/*
		if (g_pMP3 != NULL)
		{
			g_pMP3->Pause();
			delete g_pMP3;
		}

		g_pMP3 = new CMySound;// (*g_pMusicTable)[ (*g_pZoneTable)[g_nZoneLarge].MusicID ].Filename );
		//g_pMP3->Play();
		g_pMP3->Load( (*g_pMusicTable)[ (*g_pZoneTable)[g_nZoneLarge].MusicID ].Filename );
		*/

		g_bZonePlayerInLarge = true;
	}

	DEBUG_ADD("[Load Zone] Before Minimap Loading");
	
	//------------------------------------------------
	// UI�� zone����..
	//------------------------------------------------
	SIZE zoneSize = { g_pZone->GetWidth(), g_pZone->GetHeight() };

	gC_vs_ui.SetSize( zoneSize );
	gC_vs_ui.SetZone( n );
	
#ifdef OUTPUT_DEBUG
//	if(C_VS_UI_MINIMAP::GetZoneName(n))
//	{
//		extern int CLogFile;
//		
//		_write( CLogFile, "<<<", 3 );
//		_write( CLogFile, C_VS_UI_MINIMAP::GetZoneName(n), strlen(C_VS_UI_MINIMAP::GetZoneName(n)));
//		_write( CLogFile, ">>>", 3 );
//		_write( CLogFile, "\n", 1 );
//	}
#endif
	
	LoadZoneInfo( n );
	g_pZone->SetCurrentZoneID( n );

	// 2004, 6, 22 sobeit add start - ���巹 �ھ� ����
	Add_GDR_Ghost(n);
	Add_GDR_Effect(1,false);
	Add_GDR_Effect(2,false);
	Add_GDR_Potal_Effect(n);
	// 2005, 1, 18, sobeit add start-����Ʈ ���� - bDisableTileImage==false�� ��κ��̹Ƿ�..
	if(n == 4001)
	{
		for (int i=0; i<g_pZone->GetHeight(); i++)
		{
			for (int j=0; j<g_pZone->GetWidth(); j++)
			{
				const_cast<MSector &>(g_pZone->GetSector(i, j)).SetDisableTileImage();
			}
		}
	}
	// 2005, 1, 18, sobeit add end
	// 2004, 9, 21, sobeit add start - �ƴ� �� ����
	else if(n == 74)
	{
		if(g_pPlayer->GetY()<60)
			g_pPlayer->SetShowAdamCloud(true);
		else
			g_pPlayer->SetShowAdamCloud(false);
	}
	// 2004, 9, 21, sobeit add end
//	BYTE PkType = g_pZone->GetPKType();
//	if(PkType != PK_TYPE_NULL)	// �׳� �Ϲ� ��
//	{
//		if(PkType == PK_TYPE_DISABLE)		// �� �츮��..-_-; pk ����
//			g_pPlayer->SetAttackModePeace();
//		else if(PkType == PK_TYPE_ALL)		// �� ���� �� ��
//			g_pPlayer->SetAttackModeAggress();
//		else if(PkType == PK_TYPE_GUILD)	// �츮 ��� ���� �� ��..
//		{
//			int myGuildID = g_pPlayer->GetGuildNumber();	
//			int OtherGuildID = pCreature->GetGuildNumber();	
//			if( myGuildID		== GUILDID_VAMPIRE_DEFAULT ||
//				myGuildID		== GUILDID_SLAYER_DEFAULT ||
//				myGuildID		== GUILDID_OUSTERS_DEFAULT ||
//				OtherGuildID	== GUILDID_VAMPIRE_DEFAULT ||
//				OtherGuildID	== GUILDID_SLAYER_DEFAULT ||
//				OtherGuildID	== GUILDID_OUSTERS_DEFAULT ) // ��尡 ���� �༮ ����..
//				return TRUE; // ȥ�� �ο���..-_-;
//
//			if(myGuildID == OtherGuildID)
//				return FALSE; // �츮 ���...
//			else
//				return TRUE;
//		}
//	}
//	else
//		g_pPlayer->SetAttackModeNormal();

	// 2004, 6, 22 sobeit add end
	//------------------------------------------------
	// minimap �׸� ����
	//------------------------------------------------
	//g_pTopView->LoadMinimap( pZoneInfo->MinimapFilename );	
	
	//------------------------------------------------
	// Random SoundID �ð� ����
	//------------------------------------------------
	g_ZoneRandomSoundTime = g_CurrentTime + ((rand()%5)+10)*1000;	// 10~15����..
	
	


	//---------------------------------------------------------------
	// �ϳ��� �Ҹ��� ���� ����
	//---------------------------------------------------------------
	/*
	ZONESOUND_INFO* pSoundInfo	= new ZONESOUND_INFO;
	pSoundInfo->ID				= 1;
	pSoundInfo->SoundID			= SOUND_WORLD_WATER_DROP;
	pSoundInfo->Loop			= true;
	pSoundInfo->MinDelay		= 0;
	pSoundInfo->MaxDelay		= 24;
	pSoundInfo->StartHour		= 0;
	pSoundInfo->EndHour			= 24;
	
	g_pZoneSoundTable->AddData( pSoundInfo->ID, pSoundInfo );
	*/

	//*/
	
	

	//------------------------------------------------
	// �� Zone���� �����ϴ� Creature�� ���� Sprite��
	//------------------------------------------------
	//g_pTopView->LoadFromFileCreatureSPK( 0 );
	//g_pTopView->LoadFromFileCreatureSPK( 1 );

	

	//------------------------------------------------
	// View���� ����ؾ��� Zone�� �����Ѵ�.
	//------------------------------------------------
	// ������ ��µ� creature���� ���ش�.
	g_pTopView->SetZone(g_pZone);	

	// Debug Message
	DEBUG_ADD_FORMAT("LoadZone OK : size=(%d, %d)", g_pZone->GetWidth(), g_pZone->GetHeight());			
		

	// priority�� ��������
	if (g_pLoadingThread!=NULL)
	{
		g_pLoadingThread->SetPriority( THREAD_PRIORITY_LOWEST );
	}

	if (pZoneInfo->CreatureColorSet < MAX_COLORSET)
	{
		g_ZoneCreatureColorSet = pZoneInfo->CreatureColorSet;
	}
	else
	{
		g_ZoneCreatureColorSet = 0xFFFF;
	}	

	g_bZoneSafe = pZoneInfo->Safety;
	g_bHolyLand = pZoneInfo->HolyLand;

//	if( g_pWarManager->IsExist( pZoneInfo->ID ) )
//	{
//		g_bZoneSafe = false;
//	}

	g_pWarManager->ClearWar();
	g_pTimeItemManager->clear();

	g_pUserInformation->WorldName = g_pServerInformation->GetServerGroupName();
#ifdef __DEBUG_OUTPUT__
	for(int w=0;w<g_pZone->GetWidth();w++)
	{
		for(int h=0;h<g_pZone->GetHeight();h++)
		{
			if( g_pZone->GetSector(w,h).IsBlockAny() && g_pZone->GetID() == 3001 )
			{
				gC_vs_ui.SetBlock( w,h );
			}
		}
	}
#endif
	
#ifndef __METROTECH_TEST__
	if(gpC_base != NULL && g_pUserInformation->bCompetence == true && g_pUserInformation->bCompetenceShape != true &&
		g_pZoneTable->Get( g_pZone->GetID() )->CompetenceZone == false
		)
	{
		gpC_base->SendMessage(UI_CHAT_RETURN, CLD_NORMAL, 0, "*command ghost on");
	}
#endif
	
	return TRUE;
}

//-----------------------------------------------------------------------------
// Move Zone 
//-----------------------------------------------------------------------------
// Zone�� �̵��Ѵ�.
//-----------------------------------------------------------------------------
void
MoveZone(int n)
{
	//------------------------------------------------
	// Zone���� Player�� ������.
	//------------------------------------------------
	if (g_pZone != NULL)
	{
		g_pPlayer->SetStop();
		g_pPlayer->SetAction( ACTION_STAND );
//		g_pPlayer->UnSetTimeLightSight();
//		g_pPlayer->UnSetLightSightAttachEffect();
		g_pZone->RemovePlayer();
	}
	
	// n Zone�� load�Ѵ�.
	LoadZone( n );

	g_pPlayer->SetZone(g_pZone);
	g_pZone->SetPlayer();//&g_pPlayer->;	
	g_pPlayer->SetTimeLightSight(g_pPlayer->GetTimeLightSight());
//	g_pPlayer->SetLightSightAttachEffect();
}

//-----------------------------------------------------------------------------
// LoadZoneInfo
//-----------------------------------------------------------------------------
BOOL
LoadZoneInfo(int n)
{
	//------------------------------------------------
	// ZoneInfo
	//------------------------------------------------
	ZONETABLE_INFO* pZoneInfo = g_pZoneTable->Get( n );

	if (pZoneInfo==NULL)
	{
		DEBUG_ADD_FORMAT("[Error] Wrong Zone ID=%d", n);	
		
		return FALSE;
	}

	//------------------------------------------------
	//
	// ZoneInfoFile Loading
	//
	//------------------------------------------------
	DEBUG_ADD("[Load Zone] Before Open ZoneInfoFile");
	
	//------------------------------------------------
	// ZoneInfo
	//------------------------------------------------
//	MZoneInfo zoneInfo;
	class ifstream zoneInfoFile(pZoneInfo->InfoFilename.GetString(), ios::binary | ios::nocreate);

	//------------------------------------------------
	// File�� �ִ� ��츸 loading�Ѵ�.
	//------------------------------------------------
	if (zoneInfoFile.is_open())
	{
		DEBUG_ADD("[Load Zone] Load MinimapInfo");
		
		/*
		zoneInfo.LoadFromFile( zoneInfoFile );		

		//------------------------------------------------
		// minimap�� �������븦 ǥ���Ѵ�.
		//------------------------------------------------
		g_pTopView->LoadMinimap( pZoneInfo->MinimapFilename, &zoneInfo );	
		*/
		WORD width, height;
		
		zoneInfoFile.read((char*)&width, 2);
		zoneInfoFile.read((char*)&height, 2);

		//------------------------------------------------
		// size üũ
		//------------------------------------------------
		if (width==g_pZone->GetWidth() && height==g_pZone->GetHeight())
		{		
			DEBUG_ADD("[Load Zone] Load PortalInfo");
			
			//------------------------------------------------
			// ��Ż ������ loading�Ѵ�.
			// ���ο��� ���ִ°� ������... �ϴ�..
			//------------------------------------------------
			int numPortal;
			
			zoneInfoFile.read((char*)&numPortal, 4);

			DEBUG_ADD_FORMAT("numPortal = %d", numPortal);

			MPortal portal;
			RECT rect;
				
			for (int i=0; i<numPortal; i++)
			{			
				portal.LoadFromFile( zoneInfoFile );

				std::vector<WORD>& zoneID = portal.GetZoneID();

				int numZoneID = zoneID.size();

				DEBUG_ADD_FORMAT("[%d] numZoneID = %d", i, numZoneID);

				for (int i=0; i<numZoneID; i++)
				{
					rect.left = portal.GetLeft();
					rect.top = portal.GetTop();
					rect.right = portal.GetRight(); 
					rect.bottom = portal.GetBottom(); 

					DEBUG_ADD_FORMAT("AddPortal. type=%d, zoneID=%d", portal.GetType(), zoneID[i]);
					
					g_pZone->AddPortal( portal.GetType(), zoneID[i], rect );
				}

				//------------------------------------------------
				// UI�� �����Ѵ�.
				//------------------------------------------------
				if (numZoneID==1)
				{					
					DEBUG_ADD("UI SetPortal");

					gC_vs_ui.SetPortal( rect, zoneID[0] );
				}
				else
				{
					DEBUG_ADD("UI SetPortal - 60001");

					// ��Ƽ ��Ż�� ���.. ����.. _-_;
					gC_vs_ui.SetPortal( rect, 60001 );
				}
			}

			DEBUG_ADD("PortalInfo OK");

			//------------------------------------------------
			// �������� ����
			//------------------------------------------------
			int numSafe;
			
			zoneInfoFile.read((char*)&numSafe, 4);

			DEBUG_ADD_FORMAT("numSafe = %d", numSafe);

			B_RECT	rect2;

			DEBUG_ADD_FORMAT("[g_pPlayer] %x", g_pPlayer);
			//BYTE bSlayer = (g_pPlayer==NULL || g_pPlayer->IsSlayer());
			Race MyRace = g_pPlayer->GetRace();
			DEBUG_ADD("bSlayer OK");

			for (i=0; i<numSafe; i++)
			{			
				zoneInfoFile.read((char*)&rect2, SIZE_B_RECT);

				RECT safeRect = 
				{ 
					rect2.left,
					rect2.top,
					rect2.right,
					rect2.bottom
				};
				
				DEBUG_ADD_FORMAT("UI SetSafety. f=%d, (%d, %d, %d, %d)", rect2.flag, safeRect.left, safeRect.top, safeRect.right, safeRect.bottom);

				if (rect2.flag != 0)
				{
					BYTE fSafe = 0;

					if (rect2.flag & FLAG_MIP_SAFE_COMMON)
					{
						fSafe = FLAG_SECTOR_SAFE_COMMON;
					}
					
					if (rect2.flag & FLAG_MIP_SAFE_SLAYER)
					{
						fSafe |= FLAG_SECTOR_SAFE_SLAYER;
					}

					if (rect2.flag & FLAG_MIP_SAFE_VAMPIRE)
					{
						fSafe |= FLAG_SECTOR_SAFE_VAMPIRE;
					}
					if (rect2.flag & FLAG_MIP_SAFE_OUSTERS)
					{
						fSafe |= FLAG_SECTOR_SAFE_OUSTERS;
					}
					
					g_pZone->SetSafeSector( safeRect, fSafe );

					// ���� ������ ��ġ�ΰ�?

					if(MyRace == RACE_OUSTERS && ( rect2.flag & FLAG_MIP_SAFE_OUSTERS ) ||
						MyRace == RACE_VAMPIRE && ( rect2.flag & FLAG_MIP_SAFE_VAMPIRE) ||
						MyRace == RACE_SLAYER && (rect2.flag & FLAG_MIP_SAFE_SLAYER) ||
						(rect2.flag & FLAG_MIP_SAFE_COMMON) )
					{
						gC_vs_ui.SetSafetyZone( safeRect, true );						
					}
					// �ٸ� ������ ������ ��ġ�ΰ�?
					else
					{
						gC_vs_ui.SetSafetyZone( safeRect, false );
					}
				}
			}
			DEBUG_ADD("NUMSAFE OK");

			DEBUG_ADD("zoneinfoclose");
			zoneInfoFile.close();
			DEBUG_ADD("zoneinfoclose OK");
			
			DEBUG_ADD("Horn Setting Start");
			// ousters horn�� �ʿ� �ɴ´�
			UI_PORTAL_LIST portalList;
			
			for(i = 0; i < g_pZone->GetHorn().size(); i++)
			{
				portalList = g_pZone->GetHorn()[i];
				
				UI_PORTAL_LIST::iterator itr = portalList.begin();
				UI_PORTAL_LIST::iterator endItr = portalList.end();
				
				while(itr != endItr)
				{
					if(itr->zone_id == g_pZone->GetID())
					{
						DEBUG_ADD_FORMAT("zoneID : %d, x : %d, y : %d, portalX : %d, portalY : %d", 
							itr->zone_id, itr->x, itr->y, itr->portal_x, itr->portal_y);

						int npcID = 659;
						
						MNPC* pNPC = new MNPC;
						
						pNPC->SetZone( g_pZone );
						
						int zoneID	= (g_bZonePlayerInLarge?g_nZoneLarge : g_nZoneSmall);
						
						int creatureType = npcID;
						int spriteType = (*g_pCreatureTable)[creatureType].SpriteTypes[0];			
						
						pNPC->SetGuildNumber( GUILDID_OUSTERS );
						
						//pNPC->SetCreatureType( 0 );
						pNPC->SetCreatureType( npcID );
						pNPC->SetGroundCreature();
						pNPC->SetID(MFakeCreature::GetFakeID());
						//pNPC->SetAction(ACTION_MOVE);
						// Edit By Sonic 2006.10.1  ����ħ��������λ��
						//ԭλ�� 62  x=39 y=30  ����λ�� x=7 y=11
						if(itr->zone_id==62)
						{
							pNPC->SetPosition( 7, 11 );
						}else
						{
							pNPC->SetPosition( itr->portal_x, itr->portal_y );
						}
						// End
						pNPC->SetServerPosition( itr->portal_x, itr->portal_y );
						pNPC->SetDirection( 1 );
						pNPC->SetCurrentDirection( 1 );
						pNPC->SetAction( ACTION_STAND );
						
						pNPC->SetName( (*g_pCreatureTable)[npcID].Name.GetString() );
						
						// NPC ID
						pNPC->SetNPCID( npcID );
						
						//
						pNPC->SetStatus( MODIFY_MAX_HP, 100 );
						pNPC->SetStatus( MODIFY_CURRENT_HP, 100 );
						
						if (!g_pZone->AddCreature( pNPC ))
						{
							delete pNPC;
							pNPC = NULL;
						}
						else if(g_pPlayer->IsOusters())
						{
							const char* pName = pNPC->GetName();
							int x = pNPC->GetX();;
							int y = pNPC->GetY();
							
							UI_SetNPCInfo( pName, npcID, x, y );
						}
						DEBUG_ADD("AddNPC OK");
					}
					itr++;
				}
			}
			DEBUG_ADD("Horn Setting End");

			if(g_pZone->GetID() == 1311)
			{
				SetWeather(WEATHER_SPOT, 2);
			}
/*
			//---------------------------------------------------------------
			//
			//  Zone�� ȯ�� ���� ����
			//
			//---------------------------------------------------------------
			long fpCurrent = zoneInfoFile.tellg();
			zoneInfoFile.seekg( 0, ios::end );
			long fpEof = zoneInfoFile.tellg();
				
			if (!zoneInfoFile.eof()	// �� �̰� ����� �ȵ���- -;
				&& fpCurrent!=fpEof)
			{
				zoneInfoFile.seekg( fpCurrent, ios::beg );
			
				if (g_pZoneSoundTable)
				{
					DEBUG_ADD("Delete ZoneSoundTable");
					
					delete g_pZoneSoundTable;
				}

				if (g_pZoneSoundManager)
				{		
					DEBUG_ADD("Delete ZoneSoundManager");
					
					delete g_pZoneSoundManager;
				}

				DEBUG_ADD("New ZoneSoundTable");
				
				// Zone�� ���带 ��� ����?�� ���� ����
				g_pZoneSoundTable = new MZoneSoundTable;

				DEBUG_ADD("Delete ZoneSoundManager");
				
				// Zone�� �ִ� ���� ��ü�� ���� ����
				g_pZoneSoundManager = new MZoneSoundManager;

				
				DEBUG_ADD("Load SectorSound");
				
				//---------------------------------------------------------------
				// Sector�� ���� ������ Loading�Ѵ�.
				//---------------------------------------------------------------
				g_pZone->LoadFromFileSectorSound( zoneInfoFile );
				
				//---------------------------------------------------------------
				// ZoneSoundTable�� 
				// ���� Map�� ���� ���� ������ Loading�Ѵ�.
				//---------------------------------------------------------------
				DEBUG_ADD("Load ZoneSoundTable");	
				
				g_pZoneSoundTable->LoadFromFile( zoneInfoFile );

				DEBUG_ADD("Load ZoneSoundTable OK");
			}
			else
			{
				DEBUG_ADD("No ZoneSound Info");
			}			
*/
		}
		else
		{			
			DEBUG_ADD_FORMAT("[Error] ZoneInfo Size Mismatch: (%d,%d) != (%d,%d)", 
									g_pZone->GetWidth(), g_pZone->GetHeight(), 
									width, height );				
		}

		
		
		DEBUG_ADD("[Load Zone] Load ZoneInfo OK");
	}
	else
	{		
		DEBUG_ADD("[Load Zone] ZoneInfo File OpenError");
	}

	DEBUG_ADD("[Load Zone] OK");

	return TRUE;
}

//-----------------------------------------------------------------------------
// Init Player
//-----------------------------------------------------------------------------
BOOL
InitPlayer(int x, int y, int dir)
{
	// Debug Message
	DEBUG_ADD_FORMAT("InitPlayer : (%d,%d) Dir=%d", x, y, dir);			
	
	//------------------------------------------------
	// Creature�� ����
	//------------------------------------------------
	//g_pPlayer->SetCreatureType( 0 );

	//g_pPlayer->SetCreatureType( id%2 );
	//g_pPlayer->SetCreatureType( 1 );

	g_pPlayer->ClearChatString();

	//------------------------------------------------
	// ����ְ� �Ѵ�. Ȯ�ο�...
	//------------------------------------------------
	g_pTopView->SetFadeEnd();

	//------------------------------------------------
	// ��ġ ����
	//------------------------------------------------
	//g_pPlayer->SetPosition(x, y);	
	g_pPlayer->SetStop();
	g_pPlayer->SetX( x );
	g_pPlayer->SetY( y );
	g_pPlayer->SetServerPosition(x, y);
	g_pPlayer->SetDirection(dir);
	g_pPlayer->SetCurrentDirection(dir);
	//g_pPlayer->SetAction( ACTION_MOVE );	// Default

	//------------------------------------------------
	//  Zone <--> Player
	//------------------------------------------------
	g_pZone->SetPlayer();//&g_pPlayer->;	
	g_pPlayer->SetZone(g_pZone);

	//------------------------------------------------
	// �þ� Ȯ��..
	//------------------------------------------------
	//#ifdef CONNECT_SERVER
	//	g_pZone->KeepObjectInSight(x, y, g_pPlayer->GetSight());
	//#endif

	//------------------------------------------------
	// ���°�
	//------------------------------------------------
	//g_pPlayer->SetStatus(MODIFY_HP, 100);
	//g_pPlayer->SetStatus(MODIFY_MP, 100);
	
	//------------------------------------------------
	// �� ������	
	//------------------------------------------------
	///*
	//g_pPlayer->SetAddonEnable(ADDON_HAIR);		// �Ӹ�
	//g_pPlayer->SetAddonEnable(ADDON_COAT);		// ����
	//g_pPlayer->SetAddonEnable(ADDON_TROUSER);	// ����
	//g_pPlayer->SetAddonEnable(ADDON_HELM);		// ����
	//g_pPlayer->SetAddonEnable(ADDON_LEFTHAND);	// �޼� 
	//g_pPlayer->SetAddonEnable(ADDON_RIGHTHAND);	// ������	
	//g_pPlayer->SetAddonEnable(ADDON_MOTOR);		// �������
	
	//g_pPlayer->SetAddon(ADDON_COAT, ADDONID_COAT1_MALE);	
	//g_pPlayer->SetAddon(ADDON_TROUSER, ADDONID_TROUSER1_MALE);
	////g_pPlayer->SetAddon(ADDON_HELM, 9);
	////g_pPlayer->SetAddon(ADDON_RIGHTHAND, 7);
	//g_pPlayer->SetAddon(ADDON_HAIR, ADDONID_HAIR1_MALE);
	//g_pPlayer->RemoveAddon(ADDON_MOTOR);//, ADDONID_MOTORCYCLE_MALE);
	//*/

	//------------------------------------------------
	// �þ� ����
	//------------------------------------------------
	//g_pPlayer->SetLightSight( 12 );	// ���� ũ��
	//g_pPlayer->SetSight( 12 );		// ĳ������ �þ�

	//------------------------------------------------
	// ����, ��� ����
	//------------------------------------------------
	// ����
	//g_pPlayer->SetBasicActionInfo( SKILL_ATTACK_MELEE );
	
	// ���� ���ɰŸ� ����
	//g_pPlayer->SetBasicAttackDistance( 1 );

	// Ư�� ����
	//g_pPlayer->SetSpecialActionInfo( MAGIC_BLESS );

	// ���� ����
	if (g_pPlayer->IsAlive())
	{
		g_pPlayer->SetAction( ACTION_STAND );
	}
	else
	{
		g_pPlayer->SetAction( ACTION_DIE );
	}

	// �����̴� ���
	//g_pPlayer->SetMoveDevice( MCreature::MOVE_DEVICE_WALK );

	//-------------------------------------------------------
	// UI�� ���� ����
	//-------------------------------------------------------
	//gC_vs_ui.SetHP(g_pPlayer->GetHP(), g_pPlayer->GetMAX_HP());
	//gC_vs_ui.SetMP(g_pPlayer->GetMP(), g_pPlayer->GetMAX_MP());

	//-------------------------------------------------------
	// Server�� ���� move packet ������ �����
	// ó������~~ �ٽ� move�ϰ� �Ѵ�.
	//-------------------------------------------------------
	g_pPlayer->ResetSendMove();

	//-------------------------------------------------------
	// Attack Mode
	//-------------------------------------------------------
	//g_pPlayer->SetAttackModeNormal();


	//-------------------------------------------------------
	//
	//				����� �� �ִ� ���
	//
	//-------------------------------------------------------
	/*
	(*g_pSkillManager).Init( MAX_SKILLDOMAIN );

	//---------------------------------------------------------------------
	// �⺻ ����κ��� skill tree�� �ʱ�ȭ�Ѵ�.
	//---------------------------------------------------------------------
	(*g_pSkillManager)[SKILLDOMAIN_BLADE].SetRootSkill( SKILL_SINGLE_BLOW );
	(*g_pSkillManager)[SKILLDOMAIN_SWORD].SetRootSkill( SKILL_DOUBLE_IMPACT );
	(*g_pSkillManager)[SKILLDOMAIN_GUN].SetRootSkill( SKILL_SNIPPING );
	(*g_pSkillManager)[SKILLDOMAIN_GUN].SetRootSkill( SKILL_SHARP_SHOOTING );
	(*g_pSkillManager)[SKILLDOMAIN_ENCHANT].SetRootSkill( MAGIC_CREATE_HOLY_WATER );
	(*g_pSkillManager)[SKILLDOMAIN_HEAL].SetRootSkill( MAGIC_CURE_POISON );
	(*g_pSkillManager)[SKILLDOMAIN_VAMPIRE].SetRootSkill( MAGIC_HIDE );	

	MSkillDomain& bladeDomain = (*g_pSkillManager)[SKILLDOMAIN_BLADE];
	MSkillDomain& swordDomain = (*g_pSkillManager)[SKILLDOMAIN_SWORD];
	MSkillDomain& gunDomain = (*g_pSkillManager)[SKILLDOMAIN_GUN];
	MSkillDomain& enchantDomain = (*g_pSkillManager)[SKILLDOMAIN_ENCHANT];
	MSkillDomain& healDomain = (*g_pSkillManager)[SKILLDOMAIN_HEAL];
	*/

	//---------------------------------------------------------------------
	// ��� skill�� ����ٰ� ǥ���Ѵ�.
	//---------------------------------------------------------------------
	/*
	swordDomain.LearnSkill( SKILL_DOUBLE_IMPACT );
	swordDomain.LearnSkill( SKILL_TRIPLE_SLASHER );
	swordDomain.LearnSkill( SKILL_SCREW_SLASHER );
	swordDomain.LearnSkill( SKILL_RAINBOW_SLASHER );
	swordDomain.LearnSkill( SKILL_CRUSH_COMBO );
	swordDomain.LearnSkill( SKILL_CROSS_COUNTER );
	
	bladeDomain.LearnSkill( SKILL_SINGLE_BLOW );
	bladeDomain.LearnSkill( SKILL_TWIN_BREAK );
	bladeDomain.LearnSkill( SKILL_TRIPLE_BREAK );
	bladeDomain.LearnSkill( SKILL_SPIRAL_SLAY );
	bladeDomain.LearnSkill( SKILL_WILD_SMASH );
	bladeDomain.LearnSkill( SKILL_ARMOR_CRASH );

	gunDomain.LearnSkill( SKILL_SNIPPING );
	gunDomain.LearnSkill( SKILL_SHARP_SHOOTING );
	gunDomain.LearnSkill( SKILL_FAST_RELOAD );
	gunDomain.LearnSkill( SKILL_KNOCKS_TARGET_BACK );

	enchantDomain.LearnSkill( MAGIC_LIGHT );
	enchantDomain.LearnSkill( MAGIC_DETECT_HIDDEN );
	enchantDomain.LearnSkill( MAGIC_CONTINUAL_LIGHT );
	enchantDomain.LearnSkill( MAGIC_DETECT_INVISIBILITY );
	enchantDomain.LearnSkill( MAGIC_VISIBLE );

	healDomain.LearnSkill( MAGIC_CURE_POISON );
	healDomain.LearnSkill( MAGIC_PROTECTION_FROM_CURSE );
	healDomain.LearnSkill( MAGIC_CURE_LIGHT_WOUNDS );
	healDomain.LearnSkill( MAGIC_CURE_POISON );
	healDomain.LearnSkill( MAGIC_PROTECTION_FROM_POISON );
	healDomain.LearnSkill( MAGIC_CURE_PARALYSIS );

	*/
	//g_SkillAvailable.AddSkill( MAGIC_CURE_POISON );
	//g_SkillAvailable.AddSkill( MAGIC_PROTECTION_FROM_POISON );
	//g_SkillAvailable.AddSkill( MAGIC_CURE_PARALYSIS );

	//-------------------------------------------------------
	// ��� ���� ����..
	//-------------------------------------------------------
	g_pPlayer->SetWaitVerifyNULL();

	//-------------------------------------------------------
	//
	//						Item ����
	//
	//-------------------------------------------------------
	//------------------------------------------------
	// ItemCheckBuffer����
	//------------------------------------------------
	g_pPlayer->ClearItemCheckBuffer();
	
	//------------------------------------------------
	// Gear �ʱ�ȭ
	//------------------------------------------------
	/*
	if (g_pPlayer->IsSlayer())
	{
		g_SlayerGear.Init();
	}
	else
	{
		g_VampireGear.Init();
	}

	//------------------------------------------------
	//  Inventory �ʱ�ȭ
	//------------------------------------------------
	g_Inventory.Init(10,6);
	*/

	//------------------------------------------------
	// ����â�� �����ִ� ����..
	//------------------------------------------------
	g_char_slot_ingame.Race = g_pPlayer->GetRace();
	g_char_slot_ingame.bl_female = !g_pPlayer->IsMale();

	return TRUE;
}

//-----------------------------------------------------------------------------
// Make ScreenShot
//-----------------------------------------------------------------------------
// ���� ȭ���� ScreenShot�� �����Ѵ�.
//-----------------------------------------------------------------------------
void	
MakeScreenShot()
{
	char str[256];

	int maxScreenShot = g_pClientConfig->MAX_SCREENSHOT;

	#ifdef OUTPUT_DEBUG
		maxScreenShot = 1000;
	#endif

	_mkdir("ScreenShot");
	// MAX_SCREENSHOT���� ScreenCapture�� �����ϴ�.
	for (; g_ScreenShotNumber<maxScreenShot; g_ScreenShotNumber++)
	{		
		sprintf(str, "%s%03d.jpg", g_pFileDef->getProperty("PATH_SCREENSHOT").c_str(), g_ScreenShotNumber);
		
		int fd = _open( str, _O_RDONLY );

		// file�� ���� ��쿡 save�ϱ� ���ؼ�..
		if( fd == -1 )
		{
			// Save
			#ifdef OUTPUT_DEBUG
				if (g_bSaveSlideScreenShot
					&& g_rectScreenShot.left!=g_rectScreenShot.right
					&& g_rectScreenShot.top!=g_rectScreenShot.bottom)
				{
					if (g_rectScreenShot.left > g_rectScreenShot.right) { int temp=g_rectScreenShot.left; g_rectScreenShot.left=g_rectScreenShot.right; g_rectScreenShot.right=temp; }
					if (g_rectScreenShot.top > g_rectScreenShot.bottom) { int temp=g_rectScreenShot.top; g_rectScreenShot.top=g_rectScreenShot.bottom; g_rectScreenShot.bottom=temp; }

					int width = g_rectScreenShot.right - g_rectScreenShot.left + 8;
					int height = g_rectScreenShot.bottom - g_rectScreenShot.top + 8;

					width &= ~0x07;
					height &= ~0x07;

					CSpriteSurface surface;
					surface.InitOffsurface( width, height, DDSCAPS_SYSTEMMEMORY );

					POINT point0 = { 0, 0 };
					RECT rect = g_rectScreenShot;
					rect.left += 1;
					rect.top += 1;
					surface.BltNoColorkey(&point0, g_pBack, &rect);

					surface.SaveToBMP(str);
				}
				else
			#endif

//			g_pBack->SaveToBMP(str);
			SaveSurfaceToImage(str, *g_pBack);
			
			_close(fd);
			g_ScreenShotNumber++;
			return;	
		}
		else
		{
			_close(fd);
		}
	}


	#ifdef OUTPUT_DEBUG
		g_bSaveSlideScreenShot = false;
	#endif
}

//-----------------------------------------------------------------------------
// PlaySound
//-----------------------------------------------------------------------------
// (*g_pSoundTable)������ soundID�� ���õǴ� Filename�� Play�ϸ� �ȴ�.
// (*g_pSoundManager)�� ������ �ٷ� play�ϸ� �ǰ�.. 
// ������ Wav�� Load�ؼ� play�ϸ� �ȴ�.
//-----------------------------------------------------------------------------
void	
PlaySound(TYPE_SOUNDID soundID, bool repeat, int x, int y)
{
	if(g_pEventManager->GetEventByFlag(EVENTFLAG_NOT_PLAY_SOUND))
		return;
	
	__BEGIN_PROFILE("PlaySound1")

	//static int reload	= 0;
	//static int reuse	= 0;

	//-----------------------------------------------------------
	// ���ǵ��� �ʴ� sound ID�� ���..
	//-----------------------------------------------------------
	if (!g_DXSound.IsInit() || soundID >= (*g_pSoundTable).GetSize()
		|| !g_pUserOption->PlaySound)
	{
		__END_PROFILE("PlaySound1")
		return;
	}

	//-----------------------------------------------------------
	// �ʴ� �Ҹ��� �� �ִ� ���� ����
	//-----------------------------------------------------------
	if (!repeat 
		&& g_SoundPerSecond > g_pClientConfig->MAX_SOUND_PER_SECOND)
	{
		__END_PROFILE("PlaySound1")
		return;
	}

	int gapX = x - g_pPlayer->GetX();
	int gapY = y - g_pPlayer->GetY();
			
	int dist = max(abs(gapX), abs(gapY));				


	// �Ÿ��� ��� ���� �̻��̸� �Ҹ��� ������� �ʾƾ� �Ѵ�.
	if (dist < 25)
	{			
		//-----------------------------------------------------------
		// ������ --> Load & Play
		//-----------------------------------------------------------
		if ((*g_pSoundManager).IsDataNULL(soundID))
		{
			const char* pFilename = (*g_pSoundTable)[soundID].Filename;

			if (pFilename==NULL)
			{
				__END_PROFILE("PlaySound1")
				return;
			}					

			char strFilename[256];
			strcpy(strFilename, pFilename);
 			
			LPDIRECTSOUNDBUFFER pBuffer = g_DXSound.LoadWav( strFilename );
			//LPDIRECTSOUNDBUFFER	pBuffer = g_pWavePackFileManager->LoadFromFileData(soundID);

			//-----------------------------------------------------------
			// Loading ����
			//-----------------------------------------------------------
			if (pBuffer==NULL)
			{
				(*g_pSoundTable)[soundID].Filename.Release();
				DEBUG_ADD_FORMAT("[Error] Failed to Load WAV. id=%d, fn=%s", soundID, (*g_pSoundTable)[soundID].Filename );
			}
			else
			//-----------------------------------------------------------
			// Load�� ���� ������...			
			//-----------------------------------------------------------
			{
				// Replace������ �������� �޸𸮿��� �����.
				LPDIRECTSOUNDBUFFER pOld;
				if ((*g_pSoundManager).SetData( soundID, pBuffer, pOld )!=0xFFFF)
				{
					pOld->Release();
				}

				int gapX = x - g_pPlayer->GetX();
				int gapY = y - g_pPlayer->GetY();

				int dist = max(abs(gapX), abs(gapY));				
			
				if (gapX > 3)
				{
					g_DXSound.CenterToRightPan( pBuffer, (gapX-3) << 7 );
				}
				else if (gapX < -3)
				{
					g_DXSound.CenterToLeftPan( pBuffer, (abs(gapX+3)) << 7 );
				}
				else
				{
					g_DXSound.CenterPan( pBuffer );
				}			

				
				// ������� �Ҹ� �� ���̱� �ϵ��ڵ�. - -;
				if (soundID==SOUND_WORLD_BIKE_GO
					|| soundID==SOUND_WORLD_BIKE_STOP)
				{
					dist += 5;
				}

				
				int sub = (dist << 2) * g_pUserOption->VolumeSound;
				//int sub = dist * g_pUserOption->VolumeSound;

				g_DXSound.SubVolumeFromMax(pBuffer, sub);			

				// Play
				g_DXSound.Play( pBuffer, repeat, g_bGoodFPS);
				g_SoundPerSecond++;

				// Force Feel
				//-------------------------------------------------
				//if (gpC_Imm!=NULL && gpC_Imm->IsDevice())
				{
				//	gpC_Imm->ForceSound( strFilename );
				}

				//reload++;
			}
		}
		//-----------------------------------------------------------
		// �ִ� ��� --> Play
		//-----------------------------------------------------------
		else
		{
			LPDIRECTSOUNDBUFFER pBuffer;
			if ((*g_pSoundManager).GetData(soundID, pBuffer))
			{			
				
				if (gapX > 3)
				{
					g_DXSound.CenterToRightPan( pBuffer, (gapX-3) << 7 );
				}
				else if (gapX < -3)
				{
					g_DXSound.CenterToLeftPan( pBuffer, (abs(gapX+3)) << 7 );
				}
				else
				{
					g_DXSound.CenterPan( pBuffer );
				}

				// ������� �Ҹ� �� ���̱� �ϵ��ڵ�. - -;
				if (soundID==SOUND_WORLD_BIKE_GO
					|| soundID==SOUND_WORLD_BIKE_STOP)
				{
					dist += 5;
				}

				int sub = (dist << 2) * g_pUserOption->VolumeSound;
				//int sub = dist * g_pUserOption->VolumeSound;
				
				g_DXSound.SubVolumeFromMax(pBuffer, sub);

				g_DXSound.Play( pBuffer, repeat, g_bGoodFPS );
				g_SoundPerSecond++;

				// Force Feel
				//-------------------------------------------------				
				/*
				if (gpC_Imm!=NULL && gpC_Imm->IsDevice())
				{
					const char* pFilename = (*g_pSoundTable)[soundID].Filename;
				
					if (pFilename!=NULL)
					{					
						char strFilename[256];
						strcpy(strFilename, pFilename);

						gpC_Imm->ForceSound( strFilename );
					}
				}
				*/
			}
			
			//reuse ++;
		}
	}

	__END_PROFILE("PlaySound1")

	//#ifdef OUTPUT_DEBUG
	//	DEBUG_ADD_FORMAT("miss(%d) : match(%d)  / %d", reload, reuse, reload+reuse);		
	//#endif
}

//-----------------------------------------------------------------------------
// PlaySound
//-----------------------------------------------------------------------------
// �Ҹ����� ��ġ�� �� player�� ��ġ..
// CenterPan & MaxVolume
//-----------------------------------------------------------------------------
void	
PlaySound(TYPE_SOUNDID soundID)
{
	if(g_pEventManager->GetEventByFlag(EVENTFLAG_NOT_PLAY_SOUND))
		return;

	__BEGIN_PROFILE("PlaySound2")

	//-----------------------------------------------------------
	// ���ǵ��� �ʴ� sound ID�� ���..
	//-----------------------------------------------------------
	if (!g_DXSound.IsInit() || soundID >= (*g_pSoundTable).GetSize()
		|| !g_pUserOption->PlaySound)
	{
		__END_PROFILE("PlaySound2")
		return;
	}

	//-----------------------------------------------------------
	// �ʴ� �Ҹ��� �� �ִ� ���� ����
	//-----------------------------------------------------------
	// player�� �Ҹ��� ������ �ʿ䰡 ����.
	//if (g_SoundPerSecond > g_pClientConfig->MAX_SOUND_PER_SECOND)
	//{
	//	__END_PROFILE("PlaySound2")
		//return;
	//}

	//-----------------------------------------------------------
	// ������ --> Load & Play
	//-----------------------------------------------------------
	if ((*g_pSoundManager).IsDataNULL(soundID))
	{
		const char* pFilename = (*g_pSoundTable)[soundID].Filename;

		if (pFilename==NULL)
		{
			__END_PROFILE("PlaySound2")
			return;
		}

		char strFilename[256];
		strcpy(strFilename, pFilename);
 		LPDIRECTSOUNDBUFFER pBuffer = g_DXSound.LoadWav( strFilename );
		//LPDIRECTSOUNDBUFFER	pBuffer = g_pWavePackFileManager->LoadFromFileData(soundID);

		//-----------------------------------------------------------
		// Loading ����
		//-----------------------------------------------------------
		if (pBuffer==NULL)
		{
			(*g_pSoundTable)[soundID].Filename.Release();
			DEBUG_ADD_FORMAT("[Error] Failed to Load WAV. id=%d, fn=%s", soundID, (*g_pSoundTable)[soundID].Filename );
		}
		//-----------------------------------------------------------
		// Load�� ���� ������...
		//-----------------------------------------------------------
		else		
		{
			// Replace������ �������� �޸𸮿��� �����.
			LPDIRECTSOUNDBUFFER pOld;
			if ((*g_pSoundManager).SetData( soundID, pBuffer, pOld )!=0xFFFF)
			{
				pOld->Release();
			}

			g_DXSound.CenterPan( pBuffer );						
		
			g_DXSound.SetMaxVolume(pBuffer);

			// Play
			g_DXSound.Play( pBuffer, false, g_bGoodFPS );	
			
			g_SoundPerSecond++;

			//-------------------------------------------------
			// Force Feel
			//-------------------------------------------------
			//if (gpC_Imm!=NULL && gpC_Imm->IsDevice())
			{
			//	gpC_Imm->ForceSound( pFilename );
			}

			//reload++;
		}
	}
	//-----------------------------------------------------------
	// �ִ� ��� --> Play
	//-----------------------------------------------------------
	else
	{
		LPDIRECTSOUNDBUFFER pBuffer;
		if ((*g_pSoundManager).GetData(soundID, pBuffer))
		{			
			g_DXSound.CenterPan( pBuffer );
		
			g_DXSound.SetMaxVolume(pBuffer);

			g_DXSound.Play( pBuffer, false, g_bGoodFPS );
			g_SoundPerSecond++;
		}


		// Force Feel
		//-------------------------------------------------
		/*
		const char* pFilename = (*g_pSoundTable)[soundID].Filename;

		if (pFilename!=NULL)
		{
			char strFilename[256];
			strcpy(strFilename, pFilename);
			if (gpC_Imm!=NULL && gpC_Imm->IsDevice())
			{
				gpC_Imm->ForceSound( strFilename );
			}
		}
		*/
		
		//reuse ++;
	}	

	__END_PROFILE("PlaySound2")
}

void PlaySoundForce(TYPE_SOUNDID soundID)
{
	__BEGIN_PROFILE("PlaySound2")

	//-----------------------------------------------------------
	// ���ǵ��� �ʴ� sound ID�� ���..
	//-----------------------------------------------------------
	if (!g_DXSound.IsInit() || soundID >= (*g_pSoundTable).GetSize()
		)
	{
		__END_PROFILE("PlaySound2")
		return;
	}

	//-----------------------------------------------------------
	// �ʴ� �Ҹ��� �� �ִ� ���� ����
	//-----------------------------------------------------------
	// player�� �Ҹ��� ������ �ʿ䰡 ����.
	//if (g_SoundPerSecond > g_pClientConfig->MAX_SOUND_PER_SECOND)
	//{
	//	__END_PROFILE("PlaySound2")
		//return;
	//}

	//-----------------------------------------------------------
	// ������ --> Load & Play
	//-----------------------------------------------------------
	if ((*g_pSoundManager).IsDataNULL(soundID))
	{
		const char* pFilename = (*g_pSoundTable)[soundID].Filename;

		if (pFilename==NULL)
		{
			__END_PROFILE("PlaySound2")
			return;
		}

		char strFilename[256];
		strcpy(strFilename, pFilename);
 		LPDIRECTSOUNDBUFFER pBuffer = g_DXSound.LoadWav( strFilename );
		//LPDIRECTSOUNDBUFFER	pBuffer = g_pWavePackFileManager->LoadFromFileData(soundID);

		//-----------------------------------------------------------
		// Loading ����
		//-----------------------------------------------------------
		if (pBuffer==NULL)
		{
			(*g_pSoundTable)[soundID].Filename.Release();
			DEBUG_ADD_FORMAT("[Error] Failed to Load WAV. id=%d, fn=%s", soundID, (*g_pSoundTable)[soundID].Filename );
		}
		//-----------------------------------------------------------
		// Load�� ���� ������...
		//-----------------------------------------------------------
		else		
		{
			// Replace������ �������� �޸𸮿��� �����.
			LPDIRECTSOUNDBUFFER pOld;
			if ((*g_pSoundManager).SetData( soundID, pBuffer, pOld )!=0xFFFF)
			{
				pOld->Release();
			}

			g_DXSound.CenterPan( pBuffer );						
		
			g_DXSound.SetMaxVolume(pBuffer);

			// Play
			g_DXSound.Play( pBuffer, false, g_bGoodFPS );	
			
			g_SoundPerSecond++;

			//-------------------------------------------------
			// Force Feel
			//-------------------------------------------------
			//if (gpC_Imm!=NULL && gpC_Imm->IsDevice())
			{
			//	gpC_Imm->ForceSound( pFilename );
			}

			//reload++;
		}
	}
	//-----------------------------------------------------------
	// �ִ� ��� --> Play
	//-----------------------------------------------------------
	else
	{
		LPDIRECTSOUNDBUFFER pBuffer;
		if ((*g_pSoundManager).GetData(soundID, pBuffer))
		{			
			g_DXSound.CenterPan( pBuffer );
		
			g_DXSound.SetMaxVolume(pBuffer);

			g_DXSound.Play( pBuffer, false, g_bGoodFPS );
			g_SoundPerSecond++;
		}


		// Force Feel
		//-------------------------------------------------
		/*
		const char* pFilename = (*g_pSoundTable)[soundID].Filename;

		if (pFilename!=NULL)
		{
			char strFilename[256];
			strcpy(strFilename, pFilename);
			if (gpC_Imm!=NULL && gpC_Imm->IsDevice())
			{
				gpC_Imm->ForceSound( strFilename );
			}
		}
		*/
		
		//reuse ++;
	}	

	__END_PROFILE("PlaySound2")
}

//-----------------------------------------------------------------------------
// Stop Sound
//-----------------------------------------------------------------------------
void	
StopSound(TYPE_SOUNDID soundID)
{
	//-----------------------------------------------------------
	// ���ǵ��� �ʴ� sound ID�� ���..
	//-----------------------------------------------------------
	if (!g_DXSound.IsInit() || soundID == SOUNDID_NULL)
		return;

	//-----------------------------------------------------------
	// ���ǵ��� �ʴ� sound ID�� ���..
	//-----------------------------------------------------------
	if (soundID == SOUNDID_NULL)
		return;

	//-----------------------------------------------------------
	// ������ --> �׳� return
	//-----------------------------------------------------------
	if (soundID < g_pSoundManager->GetMaxIndex())
	{
		if ((*g_pSoundManager).IsDataNULL(soundID))
		{
			return;
		}
		//-----------------------------------------------------------
		// �ִ� ��� --> Stop
		//-----------------------------------------------------------
		else
		{
			LPDIRECTSOUNDBUFFER pBuffer;
			if ((*g_pSoundManager).GetData(soundID, pBuffer))
			{	
				g_DXSound.Stop( pBuffer );
			}	
		}
	}
}

//---------------------------------------------------------------------------
// Play Music Current Zone
//---------------------------------------------------------------------------
// ������ �ٲ۴�.
//---------------------------------------------------------------------------
void		
PlayMusicCurrentZone()
{
	// �ð��� ���� play
	if(g_pEventManager->GetEventByFlag(EVENTFLAG_NOT_PLAY_SOUND))
		return;
	
	const MUSIC_ID musicByTime[] = 
	{
		MUSIC_LIVE_OR_DEAD,
		MUSIC_WINDMILL,
		MUSIC_WINDMILL,
		MUSIC_TREASURE,
		MUSIC_MARCHING,
		MUSIC_WHISPER,
		MUSIC_HELL_KNIGHT,
		MUSIC_LUNATIC,
		MUSIC_SAY_AGAIN,
		MUSIC_HIDE_AWAY,
		MUSIC_HELL_KNIGHT,
		MUSIC_HOLLOWEEN,		
	};


	// �ð��� ���� play
	const MUSIC_ID musicByTimeXmas[] = 
	{
		MUSIC_XMAS_SILENTNIGHT,
		MUSIC_XMAS_SILENTNIGHT,
		MUSIC_XMAS_SILVERBELL,
		MUSIC_XMAS_SILVERBELL,
		MUSIC_XMAS_JINGLEBELL,
		MUSIC_XMAS_JINGLEBELL,
		MUSIC_XMAS_JINGLEBELL,
		MUSIC_XMAS_JINGLEBELL,
		MUSIC_XMAS_SILVERBELL,
		MUSIC_XMAS_SILVERBELL,
		MUSIC_XMAS_SILENTNIGHT,
		MUSIC_XMAS_SILENTNIGHT
	};
	
	const MUSIC_ID musicByHolyLand[] =
	{
		MUSIC_HOLYLAND,
		MUSIC_HOLYLAND_WAR,
		MUSIC_OCTAVUS,
		MUSIC_SEPTIMUS,
		MUSIC_TERTIUS,
		MUSIC_QUARTUS,
	};

	// ũ�������� �̺�Ʈ ��¥ üũ
//	SYSTEMTIME st;
//	GetLocalTime( &st ); 
	
	// ũ���������� ũ�������� �뷡�� Ʋ���ش�.
	int newMusicID;

	// ���������ΰ�?
	int zoneID	= (g_bZonePlayerInLarge?g_nZoneLarge : g_nZoneSmall);
	ZONETABLE_INFO* pZoneInfo = g_pZoneTable->Get( zoneID );	
	bool bSafetyZone = (pZoneInfo!=NULL && pZoneInfo->Safety);

//	if (bSafetyZone 
//		&& st.wMonth==12 && st.wDay>=17 && st.wDay<=25)
//	{
//		newMusicID = musicByTimeXmas[ (g_pGameTime->GetHour() / 2) % 12 ];
//	}
//	else
	if( pZoneInfo->HolyLand && g_pUserOption->PlayWaveMusic)
	{
		switch ( zoneID )
		{
		case 1201 :
		case 1211 :
		case 1212 :
			newMusicID = musicByHolyLand[2];
			break;
		case 1202 :
		case 1221 :
		case 1222 :
			newMusicID = musicByHolyLand[4];
			break;
		case 1203 :
		case 1231 :
		case 1232 :
			newMusicID = musicByHolyLand[3];
			break;
		case 1204 :
		case 1241 :
		case 1242 :
			newMusicID = musicByHolyLand[5];
			break;
		case 1205 :
		case 1251 :
		case 1252 :
			newMusicID = musicByHolyLand[2];
			break;
		case 1206 :
		case 1261 :
		case 1262 :
			newMusicID = musicByHolyLand[4];
			break;
		default :
			if(g_pWarManager->IsExist( zoneID ) )
				newMusicID = musicByHolyLand[1];
			else
				newMusicID = musicByHolyLand[0];
			break;
		}
	} else 
	{
		newMusicID = musicByTime[ (g_pGameTime->GetHour() / 2) % 12 ];
	}	
	// 2004, 7, 6 sobeit add start - ���巹 ���� ����� - bgm�� info���� ���� ���� �ʴ°���..
	if(zoneID == 1410 || zoneID == 1411)
		newMusicID = MUSIC_ILLUSIONS_WAY;
	else if(zoneID == 1412 || zoneID == 1413)
		newMusicID = MUSIC_GDR_LAIR;
	// 2004, 7, 6 sobeit add start

	if (g_Mode==MODE_GAME && g_pZone!=NULL && g_pUserOption->PlayMusic)
	{
		//int zondID = (g_bZonePlayerInLarge? g_nZoneLarge : g_nZoneSmall);

		//ZONETABLE_INFO* pZoneInfo = (*g_pZoneTable).Get( zondID );

		//if (pZoneInfo!=NULL)
		{
			//------------------------------------------
			// ������ ���� ������ �޶�����.
			//------------------------------------------
			//TYPE_MUSICID	newMusicID = 0;

			//if (g_pPlayer!=NULL && g_pPlayer->IsSlayer())
			{		
			//	newMusicID = pZoneInfo->MusicIDSlayer;
			}
			//else
			{
			//	newMusicID = pZoneInfo->MusicIDVampire;
			}

			int musicID = newMusicID;

			if (musicID!=MUSICID_NULL)
			{
				if (g_pUserOption->PlayWaveMusic)
				{
#ifdef __USE_MP3__
					DEBUG_ADD("MP3 OPEN1");
					g_pMP3->Open( (*g_pMusicTable)[ musicID ].FilenameWav );
					DEBUG_ADD("MP3 OPEN1 OK");
					DEBUG_ADD("MP3 PLAY3");
					g_pMP3->Play( false );
					DEBUG_ADD("MP3 PLAY3 OK");
//					g_pDXSoundStream->Load( (*g_pMusicTable)[ musicID ].FilenameWav );
//					g_pDXSoundStream->Play( FALSE );
#else
					if( g_oggfile != NULL )
						fclose(g_oggfile);

					g_oggfile = NULL;

					if( g_DXSound.IsInit() )
					{
						g_pOGG->streamClose();
						g_oggfile = fopen( (*g_pMusicTable)[ musicID ].FilenameWav, "rb");
						if( g_oggfile != NULL )
						{
							// 2004, 11, 8, sobeit add start - �׳� ���� üũ
							if(SOUND_ERR_OK == g_pOGG->streamLoad( g_oggfile, NULL ))
							{
								if(SOUND_ERR_OK == g_pOGG->streamPlay( SOUND_PLAY_ONCE ))
								{
									int volume = (g_pUserOption->VolumeMusic - 15) * 250;
									g_pOGG->streamVolume( max( -10000, min( -1, volume ) ) );
								}
							}
							// 2004, 11, 8, sobeit add end - �׳� ���� üũ
						}
					}
#endif
				}
				else
				{
					g_Music.Play( (*g_pMusicTable)[ musicID ].Filename );
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
// Set Weather
//---------------------------------------------------------------------------
// ������ �ٲ۴�.
//---------------------------------------------------------------------------
void		
SetWeather(int weather, int level)
{
	static int previousWeather = weather;

	//---------------------------------------------
	// ������ ������ ���õ� Sound�� ���ش�.
	//---------------------------------------------
	StopSound( g_previousSoundID );
	

	DEBUG_ADD_FORMAT("[Set Weather] %d, %d", weather, level);
	
	//---------------------------------------------
	// ���� ������ ����...
	//---------------------------------------------
	if(previousWeather == WEATHER_SPOT)
		g_pWeather->Release();
	
	switch (weather)
	{
		//------------------------------
		// ���� ����
		//------------------------------
		case WEATHER_CLEAR :	
			// ������ �� ���� ����������...
			if (previousWeather==WEATHER_RAINY)
			{
				if (g_pTopView!=NULL && g_pTopView->IsInit())
				{
					g_pTopView->ClearShadowManager();
				}
			}
			
			g_pWeather->Stop();
			g_previousSoundID = SOUNDID_NULL;
		break;

		//------------------------------
		// ��
		//------------------------------
		case WEATHER_RAINY :
			// ������ ���� �������ٸ�...
			if (previousWeather!=WEATHER_RAINY)
			{
				if (g_pTopView!=NULL && g_pTopView->IsInit())
				{
					g_pTopView->ClearShadowManager();
				}
			}

			g_pWeather->SetRain( level<<3 );

			// 2�� �� �� ���� �ö��� �Ҹ�
			g_previousSoundID = (level>=15)? SOUND_WORLD_WEATHER_RAIN_2 : SOUND_WORLD_WEATHER_RAIN_1; 
			
			// �ݺ��ؼ� �� �Ҹ� ����...
			PlaySound( g_previousSoundID , 
						true, 
						g_pPlayer->GetX(), g_pPlayer->GetY() );
		break;

		//------------------------------
		// ��
		//------------------------------
		case WEATHER_SNOWY  :
			// ������ �� ���� ����������...
			if (previousWeather==WEATHER_RAINY)
			{
				if (g_pTopView!=NULL && g_pTopView->IsInit())
				{
					g_pTopView->ClearShadowManager();
				}
			}

			g_pWeather->SetSnow( level<<3 );
			g_previousSoundID = SOUNDID_NULL;
		break;

		//------------------------------
		// Spot
		//------------------------------
		case WEATHER_SPOT  :
			// ������ �� ���� ����������...
			if (previousWeather==WEATHER_RAINY)
			{
				if (g_pTopView!=NULL && g_pTopView->IsInit())
				{
					g_pTopView->ClearShadowManager();
				}
			}
			
			g_pWeather->SetSpot( level<<3 );
			g_previousSoundID = SOUNDID_NULL;
			break;
	}

	previousWeather = weather;

	DEBUG_ADD("[Set Weather] OK");
}

//---------------------------------------------------------------------------
// Set Lightning
//---------------------------------------------------------------------------
void
SetLightning(DWORD delay)
{
	DEBUG_ADD("[Set Lightning]");
	
	//---------------------------------------------
	// ���� ǥ��..
	//---------------------------------------------
	if (g_pTopView!=NULL && g_pTopView->IsInit())
	{
		g_pTopView->SetFadeStart(1, 31, 10, 31,31,31);
	}

	// 1�� ���� �Ÿ��� ������.. THUNDER1
	// �� �ָ� THUNDER2
	TYPE_SOUNDID sid = (delay<=1000)? SOUND_WORLD_WEATHER_THUNDER_1 : SOUND_WORLD_WEATHER_THUNDER_2;

	// sound�� ����ص״ٰ� ���߿� ����Ѵ�.
	SOUND_NODE* pNode = new SOUND_NODE( sid, delay, g_pPlayer->GetX(), g_pPlayer->GetY() );

	g_pZone->AddSound( pNode );
}

//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileOpenBinary(const char* filename, class ifstream& file)
{
	if (file.is_open())
	{
		file.close();
	}

	file.open(filename, ios::binary | ios::nocreate);
	
	if (!file.is_open())
	{
		/*
		DEBUG_ADD_FORMAT("[Error] File Open Error : [%s]", filename);
		*/
		InitFail("[Error] File Open Error : [%s]", filename);
		return false;
	}

	/*
	DEBUG_ADD_FORMAT("File Open OK : [%s]", filename);
	*/
	return true;
}

//---------------------------------------------------------------------------
// Update Input
//---------------------------------------------------------------------------
void
UpdateInput()
{
	// Input Event
	//g_pDXInput->PollJoy();
	//g_pDXInput->PollKey();
	//g_pDXInput->PollMouse();    
	if (g_pDXInput!=NULL)
	{
		g_pDXInput->UpdateInput();
	}

	//---------------------------------------------------
	//
	// mouse
	//
	//---------------------------------------------------		
	/*
	static int xSign = 0;
	static int ySign = 0;
	static int mouseStep = 1;
	
	// ��ȣ ����
	int xSignNew = 0;
	int ySignNew = 0;

	if (g_pDXInput->m_mouse_x)
	{
		xSignNew = (g_pDXInput->m_mouse_xdata > 0)? 1: -1;
	}

	if (g_pDXInput->m_mouse_y)
	{
		ySignNew = (g_pDXInput->m_mouse_ydata > 0)? 1: -1;
	}

	//------------------------------------------------------
	// ������ ����
	//------------------------------------------------------
	if (xSignNew==0 && ySignNew==0)
	{		
		mouseStep = 6;
	}
	//------------------------------------------------------
	// ������ ���
	//------------------------------------------------------
	else
	{
		//------------------------------------------------------
		// ���� �������� �̵��ϸ�..
		//------------------------------------------------------
		if (xSignNew==xSign && ySignNew==ySign)
		{
			// �ִ� mouse �̵� pixel����
			if (abs(mouseStep) < 20)
			{
				mouseStep ++;
			}
		}
		//------------------------------------------------------
		// �ٸ� �������� �̵��ϴ� ���
		//------------------------------------------------------
		else
		{
			mouseStep = 6;			
		}

		xSign = xSignNew;
		ySign = ySignNew;

		// Ŀ���� ������ �ش�.
		int step = mouseStep >> 1;
		if (g_pDXInput->m_mouse_x) g_x += g_pDXInput->m_mouse_xdata * (step? step : 1);
		if (g_pDXInput->m_mouse_y) g_y += g_pDXInput->m_mouse_ydata * (step? step : 1);
	}
	*/

	

	//sprintf(g_pDebugMessage->GetCurrent(), "(%d, %d)", g_pDXInput->m_mouse_xdata, g_pDXInput->m_mouse_ydata);
	//g_pDebugMessage->Next();
	
	
	//if (g_pDXInput->m_mouse_x) g_x += g_pDXInput->m_mouse_xdata*3;
	//if (g_pDXInput->m_mouse_y) g_y += g_pDXInput->m_mouse_ydata*3;	

	// Cursor�� position�� ����.
	/*
	POINT point;
	GetCursorPos(&point);
	g_x = point.x;
	g_y = point.y;


	//-----------------------------------------------
	// Mouse Cursor�� ������ ������ �ʵ��� �Ѵ�.
	//-----------------------------------------------
	if (g_x<0) g_x=0;
	else if (g_x>=SURFACE_WIDTH) g_x=SURFACE_WIDTH-1;
	if (g_y<0) g_y=0;
	else if (g_y>=SURFACE_HEIGHT) g_y=SURFACE_HEIGHT-1;
	*/
	// - -;;
	//g_pDXInput->SetMousePosition( g_x, g_y );

	//-----------------------------------------------
	// ���� �Էµ� ���� CInputManager�� ����
	//-----------------------------------------------
	/*
	g_InputManager.SetPosition( g_x, g_y );

	if (g_pDXInput->m_lbutton_down)	g_InputManager.SetLButtonDown();
	if (g_pDXInput->m_lbutton_up)	g_InputManager.SetLButtonUp();
	if (g_pDXInput->m_rbutton_down)	g_InputManager.SetRButtonDown();
	if (g_pDXInput->m_rbutton_up)	g_InputManager.SetRButtonUp();
	*/}

//---------------------------------------------------------------------------
// Update Mouse
//---------------------------------------------------------------------------
void
UpdateMouse()
{
	// Cursor�� position�� ����.
	POINT point;
	GetCursorPos(&point);
	// add by svi
	ScreenToClient(g_hWnd, &point); 
	// end
//	RECT rc;
//	GetWindowRect(g_hWnd, &rc);
	g_x = point.x;
	g_y = point.y;


	//-----------------------------------------------
	// Mouse Cursor�� ������ ������ �ʵ��� �Ѵ�.
	//-----------------------------------------------
	if (g_x<0) g_x=0;
	else if (g_x>=g_GameRect.right) g_x=g_GameRect.right-1;
	if (g_y<0) g_y=0;
	else if (g_y>=g_GameRect.bottom) g_y=g_GameRect.bottom-1;

}

//---------------------------------------------------------------------------
// keep Connection
//---------------------------------------------------------------------------
void
KeepConnection()
{
	/*
	// CGVerifyTime�� �����Ƿ� ���� �ʿ����.
	#ifdef CONNECT_SERVER	
		if (
			#ifndef _DEBUG		// debug���������� ������ KeepConnection�̴�.
				(g_pUserInformation->KeepConnection || g_pUserInformation->IsMaster)
				&&				
			#endif
			g_pSocket!=NULL)
	
		{
			static DWORD lastTime = g_CurrentTime;

			//------------------------------------------------------------------
			// 3�� ���� �ѹ��� garbarge packet�� ������.
			//------------------------------------------------------------------
			if (g_CurrentTime - lastTime > 180000)		// 3 * 60 * 1000
			{
				#ifdef	CONNECT_SERVER			
					CGSay _CGSay;
					_CGSay.setMessage( "*" );
					g_pSocket->sendPacket( &_CGSay );			
				#endif

				lastTime = g_CurrentTime;
			}
		}
	#endif
	*/
}

//---------------------------------------------------------------------------
// Update Disconnected
//---------------------------------------------------------------------------
void
UpdateDisconnected()
{
	DEBUG_ADD("UpdateDisconnected : Start Process");
	
	//--------------------------------------------------
	// socket����
	//--------------------------------------------------
	ReleaseSocket();

	//--------------------------------------------------
	// �Ҹ� ����
	//--------------------------------------------------
	StopSound( g_previousSoundID );
	StopSound( SOUND_WORLD_PROPELLER );

	//--------------------------------------------------
	// ���� �����.
	//--------------------------------------------------
	if (g_pUserOption->PlayWaveMusic)
	{
//		g_pDXSoundStream->Stop();
		DEBUG_ADD("MP3 STOP5");
#ifdef __USE_MP3__
		g_pMP3->Stop();
#else
		if( g_DXSound.IsInit() )
			g_pOGG->streamClose();
#endif
		DEBUG_ADD("MP3 STOP5 OK");
	}
	else
	{
		g_Music.Stop();
	}

	DEBUG_ADD("UpdateDisconnected : Stop Music OK");
	
	//--------------------------------------------------
	// Thread Loading ����..
	//--------------------------------------------------
	StopLoadingThread();

	DEBUG_ADD("UpdateDisconnected : Stop Thread OK");
	
	//--------------------------------------------------
	// game object�� ����
	//--------------------------------------------------
	ReleaseGameObject();

	DEBUG_ADD("UpdateDisconnected : Release GameObject OK");
	
	//------------------------------------------------------
	// dialog�� �� �ݱ�.
	//------------------------------------------------------
	gC_vs_ui.CloseOption();
//	gC_vs_ui.CloseInfo();
//	gC_vs_ui.CloseShop();
	//UI_SetShop( NULL );
	//gC_vs_ui.CloseSkillTree();
	//gC_vs_ui.CloseGameMenu();
	//gC_vs_ui.CloseUserRegistrationWindow();
	
//	DEBUG_ADD("UpdateDisconnected : ServerDisc");
//	gC_vs_ui.ServerDisconnectMessage();
//	DEBUG_ADD("UpdateDisconnected : ServerDisc OK");

//	g_pUIDialog->CloseHelpDlg();
	g_pUIDialog->CloseMessageDlg();
	g_pUIDialog->ClosePCTalkDlg();

	DEBUG_ADD("UpdateDisconnected : Close All Dialog OK");
	

	//--------------------------------------------------
	// ���� ����ٴ� dialog
	//--------------------------------------------------
	// �ʻ�~ �ӽ� �ڵ�..
	CSpritePack		SPK;
	CFileIndexTable	FIT;
	
	class ifstream indexFile(g_pFileDef->getProperty("FILE_SPRITEINDEX_UI").c_str(), ios::binary);
	FIT.LoadFromFile( indexFile );
	indexFile.close();

	SPK.Init( FIT.GetSize() );
	
	// return�� ���� ������...
	CSprite* pSpriteDisconected = &SPK[ SPRITEID_DISCONNECTED ];
	CSprite* pSpriteDisconectedCloseFocused = &SPK[ SPRITEID_DISCONNECTED_CLOSE_FOCUSED ];
	CSprite* pSpriteDisconectedClosePushed = &SPK[ SPRITEID_DISCONNECTED_CLOSE_PUSHED ];

	if (pSpriteDisconected->IsNotInit() 
		|| pSpriteDisconectedCloseFocused->IsNotInit()
		|| pSpriteDisconectedClosePushed->IsNotInit())
	{
		class ifstream spkFile(g_pFileDef->getProperty("FILE_SPRITE_UI").c_str(), ios::binary);
		
		if (pSpriteDisconected->IsNotInit())
		{
			spkFile.seekg(FIT[SPRITEID_DISCONNECTED], ios::beg);
			pSpriteDisconected->LoadFromFile( spkFile );
		}

		if (pSpriteDisconectedCloseFocused->IsNotInit())
		{
			spkFile.seekg(FIT[SPRITEID_DISCONNECTED_CLOSE_FOCUSED], ios::beg);
			pSpriteDisconectedCloseFocused->LoadFromFile( spkFile );		
		}

		if (pSpriteDisconectedClosePushed->IsNotInit())
		{
			spkFile.seekg(FIT[SPRITEID_DISCONNECTED_CLOSE_PUSHED], ios::beg);
			pSpriteDisconectedClosePushed->LoadFromFile( spkFile );		
		}

		spkFile.close();
	}

	DEBUG_ADD("UpdateDisconnected : Load Disconnected Dialog OK");
	
	//--------------------------------------------------
	// ���� ����ٴ� �� ���� �ѹ� ����ش�.
	//--------------------------------------------------
//	if (CDirect3D::IsHAL())
//	{
//		POINT point;
//		if (CDirect3D::GetDevice()->BeginScene()!=D3D_OK)
//		{
//			return;
//		}
//
//		//gC_vs_ui.Show();
//
//		//-----------------------------------------------------------------
//		// Disconnected dialog
//		//-----------------------------------------------------------------
//		g_pBack->Lock();
//		
//		point.x = 400 - (pSpriteDisconected->GetWidth()>>1);
//		point.y = 300 - (pSpriteDisconected->GetHeight()>>1);
//
//		g_pBack->BltSprite( &point, pSpriteDisconected );
//
////		const int maskX = 116;
////		const int maskY = 109;
////		point.x = 400 - (pSpriteDisconected->GetWidth()>>1) + maskX;
////		point.y = 300 - (pSpriteDisconected->GetHeight()>>1) + maskY;
////		g_pBack->BltSprite( &point, pSpriteDisconectedMask );
//
//		g_pBack->Unlock();
//
//		//gC_vs_ui.MouseControl(M_MOVING, g_x, g_y);
//		//gC_vs_ui.DrawMousePointer();
//	
//		CDirect3D::GetDevice()->EndScene();
//	}
//	else
	{
		//gC_vs_ui.Show();
		POINT point;

		//-----------------------------------------------------------------
		// Disconnected dialog
		//-----------------------------------------------------------------
		g_pLast->Lock();
		
		point.x = (g_GameRect.right / 2)  - (pSpriteDisconected->GetWidth()>>1);
		point.y = (g_GameRect.bottom / 2) - (pSpriteDisconected->GetHeight()>>1);

		g_pLast->BltSprite( &point, pSpriteDisconected );

//		const int maskX = 116;
//		const int maskY = 109;
//		point.x = 400 - (pSpriteDisconected->GetWidth()>>1) + maskX;
//		point.y = 300 - (pSpriteDisconected->GetHeight()>>1) + maskY;
//		g_pBack->BltSprite( &point, pSpriteDisconectedMask );

		g_pLast->Unlock();

		//gC_vs_ui.MouseControl(M_MOVING, g_x, g_y);
		//gC_vs_ui.DrawMousePointer();

		//-----------------------------------------------------------------
		// Last�� Back���� copy - 3D HAL�� �ƴ� ��츸..
		//-----------------------------------------------------------------
		point.x = 0;
		point.y = 0;
		RECT rect = { 0, 0, g_GameRect.right, g_GameRect.bottom };

		g_pBack->BltNoColorkey( &point, g_pLast, &rect );	
	}	

	CDirectDraw::Flip();	

	DEBUG_ADD("UpdateDisconnected : Draw Disconnected Dialog Once OK");
	
	
	//------------------------------------------------------
	// Main ȭ��..
	//------------------------------------------------------
//	gC_vs_ui.StartTitle();
	
	DEBUG_ADD("UpdateDisconnected : UI Start Title OK");
	
	//------------------------------------------------------
	// ALT + TAB ���°� �ƴ� ��
	//------------------------------------------------------
	extern bool	g_bTestMode;
	if (g_bActiveGame
#ifdef OUTPUT_DEBUG
		|| g_bTestMode
#endif
		)
	{
		DEBUG_ADD("UpdateDisconnected : Wait For Press Key");
		
		const int closeX	= 111;
		const int closeY	= 69;
		const int closeWidth = 198;
		const int closeHeight = 20;

		BOOL bClickClose = FALSE, bClickFocused = FALSE;
		
		MSG                         msg;

		while (1)
		{
			// UI���� �Է��� ���ƾ� �Ǵµ�...
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
			{	
				if (!GetMessage(&msg, NULL, 0, 0))
					break;
					//return msg.wParam;

				if (msg.message!=WM_KEYDOWN 
					&& msg.message!=WM_CHAR 
					&& msg.message!=WM_KEYUP
					&& msg.message!=WM_IME_COMPOSITION
					&& msg.message!=WM_IME_STARTCOMPOSITION
					&& msg.message!=WM_IME_ENDCOMPOSITION)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		
			UpdateInput();
			UpdateMouse();

			POINT point;
			
			RECT rectClose;
			rectClose.left = g_GameRect.right /2 - (pSpriteDisconected->GetWidth()>>1) + closeX;
			rectClose.top = g_GameRect.bottom /2 - (pSpriteDisconected->GetHeight()>>1) + closeY;
			rectClose.right = rectClose.left + closeWidth;
			rectClose.bottom = rectClose.top + closeHeight;

			if (g_pDXInput->KeyDown(DIK_ESCAPE)
				|| g_pDXInput->KeyDown(DIK_NUMPADENTER)
				|| g_pDXInput->KeyDown(DIK_RETURN)
				|| g_pDXInput->KeyDown(DIK_LMENU)
				|| g_pDXInput->KeyDown(DIK_RMENU)
				|| g_pDXInput->KeyDown(DIK_TAB)
				|| g_pDXInput->KeyDown(DIK_SPACE))
			{
				break;
			}

			if (g_x > rectClose.left && g_x < rectClose.right
				&& g_y > rectClose.top && g_y < rectClose.bottom)
			{
				bClickFocused = TRUE;
			}
			else bClickFocused = FALSE;

			if (g_pDXInput->m_lb_down)
			{		
				if (g_x > rectClose.left && g_x < rectClose.right
					&& g_y > rectClose.top && g_y < rectClose.bottom)
				{
					bClickClose = TRUE;
				}
			}

			if (g_pDXInput->m_lb_up)
			{
				if (bClickClose)
				{
					if (g_x > rectClose.left && g_x < rectClose.right
						&& g_y > rectClose.top && g_y < rectClose.bottom)
					{
						break;
					}
				}

				bClickClose = FALSE;
			}
		

//			if (CDirect3D::IsHAL())
//			{
//				if (CDirect3D::GetDevice()->BeginScene()!=D3D_OK)
//				{
//					return;
//				}
//
//				gC_vs_ui.Show();
//
//				//-----------------------------------------------------------------
//				// Disconnected dialog
//				//-----------------------------------------------------------------
//				g_pBack->Lock();
//				
//				point.x = 400 - (pSpriteDisconected->GetWidth()>>1);
//				point.y = 300 - (pSpriteDisconected->GetHeight()>>1);
//
//				g_pBack->BltSprite( &point, pSpriteDisconected );
//
//				if (bClickFocused)
//				{
//					if (g_x > rectClose.left && g_x < rectClose.right
//						&& g_y > rectClose.top && g_y < rectClose.bottom)
//					{
//						point.x = 400 - (pSpriteDisconected->GetWidth()>>1) + closeX;
//						point.y = 300 - (pSpriteDisconected->GetHeight()>>1) + closeY;
//
//						g_pBack->BltSprite( &point, pSpriteDisconectedCloseFocused );
//					}
//				}
//
//				if (bClickClose)
//				{
//					if (g_x > rectClose.left && g_x < rectClose.right
//						&& g_y > rectClose.top && g_y < rectClose.bottom)
//					{
//						point.x = 400 - (pSpriteDisconected->GetWidth()>>1) + closeX;
//						point.y = 300 - (pSpriteDisconected->GetHeight()>>1) + closeY;
//
//						g_pBack->BltSprite( &point, pSpriteDisconectedClosePushed );
//					}
//				}
//
//				g_pBack->Unlock();
//
//				gC_vs_ui.MouseControl(M_MOVING, g_x, g_y);
//				gC_vs_ui.DrawMousePointer();
//			
//				CDirect3D::GetDevice()->EndScene();
//			}
//			else
			{
				gC_vs_ui.Show();

				//-----------------------------------------------------------------
				// Disconnected dialog
				//-----------------------------------------------------------------
				g_pLast->Lock();
				
				point.x = g_GameRect.right /2 - (pSpriteDisconected->GetWidth()>>1);
				point.y = g_GameRect.bottom/2 - (pSpriteDisconected->GetHeight()>>1);

				g_pLast->BltSprite( &point, pSpriteDisconected );

				if (bClickFocused)
				{
					if (g_x > rectClose.left && g_x < rectClose.right
						&& g_y > rectClose.top && g_y < rectClose.bottom)
					{
						point.x = g_GameRect.right /2 - (pSpriteDisconected->GetWidth()>>1) + closeX;
						point.y = g_GameRect.bottom/2 - (pSpriteDisconected->GetHeight()>>1) + closeY;

						g_pBack->BltSprite( &point, pSpriteDisconectedCloseFocused );
					}
				}

				if (bClickClose)
				{
					if (g_x > rectClose.left && g_x < rectClose.right
						&& g_y > rectClose.top && g_y < rectClose.bottom)
					{
						point.x = g_GameRect.right /2 - (pSpriteDisconected->GetWidth()>>1) + closeX;
						point.y = g_GameRect.bottom/2 - (pSpriteDisconected->GetHeight()>>1) + closeY;

						g_pLast->BltSprite( &point, pSpriteDisconectedClosePushed );
					}
				}

				g_pLast->Unlock();

				gC_vs_ui.MouseControl(M_MOVING, g_x, g_y);
				gC_vs_ui.DrawMousePointer();

				//-----------------------------------------------------------------
				// Last�� Back���� copy - 3D HAL�� �ƴ� ��츸..
				//-----------------------------------------------------------------
				point.x = 0;
				point.y = 0;
				RECT rect = { 0, 0, g_GameRect.right, g_GameRect.bottom };

				g_pBack->BltNoColorkey( &point, g_pLast, &rect );	
			}	
			
			CDirectDraw::Flip();

		}
		
		pSpriteDisconected->Release();
		pSpriteDisconectedCloseFocused->Release();
		pSpriteDisconectedClosePushed->Release();

		// 2004, 07, 19 sobeit add start - ������ �����Ҽ� �����ϴ�. Ȯ�� ������ ���� �����ϰ� ����
		if(true == g_pUserInformation->IsAutoLogIn) // �� �ڵ� �α��� �� ����
			SetMode(MODE_QUIT);
		// 2004, 07, 19 sobeit add end

	}
	else
	{
		DEBUG_ADD("UpdateDisconnected : Now ALT+TAB Mode");
		
//		if (CDirect3D::IsHAL())
//		{
//			if (CDirect3D::GetDevice()->BeginScene()!=D3D_OK)
//			{
//				return;
//			}
//
//			gC_vs_ui.Show();	
//
//			gC_vs_ui.MouseControl(M_MOVING, g_x, g_y);
//			gC_vs_ui.DrawMousePointer();
//		
//			CDirect3D::GetDevice()->EndScene();
//		}
//		else
		{
			POINT point;
			
			gC_vs_ui.Show();

			gC_vs_ui.MouseControl(M_MOVING, g_x, g_y);
			gC_vs_ui.DrawMousePointer();

			//-----------------------------------------------------------------
			// Last�� Back���� copy - 3D HAL�� �ƴ� ��츸..
			//-----------------------------------------------------------------
			point.x = 0;
			point.y = 0;
			RECT rect = { 0, 0, g_GameRect.right, g_GameRect.bottom };

			g_pBack->BltNoColorkey( &point, g_pLast, &rect );	
		}	
		
		CDirectDraw::Flip();

		pSpriteDisconected->Release();
		pSpriteDisconectedCloseFocused->Release();
		pSpriteDisconectedClosePushed->Release();
	}

	DEBUG_ADD("UpdateDisconnected : OK");
	
	/*
	//InitFail("Server�� �������� �ʽ��ϴ�.");
	//InitFail("Server���� ������ ���������ϴ�.");
	g_pBack->GDI_Text(101,201, "Server�� �������� �ʽ��ϴ�.", RGB(0,0,0));
	g_pBack->GDI_Text(100,200, "Server�� �������� �ʽ��ϴ�.", RGB(220,220,220));

	g_pBack->GDI_Text(101,221, "[ESC]�� ��������.", RGB(0,0,0));
	g_pBack->GDI_Text(100,220, "[ESC]�� ��������.", RGB(220,220,220));

	CDirectDraw::Flip();

	// return�� ���� ������...
	while (1)
	{
		UpdateInput();
		
		if (g_pDXInput->KeyDown(DIK_ESCAPE))
		{
			break;
		}
	}

	// Titleȭ�� UI����
	//gC_vs_ui.StartTitle();	

	//g_pBack->GDI_Text(101,201, "��� ��ٷ� �ּ���.", RGB(0,0,0));
	//g_pBack->GDI_Text(100,200, "��� ��ٷ� �ּ���.", RGB(220,220,220));
	//CDirectDraw::Flip();
	*/
}

// ok�� ���� �� ����Ǵ� ��.
void RunAfterServerDisconnect()
{

}

//-----------------------------------------------------------------------------
// Select LastSelected Character
//-----------------------------------------------------------------------------
// ������ ������ ĳ���͸� �����ϱ�
//-----------------------------------------------------------------------------
void
SelectLastSelectedCharacter()
{
	if (g_pWorldPlayerConfigTable==NULL)
	{
		g_pWorldPlayerConfigTable = new WorldPlayerConfigTable;
	}

	if (g_pWorldPlayerConfigTable!=NULL
		&& g_pUserInformation!=NULL
		&& g_pServerInformation!=NULL)
	{
		if (g_pWorldPlayerConfigTable->empty())
		{
			g_pWorldPlayerConfigTable->LoadFromFile( g_pFileDef->getProperty("FILE_INFO_PLAYER_INFO").c_str());
		}

		int worldID = g_pServerInformation->GetServerGroupID();

		PlayerConfigTable* pPCTable = g_pWorldPlayerConfigTable->GetPlayerConfigTable( worldID );

		if (pPCTable!=NULL)
		{
			const char* playerID = g_pUserInformation->UserID.GetString();		

			if( strlen( playerID ) >= 12 )
				return;
		
			PlayerConfig* pConfig = pPCTable->GetPlayerConfig( playerID );

			if (pConfig!=NULL)
			{
				gC_vs_ui.SelectCharacter( pConfig->GetLastSlot() );
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Select LastSelected Character
//-----------------------------------------------------------------------------
// ���� ������ ĳ���͸� �����ϱ�
//-----------------------------------------------------------------------------
void
SaveLastSelectedCharacter(int slot)
{
	if (g_pWorldPlayerConfigTable==NULL)
	{
		g_pWorldPlayerConfigTable = new WorldPlayerConfigTable;
	}

	if (g_pWorldPlayerConfigTable!=NULL
		&& g_pServerInformation!=NULL
		&& g_pUserInformation!=NULL)
	{		
		int			worldID		= g_pServerInformation->GetServerGroupID();
		const char* playerID	= g_pUserInformation->UserID.GetString();
		
		PlayerConfigTable* pPCTable = g_pWorldPlayerConfigTable->GetPlayerConfigTable( worldID );

		if (pPCTable==NULL)
		{
			// worldID�� ������ �����ؼ� �߰�
			pPCTable = new PlayerConfigTable;

			g_pWorldPlayerConfigTable->AddPlayerConfigTable( worldID, pPCTable );
		}
		
		PlayerConfig* pConfig = pPCTable->GetPlayerConfig( playerID );

		bool bNewPlayer = false;
		if (pConfig==NULL)
		{
			bNewPlayer = true;

			// playerID�� ������ �����ؼ� �߰�
			pConfig = new PlayerConfig;
			if( playerID != NULL && strlen( playerID ) < 15 )
				pConfig->SetPlayerID( playerID );
			else
				pConfig->SetPlayerID( "DarkEden" );

			pPCTable->AddPlayerConfig( pConfig );
		}		

		int oldSlot = pConfig->GetLastSlot();

		// �׻� �����ϰ� ����..
		//if (oldSlot != slot || bNewPlayer)
		{
			pConfig->SetLastSlot( slot );		

			g_pWorldPlayerConfigTable->SaveToFile( g_pFileDef->getProperty("FILE_INFO_PLAYER_INFO").c_str());
		}
	}
}

//-----------------------------------------------------------------------------
// Set WatchMode ( true || false )
//-----------------------------------------------------------------------------
// �����ϴ� mode..
//-----------------------------------------------------------------------------
void	
SetWatchMode(bool active)
{
	//-------------------------------------------------------------------
	// Player�� Zone���� ����
	// UI �۵� ���ϰ� ����?
	// �̵� ��� ����
	//-------------------------------------------------------------------
	if (active)
	{
		g_pPlayer->SetStop();
		g_pPlayer->SetAction( ACTION_STAND );
		g_pZone->RemovePlayer();

		g_bWatchMode = true;
	}
	//-------------------------------------------------------------------
	//
	//-------------------------------------------------------------------
	else
	{
		g_pPlayer->SetZone(g_pZone);
		g_pZone->SetPlayer();
		g_pPlayer->SetTimeLightSight(g_pPlayer->GetTimeLightSight());

		g_bWatchMode = false;
	}
}

//-----------------------------------------------------------------------------
// Add ClientCreature
//-----------------------------------------------------------------------------
MCreature*
AddClientCreature()
{
	//------------------------------------------------
	// NPC 
	//------------------------------------------------	
	const int hairMaleID[] = 
	{
		ADDONID_HAIR1_MALE,
		ADDONID_HAIR2_MALE,
		ADDONID_HAIR3_MALE
	};

	const int hairFemaleID[] = 
	{
		ADDONID_HAIR1_FEMALE,
		ADDONID_HAIR2_FEMALE,
		ADDONID_HAIR3_FEMALE
	};		

	static MCoat coat1;	coat1.SetItemType( 0 ); coat1.ClearItemOption();
	static MCoat coat2;	coat2.SetItemType( 1 );	coat2.ClearItemOption();
	static MItem* jacket[3] =
	{
		&coat1,		//JACKET_BASIC, 
		&coat1,		//JACKET1 , 
		&coat2		//JACKET2
	};

	static MTrouser	trouser1;	trouser1.SetItemType( 0 ); trouser1.ClearItemOption();
	static MTrouser	trouser2;	trouser2.SetItemType( 1 ); trouser2.ClearItemOption();
	static MItem* pants[3] =
	{
		&trouser1,	//PANTS_BASIC , 
		&trouser1,	//PANTS1 , 
		&trouser2	//PANTS2 ,
	};

	static MHelm helm1; helm1.SetItemType( 0 ); helm1.ClearItemOption(); 
	static MHelm helm2; helm2.SetItemType( 1 ); helm2.ClearItemOption();
	static MItem* helm[3] = 
	{
		NULL,		// NONE
		&helm1,		// HELMET1 ,
		&helm2,		// HELMET2
	};

	static MSword	sword;	sword.SetItemType( 0 );	sword.ClearItemOption();
	static MBlade	blade;	blade.SetItemType( 0 ); blade.ClearItemOption();
	static MGunAR	gunAR;	gunAR.SetItemType( 0 ); gunAR.ClearItemOption();
	static MGunTR	gunSR;	gunSR.SetItemType( 0 ); gunSR.ClearItemOption();
	static MGunSG	gunSG;	gunSG.SetItemType( 0 );	gunSG.ClearItemOption();
	static MGunSMG	gunSMG;	gunSMG.SetItemType( 0 );gunSMG.ClearItemOption();
	static MCross	cross;	cross.SetItemType( 0 );	cross.ClearItemOption();
	static MMace	mace;	mace.SetItemType( 0 ); mace.ClearItemOption();
	static MItem* weapon[11] =
	{
		NULL,		//WEAPON_NONE ,
		&sword,		//WEAPON_SWORD ,
		&blade,		//WEAPON_BLADE ,
		NULL,		//WEAPON_SHIELD ,
		&sword,		//WEAPON_SWORD_SHIELD ,
		&gunAR,		//WEAPON_AR ,
		&gunSR,		//WEAPON_SR ,
		&gunSG,		//WEAPON_SG ,
		&gunSMG,	//WEAPON_SMG ,
		&cross,		//WEAPON_CROSS ,			
		&mace
	};

	static MShield shield; shield.SetItemType( 0 ); shield.ClearItemOption();


	const int createPositionY[100] =
	{
		20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
		21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
		22, 22, 22, 22, 22, 22, 22, 22, 22, 22,
		23, 23, 23, 23, 23, 23, 23, 23, 23, 24,
		24, 24, 24, 24, 24, 24, 24, 24, 26, 26,
		25, 25, 25, 25, 25, 25, 27, 27, 27, 27,
		27, 26, 26, 26, 26, 26, 28, 28, 28, 28, 
		28, 29, 29, 29, 30, 30, 30, 30, 31, 31,
		31, 32, 31, 32, 32, 32, 35, 35, 34, 34,
		34, 34, 37, 37, 35, 36, 39, 38, 38, 40			
	};
		

	int creatureID;
	
	while (1)
	{
		creatureID = 1001 + rand()%50000;

		MCreature* pCreature = g_pZone->GetCreature( creatureID );

		if (pCreature==NULL)
		{
			break;
		}
	}

	int x, y;

	//-----------------------------------
	// �� �Դ� Creature
	//-----------------------------------
	if (0)//rand()%2)
	{
		MCreatureWear* pCreature = new MCreatureWear;

		pCreature->SetZone(g_pZone);

		// (*g_pCreatureTable)�� ������ ���� �ϳ�..
		pCreature->SetCreatureType( rand()%2 );

		// Move ������ �ٸ��� �Ѵ�.
		switch (0)//rand()%2)//rand()%3)
		{
			case 0 :
				pCreature->SetGroundCreature();
			break;
		
			case 1 :
				pCreature->SetFlyingCreature();					
			break;
			
			case 2 :
				pCreature->SetUndergroundCreature();
			break;
		}						
		
		while (1)
		{
			x = rand()%(g_pZone->GetWidth()-1)+1;
			y = rand()%(g_pZone->GetHeight()-1)+1;
			//x = rand()%(20-1)+10;
			//y = rand()%(20-1)+20;	// 20~40
			/*
			int p = rand()%100;

			y = createPositionY[p];
			x = 12 - ((40-y)>>1) + (rand()%(41-y));

			if (rand()%2)
			{
				x += rand()%4;
			}
			else
			{
				x -= rand()%4;
			}
			*/

			if (x>=0 && x<g_pZone->GetWidth() 
				&& y>=0 && y<g_pZone->GetHeight())
			{					
				if (g_pZone->GetSector(x,y).IsEmpty())
				{
					pCreature->SetPosition( x, y );
					pCreature->SetServerPosition( x, y );
					break;
				}
			}
		}
		//pCreature->SetID(1000 + y*256 + x);
		
		pCreature->SetID( creatureID );

		// �̸� ���� - �ϴ��� ID��
		//char str[80];
		//sprintf(str, "ID=%d", pCreature->GetID());
		//pCreature->SetName( str );
		
		pCreature->SetDirection(DIRECTION_DOWN);
		pCreature->SetNextAction( ACTION_STAND );

		if (pCreature->IsMale())
		{
			pCreature->SetAddonHair( hairMaleID[rand()%3], 0);		// type, color				
		}
		else
		{
			pCreature->SetAddonHair( hairFemaleID[rand()%3], 0);		// type, color				
		}

		pCreature->SetAddonItem( jacket[rand()%3] );	
		pCreature->SetAddonItem( pants[rand()%3] );	
		pCreature->SetAddonItem( helm[rand()%3] );
		int w = rand()%10;
		pCreature->SetAddonItem( weapon[w] );
		if (w==3 || w==4)
		{
			pCreature->SetAddonItem( &shield );
		}

		

		if (!g_pZone->AddCreature(pCreature))
		{
			delete pCreature;
			return NULL;
		}

		return pCreature;
	}
	//-----------------------------------
	// �� ���� Creature
	//-----------------------------------
	else
	{				
		static int cType = 371;//199//11;
		
		LoadCreatureType( cType );

		MCreature* pCreature;

		if ((*g_pCreatureTable)[cType].pItemWearInfo!=NULL)
		{
			pCreature = new MCreatureWear;

			pCreature->SetCreatureType( cType );//11+rand()%(23-11+1) );

			SetAddonToSlayer( (MCreatureWear*)pCreature, cType );
		}
		else
		{
			pCreature = new MCreature;

			pCreature->SetCreatureType( cType );//11+rand()%(23-11+1) );
		}

		// �����ϴ� Zone�� �����Ѵ�.
		pCreature->SetZone(g_pZone);

		// (*g_pCreatureTable)�� ������ ���� �ϳ�..
		//pCreature->SetCreatureType( (rand()%((*g_pCreatureTable).GetSize()-4))+4 );				
		
		//------------------------------------------------------------
		// ���丮�� ���.. �ϵ��ڵ�(-_-);
		//------------------------------------------------------------
		pCreature->SetStatus( MODIFY_MAX_HP, 100 );
		if (cType==217)
		{
			pCreature->SetStatus( MODIFY_CURRENT_HP, 10 );
			pCreature->SetStatus( MODIFY_ALIGNMENT, -10000 );
		}
		else
		{
			pCreature->SetStatus( MODIFY_CURRENT_HP, rand()%101 );
			pCreature->SetStatus( MODIFY_ALIGNMENT, -5000 + rand()%10000 );
		}
		
		cType++;

		if (cType==g_pCreatureTable->GetSize())
		{
			cType = 296;//104;//11;
		}
		else if (cType==111)
		{
			cType = 197;
		}
		else if (cType==200)
		{
			cType = 208;
		}
		else if (cType==210)
		{
			cType = 217;
		}
		else if (cType==220)
		{
			cType = 229;
		}
		else if (cType==231)
		{
			cType = 239;
		}
		else if (cType==241)
		{
			cType = 250;
		}
		else if (cType==251)
		{
			cType = 256;
		}
		else if (cType==257)
		{
			cType = 266;
		}
		else if (cType==267)
		{
			cType = 276;
		}
		else if (cType==277)
		{
			cType = 286;
		}
		else if (cType==288)
		{
			cType = 318;
		}
		else if (cType==320)
		{
			cType = 328;
		}
		else if (cType==330)
		{
			cType = 338;
		}
		else if (cType==340)
		{
			cType = 348;
		}
		

		pCreature->SetLevelName( rand()%100 );

		//int numGuildMark = g_pTopView->m_GuildSPK();
		//int guildMark = ((numGuildMark==0)? -1 : rand()%numGuildMark);
		//pCreature->SetGuildNumber( guildMark );
		
		if (pCreature->IsVampire())
		{
			pCreature->SetGuildNumber( 1 );
		}
		

		// Move ������ �ٸ��� �Ѵ�.
		switch (0)//rand()%2)//rand()%3)
		{
			case 0 :
				pCreature->SetGroundCreature();
			break;
		
			case 1 :
				pCreature->SetFlyingCreature();
			break;
			
			case 2 :
				pCreature->SetUndergroundCreature();
			break;
		}		

		while (1)
		{
			x = rand()%40 + 10;
			y = rand()%40 + 10;

			//x = rand()%(g_pZone->GetWidth()-1)+1;
			//y = rand()%(g_pZone->GetHeight()-1)+1;
			//x = rand()%(20-1)+10;
			//y = rand()%(20-1)+20;	// 20~40
			/*
			int p = rand()%100;

			y = 140 - createPositionY[p];
			x = 12 - ((40-createPositionY[p])>>1) + (rand()%(41-createPositionY[p]));
			
			if (rand()%2)
			{
				x += rand()%4;
			}
			else
			{
				x -= rand()%4;
			}
			*/

			if (x>=0 && x<g_pZone->GetWidth() 
				&& y>=0 && y<g_pZone->GetHeight())
			{					
				if (g_pZone->GetSector(x,y).IsEmpty())
				{
					pCreature->SetPosition( x, y );
					pCreature->SetServerPosition( x, y );
					break;
				}
			}
		}
		//pCreature->SetID(1000 + y*256 + x);
		pCreature->SetID( creatureID );

				
		// �̸� ���� - �ϴ��� ID��
		//if (pCreature->IsVampire())
		{
			//char str[80];
			//sprintf(str, "ID=%d, Type=%d", pCreature->GetID(), pCreature->GetCreatureType());
			pCreature->SetName( (*g_pCreatureTable)[pCreature->GetCreatureType()].Name.GetString() );

			// �Լ���ü�� Ŭ���̾�Ʈ ����-.-;;; ����-_-;
			if ((pCreature->GetID() & 0x00000007)==7)
			{
				pCreature->SetPlayerParty();
			}
		}
		
		int direction = DIRECTION_LEFTDOWN;

		int creatureType = pCreature->GetCreatureType();
		int spriteType = (*g_pCreatureTable)[creatureType].SpriteTypes[0];
		int frameID = (*g_pCreatureSpriteTable)[spriteType].FrameID;

		if (frameID < g_pTopView->m_CreatureFPK.GetSize())
		{
			if (g_pTopView->m_CreatureFPK[frameID][0][1].GetSize()==0)
			{
				if (g_pTopView->m_CreatureFPK[frameID][0][3].GetSize()!=0)
				{
					direction = DIRECTION_RIGHTDOWN;
				}
				else if (g_pTopView->m_CreatureFPK[frameID][0][2].GetSize()!=0)
				{
					direction = DIRECTION_DOWN;
				}
			}
			else if (g_pTopView->m_CreatureFPK[frameID][0][3].GetSize()==0)
			{
				if (g_pTopView->m_CreatureFPK[frameID][0][3].GetSize()!=0)
				{
					direction = DIRECTION_RIGHTDOWN;
				}
				else if (g_pTopView->m_CreatureFPK[frameID][0][2].GetSize()!=0)
				{
					direction = DIRECTION_DOWN;
				}
			}
			else
			{
				// default
				direction = DIRECTION_LEFTDOWN;
			}
		}				

		pCreature->SetDirection(direction);//DIRECTION_UP);
		pCreature->SetCurrentDirection(direction);
		pCreature->SetNextAction( ACTION_STAND );

		if (!g_pZone->AddCreature(pCreature))
		{
			delete pCreature;
			return NULL;
		}

		// [ TEST CODE ]
		//pCreature->SetChatString( "1234567890abcdefgijklmnopqrstuvwxyz");
		
		// ������ frame���� �����Ѵ�.
		//int end = rand()%20;
		//for (int a=0; a<end; a++)
		//{
		//	pCreature->Action();
		//}

		return pCreature;
	}

	return NULL;
}



//-----------------------------------------------------------------------------
// GetMakeItemFitPosition
//-----------------------------------------------------------------------------
//
// ���������, ��ź/���� �����.. ��� ���ȴ�.
//
// pItem���� ���ؼ� �����Ǵ� item(itemClass, itemType)�� �� ��ġ��
// fitPoint�� ���ؼ� ���� �� �ִ�.
//
// return true�� ��츸 fitPoint�� �� �� �ִ� ��ġ�� ����ȴ�.
// return false�̸� �� ��ġ�� ���ٴ� �ǹ��̴�.
//-----------------------------------------------------------------------------
bool
GetMakeItemFitPosition(MItem* pItem, ITEM_CLASS itemClass, int itemType, POINT& fitPoint)
{
	bool bFindPos = false;	// �ڸ��� �ֳ�?
	
	// �ӽ÷� ������ ���� �� �ڸ��� ã�´�.
	MItem* pResultItem = MItem::NewItem( itemClass );
	pResultItem->SetItemType( itemType );

	if (g_pInventory->GetFitPosition(pResultItem, fitPoint))
	{
		bFindPos = true;

		MItem* pOldItem = g_pInventory->GetItem(fitPoint.x, fitPoint.y);

		// �� ���� �߰��ҷ��� �ϰ�..
		// �ϳ��� �����ִٸ�.. 
		// ���� ��ġ���� �״�� �ٲ۴�.
		if (pOldItem==NULL
			&& pItem->GetNumber()==1)
		{
			fitPoint.x = pItem->GetGridX();
			fitPoint.y = pItem->GetGridY();

			bFindPos = true;
		}									
	}
	else
	{
		// �� �ڸ��� ���� ��쿡
		// �ϳ��� �����ִٸ�.. �� �ڸ����� �ٲٸ� �ȴ�.
		if (pItem->GetNumber()==1)
		{
			fitPoint.x = pItem->GetGridX();
			fitPoint.y = pItem->GetGridY();

			bFindPos = true;
		}
	}

	// �ӽ÷� ����� ����
	delete pResultItem;

	return bFindPos;
}
// 2004, 03, 29 sobeit add start - ���巹 �� ��Ʈ �߰�
void 
Add_GDR_Ghost(int ZoneID)
{
	if(1412 != ZoneID && 1413 != ZoneID) // ���巹 ����, ���巹 �ϵ�
		return;
	CRarFile GhostFile;
	GhostFile.SetRAR("data\\ui\\txt\\TutorialEtc.rpk", "darkeden");
	if(!GhostFile.Open("ghostPos.xml"))
		return;

	XMLTree computerTree;
	XMLParser parser;
	char szTempBuffer[64];
	int MapX = 0, MapY = 0;

	sprintf(szTempBuffer, "PositionList_%d", ZoneID);
	parser.parse( (char *)GhostFile.GetFilePointer(), &computerTree );
	
	const XMLTree *pMapElement = computerTree.GetChild( szTempBuffer );
	if( pMapElement != NULL )
	{
		const size_t GhostMax =pMapElement->GetChildCount();
		
		for( size_t GhostCount = 0; GhostCount < GhostMax; GhostCount++ )
		{
			sprintf(szTempBuffer, "Position%d", GhostCount+1);
			const XMLTree *pGhostPos = pMapElement->GetChild( szTempBuffer );
			if( pGhostPos != NULL )
			{
				const XMLAttribute *pPosX = pGhostPos->GetAttribute( "x" );
				if( pPosX != NULL )
				{
					MapX = pPosX->ToInt();
				}
				const XMLAttribute *pPosY = pGhostPos->GetAttribute( "y" );
				if( pPosY != NULL )
				{
					MapY = pPosY->ToInt();
				}

				// create ghost
				MFakeCreature *pFakeCreature = NewFakeCreature(CREATURETYPE_GHOST, MapX, MapY, rand()%8);

				if (!g_pZone->AddFakeCreature( pFakeCreature ))
				{
					delete pFakeCreature;
					continue;
				}
				pFakeCreature->SetZone(g_pZone);
				pFakeCreature->SetFakeCreatureType(MFakeCreature::FAKE_CREATURE_GHOST);
				pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_UNDERGROUND);
				pFakeCreature->AddEffectStatus( (EFFECTSTATUS)(EFFECTSTATUS_GHOST_1+rand()%2), 0xFFFF );
			}
		}
	}
	GhostFile.Release();
}
// 2004, 03, 29 sobeit add end - ���巹 �� ��Ʈ �߰�

