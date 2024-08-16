//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromGQuestInventory.cpp 
// Written By  : excel96
// Description : 
// �κ��丮 ���� �������� ����� ��, Ŭ���̾�Ʈ�� X, Y �� ObjectID��
// ������ ������ Ŭ������ ����, ������ �̿� �´� �ڵ带 ó���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGUseItemFromGQuestInventory.h"

void CGUseItemFromGQuestInventory::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_Index);

	__END_CATCH
}
		    
void CGUseItemFromGQuestInventory::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	oStream.write(m_Index);

	__END_CATCH
}
void CGUseItemFromGQuestInventory::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
#ifndef __GAME_CLIENT__
	CGUseItemFromGQuestInventoryHandler::execute (this , pPlayer);
#endif		
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
string CGUseItemFromGQuestInventory::toString () 
	const throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "CGUseItemFromGQuestInventory("
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif