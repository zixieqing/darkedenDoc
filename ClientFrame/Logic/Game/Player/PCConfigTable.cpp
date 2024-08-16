//----------------------------------------------------------------------
// PCConfigTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "PCConfigTable.h"

const int PLAYER_CONFIG_VERSION	= 2;

#define LIMIT_PLAYER_CONFIG		20

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
WorldPlayerConfigTable*		g_pWorldPlayerConfigTable = NULL;

//----------------------------------------------------------------------
// PlayerConfigSort
//----------------------------------------------------------------------
class PlayerConfigSort {
	public :
		bool operator () (PlayerConfig *pLeft, PlayerConfig *pRight) const
		{
			return pLeft->GetRecentCount() < pRight->GetRecentCount();
		}
};

//----------------------------------------------------------------------
//
//							PlayerConfig
//
//----------------------------------------------------------------------
PlayerConfig::PlayerConfig()
{
	m_LastSlot = 0;
	m_RecentCount = 0;
}

PlayerConfig::~PlayerConfig()
{
}

//----------------------------------------------------------------------
// Set LastSlot
//----------------------------------------------------------------------
void		
PlayerConfig::SetLastSlot(int slot)
{ 
	if (slot < 3)	//MAX_SLOT
	{
		m_LastSlot = slot; 
	}

	// �ֱٿ� ���� ���̴�.
	m_RecentCount = 0;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
PlayerConfig::SaveToFile(class ofstream& file)
{
	// save�Ҷ����� RecentCount�� 1�� ������Ų��.
	// SetLastSlot(�����Ҷ�)�� ���� �ʰ�.. save�� �ϰ� �Ǹ�
	// �ᱹ RecentCount�� ���� ū �ְ�.. ����~~ �������� �����Ѿְ� �ȴ�.
	m_RecentCount ++;

	file.write((const char*)&m_LastSlot, 1);
	file.write((const char*)&m_RecentCount, 4);
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void		
PlayerConfig::LoadFromFile(class ifstream& file)
{
	file.read((char*)&m_LastSlot, 1);
	file.read((char*)&m_RecentCount, 4);
}


//----------------------------------------------------------------------
//
//						PlayerConfigTable
//
//----------------------------------------------------------------------
PlayerConfigTable::PlayerConfigTable()
{
}

PlayerConfigTable::~PlayerConfigTable()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void				
PlayerConfigTable::Release()
{
	iterator iConfig = begin();

	while (iConfig != end())
	{
		PlayerConfig* pConfig = iConfig->second;

		if (pConfig!=NULL)
		{
			delete pConfig;
		}

		iConfig ++;
	}

	clear();
}

//----------------------------------------------------------------------
// Add PlayerConfigTable
//----------------------------------------------------------------------
void				
PlayerConfigTable::AddPlayerConfig(PlayerConfig* pConfig)
{
	if (pConfig==NULL
		|| pConfig->GetPlayerID().length()==0)
	{
		return;
	}

	const std::string& playerID = pConfig->GetPlayerID();

	iterator iConfig = find( playerID );

	// �̹� ������ �����.
	if (iConfig != end())
	{
		PlayerConfig* pConfig = iConfig->second;

		if (pConfig!=NULL)
		{
			delete pConfig;
		}
	}

	(*this)[playerID] = pConfig;
}

//----------------------------------------------------------------------
// Get PlayerConfigTable
//----------------------------------------------------------------------
PlayerConfig*		
PlayerConfigTable::GetPlayerConfig(const char* pPlayerID) const
{
	if (pPlayerID==NULL)
	{
		return NULL;
	}

	const_iterator iConfig = find( std::string(pPlayerID) );

	if (iConfig != end())
	{
		return iConfig->second;
	}

	return NULL;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
PlayerConfigTable::SaveToFile(class ofstream& file)
{
	int num = size();

	//---------------------------------------------------------------
	// ���� ���ѿ� �ɸ��� ���
	//---------------------------------------------------------------
	if (num > LIMIT_PLAYER_CONFIG)
	{
		int removeNum = num - LIMIT_PLAYER_CONFIG;	// �����Ұ� ����
		num = LIMIT_PLAYER_CONFIG;

		// ����
		file.write((const char*)&num, 4);

		// vector�� ���� �����Ұ͸� �̾ƾ� �Ѵ�.
		std::vector<PlayerConfig*> playerConfigs;
		
		playerConfigs.reserve( size() );	// ��ü ������ŭ

		const_iterator iConfig = begin();

		// map --> vector
		while (iConfig != end())
		{
			playerConfigs.push_back( iConfig->second );
			iConfig ++;
		}

		// sort. �ֱٿ��͵��� ������ �´�.
		std::stable_sort( playerConfigs.begin(), playerConfigs.end(), PlayerConfigSort() );

		BYTE len;

		// num���� �����Ѵ�.
		for (int i=0; i<num; i++)
		{
			PlayerConfig* pConfig = playerConfigs[i];

			if (pConfig!=NULL)
			{
				const std::string& playerID = pConfig->GetPlayerID();

				// PlayerID
				len = playerID.length();
				file.write((const char*)&len, 1);			
				file.write((const char*)playerID.c_str(), len);

				// PlayerConfig
				pConfig->SaveToFile( file );
			}
			else
			{
				// NULL�� ����.. PlayerID ���� 0����.
				len = 0;
				file.write((const char*)&len, 1);
			}
		}
	}
	//---------------------------------------------------------------
	// ���� �����ϴ� ���
	//---------------------------------------------------------------
	else
	{
		// ����
		file.write((const char*)&num, 4);

		// �� ����..
		const_iterator iConfig = begin();

		BYTE len;

		while (iConfig != end())
		{
			PlayerConfig* pConfig = iConfig->second;

			if (pConfig!=NULL)
			{
				const std::string& playerID = pConfig->GetPlayerID();

				// PlayerID
				len = playerID.length();
				file.write((const char*)&len, 1);			
				file.write((const char*)playerID.c_str(), len);

				// PlayerConfig
				pConfig->SaveToFile( file );
			}
			else
			{
				// NULL�� ����.. PlayerID ���� 0����.
				len = 0;
				file.write((const char*)&len, 1);
			}

			iConfig ++;
		}
	}

}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void		
PlayerConfigTable::LoadFromFile(class ifstream& file)
{
	Release();

	int num;

	// ����
	file.read((char*)&num, 4);

	BYTE len;
	char str[20];			

	for (int i=0; i<num; i++)
	{
		file.read((char*)&len, 1);		// �̸� ����

		if (len != 0)
		{
			file.read((char*)str, len);
			str[len] = '\0';

			PlayerConfig* pConfig = new PlayerConfig;
			pConfig->LoadFromFile( file );
			pConfig->SetPlayerID( str );		// pConfig ���ο����� �ϵ��� �ٲ���Ѵ�.

			AddPlayerConfig( pConfig );
		}
	}
}


//----------------------------------------------------------------------
//
//						World PlayerConfigTable
//
//----------------------------------------------------------------------
WorldPlayerConfigTable::WorldPlayerConfigTable()
{
}

WorldPlayerConfigTable::~WorldPlayerConfigTable()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void				
WorldPlayerConfigTable::Release()
{
	iterator iTable = begin();

	while (iTable != end())
	{
		PlayerConfigTable* pTable = iTable->second;

		if (pTable!=NULL)
		{
			delete pTable;
		}

		iTable ++;
	}

	clear();
}

//----------------------------------------------------------------------
// Add PlayerConfigTable
//----------------------------------------------------------------------
void				
WorldPlayerConfigTable::AddPlayerConfigTable(int worldID, PlayerConfigTable* pTable)
{
	if (pTable==NULL)
	{
		return;
	}

	iterator iTable = find( worldID );

	// �̹� ������ �����.
	if (iTable != end())
	{
		PlayerConfigTable* pTable = iTable->second;

		if (pTable!=NULL)
		{
			delete pTable;
		}
	}

	(*this)[worldID] = pTable;
}

//----------------------------------------------------------------------
// Get PlayerConfigTable
//----------------------------------------------------------------------
PlayerConfigTable*	
WorldPlayerConfigTable::GetPlayerConfigTable(int worldID) const
{
	const_iterator iTable = find( worldID );

	if (iTable != end())
	{
		return iTable->second;
	}

	return NULL;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
WorldPlayerConfigTable::SaveToFile(const char* pFilename)
{
	class ofstream file(pFilename, ios::binary | ios::trunc);

	if (file.is_open())
	{
		file.write((const char*)&PLAYER_CONFIG_VERSION, 4);

		int num = size();

		// ����
		file.write((const char*)&num, 4);

		// �� ����..
		const_iterator iConfig = begin();

		while (iConfig != end())
		{
			PlayerConfigTable* pTable = iConfig->second;

			if (pTable!=NULL)
			{
				int worldID = iConfig->first;			
				file.write((const char*)&worldID, 4);

				pTable->SaveToFile( file );
			}
			else
			{
				int worldID = -1;
				file.write((const char*)&worldID, 4);
			}

			iConfig ++;
		}

		file.close();
	}
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void		
WorldPlayerConfigTable::LoadFromFile(const char* pFilename)
{
	Release();

	if (pFilename==NULL)
	{
		return;
	}

	class ifstream file(pFilename, ios::binary | ios::nocreate);

	if (file.is_open())
	{
		int version;
		file.read((char*)&version, 4);

		if (version==PLAYER_CONFIG_VERSION)
		{
			int num;

			// ����
			file.read((char*)&num, 4);

			int worldID;

			for (int i=0; i<num; i++)
			{
				file.read((char*)&worldID, 4);

				if (worldID != -1)
				{
					PlayerConfigTable* pTable = new PlayerConfigTable;
					pTable->LoadFromFile( file );

					AddPlayerConfigTable( worldID, pTable );
				}
			}
		}

		file.close();
	}
}