//////////////////////////////////////////////////////////////////////
// 
// Filename    : CRRequest.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ٸ� Ŭ���̾�Ʈ���� ������ ��û�ϴ°Ŵ�.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CRRequest2.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CRRequest2::CRRequest2 () 
     throw ()
{
	__BEGIN_TRY

	m_Code = CR_REQUEST2_NULL;

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CRRequest2::~CRRequest2 () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CRRequest2::read ( Datagram & iDatagram ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE code;
	iDatagram.read( code);
	m_Code = (CR_REQUEST_CODE2)code;

	BYTE num;
	iDatagram.read( num );

	if (num > 20)
		throw InvalidProtocolException("szRequestName>20");
	
	if (num > 0)
	{
		iDatagram.read( m_RequestName, num );
	}
		
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CRRequest2::write ( Datagram & oDatagram )  
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE code = (BYTE)m_Code;
	oDatagram.write( code);

	
	BYTE num = m_RequestName.size();
	
	if (num > 20)
		throw InvalidProtocolException("szRequestName>20");

	oDatagram.write( num );

	if (num > 0)
	{
		oDatagram.write( m_RequestName );	
	}

	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void CRRequest2::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CRRequest2Handler::execute( this );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CRRequest2::toString () 
		const throw ()
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "CRRequest2( "
			<< "code: " << (int)m_Code
			<< "RequestName: " << m_RequestName
			<< ")";

		return msg.toString();

		__END_CATCH
	}

#endif