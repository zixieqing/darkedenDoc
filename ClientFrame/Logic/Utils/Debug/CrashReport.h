/********************************************************************
	created:	2003/12/01
	created:	1:12:2003   12:16
	filename: 	D:\study\smodulelib\CrashReport.h
	file path:	D:\study\smodulelib
	file base:	CrashReport
	file ext:	h
	author:		����
	
	purpose:	ġ������ ������ ������ �α׸� �����.
*********************************************************************/

#pragma once

extern LONG __stdcall RecordExceptionInfo( _EXCEPTION_POINTERS* pExp );

// �α� ���ϸ��� �ٲٰ� ������ ���� �ٲټ�
#define OLD_CRASH_LOG_FILENAME	"CrashReport.log"
#define CRASH_LOG_FILENAME		"CrashReport2.log"

#define InitCrashReport()		SetUnhandledExceptionFilter( RecordExceptionInfo )
