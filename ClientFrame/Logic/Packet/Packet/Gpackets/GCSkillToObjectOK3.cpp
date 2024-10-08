//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSkillToObjectOK3.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "GCSkillToObjectOK3.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCSkillToObjectOK3::GCSkillToObjectOK3 () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCSkillToObjectOK3::~GCSkillToObjectOK3 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK3::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	iStream.read( m_ObjectID );
	iStream.read( m_SkillType );
	iStream.read( m_TargetX);
	iStream.read( m_TargetY);
	iStream.read( m_Grade);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK3::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// 최적화 작업시 실제 크기를 명시하도록 한다.
	oStream.write( m_ObjectID );
	oStream.write( m_SkillType );
	oStream.write( m_TargetX);
	oStream.write( m_TargetY);
	oStream.write( m_Grade);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCSkillToObjectOK3::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCSkillToObjectOK3Handler::execute( this , pPlayer );
		
	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
std::string GCSkillToObjectOK3::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCSkillToObjectOK3("
		<< "SkillType:" << (int)m_SkillType 
		<< ",ObjectID:" << (int)m_ObjectID 
		<< ",TargetXY:" << m_TargetX << "," << m_TargetY 
		<< ",Grade:" << m_Grade 
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif