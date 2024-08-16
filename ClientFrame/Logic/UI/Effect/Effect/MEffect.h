//----------------------------------------------------------------------
// MEffect.h
//----------------------------------------------------------------------
// ȭ�鿡 ��µǴ� Effect
//----------------------------------------------------------------------
//
// < Effect��? >
//   - ȭ�鿡�� �������� ȿ��.
//   - ĳ����, ������, �ǹ�, ��ֹ�.. ���� ������ �͵� ��(���� ��������)����
//     Animation�� �Ǵ� �͵��� ���Ѵ�.
//   - Effect�� ��� CAlphaSprite�� �̿��ؼ� ����ä�κ���~���� ǥ���Ѵ�.
//   - ĳ���Ͱ� Į~�� �ֵѷ��� ���� �˱⳪ �ź��� ������ ������
//     ���⼭ ���ϴ� Effect�� ���Ե��� �ʴ´�.
//   - Effect�� �������� �ϳ��� ��ü��� �� �� �ִ�.
//
//
// < Effect�� ���� >
//   = �̻��� ��
//     - Pixel������ ������.
//     - �߻���ġ���� --> ��ǥ��ġ���� Animation�Ǹ鼭 
//       ���� �ӵ�(pixel)�� �̵���
//     - �����̻����� ���� �ƴ� ��찡 ����.
//     - ��ֹ�, ĳ����, �ǹ� � �ε����� �Ҹ�� ���� ����.
//     - ��ǥ��ġ�� �����ϸ� �Ҹ�.
//            
//   = Tile���� ��
//     - Ư�� Tile���� Animation��.
//     - ũ��� Tile���� Ŀ�� �������.
//     - ��� ������ �� Tile���� ���� ���߿� ����Ѵ�.
//     - ���� Frame�� ������ �Ҹ�.
//         
//----------------------------------------------------------------------
// - ��� Effect�� Zone�� �� Sector���� ���ؾ� �� ���̴�.
//   ��� ������ y��ǥ�� Sort�ž��ϱ� ������, Sector�� Object��¿� ���߾�
//   ����ϱ� ���ؼ�.. Sector�� �ֱ�� ����..
//
// - Effect�� ���� �ð� ���ӵȴ�. 
//   ��, Counter�� �ξ 0�� �Ǹ� ��������...
//----------------------------------------------------------------------
//
//              Effect�� File�� ������� �ʴ´�.
//
//----------------------------------------------------------------------
/* class hierarchy


      MEffect --+-- MMovingEffect ---- ....	            
								


   MEffect : Tile�� ������ Effect
*/
//----------------------------------------------------------------------

#ifndef	__MEFFECT_H__
#define	__MEFFECT_H__

#pragma warning(disable:4786)

#include "FrameLib\CAnimationFrame.h"
#include "MTypeDef.h"
#include "MObject.h"
#include "MEffectTarget.h"

class ofstream;
class ifstream;


extern DWORD	g_CurrentFrame;


class MEffect : public MObject, public CAnimationFrame {
	
	public :
		enum EFFECT_TYPE 
		{
			EFFECT_SECTOR = 0,		// Sector�� ���� 
			EFFECT_MOVING,			// �����̴� Effect
			EFFECT_LINEAR,			// ���� �̵�
			EFFECT_GUIDANCE,		// ����(����)�ϰ� ����
			EFFECT_HOMING,			// ����� ����ź
			EFFECT_PARABOLA,		// ������
			EFFECT_ATTACH,			// (ĳ���Ϳ�) ����
			EFFECT_SCREEN,			// ȭ����ǥ�� ǥ��
			EFFECT_CHASE,			// �����ϸ鼭 ��� �پ� �ٴ�
			EFFECT_ATTACH_ORBIT,	// ĳ���Ϳ� �پ ����~ ���鼭 �پ�ٴ�
		};

	public :
		MEffect(BYTE bltType);
		~MEffect();

		//--------------------------------------------------------
		// Set FrameID
		//--------------------------------------------------------
		void			SetFrameID(TYPE_FRAMEID FrameID, BYTE max);

		//--------------------------------------------------------
		// GetEffectType
		//--------------------------------------------------------
		virtual EFFECT_TYPE		GetEffectType()	const	{ return EFFECT_SECTOR; }

		void SetEst( int est ) { m_est = est; }
		int GetEst() const { return m_est; }
		//--------------------------------------------------------
		//	Is Selectable
		//--------------------------------------------------------
		virtual bool		IsSelectable() const		{ return false; }		

		//--------------------------------------------------------
		// ������ �ð�...
		//--------------------------------------------------------		
		// ���� �ð� + last���� �۵�		
		void			SetCount(DWORD last, DWORD linkCount=0xFFFF);
		DWORD			GetEndFrame() const			{ return m_EndFrame; }
		DWORD			GetEndLinkFrame() const		{ return m_EndLinkFrame; }
		bool			IsEnd() const				{ return g_CurrentFrame >= m_EndFrame; }

		
		//--------------------------------------------------------
		// �� ���� Update�� ȣ��� �Լ�..
		//--------------------------------------------------------
		virtual bool	Update();
		
		//--------------------------------------------------------
		// Sector������ ��ǥ
		//--------------------------------------------------------	
		void			SetPosition(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y);
		void			SetX(TYPE_SECTORPOSITION x);
		void			SetY(TYPE_SECTORPOSITION y);
		void			SetZ(int z)						{ m_PixelZ = (float)z; }
		void			SetDirection(BYTE d)			{ m_Direction = d; }
		BYTE			GetDirection() const			{ return m_Direction; }
		void			SetLight(char light)			{ m_Light = light; }

	
		//--------------------------------------------------------
		// Pixel ��ǥ ����
		//--------------------------------------------------------
		void			SetPixelPosition(int x, int y, int z);

		//--------------------------------------------------------
		// Get Functions
		//--------------------------------------------------------
		char			GetLight() const	{ return m_Light; }
		virtual int		GetPixelX() const	{ return (int)m_PixelX; }
		virtual int		GetPixelY() const	{ return (int)m_PixelY; }
		virtual int		GetPixelZ() const	{ return (int)m_PixelZ; }

		//--------------------------------------------------------
		// Power
		//--------------------------------------------------------
		void			SetPower(BYTE power)	{ m_Power = power; }
		BYTE			GetPower() const		{ return m_Power; }

		//--------------------------------------------------------
		// Step
		//--------------------------------------------------------
		void			SetStepPixel(WORD step)	{ m_StepPixel=step; }
		WORD			GetStepPixel() const	{ return m_StepPixel; }

		//--------------------------------------------------------
		// Effect ������ ���� ����
		//--------------------------------------------------------
		void			SetLink(TYPE_ACTIONINFO nActionInfo, MEffectTarget* pEffectTarget);		

		void			SetEffectTargetNULL();

		// �� ��° ActionInfo�ΰ�?
		TYPE_ACTIONINFO	GetActionInfo()	const { return m_nActionInfo; }

		// ���� Effect������ return�Ѵ�.
		MEffectTarget*	GetEffectTarget()		{ return m_pEffectTarget; }
		int				GetLinkSize()			{ return (m_pEffectTarget==NULL || m_pEffectTarget->IsEnd())? 0 : m_pEffectTarget->GetCurrentPhase(); }	

		void			SetMulti(bool bMulti)	{ m_bMulti = bMulti; }
		const bool		IsMulti()				{ return m_bMulti; }

		void			SetDelayFrame(DWORD frame);
		bool			IsDelayFrame() const;

		// 2004, 10, 15, sobeit add start - ����Ʈ ������ ��ٸ���.
		void			SetWaitFrame(DWORD frame);
		bool			IsWaitFrame() const;
		// 2004, 10, 15, sobeit add end

		// 2004, 9, 30, sobeit add start - �������� ����..
		bool			IsSkipDraw() const			{ return m_bDrawSkip; }
		void			SetDrawSkip(bool bSkip)		{ m_bDrawSkip = bSkip;}
		// 2004, 9, 30, sobeit add end
	protected :
		// PixelPositon���μ� Sector��ǥ�� �����Ѵ�.
		void			AffectPosition();



	protected :
		DWORD					m_DelayFrame;
		
		int	m_est;

		// ������ �ð�
		DWORD					m_EndFrame;
		DWORD					m_EndLinkFrame;	// ���� link�� �Ѿ�� frame
		
		BYTE					m_Direction;	// ����

		// Effect�� ��� 
		char					m_Light;

		// Effect�� �����ϴ� Zone������ Pixel��ǥ(���� ��ġ)
		float			m_PixelX;
		float			m_PixelY;
		float			m_PixelZ;
		WORD			m_StepPixel;

		BYTE			m_Power;

		// ���� Effect���� ������ ���� ����
		TYPE_ACTIONINFO			m_nActionInfo;
		MEffectTarget*			m_pEffectTarget;

		static TYPE_OBJECTID	s_ID;			// ID�߱��� ����...

		// �ߺ� �����Ѱ�
		bool			m_bMulti;

		bool			m_bDrawSkip;
		DWORD			m_dwWaitFrame;
};

//----------------------------------------------------------------------
// MSelectableEffect - ���콺�� ���õǴ� effect
//----------------------------------------------------------------------
class MSelectableEffect : public MEffect {
	public :
		MSelectableEffect(BYTE bltType) : MEffect(bltType) {}
		~MSelectableEffect() {}

		//--------------------------------------------------------
		//	Is Selectable
		//--------------------------------------------------------
		bool		IsSelectable() const		{ return true; }		
};

#endif



