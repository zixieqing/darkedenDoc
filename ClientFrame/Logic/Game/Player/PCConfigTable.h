//----------------------------------------------------------------------
// PCConfigTable.h
//----------------------------------------------------------------------
// key���� <WorldID, PlayerID>�� ���� PCConfig����
//
// �ϴ���... PlayerID�� 3ĳ�� �߿��� 
//           ��� ĳ���� �ֱٿ� �����߳�?�� ������ ������ �ȴ�.
//
// ��� ����Ű, ��Ÿ ĳ���� ������ �ɼ�? ���� ����...��?
// �� ������� ���� �� �ְ���...
// �����̾�.. PlayerID�ۿ�.. -_-;
//
// [ RecentCountó�� ]
//
// PlayerID data������ �����ϱ� ���ؼ� LRU PlayerID�� �����Ѵ�.
// save�Ҷ����� RecentCount�� 1�� ������Ų��.
// SetLastSlot(�����Ҷ�)�� ���� �ʰ�.. save�� �ϰ� �Ǹ�
// �ᱹ RecentCount�� ���� ū �ְ�.. ����~~ �������� �����Ѿְ� �ȴ�.
// 
//----------------------------------------------------------------------

#ifndef __PC_CONFIG_TABLE_H__
#define __PC_CONFIG_TABLE_H__

#pragma warning(disable:4786)

#include <Windows.h>
#include <map>
#include <string>
class ofstream;
class ifstream;

/*
class CharacterConfig {
	public :
		PCConfig();
		~PCConfig();			
};
*/

//----------------------------------------------------------------------
// PlayerConfig
//----------------------------------------------------------------------
class PlayerConfig {
	public :
		PlayerConfig();
		~PlayerConfig();

		//--------------------------------------------------------
		// PlayerID
		//--------------------------------------------------------
		void				SetPlayerID(const std::string& playerID)	{ m_PlayerID = playerID; }
		const std::string&	GetPlayerID() const							{ return m_PlayerID; }
		
		//--------------------------------------------------------
		// slot
		//--------------------------------------------------------
		int			GetLastSlot() const				{ return m_LastSlot; }
		void		SetLastSlot(int slot);

		DWORD		GetRecentCount() const						{ return m_RecentCount; }
		
		//--------------------------------------------------------
		// File I/O
		//--------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

	protected :
		std::string	m_PlayerID;
		BYTE		m_LastSlot;			// �ֱٿ� login�� ĳ������ slot��ȣ( 0,1,2 )
		DWORD		m_RecentCount;		// ���� �������� ����(LRU) ĳ���� üũ��.
		//CharacterConfig[3]			// ĳ���͵鿡 ���� ����
};

//----------------------------------------------------------------------
// PlayerConfigTable
//----------------------------------------------------------------------
// map<PlayerID, PlayerConfig*>
//----------------------------------------------------------------------
class PlayerConfigTable : public std::map<std::string, PlayerConfig*> {
	public :
		PlayerConfigTable();
		~PlayerConfigTable();

		void				Release();

		//--------------------------------------------------------
		// Add/Get PlayerConfigTable
		//--------------------------------------------------------
		void				AddPlayerConfig(PlayerConfig* pConfig);
		PlayerConfig*		GetPlayerConfig(const char* pPlayerID) const;

		//--------------------------------------------------------
		// Limit PlayerConfig
		//--------------------------------------------------------
		void				LimitPlayerConfig(int limit);

		//--------------------------------------------------------
		// File I/O
		//--------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

};


//----------------------------------------------------------------------
// WorldPlayerConfigTable
//----------------------------------------------------------------------
// map<WorldID, PlayerConfigTable*>
//----------------------------------------------------------------------
class WorldPlayerConfigTable : public std::map<int, PlayerConfigTable*> {
	public :
		WorldPlayerConfigTable();
		~WorldPlayerConfigTable();

		void				Release();

		//--------------------------------------------------------
		// Add/Get PlayerConfigTable
		//--------------------------------------------------------
		void				AddPlayerConfigTable(int worldID, PlayerConfigTable* pTable);
		PlayerConfigTable*	GetPlayerConfigTable(int worldID) const;

		//--------------------------------------------------------
		// File I/O
		//--------------------------------------------------------
		void		SaveToFile(const char* pFilename);
		void		LoadFromFile(const char* pFilename);
};


//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
extern WorldPlayerConfigTable*		g_pWorldPlayerConfigTable;

#endif

