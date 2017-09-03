#include "Session.h"
#include "Static/String.h"
#include "Globals.h"
#include "IMGF.h"
#include "SessionManager.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Format/Text/INI/INIManager.h"
#include "Static/AppDataPath.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

// serialize
string			Session::serialize(void)
{
	return m_strName + "; " + String::join(m_vecPaths, "; ");
}

// serialize to file
void			Session::serializeToFile(void)
{
	uint32 uiSessionIndex = getIMGF()->getSessionManager()->getIndexByEntry(this);
	INIManager::setItem(AppDataPath::getSessionsPath(), "Sessions", uiSessionIndex, serialize());
}

// name
void			Session::setName(string strSessionName)
{
	m_strName = strSessionName;
	serializeToFile();
}

// paths
void			Session::setPaths(vector<string> vecPaths)
{
	m_vecPaths = vecPaths;
	serializeToFile();
}