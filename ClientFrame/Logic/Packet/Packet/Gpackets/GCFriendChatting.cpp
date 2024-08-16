//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCSay.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCFriendChatting.h"


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
GCFriendChatting::GCFriendChatting()
{

	m_Command = 0;
	m_IsBlack = 0;
	m_IsOnLine = 0;
}
void GCFriendChatting::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	cout<<"read1"<<endl;
	iStream.read( m_Command );

	cout<<"read2"<<endl;
	BYTE szPlayerName;
	iStream.read( szPlayerName );
	if ( szPlayerName>32 )
		throw InvalidProtocolException("PlayerName Lenth error");
	if(szPlayerName>0)
		iStream.read(m_PlayerName, szPlayerName);

	cout<<"read3"<<endl;
	WORD szMessage;
	iStream.read( szMessage);
	if ( szMessage > 512 )
		throw InvalidProtocolException("Too large Message length");
	if(szMessage>0)
		iStream.read( m_Message , szMessage );

	cout<<"read4"<<endl;
	iStream.read(m_IsBlack);
	iStream.read(m_IsOnLine);

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCFriendChatting::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_Command );

	BYTE szPlayerName = m_PlayerName.size();
	if(szPlayerName>32)
		throw InvalidProtocolException("Too Large PlayerName Lenth");
	oStream.write(szPlayerName);
	if(szPlayerName>0)
		oStream.write(m_PlayerName);

	WORD szMessage = m_Message.size();
	if(szMessage>512)
		throw InvalidProtocolException("Too Large Message Lenth");
	oStream.write(szMessage);
	if(szMessage>0)
		oStream.write(m_Message);

	oStream.write(m_IsBlack);
	oStream.write(m_IsOnLine);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCFriendChatting::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		 
	GCFriendChattingHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCFriendChatting::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCFriendChatting("
		<< "Command:" << m_Command 
		<< ",PlayerName:" << m_PlayerName
		<< ",Message:" << m_Message 
		<< ",m_IsBlack:"<<m_IsBlack
		<< ",m_IsOnLine:"<<m_IsOnLine
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}