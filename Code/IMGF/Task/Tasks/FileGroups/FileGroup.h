#pragma once

#include "nsimgf.h"
#include <string>
#include <vector>

class imgf::FileGroup
{
public:
	void							unload(void) {}

	std::string						serialize(void);
	void							serializeToFile(void);
	
	void							setName(std::string strSessionName);
	std::string						getName(void) { return m_strName; }
	
	void							setPaths(std::vector<std::string> vecPaths);
	std::vector<std::string>		getPaths(void) { return m_vecPaths; }
	
public:
	std::string						m_strName;
	std::vector<std::string>		m_vecPaths;
};