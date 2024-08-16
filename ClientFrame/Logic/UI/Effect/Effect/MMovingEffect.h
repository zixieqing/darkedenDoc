//----------------------------------------------------------------------
// MMovingEffect.h
//----------------------------------------------------------------------
//
// Effect�߿��� �����̴� Effect�� �ǹ��Ѵ�.
//
// - ������ Pixel��ǥ�� �߰��� ������.
// - �� Pixel��ǥ�� ���� ���� ��, ������ Sector��ǥ���� Setting����� �Ѵ�.
//
//----------------------------------------------------------------------

#ifndef	__MMOVINGEFFECT_H__
#define	__MMOVINGEFFECT_H__

#include "MEffect.h"

class MMovingEffect : public MEffect {
	public :
		MMovingEffect(BYTE bltType);
		~MMovingEffect();

		virtual EFFECT_TYPE		GetEffectType()	const	{ return EFFECT_MOVING; }

		//--------------------------------------------------------
		// �� ���� Update�� ȣ��� �Լ�..
		//--------------------------------------------------------
		virtual bool	Update();
};

#endif

