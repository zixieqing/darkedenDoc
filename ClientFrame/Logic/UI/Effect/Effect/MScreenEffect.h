//----------------------------------------------------------------------
// MScreenEffect.h
//----------------------------------------------------------------------
//
// Effect�߿��� ȭ����ǥ�� ǥ���Ǵ� Effect�� �ǹ��Ѵ�.
//
// SetScreenPosition()�� �����Ҷ��� Basis������ ��ǥ�������� �����صΰ�
//  --> m_PixelX, m_PixelY
//
// ����Ҷ� SetScreenBasis()�� �����ؼ�..
// GetScreenX,Y�� ����ϸ� ������ ��ǥ�� ���� �� �ִ�.
//
//----------------------------------------------------------------------

#ifndef	__MSCREENEFFECT_H__
#define	__MSCREENEFFECT_H__

#include "MEffect.h"

class MScreenEffect : public MEffect {
	public :
		MScreenEffect(BYTE bltType);
		~MScreenEffect();

		virtual EFFECT_TYPE		GetEffectType()	const	{ return EFFECT_SCREEN; }

		//--------------------------------------------------------
		// ��ǥ ����
		//--------------------------------------------------------
		// ȭ�� ������
		static void		SetScreenBasis(int bx, int by);

		// ȭ�鿡���� ��ǥ
		void			SetScreenPosition(int x, int y);

		//--------------------------------------------------------
		// Get
		//--------------------------------------------------------
		int				GetScreenX()	{ return (int)m_PixelX + m_ScreenBasisX; }
		int				GetScreenY()	{ return (int)m_PixelY + m_ScreenBasisY; }

		//--------------------------------------------------------
		// �� ���� Update�� ȣ��� �Լ�..
		//--------------------------------------------------------
		virtual bool	Update();

	public :
		// ȭ����ǥ ������
		static	int		m_ScreenBasisX;
		static	int		m_ScreenBasisY;
};

#endif

