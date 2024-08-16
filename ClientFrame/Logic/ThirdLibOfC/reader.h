#ifndef _MP3_READER_H_
#define _MP3_READER_H_

#include <wtypes.h>
#include "mp3.h"
#include <stdio.h>

extern int Open(LPSTR PathName) ;						// MP3 ������ ����.
extern int Close() ;									// MP3 ������ �ݴ´�.
extern int ReadHeader(UINT *headerStr) ;				// ����θ� �о���δ�.	
extern int ReadBytes(BYTE* buf, UINT bytes) ;			// 1 ����Ʈ ������ �о���δ�.
extern int ReadWords(WORD* buf, UINT words) ;			// 2 ����Ʈ ������ �о���δ�.
extern int ReadDwords(DWORD* buf, UINT dwords) ;		// 4 ����Ʈ ������ �о���δ�.
extern UINT ReadBits(UINT bits) ;
extern int ReadSideInfo(UINT channel, side_info_t *sideInfo) ;	// 
extern int GetCurOffset() ;				// ������ offset�� ��� �´�.
extern int GetFileSize() ;				// ���� ����� ���´�.
extern int SetOffset(int offset) ;
extern int GetMaxFrames(MP3 *mp3) ;
extern int GetMinFrames(MP3 *mp3) ;

#endif //_MP3_READER_H_
