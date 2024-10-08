//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttack.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCAttack.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAttack::GCAttack () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAttack::~GCAttack () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCAttack::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( (char*)&m_ObjectID , szObjectID );
	iStream.read( (char*)&m_X , szCoord );
	iStream.read( (char*)&m_Y , szCoord );
	iStream.read( (char*)&m_Dir , szDir );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCAttack::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( (char*)&m_ObjectID , szObjectID );
	oStream.write( (char*)&m_X , szCoord );
	oStream.write( (char*)&m_Y , szCoord );
	oStream.write( (char*)&m_Dir , szDir );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCAttack::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	GCAttackHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCAttack::toString () const
		throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "GCAttack(X:" << (int)m_X << ",Y:" << (int)m_Y << ",ObjectID:" << (int)m_ObjectID;
		return msg.toString();

		__END_CATCH
	}
#endif
