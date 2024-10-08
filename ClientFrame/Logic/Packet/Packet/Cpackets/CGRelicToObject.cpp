//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRelicToObject.cpp 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "CGRelicToObject.h"

CGRelicToObject::CGRelicToObject () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

CGRelicToObject::~CGRelicToObject () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

void CGRelicToObject::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	iStream.read(m_ItemObjectID);
	iStream.read(m_ObjectID);
	iStream.read(m_X);
	iStream.read(m_Y);

	__END_CATCH
}

void CGRelicToObject::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	oStream.write(m_ItemObjectID);
	oStream.write(m_ObjectID);
	oStream.write(m_X);
	oStream.write(m_Y);

	__END_CATCH
}

void CGRelicToObject::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
#ifndef __GAME_CLIENT__		
	CGRelicToObjectHandler::execute(this , pPlayer);
#endif
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
std::string CGRelicToObject::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
    msg << "CGRelicToObject("
		<< "X:"         << (int)m_X 
		<< ",Y:"        << (int)m_Y
		<< ",ItemObjectID:" << (int)m_ItemObjectID
		<< ",ObjectID:" << (int)m_ObjectID
	   	<< ")" ;
	return msg.toString();

	__END_CATCH
}
#endif