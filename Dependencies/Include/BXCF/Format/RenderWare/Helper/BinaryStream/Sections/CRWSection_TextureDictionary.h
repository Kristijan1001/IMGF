#ifndef CRWSection_TextureDictionary_H
#define CRWSection_TextureDictionary_H

#include "bxcf.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWSection.h"

class bxcf::CRWSection_TextureDictionary : public bxcf::CRWSection
{
public:
	CRWSection_TextureDictionary(void);

	void							unserialize(void);
	void							serialize(void);

	void							setDeviceId(uint16 usDeviceId) { m_usDeviceId = usDeviceId; }
	uint16							getDeviceId(void) { return m_usDeviceId; }

private:
	uint16							m_usDeviceId;
};

#endif