//-----------------------------------------------------------------------------
// MZoneSoundManager.cpp
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include "MZoneSoundManager.h"
#include "UserOption.h"
#include "CDirectSound.h"
#include "MSoundTable.h"
#include "DebugInfo.h"
#include "MTestDef.h"


#ifdef __GAME_CLIENT__
	#include "CSoundPartManager.h"
	#include "MZone.h"
	#include "MPlayer.h"

	#ifdef __METROTECH_TEST__
		#define OUTPUT_DEBUG_ZONESOUND_PROCESS
	#endif
#endif

//-----------------------------------------------------------------------------
// global
//-----------------------------------------------------------------------------
MZoneSoundTable*	g_pZoneSoundTable = NULL;

MZoneSoundManager*	g_pZoneSoundManager = NULL;

#ifdef __GAME_CLIENT__
	extern DWORD	g_CurrentTime;

	extern CSoundPartManager*	g_pSoundManager;
#endif

//-----------------------------------------------------------------------------
//
//						ZONESOUND_NODE
//
//-----------------------------------------------------------------------------
ZONESOUND_NODE::ZONESOUND_NODE(TYPE_SOUNDID id)
{
	m_SoundID	= id;
	m_pBuffer	= NULL;
	m_X			= -1; 
	m_Y			= -1;
	m_bLoop		= false;
	m_bContinueLoop = false;
}

ZONESOUND_NODE::~ZONESOUND_NODE()
{
	if (m_pBuffer!=NULL)
	{
		m_pBuffer->Stop();
		m_pBuffer->Release();
		m_pBuffer = NULL;
	}
}

//-----------------------------------------------------------------------------
// Save To File
//-----------------------------------------------------------------------------
void					
ZONESOUND_NODE::SaveToFile(class ofstream& file)
{
	// ��� �̰Ŵ� file ������� �ʿ䰡 ����.
}

//-----------------------------------------------------------------------------
// Load From File
//-----------------------------------------------------------------------------
void					
ZONESOUND_NODE::LoadFromFile(class ifstream& file)
{
	// ��� �̰Ŵ� file ������� �ʿ䰡 ����.
}

//-----------------------------------------------------------------------------
// Play
//-----------------------------------------------------------------------------
void
ZONESOUND_NODE::Play(int x, int y, bool bLoop)
{	
#ifdef __GAME_CLIENT__
	//-----------------------------------------------------------
	// �Ҹ� ����ص� �Ǵ��� üũ..
	//-----------------------------------------------------------
	if (!g_DXSound.IsInit() 
		|| m_SoundID >= g_pSoundTable->GetSize()
		|| !g_pUserOption->PlaySound)
	{
		return;
	}

	int playerX = g_pPlayer->GetX();
	int playerY = g_pPlayer->GetY();

	//-----------------------------------------------------------
	// Player�� �Ҹ� �ٿ������� �Ÿ� ���..
	//-----------------------------------------------------------
	int gapX = x - playerX;
	int gapY = y - playerY;

	int dist = max(abs(gapX), abs(gapY));
	
	//-----------------------------------------------------------
	// �̹� ���� ��ġ���� play�ǰ� �ִ� sound�� ���Ѵ�.
	//-----------------------------------------------------------
	if (m_pBuffer!=NULL
		&& m_playerX==playerX && m_playerY==playerY)
	{
		// �Ҹ� ū ���� ���ܵ־� �Ѵ�.
		int oldGapX = m_X - m_playerX;
		int oldGapY = m_Y - m_playerY;

		int oldDist = max(abs(oldGapX), abs(oldGapY));
	
		// ������ �Ҹ��� �� ������ ���ο� �Ҹ��� ����� �ʿ䰡 ����.
		if (oldDist < dist)
		{
			return;
		}
	}

	//-----------------------------------------------------------
	// �� ����
	//-----------------------------------------------------------
	m_X				= x;
	m_Y				= y;
	m_bLoop			= bLoop;
	m_bContinueLoop = bLoop;
	m_playerX		= playerX;
	m_playerY		= playerY;	

	//-----------------------------------------------------------
	// �Ÿ��� ��� ���� �̻��̸� �Ҹ��� ������� �ʾƾ� �Ѵ�.
	//-----------------------------------------------------------
	if (dist < 40)
	{			
		//-----------------------------------------------------------
		// ���� ȭ���� Load�Ǿ����� Ȯ��.. 
		// �ȵ�����.. Load�Ѵ�.
		//-----------------------------------------------------------
		if (m_pBuffer==NULL)
		{
			DEBUG_ADD("[ZONESOUND_NODE] Play:New Buffer");

			//-----------------------------------------------------------
			// ������ --> Load
			//-----------------------------------------------------------
			if (g_pSoundManager->IsDataNULL(m_SoundID))
			{
				DEBUG_ADD("[ZONESOUND_NODE] Load Wave");

				// �ٽ� load						
 				LPDIRECTSOUNDBUFFER pBuffer = g_DXSound.LoadWav( (*g_pSoundTable)[m_SoundID].Filename );

				//-----------------------------------------------------------
				// Loading ����
				//-----------------------------------------------------------
				if (pBuffer==NULL)
				{
					DEBUG_ADD_FORMAT("[Error] Failed to Load WAV. id=%d, fn=%s", m_SoundID, (*g_pSoundTable)[m_SoundID].Filename );

					return;
				}
				else
				//-----------------------------------------------------------
				// Load�� ���� ������...			
				//-----------------------------------------------------------
				{
					// Replace������ �������� �޸𸮿��� �����.
					LPDIRECTSOUNDBUFFER pOld;
					if ((*g_pSoundManager).SetData( m_SoundID, pBuffer, pOld )!=0xFFFF)
					{
						pOld->Release();
					}
					
					//-----------------------------------------------------------
					// Duplicate�ؼ� ������ �ִ´�.
					//-----------------------------------------------------------
					// autoRelease �ϸ� �ȵȴ�.
					m_pBuffer = g_DXSound.DuplicateSoundBuffer(pBuffer, false);
				}
			}
			//-----------------------------------------------------------
			// �ִ� ��� --> Play
			//-----------------------------------------------------------
			else
			{
				DEBUG_ADD("[ZONESOUND_NODE] Already Exist Buffer");

				LPDIRECTSOUNDBUFFER pBuffer;
				if ((*g_pSoundManager).GetData(m_SoundID, pBuffer))
				{			
					//-----------------------------------------------------------
					// Duplicate�ؼ� ������ �ִ´�.
					//-----------------------------------------------------------
					// autoRelease �ϸ� �ȵȴ�.
					m_pBuffer = g_DXSound.DuplicateSoundBuffer(pBuffer, false);
				}
			}
		}

		DEBUG_ADD("[ZONESOUND_NODE] Arrange Volume & Dist");
			
		//-----------------------------------------------------------
		// ��..
		//-----------------------------------------------------------
		if (m_pBuffer!=NULL)
		{
			//-----------------------------------------------------------
			// �¿�  (������. - -;;) ����..
			//-----------------------------------------------------------
			if (gapX > 3)
			{
				g_DXSound.CenterToRightPan( m_pBuffer, (gapX-3) << 7 );
			}
			else if (gapX < -3)
			{
				g_DXSound.CenterToLeftPan( m_pBuffer, (abs(gapX+3)) << 7 );
			}
			else
			{
				g_DXSound.CenterPan( m_pBuffer );
			}

			//-----------------------------------------------------------
			// �Ҹ� ũ�� ����
			//-----------------------------------------------------------
			int sub = (dist << 2) * g_pUserOption->VolumeSound;
			
			g_DXSound.SubVolumeFromMax(m_pBuffer, sub);

			//-----------------------------------------------------------
			// �̹� �������̸� �ٽ� Play���� �ʴ´�.
			// ������ ����� ũ��� ����������...
			//-----------------------------------------------------------
			DEBUG_ADD("[ZONESOUND_NODE] Play Buffer");
	
			if (!g_DXSound.IsPlay( m_pBuffer ))
			{
				g_DXSound.Play( m_pBuffer, m_bLoop );
			}
		}
	}
#endif
}

//-----------------------------------------------------------------------------
// Stop
//-----------------------------------------------------------------------------
void
ZONESOUND_NODE::Stop()
{
	//-----------------------------------------------------------
	//
	//-----------------------------------------------------------
	if (m_pBuffer!=NULL)
	{
		if (g_DXSound.IsPlay( m_pBuffer ))
		{
			g_DXSound.Stop( m_pBuffer );
		}
	}

	m_bContinueLoop = false;
}

//-----------------------------------------------------------------------------
// Stop
//-----------------------------------------------------------------------------
void
ZONESOUND_NODE::StopLoop()
{
	//-----------------------------------------------------------
	//
	//-----------------------------------------------------------
	if (m_pBuffer!=NULL)
	{
		if (g_DXSound.IsPlay( m_pBuffer ))
		{
			m_pBuffer->Play(0, 0, 0);	// loop�� �����.
		}
	}

	m_bContinueLoop = false;
}

//-----------------------------------------------------------------------------
//
//								MZoneSoundTable
//
//-----------------------------------------------------------------------------
MZoneSoundTable::MZoneSoundTable()
{
}

MZoneSoundTable::~MZoneSoundTable()
{
}

//-----------------------------------------------------------------------------
//
//								MZoneSoundManager
//
//-----------------------------------------------------------------------------
MZoneSoundManager::MZoneSoundManager()
{
	m_LastX = -1;
	m_LastY = -1;
	m_LastUpdateTime = 0;
}

MZoneSoundManager::~MZoneSoundManager()
{
}

//-----------------------------------------------------------------------------
// Update Sound
//-----------------------------------------------------------------------------
// Zone�� sound�� ���.. ������ ��µǴ��� ������ ����.
//-----------------------------------------------------------------------------
void			
MZoneSoundManager::UpdateSound()
{
#ifdef __GAME_CLIENT__
	if (g_pZone==NULL 
		|| g_pPlayer==NULL)
	{
		return;
	}
		
	//--------------------------------------------------------------------
	// ���� update�ؾ��� �ð��� �ưų�..
	// Player�� ��ǥ�� �޶��� ���..
	//--------------------------------------------------------------------
	if (g_CurrentTime - m_LastUpdateTime > 5000
		|| g_pPlayer->GetX()!=m_LastX
		|| g_pPlayer->GetY()!=m_LastY)
	{
		#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
			DEBUG_ADD_FORMAT("Get Sector(%d,%d)", g_pPlayer->GetX(), g_pPlayer->GetY());
		#endif

		//--------------------------------------------------------------
		// ���� play�ϰ� �ִ� �Ҹ��鿡 ���ؼ�..
		//--------------------------------------------------------------
		CTypeMap<ZONESOUND_NODE>::iterator iPlaySound = begin();

		while (iPlaySound != end())
		{
			ZONESOUND_NODE* pNode = iPlaySound->second;

			//----------------------------------------------------------
			// Loop�� ���� üũ�غ��� �Ѵ�.
			//----------------------------------------------------------
			pNode->UnSetContinueLoop();
			
			iPlaySound++;
		}

		//--------------------------------------------------------------
		// sector�� sound������ �о�´�.
		//--------------------------------------------------------------
		const MSector& sector = g_pZone->GetSector( g_pPlayer->GetX(), g_pPlayer->GetY() );

		const SECTORSOUND_LIST& listSectorSound = sector.GetSectorSoundList();

		SECTORSOUND_LIST::const_iterator iSound = listSectorSound.begin();

		#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
			DEBUG_ADD_FORMAT("listSectorSound. size=%d", listSectorSound.size());	
		#endif

		//--------------------------------------------------------------
		// ������ ZoneSound�� ���ؼ� play�Ѵ�.
		//--------------------------------------------------------------
		while (iSound != listSectorSound.end())
		{
			const SECTORSOUND_INFO& soundInfo = *iSound;

			int zoneSoundID = soundInfo.ZoneSoundID;
			int x = soundInfo.X;
			int y = soundInfo.Y;

			#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
				DEBUG_ADD_FORMAT("SectorSoundInfo. id=%d, (%d, %d)", zoneSoundID, x, y);
			#endif

			ZONESOUND_INFO* pInfo = g_pZoneSoundTable->GetData( zoneSoundID );

			//---------------------------------------------------------
			// ���� �ؾ��� �ð��̸�..
			//---------------------------------------------------------
			if (pInfo!=NULL)
			{
				if (pInfo->IsShowTime())
				{
					#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
						DEBUG_ADD("Get ZONESOUND_NODE");
					#endif
	
					ZONESOUND_NODE* pSound = GetData( zoneSoundID );

					//------------------------------------------------------
					// Play
					//------------------------------------------------------
					if (pSound==NULL)
					{
						// ������ �����Ѵ�.
						pSound = new ZONESOUND_NODE( pInfo->SoundID );

						// �߰��ϰ� play
						AddData( zoneSoundID, pSound );						
					}					
					
					#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
						DEBUG_ADD("Before Play");
					#endif

					pSound->Play( x, y, pInfo->Loop );					

					#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
						DEBUG_ADD("After Play");
					#endif

					//------------------------------------------------------
					// ������ ������ �ð��� �����Ѵ�.
					//------------------------------------------------------
					#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
						DEBUG_ADD("Set NextPlayTime");
					#endif

					pInfo->SetNextShowTime();
				}
				//---------------------------------------------------------
				// ������ �ð��밡 �ƴϸ� �Ҹ��� �����.
				//---------------------------------------------------------
				else if (!pInfo->IsShowHour())
				{
					#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
						DEBUG_ADD("[for stop]Get ZONESOUND_NODE");
					#endif

					ZONESOUND_NODE* pSound = GetData( zoneSoundID );

					//------------------------------------------------------
					// Play
					//------------------------------------------------------
					if (pSound!=NULL)
					{
						pSound->Stop();
					}	
				}
				else
				{
					ZONESOUND_NODE* pSound = GetData( zoneSoundID );

					if (pSound->IsLoop())
					{
						pSound->SetContinueLoop();
					}

					#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
						DEBUG_ADD("Skip");
					#endif
				}

			}

			iSound++;
		}

		#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
			DEBUG_ADD("UpdateSectorSound OK");
		#endif

		//--------------------------------------------------------------
		// ���� play�ϰ� �ִ� �Ҹ��鿡 ���ؼ�..
		//--------------------------------------------------------------
		iPlaySound = begin();

		while (iPlaySound != end())
		{
			ZONESOUND_NODE* pNode = iPlaySound->second;

			//----------------------------------------------------------
			// Loop�� ���� ���� sector�� ������ �Ҹ��� ����� �Ѵ�.
			//----------------------------------------------------------
			if (pNode->IsLoop() && !pNode->IsContinueLoop())
			{
				pNode->StopLoop();
			}

			iPlaySound++;
		}

		#ifdef OUTPUT_DEBUG_ZONESOUND_PROCESS
			DEBUG_ADD("zoneSoundNode OK");
		#endif

		//---------------------------------------------------------
		// update ���� ���
		//---------------------------------------------------------
		m_LastX = g_pPlayer->GetX();
		m_LastY = g_pPlayer->GetY();
		m_LastUpdateTime = g_CurrentTime;
	}
#endif
}