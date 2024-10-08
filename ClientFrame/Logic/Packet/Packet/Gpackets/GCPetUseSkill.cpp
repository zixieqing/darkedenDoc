//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPetUseSkill.cpp 
// Written By  : elca@ewestsoft.com
// Description : 자신에게 쓰는 기술의 성공을 알리기 위한 패킷 클래스의
//               멤버 정의.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCPetUseSkill.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCPetUseSkill::GCPetUseSkill () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCPetUseSkill::~GCPetUseSkill () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////
void GCPetUseSkill::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read(m_Attacker);
	iStream.read(m_Target);
	
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////
void GCPetUseSkill::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_Attacker);
	oStream.write(m_Target);
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCPetUseSkill::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCPetUseSkillHandler::execute( this , pPlayer );
		
	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCPetUseSkill::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCPetUseSkill("
		<< ")";
	return msg.toString();

	__END_CATCH
}

#endif