//----------------------------------------------------------------------
// MZoneTable.h
//----------------------------------------------------------------------
// Zone Loading�ÿ� Zone���� �ʿ��� ������ �����ϴ� class
//----------------------------------------------------------------------
//
// [ Zone���� Loadind�� �ʿ��� ���� ] 
//
// - ZoneID
// - Zoneũ��Type (Large or Small)
// - file�̸�
// 
//----------------------------------------------------------------------

#ifndef	__MZONETABLE_H__
#define	__MZONETABLE_H__

#include <Windows.h>
#include "MTypeDef.h"
#include "MString.h"
#include <map>
#include <list>

#define	FLAG_ZONESIZE_SMALL		0x01


// 2004, 5, 14 sobeit add start - pk zone ����
#define PK_TYPE_NULL			0			// �׳� default map
#define PK_TYPE_DISABLE			0x01		// �� �츮��..-_-; pk ����
#define PK_TYPE_ALL				0x02		// �� ���� �� ��
#define PK_TYPE_GUILD			0x03		// �츮 ��� ���� �� ��..
#define PK_TYPE_SIEGE			0x04		// Siege �� // effect status������ ��
// 2004, 5, 14 sobeit add end - pk zone ����
//----------------------------------------------------------------------
//
// �� ������ Zone�� ���� ����
//
//----------------------------------------------------------------------
class ZONETABLE_INFO {
	public :
		typedef std::list<TYPE_SOUNDID>			SOUNDID_LIST;

	
	public :
		TYPE_ZONEID				ID;						// Zone ID
		MString					Name;					// Zone �̸�
		BYTE					Property;				// Zone�� �Ӽ�
		MString					Filename;				// Zone File�̸�
		MString					InfoFilename;			// ZoneInfo File�̸�
		MString					TeenFilename;			// Minimap File�̸�
		TYPE_MUSICID			MusicIDSlayer;			// Music����		
		TYPE_MUSICID			MusicIDVampire;			// Music����		
		SOUNDID_LIST			SoundIDList;			// random�ϰ� ���� �Ҹ���..
		WORD					CreatureColorSet;		// Zone ��ü�� �� ���� �ٲٱ�
		bool					Safety;
		unsigned short			MinimapSpriteID;		// �̴ϸ��� ��������Ʈ ���̵�
		bool					HolyLand;				// �ƴ��� �����ΰ�
		bool					ChatMaskByRace;			// ������ ���� ä�ó��뿡 ����ũ�� ����°�
		bool					CannotAttackInSafe;		// �������뿡�� ������ �� ���°�
		bool					CannotUseSpecialItem;	// �����̳� ��ȯ ���� ����
		bool					CompetenceZone;
		BYTE					PKType;					// ���� PK �����ΰ�?
		
	public :
		ZONETABLE_INFO();

		TYPE_SOUNDID			GetRandomSoundID() const;

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);		
		void			LoadFromFile(class ifstream& file);		
};

//----------------------------------------------------------------------
//
// ��ü Zone�� ���� ����
//
//----------------------------------------------------------------------
class CZoneTable {
	public :
		typedef	std::map<TYPE_ZONEID, ZONETABLE_INFO*>	ZONEINFO_MAP;

	public :
		CZoneTable();
		~CZoneTable();

		//-------------------------------------------------------
		// Release
		//-------------------------------------------------------
		void				Release();

		//-------------------------------------------------------
		// zoneID�� id�� zone�� ������ ��´�.
		//-------------------------------------------------------
		bool				Add(ZONETABLE_INFO* pZoneInfo);
		ZONETABLE_INFO*		Get(TYPE_ZONEID id);

		const ZONEINFO_MAP&	GetZoneMap() const	{ return m_mapZoneInfo; }

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void				SaveToFile(class ofstream& file);
		void				LoadFromFile(class ifstream& file);
	
	protected :
		ZONEINFO_MAP		m_mapZoneInfo;		// zone���� map
};

extern CZoneTable*		g_pZoneTable;

#endif


