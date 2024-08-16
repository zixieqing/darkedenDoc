//----------------------------------------------------------------------
//
// Filename    : PlayerInfo.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"

//----------------------------------------------------------------------
//
// class PlayerInfo;
//
// �÷��̾� ��Ͻ� �� ����Ÿ ������� �ִ� �ּ� ���� ���� ������ ��´�.
//
//----------------------------------------------------------------------
namespace PlayerInfo {

	// �÷��̾� ���̵�
	const uint minIDLength = 4;
	const uint maxIDLength = 10;

	// �÷��̾� ��ȣ
	const uint minPasswordLength = 6;
	const uint maxPasswordLength = 10;

	// �÷��̾� �̸�
	const uint maxNameLength = 20;

	// �ֹε�Ϲ�ȣ ( '-' �� �����ؾ� �Ѵ�. )
	const uint maxSSNLength = 20;

	// ����ȭ
	const uint maxTelephoneLength = 15;

	// �޴���
	const uint maxCellularLength = 15;

	// �����ȣ
	const uint maxZipCodeLength = 7;

	// ���ּ�
	const uint maxAddressLength = 100;

	// ���ڸ���
	const uint maxEmailLength = 50;

	// Ȩ������
	const uint maxHomepageLength = 50;

	// �ڱ�Ұ���
	const uint maxProfileLength = 200;

};

#endif
