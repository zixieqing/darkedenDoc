#ifndef _SOUNDBUF_H_
#define _SOUNDBUF_H_

#include <wtypes.h>
#include "mp3.h"
//#include "dslib.h"
#include <dsound.h>


struct MP3 ;

struct SOUNDBUF
{
	char		databuf[0x1200] ;		// ���� ���ǽ��� ������� ����Ÿ�� ���� 
	int			nWritten ;				// �� ����Ʈ �� 
	int			lp ;					// ���� ä�� �ε��� (����� ��� �� ����Ÿ �ε���)
	int			rp ;					// ������ ä�� �ε��� 
	int			channels ;				// ä�� �� ( 1 or 2 ) 
	int			nFrames ;				// ���۸� ��
	int			nPushedFrames ;			// ���� ���۸��� �� 
	int			bufSize ;				// ������ ������ 
	int			curBuffer ;				// ���� ������ ID 
	LPDIRECTSOUNDBUFFER		dsPlayBuf ;				// ���ֿ� ���� 
	LPDIRECTSOUNDBUFFER		dsWriteBuf ;			// ����� ���� 
	int			readyBufs ;				// ����Ÿ�� ��� ������ �� 
	int			offWrite ;				// ���� ������ write ������
	BOOL		bPlaying ;				// ���� ������??
} ;

typedef SOUNDBUF	*LPSOUNDBUF ;


LPSOUNDBUF CreateSoundBuf ( MP3 *mp3, int nFrames, DSBPOSITIONNOTIFY[], int n  ) ;
LPSOUNDBUF CreateSoundBuf ( MP3 *mp3, int nFrames) ;
int AppendData ( int ch, LPSOUNDBUF lpsb, int data ) ;
int Destroy ( LPSOUNDBUF lpsb ) ;
int WriteTo ( LPSOUNDBUF lpsb , BYTE* arr) ;
extern int OutputData (LPSOUNDBUF lpsb ) ;
#endif // _SOUNDBUF_H_