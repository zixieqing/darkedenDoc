//----------------------------------------------------------------------
// MAnimationObject.h
//----------------------------------------------------------------------
//
// �ϳ��� �׸�+�ִ�Frame�� ���� ����
// 
//----------------------------------------------------------------------
//
// MImageObject�� �ܼ��� �ϳ��� Sprite�θ� ǥ���ȴ�.
// ���δ� Animation�� �Ǵ� ImageObject�� ������ ���� �;.. *_*;
//
//    SpriteID + FrameID �ν� Animation�Ǵ� Object�� ǥ���Ѵ�.
//    ���⼭.. SpriteID�� �⺻ Frame�� �ǰ�.. 
//             FrameID�� �ִ� Frame�� �ȴ�.
//    
//  ��, ����Ҷ�.. �� SpriteID�� ��µǰ�.. 
//                 FrameID�� ���� SpriteID�� �ϳ� ��µȴٴ� ���̴�.
//
//----------------------------------------------------------------------

#ifndef	__MANIMATIONOBJECT_H__
#define	__MANIMATIONOBJECT_H__

#include <Windows.h>
class ofstream;
class ifstream;
#include "MTypeDef.h"
#include "MImageObject.h"
#include "CAnimationFrame.h"
#include "ShowTimeChecker.h"

//----------------------------------------------------------------------
//
// ImageObject class
//
//----------------------------------------------------------------------
class MAnimationObject : public MImageObject, public CAnimationFrame, public ShowTimeChecker {
	public :
		MAnimationObject();
		MAnimationObject(TYPE_OBJECTID id, TYPE_OBJECTID ImageObjectID, TYPE_SPRITEID nSprite, int pX, int pY, TYPE_SECTORPOSITION viewpoint, bool trans, BYTE bltType=BLT_NORMAL);
		~MAnimationObject();


		void	Set(TYPE_OBJECTID id, TYPE_OBJECTID ImageObjectID, TYPE_SPRITEID nSprite, int pX, int pY, TYPE_SECTORPOSITION viewpoint, bool trans, BYTE bltType=BLT_NORMAL);

		void	NextFrame();
		void	SetDirection(BYTE dir) 	{ m_Direction = dir; }
		BYTE	GetDirection() const	{ return m_Direction; }

		//-------------------------------------------------------
		// Sound
		//-------------------------------------------------------
		bool			IsSoundFrame() const			{ return m_SoundFrame==m_CurrentFrame; }
		void			SetSoundFrame(BYTE fr)			{ m_SoundFrame = fr; }
		BYTE			GetSoundFrame() const			{ return m_SoundFrame; }
		void			SetSoundID(TYPE_SOUNDID id)		{ m_SoundID = id; }
		TYPE_SOUNDID	GetSoundID() const				{ return m_SoundID; }

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		virtual void	SaveToFile(class ofstream& file);
		virtual void	LoadFromFile(class ifstream& file);

		static void		NextLoopFrame()					{ LoopFrameCount++; }
		
	protected :
		static DWORD	LoopFrameCount;
		BYTE			m_Direction;

		BYTE			m_SoundFrame;	// �Ҹ��� ��µǴ� frame
		TYPE_SOUNDID	m_SoundID;
};


#endif
