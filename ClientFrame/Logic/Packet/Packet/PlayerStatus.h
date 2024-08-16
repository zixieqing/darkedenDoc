//----------------------------------------------------------------------
//
// Filename    : PlayerStatus.h
// Written By  : Reiot
// Description : 플레이어 상태에 따른 허용 가능한 패킷 아이디의 매핑 정의
//
//----------------------------------------------------------------------

#ifndef __PLAYER_STATUS_H__
#define __PLAYER_STATUS_H__

enum PlayerStatus {

#if defined(__GAME_CLIENT__)

	//----------------------------------------------------------------------
	// ClientPlayer 객체가 생성된 직후
	// Next Packets : NONE
	//----------------------------------------------------------------------
	CPS_NONE ,

	//----------------------------------------------------------------------
	// 로그인 서버에 로그인 정보를 보내기 전
	// Next Packets : LCLoginOK, LCLoginError
	//----------------------------------------------------------------------
	CPS_BEGIN_SESSION ,

	//----------------------------------------------------------------------
	// CLLogin 을 보낸 직후
	// Next Packets : LCLoginOK, LCLoginError
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_LOGIN ,

	//----------------------------------------------------------------------
	// CLQueryPlayerID 을 보낸 직후
	// Next Packets : LCQueryResultPlayerID
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_QUERY_PLAYER_ID,

	//----------------------------------------------------------------------
	// CLRegisterPlayer 을 보낸 직후
	// Next Packets : LCRegisterPlayerOK, LCRegisterPlayerError
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_REGISTER_PLAYER ,

	//----------------------------------------------------------------------
	// CLGetPCList 패킷을 보낸 직후
	// Next Packets : LCPCList
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_GET_PC_LIST ,

	//----------------------------------------------------------------------
	// CLCreatePC 를 보낸 직후
	// Next Packets : LCCreatePCOK
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_CREATE_PC ,

	//----------------------------------------------------------------------
	// CLDeletePC 를 보낸 직후
	// Next Packets : LCDeletePCOK, LCDeletePCError
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_DELETE_PC ,

	//----------------------------------------------------------------------
	// CLSelectPC 를 보낸 직후
	// Next Packets : LCSelectPCOK, LCSelectPCError
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_SELECT_PC ,

	//----------------------------------------------------------------------
	// 게임 서버로 CGConnect 패킷을 보낸다.
	// Next Packets : GCUpdateInfo
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CG_CONNECT ,

	//----------------------------------------------------------------------
	// 로딩이 끝날 때까지 기다린다.
	// Next Packets : NONE
	//----------------------------------------------------------------------
	CPS_WAITING_FOR_LOADING ,

	//----------------------------------------------------------------------
	// CGReady 패킷을 보낸 후, 서버상에서 자신의 위치가 결정되기를 기다린다.
	// Next Packets : GCSetPosition
	//----------------------------------------------------------------------
	CPS_WAITING_FOR_GC_SET_POSITION ,

	//----------------------------------------------------------------------
	// 일반적인 게임 상태
	//----------------------------------------------------------------------
	CPS_NORMAL ,

	//----------------------------------------------------------------------
	// LOGOUT후 CGReconnectLogin
	//----------------------------------------------------------------------
	CPS_WAITING_FOR_GC_RECONNECT_LOGIN ,

	//----------------------------------------------------------------------
	// 로그인/게임 서버와의 연결 종료
	//----------------------------------------------------------------------
	CPS_END_SESSION ,

	//----------------------------------------------------------------------
	//						Request Server/Client
	//----------------------------------------------------------------------
	// 접속 하기 전
	//----------------------------------------------------------------------
	CPS_REQUEST_SERVER_BEGIN_SESSION,
	CPS_REQUEST_CLIENT_BEGIN_SESSION,

	//----------------------------------------------------------------------
	// RequestServer에 접속 요청 후
	//----------------------------------------------------------------------
	CPS_REQUEST_CLIENT_AFTER_SENDING_CONNECT,

	//----------------------------------------------------------------------
	// RequestServer정상 상태
	//----------------------------------------------------------------------
	CPS_REQUEST_SERVER_NORMAL,	
	
	//----------------------------------------------------------------------
	// RequestClient정상 상태
	//----------------------------------------------------------------------
	CPS_REQUEST_CLIENT_NORMAL,	

	//----------------------------------------------------------------------
	//						Client Communication
	//----------------------------------------------------------------------
	CPS_CLIENT_COMMUNICATION_NORMAL,

	/*
	//----------------------------------------------------------------------
	// 게임 게시판 시작
	//----------------------------------------------------------------------
	
	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_SELECT_BOARD
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_SELECT_BOARD,

	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_WRITE_TEXT
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_WRITE_CONTENT,

	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_SELECT_TEXT
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_SELECT_TEXT,

	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_RELPLY_CONTENT
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_REPLY_CONTENT,

	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_SEND_PASSWORD
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_SEND_PASSWORD,

	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_MODIFY_CONTENT
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_MODIFY_CONTENT,
	       
	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_PREV_PAGE
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_PREV_PAGE,
	    
	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_NEXT_PAGE
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_NEXT_PAGE,

	//----------------------------------------------------------------------
	// CPS_AFTER_SENDING_CL_SELECT_LIST
	//----------------------------------------------------------------------
	CPS_AFTER_SENDING_CL_SELECT_LIST,
	//----------------------------------------------------------------------
	// 게임 게시판 끝�

	//----------------------------------------------------------------------
	*/
	
#elif defined(__LOGIN_SERVER__)

	//----------------------------------------------------------------------
	// LoginPlayer 객체가 생성된 직후
	// Next Packets : NONE
	//----------------------------------------------------------------------
	LPS_NONE ,

	//----------------------------------------------------------------------
	// 로그인 서버에 소켓 연결 직후
	// Next Packets : CLLogin
	//----------------------------------------------------------------------
	LPS_BEGIN_SESSION ,

	//----------------------------------------------------------------------
	// 아이디/패스워드 전송 직후
	// Next Packets : CLGetPCList, CLLogout
	//----------------------------------------------------------------------
	LPS_WAITING_FOR_CL_GET_PC_LIST ,				

	//----------------------------------------------------------------------
	// guest 로 로그온했을 경우
	// Next Packets : CLRegisterPlayer, CLQueryPlayerID
	//----------------------------------------------------------------------
	LPS_WAITING_FOR_CL_REGISTER_PLAYER,

	//----------------------------------------------------------------------
	// 캐릭터 관리 상태
	// Next Packets : CLCreatePC, CLDeletePC, CLSelectPC, CLLogout
	//----------------------------------------------------------------------
	LPS_PC_MANAGEMENT ,

	//----------------------------------------------------------------------
	// 게임 서버로 LGIncomingConnection 패킷을 보낸 직후
	// Next Packets : GLIncomingConnectionOK, GLIncomingConnectionError
	//----------------------------------------------------------------------
	LPS_AFTER_SENDING_LG_INCOMING_CONNECTION ,

	//----------------------------------------------------------------------
	// 로그인 서버와의 연결을 종료할때
	// Next Packets : NONE
	//----------------------------------------------------------------------
	LPS_END_SESSION ,


	/*
	//----------------------------------------------------------------------
	// 게임 게시판 시작
	//----------------------------------------------------------------------
	
	//----------------------------------------------------------------------
	// LPS_WAITHING_FOR_CL_SELECT_BOARD
	//----------------------------------------------------------------------
	 LPS_WAITING_FOR_CL_SELECT_BOARD,

	//----------------------------------------------------------------------
	// LPS_AFTER_SENDING_CL_TEXT_LIST
	//----------------------------------------------------------------------
	 LPS_AFTER_SENDING_LC_TEXT_LIST,
		    
	//----------------------------------------------------------------------
	// LPS_AFTER_SENDING_CL_SENDING_CONTENT
	//----------------------------------------------------------------------
	 LPS_AFTER_SENDING_LC_SEND_CONTENT,
	
	//----------------------------------------------------------------------
	// 게임 게시판 끝�

	//----------------------------------------------------------------------
	*/
	
#elif defined(__GAME_SERVER__)

	//----------------------------------------------------------------------
	// GamePlayer 객체가 생성된 직후
	// Next Packets : NONE
	//----------------------------------------------------------------------
	GPS_NONE ,

	//----------------------------------------------------------------------
	// 게임 서버에 소켓 연결 직후
	// Next Packets : CGConnect
	//----------------------------------------------------------------------
	GPS_BEGIN_SESSION ,

	//----------------------------------------------------------------------
	// 사용자 인증 직후 
	// Next Packets : CGReady
	//----------------------------------------------------------------------
	GPS_WAITING_FOR_CG_READY ,

	//----------------------------------------------------------------------
	// 게임에 들어갔다. 이제 아무 패킷이나 와라.
	// Next Packets : ANY
	//----------------------------------------------------------------------
	GPS_NORMAL,

	//----------------------------------------------------------------------
	// 아무 패킷도 받지 않는 상태다. -_-; fuck suck
	//----------------------------------------------------------------------
	GPS_IGNORE_ALL,

	//----------------------------------------------------------------------
	// 로그인 서버로 GLIncomingConnection 패킷을 보낸 직후
	// Next Packets : LGIncomingConnectionOK, LGIncomingConnectionError
	//----------------------------------------------------------------------
	GPS_AFTER_SENDING_GL_INCOMING_CONNECTION ,

	//----------------------------------------------------------------------
	// 게임 서버와의 연결을 종료한다.
	// Next Packets : NONE
	//----------------------------------------------------------------------
	GPS_END_SESSION ,


#elif defined(__UPDATE_SERVER__)

	//----------------------------------------------------------------------
	// UpdateServerPlayer 객체가 생성된 직후
	// Next Packets : NONE
	//----------------------------------------------------------------------
	USPS_NONE,

	//----------------------------------------------------------------------
	// 업데이트 클라이언트와 연결이 된 직후
	// Next Packets : CUBeginUpdate
	//----------------------------------------------------------------------
	USPS_BEGIN_SESSION,

	//----------------------------------------------------------------------
	// UCUpdateList 를 보낸 직후
	// Next Packets : CURequest, CUEndUpdate
	//----------------------------------------------------------------------
	USPS_AFTER_SENDING_UC_UPDATE_LIST,

	//----------------------------------------------------------------------
	// UCUpdate 를 보낸 직후
	// Next Packets : CURequest, CUEndUpdate
	//----------------------------------------------------------------------
	USPS_AFTER_SENDING_UC_UPDATE,

	//----------------------------------------------------------------------
	// CUEndUpdate 를 받은 직후
	// Next Packets : NONE
	//----------------------------------------------------------------------
	USPS_END_SESSION,

#elif defined(__UPDATE_CLIENT__)

	//----------------------------------------------------------------------
	// UpdateClientPlayer 객체가 생성된 직후
	// Next Packets : NONE
	//----------------------------------------------------------------------
	UCPS_NONE ,
	
	//----------------------------------------------------------------------
	// 업데이트 서버에 연결한 직후
	// Next Packets : NONE
	//----------------------------------------------------------------------
	UCPS_BEGIN_SESSION,

	//----------------------------------------------------------------------
	// CUBeginUpdate 패킷을 보낸 직후
	// Next Packets : UCUpdateList
	//----------------------------------------------------------------------
	UCPS_WAITING_FOR_UC_UPDATE_LIST,

	//----------------------------------------------------------------------
	// CURequest 패킷을 보낸 직후
	// Next Packets : UCUpdate
	//----------------------------------------------------------------------
	UCPS_WAITING_FOR_UC_UPDATE,

	//----------------------------------------------------------------------
	// 업데이트 서버와의 연결을 종료한다.
	// Next Packets : NONE
	//----------------------------------------------------------------------
	UCPS_END_SESSION,

#endif

	//--------------------------------------------------
	// Player Status 배열의 크기 등을 설정할 때 사용된다.
	//--------------------------------------------------
	PLAYER_STATUS_MAX

};

#endif
