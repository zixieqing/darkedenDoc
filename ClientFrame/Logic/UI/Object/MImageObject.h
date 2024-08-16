//----------------------------------------------------------------------
// MImageObject.h
//----------------------------------------------------------------------
//
// �ϳ��� �׸��� ���� ����
// 
//  - �׸��� �׸��� Surface�� ����Ǵ� ���� �ƴ϶� 
//    Sprite�� ����ȴ�.  ũ�Ⱑ �پ��ϱ� �����̴�.
//    �翬�� �������, �׸�Sprite�� �簢���̴�.
//    ������� �����ϱ� ������ ������� �׸��̱�� ������...
//
//  - �׸��� ��ġ�� Sector��ǥ�� ǥ���ϱⰡ ����ϴ�.
//    �簢�� �׸��� �ִ� ���� �ƴϱ� ������ �簢������ �ȵȴ�.
//    �׳� Zone���� Pixel������ ��ǥ�� ǥ���ؾ� �Ѵ�.
//    ��, �׸� Sprite�� ��������� ��ġ�� ������ �׸��� ��ġ�̴�.
//
// �׸� �׸��� ���� Zone���� � ��ġ(pixel)�� �׷��� ���̴�.
// �׷��Ƿ�, �浹 check ���� �������� Zone�� Sector�� ǥ���ؾ� �Ѵ�.
//
// �׸��� ���� ���� ���� MTransfer�� Sector�� ǥ���Ǵ� ������
// Ư���� �ٸ� ó���� �ϴ� ���� �ƴϴ�.
//
// �׸��� �׸��� ���� �������� ��µǴ� ���� �ϳ��� Sprite�� ǥ���Ǿ�� �Ѵ�.
//
//----------------------------------------------------------------------
//
// [ Sector�� ���� ���� ]
//
// �׸��� ȭ�鿡 ��µǴ� Sector���� FLAG_SECTOR_BUILDING�� ǥ���Ѵ�.
// �׸��� �ٴ��� ��ġ�ϴ� Sector���� FLAG_SECTOR_BLOCK�� ǥ���Ѵ�.
//
// FLAG_SECTOR_BUILDING�� ǥ�õǾ�����, FLAG_SECTOR_BLOCK�� ǥ�õ���
// ���� ���� Player�� �׸��� �������� �κ��̹Ƿ� �׸��� ������ ó�� �ؾ��Ѵ�.
//----------------------------------------------------------------------
//
// �׸��� ��������� �ϳ��� �׸����� ǥ���Ǳ�� ������,
// ���������δ� ��� Sprite�� ���� �� �ִ�.
// ��, ������ ó���� �� ��, �������� Sprite�� ���ÿ� ������ �Ǿ�� �Ѵ�.
// 
// 
//----------------------------------------------------------------------
// - �ΰ��� Image�� �ϳ��� Object�� ǥ���ؾ��� ��찡 �ִ�.
//   �̶� Object�� �����ϴ°� ImageObjectID�̴�.
//
// - m_ID�� ���� Object�� �ٸ���. ���� �� ����.
//----------------------------------------------------------------------

#ifndef	__MIMAGEOBJECT_H__
#define	__MIMAGEOBJECT_H__

class ofstream;
class ifstream;
#include "MTypeDef.h"
#include "MObject.h"
#include "DrawTypeDef.h"

#define	IMAGEOBJECT_NULL	0xFFFF
#define OBJECT_TRANS_FLAG	1
#define OBJECT_HALF_FLAG	2
//----------------------------------------------------------------------
//
// ImageObject class
//
//----------------------------------------------------------------------
class MImageObject : public MObject {
	public :
		// �̰Ŵ� ��������.. ������ �����Ҷ� ����.
		enum WALL_DIRECTION
		{
			WALL_RIGHTDOWN = 1,		// ���������� ���鼭 �Ʒ��� �������� ��
			WALL_RIGHTUP,			// ���������� ���鼭 ���� �ö󰡴� ��			

			WALL_NULL = SECTORPOSITION_NULL,			// �� ������ �ƴϴ�. - -;			
		};

	public :
		MImageObject();
		MImageObject(TYPE_OBJECTID id, TYPE_OBJECTID ImageObjectID, TYPE_SPRITEID nSprite, int pX, int pY, TYPE_SECTORPOSITION viewpoint, BYTE trans);
		~MImageObject();
		
		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		virtual void	SaveToFile(class ofstream& file);
		virtual void	LoadFromFile(class ifstream& file);

		//-------------------------------------------------------
		// Is...
		//-------------------------------------------------------
		bool	IsAnimation() const		{ return m_bAnimation; }
		bool	IsSame(const MImageObject* pImageObject) const	{ return m_ImageObjectID==pImageObject->m_ImageObjectID; }
		//bool	IsTrans() const			{ return m_bTrans; }
		bool	IsTrans() const			{ return (m_bTrans&OBJECT_TRANS_FLAG)?true:false; }
		bool	IsHalf() const			{ return (m_bTrans&OBJECT_HALF_FLAG)?true:false; }
		//-------------------------------------------------------
		// set				
		//-------------------------------------------------------
		void	Set(TYPE_OBJECTID ImageObjectID, TYPE_SPRITEID SpriteID, int pX, int pY, TYPE_SECTORPOSITION viewpoint, BYTE trans);
		void	SetPixelX(int px)		{ m_PixelX = px; }
		void	SetPixelY(int py)		{ m_PixelY = py; }
		void	SetViewpoint(TYPE_SECTORPOSITION vp)	{ m_Viewpoint = vp; }
		//void	SetTrans()				{ m_bTrans = true; }
		//void	UnSetTrans()				{ m_bTrans = false; }
		void	SetTrans()				{ m_bTrans |= OBJECT_TRANS_FLAG; }
		void	UnSetTrans()				{ m_bTrans &= ~OBJECT_TRANS_FLAG; }
		void	SetHalf()				{ m_bTrans |= OBJECT_HALF_FLAG; }
		void	UnSetHalf()				{ m_bTrans &= ~OBJECT_HALF_FLAG; }

		//-------------------------------------------------------
		// get
		//-------------------------------------------------------
		TYPE_OBJECTID			GetImageObjectID()		{ return m_ImageObjectID; }
		TYPE_SPRITEID	GetSpriteID() const		{ return m_SpriteID; }
		int				GetPixelX()		const	{ return m_PixelX; }
		int				GetPixelY()		const	{ return m_PixelY; }
		TYPE_SECTORPOSITION			GetViewpoint() const	{ return m_Viewpoint; }
		
		//-------------------------------------------------------
		// �׸��� �ִ� Sector�� ���� ����
		//-------------------------------------------------------

		//-------------------------------------------------------
		// �� ������(-_-;)
		//-------------------------------------------------------
		void				SetWall(WALL_DIRECTION wd);
		bool				IsWall() const;
		WALL_DIRECTION		GetWallDirection() const;		
		int					GetWallValue() const;
		bool				IsWallTransPosition(int sX, int sY) const;
		

	protected :

		// Sprite�� �������϶� �� �׸��� �ϳ��� ID�� ������ �ؾ��� ���̴�.
		// ���� �׸����� ��Ÿ���� ID�� �־�� �� ���̴�.
		TYPE_OBJECTID			m_ImageObjectID;

		// SpritePack�� �ִ� Sprite ID
		TYPE_SPRITEID			m_SpriteID;

		// Animation�Ǵ� ���ΰ�?
		bool					m_bAnimation;

		// �׸��� ��µ� Zone���� Pixel��ġ
		int						m_PixelX;
		int						m_PixelY;

		// ��µ� Sector ���� ���� ��ġ
		TYPE_SECTORPOSITION					m_Viewpoint;
		
		// Player�� ���� �� �������� �Ǿ�� �ϴ°�?
		BYTE					m_bTrans;
};


#endif


