////////////////////////////////////////////////////////////////////////////////
// 
// Filename    : GCStashSell.cpp 
// Written By  : 김성민
// Description : 
// 
////////////////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCStashSell.h"

////////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
////////////////////////////////////////////////////////////////////////////////
void GCStashSell::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	iStream.read(m_Price);

	__END_DEBUG
	__END_CATCH
}

		    
////////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
////////////////////////////////////////////////////////////////////////////////
void GCStashSell::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	oStream.write(m_Price);
	
	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// execute packet's handler
////////////////////////////////////////////////////////////////////////////////
void GCStashSell::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCStashSellHandler::execute( this , pPlayer );

	__END_DEBUG
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------
// get packet's debug string
//--------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCStashSell::toString () const
		   throw ()
	{
		__BEGIN_TRY
		__BEGIN_DEBUG
			
		StringStream msg;
		
		msg << "GCStashSell("
			<< "Price:" << (int)m_Price
			<< ")";

		return msg.toString();
			
		__END_DEBUG
		__END_CATCH
	}
#endif
