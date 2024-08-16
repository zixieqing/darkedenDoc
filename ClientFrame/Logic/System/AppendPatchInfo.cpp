//-----------------------------------------------------------------------------
// AppendPatchInfo.cpp
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include "AppendPatchInfo.h"

#ifdef __GAME_CLIENT__
	extern void		UpdateProgressBar();
	extern void		SetProgressBarText(const char* title);
#endif

//-----------------------------------------------------------------------------
//s
//						APPEND_PATCH_NODE
//
//-----------------------------------------------------------------------------
bool		
APPEND_PATCH_NODE::Append(const char* orgFilename) const
{	
	//-------------------------------------------------------------
	// appendȭ�� üũ..
	//-------------------------------------------------------------
	class ifstream appendFile(appendFilename.GetString(), ios::binary | ios::nocreate);		

	int n;
	char buffer[4096];

	// ����.. - -;;
	#ifdef __GAME_CLIENT__
		UpdateProgressBar();
	#endif

	//-------------------------------------------------------------
	// ��ġ ȭ���� ������ �� ��ġ..
	//-------------------------------------------------------------
	if (appendFile.is_open())
	{
		#ifdef __GAME_CLIENT__
			SetProgressBarText("��ġ ȭ���� �����Ű�� �ֽ��ϴ�.");
		#endif

		class fstream orgFile(orgFilename, ios::binary | ios::ate | ios::in | ios::out);
		
		if (orgFile.is_open())
		{
			WORD orgSpkSize;
			orgFile.seekg( 0 );
			orgFile.read((char*)&orgSpkSize, 2);	// Sprite�� ����

			appendFile.seekg( 2 );	// size�κ� ����
			orgFile.seekp( writePosition );		
			
			while (1)
			{
				appendFile.read(buffer, 4096);
				n = appendFile.gcount();

				if (n > 0)
				{
					orgFile.write(buffer, n);
				}
				else
				{
					break;
				}
			}		

			appendFile.close();
			
			// ���� ����
			orgFile.seekp( 0, ios::beg );
			WORD afterNum = max(afterSpkSize, orgSpkSize);	// ū ������ ���� - -;

			orgFile.write((const char*)&afterSpkSize, 2);
			orgFile.close();

			// ��ġȭ���� �����.
			remove( appendFilename.GetString() );
		}
		else
		{
			return false;
		}
	}	

	return true;
}

//-----------------------------------------------------------------------------
// Save To File
//-----------------------------------------------------------------------------
void		
APPEND_PATCH_NODE::SaveToFile(class ofstream& file)
{
	appendFilename.SaveToFile( file );
	file.write((const char*)&appendFilesize, 4);
	file.write((const char*)&appSpkSize, 2);
	file.write((const char*)&writePosition, 4);
	file.write((const char*)&afterFilesize, 4);
	file.write((const char*)&afterSpkSize, 2);
}

//-----------------------------------------------------------------------------
// Load From File
//-----------------------------------------------------------------------------
void		
APPEND_PATCH_NODE::LoadFromFile(class ifstream& file)
{
	appendFilename.LoadFromFile( file );
	file.read((char*)&appendFilesize, 4);
	file.read((char*)&appSpkSize, 2);
	file.read((char*)&writePosition, 4);
	file.read((char*)&afterFilesize, 4);
	file.read((char*)&afterSpkSize, 2);
}


//-----------------------------------------------------------------------------
//
//							AppendPatch
//
//-----------------------------------------------------------------------------
AppendPatch::AppendPatch()
{
	m_orgFilesize = 0;
	m_orgSpkSize = 0;

	m_finalFilesize = 0;
	m_finalSpkSize = 0;
}

AppendPatch::~AppendPatch()
{
	Release();
}

//-----------------------------------------------------------------------------
// Release
//-----------------------------------------------------------------------------
void
AppendPatch::Release()
{
	APPEND_PATCH_VECTOR::iterator iNode = m_AppendPatch.begin();

	while (iNode != m_AppendPatch.end())
	{
		delete *iNode;

		iNode ++;
	}

	m_AppendPatch.clear();

	m_orgFilename.Release();
	m_orgFilesize = 0;
	m_orgSpkSize = 0;
	m_finalFilesize = 0;
	m_finalSpkSize = 0;
}

//-----------------------------------------------------------------------------
// Set OriginalInfo
//-----------------------------------------------------------------------------
void		
AppendPatch::SetOriginalInfo(const char* orgFilename, long orgFilesize, WORD orgSpkSize)
{
	m_orgFilename = orgFilename;

	m_orgFilesize = orgFilesize;
	m_orgSpkSize = orgSpkSize;
}

//-----------------------------------------------------------------------------
// Set FinalInfo
//-----------------------------------------------------------------------------
void		
AppendPatch::SetFinalInfo(long finalFilesize, WORD finalSpkSize)
{
	m_finalFilesize = finalFilesize;
	m_finalSpkSize = finalSpkSize;
}

//-----------------------------------------------------------------------------
// Set FinalInfo
//-----------------------------------------------------------------------------
// currentFilename���� ������ �о���δ�.
//-----------------------------------------------------------------------------
bool		
AppendPatch::SetFinalInfo(const char* currentFilename)
{
	class ifstream file(currentFilename, ios::binary | ios::nocreate);

	if (!file.is_open())
	{
		return false;
	}

	// appSpkSize - Pack ����
	file.read((char*)&m_finalSpkSize, 2);
	file.seekg( 0, ios::end );

	// appendFilesize - AppendPack ũ��
	m_finalFilesize = file.tellg();	
	
	file.close();

	return true;
}

//-----------------------------------------------------------------------------
// Add AppendInfo
//-----------------------------------------------------------------------------
void		
AppendPatch::AddAppendInfo(const char* appendFilename, long appendFilesize, WORD appSpkSize)
{
	long previousFilesize;
	WORD previousSpkSize;

	//------------------------------------------------------------
	// �ٷ� �� ������ ����
	//------------------------------------------------------------
	if (m_AppendPatch.size()==0)
	{
		previousFilesize = m_orgFilesize;
		previousSpkSize	= m_orgSpkSize;
	}
	else
	{
		APPEND_PATCH_NODE* pNode = m_AppendPatch.back();

		previousFilesize = pNode->afterFilesize;
		previousSpkSize = pNode->afterSpkSize;
	}

	//------------------------------------------------------------
	// ���� ���� ����
	//------------------------------------------------------------
	APPEND_PATCH_NODE* pNode = new APPEND_PATCH_NODE;

	pNode->appendFilename	= appendFilename;
	pNode->appendFilesize	= appendFilesize;
	pNode->appSpkSize		= appSpkSize;		
	pNode->writePosition	= previousFilesize;
	pNode->afterFilesize	= previousFilesize + appendFilesize-2;	// SPK�� ���� �κ� 2 bytes
	pNode->afterSpkSize		= previousSpkSize + appSpkSize;

	m_AppendPatch.push_back( pNode );
}

//-----------------------------------------------------------------------------
// Add AppendInfo
//-----------------------------------------------------------------------------
// currentFilename�� ���� ȭ���� ��ġ�̴�.
// appendPatch�� �� ��ġ�� m_orgFilename�� �����ؾ� �Ѵ�.
//-----------------------------------------------------------------------------
bool
AppendPatch::AddAppendInfo(const char* currentFilename)
{
	//------------------------------------------------------------
	// �ʿ��� ����
	//------------------------------------------------------------
	char appendFilename[256];
	long appendFilesize;
	WORD appSpkSize;

	class ifstream file(currentFilename, ios::binary | ios::nocreate);

	if (!file.is_open())
	{
		return false;
	}

	// appSpkSize - Pack ����
	file.read((char*)&appSpkSize, 2);
	file.seekg( 0, ios::end );

	// appendFilesize - AppendPack ũ��
	appendFilesize = file.tellg();
	
	file.close();

	// appendFilename
	strcpy(appendFilename, m_orgFilename.GetString());
	char* pBS = strrchr(appendFilename, '\\');
	if (pBS==NULL)
	{
		// ? -_-;;
		return false;
	}
	else
	{
		*(pBS+1) = '\0';		// 'Data\\Image\\' ����
	}

	pBS = strrchr(currentFilename, '\\');	// '\\NewXX.spk'
	if (pBS==NULL)
	{
		strcat(appendFilename, currentFilename);
	}
	else
	{
		strcat(appendFilename, pBS+1);		// NewXX.spk
	}

	long previousFilesize;
	WORD previousSpkSize;

	//------------------------------------------------------------
	// �ٷ� �� ������ ����
	//------------------------------------------------------------
	if (m_AppendPatch.size()==0)
	{
		previousFilesize = m_orgFilesize;
		previousSpkSize	= m_orgSpkSize;
	}
	else
	{
		APPEND_PATCH_NODE* pNode = m_AppendPatch.back();

		previousFilesize = pNode->afterFilesize;
		previousSpkSize = pNode->afterSpkSize;
	}

	//------------------------------------------------------------
	// ���� ���� ����
	//------------------------------------------------------------
	APPEND_PATCH_NODE* pNode = new APPEND_PATCH_NODE;

	pNode->appendFilename	= appendFilename;
	pNode->appendFilesize	= appendFilesize;
	pNode->appSpkSize		= appSpkSize;		
	pNode->writePosition	= previousFilesize;
	pNode->afterFilesize	= previousFilesize + appendFilesize-2;	// SPK�� ���� �κ� 2 bytes
	pNode->afterSpkSize		= previousSpkSize + appSpkSize;

	m_AppendPatch.push_back( pNode );

	return true;
}

//-----------------------------------------------------------------------------
// Execute Patch
//-----------------------------------------------------------------------------
bool
AppendPatch::ExecutePatch() const
{
	APPEND_PATCH_VECTOR::const_iterator iNode = m_AppendPatch.begin();

	while (iNode != m_AppendPatch.end())
	{
		APPEND_PATCH_NODE* pNode = *iNode;

		if (!pNode->Append(m_orgFilename.GetString()))
		{
			return false;
		}
	
		iNode++;
	}

	return true;
}

//-----------------------------------------------------------------------------
// Check FinalInfo
//-----------------------------------------------------------------------------
bool
AppendPatch::CheckFinalInfo() const
{
	class ifstream orgFile(m_orgFilename.GetString(), ios::binary | ios::nocreate);
		
	if (orgFile.is_open())
	{
		WORD spkSize;
		orgFile.read((char*)&spkSize, 2);	// Sprite�� ����

		if (spkSize != m_finalSpkSize)
		{
			return false;
		}

		orgFile.seekg( 0, ios::end );
		long fpEnd = orgFile.tellg();

		if (fpEnd != m_finalFilesize)
		{
			return false;
		}
		
		orgFile.close();
	}

	return true;
}

//-----------------------------------------------------------------------------
// Calculate FinalInfo 
//-----------------------------------------------------------------------------
// �������� �´��� üũ�Ѵ�.
//-----------------------------------------------------------------------------
bool
AppendPatch::CalculateFinalInfo() const
{
	APPEND_PATCH_VECTOR::const_iterator iNode = m_AppendPatch.begin();

	long totalFilesize	= m_orgFilesize;
	WORD totalSpkSize	= m_orgSpkSize;

	while (iNode != m_AppendPatch.end())
	{
		APPEND_PATCH_NODE* pNode = *iNode;

		totalFilesize += pNode->appendFilesize - 2;	// -2 for spkNum
		totalSpkSize += pNode->appSpkSize;
		
		iNode++;
	}

	if (m_finalFilesize==totalFilesize
		&& m_finalSpkSize==totalSpkSize)
	{
		return true;
	}
	
	return false;
}

//-----------------------------------------------------------------------------
// Save To File
//-----------------------------------------------------------------------------
void		
AppendPatch::SaveToFile(class ofstream& file)
{	
	m_orgFilename.SaveToFile( file );
	file.write((const char*)&m_orgFilesize, 4);
	file.write((const char*)&m_orgSpkSize, 2);
	file.write((const char*)&m_finalFilesize, 4);
	file.write((const char*)&m_finalSpkSize, 2);

	int num = m_AppendPatch.size();
	file.write((const char*)&num, 4);

	APPEND_PATCH_VECTOR::const_iterator iNode = m_AppendPatch.begin();

	while (iNode != m_AppendPatch.end())
	{
		APPEND_PATCH_NODE* pNode = *iNode;

		pNode->SaveToFile( file );
		
		iNode++;
	}	
}

//-----------------------------------------------------------------------------
// Load From File
//-----------------------------------------------------------------------------
void		
AppendPatch::LoadFromFile(class ifstream& file)
{
	Release();

	m_orgFilename.LoadFromFile( file );
	file.read((char*)&m_orgFilesize, 4);
	file.read((char*)&m_orgSpkSize, 2);
	file.read((char*)&m_finalFilesize, 4);
	file.read((char*)&m_finalSpkSize, 2);

	int num;
	file.read((char*)&num, 4);

	for (int i=0; i<num; i++)
	{
		APPEND_PATCH_NODE* pNode = new APPEND_PATCH_NODE;

		pNode->LoadFromFile( file );
		
		m_AppendPatch.push_back( pNode );
	}
}


//-----------------------------------------------------------------------------
// GetAllSize
//-----------------------------------------------------------------------------
int
AppendPatchTable::GetAllSize() const
{
	int allSize = 0;

	for (int i=0; i<m_Size; i++)
	{
		allSize += m_pTypeInfo[i].GetSize();
	}

	return allSize;
}

