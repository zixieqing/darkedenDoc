//----------------------------------------------------------------------
// MSector.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#pragma warning(disable:4786)

#include "MObject.h"
#include "MItem.h"
#include "MCreature.h"
#include "MImageObject.h"
#include "MEffect.h"
#include "MSector.h"
#include "MTopView.h"
#include "EffectSpriteTypeDef.h"
#include <fstream.h>

//----------------------------------------------------------------------
//
// constructor/destructor
//
//----------------------------------------------------------------------
MSector::MSector(TYPE_SPRITEID	spriteID)
{
	m_SpriteID = spriteID;

	m_fProperty		= 0;

	// ���� Sector�� �����ϴ� Object���� ����
	m_nImageObject	= 0;

	//m_FilterSpriteID = SPRITEID_NULL;

	m_Light = 0;

	m_fProperty2 = 0;

	m_bDarkness = false;
	m_bSanctuary = false;	// [�����]
	m_bGroundElemental = false;	// [�����]
	m_bDarknessForbidden = false;	// [�����]

	m_nGroundCreature = 0;
	m_nUndergroundCreature = 0;
	m_nFlyingCreature = 0;
	m_bVisitedFlag = false;
	m_bFuryOfGnome = false;
	m_bDisableTileImage = false;
}

MSector::~MSector()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
void	
MSector::Set(TYPE_SPRITEID spriteID, BYTE fObject)
{ 
	m_SpriteID	= spriteID;
	m_fProperty	= fObject;

	// m_mapObject.clear();
}

//----------------------------------------------------------------------
// Remove All Object
//----------------------------------------------------------------------
void	
MSector::RemoveAllObject()	
{ 
	m_mapObject.clear(); 
	m_nImageObject;
	m_fProperty = 0; 
	m_fProperty2 = 0;

	m_nGroundCreature = 0;
	m_nUndergroundCreature = 0;
	m_nFlyingCreature = 0;
}

//----------------------------------------------------------------------
// Save to File
//----------------------------------------------------------------------
// SpriteID�� BlockFlag, Light�� �����Ѵ�.
//----------------------------------------------------------------------
void	
MSector::SaveToFile(ofstream& file)
{
	BYTE flag = 0;

	// Underground BLOCK flag�� ���� ���
	if (m_fProperty & FLAG_SECTOR_BLOCK_UNDERGROUND)
	{
		// BLOCK flag �ϳ��� �����Ѵ�.
		flag |= FLAG_SECTOR_BLOCK_UNDERGROUND;
	}

	// Ground BLOCK flag�� ���� ���
	if (m_fProperty & FLAG_SECTOR_BLOCK_GROUND)
	{
		// BLOCK flag �ϳ��� �����Ѵ�.
		flag |= FLAG_SECTOR_BLOCK_GROUND;
	}

	// Flying BLOCK flag�� ���� ���
	if (m_fProperty & FLAG_SECTOR_BLOCK_FLYING)
	{
		// BLOCK flag �ϳ��� �����Ѵ�.
		flag |= FLAG_SECTOR_BLOCK_FLYING;
	}

	// Portal flag�� ���� ���
	if (m_fProperty & FLAG_SECTOR_PORTAL)
	{
		// BLOCK flag �ϳ��� �����Ѵ�.
		flag |= FLAG_SECTOR_PORTAL;
	}
	

	file.write((const char*)&m_SpriteID, SIZE_SPRITEID);
	file.write((const char*)&flag, 1);
	file.write((const char*)&m_Light, 1);
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
// SpriteID�� Block Flag, Light�� Load�ȴ�.
//----------------------------------------------------------------------
void	
MSector::LoadFromFile(ifstream& file)
{
	//----------------------------------------
	// Object list�� �ʱ�ȭ�ؾ� �Ǵµ�....
	// Load�ϰ� Object�߰��ϰ�
	// �ٽ� Load�ϴ� ��찡 ���ٰ� ����..
	// �ӵ� ������, �ʱ�ȭ���� �ʴ´�.
	//----------------------------------------
	// m_listObject.clear();

	file.read((char*)&m_SpriteID, SIZE_SPRITEID);
	file.read((char*)&m_fProperty, 1);
	file.read((char*)&m_Light, 1);
}


//----------------------------------------------------------------------
// Assign Operator
//----------------------------------------------------------------------
// Tile�� ����
// Block Flag�� ���Եȴ�.
//----------------------------------------------------------------------
void	
MSector::operator = (const MSector& sector)
{
	m_SpriteID = sector.m_SpriteID;

	// undeground block
	if (sector.m_fProperty & FLAG_SECTOR_BLOCK_UNDERGROUND)
		m_fProperty |= FLAG_SECTOR_BLOCK_UNDERGROUND;

	// ground block
	if (sector.m_fProperty & FLAG_SECTOR_BLOCK_GROUND)
		m_fProperty |= FLAG_SECTOR_BLOCK_GROUND;

	// flying block
	if (sector.m_fProperty & FLAG_SECTOR_BLOCK_FLYING)
		m_fProperty |= FLAG_SECTOR_BLOCK_FLYING;
}

//----------------------------------------------------------------------
// Can Stand UndergroundCreature
//----------------------------------------------------------------------
// �� Sector�� UndergroundCreature�� �� �� �ִ����� ���� check
//----------------------------------------------------------------------
// Block�̸� false
// UndergroundCreature�� ������ false
// �ƴϸ� true
//----------------------------------------------------------------------
bool
MSector::CanStandUndergroundCreature() const
{
	if (m_fProperty & FLAG_SECTOR_BLOCK_UNDERGROUND		
		|| m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE
		|| m_fProperty2 & FLAG_SECTOR_BLOCK_SERVER_UNDERGROUND)
		return false;

	return true;
}

//----------------------------------------------------------------------
// Can Stand Creature
//----------------------------------------------------------------------
// �� Sector�� Creature�� �� �� �ִ����� ���� check
//----------------------------------------------------------------------
// Block�̸� false
// Creature�� ������ false
// �ƴϸ� true
//----------------------------------------------------------------------
bool
MSector::CanStandGroundCreature() const
{
	if (m_fProperty & FLAG_SECTOR_BLOCK_GROUND	
		|| m_fProperty & FLAG_SECTOR_GROUNDCREATURE
		|| m_fProperty2 & FLAG_SECTOR_BLOCK_SERVER_GROUND)
		return false;

	return true;
}


//----------------------------------------------------------------------
// Can Stand FlyingCreature
//----------------------------------------------------------------------
// �� Sector�� FlyingCreature�� �� �� �ִ����� ���� check
//----------------------------------------------------------------------
// Block�̸� false
// FlyingCreature�� ������ false
// �ƴϸ� true
//----------------------------------------------------------------------
bool
MSector::CanStandFlyingCreature() const
{
	if (m_fProperty & FLAG_SECTOR_BLOCK_FLYING
		|| m_fProperty & FLAG_SECTOR_FLYINGCREATURE
		|| m_fProperty2 & FLAG_SECTOR_BLOCK_SERVER_FLYING)		
		return false;

	return true;
}



//----------------------------------------------------------------------
// 
//                        Add Object
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Add Item
//----------------------------------------------------------------------
// �̹� Item�� ������ �߰��� �� ����.
// Item�� �߰��� �� ������ pItem�� �߰��ϰ�
// Item Flag�� check���ش�.
//----------------------------------------------------------------------
bool	
MSector::AddItem(const MItem* pItem)
{
	// �̹� Item�� ������.. �߰� �Ұ���
	if (m_fProperty & FLAG_SECTOR_ITEM)
		return false;

	// Item�� ��ġ�� Item�� �߰��Ѵ�.
	m_mapObject.insert( OBJECT_MAP::value_type(POSITION_ITEM, (MObject*)pItem) );

	// Item Flag�� check���ش�.
	m_fProperty |= FLAG_SECTOR_ITEM;
	if( pItem->GetItemClass() == ITEM_CLASS_CORPSE )
	{
		const MCorpse* pCorpse = dynamic_cast<const MCorpse*>(pItem);
		if( pCorpse == NULL || pCorpse->GetCreature() == NULL )
			return true;

		const MCreature* pCreature = pCorpse->GetCreature();

		if( pCreature->GetCreatureType() == 672 )
			m_fProperty |= FLAG_SECTOR_BLOCK_GROUND;
	}

	return true;
}

//----------------------------------------------------------------------
// Add UndergroundCreature
//----------------------------------------------------------------------
// �̹� UndergroundCreature�� ������ �߰��� �� ����.
// UndergroundCreature�� �߰��� �� ������ pUndergroundCreature�� �߰��ϰ�
// UndergroundCreature Flag�� check���ش�.
//----------------------------------------------------------------------
bool	
MSector::AddUndergroundCreature(const MCreature* pUndergroundCreature)
{
	// �̹� UndergroundCreature�� ������.. �߰� �Ұ���
	//if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	//	return false;

	BYTE pos = POSITION_UNDERGROUNDCREATURE+m_nUndergroundCreature;

	if (pos > POSITION_UNDERGROUNDCREATURE_MAX)
		return false;
	

	int beforeSize = m_mapObject.size();

	// UndergroundCreature�� ��ġ�� UndergroundCreature�� �߰��Ѵ�.
	m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pUndergroundCreature) );

	int afterSize = m_mapObject.size();

	// �߰��� �� �ƴٸ�..
	if (afterSize==beforeSize)
	{
		BYTE previousPos = POSITION_UNDERGROUNDCREATURE-1;

		// ��~ �˻��ؼ� �� ���� ã�Ƽ� �߰��ؾ� �Ѵ�. 
		OBJECT_MAP::const_iterator iCreature = GetUndergroundCreatureIterator();
		BYTE currentPos;
		
		for (int i=0; i<beforeSize; i++)
		{
			currentPos = iCreature->first;

			// ���������� ���� �����̸�... �� ���� �ִٴ� �ǹ��̴�.
			// currentPos-1�� Ȯ���� �� ���̶�� �� �� �ִ�.
			if (currentPos - previousPos > 1)
			{
				pos = currentPos - 1;
				m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pUndergroundCreature) );

				break;
			}

			previousPos = currentPos;

			iCreature ++;
		}

		// �� �������� ������ �ִ´�.
		if (i==beforeSize)
		{
			pos = currentPos + 1;
			m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pUndergroundCreature) );
		}
	}

	// UndergroundCreature Flag�� check���ش�.
	m_fProperty |= FLAG_SECTOR_UNDERGROUNDCREATURE;

	m_nUndergroundCreature ++;

	return true;
}

//----------------------------------------------------------------------
// Add Creature
//----------------------------------------------------------------------
// �̹� Creature�� ������ �߰��� �� ����.
// Creature�� �߰��� �� ������ pCreature�� �߰��ϰ�
// Creature Flag�� check���ش�.
//----------------------------------------------------------------------
bool	
MSector::AddGroundCreature(const MCreature* pCreature)
{
	// �̹� Creature�� ������.. �߰� �Ұ���
	//if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	//	return false;

	//----------------------------------------------------------
	// ������ �̹� �ִ��� üũ�ϱ�
	//----------------------------------------------------------
	/*
	if (m_nGroundCreature>0)
	{
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_GROUNDCREATURE);

		while (iObject!=m_mapObject.end() 
				&& iObject->first <= POSITION_GROUNDCREATURE_MAX)
		{
			// �̹� �ִ� ���.. pointer�� ��
			if (((MCreature*)iObject->second)==pCreature)
			{
				return true;
			}
			
			iObject ++;
		}
	}
	*/

	BYTE pos = POSITION_GROUNDCREATURE+m_nGroundCreature;

	if (pos > POSITION_GROUNDCREATURE_MAX)
		return false;

	int beforeSize = m_mapObject.size();

	// Creature�� ��ġ�� Creature�� �߰��Ѵ�.
	m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pCreature) );

	int afterSize = m_mapObject.size();

	// �߰��� �� �ƴٸ�..
	if (afterSize==beforeSize)
	{
		BYTE previousPos = POSITION_GROUNDCREATURE-1;

		// ��~ �˻��ؼ� �� ���� ã�Ƽ� �߰��ؾ� �Ѵ�. 
		OBJECT_MAP::const_iterator iCreature = GetGroundCreatureIterator();
		BYTE currentPos;
		
		for (int i=0; i<beforeSize; i++)
		{
			currentPos = iCreature->first;

			// ���������� ���� �����̸�... �� ���� �ִٴ� �ǹ��̴�.
			// currentPos-1�� Ȯ���� �� ���̶�� �� �� �ִ�.
			if (currentPos - previousPos > 1)
			{
				pos = currentPos - 1;
				m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pCreature) );

				break;
			}

			previousPos = currentPos;

			iCreature ++;
		}

		// �� �������� ������ �ִ´�.
		if (i==beforeSize)
		{
			pos = currentPos + 1;
			m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pCreature) );
		}
	}


	// Creature Flag�� check���ش�.
	m_fProperty |= FLAG_SECTOR_GROUNDCREATURE;

	m_nGroundCreature ++;

	return true;
}

//----------------------------------------------------------------------
// Add FlyingCreature
//----------------------------------------------------------------------
// �̹� FlyingCreature�� ������ �߰��� �� ����.
// FlyingCreature�� �߰��� �� ������ pFlyingCreature�� �߰��ϰ�
// FlyingCreature Flag�� check���ش�.
//----------------------------------------------------------------------
bool	
MSector::AddFlyingCreature(const MCreature* pFlyingCreature)
{
	// �̹� FlyingCreature�� ������.. �߰� �Ұ���
	//if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	//	return false;

	BYTE pos = POSITION_FLYINGCREATURE+m_nFlyingCreature;

	if (pos > POSITION_FLYINGCREATURE_MAX)
		return false;	

	int beforeSize = m_mapObject.size();

	// FlyingCreature�� ��ġ�� FlyingCreature�� �߰��Ѵ�.
	m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pFlyingCreature) );

	int afterSize = m_mapObject.size();

	// �߰��� �� �ƴٸ�..
	if (afterSize==beforeSize)
	{
		BYTE previousPos = POSITION_FLYINGCREATURE-1;

		// ��~ �˻��ؼ� �� ���� ã�Ƽ� �߰��ؾ� �Ѵ�. 
		OBJECT_MAP::const_iterator iCreature = GetFlyingCreatureIterator();
		BYTE currentPos;
		
		for (int i=0; i<beforeSize; i++)
		{
			currentPos = iCreature->first;

			// ���������� ���� �����̸�... �� ���� �ִٴ� �ǹ��̴�.
			// currentPos-1�� Ȯ���� �� ���̶�� �� �� �ִ�.
			if (currentPos - previousPos > 1)
			{
				pos = currentPos - 1;
				m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pFlyingCreature) );

				break;
			}

			previousPos = currentPos;

			iCreature ++;
		}

		// �� �������� ������ �ִ´�.
		if (i==beforeSize)
		{
			pos = currentPos + 1;
			m_mapObject.insert( OBJECT_MAP::value_type(pos, (MObject*)pFlyingCreature) );
		}
	}

	// FlyingCreature Flag�� check���ش�.
	m_fProperty |= FLAG_SECTOR_FLYINGCREATURE;

	m_nFlyingCreature ++;

	return true;
}

//----------------------------------------------------------------------
// Add ImageObject
//----------------------------------------------------------------------
// �̹� ImageObject�� �ְų� ���ų� ������ �߰��ϸ� �ȴ�.
// �׷���, �̹� ImageObject�� ���� ���� �����Ƿ� 
// ���� �����ϴ� ������ �˾ƺ��� �� ����~ ������ �ȴ�.
// �߰��ϰ� m_nImageObject�� 1 ����. 
//
// (��, ImageObject�� ������ �Ѱ踦 �Ѿ���� ������... Ȯ���� ����ϹǷ�
//  �׷� ���� ���ٰ� ���� check���� �ʴ´�..)
//
//----------------------------------------------------------------------
bool	
MSector::AddImageObject(const MImageObject* pImageObject)
{
	BYTE pos = POSITION_IMAGEOBJECT+m_nImageObject;

	if (pos >= POSITION_EFFECT)
		return false;

	// ImageObject�� ��ġ�� ImageObject�� �߰��Ѵ�.
	m_mapObject.insert( 
		OBJECT_MAP::value_type(pos, (MObject*)pImageObject) 
	);

	// ������ ������Ų��.
	m_nImageObject ++;

	return true;
}


//----------------------------------------------------------------------
// 
//                         Get Object
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Get Item
//----------------------------------------------------------------------
// Item Flag�� ���� Item�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
MItem* const			
MSector::GetItem() const
{
	// Item�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_ITEM)
	{
		// Item�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.find(POSITION_ITEM);

		// ���� ��� NULL�� return�Ѵ�.
		if (iObject == m_mapObject.end()) 
			return NULL;
		
		// ������ �� Object�� return�Ѵ�.
		return (MItem* const)((*iObject).second);
	}

	return NULL;
}

//----------------------------------------------------------------------
// Get Creature
//----------------------------------------------------------------------
// Creature Flag�� ���� Creature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::const_iterator
MSector::GetCreatureIterator() const
{
	// UndergroundCreature�� �ִٸ�...
	if (IsExistAnyCreature())
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_UNDERGROUNDCREATURE);
		
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}

//----------------------------------------------------------------------
// Get UndergroundCreature
//----------------------------------------------------------------------
// UndergroundCreature Flag�� ���� UndergroundCreature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::const_iterator
MSector::GetUndergroundCreatureIterator() const
{
	// UndergroundCreature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_UNDERGROUNDCREATURE);
		
		// ������ UndergroundCreature�� ������..
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_UNDERGROUNDCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}

//----------------------------------------------------------------------
// Get Creature
//----------------------------------------------------------------------
// Creature Flag�� ���� Creature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::const_iterator
MSector::GetGroundCreatureIterator() const
{
	// Creature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	{
		// Creature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_GROUNDCREATURE);

		// ������ GroundCreature�� ������..
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_GROUNDCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}
		
//----------------------------------------------------------------------
// Get FlyingCreature
//----------------------------------------------------------------------
// FlyingCreature Flag�� ���� FlyingCreature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::const_iterator
MSector::GetFlyingCreatureIterator() const
{
	// FlyingCreature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	{
		// FlyingCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_FLYINGCREATURE);

		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}

//----------------------------------------------------------------------
// Get Creature
//----------------------------------------------------------------------
// Creature Flag�� ���� Creature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::iterator
MSector::GetCreatureIterator()
{
	// UndergroundCreature�� �ִٸ�...
	if (IsExistAnyCreature())
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.lower_bound(POSITION_UNDERGROUNDCREATURE);
		
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}

//----------------------------------------------------------------------
// Get UndergroundCreature
//----------------------------------------------------------------------
// UndergroundCreature Flag�� ���� UndergroundCreature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::iterator
MSector::GetUndergroundCreatureIterator()
{
	// UndergroundCreature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.lower_bound(POSITION_UNDERGROUNDCREATURE);
		
		// ������ UndergroundCreature�� ������..
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_UNDERGROUNDCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}

//----------------------------------------------------------------------
// Get Creature
//----------------------------------------------------------------------
// Creature Flag�� ���� Creature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::iterator
MSector::GetGroundCreatureIterator()
{
	// Creature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	{
		// Creature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.lower_bound(POSITION_GROUNDCREATURE);

		// ������ GroundCreature�� ������..
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_GROUNDCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}
		
//----------------------------------------------------------------------
// Get FlyingCreature
//----------------------------------------------------------------------
// FlyingCreature Flag�� ���� FlyingCreature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
OBJECT_MAP::iterator
MSector::GetFlyingCreatureIterator()
{
	// FlyingCreature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	{
		// FlyingCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.lower_bound(POSITION_FLYINGCREATURE);

		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			return iObject;
		}
	}

	return m_mapObject.end();
}

//----------------------------------------------------------------------
// Get Creature
//----------------------------------------------------------------------
// Creature Flag�� ���� Creature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
MCreature * const
MSector::GetCreature() const
{
	// UndergroundCreature�� �ִٸ�...
	if (IsExistAnyCreature())
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_UNDERGROUNDCREATURE);
		
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			return (MCreature* const)(iObject->second);
		}
	}
	
	return NULL;
}

//----------------------------------------------------------------------
// Get UndergroundCreature
//----------------------------------------------------------------------
// UndergroundCreature Flag�� ���� UndergroundCreature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
MCreature * const
MSector::GetUndergroundCreature() const
{
	// UndergroundCreature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_UNDERGROUNDCREATURE);
		
		// ������ UndergroundCreature�� ������..
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_UNDERGROUNDCREATURE_MAX)
		{
			return (MCreature* const)(iObject->second);
		}
	}
	
	return NULL;
}

//----------------------------------------------------------------------
// Get Creature
//----------------------------------------------------------------------
// Creature Flag�� ���� Creature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
MCreature * const
MSector::GetGroundCreature() const
{
	// Creature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	{
		// Creature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_GROUNDCREATURE);
		
		// ������ GroundCreature�� ������..
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_GROUNDCREATURE_MAX)
		{
			return (MCreature* const)(iObject->second);
		}
	}
	
	return NULL;
}

//----------------------------------------------------------------------
// Get FlyingCreature
//----------------------------------------------------------------------
// FlyingCreature Flag�� ���� FlyingCreature�� �ִٸ� return���ָ� �ȴ�.
//----------------------------------------------------------------------
MCreature * const
MSector::GetFlyingCreature() const
{
	// FlyingCreature�� �ִٸ�...
	if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	{
		// FlyingCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.lower_bound(POSITION_FLYINGCREATURE);
		
		if (iObject!=m_mapObject.end() 
			&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			return (MCreature* const)(iObject->second);
		}
	}
	
	return NULL;
}
	
//----------------------------------------------------------------------
// Get ImageObject
//----------------------------------------------------------------------
// ImageObject Flag�� ���� ImageObject�� �ִٸ� 
// ���ϴ� id�� ������ ImageObject�� ������ return���ָ� �ȴ�.
//----------------------------------------------------------------------
MImageObject* const	
MSector::GetImageObject(TYPE_OBJECTID id) const
{
	// ImageObject�� �ִٸ�...
	if (m_nImageObject)
	{
		// ImageObject�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::const_iterator iObject = m_mapObject.find(POSITION_IMAGEOBJECT);

		// ���� ��� NULL�� return�Ѵ�.
		if (iObject == m_mapObject.end()) 
			return NULL;

		// ������ ImageObject ������ŭ �񱳸� �ϰ�..		
		// ���߿� ID�� id�� ImageObject�� ������ return�Ѵ�.
		for (register BYTE i=0; i<m_nImageObject; i++)
		{
			// ���� ID�̸� return�Ѵ�.
			if ( ((*iObject).second)->GetID() == id )
				return (MImageObject* const)((*iObject).second);

			// ���� ImageObject
			iObject++;
		}
		
	}

	return NULL;
}


//----------------------------------------------------------------------
//
//                       Remove Object
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Remove Item
//----------------------------------------------------------------------
// Item�� ������ �����ϰ� Flag�� ���ְ�
// pItem���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveItem(MItem*& pItem)
{
	// Item�� ������
	if (m_fProperty & FLAG_SECTOR_ITEM)
	{
		// Item�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_ITEM);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// ������ �� Object�� �Ѱ��� �� �ֵ��� pItem�� �����Ѵ�.
		pItem =  (MItem*)((*iObject).second);

		// iObject�� �����Ѵ�.
		m_mapObject.erase( iObject );

		// Item Flag�� �����Ѵ�.
		if( pItem->GetItemClass() == ITEM_CLASS_CORPSE &&
			((MCorpse*)pItem)->GetCreature() != NULL &&
			((MCorpse*)pItem)->GetCreature()->GetCreatureType() == 672 )
			m_fProperty &= ~FLAG_SECTOR_BLOCK_GROUND;

		m_fProperty &= ~FLAG_SECTOR_ITEM;

		return true;
	}

	// ������
	return false;
}

//----------------------------------------------------------------------
// Remove UndergroundCreature
//----------------------------------------------------------------------
// UndergroundCreature�� ������ �����ϰ� Flag�� ���ְ�
// pUndergroundCreature���� �Ѱ��ش�.
//----------------------------------------------------------------------
/*
bool	
MSector::RemoveUndergroundCreature(MCreature*& pUndergroundCreature)
{
	// UndergroundCreature�� ������
	if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_UNDERGROUNDCREATURE);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// ������ �� Object�� �Ѱ��� �� �ֵ��� pUndergroundCreature�� �����Ѵ�.
		pUndergroundCreature =  (MCreature*)((*iObject).second);

		// iObject�� �����Ѵ�.
		m_mapObject.erase( iObject );

		// UndergroundCreature Flag�� �����Ѵ�.
		m_fProperty &= ~FLAG_SECTOR_UNDERGROUNDCREATURE;

		return true;
	}

	// ������
	return false;
}

//----------------------------------------------------------------------
// Remove Creature
//----------------------------------------------------------------------
// Creature�� ������ �����ϰ� Flag�� ���ְ�
// pCreature���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveGroundCreature(MCreature*& pCreature)
{
	// Creature�� ������
	if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	{
		// Creature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_GROUNDCREATURE);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// ������ �� Object�� �Ѱ��� �� �ֵ��� pCreature�� �����Ѵ�.
		pCreature =  (MCreature*)((*iObject).second);

		// iObject�� �����Ѵ�.
		m_mapObject.erase( iObject );

		// Creature Flag�� �����Ѵ�.
		m_fProperty &= ~FLAG_SECTOR_GROUNDCREATURE;

		return true;
	}

	// ������
	return false;
}
		
//----------------------------------------------------------------------
// Remove FlyingCreature
//----------------------------------------------------------------------
// FlyingCreature�� ������ �����ϰ� Flag�� ���ְ�
// pFlyingCreature���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveFlyingCreature(MCreature*& pFlyingCreature)
{
	// FlyingCreature�� ������
	if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	{
		// FlyingCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_FLYINGCREATURE);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// ������ �� Object�� �Ѱ��� �� �ֵ��� pFlyingCreature�� �����Ѵ�.
		pFlyingCreature =  (MCreature*)((*iObject).second);

		// iObject�� �����Ѵ�.
		m_mapObject.erase( iObject );

		// FlyingCreature Flag�� �����Ѵ�.
		m_fProperty &= ~FLAG_SECTOR_FLYINGCREATURE;

		return true;
	}

	// ������
	return false;
}
*/

//----------------------------------------------------------------------
// Remove Item(id, &Item)
//----------------------------------------------------------------------
// Item�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ְ�
// pItem���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveItem(TYPE_OBJECTID id, MItem*& pItem)
{
	// Item�� ������
	if (m_fProperty & FLAG_SECTOR_ITEM)
	{
		// Item�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_ITEM);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		pItem =  (MItem*)((*iObject).second);
			
		// ������ 
		// ID�� ���ؼ� ���� ���,
		// �� Object�� �Ѱ��� �� �ֵ��� pItem�� �����Ѵ�.
		if (((*iObject).second)->GetID() == id)
		{
			// iObject�� �����Ѵ�.
			m_mapObject.erase( iObject );

			// Item Flag�� �����Ѵ�.
			if( pItem->GetItemClass() == ITEM_CLASS_CORPSE &&
				((MCorpse*)pItem)->GetCreature() != NULL &&
				((MCorpse*)pItem)->GetCreature()->GetCreatureType() == 672 )
				m_fProperty &= ~FLAG_SECTOR_BLOCK_GROUND;

			m_fProperty &= ~FLAG_SECTOR_ITEM;

			return true;
		}		
	}

	// ������
	return false;
}

//----------------------------------------------------------------------
// Remove Creature(id, &Creature)
//----------------------------------------------------------------------
// Creature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ְ�
// pCreature �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveCreature(TYPE_OBJECTID id, MCreature*& pCreature)
{
	if (IsExistAnyCreature())
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetCreatureIterator();

		while (iObject!=m_mapObject.end() 
				&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			pCreature =  (MCreature*)iObject->second;
				
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pCreature�� �����Ѵ�.
			if (pCreature->GetID() == id)
			{
				// Underground
				if (iObject->first <= POSITION_UNDERGROUNDCREATURE_MAX)
				{					
					if (--m_nUndergroundCreature==0)
					{
						m_fProperty &= ~FLAG_SECTOR_UNDERGROUNDCREATURE;
					}
				}
				// Ground
				else if (iObject->first <= POSITION_GROUNDCREATURE_MAX)
				{
					if (--m_nGroundCreature==0)
					{
						m_fProperty &= ~FLAG_SECTOR_GROUNDCREATURE;
					}
				}
				// Flying
				else 
				{
					if (--m_nFlyingCreature==0)
					{
						m_fProperty &= ~FLAG_SECTOR_FLYINGCREATURE;
					}
				}		
				
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );				

				return true;
			}

			iObject ++;
		}		
	}

	// ������
	pCreature = NULL;

	return false;
}

//----------------------------------------------------------------------
// Remove UndergroundCreature(id, &UndergroundCreature)
//----------------------------------------------------------------------
// UndergroundCreature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ְ�
// pUndergroundCreature���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveUndergroundCreature(TYPE_OBJECTID id, MCreature*& pUndergroundCreature)
{
	// UndergroundCreature�� ������
	if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetUndergroundCreatureIterator();

		for (int i=0; iObject!=m_mapObject.end() && i<m_nUndergroundCreature; i++)
		{
			pUndergroundCreature =  (MCreature*)iObject->second;
				
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pUndergroundCreature�� �����Ѵ�.
			if (pUndergroundCreature->GetID() == id)
			{
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );

				// UndergroundCreature Flag�� �����Ѵ�.
				if (--m_nUndergroundCreature==0)
				{
					m_fProperty &= ~FLAG_SECTOR_UNDERGROUNDCREATURE;				
				}

				return true;
			}

			iObject ++;
		}		
	}

	// ������
	pUndergroundCreature = NULL;

	return false;
}

//----------------------------------------------------------------------
// Remove Creature(id, &Creature)
//----------------------------------------------------------------------
// Creature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ְ�
// pGroundCreature���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveGroundCreature(TYPE_OBJECTID id, MCreature*& pGroundCreature)
{
	// GroundCreature�� ������
	if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	{
		// GroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetGroundCreatureIterator();

		for (int i=0; iObject!=m_mapObject.end() && i<m_nGroundCreature; i++)
		{
			pGroundCreature =  (MCreature*)iObject->second;
				
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pGroundCreature�� �����Ѵ�.
			if (pGroundCreature->GetID() == id)
			{
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );

				// GroundCreature Flag�� �����Ѵ�.				
				if (--m_nGroundCreature==0)
				{
					m_fProperty &= ~FLAG_SECTOR_GROUNDCREATURE;
				}

				return true;
			}

			iObject ++;
		}		
	}

	// ������
	pGroundCreature = NULL;

	// ������
	return false;
}
		
//----------------------------------------------------------------------
// Remove FlyingCreature(id, &FlyingCreature)
//----------------------------------------------------------------------
// FlyingCreature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ְ�
// pFlyingCreature���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveFlyingCreature(TYPE_OBJECTID id, MCreature*& pFlyingCreature)
{
	// FlyingCreature�� ������
	if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	{
		// FlyingCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetFlyingCreatureIterator();

		for (int i=0; iObject!=m_mapObject.end() && i<m_nFlyingCreature; i++)
		{
			pFlyingCreature =  (MCreature*)iObject->second;
				
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pFlyingCreature�� �����Ѵ�.
			if (pFlyingCreature->GetID() == id)
			{
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );

				// FlyingCreature Flag�� �����Ѵ�.				
				if (--m_nFlyingCreature==0)
				{
					m_fProperty &= ~FLAG_SECTOR_FLYINGCREATURE;
				}

				return true;
			}

			iObject ++;
		}		
	}

	// ������
	pFlyingCreature = NULL;

	// ������
	return false;
}

//----------------------------------------------------------------------
// Remove ImageObject(id, &ImageObject)
//----------------------------------------------------------------------
// ImageObject�� ������ id�� ���ؼ� ���� �� �����ϰ� Flag�� ���ְ�
// m_nImageObject�� 1 ���� ��Ű�� 
// pImageObject���� �Ѱ��ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveImageObject(TYPE_OBJECTID id, MImageObject*& pImageObject)
{
	// ImageObject�� ������
	if (m_nImageObject)
	{
		// ImageObject�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_IMAGEOBJECT);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// ������ ��� ImageObject�� ID�� ���ؼ�..
		// ���� ���, �� Object�� �Ѱ��� �� �ֵ��� pImageObject�� �����Ѵ�.
		for (register BYTE i=0; i<m_nImageObject; i++)
		{
			// ID�� ���� ���..
			if (((*iObject).second)->GetID() == id)
			{
				pImageObject =  (MImageObject*)((*iObject).second);

				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );

				// m_nImageObject�� 0�� ��츸 Flag�� �����Ѵ�.
				m_nImageObject--;				

				return true;
			}		

			// ���� ImageObject
			iObject++;
		}
	}

	// ������
	return false;
}


//----------------------------------------------------------------------
// Remove Item(id)
//----------------------------------------------------------------------
// Item�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveItem(TYPE_OBJECTID id)
{
	// Item�� ������
	if (m_fProperty & FLAG_SECTOR_ITEM)
	{
		// Item�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_ITEM);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// ������ 
		// ID�� ���ؼ� ���� ���,
		// �� Object�� �Ѱ��� �� �ֵ��� pItem�� �����Ѵ�.
		if (((*iObject).second)->GetID() == id)
		{
			// iObject�� �����Ѵ�.
			MItem* pItem = dynamic_cast<MItem*>(iObject->second);
			if( pItem->GetItemClass() == ITEM_CLASS_CORPSE &&
				((MCorpse*)pItem)->GetCreature() != NULL &&
				((MCorpse*)pItem)->GetCreature()->GetCreatureType() == 672 )
				m_fProperty &= ~FLAG_SECTOR_BLOCK_GROUND;

			m_mapObject.erase( iObject );

			// Item Flag�� �����Ѵ�.
			m_fProperty &= ~FLAG_SECTOR_ITEM;

			return true;
		}		
	}

	// ������
	return false;
}


//----------------------------------------------------------------------
// Remove Creature(id)
//----------------------------------------------------------------------
// Creature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveCreature(TYPE_OBJECTID id)
{	
	if (IsExistAnyCreature())
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetCreatureIterator();

		while (iObject!=m_mapObject.end() 
				&& iObject->first <= POSITION_FLYINGCREATURE_MAX)
		{
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pCreature�� �����Ѵ�.
			if (((MCreature*)iObject->second)->GetID() == id)
			{
				// Underground
				if (iObject->first <= POSITION_UNDERGROUNDCREATURE_MAX)
				{
					if (--m_nUndergroundCreature==0)
					{
						m_fProperty &= ~FLAG_SECTOR_UNDERGROUNDCREATURE;
					}					
				}
				// Ground
				else if (iObject->first <= POSITION_GROUNDCREATURE_MAX)
				{
					if (--m_nGroundCreature==0)
					{
						m_fProperty &= ~FLAG_SECTOR_GROUNDCREATURE;
					}
					
				}
				// Flying
				else 
				{
					if (--m_nFlyingCreature==0)
					{
						m_fProperty &= ~FLAG_SECTOR_FLYINGCREATURE;
					}					
				}	
				
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );				

				return true;
			}

			iObject ++;
		}		
	}

	// ������
	return false;
}
		
//----------------------------------------------------------------------
// Remove UndergroundCreature(id)
//----------------------------------------------------------------------
// UndergroundCreature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveUndergroundCreature(TYPE_OBJECTID id)
{
	// UndergroundCreature�� ������
	if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetUndergroundCreatureIterator();

		for (int i=0; iObject!=m_mapObject.end() && i<m_nUndergroundCreature; i++)
		{
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pUndergroundCreature�� �����Ѵ�.
			if (((MCreature*)iObject->second)->GetID() == id)
			{
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );

				// UndergroundCreature Flag�� �����Ѵ�.
				if (--m_nUndergroundCreature==0)
				{
					m_fProperty &= ~FLAG_SECTOR_UNDERGROUNDCREATURE;
				}

				return true;
			}

			iObject ++;
		}		
	}

	// ������
	return false;
}
		
//----------------------------------------------------------------------
// Remove Creature(id)
//----------------------------------------------------------------------
// Creature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveGroundCreature(TYPE_OBJECTID id)
{
	// GroundCreature�� ������
	if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	{
		// GroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetGroundCreatureIterator();

		for (int i=0; iObject!=m_mapObject.end() && i<m_nGroundCreature; i++)
		{
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pGroundCreature�� �����Ѵ�.
			if (((MCreature*)iObject->second)->GetID() == id)
			{
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );

				// GroundCreature Flag�� �����Ѵ�.
				if (--m_nGroundCreature==0)
				{
					m_fProperty &= ~FLAG_SECTOR_GROUNDCREATURE;
				}				

				return true;
			}

			iObject ++;
		}		
	}

	// ������
	return false;
}
		
//----------------------------------------------------------------------
// Remove FlyingCreature(id)
//----------------------------------------------------------------------
// FlyingCreature�� ������ id�� ���ؼ� �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveFlyingCreature(TYPE_OBJECTID id)
{
	// FlyingCreature�� ������
	if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	{
		// FlyingCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = GetFlyingCreatureIterator();

		for (int i=0; iObject!=m_mapObject.end() && i<m_nFlyingCreature; i++)
		{
			// ������ 
			// ID�� ���ؼ� ���� ���,
			// �� Object�� �Ѱ��� �� �ֵ��� pFlyingCreature�� �����Ѵ�.
			if (((MCreature*)iObject->second)->GetID() == id)
			{
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );

				// FlyingCreature Flag�� �����Ѵ�.
				if (--m_nFlyingCreature==0)
				{
					m_fProperty &= ~FLAG_SECTOR_FLYINGCREATURE;
				}
				

				return true;
			}

			iObject ++;
		}		
	}


	// ������
	return false;
}
		
//----------------------------------------------------------------------
// Remove ImageObject(id)
//----------------------------------------------------------------------
// ImageObject�� ������ id�� ���ؼ� 
// ������ ������ ����
//----------------------------------------------------------------------
bool	
MSector::RemoveImageObject(TYPE_OBJECTID id)
{
	// ImageObject�� ������
	if (m_nImageObject)
	{
		// ImageObject�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_IMAGEOBJECT);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// ������ 
		// ID�� ���ؼ� ���� ���,
		// �� Object�� �Ѱ��� �� �ֵ��� pImageObject�� �����Ѵ�.
		for (register BYTE i=0; i<m_nImageObject; i++)
		{
			if (((*iObject).second)->GetID() == id)
			{
				// iObject�� �����Ѵ�.
				m_mapObject.erase( iObject );
				
				m_nImageObject--;				

				return true;
			}		

			// ���� ImageObject
			iObject ++;
		}
	}

	// ������
	return false;
}


//----------------------------------------------------------------------
// Remove Item
//----------------------------------------------------------------------
// Item�� ������ �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveItem()
{
	// Item�� ������
	if (m_fProperty & FLAG_SECTOR_ITEM)
	{
		// Item�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_ITEM);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;

		MItem* pItem = dynamic_cast<MItem*>(iObject->second);
		if( pItem->GetItemClass() == ITEM_CLASS_CORPSE && 
			((MCorpse*)pItem)->GetCreature() != NULL &&
			((MCorpse*)pItem)->GetCreature()->GetCreatureType() == 672 )
			m_fProperty &= ~FLAG_SECTOR_BLOCK_GROUND;
		
		// �����ϰ�
		m_mapObject.erase( iObject );

		// Item Flag�� �����Ѵ�.
		m_fProperty &= ~FLAG_SECTOR_ITEM;

		return true;
	}

	// ������
	return false;
}

//----------------------------------------------------------------------
// Remove UndergroundCreature
//----------------------------------------------------------------------
// UndergroundCreature�� ������ �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
/*
bool	
MSector::RemoveUndergroundCreature()
{
	// UndergroundCreature�� ������
	if (m_fProperty & FLAG_SECTOR_UNDERGROUNDCREATURE)
	{
		// UndergroundCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_UNDERGROUNDCREATURE);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// �����ϰ�
		m_mapObject.erase( iObject );

		// UndergroundCreature Flag�� �����Ѵ�.
		m_fProperty &= ~FLAG_SECTOR_UNDERGROUNDCREATURE;

		return true;
	}

	// ������
	return false;
}

//----------------------------------------------------------------------
// Remove Creature
//----------------------------------------------------------------------
// Creature�� ������ �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveGroundCreature()
{
	// Creature�� ������
	if (m_fProperty & FLAG_SECTOR_GROUNDCREATURE)
	{
		// Creature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_GROUNDCREATURE);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// �����ϰ�
		m_mapObject.erase( iObject );

		// Creature Flag�� �����Ѵ�.
		m_fProperty &= ~FLAG_SECTOR_GROUNDCREATURE;

		return true;
	}

	// ������
	return false;
}

//----------------------------------------------------------------------
// Remove FlyingCreature
//----------------------------------------------------------------------
// FlyingCreature�� ������ �����ϰ� Flag�� ���ش�.
//----------------------------------------------------------------------
bool	
MSector::RemoveFlyingCreature()
{
	// FlyingCreature�� ������
	if (m_fProperty & FLAG_SECTOR_FLYINGCREATURE)
	{
		// FlyingCreature�� ��ġ�� �ִ� Object�� ã�´�.
		OBJECT_MAP::iterator iObject = m_mapObject.find(POSITION_FLYINGCREATURE);

		// ���� ��� return false
		if (iObject == m_mapObject.end()) 
			return false;
		
		// �����ϰ�
		m_mapObject.erase( iObject );

		// FlyingCreature Flag�� �����Ѵ�.
		m_fProperty &= ~FLAG_SECTOR_FLYINGCREATURE;

		return true;
	}

	// ������
	return false;
}
*/

//----------------------------------------------------------------------
//
//                      iterator�� �Ѱ��ش�.
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// ImageObject Iterator
//----------------------------------------------------------------------
// ImageObject�� �ִ� ��쿡.. ������ ImageObject�� ����
// Iterator�� �Ѱ��ش�.
//----------------------------------------------------------------------
OBJECT_MAP::const_iterator	
MSector::GetImageObjectIterator() const
{
	if (m_nImageObject)
	{
		// ImageObject�� ��ġ�� �ִ� Object�� ã�´�.
		return m_mapObject.find(POSITION_IMAGEOBJECT);
	}

	return NULL;
}


//----------------------------------------------------------------------
//
//                       Effect List ó��
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Add Effect
//----------------------------------------------------------------------
// Effect List�� ���� Effect�� �߰��Ѵ�.
//----------------------------------------------------------------------
void
MSector::AddEffect(const MEffect* pEffect)
{
	// NULL�� �ƴ� ��� �߰�..(�׳�.. - -;;)
	if (pEffect!=NULL)
	{
		m_listEffect.push_back((MEffect*)pEffect);

		// Darkness���� üũ�Ѵ�.
		if (!m_bDarkness || !m_bSanctuary)	// [�����]
		{
			int fid = pEffect->GetFrameID();
			int est = g_pTopView->GetEffectSpriteType( (BLT_TYPE)pEffect->GetBltType(), fid );

//			if(est >= EFFECTSPRITETYPE_MAP_BLACK_LARGE_SMOKE &&
//				est >= EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_3)
//				m_bDarkness = true;
			// darkness �ִ� ���			
			if (est>=EFFECTSPRITETYPE_DARKNESS_2_1
					&& est<=EFFECTSPRITETYPE_DARKNESS_2_5)
			{
				m_bDarkness = true;
			}				
			
			if( est>= EFFECTSPRITETYPE_GRAY_DARKNESS_2_1 &&
				est<= EFFECTSPRITETYPE_GRAY_DARKNESS_2_5 )
			{
				m_bDarkness = true;
			}

			// sanctuary �ִ� ���			
			if (est>=EFFECTSPRITETYPE_SANCTUARY_1
					&& est<=EFFECTSPRITETYPE_SANCTUARY_3)
			{
				m_bSanctuary = true;
			}

		}
	}
}

//----------------------------------------------------------------------
// Get Effect
//----------------------------------------------------------------------
// Effect ID�� id�� effect�� ã�´�.
//----------------------------------------------------------------------
MEffect*	
MSector::GetEffect(TYPE_OBJECTID id) const
{
	EFFECT_LIST::const_iterator iEffect = m_listEffect.begin();

	while (iEffect != m_listEffect.end())
	{
		// ���ϴ� id���� check
		if ((*iEffect)->GetID()==id)
		{
			return *iEffect;
		}

		iEffect++;
	}

	return NULL;
}


//----------------------------------------------------------------------
// Remove Effect(id)
//----------------------------------------------------------------------
// Effect List���� ID�� id�� ���� ã�Ƽ� list���� �����Ѵ�.
//----------------------------------------------------------------------
bool		
MSector::RemoveEffect(TYPE_OBJECTID id)
{
	EFFECT_LIST::iterator iEffect = m_listEffect.begin();

	while (iEffect != m_listEffect.end())
	{
		MEffect* pEffect = *iEffect;				

		// ���ϴ� id���� check
		if (pEffect->GetID()==id)
		{
			// ����~
			m_listEffect.erase( iEffect );

			// Darkness���� üũ�Ѵ�.
			if (m_bDarkness || m_bSanctuary)	// [�����]
			{
				int fid = pEffect->GetFrameID();
				int est = g_pTopView->GetEffectSpriteType( (BLT_TYPE)pEffect->GetBltType(), fid );

//				if(est >= EFFECTSPRITETYPE_MAP_BLACK_LARGE_SMOKE &&
//					est <= EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_3
//					)
//				{
//					m_bDarkness = false;
//				}
				// darkness �ִ� ���			
				if (est>=EFFECTSPRITETYPE_DARKNESS_2_1
						&& est<=EFFECTSPRITETYPE_DARKNESS_2_5)
				{
					m_bDarkness = false;
				}				

				if (est>=EFFECTSPRITETYPE_GRAY_DARKNESS_2_1
						&& est<=EFFECTSPRITETYPE_GRAY_DARKNESS_2_5)
				{
					m_bDarkness = false;
				}				

				// sanctuary �ִ� ���			
				if (est>=EFFECTSPRITETYPE_SANCTUARY_1
						&& est<=EFFECTSPRITETYPE_SANCTUARY_3)
				{
					m_bSanctuary = false;
				}
			}

			return true;
		}

		iEffect++;
	}

	return false;
}

//----------------------------------------------------------------------
// Remove Effect(id, &pEffect)
//----------------------------------------------------------------------
// Effect List���� ID�� id�� ���� ã�Ƽ� list���� �����ϰ�
// �� Effect�� �Ѱ��ش�.
//----------------------------------------------------------------------
bool		
MSector::RemoveEffect(TYPE_OBJECTID id, MEffect*& pEffect)
{
	EFFECT_LIST::iterator iEffect = m_listEffect.begin();

	while (iEffect != m_listEffect.end())
	{
		MEffect* pEffect = *iEffect;

		// ���ϴ� id���� check
		if (pEffect->GetID()==id)
		{
			// ������ Effect�� �Ѱ��ش�.
			pEffect = *iEffect;

			// ����~
			m_listEffect.erase( iEffect );

			// Darkness���� üũ�Ѵ�.
			if (m_bDarkness || m_bSanctuary)	// [�����]
			{
				int fid = pEffect->GetFrameID();
				int est = g_pTopView->GetEffectSpriteType( (BLT_TYPE)pEffect->GetBltType(), fid );

				// darkness �ִ� ���			
				if (est>=EFFECTSPRITETYPE_DARKNESS_2_1
						&& est<=EFFECTSPRITETYPE_DARKNESS_2_5)
				{
					m_bDarkness = false;
				}				

				if (est>=EFFECTSPRITETYPE_GRAY_DARKNESS_2_1
						&& est<=EFFECTSPRITETYPE_GRAY_DARKNESS_2_5)
				{
					m_bDarkness = false;
				}				

				// sanctuary �ִ� ���			
				if (est>=EFFECTSPRITETYPE_SANCTUARY_1
						&& est<=EFFECTSPRITETYPE_SANCTUARY_3)
				{
					m_bSanctuary = false;
				}
			}

			return true;
		}

		iEffect++;
	}

	return false;
}

//----------------------------------------------------------------------
// Add Portal ( zoneID )
//----------------------------------------------------------------------
// �̹� �ִ°Ÿ� �߰����� �ʴ´�.
// cut&paste .. ������
//----------------------------------------------------------------------
bool					
MSector::AddPortal(int type, int zoneID)
{
	PORTAL_LIST::iterator iData = m_listPortal.begin();

	// �̹� list�� ����ִ� ��� Data�� ���غ���
	// ������ ���� �� �߰��Ѵ�.
	while (iData != m_listPortal.end())
	{
		// ���� ����ִ°� �߰��ҷ��°ͺ��� Ŭ ���,
		// ���� ��ġ�� �߰��ϸ� �ȴ�.
		if (iData->ZoneID > zoneID)
		{
			m_listPortal.insert(iData, PORTAL_INFO(type, zoneID));

			m_fProperty |= FLAG_SECTOR_PORTAL;

			return true;
		}

		// �̹� �ִ� ���̸�
		// �߰����� �ʴ´�.
		if (iData->ZoneID==zoneID)
		{
			return false;
		}

		iData++;
	}	

	// list�� ��� ���ҵ麸�� ũ�Ƿ� 
	// list�� ���� �߰��Ѵ�.
	m_listPortal.push_back( PORTAL_INFO(type, zoneID) );

	m_fProperty |= FLAG_SECTOR_PORTAL;

	return true;
}

//----------------------------------------------------------------------
// Clear Portal ( zoneID )
//----------------------------------------------------------------------
void					
MSector::ClearPortal()
{
	m_listPortal.clear();

	m_fProperty &= ~FLAG_SECTOR_PORTAL;
}

//----------------------------------------------------------------------
// Add SectorSound (SECTORSOUND_INFO&)
//----------------------------------------------------------------------
bool								
MSector::AddSectorSound(const SECTORSOUND_INFO& info)
{
	return AddSectorSound( info.ZoneSoundID, info.X, info.Y );
}

//----------------------------------------------------------------------
// Add SectorSound ( ZoneSoundID, Xo, Yo )
//----------------------------------------------------------------------
// �̹� �ִ°Ÿ� �߰����� �ʴ´�.
// cut&paste .. ������
//----------------------------------------------------------------------
bool					
MSector::AddSectorSound(int zoneSoundID, TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y)
{
	SECTORSOUND_LIST::iterator iData = m_listSectorSound.begin();

	// �̹� list�� ����ִ� ��� Data�� ���غ���
	// ������ ���� �� �߰��Ѵ�.
	while (iData != m_listSectorSound.end())
	{
		// ���� ����ִ°� �߰��ҷ��°ͺ��� Ŭ ���,
		// ���� ��ġ�� �߰��ϸ� �ȴ�.
		if (iData->ZoneSoundID > zoneSoundID)
		{
			m_listSectorSound.insert(iData, SECTORSOUND_INFO(zoneSoundID, x, y));

			return true;
		}

		// �̹� �ִ� ���̸�
		// �߰����� �ʴ´�.
		if (iData->ZoneSoundID==zoneSoundID)
		{
			return false;
		}

		iData++;
	}	

	// list�� ��� ���ҵ麸�� ũ�Ƿ� 
	// list�� ���� �߰��Ѵ�.
	m_listSectorSound.push_back( SECTORSOUND_INFO(zoneSoundID, x, y) );

	return true;
}

//----------------------------------------------------------------------
// Clear SectorSound ( zoneID )
//----------------------------------------------------------------------
void					
MSector::ClearSectorSound()
{
	m_listSectorSound.clear();
}