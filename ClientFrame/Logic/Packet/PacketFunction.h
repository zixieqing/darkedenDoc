//-----------------------------------------------------------------------------
// PacketFunction.h
//-----------------------------------------------------------------------------

#ifndef __PACKETFUNCTION_H__
#define __PACKETFUNCTION_H__

#include <Windows.h>
#include "MTypeDef.h"
//#include "SkillDef.h"
#include "Packet\Types\PacketItemDef.h"
//#include "Packet\Types\ItemTypes.h"
class MActionResult;
class MCreature;
class MCreatureWear;
class GCAddItemToZone;
class PCSlayerInfo2;
class PCSlayerInfo3;
class PCVampireInfo2;
class PCOustersInfo2;
class PCOustersInfo3;
class InventoryInfo;
class GearInfo;
class ExtraInfo;
class EffectInfo;
class MItem;
class MStatus;
class ModifyInfo;
class MFakeCreature;
class BloodBibleSignInfo;
//-----------------------------------------------------------------------------
// Global Packet HairID
//-----------------------------------------------------------------------------
extern int g_PacketHairMaleID[3];

extern int g_PacketHairFemaleID[3];

//-----------------------------------------------------------------------------
// Global Packet Item Table
//-----------------------------------------------------------------------------
extern MItem*		g_pPacketItemHelm[HELMET_MAX];
extern MItem*		g_pPacketItemJacket[JACKET_MAX];
extern MItem*		g_pPacketItemPants[PANTS_MAX];
extern MItem*		g_pPacketItemWeapon[WEAPON_MAX];
extern MItem*		g_pPacketItemShield[SHIELD_MAX];
extern MItem*		g_pPacketItemMotorcycle[MOTORCYCLE_MAX];
extern MItem*		g_pPacketItemOustersCoat[OUSTERS_COAT_MAX];
extern MItem*		g_pPacketItemOustersArm[OUSTERS_ARM_MAX];

//-----------------------------------------------------------------------------
// Set Server GroupName/Name
//-----------------------------------------------------------------------------
void			SetServerGroupName( const char* pName );
void			SetServerGroupStatus( int status );
void			SetServerName( const char* pName );

//-----------------------------------------------------------------------------
// Set GoreLevel
//-----------------------------------------------------------------------------
void			SetGoreLevel(bool bGoreLevel);

//-----------------------------------------------------------------------------
// Init / Release PacketItemTable
//-----------------------------------------------------------------------------
extern void		InitPacketItemTable();
extern void		ReleasePacketItemTable();

//-----------------------------------------------------------------------------
// Use Item OK
//-----------------------------------------------------------------------------
bool			UseItemOK();

bool			UseSkillCardOK(BYTE CardType);

//-----------------------------------------------------------------------------
// Get Mine/Bomb ActionInfo
//-----------------------------------------------------------------------------
int				GetMineActionInfo(int itemType);
int				GetBombActionInfo(int itemType);

//-----------------------------------------------------------------------------
// ���� ����
//-----------------------------------------------------------------------------
extern int		GetVampireCreatureType(int shape, bool bMale, int coatType);
extern int		GetOustersCreatureType(int coatType);
extern void		SetPCSlayerInfo(PCSlayerInfo2* pInfo);
extern void		SetPCVampireInfo(PCVampireInfo2* pInfo);
extern void		SetPCOustersInfo(PCOustersInfo2* pInfo);
extern void		SetInventoryInfo(InventoryInfo* pInventoryInfo);
extern void		SetGearInfo(GearInfo* pGearInfo, BloodBibleSignInfo* pBloodBibleInfo = NULL);
extern void		SetExtraInfo(ExtraInfo* pExtraInfo);
extern void		SetEffectInfo(MCreature* pCreature, EffectInfo* pEffectInfo, int delayedFrame=0);
extern void		AffectModifyInfo(MStatus* pStatus, ModifyInfo* pInfo);

//-----------------------------------------------------------------------------
// set addon
//-----------------------------------------------------------------------------
extern void		SetAddonToSlayer(MCreatureWear* pCreature, int npcID);
extern void		SetAddonToSlayer(MCreatureWear* pCreature, const PCSlayerInfo2* pInfo);
extern void		SetAddonToSlayer(MCreatureWear* pCreature, const PCSlayerInfo3* pInfo);

extern void		SetAddonToOusters(MCreatureWear* pCreature, const PCOustersInfo2* pInfo);
extern void		SetAddonToOusters(MCreatureWear* pCreature, const PCOustersInfo3* pInfo);
extern MFakeCreature*	NewFakeCreature(MCreature* pCreature, int x, int y);
extern MFakeCreature*	NewFakeCreature(int creatureType, int x, int y, int dir);

//-----------------------------------------------------------------------------
// add item to zone
//-----------------------------------------------------------------------------
extern MItem*	AddItemToZone(GCAddItemToZone* pPacket, BOOL bDropping);

//-----------------------------------------------------------------------------
// Get Direction to Position
//-----------------------------------------------------------------------------
extern BYTE		GetDirectionToPosition(int originX, int originY, int destX, int destY);

//-----------------------------------------------------------------------------
// Convert Alignment
//-----------------------------------------------------------------------------
int				ConvertAlignment(int alignment);

//-----------------------------------------------------------------------------
// Skill to Sector
//-----------------------------------------------------------------------------
extern void		SkillToSector(TYPE_ACTIONINFO nActionInfo, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, int dir, DWORD delayFrame, MActionResult* pResult);
extern void		SkillCrossCounter(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID);
extern void		SkillIllendue(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID);
extern void		SkillBlazeWalk(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID, BYTE grade);

//-----------------------------------------------------------------------------
// Portal ����
//-----------------------------------------------------------------------------
extern void		MoveIntoPortal(MCreature* pCreature);
extern void		ComeFromPortal(MCreature* pCreature);

//-----------------------------------------------------------------------------
// execute action info from mainnode
//-----------------------------------------------------------------------------
extern void		ExecuteActionInfoFromMainNode(
						TYPE_ACTIONINFO nActionInfo,										// ��� ��� ��ȣ
					
						TYPE_SECTORPOSITION startX, TYPE_SECTORPOSITION startY, int startZ, // ��� ����ϴ� ���(?) 
						int direction,														// ��� ����
						
						TYPE_OBJECTID targetID,												// ��ǥ�� ���� ����
						TYPE_SECTORPOSITION targetX, TYPE_SECTORPOSITION targetY, int targetZ, 
						
						DWORD delayFrame,													// ����� (����) ���� �ð�		
						
						MActionResult* pActionResult,	// ��� ����
						
						bool bStartFromMainNode = true,

						int sX = 0, int sY = 0		// ��ǥ ����
				);

extern void		AddVampirePortal(
						int serverID,								// ����Ʈ�� OID
						const char* ownerName,								// ��Ż ���� �̸�
						TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY,		// ��Ż�� ��ǥ
						DWORD delayFrame,							// ��Ż�� ���� �ð�
						
						// ��ǥ ����
						int zoneID,							// ��Ż�� ��ǥ �� ID
						TYPE_SECTORPOSITION zoneX,			// ��Ż�� ��ǥ ��ǥ x
						TYPE_SECTORPOSITION zoneY,			// ��Ż�� ��ǥ ��ǥ y

						bool bStartFromMainNode = true
				);

extern void		SetFadeStart(char start, char end, char step, BYTE r = 0, BYTE g = 0, BYTE b = 0,WORD delay = 0);
extern void		SetFadeEnd();

extern void		AddOustersElemental( MCreature *pOwnerCreature, int creatureType, int status );

extern void		SendBugReport(const char *bug, ...);
extern void		SendCrashReport();

extern BOOL GetMacAddressFromNetBIOS(LPBYTE lpMacAddress);

extern void SetBloodBibleSlot(BloodBibleSignInfo* pBloodBibleInfo);
#endif