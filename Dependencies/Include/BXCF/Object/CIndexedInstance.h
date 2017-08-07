#ifndef CIndexedInstance_H
#define CIndexedInstance_H

#include "bxcf.h"
#include <vector>

template<class Class>
class bxcf::CIndexedInstance
{
public:
	static Class*						get(uint32 uiInstanceIndex = 0);
	static std::vector<Class*>&			gets(void) { return m_vecInstances; }

private:
	static std::vector<Class*>			m_vecInstances;
};

template <class Class>
std::vector<Class*>						bxcf::CIndexedInstance<Class>::m_vecInstances;

template <class Class>
Class*									bxcf::CIndexedInstance<Class>::get(uint32 uiInstanceIndex)
{
	if (uiInstanceIndex >= m_vecInstances.size())
	{
		m_vecInstances.resize(uiInstanceIndex + 1);
		m_vecInstances[uiInstanceIndex] = new Class;
	}
	return m_vecInstances[uiInstanceIndex];
}

#endif