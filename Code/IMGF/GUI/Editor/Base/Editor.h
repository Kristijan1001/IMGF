#pragma once

#include "nsimgf.h"
#include "Layer/Layer.h"
#include "Pool/VectorPool.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include <string>

class bxgx::TabBar;
class bxgx::TextBox;

class imgf::Editor : public bxgx::Layer
{
public:
	Editor(void);

	virtual void						init(void) = 0;

	virtual void						addControls(void);
	virtual void						initControls(void);

	void								addFile(EditorTab *pEditorTab);
	void								removeFile(EditorTab *pEditorTab);
	void								removeActiveFile(void);

	bxcf::VectorPool<EditorTab*>&		getTabs(void) { return m_vecTabs; }

	void								setActiveFile(EditorTab *pEditorFile);
	EditorTab*							getActiveFile(void) { return m_pActiveFile; }

	void								setTabBar(bxgx::TabBar *pTabBar) { m_pTabBar = pTabBar; }
	bxgx::TabBar*						getTabBar(void) { return m_pTabBar; }

	void								setLog(bxgx::TextBox *pLog) { m_pLog = pLog; }
	bxgx::TextBox*						getLog(void) { return m_pLog; }

	void								updateActiveFileDisplayedInfo(void);
	void								clearActiveFileDisplayedInfo(void);

	virtual void						setFileInfoText(EditorTab *pEditorFile) = 0;
	virtual void						clearFileInfoText(void) = 0;

	virtual std::string					getResolvedFilePath(std::string& strFilePath) { return strFilePath; } // file name or file path

protected:
	bxgx::TabBar*						m_pTabBar;
	EditorTab*							m_pActiveFile;
	bxgx::TextBox*						m_pLog;
	bxcf::VectorPool<EditorTab*>		m_vecTabs;
};