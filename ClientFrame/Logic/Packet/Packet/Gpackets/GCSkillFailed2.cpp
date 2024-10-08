//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillFailed2.cc 
// Written By  : elca@ewestsoft.com
// Description : Skill이 실패 했을때 날려주는 패킷의 멤버 정의
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCSkillFailed2.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillFailed2::GCSkillFailed2 () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillFailed2::~GCSkillFailed2 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCSkillFailed2::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
	iStream.read( m_SkillType );
	iStream.read( m_Grade );
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCSkillFailed2::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
	oStream.write( m_SkillType );
	oStream.write( m_Grade );
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCSkillFailed2::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillFailed2Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCSkillFailed2::toString () const
		   throw ()
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "GCSkillFailed2( ObjectID : " << (int)m_ObjectID << ", TargetObjectID: " << (int)m_TargetObjectID << ", SkillType : " << (int)m_SkillType << " )" << "grade : " << (int) m_Grade ;
		return msg.toString();

		__END_CATCH
	}

#endif
