//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCUseBonusPointFail.cpp
// Written By  : crazydog
// Description :  
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCUseBonusPointFail.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCUseBonusPointFail::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCUseBonusPointFail::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCUseBonusPointFail::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCUseBonusPointFailHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCUseBonusPointFail::toString () const
		   throw ()
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "GCUseBonusPointFail";
		return msg.toString();

		__END_CATCH
	}
#endif

