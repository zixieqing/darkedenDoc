//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCModifyGuildMemberInfo.cpp 
// Written By  : reiot@ewestsoft.com
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCModifyGuildMemberInfo.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCModifyGuildMemberInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName;
	
	iStream.read( m_GuildID );
	iStream.read( szGuildName );

//	if ( szGuildName == 0 )
//		throw InvalidProtocolException("szGuildName == 0");

	if ( szGuildName > 30 )
		throw InvalidProtocolException("too long GuildName length");

	if ( szGuildName != 0 )
	{
		iStream.read( m_GuildName, szGuildName );
	}

	iStream.read( m_GuildMemberRank );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCModifyGuildMemberInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE szGuildName = m_GuildName.size();

//	if ( szGuildName == 0 )
//		throw InvalidProtocolException("szGuildName == 0");

	if ( szGuildName > 256 )
		throw InvalidProtocolException("too long GuildName length");

	oStream.write( m_GuildID );
	oStream.write( szGuildName );
	if( szGuildName != 0 )
	{
		oStream.write( m_GuildName );
	}
	oStream.write( m_GuildMemberRank );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCModifyGuildMemberInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCModifyGuildMemberInfoHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
std::string GCModifyGuildMemberInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCModifyGuildMemberInfo("
		<< "GuildID:" << (int)m_GuildID
		<< "GuildName:" << m_GuildName
		<< "GuildMemberRank:" << (int)m_GuildMemberRank
		<< ")" ;
	
	return msg.toString();
		
	__END_CATCH
}
#endif

