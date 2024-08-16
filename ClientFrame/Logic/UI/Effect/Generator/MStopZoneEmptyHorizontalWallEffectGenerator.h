//----------------------------------------------------------------------
// MStopZoneEmptyHorizontalWallEffectGenerator.h
//----------------------------------------------------------------------
// Zone�� �� ��������  ����
//----------------------------------------------------------------------

#ifndef	__MSTOPZONEEMPTYHORIZONTALWALLEEFFECTGENERATOR_H__
#define	__MSTOPZONEEMPTYHORIZONTALWALLEEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MStopZoneEmptyHorizontalWallEffectGenerator : public MEffectGenerator {
	public :
		MStopZoneEmptyHorizontalWallEffectGenerator() {}
		~MStopZoneEmptyHorizontalWallEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_STOP_ZONE_EMPTY_HORIZONTAL_WALL; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

#endif

