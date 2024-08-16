//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGUseBonusPoint.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGUseBonusPoint.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CGUseBonusPoint::CGUseBonusPoint () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CGUseBonusPoint::~CGUseBonusPoint () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void CGUseBonusPoint::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_Which);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void CGUseBonusPoint::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_Which );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CGUseBonusPoint::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CGUseBonusPointHandler::execute( this , pPlayer );
	#endif

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGUseBonusPoint::toString () const
		   throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		
		msg << "CGUseBonusPoint(Which:" << (int)m_Which 
			<< ")" ;
		
		return msg.toString();

		__END_CATCH
	}
#endif