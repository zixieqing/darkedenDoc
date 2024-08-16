//----------------------------------------------------------------------
// MZoneTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MZoneTable.h"

//----------------------------------------------------------------------
// SOUND_SOURCE
//----------------------------------------------------------------------
/*
class SOUND_SOURCE
{
	public :
		SOUND_SOURCE();
		~SOUND_SOURCE();

	//-------------------------------------------------------
	// zone�� (x, y)���� TimeGap
	//-------------------------------------------------------
	public :
		int				x, y;
		int				MinTimeGap;			// �ּ��� MinTimeGap�Ŀ� play�ؾ��Ѵ�.
		int				MaxTimeGap;			// MaxTime�ȿ��� play�ؾ��Ѵ�.
		int				SoundID;
		int				NextPlayTime;		// ������ play�ص� �Ǵ� �ð�

	public :
		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);		
		void			LoadFromFile(class ifstream& file);		
};
*/

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
CZoneTable*		g_pZoneTable = NULL;

//----------------------------------------------------------------------
//
//						ZONETABLE_INFO
//
//----------------------------------------------------------------------
ZONETABLE_INFO::ZONETABLE_INFO()
{
	Property = 0;
	CreatureColorSet = 0xFFFF;	
	Safety = false;
	HolyLand = false;
	ChatMaskByRace = true;
	CannotAttackInSafe = false;
	CannotUseSpecialItem = false;
	CompetenceZone = false;
	PKType = PK_TYPE_NULL;
}

//----------------------------------------------------------------------
// Get Random SoundID
//----------------------------------------------------------------------
TYPE_SOUNDID			
ZONETABLE_INFO::GetRandomSoundID() const
{
	int numSound = SoundIDList.size();

	if (numSound == 0)
	{
		return SOUNDID_NULL;
	}

	int select = rand()%numSound;
	
	SOUNDID_LIST::const_iterator	iID = SoundIDList.begin();

	// select��° id�� �����Ѵ�.
	for (int i=0; i<select; i++)
	{
		iID++;
	}

	return *iID;
}

//----------------------------------------------------------------------
// Save
//----------------------------------------------------------------------
void			
ZONETABLE_INFO::SaveToFile(class ofstream& file)
{
	file.write((const char*)&ID, SIZE_ZONEID);
	Name.SaveToFile( file );
	file.write((const char*)&Property, 1);
	file.write((const char*)&MusicIDSlayer, SIZE_MUSICID);
	file.write((const char*)&MusicIDVampire, SIZE_MUSICID);
	Filename.SaveToFile( file );
	InfoFilename.SaveToFile( file );
	TeenFilename.SaveToFile( file );
	
	// sound ID�� ����
	int numSound = SoundIDList.size();

	file.write((const char*)&numSound, 4);

	SOUNDID_LIST::iterator	iID = SoundIDList.begin();
	
	while (iID != SoundIDList.end())
	{
		TYPE_SOUNDID soundID = *iID;

		file.write((const char*)&soundID, SIZE_SOUNDID);

		iID++;
	}
	
	file.write((const char*)&Safety, 1);
	file.write((const char*)&CreatureColorSet, 2);	

	file.write((char*)&MinimapSpriteID, 2);
	file.write((const char*)&HolyLand,1);
	file.write((const char*)&ChatMaskByRace,1);
	file.write((const char*)&CannotAttackInSafe,1);		
	file.write((const char*)&CannotUseSpecialItem,1);	
	file.write((const char*)&CompetenceZone,1);	
	file.write((const char*)&PKType, 1 );
}

//----------------------------------------------------------------------
// Load
//----------------------------------------------------------------------
void			
ZONETABLE_INFO::LoadFromFile(class ifstream& file)
{
	file.read((char*)&ID, SIZE_ZONEID);
	Name.LoadFromFile( file );
	file.read((char*)&Property, 1);
	file.read((char*)&MusicIDSlayer, SIZE_MUSICID);
	file.read((char*)&MusicIDVampire, SIZE_MUSICID);
	Filename.LoadFromFile( file );
	InfoFilename.LoadFromFile( file );
	TeenFilename.LoadFromFile( file );

	// sound id�� loading
	SoundIDList.clear();

	int numSound;
	file.read((char*)&numSound, 4);

	TYPE_SOUNDID soundID;
	for (int i=0; i<numSound; i++)
	{
		file.read((char*)&soundID, SIZE_SOUNDID);

		SoundIDList.push_back( soundID );
	}

	file.read((char*)&Safety, 1);	
	file.read((char*)&CreatureColorSet, 2);

	file.read((char*)&MinimapSpriteID, 2);
	file.read((char*)&HolyLand,1);
	file.read((char*)&ChatMaskByRace,1);
	file.read((char*)&CannotAttackInSafe,1);	
	file.read((char*)&CannotUseSpecialItem,1);	
	file.read((char*)&CompetenceZone,1);	
	file.read((char*)&PKType, 1 );
}


//----------------------------------------------------------------------
//
//							CZoneTable
//
//----------------------------------------------------------------------
CZoneTable::CZoneTable()
{
}

CZoneTable::~CZoneTable()
{
	Release();
}

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void				
CZoneTable::Release()
{
	ZONEINFO_MAP::iterator iInfo = m_mapZoneInfo.begin();

	// ��� ZoneInfo�� �޸𸮿��� �����.
	while (iInfo != m_mapZoneInfo.end())
	{
		ZONETABLE_INFO*	pInfo = (*iInfo).second;
		
		if (pInfo!=NULL)
		{
			delete pInfo;
		}

		iInfo++;
	}

	m_mapZoneInfo.clear();
}

//----------------------------------------------------------------------
// Add ZoneInfo
//----------------------------------------------------------------------
// ZoneInfo�� �߰��Ѵ�.
//----------------------------------------------------------------------
bool				
CZoneTable::Add(ZONETABLE_INFO* pZoneInfo)
{
	if (pZoneInfo==NULL)
	{
		return false;
	}

	ZONEINFO_MAP::iterator iInfo = m_mapZoneInfo.find( pZoneInfo->ID );

	// �̹� ������.. �����.
	if (iInfo!=m_mapZoneInfo.end())
	{
		delete pZoneInfo;

		return false;
	}

	// �߰��Ѵ�.
	m_mapZoneInfo.insert( ZONEINFO_MAP::value_type(pZoneInfo->ID, pZoneInfo) );

	return true;
}

//----------------------------------------------------------------------
// Get ZoneInfo
//----------------------------------------------------------------------
// zoneID�� id�� zoneInfo�� ��´�.
//----------------------------------------------------------------------
ZONETABLE_INFO*		
CZoneTable::Get(TYPE_ZONEID id)
{
	ZONEINFO_MAP::iterator iInfo = m_mapZoneInfo.find( id );

	// ������..
	if (iInfo == m_mapZoneInfo.end())
	{
		return NULL;
	}

	return (*iInfo).second;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
// size , ������ ZoneInfo
//----------------------------------------------------------------------
void				
CZoneTable::SaveToFile(class ofstream& file)
{
	//---------------------------------------------
	// ��ü ���� ����
	//---------------------------------------------
	int size = m_mapZoneInfo.size();

	file.write((const char*)&size , 4);

	//---------------------------------------------
	// ������ zoneInfo�� �����Ѵ�.
	//---------------------------------------------
	ZONEINFO_MAP::iterator iInfo = m_mapZoneInfo.begin();

	while (iInfo != m_mapZoneInfo.end())
	{
		ZONETABLE_INFO*	pInfo = (*iInfo).second;
		
		if (pInfo!=NULL)
		{
			pInfo->SaveToFile( file );
		}

		iInfo++;
	}
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
// size , ������ ZoneInfo
//----------------------------------------------------------------------
void				
CZoneTable::LoadFromFile(class ifstream& file)
{
	//---------------------------------------------
	// ������ �ִ� �޸� ����
	//---------------------------------------------
	Release();

	//---------------------------------------------
	// size �о����
	//---------------------------------------------
	int size;

	file.read((char*)&size, 4);

	//---------------------------------------------
	// ������ ZoneInfo�� Load�Ѵ�.
	//---------------------------------------------
	for (int i=0; i<size; i++)
	{
		ZONETABLE_INFO* pInfo = new ZONETABLE_INFO;

		pInfo->LoadFromFile( file );

		Add( pInfo );
	}
}
