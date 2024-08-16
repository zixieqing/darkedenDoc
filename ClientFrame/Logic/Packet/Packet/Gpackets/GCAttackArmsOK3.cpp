//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAttackArmsOK3.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCAttackArmsOK3.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAttackArmsOK3::GCAttackArmsOK3 ()
     throw ()
{
	__BEGIN_TRY

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAttackArmsOK3::~GCAttackArmsOK3 ()
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK3::read ( SocketInputStream & iStream )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_SkillType );
	iStream.read( m_ObjectID );
//	iStream.read( m_TargetObjectID );
	iStream.read( m_X);
	iStream.read( m_Y );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK3::write ( SocketOutputStream & oStream )
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_SkillType );
	oStream.write( m_ObjectID );
//	oStream.write( m_TargetObjectID );
	oStream.write( m_X);
	oStream.write( m_Y);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCAttackArmsOK3::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAttackArmsOK3Handler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCAttackArmsOK3::toString () 
		const throw ()
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCAttackArmsOK3(ObjectID: " << (int)m_ObjectID 
	//		<< ",TargetObjectID: " << (int)m_TargetObjectID << ",Success: "<< m_bSuccess
			<< ",TargetXY: " << (int)m_X<<","<<(int)m_Y
			<< ")";

		return msg.toString();

		__END_CATCH
	}
#endif