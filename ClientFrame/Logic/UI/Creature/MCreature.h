//----------------------------------------------------------------------
// MCreature.h
//----------------------------------------------------------------------
// �����̴� ������ ���� class
//----------------------------------------------------------------------
// UndergroundCreature
// GroundCreature
// FlyingCreature �� ���еȴ�.
//
// ��� Z��ǥ�� ���� ������, 
// FlyingCreature���� ������ ���̿� �����ϰ� �ȴ�.
//----------------------------------------------------------------------

#ifndef	__MCREATURE_H__
#define	__MCREATURE_H__

#include "MTypeDef.h"
#include "MObject.h"
#include "MAttachEffect.h"
#include "MActionInfoTable.h"
#include "MCreatureTable.h"
#include "MCreatureSpriteTable.h"
#include "MEffectStatusTable.h"
#include "MStatus.h"
#include "RaceType.h"
#include "MemoryPool.h"
#include "NicknameInfo.h"
class MItem;

//----------------------------------------------------------------------
// define
//----------------------------------------------------------------------
#define	MAX_FRAME_MOVE	16

// ���� ĳ������ ����(����)
//#define	FLYINGCREATURE_HEIGHT	0	//64

class MZone;
class MActionFrameArray;
class MActionResult;

class MCreature : public MObject, public MStatus {
	//--------------------------------------------------------------
	// enum
	//--------------------------------------------------------------
	public :
		enum CLASS_TYPE
		{
			CLASS_CREATURE,
			CLASS_CREATUREWEAR,
			CLASS_NPC,
			CLASS_FAKE,
			CLASS_PLAYER
		};

		// Creature�� ���� : ����,����,����
		enum MOVE_TYPE
		{
			CREATURE_UNDERGROUND = 0,
			CREATURE_GROUND,
			CREATURE_FLYING,
			CREATURE_FAKE_NO_BLOCK,		// sector�� �������� �ʴ� �ִ�..
			CREATURE_FAKE_UNDERGROUND,
			CREATURE_FAKE_GROUND,
			CREATURE_FAKE_FLYING,
		};

		// �̵��ϴ� ���
		enum MOVE_DEVICE
		{
			MOVE_DEVICE_WALK,		// �ɾ�ٴѴ�.
			MOVE_DEVICE_RIDE,		// ���ͽ���Ŭ			
			MOVE_DEVICE_SUMMON_SYLPH,		// ����Ÿ�� ��~ 
			MOVE_DEVICE_MAX
		};

		// �̵��ϴ� ���
		enum WEAPON_SPEED
		{
			WEAPON_SPEED_SLOW,			// ���� ����
			WEAPON_SPEED_NORMAL,			// ���� ����
			WEAPON_SPEED_FAST				// ���� ����
		};

	public :
		//----------------------------------------------------------------------
		// MoveNode
		//----------------------------------------------------------------------
		// (x,y)���� direction�������� �����δٴ� �ǹ�
		class MoveNode {
			public :
				int		x;
				int		y;
				int		direction;
		};

		typedef	std::list<MoveNode*>	MOVENODE_LIST;

		//----------------------------------------------------------------------
		// HPModifyList
		//----------------------------------------------------------------------
		class HPModify {
			public :
				HPModify(int value_modify, DWORD value_TickCount) { modify = value_modify; TickCount = value_TickCount; }
				int		modify;
				DWORD	TickCount;
		};

		typedef	std::list<HPModify>	HPMODIFYLIST;

	public :
		MCreature();//MActionFrameArray* pFrames);
		virtual ~MCreature();
		
		void* operator new( size_t size )
		{
			return g_CreatureMemoryPool.Alloc();
		}

		void  operator delete( void *pmem )
		{
			g_CreatureMemoryPool.Free( pmem );
		}

		virtual CLASS_TYPE	GetClassType() const	{ return CLASS_CREATURE; }

		//------------------------------------------------------
		// Init
		//------------------------------------------------------
		static void	InitMoveTable();
		static void	ReleaseMoveTable();

		//------------------------------------------------------
		// (x,y)���� direction���� ������ ��ǥ�� �Ѱ��ش�.
		//------------------------------------------------------
		static void	GetPositionToDirection(TYPE_SECTORPOSITION &x, TYPE_SECTORPOSITION &y, BYTE direction);

		int				GetHeadSkin() const;
		//-------------------------------------------------------
		// Creature Type
		//-------------------------------------------------------
		virtual void	SetCreatureType(TYPE_CREATURETYPE type);		
		TYPE_CREATURETYPE	GetCreatureType() const				{ return m_CreatureType; }

		CREATURETRIBE	GetCreatureTribe() const				{ return (*g_pCreatureTable)[m_CreatureType].GetCreatureTribe(); }
		bool			IsPlayer() const		{ return (*g_pCreatureSpriteTable)[(*g_pCreatureTable)[m_CreatureType].SpriteTypes[m_current_sprite_index]].IsPlayerSprite() != false; }
		bool			IsPlayerOnly() const	{ return (*g_pCreatureSpriteTable)[(*g_pCreatureTable)[m_CreatureType].SpriteTypes[m_current_sprite_index]].IsPlayerOnlySprite() != false; }
		bool			IsSlayer() const		{ return (*g_pCreatureTable)[m_CreatureType].IsSlayer(); }
		bool			IsVampire() const		{ return (*g_pCreatureTable)[m_CreatureType].IsVampire(); }
		bool			IsOusters() const		{ return (*g_pCreatureTable)[m_CreatureType].IsOusters(); }
		bool			IsNPC() const			{ return (*g_pCreatureTable)[m_CreatureType].IsNPC(); }
		int				GetActionMax() const;	
		bool			IsSlayerCharacter() const;
		Race			GetRace() const			{ if(IsSlayer())return RACE_SLAYER; else if(IsVampire())return RACE_VAMPIRE; return RACE_OUSTERS; }

		// 2004, 12, 7, sobeit add start - ��� ���� �ƴ���
		bool			IsSlayerOperator() const { return m_CreatureType == CREATURETYPE_SLAYER_OPERATOR ;}
		bool			IsVampireOperator() const { return m_CreatureType == CREATURETYPE_VAMPIRE_OPERATOR ;}
		bool			IsOustersOperator() const { return m_CreatureType == CREATURETYPE_OUSTERS_OPERATOR ;}
		bool			IsOperator() const { return (	m_CreatureType == CREATURETYPE_SLAYER_OPERATOR
													||	m_CreatureType == CREATURETYPE_VAMPIRE_OPERATOR
													||	m_CreatureType == CREATURETYPE_OUSTERS_OPERATOR);}
		// 2004, 12, 7, sobeit add end
		//------------------------------------------------------
		// IndexSet�� �����ش�.
		//------------------------------------------------------
		int			GetCreatureColorSet() const	{ return (*g_pCreatureTable)[m_CreatureType].ColorSet; }
		
		//------------------------------------------------------
		// Set Same Body
		//------------------------------------------------------
		void		SetSameBody(const MCreature* pCreature);

		//------------------------------------------------------
		// ���� ����... 
		//------------------------------------------------------
		void		SetBodyColor1(WORD set);
		void		SetBodyColor2(WORD set);
		void		SetChangeColorSet(WORD set)	{ m_ChangeColorSet = set; }
		WORD		GetBodyColor1() const		{ return m_ColorBody1; }
		WORD		GetBodyColor2() const		{ return m_ColorBody2; }		
		WORD		GetChangeColorSet() const	{ return m_ChangeColorSet; }
		void		SetBatColor(WORD set)		{ m_BatColorSet = set; }
		WORD		GetBatColor() const			{ return m_BatColorSet; }
		// 2005, 2, 21, sobeit add start
		void		SetMasterEffectType(BYTE bType)		{ m_MasterEffectType = bType; }
		BYTE		GetMasterEffectType() const			{ return m_MasterEffectType; }
		// 2005, 2, 21, sobeit add end
		//------------------------------------------------------
		// Move Type
		//------------------------------------------------------
		MOVE_TYPE	GetMoveType() const				{ return m_MoveType; }
		void	SetMoveType(MOVE_TYPE moveType)		{ m_MoveType = moveType; }
		void	SetUndergroundCreature();
		void	SetGroundCreature();
		void	SetFlyingCreature();
		void	SetFakeCreature()				{ m_MoveType = CREATURE_FAKE_NO_BLOCK; m_Z=(*g_pCreatureTable)[m_CreatureType].FlyingHeight; }
		bool	IsUndergroundCreature()	const	{ return m_MoveType == CREATURE_UNDERGROUND || m_MoveType == CREATURE_FAKE_UNDERGROUND; }
		bool	IsGroundCreature()	const		{ return m_MoveType == CREATURE_GROUND || m_MoveType == CREATURE_FAKE_GROUND; }
		bool	IsFlyingCreature()	const		{ return m_MoveType == CREATURE_FLYING || m_MoveType == CREATURE_FAKE_FLYING; }
		bool	IsFakeCreature()	const		{ return m_MoveType == CREATURE_FAKE_NO_BLOCK || m_MoveType == CREATURE_FAKE_UNDERGROUND || m_MoveType == CREATURE_FAKE_GROUND || m_MoveType == CREATURE_FAKE_FLYING; }

		//------------------------------------------------------
		// ����
		//------------------------------------------------------
		//bool	IsMale() const					{ return (*g_pCreatureTable)[m_CreatureType].bMale; }
		//bool	IsFemale() const				{ return !(*g_pCreatureTable)[m_CreatureType].bMale; }
		void	SetMale(bool bMale=true)		{ m_bMale = bMale; }
		void	SetFemale()						{ m_bMale = false; }
		bool	IsMale() const					{ return m_bMale; }
		bool	IsFemale() const				{ return !m_bMale; }

		//------------------------------------------------------
		// Ű 
		//------------------------------------------------------
		int		GetHeight() const				{ if (m_bAlive) return (*g_pCreatureTable)[m_CreatureType].Height; return (*g_pCreatureTable)[m_CreatureType].DeadHeight; }
		
		//------------------------------------------------------
		// �̵��ϴ� ���
		//------------------------------------------------------	
		void		SetMoveDevice(MOVE_DEVICE md);
		MOVE_DEVICE	GetMoveDevice()	const			{ return m_MoveDevice; }

		//------------------------------------------------------
		// �����̱� 
		//------------------------------------------------------		
		virtual void	Action();			// ���� �ൿ�� ���ϵ��� �Ѵ�.
		virtual BOOL	IsStop();
		virtual void	SetStop();

		//------------------------------------------------------		
		// Buffering�� ������ �̵� ������ �����´�.
		//------------------------------------------------------		
		virtual bool	AffectMoveBuffer();		
		virtual void	AffectMoveBufferAll();		
		void			ReleaseMoveBuffer();

		//----------------------------------------------------------
		// ���� �� �ٲٱ�
		//----------------------------------------------------------
		virtual void	SetStatus(DWORD n, DWORD value);

		//----------------------------------------------------------
		// ����
		//----------------------------------------------------------
		virtual bool	ChangeToSlayer();
		virtual bool	ChangeToVampire();

		//----------------------------------------------------------
		// item��� ���� ���� üũ
		//----------------------------------------------------------
		virtual void	CheckAffectStatus(MItem* pItem);	// Ư�� ������

		//------------------------------------------------------
		//	set
		//-------------------------------------x-----------------
		void	SetName(const char* pName);
		bool	MovePosition(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);	// Zone�� Sector������ �̵��Ѵ�.
		void	SetZone(MZone* pZone)		{ m_pZone = pZone; }
		void	SetPosition(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);
		void	SetDirection(BYTE d)		{ m_Direction = d; }
		void	SetCurrentDirection(BYTE d)		{ m_CurrentDirection = d; }
		void	SetDirectionToPosition(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);		
		virtual void	SetAction(BYTE action);
		//void	SetFrame(BYTE f)			{ m_ActionCount = f; }
		//void	SetZ(short z)				{ m_Z = z; }	
		
		//----------------------------------------------------------
		// ���� ����
		//----------------------------------------------------------
		bool	ChangeNearDirection();	// CurrentDirection�� Direction���� �ڿ������� �ٲ۴�.

		//----------------------------------------------------------
		// Server
		//----------------------------------------------------------
		virtual void		SetServerPosition(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);

		// ������ �� �ൿ ����.. 
		virtual void	SetNextAction(BYTE action);				
		virtual void	SetNextActionToMove();


		//------------------------------------------------------
		// get
		//------------------------------------------------------		
		const char*	GetName() const				{ return m_pName; }
		int	GetCX()	const				{ return m_cX; }	// �ѹ��� �̵��ϴ� pixel x
		int	GetCY()	const				{ return m_cY; }	// �ѹ��� �̵��ϴ� pixel y
		int	GetSX()	const				{ return m_sX; }	// sector���� ������ X��
		int	GetSY()	const				{ return m_sY; }	// sector���� ������ Y��
		TYPE_SECTORPOSITION	GetServerX() const	{ return m_ServerX; }
		TYPE_SECTORPOSITION	GetServerY() const	{ return m_ServerY; }
		BYTE		GetAction()	const			{ return m_Action; }
		BYTE		GetNextAction()	const		{ return m_NextAction; }
		BYTE		GetDirection()	const		{ return m_CurrentDirection; }
		BYTE		GetServerDirection()	const		{ return m_Direction; }
		short		GetZ() const				{ return m_Z; }
		BYTE		GetActionCount() const		{ return m_ActionCount; }
		BYTE		GetActionCountMax() const;//{ return m_ActionCountMax; }
		BYTE		GetMoveCount() const		{ return m_MoveCount; }
		BYTE		GetMoveCountMax() const		{ return m_MoveCountMax; }
		BYTE		GetFrame() const			
		{ 
			// Ư���� action�� ���� �����̰� �ִ� ���
			if (m_ActionCount>=GetActionCountMax())
			{
				// �� �������� �����ϰ� �ִ� ����...action�� ������� �Ѵ�.
				return (m_MoveCount<m_MoveCountMax)?m_MoveCount:
						(m_ActionCount==0)? 0 : GetActionCountMax()-1; 
			}
			// action�� ǥ�����ִ� ���
			else
			{
				return (m_ActionCount<GetActionCountMax())?m_ActionCount:GetActionCountMax()-1; 				
			}
		}

		// nActionInfo�� ������ action�� ã�´�.
		int			GetActionInfoAction(TYPE_ACTIONINFO nActionInfo, bool IsSelfAction = false);
		int			GetActionInfoCastingStartFrame(TYPE_ACTIONINFO nActionInfo);
		int			GetActionInfoCastingFrames(TYPE_ACTIONINFO nActionInfo);
		int			GetActionInfoDelay(TYPE_ACTIONINFO nActionInfo);
		int			GetActionInfoActionEffectSpriteType(TYPE_ACTIONINFO nActionInfo);
		int			GetActionInfoRepeatStartFrame(TYPE_ACTIONINFO nActionInfo);
		int			GetActionInfoRepeatEndFrame(TYPE_ACTIONINFO nActionInfo);
		

		// nActionInfo�� ������ casting sound�� ã�´�.
		TYPE_SOUNDID	GetCastingSoundID(TYPE_ACTIONINFO nActionInfo);

		void		GetNextPosition(BYTE direction, POINT &next);
		//void		GetNextPosition(POINT &next);
		void		GetNextPosition(TYPE_SECTORPOSITION &sX, TYPE_SECTORPOSITION &sY);
		int			GetCounterDirection( int d );
		
		// LightSight�� MaxEffectLight �߿��� ū ���� �Ѱ��ش�. (������ ���� ū �þ�)
		//char		GetMaxLightSight() const			{ return (m_MaxEffectLight > m_LightSight)? m_MaxEffectLight : m_LightSight; }
		BYTE		GetDirectionToPosition(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);

		// Pixel��ǥ
		int			GetPixelX() const;
		int			GetPixelY() const;

		// item count
		int			GetItemCount() const	{ return m_ItemCount; }
		void		SetItemCount(int c)		{ m_ItemCount = c; }

		// ( ���ID, Effect DelayFrame )
		TYPE_ACTIONINFO	GetDelayActionInfo() const		{ return m_DelayActionInfo; }
		DWORD			GetEffectDelayFrame() const		{ return m_EffectDelayFrame; }
		void			SetEffectDelayFrame(TYPE_ACTIONINFO ai, DWORD f)	{ m_DelayActionInfo=ai; m_EffectDelayFrame = f; }


		//------------------------------------------------------
		// ĳ���� ����
		//------------------------------------------------------
		TYPE_FRAMEID	GetCreatureFrameID(int index) const	{ return m_CreatureFrameIDs[index]; }
		int				GetCreatureFrameCount()	  const { return m_CreatureFrameIDs.GetSize();}

		BOOL		IsExistBody() const			{ return m_bExistBody; }
		
		//------------------------------------------------------
		// ���
		//------------------------------------------------------
		void				SetBasicActionInfo( TYPE_ACTIONINFO n )		{ m_nBasicActionInfo = n; }
		TYPE_ACTIONINFO		GetBasicActionInfo() const;
		virtual void		SetSpecialActionInfo( TYPE_ACTIONINFO n )	{ m_nSpecialActionInfo = n; }
		void				SetSpecialActionInfoNULL()					{ m_nSpecialActionInfo = ACTIONINFO_NULL; }
		TYPE_ACTIONINFO		GetSpecialActionInfo() const				{ return m_nSpecialActionInfo; }		
		TYPE_ACTIONINFO		GetUsedActionInfo() const					{ return m_nUsedActionInfo; }

		//----------------------------------------------------------
		// ��� ��ǥ��?
		//----------------------------------------------------------
		BOOL	IsSpecialActionInfoTargetSelf()	const	{ return (m_nSpecialActionInfo==ACTIONINFO_NULL)?FALSE : (*g_pActionInfoTable)[m_nSpecialActionInfo].IsTargetSelf(); }	
		BOOL	IsSpecialActionInfoTargetOther() const	{ return (m_nSpecialActionInfo==ACTIONINFO_NULL)?FALSE : (*g_pActionInfoTable)[m_nSpecialActionInfo].IsTargetOther(); }
		BOOL	IsSpecialActionInfoTargetZone() const	{ return (m_nSpecialActionInfo==ACTIONINFO_NULL)?FALSE : (*g_pActionInfoTable)[m_nSpecialActionInfo].IsTargetZone(); }
		BOOL	IsSpecialActionInfoTargetItem() const	{ return (m_nSpecialActionInfo==ACTIONINFO_NULL)?FALSE : (*g_pActionInfoTable)[m_nSpecialActionInfo].IsTargetItem(); }		
		

		// ����
		virtual BOOL		IsWear() const					{ return FALSE; }

		//------------------------------------------------------
		// Chatting String
		//------------------------------------------------------
		void		SetChatString(char *str, COLORREF color = RGB(255, 255, 255));
		void		SetPersnalString(char *str, COLORREF color = RGB(255, 255, 255));
		const char*	GetChatString(BYTE i);
		void		ClearChatString();
		void		FadeChatString();
		COLORREF	GetChatColor()		{ return m_ChatColor; }
		COLORREF	GetOriChatColor()	{ return m_OriChatColor; }
		DWORD		GetChatTime() const	{ return m_ChatTime; }

		//------------------------------------------------
		//
		// Effect ����...
		//
		// AttachEffect�� ĳ���� ���� �پ��ִ� effect�� �ǹ��Ѵ�.
		// GroundAttachEffect�� ĳ������ �� �ؿ� �پ��ִ� effect�� �ǹ��Ѵ�.
		// �ٵ�, AttachEffect�� GroundAttachEffect�� �����ϴ� �ǹ��̱⵵ �Ѵ�.
		// (������ ��ȹ�� ���� �����̶� �߰��ϸ鼭 ���� �� ������ �ڵ� ���� �ϳ��̴�. 1818!)
		//
		//------------------------------------------------
		bool		IsExistAttachEffect() const		{ return !m_listEffect.empty(); }
		bool		IsExistGroundAttachEffect() const		{ return !m_listGroundEffect.empty(); }
		int			GetAttachEffectSize() const		{ return m_listEffect.size(); }
		int			GetGroundAttachEffectSize() const		{ return m_listGroundEffect.size(); }
		void		ClearAttachEffect();
		

		// �������� �پ��ִ� Effect�� ǥ���ϴ� ���� �߿��� --> ���� ����ҷ��� ��
		WORD		GetAttachEffectColor() const	{ return m_AttachEffectColor; }

		// AttachEffect�� �þ� �߰�/����
		//void		SetLightSightAttachEffect();
		//void		UnSetLightSightAttachEffect();

		// �ܺο��� iterator�� �۾��� �� �� �ֵ���..
		ATTACHEFFECT_LIST::const_iterator GetAttachEffectIterator() const { return m_listEffect.begin(); }
		ATTACHEFFECT_LIST::const_iterator GetGroundAttachEffectIterator() const { return m_listGroundEffect.begin(); }

		// Add/Update
		MAttachEffect*		CreateAttachEffect(TYPE_EFFECTSPRITETYPE type, DWORD delayFrame, DWORD linkDelayFrame, BOOL bGroundEffect=FALSE, MEffect::EFFECT_TYPE eType=MEffect::EFFECT_ATTACH);
		virtual bool		AddEffectStatus(EFFECTSTATUS status, DWORD delayFrame);
		virtual bool		RemoveEffectStatus(EFFECTSTATUS status);		
		bool				HasEffectStatus(EFFECTSTATUS status) const		{ return m_bEffectStatus[status]; }
		bool				IsAvailableEffectStatus() const		{ return m_bEffectStatus != NULL; }

		virtual void		UpdateAttachEffect();

		void				RemoveGlacierEffect();
		void				Remove_Curse_Paralsis_Effect();

		//char		GetMaxEffectLight() const		{ return m_MaxEffectLight; }

		//------------------------------------------------------
		// ����..
		//------------------------------------------------------
		virtual void		SetDead();		// �״� ��� �����ش�.
		virtual void		SetAlive();		// ��Ƴ���.
		virtual void		SetCorpse();	// �׾��ִ� ��ü ����
		virtual bool		IsDead() const		{ return !m_bAlive; }
		virtual bool		IsAlive() const		{ return m_bAlive; }		
		
		//------------------------------------------------------
		// Invisible
		//------------------------------------------------------
		int					IsInvisible() const			{ return m_InvisibleCount; }
		void				SetInvisible();
		void				SetInvisibleSoon();	// ��� invisible�� �����.
		void				SetVisible();
		void				SetVisibleSoon();
		int					GetInvisibleCount() const	{ return m_InvisibleCount; }
		void				UpdateInvisible();

		//------------------------------------------------------
		// Level Name
		//------------------------------------------------------
		void				SetLevelName(int ln);
		BOOL				HasLevelName() const		{ return m_LevelName; }
		const char*			GetLevelName() const;

		//------------------------------------------------------
		// Guild
		//------------------------------------------------------
		void				SetGuildNumber(int gn)		{ m_GuildNumber = gn; }
		int					GetGuildNumber() const		{ return m_GuildNumber; }		
		
		void				SetUnionGuildID(int gn)		{ m_nUnionGuildID = gn; }
		int					GetUnionGuildID() const		{ return m_nUnionGuildID; }		

		//------------------------------------------------------
		// Weapon Speed
		//------------------------------------------------------
		WEAPON_SPEED		GetWeaponSpeed() const			{ return m_WeaponSpeed; }
		void				SetWeaponSpeed(int speed);
		void				SetWeaponSpeed(WEAPON_SPEED ws)	{ m_WeaponSpeed = ws; }

		//------------------------------------------------------
		// Head
		//------------------------------------------------------
		bool				CanRemoveHead() const			{ return (*g_pCreatureTable)[m_CreatureType].bHeadCut; }
		void				RemoveHead()					{ if (CanRemoveHead()) m_bHasHead = false; }
		bool				HasHead() const					{ return m_bHasHead; }

		//------------------------------------------------------
		// HP ȸ��
		//------------------------------------------------------
		// rate��ŭ times�� ȸ���ȴ�.
		inline BOOL			IsRecoveryHP();
		inline BOOL			IsRecoveryMP();
		void				SetRecoveryHP(int amount, int times, DWORD delay);
		void				SetRecoveryMP(int amount, int times, DWORD delay);
		void				StopRecoveryHP()	{ m_RecoveryHPTimes = 0; }
		void				StopRecoveryMP()	{ m_RecoveryMPTimes = 0; }
		DWORD				GetRecoveryHPDelayTime() const		{ return m_RecoveryHPDelayTime; }
		int					GetRecoveryHPTimes() const			{ return m_RecoveryHPTimes; }
		int					GetRecoveryHPAmmount() const		{ return m_RecoveryHPAmount; }
		DWORD				GetRecoveryMPDelayTime() const		{ return m_RecoveryMPDelayTime; }
		int					GetRecoveryMPTimes() const			{ return m_RecoveryMPTimes; }
		int					GetRecoveryMPAmmount() const		{ return m_RecoveryMPAmount; }

		void				SetRegen(int amount, DWORD delay);
		void				SetRegenBonus(int amount, DWORD delay);			
		void				CheckRegen();

		void				UpdateStatus();

		//------------------------------------------------------
		// �� �긮��
		//------------------------------------------------------
		virtual void		CheckDropBlood();

		//------------------------------------------------------
		// ȭ�鿡 ǥ���ϴ� HP bar�� ����
		//------------------------------------------------------
		int					GetHPBarWidth()	const				{ return (*g_pCreatureTable)[m_CreatureType].HPBarWidth; }

		//------------------------------------------------------
		// Fade
		//------------------------------------------------------
		// �� ��ü�� ��Ӱ� ǥ���Ǵ� ���
		bool				IsFade() const						{ return m_bFade; }
		void				SetFade() 							{ m_bFade = true; }
		void				UnSetFade()							{ m_bFade = false; }

		// ĳ���� ������ ������ �׸��� ��� ����.. - -;
		int					GetShadowCount() const				{ return m_ShadowCount; }
		void				SetShadowCount(int n);

		//------------------------------------------------------
		// ��..
		//------------------------------------------------------
		virtual int			FindEnemy();

		//------------------------------------------------------
		//
		//              Server Packet ó��
		//
		//------------------------------------------------------
		virtual void		PacketSpecialActionResult(TYPE_ACTIONINFO nResultActionInfo, TYPE_OBJECTID id, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, BYTE temp = 0);
		virtual void		PacketAttackNormal(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y, BYTE direction);
		virtual void		PacketMove(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y, BYTE direction);		
		virtual void		PacketSpecialActionToSector(TYPE_ACTIONINFO nActionInfo, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, MActionResult* pActionResult);
		virtual void		PacketSpecialActionToOther(TYPE_ACTIONINFO nActionInfo, TYPE_OBJECTID id, MActionResult* pActionResult);
		virtual void		PacketSpecialActionToNobody(TYPE_ACTIONINFO nActionInfo, TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);	// ��밡 zone�� ���� ���
		virtual void		PacketSpecialActionToSelf(TYPE_ACTIONINFO nActionInfo, MActionResult* pActionResult);
		virtual void		PacketSpecialActionToInventoryItem(TYPE_ACTIONINFO nActionInfo);
		
	
		//------------------------------------------------------
		// Fast Move
		//------------------------------------------------------
		bool				IsFastMove() const	{ return m_bFastMove; }
		virtual bool		FastMovePosition(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y,bool server = false);	// Zone�� Sector������ ����(-_-;) �̵��Ѵ�.
		void				StopFastMove();

		//------------------------------------------------------
		// Knock Back
		//------------------------------------------------------
		int					IsKnockBack() const			{ return m_bKnockBack>0; }
		virtual bool		KnockBackPosition(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, BYTE Action = 0);
		void				StopKnockBack()			{ m_bKnockBack = 0; }
		
		//------------------------------------------------------
		// Casket
		//------------------------------------------------------
		bool				IsInCasket() const			{ return m_bInCasket; }
		int					GetCasketCount() const		{ return m_CasketCount; }
		int					GetCasketType() const		{ return m_CasketType; }
		void				AddCasket(int casketType);
		void				RemoveCasket();
		void				AddCasketSoon(int casketType);
		void				RemoveCasketSoon();
		void				UpdateCasket();		

		//--------------------------------------------------
		// CutHeight
		//--------------------------------------------------
		bool				IsCutHeight() const			{ return m_bCutHeight; }
		int					GetCutHeightCount() const	{ return m_CutHeightCount; }
		void				SetCutHeightFrom(int startCount, int lastCount, int inc);
		void				UpdateCutHeight();

		//--------------------------------------------------
		// Turning
		//--------------------------------------------------
		bool				IsTurning() const			{ return m_bTurning; }
		int					GetTurningCount() const		{ return m_TurningCount; }
		void				SetTurning(WORD count)		{ m_bTurning = true; m_TurningCount = count; }
		void				StopTurning()				{ m_bTurning = false; }
		void				UpdateTurning();
		
		//--------------------------------------------------
		// CauseCriticalWounds
		//--------------------------------------------------
		bool				IsCauseCriticalWounds() const			{ return m_bCauseCriticalWounds; }
		void				SetCauseCriticalWounds(int delay)		{ m_bCauseCriticalWounds = true; m_CauseCriticalWoundsCount = delay; }
		void				StopCauseCriticalWounds()				{ m_bCauseCriticalWounds = false; }
		void				UpdateCauseCriticalWounds();

		//--------------------------------------------------
		// BloodyZenith
		//--------------------------------------------------
		bool				IsBloodyZenith();
		void				SetBloodyZenith(int delay)		{ m_bBloodyZenith = true; m_BloodyZenithCount = delay; }
		void				StopBloodyZenith()				{ m_bBloodyZenith = false; }
		int					GetBloodyZenithCount();
		void				UpdateBloodyZenith();
		
		//--------------------------------------------------
		// GunShotGuidance
		//--------------------------------------------------
		bool				IsGunShotGuidance() const			{ return m_bGunShotGuidance; }
		void				SetGunShotGuidance(int delay)		{ m_bGunShotGuidance = true; m_GunShotGuidanceCount = delay; }
		void				StopGunShotGuidance()				{ m_bGunShotGuidance = false; }
		void				UpdateGunShotGuidance();

		//--------------------------------------------------
		// BurningSolCount
		//--------------------------------------------------
		bool				IsBurningSol() const			{ return m_bBurningSol; }
		void				SetBurningSol(int delay)		{ m_bBurningSol = true; m_bBurningSolCount = delay; }
		void				StopBurningSol()				{ m_bBurningSol = false; }
		bool				UpdateBurningSol();

		//--------------------------------------------------
		// InstallTurret
		//--------------------------------------------------
		BYTE				GetInstallTurretCount() const			{ return m_bInstallTurretCount; }
		void				SetInstallTurretCount(int Count)		{ m_bInstallTurretCount = Count; }
		BYTE				GetInstallTurretDirect() const			{ return m_bInstallTurretDirect; }
		void				SetInstallTurretDirect(int Count)		{ m_bInstallTurretDirect = Count; }
		bool				UpDateInstallTurret();
		void				InstallTurretStopAttack();


		//--------------------------------------------------
		// Armageddon
		//--------------------------------------------------
		bool				IsArmageddon() const			{ return m_bArmageddon; }
		void				SetArmageddon(int delay)		{ m_bArmageddon = true; m_ArmageddonCount = delay; }
		const int			GetArmageddon() const			{ if(IsArmageddon())return m_ArmageddonCount; return -1; }
		void				StopArmageddon()				{ m_bArmageddon = false; }
		void				UpdateArmageddon();

		//--------------------------------------------------
		// Teleport
		//--------------------------------------------------
		bool				IsGhost(BYTE flag) const			{ return (m_fGhost&flag)?true:false; }
		void				SetGhost(BYTE flag, int delay)		{ m_fGhost = flag; m_GhostCount = delay; }
		const int			GetGhost() const			{ if(IsGhost(0xFF))return m_GhostCount; return -1; }
		void				StopGhost()				{ m_fGhost = 0; }
		void				UpdateGhost();
		
		//--------------------------------------------------
		// FakeDie
		//--------------------------------------------------
		bool				IsFakeDie() const			{ return m_bFakeDie; }
		void				SetFakeDie();
		int					GetFakeDieCount()			{ return m_FakeDieCount; }
		void				StopFakeDie()				{ m_bFakeDie = false; }
		void				UpdateFakeDie();

		//----------------------------------------------------------
		// player�� Darkness�ȿ� �ִ°�?
		// DarknessCount�� ��Ÿ���� ���̴°�?�̴�.
		//----------------------------------------------------------
		BOOL				IsInDarkness() const		{ return m_DarknessCount>=0; }
		BOOL				ShowInDarkness(int sX, int sY) const;
		int					GetDarknessCount() const	{ return m_DarknessCount; }
		void				UpdateDarkness();
		virtual void		CheckInDarkness();
		void				PlaceInDarkness(bool IsBlindness = false); // 2004, 6, 24 sobeit modify - blindness ó�� ����
		void				PlaceNotInDarkness();

		BOOL				IsInGroundElemental() const;
		//--------------------------------------------------
		// ���� delay�� ���ֱ� ���ؼ� �ӽ÷�..
		//--------------------------------------------------
		void				SetStopBloodDrain()			{ m_bStopBloodDrain++; }
		void				UnSetStopBloodDrain()		{ if (m_bStopBloodDrain>0) m_bStopBloodDrain--; }
		void				ClearStopBloodDrain()		{ m_bStopBloodDrain = 0; }
		virtual void		StopBloodDrain();

		//--------------------------------------------------
		// �� delay�� ���ֱ� ���ؼ� �ӽ÷�..
		//--------------------------------------------------
		void				SetStopAbsorbSoul()			{ m_bStopAbsorbSoul++; }
		void				UnSetStopAbsorbSoul()		{ if (m_bStopAbsorbSoul>0) m_bStopAbsorbSoul--; }
		void				ClearStopAbsorbSoul()		{ m_bStopAbsorbSoul = 0; }
		virtual void		StopAbsorbSoul();
		
		//--------------------------------------------------
		// ��Ƽ üũ
		//--------------------------------------------------
		bool				IsPlayerParty() const		{ return m_bPlayerParty; }
		void				SetPlayerParty()			{ m_bPlayerParty = true; }
		void				UnSetPlayerParty()			{ m_bPlayerParty = false; }

		//--------------------------------------------------
		// Hallucination�ɷ����� ������ ���̱� - -;
		//--------------------------------------------------		
		bool				IsHallu() const				{ return m_bHallu; }
		void				DetermineHalluActionFrame();
		void				SetHalluCreature(TYPE_CREATURETYPE type);
		void				UnSetHalluCreature()		{ m_bHallu = false; }
		TYPE_FRAMEID		GetHalluCreatureFrameID() const	{ return m_HalluCreatureFrameID; }
		TYPE_CREATURETYPE	GetHalluCreatureType() const { return m_HalluCreatureType; }
		WORD				GetHalluColor() const		{ return m_HalluColorBody; }
		BYTE				GetHalluAction() const		{ return m_HalluAction; }
		BYTE				GetHalluFrame() const		{ return m_HalluFrame; }
		const char*			GetHalluName() const;
		

		// ���
		void				SetCompetence(BYTE c)		{ m_Competence = c; }
		BYTE				GetCompetence() const		{ return m_Competence; }

		// ����
		void				SetDrainCreatureID(TYPE_OBJECTID id)	{ m_DrainCreatureID = id; }
		const TYPE_OBJECTID	GetDrainCreatureID() const				{ return m_DrainCreatureID; }
		void				StopDrain();	// ���� �����ϰ� �ִ� Creature�� ���������� �����

		// ��
		void				SetAbsorbCreatureID(TYPE_OBJECTID id)	{ m_DrainCreatureID = id; }
		const TYPE_OBJECTID	GetAbsorbCreatureID() const				{ return m_DrainCreatureID; }
		void				StopAbsorb();	// ���� �����ϰ� �ִ� Creature�� �������� �����
		
		// PET
		void				SetPetID(TYPE_OBJECTID id)				{ m_PetID = id; }
		const TYPE_OBJECTID	GetPetID() const						{ return m_PetID; }
		
		// Elemental
		void				SetElementalID(TYPE_OBJECTID id)				{ m_ElementalID = id; }
		const TYPE_OBJECTID	GetElementalID() const						{ return m_ElementalID; }
		
		//--------------------------------------------------
		// HP Modify����
		//--------------------------------------------------		
		const HPMODIFYLIST *GetHPModifyList() const			{ return &m_HPModifyList; }
		void				AddHPModify(const int modify);
		const bool			IsEmptyHPModifyList() const		{ return m_HPModifyList.empty(); }
		const int			GetHPModifyListSize() const		{ return m_HPModifyList.size(); }

		void			SetActionGrade( BYTE a ) { if( a != 0 ) m_GradeActionInfo = a; }
		void			ClearActionGrade() {m_GradeActionInfo = 0;}
		BYTE			GetActionGrade() { return m_GradeActionInfo; }
		
		virtual	void	SetTraceID( TYPE_OBJECTID id );

		void			SetActionDelay(short time)			{ m_DelayLastAction = time; }
		short			GetActionDelay()		const		{ return m_DelayLastAction; }

		void			SetNickName(BYTE bType, char* szNickName) { m_NickNameType = bType; m_NickName = szNickName;}
		string			GetNickName() { return m_NickName;}
		BYTE			GetNickNameType() { return m_NickNameType;}

		bool			GetIsInSiegeWar() { return (m_bSiegeWar>0)?true:false;}
		void			SetSiegeWar(BYTE bSiege) { m_bSiegeWar = bSiege; }
		bool			GetIsAttackerInSiegeWar() {return (m_bSiegeWar>2&&m_bSiegeWar<8)?true:false;}
		bool			GetIsDefenderInSiegeWar() {return (m_bSiegeWar>0&&m_bSiegeWar<3)?true:false;}
		
		BOOL			IsInFuryOfGnome() const;


		string			GetPersnalShopMessage() {return m_PersnalMessage; }
		void 			SetPersnalShopMessage(const char * str) {m_PersnalMessage = str; }

		void			SetPersnalShop(int curshop) { m_Persnal_flag = curshop; }
		int				CurPernalShop() {return m_Persnal_flag;}

		void			SetInputChatting(bool b_input) {  m_Input_Chat_Flag = b_input ;}
		bool			GetInputChatting() { return  m_Input_Chat_Flag; }

		BYTE			GetPersonalShopMsgTime() const { return m_PersonalShopOpenTime; }
		void			SetPersonalShopMsgTime( BYTE time ) { m_PersonalShopOpenTime = time;	}
		
		bool			IsAdvancementClass() const { return GetAdvancementClassLevel() > 0 && GetAdvancementClassLevel() != MODIFY_NULL; }


		// 2005, 1, 5, sobeit add start
		void		UpdateBikeCrash();
		// 2005, 1, 5, sobeit add end
		void			RemoveCauseCriticalWoundsEffect();

		// 2005, 2, 22, sobeit add start
		int 			GetMasterEffectType(DWORD Status);
		void			ChangeMasterEffectType(int MarketEffect);
		// 2005, 2, 22, sobeit add end
	protected :
		virtual void	ActionMove();
		virtual void	ActionEffect();
	
		virtual void	AffectUsedActionInfo(TYPE_ACTIONINFO nUsedActionInfo);
		virtual void	AttachCastingEffect(TYPE_ACTIONINFO nUsedActionInfo, BOOL bForceAttach=FALSE);

		virtual void	AffectBufferedActionInfo();
	

	protected :
		// Creature�� ����
		TYPE_CREATURETYPE		m_CreatureType;
		//TYPE_FRAMEID			m_CreatureFrameID;
		CTypeTable<TYPE_FRAMEID>			m_CreatureFrameIDs;
		BOOL					m_bExistBody;
		DWORD					m_TraceTimer;				// ���󰡱� ���ѽð�

		//add by viva
		BYTE					m_MoveCount;		// �̵��� ȸ��
		//end

		//--------------------------------------------------
		// ����
		//--------------------------------------------------
		// PC Vampire : 1=�Ǻ�, 2=��		
		// Monster : 1=���� ��򰡿� ���ϴ� ��.. - -; 2=Nothing
		WORD					m_ColorBody1;		
		WORD					m_ColorBody2;	
		WORD					m_ChangeColorSet;	// �� ��ü ������ �ٲ�� ���
		WORD					m_BatColorSet;
		// 2005, 2, 21, sobeit add start
		BYTE					m_MasterEffectType;
		// 2005, 2, 21, sobeit add end
		

		// Move ���� : ����,����,����
		MOVE_TYPE				m_MoveType;
		short					m_Z;			// ���� Z

		// �̵��ϴ� ���
		MOVE_DEVICE				m_MoveDevice;
		BYTE					m_MoveAction;

		MZone*					m_pZone;		// �� Creature�� ���ϴ� Zone


		// ���� ������ ����
		TYPE_SECTORPOSITION		m_NextX;
		TYPE_SECTORPOSITION		m_NextY;
		BYTE					m_NextDirection;

		//--------------------------------------------------
		// Move Buffering
		//--------------------------------------------------
		MOVENODE_LIST			m_listMoveBuffer;
	

		// sector������ smooth scroll�� ���ؼ�		
		int				m_sX, m_sY;		// �̵��ؾ��� ������ pixels
		int				m_cX, m_cY;		// �ѹ��� �̵��ϴ� ���� pixel
		
		// �̵��ϴµ� �ʿ��� ����
		static int		m_sXTable[MAX_DIRECTION];
		static int		m_sYTable[MAX_DIRECTION];
		static int		*m_cXTable[MAX_FRAME_MOVE][MAX_DIRECTION];
		static int		*m_cYTable[MAX_FRAME_MOVE][MAX_DIRECTION];		

		// ���� frame�� ���� ����
		BYTE					m_Action;			// Action�� ���� ID
		//add by viva for no increase speed
		//BYTE					m_CurrentDirection;	// ������ Direction
		//BYTE					m_Direction;		// �ٶ���� �ϴ� Direction
		//BYTE					m_DirectionMove;	// �̵��� ����
		//BYTE					m_DirectionMoved;	// �̵��� ����		
		//BYTE					m_ActionCount;		// ActionCount == Frame
		//BYTE					m_ActionCountMax;	// ActionCountMax
		//BYTE					m_MoveCount;		// �̵��� ȸ��
		//BYTE					m_MoveCountMax;		// �̵��ϴ� ��ǥ ȸ��
		//BYTE					m_MoveTableCount;	// cX,YTable�� count
		//BYTE					m_NextMoveCount;	// ������ �̵��ؾ��ϴ� count��


		//BYTE					m_NextAction;
		//end
		// ��� ����		
		TYPE_ACTIONINFO			m_nBasicActionInfo;		// ���õǾ� �ִ� �⺻ ��� ����				
		TYPE_ACTIONINFO			m_nSpecialActionInfo;	// ���õǾ� �ִ� Ư�� ��� ����
		TYPE_ACTIONINFO			m_nUsedActionInfo;		// ����� ��
		
		// ������ ����ϰԵǴ� ���..
		TYPE_ACTIONINFO			m_nNextUsedActionInfo;

		// �����ϴ� ��ǥ�� ���� ����
		TYPE_OBJECTID			m_TraceID;				// ���󰡴� Object�� ID		
		TYPE_SECTORPOSITION		m_TraceX;				// �����ϴ� ��ǥ ��ġ
		TYPE_SECTORPOSITION		m_TraceY;
		short					m_TraceZ;

		
		// Server���� �ֱٿ� ������ ��ġ
		TYPE_SECTORPOSITION			m_ServerX;	
		TYPE_SECTORPOSITION			m_ServerY;		

		// ĳ���Ϳ� �پ� �ִ� Effect ǥ��
		bool*					m_bAttachEffect;
		bool*					m_bEffectStatus;
		ATTACHEFFECT_LIST		m_listEffect;
		ATTACHEFFECT_LIST		m_listGroundEffect;
		WORD					m_AttachEffectColor;	// ���� ����ҷ��� ĳ���� ���� �ٲٱ� �� -_-;(���� �̻���..����)
		//BYTE					m_nAlphaEffect;		
		//char					m_MaxEffectLight;		// Effect�� �ְ� ���(�þ�)

		// chat
		COLORREF				m_ChatColor;				// ������ ä�� ��
		COLORREF				m_OriChatColor;				// fade�Ǳ� ���� ä�� ��
		DWORD					m_NextChatFadeTime;		// �ֱ��� Chat string�� �Էµ� �ð�
		BYTE					m_ChatStringCurrent;
		char**					m_ChatString;
		DWORD					m_ChatTime;
		BYTE					m_PersonalShopOpenTime;
		
		// ActionInfo�� ���� ���(Server�κ��� ������ ��)
		MActionResult*			m_pActionResult;

		// ĳ���� �̸�
		char*					m_pName;

		// ����ֳ�?
		bool					m_bAlive;		

		// ���� �ൿ�� �ֳ�?
		bool					m_bNextAction;		

		// ������ �ִ� item ���� [ TEST CODE ] - -;;
		int						m_ItemCount;
		//add by viva
		BYTE					m_DirectionMove;	// �̵��� ����
		//end
		// ����� ���� �ð� ����
		TYPE_ACTIONINFO			m_DelayActionInfo;
		DWORD					m_EffectDelayFrame;

		// LevelName
		int						m_LevelName;

		// ���
		int						m_GuildNumber;
		int						m_nUnionGuildID;
		//add by viva
		BYTE					m_Direction;		// �ٶ���� �ϴ� Direction
		//end
		// fast move
		bool					m_bFastMove;

		// repeat count
		int						m_RepeatCount;

		// ���� ���� �ӵ�
		WEAPON_SPEED			m_WeaponSpeed;

		static int				s_SlayerActionSpeed[ACTION_MAX_SLAYER][3];
		static int				s_VampireActionSpeed[ACTION_MAX_SLAYER][3];	//ACTION_MAX_VAMPIRE][3];
		static int				s_OustersActionSpeed[ACTION_MAX_SLAYER][3];	//ACTION_MAX_VAMPIRE][3];

		//--------------------------------------------------
		// �ð��� ���� HP ȸ��
		//--------------------------------------------------
		DWORD					m_RecoveryHPNextTime;
		DWORD					m_RecoveryHPDelayTime;
		int						m_RecoveryHPTimes;
		int						m_RecoveryHPAmount;
		DWORD					m_RecoveryMPNextTime;
		DWORD					m_RecoveryMPDelayTime;
		int						m_RecoveryMPTimes;
		int						m_RecoveryMPAmount;
		//DWORD					m_RecoveryPart;		// hp, mp?
		//add by viva
		BYTE					m_NextAction;
		//end
		// �ڵ� regen - -;
		DWORD					m_RegenDelayTime;
		DWORD					m_RegenNextTime;
		int						m_RegenAmount;
		DWORD					m_RegenBonusDelayTime;
		DWORD					m_RegenBonusNextTime;
		int						m_RegenBonusAmount;
		//add by viva
		BYTE					m_ActionCountMax;	// ActionCountMax
		//end
		//--------------------------------------------------
		// �Ӹ��� �ֳ�?
		//--------------------------------------------------
		bool					m_bHasHead;

		//--------------------------------------------------
		// ��Ӱ� ���
		//--------------------------------------------------
		bool					m_bFade;
		int						m_ShadowCount;
		//add by viva
		BYTE					m_NextMoveCount;	// ������ �̵��ؾ��ϴ� count��
		//end
		//--------------------------------------------------
		// ����
		//--------------------------------------------------
		bool					m_bMale;

		//--------------------------------------------------
		// �� �긮��
		//--------------------------------------------------
		DWORD					m_NextBloodingTime;

		//--------------------------------------------------
		// KnockBack ó��
		//--------------------------------------------------
		int						m_bKnockBack;	// >0�̸� KnockBack��.

		//--------------------------------------------------
		// �̰͵� �� ����� �Ǵµ�...  ������~ --;;
		//--------------------------------------------------
		// ���� �Ǳ�
		//--------------------------------------------------
		int						m_InvisibleCount;	// 0�̸� ������ ���δ�. 64�� ���� ����
		int						m_InvisibleStep;
		
		//--------------------------------------------------
		// ��
		//--------------------------------------------------
		bool					m_bInCasket;
		int						m_CasketCount;
		int						m_CasketCountInc;
		int						m_CasketType;
		//add by viva
		BYTE					m_MoveTableCount;	// cX,YTable�� count
		//end
		//--------------------------------------------------
		// �� �׸��� ����..
		//--------------------------------------------------
		bool					m_bCutHeight;
		int						m_CutHeightCount;
		int						m_CutHeightCountLast;
		int						m_CutHeightCountInc;

		//--------------------------------------------------
		// ���� ����
		//--------------------------------------------------
		bool					m_bTurning;
		int						m_TurningCount;

		//--------------------------------------------------
		// ���� delay�� ���ֱ� ���� �ӽ� ����
		//--------------------------------------------------
		BYTE					m_bStopBloodDrain;
		BYTE					m_bStopAbsorbSoul;

		//----------------------------------------------------
		// CauseCriticalWounds�� ���� ������ ���� ���ϴ� ����
		//----------------------------------------------------
		bool					m_bCauseCriticalWounds; 
		int						m_CauseCriticalWoundsCount; 
		//add by viva
		BYTE					m_ActionCount;		// ActionCount == Frame
		//end
		//----------------------------------------------------
		// Bloody Zenith�� ���� ������ ���� ���ϴ� ����
		//----------------------------------------------------
		bool					m_bBloodyZenith; 
		int						m_BloodyZenithCount; 
		
		//----------------------------------------------------
		// GunShotGuidance�� ���� ������ �ѽ�� ����
		//----------------------------------------------------
		bool					m_bGunShotGuidance; 
		int						m_GunShotGuidanceCount; 
		
		//----------------------------------------------------
		// Armageddon�� ���� ���� ��
		//----------------------------------------------------
		bool					m_bArmageddon; 
		int						m_ArmageddonCount; 
		//add by viva
		BYTE					m_CurrentDirection;	// ������ Direction
		//end
		//----------------------------------------------------
		// Teleport�� ���� ���� ��
		//----------------------------------------------------
		BYTE					m_fGhost; 
		int						m_GhostCount; 
		
		//----------------------------------------------------
		// ĳ���� ������� ����
		//----------------------------------------------------
		bool					m_bFakeDie; 
		int						m_FakeDieCount; 
		
		//----------------------------------------------------
		// darkness
		//----------------------------------------------------
		int						m_DarknessCount;
		int						m_DarknessCountInc;

		//----------------------------------------------------
		// party - player�� üũ�� ������ �ҷ���..
		//----------------------------------------------------
		bool					m_bPlayerParty;

		//--------------------------------------------------
		// Hallucination�ɷ����� ������ ���̱�
		//--------------------------------------------------		
		bool					m_bHallu;
		TYPE_CREATURETYPE		m_HalluCreatureType;
		TYPE_FRAMEID			m_HalluCreatureFrameID;
		WORD					m_HalluColorBody;
		BYTE					m_HalluAction;
		BYTE					m_HalluFrame;
		WORD					m_HalluName;	// �ϴ� �ӽ÷�...
		short					m_DelayLastAction;					// �ش� �׼��� �� �Ŀ� �Ϲ� �׼����� ���ƿö� ������
		//add by viva
		BYTE					m_DirectionMoved;	// �̵��� ����	
		//end
		//--------------------------------------------------		
		// ���
		//--------------------------------------------------		
		BYTE					m_Competence;

		//--------------------------------------------------		
		// �����߿� ������밡 ������ ���� ���� �����ϱ� ����.
		// �������ϴ� ����� �ڽ��� ���� �ϴ� ����� ID�� ���
		//--------------------------------------------------		
		TYPE_OBJECTID			m_DrainCreatureID;

		// PET ID
		TYPE_OBJECTID			m_PetID;
		TYPE_OBJECTID			m_ElementalID;
		
		//--------------------------------------------------
		// HP�� ��ȭ���� ���
		//--------------------------------------------------
		HPMODIFYLIST			m_HPModifyList;		
		BYTE					m_GradeActionInfo;				// �����Ϸ��� Action �� �ܰ�.
		
		int						m_HeadSkin;
		
		BYTE					m_NickNameType;
		string					m_NickName;
		
		//--------------------------------------------------
		// ������ ���� ������.. 
		// 1,2 : ������
		// 3~7 : ������
		//--------------------------------------------------
		BYTE					m_bSiegeWar;	

		// ���� ��
		BYTE					m_bBurningSolCount;
		bool					m_bBurningSol;

		BYTE					m_bInstallTurretCount;
		BYTE					m_bInstallTurretDirect;
		int						m_current_sprite_index;

		//add by viva for no increase speed
		BYTE					m_MoveCountMax;		// �̵��ϴ� ��ǥ ȸ��
		//end

		string					m_PersnalMessage;
		int						m_Persnal_flag;
		bool					m_Input_Chat_Flag;

		bool					m_IsSkipMotorStand;

};

#endif

		