//-----------------------------------------------------------------------------
// ShowTimeChecker.h
//-----------------------------------------------------------------------------

#ifndef __SHOWTIMECHECKER_H__
#define __SHOWTIMECHECKER_H__

#include <Windows.h>
class ofstream;
class ifstream;

class ShowTimeChecker {
	public :
		ShowTimeChecker();
		~ShowTimeChecker();

		bool			IsShowTime() const;		// �� ����� ��Ȳ����.. ShowTime�ΰ�?
		bool			IsShowHour() const;		// startHour~EndHour�� ����..

		void			SetNextShowTime();

		//---------------------------------------------------------------
		// File I/O
		//---------------------------------------------------------------
		void			SaveToFile(class ofstream& file);
		void			LoadFromFile(class ifstream& file);

	public :
		// �ݺ����ΰ�?
		bool			Loop;

		// MinDelay ~ MaxDelay ���̿��� �� �� ��
		DWORD			MinDelay;
		DWORD			MaxDelay;
		
		// StartHour���� EndHour ���̿��� (0~24�ø� ����?)
		BYTE			StartHour;
		BYTE			EndHour;

		DWORD			NextPlayTime;		// ������ show�� �ð�
};

#endif


