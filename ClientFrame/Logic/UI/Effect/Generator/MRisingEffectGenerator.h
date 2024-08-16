//----------------------------------------------------------------------
// MRisingEffectGenerator.h
//----------------------------------------------------------------------
// �������� �ھƿ����� Effect
//----------------------------------------------------------------------

#ifndef	__MRISINGEFFECTGENERATOR_H__
#define	__MRISINGEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MRisingEffectGenerator : public MEffectGenerator {
	public :
		MRisingEffectGenerator() {}
		~MRisingEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_RISING; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MRisingEffectGenerator	g_RisingEffectGenerator;

#endif

