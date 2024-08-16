//----------------------------------------------------------------------
// ClientConfig.h
//----------------------------------------------------------------------
// Client�� ���� �߿��� ���� �� �ִ� ��
//----------------------------------------------------------------------

#ifndef	__CLIENTCONFIG_H__
#define	__CLIENTCONFIG_H__

#include <Windows.h>
#include "MString.h"

class ClientConfig {
	public :
		enum NUR_MODE
		{
			NUR_CLIENT,				// �� ����� ��� ����
			NUR_HOMEPAGE,			// Ȩ�������� ����ָ鼭 ���
			NUR_MESSAGE_HOMEPAGE,	// Ȩ���������� ����϶�� message
			NUR_DENY				// �� ����� ��� �Ұ�			
		};

	public :
		ClientConfig();
		~ClientConfig();

		//--------------------------------------------------------
		// File I/O
		//--------------------------------------------------------
		void	SaveToFile(const char* filename);
		bool	LoadFromFile(const char* filename);

	public :
		//--------------------------------------------------------------
		// �ʴ� Update Frame ��
		//--------------------------------------------------------------
		int		FPS;						// ���� ��Ű���� �ʴ´�.

		int		MAX_SCREENSHOT;				// ScreenShotȭ�� �ִ� ����
		int		DELAY_PLAYER_DEAD;			// player�� �װ����� delay
		int		DELAY_PLAYER_RESURRECT_TIMEOUT;			// player�� �װ����� ���� ��Ȱ������ �ð�
		int		MAX_CLIENT_MOVE;			// client���� ������ �� �ִ� sector��
		int		MAX_CREATURE_MOVE_BUFFER;	// creature�� �����̴� max move buffer 
		int		MAX_LIGHT_DRAW;				// ȭ�� ���� �ִ� light����

		int		MAX_SOUNDPART;				// load�ϴ� wav����

		//--------------------------------------------------------------
		// RequestService
		//--------------------------------------------------------------
		int		MAX_REQUEST_SERVICE;		// RequestServerPlayer ���� ��

		//--------------------------------------------------------------
		// packet����
		//--------------------------------------------------------------
		int		MAX_WAIT_PACKET;			// packet��ٸ��� �ð�
		int		MAX_PROCESS_PACKET;			// �ѹ��� ó���ϴ� packet����
		
		//--------------------------------------------------------------
		// �ִ� �ѹ��� update�Ǵ� ȸ��
		//--------------------------------------------------------------
		int		MAX_UPDATE_ONETIME;
		int		MAX_UPDATE_ONETIME_COUNT;	// onetime_update�� �ִ� ȸ��(���ڱ� �޸���? -_-;)

		//--------------------------------------------------------------
		// ��ġ�� delay �ð�
		//--------------------------------------------------------------
		int		DELAY_GLOBAL_SAY;		

		//--------------------------------------------------------------
		// titleȭ�� ����
		//--------------------------------------------------------------
		int		MUSIC_THEME;

		//--------------------------------------------------------------
		// message scroll �ð�
		//--------------------------------------------------------------
		int		DELAY_SYSTEMMESSAGE;
		int		DELAY_GAMEMESSAGE;

		//--------------------------------------------------------------
		// ȭ�鿡 ��µǴ� item�̸� ����
		//--------------------------------------------------------------
		int		MAX_DRAWITEMNAME;

		//--------------------------------------------------------------
		// ä�� String �� ��
		//--------------------------------------------------------------
		int		MAX_CHATSTRING;
		int		MAX_CHATSTRING_MINUS_1;
		int		MAX_CHATSTRING_LENGTH;
		int		MAX_CHATSTRINGLENGTH_PLUS1;

		//--------------------------------------------------------------
		// ä�� �������� �ð�..
		//--------------------------------------------------------------
		int		DELAY_CHATSTRING_KEEP;		// ������� ǥ���ϴ� �ð�
		int		DELAY_CHATSTRING_FADE;		// ��ο����� �ܰ��� �ð�
		int		VALUE_CHATSTRING_FADE;		// ��ο����� ��
		int		MIN_CHATSTRING_COLOR256;	// ���� ��ο� ä�� String��

		//--------------------------------------------------------
		// TexturePart Manager�� Part ����
		//--------------------------------------------------------
		int		MAX_TEXTUREPART_EFFECT;
		int		MAX_TEXTUREPART_SCREENEFFECT;
		int		MAX_TEXTUREPART_CREATURESHADOW;
		int		MAX_TEXTUREPART_IMAGEOBJECTSHADOW;
		int		MAX_TEXTUREPART_ADDON_SHADOW;
		int		MAX_TEXTUREPART_IMAGEOBJECTSPK;
		int		MAX_TEXTUREPART_EFFECTSHADOW;

		//--------------------------------------------------------
		// Font ũ��
		//--------------------------------------------------------
		int		FONT_HEIGHT;
		int		FONT_ITEM_HEIGHT;

		//--------------------------------------------------------
		// ĳ���� �̸� + HP ǥ��
		//--------------------------------------------------------
		int		MAX_HP_BAR_PIXEL;			// hp bar�� ũ��
		int		POSITION_HP_BAR;		// �̸��� ��ġ(hp bar ��ġ)

		//--------------------------------------------------------------
		// Item �μ����� ���� ǥ��
		//--------------------------------------------------------------
		int		PERCENTAGE_ITEM_SOMEWHAT_BROKEN;
		int		PERCENTAGE_ITEM_ALMOST_BROKEN;

		//--------------------------------------------------------------
		// ĳ���Ϳ� �ٴ� Effect�����ٶ� ���� ���� ���� �����ִ� Frame
		//--------------------------------------------------------------
		int		FRAME_DRAW_ORIGINAL_SPRITE;

		//--------------------------------------------------------
		// ����
		//--------------------------------------------------------			
		WORD	COLOR_OUTLINE_INTERACTIONOBJECT;

		// item
		COLORREF	COLOR_NAME_ITEM;
		COLORREF	COLOR_NAME_ITEM_OPTION;
		COLORREF	COLOR_NAME_ITEM_RARE_OPTION;
		WORD		COLOR_OUTLINE_ITEM;

		// ������
		COLORREF	COLOR_NAME_VAMPIRE;
		COLORREF	COLOR_NAME_SLAYER;
		COLORREF	COLOR_NAME_NPC;

		// ���� ����?
		WORD		COLOR_OUTLINE_NPC;
		WORD		COLOR_OUTLINE_ATTACK_POSSIBLE;
		WORD		COLOR_OUTLINE_ATTACK_IMPOSSIBLE;

		// HP bar�� ����
		BYTE		COLOR_HP_BAR_R;
		BYTE		COLOR_HP_BAR_G;
		BYTE		COLOR_HP_BAR_B;

		//--------------------------------------------------------
		// �� ����� ��� mode
		//--------------------------------------------------------
		NUR_MODE	NEW_USER_REGISTERATION_MODE;
		MString		URL_HOMEPAGE;				// Ȩ������ main
		MString		URL_HOMEPAGE_NEW_USER;		// �� ����� ��� URL
		MString		URL_HOMEPAGE_BILING;

		//--------------------------------------------------------
		// ���⿡ ���� ���� - 2001.8.2
		//--------------------------------------------------------
		COLORREF	COLOR_NAME_GOOD_MORE;
		COLORREF	COLOR_NAME_GOOD;
		COLORREF	COLOR_NAME_NEUTRAL;
		COLORREF	COLOR_NAME_EVIL;
		COLORREF	COLOR_NAME_EVIL_MORE;

		//--------------------------------------------------------
		// �� �긮��
		//--------------------------------------------------------
		int			BLOOD_DROP_HP_PERCENT;		// �� �긮�� �����ϴ� HP %
		DWORD		BLOOD_DROP_GAP_TIME;		// ������ �� �긮�� �����ϴ� �ð� gap
		DWORD		BLOOD_DROP_RANDOM_TIME;		// �� �긮�� �ð� = GAP + RANDOM

		//--------------------------------------------------------
		// �ð�
		//--------------------------------------------------------
		DWORD		AFTER_TRADE_ITEM_DROP_DELAY;	// trade�� item�������°� ���������� �ð�
		DWORD		AFTER_PARTY_KICK_DELAY;			// ��Ƽ join�� �ٸ���� kick�� �� �ִ� �ð�
		DWORD		TRACE_CHARACTER_LIMIT_TIME;		// ĳ���� ���󰡱� ���� �ð�.

		//--------------------------------------------------------
		// Repeat & Lock
		//--------------------------------------------------------
		DWORD		REPEAT_TIME;				// �ڵ����� ���ѽð�
		DWORD		LOCK_TIME;					// Caps Lock�ڵ����� ���ѽð�

		//--------------------------------------------------------------
		// Client��ſ� ����ϴ� UDP Port
		//--------------------------------------------------------------
		DWORD		CLIENT_COMMUNICATION_UDP_PORT;

		//--------------------------------------------------------------
		// Client��Ű� ���õ� delay��
		//--------------------------------------------------------------
		DWORD		CLIENT_COMMUNICATION_STATUS_DELAY;

		//--------------------------------------------------------------
		// Trade�� �� delay �ð�
		//--------------------------------------------------------------
		DWORD		TRADE_ACCEPT_DELAY_TIME;

		//--------------------------------------------------------------
		// Regen��
		//--------------------------------------------------------------
		BYTE		REGEN_AMOUNT_BURROW;
		BYTE		REGEN_AMOUNT_CASKET;
		BYTE		REGEN_AMOUNT_VAMPIRE;

		//--------------------------------------------------------------
		// �ʴ� �Ҹ��� �� �ִ� wave ���� ����
		//--------------------------------------------------------------
		BYTE		MAX_SOUND_PER_SECOND;

		DWORD		UniqueItemColorSet;
		DWORD		QuestItemColorSet;

		//--------------------------------------------------------------
		// HPModifyList �������� �� �ð�����
		//--------------------------------------------------------------
		BYTE		HPModifyListMax;
		DWORD		HPModifyListTime;
};


extern	ClientConfig*	g_pClientConfig;

#endif

