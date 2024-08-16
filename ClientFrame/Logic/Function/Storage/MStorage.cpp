//----------------------------------------------------------------------
// MStorage.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MStorage.h"
#include "MGameDef.h"

#ifdef __GAME_CLIENT__
	#include "MPlayer.h"
#endif

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MStorage*		g_pStorage = NULL;
MStorage*		g_pStorage2= NULL;
MStorage*		g_pStorageTemp = NULL;
//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MStorage::MStorage()
{
	m_bActive			= false;

	m_Size				= 0;
	m_CurrentStorage	= 0;
	m_pStorage			= NULL;
	m_pMoneyManager		= NULL;
	m_pPersnalMsg		= NULL;
}

MStorage::~MStorage()
{
	Release();
}

//----------------------------------------------------------------------
// Init ( n )
//----------------------------------------------------------------------
void				
MStorage::Init(unsigned int n)
{
	Release();
	
	//--------------------------------------------------
	// �������� n�� �����.	
	//--------------------------------------------------
	m_Size		= n;
	m_pStorage	= new MItem** [m_Size];

	for (int i=0; i<m_Size; i++)
	{
		//--------------------------------------------------
		// �� �����Կ� STORAGE_SLOT���� slot�� �����.
		//--------------------------------------------------
		m_pStorage[i] = new MItem* [STORAGE_SLOT];

		//--------------------------------------------------
		// NULL�� �ʱ�ȭ �Ѵ�.	
		//--------------------------------------------------
		for (int s=0; s<STORAGE_SLOT; s++)
		{
			m_pStorage[i][s] = NULL;
		}
	}

	//--------------------------------------------------
	// ��
	//--------------------------------------------------
	m_pMoneyManager		= new MMoneyManager;
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void				
MStorage::Release()
{
	//---------------------------------------------------
	// �����.
	//---------------------------------------------------
	if (m_pStorage!=NULL)
	{
		for (int i=0; i<m_Size; i++)
		{
			if (m_pStorage[i]!=NULL)
			{
				for (int s=0; s<STORAGE_SLOT; s++)
				{
					if (m_pStorage[i][s]!=NULL)
					{
						delete m_pStorage[i][s];						
					}
				}

				delete [] m_pStorage[i];
			}
		}

		delete [] m_pStorage;
	}

	//---------------------------------------------------
	// ��
	//---------------------------------------------------
	if (m_pMoneyManager!=NULL)
	{
		delete m_pMoneyManager;
		m_pMoneyManager = NULL;
	}

	m_pStorage		= NULL;
	m_pPersnalMsg   = NULL;
	m_Size			= 0;
	m_CurrentStorage	= 0;

	m_bActive = false;
}

//----------------------------------------------------------------------
// Set Item
//----------------------------------------------------------------------
bool				
MStorage::SetItem(unsigned int slot, MItem* pItem)
{
	if (m_pStorage==NULL || slot>=STORAGE_SLOT)
	{
		return false;
	}

	//----------------------------------------------
	// �̹� �ٸ��� �ִٸ� �����.
	//----------------------------------------------
	if (m_pStorage[m_CurrentStorage][slot]!=NULL)
	{
		delete m_pStorage[m_CurrentStorage][slot]; 
	}

	//----------------------------------------------
	// item ����..
	//----------------------------------------------
	m_pStorage[m_CurrentStorage][slot] = pItem;

	return true;
}

//----------------------------------------------------------------------
// Remove Item
//----------------------------------------------------------------------
MItem*				
MStorage::RemoveItem(unsigned int slot)
{
	if (m_pStorage==NULL || slot>=STORAGE_SLOT)
	{
		return NULL;
	}

	//-------------------------------------------------
	// �����ߴٰ� .. �� ��ġ�� �����.. �Ѱ��ش�.
	//-------------------------------------------------
	MItem* pItem = m_pStorage[m_CurrentStorage][slot];

	m_pStorage[m_CurrentStorage][slot] = NULL;

	return pItem;
}

//----------------------------------------------------------------------
// Get Item
//----------------------------------------------------------------------
const MItem*		
MStorage::GetItem(unsigned int slot) const
{
	if (m_pStorage==NULL || slot>=STORAGE_SLOT)
	{
		return NULL;
	}

	return m_pStorage[m_CurrentStorage][slot];
}

//----------------------------------------------------------------------
// Set Current( n )
//----------------------------------------------------------------------
// ���� ���� ���� Shelf�� �����Ѵ�.
//----------------------------------------------------------------------
void				
MStorage::SetCurrent(unsigned int n)
{
	if (m_pStorage==NULL || n>=m_Size)
	{
		return;
	}

	m_CurrentStorage = n;

	//------------------------------------------------------
	// ��� ���� ���� üũ
	//------------------------------------------------------
	#ifdef __GAME_CLIENT__
		for (int i=0; i<STORAGE_SLOT; i++)
		{
			MItem* pItem = m_pStorage[m_CurrentStorage][i];

			if (pItem!=NULL)
			{	
				g_pPlayer->CheckAffectStatus( pItem );
			}
		}		
	#endif

	
}

