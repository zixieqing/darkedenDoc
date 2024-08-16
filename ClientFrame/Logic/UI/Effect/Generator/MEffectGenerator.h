//----------------------------------------------------------------------
// MEffectGenerator.h
//----------------------------------------------------------------------
//
// = ������ ������ ���ÿ� �߻��ϴ� Effect���� �����ؼ� Zone�� ����ϴ� ���� �Ѵ�.
//
// = �������� Effect���� �����ϰ� Player���� ������ �� ���� �ִ�.
//
// = ����, �����ؼ� Zone�� ����ϴ� ���Ҹ� �Ѵ�. 
//
// = �ϳ��� Effect�� �����ϴµ� �ʿ��� ������
//    - �������(BltType)
//    - �׸�(FrameID)
//    - ����(pX,pY,pZ)
//    - ��ǥ(pX,pY,pZ)
//    - ��ǥCreature(CreatureID)
//    - ����(Direction)
//    - �ӵ�(Step)
//    - ���ӽð�(Count)
//    - ����(Power)
//
//----------------------------------------------------------------------

#ifndef	__MEFFECTGENERATOR_H__
#define	__MEFFECTGENERATOR_H__

#include "MTypeDef.h"
#include "MEffectGeneratorDef.h"
#include "DrawTypeDef.h"
#include "MEffectTarget.h"
class MEffect;

//----------------------------------------------------------------------
// effect�� �����ϴµ� �ʿ��� ������
//----------------------------------------------------------------------
class EFFECTGENERATOR_INFO
{
	public :
		TYPE_ACTIONINFO			nActionInfo;				// �ش��ϴ� �׼� ����
		MEffectTarget*			pEffectTarget;				// ����Ʈ�� ��ǥ
		TYPE_EFFECTSPRITETYPE	effectSpriteType;			// ��������Ʈ Ÿ��
		int						x0, y0, z0;					// ������
		int						x1, y1, z1;					// ��ǥ����		
		TYPE_OBJECTID			creatureID;					// ��� CreatureID
		BYTE					direction;					// ����
		BYTE					step;						// ���� �ӵ�
		WORD					count;						// ���ӽð�
		WORD					linkCount;					// ���� ����Ʈ�� ����� �ð�
		BYTE					power;						// ����
		MEffect*				pPreviousEffect;			// ���� ����Ʈ
		BYTE					temp1,temp2;				// ��Ÿ
};

//----------------------------------------------------------------------
//
//		 Effect Generator
//
//----------------------------------------------------------------------
class MEffectGenerator {
	public :
		MEffectGenerator()	{}
		~MEffectGenerator() {}

		virtual TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_NULL; }

		virtual bool	Generate(	const EFFECTGENERATOR_INFO& egInfo	) = 0;

	protected :
};

#endif
