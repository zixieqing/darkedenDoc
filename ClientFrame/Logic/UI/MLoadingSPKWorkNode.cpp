//----------------------------------------------------------------------
// MLoadingSPKWorkNode.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MLoadingSPKWorkNode.h"

extern bool		FileOpenBinary(const char* filename, class ifstream& file);

//----------------------------------------------------------------------
// MLoadingSPKWorkNode1 :: Execute
//----------------------------------------------------------------------
//		= FilePosition���� SFPArray�� �о SPK�� load�Ѵ�.
//		CSpritePack*	SPK
//		long			FilePosition
//
//		[Remain] --> Node 2
//----------------------------------------------------------------------
BOOL
MLoadingSPKWorkNode1::Execute(MWorkNode*& pRemainNode)
{
	// ������
	//m_bExecute = TRUE;

	//---------------------------------------------------
	//
	// Load SpriteFilePositionArray 
	//
	//---------------------------------------------------
	class ifstream file;
	if (!FileOpenBinary(m_SFPAFilename, file))
	{
		// -_-;;
		m_bExecute = FALSE;
		pRemainNode = NULL;
		return FALSE;
	}
	CSpriteFilePositionArray SFPA;
	SFPA.LoadFromFile( file );
	file.close();

	//---------------------------------------------------
	//
	// SPK Load
	//
	//---------------------------------------------------
	class ifstream spkFile;
	if (!FileOpenBinary(m_SPKFilename, spkFile))
	{
		// -_-;;
		m_bExecute = FALSE;
		pRemainNode = NULL;
		return FALSE;
	}

	int size = SFPA.GetSize();
	for (int i=0; i<size; i++)
	{
		//---------------------------------------------------
		// ��� load���� ���..
		//---------------------------------------------------
		if (m_bExecute)
		{
			// Load�ҷ��� ��ġ���� FilePosition�� �̵��Ѵ�.
			spkFile.seekg( SFPA[i].FilePosition, ios::beg );

			CSprite& sprite = (*m_pSPK)[SFPA[i].SpriteID];

			//---------------------------------------------------
			// Sprite�� Load�Ѵ�.
			//---------------------------------------------------
			// ���� Load���� ���� ��쿡�� Load�Ѵ�.
			if (sprite.IsInit())
				continue;

			sprite.LoadFromFile( spkFile );
		}
		//---------------------------------------------------
		// Stop �� ���..
		//---------------------------------------------------
		else
		{
			//---------------------------------------------------
			// ������ ����̴�.
			//---------------------------------------------------
			// ���� SFPA�� ���ο� SFPA�� �����Ѵ�.
			// --> Node2	
			CSpriteFilePositionArray* pRemainSFPA = new CSpriteFilePositionArray;

			int remainSize = size - i;

			pRemainSFPA->Init( remainSize );			

			// m_SFPA�� ���� �κ��� �����Ѵ�.
			for (int j=0; j<remainSize; j++)
			{
				(*pRemainSFPA)[j] = SFPA[i + j];
			}

			MLoadingSPKWorkNode2* pNode = new MLoadingSPKWorkNode2( pRemainSFPA );

			pNode->SetSPK( m_pSPK, m_SPKFilename );
			pNode->SetType( m_Type );

			// ���� ���� �Ѱ��ش�.
			spkFile.close();
			pRemainNode = pNode;
			return FALSE;
		}
	}
	spkFile.close();

	// ���� ��
	m_bExecute = FALSE;

	// �������� ����..
	pRemainNode = NULL;
	return TRUE;
}


//----------------------------------------------------------------------
// MLoadingSPKWorkNode2 :: Execute
//----------------------------------------------------------------------
//		= SFPArray�� �̿��ؼ� SPK���� load�Ѵ�.
//
//		SFPArray*		SFPA
//
//		[Remain] --> Node 2
//----------------------------------------------------------------------
BOOL
MLoadingSPKWorkNode2::Execute(MWorkNode*& pRemainNode)
{
	//m_bExecute = TRUE;

	//---------------------------------------------------
	//
	// SPK Load
	//
	//---------------------------------------------------
	class ifstream spkFile;
	if (!FileOpenBinary(m_SPKFilename, spkFile))
	{
		// -_-;;
		m_bExecute = FALSE;
		pRemainNode = NULL;
		return FALSE;
	}

	int size = m_pSFPA->GetSize();
	for (int i=0; i<size; i++)
	{
		SPRITE_FILEPOSITION_NODE& node = (*m_pSFPA)[i];

		//---------------------------------------------------
		// ��� load���� ���..
		//---------------------------------------------------
		if (m_bExecute)
		{
			// Load�ҷ��� ��ġ���� FilePosition�� �̵��Ѵ�.
			spkFile.seekg( node.FilePosition, ios::beg );

			CSprite& sprite = (*m_pSPK)[node.SpriteID];

			//---------------------------------------------------
			// Sprite�� Load�Ѵ�.
			//---------------------------------------------------
			// ���� Load���� ���� ��쿡�� Load�Ѵ�.
			if (sprite.IsInit())
				continue;

			sprite.LoadFromFile( spkFile );
		}
		//---------------------------------------------------
		// Stop �� ���..
		//---------------------------------------------------
		else
		{
			CSpriteFilePositionArray* pRemainSFPA = new CSpriteFilePositionArray;

			int remainSize = size - i;

			pRemainSFPA->Init( remainSize );			

			// m_SFPA�� ���� �κ��� �����Ѵ�.
			for (int j=0; j<remainSize; j++)
			{
				(*pRemainSFPA)[j] = (*m_pSFPA)[i + j];
			}

			MLoadingSPKWorkNode2* pNode = new MLoadingSPKWorkNode2( pRemainSFPA );

			pNode->SetSPK( m_pSPK, m_SPKFilename );
			pNode->SetType( m_Type );

			// ���� ���� �Ѱ��ش�.
			spkFile.close();
			pRemainNode = pNode;
			return FALSE;
		}
	}
	spkFile.close();

	// ���� ��
	m_bExecute = FALSE;

	// ���������� ���� ���
	pRemainNode = NULL;
	return TRUE;
}

//----------------------------------------------------------------------
// MLoadingSPKWorkNode3 :: Execute
//----------------------------------------------------------------------
//		TYPE_SPRITEID	SpriteID
//		long			FilePosition
//
//		[Remain] --> NULL
//----------------------------------------------------------------------
BOOL
MLoadingSPKWorkNode3::Execute(MWorkNode*& pRemainNode)
{
	//m_bExecute = TRUE;

	CSprite& sprite = (*m_pSPK)[m_SpriteID];

	//-------------------------------------------------------------
	// ���� Loading���� ���� ��쿡�� loading�Ѵ�.
	//-------------------------------------------------------------
	if (sprite.IsNotInit())
	{	
		class ifstream spkFile;
		if (!FileOpenBinary(m_SPKFilename, spkFile))
		{
			// -_-;;
			m_bExecute = FALSE;
			pRemainNode = NULL;
			return FALSE;
		}

		// loading�ҷ��� sprite�� �����Ѵ�.
		spkFile.seekg(m_FilePosition, ios::beg);
		
		//--------------------------------------------------
		// Sprite �ϳ� Loading
		//--------------------------------------------------
		if (sprite.LoadFromFile( spkFile ))
		{
		}
		else
		{
			// -_-;;
			// ����.. �̷� �� �ֳ�..
			int a =0;
		}
		spkFile.close();
	}

	m_bExecute = FALSE;	

	pRemainNode = NULL;
	return TRUE;
}


//----------------------------------------------------------------------
// MLoadingSPKWorkNode4 :: Execute
//----------------------------------------------------------------------
//		TYPE_SPRITEID	FirstSpriteID
//		TYPE_SPRITEID	LastSpriteID
//		long			FilePosition
//
//		[Remain] --> Node 4
//----------------------------------------------------------------------
BOOL
MLoadingSPKWorkNode4::Execute(MWorkNode*& pRemainNode)
{
	//m_bExecute = TRUE;

	class ifstream spkFile;
	if (!FileOpenBinary(m_SPKFilename, spkFile))
	{
		// -_-;;
		m_bExecute = FALSE;
		pRemainNode = NULL;
		return FALSE;
	}

	//-------------------------------------------------------
	// FirstSprite�� ����..
	//-------------------------------------------------------
	spkFile.seekg(m_FilePosition, ios::beg);

	//-------------------------------------------------------
	// FirstSpriteID ~ LastSpriteID�� Loading�Ѵ�.
	//-------------------------------------------------------
	for (TYPE_SPRITEID i=m_FirstSpriteID; i<m_LastSpriteID; i++)
	{
		//---------------------------------------------------
		// ��� load���� ���..
		//---------------------------------------------------
		if (m_bExecute)
		{
			CSprite& sprite = (*m_pSPK)[i];

			//---------------------------------------------------
			// ���� loading���� ���� ��쿡�� loading�Ѵ�.
			// (!) �ȵȴ�.. file position�� �������Ѿ� �Ǳ� ����..
			// ������ loading!
			//---------------------------------------------------
			//if (sprite.IsNotInit())
			{
				sprite.LoadFromFile( spkFile );
			}
		}
		//---------------------------------------------------
		// Stop�� ���
		//---------------------------------------------------
		else
		{
			//---------------------------------------------------
			// firstSpriteID�� ������ i�� �����ؼ� node�� �����Ѵ�.
			//---------------------------------------------------
			MLoadingSPKWorkNode4* pNode = new MLoadingSPKWorkNode4( 
													i,					// first SpriteID
													m_LastSpriteID,		// last SpriteID
													spkFile.tellg()		// file position
												);
			pNode->SetSPK( m_pSPK, m_SPKFilename );
			pNode->SetType( m_Type );

			spkFile.close();
			
			pRemainNode = pNode;
			return FALSE;
		}
	}

	m_bExecute = FALSE;

	spkFile.close();
	pRemainNode = NULL;
	return TRUE;
}

