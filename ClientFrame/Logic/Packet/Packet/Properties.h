//////////////////////////////////////////////////////////////////////
//
// Filename    : Properties.h
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

#pragma warning(disable:4786)

// include files
#include "Types.h"
#include "Exception.h"
#include <map>

// help class
class StringCompare {
public :
	bool operator () ( const std::string & left , const std::string & right ) const
	{
		return left.compare(right) < 0;
	}
};

//////////////////////////////////////////////////////////////////////
//
// class Properties;
//
// ���Ϸκ��� (key,value) pair �� �о map �� ���·� ������ �ִ´�.
// �ַ� ȯ���̳� �ɼǵ��� ���� ���Ͽ� ����Ѵ�. ��ü�� �����ؼ� ����
// �ɼ��� �����ϰ� �����ϸ� �� ������ ���������. 
//
// *Usage*
//
// Properties prop;
// prop.load("gameserver.conf");
// cout << prop.getProperty("MODE") << endl;
// cout << prop.getProperty("NumOfPlayerThreads") << endl;
// prop.setProperty("MODE","MODE_IV");
// prop.save();
//
// Properties prop2("loginserver.conf");
// prop2.load();
// prop2.save("loginserver.new");
//
//////////////////////////////////////////////////////////////////////

class Properties {
	
public :
	
	static const char Comment;
	static const char Separator;
	static const char * WhiteSpaces;
	
public :
	
	// constructor
	Properties () throw ();
	Properties ( const std::string & filename ) throw ();
	
	// destructor
	~Properties () throw ();
	

public :
	
	// load from file
	void load () throw ( IOException , Error );
	void load ( const std::string & filename ) throw ( IOException , Error ) { m_Filename = filename; load(); }

	// save to file
	void save () throw ( IOException );
	void save ( const std::string & filename ) throw ( IOException ) { m_Filename = filename; save(); }

	// get/set property
	std::string getProperty ( std::string key ) const throw ( NoSuchElementException );
	int getPropertyInt ( std::string key ) const throw ( NoSuchElementException );
	std::string getProperty ( const char* key ) const throw ( NoSuchElementException );
	int getPropertyInt ( const char* key ) const throw ( NoSuchElementException );
	void setProperty ( std::string key , std::string value ) throw ();

	// get debug string
	std::string toString () const throw ();
	
private :
	
	// key �� string �̰�, value ���� string �� map �̴�.
	std::map< std::string , std::string , StringCompare > m_Properties;

	// load/save target file's name
	std::string m_Filename;
	
};

//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
extern Properties * g_pConfigKorean;
extern Properties * g_pFileDef;

#endif
