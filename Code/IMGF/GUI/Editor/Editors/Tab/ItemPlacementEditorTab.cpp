#include "ItemPlacementEditorTab.h"
#include "Format/IPL/IPLFormat.h"
#include "Window/Window.h"
#include "IMGF.h"
#include "Task/Tasks/RecentlyOpen/RecentlyOpenManager.h"
#include "Static/File.h"
#include "Control/Controls/TextBox.h"

using namespace bxcf;
using namespace imgf;

ItemPlacementEditorTab::ItemPlacementEditorTab(void) :
	m_pIPLFile(nullptr),
	m_pTextBox(nullptr)
{
}

// controls
void						ItemPlacementEditorTab::addControls(void)
{
	m_pTextBox = addTextBox(139 + 139, 192, 600, 512, "", true, "textBasedEditorTextBox");
}

// events
void						ItemPlacementEditorTab::bindEvents(void)
{
	EditorTab::bindEvents();
}

void						ItemPlacementEditorTab::unbindEvents(void)
{
	EditorTab::unbindEvents();
}

// file loading
bool						ItemPlacementEditorTab::unserializeFile(void)
{
	return m_pIPLFile->unserialize();
}

void						ItemPlacementEditorTab::onFileLoaded(void)
{
	// update tab text
	updateTabText();

	// add file path to recently opened files list
	getIMGF()->getRecentlyOpenManager()->addRecentlyOpenEntry(getFile()->getFilePath());

	// display file info
	setFileInfoText();

	// show file content
	m_pTextBox->setText(File::getFileContent(getFile()->getFilePath()));

	// render
	m_pWindow->render();
}

// file info
void						ItemPlacementEditorTab::setFileInfoText(void)
{
}