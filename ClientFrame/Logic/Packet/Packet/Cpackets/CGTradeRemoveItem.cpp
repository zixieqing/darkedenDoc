////////////////////////////////////////////////////////////////////////////////
// Filename    : CGTradeRemoveItem.cpp 
// Written By  : �輺��
// Description : 
////////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGTradeRemoveItem.h"

////////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
////////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItem::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_TargetObjectID );
	iStream.read( m_ItemObjectID );

	__END_CATCH
}

		    
////////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
////////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItem::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_TargetObjectID );
	oStream.write( m_ItemObjectID  );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// execute packet's handler
////////////////////////////////////////////////////////////////////////////////
void CGTradeRemoveItem::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGTradeRemoveItemHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug std::string
////////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGTradeRemoveItem::toString () 
		const throw ()
	{
		__BEGIN_TRY

		StringStream msg;
		msg << "CGTradeRemoveItem(" 
			<< "TargetObjectID : " << (int)m_TargetObjectID << ","
			<< "ItemObjectID : " << (int)m_ItemObjectID
			<< ")";
		return msg.toString();

		__END_CATCH
	}
#endif