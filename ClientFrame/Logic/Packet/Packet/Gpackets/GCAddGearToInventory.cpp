//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddGearToInventory.cpp 
// Written By  : crazydog
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCAddGearToInventory.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAddGearToInventory::GCAddGearToInventory () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAddGearToInventory::~GCAddGearToInventory () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCAddGearToInventory::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_SlotID );
	iStream.read( m_InvenX );
	iStream.read( m_InvenY );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCAddGearToInventory::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_SlotID );
	oStream.write( m_InvenX );
	oStream.write( m_InvenY );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddGearToInventory::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	GCAddGearToInventoryHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCAddGearToInventory::toString () 
		const throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "GCAddGearToInventory( SlotID : " << (int)m_SlotID 
			<< ", InventoryX : " << (int)m_InvenX 
			<< ", InventoryY : " << (int)m_InvenY 
			<< ")";
		return msg.toString();

		__END_CATCH
	}
#endif
