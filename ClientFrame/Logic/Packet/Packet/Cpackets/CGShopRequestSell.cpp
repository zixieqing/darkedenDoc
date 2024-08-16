////////////////////////////////////////////////////////////////////////////////
// Filename    : CGShopRequestSell.cpp 
// Written By  : �輺��
// Description : 
// �÷��̾�� �ڽ��� ������ �ִ� �������� ���� NPC����
// �ȱ⸦ ��û�� �� ���̴� ��Ŷ�̴�.
////////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGShopRequestSell.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

////////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void CGShopRequestSell::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	iStream.read( m_ItemObjectID );
	iStream.read( m_OpCode );

	__END_CATCH
}

		    
////////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
////////////////////////////////////////////////////////////////////////////////
void CGShopRequestSell::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_ObjectID );
	oStream.write( m_ItemObjectID );
	oStream.write( m_OpCode );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// execute packet's handler
////////////////////////////////////////////////////////////////////////////////
void CGShopRequestSell::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGShopRequestSellHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug std::string
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
std::string CGShopRequestSell::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGShopRequestSell( ObjectID : " << (int)m_ObjectID << ")";
	return msg.toString();

	__END_CATCH
}
#endif