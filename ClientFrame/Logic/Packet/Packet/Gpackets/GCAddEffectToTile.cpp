//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddEffectToTile.cpp 
// Written By  : crazydog
// Description : 
//               
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCAddEffectToTile.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAddEffectToTile::GCAddEffectToTile () 
     throw ()
{
	__BEGIN_TRY
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAddEffectToTile::~GCAddEffectToTile () 
    throw ()
{
	__BEGIN_TRY
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAddEffectToTile::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	iStream.read( m_ObjectID);
	iStream.read( m_X);
	iStream.read( m_Y);
	iStream.read( m_EffectID);
	iStream.read( m_Duration);
	//by viva
//	m_EffectID = 476;
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAddEffectToTile::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	// ����ȭ �۾��� ���� ũ�⸦ ����ϵ��� �Ѵ�.
	oStream.write( m_ObjectID);
	oStream.write( m_X);
	oStream.write( m_Y);
	oStream.write( m_EffectID);
	oStream.write( m_Duration);
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// execute packet's handler
//
//////////////////////////////////////////////////////////////////////
void GCAddEffectToTile::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddEffectToTileHandler::execute( this , pPlayer );
		
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get packet's debug std::string
//
//////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
	std::string GCAddEffectToTile::toString () 
		const throw ()
	{
		__BEGIN_TRY

		StringStream msg;

		msg << "GCAddEffectToTile( "
			<< ",ObjectID: " << (int)m_ObjectID
			<< ",X, Y: " << (int)m_X<<","<<(int)m_Y
			<< ",EffectID: " << (int)m_EffectID
			<< ",Duration: " << (int)m_Duration;


		msg << ")";

		return msg.toString();

		__END_CATCH
	}
#endif