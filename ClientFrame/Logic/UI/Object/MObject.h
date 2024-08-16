//----------------------------------------------------------------------
// MObject.h
//----------------------------------------------------------------------
// ȭ�鿡 ��µǴ� Object
//----------------------------------------------------------------------
/* class hierachy

      MObject --+-- MCreature ---- MCreatureWear -- MPlayer
				|
				+-- MItem
	            |				
				+-- MImageObject -- MAnimationObject -- MInteractionObject
				|
				+-- MEffect --- ....
	            


*/
//----------------------------------------------------------------------

#ifndef	__MOBJECT_H__
#define	__MOBJECT_H__

class ofstream;
class ifstream;
#include "MTypeDef.h"


class MObject {
	public :
		MObject();
		~MObject()	{}

		BYTE	GetObjectType()	const	{ return m_ObjectType; }

		//--------------------------------------------------------
		// id
		//--------------------------------------------------------
		void			SetID(TYPE_OBJECTID id)	{ m_ID = id; }
		TYPE_OBJECTID	GetID()	const			{ return m_ID; }

		//--------------------------------------------------------
		// Sector������ ��ǥ
		//--------------------------------------------------------
		void		SetPosition(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y)	{ m_X = x; m_Y = y; }
		void		SetX(TYPE_SECTORPOSITION x)		{ m_X = x; }
		void		SetY(TYPE_SECTORPOSITION y)		{ m_Y = y; }
		TYPE_SECTORPOSITION		GetX()	const		{ return m_X; }		// ��ǥX
		TYPE_SECTORPOSITION		GetY()	const		{ return m_Y; }		// ��ǥY

		//------------------------------------------------------
		// ȭ�鿡���� ����
		//------------------------------------------------------
		//extern BOOL g_MyFull;
		/*  edit by coffee 2007-01-01
		void				ClearScreenRect()	
		{ 
			// �ִ�/�ּҰ��� ���ϱ� ���� ���̹Ƿ�.. �Ųٷ� �־�� �Ѵ�.
			// add by Sonic 2006.9.26
			if(g_MyFull)
			{
				m_ScreenRect.left = 1024;	// �ٷ� ���� �������.
				m_ScreenRect.top = 768;		// -_-; �̷��� �ȵ����� ��ġ�� ¯����~
				m_ScreenRect.right = 0;
				m_ScreenRect.bottom = 0;
			}
			else
			{
				m_ScreenRect.left = 800;	// �ٷ� ���� �������.
				m_ScreenRect.top = 600;		// -_-; �̷��� �ȵ����� ��ġ�� ¯����~
				m_ScreenRect.right = 0;
				m_ScreenRect.bottom = 0;
			}
			// end
		}
		*/  //end edit
		void				ClearScreenRect()	
		{
				m_ScreenRect.left = 800;	// �ٷ� ���� �������.
				m_ScreenRect.top = 600;		// -_-; �̷��� �ȵ����� ��ġ�� ¯����~
				m_ScreenRect.right = 0;
				m_ScreenRect.bottom = 0;
		}
		void				AddScreenRect(RECT* pRect);
		void				SetScreenRect(RECT* pRect)	{ m_ScreenRect = *pRect; }
		const RECT&			GetScreenRect() const	{ return m_ScreenRect; }
		BOOL				IsPointInScreenRect(int x, int y) const
		{
			if (x >= m_ScreenRect.left && x < m_ScreenRect.right
				&& y >= m_ScreenRect.top && y < m_ScreenRect.bottom)
			{
				return TRUE;
			}

			return FALSE;
		}

		//--------------------------------------------------------
		// file I/O
		//--------------------------------------------------------
		virtual void	SaveToFile(class ofstream& file);
		virtual void	LoadFromFile(class ifstream& file);

	public :
		//--------------------------------------------------------
		// Object ������ ���� ���� : class ID
		//--------------------------------------------------------
		enum OBJECT_TYPE 
		{
			TYPE_OBJECT = 0,
			TYPE_CREATURE,	
			TYPE_ITEM,			
			TYPE_IMAGEOBJECT,
			TYPE_SHADOWOBJECT,
			TYPE_ANIMATIONOBJECT,
			TYPE_SHADOWANIMATIONOBJECT,
			TYPE_INTERACTIONOBJECT,
			TYPE_PORTAL,
			TYPE_EFFECT			
		};

	protected :
		BYTE				m_ObjectType;	// Object�� ����
		TYPE_OBJECTID		m_ID;			// Object's instance ID
		
		// ��ġ
		TYPE_SECTORPOSITION				m_X, m_Y;		// Sector ��ǥ (pixel���� �ƴ�!)

		// ȭ�鿡���� Sprite�浹 �簢 ����
		RECT					m_ScreenRect;
};

#endif