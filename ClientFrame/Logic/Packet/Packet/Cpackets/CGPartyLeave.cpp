//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPartyLeave.cpp 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGPartyLeave.h"

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGPartyLeave::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE name_length = 0;
	iStream.read(name_length);
	if (name_length > 0)
	{
		iStream.read(m_TargetName, name_length);
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void CGPartyLeave::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY

	BYTE name_length = m_TargetName.size();
	oStream.write(name_length);
	if (name_length > 0)
	{
		oStream.write(m_TargetName);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void CGPartyLeave::execute (Player * pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	#ifndef __GAME_CLIENT__
		CGPartyLeaveHandler::execute (this , pPlayer);
	#endif
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug std::string
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
std::string CGPartyLeave::toString () 
	const throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "CGPartyLeave(" 
		<< "TargetName:" << m_TargetName
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif