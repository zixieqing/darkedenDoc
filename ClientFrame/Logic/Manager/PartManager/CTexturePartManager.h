//----------------------------------------------------------------------
// CTexturePartManager.h
//----------------------------------------------------------------------
// Ư��File(ASPK)�� ���ؼ�
// FileIndex(ASPKI)�� �����ؼ�
// �Ϻ��� AlphaSprite�� Load�ؼ� ����ϰ� �ϴ� class
//----------------------------------------------------------------------

#ifndef	__CTEXTUREPARTMANAGER_H__
#define	__CTEXTUREPARTMANAGER_H__

#include "CPartManager.h"
#include "CSpriteSurface.h"
#include <list>
#include <map>
//class ifstream;
//class CFileIndexTable;
//class CAlphaSpritePack;
#include "CAlphaSpritePal.h"
#include "MPalettePack.h"

class CTexturePartManager : public CPartManager<WORD, WORD, CSpriteSurface*>
{
	public :
		typedef std::list<CSpriteSurface*>	SPRITESURFACE_LIST;
		typedef std::map<int, int>			SPRITE_PALETTE;			// ����� ��������Ʈ ���̵� �������� ����� �ķ�Ʈ ��ȣ

	public :
		//CTexturePartManager(CAlphaSpritePack* pASPK, WORD partSize=100);
		CTexturePartManager(const char* aspkFilename, WORD partSize=100);
		~CTexturePartManager();

		//---------------------------------------------------
		// Init / Release
		//---------------------------------------------------
		//void				Init(CAlphaSpritePack* pASPK, WORD partSize);
		void				Init(const char* aspkFilename, WORD partSize);
		void				Release();
	
		// data������ �ʱ�ȭ ��Ų��.
		void				Clear();

		//---------------------------------------------------
		// aspk�� id��° AlphaSprite�� �Ѱܹ޴´�.
		//---------------------------------------------------
		CSpriteSurface*		GetTexture(TYPE_SPRITEID id, int index);

		// AlphaSprite�� ���� ũ�⸦ �Ѱ��ش�.
		int					GetWidth(TYPE_SPRITEID id)	{ return m_pWidth[id]; }
		int					GetHeight(TYPE_SPRITEID id)	{ return m_pHeight[id]; }

		int					GetSpriteWidth(TYPE_SPRITEID id)	{ return m_ASPK[id].GetWidth(); }
		int					GetSpriteHeight(TYPE_SPRITEID id)	{ return m_ASPK[id].GetHeight(); }

		//---------------------------------------------------
		// ������ �� �͵�
		//---------------------------------------------------
		void				DeleteRemoved();
		int					GetUsedPalette(int spriteID);

	protected :
//		bool				m_bOpen;		// ASPK File�� Open�ߴ°�?
//		class ifstream		m_ASPKFile;		// ASPK File
//		CFileIndexTable		m_ASPKIndex;	// ASPK Index ����
		CAlphaSpritePalPack	m_ASPK;			// ASPK

		//CAlphaSpritePack	*m_pASPK;			// ASPK
		
		// Texture ����Ҷ��� ũ��
		int					*m_pWidth;
		int					*m_pHeight;

		// �������� �͵�..
		SPRITESURFACE_LIST	m_listRemoved;
		SPRITE_PALETTE		m_historySprPal;
		MPalettePack		m_EffectAlphaPPK;
};


#endif

