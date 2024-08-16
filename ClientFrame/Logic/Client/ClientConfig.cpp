//----------------------------------------------------------------------
// ClientConfig.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "ClientConfig.h"
#include "MusicDef.h"

//----------------------------------------------------------------------
// Global
//----------------------------------------------------------------------
ClientConfig*	g_pClientConfig = NULL;

//----------------------------------------------------------------------
// define functions
//----------------------------------------------------------------------
#define READ_CHECK_EOF( value, temp, bytes )		\
		{											\
			file.read((char*)&temp, bytes);			\
			if (!file.eof())						\
			{										\
				value = temp;						\
			}										\
			else									\
			{										\
				return true;						\
			}										\
		}

//----------------------------------------------------------------------
// 
// constructor
//
//----------------------------------------------------------------------
ClientConfig::ClientConfig()
{	
	//--------------------------------------------------------------
	// FPS - ������ �ȵȴ�.
	//--------------------------------------------------------------
	FPS						= 16;
 
	// ScreenShot�� ����
	MAX_SCREENSHOT			= 100;

	// �װ� ���� �ٽ� ��Ƴ��µ������� delay�ð� 10��
	DELAY_PLAYER_DEAD		= 10 * 1000;	

	DELAY_PLAYER_RESURRECT_TIMEOUT = 60 * 1000;		// 1��
	
	// client���� ������ �� �ִ� sector��
	MAX_CLIENT_MOVE			= 6;

	// client���� ������ �� �ִ� sector��
	MAX_CREATURE_MOVE_BUFFER	= 2;
	
	// ȭ���� �ִ� Light����
	MAX_LIGHT_DRAW			= 50;

	// Load�ϴ� Sound ����
	MAX_SOUNDPART			= 100;

	MAX_REQUEST_SERVICE		= 10;

	//--------------------------------------------------------------
	// �ѹ��� udpate�ϴ� �ִ� ȸ��
	//--------------------------------------------------------------
	// �ѹ��� �ִ� 6 Frame�� �ǹ̴�
	// 6 Frame���� ��� �ѹ��� �׷��شٴ� �ǹ̰� �ȴ�.
	//--------------------------------------------------------------
	MAX_UPDATE_ONETIME		= 6;

	//--------------------------------------------------------------
	// '�ѹ��� update�ϴ� �ִ� ȸ��'�� �����ϴ� ȸ��.. - -;;
	//--------------------------------------------------------------
	// �̷��� �ϸ�..
	// �ѹ��� �ִ� 6 Frame��, �ִ� "10"ȸ�ϱ�..
	// 60 Frame���� ǥ���� ����.. ������~~���� ǥ���ǰ� �ȴ�.
	// 10 Frame�� ���̰���.. 
	//--------------------------------------------------------------
	MAX_UPDATE_ONETIME_COUNT		= 10;		

	DELAY_GLOBAL_SAY				= 12*1000;	// 12��

	//--------------------------------------------------------------
	// message scroll delay�ð�
	//--------------------------------------------------------------
	DELAY_SYSTEMMESSAGE		= 5000;
	DELAY_GAMEMESSAGE		= 5000;

	//--------------------------------------------------------------
	// ȭ�鿡 ��µǴ� item�̸� ����
	//--------------------------------------------------------------
	MAX_DRAWITEMNAME			= 20;

	//--------------------------------------------------------------
	// packet��ٸ��� �ð�
	//--------------------------------------------------------------
	MAX_WAIT_PACKET			= 15000;	// 15��

	//--------------------------------------------------------------
	// �� loop�� ó���Ǵ� packet�� �ִ� ��
	//--------------------------------------------------------------
	MAX_PROCESS_PACKET			= 11;		// 15�� ó��

	//--------------------------------------------------------------
	// �ʱ�ȭ���� ����
	//--------------------------------------------------------------
	MUSIC_THEME				= MUSIC_TREASURE;

	//--------------------------------------------------------------
	// ä�� String �� ��
	//--------------------------------------------------------------
	MAX_CHATSTRING				= 5;
	MAX_CHATSTRING_MINUS_1		= 4;
	MAX_CHATSTRING_LENGTH		= 20;
	MAX_CHATSTRINGLENGTH_PLUS1	= 21;

	//--------------------------------------------------------------
	// ä�� ���� �ð�
	//--------------------------------------------------------------
	DELAY_CHATSTRING_KEEP		= 1500;		// ����� ���� �ð�
	DELAY_CHATSTRING_FADE		= 250;		// ��ο����� �ܰ��� �ð�
	VALUE_CHATSTRING_FADE		= 8;		// ��ο����� ��
	MIN_CHATSTRING_COLOR256		= 96;		// ���� ��ο� ä�� String��
	
	//--------------------------------------------------------
	// TexturePart Manager�� Part ����
	//--------------------------------------------------------
	MAX_TEXTUREPART_EFFECT				= 25;
	MAX_TEXTUREPART_CREATURESHADOW		= 100;
	MAX_TEXTUREPART_IMAGEOBJECTSHADOW	= 100;
	MAX_TEXTUREPART_ADDON_SHADOW			= 200;
	MAX_TEXTUREPART_IMAGEOBJECTSPK		= 20;
	MAX_TEXTUREPART_SCREENEFFECT		= 25;

	//--------------------------------------------------------
	// Font ũ��
	//--------------------------------------------------------
	FONT_HEIGHT				= 20;
	FONT_ITEM_HEIGHT			= 15;

	//--------------------------------------------------------
	// HP Bar
	//--------------------------------------------------------
	MAX_HP_BAR_PIXEL			= 120;		// hp bar�� ũ��
	POSITION_HP_BAR			= -10;		// �̸��� ��ġ(hp bar ��ġ)

	//--------------------------------------------------------
	// ������ �μ����°ſ� ���� ���� ǥ��
	//--------------------------------------------------------
	PERCENTAGE_ITEM_SOMEWHAT_BROKEN	= 25;		// 25%�������� ��������
	PERCENTAGE_ITEM_ALMOST_BROKEN		= 10;		// 10%�������� ������

	//--------------------------------------------------------------
	// Effect�پ ĳ���� ���� �ٲ� ������ ���� ��� �����ִ� frame
	//--------------------------------------------------------------
	FRAME_DRAW_ORIGINAL_SPRITE			= 8;		// 4frame���� �ѹ���

	//--------------------------------------------------------
	// ���� - 5:6:5�� �����ؾ� �Ѵ�.
	//--------------------------------------------------------
	COLOR_OUTLINE_INTERACTIONOBJECT	= (0 << 11) | (31 << 6) | 0;	// GREEN

	// item
	COLOR_NAME_ITEM					= RGB(31<<3, 31<<3, 31<<3);	// WHITE
	COLOR_NAME_ITEM_OPTION			= RGB(31<<3, 31<<3, 5<<3);	// ���� blue
	COLOR_NAME_ITEM_RARE_OPTION		= RGB(19<<3, 19<<3, 31<<3);	// ���� blue
	COLOR_OUTLINE_ITEM				= (23 << 11) | (23 << 6) | 23;

	// ������
	COLOR_NAME_VAMPIRE				= RGB(31<<3, 10<<3, 10<<3);	// RED
	COLOR_NAME_SLAYER				= RGB(23<<3, 23<<3, 31<<3);	// BLUE
	COLOR_NAME_NPC					= RGB(5<<3, 27<<3, 5<<3);	// GREEN

	// ���� ����?
	COLOR_OUTLINE_NPC				= (5 << 11) | (23 << 6) | 5;
	COLOR_OUTLINE_ATTACK_POSSIBLE	= (23 << 11) | (5 << 6) | 5;
	COLOR_OUTLINE_ATTACK_IMPOSSIBLE	= (5 << 11) | (5 << 6) | 18;

	// hp bar
	COLOR_HP_BAR_R					= 15;
	COLOR_HP_BAR_G					= 16;
	COLOR_HP_BAR_B					= 15;

	//---------------------------------------------------------------------
	// �� ����� ��� ���
	//---------------------------------------------------------------------
	//	NUR_CLIENT,				// �� ����� ��� ����
	//	NUR_HOMEPAGE,			// Ȩ�������� ����ָ鼭 ���
	//	NUR_MESSAGE_HOMEPAGE,	// Ȩ���������� ����϶�� message
	//	NUR_DENY				// �� ����� ��� �Ұ�			
	NEW_USER_REGISTERATION_MODE	= ClientConfig::NUR_HOMEPAGE;
//	URL_HOMEPAGE					= "http://www.t2cn.com";				// Ȩ������ main
//	URL_HOMEPAGE_NEW_USER			= "http://member.t2cn.com/reg";		// �� ����� ��� URL
//	URL_HOMEPAGE_BILING				= "http://member.t2cn.com/billing";
	URL_HOMEPAGE					= "http://www.darkeden.com";				// Ȩ������ main
	URL_HOMEPAGE_NEW_USER			= "http://www.darkeden.com/pg/new_reg.html";		// �� ����� ��� URL
	URL_HOMEPAGE_BILING				= "http://www.darkeden.com/pg/buy_index.html";

	//---------------------------------------------------------------------
	// ���⿡ ���� ����
	//---------------------------------------------------------------------
	COLOR_NAME_GOOD_MORE		= RGB(50, 50, 200);	
	COLOR_NAME_GOOD				= RGB(25, 210, 220);
	COLOR_NAME_NEUTRAL			= RGB(128, 128, 128);
	COLOR_NAME_EVIL				= RGB(200, 50, 50);
	COLOR_NAME_EVIL_MORE		= RGB(110, 25, 25);

	//--------------------------------------------------------
	// �� �긮��
	//--------------------------------------------------------
	BLOOD_DROP_HP_PERCENT		= 30;		// �� �긮�� �����ϴ� HP %
	BLOOD_DROP_GAP_TIME			= 3000;		// ������ �� �긮�� �����ϴ� �ð� gap
	BLOOD_DROP_RANDOM_TIME		= 3000;		// �� �긮�� �ð� = GAP + RANDOM

	//--------------------------------------------------------
	//
	//--------------------------------------------------------
	MAX_TEXTUREPART_EFFECTSHADOW	= 3;

	//--------------------------------------------------------
	// trade�� item�������°� ���������� �ð�
	//--------------------------------------------------------
	AFTER_TRADE_ITEM_DROP_DELAY = 3000;	

	//--------------------------------------------------------
	// ��Ƽ join�� �ٸ���� kick�� �� �ִ� �ð�
	//--------------------------------------------------------
	AFTER_PARTY_KICK_DELAY	= 60*60*1000;	// 1�ð� = 60�� * 60�� 

	//--------------------------------------------------------------
	// Client��ſ� ����ϴ� UDP Port
	//--------------------------------------------------------------
	CLIENT_COMMUNICATION_UDP_PORT	= 9858;

	CLIENT_COMMUNICATION_STATUS_DELAY = 5000;

	//--------------------------------------------------------------
	// trade�� �� cancel�� OK�� ���� �� delay �ð�
	//--------------------------------------------------------------
	TRADE_ACCEPT_DELAY_TIME = 5000;

	//--------------------------------------------------------------
	// Vampire ������
	//--------------------------------------------------------------
	REGEN_AMOUNT_BURROW		= 4;
	REGEN_AMOUNT_CASKET		= 10;
	REGEN_AMOUNT_VAMPIRE	= 2;

	//--------------------------------------------------------------
	// �ʴ� wave sound �Ҹ� ���� ���� ����
	//--------------------------------------------------------------
	MAX_SOUND_PER_SECOND	= 6;

	REPEAT_TIME				= 10*60*1000;				// �ڵ����� ���ѽð� 10��
	LOCK_TIME				= 10*60*1000;				// Caps Lock�ڵ����� ���ѽð� 10��
	
	// ����ũ ������ Į���
	UniqueItemColorSet		= 405;
	QuestItemColorSet		= 345;

	// HPModifyList ���� ���ѹ� �ð�����(msec)
	HPModifyListMax			= 10;
	HPModifyListTime		= 10000;
	TRACE_CHARACTER_LIMIT_TIME		= 5*60*1000;		// ĳ���͵��󰡱� ���ѽð� 5��
}

ClientConfig::~ClientConfig()
{
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void	
ClientConfig::SaveToFile(const char* filename)
{
	class ofstream file(filename, ios::binary);	

	file.write((const char*)&FPS, 4);

	file.write((const char*)&MAX_SCREENSHOT, 4);

	file.write((const char*)&DELAY_PLAYER_DEAD, 4);
	file.write((const char*)&MAX_CLIENT_MOVE, 4);
	file.write((const char*)&MAX_CREATURE_MOVE_BUFFER, 4);
	file.write((const char*)&MAX_LIGHT_DRAW, 4);

	file.write((const char*)&MAX_SOUNDPART, 4);

	file.write((const char*)&MAX_UPDATE_ONETIME, 4);
	file.write((const char*)&MAX_UPDATE_ONETIME_COUNT, 4);

	file.write((const char*)&DELAY_GLOBAL_SAY, 4);	

	file.write((const char*)&DELAY_SYSTEMMESSAGE, 4);	
	file.write((const char*)&DELAY_GAMEMESSAGE, 4);	

	file.write((const char*)&MAX_DRAWITEMNAME, 4);	

	file.write((const char*)&MAX_WAIT_PACKET, 4);
	file.write((const char*)&MAX_PROCESS_PACKET, 4);
	
	file.write((const char*)&MUSIC_THEME, 4);
	
	//--------------------------------------------------------------
	// ä�� String �� ��
	//--------------------------------------------------------------
	file.write((const char*)&MAX_CHATSTRING, 4);
	file.write((const char*)&MAX_CHATSTRING_MINUS_1, 4);
	file.write((const char*)&MAX_CHATSTRING_LENGTH, 4);
	file.write((const char*)&MAX_CHATSTRINGLENGTH_PLUS1, 4);

	//--------------------------------------------------------------
	// ä�� �������� �ð�..
	//--------------------------------------------------------------
	file.write((const char*)&DELAY_CHATSTRING_KEEP, 4);		// ������� ǥ���ϴ� �ð�
	file.write((const char*)&DELAY_CHATSTRING_FADE, 4);		// ��ο����� �ܰ��� �ð�
	file.write((const char*)&VALUE_CHATSTRING_FADE, 4);		// ��ο����� ��
	file.write((const char*)&MIN_CHATSTRING_COLOR256, 4);		// ���� ��ο� ä�� String��

	//--------------------------------------------------------
	// TexturePart Manager�� Part ����
	//--------------------------------------------------------
	file.write((const char*)&MAX_TEXTUREPART_EFFECT, 4);
	file.write((const char*)&MAX_TEXTUREPART_CREATURESHADOW, 4);
	file.write((const char*)&MAX_TEXTUREPART_IMAGEOBJECTSHADOW, 4);
	file.write((const char*)&MAX_TEXTUREPART_ADDON_SHADOW, 4);
	file.write((const char*)&MAX_TEXTUREPART_IMAGEOBJECTSPK, 4);

	//--------------------------------------------------------
	// Font ũ��
	//--------------------------------------------------------
	file.write((const char*)&FONT_HEIGHT, 4);
	file.write((const char*)&FONT_ITEM_HEIGHT, 4);

	//--------------------------------------------------------
	// HP Bar
	//--------------------------------------------------------
	file.write((const char*)&MAX_HP_BAR_PIXEL, 4);			// hp bar�� ũ��
	file.write((const char*)&POSITION_HP_BAR, 4);		// �̸��� ��ġ(hp bar ��ġ)

	//--------------------------------------------------------
	// item �μ��� ����(%)
	//--------------------------------------------------------
	file.write((const char*)&PERCENTAGE_ITEM_SOMEWHAT_BROKEN, 4);
	file.write((const char*)&PERCENTAGE_ITEM_ALMOST_BROKEN, 4);

	//--------------------------------------------------------------
	// ĳ���Ϳ� �ٴ� Effect�����ٶ� ���� ���� ���� �����ִ� Frame
	//--------------------------------------------------------------
	file.write((const char*)&FRAME_DRAW_ORIGINAL_SPRITE, 4);
		
	//--------------------------------------------------------
	// ����
	//--------------------------------------------------------
	file.write((const char*)&COLOR_OUTLINE_INTERACTIONOBJECT, 2);

	// item
	file.write((const char*)&COLOR_NAME_ITEM, 4);
	file.write((const char*)&COLOR_NAME_ITEM_OPTION, 4);
	file.write((const char*)&COLOR_NAME_ITEM_RARE_OPTION, 4);
	file.write((const char*)&COLOR_OUTLINE_ITEM, 2);

	// ������
	file.write((const char*)&COLOR_NAME_VAMPIRE, 4);
	file.write((const char*)&COLOR_NAME_SLAYER, 4);
	file.write((const char*)&COLOR_NAME_NPC, 4);

	// ���� ����?
	file.write((const char*)&COLOR_OUTLINE_NPC, 2);
	file.write((const char*)&COLOR_OUTLINE_ATTACK_POSSIBLE, 2);
	file.write((const char*)&COLOR_OUTLINE_ATTACK_IMPOSSIBLE, 2);

	// HP bar�� ����
	file.write((const char*)&COLOR_HP_BAR_R, 1);
	file.write((const char*)&COLOR_HP_BAR_G, 1);
	file.write((const char*)&COLOR_HP_BAR_B, 1);

	//--------------------------------------------------------
	// �� ����� ��� mode
	//--------------------------------------------------------
	file.write((const char*)&NEW_USER_REGISTERATION_MODE, sizeof(NUR_MODE));
	URL_HOMEPAGE.SaveToFile( file );				// Ȩ������ main
	URL_HOMEPAGE_NEW_USER.SaveToFile( file );		// �� ����� ��� URL
	URL_HOMEPAGE_BILING.SaveToFile( file );

	file.write((const char*)&COLOR_NAME_GOOD_MORE, 4);
	file.write((const char*)&COLOR_NAME_GOOD, 4);
	file.write((const char*)&COLOR_NAME_NEUTRAL, 4);
	file.write((const char*)&COLOR_NAME_EVIL, 4);
	file.write((const char*)&COLOR_NAME_EVIL_MORE, 4);	

	file.write((const char*)&BLOOD_DROP_HP_PERCENT, 4);
	file.write((const char*)&BLOOD_DROP_GAP_TIME, 4);
	file.write((const char*)&BLOOD_DROP_RANDOM_TIME, 4);	
	file.write((const char*)&MAX_TEXTUREPART_EFFECTSHADOW, 4);
	file.write((const char*)&MAX_TEXTUREPART_SCREENEFFECT, 4);	

	file.write((const char*)&MAX_REQUEST_SERVICE, 4);

	file.write((const char*)&AFTER_TRADE_ITEM_DROP_DELAY, 4);

	file.write((const char*)&DELAY_PLAYER_RESURRECT_TIMEOUT, 4);
	
	file.write((const char*)&AFTER_PARTY_KICK_DELAY, 4);

	//--------------------------------------------------------------
	// Client��ſ� ����ϴ� UDP Port
	//--------------------------------------------------------------
	file.write((const char*)&CLIENT_COMMUNICATION_UDP_PORT, 4);
	file.write((const char*)&CLIENT_COMMUNICATION_STATUS_DELAY, 4);

	//--------------------------------------------------------------
	// trade �� accept ���� �� �ִ� delay
	//--------------------------------------------------------------
	file.write((const char*)&TRADE_ACCEPT_DELAY_TIME, 4);

	//--------------------------------------------------------------
	// vampire ����
	//--------------------------------------------------------------
	file.write((const char*)&REGEN_AMOUNT_BURROW, 1);
	file.write((const char*)&REGEN_AMOUNT_CASKET, 1);
	file.write((const char*)&REGEN_AMOUNT_VAMPIRE, 1);	

	//--------------------------------------------------------------
	// �ʴ� wave sound �Ҹ� ���� ���� ����
	//--------------------------------------------------------------
	file.write((const char*)&MAX_SOUND_PER_SECOND, 1);	

	// ���콺 ���� ����
	file.write((const char*)&REPEAT_TIME, 4);
	file.write((const char*)&LOCK_TIME, 4);

	// ����ũ ������ Į���
	file.write((const char*)&UniqueItemColorSet, 4);
	file.write((const char*)&QuestItemColorSet, 4);

	// HPModifyList ���� ���ѹ� �ð�����(sec)
	file.write((const char*)&HPModifyListMax, 1);
	file.write((const char*)&HPModifyListTime, 4);
	file.write((const char*)&TRACE_CHARACTER_LIMIT_TIME, 4);
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
bool	
ClientConfig::LoadFromFile(const char* filename)
{
	class ifstream file(filename, ios::binary | ios::nocreate);	

	if (!file || !file.is_open())
	{
		return false;
	}
	
	file.read((char*)&FPS, 4);

	file.read((char*)&MAX_SCREENSHOT, 4);

	file.read((char*)&DELAY_PLAYER_DEAD, 4);
	file.read((char*)&MAX_CLIENT_MOVE, 4);
	file.read((char*)&MAX_CREATURE_MOVE_BUFFER, 4);
	file.read((char*)&MAX_LIGHT_DRAW, 4);

	file.read((char*)&MAX_SOUNDPART, 4);

	file.read((char*)&MAX_UPDATE_ONETIME, 4);
	file.read((char*)&MAX_UPDATE_ONETIME_COUNT, 4);

	file.read((char*)&DELAY_GLOBAL_SAY, 4);	

	file.read((char*)&DELAY_SYSTEMMESSAGE, 4);	
	file.read((char*)&DELAY_GAMEMESSAGE, 4);	

	file.read((char*)&MAX_DRAWITEMNAME, 4);

	file.read((char*)&MAX_WAIT_PACKET, 4);
	file.read((char*)&MAX_PROCESS_PACKET, 4);

	file.read((char*)&MUSIC_THEME, 4);

	//--------------------------------------------------------------
	// ä�� String �� ��
	//--------------------------------------------------------------
	file.read((char*)&MAX_CHATSTRING, 4);
	file.read((char*)&MAX_CHATSTRING_MINUS_1, 4);
	file.read((char*)&MAX_CHATSTRING_LENGTH, 4);
	file.read((char*)&MAX_CHATSTRINGLENGTH_PLUS1, 4);

	//--------------------------------------------------------------
	// ä�� �������� �ð�..
	//--------------------------------------------------------------
	file.read((char*)&DELAY_CHATSTRING_KEEP, 4);		// ������� ǥ���ϴ� �ð�
	file.read((char*)&DELAY_CHATSTRING_FADE, 4);		// ��ο����� �ܰ��� �ð�
	file.read((char*)&VALUE_CHATSTRING_FADE, 4);		// ��ο����� ��
	file.read((char*)&MIN_CHATSTRING_COLOR256, 4);		// ���� ��ο� ä�� String��

	//--------------------------------------------------------
	// TexturePart Manager�� Part ����
	//--------------------------------------------------------
	file.read((char*)&MAX_TEXTUREPART_EFFECT, 4);
	file.read((char*)&MAX_TEXTUREPART_CREATURESHADOW, 4);
	file.read((char*)&MAX_TEXTUREPART_IMAGEOBJECTSHADOW, 4);
	file.read((char*)&MAX_TEXTUREPART_ADDON_SHADOW, 4);
	file.read((char*)&MAX_TEXTUREPART_IMAGEOBJECTSPK, 4);

	//--------------------------------------------------------
	// Font ũ��
	//--------------------------------------------------------
	file.read((char*)&FONT_HEIGHT, 4);
	file.read((char*)&FONT_ITEM_HEIGHT, 4);

	//--------------------------------------------------------
	// HP Bar
	//--------------------------------------------------------
	file.read((char*)&MAX_HP_BAR_PIXEL, 4);			// hp bar�� ũ��
	file.read((char*)&POSITION_HP_BAR, 4);		// �̸��� ��ġ(hp bar ��ġ)

	//--------------------------------------------------------
	// item �μ��� ����(%)
	//--------------------------------------------------------
	file.read((char*)&PERCENTAGE_ITEM_SOMEWHAT_BROKEN, 4);
	file.read((char*)&PERCENTAGE_ITEM_ALMOST_BROKEN, 4);

	//--------------------------------------------------------------
	// ĳ���Ϳ� �ٴ� Effect�����ٶ� ���� ���� ���� �����ִ� Frame
	//--------------------------------------------------------------
	file.read((char*)&FRAME_DRAW_ORIGINAL_SPRITE, 4);

	//--------------------------------------------------------
	// ����
	//--------------------------------------------------------
	file.read((char*)&COLOR_OUTLINE_INTERACTIONOBJECT, 2);

	// item
	file.read((char*)&COLOR_NAME_ITEM, 4);
	file.read((char*)&COLOR_NAME_ITEM_OPTION, 4);
	file.read((char*)&COLOR_NAME_ITEM_RARE_OPTION, 4);
	file.read((char*)&COLOR_OUTLINE_ITEM, 2);

	// ������
	file.read((char*)&COLOR_NAME_VAMPIRE, 4);
	file.read((char*)&COLOR_NAME_SLAYER, 4);
	file.read((char*)&COLOR_NAME_NPC, 4);

	// ���� ����?
	file.read((char*)&COLOR_OUTLINE_NPC, 2);
	file.read((char*)&COLOR_OUTLINE_ATTACK_POSSIBLE, 2);
	file.read((char*)&COLOR_OUTLINE_ATTACK_IMPOSSIBLE, 2);

	// HP bar�� ����
	file.read((char*)&COLOR_HP_BAR_R, 1);
	file.read((char*)&COLOR_HP_BAR_G, 1);
	file.read((char*)&COLOR_HP_BAR_B, 1);

	//--------------------------------------------------------
	// �� ����� ��� mode
	//--------------------------------------------------------
	file.read((char*)&NEW_USER_REGISTERATION_MODE, sizeof(NUR_MODE));
	URL_HOMEPAGE.LoadFromFile( file );				// Ȩ������ main
	URL_HOMEPAGE_NEW_USER.LoadFromFile( file );		// �� ����� ��� URL
	URL_HOMEPAGE_BILING.LoadFromFile( file );

	URL_HOMEPAGE					= "http://bbstest.web11.zcidc.com/bbs/index.asp";				// Ȩ������ main
	URL_HOMEPAGE_NEW_USER			= "http://bbstest.web11.zcidc.com/bbs/index.asp";		// �� ����� ��� URL
	URL_HOMEPAGE_BILING				= "http://bbstest.web11.zcidc.com/bbs/index.asp";
	
	//--------------------------------------------------------
	// ���⿡ ���� ����..
	//--------------------------------------------------------
	DWORD temp;
	READ_CHECK_EOF( COLOR_NAME_GOOD_MORE, temp, 4 )
	READ_CHECK_EOF( COLOR_NAME_GOOD, temp, 4 )
	READ_CHECK_EOF( COLOR_NAME_NEUTRAL, temp, 4 )
	READ_CHECK_EOF( COLOR_NAME_EVIL, temp, 4 )
	READ_CHECK_EOF( COLOR_NAME_EVIL_MORE, temp, 4 )	

	READ_CHECK_EOF( BLOOD_DROP_HP_PERCENT, temp, 4 )
	READ_CHECK_EOF( BLOOD_DROP_GAP_TIME, temp, 4 )
	READ_CHECK_EOF( BLOOD_DROP_RANDOM_TIME, temp, 4 )	
	READ_CHECK_EOF( MAX_TEXTUREPART_EFFECTSHADOW, temp, 4 )
	READ_CHECK_EOF( MAX_TEXTUREPART_SCREENEFFECT, temp, 4 )	

	READ_CHECK_EOF( MAX_REQUEST_SERVICE, temp, 4 )

	READ_CHECK_EOF( AFTER_TRADE_ITEM_DROP_DELAY, temp, 4 )

	READ_CHECK_EOF( DELAY_PLAYER_RESURRECT_TIMEOUT, temp, 4 )
	
	READ_CHECK_EOF( AFTER_PARTY_KICK_DELAY, temp, 4 )

	//--------------------------------------------------------------
	// Client��ſ� ����ϴ� UDP Port
	//--------------------------------------------------------------
	READ_CHECK_EOF( CLIENT_COMMUNICATION_UDP_PORT, temp, 4 )

	READ_CHECK_EOF( CLIENT_COMMUNICATION_STATUS_DELAY, temp, 4 )
	
	//--------------------------------------------------------------
	// trade �� accept ���� �� �ִ� delay
	//--------------------------------------------------------------
	READ_CHECK_EOF( TRADE_ACCEPT_DELAY_TIME, temp, 4)

	//--------------------------------------------------------------
	// vampire ������
	//--------------------------------------------------------------
	BYTE temp1;
	READ_CHECK_EOF( REGEN_AMOUNT_BURROW, temp1, 1)
	READ_CHECK_EOF( REGEN_AMOUNT_CASKET, temp1, 1)
	READ_CHECK_EOF( REGEN_AMOUNT_VAMPIRE, temp1, 1)	

	//--------------------------------------------------------------
	// �ʴ� wave sound �Ҹ� ���� ���� ����
	//--------------------------------------------------------------	
	READ_CHECK_EOF( MAX_SOUND_PER_SECOND, temp1, 1)

	// ���콺 ���� ����
	READ_CHECK_EOF( REPEAT_TIME, temp, 4)
	READ_CHECK_EOF( LOCK_TIME, temp, 4)

	// ����ũ ������ Į���
	READ_CHECK_EOF( UniqueItemColorSet, temp, 4);
	READ_CHECK_EOF( QuestItemColorSet, temp, 4);

	
	// HPModifyList ���� ���ѹ� �ð� ����(sec)
	READ_CHECK_EOF( HPModifyListMax, temp1, 1);
	READ_CHECK_EOF( HPModifyListTime, temp, 4);
	READ_CHECK_EOF( TRACE_CHARACTER_LIMIT_TIME, temp, 4 );
	
	return true;
}
