//////////////////////////////////////////////////////////////////////
// 
// Filename    : CGSetVampireHotKey.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "CGSetVampireHotKey.h"

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void CGSetVampireHotKey::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	for( int i = 0; i < 8; i++ ) {
		iStream.read( m_HotKey[i] );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void CGSetVampireHotKey::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	for ( int i = 0; i < 8; i++ ) {
		oStream.write( m_HotKey[i] );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void CGSetVampireHotKey::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	#ifndef __GAME_CLIENT__
		CGSetVampireHotKeyHandler::execute ( this , pPlayer );
	#endif
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string CGSetVampireHotKey::toString () const
		throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "CGSetVampireHotKey("
			<< "F5:" << (int)m_HotKey[1]
			<< "F6:" << (int)m_HotKey[2]
			<< "F7:" << (int)m_HotKey[3]
			<< "F8:" << (int)m_HotKey[4]
			<< "F9:" << (int)m_HotKey[5]
			<< ",F10:" << (int)m_HotKey[6]
			<< ",F11:" << (int)m_HotKey[7]
			<< ",F12:" << (int)m_HotKey[8]
			<< ")";

		return msg.toString();

		__END_CATCH
	}
#endif