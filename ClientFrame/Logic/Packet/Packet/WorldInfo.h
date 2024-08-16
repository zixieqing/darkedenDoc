//////////////////////////////////////////////////////////////////////
// 
// Filename    : WorldInfo.h 
// Written By  : elca@ewestsoft.com
// Description : �κ��丮 �������� ������
// 
//////////////////////////////////////////////////////////////////////

#ifndef __WORLD_INFO_H__
#define __WORLD_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"

//////////////////////////////////////////////////////////////////////
//
// class WorldInfo;
//
// ���Ӽ������� Ŭ���̾�Ʈ�� �ڽ��� ����� ������ �˷��ֱ� ���� Ŭ����
//
//////////////////////////////////////////////////////////////////////

class WorldInfo {

public :
	
	// constructor
	WorldInfo () throw ();
	
	// destructor
	~WorldInfo () throw ();

public :
	
	
    // �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
    void read (SocketInputStream & iStream) throw (ProtocolException, Error);
		    
    // ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
    void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// get packet's body size
	// ����ȭ��, �̸� ���� ������ ����Ѵ�.
	PacketSize_t getSize () throw ();

	static uint getMaxSize() throw() {
		return (szBYTE + szBYTE + 20 + szBYTE)* 37;
	}

	#ifdef __DEBUG_OUTPUT__
		// get packet's debug std::string
		std::string toString () const throw ();
	#endif

	// get / set ID
	BYTE getID() const throw() { return m_ID; }
	void setID(WorldID_t ID) throw() { m_ID = ID; }

	// get / set Name
	std::string getName() const throw() { return m_Name; }
	void setName(std::string Name) throw() { m_Name = Name; }

	// get / set  Stat
	BYTE getStat() const throw() { return m_Stat; }
	void setStat(BYTE Stat) throw() { m_Stat = Stat; }

private :

	// �׷� ���̵�
	WorldID_t m_ID;

	// �׷� �̸�
	std::string m_Name;

	// �׷��� ����
	BYTE	m_Stat;

};

#endif
