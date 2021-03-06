#pragma once

#include "nsimgf.h"
#include "Type/Types.h"
#include <string>
#include <deque>

class imgf::LSTEntry
{
public:
	void								unload(void) {}

	std::string							getValue(uint32 uiValueIndex);
	std::string							getLine(void);
	std::string							getValuesLine(void);

	void								setName(std::string& strName) { m_strName = strName; }
	std::string&						getName(void) { return m_strName; }

	void								setValues(std::deque<std::string>& deqValues) { m_deqValues = deqValues; }
	std::deque<std::string>&			getValues(void) { return m_deqValues; }

private:
	std::string							m_strName;
	std::deque<std::string>				m_deqValues;
};