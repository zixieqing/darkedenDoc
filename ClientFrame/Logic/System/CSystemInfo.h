/********************************************************************
	created:	2003/10/17
	created:	17:10:2003   13:39
	filename: 	E:\designed\project\CSystemInfo.h
	file path:	E:\designed\project
	file base:	CSystemInfo
	file ext:	h
	author:		sonee
	
	purpose:
*********************************************************************/


#pragma once

class CSystemInfo
{
public :
	//------------------------------------------------------------------
	// Processor ���� 
	//------------------------------------------------------------------
	long			GetCpuClock();
	bool			CheckMMXTechnology();
//	bool			CheckSSETechnology();				// VC7 ���� ����.
	bool			CheckSSE2Technology();
	bool			Check3DNowTechnology();
	bool			CheckHyperThreadTechnology();

	//------------------------------------------------------------------
	// VideoCard ����
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	// System-Memory
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	// Sound/Monitor
	//------------------------------------------------------------------

private :	
	
};
