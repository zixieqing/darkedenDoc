//----------------------------------------------------------------------
// UserOption.h
//----------------------------------------------------------------------
// ����ڰ� �ٲ� �� �ִ� ��
//----------------------------------------------------------------------

#ifndef	__USEROPTION_H__
#define	__USEROPTION_H__

#include <Windows.h>

class UserOption {
	public :
		UserOption();
		~UserOption();

		//--------------------------------------------------------
		// File I/O
		//--------------------------------------------------------
		void	SaveToFile(const char* filename);
		bool	LoadFromFile(const char* filename);

	public :
		BOOL	Chinese;
		BOOL	Korean;
		BOOL	Japanese;
		BOOL	English;
		BOOL	Use3DHAL;					// 3D���� ����� �� �ִ��� �׽�Ʈ �Ѵ�.
		BOOL	UseSmoothCursor;			// �ε巯��(?) cursor�� ����ұ�?
		BOOL	DrawMinimap;				// minimap�� �׸���?
		BOOL	DrawZoneName;				// Zone�̸� ���
		BOOL	DrawGameTime;				/// ���� �ð� ���
		BOOL	DrawInterface;				// interface�� ����ұ�?
		BOOL	DrawFPS;					// FPS�� ����ұ�?
		BOOL	BlendingShadow;				// �׸��ڸ� �������ؼ� ����ұ�?
		BOOL	FilteringCurse;				// ���� �� ���� �ұ�?
		BOOL	PlayMusic;					// �뷡 ����ұ�?
		BOOL	PlaySound;					// ȿ���� ����ұ�?
		int		VolumeMusic;				// ���� ����
		int		VolumeSound;				// ȿ���� ����
		BOOL	UseHelpEvent;				// HelpEvent�� ����ϴ°�?
		BOOL	PlayWaveMusic;				// wave�� ������ ��°�?
		BOOL	BloodDrop;					// HP ���� �� �� �긮��
		BOOL	OpenQuickSlot;				// QuickSlot�� �����ִ°�?
		BOOL	UseHalfFrame;				// Frame ���ΰ� �����ٱ�?
		BOOL	DrawTransHPBar;				// ������ HP �ڽ��ΰ�?
		BOOL	UseForceFeel;				// ���� ���콺 ���?
		BOOL	UseGammaControl;			// ���� �� �����ϴ°� ����ϴ°�?
		BOOL	GammaValue;					// ���� ��( 50 ~ 100(�⺻) ~ 150(����) )
		BOOL	DrawChatBoxOutline;			// ĳ���� �Ӹ� ���� �ߴ� ä�ñ��� �ܰ��� �� �׸���
		
		// new interface
		char	BackupID[11];
		BOOL	UseEnterChat;
		BOOL	UseMouseSpeed;
		int		MouseSpeedValue;
		BOOL	PlayYellSound;
		BOOL	ShowChoboHelp;
		BOOL	TribeChange;
		BOOL	DenyPartyInvite;
		BOOL	DenyPartyRequest;
		BOOL	AutoHideSmoothScroll;		// â �ڵ����� �ε巴�� �ϴ°�?
		COLORREF ChattingColor;
		BYTE	ALPHA_DEPTH;
		BOOL	DefaultAlpha;
		BOOL	IsPreLoadMonster;
		BOOL	ChatWhite;					// ä�� ��� ������� ����
		BOOL	UseTeenVersion;				// ƾ�������� �����ϱ�
		BOOL	PopupChatByWhisper;			// �ӼӸ� ������ ä��â ��� ���̱�
		BOOL	NotSendMyInfo;				// �� ���� ������ ������ �ʱ�
		BOOL	DoNotShowWarMsg;			// ����޽��� ���� �ʱ�
		BOOL	DoNotShowLairMsg;			// ������� �޽��� ���� �ʱ� 
		BOOL	DoNotShowHolyLandMsg;		// �ƴ��� ���� �޽��� ���� �ʱ�
		int		persnalShopupdatetime;
		// 2004, 12, 21, sobeit add start - ���ӸӴ� ���̴� ���
		BOOL	ShowGameMoneyWithHANGUL;
		// 2004, 12, 21, sobeit add end
		// 2005, 1, 20, sobeit add start - ���λ��� �޼��� �Ⱥ���
		BOOL	DoNotShowPersnalShopMsg;
		// 2005, 1, 20, sobeit add end
};


extern	UserOption*		g_pUserOption;

#endif

