//----------------------------------------------------------------------
// MAttachCreatureEffectGenerator.h
//----------------------------------------------------------------------
// Creature�� �پ������ Effect
//----------------------------------------------------------------------

#ifndef	__MATTACHCREATUREEFFECTGENERATOR_H__
#define	__MATTACHCREATUREEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MAttachCreatureEffectGenerator : public MEffectGenerator {
	public :
		MAttachCreatureEffectGenerator() {}
		~MAttachCreatureEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_ATTACH_CREATURE; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MAttachCreatureEffectGenerator	g_AttachCreatureEffectGenerator;

#endif

