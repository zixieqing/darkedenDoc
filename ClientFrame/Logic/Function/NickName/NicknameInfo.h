#ifndef __NICKNAME_INFO_H__
#define __NICKNAME_INFO_H__

#include "packet\Types.h"

#include "packet\Packet.h"
#include "packet\SocketInputStream.h"
#include "packet\SocketOutputStream.h"

#include <string>

#define MAX_NICKNAME_SIZE	22

class NicknameInfo
{
public:
	NicknameInfo();
	enum
	{
		NICK_NONE = 0,		// �г��� ����
		NICK_BUILT_IN,		// �Ϲ������� �ڵ����� �־����� �г��� (�ε���)
		NICK_QUEST,			// ����Ʈ Ŭ������ �� �޴� �г��� (�ε���)
		NICK_FORCED,		// ������ �ٿ��� �г��� (�ε���)
		NICK_CUSTOM_FORCED,	// ������ �ٿ��� �г��� (��Ʈ��)
		NICK_CUSTOM,		// ������ �����Ӱ� ���� �г��� (��Ʈ��)
	};

	PacketSize_t		getSize() const;
	static PacketSize_t	getMaxSize() { return szWORD + szBYTE + szBYTE + MAX_NICKNAME_SIZE; }

	void read(SocketInputStream& iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	WORD	getNicknameID() const { return m_NicknameID; }
	BYTE	getNicknameType() const { return m_NicknameType; }
	string	getNickname() const { return m_Nickname; }
	WORD	getNicknameIndex() const { return m_NicknameIndex; }

	void	setNicknameID( WORD id ) { m_NicknameID = id; }
	void	setNicknameType( BYTE type ) { m_NicknameType = type; }
	void	setNickname( const string& name ) { m_Nickname = name; }
	void	setNicknameIndex( WORD index ) { m_NicknameIndex = index; }
	void	setNickname( char* name ) { m_Nickname = name; }

private:
	WORD	m_NicknameID;
	BYTE	m_NicknameType;
	string	m_Nickname;
	WORD	m_NicknameIndex;	// ��Ʈ�� �Ǵ� �ε��� �ϳ��� ���ȴ�.
};

#endif
