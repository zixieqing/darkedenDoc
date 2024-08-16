//--------------------------------------------------------------------------------
//
// Filename    : Properties.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "Client_PCH.h"
#include <wtypes.h>
#include "Properties.h"
#include <stdlib.h>			// atoi()
#include "fstream"
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
const char Properties::Comment = '#';
const char Properties::Separator = ':';
const char * Properties::WhiteSpaces = " \t";


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
Properties::Properties () 
	throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

Properties::Properties ( const std::string & filename ) 
	throw ()
: m_Filename(filename)
{
	__BEGIN_TRY
	__END_CATCH
}
	

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
Properties::~Properties () 
	throw ()
{	
	__BEGIN_TRY
		
	// ��� pair �� �����Ѵ�.
	m_Properties.clear();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// load from file
//--------------------------------------------------------------------------------
void Properties::load () 
	throw ( IOException , Error )
{
	__BEGIN_TRY
		
	if ( m_Filename.empty() )
		throw Error("filename not specified");
		
	std::ifstream ifile( m_Filename.c_str() , ios::in );
	
	if ( ! ifile )
		throw FileNotExistException( m_Filename.c_str() );

	while ( true ) {

		std::string line;
		std::getline( ifile , line );
		
		if ( ifile.eof() )
			break;

		// �ڸ�Ʈ �����̰ų� �� �����̹Ƿ� skip �Ѵ�.
		if ( line[0] == Comment || line.size() == 0 )	
			continue;

		// key �� ���۹���(white space�� �ƴ� ����)�� ã�´�. 
		uint key_begin = line.find_first_not_of( WhiteSpaces );
		
		// key_begin�� npos ��� ���� �׷� ���ڸ� ã�� ���ߴٴ� ���̴�.
		// ��, ���� white space �θ� �Ǿ� �ִ� �����̹Ƿ� skip �Ѵ�.
		if ( key_begin == std::string::npos )
			continue;

		// key �� value �� �������� separator �� ã�´�.
		// key_end ���� sep �� ���� ã�� ������ find_last_not_of()�� �Ἥ
		// sep �������� ������ key_end �� ã�� ���ؼ��̴�. ^^;
		uint sep = line.find( Separator , key_begin );

		// Separator �� �߰����� ������ ���� �Ľ� ������ �����Ѵ�.
		if ( sep == std::string::npos )
			throw IOException("missing separator");
		
		// sep �������� ������ key_end �� ã�Ƴ�����.
		uint key_end = line.find_last_not_of( WhiteSpaces , sep - 1 );
		
		// sep �������� value_begin �� ã�´�.
		uint value_begin = line.find_first_not_of( WhiteSpaces , sep + 1 );
		
		// key �� ������ value �� ���� �����̴�. 
		if ( value_begin == std::string::npos )
			throw IOException("missing value");
		
		// �� ���������� ������ value_end �� ã�´�. 
		// ( value_begin �� ������ value_end �� ������ �����Ѵ�.)
		uint value_end = line.find_last_not_of( WhiteSpaces ); 

		// key_begin,key_end �� value_begin,value_end �� ����ؼ� 
		// line �� substring �� key �� value �� �����Ѵ�.
		std::string key = line.substr( key_begin , key_end - key_begin + 1 );
		std::string value = line.substr( value_begin , value_end - value_begin + 1 );

		// property �� ����Ѵ�.
		setProperty( key , value );
	}
	
	ifile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// save to file
//--------------------------------------------------------------------------------
void Properties::save () 
	throw ( IOException )
{
	__BEGIN_TRY
		
	if ( m_Filename.empty() )
		throw Error("filename not specified");

	std::ofstream ofile( m_Filename.c_str() , ios::out | ios::trunc );
	
	for ( std::map< std::string , std::string , StringCompare >::iterator itr = m_Properties.begin() ;
		  itr != m_Properties.end() ;
		  itr ++ )
		ofile << itr->first.c_str() << ' ' << Separator << ' ' << itr->second.c_str() << endl;
	
	ofile.close();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get property
//--------------------------------------------------------------------------------
std::string Properties::getProperty ( std::string key ) const 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY

		return getProperty(key.c_str());

	__END_CATCH
}

//--------------------------------------------------------------------------------
// get property
//--------------------------------------------------------------------------------
std::string Properties::getProperty ( const char* key ) const 
throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
		std::string value;
	
	std::map< std::string , std::string , StringCompare >::const_iterator itr = m_Properties.find( key );
	
	if ( itr != m_Properties.end() )
		value = itr->second;
	else
		throw NoSuchElementException(key);
	
	return value;
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get property as int
//--------------------------------------------------------------------------------
int Properties::getPropertyInt ( std::string key ) const 
	throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
	return atoi( getProperty(key).c_str() );
	
	__END_CATCH
}

//--------------------------------------------------------------------------------
// get property as int
//--------------------------------------------------------------------------------
int Properties::getPropertyInt ( const char* key ) const 
throw ( NoSuchElementException )
{
	__BEGIN_TRY
		
		return atoi( getProperty(key).c_str() );
	
	__END_CATCH
}


//--------------------------------------------------------------------------------
// set property
//--------------------------------------------------------------------------------
void Properties::setProperty ( std::string key , std::string value )
	throw ()
{
	__BEGIN_TRY
		
	// �̹� Ű�� ������ ���, value �� �����.
	m_Properties[ key ] = value;

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
std::string Properties::toString () const
    throw ()
{
	__BEGIN_TRY
		
	StringStream msg;

	for ( std::map< std::string , std::string , StringCompare >::const_iterator itr = m_Properties.begin() ;
		  itr != m_Properties.end() ;
		  itr ++ ) {
		
		msg << itr->first << " : " << itr->second << "\n";
	}
	
	if ( msg.isEmpty() )
		msg << "empty properties";
	
	return msg.toString();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// global variable definition
//--------------------------------------------------------------------------------
Properties * g_pConfigKorean = NULL;
Properties * g_pFileDef = NULL;
