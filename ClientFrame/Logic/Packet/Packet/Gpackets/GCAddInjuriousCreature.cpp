//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddInjuriousCreature.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCAddInjuriousCreature.h"

void GCAddInjuriousCreature::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// �̸� �б�
	BYTE szName;

	iStream.read(szName);

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 10)
		throw InvalidProtocolException("too large name length");

	iStream.read(m_Name , szName);

	__END_CATCH
}
		    
void GCAddInjuriousCreature::write (SocketOutputStream & oStream) const 
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	// �̸� ����
	BYTE szName = m_Name.size();

	if (szName == 0)
		throw InvalidProtocolException("szName == 0");

	if (szName > 10)
		throw InvalidProtocolException("too large name length");

	oStream.write(szName);

	oStream.write(m_Name);

	__END_CATCH
}

void GCAddInjuriousCreature::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	GCAddInjuriousCreatureHandler::execute(this , pPlayer);

	__END_CATCH
}


#ifdef __DEBUG_OUTPUT__
	std::string GCAddInjuriousCreature::toString () const
		   throw ()
	{
		__BEGIN_TRY
			
		StringStream msg;
		msg << "GCAddInjuriousCreature(Name :" << m_Name 
			<< ")" ;
		return msg.toString();

		__END_CATCH
	}
#endif