//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddMonster.cpp 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCAddMonster.h"

//////////////////////////////////////////////////////////////////////////////
// Constructor
//////////////////////////////////////////////////////////////////////////////
GCAddMonster::GCAddMonster()
	throw( Error )
{
	__BEGIN_TRY

	m_pEffectInfo = NULL;
	m_FromFlag = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////////
GCAddMonster::~GCAddMonster()
	throw( Error )
{
	__BEGIN_TRY

	delete m_pEffectInfo;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCAddMonster::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE name_length = 0;

	iStream.read( m_ObjectID );
	iStream.read( m_MonsterType );

	iStream.read( name_length );
	if (name_length != 0) iStream.read( m_MonsterName, name_length );

	iStream.read( m_MainColor );
	iStream.read( m_SubColor );
	iStream.read( m_X );
	iStream.read( m_Y );
	iStream.read( m_Dir );

	m_pEffectInfo = new EffectInfo();
	m_pEffectInfo->read( iStream );

	iStream.read( m_CurrentHP );
	iStream.read( m_MaxHP );

	iStream.read( m_FromFlag );

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCAddMonster::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	BYTE name_length = m_MonsterName.size();

	oStream.write( m_ObjectID );
	oStream.write( m_MonsterType );
	oStream.write( name_length );
	if (m_MonsterName.size() != 0) oStream.write( m_MonsterName );
	oStream.write( m_MainColor );
	oStream.write( m_SubColor );
	oStream.write( m_X );
	oStream.write( m_Y );
	oStream.write( m_Dir );

	m_pEffectInfo->write( oStream );

	oStream.write( m_CurrentHP );
	oStream.write( m_MaxHP );

	oStream.write( m_FromFlag );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCAddMonster::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddMonsterHandler::execute( this , pPlayer );
		
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
std::string GCAddMonster::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddMonster("
		<< "ObjectID:"     << (int)m_ObjectID
		<< ",MonsterType:" << (int)m_MonsterType
		<< ",MonsterName:" << m_MonsterName
		<< ",MainColor:"   << (int)m_MainColor
		<< ",SubColor:"    << (int)m_SubColor
		<< ",X:"           << (int)m_X 
		<< ",Y:"           << (int)m_Y 
		<< ",Dir:"         << Dir2String[m_Dir]
		<< ",Effects:"     << m_pEffectInfo->toString()
		<< ",CurrentHP:"   << (int)m_CurrentHP
		<< ",MaxHP:"       << (int)m_MaxHP
		<< ",FromFlag:"       << (int)m_FromFlag
		<< ")" ;
	return msg.toString();

	__END_CATCH
}
#endif