#include "LSTFormat.h"
#include "Format/LST/LSTEntry.h"
#include "Static/String.h"
#include "Static/StdVector.h"
#include "Stream/DataReader.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void						LSTFormat::unload(void)
{
	removeAllEntries();
}

// serialization
void						LSTFormat::_unserialize(void)
{
	DataReader *pDataReader = DataReader::get();
	pDataReader->readAndStoreLines();
	while (pDataReader->iterateLines() && pDataReader->getUserData() == 0) // LST format user data for data reader: 0 = normal processing, 1 = stop processing (e.g. found END in file)
	{
		unserializeLine();
	}
}

void						LSTFormat::_serialize(void)
{
	// todo - serialize LST format
}

void						LSTFormat::unserializeLine(void)
{
	// initialize
	static LSTSection *pLSTActiveSection = nullptr;
	DataReader *pDataReader = DataReader::get();
	string strActiveLine = *pDataReader->getActiveLine();

	// remove comment from end of line ( comment characters: # ; )
	string strComment = "";
	size_t uiCommentPosition = strActiveLine.find('#');
	if (uiCommentPosition != string::npos)
	{
		strComment = strActiveLine.substr(uiCommentPosition + 1);
		strActiveLine = strActiveLine.substr(0, uiCommentPosition);
	}
	uiCommentPosition = strActiveLine.find(';');
	if (uiCommentPosition != string::npos)
	{
		strComment = strActiveLine.substr(uiCommentPosition + 1);
		strActiveLine = strActiveLine.substr(0, uiCommentPosition);
	}

	// trim line
	strActiveLine = String::trim(strActiveLine);
	
	// process line
	if (strActiveLine == "")
	{
		// blank line
	}
	else
	{
		if (strActiveLine.c_str()[0] == '[')
		{
			// line is a section
			LSTSection *pLSTFileSection = new LSTSection;
			pLSTFileSection->setName(String::trim(strActiveLine.substr(1, strActiveLine.length() - 2)));
			pLSTActiveSection = pLSTFileSection;
			addEntry(pLSTFileSection);

			if (String::toUpperCase(pLSTFileSection->getName()) == "END")
			{
				pDataReader->setUserData(1); // stop processing LST format
			}
		}
		else
		{
			// line is an entry
			deque<string> deqTokens = StdVector::convertVectorToDeque(String::split(strActiveLine, " "));

			LSTEntry *pLSTEntry = new LSTEntry;
			pLSTEntry->setName(deqTokens[0]);
			deqTokens.pop_front();
			pLSTEntry->setValues(deqTokens);
			pLSTActiveSection->addEntry(pLSTEntry);
		}
	}
}

// fetch entry
LSTSection*				LSTFormat::getEntryByName(string strName)
{
	strName = String::toUpperCase(strName);
	for (auto pSection : getEntries())
	{
		if (String::toUpperCase(pSection->getName()) == strName)
		{
			return pSection;
		}
	}
	return nullptr;
}

// check entry existence
bool						LSTFormat::doesEntryExistByName(string strName)
{
	return getEntryByName(strName) != nullptr;
}