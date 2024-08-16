//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGRequestIP.cpp 
// Written By  : elca@ewestsoft.com
// Description : 서버에 원하는 사람의 IP 요청
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGRequestIP.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CGRequestIP::CGRequestIP () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CGRequestIP::~CGRequestIP () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void CGRequestIP::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE num;
	iStream.read( num );

	if (num > 0)
	{
		iStream.read( m_Name, num );
	}
	

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void CGRequestIP::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	BYTE num = m_Name.size();
	oStream.write( num );

	if (num > 0)
	{
		oStream.write( m_Name );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void CGRequestIP::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CGRequestIPHandler::execute( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGRequestIP::toString () 
		const throw ()
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "CGRequestIP( "
			<< ",Name: " << m_Name			
			<< ")";

		return msg.toString();

		__END_CATCH
	}

#endif