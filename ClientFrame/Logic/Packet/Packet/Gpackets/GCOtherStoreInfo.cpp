//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherStoreInfo.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "GCOtherStoreInfo.h"
#include "Assert.h"
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCOtherStoreInfo::~GCOtherStoreInfo() 
	throw ()
{
	__BEGIN_TRY 

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCOtherStoreInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read(m_ObjectID);
	iStream.read(m_IsRequested);
	SAFE_DELETE(m_pInfo);
	m_pInfo = new StoreInfo;	
	m_pInfo->read( iStream, true );

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCOtherStoreInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
	oStream.write(m_IsRequested);
	m_pInfo->write( oStream, true );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCOtherStoreInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCOtherStoreInfoHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
string GCOtherStoreInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCOtherStoreInfo(";
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}
#endif
