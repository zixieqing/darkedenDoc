#include "CSpritePal.h"

#include "CDirectDraw.h"

#include <vector>
#include <fstream.h>

MPalette::MPalette()
{
	m_Size = 0;
	m_pColor = NULL;
}

MPalette::~MPalette()
{
	Release();
}

void MPalette::Release()
{
	if(m_pColor != NULL)
	{ 
		delete []m_pColor;
		m_pColor = NULL;
		m_Size = 0;
	}
}

void MPalette::Init(BYTE size)
{
	if (size==0) return;
	Release();
	
	m_Size = size;
	m_pColor = new WORD[m_Size];
}

void MPalette::operator = (const MPalette& pal)
{
	// �޸� ����
	Release();
	
	m_Size = pal.m_Size;

	m_pColor = new WORD[m_Size];
	
	memcpy(m_pColor, pal.m_pColor, m_Size);
}


// file save�� 565�� �������� �Ѵ�.
bool MPalette555::LoadFromFile(class ifstream &file)
{
	Release();
	
	file.read((char *)&m_Size, 1);
	
	Init(m_Size);
	
	for(int i = 0; i < m_Size; i++)
	{
		file.read((char *)&m_pColor[i], 2);
		m_pColor[i] = ((m_pColor[i] & 0xffc0) >> 1) | (m_pColor[i] & 0x1f);
	}
	
	return true;
}

// file save�� 565�� �������� �Ѵ�.
bool MPalette555::SaveToFile(class ofstream &file)
{
	file.write((const char *)&m_Size, 1);
	
	WORD color = 0;
	
	for(int i = 0; i < m_Size; i++)
	{
//		color = m_pColor[i];
		color = ((m_pColor[i] & 0xffe0) << 1) | (m_pColor[i] & 0x1f);
		file.write((const char *)&color, 2);
	}
	
	return true;
}

bool MPalette565::LoadFromFile(class ifstream &file)
{
	Release();
	
	file.read((char *)&m_Size, 1);
	
	Init(m_Size);
	
	for(int i = 0; i < m_Size; i++)
	{
		file.read((char *)&m_pColor[i], 2);
	}

	return true;
}

bool MPalette565::SaveToFile(class ofstream &file)
{
	file.write((const char *)&m_Size, 1);
	
	for(int i = 0; i < m_Size; i++)
	{
		file.write((const char *)&m_pColor[i], 2);
	}

	return true;
}

MPalettePack::MPalettePack()
{
	m_pPalette = NULL;
	m_Size = 0;
}

MPalettePack::~MPalettePack()
{
	Release();
}

void MPalettePack::Release()
{
	if(m_pPalette != NULL)
	{
		delete []m_pPalette;
		m_pPalette = NULL;
		m_Size = 0;
	}
}

void MPalettePack::Init(WORD size, bool b565)
{
	if(size == 0)
		return;

	Release();

	m_b565 = b565;
	m_Size = size;

	if(m_b565)
		m_pPalette = new MPalette565[size];
	else
		m_pPalette = new MPalette555[size];
}

bool MPalettePack::LoadFromFile(LPCTSTR lpszFilename, bool b565)
{
	ifstream file(lpszFilename, ios::binary);
	bool re = LoadFromFile(file, b565);
	file.close();
	
	return re;
}

bool MPalettePack::SaveToFile(LPCTSTR lpszFilename)
{
	ofstream file(lpszFilename, ios::binary);
	bool re = SaveToFile(file);
	file.close();
	
	return re;
}

bool MPalettePack::LoadFromFile(class ifstream &file, bool b565)
{
	Release();
	
	file.read((char *)&m_Size, 2);
	
	Init(m_Size, b565);
	
	for(int i = 0; i < m_Size; i++)
	{
		m_pPalette[i].LoadFromFile(file);
	}
	
	return true;
}

bool MPalettePack::SaveToFile(class ofstream &file)
{
	DWORD flag = 0;
	
	file.write((const char *)&m_Size, 2);
	
	for(int i = 0; i < m_Size; i++)
	{
		m_pPalette[i].SaveToFile(file);
	}
	
	return true;
}


BYTE CSpritePal::s_Colorkey = 0xFF;

CSpritePal::CSpritePal()
{
	m_Width = 0;		// ���� pixel��
	m_Height = 0;		// ���� pixel��		
	m_Size = 0;			// ��������Ʈ�� size
	
	m_pPixels = NULL;		// pixels point array
	m_pData = NULL;			// data
	
	m_bInit = false;		// data�� �ִ°�?
	m_bLoading = false;		// Loading���ΰ�?
}

CSpritePal::~CSpritePal()
{
	Release();
}

void CSpritePal::Release()
{
	m_Width = 0;		// ���� pixel��
	m_Height = 0;		// ���� pixel��		
	m_Size = 0;			// ��������Ʈ�� size

	if(m_pData != NULL)
	{
		delete [] m_pData;
		m_pData = NULL;			// data
		m_pPixels = NULL;
	}
	
	m_bInit = false;		// data�� �ִ°�?
	m_bLoading = false;		// Loading���ΰ�?
}

void CSpritePal::SetEmptySprite()
{
	Release();
	m_bInit = true;
}

void CSpritePal::SetPixel(BYTE *pSource, WORD pitch, WORD width, WORD height)
{
	// memory����
	Release();

	m_Width = width;
	m_Height = height;

	// �ϴ� memory�� ������ ��Ƶд�.	
	BYTE*	data = new BYTE[m_Width*2+10];

	int		index,				// data�� index�� ���
			lastColorIndex;		// ������ �ƴѻ� ������ �ֱ� index
	int		count;				// �ݺ���
	int		trans,				// ����� ����
			color;				// ������ �ƴѻ� ����

	BOOL	bCheckTrans;		// �ֱٿ� �˻��Ѱ� ������ΰ�?

	BYTE	*pSourceTemp;


	// height�� ��ŭ memory���
	m_pPixels = new BYTE* [height];
	BYTE **Pixels = new BYTE* [height];
	std::vector<int> PixelSize;

	register int i;
	register int j;

	for (i=0; i<height; i++)
	{
		index = 0;
		count = 0;
		trans = 0;
		color = 0;
		bCheckTrans = TRUE;

		pSourceTemp = pSource;

		// �� line�� ���ؼ� ����~
		for (j=0; j<width; j++)
		{
			// 0�� color�� ���ؼ� ����
			if (*pSourceTemp==s_Colorkey)
			{
				// �ֱٿ� �˻��Ѱ� ������� �ƴϾ��ٸ�
				if (!bCheckTrans)
				{
					// ' (����,�����,�����) '�� �� set�� �������� �ǹ��ϹǷ�
					count++;
					
					data[lastColorIndex] = color;
					color = 0;

					bCheckTrans = TRUE;
				}
				
				trans++;				
			}
			else
			{
				// �ֱٿ� �˻��Ѱ� ������̾��ٸ�..
				if (bCheckTrans)
				{						
					data[index++] = trans;		// ���� byte�� ������� �ִ´�.
					trans = 0;

					lastColorIndex=index++;			// ������� ���� ��ġ�� ���					

					bCheckTrans = FALSE;
				}

				data[index++] = *pSourceTemp;	// ���� ������ �����Ѵ�.

				color++;								
			}

			pSourceTemp++;
		}
		
		// �� ���� ������ ���� ������ΰ�?
		if (bCheckTrans)
		{
			// ������̸� ���ٸ� ó���� �����൵ �ɰ� ����.
		}	
		// ������� �ƴ� ���, ���� ������ ���������� �Ѵ�.
		else
		{			
			count++;
			data[lastColorIndex] = color;
		}
		
		// memory�� �ٽ� ��´�.
		Pixels[i] = new BYTE [index+1];
		m_Size += index+1;

		// m_pPixels[i]�� ���������Ƿ� data�� ��ü�Ѵ�.
		// m_pPixels[i][0]���� count�� �־�� �Ѵ�.
		Pixels[i][0] = count;
		memcpy(Pixels[i]+1, data, index);
		PixelSize.push_back(index+1);

		pSource = pSource + pitch;
	}

	m_pData = new BYTE[m_Size+sizeof(BYTE *)*height];
	m_pPixels = (BYTE **)(m_pData+m_Size);
	BYTE *TempData = m_pData;

	for(i = 0; i < height; i++)
	{
		memcpy(TempData, Pixels[i], PixelSize[i]);
		m_pPixels[i] = TempData;
		TempData += PixelSize[i];
		delete [] Pixels[i];
	}

	delete [] data;
	delete [] Pixels;

	m_bInit = true;
}

void CSpritePal::Blt(int x, int y, WORD* pDest, int pitch, MPalette &pal)
{
	int	count,			
		colorCount;
	
	WORD	*pDestTemp;
	BYTE	*pPixels;
	
	register int i;
	register int j;
	register int k;
	int rectBottom = m_Height;
	
	pDest = (WORD*)((BYTE*)pDest + y*pitch +x*2);
	
	if (rectBottom > 0)
	{
		i = 0;
		
		do
		{
			pPixels		= m_pPixels[i];
			pDestTemp = (WORD*)((BYTE*)pDest + i*pitch);
			
			// (�����,�����,�����)�� �ݺ� ��		
			count	= *pPixels++;		
			// �� �� ���
			if (count > 0)
			{	
				j = count;
				do {
					pDestTemp += *pPixels++;			// �������ŭ �ǳ� �ڴ�.
					colorCount = *pPixels++;		// ���� �ƴ� �� ��				
					
					// ������ �ƴ� ������ Surface�� ����Ѵ�.
					for(k = 0; k < colorCount; k++)
					{
						memcpy((void*)(pDestTemp+k), (void*)(&pal[*(pPixels+k)]), 2);
					}
					
					pDestTemp	+= colorCount;
					pPixels		+= colorCount;
				} while (--j);
			}
			
		} while (i++ < rectBottom-1);
	}
}

bool CSpritePal::LoadFromFile(class ifstream &file)
{
	Release();
	
	file.read((char *)&m_Size, 4);

//	// size �� ������ ��������
//	if(m_Size == 0)
//		return true;

	file.read((char *)&m_Width, 2);
	file.read((char *)&m_Height, 2);

	m_pData = new BYTE[m_Size+sizeof(BYTE *)*m_Height];
	m_pPixels = (BYTE **)(m_pData+m_Size);

	file.read((char *)m_pData, m_Size);

	register int i;
	
	WORD *indexArray = new WORD[m_Height];

	file.read((char *)indexArray, m_Height<<1);

	BYTE *tempData = m_pData;

	for (i=0; i<m_Height; i++)
	{
		m_pPixels[i] = tempData;
		tempData += indexArray[i];
	}

	delete []indexArray;

	m_bInit = true;
	
	return true;
}

bool CSpritePal::SaveToFile(class ofstream &file)
{
	if(IsNotInit())
	{
		MessageBox(NULL, "�ƹ��͵� ���µ� �� ������-_-", "CSpritePal", MB_OK);
		return false;
	}

	if(IsInit() && m_Size == 0)
	{
		return false;
	}

	file.write((const char *)&m_Size, 4);

//	// size�� 0�̸� ��������
//	if(m_Size == 0)
//		return true;

	file.write((const char *)&m_Width, 2);
	file.write((const char *)&m_Height, 2);
	file.write((const char *)m_pData, m_Size);

	register int i;

	WORD index;

	for (i=0; i<m_Height; i++)
	{
		if(i == m_Height -1)
		{
			index = (m_pData+m_Size) - m_pPixels[i];
		}
		else
			index = m_pPixels[i+1] - m_pPixels[i];
		// byte���� ���� data�� �����Ѵ�.
		file.write((const char*)&index, 2);
	}

	return true;
}

void CSpritePal::operator = (const CSpritePal& sprite)
{
	// �޸� ����
	Release();

	m_Size = sprite.m_Size;
	m_Width = sprite.m_Width;
	m_Height = sprite.m_Height;
	m_bInit = true;

	m_pData = new BYTE[m_Size+sizeof(BYTE *)*m_Height];
	m_pPixels = (BYTE **)(m_pData+m_Size);
	
	memcpy(m_pData, sprite.m_pData, m_Size);

	register int i;
	for(i = 0; i < m_Height; i++)
	{
		m_pPixels[i] = m_pData + (sprite.m_pPixels[i]-sprite.m_pData);
	}
}

CSpritePalPack::CSpritePalPack()
{
	m_pSpritePals = NULL;
	m_Size = 0;
}

CSpritePalPack::~CSpritePalPack()
{
	Release();
}

void CSpritePalPack::Release()
{
	if(m_pSpritePals != NULL)
	{
		delete []m_pSpritePals;
		m_pSpritePals = NULL;
		m_Size = 0;
	}
}

void CSpritePalPack::Init(WORD size)
{
	if(size == 0)
		return;
	
	Release();
	
	m_Size = size;
	
	m_pSpritePals = new CSpritePal[size];
}

bool CSpritePalPack::LoadFromFile(LPCTSTR lpszFilename)
{
	ifstream file(lpszFilename, ios::binary);
	bool re = LoadFromFile(file);
	file.close();

	return re;
}

bool CSpritePalPack::SaveToFile(LPCTSTR lpszFilename)
{
	ofstream file(lpszFilename, ios::binary);
	bool re = SaveToFile(file);
	file.close();

	return re;
}


bool CSpritePalPack::LoadFromFile(class ifstream &file)
{
	Release();
	
	file.read((char *)&m_Size, 2);
	
	Init(m_Size);
	
	register int i;

	for(i = 0; i < m_Size; i++)
	{
		m_pSpritePals[i].LoadFromFile(file);
	}
	
	return true;
}

bool CSpritePalPack::SaveToFile(class ofstream &file)
{
	file.write((const char *)&m_Size, 2);
	WORD realSize = m_Size;
	
	for(int i = 0; i < m_Size; i++)
	{
		if(m_pSpritePals[i].SaveToFile(file) == false)
		{
			realSize--;
		}
	}
	
	if(realSize != m_Size)
	{
		char szTemp[512];
		sprintf(szTemp, "real size : %d size : %d", realSize, m_Size);
		file.seekp(0);
		file.write((const char *)&realSize, 2);
	}

	return true;
}

