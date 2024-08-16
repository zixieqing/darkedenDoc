//----------------------------------------------------------------------
// MStopZoneCrossEffectGenerator.h
//----------------------------------------------------------------------
// ���ڰ�(+) ������� ����
//----------------------------------------------------------------------

#ifndef	__MSTOPZONECROSSEFFECTGENERATOR_H__
#define	__MSTOPZONECROSSEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MStopZoneCrossEffectGenerator : public MEffectGenerator {
	public :
		MStopZoneCrossEffectGenerator()	 {}
		~MStopZoneCrossEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_STOP_ZONE_CROSS; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MStopZoneCrossEffectGenerator	g_StopZoneCrossEffectGenerator;

#endif

