//////////////////////////////////////////////////////////////////////////////
// Filename    : CGThrowBomb.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGThrowBomb.h"

void CGThrowBomb::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ZoneX);
	iStream.read(m_ZoneY);
	iStream.read(m_BombX);
	iStream.read(m_BombY);
	iStream.read(m_AttackSlayerFlag);

	__END_CATCH
}

void CGThrowBomb::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_ZoneX);
	oStream.write(m_ZoneY);
	oStream.write(m_BombX);
	oStream.write(m_BombY);
	oStream.write(m_AttackSlayerFlag);

	__END_CATCH
}

void CGThrowBomb::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifndef __GAME_CLIENT__
	CGThrowBombHandler::execute(this , pPlayer);
#endif

	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
	std::string CGThrowBomb::toString () const
		   throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "CGThrowBomb("
			<< "ZoneX:" << (int)m_ZoneX
			<< ",ZoneY:" << (int)m_ZoneY
			<< ",BombX:" << (int)m_BombX
			<< ",BombY:" << (int)m_BombY
			<< ",AttackerSlayerFlag:" << (int)m_AttackSlayerFlag
			<< ")" ;
		return msg.toString();

		__END_CATCH
	}
#endif