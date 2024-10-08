//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRegenZoneStatus.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCRegenZoneStatus.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCRegenZoneStatus::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	for ( int i=0; i<8; ++i )
	{
		BYTE buf;
		iStream.read(buf);
		m_Statuses.push_back(buf);
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCRegenZoneStatus::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	for ( int i=0; i<8; ++i ) oStream.write( m_Statuses[i] );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCRegenZoneStatus::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCRegenZoneStatusHandler::execute( this , pPlayer );

	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
std::string GCRegenZoneStatus::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCRegenZoneStatus(" << ")";

	return msg.toString();
		
	__END_CATCH
}
#endif