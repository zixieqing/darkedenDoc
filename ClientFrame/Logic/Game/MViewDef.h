//----------------------------------------------------------------------
// MViewDef.h
//----------------------------------------------------------------------
//
// View�� ���õ� ����.
//
//----------------------------------------------------------------------

#ifndef	__MVIEWDEF_H__
#define	__MVIEWDEF_H__


// ����ȸ���� FullScreen�̴�.
#ifdef __EXPO_CLIENT__
	#define	__FULLSCREEN_MODE__
#endif

//----------------------------------------------------------------------
//
// defines
//
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// ȭ�� ũ�⿡ ���� ����
//----------------------------------------------------------------------
#define	SURFACE_WIDTH			800
#define	SURFACE_HEIGHT			600


//----------------------------------------------------------------------
// �⺻ �ٴ� Tile�� ũ��
//----------------------------------------------------------------------
#define	TILE_X					48	//64
#define	TILE_Y					24	//32
#define	TILE_X_HALF				24	//32
#define	TILE_Y_HALF				12	//16

//----------------------------------------------------------------------
// 8���⿡ ���� ������ �Ǵ� ���� : ����/���� ������ ����
//----------------------------------------------------------------------
#define	BASIS_DIRECTION_LOW			0.35
#define	BASIS_DIRECTION_HIGH		3.0


//----------------------------------------------------------------------
// ScreenLight ũ�� - 3D�þ�ó������ ����ϴ� ��
//----------------------------------------------------------------------
#define	SCREENLIGHT_WIDTH		64
#define	SCREENLIGHT_HEIGHT		64


#ifdef __FULLSCREEN_MODE__

	//----------------------------------------------------------------------
	// �� ȭ�鿡 ��µǴ� Sector�� ����?
	//----------------------------------------------------------------------
	#define	SECTOR_SKIP_LEFT		-1
	#define	SECTOR_SKIP_UP			-1
	#define	SECTOR_WIDTH			16	//16
	#define	SECTOR_HEIGHT			25

	//----------------------------------------------------------------------
	// Player�� �þ� �ִ� ���� == ȭ�� ���� Tile����
	//
	// ���� : 9 + 1 + 9
	// ���� : 13 + 1 + 13
	//
	// 1�� ĳ������ ��ǥ �߽��̴�.
	//----------------------------------------------------------------------
	#define	SECTOR_WIDTH_HALF			9
	#define	SECTOR_HEIGHT_HALF			13

	// ĳ���͸� ȭ�� �߽ɿ� ����� ���� ��ǥ
	#define	SECTOR_SKIP_PLAYER_LEFT		-8
	#define	SECTOR_SKIP_PLAYER_UP		-12	// -SECTOR_HEIGHT/2

	//----------------------------------------------------------------------
	// ���� ���� ȭ��
	//----------------------------------------------------------------------
	#define	CLIPSURFACE_WIDTH		800
	#define	CLIPSURFACE_HEIGHT		600

	//----------------------------------------------------------------------
	//
	// Tile Surface�� ���� ����
	//
	//----------------------------------------------------------------------
	#define	TILESURFACE_SECTOR_EDGE				3		// ���� ���� Sector����

	#define	TILESURFACE_SECTOR_WIDTH			22		// 3+16+3���� ����
	#define	TILESURFACE_SECTOR_HEIGHT			31		// 3+25+3���� ����
	#define	TILESURFACE_SECTOR_OUTLINE_LEFT		3		// ���� ���
	#define	TILESURFACE_SECTOR_OUTLINE_RIGHT	19		// 3+16������ ���
	#define	TILESURFACE_SECTOR_OUTLINE_UP		3		// ���� ���
	#define	TILESURFACE_SECTOR_OUTLINE_DOWN		28		// 3+25�Ʒ��� ���

	#define	TILESURFACE_WIDTH					1056	//1152	// TileSurface�� ���� ũ��
	#define	TILESURFACE_HEIGHT					744		//768		// TileSurface�� ���� ũ��
	#define	TILESURFACE_OUTLINE_LEFT			144		// ���� ���
	#define	TILESURFACE_OUTLINE_RIGHT			912		// ������ ���
	#define	TILESURFACE_OUTLINE_UP				72		// ���� ���
	#define	TILESURFACE_OUTLINE_DOWN			672		//672		// �Ʒ��� ���

#else

	//----------------------------------------------------------------------
	// �� ȭ�鿡 ��µǴ� Sector�� ����?
	//----------------------------------------------------------------------
	#define	SECTOR_SKIP_LEFT		-1
	#define	SECTOR_SKIP_UP			-1
	#define	SECTOR_WIDTH			16	//16
	#define	SECTOR_HEIGHT			25	//18 - interface������ 500�� ������ �ȴ�.

	//----------------------------------------------------------------------
	// Player�� �þ� �ִ� ���� == ȭ�� ���� Tile����
	//
	// ���� : 9 + 1 + 9
	// ���� : 10 + 1 + 10
	//
	// 1�� ĳ������ ��ǥ �߽��̴�.
	//----------------------------------------------------------------------
	#define	SECTOR_WIDTH_HALF			9
	#define	SECTOR_HEIGHT_HALF			12

	// ĳ���͸� ȭ�� �߽ɿ� ����� ���� ��ǥ
	#define	SECTOR_SKIP_PLAYER_LEFT		-8
	#define	SECTOR_SKIP_PLAYER_UP		-13

	//----------------------------------------------------------------------
	// ���� ���� ȭ��
	//----------------------------------------------------------------------
	#define	CLIPSURFACE_WIDTH		800
	#define	CLIPSURFACE_HEIGHT		600

	//----------------------------------------------------------------------
	//
	// Tile Surface�� ���� ����
	//
	//----------------------------------------------------------------------
	#define	TILESURFACE_SECTOR_EDGE				3		// ���� ���� Sector����

	#define	TILESURFACE_SECTOR_WIDTH			22		// 3+16+3���� ����
	#define	TILESURFACE_SECTOR_HEIGHT			31		// 3+25+3���� ����
	#define	TILESURFACE_SECTOR_OUTLINE_LEFT		3		// ���� ���
	#define	TILESURFACE_SECTOR_OUTLINE_RIGHT	19		// 3+16������ ���
	#define	TILESURFACE_SECTOR_OUTLINE_UP		3		// ���� ���
	#define	TILESURFACE_SECTOR_OUTLINE_DOWN		28		// 3+25�Ʒ��� ���

	#define	TILESURFACE_WIDTH					1056	//1152	// TileSurface�� ���� ũ��
	#define	TILESURFACE_HEIGHT					744		//768		// TileSurface�� ���� ũ��
	#define	TILESURFACE_OUTLINE_LEFT			144		// ���� ���
	#define	TILESURFACE_OUTLINE_RIGHT			912		// ������ ���
	#define	TILESURFACE_OUTLINE_UP				72		// ���� ���
	#define	TILESURFACE_OUTLINE_DOWN			672		//672		// �Ʒ��� ���
#endif

//----------------------------------------------------------------------
// Tile Surface�� �ٽ� �׸��� Flag
//----------------------------------------------------------------------
#define	FLAG_TILESURFACE_LACK_LEFT			0x01	// ���� ����
#define	FLAG_TILESURFACE_LACK_RIGHT			0x02	// ������ ����
#define	FLAG_TILESURFACE_LACK_UP			0x04	// ���� ����
#define	FLAG_TILESURFACE_LACK_DOWN			0x08	// �Ʒ��� ����


#endif