//----------------------------------------------------------------------
// MParabolaEffect.h
//----------------------------------------------------------------------
// �������� �׸��� Effect
//----------------------------------------------------------------------

#ifndef	__MPARABOLAEFFECT_H__
#define	__MPARABOLAEFFECT_H__


#include "MLinearEffect.h"

#define	PI	3.14159265


class MParabolaEffect : public MLinearEffect {
	public :
		MParabolaEffect(BYTE bltType);
		~MParabolaEffect(); 

		virtual EFFECT_TYPE		GetEffectType()	const	{ return EFFECT_PARABOLA; }

		//--------------------------------------------------------
		// ���ο� ��ǥ ����
		//--------------------------------------------------------
		virtual void		SetTarget(int x, int y, int z, WORD stepPixel);
		
		//--------------------------------------------------------
		// �� ���� Update�� ȣ��� �Լ�..
		//--------------------------------------------------------
		virtual bool		Update();

		void				MakeCannonadeSmoke();
		void				SetTargetTile(int x, int y) {	m_TargetTileX = x; m_TargetTileY = y;	}
	protected :	
		int			m_RadCurrent;	// ���� radian��
		int			m_RadStep;		// �� turn���� �޶����� radian��
		TYPE_SECTORPOSITION m_TargetTileX;
		TYPE_SECTORPOSITION m_TargetTileY;
};


#endif

