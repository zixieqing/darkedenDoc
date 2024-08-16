//----------------------------------------------------------------------
// MAttackCreatureHomingEffectGenerator.h
//----------------------------------------------------------------------
// ������� Creature ����
//----------------------------------------------------------------------

#ifndef	__MATTACKCREATUREHOMINGEFFECTGENERATOR_H__
#define	__MATTACKCREATUREHOMINGEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MAttackCreatureHomingEffectGenerator : public MEffectGenerator {
	public :
		MAttackCreatureHomingEffectGenerator()	{}
		~MAttackCreatureHomingEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_ATTACK_CREATURE_HOMING; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MAttackCreatureHomingEffectGenerator	g_AttackCreatureHomingEffectGenerator;

#endif

