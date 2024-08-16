//////////////////////////////////////////////////////////////////////
// 
// Filename    : InventoryInfo.h 
// Written By  : elca@ewestsoft.com
// Description : �κ��丮 �������� ������
// 
//////////////////////////////////////////////////////////////////////

#ifndef __INVENTORY_INFO_H__
#define __INVENTORY_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "InventorySlotInfo.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class InventoryInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class InventoryInfo {

public :
	
	// constructor
	InventoryInfo () throw ();
	
	// destructor
	~InventoryInfo () throw ();

	
public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () throw ();

	static uint getMaxSize() throw() {
		return szBYTE + ( InventorySlotInfo::getMaxSize() * 60 ) + szCoordInven + szCoordInven;
	}

	// get packet's debug std::string
	std::string toString () const throw ();

	CoordInven_t getWidth() const { return m_Width; }
	void setWidth( CoordInven_t Width ) { m_Width = Width; }

	CoordInven_t getHeight() const { return m_Height; }
	void setHeight( CoordInven_t Height ) { m_Height = Height; }
	
	// get / set ListNumber
	BYTE getListNum() const throw() { return m_ListNum; }
	void setListNum( BYTE ListNum ) throw() { m_ListNum = ListNum; }

	// add / delete / clear S List
	void addListElement( InventorySlotInfo * pInventorySlotInfo ) throw() { m_InventorySlotInfoList.push_back( pInventorySlotInfo ); }

	// ClearList
	void clearList() throw() { m_InventorySlotInfoList.clear(); m_ListNum = 0; }

	// pop front Element in Status List
	InventorySlotInfo * popFrontListElement() throw() 
	{ 
		InventorySlotInfo * TempInventorySlotInfo = m_InventorySlotInfoList.front(); m_InventorySlotInfoList.pop_front(); return TempInventorySlotInfo; 
	}

private :
	
	CoordInven_t	m_Width, m_Height;

	// InventorySlotInfo List Total Number
	BYTE m_ListNum;

	// InventorySlotInfo List
	std::list<InventorySlotInfo*> m_InventorySlotInfoList;

};

#endif
