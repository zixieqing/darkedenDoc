//----------------------------------------------------------------------
// MFollowPathEffectGenerator.h
//----------------------------------------------------------------------
// Zone�� �� ��������  ����
//----------------------------------------------------------------------

#ifndef	__MFOLLOWPATHEFFECTGENERATOR_H__
#define	__MFOLLOWPATHEFFECTGENERATOR_H__

#include "MEffectGenerator.h"

class MFollowPathEffectGenerator : public MEffectGenerator {
	public :
		MFollowPathEffectGenerator()	{}
		~MFollowPathEffectGenerator() {}

		TYPE_EFFECTGENERATORID		GetID()		{ return EFFECTGENERATORID_FOLLOW_PATH; }

		// Effect����
		bool	Generate( const EFFECTGENERATOR_INFO& egInfo );
};

#endif

