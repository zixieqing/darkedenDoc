//----------------------------------------------------------------------
// MEffectGeneratorTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MEffectGeneratorTable.h"
#include "MAttackCreatureEffectGenerator.h"
#include "MAttackZoneEffectGenerator.h"
#include "MAttackZoneParabolaEffectGenerator.h"
#include "MStopZoneEffectGenerator.h"
#include "MFirePiecingEffectGenerator.h"
#include "MRisingEffectGenerator.h"
#include "MFallingEffectGenerator.h"
#include "MAttackCreatureParabolaEffectGenerator.h"
#include "MAttachCreatureEffectGenerator.h"
#include "MAttachCreatureEffectGroundGenerator.h"
#include "MStopZoneCrossEffectGenerator.h"
#include "MStopZoneXEffectGenerator.h"
#include "MStopZoneRectEffectGenerator.h"
#include "MRippleZoneEffectGenerator.h"
#include "MRippleZoneWideEffectGenerator.h"
#include "MStopZoneRhombusEffectGenerator.h"
#include "MStopInventoryEffectGenerator.h"
#include "MMultipleFallingEffectGenerator.h"
#include "MStopZoneMultipleEffectGenerator.h"
#include "MAttachZoneEffectGenerator.h"
#include "MStopZoneRandomEffectGenerator.h"
#include "MStopZoneWallEffectGenerator.h"
#include "MRippleZonePixelEffectGenerator.h"
#include "MStopZoneSelectableEffectGenerator.h"
#include "MAttachZoneSelectableEffectGenerator.h"
#include "MSpreadOutEffectGenerator.h"
#include "MBloodyWallEffectGenerator.h"
#include "MBloodyWaveEffectGenerator.h"
#include "MAttackCreatureHomingEffectGenerator.h"
#include "MAroundZoneEffectGenerator.h"
#include "MStopZoneEmptyCrossEffectGenerator.h"
#include "MStopZoneEmptyRectEffectGenerator.h"
#include "MStopZoneEmptyHorizontalWallEffectGenerator.h"
#include "MStopZoneEmptyVerticalEffectGenerator.h"
#include "MAttackZoneBombEffectGenerator.h"
#include "MAttachCreatureOrbitEffectGenerator.h"
#include "MMeteorDropEffectGenerator.h"
#include "MBloodyBreakerEffectGenerator.h"
#include "MAttachZoneAroundEffectGenerator.h"
#include "MAttackZoneRectEffectGenerator.h"
#include "MFollowPathEffectGenerator.h"

#include "MEffect.h"
#include "MSoundTable.h"
#include "MEffectSpriteTypeTable.h"

#include "MTopView.h"
#include "ClientDef.h"

#include "DebugInfo.h"
#include "SkillDef.h"
#include "EffectSpriteTypeDef.h"
#include "MSkipEffectGenerator.h"
#include "MPlayingWithFireEffectGenerator.h"
//#define	new			DEBUG_NEW

#ifdef OUTPUT_DEBUG
	#define OUTPUT_DEBUG_EFFECT_GENERATOR
#endif


//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
MEffectGeneratorTable*	g_pEffectGeneratorTable = NULL;

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------
MEffectGeneratorTable::MEffectGeneratorTable()
{
	for (int i=0; i<MAX_EFFECTGENERATORID; i++)
	{
		m_pEffectGenerator[i] = NULL;
	}	
}

MEffectGeneratorTable::~MEffectGeneratorTable()
{
	Release();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Init - �� ���� �ҷ��� �Ѵ�.
//----------------------------------------------------------------------
void
MEffectGeneratorTable::Init()
{
	Release();

	AddEffectGenerator( new MAttackCreatureEffectGenerator );
	AddEffectGenerator( new MAttackZoneEffectGenerator );	
	AddEffectGenerator( new MAttackZoneParabolaEffectGenerator );	
	AddEffectGenerator( new MStopZoneEffectGenerator );
	AddEffectGenerator( new MFirePiecingEffectGenerator );
	AddEffectGenerator( new MRisingEffectGenerator );
	AddEffectGenerator( new MFallingEffectGenerator );
	AddEffectGenerator( new MAttackCreatureParabolaEffectGenerator );
	AddEffectGenerator( new MAttachCreatureEffectGenerator );
	AddEffectGenerator( new MAttachCreatureEffectGroundGenerator );
	AddEffectGenerator( new MStopZoneCrossEffectGenerator );
	AddEffectGenerator( new MStopZoneXEffectGenerator );
	AddEffectGenerator( new MStopZoneRectEffectGenerator );
	AddEffectGenerator( new MRippleZoneEffectGenerator );
	AddEffectGenerator( new MRippleZoneWideEffectGenerator );
	AddEffectGenerator( new MStopZoneRhombusEffectGenerator );
	AddEffectGenerator( new MStopInventoryEffectGenerator );
	AddEffectGenerator( new MMultipleFallingEffectGenerator );
	AddEffectGenerator( new MStopZoneMultipleEffectGenerator );
	AddEffectGenerator( new MAttachZoneEffectGenerator );
	AddEffectGenerator( new MStopZoneRandomEffectGenerator );
	AddEffectGenerator( new MStopZoneWallEffectGenerator );
	AddEffectGenerator( new MRippleZonePixelEffectGenerator );
	AddEffectGenerator( new MStopZoneSelectableEffectGenerator );
	AddEffectGenerator( new MAttachZoneSelectableEffectGenerator );
	AddEffectGenerator( new MSpreadOutEffectGenerator );
	AddEffectGenerator( new MBloodyWallEffectGenerator );
	AddEffectGenerator( new MBloodyWaveEffectGenerator );
	AddEffectGenerator( new MAttackCreatureHomingEffectGenerator );
	AddEffectGenerator( new MAroundZoneEffectGenerator );
	AddEffectGenerator( new MStopZoneEmptyCrossEffectGenerator );
	AddEffectGenerator( new MStopZoneEmptyRectEffectGenerator );
	AddEffectGenerator( new MStopZoneEmptyHorizontalWallEffectGenerator );
	AddEffectGenerator( new MStopZoneEmptyVerticalWallEffectGenerator );
	AddEffectGenerator( new MAttackZoneBombEffectGenerator );
	AddEffectGenerator( new MAttachCreatureOrbitEffectGenerator );	
	AddEffectGenerator( new MMeteorDropEffectGenerator );	
	AddEffectGenerator( new MBloodyBreakerEffectGenerator );
	AddEffectGenerator( new MAttachZoneAroundEffectGenerator );
	AddEffectGenerator( new MAttackZoneRectEffectGenerator );
	AddEffectGenerator( new MFollowPathEffectGenerator );
	AddEffectGenerator( new MSkipEffectGenerator );
	AddEffectGenerator( new MPlayingWithFireEffectGenerator );
}	

//----------------------------------------------------------------------
// Release
//----------------------------------------------------------------------
void
MEffectGeneratorTable::Release()
{
	for (int i=0; i<MAX_EFFECTGENERATORID; i++)
	{
		if (m_pEffectGenerator[i] != NULL)
		{
			//#ifdef DEBUG_NEW
			//	operator delete (m_pEffectGenerator[i], __FILE__, __LINE__);
			//#else
				delete m_pEffectGenerator[i];
			//#endif

		}
	}	
}

//----------------------------------------------------------------------
// m_pEffectGenerator�� MEffectGenerator*�� �߰��Ѵ�.
//----------------------------------------------------------------------
void
MEffectGeneratorTable::AddEffectGenerator(MEffectGenerator* pEffectGenerator)
{
	// ���� ��쿡 �߰��ϰ�..
	if (m_pEffectGenerator[ pEffectGenerator->GetID() ] == NULL)
	{
		m_pEffectGenerator[ pEffectGenerator->GetID() ] = pEffectGenerator;
	}
	// �̹� �ٸ��� �ִٸ�... �߰����� �ʴ´�.
	else
	{
		delete pEffectGenerator;
	}
}


//----------------------------------------------------------------------
// Generate
//----------------------------------------------------------------------
// ���� Effect���� 
//----------------------------------------------------------------------
void
MEffectGeneratorTable::Generate(	
	int x0, int y0, int z0,
	BYTE direction,	
	BYTE power,
	TYPE_ACTIONINFO nActionInfo,
	MEffectTarget* pEffectTarget,
	BYTE temp1, BYTE temp2)
{	
	#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
		DEBUG_ADD_FORMAT("EGT-Generate. ai=%d, target=0x%X", nActionInfo, pEffectTarget);
	#endif

	if (nActionInfo >= g_pActionInfoTable->GetSize())
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD_FORMAT("Exceed Max ActionInfo(%d/%d)", nActionInfo, g_pActionInfoTable->GetSize());
		#endif

		return;
	}
	
	//------------------------------------------------------------
	// EffectTarget�� ���ų�..
	// ������ ������ �ٸ���...
	// ����(?) �߸��ƴٴ� ����..	
	//------------------------------------------------------------
	if (pEffectTarget==NULL)
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD_FORMAT("EGT-Generate OK0. ai=%d, target=0x%X", nActionInfo, pEffectTarget);
		#endif

		return;
	}
	else if ((*g_pActionInfoTable)[ nActionInfo ].GetSize()!=pEffectTarget->GetMaxPhase())
	{
		// ��ǥ �Ϸ��Ų��.
		//while (!pEffectTarget->IsEnd())
		//{
		//	pEffectTarget->NextPhase();
		//}

		//------------------------------------------------------------
		// ��ǥ�� ���� Target�̴�.. �����.
		//------------------------------------------------------------
		if (pEffectTarget->IsExistResult())
		{
			pEffectTarget->GetResult()->Release();			
		}
		delete pEffectTarget;
		pEffectTarget = NULL;

		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD_FORMAT("EGT-Generate OK1. ai=%d, target=0x%X", nActionInfo, pEffectTarget);
		#endif

		return;
	}

	#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
		DEBUG_ADD_FORMAT("et=0x%X, targetID=%d, targetPhase=%d", pEffectTarget, (int)pEffectTarget->GetEffectID(), pEffectTarget->GetMaxPhase());
	#endif
	
	//------------------------------------------------------------
	// Effect���� ������ ������...
	// ������ Effect�� ������.. ����� �ٷ� ó���ϸ� �ȴ�.
	//------------------------------------------------------------
	bool bGenerated = false;
	if ((*g_pActionInfoTable)[ nActionInfo ].GetSize()==0)
	{
		// ��� �ٷ� ó��
		pEffectTarget->SetResultTime();
	}	
	else
	{
		//------------------------------------------------------------
		// ���� EFFECT_INFO_NODE 
		//------------------------------------------------------------
		// ��ü�� 0������.. main node���� �����ϴ� ��쵵 �ִ�.
		// �׷��Ƿ� --> pEffectTarget->GetCurrentPhase()
		//------------------------------------------------------------
		ACTION_INFO_NODE&			info	= (*g_pActionInfoTable)[ nActionInfo ][pEffectTarget->GetCurrentPhase()];
		TYPE_EFFECTSPRITETYPE		EffectSpriteType = info.EffectSpriteType;
		
		if(nActionInfo == MAGIC_ACID_TOUCH || nActionInfo == MAGIC_BLOODY_NAIL )
		{
			if(power == 2)
			{
				if( nActionInfo == MAGIC_ACID_TOUCH )
				{
					EffectSpriteType = EFFECTSPRITETYPE_ACID_TOUCH;
				}
					else
				{
					EffectSpriteType = EFFECTSPRITETYPE_BLOODY_NAIL;
				}				
			}
		}

		//------------------------------------------------------------
		// ù��° ��ǥ
		//------------------------------------------------------------
		int targetX = pEffectTarget->GetX();
		int targetY = pEffectTarget->GetY();
		int targetZ = pEffectTarget->GetZ();
		int targetID = pEffectTarget->GetID();
		
		
		DWORD count;
		
		//------------------------------------------------------------
		// Effect�� �̹� node�� ���� �ð� ����
		//------------------------------------------------------------
		// bDelayNode�̰� ������ delay�� �ִ� ���
		//		//main node�̰� pEffectTarget�� DelayFrame�� 0�� �ƴ� ���
		//------------------------------------------------------------
		if (info.bDelayNode
			//(*g_pActionInfoTable)[ nActionInfo ].HasMainNode()
			//&& pEffectTarget->GetCurrentPhase()==(*g_pActionInfoTable)[ nActionInfo ].GetMainNode()
			&& pEffectTarget->GetDelayFrame()!=0)
		{
			count = pEffectTarget->GetDelayFrame();
		}
		else
		{
			count = info.Count;
		}


		//------------------------------------------------------------
		// ���� ��ǥ
		//------------------------------------------------------------
		pEffectTarget->NextPhase();

		
		//------------------------------------------------------------
		// EffectGenerator�� �������� ���� ���
		//------------------------------------------------------------
		if (info.EffectGeneratorID >= MAX_EFFECTGENERATORID
			|| m_pEffectGenerator[ info.EffectGeneratorID ]==NULL)
		{
			// ��ǥ �Ϸ��Ų��.
			//while (!pEffectTarget->IsEnd())
			//{
				//pEffectTarget->NextPhase();
			//}
			//------------------------------------------------------------
			// ��ǥ�� ���� Target�̴�.. �����.
			//------------------------------------------------------------
			if (pEffectTarget->IsExistResult())
			{
				pEffectTarget->GetResult()->Release();				
			}
			delete pEffectTarget;
			pEffectTarget = NULL;

			#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD_FORMAT("[Error] EGT-Generate id=%d, ai=%d, target=0x%X", info.EffectGeneratorID, nActionInfo, pEffectTarget);
			#endif	
			
			return;
		}

		//------------------------------------------------------------
		//
		// EffectGenerator���� Effect�� �����ϰ� �Ѵ�.
		//
		//------------------------------------------------------------
		EFFECTGENERATOR_INFO egInfo;

		egInfo.nActionInfo			= nActionInfo;
		egInfo.pEffectTarget		= pEffectTarget->IsEnd()? NULL : pEffectTarget;
		egInfo.effectSpriteType		= EffectSpriteType;//info.EffectSpriteType;
		egInfo.x0					= x0;
		egInfo.y0					= y0;
		egInfo.z0					= z0;
		egInfo.x1					= targetX;
		egInfo.y1					= targetY;
		egInfo.z1					= targetZ;
		egInfo.creatureID			= targetID;
		egInfo.direction			= direction;
		egInfo.step					= info.Step;
		egInfo.count				= count;
		egInfo.linkCount			= info.LinkCount;
		egInfo.power				= power;
		egInfo.pPreviousEffect		= NULL;
		egInfo.temp1				= temp1;
		egInfo.temp2				= temp2;

		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD_FORMAT("et=0x%X, targetID=%d, targetPhase2=%d", pEffectTarget, (int)pEffectTarget->GetEffectID(), pEffectTarget->GetMaxPhase());
		#endif

		//------------------------------------------------------------
		// Generate�� return���� egInfo.pEffectTarget�� 
		// ���ο��� �ٸ� effect�� link�Ǿ��°��� �ǹ��Ѵ�.
		//------------------------------------------------------------
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD_FORMAT("Generate before. id=%d", info.EffectGeneratorID);
		#endif

		if (m_pEffectGenerator[ info.EffectGeneratorID ]->Generate( egInfo ))
		{
			#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD("Generate true");
			#endif

			//------------------------------------------------------------
			// ����� �ܰ迡 �´� sound�� ������ش�.
			//------------------------------------------------------------
			if (info.SoundID != SOUNDID_NULL)
			{
				//g_Sound.Play( g_SoundTable[info.SoundID].pDSBuffer );
				POINT point = MTopView::PixelToMap(x0, y0);
				PlaySound( info.SoundID, false, point.x, point.y );
			}

			//------------------------------------------------------------
			// ����� ó���ؾ��ϴ� �����ΰ�? 
			//------------------------------------------------------------
			if (info.bResultTime)
			{
				// ��� ó�� �ð��� �����ٰ� üũ�Ѵ�.
				// ���߿� ����� ����� �ٷ� ó���ϰ� �ȴ�.
				pEffectTarget->SetResultTime();
			}

			#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD_FORMAT("et=0x%X, targetID=%d, targetPhase3=%d", pEffectTarget, (int)pEffectTarget->GetEffectID(), pEffectTarget->GetMaxPhase());
			#endif

			bGenerated = true;
		}
		else
		{
			#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD("Generate false");
			#endif

			pEffectTarget->SetResultTime();
		}
	}

	//------------------------------------------------------------
	// ��� ó��
	//------------------------------------------------------------
	if (pEffectTarget->IsResultTime() || pEffectTarget->IsEnd())
	{	
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("Check Result");
		#endif

		// ����� ������ ó���ؾ� �Ѵ�.
		if (pEffectTarget->IsExistResult())
		{
			MActionResult* pResult = pEffectTarget->GetResult();
			pEffectTarget->SetResultNULL();

			#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD_FORMAT("ExecuteResult. et=0x%X, targetID=%d, targetPhase4=%d", pEffectTarget, (int)pEffectTarget->GetEffectID(), pEffectTarget->GetMaxPhase());
			#endif

			// ��� ����
			pResult->Execute();
			
			// �޸� ����
			delete pResult;			
		}

		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			else
			{
				DEBUG_ADD("NO Result");
			}
		#endif
		
		//------------------------------
		// [ TEST CODE ]
		//------------------------------
		// Player�� �������̴� EffectTarget�� �����ٰ� �����Ѵ�.
		// �� ���� Player�ΰ�?
		// �ٸ� ĳ���͵� �� �Լ�(Generate)�� ����.
		g_pPlayer->RemoveEffectTarget( pEffectTarget->GetEffectID() );

		//if (!bGenerated)
		//{
		//	delete pEffectTarget;
		//}
	}
	
	//------------------------------------------------------------
	// �� �̻� ��ǥ�� �ʿ���� ������ �ܰ��� ���..
	// effect�� ������� �������� �Ѵ�.
	//------------------------------------------------------------
	if (//pEffectTarget->IsEnd() && 
		!bGenerated || pEffectTarget->IsEnd() )
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("delete EffectTarget");
		#endif

			if (pEffectTarget->IsExistResult())
			{
				MActionResult* pResult = pEffectTarget->GetResult();
				pEffectTarget->SetResultNULL();
				
#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD_FORMAT("ExecuteResult. et=0x%X, targetID=%d, targetPhase4=%d", pEffectTarget, (int)pEffectTarget->GetEffectID(), pEffectTarget->GetMaxPhase());
#endif
				
				// ��� ����
				pResult->Execute();
				
				// �޸� ����
				delete pResult;			
			}

		delete pEffectTarget;	
		pEffectTarget = NULL;
	}

	#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
		DEBUG_ADD_FORMAT("EGT-Generate OK. ai=%d, target=0x%X", nActionInfo, pEffectTarget);
	#endif
}

//----------------------------------------------------------------------
// GenerateNext
//----------------------------------------------------------------------
// ����� ���� Effect ����
//----------------------------------------------------------------------
void	 
MEffectGeneratorTable::GenerateNext( MEffect* pEffect )
{
	#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
		DEBUG_ADD_FORMAT("EGT-GenerateNext. target=0x%X", pEffect->GetEffectTarget());
	#endif

	if (pEffect==NULL)
	{
		return;
	}

	//------------------------------------------------------------
	// pEffect�� ������ �����ؼ� Generate�Ѵ�.
	//------------------------------------------------------------
	MEffectTarget* pEffectTarget = pEffect->GetEffectTarget();
	
	//------------------------------------------------------------
	// [ �ʻ�!~ ] ���� Effect�� Link�� �� Effect�� 
	//						EffectTarget�� �����Ѵ�.
	//
	// pEffectTarget�� Generate()���� ���� Effect�� ���޵ǰų�
	//							�̹� loop���� delete�Ǿ�� �Ѵ�.
	//------------------------------------------------------------
	pEffect->SetEffectTargetNULL();

	//------------------------------------------------------------
	// ��ǥ�� ������..
	//------------------------------------------------------------
	if (pEffectTarget==NULL)
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("return-pEffectTarget NULL");
		#endif

		return;
	}

	///*
	// ���� - -;
	// ������ ������ �ǹ��Ѵ�.
	if (pEffectTarget->IsEnd())
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("EffectTarget End - Check Result0");
		#endif

		// ����� ������ ó���ؾ� �Ѵ�.
 		if (pEffectTarget->IsExistResult())
		{
			MActionResult* pResult = pEffectTarget->GetResult();

			pEffectTarget->SetResultNULL();

			#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD("Execute Result0");
			#endif

			// ��� ����
			pResult->Execute();
			
			// �޸� ����
			delete pResult;			
		}
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			else		
			{			
				DEBUG_ADD("NO Result0");				
			}
		#endif
		
		// Player�� �������̴� EffectTarget�� �����ٰ� �����Ѵ�.
		g_pPlayer->RemoveEffectTarget( pEffectTarget->GetEffectID() );

		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("delete EffectTarget0");
		#endif

		delete pEffectTarget;	// ��(!) �̰� �³�??
		//pEffect->SetEffectTargetNULL();

		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("GenerateNext OK0");
		#endif

		return;
	}
	//*/


	// ���° Info�� �ϸ�...
	int nActionInfoNode = pEffectTarget->GetCurrentPhase();		

	
	ACTION_INFO_NODE&			info	= (*g_pActionInfoTable)[ pEffect->GetActionInfo() ][ nActionInfoNode ];

	int targetX = pEffectTarget->GetX();
	int targetY = pEffectTarget->GetY();
	int targetZ = pEffectTarget->GetZ();
	int targetID = pEffectTarget->GetID();
	
	DWORD count;
	
	//------------------------------------------------------------
	// Effect�� �̹� node�� ���� �ð� ����
	//------------------------------------------------------------
	// bDelayNode�̰� ������ delay�� �ִ� ���
	//		//main node�̰� pEffectTarget�� DelayFrame�� 0�� �ƴ� ���
	//------------------------------------------------------------
	if (info.bDelayNode
		//(*g_pActionInfoTable)[ nActionInfo ].HasMainNode()
		//&& pEffectTarget->GetCurrentPhase()==(*g_pActionInfoTable)[ nActionInfo ].GetMainNode()
		&& pEffectTarget->GetDelayFrame()!=0)
	{
		count = pEffectTarget->GetDelayFrame();
	}
	else
	{
		count = info.Count;
	}

	//------------------------------------------------------------
	// ���� ��ǥ
	//------------------------------------------------------------
	pEffectTarget->NextPhase();

	//------------------------------------------------------------
	// EffectGenerator�� �������� ���� ���
	//------------------------------------------------------------
	if (info.EffectGeneratorID >= MAX_EFFECTGENERATORID
		|| m_pEffectGenerator[ info.EffectGeneratorID ]==NULL)
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD_FORMAT("[Error] EGT-Generate id=%d, target=0x%X", info.EffectGeneratorID, pEffectTarget);
		#endif	

		// ��ǥ �Ϸ��Ų��.
		//while (!pEffectTarget->IsEnd())
		//{
		//	pEffectTarget->NextPhase();
		//}

		if (pEffectTarget->IsExistResult())
		{
			pEffectTarget->GetResult()->Release();			
		}

		delete pEffectTarget;
		//pEffect->SetEffectTargetNULL();	// �̰� �ּ� �Ǿ��� ������ ����.. -> ������ ���ֳ� - -;

		return;
	}

	//------------------------------------------------------------
	//
	// EffectGenerator���� Effect�� �����ϰ� �Ѵ�.
	//
	//------------------------------------------------------------
	EFFECTGENERATOR_INFO egInfo;

	egInfo.nActionInfo			= pEffect->GetActionInfo();
	
	// ���������� target�� �Ѱ����� �ʴ´�.
	egInfo.pEffectTarget		= pEffectTarget->IsEnd()? NULL : pEffectTarget;

	egInfo.effectSpriteType		= info.EffectSpriteType;
	egInfo.x0					= pEffect->GetPixelX();
	egInfo.y0					= pEffect->GetPixelY();
	egInfo.z0					= pEffect->GetPixelZ();
	egInfo.x1					= targetX;
	egInfo.y1					= targetY;
	egInfo.z1					= targetZ;
	egInfo.creatureID			= targetID;
	egInfo.direction			= pEffect->GetDirection();
	egInfo.step					= info.Step;
	egInfo.count				= count;
	egInfo.linkCount			= info.LinkCount;
	egInfo.power				= pEffect->GetPower();
	egInfo.pPreviousEffect		= pEffect;
	egInfo.temp1				= 0;
	egInfo.temp2				= 0;

	// Generate
	bool bGenerated = false;

	//------------------------------------------------------------
	// Generate�� return���� egInfo.pEffectTarget�� 
	// ���ο��� �ٸ� effect�� link�Ǿ��°��� �ǹ��Ѵ�.
	//------------------------------------------------------------
	#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
		DEBUG_ADD_FORMAT("Generate before. id=%d", info.EffectGeneratorID);
	#endif	

	if (m_pEffectGenerator[ info.EffectGeneratorID ]->Generate( egInfo ))
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("Generate OK");
		#endif	

		//------------------------------------------------------------
		// ����� �ܰ迡 �´� sound�� ������ش�.
		//------------------------------------------------------------
		if (info.SoundID != SOUNDID_NULL)
		{
			//g_Sound.Play( g_SoundTable[info.SoundID].pDSBuffer );
			POINT point = MTopView::PixelToMap(pEffect->GetPixelX(), pEffect->GetPixelY());
			PlaySound( info.SoundID, false, point.x, point.y );
		}

		//------------------------------------------------------------
		// ����� ó���ؾ��ϴ� �����ΰ�? 
		//------------------------------------------------------------
		if (info.bResultTime)
		{
			// ��� ó�� �ð��� �����ٰ� üũ�Ѵ�.
			// ���߿� ����� ����� �ٷ� ó���ϰ� �ȴ�.
			pEffectTarget->SetResultTime();
		}

		bGenerated = true;
	}
	else
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("Generate false");
		#endif

		pEffectTarget->SetResultTime();
	}

	//------------------------------------------------------------
	// ��� ó��
	//------------------------------------------------------------
	if (pEffectTarget->IsResultTime() 
		|| pEffectTarget->IsEnd()
		|| !bGenerated)
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("Check Result");
		#endif

		// ����� ������ ó���ؾ� �Ѵ�.
 		if (pEffectTarget->IsExistResult())
		{
			MActionResult* pResult = pEffectTarget->GetResult();

			pEffectTarget->SetResultNULL();

			#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
				DEBUG_ADD("Execute Result");
			#endif

			// ��� ����
			pResult->Execute();
			
			// �޸� ����
			delete pResult;
			
			//pEffectTarget
		}
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			else
			{
				DEBUG_ADD("NO Result");
			}
		#endif
		
		// Player�� �������̴� EffectTarget�� �����ٰ� �����Ѵ�.
		g_pPlayer->RemoveEffectTarget( pEffectTarget->GetEffectID() );

		//delete pEffectTarget;
		//pEffect->SetEffectTargetNULL();
	}

	//------------------------------------------------------------
	// �� �̻� ��ǥ�� �ʿ���� ������ �ܰ��� ���..
	//------------------------------------------------------------
	// end�̸� Generate()���� pEffectTarget�� �Ѱ����� �����Ƿ�
	// ���⼭ ������ �Ѵ�.
	if (pEffectTarget->IsEnd() || !bGenerated)
	{
		#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("delete EffectTarget");
		#endif
			
		if (pEffectTarget->IsExistResult())
		{
			MActionResult* pResult = pEffectTarget->GetResult();
			
			pEffectTarget->SetResultNULL();
			
#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
			DEBUG_ADD("Execute Result");
#endif
			
			// ��� ����
			pResult->Execute();
			
			// �޸� ����
			delete pResult;
		}

		delete pEffectTarget;
		//pEffect->SetEffectTargetNULL();
	}	

	#ifdef OUTPUT_DEBUG_EFFECT_GENERATOR
		DEBUG_ADD("GenerateNext OK");
	#endif
}


