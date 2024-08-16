//----------------------------------------------------------------------
// SectorSoundInfo.h
//----------------------------------------------------------------------

#ifndef __SECTORSOUNDINFO_H__
#define __SECTORSOUNDINFO_H__

#pragma warning(disable:4786)

#include "MTypeDef.h"
#include <list>
class ofstream;
class ifstream;


//----------------------------------------------------------------------
// SectorSoundInfo
//----------------------------------------------------------------------
// ZoneSoundID�� (x, y)���� �Ҹ��� ����..�� ����.
//----------------------------------------------------------------------
class SECTORSOUND_INFO
{
	public :
		unsigned short		ZoneSoundID;
		unsigned char		X, Y;

	public :
		SECTORSOUND_INFO(unsigned short zoneSoundID=0, unsigned char x=0, unsigned char y=0)
		{
			ZoneSoundID = zoneSoundID;
			X = x;
			Y = y;
		}

		void		operator = (const SECTORSOUND_INFO& info)
		{
			ZoneSoundID = info.ZoneSoundID;
			X = info.X;
			Y = info.Y;
		}

		bool		operator == (const SECTORSOUND_INFO& info) const
		{
			return ZoneSoundID==info.ZoneSoundID
					&&	X==info.X
					&&	Y==info.Y;
		}

		bool		operator != (const SECTORSOUND_INFO& info) const
		{
			return ZoneSoundID!=info.ZoneSoundID
					||	X!=info.X
					||	Y!=info.Y;
		}

		void	SaveToFile(class ofstream& file) const;
		void	LoadFromFile(class ifstream& file);
};


// SectorSound List
typedef std::list<SECTORSOUND_INFO>		SECTORSOUND_LIST;


#endif