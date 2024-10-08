//////////////////////////////////////////////////////////////////////////////
// Filename    : NPCInfo.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "NPCInfo.h"
#include "MCreatureTable.h"
#include "MZone.h"
//////////////////////////////////////////////////////////////////////////////
// class NPCInfo member methods
//////////////////////////////////////////////////////////////////////////////


NPCInfo::NPCInfo()
{
	m_Name  = "";
	m_NPCID = 0;
	m_X     = 0;
	m_Y     = 0;
}

NPCInfo::~NPCInfo()
{
}

void NPCInfo::read(SocketInputStream& iStream)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	BYTE m_NameLength = 0;
	iStream.read( m_NameLength );

	if (m_NameLength > 0)
	{
		iStream.read( m_Name, m_NameLength );
		iStream.read( m_NPCID );
		iStream.read( m_X );
		iStream.read( m_Y );
	}
	__END_CATCH
}

void NPCInfo::write(SocketOutputStream& oStream) const
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	BYTE m_NameLength = m_Name.size();
	oStream.write(m_NameLength);

	if (m_NameLength > 0)
	{
		oStream.write( m_Name );
		oStream.write( m_NPCID );
		oStream.write( m_X );
		oStream.write( m_Y );
	}
	
	__END_CATCH
}

