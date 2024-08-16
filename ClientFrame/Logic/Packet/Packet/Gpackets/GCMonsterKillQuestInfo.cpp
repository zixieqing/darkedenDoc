//////////////////////////////////////////////////////////////////////////////
// Filename    : GCMonsterKillQuestInfo.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "GCMonsterKillQuestInfo.h"
#include "Assert.h"

const int GCMonsterKillQuestInfo::szQuestInfo = szQuestID + szSpriteType + szWORD + szDWORD;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCMonsterKillQuestInfo::~GCMonsterKillQuestInfo() 
	throw ()
{
	__BEGIN_TRY 

	std::list<QuestInfo*>::iterator itr = m_QuestInfoList.begin();
	std::list<QuestInfo*>::iterator endItr = m_QuestInfoList.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( (*itr) != NULL ) 
		{
			delete (*itr);
			(*itr) = NULL;			
		}
	}

	m_QuestInfoList.clear();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCMonsterKillQuestInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE num;

	iStream.read( num );

	for ( int i=0; i<num; ++i )
	{
		QuestInfo* pQI = new QuestInfo;
		iStream.read( pQI->questID );
		iStream.read( pQI->sType );
		iStream.read( pQI->goal );
		iStream.read( pQI->timeLimit );

		addQuestInfo( pQI );
	}

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCMonsterKillQuestInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	Assert( m_QuestInfoList.size() <= maxQuestNum );

	BYTE num = m_QuestInfoList.size();

	oStream.write(num);

	std::list<QuestInfo*>::const_iterator itr = m_QuestInfoList.begin();

	for ( int i=0; i<num; i++ )
	{
		oStream.write( (*itr)->questID );
		oStream.write( (*itr)->sType );
		oStream.write( (*itr)->goal );
		oStream.write( (*itr)->timeLimit );

		itr++;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCMonsterKillQuestInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMonsterKillQuestInfoHandler::execute( this , pPlayer );

	__END_CATCH
}

PacketSize_t GCMonsterKillQuestInfo::getPacketSize() const
	throw()
{
	__BEGIN_TRY

	PacketSize_t result = 0;

	result += szBYTE + szQuestInfo * m_QuestInfoList.size();

	return result;

	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
//////////////////////////////////////////////////////////////////////////////
// get packet's debug std::string
//////////////////////////////////////////////////////////////////////////////
std::string GCMonsterKillQuestInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCMonsterKillQuestInfo(";

	std::list<QuestInfo*>::const_iterator itr = m_QuestInfoList.begin();
	for( ; itr != m_QuestInfoList.end() ; itr++ )
	{
		msg << "< " << (*itr)->questID << ", "
			<< (*itr)->sType << ", "
			<< (*itr)->goal << ", "
			<< (*itr)->timeLimit << " >";
	}
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}
#endif