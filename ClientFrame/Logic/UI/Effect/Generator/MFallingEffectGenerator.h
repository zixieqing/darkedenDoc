//----------------------------------------------------------------------
// MFallingEffectGenerator.h
//----------------------------------------------------------------------
// �������� �ھƿ����� Effect
//----------------------------------------------------------------------

#ifndef	__MFALLINGEFFECTGENERATOR_H__
#define	__MFALLINGEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MFallingEffectGenerator : public MEffectGenerator {
	public :
		MFallingEffectGenerator()	{}
		~MFallingEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_FALLING; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MFallingEffectGenerator	g_FallingEffectGenerator;

#endif

