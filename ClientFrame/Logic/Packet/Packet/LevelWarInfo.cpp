//////////////////////////////////////////////////////////////////////
// 
// Filename    : WarInfo.cpp 
// Written By  : 
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "LevelWarInfo.h"

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void LevelWarInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read( m_Level );
	WarInfo::read( iStream );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void LevelWarInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write( m_Level );
	WarInfo::write( oStream );

	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
std::string LevelWarInfo::toString () const
	throw ()
{
	StringStream msg;

	msg << "LevelWarInfo("
		<< "Level: " << m_Level
		<< ",RemainTime:" << (int)m_RemainTime
		<< ")";

	return msg.toString();
}

#endif