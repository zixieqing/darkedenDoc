//--------------------------------------------------------------------------------
// 
// Filename    : WarInfo.h 
// Written By  : 
// Description : 
// 
//--------------------------------------------------------------------------------

#ifndef __WAR_LIST_H__
#define __WAR_LIST_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "ValueList.h"
#include "types/WarTypes.h"

//--------------------------------------------------------------------------------
//
// class WarInfo;
//
// 하나의 전쟁에 대한 정보
//
//--------------------------------------------------------------------------------

class WarInfo {

public :
	WarInfo() {}
	virtual ~WarInfo() {}
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    virtual void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    virtual void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

//	// execute packet's handler
//	virtual void execute(Player* pPlayer) throw(ProtocolException, Error);

	virtual PacketSize_t getSize() const throw() 
	{ 
		return szDWORD*2;
	}

	static PacketSize_t getMaxSize() throw() 
	{ 
		return szDWORD*2;
	}

#ifdef __DEBUG_OUTPUT__
	// get packet's debug string
	virtual std::string toString() const throw() = 0;
#endif

public :
	virtual WarType_t 	getWarType() const = 0;

	DWORD 				getRemainTime() const 		{ return m_RemainTime; }
	void 				setRemainTime(DWORD rt) 	{ m_RemainTime = rt; }

	DWORD				getStartTime() const		{ return m_StartTime; }
	void				setStartTime(DWORD st)		{ m_StartTime = st; }

protected :
	DWORD					m_RemainTime;	// 남은 시간(초)
	DWORD					m_StartTime;
};

#endif
