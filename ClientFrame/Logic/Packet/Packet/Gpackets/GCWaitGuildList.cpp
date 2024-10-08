//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCWaitGuildList.cpp 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCWaitGuildList.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCWaitGuildList::GCWaitGuildList()
	throw()
{
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCWaitGuildList::~GCWaitGuildList()
	throw()
{
	__BEGIN_TRY
	
	// 길드 리스트의 모든 객체를 삭제
	clearGuildInfoList();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	WORD ListNum;

	iStream.read( ListNum );
	for ( int i = 0; i < ListNum; i++ )
	{
		GuildInfo* pGuildInfo = new GuildInfo();
		pGuildInfo->read( iStream );
		m_GuildInfoList.push_front( pGuildInfo );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	WORD ListNum = m_GuildInfoList.size();
	oStream.write( ListNum );

	GuildInfoListConstItor itr = m_GuildInfoList.begin();
	for ( ; itr != m_GuildInfoList.end(); itr++ )
	{
		(*itr)->write( oStream );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::clearGuildInfoList()
	throw()
{
	__BEGIN_TRY

	// GuildInfoList 를 삭제한다
	while( !m_GuildInfoList.empty() )
	{
		GuildInfo* pGuildInfo = m_GuildInfoList.front();
		m_GuildInfoList.pop_front();
		delete( pGuildInfo );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCWaitGuildList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCWaitGuildListHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet size
//////////////////////////////////////////////////////////////////////
PacketSize_t GCWaitGuildList::getPacketSize() const
	throw()
{
	__BEGIN_TRY

	PacketSize_t PacketSize = szWORD;

	GuildInfoListConstItor itr = m_GuildInfoList.begin();

	for ( ; itr != m_GuildInfoList.end(); itr++ )
	{
		PacketSize += (*itr)->getSize();
	}

	return PacketSize;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
std::string GCWaitGuildList::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCWaitGuildList(";

	std::list<GuildInfo*>::const_iterator itr = m_GuildInfoList.begin();
	for ( ; itr != m_GuildInfoList.end(); itr++ )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	
	return msg.toString();
		
	__END_CATCH
}

