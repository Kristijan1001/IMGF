#ifndef CRageResourceType_H
#define CRageResourceType_H

#include "bxcf.h"
#include "Type/Types.h"
#include "eRageResourceType.h"
#include <string>

class bxcf::CRageResourceType
{
public:
	void						unload(void) {}

	std::string					getResourceName(void);
	bxcf::eRageResourceType			getResourceId(void);

	void						setResourceTypeId(bxcf::eRageResourceType eResourceTypeId) { m_eResourceTypeId = eResourceTypeId; }
	bxcf::eRageResourceType			getResourceTypeId(void) { return m_eResourceTypeId; }

	void						setIdentifier(uint32 uiIdentifier) { m_uiIdentifier = uiIdentifier; }
	uint32						getIdentifier(void) { return m_uiIdentifier; }

	void						setName(std::string strName) { m_strName = strName; }
	std::string					getName(void) { return m_strName; }

	void						setFileExtension(std::string strFileExtension) { m_strFileExtension = strFileExtension; }
	std::string					getFileExtension(void) { return m_strFileExtension; }

private:
	bxcf::eRageResourceType			m_eResourceTypeId;
	uint32						m_uiIdentifier;
	std::string					m_strName;
	std::string					m_strFileExtension;
};

#endif