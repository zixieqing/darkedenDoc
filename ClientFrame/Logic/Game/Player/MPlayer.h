//----------------------------------------------------------------------
// MPlayer.h
//----------------------------------------------------------------------
// Ư���� Player�� �ٷ�� class
// ��ã�� algorithm ����
//----------------------------------------------------------------------

#ifndef	__MPLAYER_H__
#define	__MPLAYER_H__

#pragma warning(disable:4786)

#include <list>
#include <queue>

//----------------------------------------------------------------------
// define
//----------------------------------------------------------------------
// �����ϴ� �Ϳ� ���� flag
#define	FLAG_TRACE_NULL					0
#define	FLAG_TRACE_CREATURE_BASIC		0x0001
#define	FLAG_TRACE_CREATURE_SPECIAL		0x0002
#define	FLAG_TRACE_SECTOR_BASIC			0x0004
#define	FLAG_TRACE_SECTOR_SPECIAL		0x0008
#define	FLAG_TRACE_ITEM					0x0010
#define	FLAG_TRACE_INTERACTIONOBJECT	0x0020
#define	FLAG_TRACE_SELF					0x0040
#define	FLAG_TRACE_INVENTORY			0x0080
#define	FLAG_TRACE_EFFECT				0x0100


//----------------------------------------------------------------------
// class ����
//----------------------------------------------------------------------
class MCreature;
class MItem;
class MInteractionObject;
class Effect;
class MSlayerGear;
class MVampireGear;
class MOustersGear;

extern MSlayerGear*		g_pSlayerGear;
extern MVampireGear*	g_pVampireGear;
extern MOustersGear*	g_pOustersGear;

#include "MCreatureWear.h"
#include "MEffectTarget.h"
#include "MRequestMode.h"

extern DWORD	g_CurrentTime;

#ifndef __DNODE_DEFINE__
#define __DNODE_DEFINE__

//----------------------------------------------------------------------
//
// ��ã�⿡ �̿��� Direction Node
//
//----------------------------------------------------------------------
class DNode {
	public :
		DNode(int _x=0, int _y=0, int _d=0, int _ds=0, int _s=0)
		{ 
			x=_x;
			y=_y;
			direction=_d;
			distance=_ds;
			step = _s;
			pParent=NULL;
		}

		void	SetParent(DNode* pDNode)	{ pParent = pDNode; }

		int		x;
		int		y;
		int		direction;
		int		distance;
		int		step;
		DNode*	pParent;
};


//----------------------------------------------------------------------
//
// ��ã���� �� �� ���� Node�� �����ϴ� �� ����
//
//----------------------------------------------------------------------
// [1] �Ÿ��� ����� ��
// [2] ������ ȸ���� ���� ��
// [3] ���� ����� ���� ��
class Comparison {
	public :
		// distance�� ���� �� �����ؾ� �Ѵ�.		
		// true : right�� �����Ѵ�.
		// false : left�� �����Ѵ�.
		bool operator () (DNode * left, DNode * right) const
		{ 
			int diff = left->distance - right->distance;			
			int s = left->step - right->step;

			// �Ÿ���(diff) ���� ���..
			if (diff==0)
			{			
				// ������ ȸ���� ���� ���
				if (s==0)
				{
					if (left->pParent!=NULL && right->pParent!=NULL)
					{
						if (right->pParent->direction == right->direction)
						{
							return true;	// right����
						}
						
						return false;	// left����						
					}
				}
				// ������ ȸ���� ���� ��
				else if (s>0) 
				{
					return true;
				}
				
				return false;				
			}			
			// �Ÿ��� ���� ��
			else if (diff>0) return true; 

			return false;
		}
};
#endif

//----------------------------------------------------------------------
//
// MPlayer class
//
//----------------------------------------------------------------------
class MPlayer : public MCreatureWear, public MRequestMode {
	public :
		typedef	std::list<BYTE>		DIRECTION_LIST;

		enum REQUEST_MODE
		{
			REQUEST_NULL,
			REQUEST_TRADE,
			REQUEST_PARTY
		};

		enum ATTACK_MODE 
		{
			ATTACK_MODE_PEACE,		// �ƹ��� ���� �� ��
			ATTACK_MODE_NORMAL,		// ��(!)�� ������
			ATTACK_MODE_AGGRESS,	// �ƹ��� ������
			ATTACK_MODE_GUILD,		// �츮 ��常 �츮��
		};

		enum ITEM_CHECK_BUFFER
		{
			ITEM_CHECK_BUFFER_NULL = 0,

			// item�ݱ�
			ITEM_CHECK_BUFFER_PICKUP_TO_INVENTORY,
			ITEM_CHECK_BUFFER_PICKUP_TO_MOUSE,
			ITEM_CHECK_BUFFER_PICKUP_TO_QUICKSLOT,
			ITEM_CHECK_BUFFER_PICKUP_MONEY,

			// item ��� 
			ITEM_CHECK_BUFFER_USE_FROM_INVENTORY,
			ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT,
			
			// item�� �ٸ� item�� �߰�
			ITEM_CHECK_BUFFER_INSERT_FROM_INVENTORY,	
			ITEM_CHECK_BUFFER_INSERT_FROM_GEAR,	
			ITEM_CHECK_BUFFER_INSERT_FROM_QUICKSLOT,			
			
			ITEM_CHECK_BUFFER_DROP_TO_INVENTORY,
			ITEM_CHECK_BUFFER_PICKUP_FROM_INVENTORY,

			ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY,	// ������ ��� ���

			// trade�� ��
			ITEM_CHECK_BUFFER_TRADE_ADD,
			ITEM_CHECK_BUFFER_TRADE_REMOVE,

			// item�� ��� ���
			ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY,

			// item���� ��� ���
			ITEM_CHECK_BUFFER_SKILL_FROM_ITEM,

			// mouse���� zone���� ������.
			ITEM_CHECK_BUFFER_DROP_TO_ZONE,			

			ITEM_CHECK_BUFFER_DROP_TO_RELICTABLE,			

			// item�� �ٸ� �����ۿ� ���ϱ�
			ITEM_CHECK_BUFFER_ITEM_TO_ITEM,

			// Ʈ�� ��ü
			ITEM_CHECK_BUFFER_TREE_MERGE,
			ITEM_CHECK_BUFFER_USE_FROM_GEAR,
			
			ITEM_CHECK_BUFFER_USE_MIXING_ITEM,
			ITEM_CHECK_BUFFER_DROP_TO_CREATURE,			
			
			ITEM_CHECK_BUFFER_USE_FROM_GQUEST_INVENTORY,
		};

		// server���� �����ޱ�..
		enum WAIT_VERIFY
		{
			WAIT_VERIFY_NULL,
			WAIT_VERIFY_MOTORCYCLE_GETON,
			WAIT_VERIFY_MOTORCYCLE_GETOFF,
			WAIT_VERIFY_SKILL_SUCCESS,
			WAIT_VERIFY_ITEM_USE,
			WAIT_VERIFY_NPC_ASK,
			WAIT_VERIFY_TRADE,
			WAIT_VERIFY_PARTY,
			WAIT_VERIFY_PARTY_LEAVE,
			WAIT_VERIFY_RESURRECT,
			WAIT_VERIFY_LOVE_CHAIN,
			WAIT_VERIFY_LOGOUT,
			WAIT_VERIFY_SYLPH_SUMMON_GETOFF,
		};

	public :
		MPlayer();
		~MPlayer();

		void* operator new( size_t size )
		{
			return ::operator new( size );
		}

		void operator delete( void* pmem )
		{
			::operator delete ((MPlayer*)pmem);
		}
		
		virtual CLASS_TYPE	GetClassType() const	{ return CLASS_PLAYER; }

		class MPlayerGear*	GetGear() const 
		{
			switch(GetRace())
			{
			case RACE_SLAYER:
				return (MPlayerGear *)g_pSlayerGear;
				
			case RACE_VAMPIRE:
				return (MPlayerGear *)g_pVampireGear;
				
			case RACE_OUSTERS:
				return (MPlayerGear *)g_pOustersGear;
			}

			return NULL;
		}

		// Zone�� set�Ѵ�.
		void	SetZone(MZone* pZone);

		virtual void	SetCreatureType(TYPE_CREATURETYPE type);		

		// 
		virtual void		SetServerPosition(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);

		// �þ� ����
		void	CalculateLightSight();
		const int	GetLightSight() const			{ return m_LightSight; }
		char	GetTimeLightSight()	const		{ return m_TimeLightSight; }
		void	SetTimeLightSight(char s);
		void	SetItemLightSight(int s);
		int		GetItemLightSight() const			{ return m_ItemLightSight; }
		void	SetSight(char s)				{ m_Sight = s; }
		char	GetSight()	const			{ return m_Sight; }
		
		// �� �ൿ~
		void	Action();

		// ������ �� �ൿ ����.. 
		void	SetNextAction(BYTE action);	
		void	SetNextActionToMove();

		// 
		void	SetAction(BYTE action);

		// ���� delay�� ���ֱ� ���ؼ� �ӽ÷�..
		void	StopBloodDrain();
		void	StopAbsorbSoul();	// ��

		//----------------------------------------------------------
		// EffectStatus
		//----------------------------------------------------------
		bool	AddEffectStatus(EFFECTSTATUS status, DWORD delayFrame);
		bool	RemoveEffectStatus(EFFECTSTATUS status);		

		//----------------------------------------------------------
		// ���� �� �ٲٱ�
		//----------------------------------------------------------
		void	SetStatus(DWORD n, DWORD value);
		void	CalculateStatus();
		
		void	CalculateSight();
		
		//----------------------------------------------------------
		// ����
		//----------------------------------------------------------
		bool	ChangeToSlayer();
		bool	ChangeToVampire();

//		//----------------------------------------------------------
//		// �þ�
//		//----------------------------------------------------------
//		void	SetLightSight(char LightSight);
//		void	UnSetLightSight();	
		
		//----------------------------------------------------------
		// �������뿡 �ֳ�?
		//----------------------------------------------------------
		BOOL	IsInSafeSector() const;
		
		//----------------------------------------------------------
		// ���/�ױ�
		//----------------------------------------------------------
		void	SetAlive();		// ��Ƴ���? - -;
		void	SetDead();		// �״´�.

		//----------------------------------------------------------
		// ���� �ٲٱ�
		//----------------------------------------------------------
		bool	SetAddonItem( MItem* pItem );
		bool	RemoveAddonItem( MItem* pItem );

		//----------------------------------------------------------
		// SoulChain ����
		//----------------------------------------------------------
		void	SetCannotTrace();
		

		//----------------------------------------------------------
		//
		//			 Item ó��
		//
		//----------------------------------------------------------
		void	PickupItem(MItem* pItem);	// item �ݱ� ó��
		void	PickupItemToInventory(MItem* pItem);
		void	PickupItemToMouse(MItem* pItem);
		bool	PickupItemToQuickslot(MItem* pItem);
		void	PickupMoney(MMoney* pItem);
		void	RideMotorcycle(MMotorcycle* pMotorcycle);		

		//----------------------------------------------------------
		//
		//            Server Packet�� ����
		//
		//----------------------------------------------------------
		// ��ٸ��� Move Packet�� ����.
		BYTE	GetSendMove() const		{ return m_SendMove; }
		void	ResetSendMove();
		
		//----------------------------------------------------------
		// server�κ��� ������ ��ٸ��� ����
		//----------------------------------------------------------
		BOOL	IsWaitVerifyNULL() const	{ return m_WaitVerify==WAIT_VERIFY_NULL; }
		BOOL	IsWaitVerify() const		{ return m_WaitVerify!=WAIT_VERIFY_NULL; }
		WAIT_VERIFY	GetWaitVerify() const	{ return m_WaitVerify; }
		TYPE_ACTIONINFO GetWaitVerifyActionInfo() const { return m_WaitVerifyActionInfo; }
		void	SetWaitVerifyNULL()			{ m_WaitVerify=WAIT_VERIFY_NULL; m_WaitVerifyActionInfo=ACTIONINFO_NULL; }
		void	SetWaitVerify(WAIT_VERIFY wv, TYPE_ACTIONINFO ai=ACTIONINFO_NULL)	{ m_WaitVerify=wv; m_WaitVerifyActionInfo=ai; }

		//----------------------------------------------------------
		// packetó��
		//----------------------------------------------------------
		//void	PacketBack();
		void	PacketMoveOK(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, BYTE direction);
		void	PacketMoveNO();
		void	PacketSpecialActionResult(TYPE_ACTIONINFO nResultActionInfo, TYPE_OBJECTID id, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, BYTE temp=0);
		bool	PacketAddActionResult(WORD effectID, MActionResult* pResult);	// ��� ����

		bool	FastMovePosition(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y, bool server = false);	// Zone�� Sector������ ����(-_-;) �̵��Ѵ�.

		bool	KnockBackPosition(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);

		//----------------------------------------------------------
		//
		//           ���� 
		//
		//----------------------------------------------------------
		bool	SelfSpecialAction();
		// �ٸ� Creature�� �����ؼ� Action�� ���Ѵ�.
		bool	TraceCreatureToBasicAction(TYPE_OBJECTID id, bool bForceAttack=false, bool	bClick = false);
		bool	TraceCreatureToSpecialAction(TYPE_OBJECTID id, bool bForceAttack=false);
		bool	TraceSectorToBasicAction(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);
		bool	TraceSectorToSpecialAction(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);
		bool	TraceItem(TYPE_OBJECTID id);
		bool	TraceInteractionObject(TYPE_OBJECTID id, BYTE currentAction);
		bool	TraceEffect(TYPE_OBJECTID id);
		bool	TraceInventoryItem(TYPE_OBJECTID id);

		// creature��� ����
		void	KeepTraceCreature();

		// ��� ���� ����
		void	TraceNULL()				{ m_fTrace=FLAG_TRACE_NULL; m_fNextTrace=FLAG_TRACE_NULL; }
		void	TraceNextNULL()			{ m_fNextTrace=FLAG_TRACE_NULL; } 

		// nActionInfo�� ��� ���� �Ÿ���?
		int		GetActionInfoRange(TYPE_ACTIONINFO nActionInfo);
		
		//----------------------------------------------------------
		//
		//         ��ã��
		//
		//----------------------------------------------------------
		// Zone�󿡼��� ��ǥ��ġ�� ����
		bool	SetMovePosition(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);
		bool	SetNextDestination(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);
		bool	SetDestination(TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY);		
		bool	IsNextDirectionNULL()		{ return m_listDirection.empty(); }
		void	SetStop();		
		
		// get
		void	GetDestination(POINT &dest);
		void	GetNextDestination(POINT &dest);
		bool	GetNextPosition(POINT &next);
		BYTE	GetNextDirection()	const			{ return m_listDirection.front(); }

		//----------------------------------------------------------
		// ����
		//----------------------------------------------------------
		BYTE			GetBasicAttackDistance() const	{ return m_BasicAttackDistance; }
		void			SetBasicAttackDistance(BYTE bad) { m_BasicAttackDistance = (bad==0)?1:bad; }
		TYPE_OBJECTID	GetTraceID() const				{ return m_TraceID; }
		BOOL			IsTraceNULL()	const			{ return m_fTrace==0; }
		BOOL			IsTraceCreature()	const		{ return (m_fTrace & FLAG_TRACE_CREATURE_BASIC) || (m_fTrace & FLAG_TRACE_CREATURE_SPECIAL); }
		BOOL			IsTraceSector()	const			{ return (m_fTrace & FLAG_TRACE_SECTOR_BASIC) || (m_fTrace & FLAG_TRACE_SECTOR_SPECIAL); }
		BOOL			IsTraceItem()	const			{ return m_fTrace & FLAG_TRACE_ITEM; }
		BOOL			IsTraceInteractionObject() const { return m_fTrace & FLAG_TRACE_INTERACTIONOBJECT; }
		BOOL			IsTraceEffect() const			{ return m_fTrace & FLAG_TRACE_EFFECT; }

		//----------------------------------------------------------
		// ��� Creature�� �����ϴ°�?
		//----------------------------------------------------------
		bool			IsKeepTraceCreature() const		{ return m_bKeepTraceCreature; }
		void			SetKeepTraceCreature()			{ m_bKeepTraceCreature = true; }
		void			UnSetKeepTraceCreature()		{ m_bKeepTraceCreature = false; }

		//----------------------------------------------------------
		// �ൿ �ݺ��ϱ�
		//----------------------------------------------------------
		BOOL			IsRepeatAction() const			{ return m_bRepeatAction; }
		void			SetRepeatAction()				{ m_bRepeatAction = TRUE; m_RepeatCount = 0; m_RepeatTimer = GetTickCount(); }		
		void			UnSetRepeatAction();

		// ��� ����
		void			SetSpecialActionInfo( TYPE_ACTIONINFO n );

		// ���� ���ΰ�?
		bool			OnAttacking() const;
				
		//----------------------------------------------------------
		// Delay�ð��� ������ delay�� �����°�?
		//----------------------------------------------------------
		bool			IsNotDelay() const		{ return m_DelayTime==0 || m_DelayTime <= g_CurrentTime; }
		bool			IsNotDeadDelay() const	{ return m_DeadDelayTime <= g_CurrentTime; }
		void			SetDelay(DWORD delay)	{ m_DelayTime = g_CurrentTime + delay; }
		DWORD			GetDeadDelayLast() const;

		//----------------------------------------------------------
		// �����̾�� ���ϴµ� ���� �ð�
		//----------------------------------------------------------
		void			SetConversionDelay(DWORD last)		{ m_ConversionDelayTime = g_CurrentTime + last; }
		DWORD			GetConversionDelayTime() const		{ return m_ConversionDelayTime; }
		void			UnSetConversionDelay()				{ m_ConversionDelayTime=0; }
		void			UpdateConversionTime();

		//----------------------------------------------------------
		// �������� ���..
		//----------------------------------------------------------
		void			RemoveEffectTarget(BYTE id);
		void			AddEffectTarget(MEffectTarget* pEffectTarget);
		
		//----------------------------------------------------------
		// Player�� Attack Mode
		//----------------------------------------------------------
		ATTACK_MODE	GetAttackMode() const	{ return m_AttackMode; }
		bool	IsAttackModePeace() const	{ return m_AttackMode == ATTACK_MODE_PEACE; }
		bool	IsAttackModeNormal() const	{ return m_AttackMode == ATTACK_MODE_NORMAL; }
		bool	IsAttackModeAggress() const	{ return m_AttackMode == ATTACK_MODE_AGGRESS; }
		bool	IsAttackModeGuild() const	{ return m_AttackMode == ATTACK_MODE_GUILD; }
		void	SetAttackModePeace()		{ m_AttackMode = ATTACK_MODE_PEACE; }
		void	SetAttackModeNormal()		{ m_AttackMode = ATTACK_MODE_NORMAL; }
		void	SetAttackModeAggress()		{ m_AttackMode = ATTACK_MODE_AGGRESS; }
		void	SetAttackModeGuild()		{ m_AttackMode = ATTACK_MODE_GUILD; }

		// to������ ������ �� �ִ� AttackMode�ΰ�?
		bool	CanAttackTribe( enum CREATURETRIBE to ) const;
		bool	CanAttackTribe( const MCreature* pCreature ) const	{ return CanAttackTribe( pCreature->GetCreatureTribe() ); }
		bool	CanAttackGuild( const MCreature* pCreature ) const;

		//----------------------------------------------------------
		// Item Check Buffer
		//----------------------------------------------------------
		bool	IsItemCheckBufferNULL()				{ return m_pItemCheckBuffer==NULL; }

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		void	SetItemCheckBuffer(MItem* pItem, enum ITEM_CHECK_BUFFER status, TYPE_OBJECTID SubItem = OBJECTID_NULL);
	#else
		void	SetItemCheckBuffer(MItem* pItem, enum ITEM_CHECK_BUFFER status);
	#endif
		
		void	ClearItemCheckBuffer();		// ����
		MItem*	GetItemCheckBuffer() const				{ return m_pItemCheckBuffer; }
	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		TYPE_OBJECTID	GetItemIDCheckBufferSubInventory() const	{ return m_dwSubItemIDCheckBuffer; }
	#endif
		enum ITEM_CHECK_BUFFER	GetItemCheckBufferStatus() const	{ return m_ItemCheckBufferStatus; }

		// ���� ���� �Լ��� - -;
		bool	IsItemCheckBufferPickupToInventory() const		{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_PICKUP_TO_INVENTORY; }
		bool	IsItemCheckBufferPickupToMouse() const			{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_PICKUP_TO_MOUSE; }
		bool	IsItemCheckBufferPickupToQuickslot() const		{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_PICKUP_TO_QUICKSLOT; }
		bool	IsItemCheckBufferPickupMoney() const			{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_PICKUP_MONEY; }
		bool	IsItemCheckBufferUseFromInventory() const		{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_USE_FROM_INVENTORY; }
		bool	IsItemCheckBufferUseFromQuickSlot() const		{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT; }
		bool	IsItemCheckBufferInsertFromInventory() const	{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_INSERT_FROM_INVENTORY; }
		bool	IsItemCheckBufferInsertFromQuickSlot() const	{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_INSERT_FROM_QUICKSLOT; }
		bool	IsItemCheckBufferDropToInventory() const		{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_DROP_TO_INVENTORY; }
		bool	IsItemCheckBufferPickupSomeFromInventory() const	{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_PICKUP_SOME_FROM_INVENTORY; }		
		bool	IsItemCheckBufferPickupFromInventory() const	{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_PICKUP_FROM_INVENTORY; }
		bool	IsItemCheckBufferTradeAdd() const				{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_TRADE_ADD; }
		bool	IsItemCheckBufferTradeRemove() const			{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_TRADE_REMOVE; }
		bool	IsItemCheckBufferSkillToInventory() const		{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_SKILL_TO_INVENTORY; }
		bool	IsItemCheckBufferSkillFromItem() const			{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_SKILL_FROM_ITEM; }
		bool	IsItemCheckBufferDropToZone() const				{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_DROP_TO_ZONE; }
		bool	IsItemCheckBufferDropToRelicTable() const		{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_DROP_TO_RELICTABLE; }
		bool	IsItemCheckBufferItemToItem() const				{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_ITEM_TO_ITEM; }
		bool	IsItemCheckBufferDropToCreature() const			{ return m_ItemCheckBufferStatus==ITEM_CHECK_BUFFER_DROP_TO_CREATURE; }
		
		//----------------------------------------------------------
		// Lock Mode
		//----------------------------------------------------------
		bool	IsLockMode() const		{ return m_bLockMode; }
		void	SetLockMode()			{ m_bLockMode = true; m_LockTimer = GetTickCount(); }
		void	UnSetLockMode()			{ m_bLockMode = false; }
		int		FindEnemy();

		//----------------------------------------------------------
		// player�� Darkness�ȿ� �ִ°�?
		// DarknessCount�� ��Ÿ���� ���̴°�?�̴�.
		//----------------------------------------------------------
		void	CheckInDarkness();

		void	SetUndergroundCreature();
		void	SetGroundCreature();
		void	SetFlyingCreature();

		// 2004, 5, 7, sobeit add start
		void	SetPetDelay(DWORD dwDelay) {m_PetDelayTime = dwDelay;}
		// 2004, 5, 7, sobeit add end

		// 2004, 8, 21, sobeit add start
		void	SetSweepViewValue(BYTE n ) {m_SweepVice_Value = n;}
		BYTE	GetSweepViewValue() { return m_SweepVice_Value;}
		bool	CheckRbuttonUpSkill();
		void	SetSweepPos(int x, int y) { m_SweepViceX = x; m_SweepViceY = y;	}
		void	SetTempSelectPos(int x, int y) { m_TempSelectPosX = x; m_TempSelectPosY = y;	}

		bool	IsShowAdamCloud() { return m_bShowAdamCloud;}
		void	SetShowAdamCloud(bool bShow) { m_bShowAdamCloud = bShow;}
		// 2004, 8, 21, sobeit add end
		
		// 2005, 1, 4, sobeit add start
		void	UseWildWolf_Corpse(MItem *pItem);
		// 2005, 1, 4, sobeit add end

		void	SetResurrectZoneID(int ZoneID) { m_ResurrectZoneID = ZoneID; }
		int		GetResurrectZoneID() { return m_ResurrectZoneID; }

	protected :				
		void	ActionMove();			// move
		void	ActionEffect();			// effect
		void	ActionToSendPacket();		// packet�� ������..
		bool	ActionInTraceDistance();	// �ൿ ���� �Ÿ��� ���� ��
		void	AffectUsedActionInfo(TYPE_ACTIONINFO nUsedActionInfo);		// m_nUsedActionInfo�� �����Ų��.
		void	AttachCastingEffect(TYPE_ACTIONINFO nUsedActionInfo, BOOL bForceAttach=FALSE);

		// ������ creature���� �⺻ action ����
		void	BasicActionToCreature();

		// ���� �ൿ�� ����
		bool	CheckBufferAction();

		// �ݺ� �ൿ ����
		bool	CheckRepeatAction();

		// list node�� �����.
		void	RemoveNodes();

		// ��ǥ��ġ������ �Ÿ� ���
		int		CalculateDistance(int x, int y);
		
		// sweep vice update
		void	UpdateSweepVice();
		bool	UpdateBurningSol();
		bool	UpDateInstallTurret();

	protected :		
		DWORD						m_RepeatTimer;				// Repeat��� ���ѽð�
		DWORD						m_LockTimer;				// Lock��� ���ѽð�		

		TYPE_SECTORPOSITION			m_DestX;
		TYPE_SECTORPOSITION			m_DestY;					// ��ǥ��ġ(Sector)

		TYPE_SECTORPOSITION			m_NextDestX; 
		TYPE_SECTORPOSITION			m_NextDestY;				// ���� ��ǥ��ġ(Sector)

		TYPE_SECTORPOSITION			m_BlockDestX;				// �� ���� ��.. 
		TYPE_SECTORPOSITION			m_BlockDestY;				// 

		// ��ٸ��� move packet��
		BYTE					m_SendMove;

		// Basic������ ���� ���� �Ÿ� : 0�� �Ǿ�� �ȵȴ�. �ּ� 1�̴�.
		BYTE					m_BasicAttackDistance;	

		// �����ϱ�
		WORD					m_fTrace;				// ������ ����		
		WORD					m_fTraceBuffer;			// ������ ����(��� ����صδ� ��)
		TYPE_OBJECTID			m_TraceIDBuffer;		//
		BYTE					m_TraceDistance;		// ���� �Ÿ�		
		BYTE					m_TraceObjectAction;	// �����ϴ� Object�� ����
		bool					m_bTraceCreatureToForceAttack;
		bool					m_bNextForceAttack;

		// ���� ���� - Buffering
		WORD					m_fNextTrace;
		TYPE_OBJECTID			m_NextTraceID;
		TYPE_SECTORPOSITION		m_NextTraceX;
		TYPE_SECTORPOSITION		m_NextTraceY;
		short					m_NextTraceZ;
		BYTE					m_NextTraceObjectAction;

		// �ൿ�� �ݺ��ϴ°�?
		BOOL					m_bRepeatAction;
		
		// � Creature�� ��� �����ϴ°�?
		bool					m_bKeepTraceCreature;

		// �����̴µ� �ʿ��� �͵�..
		typedef std::priority_queue<DNode*, std::vector<DNode*>, Comparison>	DNODE_PQ;
		typedef	std::list<DNode*>												DNODE_LIST;

		DNODE_PQ			m_pqDNodes;
		DNODE_LIST			m_listDNodes;

		DIRECTION_LIST	m_listDirection;
		DIRECTION_LIST	m_listSendDirection;

		// ��� ��� ���� delay
		DWORD						m_DelayTime;

		// �� ���� ������� delay
		DWORD						m_PetDelayTime;

		// ���� ���� ���� ��� ���
		EFFECTTARGET_LIST			m_listEffectTarget;

		// ���� ���� Mode
		ATTACK_MODE					m_AttackMode;

		// �װ� ������ delay�ð� - ��������..
		DWORD						m_DeadDelayTime;

		// Item�� ����ϰ� ����..
		ITEM_CHECK_BUFFER			m_ItemCheckBufferStatus;
		MItem*						m_pItemCheckBuffer;

	#ifdef __TEST_SUB_INVENTORY__   // add by Coffee 2007-8-9 ���Ӱ��а�
		DWORD						m_dwSubItemIDCheckBuffer; // add 2005, 3, 2, sobeit added  - � subinventory ���� ��� �ߴ���
	#endif

		// ��� ����� ��ǥ : effect target
		MEffectTarget*				m_pEffectTarget;

		// server���� ������ ��ٸ��� ����
		WAIT_VERIFY					m_WaitVerify;
		TYPE_ACTIONINFO				m_WaitVerifyActionInfo;

		// �����̾�� ���ϴµ� ���� delay frame - ��������
		DWORD						m_ConversionDelayTime;

		// packet�� ������ �ʴ� actioninfo 
		// flash sliding������ �߰��ƴ�. - -;;
		TYPE_ACTIONINFO					m_nNoPacketUsedActionInfo;

		//----------------------------------------------------
		// Lock Mode
		//----------------------------------------------------
		// ���ڸ��� �����ؼ� ��ó�� �ִ� ���� �����Ѵ�.
		bool						m_bLockMode;

		// ���� ũ�� 
		char					m_TimeLightSight;
//		TYPE_SECTORPOSITION		m_TimeLightSightX;	// �ֱٿ� �þ߸� Set�� ��ġ
//		TYPE_SECTORPOSITION		m_TimeLightSightY;		
		int						m_ItemLightSight;
		int						m_LightSight;

		// �þ��� ũ��
		char					m_Sight;		

		// 2004, 8, 21, sobeit add start
		// ��æ 130 ��ų ����
		BYTE					m_SweepVice_Value;
		TYPE_SECTORPOSITION		m_TempSelectPosX; // Temporary �ϰ� ������..-_-
		TYPE_SECTORPOSITION		m_TempSelectPosY;
		TYPE_SECTORPOSITION		m_SweepViceX;
		TYPE_SECTORPOSITION		m_SweepViceY;
		
		bool					m_bShowAdamCloud;
		// 2004, 8, 21, sobeit add end

		int						m_ResurrectZoneID;

};


extern MPlayer*		g_pPlayer;

#endif


