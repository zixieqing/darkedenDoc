//--------------------------------------------------------------------------
// WavePackFileManager.h
//--------------------------------------------------------------------------
/*
	
		// WaveFileData

		WAVEFORMATEX	wavefmt;
		DWORD			size;
		char*			pBuffer;

*/
//--------------------------------------------------------------------------


#ifndef __WAVE_PACK_FILE_MANAGER__
#define __WAVE_PACK_FILE_MANAGER__

#include "PackFileManager.h"
#include "MTypeDef.h"
#include <DSound.h>

//--------------------------------------------------------------------------
// WavePackFileInfo
//--------------------------------------------------------------------------
class WavePackFileInfo : public PackFileInfo {
	public :
		WavePackFileInfo() {}
		virtual ~WavePackFileInfo() {}

		virtual bool			SaveToFileData(class ofstream& file);
		LPDIRECTSOUNDBUFFER		LoadFromFileData(class ifstream& file);
};

//--------------------------------------------------------------------------
// WavePackFileManager
//--------------------------------------------------------------------------
class WavePackFileManager : public PackFileManager<WavePackFileInfo> {
	public :
		WavePackFileManager();
		virtual ~WavePackFileManager();

		LPDIRECTSOUNDBUFFER		LoadFromFileData(TYPE_SOUNDID id);
};

extern WavePackFileManager*	g_pWavePackFileManager;

#endif