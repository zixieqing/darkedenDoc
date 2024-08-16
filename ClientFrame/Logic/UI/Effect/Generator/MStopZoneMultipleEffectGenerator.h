//----------------------------------------------------------------------
// MStopZoneMultipleEffectGenerator.h
//----------------------------------------------------------------------
// ���ڰ�(+) ������� ����
//----------------------------------------------------------------------

#ifndef	__MSTOPZONEMULTIPLEEFFECTGENERATOR_H__
#define	__MSTOPZONEMULTIPLEEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MStopZoneMultipleEffectGenerator : public MEffectGenerator {
	public :
		MStopZoneMultipleEffectGenerator() {}
		~MStopZoneMultipleEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_STOP_ZONE_MULTIPLE; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MMultipleFallingEffectGenerator	g_StopZoneCrossEffectGenerator;

#endif

