//----------------------------------------------------------------------
// UserInformation.h
//----------------------------------------------------------------------
// Client�� ���� �߿��� ���� �� �ִ� ��
//----------------------------------------------------------------------

#ifndef	__USERINFORMATION_H__
#define	__USERINFORMATION_H__

#include <Windows.h>
#include <vector>
#include <bitset>
#include "MString.h"
#include "RaceType.h"

struct WAR_INFO
{
	std::string zone_name;
	std::string attack_guild_name, defense_guild_name;
	WORD	zone_id;
	DWORD left_time;
	BYTE war_type;
};

class MPetItem;

class UserInformation {	
	public :
		UserInformation();
		~UserInformation();

		//--------------------------------------------------------
		// File I/O
		//--------------------------------------------------------
		//void	SaveToFile(const char* filename);
		//bool	LoadFromFile(const char* filename);

	public :

		// ������ �ѱ�
		MString			UserID;				// ������� ID
		MString			Character[3];		// ĳ���� �̸�
		Race			Race[3];		// slayer ĳ�����ΰ�?
		MString			CharacterID;		// ���õ� Character ID
		MString			GuildName;			// �� ��� �̸�
		BYTE			GuildGrade;			// �� ��� �ȿ����� ���
		int				PCSNumber;			// �� pcs ��ȣ
		int				FaceStyle;			// �� ���
		int				FaceStyleSlot[3];	// ����â���� �� ��Ÿ��
		int				HairColor;
		int				SkinColor;
		int				BatColor;
		MString			WhisperID;			// ��� ���� �ӼӸ� ���

		MString			PCSUserName[3];		// ����� �̸�
		int				OtherPCSNumber[3];		// �������� ��ȣ

		// �ϼ��� �ѱ�
		//MString			UserIDW;			// ������� ID
		//MString			CharacterW[3];		// ������� ID		
		//MString			CharacterIDW;		// ������� Character ID

		//
		int				Slot;				// �����ҷ��� Slot
//		bool			Invisible;			// ���� ĳ����(Super User��?)

		DWORD			GlobalSayTime;		// ���������� ��ġ��~�� �ð�.

		bool			GoreLevel;			// �� Ƣ�� �ұ�?

		BOOL			KeepConnection;		// ���� �����ؾ��ϴ� �����ΰ�?
		BOOL			IsMaster;			// ����ΰ�?
		DWORD			ItemDropEnableTime;	// item�� ����߷��� �Ǵ� �ð�
		bool			HasSkillRestore;	// Restore ����� �� �ִ°�?
		DWORD			LogoutTime;			// Logout�� ������ �ð�
		DWORD			GameVersion;		// Game�� Version
		bool			HasMagicGroundAttack;	// �ұ�� ����� �� �ִ°�?
		bool			HasMagicHallu;			// Hallu ����� �� �ִ°�?
		bool			HasMagicBloodySnake;			// Bloody Snake ����� �� �ִ°�?
		bool			HasMagicBloodyWarp;			// Bloody Warp ����� �� �ִ°�?

		// �ݸ����
		bool			IsNetmarble;		// NetMarble �� Ŭ���̾�Ʈ �ΰ�
		MString			NetmarbleID;
		MString			NetmarblePassword;
		bool			bNetmarbleGoreLevel;

		int				WorldID;
		int				ServerID;

		std::vector<WAR_INFO>		WarInfo;
		
		bool			bMetrotech;
		MString			WorldName;

		bool			bChinese;
		bool			bKorean;
		bool			bJapanese;
		bool			bEnglish;

		void			SetKorean() { bKorean = true; bChinese=bJapanese=bEnglish=false;}
		void			SetChinese() { bChinese = true; bKorean=bJapanese=bEnglish=false;}
		void			SetJapanese() { bJapanese = true; bKorean=bChinese=bEnglish=false;}
		
		// �Ӹ����� ������
		int				HeadPrice;

		bool			bCompetence;
		bool			bCompetenceShape;
		
		// 2004, 7, 15, sobeit add start
		bool			IsAutoLogIn;		// �ڵ� �α���(���α���) ������� �ƴ���
		MString			AutoLogInKeyValue;	// �ڵ� �α���(���α���) ����϶� key ��
		void*			pLogInClientPlayer;
		// 2004, 7, 15, sobeit add end
		
		// 2004, 9, 14, sobeit add start
		bool			IsNonPK;
		// 2004, 9, 14, sobeit add end
		// 2004, 10, 18, sobeit add start
		DWORD			dwUnionID;
		BYTE			bUnionGrade; // 0: ���Ͽ� ����Ʈ 1: �Ϲ� ������ 3: nothing
		// 2004, 10, 18, sobeit add end
		
		// 2004, 12, 14, sobeit add start
		bool			IsTestServer;
		// 2004, 12, 14, sobeit add end

};


extern	UserInformation	*	g_pUserInformation;

#endif

