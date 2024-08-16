//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGThrowItem.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGThrowItem.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CGThrowItem::CGThrowItem () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CGThrowItem::~CGThrowItem () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CGThrowItem::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_TargetObjectID );
	iStream.read( m_InvenX );
	iStream.read( m_InvenY );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CGThrowItem::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
	oStream.write( m_ObjectID );
	oStream.write( m_TargetObjectID );
	oStream.write( m_InvenX );
	oStream.write( m_InvenY );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CGThrowItem::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CGThrowItemHandler::execute( this , pPlayer );
	#endif

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGThrowItem::toString () const
		   throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		
		msg << "CGThrowItem( ObjectID :" << (int)m_ObjectID 
    		<< ", TargetObjectID :" << (int)m_TargetObjectID 
			<< ", InvenX " << (int)m_InvenX
			<< ", InvenY " << (int)m_InvenY
			<< ")" ;

		
		return msg.toString();

		__END_CATCH
	}
#endif
