//----------------------------------------------------------------------
// MHomingEffect.h
//----------------------------------------------------------------------
// ��� �׸��� ��ǥ�� �ٰ����� effect
//
//             90��
//              |
//              |
//  180��-------+--------0��
//              |
//              |
//             270��
//
//----------------------------------------------------------------------

#ifndef	__MHOMINGEEFFECT_H__
#define	__MHOMINGEEFFECT_H__

#include "MGuidanceEffect.h"
#include "MTypeDef.h"

class MHomingEffect : public MGuidanceEffect {
	public :
		MHomingEffect(BYTE bltType, int currentAngle, int turnAngle);
		~MHomingEffect();
		
		virtual EFFECT_TYPE		GetEffectType()	const	{ return EFFECT_HOMING; }
		
		//--------------------------------------------------------
		// Set Target
		//--------------------------------------------------------
		virtual void		SetTarget(int x, int y, int z, WORD stepPixel);

		//--------------------------------------------------------
		// �� ���� Update�� ȣ��� �Լ�..
		//--------------------------------------------------------
		virtual bool		Update();
		void	SetRadStep(int step);
		void	SetRadCurrent(int step);

	protected :
		void			CalculateAngle();
		void			SetDirectionByAngle();
		virtual bool	TraceCreature();
	
	protected :	
		int			m_RadCurrent;	// ���� �̵��ϴ� ���Ⱒ��
		int			m_RadStep;		// �� turn���� �޶����� radian��
};

#endif