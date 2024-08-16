//----------------------------------------------------------------------
// MStopZoneEffectGenerator.h
//----------------------------------------------------------------------
// Zone�� �� ��������  ����
//----------------------------------------------------------------------

#ifndef	__MSTOPZONEEFFECTGENERATOR_H__
#define	__MSTOPZONEEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MStopZoneEffectGenerator : public MEffectGenerator {
	public :
		MStopZoneEffectGenerator() {}
		~MStopZoneEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_STOP_ZONE; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MStopZoneEffectGenerator	g_StopZoneEffectGenerator;

#endif

