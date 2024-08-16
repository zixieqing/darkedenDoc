//---------------------------------------------------------------------------
// ClientFunction.cpp
//---------------------------------------------------------------------------
#include "Client_PCH.h"
#include "ClientFunction.h"
#include "SkillDef.h"
#include "MItemOptionTable.h"

#ifdef __GAME_CLIENT__
	#include "MTopView.h"
	#include "MInventory.h"
	#include "MEffectGeneratorTable.h"
	#include "MActionInfoTable.h"
	#include "MScreenEffectManager.h"
	#include "MScreenEffect.h"	
	#include "UserInformation.h"
	#include "UIFunction.h"
	#include "DebugInfo.h"
	#include "MPlayer.h"
	
	extern MScreenEffectManager* g_pInventoryEffectManager;

	extern bool   g_bZoneSafe;
	extern BOOL g_MyFull;
	extern RECT g_GameRect;
#else
	#include "VS_UI_Base.h"
	#include "CSoundPartManager.h"
	#include "MSoundTable.h"

	CSoundPartManager*		g_pSoundManager = NULL;

	extern HWND	g_hWnd;
#endif

#if !defined(_LIB) && !defined(__GAME_CLIENT__)
	
//-----------------------------------------------------------------------------
// �ʱ�ȭ �� ��,
//-----------------------------------------------------------------------------
void
InitSound()
{
	if (g_pSoundTable==NULL)
	{
		g_pSoundTable = new SOUND_TABLE;
	}

	//------------------------------------------------
	// Load SoundTable
	//------------------------------------------------
	class ifstream soundTable("Data\\Info\\Sound.inf", ios::binary);
	g_pSoundTable->LoadFromFile(soundTable);
	soundTable.close();


	//------------------------------------------------
	// DXSound & SoundManager �ʱ�ȭ
	//------------------------------------------------
	if (g_DXSound.Init(g_hWnd))
	{
		g_pSoundManager = new CSoundPartManager;
		g_pSoundManager->Init( g_pSoundTable->GetSize(), 50 );	// 50���� wav�� loading�Ѵٴ� �ǹ�
	}
}

//-----------------------------------------------------------------------------
// UnInit Sound
//-----------------------------------------------------------------------------
void
UnInitSound()
{
	//-------------------------------------
	// UnInit DirectSound
	//-------------------------------------
	g_pSoundManager->Release();	

	g_DXSound.Release();
}

	//---------------------------------------------------------------------------
	// PlaySound
	//---------------------------------------------------------------------------
	// Client�� �ƴ� ��쿡 ���..
	//---------------------------------------------------------------------------	
	void		
	PlaySound(TYPE_SOUNDID soundID)
	{
		//-----------------------------------------------------------
		// ���ǵ��� �ʴ� sound ID�� ���..
		//-----------------------------------------------------------
		if (!g_DXSound.IsInit() || soundID >= g_pSoundTable->GetSize())
			return;

		//-----------------------------------------------------------
		// ������ --> Load & Play
		//-----------------------------------------------------------
		if (g_pSoundManager->IsDataNULL(soundID))
		{
			// �ٽ� load						
			const char* filename = (*g_pSoundTable)[soundID].Filename.GetString();
 			LPDIRECTSOUNDBUFFER pBuffer = g_DXSound.LoadWav( (char*)filename );

			//-----------------------------------------------------------
			// Loading ����
			//-----------------------------------------------------------
			if (pBuffer==NULL)
			{
			}
			//-----------------------------------------------------------
			// Load�� ���� ������...
			//-----------------------------------------------------------
			else		
			{
				// Replace������ �������� �޸𸮿��� �����.
				LPDIRECTSOUNDBUFFER pOld;
				if (g_pSoundManager->SetData( soundID, pBuffer, pOld )!=0xFFFF)
				{
					pOld->Release();
				}

				// Play
				g_DXSound.Play( pBuffer, false );				
			}
		}
		//-----------------------------------------------------------
		// �ִ� ��� --> Play
		//-----------------------------------------------------------
		else
		{
			LPDIRECTSOUNDBUFFER pBuffer;
			if (g_pSoundManager->GetData(soundID, pBuffer))
			{			
				g_DXSound.Play( pBuffer, false );
			}
		}
	}

	const char*
	GetWhisperID()
	{
		return NULL;
	}

	BOOL
	IsPlayerInSafePosition()
	{
		return FALSE;
	}

	bool
	IsPlayerInSafeZone()
	{
		return false;
	}
#else
	//---------------------------------------------------------------------------
	// Get Whisper ID
	//---------------------------------------------------------------------------
	const char*
	GetWhisperID()
	{
		return g_pUserInformation->WhisperID.GetString();
	}

	BOOL
	IsPlayerInSafePosition()
	{
		if (g_pPlayer!=NULL)
		{
			return g_pPlayer->IsInSafeSector();
		}
		
		return false;
	}

	bool
	IsPlayerInSafeZone()
	{
		return g_bZoneSafe;
	}
#endif

//---------------------------------------------------------------------------
// DrawInventoryEffect
//---------------------------------------------------------------------------
// InventoryEffect���� �׷��ش�.
//---------------------------------------------------------------------------
void
DrawInventoryEffect()
{
	#ifdef __GAME_CLIENT__
		// ���� inventory�� ù ��ǥ			
		POINT point = UI_GetInventoryPosition();
		
		g_pTopView->DrawInventoryEffect(&point);

	#endif
}

void 
DrawTitleEffect()
{
	#ifdef __GAME_CLIENT__
		// ���� inventory�� ù ��ǥ			
		POINT point = 	{400,528};

		g_pTopView->DrawTitleEffect(&point);

	#endif
}

// 2004, 11, 22, sobeit add start
//--------------------------------------------------------------------
//	��� â�� ���� ���� ������ �ڿ� �Ѹ���..
//  DrawInventoryEffect ó�� generator ������� ������..Ư���� ���� ������ ����
//-------------------------------------------------------------------
void 
DrawBloodBibleEffect_InGear(int X, int Y)
{
	#ifdef __GAME_CLIENT__
		// ���� inventory�� ù ��ǥ			
		POINT point = 	{X,Y};

		g_pTopView->DrawBloodBibleEffect_InGear(&point);

	#endif
}
// 2004, 11, 22, sobeit add end
//---------------------------------------------------------------------------
// Add New_Inventory_Effect
//---------------------------------------------------------------------------
// ȭ����ǥ(x,y)
//---------------------------------------------------------------------------
void
AddNewInventoryEffect(TYPE_OBJECTID id, TYPE_ACTIONINFO ai, DWORD delayFrame, DWORD value)
{
	#ifdef __GAME_CLIENT__
	
		DEBUG_ADD("AddNewInventoryEffect");

		//---------------------------------------------------------
		// ��� ������ �߸��� ���
		//---------------------------------------------------------
		if (ai>=g_pActionInfoTable->GetSize())
		{
			return;
		}

		// item�� grid ��ǥ
		int x, y;

		const MItem* pItem = g_pInventory->GetItemToModify( id );
		/*
		for (int i=0; i<8; i++)
		{
			const MItem* pCheckItem = g_pInventory->GetItem(i, 0);

			if (pCheckItem!=NULL)
			{
				if (pCheckItem->GetID()==id)
				{
					x = pCheckItem->GetGridX();
					y = pCheckItem->GetGridY();			

					break;
				}
			}
		}
		*/

		//---------------------------------------------------------
		// item�� ���� ���
		//---------------------------------------------------------
		if (pItem==NULL || !(*g_pActionInfoTable)[ai].IsTargetItem())
		{
			DEBUG_ADD("No such item or Not Target Item");
			return;
		}

		x = pItem->GetGridX();
		y = pItem->GetGridY();

		//---------------------------------------------------------
		// ����� ���� ����?���� �ִ� ��쿡��...
		//---------------------------------------------------------
		if ((*g_pActionInfoTable)[ai].GetSize()!=0)
		{
			MEffectTarget* pEffectTarget = new MEffectTarget( (*g_pActionInfoTable)[ai].GetSize() );

			pEffectTarget->Set( x, y, 0, id );

			pEffectTarget->SetDelayFrame( delayFrame );

			//--------------------------------------------------------
			//
			//                   Effect����		
			//
			//--------------------------------------------------------
			g_pEffectGeneratorTable->Generate(
					x,y,0,		// ���� ��ġ
					0, 			// ����
					1,			// power
					ai,			//	ActionInfoTable����,
					pEffectTarget		// ��ǥ ����
			);

			//------------------------------------------------------
			// ��� ����
			//------------------------------------------------------
			MActionResult* pResult = new MActionResult;
			MActionResultNode* pActionResultNode = NULL;

			switch(ai)
			{
			case MAGIC_ENCHANT_OPTION_PLUS:
				{
					MItem* pInvenItem = g_pInventory->GetItem(id);

					if(pInvenItem != NULL)
					{
						pActionResultNode = new MActionResultNodeChangeItemOptionInInventory(id, value);
					}
				}
				break;

			case MAGIC_ENCHANT_OPTION_NULL:
				{
					MItem* pInvenItem = g_pInventory->GetItem(id);

					// ��� �������� ��������ΰ��� ó�� ����
					if(pInvenItem != NULL)
					{
						if(pInvenItem->GetItemClass() != ITEM_CLASS_PET_ITEM)
						{
							pActionResultNode = new MActionResultNodeChangeItemOptionInInventory(id, value);
						}
						else
						{
							if(g_pPlayer->IsItemCheckBufferItemToItem())
							{
								MItem *pMouseItem = g_pPlayer->GetItemCheckBuffer();

								g_pPlayer->ClearItemCheckBuffer();

								if(pMouseItem != NULL)
									delete pMouseItem;
							}
						}
					}

				}
				break;

			case MAGIC_ENCHANT_REMOVE_ITEM:
				pActionResultNode = new MActionResultNodeRemoveItemInInventory(id);
				break;
			case MAGIC_TRANS_ITEM_OK :
				pActionResultNode = new MActionResultNodeChangeItemGenderInInventory( id );
				break;
			}

			if (pActionResultNode!=NULL)
			{
				pResult->Add( pActionResultNode );
				pEffectTarget->SetResult(pResult);
			}

			DEBUG_ADD_FORMAT("[AddNewInventoryEffect] ai=%d, item id=%d", ai, id);
		}
		//---------------------------------------------------------
		// ����� ���� ������ ���� ���
		//---------------------------------------------------------
		else
		{
			//------------------------------------------------------------
			// ����� ó���ؾ��ϴ� �����ΰ�? - �翬�ϴٰ� ���� *_*;
			//------------------------------------------------------------				
			// ��.. ����� �����.. - -;;
		}
	#endif
}


//---------------------------------------------------------------------------
// Draw AlphaBox (pRect,  (r,g,b),  alpha)
//---------------------------------------------------------------------------
// alpha�� Ŀ����.. �� �������� �Ǿ� ����..
//---------------------------------------------------------------------------
void
DrawAlphaBox(RECT* pRect, BYTE r, BYTE g, BYTE b, BYTE alpha)
{
	// Ŭ����
	RECT rect = *pRect;
	pRect = &rect;
	// add by Sonic 2006.9.26
//	if(g_MyFull)
//	{
//		if(pRect->left < 0)pRect->left = 0;
//		if(pRect->right > 1024-1)pRect->right = 1024-1;
//		if(pRect->top < 0)pRect->top = 0;
//		if(pRect->bottom > 768-1)pRect->bottom = 768-1;

//	}
//	else
//	{
		if(pRect->left < 0)pRect->left = 0;
		if(pRect->right > g_GameRect.right-1)pRect->right = g_GameRect.right-1;
		if(pRect->top < 0)pRect->top = 0;
		if(pRect->bottom > g_GameRect.bottom -1)pRect->bottom = g_GameRect.bottom-1;
//	}
	// end
	if(pRect->left >= pRect->right || pRect->top >= pRect->bottom)return;

	#ifdef __GAME_CLIENT__
		int reverseAlpha = 31-alpha;

		if (alpha<0) alpha = 0;

		g_pTopView->DrawAlphaBox(pRect, r, g, b, reverseAlpha);
	#else
		int reverseAlpha = 31-alpha;

		WORD color;
		//------------------------------------------------
		// Lock ���·� �����.
		//------------------------------------------------
		BOOL bUnlock = !gpC_base->m_p_DDSurface_back->IsLock();
		if (bUnlock)
		{
			gpC_base->m_p_DDSurface_back->Lock();
		}

		color = CDirectDraw::Color(r,g,b);

		//-------------------------------------------------
		// �������̸�.. ���� �ȴ�~
		//-------------------------------------------------
		if (color==0)
		{
			// 2D 5:6:5
			if (CDirectDraw::Is565())
			{
				gpC_base->m_p_DDSurface_back->GammaBox565(pRect, reverseAlpha);
			}
			// 2D 5:5:5
			else
			{
				gpC_base->m_p_DDSurface_back->GammaBox555(pRect, reverseAlpha);
			}
		}
		//-------------------------------------------------
		// �ƴϸ�...
		//-------------------------------------------------
		else
		{
			gpC_base->m_p_DDSurface_back->BltColorAlpha(pRect, color, reverseAlpha);
		}

		//------------------------------------------------
		// ������ Lock ���·� �ǵ�����.
		//------------------------------------------------
		if (bUnlock)
		{
			gpC_base->m_p_DDSurface_back->Unlock();
		}
	#endif
}


//---------------------------------------------------------------------------
// InitMinimap
//---------------------------------------------------------------------------
//void
//InitMinimap(CSpriteSurface *minimap_surface)
//{
//	#ifdef __GAME_CLIENT__
//		g_pTopView->InitMinimapTexture(minimap_surface);
//	#endif
//}
//
//
////---------------------------------------------------------------------------
//// DrawMinimap
////---------------------------------------------------------------------------
//void
//DrawMinimapAlpha(int x, int y, CSpriteSurface *minimap_surface)
//{
////	#ifdef __GAME_CLIENT__
////		g_pTopView->DrawMinimap(x, y, 1);
////	#else
//		RECT rt = {0,0,minimap_surface->GetWidth(),minimap_surface->GetHeight()};
//		POINT map_point = {x, y};
//
//		gpC_base->m_p_DDSurface_back->Blt(&map_point, minimap_surface, &rt);
//// 	#endif
//}

