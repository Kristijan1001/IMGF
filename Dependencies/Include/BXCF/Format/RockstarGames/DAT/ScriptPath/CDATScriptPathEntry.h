#ifndef CDATScriptPathEntry_H
#define CDATScriptPathEntry_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Type/Vector/Vec3f.h"

class bxcf::CDATScriptPathEntry
{
public:
	CDATScriptPathEntry(void);
	
	void					unload(void) {}

	void					setPosition(bxcf::Vec3f& vecPosition) { m_vecPosition = vecPosition; }
	bxcf::Vec3f&				getPosition(void) { return m_vecPosition; }
	
	void					unserialize(void); // todo
	void					serialize(void); // todo
	
private:
	bxcf::Vec3f				m_vecPosition;
};

#endif