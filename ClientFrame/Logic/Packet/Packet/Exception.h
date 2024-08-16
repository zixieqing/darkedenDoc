//////////////////////////////////////////////////////////////////////
// 
// Filename    : Exception.h 
// Written By  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

// include files
#include "Types.h"
#include "StringStream.h"

#if __WINDOWS__
#pragma warning ( disable : 4786 )
#endif

#include <list>


//////////////////////////////////////////////////////////////////////
//
// class Throwable
//
// Exception �� Error �� ���̽� Ŭ�����̴�. ���� �޽�� �� ����Ÿ��
// �����س��� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class Throwable {

public :

	// constructor
	Throwable () throw () {}
	
	// constructor
	Throwable ( std::string message ) throw () : m_Message(message) {}

	// destructor
	virtual ~Throwable () throw () {}

	// return class's name
	virtual std::string getName () const throw () { return "Throwable"; }

	// add function name to throwable object's function stack
	void addStack ( const std::string & file, const int line ) throw ()
	{
		StringStream s;
		s << file << ":" << line;
		m_Stacks.push_front( s.toString());
	}

	// return debug std::string - throwable object's function stack trace
	std::string getStackTrace () const throw ()
	{
		StringStream buf;
		int i = 1;

		for ( std::list<std::string>::const_iterator itr = m_Stacks.begin() ;
			  itr != m_Stacks.end() ;
			  itr ++ , i ++ ) {
			for ( int j = 0 ; j < i ; j ++ )
				buf << " ";
			buf << *itr << '\n' ;
		}
		
		return std::string( buf.toString() );
	}

	// get throwable object's message
	std::string getMessage () const throw () { return m_Message; }
	
	// set throwable object's message
	void setMessage ( const std::string & message ) throw () { m_Message = message; }
	
	// return debug string - throwable object's detailed information
	virtual std::string toString () const throw ()
	{
		StringStream buf;
		buf << getName() << " : " << m_Message << '\n'
			<< getStackTrace () ;
		
		return std::string( buf.toString() );
	}

private :
	
	// message string
	std::string m_Message;
	
	// function stack 
	std::list<std::string> m_Stacks;
};

//--------------------------------------------------------------------------------
// macro definition
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//
// Throwable�� �ʿ��ϱ� ������ �Ʒ��� �����ߴ�.
// Exception/Error�� ������ ��� �޽���� ��/�Ʒ��� ��õǾ�� �Ѵ�.
// __END_CATCH�� Throwable�� �޼ҵ� ���ÿ� ����� �� ������ ������
// ������ �Ѵ�.
//
//--------------------------------------------------------------------------------

#ifdef NDEBUG
	#define __BEGIN_TRY ((void)0);
	#define __END_CATCH ((void)0);
#else
	#define __BEGIN_TRY \
				try {
	#define __END_CATCH \
				} catch ( Throwable & t ) { \
					t.addStack(__FILE__, __LINE__); \
					throw; \
				}
#endif

//--------------------------------------------------------------------------------
//
// critical section
//
//--------------------------------------------------------------------------------
#define __ENTER_CRITICAL_SECTION(mutex) \
			mutex.lock(); \
			try {

#define __LEAVE_CRITICAL_SECTION(mutex) \
			} catch ( Throwable & t ) { \
				mutex.unlock(); \
				throw; \
			} \
			mutex.unlock();

//--------------------------------------------------------------------------------
//
// cout debugging
//
//--------------------------------------------------------------------------------
#if defined(NDEBUG) || defined(__WIN32__)
	#define __BEGIN_DEBUG ((void)0);
	#define __END_DEBUG ((void)0);
#elif defined(__LINUX__) || defined(__WIN_CONSOLE__)
	#define __BEGIN_DEBUG \
				try {
	#define __END_DEBUG  \
				} catch ( Throwable & t ) { \
					cout << t.toString() << endl; \
					throw; \
				} catch ( exception & e ) { \
					cout << e.what() << endl; \
					throw; \
				}
#elif defined(__MFC__)
	#define __BEGIN_DEBUG \
				try {
	#define __END_DEBUG \
				} catch ( Throwable & t ) { \
					AfxMessageBox(t.toString()); \
					throw; \
				}
#endif


//////////////////////////////////////////////////////////////////////
//
// Exception
//
//////////////////////////////////////////////////////////////////////
class Exception : public Throwable {
public :
	Exception () throw () : Throwable() {}
	Exception ( std::string msg ) throw () : Throwable(msg) {}
	std::string getName () const throw () { return "Exception"; }
};

	//////////////////////////////////////////////////////////////////////
	//
	// I/O Exception
	//
	// ����, ����, IPC ����½� �߻��� �� �ִ� ����
	//
	//////////////////////////////////////////////////////////////////////
	// ����, ����, IPC ����½� �߻��� �� �ִ� ����
	class IOException : public Exception {
	public :
		IOException () throw () : Exception () {}
		IOException ( std::string msg ) throw () : Exception (msg) {}
		std::string getName () const throw () { return "IOException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Non Blocking I/O Exception
		//
		// I/O �� nonblocking �� �߻��� ���
		//
		//////////////////////////////////////////////////////////////////////
		class NonBlockingIOException : public IOException {
		public :
			NonBlockingIOException () throw () : IOException () {}
			NonBlockingIOException ( std::string msg ) throw () : IOException (msg) {}
			std::string getName () const throw () { return "NonBlockingIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted I/O Exception
		//
		// I/O �� ���ͷ�Ʈ�� �ɸ� ���
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedIOException : public IOException {
		public :
			InterruptedIOException () throw () : IOException () {}
			InterruptedIOException ( std::string msg ) throw () : IOException (msg) {}
			std::string getName () const throw () { return "InterruptedIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// EOF Exception
		//
		// I/O �� EOF �� ���� ���
		//
		//////////////////////////////////////////////////////////////////////
		class EOFException : public IOException {
		public :
			EOFException () throw () : IOException () {}
			EOFException ( std::string msg ) throw () : IOException (msg) {}
			std::string getName () const throw () { return "EOFException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// File Not Opened Exception 
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotOpenedException : public IOException {
		public :
			FileNotOpenedException () throw () : IOException() {}
			FileNotOpenedException ( std::string msg ) throw () : IOException(msg) {}
			std::string getName () const throw () { return "FileNotOpenedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Already Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileAlreadyExistException : public IOException {
		public :
			FileAlreadyExistException () throw () : IOException() {}
			FileAlreadyExistException ( std::string msg ) throw () : IOException(msg) {}
			std::string getName () const throw () { return "FileAlreadyExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Not Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotExistException : public IOException {
		public :
			FileNotExistException () throw () : IOException() {}
			FileNotExistException ( std::string msg ) throw () : IOException(msg) {}
			std::string getName () const throw () { return "FileNotExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Time out Exception
		//
		// ���� �ð��� ������ ���
		//
		//////////////////////////////////////////////////////////////////////
		class TimeoutException : public IOException {
		public :
			TimeoutException () throw () : IOException () {}
			TimeoutException ( std::string msg ) throw () : IOException (msg) {}
			std::string getName () const throw () { return "TimeoutException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Socket Exception
		//
		// Ư�� ���Ͽ��� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class SocketException : public IOException {
		public :
			SocketException () throw () : IOException () {}
			SocketException ( std::string msg ) throw () : IOException (msg) {}
			std::string getName () const throw () { return "SocketException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Bind Exception
			//
			// bind()�� �߻��ϴ� ����
			//
			//////////////////////////////////////////////////////////////////////
			class BindException : public SocketException {
			public :
				BindException () throw () : SocketException () {}
				BindException ( std::string msg ) throw () : SocketException (msg) {}
				std::string getName () const throw () { return "BindException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Connect Exception
			//
			// ���� ������ ���� ��� ( ���� ���� �߻��Ѵٰ� ���� �ȴ�. )
			//
			//////////////////////////////////////////////////////////////////////
			class ConnectException : public SocketException {
			public :
				ConnectException () throw () : SocketException () {}
				ConnectException ( std::string msg ) throw () : SocketException (msg) {}
				std::string getName () const throw () { return "ConnectException"; }
			};
			
		//////////////////////////////////////////////////////////////////////
		//
		// Protocol Exception
		//
		// ��Ŷ �Ľ��Ҷ� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class ProtocolException : public IOException {
		public :
			ProtocolException () throw () : IOException () {}
			ProtocolException ( std::string msg ) throw () : IOException (msg) {}
			std::string getName () const throw () { return "ProtocolException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Idle Exception
			//
			// ���� �ð����� peer �κ��� �Է��� ���� ���
			//
			//////////////////////////////////////////////////////////////////////
			class IdleException : public ProtocolException {
			public :
				IdleException () throw () : ProtocolException () {}
				IdleException ( std::string msg ) throw () : ProtocolException (msg) {}
				std::string getName () const throw () { return "IdleException"; }
			};
	

			//////////////////////////////////////////////////////////////////////
			//
			// Invalid Protocol Exception
			//
			// �߸��� ��������
			//
			//////////////////////////////////////////////////////////////////////
			class InvalidProtocolException : public ProtocolException {
			public :
				InvalidProtocolException () throw () : ProtocolException () {}
				InvalidProtocolException ( std::string msg ) throw () : ProtocolException (msg) {}
				std::string getName () const throw () { return "InvalidProtocolException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Insufficient Data Exception
			//
			// ���� ��Ŷ ����Ÿ�� �����ϰ� �������� �ʾ��� ���
			//
			//////////////////////////////////////////////////////////////////////
			class InsufficientDataException : public ProtocolException {
			public :
				InsufficientDataException ( uint size = 0 ) throw () : ProtocolException () , m_Size(size) {}
				InsufficientDataException ( std::string msg , uint size = 0 ) throw () : ProtocolException (msg) , m_Size(size) {}
				std::string getName () const throw () { return "InsufficientDataException"; }
				uint getSize () const throw () { return m_Size; }
				std::string toString () const throw ()
				{
					StringStream buf;
					buf << getName() << " : " << getMessage();
					if ( m_Size > 0 ) {
						buf << " ( lack of " << m_Size << " bytes )\n";
					}
					buf << getStackTrace ();
			
					return buf.toString();
				}
	
			private :
				uint m_Size;
			};

			//////////////////////////////////////////////////////////////////////
			// 
			// �������� ����, �ý��� ���� ���������ؼ� ������ ©��� �� ���
			// �� ���ܸ� ����Ѵ�.
			// 
			//////////////////////////////////////////////////////////////////////
			class DisconnectException : public ProtocolException {
			public :
				DisconnectException () throw () : ProtocolException () {}
				DisconnectException ( std::string msg ) throw () : ProtocolException (msg) {}
				std::string getName () const throw () { return "DisconnectException"; }
			};

			//////////////////////////////////////////////////////////////////////
			// 
			// Ư�� ��Ȳ�� �����ؾ� �Ǵ� ��Ŷ�� ������ ���
			// 
			//////////////////////////////////////////////////////////////////////
			class IgnorePacketException : public ProtocolException {
			public :
				IgnorePacketException () throw () : ProtocolException () {}
				IgnorePacketException ( std::string msg ) throw () : ProtocolException (msg) {}
				std::string getName () const throw () { return "IgnorePacketException"; }
			};


	//////////////////////////////////////////////////////////////////////
	//
	// Thread Exception
	//
	// ������ �� ����ȭ �����鿡�� �߻��ϴ� ���ܵ�
	//
	//////////////////////////////////////////////////////////////////////
	class ThreadException : public Exception {
	public :
		ThreadException () throw () : Exception () {}
		ThreadException ( std::string msg ) throw () : Exception (msg) {}
		std::string getName () const throw () { return "ThreadException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Mutex Exception
		//
		// ���ؽ����� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class MutexException : public ThreadException {
		public :
			MutexException () throw () : ThreadException () {}
			MutexException ( std::string msg ) throw () : ThreadException (msg) {}
			std::string getName () const throw () { return "MutexException"; }
		};

			//////////////////////////////////////////////////////////////////////
			//
			// Mutex Attribute Exception
			//
			// ���ؽ� �Ӽ����� �߻��ϴ� ���ܵ�
			//
			//////////////////////////////////////////////////////////////////////
			class MutexAttrException : public MutexException {
			public :
				MutexAttrException () throw () : MutexException () {}
				MutexAttrException ( std::string msg ) throw () : MutexException (msg) {}
				std::string getName () const throw () { return "MutexAttrException"; }
			};


		//////////////////////////////////////////////////////////////////////
		//
		// Conditional Variable Exception
		//
		// Conditional Variable ���� �߻��ϴ� ���� (�̸��� �ʹ� ���.. - -)
		//
		//////////////////////////////////////////////////////////////////////
		class CondVarException : public ThreadException {
		public :
			CondVarException () throw () : ThreadException () {}
			CondVarException ( std::string msg ) throw () : ThreadException (msg) {}
			std::string getName () const throw () { return "CondVarException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Semaphore Exception
		//
		// Semaphore ���� �߻��ϴ� ����
		//
		//////////////////////////////////////////////////////////////////////
		class SemaphoreException : public ThreadException {
		public :
			SemaphoreException () throw () : ThreadException () {}
			SemaphoreException ( std::string msg ) throw () : ThreadException (msg) {}
			std::string getName () const throw () { return "SemaphoreException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// SQL Exception 
	//
	// SQL ���� ����
	//
	//////////////////////////////////////////////////////////////////////
	class SQLException : public Exception {
	public :
		SQLException () throw () : Exception() {}
		SQLException ( std::string msg ) throw () : Exception(msg) {}
		std::string getName () const throw () { return "SQLException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// SQL Warning
		//
		// SQL ����� ��Ÿ���� ����~~
		//
		//////////////////////////////////////////////////////////////////////
		class SQLWarning : public SQLException {
		public :
			SQLWarning () throw () : SQLException() {}
			SQLWarning ( std::string msg ) throw () : SQLException(msg) {}
			std::string getName () const throw () { return "SQLWarning"; }
		};


		//////////////////////////////////////////////////////////////////////
		//
		// SQL Connect Exception
		//
		// SQL�� ���� ���� �õ��� ������ ���, ������ �������� ��� ��
		//
		//////////////////////////////////////////////////////////////////////
		class SQLConnectException : public SQLException {
		public :
			SQLConnectException () throw () : SQLException() {}
			SQLConnectException ( std::string msg ) throw () : SQLException(msg) {}
			std::string getName () const throw () { return "SQLConnectException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Query Exception
		//
		//////////////////////////////////////////////////////////////////////
		class SQLQueryException : public SQLException {
		public :
			SQLQueryException () throw () : SQLException() {}
			SQLQueryException ( std::string msg ) throw () : SQLException(msg) {}
			std::string getName () const throw () { return "SQLQueryException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// Runtime Exception
	//
	// ��Ÿ�ӿ� �߻������� generic �� �뵵�� ���� �� �ִ� ���ܵ�
	//
	//////////////////////////////////////////////////////////////////////
	class RuntimeException : public Exception {
	public :
		RuntimeException () throw () : Exception () {}
		RuntimeException ( std::string msg ) throw () : Exception (msg) {}
		std::string getName () const throw () { return "RuntimeException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Invalid Arguemnt Exception
		//
		// �Լ�, ����Լ��� �Ķ���Ͱ� �߸��� ��� 
		//
		//////////////////////////////////////////////////////////////////////
		class InvalidArgumentException : public RuntimeException {
		public :
			InvalidArgumentException () throw () : RuntimeException () {}
			InvalidArgumentException ( std::string msg ) throw () : RuntimeException (msg) {}
			std::string getName () const throw () { return "InvalidArgumentException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Out Of Bound Exception
		//
		// ���״��. Out Of Bound!
		//
		//////////////////////////////////////////////////////////////////////
		class OutOfBoundException : public RuntimeException {
		public :
			OutOfBoundException () throw () : RuntimeException () {}
			OutOfBoundException ( std::string msg ) throw () : RuntimeException (msg) {}
			std::string getName () const throw () { return "OutOfBoundException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted Exception
		//
		// System Call ���� ���ͷ�Ʈ ������ ���
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedException : public RuntimeException {
		public :
			InterruptedException () throw () : RuntimeException () {}
			InterruptedException ( std::string msg ) throw () : RuntimeException (msg) {}
			std::string getName () const throw () { return "InterruptedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// No Such Element Exception
		//
		// �÷��ǿ��� Ư�� Ű���� �˻������� �׷� ������Ʈ�� ���� ���
		//
		//////////////////////////////////////////////////////////////////////
		class NoSuchElementException : public RuntimeException {
		public :
			NoSuchElementException () throw () : RuntimeException () {}
			NoSuchElementException ( std::string msg ) throw () : RuntimeException (msg) {}
			std::string getName () const throw () { return "NoSuchElementException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Duplicated Exception
		//
		// �÷����� Ư�� Ű�� �ߺ��Ǿ��� �� 
		//
		//////////////////////////////////////////////////////////////////////
		class DuplicatedException : public RuntimeException {
		public :
			DuplicatedException () throw () : RuntimeException () {}
			DuplicatedException ( std::string msg ) throw () : RuntimeException (msg) {}
			std::string getName () const throw () { return "DuplicatedException"; }
		};

	//////////////////////////////////////////////////////////////////////
	//
	// Game Exception
	//
	// ���ӿ��� goto �뵵�� ����ϴ� ���ܵ�.. -_-;
	//
	//////////////////////////////////////////////////////////////////////
	class GameException : public Exception {
	public :
		GameException () throw () : Exception () {}
		GameException ( std::string msg ) throw () : Exception (msg) {}
		std::string getName () const throw () { return "GameException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Portal Exception
		//
		// PC �� ��Ż�� �������...�

		//
		//////////////////////////////////////////////////////////////////////
		class PortalException : public GameException {
		public :
			PortalException () throw () : GameException () {}
			PortalException ( std::string msg ) throw () : GameException (msg) {}
			std::string getName () const throw () { return "PortalException"; }
		};


//////////////////////////////////////////////////////////////////////
//
// Error
//
//////////////////////////////////////////////////////////////////////
class Error : public Throwable {
public :
	Error () throw () : Throwable() {}
	Error ( const std::string & msg ) throw () : Throwable(msg) {}
	std::string getName () const throw () { return "Error"; }
};	
	//////////////////////////////////////////////////////////////////////
	//
	// Game Error
	//
	//////////////////////////////////////////////////////////////////////
	class GameError : public Error {
	public :
		GameError () throw () : Error () {}
		GameError ( std::string msg ) throw () : Error(msg) {}
		std::string getName () const throw () { return "GameError"; }
	};


	//////////////////////////////////////////////////////////////////////
	//
	// Assertion Error
	//
	//////////////////////////////////////////////////////////////////////
	class AssertionError : public Error {
	public :
		AssertionError () throw () : Error () {}
		AssertionError ( std::string msg ) throw () : Error(msg) {}
		std::string getName () const throw () { return "AssertionError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unsupported Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnsupportedError : public Error {
	public :
		UnsupportedError () throw () : Error () {}
		UnsupportedError ( std::string msg ) throw () : Error(msg) {}
		std::string getName () const throw () { return "UnsupportedError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Log Error
	//
	// �Ϲ����� �����ʹ� �޸� LogError�� ����Ʈ �α����Ͽ� �α׵� �� ����.
	// (�����غ���. �α׸Ŵ��� ��ü�� ������ ��� �α��Ѵٴ� ���ΰ�?)
	//
	//////////////////////////////////////////////////////////////////////
	class LogError : public Error {
	public :
		LogError () throw () : Error () {}
		LogError ( std::string msg ) throw () : Error(msg) {}
		std::string getName () const throw () { return "LogError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unknown Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnknownError : public Error {
	public :
		UnknownError () throw () : Error() {}
		UnknownError ( const std::string & msg ) throw () : Error(msg) {}
		UnknownError ( const std::string & msg , uint ErrorCode ) throw () : Error(msg), m_ErrorCode(ErrorCode) {}
		std::string getName () const throw () { return "UnknownError"; }
		uint getErrorCode () const throw () { return m_ErrorCode; }
		std::string toString () const throw ()
		{
			StringStream buf;
			buf << getName() << " : " << getMessage() << " ( " << getErrorCode() << " ) \n"
				<< getStackTrace () ;
			
			return buf.toString();
		}
	private :
		uint m_ErrorCode;
	};

#endif
