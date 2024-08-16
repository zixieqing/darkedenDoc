//----------------------------------------------------------------------
// CShadowPartManager.h
//----------------------------------------------------------------------
// Ư��File(SSPK)�� ���ؼ�
// FileIndex(SSPKI)�� �����ؼ�
// �Ϻ��� ShadowSprite�� Load�ؼ� ����ϰ� �ϴ� class
//----------------------------------------------------------------------
// �׸��� Texture�� �⺻ ũ��� 64*64�̴�.
//----------------------------------------------------------------------
// �̰Ŷ� TexturePartManager�� ���� ����..
// template���� �ٲ�� �Ǵµ�.. - -;; �� ������... ���߿�.. - -;
//----------------------------------------------------------------------

#ifndef	__CSHADOWPARTMANAGER_H__
#define	__CSHADOWPARTMANAGER_H__

#include "CPartManager.h"
#include "CSpriteSurface.h"
#include "DrawTypeDef.h"
#include <list>
#include "CShadowSprite.h"
class ifstream;
class CFileIndexTable;

// <��ü����, ��밳��, ���Data>
class CShadowPartManager : public CPartManager<WORD, WORD, CSpriteSurface*>
{
	public :
		typedef std::list<CSpriteSurface*>	SPRITESURFACE_LIST;

	public :
		//CShadowPartManager(CShadowSpritePack* pSSPK, WORD partSize=100);
		CShadowPartManager(const char* SSPKFilename, WORD partSize=100);
		~CShadowPartManager();

		//---------------------------------------------------
		// Init / Release
		//---------------------------------------------------
		//void				Init(CShadowSpritePack* pSSPK, WORD partSize);
		void				Init(const char* SSPKFilename, WORD partSize);
		void				Release();
	
		// data������ �ʱ�ȭ ��Ų��.
		void				Clear();

		//---------------------------------------------------
		// sspk�� id��° AlphaSprite�� �Ѱܹ޴´�.
		//---------------------------------------------------
		CSpriteSurface*		GetTexture(TYPE_SPRITEID id);

		// AlphaSprite�� ���� ũ�⸦ �Ѱ��ش�.
		int					GetWidth(TYPE_SPRITEID id)	{ return m_pWidth[id]; }
		int					GetHeight(TYPE_SPRITEID id)	{ return m_pHeight[id]; }

		// Sprite�� �Ѱ��ش�.
		CShadowSprite&		GetSprite(TYPE_SPRITEID id);

		//---------------------------------------------------
		// ������ �� �͵�
		//---------------------------------------------------
		void				DeleteRemoved();


	protected :
//		bool				m_bOpen;		// SSPK File�� Open�ߴ°�?
//		class ifstream		m_SSPKFile;		// SSPK File
//		CFileIndexTable		m_SSPKIndex;	// SSPK Index ����
		CShadowSpritePack	m_SSPK;			// SSPK

		//CShadowSpritePack	*m_pSSPK;			// SSPK
		

		// Texture ����Ҷ��� ũ��
		int					*m_pWidth;
		int					*m_pHeight;

		// �������� �͵�..
		SPRITESURFACE_LIST	m_listRemoved;
};


#endif

