//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGReloadFromQuickSlot.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGReloadFromQuickSlot.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CGReloadFromQuickSlot::CGReloadFromQuickSlot () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CGReloadFromQuickSlot::~CGReloadFromQuickSlot () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CGReloadFromQuickSlot::read ( SocketInputStream & iStream ) 
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
void CGReloadFromQuickSlot::write ( SocketOutputStream & oStream ) const 
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
void CGReloadFromQuickSlot::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGReloadFromQuickSlotHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGReloadFromQuickSlot::toString () 
		const throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "CGReloadFromQuickSlot( ObjectID : " << (int)m_ObjectID 
			<< ",SlotID: " << (int)m_SlotID 
			<< ")";
		return msg.toString();

		__END_CATCH
	}

	// global variable definition
	//CGReloadFromQuickSlotFactory g_CGReloadFromQuickSlotFactory;
#endif
