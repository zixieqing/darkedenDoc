//----------------------------------------------------------------------
// MStopZoneEmptyRectEffectGenerator.h
//----------------------------------------------------------------------
// �簢������ ����
//----------------------------------------------------------------------

#ifndef	__MSTOPZONEEMPTYRECTEFFECTGENERATOR_H__
#define	__MSTOPZONEEMPTYRECTEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MStopZoneEmptyRectEffectGenerator : public MEffectGenerator {
	public :
		MStopZoneEmptyRectEffectGenerator()	{}
		~MStopZoneEmptyRectEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_STOP_ZONE_EMPTY_RECT; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MStopZoneRectEffectGenerator	g_StopZoneRectEffectGenerator;

#endif

