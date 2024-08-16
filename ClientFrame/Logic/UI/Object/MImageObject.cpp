//----------------------------------------------------------------------
// MImageObject.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MObject.h"
#include "MImageObject.h"

#ifdef __GAME_CLIENT__
	#include "MTopView.h"
#endif


//----------------------------------------------------------------------
// Init Static Members
//----------------------------------------------------------------------
//TYPE_OBJECTID	MImageObject::s_ID	= 0;

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------
MImageObject::MImageObject()
{
	// type
	m_ObjectType	= TYPE_IMAGEOBJECT;	

	m_bAnimation	= false;

	// ImageObject�� m_X�� �� ���� ������.. �ӽ÷�(�Ƹ� ������.. -_-;) ����Ѵ�.
	m_X	= WALL_NULL;
}

MImageObject::MImageObject(TYPE_OBJECTID id, TYPE_OBJECTID ImageObjectID, TYPE_SPRITEID SpriteID, int pX, int pY, TYPE_SECTORPOSITION viewpoint, BYTE trans)
{
	// instace ID�߱�
	m_ID			= id;

	// type
	m_ObjectType	= TYPE_IMAGEOBJECT;	
	m_ImageObjectID = ImageObjectID;

	m_bAnimation	= false;

	// data
	m_SpriteID		= SpriteID;
	m_PixelX		= pX;
	m_PixelY		= pY;	
	m_Viewpoint		= viewpoint;
	m_bTrans		= trans;
}

MImageObject::~MImageObject() 
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Set
//----------------------------------------------------------------------
void
MImageObject::Set(TYPE_OBJECTID ImageObjectID, TYPE_SPRITEID SpriteID, int pX, int pY, TYPE_SECTORPOSITION viewpoint, BYTE trans)
{
	m_ImageObjectID = ImageObjectID;
	m_SpriteID		= SpriteID;
	m_PixelX		= pX;
	m_PixelY		= pY;	
	m_Viewpoint		= viewpoint;
	m_bTrans		= trans;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void	
MImageObject::SaveToFile(ofstream& file)
{
	MObject::SaveToFile(file);	

	file.write((const char*)&m_ImageObjectID, SIZE_OBJECTID);
	file.write((const char*)&m_SpriteID, SIZE_SPRITEID);
	file.write((const char*)&m_PixelX, 4);
	file.write((const char*)&m_PixelY, 4);
	file.write((const char*)&m_Viewpoint, SIZE_SECTORPOSITION);
	file.write((const char*)&m_bAnimation, 1);
	file.write((const char*)&m_bTrans, 1);
}
		
//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
void	
MImageObject::LoadFromFile(ifstream& file)
{
	MObject::LoadFromFile(file);

	file.read((char*)&m_ImageObjectID, SIZE_OBJECTID);
	file.read((char*)&m_SpriteID, SIZE_SPRITEID);
	file.read((char*)&m_PixelX, 4);
	file.read((char*)&m_PixelY, 4);
	file.read((char*)&m_Viewpoint, SIZE_SECTORPOSITION);
	file.read((char*)&m_bAnimation, 1);
	file.read((char*)&m_bTrans, 1);
}

//----------------------------------------------------------------------
// Set Wall
//----------------------------------------------------------------------
// m_X���� WallDirection
// m_Y���� WallValue�� �����Ѵ�.
//----------------------------------------------------------------------
void				
MImageObject::SetWall(WALL_DIRECTION wd)//, int x, int y)
{
	m_X = wd;

	/*
	switch (m_X)
	{
		//-------------------------------------------------------------
		// ���������� ���鼭 �Ʒ��� �������� ��
		//-------------------------------------------------------------
		case WALL_RIGHTDOWN :
			// x - y ���� ����Ǿ������Ƿ�..
			// ���� �����ϼ��� �ִ�. (m_Y�� unsigned�̴�. - -;)
			m_Y = x - y;
		break;

		//-------------------------------------------------------------
		// ���������� ���鼭 ���� �ö󰡴� ��
		//-------------------------------------------------------------
		case WALL_RIGHTUP :
			// x + y �� ��
			m_Y = x + y;
		break;
	}
	*/
}

//----------------------------------------------------------------------
// Is Wall
//----------------------------------------------------------------------
bool				
MImageObject::IsWall() const
{
	return m_X != WALL_NULL;
}

//----------------------------------------------------------------------
// Get Wall Direction
//----------------------------------------------------------------------
MImageObject::WALL_DIRECTION		
MImageObject::GetWallDirection() const
{
	return (MImageObject::WALL_DIRECTION)m_X;
}

//----------------------------------------------------------------------
// Is Trans Position
//----------------------------------------------------------------------
// player�� sector��ǥ (sX,sY)�� ������ �� Object�� ������ �Ǵ°�?
//
// WALL_RIGHTDOWN ������ ��,
//			value = x-y
//			sX-sY�� value���� ū ��찡 ������ �ȴ�.
//
// WALL_RIGHTUP ������ ��,
//			value = x+y
//			sX+sY�� value���� ���� ��� ������ �ȴ�.
//
//----------------------------------------------------------------------
bool
MImageObject::IsWallTransPosition(int sX, int sY) const
{
	#ifdef __GAME_CLIENT__			
		switch (m_X)
		{
			//-------------------------------------------------------------
			// ���������� ���鼭 �Ʒ��� �������� ��
			//-------------------------------------------------------------
			case WALL_RIGHTDOWN :
			{
				// imageObject�� sector X��ǥ
				int objectSX = MTopView::PixelToMapX( m_PixelX );
		
				// x - y
				int value = objectSX - (int)m_Viewpoint;			
				
				if (sX-sY > value)
				{
					return true;
				}

				return false;
			}
			break;

			//-------------------------------------------------------------
			// ���������� ���鼭 ���� �ö󰡴� ��
			//-------------------------------------------------------------
			case WALL_RIGHTUP :
			{
				// imageObject�� sector X��ǥ
				int objectSX = MTopView::PixelToMapX( m_PixelX );
				
				// x + y
				int value = objectSX + (int)m_Viewpoint;			

				if (sX+sY < value)
				{
					return true;
				}

				return false;
			}
			break;
		}
	#endif

	return true;
}