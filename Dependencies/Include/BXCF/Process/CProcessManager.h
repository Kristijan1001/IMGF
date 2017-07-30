#ifndef CProcessManager_H
#define CProcessManager_H

#include "bxcf.h"
#include <string>
#include <Windows.h>

class bxcf::CProcessManager
{
public:
	static bool							startProcess(std::string& strExecutableParh);
	static void							injectLibrary(HANDLE hProcess, std::string& strLibraryParh);
	static bool							isProcessActive(std::string strExecutableName);
	
	// threads
	static HANDLE						getPrimaryThread(void);
	static HANDLE						getCurrentThreadNonPseudo(void);
	static bool							toggleThreadSuspended(HANDLE hThread, bool bSuspended);
};

#endif