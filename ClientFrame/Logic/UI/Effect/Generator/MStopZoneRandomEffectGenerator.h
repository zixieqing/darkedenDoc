//----------------------------------------------------------------------
// MStopZoneRandomEffectGenerator.h
//----------------------------------------------------------------------
// �߽ɿ��� ������� ������(?) ��ġ��
// 4���� Effect�� ��½�Ų��.
//----------------------------------------------------------------------

#ifndef	__MSTOPZONERANDOMEFFECTGENERATOR_H__
#define	__MSTOPZONERANDOMEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MStopZoneRandomEffectGenerator : public MEffectGenerator {
	public :
		MStopZoneRandomEffectGenerator() {}
		~MStopZoneRandomEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_STOP_ZONE_RANDOM; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

//
//extern MStopZoneRandomEffectGenerator	g_StopZoneCrossEffectGenerator;

#endif

