//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGVerifyTime.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGVerifyTime.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
#endif

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void CGVerifyTime::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void CGVerifyTime::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CGVerifyTime::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CGVerifyTimeHandler::execute( this , pPlayer );
	#endif

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGVerifyTime::toString () const
		   throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		
		msg << "CGVerifyTime()" ;
		
		return msg.toString();

		__END_CATCH
	}
#endif
