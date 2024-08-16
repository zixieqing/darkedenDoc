//----------------------------------------------------------------------
// CMessageArray.h
//----------------------------------------------------------------------
// String Array�̴�.
// 
// �ʱ�ȭ �� �� : Init(String��, ��String�� �ִ����, log File);
//
// Init(...)�Ҷ� �޸𸮸� �� ��ƹ�����.
// filename�� ���ָ� �ڵ����� string�� �߰��ɶ� log�Ѵ�.
//----------------------------------------------------------------------

#ifndef	__CMESSAGEARRAY_H__
#define	__CMESSAGEARRAY_H__

class CMessageArray {
	public :
		CMessageArray();
		~CMessageArray();

		//--------------------------------------------------
		// Init / Release
		//--------------------------------------------------
		void		Init(int max, int length, const char* filename=NULL);
		void		Release();

		//--------------------------------------------------
		// Add / Get
		//--------------------------------------------------
		void		Add(const char *str);
		//void		Add(std::string str)			{ Add(str.c_str()); }
		void		AddToFile(const char *str);
		//void		AddToFile(std::string str)	{ AddToFile(str.c_str()); }
		void		AddFormat(const char* format, ...);
		void		AddFormatVL(const char* format, va_list& vl);
		const char*	operator [] (int i);

		// �ܺο��� ����..
		char*&		GetCurrent()		{ return m_ppMessage[m_Current]; }

		// ���� ��
		void		Next();

		// size
		int			GetSize() const			{ return m_Max; }

		// clear
		void		Clear();

		// filename
		const char*	GetFilename() const		{ return m_Filename; }


	protected :		
		int			m_Length;		// Message �ϳ��� ����
		int			m_Max;			// Message ����

		char**		m_ppMessage;	// �Էµ� Message
		int			m_Current;		// �Է��ҷ��� Message 

		// file Log
		bool			m_bLog;
		int				m_LogFile;
		char*			m_Filename;


};

#endif


