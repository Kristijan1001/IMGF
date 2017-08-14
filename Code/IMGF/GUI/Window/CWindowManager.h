#ifndef CWindowManager_H
#define CWindowManager_H

#include "Object/CManager.h"

class CMainWindow;

class CWindowManager : public bxcf::CManager
{
public:
	CWindowManager(void);

	void					init(void);
	void					uninit(void);

	CMainWindow*			openWindow(void);

	void					processWindows(void);

	CMainWindow*			getMainWindow(void) { return m_pMainWindow; }

private:
	CMainWindow*			m_pMainWindow;
};

#endif