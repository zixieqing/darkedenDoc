//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGAddQuickSlotToMouse.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGAddQuickSlotToMouse.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
CGAddQuickSlotToMouse::CGAddQuickSlotToMouse () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
CGAddQuickSlotToMouse::~CGAddQuickSlotToMouse () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CGAddQuickSlotToMouse::read ( SocketInputStream & iStream ) 
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
void CGAddQuickSlotToMouse::write ( SocketOutputStream & oStream ) const 
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
void CGAddQuickSlotToMouse::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGAddQuickSlotToMouseHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGAddQuickSlotToMouse::toString () 
		const throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;

		msg << "CGAddQuickSlotToMouse( ObjectID : " << (int)m_ObjectID 
			<< ",SlotID : " << (int)m_SlotID
			<< ")";

		return msg.toString();

		__END_CATCH
	}

	// global variable definition
	//CGAddQuickSlotToMouseFactory g_CGAddQuickSlotToMouseFactory;
#endif
