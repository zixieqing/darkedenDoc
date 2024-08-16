//////////////////////////////////////////////////////////////////////
// 
// Filename    : RCStatusHP.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "RCStatusHP.h"


RCStatusHP::RCStatusHP()
{
	m_CurrentHP = m_MaxHP = 0;
}

//////////////////////////////////////////////////////////////////////
// Datagram ��ü�κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void RCStatusHP::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	// Name
	BYTE szName;

	iDatagram.read( szName );

	//if ( szName == 0 )
	//	throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long Name length");

	if (szName > 0)
	{
		iDatagram.read( m_Name , szName );
	}

	// 
	iDatagram.read( m_MaxHP);
	iDatagram.read( m_CurrentHP );	

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// Datagram ��ü�� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void RCStatusHP::write ( Datagram & oDatagram ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	// Name
	BYTE szName = m_Name.size();

	//if ( szName == 0 )
	//	throw InvalidProtocolException("szName == 0");

	if ( szName > 20 )
		throw InvalidProtocolException("too long Name length");

	oDatagram.write( szName );

	if (szName > 0)
	{
		oDatagram.write( m_Name );
	}

	oDatagram.write( m_MaxHP );
	oDatagram.write( m_CurrentHP );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void RCStatusHP::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	RCStatusHPHandler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string RCStatusHP::toString () const
		throw ()
	{
		StringStream msg;
		
		msg << "RCStatusHP( "
			<< ",CurrentHP: " << (int)m_CurrentHP
			<< ",MaxHP: " << (int)m_MaxHP
			<< ")";


		return msg.toString();
	}
#endif

