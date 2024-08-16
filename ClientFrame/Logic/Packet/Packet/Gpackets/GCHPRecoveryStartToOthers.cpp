//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCHPRecoveryStartToOthers.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCHPRecoveryStartToOthers.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCHPRecoveryStartToOthers::GCHPRecoveryStartToOthers () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCHPRecoveryStartToOthers::~GCHPRecoveryStartToOthers () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToOthers::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ObjectID );
	iStream.read( m_Delay );
	iStream.read( m_Period );
	iStream.read( m_Quantity );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToOthers::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ObjectID );
	oStream.write( m_Delay );
	oStream.write( m_Period );
	oStream.write( m_Quantity );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCHPRecoveryStartToOthers::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCHPRecoveryStartToOthersHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCHPRecoveryStartToOthers::toString () 
		const throw ()
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCHPRecoveryStartToOthers( ObjectID:" << (int)m_ObjectID 
			<< " Delay : " << (int)m_Delay
			<< " Period : " << (int)m_Period
			<< " Quantity : " << (int)m_Quantity
			<< " )";

		return msg.toString();

		__END_CATCH
	}
#endif

