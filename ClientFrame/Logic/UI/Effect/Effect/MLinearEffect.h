//----------------------------------------------------------------------
// MLinearEffect.h
//----------------------------------------------------------------------

#ifndef	__MLINEAREFFECT_H__
#define	__MLINEAREFFECT_H__

#include "MMovingEffect.h"

class MLinearEffect : public MMovingEffect {
	public :
		MLinearEffect(BYTE bltType);
		~MLinearEffect();

		virtual EFFECT_TYPE		GetEffectType()	const	{ return EFFECT_LINEAR; }

		//--------------------------------------------------------
		// ���ο� ��ǥ ����
		//--------------------------------------------------------
		virtual void		SetTarget(int x, int y, int z, WORD stepPixel);
		
		//--------------------------------------------------------
		// �� ���� Update�� ȣ��� �Լ�..
		//--------------------------------------------------------
		virtual bool		Update();
	

	protected :
		// ��ǥ ��ǥ
		int			m_TargetX;
		int			m_TargetY;
		int			m_TargetZ;

		// �� ���� �̵��ϴ� pixel��
		float		m_StepX;
		float		m_StepY;
		float		m_StepZ;		
	
		// �̵��ؾ��ϴ� ��ü �Ÿ�(pixel)
		float		m_Len;	
};

#endif

