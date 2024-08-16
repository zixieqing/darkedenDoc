/*-----------------------------------------------------------------------------

	CDirectDrawSurface.h

	DirectX class library component.

	1999.12.28. sigi, KJTINC

-----------------------------------------------------------------------------*/

//----------------------------------------------------------------------
// CDirectDrawSurface.h
//----------------------------------------------------------------------
//
//
// 5:6:5 ��  5:5:5�� ���̴� 
// Bit Mask�� ���� ó���Ǵ� �κп��� �߻��ϴµ�
// CDirectDraw class�� InitMask()���� Video Card�� �´�
// ������ Mask�� �����ϹǷ� �׳�~ CDirectDraw�� Mask�� ����ϸ� �ȴ�.
//
//
//
//----------------------------------------------------------------------
/*

  < DDSurface�� �����Ǵ� MEMORY >

	- DDSCAPS_SYSTEMMEMORY�� Lock�� ����� �� ������.
	- DDSCAPS_VIDEOMEMORY�� Blt�� ����� �� ������.
	  ��, VIDEOMEMORY�� �����ϸ� Surface�� �������� �����Ƿ� error!
	- ������ �� �� �ָ� VIDEOMEMORY�� ��밡���ϸ� ����ϰ� 
   	  �ƴϸ� SYSTEMMEMORY�� ����Ѵ�.
	
  < Alpha Blending >
    - ����Ϸ��� DDSCAPS_SYSTEMMEMORY�� ����ϴ°� ����.
	- Surface --> Surface���� Alpha Blending����
	  Memory(SpriteFile) --> Surface���� Alpha Blending�� ������.

*/
//----------------------------------------------------------------------

#ifndef	__CDIRECTDRAWSURFACE_H__
#define	__CDIRECTDRAWSURFACE_H__


#include "CDirectDraw.h"

/*-----------------------------------------------------------------------------
  Class DirectDraw Surface
-----------------------------------------------------------------------------*/
class CDirectDrawSurface : public CDirectDraw 
{
public :
	CDirectDrawSurface();
	~CDirectDrawSurface();

	// text out for debugging.
	void	GDI_Text(int x, int y, const char *str, COLORREF fcolor, 
																 COLORREF bcolor = 0, 
																 bool option = true);
	void	ShowFPS(int x, int y, COLORREF bcolor, COLORREF fcolor); // FPS�� ����Ѵ�.


	//------------------------------------------------------------
	// Gamma
	//------------------------------------------------------------
	void			GammaBox555(RECT* pRect, int p);
	void			GammaBox565(RECT* pRect, int p);
	static void		Gamma4Pixel(void *pDest, int len, int p)	{ (*s_GammaFunction)(pDest, len, p); }		
	static void		Gamma4Pixel565(void *pDest, int len, int p);
	static void		Gamma4Pixel555(void *pDest, int len, int p);
	static void		SetGammaFunction()
	{
		if (CDirectDraw::Is565())
			s_GammaFunction = Gamma4Pixel565;
		else 
			s_GammaFunction = Gamma4Pixel555;
	}

	//------------------------------------------------------------
	// Init
	//------------------------------------------------------------
	bool	InitBacksurface();	
	bool	InitOffsurface(int wWidth, int wHeight, DWORD dwCaps = 0);	
	bool	InitFromBMP(LPCSTR szBitmap, DWORD dwCaps = 0);
	bool	InitTextureSurface(int wWidth, int wHeight, DWORD dwCaps = 0, const LPDDPIXELFORMAT pDDPF = NULL);
	bool	InitTextureSurfaceFromBMP(LPCSTR szBitmap, DWORD dwCaps = 0);

	//------------------------------------------------------------
	// Load bitmap from File
	//------------------------------------------------------------
	bool	ReLoadBMP(LPCSTR szBitmap);		
	bool	SaveToBMP(const char* szFilename);

	//------------------------------------------------------------
	// Restore Lost Surface
	//------------------------------------------------------------
	bool	Restore();

	//------------------------------------------------------------
	// Set Transparency color
	// `Blt�� �� �ݵ�� ����� �Ѵ�.
	//------------------------------------------------------------
	void	SetTransparency(DWORD dwValue);

	//------------------------------------------------------------
	// Blt
	//------------------------------------------------------------
	void	Blt(POINT* pPoint, CDirectDrawSurface* SourceSurface, RECT*  pRect);
	void	BltNoColorkey(POINT* pPoint, CDirectDrawSurface* SourceSurface, RECT*  pRect);
	void	Blt(RECT* pDestRect, CDirectDrawSurface* SourceSurface, RECT* pSourceRect);	

	// ���� surface�� pPoint�� PrimarySurface�� pRect�� blt�Ѵ�.
	void	BltPrimarySurface(POINT* pPoint, RECT* pRect);

	//------------------------------------------------------------
	// DirectDraw ���� Drawing �Լ���...
	//------------------------------------------------------------
	void	FillSurface(WORD color);
	void	FillRect(RECT* rect, WORD Color);
		
	//------------------------------------------------------------
	// Get
	//------------------------------------------------------------
	inline void *	GetSurfacePointer() { return m_ddsd.lpSurface; }
	inline long		GetSurfacePitch() { return m_ddsd.lPitch; }
	inline LPDIRECTDRAWSURFACE7 &	GetSurface() { return m_pDDSurface; } const
	inline DDSURFACEDESC2 * GetDDSD() { return &m_ddsd; }
	inline int		GetWidth() const	{ return m_Width; } // no const...
	inline int		GetHeight() const	{ return m_Height; } // no const...

	//------------------------------------------------------------
	// Clip ����
	//------------------------------------------------------------
	///*
	inline void		SetClipLeft(int Left)				{ if (Left>=0) m_ClipLeft = Left; }
	inline void		SetClipTop(int Top)					{ if (Top>=0) m_ClipTop = Top; }
	inline void		SetClipLeftTop(int Left, int Top)	{ if (Left>=0) m_ClipLeft = Left; 
															if (Top>=0) m_ClipTop = Top; }

	inline void		SetClipRight(int Right)			{ if (Right<=m_Width) m_ClipRight = Right; }
	inline void		SetClipBottom(int Bottom)		{ if (Bottom<=m_Height) m_ClipBottom = Bottom; }
	inline void		SetClipRightBottom(int Right, int Bottom)	{ if (Right<=m_Width) m_ClipRight = Right; 
														if (Bottom<=m_Height) m_ClipBottom = Bottom; }
	
	inline void		SetClip(RECT* pRect)			{ SetClipLeftTop(pRect->left, pRect->top); SetClipRightBottom(pRect->right, pRect->bottom); }
	inline void		SetClipNULL()					{ m_ClipLeft=0; m_ClipTop=0; m_ClipRight=m_Width; m_ClipBottom=m_Height; }

	inline int		GetClipRight() const			{ return m_ClipRight; } // no const...
	inline int		GetClipBottom() const			{ return m_ClipBottom; } // no const...
	inline int		GetClipLeft() const				{ return m_ClipLeft; } // no const...
	inline int		GetClipTop() const				{ return m_ClipTop; } // no const...	
	
	
	//*/

	//
	// ! Pitch�� Surface pointer�� ��������, CDirectDraw�� GetDDDesc()�� �̿��Ѵ�.
	//

	//------------------------------------------------------------
	// Lock / Unlock
	//------------------------------------------------------------		
	bool		Lock();
	bool		Unlock();
	bool		IsLock() const		{ return m_bLock; }

	// ��... �׳� cast�ؼ� ���°�...
	void	LockW(WORD*& lpSurface, WORD& lPitch);
	//void	LockDW(DWORD*& lpSurface, WORD& lPitch);
	//void	LockQW(QWORD*& lpSurface, WORD& lPitch);

	//------------------------------------------------------------		
	// operator
	//------------------------------------------------------------		
	operator const LPDIRECTDRAWSURFACE7&()	{ return m_pDDSurface; }
	
	// class ���ο��� ���� �Լ�
protected :
	bool	CopyBitmap(HBITMAP hbm, int x, int y, int dx, int dy);

protected :
	LPDIRECTDRAWSURFACE7	m_pDDSurface;

	// Surface�� ũ��, ���ӻ��� �����Ƿ� member�� ������ �ִ´�.
	int					m_Width;
	int					m_Height;

	// surface�� back surface�ΰ��� ��Ÿ���� flag.
	bool					m_bBackSurface;	

	// Lock�� �� �����ΰ�?
	bool					m_bLock;	

	// ���� ũ�⺸�� ����.. Clip�� �Ǿ �������� ������ ����	
	int					m_ClipRight;
	int					m_ClipBottom;
	int					m_ClipLeft;
	int					m_ClipTop;

	static	void		(*s_GammaFunction)(void *pDest, int len, int p);
};

#endif

