//---------------------------------------------------------------------------------
// ExperienceTable.cpp
//---------------------------------------------------------------------------------
#include "Client_PCH.h"
#include "ExperienceTable.h"

//---------------------------------------------------------------------------------
// Global
//---------------------------------------------------------------------------------
ExperienceTable* g_pExperienceTable = NULL;

//---------------------------------------------------------------------------------
//
//					ExperienceTable
//
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
// constructor / destructor
//---------------------------------------------------------------------------------
ExperienceTable::ExperienceTable()
{
	// �ȳ�..
}

ExperienceTable::~ExperienceTable()
{
	// ����.. ���ص� �Ǵµ�.. ��..
	Release();
}

//---------------------------------------------------------------------------------
// Release
//---------------------------------------------------------------------------------
void
ExperienceTable::Release()
{
	m_STRExp.Release();
	m_DEXExp.Release();
	m_INTExp.Release();
	m_VampireExp.Release();
	m_OustersExp.Release();
	m_SlayerRankExp.Release();
	m_VampireRankExp.Release();
	m_OustersRankExp.Release();
	m_PetExp.Release();
}

//---------------------------------------------------------------------------------
// LoadFromFileSTR
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileSTR(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);

	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_STRExp.Init( num + 1 );

	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_STRExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File DEX
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileDEX(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);

	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_DEXExp.Init( num + 1 );

	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_DEXExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File INT
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileINT(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);

	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_INTExp.Init( num + 1 );

	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_INTExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File Vampire
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileVampire(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);

	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_VampireExp.Init( num + 1 );

	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_VampireExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File Ousters
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileOusters(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);
	
	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_OustersExp.Init( num + 1 );
	
	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_OustersExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File Slayer Rank
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileSlayerRank(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);

	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_SlayerRankExp.Init( num + 1 );

	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_SlayerRankExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File Vampire Rank
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileVampireRank(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);

	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_VampireRankExp.Init( num + 1 );

	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_VampireRankExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File Ousters Rank
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFileOustersRank(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);
	
	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_OustersRankExp.Init( num + 1 );
	
	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_OustersRankExp[level].LoadFromFile( file );		
	}
}

//---------------------------------------------------------------------------------
// Load From File Ousters Rank
//---------------------------------------------------------------------------------
void		
ExperienceTable::LoadFromFilePetExp(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);
	
	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_PetExp.Init( num + 1 );
	
	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_PetExp[level].LoadFromFile( file );		
	}
}

void
ExperienceTable::LoadFromFileAdvanceMent(class ifstream& file)
{
	int num, level;
	file.read((char*)&num, 4);
	
	// file���� 1 level���� ���ִ°ɷ� �����ϱ� ������...
	m_advanceSkillExp.Init( num + 1 );
	
	for (int i=0; i<num; i++)
	{
		file.read((char*)&level, 4);
		
		// level�� �°� loading�Ѵ�.
		m_advanceSkillExp[level].LoadFromFile( file );		
	}
}



//---------------------------------------------------------------------------------
// Get STR Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetSTRInfo(int level) const
{
	return m_STRExp[level];
}

//---------------------------------------------------------------------------------
// Get DEX Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetDEXInfo(int level) const
{
	return m_DEXExp[level];
}

//---------------------------------------------------------------------------------
// Get INT Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetINTInfo(int level) const
{
	return m_INTExp[level];
}

//---------------------------------------------------------------------------------
// Get Vampire Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetVampireInfo(int level) const
{
	return m_VampireExp[level];
}

//---------------------------------------------------------------------------------
// Get Ousters Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetOustersInfo(int level) const
{
	return m_OustersExp[level];
}

//---------------------------------------------------------------------------------
// Get SlayerRank Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetRankInfo(int level, Race_t race) const
{
	switch(race)
	{
	case RACE_SLAYER:
		return m_SlayerRankExp[level];
		break;

	case RACE_VAMPIRE:
		return m_VampireRankExp[level];
		break;

	case RACE_OUSTERS:
		return m_VampireRankExp[level];
		break;
	}

	return m_SlayerRankExp[level];
}

//---------------------------------------------------------------------------------
// Get SlayerRank Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetSlayerRankInfo(int level) const
{
	return m_SlayerRankExp[level];
}

//---------------------------------------------------------------------------------
// Get VampireRank Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetVampireRankInfo(int level) const
{
	return m_VampireRankExp[level];
}

//---------------------------------------------------------------------------------
// Get OustersRank Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetOustersRankInfo(int level) const
{
	return m_OustersRankExp[level];
}

//---------------------------------------------------------------------------------
// Get OustersRank Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetPetExp(int level) const
{
	return m_PetExp[level];
}


//---------------------------------------------------------------------------------
// Get advanceMent Info
//---------------------------------------------------------------------------------
const ExpInfo&		
ExperienceTable::GetAdvanceMent(int level) const
{
	return m_advanceSkillExp[level];
}
