
//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCTakeOutFail.cc 
// Written By  : elca@ewestsoft.com
// Description : CGMove가 날아 왓을때 자기 자신에게 Fail 사인을 날리기
//               위한 패킷 클래스 함수 정의
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCTakeOutFail.h"


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCTakeOutFail::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_ObjectID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCTakeOutFail::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCTakeOutFail::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCTakeOutFailHandler::execute( this , pPlayer );
		
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
std::string GCTakeOutFail::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCTakeOutFail("
		<< "ObjectId:" << (int)m_ObjectID
		<< ")";
	return msg.toString();

	__END_CATCH
}

#endif