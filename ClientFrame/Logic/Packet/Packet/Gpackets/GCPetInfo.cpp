//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetInfo.cpp 
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "GCPetInfo.h"
#include "RaceWarInfo.h"
#include "LevelWarInfo.h"
#include "GuildWarInfo.h"
#include "Assert.h"

#ifdef __GAME_SERVER__
#include "PetItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
GCPetInfo::GCPetInfo() 
	throw ()
{
	__BEGIN_TRY 

	m_pPetInfo = NULL;
	m_ObjectID = 0;

	__END_CATCH;
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCPetInfo::~GCPetInfo() 
	throw ()
{
	__BEGIN_TRY 

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCPetInfo::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	m_pPetInfo = new PetInfo;
	m_pPetInfo->read( iStream );
	iStream.read( m_ObjectID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCPetInfo::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	if ( m_pPetInfo == NULL )
	{
		PetType_t PetType = PET_NONE;
		oStream.write(PetType);
	}
	else
	{
		m_pPetInfo->setSummonInfo(1);
		m_pPetInfo->write( oStream );
	}

	oStream.write( m_ObjectID );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCPetInfo::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCPetInfoHandler::execute(this , pPlayer);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCPetInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCPetInfo(" ;
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}

#ifdef __GAME_SERVER__
ObjectID_t PetInfo::getItemObjectID() const
{
	if ( m_pPetItem == NULL ) return 0;
		return m_pPetItem->getObjectID();
	return 0;
}
#endif

