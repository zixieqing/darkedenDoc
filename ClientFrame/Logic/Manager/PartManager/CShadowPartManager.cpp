//----------------------------------------------------------------------
// CShadowPartManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "DX3D.h"
#include "CFileIndexTable.h"
#include "CShadowPartManager.h"
#include "MGameTime.h"
#include "MWeather.h"

#include "DebugInfo.h"
//#define	new			DEBUG_NEW
//#define	delete		DEBUG_DELETE

extern bool FileOpenBinary(const char* filename, class ifstream& fil);

extern bool		g_bZonePlayerInLarge;

// �̰� 128�ϸ� memory�� �峭�� �ƴϴ�.
// detail�� �����ε�... ���..
#define	MAX_SIZE_TEXTURE_SHADOW		128


#ifdef OUTPUT_DEBUG
	#undef OUTPUT_DEBUG
#endif


//----------------------------------------------------------------------
//
// contructor/destructor
//
//----------------------------------------------------------------------
//CShadowPartManager::CShadowPartManager(CShadowSpritePack* pSSPK, WORD partSize)
CShadowPartManager::CShadowPartManager(const char* SSPKFilename, WORD partSize)
{
	//m_pSSPK		= NULL;
	m_pWidth	= NULL;
	m_pHeight	= NULL;

//	m_bOpen = false;
//	Init(SSPKFilename, indexFilename, partSize);	
	Init(SSPKFilename, partSize);	

	//Init(pSSPK, partSize);
}

CShadowPartManager::~CShadowPartManager()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Init(SSPKFilename, indexFilename)
//----------------------------------------------------------------------
// SSPKFilename�� ShadowSpritePack�̴�.
// indexFilename�� ShadowSpritePack Index�̴�.
//
// SSPKFilename�� ȭ���� ��� ���߿� ���� �� �ֵ��� �صΰ�
// indexFilename�� ��� �о ����صд�.
//----------------------------------------------------------------------
void
//CShadowPartManager::Init(CShadowSpritePack* pSSPK, WORD partSize)
CShadowPartManager::Init(const char* SSPKFilename, WORD partSize)
{
	Release();
	///*
	// Index File�� Load�Ѵ�.
	class ifstream indexFile;//(indexFilename, ios::binary);
//	if (!FileOpenBinary(indexFilename, indexFile))
//		return;
//
//	m_SSPKIndex.LoadFromFile( indexFile );
//	indexFile.close();
//
//	// SSPK�� �ʱ�ȭ �Ѵ�. (������ŭ..)
//	m_SSPK.Init( m_SSPKIndex.GetSize() );
//
//	// SSPK File�� ����д�.
//	m_SSPKFile.open(SSPKFilename, ios::binary);
//	
//	TYPE_SPRITEID size;
//	m_SSPKFile.read((char*)&size, SIZE_SPRITEID);
	m_SSPK.LoadFromFileRunning(SSPKFilename);

	int allSize = m_SSPK.GetSize();
	//*/

	//m_pSSPK = pSSPK;

	//int allSize = pSSPK->GetSize();

	// Base class�� Init�� �̿��ؼ�..
	// ( ��ü ����, �޸� ��� ���� ) 
	CPartManager<WORD, WORD, CSpriteSurface*>::Init( allSize, partSize );

	// NULL�� �ʱ�ȭ
	for (int i=0; i<m_nPart; i++)
	{
		m_pData[i] = NULL;
	}

	
	// texture size�� �����Ѵ�.
	m_pWidth = new int [allSize];
	m_pHeight = new int [allSize];

	for (i=0; i<allSize; i++)
	{
		m_pWidth[i] = 0;
		m_pHeight[i] = 0;
	}

	/*
	int spWidth, spHeight;
	int width, height;

	if (CDirect3D::IsTexturePow2())
	{
		for (i=0; i<allSize; i++)
		{
			if ((*pSSPK)[i].IsInit())
			{
				spWidth = (*pSSPK)[i].GetWidth();
				spHeight = (*pSSPK)[i].GetHeight();
				width = 1;
				height = 1;

				// width�� height�� spWidth�� spHeight���� Ŀ�� �Ѵ�.
				// square�� �����ش�.
				while (width < spWidth || height < spHeight)
				{
					width <<= 1;
					height <<= 1;
				}

				m_pWidth[i] = width;
				m_pHeight[i] = height;
			}
			else
			{
				m_pWidth[i] = 0;
				m_pHeight[i] = 0;
			}
		}
	}
	else
	{
		for (i=0; i<allSize; i++)
		{
			if ((*pSSPK)[i].IsInit())
			{
				spWidth = (*pSSPK)[i].GetWidth();
				spHeight = (*pSSPK)[i].GetHeight();
				width = spWidth;
				height = spHeight;

				// ū ũ��� ���߾ Square�� �����.
				if (CDirect3D::IsTextureSquareOnly())
				{				
					if (width > height)
					{
						height = width;				
					}
					else if (width < height)
					{
						width = height;				
					}	
				}

				m_pWidth[i] = width;
				m_pHeight[i] = height;
			}
			else
			{
				m_pWidth[i] = 0;
				m_pHeight[i] = 0;
			}
		}
	}
	*/

//	m_bOpen = true;
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
// ������ SSPK file�� �ݴ´�.
//----------------------------------------------------------------------
void	
CShadowPartManager::Release()
{
	///*
//	if (m_bOpen)
//	{
//		m_SSPKFile.close();
//		m_bOpen = false;
//	}
	//*/	
	if (m_pWidth != NULL)
	{
		delete [] m_pWidth;
		m_pWidth = NULL;
	}

	if (m_pHeight != NULL)
	{
		delete [] m_pHeight;
		m_pHeight = NULL;
	}	

	if (m_pData!=NULL)
	{
		for (int i=0; i<m_nPart; i++)
		{
			if (m_pData[i]!=NULL)
			{
				delete m_pData[i];
				m_pData[i] = NULL;
			}
		}
	}

	DeleteRemoved();
}

//----------------------------------------------------------------------
// Delete Removed
//----------------------------------------------------------------------
// ������ �� �͵�
//----------------------------------------------------------------------
void				
CShadowPartManager::DeleteRemoved()
{
	SPRITESURFACE_LIST::iterator iSurface = m_listRemoved.begin();

	while (iSurface != m_listRemoved.end())
	{
		CSpriteSurface*	pSurface = *iSurface;

		delete pSurface;
		
		iSurface++;
	}

	m_listRemoved.clear();
}


//----------------------------------------------------------------------
// Clear
//----------------------------------------------------------------------
// Video Memory�� ������ clear�Ѵ�.
// �����δ�... �� ���������� ���̴�.
//----------------------------------------------------------------------
void
CShadowPartManager::Clear()
{
	// video memory�� ����~�ش�.
	for (int i=0; i<m_nPart; i++)
	{
		if (m_pData[i] != NULL)			
		{
			m_pData[i]->Restore();
			delete m_pData[i];
			m_pData[i] = NULL;
		}
	}

	// Base class�� Init�� �̿��ؼ�..
	// ( ��ü ����, �޸� ��� ���� ) 
	CPartManager<WORD, WORD, CSpriteSurface*>::Init( m_nIndex, m_nPart );

	// NULL�� �ʱ�ȭ
	for (i=0; i<m_nPart; i++)
	{
		m_pData[i] = NULL;
	}

	DeleteRemoved();
}

//----------------------------------------------------------------------
// GetTexture( id )
//----------------------------------------------------------------------
// SSPK���� ID�� id�� ShadowSprite�� Load�� Surface�� �Ѱ���� �ϴµ�,
//
// Load���� �ʾ�����,
// Index�� �����ؼ� ������ SSPK File���� 
// id�� �ش��ϴ� ShadowSprite�� Load�ؼ� Surface�� �ϳ� �����ϰ�
// �� Surface�� ShadowSprite�� ������ش�.
//
// �� �κп��� �ӵ��� ����� �������� ������... 
//----------------------------------------------------------------------
CSpriteSurface*		
CShadowPartManager::GetTexture(TYPE_SPRITEID id)
{
	//static int reload	= 0;
	//static int reuse	= 0;

	//-----------------------------------------------------------
	// ������ --> Load & return
	//-----------------------------------------------------------
	if (IsDataNULL(id))
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD_FORMAT("CShadowPartManager::GetTexture New(%d)", id);
			}
		#endif	

		CShadowSprite* pSprite = &m_SSPK[id];
		//CShadowSprite* pSprite = &(*m_pSSPK)[id];


		//// �� Load�Ǿ� �ִٰ� �����Ѵ�..
		///*
		//----------------------------------------
		// �̹� Load�� ���̸�..
		//----------------------------------------
//		if (pSprite->IsInit())
//		{
//		}
//		//----------------------------------------
//		// Load�ؾ� �Ǵ� ���
//		//----------------------------------------
//		else
//		{
//			//-----------------------------------------------------------
//			// ShadowSprite�� Load�Ѵ�.
//			//-----------------------------------------------------------
//			// id�� �´� ������ FilePointer�� �̵��ؼ�
//			int temp = m_SSPKIndex[id];
//			m_SSPKFile.seekg(m_SSPKIndex[id], ios::beg);
//			pSprite->LoadFromFile( m_SSPKFile );
//		}
		//*/
		
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Loading ShadowSprite OK");
			}
		#endif	

		
		// shift���� ������ ���ؾ� �Ѵ�.
		// width�� height�� 256�� �Ѿ�� �ȵȴ�.
		// Texture�� Size�� �����Ѵ�.
		int spWidth, spHeight;
		int width, height;


		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Determine Texture GetSize OK");
			}
		#endif	

		spWidth = pSprite->GetWidth();
		spHeight = pSprite->GetHeight();
		
		//-----------------------------------------------------
		// ���̰� 0�� ���..
		//-----------------------------------------------------
		if (spWidth==0 || spHeight==0)
		{
			return NULL;
		}

		width = spWidth;
		height = spHeight;


		int shift = 0;
		// ����,���� ��� �ϳ��� MAX_SIZE_TEXTURE_SHADOW���� ũ��..
		while (width>MAX_SIZE_TEXTURE_SHADOW || height>MAX_SIZE_TEXTURE_SHADOW)
		{
			width >>= 1;
			height >>= 1;
			shift ++;
		}
		
		CDirect3D::GetTextureSize(width, height);	

		//-----------------------------------------------------------
		// 2�� �¼��� �����ϴ� ���..
		//-----------------------------------------------------------
		bool bDifferentSize;	// sprite�� texture�� ũ�Ⱑ �ٸ���?
		if (CDirect3D::IsTexturePow2())
		{
			bDifferentSize = true;

			// width�� height�� �ٸ� ���...
			// ���� �ʿ� ���缭 �Ȱ��� �Ѵ�.
			// Square�� �����..�� �� �� ����.. ����..

			// ū �ʿ� ���߸�?..
			if (width > height)
			{
				height = width;
			}
			else //if (width < height)
			{
				width = height;
			}

			//-----------------------------------------------------------
			// Textureũ�⺸�� Sprite ũ�Ⱑ �� ū ���..
			//-----------------------------------------------------------
			// ��, �ϵ����� Spriteũ�⸸ŭ�� Texture�� �������� ���ϴ� ����̴�.		
			// shift�� �̿��ؼ� ũ�⸦ ���δ�.
			shift = 0;		
			while (spWidth > width || spHeight > height)
			{
				shift ++;

				spWidth >>= 1;
				spHeight >>= 1;
			}
		}
		//-----------------------------------------------------------
		// �ƹ��� size�� ���� ���� ���
		//-----------------------------------------------------------
		else
		{
			if (CDirect3D::IsTextureSquareOnly())
			{
				// width�� height�� �ٸ� ���...
				// ū �ʿ� ���缭 �Ȱ��� �Ѵ�.
				// Square�� �����..�� �� �� ����.. ����..
				if (width > height)
				{
					height = width;
					bDifferentSize = true;
				}
				else if (width < height)
				{
					width = height;
					bDifferentSize = true;
				}				
			}
			else
			{
				bDifferentSize = false;
			}			
		}	

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Determine Texture Size OK");
			}
		#endif

		//-----------------------------------------------------------
		// (�ٽ�) �����Ѵ�.
		//-----------------------------------------------------------
		CSpriteSurface* pTextureSurface = new CSpriteSurface;

		if (pTextureSurface==NULL)
		{
			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD("[Error] Texture Surface is NULL");
				}
			#endif

			return false;
		}
		
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("New Texture Surface OK");
			}
		#endif
		

		//---------------------------------------------------
		// TextureSurface ����
		//---------------------------------------------------	
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Before Get Pixel Format");
			}
		#endif
		const LPDDPIXELFORMAT pixel4444 = CDirect3D::GetPixelFormat4444();

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Before InitTexture Surface");
			}
		#endif

		pTextureSurface->InitTextureSurface(width, height, 0, pixel4444);
		POINT point;
		point.x = 0;
		point.y = 0;

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD_FORMAT("Init Texture OK. num=%d, size=(%d, %d)", m_nPartUsed, pTextureSurface->GetWidth(), pTextureSurface->GetHeight());
			}
		#endif

		if (!pTextureSurface->Lock())
		{
			delete pTextureSurface;
			return false;
		}
			/*
		DDSURFACEDESC2 ddsd;

		ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);

		while (1)
		{
			HRESULT hr = pTextureSurface->GetSurface()->Lock(NULL, &ddsd,  DDLOCK_WAIT, NULL);

			if (hr==DD_OK)
			{
				break;
			}

			if( hr == DDERR_SURFACELOST )
			{
				bool ret = pTextureSurface->Restore();
				if (ret == false)
					break;
				else
					continue;
			}

			if( hr != DDERR_WASSTILLDRAWING )
			{
				#ifdef OUTPUT_DEBUG
					if (g_pDebugMessage)
					{
						DEBUG_ADD("Lock Failed");
					}
				#endif
				
				return false;
			}			
		}
		*/
		

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Lock OK");
			}
		#endif

		int i;

		//---------------------------------------------------
		// Texture Surface �ʱ�ȭ
		//---------------------------------------------------
		//static WORD trans[1024] = { 0, };

		WORD *pSurface = (WORD*)pTextureSurface->GetSurfacePointer();
				//,	*pSurfaceTemp;
		long pitch	= pTextureSurface->GetSurfacePitch();

		// �˰� ĥ�ϴ� �κ�..
		//if (bDifferentSize)
		{
			int width2 = width << 1;
			i = pTextureSurface->GetHeight();

			if (i>0)
			{
				do
				{			
					memset(pSurface, 0, width2);
					//memcpy(pSurface, trans, width);
					pSurface = (WORD*)((BYTE*)pSurface + pitch);
				} while (--i);
			}
		}
	
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Make Texture OK");
			}
		#endif
		
		//---------------------------------------------------
		// �ð��� ���� �׸��� ���
		//---------------------------------------------------
		const int timeShadow[] =
		{
			0x4000,		// 0��
			0x4000,		// 1��
			0x4000,		// 2��
			0x4000,		// 3��
			0x4000,		// 4��
			0x4000,		// 5��
			0x4000,		// 6��
			0x5000,		// 7��
			0x6000,		// 8��
			0x7000,		// 9��
			0x8000,		// 10��
			0x9000,		// 11��
			0xA000,		// 12��
			0xB000,		// 13��
			0xC000,		// 14��
			0xB000,		// 15��
			0xA000,		// 16��
			0x9000,		// 17��
			0x8000,		// 18��
			0x7000,		// 19��
			0x6000,		// 20��
			0x5000,		// 21��
			0x4000,		// 22��
			0x4000		// 23��			
		};

		WORD shadowColor = timeShadow[(*g_pGameTime).GetHour()];


		//---------------------------------------------------
		// �ǹ� �ȿ��� ������ 0x8000
		//---------------------------------------------------
		if (!g_bZonePlayerInLarge)
		{
			shadowColor = 0x8000;
		}
		else
		{
			//---------------------------------------------------
			// �� ���� �׸��ڰ� �� ��������.
			//---------------------------------------------------
			if (g_pWeather->GetWeatherType()==MWeather::WEATHER_RAIN)
			{
				int test = (int)shadowColor - (int)0x4000;

				if (test < 0x3000)
				{
					test = 0x3000;
				}

				shadowColor = test;
			}
		}


		//---------------------------------------------------
		// ShadowSprite���
		//---------------------------------------------------
		pTextureSurface->BltShadowSpriteSmall4444(&point, pSprite, shadowColor, shift);
		
		
	  
		pTextureSurface->Unlock();

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Blt Small4444 OK");
			}
		#endif
	
			
		//-----------------------------------------------------------
		// ����Ҷ� ����� ũ��
		//-----------------------------------------------------------
		// ������ ����� Texture Size�� ������ ���� ���� ���
		//-----------------------------------------------------------
		if (m_pWidth[id]==0 || m_pHeight[id]==0)
		{
			spWidth = pSprite->GetWidth();
			spHeight = pSprite->GetHeight();

			if (CDirect3D::IsTexturePow2())
			{	
				// texture���� ��µǴ� size�� ���Ѵ�.
				for (int i=0; i<shift; i++)
				{
					spWidth >>= 1;
					spHeight >>= 1;
				}

				// ���� ũ��
				width = width * pSprite->GetWidth() / spWidth;
				height = height * pSprite->GetHeight() / spHeight;		
			}
			else
			{
				width = spWidth;
				height = spHeight;

				// ū ũ��� ���߾ Square�� �����.
				if (CDirect3D::IsTextureSquareOnly())
				{				
					if (width > height)
					{
						height = width;				
					}
					else if (width < height)
					{
						width = height;				
					}	
				}
			}			

			m_pWidth[id] = width;
			m_pHeight[id] = height;		
		}
	
		
		//---------------------------------------------------
		// Replace������ �������� �޸𸮿��� �����.
		//---------------------------------------------------
		CSpriteSurface* pOld = NULL;
		WORD oldIndex = SetData( id, pTextureSurface, pOld );

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("Set Data OK");
			}
		#endif

		if (oldIndex != m_IndexNULL)
		{
			if (pOld != NULL)
			{
				#ifdef OUTPUT_DEBUG
					if (g_pDebugMessage)
					{
						DEBUG_ADD_FORMAT("Delete Old Surface(%d), (%d,%d)", oldIndex, m_SSPK[oldIndex].GetWidth(), m_SSPK[oldIndex].GetHeight());
					}
				#endif
				
				//------------------------------------------------------------
				// D3D�� Texture�� �ٷ� ������ �ʴ� ��쵵 �ִ�.
				// BeginScene() ~ EndScene() ���� Surface�� ����־�� �ϹǷ�
				// ���⼭ ����� �ȵȴ�.
				//------------------------------------------------------------
				//delete pOld;
				//------------------------------------------------------------
				m_listRemoved.push_back( pOld );
			}

			// loading�Ǿ� �ִ� sprite�� �����Ѵ�... �޸� ������..
			// �׸��ڴ� ����������? ��.. 
			//m_SSPK[oldIndex].Release();			
		}

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("OK");
			}
		#endif	

		// return
		return pTextureSurface;

		//reload++;
	}
	//-----------------------------------------------------------
	// �ִ� ��� --> return
	//-----------------------------------------------------------
	else
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD_FORMAT("CShadowPartManager::GetTexture(%d)", id);
			}
		#endif	

		CSpriteSurface* pTextureSurface;
		if (GetData(id, pTextureSurface))
		{
			return pTextureSurface;
		}

		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("No Exist!");
			}
		#endif	
		//reuse ++;
	}

	return NULL;
}


//----------------------------------------------------------------------
// Get Sprite
//----------------------------------------------------------------------
CShadowSprite&		
CShadowPartManager::GetSprite(TYPE_SPRITEID id)
{
	//------------------------------------------------------
	// Load�� �� ������ load�ؼ� �Ѱ��ش�.
	//------------------------------------------------------
//	if (m_SSPK[id].IsNotInit())
//	{
//		int temp = m_SSPKIndex[id];
//		m_SSPKFile.seekg(m_SSPKIndex[id], ios::beg);
//		m_SSPK[id].LoadFromFile( m_SSPKFile );
//	}
//
	return m_SSPK[id];
}