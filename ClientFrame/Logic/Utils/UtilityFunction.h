//-----------------------------------------------------------------------------
// UtilityFunction.h
//-----------------------------------------------------------------------------

#ifndef __UTILITYFUNCTION_H__
#define __UTILITYFUNCTION_H__

class CDirectDrawSurface;

//-----------------------------------------------------------------------------
// 문자열 앞 뒤의 공백 제거하기
//-----------------------------------------------------------------------------
void	RemoveStringSpace(char*& str);

//-----------------------------------------------------------------------------
// 정상적인 주민등록번호인가?
//-----------------------------------------------------------------------------
int		IsValidSSN(const char* strSSN1, const char* strSSN2);

//-----------------------------------------------------------------------------
// 정상적인 ID인가?
//-----------------------------------------------------------------------------
int		IsValidID(const char* strID, const char* strPermit);

//-----------------------------------------------------------------------------
// Is Valid Password
//-----------------------------------------------------------------------------
int		IsValidPassword(const char* str);

//-----------------------------------------------------------------------------
// LoadImageToSurface
//-----------------------------------------------------------------------------
bool	LoadImageToSurface(const char* pFilename, CDirectDrawSurface& surface);

//-----------------------------------------------------------------------------
// SaveSurfaceToImage
//-----------------------------------------------------------------------------
bool	SaveSurfaceToImage(const char* pFilename, CDirectDrawSurface& surface);

//-----------------------------------------------------------------------------
// Get DiskFreeSpace
//-----------------------------------------------------------------------------
// Drive가 NULL이면 지정을 안하면 현재 드라이브다.
//-----------------------------------------------------------------------------
unsigned long	GetDiskFreeSpace(const char* pDrive=NULL);

#endif