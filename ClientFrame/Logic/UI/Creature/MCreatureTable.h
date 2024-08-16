//----------------------------------------------------------------------
// MCreatureTable.h
//----------------------------------------------------------------------
// Creature�� ������ ���� ������ �����ϴ� class
//----------------------------------------------------------------------
//
// [ �������� �ִ� ���� ] 
//
// - ���� FrameID
// - Sprite FilePosition
// - First SpriteID
// - �̸�... ���...
// 
//----------------------------------------------------------------------

#ifndef	__MCREATURETABLE_H__
#define	__MCREATURETABLE_H__

#pragma warning(disable:4786)

#include "MObject.h"
#include "SpriteLib\DrawTypeDef.h"
#include "CTypeTable.h"
#include "MString.h"
#include <list>
#include <vector>
class ifstream;
class ofstream;

//----------------------------------------------------------------------
// Creature�� ����
//----------------------------------------------------------------------
enum CREATURETRIBE
{	
	CREATURETRIBE_SLAYER,			// �����̾�
	CREATURETRIBE_VAMPIRE,			// �����̾�
	CREATURETRIBE_NPC,				// NPC
	CREATURETRIBE_SLAYER_NPC,		// �����̾� ��������Ʈ�� ����ϴ� NPC
	CREATURETRIBE_OUSTERS,
	CREATURETRIBE_OUSTERS_NPC,		// �ƿ콺���� ��������Ʈ�� ����ϴ� NPC
	MAX_CREATURETRIBE
};

//----------------------------------------------------------------------
// CreatureType
//----------------------------------------------------------------------
#define	CREATURETYPE_SLAYER_MALE		0
#define	CREATURETYPE_SLAYER_FEMALE		1

#define	CREATURETYPE_VAMPIRE_MALE1		2
#define	CREATURETYPE_VAMPIRE_FEMALE1	3

#define	CREATURETYPE_VAMPIRE_MALE2		514
#define	CREATURETYPE_VAMPIRE_FEMALE2	515

#define	CREATURETYPE_VAMPIRE_MALE3		558
#define	CREATURETYPE_VAMPIRE_FEMALE3	559
// add by Coffee 2006.11.24  ���ӹ�����������
#define	CREATURETYPE_VAMPIRE_MALE4		807
#define	CREATURETYPE_VAMPIRE_FEMALE4	808
//add by viva  195
#define	CREATURETYPE_VAMPIRE_MALE5		809
#define	CREATURETYPE_VAMPIRE_FEMALE5	810
//add by viva  215
#define	CREATURETYPE_VAMPIRE_MALE6		811
#define	CREATURETYPE_VAMPIRE_FEMALE6	812

// end
#define	CREATURETYPE_BAT				185
#define	CREATURETYPE_WOLF				186
#define	CREATURETYPE_SLAYER_OPERATOR	367
#define	CREATURETYPE_VAMPIRE_OPERATOR	369//805//765//804//369
//#define	CREATURETYPE_VAMPIRE_OPERATOR	810//add by viva
#define	CREATURETYPE_OUSTERS_OPERATOR	652
#define CREATURETYPE_OUSTERS			651
#define CREATURETYPE_WER_WOLF			671
#define CREATURETYPE_GHOST				716
#define CREATURETYPE_INSTALL_TURRET		742
#define CREATURETYPE_ROCKET_LUNCHER		767
#define CREATURETYPE_WILD_WOLF			787
//----------------------------------------------------------------------
// �����̾� NPC�� ���忡 ���� ����
//----------------------------------------------------------------------
class ITEM_WEARINFO
{
	public :
		WORD		skinColor;
		WORD		hairColor;		
		WORD		jacketColor;
		WORD		pantsColor;
		WORD		helmetColor;
		WORD		weaponColor;
		WORD		shieldColor;
		WORD		motorcycleColor;
		
		BYTE		hair;		
		BYTE		jacket;
		BYTE		pants;
		BYTE		helmet;
		BYTE		weapon;
		BYTE		shield;
		BYTE		motorcycle;

	public :
		ITEM_WEARINFO();

		void		operator = (const ITEM_WEARINFO& info);
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);
};


//----------------------------------------------------------------------
//
// �� ������ Creature�� ���� ����
//
//----------------------------------------------------------------------
class CREATURETABLE_INFO {
	public :		
		MString					Name;					// ĳ���� �̸�
		CTypeTable<int>			SpriteTypes;			// SpriteTable������ ID
		bool					bMale;					// �����ΰ�?		
		BYTE					MoveTimes;				// �̵� ȸ��
		BYTE					MoveRatio;				// Frame��/�̵� ȸ��... �׸��� 12frame�̶� 6���� �̵��� ���� �ִ�.
		BYTE					MoveTimesMotor;			// ������� ���� �� �̵� ȸ��
		int						Height;					// Ű (ä�� ��� ��ġ�� ���ؼ�)
		int						DeadHeight;				// �׾������� Ű
		TYPE_ACTIONINFO			DeadActionInfo;			// �������� actionInfo
		int						ColorSet;				// �ٲ�� ���� ��ȣ
		bool					bFlyingCreature;		// ���ƴٴϴ� ĳ���ΰ�?
		int						FlyingHeight;			// ���ƴٴϴ� ����
		bool					bHeadCut;				// �Ӹ� �߸��°�? -_-;
		int						HPBarWidth;				// HP bar ũ��
		ITEM_WEARINFO*			pItemWearInfo;			// �����̾� NPC�� ���
		WORD					ChangeColorSet;			// ĳ���� ��ü�� �ٲ�� ���
		int						ShadowCount;			// �� ����ٴϴ� ���� �ܻ� ����

	protected :
		CREATURETRIBE			m_CreatureTribe;		// ����
		TYPE_SOUNDID*			m_pActionSound;			// Sound ID
		int*					m_pActionCount;			// Action Count
		
	public :
		CREATURETABLE_INFO();
		~CREATURETABLE_INFO();

		//-------------------------------------------------------
		// Set / Get
		//-------------------------------------------------------
		void				SetCreatureTribe(enum CREATURETRIBE ct, int nMaxAction = 0);
		bool				IsSlayer() const						{ return m_CreatureTribe==CREATURETRIBE_SLAYER || m_CreatureTribe==CREATURETRIBE_SLAYER_NPC; }
		bool				IsVampire() const						{ return m_CreatureTribe==CREATURETRIBE_VAMPIRE; }
		bool				IsOusters() const						{ return m_CreatureTribe==CREATURETRIBE_OUSTERS || m_CreatureTribe==CREATURETRIBE_OUSTERS_NPC; }
		bool				IsNPC() const							{ return m_CreatureTribe==CREATURETRIBE_NPC || m_CreatureTribe==CREATURETRIBE_SLAYER_NPC|| m_CreatureTribe==CREATURETRIBE_OUSTERS_NPC; }
		void				SetActionSound(int n, int count, TYPE_SOUNDID sid)	{ m_pActionCount[n] = count;  m_pActionSound[n] = sid; }
		void				SetActionSound(int n, TYPE_SOUNDID sid)	{ m_pActionSound[n] = sid; }
		void				SetActionCount(int n, int count)		{ m_pActionCount[n] = count; }

		enum CREATURETRIBE	GetCreatureTribe() const				{ return m_CreatureTribe; }
		int					GetActionCount(int n)					{ return m_pActionCount[n]; }		
		TYPE_SOUNDID		GetActionSound(int n)					{ return m_pActionSound[n]; }		
		int					GetActionMax() const;
		
		bool				IsFlyingCreature() const				{ return bFlyingCreature; }

		//-------------------------------------------------------
		// assign
		//-------------------------------------------------------
		void				operator = (const CREATURETABLE_INFO& creatureInfo);

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void				SaveToFile(class ofstream& file);
		void				LoadFromFile(class ifstream& file);	
		
	protected :
		void				InitActionType(int nMaxAction = 0);				
};

//----------------------------------------------------------------------
// CreatureSpriteTypeMapper
//----------------------------------------------------------------------
// SpriteID�� CreatureType�� ã�� ��쿡 ���
//----------------------------------------------------------------------
class CreatureSpriteTypeMapper {
	public :
		typedef std::vector<WORD>				CREATURE_TYPES;		// WORD.. ������..
		typedef std::vector<CREATURE_TYPES*>	CREATURE_SPRITE_TYPES;

	public :
		CreatureSpriteTypeMapper();
		~CreatureSpriteTypeMapper();

		void	Init(int num);
		void	Release();

		void	AddCreatureType(TYPE_SPRITEID spriteID, WORD creatureType);
		int		GetRandomCreatureType(TYPE_SPRITEID spriteID) const;

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void				SaveToFile(class ofstream& file);
		void				LoadFromFile(class ifstream& file);	

	protected :
		CREATURE_SPRITE_TYPES	m_CreatureSpriteTypes;
};


typedef CTypeTable<CREATURETABLE_INFO>	CREATURE_TABLE;
extern CREATURE_TABLE* g_pCreatureTable;

extern CreatureSpriteTypeMapper* g_pCreatureSpriteTypeMapper;

#endif


