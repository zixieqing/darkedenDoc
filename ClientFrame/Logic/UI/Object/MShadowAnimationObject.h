//----------------------------------------------------------------------
// MShadowAnimationObject.h
//----------------------------------------------------------------------
// ImageObject�� ���ٰ� ���� �Ǵµ�..
// ��µǴ� image�� Shadow��..
//----------------------------------------------------------------------

#ifndef	__MSHADOWANIMATIONOBJECT_H__
#define	__MSHADOWANIMATIONOBJECT_H__

class ofstream;
class ifstream;
#include "MTypeDef.h"
#include "DrawTypeDef.h"
#include "MAnimationObject.h"

//----------------------------------------------------------------------
//
// MShadowAnimationObject class
//
//----------------------------------------------------------------------
class MShadowAnimationObject : public MAnimationObject {
	public :
		MShadowAnimationObject();
		MShadowAnimationObject(TYPE_OBJECTID id, TYPE_OBJECTID shadowObjectID, TYPE_SPRITEID nSprite, int pX, int pY, TYPE_SECTORPOSITION viewpoint, bool trans);
		~MShadowAnimationObject();
};


#endif


