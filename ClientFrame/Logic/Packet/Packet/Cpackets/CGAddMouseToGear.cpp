//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAddMouseToGear.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGAddMouseToGear.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CGAddMouseToGear::CGAddMouseToGear () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CGAddMouseToGear::~CGAddMouseToGear () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CGAddMouseToGear::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_SlotID );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CGAddMouseToGear::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID ); 
	oStream.write( m_SlotID );
 
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CGAddMouseToGear::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGAddMouseToGearHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGAddMouseToGear::toString () 
		const throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "CGAddMouseToGear( ObjectID : " << (int)m_ObjectID 
			<< ",SlotID" << (int)m_SlotID
			<< ")";
		return msg.toString();

		__END_CATCH
	}

	// global variable definition
	//CGAddMouseToGearFactory g_CGAddMouseToGearFactory;
#endif
