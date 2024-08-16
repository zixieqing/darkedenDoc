//----------------------------------------------------------------------
// MActionInfo.h
//----------------------------------------------------------------------
//
//  = ����Ǵ� Effect��� �ϳ��� ����(�ʻ��..)�� ǥ���ϱ� ���� �ʿ��� ����
//
//  = ActionInfoNode
//    - EffectGeneratorTableID
//    - BltType
//    - FrameID
//    - ���ӽð�
//
//  = ActionInfoNode�� array
//
//----------------------------------------------------------------------
/*

  [ ��(Player)�� ��� ]

	Action�� ����Ǵ� �������� 
		Server�� ��� ��� Packet�� ������
		g_ActionInfoTable�� �����ؼ� ��� ��� ���� ȿ���� ǥ�����ش�.

	��� ��� ���߿� Server���� ���Packet�� �����ϸ�,
		(Player�� �������� ���ID�� ���� ���)
		�� ������� ActionResult�� ���� 
		Player�� �ִ� EffectTarget�� ActionResult*�� �����Ѵ�.


	�ƴ� ���, 
		�� ������� ActionResult�� ���� �ٷ� ����� �����Ų��.
		EffectTarget�� �ٷ� �����ϰ� EffectGenerator�� ���ؼ�..
		Effect����..... ���..


  [ �ٸ� ����� ��� ]

	����Action�� ���Action�� �����...�� �ϳ��� Packet���� �Ѿ�´�.
	���Action���� ActionResult�� ���� 
	����Action�� �����Ҷ�, EffectTarget�� ActionResult*�� �����Ѵ�.


  (*) EffectGenerator���� ActionResult�� 


  [ ���� ]

  - � ����� �������� �ܰ�(ACTION_INFO_NODE)�� ��������..
	������ ��ǥ���� ����̴�.

  ==> ĳ���õ���+ĳ����Effect --> �������Effect --> �������Effect --> �����Effect
     
  ==> [����]  ĳ���õ��� --> �������Effect --> �������Effect --> .... � ���� �ִ�.

  - ���⼭ ĳ���õ���+ĳ����Effect�� MActionInfo��,
    �� ���� ���۴ܰ���� �ϳ��� ACTION_INFO_NODE��� ��Ÿ�� �� �ִ�.

  - casting Effect�� AttachEffect��.. ĳ���Ϳ� �پ ǥ���Ǵ� ���̴�.
  - Casting ActionInfo�� �� ������ Casting�� ǥ���� �� �ִ�.

  - �ϳ��� ���(MActionInfo)�� �� ��� ������ ������
    ACTION_INFO_NODE�� array�μ� ǥ���� �ȴ�.

  - �� ����� ���� ACTION_INFO_NODE �߿����� '�⺻ ����' Ȥ�� '���� ����' ���� 
    �ǹ̷� �Ҹ����� ������ ���� �� �ִ�.
	(���������� �ߵ��Ǵ� ����̶�� ���� ���� �ִ�.)
	�̷� �ܰ踦 MainNode�� �θ���.
	
  - MainNode�� ����� ��������(-_-;) ������ �ǹ��Ѵ�.
    ���� ���, 'Light���'���� ���� ������ ����
	��� �ð��� �޶��� �� �ִ�.
	�� ��, ��� �ð��� ǥ���ϴ� �ܰ踦 MainNode�� ������ �� �ִ�.
	����� �ٷ� ����Ǿ���ϴ� ��� MainNode���� ����� �����ϰ� �ȴ�.

  - node���� bDelayNode��
    delay�� ����޴� node�� �ǹ��Ѵ�.
	MainNode�� ����ϴٰ� �� �� ������
	�������� delay�� ����޴� node�̹Ƿ� �ǹ̰� �� �ٸ���.
	MainNode�� �ϳ��ۿ� ������, bDelayNode�� �������� �� �� �ִ�.
	

  -	�̹� MainNode�� �������� ���¸� �ٷ� ǥ������� �ϴ� ��쵵 �ִ�.
	(�ٸ� ȭ�鿡 �ִٰ� �þ߿� ���̴� ��� Server���� ������ �����ְ���)
	�̷� ���.. ĳ���õ����̳� �������Effect�� �������� �ʰ� �ٷ� 
	MainNode�� ǥ������� �Ѵ�.

  - ResultTime�� ����� ó�����ִ� �����̴�.
    �������� ACTION_INFO_NODE�߿��� Server���� ���� ���(!)�� 
	��������ִ� ����..
	������ �ȵ� ���.. ��~~���� ó�����ָ� �ǰ���..

  - StartWithCasting?
    ����� ������ 
	(1)ĳ���Ͱ� Casting������ �����ϸ鼭
	(2)ĳ������ Casting������ �����鼭(StartAfterCasting)
	...�� �� ���� ��찡 �ִ�.

  - Casting?
     EffectSpriteTypeID��.. AttachEffect �ϳ��� ǥ���Ǵ� ��찡 ��κ��̴�.
	 ������, CastingActionInfo��.. Ư���� ActionInfo�� ǥ���ؾ� �Ǵ� ��찡 �ִ�.
	 bCastingActionInfo�� �����Ǿ� �ִٸ� ResultActionInfo�� ���ٰ� �����Ѵ�. 

*/
//----------------------------------------------------------------------


#ifndef	__MACTIONINFOTABLE_H__
#define	__MACTIONINFOTABLE_H__

#include <Windows.h>
#include "MTypeDef.h"
#include "DrawTypeDef.h"
#include "MActionResultDef.h"
#include "MEffectStatusDef.h"
#include "CTypeTable.h"
//#include "SkillDef.h"
#include "MString.h"
class ofstream;
class ifstream;

//----------------------------------------------------------------------
// ����� �Ӽ��� ���� flag
//----------------------------------------------------------------------
#define	FLAG_ACTIONINFO_TARGET_NONE			0		// ����� �� ����
#define	FLAG_ACTIONINFO_TARGET_SELF			0x01	// ���ο��� ���
#define FLAG_ACTIONINFO_TARGET_OTHER		0x02	// Ÿ�ο��� ���
#define	FLAG_ACTIONINFO_TARGET_ZONE			0x04	// Zone�� ���
#define	FLAG_ACTIONINFO_TARGET_ITEM			0x08	// Item�� ���

//----------------------------------------------------------------------
// packet ����
//----------------------------------------------------------------------
enum ACTIONINFO_PACKET {
	ACTIONINFO_PACKET_NONE,
	ACTIONINFO_PACKET_SELF,			// ���ο��� ���
	ACTIONINFO_PACKET_OTHER,		// Ÿ�ο��� ���
	ACTIONINFO_PACKET_ZONE,			// Zone�� ���
	ACTIONINFO_PACKET_ITEM,			// Item�� ���
	ACTIONINFO_PACKET_BLOOD_DRAIN,	// ������ ���	
	ACTIONINFO_PACKET_THROW_BOMB,	// ��ź ������ ���
	ACTIONINFO_PACKET_UNTRANSFORM,	// ���� Ǯ��
	ACTIONINFO_PACKET_VISIBLE,		// invisible Ǯ��
	ACTIONINFO_PACKET_ABSORB_SOUL,	// ���� ���	
};

//----------------------------------------------------------------------
// ����� ���� ��ġ�� ���� flag
//----------------------------------------------------------------------
#define	FLAG_ACTIONINFO_START_USER				0x01	// ����� ��ġ���� ����
#define	FLAG_ACTIONINFO_START_TARGET			0x02	// ��ǥ ��ġ���� ����
#define	FLAG_ACTIONINFO_START_SKY				0x04	// ���߿��� ����

//----------------------------------------------------------------------
// ����� ��� ���
//----------------------------------------------------------------------
#define	FLAG_ACTIONINFO_USER_ALL				0xFF	// ��� �����
#define	FLAG_ACTIONINFO_USER_NONCREATURE		0x01	// creature�� �ƴ� ���� ���
#define	FLAG_ACTIONINFO_USER_SLAYER				0x02	// slayer���� ���
#define	FLAG_ACTIONINFO_USER_VAMPIRE			0x04	// vampire���� ���
#define	FLAG_ACTIONINFO_USER_NPC				0x08	// npc���� ���(-_-;)
#define	FLAG_ACTIONINFO_USER_MONSTER			0x10	// slayer���� ���
#define	FLAG_ACTIONINFO_USER_OUSTERS			0x20	// ousters���� ���

//----------------------------------------------------------------------
// ��� ��� ���� ����
//----------------------------------------------------------------------
// ���� �����صθ�.. �Ѿ��� �־�� ������.
#define FLAG_ACTIONINFO_WEAPON_ALL				0x007F	// ��� ����
#define FLAG_ACTIONINFO_WEAPON_HAND				0x0001	// �Ǽ�
#define FLAG_ACTIONINFO_WEAPON_SWORD			0x0002	// Į
#define FLAG_ACTIONINFO_WEAPON_BLADE			0x0004	// ��
#define FLAG_ACTIONINFO_WEAPON_GUN_ALL			0x0078	// TR
#define FLAG_ACTIONINFO_WEAPON_GUN_SR			0x0008	// TR
#define FLAG_ACTIONINFO_WEAPON_GUN_SG			0x0010	// SG
#define FLAG_ACTIONINFO_WEAPON_GUN_AR			0x0020	// AR
#define FLAG_ACTIONINFO_WEAPON_GUN_SMG			0x0040	// SMG
#define FLAG_ACTIONINFO_WEAPON_SHIELD			0x0080	// ����
#define FLAG_ACTIONINFO_WEAPON_HOLY_WATER		0x0100	// holy water����ϴ� ���
#define FLAG_ACTIONINFO_WEAPON_BOMB				0x0200	// ��ź ����ϴ� ���
#define FLAG_ACTIONINFO_WEAPON_CHAKRAM			0x0400	// íũ�� ����ϴ� ���

//----------------------------------------------------------------------
// ���� ��� �ִ� ������ ������ �޴´�.
//----------------------------------------------------------------------
#define	FLAG_ACTIONINFO_CURRENT_WEAPON_ACTION					0x01	// basic actionInfo�� action����
#define	FLAG_ACTIONINFO_CURRENT_WEAPON_RANGE					0x02	// basic actionInfo�� range����
#define	FLAG_ACTIONINFO_CURRENT_WEAPON_SOUND					0x04	// basic actionInfo�� sound����
#define	FLAG_ACTIONINFO_CURRENT_WEAPON_CASTING_STARTFRAME		0x08	// basic actionInfo�� GetCastingStartFrame()����
#define	FLAG_ACTIONINFO_CURRENT_WEAPON_CASTING_FRAMES			0x10	// basic actionInfo�� GetCastingFrames()����
#define	FLAG_ACTIONINFO_CURRENT_WEAPON_DELAY					0x20	// basic actionInfo�� GetDelay()����
#define	FLAG_ACTIONINFO_CURRENT_WEAPON_ACTIONEFFECTSPRITETYPE	0x40	// (���������� �決 - -;)

//----------------------------------------------------------------------
// option flag
//----------------------------------------------------------------------
#define	FLAG_ACTIONINFO_OPTION_RANGE_TO_DIRECTION	0x01	// range���� direction���� ����Ѵ�.
#define FLAG_ACTIONINFO_OPTION_USE_WITH_BLESS		0x02	// bless�ɸ� ���¿��� ����� �� �ִ�.

//----------------------------------------------------------------------
// Select Creature
//----------------------------------------------------------------------
#define FLAG_ACTIONINFO_SELECT_ALL					0xFF
#define	FLAG_ACTIONINFO_SELECT_ENEMY				0x01
#define	FLAG_ACTIONINFO_SELECT_FRIEND				0x02
#define	FLAG_ACTIONINFO_SELECT_PARTY				0x04
#define	FLAG_ACTIONINFO_SELECT_GUILD				0x08
#define	FLAG_ACTIONINFO_SELECT_FOLLOWER				0x10

//----------------------------------------------------------------------
// main node NULL
//----------------------------------------------------------------------
#define	MAIN_NODE_NULL						0xFFFF

#define MAX_ACTION_STEP							5

//----------------------------------------------------------------------
// ACTION_INFO_NODE class
//----------------------------------------------------------------------
class ACTION_INFO_NODE {
	public :
		ACTION_INFO_NODE()
		{
			SoundID		= SOUNDID_NULL;
			//Light		= 1;
			LinkCount	= 0xFFFF;

			bDelayNode	= false;
			bResultTime = false;	
			bUseCoord = false;
		}
		
		~ACTION_INFO_NODE() {}
		

	public :
		TYPE_EFFECTGENERATORID		EffectGeneratorID;	// EffectGenerator ID		
		TYPE_EFFECTSPRITETYPE		EffectSpriteType;	// EffectSpriteType
		WORD						Step;				// �ӵ�
		WORD						Count;				// �̹� node�� ���� �ð�
		WORD						LinkCount;			// �̹� node�� �ӹ����� �ð� == ���� node�� �Ѿ�������� �ð�
		TYPE_SOUNDID				SoundID;			// ����� �� �ܰ��� Sound ID
		//BYTE						Light;				// ���� ���
		bool						bDelayNode;			// delay�� ����Ǵ� node�ΰ�?
		bool						bResultTime;		// ����� �����ִ� �����̴�.
		bool						bUseCoord;			// Step �� ��ǥ�� ����Ѵ�.
		
	public :
		void			SetUseCoord()				{ bUseCoord = true; }		
		void			SetDelayNode()				{ bDelayNode = true; }
		void			SetResultTime()				{ bResultTime = true; }
		void			SetCoord(BYTE x, BYTE y)	{ if( bUseCoord ) Step = (x<<8)|y; }
		BYTE			GetX()						{ if( bUseCoord ) return Step>>8; return 0; }
		BYTE			GetY()						{ if( bUseCoord ) return Step&0xff; return 0; }

		void			operator = (const ACTION_INFO_NODE& node)
		{
			EffectGeneratorID	= node.EffectGeneratorID;
			EffectSpriteType	= node.EffectSpriteType;
			Step				= node.Step;
			Count				= node.Count;
			LinkCount			= node.LinkCount;
			SoundID				= node.SoundID;
			//Light				= node.Light;
			bResultTime			= node.bResultTime;
			bUseCoord			= node.bUseCoord;
		}

		//-------------------------------------------------------
		// �ֵ� ����.. -_-;
		//-------------------------------------------------------
		void			SetChildMode();

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void			SaveToFile(class ofstream& file);
		void			LoadFromFile(class ifstream& file);
};


//----------------------------------------------------------------------
// �ϳ��� ����� ���� ����
// ACTION_INFO_NODE�� array 
//----------------------------------------------------------------------
class MActionInfo : public CTypeTable<ACTION_INFO_NODE> {
	public :
		MActionInfo();	
		~MActionInfo();

		//------------------------------------------------------
		// Set
		//------------------------------------------------------
		void	Set(const char* name, BYTE action, TYPE_EFFECTSPRITETYPE ActionEffectSpriteType, BYTE range, BYTE fTarget, BYTE fStart=FLAG_ACTIONINFO_START_USER, WORD delay=0, int value=0)
		{
			m_Name						= name;
			m_Action					= action;
			m_ActionEffectSpriteType	= ActionEffectSpriteType;
			m_Range						= range;
			m_fTarget					= fTarget;
			m_fStart					= fStart;
			m_Delay						= delay;
			m_Value						= value;			
		}

		//------------------------------------------------------
		// female
		//------------------------------------------------------
		TYPE_EFFECTSPRITETYPE	GetActionEffectSpriteTypeFemale() const	{ return m_ActionEffectSpriteTypeFemale; }
		void		SetActionEffectSpriteTypeFemale(TYPE_EFFECTSPRITETYPE et)
		{
			m_ActionEffectSpriteTypeFemale = et; 
		}

		//------------------------------------------------------
		// Casting ����
		//------------------------------------------------------
		bool		IsCastingEffectToSelf() const			{ return m_bCastingEffectToSelf; }
		void		SetCastingEffectToSelf()				{ m_bCastingEffectToSelf = true; }
		void		SetCastingEffectToOther()				{ m_bCastingEffectToSelf = false; }

		// speed�� slow:normal:fast = 0:1:2 �̴�. ��������.. ����
		void		SetCastingStartFrameAll(int f)			{ m_CastingStartFrame[0] = m_CastingStartFrame[1] = m_CastingStartFrame[2] = f; }
		void		SetCastingFramesAll(int f)				{ m_CastingFrames[0] = m_CastingFrames[1] = m_CastingFrames[2] = f; }

		void		SetCastingStartFrame(int speed, int f)			{ m_CastingStartFrame[speed] = f; }
		void		SetCastingFrames(int speed, int f)				{ m_CastingFrames[speed] = f; }

		int			GetCastingStartFrame(int speed) const	{ return m_CastingStartFrame[speed]; }
		int			GetCastingFrames(int speed) const		{ return m_CastingFrames[speed]; }
		
		void		SetStartWithCasting()	{ m_StartFrame[0] = m_StartFrame[1] = m_StartFrame[2] = 0; }
		void		SetStartAfterCasting()	{ m_StartFrame[0] = m_StartFrame[1] = m_StartFrame[2] = 0xFFFF; }

		// ����ҷ��� CastingActionInfo
		void		SetCastingActionInfo(TYPE_ACTIONINFO ai)	{ m_CastingActionInfo=ai; }		
		TYPE_ACTIONINFO	GetCastingActionInfo() const		{ return m_CastingActionInfo; }		

		// �� ����� CastingAction�ΰ�?
		bool		IsCastingAction() const					{ return m_bCastingAction; }		
		void		SetCastingAction()						{ m_bCastingAction=true; }
		void		UnSetCastingAction()					{ m_bCastingAction=false; }	

		
		

		//------------------------------------------------------
		// Sound ID
		//------------------------------------------------------
		void	SetSoundID(TYPE_SOUNDID id)			{ m_SoundID = id; }

		//------------------------------------------------------
		// Main Node
		//------------------------------------------------------
		void	SetMainNode(int n)					{ m_MainNode=n; }

		//------------------------------------------------------
		// attack - ���� ����ΰ�?
		//------------------------------------------------------
		void		SetAttack()				{ m_bAttack = TRUE; }
		void		UnSetAttack()			{ m_bAttack = FALSE; }
		BOOL		IsAttack() const		{ return m_bAttack; }

		//------------------------------------------------------
		// get
		//------------------------------------------------------
		const char*	GetName() const			{ return m_Name; }
		BYTE		GetAction() const		{ return m_Action; }
		BYTE		GetRange() const		{ return m_Range; }
		TYPE_EFFECTSPRITETYPE	GetActionEffectSpriteType() const { return m_ActionEffectSpriteType; }
		WORD		GetDelay() const		{ return m_Delay; }
		int			GetValue() const		{ return m_Value; }
		TYPE_SOUNDID	GetSoundID() const		{ return m_SoundID; }
		BOOL		HasMainNode() const		{ return m_MainNode!=MAIN_NODE_NULL; }
		int			GetMainNode() const		{ return m_MainNode; }
		
		//------------------------------------------------------
		// ��ǥ�� �Ӽ�
		//------------------------------------------------------
		BYTE		GetTarget() const		{ return m_fTarget; }
		bool		IsTargetNone() const	{ return m_fTarget==0; }
		BYTE		IsTargetSelf() const	{ return m_fTarget & FLAG_ACTIONINFO_TARGET_SELF; }
		BYTE		IsTargetOther() const	{ return m_fTarget & FLAG_ACTIONINFO_TARGET_OTHER; }
		BYTE		IsTargetZone() const	{ return m_fTarget & FLAG_ACTIONINFO_TARGET_ZONE; }
		BYTE		IsTargetItem() const	{ return m_fTarget & FLAG_ACTIONINFO_TARGET_ITEM; }

		//------------------------------------------------------
		// ������ packet ����
		//------------------------------------------------------
		void		SetPacketType(ACTIONINFO_PACKET ap)		{ m_PacketType = ap; }
		ACTIONINFO_PACKET	GetPacketType() const			{ return m_PacketType; }
		bool		IsPacketTypeNone() const	{ return m_PacketType == ACTIONINFO_PACKET_NONE; }
		BYTE		IsPacketTypeSelf() const	{ return m_PacketType == ACTIONINFO_PACKET_SELF; }
		BYTE		IsPacketTypeOther() const	{ return m_PacketType == ACTIONINFO_PACKET_OTHER; }
		BYTE		IsPacketTypeZone() const	{ return m_PacketType == ACTIONINFO_PACKET_ZONE; }
		BYTE		IsPacketTypeItem() const	{ return m_PacketType == ACTIONINFO_PACKET_ITEM; }
		BYTE		IsPacketTypeThrowBomb() const	{ return m_PacketType == ACTIONINFO_PACKET_THROW_BOMB; }
		BYTE		IsPacketTypeUntransform() const	{ return m_PacketType == ACTIONINFO_PACKET_UNTRANSFORM; }
		BYTE		IsPacketTypeVisible() const		{ return m_PacketType == ACTIONINFO_PACKET_VISIBLE; }


		//------------------------------------------------------
		// ���� ��ġ
		//------------------------------------------------------
		BYTE		GetStart() const		{ return m_fStart; }
		bool		IsStartNone() const		{ return m_fStart==0; }
		BYTE		IsStartUser() const		{ return m_fStart & FLAG_ACTIONINFO_START_USER; }
		BYTE		IsStartTarget() const	{ return m_fStart & FLAG_ACTIONINFO_START_TARGET; }
		BYTE		IsStartSky() const		{ return m_fStart & FLAG_ACTIONINFO_START_SKY; }
		
		void		SetStartFrameAll(int f)	{ m_StartFrame[0] = m_StartFrame[1] = m_StartFrame[2] = f; }
		void		SetStartFrame(int speed, int f)	{ m_StartFrame[speed] = f; }
		int			GetStartFrame(int speed) const	{ return m_StartFrame[speed]; }

		//------------------------------------------------------
		// ����� ��� ���
		//------------------------------------------------------
		void	SetUser(BYTE fUser)				{ m_fUserType=fUser; }
		BYTE	GetUser() const					{ return m_fUserType; }
		void	AddUserNonCreature() 			{ m_fUserType|=FLAG_ACTIONINFO_USER_NONCREATURE; }
		void	AddUserSlayer() 				{ m_fUserType|=FLAG_ACTIONINFO_USER_SLAYER; }
		void	AddUserVampire() 				{ m_fUserType|=FLAG_ACTIONINFO_USER_VAMPIRE; }
		void	AddUserOusters() 				{ m_fUserType|=FLAG_ACTIONINFO_USER_OUSTERS; }
		void	AddUserNPC() 					{ m_fUserType|=FLAG_ACTIONINFO_USER_NPC; }
		void	AddUserMonster()				{ m_fUserType|=FLAG_ACTIONINFO_USER_MONSTER; }
		BYTE	IsUserNonCreature() const		{ return m_fUserType & FLAG_ACTIONINFO_USER_NONCREATURE; }
		BYTE	IsUserSlayer() const			{ return m_fUserType & FLAG_ACTIONINFO_USER_SLAYER; }
		BYTE	IsUserVampire() const			{ return m_fUserType & FLAG_ACTIONINFO_USER_VAMPIRE; }
		BYTE	IsUserOusters() const			{ return m_fUserType & FLAG_ACTIONINFO_USER_OUSTERS; }
		BYTE	IsUserNPC() const				{ return m_fUserType & FLAG_ACTIONINFO_USER_NPC; }
		BYTE	IsUserMonster() const			{ return m_fUserType & FLAG_ACTIONINFO_USER_MONSTER; }

		//------------------------------------------------------
		// ��� ��� ���� ����
		//------------------------------------------------------
		WORD	IsWeaponTypeAll() const			{ return (m_fWeaponType & FLAG_ACTIONINFO_WEAPON_ALL)==FLAG_ACTIONINFO_WEAPON_ALL; }
		WORD	IsWeaponTypeGunAll() const		{ return (m_fWeaponType & FLAG_ACTIONINFO_WEAPON_GUN_ALL)==FLAG_ACTIONINFO_WEAPON_GUN_ALL; }
		WORD	IsWeaponTypeGunAny() const		{ return m_fWeaponType & FLAG_ACTIONINFO_WEAPON_GUN_ALL; }
		WORD	GetWeaponType() const			{ return m_fWeaponType; }
		void	SetWeaponType(WORD flag)		{ m_fWeaponType = flag; }
		void	AddWeaponType(WORD flag)		{ m_fWeaponType |= flag; }		

		//-------------------------------------------------------
		// ���� ��� �ִ� ����
		//-------------------------------------------------------
		BYTE	IsAffectCurrentWeaponAction() const	{ return m_fCurrentWeapon & FLAG_ACTIONINFO_CURRENT_WEAPON_ACTION; }
		BYTE	IsAffectCurrentWeaponRange() const	{ return m_fCurrentWeapon & FLAG_ACTIONINFO_CURRENT_WEAPON_RANGE; }
		BYTE	IsAffectCurrentWeaponSound() const	{ return m_fCurrentWeapon & FLAG_ACTIONINFO_CURRENT_WEAPON_SOUND; }
		BYTE	IsAffectCurrentWeaponCastingStartFrame() const	{ return m_fCurrentWeapon & FLAG_ACTIONINFO_CURRENT_WEAPON_CASTING_STARTFRAME; }
		BYTE	IsAffectCurrentWeaponCastingFrames() const	{ return m_fCurrentWeapon & FLAG_ACTIONINFO_CURRENT_WEAPON_CASTING_FRAMES; }
		BYTE	IsAffectCurrentWeaponDelay() const	{ return m_fCurrentWeapon & FLAG_ACTIONINFO_CURRENT_WEAPON_DELAY; }
		BYTE	IsAffectCurrentWeaponActionEffectSpriteType() const	{ return m_fCurrentWeapon & FLAG_ACTIONINFO_CURRENT_WEAPON_ACTIONEFFECTSPRITETYPE; }
		int		GetAffectCurrentWeaponActionInfoPlus() const	{ return m_PlusActionInfo; }
		void	SetAffectCurrentWeaponAction()		{ m_fCurrentWeapon |= FLAG_ACTIONINFO_CURRENT_WEAPON_ACTION; }
		void	SetAffectCurrentWeaponRange()		{ m_fCurrentWeapon |= FLAG_ACTIONINFO_CURRENT_WEAPON_RANGE; }
		void	SetAffectCurrentWeaponSound()		{ m_fCurrentWeapon |= FLAG_ACTIONINFO_CURRENT_WEAPON_SOUND; }
		void	SetAffectCurrentWeaponCastingStartFrame()	{ m_fCurrentWeapon |= FLAG_ACTIONINFO_CURRENT_WEAPON_CASTING_STARTFRAME; }
		void	SetAffectCurrentWeaponCastingFrames()		{ m_fCurrentWeapon |= FLAG_ACTIONINFO_CURRENT_WEAPON_CASTING_FRAMES; }
		void	SetAffectCurrentWeaponDelay()		{ m_fCurrentWeapon |= FLAG_ACTIONINFO_CURRENT_WEAPON_DELAY; }
		void	SetAffectCurrentWeaponActionEffectSpriteType()		{ m_fCurrentWeapon |= FLAG_ACTIONINFO_CURRENT_WEAPON_ACTIONEFFECTSPRITETYPE; }
		void	SetAffectCurrentWeaponActionInfoPlus(int pai)	{ m_PlusActionInfo = pai; }
				
		//-------------------------------------------------------
		// option flag
		//-------------------------------------------------------
		BYTE	HasOption() const					{ return m_fOption; }
		BYTE	IsOptionRangeToDirection() const	{ return m_fOption & FLAG_ACTIONINFO_OPTION_RANGE_TO_DIRECTION; }
		BYTE	IsOptionUseWithBless() const		{ return m_fOption & FLAG_ACTIONINFO_OPTION_USE_WITH_BLESS; }
		void	SetOptionRangeToDirection()			{ m_fOption |= FLAG_ACTIONINFO_OPTION_RANGE_TO_DIRECTION; }
		void	SetOptionUseWithBless()				{ m_fOption |= FLAG_ACTIONINFO_OPTION_USE_WITH_BLESS; }
		

		//-------------------------------------------------------
		// ����� ��� ����
		//-------------------------------------------------------
		// ActionResultID�� ���� �ݵ�� value�� �����ؾ� �ϴ� ��찡 �ִ�.
		//
		//				id						value
		//
		// ACTIONRESULTNODE_ACTIONINFO :	�����ҷ��� Skill ID
		//-------------------------------------------------------
		void	SetActionResult(TYPE_ACTIONRESULTID id, int value=0)	{ m_ActionResultID = id; m_ActionResultValue = value; }		
		TYPE_ACTIONRESULTID		GetActionResultID() const				{ return m_ActionResultID; }
		int		GetActionResultValue() const							{ return m_ActionResultValue; }

		//-------------------------------------------------------
		// EffectStatus
		//-------------------------------------------------------
		void			SetEffectStatus(EFFECTSTATUS effectStatus)		{ m_EffectStatus = effectStatus; }
		EFFECTSTATUS	GetEffectStatus() const							{ return m_EffectStatus; }

		//-------------------------------------------------------
		// �ݺ� action
		//-------------------------------------------------------
		int				IsUseRepeatFrame() const							{ return m_bUseRepeatFrame; }
		void			UseRepeatFrame()									{ m_bUseRepeatFrame = true; }
		void			SetRepeatFrame(int speed, int start, int frames)			{ m_RepeatStartFrame[speed] = start; m_RepeatEndFrame[speed] = start+frames-1; }
		int				GetRepeatStartFrame(int speed) const						{ return m_RepeatStartFrame[speed]; }
		int				GetRepeatEndFrame(int speed) const						{ return m_RepeatEndFrame[speed]; }

		void			SetRepeatLimit(WORD limit)							{ m_RepeatLimit = limit; }
		WORD			GetRepeatLimit() const								{ return m_RepeatLimit; }
		
		//-------------------------------------------------------
		// �� ���� ���..
		//-------------------------------------------------------
		void			SetChildMode();
		
		//-------------------------------------------------------
		// SelectCreature- ����� ���� ���
		//-------------------------------------------------------
		void		SetSelectCreatureAll()				{ m_fSelectCreature = FLAG_ACTIONINFO_SELECT_ALL; }
		void		SetSelectCreature(BYTE fSelect)		{ m_fSelectCreature = fSelect; }
		BYTE		GetActionTarget() const				{ return m_fSelectCreature; }

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

		//-------------------------------------------------------
		// Grade 
		//-------------------------------------------------------
		void		SetUseActionGrade() {	m_bUseGrade = true; }
		void		UnsetUseActionGrade() { m_bUseGrade = false; }
		bool		IsUseActionGrade() { return m_bUseGrade; }

		//-------------------------------------------------------
		// ActionStep
		//-------------------------------------------------------
		void		SetUseActionStep()	{ m_bUseActionStep = true; }
		void		SetActionStep(BYTE step,  TYPE_ACTIONINFO action);
		bool		IsUseActionStep() { return m_bUseActionStep; }
		TYPE_ACTIONINFO	GetActionStep(BYTE step);

		void		SetParentActionInfo( TYPE_ACTIONINFO Parent );
		TYPE_ACTIONINFO	GetParentActionInfo();

		//-------------------------------------------------------
		// ForceSelectEffectTarget
		//-------------------------------------------------------
		void		SetAttachSelf()	{ m_bAttachSelf = true; }
		bool		IsAttachSelf() { return m_bAttachSelf; }

		//-------------------------------------------------------
		// MasterySkill
		//-------------------------------------------------------
		void		SetMasterySkillStep(BYTE step = 3)	{ m_MasterySkillStep = step; }
		bool		IsMasterySkillStep() { return m_MasterySkillStep!=0; }
		BYTE		GetMasterySkillStep() { return m_MasterySkillStep; }

		bool		IsIgnoreSkillFailDelay() { return m_bIgnoreFailDelay;}
		void		SetSkillFailDelay(bool bflag = true) {	m_bIgnoreFailDelay = bflag;}
	protected :
		MString						m_Name;						// ��� �̸�		
		BYTE						m_Action;					// �������� ����

		bool						m_bUseActionStep;
		TYPE_ACTIONINFO				m_ActionStep[MAX_ACTION_STEP];			// �׼� ����
		TYPE_ACTIONINFO				m_Parent;				

		// casting ����
		TYPE_ACTIONINFO				m_CastingActionInfo;		// ����ҷ��� CastingActionInfo�� ID
		bool						m_bCastingAction;			// �̰Ŵ� casting action�ΰ�?
		TYPE_EFFECTSPRITETYPE		m_ActionEffectSpriteType;	// Casting EffectSpriteType		
		TYPE_EFFECTSPRITETYPE		m_ActionEffectSpriteTypeFemale;	// female�� effect - -;
		int							m_CastingStartFrame[3];		// Casting ���� frame
		int							m_CastingFrames[3];			// casting ���� frame
		int							m_PlusActionInfo;			// �ӽ÷�.. �׷��� ������.. -_-;
		bool						m_bCastingEffectToSelf;		// �ڱ����� casting effect ���δ�.(default) 2001.9.4�߰�
		
		//WORD						m_CastingTime;				// Casting Sprite ǥ�� �ð�
		BYTE						m_Range;					// ��� ���� �Ÿ�		
		BYTE						m_fTarget;					// ��ǥ�� ���� �Ӽ�
		BYTE						m_fStart;					// ���� ��ġ�� ���� �Ӽ�
		BYTE						m_fUserType;				// ���� ��ġ�� ���� �Ӽ�
		WORD						m_fWeaponType;				// ����� ����ϴµ� �ʿ��� ����
		BYTE						m_fCurrentWeapon;			// ���� ��� �ִ� ������ ������ �޴´�.

		ACTIONINFO_PACKET			m_PacketType;				// ������ packet����

		WORD						m_Delay;					// ��� ��� delay�ð�	
		int							m_Value;					// ��
		TYPE_SOUNDID				m_SoundID;					// ��� ��� ������ Sound ID
		int							m_MainNode;					// �⺻�� �Ǵ� ����, �ݺ��Ǵ� ����..��

		BOOL						m_bAttack;					// �����ϴ� ���(��뿡�� ���ظ� ������)�ΰ�?

		
		int							m_StartFrame[3];				// Effect�� �����ϴ� Frame		
		
		TYPE_ACTIONRESULTID			m_ActionResultID;			// ����� ��� ����
		int							m_ActionResultValue;		// ����� ���õ� ��

		BYTE						m_fOption;

		EFFECTSTATUS				m_EffectStatus;			// ��� EffectStatus

		// �ݺ� action�Ҷ� (����~��) frame
		bool						m_bUseRepeatFrame;
		int							m_RepeatStartFrame[3];
		int							m_RepeatEndFrame[3];
		WORD						m_RepeatLimit;			// �ݺ�ȸ�� ����

		// ����� ���� ���
		BYTE						m_fSelectCreature;
		bool						m_bUseGrade;		
		bool						m_bAttachSelf;
		
		BYTE						m_MasterySkillStep;
		bool						m_bIgnoreFailDelay; //  ��ų �����ص� �����̴� ���´�.
		
		// ���� ���� 
		bool						m_bAdvancementClassSkill;		// ������������ ��밡���� ��ų�ΰ�?
		bool						m_bNonAdvancementClassSkill;	// ���� ���� �ʾ��� ���� ��밡���� ��ų�ΰ�?		
};

//----------------------------------------------------------------------
// ACTION_INFO�� array
//----------------------------------------------------------------------
class MActionInfoTable : public CTypeTable<MActionInfo> {
	public :
		MActionInfoTable();
		~MActionInfoTable();

		//---------------------------------------------
		// Set/Get Min Result ActionInfo
		//---------------------------------------------
		void	SetMinResultActionInfo(DWORD nActionInfo)	{ m_nMinResultActionInfo = nActionInfo; }
		DWORD	GetMinResultActionInfo() const				{ return m_nMinResultActionInfo; }

		//---------------------------------------------
		// Set/Get Max Result ActionInfo (���ԵǴ� ���̴�)
		//---------------------------------------------
		void	SetMaxResultActionInfo(DWORD nActionInfo)	{ m_nMaxResultActionInfo = nActionInfo; }
		DWORD	GetMaxResultActionInfo() const				{ return m_nMaxResultActionInfo; }

		void	SetMinStepActionInfo(DWORD nActionInfo) {m_nMinStepActionInfo = nActionInfo; }
		DWORD	GetMinStepActionInfo()	const				{ return m_nMinResultActionInfo; }

		bool	IsResultActionInfo(TYPE_ACTIONINFO type);
		bool	IsActionInfo(TYPE_ACTIONINFO type);

		TYPE_ACTIONINFO	GetResultActionInfo(TYPE_ACTIONINFO action);

		//-------------------------------------------------------
		// �� ���� ���..
		//-------------------------------------------------------
		void			SetChildMode();

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void		SaveToFile(class ofstream& file);
		void		LoadFromFile(class ifstream& file);

	protected :
		// ActionInfo / ResultActionInfo / ClientOnlyActionInfo�� ��谪
		DWORD			m_nMinResultActionInfo;
		DWORD			m_nMaxResultActionInfo;		// ���԰�
		DWORD			m_nMinStepActionInfo;
};


extern	MActionInfoTable*			g_pActionInfoTable;


#endif
