//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSubInventoryInfo.cpp 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCSubInventoryInfo.h"
#include "RaceWarInfo.h"
#include "LevelWarInfo.h"
#include "GuildWarInfo.h"
#include "Assert.h"
#include "Client.h"
#ifdef __GAME_SERVER__
#include "PetItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCSubInventoryInfo::GCSubInventoryInfo() 
	throw ()
{
	__BEGIN_TRY 

	m_pInventoryInfo = NULL;
	m_ObjectID = 0;

	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCSubInventoryInfo::~GCSubInventoryInfo() 
	throw ()
{
	__BEGIN_TRY 

	SAFE_DELETE( m_pInventoryInfo );

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCSubInventoryInfo::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	m_pInventoryInfo = new InventoryInfo;
	m_pInventoryInfo->read( iStream );
	iStream.read( m_ObjectID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCSubInventoryInfo::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	m_pInventoryInfo->write( oStream );
	oStream.write( m_ObjectID );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCSubInventoryInfo::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCSubInventoryInfoHandler::execute(this , pPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__	
string GCSubInventoryInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCSubInventoryInfo(" ;
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}
#endif
