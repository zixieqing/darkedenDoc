//----------------------------------------------------------------------
// MChaseEffect.h
//----------------------------------------------------------------------
// ChaseEffect�� ��ǥ�� ������� �������� ���� ����. - -;
//----------------------------------------------------------------------

#ifndef	__MCHASEEFFECT_H__
#define	__MCHASEEFFECT_H__

#include "MGuidanceEffect.h"
#include "MTypeDef.h"

class MChaseEffect : public MGuidanceEffect {
	public :
		MChaseEffect(BYTE bltType);
		~MChaseEffect();

		virtual EFFECT_TYPE		GetEffectType()	const	{ return EFFECT_CHASE; }		
		
		//--------------------------------------------------------
		// ���� ��Ȳ?
		//--------------------------------------------------------
		bool				IsChaseOver() const		{ return m_bChaseOver; }

		//--------------------------------------------------------
		// �� ���� Update�� ȣ��� �Լ�..
		//--------------------------------------------------------
		virtual bool		Update();

	protected :
		//--------------------------------------------------------
		// �����ؼ� ���� ��ġ�� �ִ°�?
		//--------------------------------------------------------
		bool				m_bChaseOver;
};

#endif