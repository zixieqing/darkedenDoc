//////////////////////////////////////////////////////////////////////
// 
// Filename    : GLIncomingConnectionOK.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GLIncomingConnectionOK.h"


//////////////////////////////////////////////////////////////////////
// Datagram 객체로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GLIncomingConnectionOK::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// read Player ID
	//--------------------------------------------------
	BYTE szPlayerID;

	iDatagram.read( szPlayerID );

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too long playerID size");

	iDatagram.read( m_PlayerID , szPlayerID );

	//--------------------------------------------------
	// read TCP Port
	//--------------------------------------------------
	iDatagram.read( m_TCPPort );

	//--------------------------------------------------
	// read Auth Key
	//--------------------------------------------------
	iDatagram.read( m_Key );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram 객체로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GLIncomingConnectionOK::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	//--------------------------------------------------
	// write Player ID
	//--------------------------------------------------
	BYTE szPlayerID = m_PlayerID.size();

	if ( szPlayerID == 0 )
		throw InvalidProtocolException("szPlayerID == 0");

	if ( szPlayerID > 20 )
		throw InvalidProtocolException("too long playerID size");

	oDatagram.write( szPlayerID );

	oDatagram.write( m_PlayerID );

	//--------------------------------------------------
	// write TCP Port
	//--------------------------------------------------
	oDatagram.write( m_TCPPort );

	//--------------------------------------------------
	// write auth Key
	//--------------------------------------------------
	oDatagram.write( m_Key );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GLIncomingConnectionOK::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GLIncomingConnectionOKHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GLIncomingConnectionOK::toString () const
		throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "GLIncomingConnectionOK("
			<< "PlayerID:" << m_PlayerID
			<< ",TCPPort:" << m_TCPPort
			<< ",Key:" << m_Key
			<< ")";
		return msg.toString();

		__END_CATCH
	}
#endif
