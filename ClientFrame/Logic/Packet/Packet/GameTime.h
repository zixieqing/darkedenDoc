//////////////////////////////////////////////////////////////////////
//
// Filename    : GameTime.h
// Written By  : Reiot
// Description : 게임 내에서의 시간을 나타냄
//
//////////////////////////////////////////////////////////////////////

#ifndef __GAME_TIME_H__
#define __GAME_TIME_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
//
// 게임 내에서의 시간을 나타낸다.
//
// *TODO*
//
// 시스템 시간과 게임 시간을 변형해주는 루틴을 개발해야 한다.
//
// 이를 위해서는 시스템 시간의 기준점을 게임 시간의 특정 시간(ex: 2000-01-01)
// 로 지정해서 현재 시스템 시간과 기준 시스템 시간의 차를 사용해서 현재
// 게임 시간을 구해야 할 것이다.
//
// 단 이렇게 해도 요일은 구하기가 매우 막막하니 주의하기 바란다.
//
//////////////////////////////////////////////////////////////////////

class GameTime {

public :

	// 소켓에 embedding 되려는 객체는 다음과 같은 메쏘드를 구현해야 한다.
	// 나중에는 이거 인터페이스로 해결할 전망이다.

	// read from socket input stream
	void read ( SocketInputStream & iStream ) throw ( ProtocolException , Error );

	// write to socket output stream
	void write ( SocketOutputStream & oStream ) const throw ( ProtocolException , Error );

	// get size of object
	uint getSize () const throw () { return szWORD + szBYTE * 5; }
	static uint getMaxSize () throw () { return szWORD + szBYTE * 5; }


public :


	// get/set year
	WORD getYear () const throw () { return m_Year; }
	void setYear ( WORD year ) throw () { m_Year = year; }

	// get/set month
	BYTE getMonth () const throw () { return m_Month; }
	void setMonth ( BYTE month ) throw () { m_Month = month; }

	// get/set day
	BYTE getDay () const throw () { return m_Day; }
	void setDay ( BYTE day ) throw () { m_Day = day; }

	// get/set hour
	BYTE getHour () const throw () { return m_Hour; }
	void setHour ( BYTE hour ) throw () { m_Hour = hour; }

	// get/set minute
	BYTE getMinute () const throw () { return m_Minute; }
	void setMinute ( BYTE minute ) throw () { m_Minute = minute; }

	// get/set second
	BYTE getSecond () const throw () { return m_Second; }
	void setSecond ( BYTE second ) throw () { m_Second = second; }

	// get english month std::string
	std::string getMonthString () const throw ()
	{
		switch ( m_Month ) {
			case 1 : return "JAN";
			case 2 : return "FEB";
			case 3 : return "MAR";
			case 4 : return "APR";
			case 5 : return "MAY";
			case 6 : return "JUN";
			case 7 : return "JUL";
			case 8 : return "OUG";
			case 9 : return "SEP";
			case 10 : return "OCT";
			case 11 : return "NOV";
			case 12 : return "DEC";
		}
		return "???";
	}

	// get debug std::string
	std::string toString () const throw ();

private :

	// YYYY-MM-DD
	WORD m_Year;
	BYTE m_Month;
	BYTE m_Day;

	// HH:MM:SS
	BYTE m_Hour;
	BYTE m_Minute;
	BYTE m_Second;
	
};

const uint szGameTime = sizeof(GameTime);

#endif
