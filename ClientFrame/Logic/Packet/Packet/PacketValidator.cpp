//----------------------------------------------------------------------
//
// Filename    : PacketValidator.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include "PacketValidator.h"

//----------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------
PacketValidator::PacketValidator () 
	throw ()
{
	__BEGIN_TRY

	m_PacketIDSets.reserve(PLAYER_STATUS_MAX);

	for ( uint i = 0 ; i < PLAYER_STATUS_MAX ; i ++ ) {
		m_PacketIDSets[i] = NULL;
	}

	__END_CATCH
}

//----------------------------------------------------------------------
// destructor
//----------------------------------------------------------------------
PacketValidator::~PacketValidator () 
	throw ()
{
	__BEGIN_TRY

	for ( uint i = 0 ; i < PLAYER_STATUS_MAX ; i ++ ) {
		if ( m_PacketIDSets[i] != NULL ) {
			delete m_PacketIDSets[i];
			m_PacketIDSets[i] = NULL;
		}
	}

	m_PacketIDSets.clear();

	__END_CATCH
}

//----------------------------------------------------------------------
// initialize packet validators
//----------------------------------------------------------------------
void PacketValidator::init ()
	throw ( Error )
{
	__BEGIN_TRY

	PacketIDSet * pPacketIDSet = NULL;

	__BEGIN_DEBUG

#if defined(__GAME_CLIENT__)

		//----------------------------------------------------------------------
		// CPS_NONE
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_NONE , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_BEGIN_SESSION ( �α��� ��Ŷ�� ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_BEGIN_SESSION , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CL_LOGIN ( CLLogin �� ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CL_LOGIN );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_VERSION_CHECK_OK );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_VERSION_CHECK_ERROR );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_LOGIN_OK );
		//pPacketIDSet->addPacketID( Packet::PACKET_LC_GUEST_LOGIN_OK );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_LOGIN_ERROR );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_WORLD_LIST );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_SERVER_LIST );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CL_QUERY_PLAYER_ID ( CLQueryPlayerID �� ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CL_QUERY_PLAYER_ID );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_QUERY_RESULT_PLAYER_ID );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CL_REGISTER_PLAYER ( CLRegisterPlayer �� ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CL_REGISTER_PLAYER );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_VERSION_CHECK_OK );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_VERSION_CHECK_ERROR );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_REGISTER_PLAYER_OK );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_REGISTER_PLAYER_ERROR );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CL_GET_PC_LIST ( CLGetPCList �� ���� ���� )
		// CLChangeServer�� ���� ���Ŀ��� �� ���¸� �����ϵ��� �Ѵ�.
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CL_GET_PC_LIST );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_PC_LIST );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_SERVER_LIST );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CL_CREATE_PC ( CLCreatePC �� ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CL_CREATE_PC );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_CREATE_PC_OK );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_CREATE_PC_ERROR );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CL_DELETE_PC ( CLDeletePC �� ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CL_DELETE_PC );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_DELETE_PC_OK );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_DELETE_PC_ERROR );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CL_SELECT_PC ( CLSelectPC �� ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CL_SELECT_PC );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_RECONNECT );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_SELECT_PC_ERROR );
		pPacketIDSet->addPacketID( Packet::PACKET_LC_QUERY_RESULT_CHARACTER_NAME );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_AFTER_SENDING_CG_CONNECT
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_AFTER_SENDING_CG_CONNECT );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_UPDATE_INFO );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_DISCONNECT );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_SYSTEM_AVAILABILITIES );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_WAITING_FOR_LOADING
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_WAITING_FOR_LOADING , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_WAITING_FOR_GC_SET_POSITION
		//----------------------------------------------------------------------
		// 2002.2.2 , PacketIDSet::PIST_IGNORE_EXCEPT �߰�
		pPacketIDSet = new PacketIDSet( CPS_WAITING_FOR_GC_SET_POSITION, PacketIDSet::PIST_IGNORE_EXCEPT );		
		pPacketIDSet->addPacketID( Packet::PACKET_GC_SET_POSITION );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_INVITE );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_LEAVE );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_JOINED );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_ERROR );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_WAITING_FOR_GC_RECONNECT_LOGIN
		//----------------------------------------------------------------------
		// 2002.2.2 , PacketIDSet::PIST_IGNORE_EXCEPT �߰�
		pPacketIDSet = new PacketIDSet( CPS_WAITING_FOR_GC_RECONNECT_LOGIN, PacketIDSet::PIST_IGNORE_EXCEPT );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_RECONNECT_LOGIN );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_INVITE );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_LEAVE );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_JOINED );
		pPacketIDSet->addPacketID( Packet::PACKET_GC_PARTY_ERROR );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );


		//----------------------------------------------------------------------
		// CPS_NORMAL (���ӿ� ����!)
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_NORMAL , PacketIDSet::PIST_ANY );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// CPS_END_SESSION
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_END_SESSION , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );


		//----------------------------------------------------------------------
		//						Request Server/Client
		//----------------------------------------------------------------------
		// ���� �ϱ� ��
		//----------------------------------------------------------------------		,
		pPacketIDSet = new PacketIDSet( CPS_REQUEST_SERVER_BEGIN_SESSION);
		pPacketIDSet->addPacketID( Packet::PACKET_CR_CONNECT );
		pPacketIDSet->addPacketID( Packet::PACKET_CR_REQUEST );
		pPacketIDSet->addPacketID( Packet::PACKET_CR_WHISPER );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );		

		//----------------------------------------------------------------------
		// ���� �ϱ� ��
		//----------------------------------------------------------------------		,
		pPacketIDSet = new PacketIDSet( CPS_REQUEST_CLIENT_BEGIN_SESSION , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// RequestServer�� ���� ��û ��
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_REQUEST_CLIENT_AFTER_SENDING_CONNECT );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_CONNECT_VERIFY );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_REQUEST_VERIFY );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );
		
		//----------------------------------------------------------------------
		// RequestServer���� ����
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_REQUEST_SERVER_NORMAL );
		pPacketIDSet->addPacketID( Packet::PACKET_CR_REQUEST );
		pPacketIDSet->addPacketID( Packet::PACKET_CR_DISCONNECT );
		pPacketIDSet->addPacketID( Packet::PACKET_CR_WHISPER );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );
		
		//----------------------------------------------------------------------
		// RequestClient���� ����
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_REQUEST_CLIENT_NORMAL );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_REQUEST_VERIFY );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_REQUESTED_FILE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// Client Communication ����
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( CPS_CLIENT_COMMUNICATION_NORMAL );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_POSITION_INFO );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_SAY );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_STATUS_HP );
		pPacketIDSet->addPacketID( Packet::PACKET_RC_CHARACTER_INFO );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );


#elif defined(__LOGIN_SERVER__)

		//----------------------------------------------------------------------
		// LPS_NONE
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( LPS_NONE , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// LPS_BEGIN_SESSION ( �α��� ������ ������ ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( LPS_BEGIN_SESSION );
//		pPacketIDSet->addPacketID( Packet::PACKET_CL_QUERY_PLAYER_ID );
//		pPacketIDSet->addPacketID( Packet::PACKET_CL_REGISTER_PLAYER );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_LOGIN );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_RECONNECT_LOGIN );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_VERSION_CHECK );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// LPS_WAITING_FOR_CL_GET_PC_LIST ( ����� ������ ���� ���� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( LPS_WAITING_FOR_CL_GET_PC_LIST );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_GET_PC_LIST );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );
	
		//----------------------------------------------------------------------
		// LPS_WAITING_FOR_CL_REGISTER_PLAYER
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( LPS_WAITING_FOR_CL_REGISTER_PLAYER );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_REGISTER_PLAYER );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_QUERY_PLAYER_ID );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );
	
		//----------------------------------------------------------------------
		// LPS_PC_MANAGEMENT
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( LPS_PC_MANAGEMENT );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_CREATE_PC );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_DELETE_PC );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_SELECT_PC );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_LOGOUT );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_CHANGE_SERVER );
		pPacketIDSet->addPacketID( Packet::PACKET_CL_GET_SERVER_LIST );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );
	
		//----------------------------------------------------------------------
		// LPS_AFTER_SENDING_LG_INCOMING_CONNECTION
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( LPS_AFTER_SENDING_LG_INCOMING_CONNECTION , PacketIDSet::PIST_IGNORE_EXCEPT );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// LPS_END_SESSION
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( LPS_END_SESSION , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

#elif defined(__GAME_SERVER__)

		//----------------------------------------------------------------------
		// GPS_NONE
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( GPS_NONE , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// GPS_BEGIN_SESSION
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( GPS_BEGIN_SESSION );
		pPacketIDSet->addPacketID( Packet::PACKET_CG_CONNECT );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// GPS_WAITING_FOR_CG_READY
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( GPS_WAITING_FOR_CG_READY , PacketIDSet::PIST_IGNORE_EXCEPT );
		pPacketIDSet->addPacketID( Packet::PACKET_CG_READY );
		pPacketIDSet->addPacketID( Packet::PACKET_CG_SET_HOT_KEY );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// GPS_NORMAL ( �ε��� ��ġ�� ���ӿ� ���� �ٷ��� )
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( GPS_NORMAL , PacketIDSet::PIST_ANY );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// GPS_IGNORE_ALL ( �ƹ� ��Ŷ�� ���� �ʰ� �� �����ϴ� ���´�.. fucksuck)
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( GPS_IGNORE_ALL , PacketIDSet::PIST_IGNORE_EXCEPT );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

		//----------------------------------------------------------------------
		// GPS_AFTER_SENDING_GL_INCOMING_CONNECTION
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( GPS_AFTER_SENDING_GL_INCOMING_CONNECTION , PacketIDSet::PIST_IGNORE_EXCEPT );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );
	
		//----------------------------------------------------------------------
		// GPS_END_SESSION
		//----------------------------------------------------------------------
		pPacketIDSet = new PacketIDSet( GPS_END_SESSION , PacketIDSet::PIST_NONE );
		addPacketIDSet( pPacketIDSet->getPlayerStatus(), pPacketIDSet );

#endif

	__END_DEBUG

	__END_CATCH
}

//----------------------------------------------------------------------
// add packet id set
//----------------------------------------------------------------------
void PacketValidator::addPacketIDSet ( PlayerStatus playerStatus , PacketIDSet * pPacketIDSet ) 
	throw ( DuplicatedException , Error )
{
	__BEGIN_TRY

	if ( playerStatus >= PLAYER_STATUS_MAX )
		throw Error("invalid player status");

	if ( m_PacketIDSets[playerStatus] != NULL )
		throw DuplicatedException();

	m_PacketIDSets[playerStatus] = pPacketIDSet;

	__END_CATCH
}

//----------------------------------------------------------------------
// delete packet id set
//----------------------------------------------------------------------
void PacketValidator::deletePacketIDSet ( PlayerStatus playerStatus , PacketIDSet * pPacketIDSet ) 
	throw ( NoSuchElementException , Error )
{
	__BEGIN_TRY

	if ( playerStatus >= PLAYER_STATUS_MAX )
		throw Error("invalid player status");

	if ( m_PacketIDSets[playerStatus] == NULL )
		throw NoSuchElementException("invalid player status");

	m_PacketIDSets[playerStatus] = NULL;

	__END_CATCH
}

//----------------------------------------------------------------------
// is valid packet?
//----------------------------------------------------------------------
bool PacketValidator::isValidPacketID ( PlayerStatus playerStatus , PacketID_t packetID ) 
	throw ( NoSuchElementException , IgnorePacketException , Error )
{
	__BEGIN_TRY

	if ( playerStatus >= PLAYER_STATUS_MAX )
		throw Error("invalid player status");

	if ( m_PacketIDSets[playerStatus] == NULL )
		throw NoSuchElementException("invalid player status");

	return m_PacketIDSets[playerStatus]->hasPacketID(packetID);

	__END_CATCH
}

//----------------------------------------------------------------------
// get debug string
//----------------------------------------------------------------------
#ifdef __DEBUG_OUTPUT__
	std::string PacketValidator::toString () const
		throw ()
	{
		StringStream msg;

		msg << "PacketValidator(\n";

		for ( uint i = 0 ; i < PLAYER_STATUS_MAX ; i ++ )
		{
			msg << i << " : ";
			msg << ( ( m_PacketIDSets[i] != NULL ) ? m_PacketIDSets[i]->toString() : "NULL" );
		}

		msg << ")";

		return msg.toString();
	}
#endif

//----------------------------------------------------------------------
// global variable definition
//----------------------------------------------------------------------
PacketValidator * g_pPacketValidator = NULL;
