//////////////////////////////////////////////////////////////////////
// 
// Filename    : InventoryInfo.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "InventoryInfo.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
InventoryInfo::InventoryInfo () 
     throw ()
{
	__BEGIN_TRY
	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
InventoryInfo::~InventoryInfo () 
    throw ()
{
	__BEGIN_TRY

	// 소속된 모든 객체들을 삭제한다.
	while ( !m_InventorySlotInfoList.empty() ) {
		InventorySlotInfo * pInventorySlotInfo = m_InventorySlotInfoList.front();
		delete pInventorySlotInfo;
		m_InventorySlotInfoList.pop_front();
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void InventoryInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	//add by zdj
	//iStream.read( m_Width );
	//iStream.read( m_Height );
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ListNum );

	for( int i = 0; i < m_ListNum; i++ ) {
		InventorySlotInfo * pInventorySlotInfo = new InventorySlotInfo();
		pInventorySlotInfo->read( iStream );
		m_InventorySlotInfoList.push_back( pInventorySlotInfo );

	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void InventoryInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	//add by zdj
	//oStream.write( m_Width );
	//oStream.write( m_Height );

	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ListNum );

    for ( std::list<InventorySlotInfo*>:: const_iterator itr = m_InventorySlotInfoList.begin(); itr!= m_InventorySlotInfoList.end(); itr++) {
		(*itr)->write( oStream );
	}

	__END_CATCH
}

//--------------------------------------------------------------------
// getSize
//--------------------------------------------------------------------
PacketSize_t InventoryInfo::getSize()
	throw()
{

	PacketSize_t PacketSize = szBYTE;

	for ( std::list< InventorySlotInfo* >::const_iterator itr = m_InventorySlotInfoList.begin() ; itr != m_InventorySlotInfoList.end() ; itr ++ ) {

		PacketSize += (*itr)->getSize();

	}

	return PacketSize;

}

 /////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
std::string InventoryInfo::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "InventoryInfo( ListNum:" << (int)m_ListNum 
		<< " ListSet( " ;

	for ( std::list<InventorySlotInfo*>::const_iterator itr = m_InventorySlotInfoList.begin(); itr!= m_InventorySlotInfoList.end() ; itr++ ) {
		msg << (*itr)->toString() << ",";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
#endif