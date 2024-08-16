//----------------------------------------------------------------------
// MMultipleFallingEffectGenerator.h
//----------------------------------------------------------------------
// ���ڰ�(+) ������� ����
//----------------------------------------------------------------------

#ifndef	__MMULTIPLEFALLINGEFFECTGENERATOR_H__
#define	__MMULTIPLEFALLINGEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MMultipleFallingEffectGenerator : public MEffectGenerator {
	public :
		MMultipleFallingEffectGenerator() {}
		~MMultipleFallingEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_MULTIPLE_FALLING; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MMultipleFallingEffectGenerator	g_StopZoneCrossEffectGenerator;

#endif

