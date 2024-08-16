//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddItemToItemVerify.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCAddItemToItemVerify.h"

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCAddItemToItemVerify::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
		case ADD_ITEM_TO_ITEM_REMOVE_OPTION_OK:		//by svi 2009-07-15
			iStream.read(m_Parameter);
			break;
// add by svi 2009-06-28			
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
// end
			// add by Coffee 2006.11.3
		case ADD_ITEM_TO_ITEM_VERIFY_THREE_ENCHANT_OK:
			iStream.read(m_Parameter);
			iStream.read(m_Parameter2);
			break;

		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH:
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL:
		default:
			break;
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCAddItemToItemVerify::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_Code);

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
			oStream.write(m_Parameter);
			break;

		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL:
		default:
			break;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCAddItemToItemVerify::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddItemToItemVerifyHandler::execute( this , pPlayer );
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ��Ŷ ������
//////////////////////////////////////////////////////////////////////////////

PacketSize_t GCAddItemToItemVerify::getPacketSize () const 
	throw() 
{
	__BEGIN_TRY

	PacketSize_t size = szBYTE;

	switch (m_Code)
	{
		// �Ķ���͸� ��� �ϴ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_DECREASE :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_DETACHING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_MIXING_OK :
		case ADD_ITEM_TO_ITEM_VERIFY_REVIVAL_OK:
			size += szuint;
			break;
		// add by Coffee 2006.11.3
		case ADD_ITEM_TO_ITEM_VERIFY_UP_GRADE_OK:
		case ADD_ITEM_TO_ITEM_VERIFY_THREE_ENCHANT_OK:
			size += szuint + szuint;
			break;
		// �Ķ���͸� ���� �ʾƵ� �Ǵ� �ڵ�
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL_CRASH :
		case ADD_ITEM_TO_ITEM_VERIFY_ENCHANT_FAIL:
		default:
			break;
	}

	return size;

	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
std::string GCAddItemToItemVerify::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddItemToItemVerify(" 
	    << "Code : " << (int)m_Code 
		<< "Parameter : " << (int)m_Parameter
	    << ")";
	return msg.toString();

	__END_CATCH
}
#endif