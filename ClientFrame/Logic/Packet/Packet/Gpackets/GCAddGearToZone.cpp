//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddGearToZone.cpp 
// Written By  : crazydog
// Description : 	
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCAddGearToZone.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAddGearToZone::GCAddGearToZone () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAddGearToZone::~GCAddGearToZone () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCAddGearToZone::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_SlotID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCAddGearToZone::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_SlotID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAddGearToZone::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	GCAddGearToZoneHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCAddGearToZone::toString () 
		const throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "GCAddGearToZone( SlotID : " << (int)m_SlotID << ")";
		return msg.toString();

		__END_CATCH
	}
#endif
