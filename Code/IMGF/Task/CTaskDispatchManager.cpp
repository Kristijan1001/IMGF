#pragma warning(disable : 4005)

#include "CTaskDispatchManager.h"
#include "CTaskManager.h"
#include "CIMGF.h"
#include "Globals.h"
#include "GUI/Window/CWindowManager.h"
#include "GUI/Windows/CMainWindow.h"
#include "Input/CInputManager.h"
#include "Type/String/CString2.h"
#include "Type/StdVector/CStdVector.h"
#include "Path/CPathManager.h"
#include "File/CFileManager.h"
#include "Registry/CRegistryManager.h"
#include "Window/CWindow.h"
#include "GUI/Editors/CIMGEditor.h"
#include "GUI/Editors/Tab/CIMGEditorTab.h"
#include "Format/RockstarGames/IMG/CIMGManager.h"
#include "Format/RockstarGames/IMG/CIMGFormat.h"
#include "Format/RockstarGames/IMG/CIMGEntry.h"
#include "Format/RockstarGames/IDE/CIDEManager.h"
#include "Format/RockstarGames/IPL/CIPLManager.h"
#include "Format/RockstarGames/IDE/CIDEManager.h"
#include "Format/RockstarGames/COL/CCOLManager.h"
#include "Format/RockstarGames/COL/CCOLFormat.h"
#include "DragDrop/CDropTarget.h"
#include "Format/RockstarGames/TXD/CTXDManager.h"
#include "Format/RockstarGames/TXD/CTXDFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/Sections/CRWSection_TextureNative.h"
#include "Format/RockstarGames/DFF/CDFFManager.h"
#include "Format/RockstarGames/DFF/CDFFFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CTextureEntry.h"
#include "Format/RockstarGames/DAT/Loader/CDATLoaderManager.h"
#include "Format/RockstarGames/DAT/Path/CDATPathManager.h"
#include "Format/RockstarGames/DAT/Loader/CDATLoaderFormat.h"
#include "Format/RockstarGames/DAT/Loader/CDATLoaderEntry.h"
#include "Format/Image/BMP/CBMPManager.h"
#include "Format/Image/BMP/CBMPFormat.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersion.h"
#include "LST/CLSTManager.h"
#include "LST/CLSTFormat.h"
#include "LST/CLSTSection.h"
#include "LST/CLSTEntry.h"
#include "Format/RockstarGames/COL/CCOLEntry.h"
#include "Debug/CDebug.h"
#include "Format/RockstarGames/IPL/CIPLManager.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWManager.h"
#include "Tasks/RecentlyOpen/CRecentlyOpenManager.h"
#include "Tasks/Session/CSessionManager.h"
#include "GUI/Popups/CPopupGUIManager.h"
#include "Tasks/LST/CLSTProcessingManager.h"
#include "Tasks/Dump/CDumpManager.h"
#include "Settings/CSettingsManager.h"
#include "Tasks/Sort/CSortManager.h"
#include "Tasks/Sort/CSortPriority.h"
#include "Protocol/HTTP.h"
#include "DB/CDBManager.h"
#include "DB/CDBFormat.h"
#include "Image/CRasterDataFormat.h"
#include "Tasks/Find/CSearchEntry.h"
#include "Format/RenderWare/Helper/BinaryStream/CRWVersionManager.h"
#include "EntryViewer/CEntryViewerManager.h"
#include "Format/RockstarGames/IDE/CIDEFormat.h"
#include "Format/RockstarGames/IDE/CIDEEntry.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_OBJS.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_TOBJ.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_ANIM.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_CARS.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_HAND.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_HIER.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_PATH.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_PEDS.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_TXDP.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/CIDEEntry_WEAP.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/2DFX/CIDEEntry_2DFX_Light.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/2DFX/CIDEEntry_2DFX_Particle.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/2DFX/CIDEEntry_2DFX_Ped.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/2DFX/CIDEEntry_2DFX_SunReflection.h"
#include "Format/RockstarGames/IDE/Entry/DataEntry/2DFX/CIDEEntry_2DFX_Unknown1.h"
#include "Format/RockstarGames/IPL/CIPLFormat.h"
#include "Format/RockstarGames/IPL/CIPLEntry.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_INST.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_AUZO.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_CARS.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_CULL.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_ENEX.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_GRGE.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_JUMP.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_MULT.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_MZON.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_OCCL.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_PATH.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_PICK.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_TCYC.h"
#include "Format/RockstarGames/IPL/Entry/DataEntry/CIPLEntry_ZONE.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_CoverPoint.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_EnterExit.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_Escalator.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_Light.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_ParticleEffect.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_PedAttractor.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_SlotmachineWheel.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_StreetSign.h"
#include "Format/RenderWare/Helper/BinaryStream/Entries/2dEffects/CRWEntry_2dEffect_SunGlare.h"
#include "Updater/CUpdateManager.h"
#include "Updater/CUpdateConnectionManager.h"
#include "Updater/CUpdateConnection.h"
#include "Program/buildnumber.h"
#include "Format/RockstarGames/COL/CCOLVersionManager.h"
#include "Format/RockstarGames/COL/CCOLVersion.h"
#include "Math/CMath.h"
#include "Format/RenderWare/Helper/BinaryStream/Sections/CRWSection_Geometry.h"
#include "Format/RenderWare/Helper/BinaryStream/Sections/CRWSection_String.h"
#include "Format/RenderWare/Helper/BinaryStream/Sections/CRWSection_Texture.h"
#include "Format/RenderWare/Helper/BinaryStream/Sections/CRWSection_Material.h"
#include "Format/RenderWare/Helper/BinaryStream/Sections/CRWSection_2dEffect.h"
#include "Format/RockstarGames/WDR/CWDRManager.h"
#include "Format/RockstarGames/WDR/CWDRFormat.h"
#include "Format/RockstarGames/WTD/CWTDManager.h"
#include "Format/RockstarGames/WTD/CWTDFormat.h"
#include "Format/Intermediate/Texture/CIntermediateTextureFormat.h"
#include "Format/RockstarGames/DAT/Path/CDATPathFormat.h"
#include "Localization/CLocalizationManager.h"
#include "Tasks/Sort/CSortPriorities.h"
#include "EntryViewer/CTextureViewer.h"
#include "EntryViewer/CCollisionViewer.h"
#include "Tasks/Renamer/CRenamedIMGEntry.h"
#include "Format/RenderWare/Helper/BinaryStream/CTextureEntry.h"
#include "Collection/Games/eGame.h"
#include "CLastUsedValueManager.h"
#include "Task/ETask.h"
#include "Stream/CDataReader.h"
#include <gdiplus.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
using namespace bxcf;
using namespace imgf::task;

CTaskDispatchManager::CTaskDispatchManager(void) :
	m_pMainWindow(nullptr),
	m_pTaskManager(nullptr)
{
}

// main interface
void		CTaskDispatchManager::init(void)
{
	m_pMainWindow = g_pIMGF->getWindowManager()->getMainWindow();
	m_pTaskManager = g_pIMGF->getTaskManager();
}

void		CTaskDispatchManager::uninit(void)
{
}

// tasks
void		CTaskDispatchManager::chooseFilesToOpen(void)
{
	vector<string> vecFilePaths = CInputManager::openFile(OPEN, "IMG,DIR");
	if (vecFilePaths.size() == 0)
	{
		return;
	}

	for (auto &strFilePath : vecFilePaths)
	{
		openFile(strFilePath);
	}
}

void		CTaskDispatchManager::openFile(string& strFilePath)
{
	m_pTaskManager->onTaskBegin("openFile");

	string strExtensionUpper = CString2::toUpperCase(CPathManager::getFileExtension(strFilePath));
	/*
	todo - use this code
	CUnknownFormat unknownFormatFile;
	bool bUseExistingFileHandle = false;
	if (strExtensionUpper == "")
	{
		unknownFormatFile.open(strFilePath);
		uint32 uiFormatId = unknownFormatFile.getFormat();
		if (uiFormat == -1)
		{
			unknownFormatFile.close();
			CInputManager::showMessage("Unable to detect file format.\r\n\r\n" + strFilePath, "Unknown File Format");
			return m_pTaskManager->onTaskEndEarly();
		}

		bUseExistingFileHandle = true;
		if (uiFormatId == 0) // IMG format
		{
			strExtensionUpper = "DIR";
		}
	}
	*/

	if (strExtensionUpper == "DIR")
	{
		strExtensionUpper == "IMG";
		strFilePath = CPathManager::replaceFileExtension(strFilePath, "IMG");
	}

	if (strExtensionUpper == "IMG")
	{
		// IMG or DIR
		CDataReader reader;
		CIMGFormat *img = new CIMGFormat(reader, strFilePath);

		/*
		if (bUseExistingFileHandle)
		{
			img.setFileHandle(unknownFormatFile.getHandle());
		}
		else
		{
		*/
			if (!img->open())
			{
				CInputManager::showMessage("Unable to open IMG file:\r\n\r\n" + strFilePath, "Can't Open File");
				delete img;
				return m_pTaskManager->onTaskEndEarly();
			}
		//}

		if (img->getVersion() == IMG_UNKNOWN)
		{
			CInputManager::showMessage("Version of IMG format is not supported:\r\n\r\n" + strFilePath, "IMG Version Not Supported");
			delete img;
			return m_pTaskManager->onTaskEndEarly();
		}

		if (!CIMGEditor::validateFile(img))
		{
			delete img;
			return m_pTaskManager->onTaskEndEarly();
		}

		/*
		uint32
		uiProgressBarMaxMultiplier = img->getVersion() == IMG_3 ? 4 : 3, // x3 for: 1 for reading entry data (parsing), 1 for reading RW versions (parsing), and 1 for adding all entries to main list view. and x4 (+1) for version 3 entry names.
		uiProgressBarMax = img->getEntryCount() * uiProgressBarMaxMultiplier;
		m_pMainWindow->getProgressBar()->setMax(uiProgressBarMax);
		*/

		if (!img->unserialize2())
		{
			CInputManager::showMessage("Failed to read the IMG file:\r\n\r\n" + img->getFilePath(), "Unable To Read File");
			delete img;
			return m_pTaskManager->onTaskEndEarly();
		}

		m_pMainWindow->getIMGEditor()->addFile(img);

		img->close();
		m_pTaskManager->onTaskEnd();
	}
	else
	{
		if (strExtensionUpper == "")
		{
			CInputManager::showMessage("File doesn't have an extension.\r\n\r\n" + strFilePath, "Format Not Detected");
		}
		else
		{
			CInputManager::showMessage(strExtensionUpper + " files are not supported.\r\n\r\n" + strFilePath, "Format Not Supported");
		}
		m_pTaskManager->onTaskEndEarly();
	}
}
void		CTaskDispatchManager::onRequestClose(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestClose");
	CIMGEditorTab *pEditorTab = getIMGF()->getEntryListTab();
	if (!pEditorTab)
	{
		return;
	}

	if (getIMGF()->getSettingsManager()->getSettingBool("RebuildConfirmationOnClose"))
	{
		getIMGF()->getTaskManager()->onTaskPause();
		if (onRequestClose2(false) == true)
		{
			getIMGF()->getTaskManager()->onTaskUnpause();
			getIMGF()->getTaskManager()->onTaskEnd("onRequestClose", true);
			return;
		}
		getIMGF()->getTaskManager()->onTaskUnpause();
	}

	getIMGF()->getIMGEditor()->removeTab(pEditorTab);

	getIMGF()->getTaskManager()->onTaskEnd("onRequestClose");
}
void		CTaskDispatchManager::onRequestCloseAll(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestCloseAll");
	if (getIMGF()->getSettingsManager()->getSettingBool("RebuildConfirmationOnClose"))
	{
		getIMGF()->getTaskManager()->onTaskPause();
		if (onRequestClose2(true) == true)
		{
			getIMGF()->getTaskManager()->onTaskUnpause();
			getIMGF()->getTaskManager()->onTaskEnd("onRequestCloseAll", true);
			return;
		}
		getIMGF()->getTaskManager()->onTaskUnpause();
	}

	while (getIMGF()->getIMGEditor()->getTabs().getEntryCount() > 0) // todo - change to removeAllEntries or something assuming all stuff in removeTab() still gets ran somewhere
	{
		getIMGF()->getIMGEditor()->removeTab(getIMGF()->getIMGEditor()->getTabs().getEntryByIndex(0));
	}

	getIMGF()->getIMGEditor()->setActiveTab(nullptr);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestCloseAll");
}
void		CTaskDispatchManager::onRequestExitTool(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExitTool");
	DestroyWindow(getIMGF()->getActiveWindow()->getWindowHandle());
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExitTool");
}
void		CTaskDispatchManager::onRequestImportViaFiles(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestImportViaFiles");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaFiles", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("IMPORT_FILES"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaFiles", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("IMPORT_FILES", CPathManager::getDirectory(vecPaths[0]));

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecPaths.size());
	for (auto strPath : vecPaths)
	{
		getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strPath);
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_23", vecPaths.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("EntryNames"), true);
	vector<string> vecFileNames;
	for (auto strPath : vecPaths)
	{
		vecFileNames.push_back(strPath);
	}
	getIMGF()->getEntryListTab()->log(CString2::join(vecFileNames, "\n"), true);

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaFiles");
}
void		CTaskDispatchManager::onRequestRemoveSelected(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRemoveSelected");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		return;
	}

	CListCtrl *pListControl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	vector<string> vecEntryNames;
	uint32 uiRemoveCount = 0;
	CIMGEntry *pIMGEntry;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);

		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);
		vecEntryNames.push_back(pIMGEntry->getEntryName());
		getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);
		pListControl->DeleteItem(nItem);

		pos = pListControl->GetFirstSelectedItemPosition();

		uiRemoveCount++;
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	if (pListControl->GetItemCount() == 0)
	{
		getIMGF()->getEntryListTab()->readdAllEntriesToMainListView();
	}

	getIMGF()->getEntryListTab()->searchText();

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_53", uiRemoveCount));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("EntryNames"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNames, "\n"), true);

	if (uiRemoveCount > 0)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveSelected");
	*/
}
void		CTaskDispatchManager::onRequestRenameEntry(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRenameEntry");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenameEntry", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenameEntry", true);
		return;
	}

	int nItem;
	CIMGEntry *pIMGEntry = nullptr;
	nItem = pListControl->GetNextSelectedItem(pos);
	pIMGEntry = ((CIMGEntry*)pListControl->GetItemData(nItem));

	pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenameEntry", true);
		return;
	}

	bool bMultipleEntries = pListControl->GetSelectedCount() > 1;
	string strOldName = pIMGEntry->getEntryName();
	getIMGF()->getTaskManager()->onTaskPause();
	string strNewName = getIMGF()->getPopupGUIManager()->showTextInputDialog(CLocalizationManager::get()->getTranslatedText("Window_TextInput_1_Title"), CLocalizationManager::get()->getTranslatedFormattedText("Window_TextInput_1_Message", pListControl->GetSelectedCount()), pIMGEntry->getEntryName());
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strNewName == "")
	{
		return;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	while (pos)
	{
		nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = ((CIMGEntry*)pListControl->GetItemData(nItem));

		pIMGEntry->setEntryName(strNewName);
		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);

		getIMGF()->getEntryListTab()->onEntryChange(pIMGEntry);
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_54", strOldName.c_str(), strNewName.c_str()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_55", strNewName.c_str(), getIMGF()->getEntryListTab()->getIMGFile()->getEntryCountForName(strNewName)), true);

	getIMGF()->getEntryListTab()->searchText();

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRenameEntry");
	*/
}
void		CTaskDispatchManager::onRequestSelectAll(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSelectAll");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectAll", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetItemCount());
	bool bNewSelectedState = true;
	if (pListControl->GetItemState(0, LVIS_SELECTED) == LVIS_SELECTED)
	{
		bNewSelectedState = false;
	}
	for (uint32 i = 0, j = pListControl->GetItemCount(); i < j; i++)
	{
		if (bNewSelectedState)
		{
			pListControl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			pListControl->SetSelectionMark(i);
		}
		else
		{
			pListControl->SetItemState(i, ~LVIS_SELECTED, LVIS_SELECTED);
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	pListControl->SetFocus();
	if(bNewSelectedState)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_56", pListControl->GetItemCount()));
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_57", pListControl->GetItemCount()));
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectAll");
	*/
}
void		CTaskDispatchManager::onRequestSelectInverse(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSelectInverse");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectInverse", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetItemCount());
	uint32 uiSelectedEntryCount = 0;
	for (uint32 i = 0, j = pListControl->GetItemCount(); i < j; i++)
	{
		if (pListControl->GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			pListControl->SetItemState(i, ~LVIS_SELECTED, LVIS_SELECTED);
		}
		else
		{
			uiSelectedEntryCount++;
			pListControl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			pListControl->SetSelectionMark(i);
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	pListControl->SetFocus();
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_58", uiSelectedEntryCount, pListControl->GetItemCount()));
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectInverse");
	*/
}
void		CTaskDispatchManager::onRequestRebuild(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRebuild");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRebuild", true);
		return;
	}

	getIMGF()->getEntryListTab()->rebuild();
	getIMGF()->getIMGEditor()->refreshActiveTab();

	getIMGF()->getEntryListTab()->checkForUnknownRWVersionEntries();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRebuild");
}
void		CTaskDispatchManager::onRequestRebuildAs(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRebuildAs");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRebuildAs", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strIMGPath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("REBUILD_AS"), "IMG,DIR", "IMG.img");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strIMGPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRebuildAs", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("REBUILD_AS", strIMGPath);

	getIMGF()->getEntryListTab()->rebuild(strIMGPath, false);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_59", CPathManager::getFileName(strIMGPath).c_str()));
	getIMGF()->getIMGEditor()->refreshActiveTab();

	getIMGF()->getEntryListTab()->checkForUnknownRWVersionEntries();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRebuildAs");
}
void		CTaskDispatchManager::onRequestRebuildAll(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRebuildAll");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRebuildAll", true);
		return;
	}

	vector<string> vecIMGPaths;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		vecIMGPaths.push_back(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath());
		((CIMGEditorTab*)pEditorTab)->rebuild("", false);
	}
	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedFormattedText("LogAllTabs_1", getIMGF()->getIMGEditor()->getTabs().getEntryCount()));
	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedText("LogAllTabs_2"), true);
	getIMGF()->getIMGEditor()->logAllTabs(CString2::join(vecIMGPaths, "\n"), true);

	getIMGF()->getIMGEditor()->refreshActiveTab();

	getIMGF()->getEntryListTab()->checkForUnknownRWVersionEntries();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRebuildAll");
}
void		CTaskDispatchManager::onRequestConvertIMGVersion(eIMGVersion eIMGVersionValue)
{
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_Convert_IMGVersion(eIMGVersionValue);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertIMGVersion");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertIMGVersion", true);
		return;
	}

	// fetch data
	uint32 uiIMGEntryCount = getIMGF()->getEntryListTab()->getIMGFile()->getEntryCount();
	uint32 ePreviousIMGVersion = getIMGF()->getEntryListTab()->getIMGFile()->getVersion();
	bool bPreviouslyEncrypted = getIMGF()->getEntryListTab()->getIMGFile()->isEncrypted();

	// also convert entries to appropriate game version?
	bool bConvertEntries = false;
	if (ePreviousIMGVersion != IMG_FASTMAN92 && eIMGVersionValue != IMG_FASTMAN92)
	{
		bConvertEntries = getIMGF()->getPopupGUIManager()->showConfirmDialog("Also convert entries to appropriate game version?", "Convert Entries?");
	}

	// calculate progress bar tick count
	uint32 uiProgressMaxTicks = uiIMGEntryCount * 2;
	if (ePreviousIMGVersion == IMG_1)
	{
		uiProgressMaxTicks += 1;
	}
	if (getIMGF()->getSettingsManager()->getSettingBool("RebuildOnConvert"))
	{
		uiProgressMaxTicks += uiIMGEntryCount;
	}
	if (bConvertEntries)
	{
		uiProgressMaxTicks += uiIMGEntryCount;
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiProgressMaxTicks);

	/*
	// remove compression from entries body data in version Fastman92 IMG
	if (ePreviousIMGVersion == IMG_FASTMAN92)
	{
		for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
		{
			if (pIMGEntry->isCompressed())
			{
				string strEntryNewData;
				switch(pIMGEntry->getCompressionAlgorithmId())
				{
					case COMPRESSION_ZLIB:
						strEntryNewData = CIMGManager::decompressZLib(pIMGEntry->getEntryData(), pIMGEntry->getFUncompressedSize());
					break;
					case COMPRESSION_LZ4:
						strEntryNewData = CIMGManager::decompressLZ4(pIMGEntry->getEntryData(), pIMGEntry->getFUncompressedSize());
					break;
				}
				pIMGEntry->setEntryData(strEntryNewData);
				getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
			}
		}
	}
	
	// add compression to entries body data in version Fastman92 IMG
	if (eIMGVersionValue == IMG_FASTMAN92)
	{
		for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
		{
			if (pIMGEntry->isCompressed())
			{
				string strEntryNewData;
				switch(pIMGEntry->getCompressionAlgorithmId())
				{
					case COMPRESSION_ZLIB:
						strEntryNewData = CIMGManager::compressZLib(pIMGEntry->getEntryData());
					break;
					case COMPRESSION_LZ4:
						strEntryNewData = CIMGManager::compressLZ4(pIMGEntry->getEntryData());
					break;
				}
				pIMGEntry->setEntryData(strEntryNewData);
				getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
			}
		}
	}
	*/

	// re-apply compression type to entry data
	if (ePreviousIMGVersion == IMG_FASTMAN92 && eIMGVersionValue != IMG_FASTMAN92)
	{
		for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
		{
			pIMGEntry->applyCompression(COMPRESSION_NONE);
		}
	}

	// fetch RW versions or resource types
	if (eIMGVersionValue == IMG_1 || eIMGVersionValue == IMG_2)
	{
		getIMGF()->getEntryListTab()->getIMGFile()->unserializeRWVersions(); // todo - func name inconsitent with one below - RW / Rage
	}
	else
	{
		getIMGF()->getEntryListTab()->getIMGFile()->unserializeResourceTypes();
	}

	// set new IMG version
	getIMGF()->getEntryListTab()->getIMGFile()->setVersion(eIMGVersionValue);

	// remove dir file?
	if (ePreviousIMGVersion == IMG_1)
	{
		CFileManager::removeFile(CPathManager::replaceFileExtension(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath(), "dir"));
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// check to convert entries aswell as IMG
	if (bConvertEntries)
	{
		// choose destination version for DFF, TXD and COL files
		ePlatformedGame eDestGame = PLATFORMED_GAME_UNKNOWN;
		if (eIMGVersionValue == IMG_1)
		{
			eDestGame = PLATFORMED_GAME_PC_GTA_VC;
		}
		else if (eIMGVersionValue == IMG_2)
		{
			eDestGame = PLATFORMED_GAME_PC_GTA_SA;
		}
		CRWVersion *pDestRWVersion = eDestGame == PLATFORMED_GAME_UNKNOWN ? nullptr : CRWManager::get()->getVersionManager()->getRWVersionFromGame(eDestGame);

		eCOLVersion eDestCOLVersion = COL_UNKNOWN;
		if (eIMGVersionValue == IMG_1)
		{
			eDestCOLVersion = COL_2;
		}
		else if (eIMGVersionValue == IMG_2)
		{
			eDestCOLVersion = COL_3;
		}

		// convert entries to appropriate version
		for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
		{
			string strEntryExtensionUpper = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
			if (CPathManager::isModelExtension(strEntryExtensionUpper))
			{
				if (eDestGame == PLATFORMED_GAME_UNKNOWN)
				{
					getIMGF()->getTaskManager()->onTaskProgressTick();
					continue;
				}

				CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
				if (pDFFFile->doesHaveError())
				{
					pDFFFile->unload();
					delete pDFFFile;
					getIMGF()->getTaskManager()->onTaskProgressTick();
					continue;
				}

				pDFFFile->setRWVersion(pDestRWVersion);

				pIMGEntry->setEntryData(pDFFFile->storeViaMemory());
				getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
				
				pDFFFile->unload();
				delete pDFFFile;
			}
			else if (strEntryExtensionUpper == "TXD")
			{
				if (eDestGame == PLATFORMED_GAME_UNKNOWN)
				{
					getIMGF()->getTaskManager()->onTaskProgressTick();
					continue;
				}

				CTXDFormat *pTXDFile = CTXDManager::get()->parseViaMemory(pIMGEntry->getEntryData());
				if (pTXDFile->doesHaveError())
				{
					pTXDFile->unload();
					delete pTXDFile;
					getIMGF()->getTaskManager()->onTaskProgressTick();
					continue;
				}

				vector<string> vecMipmapsRemoved;
				pTXDFile->convertToGame(eDestGame, vecMipmapsRemoved);

				pIMGEntry->setEntryData(pTXDFile->serializeViaMemory());
				getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
				
				pTXDFile->unload();
				delete pTXDFile;
			}
			else if (strEntryExtensionUpper == "COL")
			{
				if (eDestCOLVersion == COL_UNKNOWN)
				{
					getIMGF()->getTaskManager()->onTaskProgressTick();
					continue;
				}

				CCOLFormat *pCOLFile = CCOLManager::get()->parseViaMemory(pIMGEntry->getEntryData());
				if (pCOLFile->doesHaveError())
				{
					pCOLFile->unload();
					delete pCOLFile;
					getIMGF()->getTaskManager()->onTaskProgressTick();
					continue;
				}

				for (auto pCOLEntry : pCOLFile->getEntries())
				{
					pCOLEntry->setCOLVersion(CCOLManager::get()->getVersionManager()->getEntryByVersionId(eDestCOLVersion));
				}

				pIMGEntry->setEntryData(pCOLFile->storeViaMemory());
				getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
				
				pCOLFile->unload();
				delete pCOLFile;
			}

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}

	// log
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_60", CIMGManager::getVersionNameWithGames((eIMGVersion)ePreviousIMGVersion, bPreviouslyEncrypted).c_str(), CIMGManager::getVersionNameWithGames(eIMGVersionValue, false).c_str()).c_str());

	// rebuild
	if (getIMGF()->getSettingsManager()->getSettingBool("RebuildOnConvert"))
	{
		getIMGF()->getEntryListTab()->rebuild();
	}

	// render
	getIMGF()->getIMGEditor()->refreshActiveTab();

	// other
	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);

	getIMGF()->getEntryListTab()->checkForUnknownRWVersionEntries();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertIMGVersion");
}
void		CTaskDispatchManager::onRequestConvertIMGVersionViaButton(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertIMGVersionViaButton");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertIMGVersionViaButton", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showConvertDialog("Convert IMG Version", CLocalizationManager::get()->getTranslatedText("Convert"));
	getIMGF()->getTaskManager()->onTaskUnpause(); 
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		return;
	}

	onRequestConvertIMGVersion((eIMGVersion)uiRadioButtonIndex);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertIMGVersionViaButton");
}
void		CTaskDispatchManager::onRequestMerge(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestMerge");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMerge", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MERGE"), "IMG");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMerge", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MERGE", CPathManager::getDirectory(vecPaths[0]));

	uint32 uiMergeEntryCount = 0;
	for (auto strPath : vecPaths)
	{
		uiMergeEntryCount += CIMGManager::getIMGEntryCount(strPath, CIMGManager::detectIMGVersion(strPath));
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiMergeEntryCount);

	uint32 uiImportedEntryCount = 0;
	vector<string> vecImportedEntryNames;
	string strExtendedLog = "";
	for (auto strPath : vecPaths)
	{
		uiImportedEntryCount += getIMGF()->getEntryListTab()->merge(strPath, vecImportedEntryNames);

		strExtendedLog += "[" + CPathManager::getFileName(strPath) + "]\n";
		strExtendedLog += CString2::join(vecImportedEntryNames, "\n");

		vecImportedEntryNames.clear();
	}

	if (vecPaths.size() == 1)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_61", CPathManager::getFileName(vecPaths[0]).c_str(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str(), uiImportedEntryCount));
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_62", vecPaths.size(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str(), uiImportedEntryCount));
	}
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_63"), true);
	getIMGF()->getEntryListTab()->log(strExtendedLog, true);

	getIMGF()->getIMGEditor()->refreshActiveTab();

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestMerge");
}
void		CTaskDispatchManager::onRequestSplitViaButton(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSplitViaButton");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaButton", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showSplitViaDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaButton", true);
		return;
	}

	switch (uiRadioButtonIndex)
	{
	case 0:
		onRequestSplitSelectedEntries();
		break;
	case 1:
		onRequestSplitViaIDEFile();
		break;
	case 2:
		onRequestSplitViaTextLines();
		break;
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaButton", true);
}
void		CTaskDispatchManager::onRequestSplitSelectedEntries(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSplitSelectedEntries");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitSelectedEntries", true);
		return;
	}

	if (getIMGF()->getIMGEditor()->getSelectedEntryCount() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitSelectedEntries", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("SPLIT_SELECTED"), "IMG,DIR", "IMG.img");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitSelectedEntries", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("SPLIT_SELECTED", strPath);

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showConvertDialog("New IMG Version", CLocalizationManager::get()->getTranslatedText("Save"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitSelectedEntries", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	bool bDeleteFromSource = getIMGF()->getPopupGUIManager()->showConfirmDialog(CLocalizationManager::get()->getTranslatedText("Window_Confirm_1_Message"), CLocalizationManager::get()->getTranslatedText("Window_Confirm_1_Title"));
	getIMGF()->getTaskManager()->onTaskUnpause();

	eIMGVersion eIMGVersionValue = IMG_UNKNOWN;
	bool bIsEncrypted = false;
	switch (uiRadioButtonIndex)
	{
	case 0:
		eIMGVersionValue = IMG_1;
		break;
	case 1:
		eIMGVersionValue = IMG_2;
		break;
	case 2:
		eIMGVersionValue = IMG_3;
		bIsEncrypted = true;
		break;
	case 3:
		eIMGVersionValue = IMG_3;
		bIsEncrypted = false;
		break;
	}

	vector<string> vecSplitEntryNames;
	getIMGF()->getEntryListTab()->splitSelectedEntries(strPath, eIMGVersionValue, bDeleteFromSource, vecSplitEntryNames);
	if(bDeleteFromSource)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_66", getIMGF()->getIMGEditor()->getSelectedEntryCount(), CPathManager::getFileName(strPath).c_str(), CIMGManager::getVersionNameWithGames(eIMGVersionValue, bIsEncrypted).c_str(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str()));
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_65", getIMGF()->getIMGEditor()->getSelectedEntryCount(), CPathManager::getFileName(strPath).c_str(), CIMGManager::getVersionNameWithGames(eIMGVersionValue, bIsEncrypted).c_str(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str()));
	}
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_67"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecSplitEntryNames, "\n"), true);

	if (bDeleteFromSource)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}

	openFile(strPath);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitSelectedEntries");
}
void		CTaskDispatchManager::onRequestSplitViaIDEFile(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSplitViaIDEFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaIDEFile", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("SPLIT_IDE"), "IMG,DIR", "IMG.img");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaIDEFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("SPLIT_IDE", strPath);

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showConvertDialog("New IMG Version", CLocalizationManager::get()->getTranslatedText("Save"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaIDEFile", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("SPLIT_IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaIDEFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("SPLIT_IDE", CPathManager::getDirectory(vecPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	bool bDeleteFromSource = getIMGF()->getPopupGUIManager()->showConfirmDialog(CLocalizationManager::get()->getTranslatedText("Window_Confirm_1_Message"), CLocalizationManager::get()->getTranslatedText("Window_Confirm_1_Title"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	vector<string> vecEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecPaths);
	vecEntryNamesWithoutExtension = CStdVector::toUpperCase(vecEntryNamesWithoutExtension);

	vector<CIMGEntry*> vecIMGEntries;
	vector<string> vecSplitEntryNames;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		auto it = std::find(vecEntryNamesWithoutExtension.begin(), vecEntryNamesWithoutExtension.end(), strEntryNameWithoutExtension);
		if (it != vecEntryNamesWithoutExtension.end())
		{
			vecIMGEntries.push_back(pIMGEntry);
			vecSplitEntryNames.push_back(pIMGEntry->getEntryName());
		}
	}

	eIMGVersion eIMGVersionValue = IMG_UNKNOWN;
	bool bIsEncrypted = false;
	switch (uiRadioButtonIndex)
	{
	case 0:
		eIMGVersionValue = IMG_1;
		break;
	case 1:
		eIMGVersionValue = IMG_2;
		break;
	case 2:
		eIMGVersionValue = IMG_3;
		bIsEncrypted = true;
		break;
	case 3:
		eIMGVersionValue = IMG_3;
		bIsEncrypted = false;
		break;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntries.size() * (bDeleteFromSource ? 2 : 1));
	getIMGF()->getEntryListTab()->getIMGFile()->split(vecIMGEntries, strPath, eIMGVersionValue);
	
	if(bDeleteFromSource)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_70", vecSplitEntryNames.size(), CPathManager::getFileName(strPath).c_str(), CIMGManager::getVersionNameWithGames(eIMGVersionValue, bIsEncrypted).c_str(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str()));
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_69", vecSplitEntryNames.size(), CPathManager::getFileName(strPath).c_str(), CIMGManager::getVersionNameWithGames(eIMGVersionValue, bIsEncrypted).c_str(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str()));
	}
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_67"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecSplitEntryNames, "\n"), true);

	if (bDeleteFromSource)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
		for (auto pIMGEntry : vecIMGEntries)
		{
			getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}

	openFile(strPath);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaIDEFile");
}
void		CTaskDispatchManager::onRequestSplitViaTextLines(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSplitViaTextLines");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("SPLIT_TEXTLINES"), "IMG,DIR", "IMG.img");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaTextLines", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("SPLIT_TEXTLINES", strPath);

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showConvertDialog("New IMG Version", CLocalizationManager::get()->getTranslatedText("Save"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Message"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strData == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	bool bDeleteFromSource = getIMGF()->getPopupGUIManager()->showConfirmDialog(CLocalizationManager::get()->getTranslatedText("Window_Confirm_1_Message"), CLocalizationManager::get()->getTranslatedText("Window_Confirm_1_Title"));
	getIMGF()->getTaskManager()->onTaskUnpause();

	vector<string> vecEntryNames;
	vector<string> vecLines = CString2::split(strData, "\r\n");
	for (auto strLine : vecLines)
	{
		strLine = CString2::trim(strLine);
		if (strLine == "")
		{
			continue;
		}

		vecEntryNames.push_back(strLine);
	}
	vecEntryNames = CStdVector::toUpperCase(vecEntryNames);

	vector<CIMGEntry*> vecIMGEntries;
	vector<string> vecSplitEntryNames;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		auto it = std::find(vecEntryNames.begin(), vecEntryNames.end(), strEntryNameWithoutExtension);
		if (it != vecEntryNames.end())
		{
			vecIMGEntries.push_back(pIMGEntry);
			vecSplitEntryNames.push_back(pIMGEntry->getEntryName());
		}
	}

	eIMGVersion eIMGVersionValue = IMG_UNKNOWN;
	bool bIsEncrypted = false;
	switch (uiRadioButtonIndex)
	{
	case 0:
		eIMGVersionValue = IMG_1;
		break;
	case 1:
		eIMGVersionValue = IMG_2;
		break;
	case 2:
		eIMGVersionValue = IMG_3;
		bIsEncrypted = true;
		break;
	case 3:
		eIMGVersionValue = IMG_3;
		bIsEncrypted = false;
		break;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntries.size() * (bDeleteFromSource ? 2 : 1));
	getIMGF()->getEntryListTab()->getIMGFile()->split(vecIMGEntries, strPath, eIMGVersionValue);

	if(bDeleteFromSource)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_73", vecSplitEntryNames.size(), CPathManager::getFileName(strPath).c_str(), CIMGManager::getVersionNameWithGames(eIMGVersionValue, bIsEncrypted).c_str(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str()));
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_72", vecSplitEntryNames.size(), CPathManager::getFileName(strPath).c_str(), CIMGManager::getVersionNameWithGames(eIMGVersionValue, bIsEncrypted).c_str(), CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str()));
	}
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_67"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecSplitEntryNames, "\n"), true);

	if (bDeleteFromSource)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
		for (auto pIMGEntry : vecIMGEntries)
		{
			getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}

	openFile(strPath);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSplitViaTextLines");
}
void		CTaskDispatchManager::onRequestReplace(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestReplace");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestReplace", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	string strEntryName;
	if (pos != NULL)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		CIMGEntry *pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);
		strEntryName = pIMGEntry->getEntryName();
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("REPLACE"), "", "", strEntryName);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestReplace", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("REPLACE", CPathManager::getDirectory(vecPaths[0]));

	vector<string> vecUniqueFilePaths = CPathManager::getUniqueFilePaths(vecPaths, getIMGF()->getEntryListTab()->getIMGFile()->getEntryNames());
	vector<string> vecReplaceFilePaths = CStdVector::getUniqueEntries(vecPaths, vecUniqueFilePaths);
	uint32 uiReplaceEntryCount = vecReplaceFilePaths.size();

	bool bOverwriteFiles = false;
	if (getIMGF()->getSettingsManager()->getSettingBool("AskBeforeOverwritingFiles"))
	{
		getIMGF()->getTaskManager()->onTaskPause();
		bOverwriteFiles = getIMGF()->getPopupGUIManager()->showConfirmDialog("Replace " + CString2::toString(uiReplaceEntryCount) + " entr" + (uiReplaceEntryCount == 1 ? "y" : "ies") + "?", CLocalizationManager::get()->getTranslatedText("Window_Confirm_2_Title"));
		getIMGF()->getTaskManager()->onTaskUnpause();

		if (!bOverwriteFiles)
		{
			vecPaths = vecUniqueFilePaths;
		}
	}
	else
	{
		//vector<string> vecA = CStdVector::getUniqueEntries(getIMGF()->getEntryListTab()->getIMGFile()->getEntryNamesUpper(), CPathManager::getFileNamesFromFilePaths(vecPaths));

		vector<string> vecNewReplacedFilePaths;
		for (auto strFilePath : vecReplaceFilePaths)
		{
			bool bReplaceEntry = true;
			CIMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByName(CPathManager::getFileName(strFilePath));

			uint32
				uiExistingEntryFileCreationDate = pIMGEntry->getFileCreationDate(),
				uiNewEntryFileCreationDate = CFileManager::getFileCreationDate(strFilePath);

			if (uiExistingEntryFileCreationDate < uiNewEntryFileCreationDate)
			{
				// the existing entry is older than the new entry

				if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteOlderFiles"))
				{
					bReplaceEntry = true;
				}
				else
				{
					bReplaceEntry = false;
				}
			}
			else if (uiExistingEntryFileCreationDate > uiNewEntryFileCreationDate)
			{
				// the existing entry is newer than the new entry

				if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteNewerFiles"))
				{
					bReplaceEntry = true;
				}
				else
				{
					bReplaceEntry = false;
				}
			}

			if (pIMGEntry->isProtectedEntry())
			{
				// the entry is protected

				if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteProtectedFiles"))
				{
					bReplaceEntry = true;
				}
				else
				{
					bReplaceEntry = false;
				}
			}

			if (bReplaceEntry)
			{
				vecNewReplacedFilePaths.push_back(strFilePath);
			}
		}
		vecPaths = CStdVector::combineVectors(vecUniqueFilePaths, vecNewReplacedFilePaths);
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecPaths.size());
	vector<string> vecReplacedEntryNames;
	getIMGF()->getEntryListTab()->replace(vecPaths, vecReplacedEntryNames);

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("ReplacedEntries", vecReplacedEntryNames.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("EntriesForReplace"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecReplacedEntryNames, "\n"), true);

	getIMGF()->getIMGEditor()->refreshActiveTab();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestReplace");
	*/
}
void		CTaskDispatchManager::onRequestExportSelected(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportSelected");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportSelected", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORT_SELECTED"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportSelected", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_SELECTED", strPath);

	vector<CIMGEntry*> vecIMGEntries;
	vector<string> vecExportedEntryNames;

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	CIMGEntry *pIMGEntry = nullptr;
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportSelected", true);
		return;
	}
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);
		vecIMGEntries.push_back(pIMGEntry);
		vecExportedEntryNames.push_back(pIMGEntry->getEntryName());

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->getIMGFile()->exportMultiple(vecIMGEntries, strPath);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_76", vecIMGEntries.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_77"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecExportedEntryNames, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportSelected");
	*/
}
void		CTaskDispatchManager::onRequestSearchText(void) // from search box
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSearchText");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSearchText", true);
		return;
	}

	CString strSearchText2;
	((CEdit*)getIMGF()->getDialog()->GetDlgItem(24))->GetWindowTextW(strSearchText2);
	string strSearchText = CString2::convertCStringToStdString(strSearchText2);
	if (strSearchText == "")
	{
		CListCtrl *pListControlSearch = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(22);
		pListControlSearch->DeleteAllItems();
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", 0).c_str());

		getIMGF()->getTaskManager()->onTaskEnd("onRequestSearchText", true);
		return;
	}

	bool bSearchInAllTabs = ((CButton*)getIMGF()->getDialog()->GetDlgItem(46))->GetCheck() == BST_CHECKED;
	if(bSearchInAllTabs)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_79", strSearchText.c_str()), bSearchInAllTabs);
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_78", strSearchText.c_str()), bSearchInAllTabs);
	}

	getIMGF()->getEntryListTab()->setSearchText(strSearchText);
	getIMGF()->getEntryListTab()->searchText();

	if (bSearchInAllTabs)
	{
		getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedFormattedText("LogAllTabs_3", getIMGF()->getIMGEditor()->getSearchHitCount(), getIMGF()->getIMGEditor()->getSearchFileCount()), true);
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("LogAllTabs_3", getIMGF()->getIMGEditor()->getSearchHitCount(), getIMGF()->getIMGEditor()->getSearchFileCount()), true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSearchText");
	*/
}
void		CTaskDispatchManager::onRequestSearchSelection(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSearchSelection");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSearchSelection", true);
		return;
	}

	CListCtrl *pListControlSearch = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(22));
	CListCtrl *pListControlMain = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	CSearchEntry *pSearchEntry;
	POSITION pos = pListControlSearch->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSearchSelection", true);
		return;
	}
	int nItem2 = -1;
	while (pos)
	{
		int nItem = pListControlSearch->GetNextSelectedItem(pos);
		pSearchEntry = (CSearchEntry*)pListControlSearch->GetItemData(nItem);

		if (pSearchEntry->getWindowTab() != getIMGF()->getEntryListTab())
		{
			getIMGF()->getIMGEditor()->setActiveTab(pSearchEntry->getWindowTab());
		}
		nItem2 = getIMGF()->getIMGEditor()->getMainListControlItemByEntry(pSearchEntry->getIMGEntry());
		pListControlMain->SetItemState(nItem2, LVIS_SELECTED, LVIS_SELECTED);
		pListControlMain->SetSelectionMark(nItem2);
	}
	//pListControlMain->SetFocus();

	if (nItem2 != -1)
	{
		CRect ItemRect;
		pListControlMain->GetSubItemRect(1, 1, LVIR_BOUNDS, ItemRect);
		uint32 uiHeight = ItemRect.bottom - ItemRect.top;

		uint32 uiCurrentScroll = (int)pListControlMain->GetScrollPos(SB_VERT);

		pListControlMain->Scroll(CSize(0, (nItem2 - uiCurrentScroll) * uiHeight));
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSearchSelection");
	*/
}
void		CTaskDispatchManager::onRequestFilter(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestFilter");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFilter", true);
		return;
	}

	if (getIMGF()->getEntryListTab()->isRestoringFilterOptions())
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFilter", true);
		return;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(getIMGF()->getEntryListTab()->getIMGFile()->getEntryCount());

	getIMGF()->getEntryListTab()->storeFilterOptions();
	getIMGF()->getEntryListTab()->readdAllEntriesToMainListView();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestFilter");
}
void		CTaskDispatchManager::onRequestFind(bool bFindInAllOpenedFiles) // from menu
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestFind");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFind", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strSearchText = getIMGF()->getPopupGUIManager()->showTextInputDialog(CLocalizationManager::get()->getTranslatedText("Window_TextInput_2_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextInput_2_Message"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	
	if (strSearchText == "")
	{
		CListCtrl *pListControlSearch = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(22);
		pListControlSearch->DeleteAllItems();
		((CStatic*)getIMGF()->getDialog()->GetDlgItem(0))->SetWindowTextW(CLocalizationManager::get()->getTranslatedFormattedTextW("Window_Main_Text_SearchResult_ActiveTab", 0).c_str());

		getIMGF()->getTaskManager()->onTaskEnd("onRequestFind", true);
		return;
	}

	((CEdit*)getIMGF()->getDialog()->GetDlgItem(24))->SetWindowTextW(CString2::convertStdStringToStdWString(strSearchText).c_str());

	if (bFindInAllOpenedFiles)
	{
		((CButton*)getIMGF()->getDialog()->GetDlgItem(46))->SetCheck(BST_CHECKED);
	}

	getIMGF()->getEntryListTab()->setSearchText(strSearchText);
	getIMGF()->getEntryListTab()->searchText();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestFind");
	*/
}
void		CTaskDispatchManager::onRequestExportViaButton(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportViaButton");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaButton", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showExportViaDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaButton", true);
		return;
	}

	switch (uiRadioButtonIndex)
	{
	case 0:
		onRequestExportSelected();
		break;
	case 1:
		onRequestExportViaIDEFile();
		break;
	case 2:
		onRequestExportViaTextLines();
		break;
	case 3:
		onRequestExportViaIPLFile();
		break;
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaButton");
}
void		CTaskDispatchManager::onRequestExportViaIDEFile(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportViaIDEFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIDEFile", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("EXPORT_IDE__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIDEFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("EXPORT_IDE__IDE", CPathManager::getDirectory(vecPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORT_IDE__DESTINATION"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIDEFile", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_IDE__DESTINATION", strPath);

	vector<string> vecEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecPaths);
	vecEntryNamesWithoutExtension = CStdVector::toUpperCase(vecEntryNamesWithoutExtension);

	vector<CIMGEntry*> vecIMGEntries;
	vector<string> vecExportedEntryNames;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		auto it = std::find(vecEntryNamesWithoutExtension.begin(), vecEntryNamesWithoutExtension.end(), strEntryNameWithoutExtension);
		if (it != vecEntryNamesWithoutExtension.end())
		{
			vecIMGEntries.push_back(pIMGEntry);
			vecExportedEntryNames.push_back(pIMGEntry->getEntryName());
		}
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntries.size());
	getIMGF()->getEntryListTab()->getIMGFile()->exportMultiple(vecIMGEntries, strPath);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_80", vecIMGEntries.size(), getIMGF()->getEntryListTab()->getIMGFile()->getEntryCount()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_77"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecExportedEntryNames, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIDEFile");
}
void		CTaskDispatchManager::onRequestExportViaTextLines(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportViaTextLines");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Message"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strData == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORT_TEXTLINES"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaTextLines", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_TEXTLINES", strPath);

	vector<string> vecEntryNames;
	vector<string> vecLines = CString2::split(strData, "\r\n");
	for (auto strLine : vecLines)
	{
		strLine = CString2::trim(strLine);
		if (strLine == "")
		{
			continue;
		}

		vecEntryNames.push_back(strLine);
	}
	vecEntryNames = CStdVector::toUpperCase(vecEntryNames);

	vector<CIMGEntry*> vecIMGEntries;
	vector<string> vecExportedEntryNames;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		auto it = std::find(vecEntryNames.begin(), vecEntryNames.end(), strEntryNameWithoutExtension);
		if (it != vecEntryNames.end())
		{
			vecIMGEntries.push_back(pIMGEntry);
			vecExportedEntryNames.push_back(pIMGEntry->getEntryName());
		}
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntries.size());
	getIMGF()->getEntryListTab()->getIMGFile()->exportMultiple(vecIMGEntries, strPath);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_81", vecIMGEntries.size(), vecEntryNames.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_77"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecExportedEntryNames, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaTextLines");
}
void		CTaskDispatchManager::onRequestSortEntries(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSortEntries");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSortEntries", true);
		return;
	}

	getIMGF()->getEntryListTab()->sortEntries();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSortEntries");
}
void		CTaskDispatchManager::onRequestSortButton(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSortButton");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSortButton", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<int> vecSortOptions = getIMGF()->getPopupGUIManager()->showSortOptionsDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecSortOptions[10] == -1)
	{
		return;
	}

	bool bCancel = false;
	for (uint32 i = 0; i < 10; i++)
	{
		for (uint32 i2 = 0; i2 < 9; i2++)
		{
			// todo CheckMenuItem(getIMGF()->m_hMenu_Entry_Sort, 1200 + (20 * i) + i2, MF_UNCHECKED);
		}

		if (vecSortOptions[i] != -1)
		{
			// todo CheckMenuItem(getIMGF()->m_hMenu_Entry_Sort, 1200 + (20 * i) + vecSortOptions[i], MF_CHECKED);
		}

		uint32 uiPriority = i;
		// todo CMenu *pSortMenu = nullptr; // todo CMenu::FromHandle(getIMGF()->m_hMenu_Entry_Sort);
		uint32 wp = 1200 + (20 * i) + vecSortOptions[i];

		if (vecSortOptions[i] == 6) // sort by IDE file
		{
			getIMGF()->getTaskManager()->onTaskPause();
			vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("SORT_IDE"), "IDE", false);
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (vecPaths.size() == 0)
			{
				bCancel = true;
			}
			else
			{
				getIMGF()->setLastUsedDirectory("SORT_IDE", CPathManager::getDirectory(vecPaths[0]));

				CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(vecPaths[0]);
				if(!pIDEFile->doesHaveError())
				{
					vector<string> vecModelNames = pIDEFile->getModelNames();
					vector<string> vecTextureNames = pIDEFile->getTXDNames();
					vector<string> vecEntryNames = CStdVector::toUpperCase(CStdVector::combineVectors(vecModelNames, vecTextureNames));
					getIMGF()->getSortManager()->getSortPriorities()->getEntryByIndex((uint16)uiPriority)->setData(vecEntryNames);

					// todo pSortMenu->ModifyMenuW(LOWORD(wp), 0, LOWORD(wp), CLocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", "IDE file", CPathManager::getFileName(pIDEFile->getFilePath()).c_str()).c_str());
				}
				pIDEFile->unload();
				delete pIDEFile;
			}
		}
		else if (vecSortOptions[i] == 7) // sort by COL file
		{
			getIMGF()->getTaskManager()->onTaskPause();
			vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("SORT_COL"), "COL", false);
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (vecPaths.size() == 0)
			{
				bCancel = true;
			}
			else
			{
				getIMGF()->setLastUsedDirectory("SORT_COL", CPathManager::getDirectory(vecPaths[0]));

				CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(vecPaths[0]);
				if(!pCOLFile->doesHaveError())
				{
					vector<string> vecEntryNames = CStdVector::toUpperCase(pCOLFile->getModelNames());
					getIMGF()->getSortManager()->getSortPriorities()->getEntryByIndex((uint16)uiPriority)->setData(vecEntryNames);

					// todo pSortMenu->ModifyMenuW(LOWORD(wp), 0, LOWORD(wp), CLocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", "COL file", CPathManager::getFileName(pCOLFile->getFilePath()).c_str()).c_str());
				}
				pCOLFile->unload();
				delete pCOLFile;
			}
		}
		else if (vecSortOptions[i] == 8) // sort by file extensions
		{
			getIMGF()->getTaskManager()->onTaskPause();
			string strText = getIMGF()->getPopupGUIManager()->showTextInputDialog(CLocalizationManager::get()->getTranslatedText("Window_TextInput_3_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextInput_4_Message"));
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (strText == "")
			{
				bCancel = true;
			}
			else
			{
				vector<string> vecFileExtensions = CString2::split(strText, ",");
				for (uint32 i = 0; i < vecFileExtensions.size(); i++)
				{
					vecFileExtensions[i] = CString2::toUpperCase(CString2::trim(vecFileExtensions[i]));
					if (vecFileExtensions[i][0] == '.')
					{
						vecFileExtensions[i] = vecFileExtensions[i].substr(1);
					}
				}
				getIMGF()->getSortManager()->getSortPriorities()->getEntryByIndex((uint16)uiPriority)->setData(vecFileExtensions);
				// todo pSortMenu->ModifyMenuW(LOWORD(wp), 0, LOWORD(wp), CLocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText_WithFilename", CLocalizationManager::get()->getTranslatedTextW("Sort_Extensions").c_str(), CString2::join(vecFileExtensions, ", ").c_str()).c_str());
			}
		}

		if (!bCancel)
		{
			// todo CheckMenuItem(getIMGF()->m_hMenu_Entry_Sort, LOWORD(wp), MF_CHECKED);
		}
	}

	if (bCancel)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSortButton", true);
		return;
	}

	getIMGF()->getEntryListTab()->sortEntries();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSortButton");
}
void		CTaskDispatchManager::onRequestRemoveViaIDEFile(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRemoveViaIDEFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaIDEFile", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("REMOVE_IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaIDEFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("REMOVE_IDE", CPathManager::getDirectory(vecPaths[0]));

	vector<string> vecEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecPaths);
	vecEntryNamesWithoutExtension = CStdVector::toUpperCase(vecEntryNamesWithoutExtension);

	vector<CIMGEntry*> vecIMGEntries;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		auto it = std::find(vecEntryNamesWithoutExtension.begin(), vecEntryNamesWithoutExtension.end(), strEntryNameWithoutExtension);
		if (it != vecEntryNamesWithoutExtension.end())
		{
			vecIMGEntries.push_back(pIMGEntry);
		}
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(getIMGF()->getEntryListTab()->getIMGFile()->getEntryCount());

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	vector<string> vecRemovedEntryNames;
	for (auto pIMGEntry : vecIMGEntries)
	{
		int nItem = getIMGF()->getEntryListTab()->getIMGFile()->getIndexByEntry(pIMGEntry);
		pListControl->DeleteItem(nItem);

		vecRemovedEntryNames.push_back(pIMGEntry->getEntryName());
		getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	if (pListControl->GetItemCount() == 0)
	{
		getIMGF()->getEntryListTab()->readdAllEntriesToMainListView();
	}

	getIMGF()->getEntryListTab()->searchText();

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_82", vecIMGEntries.size(), vecEntryNamesWithoutExtension.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_83"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecRemovedEntryNames, "\n"), true);

	if (vecIMGEntries.size() > 0)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaIDEFile");
	*/
}
void		CTaskDispatchManager::onRequestRemoveViaTextLines(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRemoveViaTextLines");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("Window_TextArea_4_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Message"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strData == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaTextLines", true);
		return;
	}

	vector<string> vecEntryNames;
	vector<string> vecLines = CString2::split(strData, "\r\n");
	for (auto strLine : vecLines)
	{
		strLine = CString2::trim(strLine);
		if (strLine == "")
		{
			continue;
		}

		vecEntryNames.push_back(CPathManager::removeFileExtension(strLine));
	}
	vecEntryNames = CStdVector::toUpperCase(vecEntryNames);

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecEntryNames.size());

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	uint32 uiRemoveCount = 0;
	vector<string> vecRemovedEntryNames;
	for (auto strEntryName : vecEntryNames)
	{
		CIMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByNameWithoutExtension(strEntryName);
		if (pIMGEntry != nullptr)
		{
			int nItem = getIMGF()->getEntryListTab()->getIMGFile()->getIndexByEntry(pIMGEntry);
			pListControl->DeleteItem(nItem);

			vecRemovedEntryNames.push_back(pIMGEntry->getEntryName());

			getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);

			uiRemoveCount++;
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	if (pListControl->GetItemCount() == 0)
	{
		getIMGF()->getEntryListTab()->readdAllEntriesToMainListView();
	}

	getIMGF()->getEntryListTab()->searchText();

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_82", uiRemoveCount, vecEntryNames.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_83"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecRemovedEntryNames, "\n"), true);

	if (uiRemoveCount > 0)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaTextLines");
	*/
}
void		CTaskDispatchManager::onRequestRemoveViaButton(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRemoveViaButton");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaButton", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showRemoveViaDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaButton", true);
		return;
	}

	switch (uiRadioButtonIndex)
	{
	case 0:
		onRequestRemoveSelected();
		break;
	case 1:
		onRequestRemoveViaIDEFile();
		break;
	case 2:
		onRequestRemoveViaTextLines();
		break;
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveViaButton");
}
void		CTaskDispatchManager::onRequestImportViaButton(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestImportViaButton");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaButton", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	uint32 uiRadioButtonIndex = getIMGF()->getPopupGUIManager()->showImportViaDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (uiRadioButtonIndex == 0xFFFFFFFF)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaButton", true);
		return;
	}

	switch (uiRadioButtonIndex)
	{
	case 0:
		onRequestImportViaFiles();
		break;
	case 1:
		onRequestImportViaIDEFile();
		break;
	case 2:
		onRequestImportViaTextLines();
		break;
	case 3:
		onRequestImportViaFolder();
		break;
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaButton");
}
void		CTaskDispatchManager::onRequestImportViaIDEFile(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestImportViaIDEFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaIDEFile", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("IMPORT_IDE__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaIDEFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("IMPORT_IDE__IDE", CPathManager::getDirectory(vecPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	string strFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_13"), getIMGF()->getLastUsedDirectory("IMPORT_IDE__SOURCE"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaIDEFile", true);
		return;
	}
	strFolderPath = CPathManager::addSlashToEnd(strFolderPath);
	getIMGF()->setLastUsedDirectory("IMPORT_IDE__SOURCE", strFolderPath);

	vector<string> vecEntryNamesInAllFiles;
	for (auto strPath : vecPaths)
	{
		CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strPath);
		vector<string> vecEntryNames;
		if(!pIDEFile->doesHaveError())
		{
			vector<string> vecModelNames = pIDEFile->getModelNames();
			for (string& strModelName : vecModelNames)
			{
				strModelName += ".DFF";
			}
			
			vector<string> vecTextureNames = pIDEFile->getTXDNames();
			for (string& strTextureName : vecTextureNames)
			{
				strTextureName += ".TXD";
			}

			vecEntryNames = CStdVector::combineVectors(vecModelNames, vecTextureNames);
		}
		pIDEFile->unload();
		delete pIDEFile;

		vecEntryNamesInAllFiles = CStdVector::combineVectors(vecEntryNamesInAllFiles, CStdVector::toUpperCase(vecEntryNames));
	}
	vecEntryNamesInAllFiles = CStdVector::removeDuplicates(vecEntryNamesInAllFiles);

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecEntryNamesInAllFiles.size());
	uint32 uiImportCount = 0;
	vector<string> vecImportedEntryNames;
	for (auto strEntryName : vecEntryNamesInAllFiles)
	{
		string strEntryPath = strFolderPath + strEntryName;
		if (CFileManager::doesFileExist(strEntryPath))
		{
			uiImportCount++;
			getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryPath);
			vecImportedEntryNames.push_back(strEntryName);
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_84", uiImportCount, vecEntryNamesInAllFiles.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("EntriesForImport"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecImportedEntryNames, "\n"), true);

	if (uiImportCount > 0)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaIDEFile");
}
void		CTaskDispatchManager::onRequestImportViaTextLines(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestImportViaTextLines");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("Window_TextArea_5_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Message"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strData == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaTextLines", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_13"), getIMGF()->getLastUsedDirectory("IMPORT_TEXTLINES"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaTextLines", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("IMPORT_TEXTLINES", strPath);

	vector<string> vecEntryNamesWithoutExtension, vecImportedEntryNames;
	vector<string> vecLines = CString2::split(strData, "\r\n");
	for (auto strLine : vecLines)
	{
		strLine = CString2::trim(strLine);
		if (strLine == "")
		{
			continue;
		}

		strLine = CPathManager::removeFileExtension(strLine);
		vecEntryNamesWithoutExtension.push_back(strLine);
	}
	vecEntryNamesWithoutExtension = CStdVector::removeDuplicates(CStdVector::toUpperCase(vecEntryNamesWithoutExtension));

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecEntryNamesWithoutExtension.size());
	uint32 uiImportCount = 0;
	for (auto strEntryNameWithoutExtension : vecEntryNamesWithoutExtension)
	{
		string strFileName = CFileManager::getFileNameFromNameWithoutExtension(strPath, strEntryNameWithoutExtension);
		if (strFileName != "")
		{
			uiImportCount++;
			getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strPath + strFileName);
			vecImportedEntryNames.push_back(strFileName);
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_84", uiImportCount, vecEntryNamesWithoutExtension.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("EntriesForImport"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecImportedEntryNames, "\n"), true);

	if (uiImportCount > 0)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaTextLines");
}
void		CTaskDispatchManager::onRequestNew(eIMGVersion eIMGVersion)
{
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_New_IMGVersion(eIMGVersion);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestNew");
	//TCHAR szCurrentDirectory[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, szCurrentDirectory);

	//string strFilePath = CPathManager::addSlashToEnd(CString2::convertStdWStringToStdString(szCurrentDirectory)) + "Untitled.img";
	//strFilePath = CFileManager::getNextIncrementingFileName(strFilePath);

	/*
	getIMGF()->getTaskManager()->onTaskPause();
	string strFilePath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("NEW"), "IMG,DIR", "IMG.img");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strFilePath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestNew", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("NEW", strFilePath);
	*/

	string strFilePath = getIMGF()->getInstallationMeta().getLocalAppPath() + "New/IMG/New.img";
	strFilePath = CFileManager::getNextIncrementingFileName(strFilePath);
	CFileManager::createFoldersForPath(strFilePath);
	strFilePath = CString2::replace(strFilePath, "/", "\\");
	getIMGF()->getIMGEditor()->addBlankFile(strFilePath, eIMGVersion);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestNew");
}
void		CTaskDispatchManager::onRequestStats(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestStats");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestStats", true);
		return;
	}

	unordered_map<uint32, uint32> umapStatsRWVersions;
	unordered_map<string, uint32> umapStatsExtensions;

	for (CIMGEntry *pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		if (pIMGEntry->getRWVersion() != nullptr)
		{
			if (pIMGEntry->isCOLFile())
			{
			}
			else
			{
				if (umapStatsRWVersions.count(pIMGEntry->getRWVersion()->getVersionCC()) == 0) // crashes when calling getVersionCC()
				{
					umapStatsRWVersions.insert(std::pair<uint32, uint32>(pIMGEntry->getRWVersion()->getVersionCC(), 1));
				}
				else
				{
					umapStatsRWVersions[pIMGEntry->getRWVersion()->getVersionCC()]++;
				}
			}
		}

		string strExtension = CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()));
		if (umapStatsExtensions.count(strExtension) == 0)
		{
			umapStatsExtensions.insert(std::pair<string, uint32>(strExtension, 1));
		}
		else
		{
			umapStatsExtensions[strExtension]++;
		}
	}

	unordered_map<uint32, vector<string>> umapVersionNames1 = CRWManager::get()->getVersionManager()->getVersionNames();
	unordered_map<uint32, string> umapVersionNames2;
	for(auto it : umapVersionNames1)
	{
		uint32 uiVersionCC = it.first;
		vector<string> vecVersionNames3 = it.second;
		string strVersionName = vecVersionNames3[0];
		string strLocalizationKey = vecVersionNames3[1];
		
		umapVersionNames2[uiVersionCC] = strVersionName + " (" + CLocalizationManager::get()->getTranslatedText(strLocalizationKey) + ")";
	}
	
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showStatsDialog(umapStatsRWVersions, umapStatsExtensions, umapVersionNames2);
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestStats");
}
void		CTaskDispatchManager::onRequestNameCase(uint8 ucCaseType, uint8 ucFilenameType)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_NameCase_CaseType(ucCaseType);
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_NameCase_FilenameType(ucFilenameType);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestNameCase");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestNameCase", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	CIMGEntry *pIMGEntry;
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestNameCase", true);
		return;
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (ucCaseType == 0)
		{
			if (ucFilenameType == 0)
			{
				pIMGEntry->setEntryName(CString2::toLowerCase(pIMGEntry->getEntryName()));
			}
			else if (ucFilenameType == 1)
			{
				pIMGEntry->setEntryName(CString2::toLowerCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName())) + "." + CPathManager::getFileExtension(pIMGEntry->getEntryName()));
			}
			else if (ucFilenameType == 2)
			{
				pIMGEntry->setEntryName(CPathManager::removeFileExtension(pIMGEntry->getEntryName()) + "." + CString2::toLowerCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())));
			}
		}
		else if (ucCaseType == 1)
		{
			if (ucFilenameType == 0)
			{
				pIMGEntry->setEntryName(CString2::toUpperCase(pIMGEntry->getEntryName()));
			}
			else if (ucFilenameType == 1)
			{
				pIMGEntry->setEntryName(CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName())) + "." + CPathManager::getFileExtension(pIMGEntry->getEntryName()));
			}
			else if (ucFilenameType == 2)
			{
				pIMGEntry->setEntryName(CPathManager::removeFileExtension(pIMGEntry->getEntryName()) + "." + CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())));
			}
		}
		else if (ucCaseType == 2)
		{
			if (ucFilenameType == 0)
			{
				pIMGEntry->setEntryName(CString2::toTitleCase(pIMGEntry->getEntryName()));
			}
			else if (ucFilenameType == 1)
			{
				pIMGEntry->setEntryName(CString2::toTitleCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName())) + "." + CPathManager::getFileExtension(pIMGEntry->getEntryName()));
			}
			else if (ucFilenameType == 2)
			{
				pIMGEntry->setEntryName(CPathManager::removeFileExtension(pIMGEntry->getEntryName()) + "." + CString2::toTitleCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())));
			}
		}

		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->searchText();

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestNameCase");
	*/
}
void		CTaskDispatchManager::onRequestCopyEntryData(eIMGEntryProperty eIMGEntryProperty)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_Copy_IMGEntryProperty(eIMGEntryProperty);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestCopyEntryData");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCopyEntryData", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	CIMGEntry *pIMGEntry;
	vector<string> vecCopyLines;
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCopyEntryData", true);
		return;
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		switch (eIMGEntryProperty)
		{
		case IMG_ENTRY_ID:
			vecCopyLines.push_back(CString2::toString(getIMGF()->getEntryListTab()->getIMGFile()->getIndexByEntry(pIMGEntry) + 1));
			break;
		case IMG_ENTRY_NAME:
			vecCopyLines.push_back(pIMGEntry->getEntryName());
			break;
		case IMG_ENTRY_OFFSET:
			vecCopyLines.push_back(CString2::toString(pIMGEntry->getEntryOffsetInSectors() * 2048));
			break;
		case IMG_ENTRY_RESOURCETYPE:
			vecCopyLines.push_back(pIMGEntry->getRageResourceType()->getResourceName());
			break;
		case IMG_ENTRY_RWVERSION:
			vecCopyLines.push_back(pIMGEntry->getRWVersion()->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pIMGEntry->getRWVersion()->getLocalizationKey()) + ")");
			break;
		case IMG_ENTRY_SIZE:
			vecCopyLines.push_back(CString2::toString(pIMGEntry->getEntrySize()));
			break;
		case IMG_ENTRY_TYPE:
			vecCopyLines.push_back(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())));
			break;
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	CString2::setClipboardText(CString2::join(vecCopyLines, "\r\n"));
	getIMGF()->getTaskManager()->onTaskEnd("onRequestCopyEntryData");
	*/
}
void		CTaskDispatchManager::onRequestShift(uint8 ucDirection)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_Shift_Direction(ucDirection);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestShift");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestShift", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	CIMGEntry *pIMGEntry = nullptr;
	int nItem;
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestShift", true);
		return;
	}
	while (pos)
	{
		nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);
		break;
	}

	if (ucDirection == 0) // up
	{
		if (nItem == 0)
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestShift", true);
			return;
		}
	}
	else if (ucDirection == 1) // down
	{
		if (nItem == (pListControl->GetItemCount() - 1))
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestShift", true);
			return;
		}
	}

	CIMGEntry *pIMGEntry2;
	uint32 uiIMGEntry1Index = nItem;
	uint32 uiIMGEntry2Index;
	if (ucDirection == 0) // up
	{
		uiIMGEntry2Index = nItem - 1;
	}
	else if (ucDirection == 1) // down
	{
		uiIMGEntry2Index = nItem + 1;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(4);

	pIMGEntry2 = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByIndex(uiIMGEntry2Index);
	getIMGF()->getEntryListTab()->getIMGFile()->swapEntries(pIMGEntry, pIMGEntry2);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	pListControl->SetItemData(uiIMGEntry1Index, (DWORD)pIMGEntry2);
	pListControl->SetItemData(uiIMGEntry2Index, (DWORD)pIMGEntry);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry2);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestShift");
	*/
}
void		CTaskDispatchManager::onRequestQuickExport(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestQuickExport");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestQuickExport", true);
		return;
	}

	if (getIMGF()->getSettingsManager()->getSettingString("QuickExportPath") == "")
	{
		getIMGF()->getTaskManager()->onTaskPause();
		string strQuickExportPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_1"), getIMGF()->getLastUsedDirectory("QUICK_EXPORT"));
		getIMGF()->getTaskManager()->onTaskUnpause();
	
		if (strQuickExportPath == "")
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestQuickExport", true);
			return;
		}
		
		getIMGF()->setLastUsedDirectory("QUICK_EXPORT", strQuickExportPath);
		getIMGF()->getSettingsManager()->setSettingString("QuickExportPath", strQuickExportPath);
	}

	vector<CIMGEntry*> vecIMGEntries;
	vector<string> vecExportedEntryNames;
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	CIMGEntry *pIMGEntry = nullptr;
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestQuickExport", true);
		return;
	}
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);
		vecIMGEntries.push_back(pIMGEntry);
		vecExportedEntryNames.push_back(pIMGEntry->getEntryName());

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->getIMGFile()->exportMultiple(vecIMGEntries, getIMGF()->getSettingsManager()->getSettingString("QuickExportPath"));
	if (vecIMGEntries.size() == 1)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_86", vecIMGEntries[0]->getEntryName().c_str(), vecIMGEntries[0]->getEntrySize()));
	}
	else
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_87", vecIMGEntries.size()));
	}
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_88"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecExportedEntryNames, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestQuickExport");
	*/
}
void		CTaskDispatchManager::onRequestSelectViaFileExtension(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSelectViaFileExtension");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaFileExtension", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strText = getIMGF()->getPopupGUIManager()->showTextInputDialog(CLocalizationManager::get()->getTranslatedText("Window_TextInput_4_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextInput_4_Message"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strText == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaFileExtension", true);
		return;
	}

	vector<string> vecFileExtensions = CString2::split(strText, ",");
	for (uint32 i = 0; i < vecFileExtensions.size(); i++)
	{
		vecFileExtensions[i] = CString2::toUpperCase(CString2::trim(vecFileExtensions[i]));
		if (vecFileExtensions[i].c_str()[0] == '.')
		{
			vecFileExtensions[i] = vecFileExtensions[i].substr(1);
		}
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	uint32 uiSelectedEntryCount = 0;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetItemCount());
	for (uint32 i = 0; i < (uint32)pListControl->GetItemCount(); i++)
	{
		if (std::find(vecFileExtensions.begin(), vecFileExtensions.end(), CString2::toUpperCase(CPathManager::getFileExtension(getIMGF()->getEntryListTab()->getIMGFile()->getEntryByIndex(i)->getEntryName()))) != vecFileExtensions.end())
		{
			uiSelectedEntryCount++;
			pListControl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			pListControl->SetSelectionMark(i);
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_89", uiSelectedEntryCount));

	pListControl->SetFocus();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaFileExtension");
	*/
}
void		CTaskDispatchManager::onRequestSelectViaRWVersion(CRWVersion *pRWVersion)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_Select_RWVersion(pRWVersion);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSelectViaRWVersion");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaRWVersion", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	uint32 uiSelectedEntryCount = 0;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetItemCount());
	for (uint32 i = 0; i < (uint32)pListControl->GetItemCount(); i++)
	{
		CRWVersion *pEntryRWVersion = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByIndex(i)->getRWVersion();
		if (pRWVersion == pEntryRWVersion || (pRWVersion->getVersionCC() == 0x0 && pEntryRWVersion == nullptr))
		{
			uiSelectedEntryCount++;
			pListControl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			pListControl->SetSelectionMark(i);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_90", uiSelectedEntryCount));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_91", (pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").c_str()), true);

	pListControl->SetFocus();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaRWVersion");
	*/
}
void		CTaskDispatchManager::onRequestVersion(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestVersion");
	CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_36", getIMGF()->getBuildMeta().getCurrentVersionString().c_str(), BUILDNUMBER_STR), CLocalizationManager::get()->getTranslatedText("Version"), MB_OK);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestVersion");
}
void		CTaskDispatchManager::onRequestTextureList(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestTextureList");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestTextureList", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	CIMGEntry *pIMGEntry = nullptr;
	int nItem;
	vector<string> vecTextureNames;
	uint32 uiEntryCount = 0;
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestTextureList", true);
		return;
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	while (pos)
	{
		nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		string strFileData = pIMGEntry->getEntryData();
		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) == "TXD")
		{
			//CDebugger::log(pIMGEntry->m_strFileName);
			CTXDFormat *pTXDFile = CTXDManager::get()->parseViaMemory(strFileData);
			if(!pTXDFile->doesHaveError())
			{
				for (auto pTexture : pTXDFile->getTextures())
				{
					if (pTexture->doesHaveDiffuse())
					{
						vecTextureNames.push_back(pTexture->getDiffuseName());
					}
					if (pTexture->doesHaveAlpha())
					{
						vecTextureNames.push_back(pTexture->getAlphaName());
					}
				}
			}
			pTXDFile->unload();
			delete pTXDFile;
			uiEntryCount++;
		}
		else if (CPathManager::isModelExtension(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()))))
		{
			CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(strFileData);
			if(!pDFFFile->doesHaveError())
			{
				for (auto pTextureEntry : pDFFFile->getTextureEntries())
				{
					if (pTextureEntry->doesHaveDiffuse())
					{
						vecTextureNames.push_back(pTextureEntry->getDiffuseName());
					}
					if (pTextureEntry->doesHaveAlpha())
					{
						vecTextureNames.push_back(pTextureEntry->getAlphaName());
					}
				}
			}
			pDFFFile->unload();
			delete pDFFFile;
			uiEntryCount++;
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getTaskManager()->onTaskPause();
	CTextureListDialogData *pTextureListDialogData = getIMGF()->getPopupGUIManager()->showTextureListDialog("Texture List", "Showing " + CString2::toString(vecTextureNames.size()) + " texture name" + (vecTextureNames.size() == 1 ? "" : "s") + " for " + CString2::toString(uiEntryCount) + " IMG entr" + (uiEntryCount == 1 ? "y" : "ies") + ".", "Texture Name", vecTextureNames);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (pTextureListDialogData->m_bSaveTexturesFormat2)
	{
		string strData = "";
		strData += "[TXDList]\n";
		strData += "Count=" + CString2::toString(vecTextureNames.size()) + "\n\n";

		for (uint32 i = 0, j = vecTextureNames.size(); i < j; i++)
		{
			strData += "[Texture" + CString2::toString(i + 1) + "]\n";
			strData += "path=" + vecTextureNames[i] + "\n\n";
		}

		getIMGF()->getTaskManager()->onTaskPause();
		string strFilePath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("SAVE_TEXTURE_LIST"), "TXT", CLocalizationManager::get()->getTranslatedText("SaveFilePopup_2_InitialFilename"));
		getIMGF()->getTaskManager()->onTaskUnpause();
		if (strFilePath == "")
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestTextureList", true);
			return;
		}
		getIMGF()->setLastUsedDirectory("SAVE_TEXTURE_LIST", strFilePath);

		CFileManager::storeFile(strFilePath, strData, true, false);
	}
	delete pTextureListDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestTextureList");
	*/
}
void		CTaskDispatchManager::onRequestAssociateIMGExtension(void)
{
	//TCHAR szExePath[MAX_PATH];
	//GetModuleFileName(NULL, szExePath, MAX_PATH);

	//CInputManager::showMessage(NULL, szExePath, "A", MB_OK);

	//CRegistryManager::assoicateFileExtension("img", CString2::convertStdWStringToStdString(szExePath));
}
string		CTaskDispatchManager::onRequestSaveLog(bool bActiveTab, bool bNormalFormat)
{
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_SaveLog_ActiveTab(bActiveTab);
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_SaveLog_NormalFormat(bNormalFormat);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSaveLog");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveLog", true);
		return "";
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strSaveFilePath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("SAVE_LOG"), "TXT", CLocalizationManager::get()->getTranslatedText("SaveFilePopup_8_InitialFilename"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strSaveFilePath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveLog", true);
		return "";
	}
	getIMGF()->setLastUsedDirectory("SAVE_LOG", strSaveFilePath);

	if (bActiveTab)
	{
		if (bNormalFormat)
		{
			CFileManager::storeFile(strSaveFilePath, CString2::join(getIMGF()->getEntryListTab()->getLogLinesBasic(), "\n"), false, false);
		}
		else
		{
			CFileManager::storeFile(strSaveFilePath, CString2::join(getIMGF()->getEntryListTab()->getLogLinesExtended(), "\n"), false, false);
		}
	}
	else
	{
		string strLogData = "";
		if (bNormalFormat)
		{
			for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
			{
				strLogData += "[[" + ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath() + "]]\n" + CString2::join(((CIMGEditorTab*)pEditorTab)->getLogLinesBasic(), "\n") + "\n\n";
			}
		}
		else
		{
			for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
			{
				strLogData += "[[" + ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath() + "]]\n" + CString2::join(((CIMGEditorTab*)pEditorTab)->getLogLinesExtended(), "\n") + "\n\n";
			}
		}
		CFileManager::storeFile(strSaveFilePath, strLogData, false, false);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveLog");

	return strSaveFilePath;
}
void		CTaskDispatchManager::onRequestSaveSession(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSaveSession");
	if (getIMGF()->getIMGEditor()->getEntryCount() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveSession", true);
		return;
	}

	string strSessionName;
	bool bSemiColonFound;
	do
	{
		getIMGF()->getTaskManager()->onTaskPause();
		strSessionName = getIMGF()->getPopupGUIManager()->showTextInputDialog(CLocalizationManager::get()->getTranslatedText("SessionName"), CLocalizationManager::get()->getTranslatedFormattedText("Window_TextInput_5_Message", getIMGF()->getIMGEditor()->getEntryCount()));
		getIMGF()->getTaskManager()->onTaskUnpause();
		if (strSessionName == "")
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveSession", true);
			return;
		}

		bSemiColonFound = CString2::isIn(strSessionName, ";");
		if (bSemiColonFound)
		{
			getIMGF()->getTaskManager()->onTaskPause();
			CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_37"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_37"), MB_OK);
			getIMGF()->getTaskManager()->onTaskUnpause();
		}
	} while (bSemiColonFound);

	vector<string> vecPaths;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getEntries())
	{
		vecPaths.push_back(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath());
	}

	getIMGF()->getSessionManager()->addSession(strSessionName, vecPaths);
	getIMGF()->getSessionManager()->loadSessions();

	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedFormattedText("LogAllTabs_4", getIMGF()->getIMGEditor()->getEntryCount(), strSessionName));
	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedText("LogAllTabs_5"), true);
	getIMGF()->getIMGEditor()->logAllTabs(CString2::join(vecPaths, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveSession");
	*/
}
void		CTaskDispatchManager::onRequestOrphanDFFEntriesNotInCOL(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanDFFEntriesNotInCOL");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInCOL", true);
		return;
	}

	// fetch DFF model names
	/*
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecDFFPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_DFF_COL__DFF"), "DFF,BSP");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecDFFPaths.size() == 0)
	{
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInCOL", true);
	return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_DFF_COL__DFF", CPathManager::getDirectory(vecDFFPaths[0]));
	*/


	vector<string> vecDFFEntryNamesWithoutExtension;
	/*
	todo
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	for (uint32 i = 0, j = pListControl->GetItemCount(); i < j; i++)
	{
		CIMGEntry *pIMGEntry = (CIMGEntry*)pListControl->GetItemData(i);

		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) == "DFF")
		{
			vecDFFEntryNamesWithoutExtension.push_back(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		}
	}
	*/

	// choose COL files
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecCOLPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_DFF_COL__COL"), "COL");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecCOLPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInCOL", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_DFF_COL__COL", CPathManager::getDirectory(vecCOLPaths[0]));

	// fetch COL model names
	vector<string> vecCOLEntryNamesWithoutExtension;
	for (auto strCOLPath : vecCOLPaths)
	{
		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(strCOLPath);
		if (!pCOLFile->doesHaveError())
		{
			vector<string> vecModelNames = pCOLFile->getModelNames();
			vecCOLEntryNamesWithoutExtension = CStdVector::combineVectors(vecCOLEntryNamesWithoutExtension, CStdVector::toUpperCase(vecModelNames));
		}
		pCOLFile->unload();
		delete pCOLFile;
	}
	vecCOLEntryNamesWithoutExtension = CStdVector::removeDuplicates(vecCOLEntryNamesWithoutExtension);

	vector<string>
		vecEntryNamesMissingFromCOL,
		vecEntryNamesMissingFromCOLUpper;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFEntryNamesWithoutExtension.size());
	for (auto strDFFEntryNameWithoutExtension : vecDFFEntryNamesWithoutExtension)
	{
		if (std::find(vecCOLEntryNamesWithoutExtension.begin(), vecCOLEntryNamesWithoutExtension.end(), strDFFEntryNameWithoutExtension) == vecCOLEntryNamesWithoutExtension.end())
		{
			vecEntryNamesMissingFromCOL.push_back(strDFFEntryNameWithoutExtension);
			vecEntryNamesMissingFromCOLUpper.push_back(CString2::toUpperCase(strDFFEntryNameWithoutExtension));
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	if (getIMGF()->getIMGEditor()->getTabs().getEntryCount() > 0)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_125", vecEntryNamesMissingFromCOL.size()));
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
		getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromCOL, "\n"), true);
	}
	else
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CLocalizationManager::get()->getTranslatedFormattedText("Log_125", vecEntryNamesMissingFromCOL.size()));
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CString2::join(vecEntryNamesMissingFromCOL, "\n"), true);
	}

	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromCOL, "DFF Entries missing from COL:");
	getIMGF()->getTaskManager()->onTaskUnpause();

	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInCOL");
}
void		CTaskDispatchManager::onRequestOrphanIDEEntriesNotInCOL(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanIDEEntriesNotInCOL");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInCOL", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_IDE_COL__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInCOL", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_IDE_COL__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecCOLPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_IDE_COL__COL"), "COL");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecCOLPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInCOL", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_IDE_COL__COL", CPathManager::getDirectory(vecCOLPaths[0]));

	vector<string> vecIDEEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, true, false);
	vecIDEEntryNamesWithoutExtension = CStdVector::toUpperCase(vecIDEEntryNamesWithoutExtension);

	vector<string> vecCOLEntryNamesWithoutExtension;
	for (auto strCOLPath : vecCOLPaths)
	{
		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(strCOLPath);
		if (pCOLFile->doesHaveError())
		{
			pCOLFile->unload();
			delete pCOLFile;
			continue;
		}
		vector<string> vecModelNames = pCOLFile->getModelNames();
		vecCOLEntryNamesWithoutExtension = CStdVector::combineVectors(vecCOLEntryNamesWithoutExtension, CStdVector::toUpperCase(vecModelNames));
		pCOLFile->unload();
		delete pCOLFile;
	}
	vecCOLEntryNamesWithoutExtension = CStdVector::removeDuplicates(vecCOLEntryNamesWithoutExtension);

	vector<string> vecEntryNamesMissingFromCOL;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIDEEntryNamesWithoutExtension.size());
	for (auto strIDEEntryNameWithoutExtension : vecIDEEntryNamesWithoutExtension)
	{
		if (std::find(vecCOLEntryNamesWithoutExtension.begin(), vecCOLEntryNamesWithoutExtension.end(), strIDEEntryNameWithoutExtension) == vecCOLEntryNamesWithoutExtension.end())
		{
			vecEntryNamesMissingFromCOL.push_back(strIDEEntryNameWithoutExtension);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_112", vecEntryNamesMissingFromCOL.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromCOL, "\n"), true);

	getIMGF()->getTaskManager()->onTaskPause();
	bool bImportEntries = getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromCOL, "IDE Entries missing from COL:", "Import into IMG");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (bImportEntries)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		string strFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_17"), getIMGF()->getLastUsedDirectory("ORPHAN_IDE_COL__IMPORT"));
		getIMGF()->getTaskManager()->onTaskUnpause();
		if (strFolderPath == "")
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInCOL", true);
			return;
		}
		strFolderPath = CPathManager::addSlashToEnd(strFolderPath);
		getIMGF()->setLastUsedDirectory("ORPHAN_IDE_COL__IMPORT", strFolderPath);

		uint32 uiImportedFileCount = 0;
		for (auto strEntryNameMissingFromCOL : vecEntryNamesMissingFromCOL)
		{
			string strEntryFilePath = strFolderPath + CFileManager::getFileNameFromNameWithoutExtension(strFolderPath, strEntryNameMissingFromCOL);
			if (CFileManager::doesFileExist(strEntryFilePath))
			{
				getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryFilePath);
				uiImportedFileCount++;
			}
		}

		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_84", uiImportedFileCount, vecEntryNamesMissingFromCOL.size()));

		if (uiImportedFileCount > 0)
		{
			getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
		}
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInCOL");
}
void		CTaskDispatchManager::onRequestOrphanDFFEntriesNotInIDE(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanDFFEntriesNotInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInIDE", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_DFF_IDE__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_DFF_IDE__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecDFFPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_DFF_IDE__DFF"), "DFF");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecDFFPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_DFF_IDE__DFF", CPathManager::getDirectory(vecDFFPaths[0]));

	vector<string> vecIDEEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, true, false);
	vecIDEEntryNamesWithoutExtension = CStdVector::toUpperCase(vecIDEEntryNamesWithoutExtension);

	vector<string> vecDFFEntryNamesWithoutExtension;
	for (auto strDFFPath : vecDFFPaths)
	{
		CDFFFormat *pDFFFile = CDFFManager::get()->parseViaFile(strDFFPath);
		if (!pDFFFile->doesHaveError())
		{
			vector<string> vecTextureNames = pDFFFile->getTextureNames();
			vecDFFEntryNamesWithoutExtension = CStdVector::combineVectors(vecDFFEntryNamesWithoutExtension, CStdVector::toUpperCase(vecTextureNames));
		}
		pDFFFile->unload();
		delete pDFFFile;
	}
	vecDFFEntryNamesWithoutExtension = CStdVector::removeDuplicates(vecDFFEntryNamesWithoutExtension);

	vector<string> vecEntryNamesMissingFromIDE;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFEntryNamesWithoutExtension.size());
	for (auto strDFFEntryNameWithoutExtension : vecDFFEntryNamesWithoutExtension)
	{
		if (std::find(vecIDEEntryNamesWithoutExtension.begin(), vecIDEEntryNamesWithoutExtension.end(), strDFFEntryNameWithoutExtension) == vecIDEEntryNamesWithoutExtension.end())
		{
			vecEntryNamesMissingFromIDE.push_back(strDFFEntryNameWithoutExtension);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_126", vecEntryNamesMissingFromIDE.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromIDE, "\n"), true);

	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromIDE, "DFF Entries missing from IDE:");
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanDFFEntriesNotInIDE");
}
void		CTaskDispatchManager::onRequestOrphanCOLEntriesNotInIDE(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanCOLEntriesNotInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanCOLEntriesNotInIDE", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_COL_IDE__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanCOLEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_COL_IDE__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecCOLPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_COL_IDE__COL"), "COL");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecCOLPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanCOLEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_COL_IDE__COL", CPathManager::getDirectory(vecCOLPaths[0]));

	vector<string> vecIDEEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, true, false);
	vecIDEEntryNamesWithoutExtension = CStdVector::toUpperCase(vecIDEEntryNamesWithoutExtension);

	vector<string> vecCOLEntryNamesWithoutExtension;
	for (auto strCOLPath : vecCOLPaths)
	{
		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(strCOLPath);
		if (!pCOLFile->doesHaveError())
		{
			vector<string> vecModelNames = pCOLFile->getModelNames();
			vecCOLEntryNamesWithoutExtension = CStdVector::combineVectors(vecCOLEntryNamesWithoutExtension, CStdVector::toUpperCase(vecModelNames));
		}
		pCOLFile->unload();
		delete pCOLFile;
	}
	vecCOLEntryNamesWithoutExtension = CStdVector::removeDuplicates(vecCOLEntryNamesWithoutExtension);

	vector<string> vecEntryNamesMissingFromIDE;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecCOLEntryNamesWithoutExtension.size());
	for (auto strCOLEntryNameWithoutExtension : vecCOLEntryNamesWithoutExtension)
	{
		if (std::find(vecIDEEntryNamesWithoutExtension.begin(), vecIDEEntryNamesWithoutExtension.end(), strCOLEntryNameWithoutExtension) == vecIDEEntryNamesWithoutExtension.end())
		{
			vecEntryNamesMissingFromIDE.push_back(strCOLEntryNameWithoutExtension);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_113", vecEntryNamesMissingFromIDE.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromIDE, "\n"), true);

	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromIDE, "COL Entries missing from IDE:");
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanCOLEntriesNotInIDE");
}
void		CTaskDispatchManager::onRequestOrphanIMGEntriesNotInIDE(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanIMGEntriesNotInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIMGEntriesNotInIDE", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_IMG_IDE__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIMGEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_IMG_IDE__IDE", CPathManager::getDirectory(vecPaths[0]));

	vector<string> vecEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecPaths);
	vecEntryNamesWithoutExtension = CStdVector::toUpperCase(vecEntryNamesWithoutExtension);

	vector<string> vecEntryNamesMissingFromIDE;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(getIMGF()->getEntryListTab()->getIMGFile()->getEntries().size());
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		if (std::find(vecEntryNamesWithoutExtension.begin(), vecEntryNamesWithoutExtension.end(), CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()))) == vecEntryNamesWithoutExtension.end())
		{
			vecEntryNamesMissingFromIDE.push_back(pIMGEntry->getEntryName());
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_92", vecEntryNamesMissingFromIDE.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromIDE, "\n"), true);

	getIMGF()->getTaskManager()->onTaskPause();
	bool bRemoveEntries = getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromIDE, "IMG Entries missing from IDE:", "Remove from IMG");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (bRemoveEntries)
	{
		CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
		for (auto strEntryNameMissingFromIDE : vecEntryNamesMissingFromIDE)
		{
			CIMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByName(strEntryNameMissingFromIDE);
			int nItem = getIMGF()->getEntryListTab()->getIMGFile()->getIndexByEntry(pIMGEntry);
			pListControl->DeleteItem(nItem);

			getIMGF()->getEntryListTab()->removeEntry(pIMGEntry);
		}

		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_53", vecEntryNamesMissingFromIDE.size()));

		if (vecEntryNamesMissingFromIDE.size() > 0)
		{
			getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
		}

		getIMGF()->getEntryListTab()->searchText();
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIMGEntriesNotInIDE");
	*/
}
void		CTaskDispatchManager::onRequestOrphanIPLEntriesNotInIDE(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanIPLEntriesNotInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIPLEntriesNotInIDE", true);
		return;
	}

	// IDE files input
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_IPL_IDE__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIPLEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_IPL_IDE__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	// IPL files input
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIPLPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_IPL_IDE__IPL"), "IPL");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIPLPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIPLEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_IPL_IDE__IPL", CPathManager::getDirectory(vecIPLPaths[0]));

	// fetch DFF names in IDE files
	vector<string> vecDFFNamesWithoutExtensionInIDE = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, true, false);
	vecDFFNamesWithoutExtensionInIDE = CStdVector::toUpperCase(vecDFFNamesWithoutExtensionInIDE);
	unordered_map<string, bool> umapDFFNamesWithoutExtensionInIDE = CStdVector::convertVectorToUnorderedMap(vecDFFNamesWithoutExtensionInIDE);
	vecDFFNamesWithoutExtensionInIDE.clear();

	// fetch DFF names in IPL files
	vector<string> vecDFFNamesWithoutExtensionInIPL;
	for (string& strIPLPath : vecIPLPaths)
	{
		CIPLFormat *pIPLFile = CIPLManager::get()->parseViaFile(strIPLPath);

		if (!pIPLFile->doesHaveError())
		{
			CStdVector::addToVector(vecDFFNamesWithoutExtensionInIPL, pIPLFile->getModelNames());
		}

		pIPLFile->unload();
		delete pIPLFile;
	}

	// find DFF names in IPL files but not found in IDE files
	vector<string> vecEntryNamesMissingFromIDE;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFNamesWithoutExtensionInIPL.size());
	for (auto strDFFEntryNameWithoutExtension : vecDFFNamesWithoutExtensionInIPL)
	{
		string strDFFEntryNameWithoutExtensionUpper = CString2::toUpperCase(strDFFEntryNameWithoutExtension);
		if (umapDFFNamesWithoutExtensionInIDE.count(strDFFEntryNameWithoutExtensionUpper) == 0)
		{
			vecEntryNamesMissingFromIDE.push_back(strDFFEntryNameWithoutExtension);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// log
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_141", vecEntryNamesMissingFromIDE.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromIDE, "\n"), true);

	// popup
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromIDE, "IPL Entries missing from IDE:");
	getIMGF()->getTaskManager()->onTaskUnpause();

	// end
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIPLEntriesNotInIDE");
}
void		CTaskDispatchManager::onRequestOrphanTXDEntriesNotInIDE(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanTXDEntriesNotInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanTXDEntriesNotInIDE", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_TXD_IDE__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanTXDEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_TXD_IDE__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecTXDPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_TXD_IDE__TXD"), "TXD");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecTXDPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanTXDEntriesNotInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_TXD_IDE__TXD", CPathManager::getDirectory(vecTXDPaths[0]));

	vector<string> vecIDEEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, false, true);
	vecIDEEntryNamesWithoutExtension = CStdVector::toUpperCase(vecIDEEntryNamesWithoutExtension);

	vector<string> vecTXDEntryNamesWithoutExtension;
	for (auto strTXDPath : vecTXDPaths)
	{
		CTXDFormat *pTXDFile = CTXDManager::get()->parseViaFile(strTXDPath);
		if (!pTXDFile->doesHaveError())
		{
			vector<string> vecTextureNames = pTXDFile->getTextureNames();
			vecTXDEntryNamesWithoutExtension = CStdVector::combineVectors(vecTXDEntryNamesWithoutExtension, CStdVector::toUpperCase(vecTextureNames));
		}
		pTXDFile->unload();
		delete pTXDFile;
	}
	vecTXDEntryNamesWithoutExtension = CStdVector::removeDuplicates(vecTXDEntryNamesWithoutExtension);

	vector<string> vecEntryNamesMissingFromIDE;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecTXDEntryNamesWithoutExtension.size());
	for (auto strTXDEntryNameWithoutExtension : vecTXDEntryNamesWithoutExtension)
	{
		if (std::find(vecIDEEntryNamesWithoutExtension.begin(), vecIDEEntryNamesWithoutExtension.end(), strTXDEntryNameWithoutExtension) == vecIDEEntryNamesWithoutExtension.end())
		{
			vecEntryNamesMissingFromIDE.push_back(strTXDEntryNameWithoutExtension);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_140", vecEntryNamesMissingFromIDE.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromIDE, "\n"), true);

	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromIDE, "TXD Entries missing from IDE:");
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanTXDEntriesNotInIDE");
}
void		CTaskDispatchManager::onRequestOrphanIDEEntriesNotInIMG(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOrphanIDEEntriesNotInIMG");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInIMG", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("ORPHAN_IDE_IMG__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInIMG", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("ORPHAN_IDE_IMG__IDE", CPathManager::getDirectory(vecPaths[0]));

	vector<string> vecEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecPaths);
	vecEntryNamesWithoutExtension = CStdVector::toUpperCase(vecEntryNamesWithoutExtension);

	vector<string> vecEntryNamesMissingFromIMG;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecEntryNamesWithoutExtension.size());
	for (auto strEntryNameWithoutExtension : vecEntryNamesWithoutExtension)
	{
		CIMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByNameWithoutExtension(strEntryNameWithoutExtension);
		if (pIMGEntry == nullptr)
		{
			vecEntryNamesMissingFromIMG.push_back(strEntryNameWithoutExtension);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_94", vecEntryNamesMissingFromIMG.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_93"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNamesMissingFromIMG, "\n"), true);

	getIMGF()->getTaskManager()->onTaskPause();
	bool bImportEntries = getIMGF()->getPopupGUIManager()->showOrphanEntriesDialog(vecEntryNamesMissingFromIMG, "IDE Entries missing from IMG:", "Import into IMG");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (bImportEntries)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		string strFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_17"), getIMGF()->getLastUsedDirectory("ORPHAN_IDE_IMG__IMPORT"));
		getIMGF()->getTaskManager()->onTaskUnpause();
		if (strFolderPath == "")
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInIMG", true);
			return;
		}
		strFolderPath = CPathManager::addSlashToEnd(strFolderPath);
		getIMGF()->setLastUsedDirectory("ORPHAN_IDE_IMG__IMPORT", strFolderPath);

		uint32 uiImportedFileCount = 0;
		for (auto strEntryNameMissingFromIMG : vecEntryNamesMissingFromIMG)
		{
			string strEntryFilePath = strFolderPath + CFileManager::getFileNameFromNameWithoutExtension(strFolderPath, strEntryNameMissingFromIMG);
			if (CFileManager::doesFileExist(strEntryFilePath))
			{
				getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strEntryFilePath);
				uiImportedFileCount++;
			}
		}

		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_84", uiImportedFileCount, vecEntryNamesMissingFromIMG.size()));

		if (uiImportedFileCount > 0)
		{
			getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
		}
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOrphanIDEEntriesNotInIMG");
}
void		CTaskDispatchManager::onRequestSettings(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSettings");
	getIMGF()->getTaskManager()->onTaskPause();
	bool bSave = getIMGF()->getPopupGUIManager()->showSettingsDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (!bSave)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSettings", true);
		return;
	}

	getIMGF()->getSettingsManager()->reloadSettings();
	
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSettings");
	if (getIMGF()->getSettingsManager()->getSettingBool("NewLanguageApplied"))
	{
		exit(EXIT_SUCCESS);
	}
}
void		CTaskDispatchManager::onRequestReopen(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestReopen");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestReopen", true);
		return;
	}

	string strIMGPath = getIMGF()->getEntryListTab()->getIMGFile()->getFilePath();
	if (onRequestClose2(false) == true)
	{
		// cancelled
		getIMGF()->getTaskManager()->onTaskEnd("onRequestReopen", true);
		return;
	}
	getIMGF()->getIMGEditor()->removeTab(getIMGF()->getEntryListTab());
	openFile(strIMGPath);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestReopen");
}
void		CTaskDispatchManager::onRequestConvertDFFToRWVersion(CRWVersion *pRWVersion)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_ConvertDFF_RWVersion(pRWVersion);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertDFFToRWVersion");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFToRWVersion", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	CDFFConversionDialogData *pDFFConversionDialogData = getIMGF()->getPopupGUIManager()->showDFFConversionDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (!pDFFConversionDialogData->m_bConvert) // cancel button
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFToRWVersion", true);
		delete pDFFConversionDialogData;
		return;
	}

	bool bConvert2DFXFromIIIOrVCToSA = false;
	unordered_map<string, vector<CIDEEntry*>> umapIDEEntriesByModelName;
	vector<CIDEFormat*> veCIDEFormats;
	bool bSelectedDFFsContainIIIOrVC = false;

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFToRWVersion", true);
		delete pDFFConversionDialogData;
		return;
	}
	CIMGEntry *pIMGEntry = nullptr;

	////////////////
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (!CPathManager::isModelExtension(CPathManager::getFileExtension(pIMGEntry->getEntryName())))
		{
			continue;
		}

		if (pIMGEntry != nullptr && (pIMGEntry->getRWVersion()->doesGameUseVersion(PLATFORMED_GAME_PC_GTA_III) || pIMGEntry->getRWVersion()->doesGameUseVersion(PLATFORMED_GAME_PC_GTA_VC)))
		{
			bSelectedDFFsContainIIIOrVC = true;
			break;
		}
	}
	//////////

	if (bSelectedDFFsContainIIIOrVC && pRWVersion->doesGameUseVersion(PLATFORMED_GAME_PC_GTA_SA))
	{
		// The selected DFFs in the active IMG tab contains at least 1 DFF IMG entry with a RW version of III or VC, and the target RW version to convert to is SA.
		vector<uint32> vecExtendedLogLines_MissingObjectIds;
		bool bDidCancel = false;
		bConvert2DFXFromIIIOrVCToSA = getIMGF()->getPopupGUIManager()->showConfirmDialog("Do you want to also convert 2DFX sections in DFF files from GTA III/VC format to GTA SA format? (Requires IDE input)", "Convert 2DFX Too?", bDidCancel);
		if (bDidCancel)
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFToRWVersion", true);
			delete pDFFConversionDialogData;
			return;
		}

		if (bConvert2DFXFromIIIOrVCToSA)
		{
			getIMGF()->getTaskManager()->onTaskPause();
			vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("CONVERT_DFF_RWVERSION_IDE"), "IDE");
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (vecIDEPaths.size() == 0)
			{
				getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFToRWVersion", true);
				return;
			}
			getIMGF()->setLastUsedDirectory("CONVERT_DFF_RWVERSION_IDE", CPathManager::getDirectory(vecIDEPaths[0]));

			for (string strIDEPath : vecIDEPaths)
			{
				CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strIDEPath);
				if (pIDEFile->doesHaveError())
				{
					pIDEFile->unload();
					delete pIDEFile;
					continue;
				}
				veCIDEFormats.push_back(pIDEFile);

				unordered_map<uint32, std::string> umapIDEModelNamesByObjectId;
				for (auto it : pIDEFile->getSectionEntries())
				{
					for (CIDEEntry *pIDEEntry : it.second)
					{
						if (pIDEEntry->getEntryType() == SECTION_LINES_ENTRY_DATA)
						{
							CIDEEntry_Data *pIDEEntry_Data = (CIDEEntry_Data*)pIDEEntry;
							uint32 uiObjectId = pIDEEntry_Data->getObjectId();
							if (uiObjectId != -1)
							{
								string strModelName = pIDEEntry_Data->getModelName();
								if (strModelName != "")
								{
									umapIDEModelNamesByObjectId[uiObjectId] = strModelName;
								}
							}
						}
					}
				}

				for (CIDEEntry_2DFX_Light *pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_2DFX_Light>(IDE_SECTION_2DFX, _2DFX_LIGHT))
				{
					if (umapIDEModelNamesByObjectId.count(pIDEEntry->getObjectId()) == 0)
					{
						vecExtendedLogLines_MissingObjectIds.push_back(pIDEEntry->getObjectId());
					}
					else
					{
						string strIDEModelName = umapIDEModelNamesByObjectId[pIDEEntry->getObjectId()];
						umapIDEEntriesByModelName[CString2::toUpperCase(strIDEModelName)].push_back(pIDEEntry);
					}
				}
				for (CIDEEntry_2DFX_Particle *pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_2DFX_Particle>(IDE_SECTION_2DFX, _2DFX_PARTICLE))
				{
					if (umapIDEModelNamesByObjectId.count(pIDEEntry->getObjectId()) == 0)
					{
						vecExtendedLogLines_MissingObjectIds.push_back(pIDEEntry->getObjectId());
					}
					else
					{
						string strIDEModelName = umapIDEModelNamesByObjectId[pIDEEntry->getObjectId()];
						umapIDEEntriesByModelName[CString2::toUpperCase(strIDEModelName)].push_back(pIDEEntry);
					}
				}
				for (CIDEEntry_2DFX_Ped *pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_2DFX_Ped>(IDE_SECTION_2DFX, _2DFX_PED))
				{
					if (umapIDEModelNamesByObjectId.count(pIDEEntry->getObjectId()) == 0)
					{
						vecExtendedLogLines_MissingObjectIds.push_back(pIDEEntry->getObjectId());
					}
					else
					{
						string strIDEModelName = umapIDEModelNamesByObjectId[pIDEEntry->getObjectId()];
						umapIDEEntriesByModelName[CString2::toUpperCase(strIDEModelName)].push_back(pIDEEntry);
					}
				}
				for (CIDEEntry_2DFX_Unknown1 *pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_2DFX_Unknown1>(IDE_SECTION_2DFX, _2DFX_UNKNOWN_1))
				{
					if (umapIDEModelNamesByObjectId.count(pIDEEntry->getObjectId()) == 0)
					{
						vecExtendedLogLines_MissingObjectIds.push_back(pIDEEntry->getObjectId());
					}
					else
					{
						string strIDEModelName = umapIDEModelNamesByObjectId[pIDEEntry->getObjectId()];
						umapIDEEntriesByModelName[CString2::toUpperCase(strIDEModelName)].push_back(pIDEEntry);
					}
				}
				for (CIDEEntry_2DFX_SunReflection *pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_2DFX_SunReflection>(IDE_SECTION_2DFX, _2DFX_SUN_REFLECTION))
				{
					if (umapIDEModelNamesByObjectId.count(pIDEEntry->getObjectId()) == 0)
					{
						vecExtendedLogLines_MissingObjectIds.push_back(pIDEEntry->getObjectId());
					}
					else
					{
						string strIDEModelName = umapIDEModelNamesByObjectId[pIDEEntry->getObjectId()];
						umapIDEEntriesByModelName[CString2::toUpperCase(strIDEModelName)].push_back(pIDEEntry);
					}
				}

			}
		}

		getIMGF()->getEntryListTab()->log("[Convert 2DFX from IDE (GTA III/VC) to DFF (GTA SA)] IDE 2DFX object IDs entries not having an IDE entry linked by object ID:", true);
		vector<string> vecExtendedLogLines_MissingObjectIds2;
		for (uint32 uiValue : vecExtendedLogLines_MissingObjectIds)
		{
			vecExtendedLogLines_MissingObjectIds2.push_back(CString2::toString(uiValue));
		}
		getIMGF()->getEntryListTab()->log(CString2::join(vecExtendedLogLines_MissingObjectIds2, "\n"), true);
		vecExtendedLogLines_MissingObjectIds.clear();
		vecExtendedLogLines_MissingObjectIds2.clear();
	}

	pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFToRWVersion", true);
		delete pDFFConversionDialogData;
		for (auto pIDEFile : veCIDEFormats)
		{
			pIDEFile->unload();
			delete pIDEFile;
		}
		return;
	}

	pIMGEntry = nullptr;
	vector<string> vecConvertedDFFEntryNames;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (!CPathManager::isModelExtension(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()))))
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		//CDebugger::log("Converting DFF: " + pIMGEntry->m_strFileName);
		string strEntryData = pIMGEntry->getEntryData();
		CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(strEntryData);
		if (pDFFFile->doesHaveError())
		{
			//CDebugger::log("CORRUPT REASON: " + pDFFFile->getCorruptReason());
			pDFFFile->unload();
			delete pDFFFile;
			continue;
		}

		vecConvertedDFFEntryNames.push_back(pIMGEntry->getEntryName());

		pDFFFile->setRWVersion(pRWVersion);

		if (pDFFConversionDialogData->m_ucPrelightningOption == 0) // keep prelightning
		{
		}
		else if (pDFFConversionDialogData->m_ucPrelightningOption == 1) // remove prelightning
		{
			pDFFFile->removePrelightning();
		}
		else if (pDFFConversionDialogData->m_ucPrelightningOption == 2) // adjust prelightning
		{
			if (pDFFConversionDialogData->m_ucAdjustPrelightningOption == 0) // fixed colour
			{
				pDFFFile->setPrelightningColour(
					pDFFConversionDialogData->m_ssAdjustColourValues[0],
					pDFFConversionDialogData->m_ssAdjustColourValues[1],
					pDFFConversionDialogData->m_ssAdjustColourValues[2],
					pDFFConversionDialogData->m_ssAdjustColourValues[3]
				);
			}
			else if (pDFFConversionDialogData->m_ucAdjustPrelightningOption == 1) // colour offset
			{
				pDFFFile->applyPrelightningColourOffset(
					pDFFConversionDialogData->m_ssAdjustColourValues[0],
					pDFFConversionDialogData->m_ssAdjustColourValues[1],
					pDFFConversionDialogData->m_ssAdjustColourValues[2],
					pDFFConversionDialogData->m_ssAdjustColourValues[3]
				);
			}
		}

		if (bConvert2DFXFromIIIOrVCToSA && pIMGEntry->getRWVersion() != nullptr && (pIMGEntry->getRWVersion()->doesGameUseVersion(PLATFORMED_GAME_PC_GTA_III) || pIMGEntry->getRWVersion()->doesGameUseVersion(PLATFORMED_GAME_PC_GTA_VC)))
		{
			// CIDEEntry_2DFX = umapIDEModelNames[modelName]->getSectionsByType(IDE_SECTION_2DFX)[0];

			string strModelNameUpper = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
			int a;
			if (umapIDEEntriesByModelName.count(strModelNameUpper) == 0)
			{
				// Coudn't find DFF model name (from IMG entry name) in IDE OBJS/TOBJ with any corresponding 2DFX entries.
			}
			else
			{
				vector<C2dEffect*> vec2dEffects;
				C2dEffect *p2dEffect;
				for (CIDEEntry *pIDEEntry : umapIDEEntriesByModelName[strModelNameUpper])
				{
					switch (((CIDEEntry_2DFX*)pIDEEntry)->get2DFXType())
					{
					case _2DFX_LIGHT:
					{
						CRWEntry_2dEffect_Light					*pDFFEntry_2dEffect_Light = new CRWEntry_2dEffect_Light;
						CIDEEntry_2DFX_Light					*pIDEEntry_2dEffect_Light = (CIDEEntry_2DFX_Light*) pIDEEntry;
						p2dEffect = pDFFEntry_2dEffect_Light;

						uint32 uiPackedColour =
							(pIDEEntry_2dEffect_Light->getColour().x << 24) |
							(pIDEEntry_2dEffect_Light->getColour().y << 16) |
							(pIDEEntry_2dEffect_Light->getColour().z << 8) |
							0xFF;

						uint32 uiNewCoronaShowMode = 0;
						uint8 ucFlags1 = 0;
						uint32 ucFlags2 = 0;
						switch (pIDEEntry_2dEffect_Light->getFlare())
						{
						case 0: // constantly lit
							uiNewCoronaShowMode = 0;
							ucFlags1 |= 32 | 64;
							break;
						case 1: // constantly lit at night
							uiNewCoronaShowMode = 0;
							ucFlags1 |= 64;
							break;


						case 2: // occasional flicker all time
						case 10: // random flashing
						case 4: // ~1 second flashes
						case 6: // ~2 seconds flashes
						case 8: // ~3 seconds flashes
							uiNewCoronaShowMode = 1;
							ucFlags1 |= 32 | 64;
							break;
						case 3: // occasional flicker at night
						case 5: // ~1 second flashes at night
						case 7: // ~2 seconds flashes at night
						case 9: // ~3 seconds flashes at night
						case 11: // random flicker at night
							uiNewCoronaShowMode = 1;
							ucFlags1 |= 64;
							break;


						case 12: // traffic light
							uiNewCoronaShowMode = 7;
							break;
						}

						uint32 ucFogType = 0; // 0, 1 or 2 (0 = none)
						if (pIDEEntry_2dEffect_Light->getIDEFlag() & 2)
						{
							ucFogType = 1;
							ucFlags1 |= 2;
						}
						if (pIDEEntry_2dEffect_Light->getIDEFlag() & 4)
						{
							ucFogType = 2;
							ucFlags1 |= 4;
						}

						bool bUpdateZPosAboveGround = true;
						if (pIDEEntry_2dEffect_Light->getIDEFlag() & 1) // bit 0 (value 1) = disable z-test for corona
						{
							bUpdateZPosAboveGround = false;
						}
						ucFlags2 |= bUpdateZPosAboveGround ? 4 : 0;

						Vec3f vecPosition = { pIDEEntry_2dEffect_Light->getPosition().x, pIDEEntry_2dEffect_Light->getPosition().y, pIDEEntry_2dEffect_Light->getPosition().z };

						pDFFEntry_2dEffect_Light->set2DFXType(_2DFX_LIGHT);
						pDFFEntry_2dEffect_Light->setDataSize(76);
						pDFFEntry_2dEffect_Light->setPosition(vecPosition);

						Vec3u8 vecLookDirection;
						vecLookDirection.x = 0;
						vecLookDirection.y = 0;
						vecLookDirection.z = 0;

						Vec2u8 vecPadding;
						vecPadding.x = 0;
						vecPadding.y = 0;

						pDFFEntry_2dEffect_Light->setCoronaFarClip(pIDEEntry_2dEffect_Light->getViewDistance());
						pDFFEntry_2dEffect_Light->setCoronaSize(pIDEEntry_2dEffect_Light->getCoronaSize());
						pDFFEntry_2dEffect_Light->setPointlightRange(pIDEEntry_2dEffect_Light->getOuterRange());
						pDFFEntry_2dEffect_Light->setShadowSize(1.0f); // ?
						pDFFEntry_2dEffect_Light->setCoronaTexName(pIDEEntry_2dEffect_Light->getCoronaTexture());
						pDFFEntry_2dEffect_Light->setShadowTexName(pIDEEntry_2dEffect_Light->getShadowTexture());
						pDFFEntry_2dEffect_Light->setCoronaEnableReflection(1); // ?
						pDFFEntry_2dEffect_Light->setCoronaFlareType(pIDEEntry_2dEffect_Light->getFlare());
						pDFFEntry_2dEffect_Light->setCoronaShowMode(uiNewCoronaShowMode);
						pDFFEntry_2dEffect_Light->setFlags1(ucFlags1); //pIDEEntry_2dEffect_Light->m_uiIDEFlag; // flags need converting..
						pDFFEntry_2dEffect_Light->setFlags2(ucFlags2); //pIDEEntry_2dEffect_Light->m_uiIDEFlag; // flags need converting..
						pDFFEntry_2dEffect_Light->setLookDirection(vecLookDirection); // only used if m_uiDataSize == 80, instead of 76
						pDFFEntry_2dEffect_Light->setPadding(vecPadding);
						pDFFEntry_2dEffect_Light->setShadowColorMultiplier(40); // ?
						pDFFEntry_2dEffect_Light->setShadowZDistance(10); // guessed //pIDEEntry_2dEffect_Light->m_fViewDistance > 255.0f ? 255.0f : (uint8) pIDEEntry_2dEffect_Light->m_fViewDistance; // is this correct?
						pDFFEntry_2dEffect_Light->setColor(uiPackedColour);
						break;
					}
					case _2DFX_PARTICLE:
					{
						CRWEntry_2dEffect_ParticleEffect		*pDFFEntry_2dEffect_Particle = new CRWEntry_2dEffect_ParticleEffect;
						CIDEEntry_2DFX_Particle					*pIDEEntry_2dEffect_Particle = (CIDEEntry_2DFX_Particle*)pIDEEntry;
						p2dEffect = pDFFEntry_2dEffect_Particle;

						Vec3f vecPosition = { pIDEEntry_2dEffect_Particle->getPosition().x, pIDEEntry_2dEffect_Particle->getPosition().y, pIDEEntry_2dEffect_Particle->getPosition().z };

						pDFFEntry_2dEffect_Particle->set2DFXType(_2DFX_PARTICLE);
						pDFFEntry_2dEffect_Particle->setDataSize(24);
						pDFFEntry_2dEffect_Particle->setPosition(vecPosition);

						//pDFFEntry_2dEffect_Particle->setParticleEffectName(pIDEEntry_2dEffect_Particle->getParticleType()); // needs convert from ID to string.. // todo
						break;
					}
					case _2DFX_PED:
					{
						CRWEntry_2dEffect_PedAttractor			*pDFFEntry_2DEffect_Ped = new CRWEntry_2dEffect_PedAttractor;
						CIDEEntry_2DFX_Ped						*pIDEEntry_2dEffect_Ped = (CIDEEntry_2DFX_Ped*)pIDEEntry;
						p2dEffect = pDFFEntry_2DEffect_Ped;

						Vec3f vecPosition = { pIDEEntry_2dEffect_Ped->getPosition().x, pIDEEntry_2dEffect_Ped->getPosition().y, pIDEEntry_2dEffect_Ped->getPosition().z };

						pDFFEntry_2DEffect_Ped->set2DFXType(_2DFX_PED_ATTRACTOR);
						pDFFEntry_2DEffect_Ped->setDataSize(56);
						pDFFEntry_2DEffect_Ped->setPosition(vecPosition);

						string strExternalScriptName = "";
						Vec3f
							vecRotation1 = { pIDEEntry_2dEffect_Ped->getPedRotation().x, pIDEEntry_2dEffect_Ped->getPedRotation().y, pIDEEntry_2dEffect_Ped->getPedRotation().z },
							vecRotation2 = { 0.0f, 0.0f, 0.0f },
							vecRotation3 = { 0.0f, 0.0f, 0.0f };

						pDFFEntry_2DEffect_Ped->setPedExistingProbability(pIDEEntry_2dEffect_Ped->getBehaviour()); // is this correct?
						pDFFEntry_2DEffect_Ped->setType(0); // ?
						pDFFEntry_2DEffect_Ped->setExternalScriptName(strExternalScriptName); // ?
						pDFFEntry_2DEffect_Ped->setNotUsed1(0);
						pDFFEntry_2DEffect_Ped->setNotUsed2(0);
						pDFFEntry_2DEffect_Ped->setUnknown1(0);
						pDFFEntry_2DEffect_Ped->setUnknown2(0);
						pDFFEntry_2DEffect_Ped->setRotation(0, vecRotation1);
						pDFFEntry_2DEffect_Ped->setRotation(1, vecRotation2);
						pDFFEntry_2DEffect_Ped->setRotation(2, vecRotation3);
						break;
					}
					case _2DFX_UNKNOWN_1:
						continue;
					case _2DFX_SUN_REFLECTION:
					{
						CRWEntry_2dEffect_SunGlare						*pDFFEntry_2DEffect_SunGlare = new CRWEntry_2dEffect_SunGlare;
						CIDEEntry_2DFX_SunReflection					*pIDEEntry_2dEffect_SunGlare = (CIDEEntry_2DFX_SunReflection*)pIDEEntry;
						p2dEffect = pDFFEntry_2DEffect_SunGlare;

						Vec3f vecPosition = { pIDEEntry_2dEffect_SunGlare->getPosition().x, pIDEEntry_2dEffect_SunGlare->getPosition().y, pIDEEntry_2dEffect_SunGlare->getPosition().z };

						pDFFEntry_2DEffect_SunGlare->set2DFXType(_2DFX_SUN_GLARE);
						pDFFEntry_2DEffect_SunGlare->setDataSize(0);
						pDFFEntry_2DEffect_SunGlare->setPosition(vecPosition);
						break;
					}
					default:
						continue;
					}
					vec2dEffects.push_back(p2dEffect);
				}
				pDFFFile->set2dEffects(vec2dEffects);
			}
		}

		string strFileData = pDFFFile->storeViaMemory();
		pDFFFile->unload();
		delete pDFFFile;

		pIMGEntry->setEntrySize(strFileData.length());
		pIMGEntry->setRWVersion(pRWVersion);
		
		pIMGEntry->setEntryData(strFileData);

		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}
	
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_95", vecConvertedDFFEntryNames.size(), (pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").c_str()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_96"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecConvertedDFFEntryNames, "\n"), true);

	if (pIMGEntry != nullptr)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}

	getIMGF()->getEntryListTab()->checkForUnknownRWVersionEntries();

	delete pDFFConversionDialogData;
	for (auto pIDEFile : veCIDEFormats)
	{
		pIDEFile->unload();
		delete pIDEFile;
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFToRWVersion");
	*/
}
void		CTaskDispatchManager::onRequestMissingTextures(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestMissingTextures");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMissingTextures", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMissingTextures", true);
		return;
	}

	vector<CIMGEntry*> vecSelectedDFFs;
	vector<string> vecSelectedDFFsFilenames;
	CIMGEntry *pIMGEntry = nullptr;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		getIMGF()->getTaskManager()->onTaskProgressTick();
		if (!CPathManager::isModelExtension(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()))))
		{
			continue;
		}

		vecSelectedDFFs.push_back(pIMGEntry);
		vecSelectedDFFsFilenames.push_back(pIMGEntry->getEntryName());
	}
	if (pIMGEntry == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_38"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_38"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMissingTextures", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSING_TEXTURES_IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMissingTextures", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MISSING_TEXTURES_IDE", CPathManager::getDirectory(vecPaths[0]));

	vector<string> vecTextureNames;
	for (auto strPath : vecPaths)
	{
		CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strPath);
		if(!pIDEFile->doesHaveError())
		{
			vecTextureNames = CStdVector::combineVectors(vecTextureNames, pIDEFile->getTXDNamesFromModelNames(vecSelectedDFFsFilenames));
		}
		pIDEFile->unload();
		delete pIDEFile;
	}

	vector<string> vecDFFTexturesMissingFromTXD;
	for (uint32 i = 0; i < vecSelectedDFFs.size(); i++)
	{
		CIMGEntry *pIMGEntry2 = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByNameWithoutExtension(vecTextureNames[i]);
		string strTXDContent;
		if (pIMGEntry2 == nullptr)
		{
			getIMGF()->getTaskManager()->onTaskPause();
			CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_39", vecSelectedDFFsFilenames[i]), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_39"), MB_OK);
			vector<string> vecPaths2 = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSING_TEXTURES_TXD"), "TXD", false);
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (vecPaths2.size() == 0)
			{
				getIMGF()->getTaskManager()->onTaskEnd("onRequestMissingTextures", true);
				return;
			}
			getIMGF()->setLastUsedDirectory("MISSING_TEXTURES_TXD", CPathManager::getDirectory(vecPaths2[0]));

			strTXDContent = CFileManager::getFileContent(vecPaths2[0]);
		}
		else
		{
			strTXDContent = pIMGEntry2->getEntryData();
		}

		string strDFFContent = vecSelectedDFFs[i]->getEntryData();

		CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(strDFFContent);
		vector<string> vecDFFTextureNames;
		if(!pDFFFile->doesHaveError())
		{
			vecDFFTextureNames = pDFFFile->getTextureNames();
		}
		pDFFFile->unload();
		delete pDFFFile;

		CTXDFormat *pTXDFile = CTXDManager::get()->parseViaMemory(strTXDContent);
		vector<string> vecTXDTextureNames;
		if(!pTXDFile->doesHaveError())
		{
			vecTXDTextureNames = pTXDFile->getTextureNames();
		}
		pTXDFile->unload();
		delete pTXDFile;

		vecTXDTextureNames = CStdVector::toUpperCase(vecTXDTextureNames);
		for (auto strDFFTexture : vecDFFTextureNames)
		{
			if (std::find(vecTXDTextureNames.begin(), vecTXDTextureNames.end(), CString2::toUpperCase(strDFFTexture)) == vecTXDTextureNames.end())
			{
				vecDFFTexturesMissingFromTXD.push_back(strDFFTexture);
			}
		}
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_97", vecDFFTexturesMissingFromTXD.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_98"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecDFFTexturesMissingFromTXD, "\n"), true);

	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showListViewDialog("Missing Textures", "Textures missing:", "Texture Name", vecDFFTexturesMissingFromTXD, CLocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_4_InitialFilename", CPathManager::replaceFileExtension(CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()), "txt").c_str()), "MISSINGTEXTURES");
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestMissingTextures");
	*/
}
bool		CTaskDispatchManager::onRequestClose2(bool bCloseAll)
{
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_Close2_CloseAll(bCloseAll);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestClose2");
	string strText = "";
	if (bCloseAll)
	{
		uint32 uiModifiedSinceRebuildCount = 0;
		for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
		{
			if (((CIMGEditorTab*)pEditorTab)->getIMGModifiedSinceRebuild())
			{
				uiModifiedSinceRebuildCount++;
			}
		}
		if (uiModifiedSinceRebuildCount > 0)
		{
			strText = CLocalizationManager::get()->getTranslatedFormattedText("Window_Confirm_3_Message", uiModifiedSinceRebuildCount);
		}
	}
	else
	{
		if (getIMGF()->getEntryListTab()->getIMGModifiedSinceRebuild())
		{
			strText = CLocalizationManager::get()->getTranslatedFormattedText("Window_Confirm_4_Message", CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str());
		}
	}

	if (strText == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2", true);
		return false;
	}

	bool bDidCancel = false;
	getIMGF()->getTaskManager()->onTaskPause();
	bool bResult = getIMGF()->getPopupGUIManager()->showConfirmDialog(strText, CLocalizationManager::get()->getTranslatedText("Window_Confirm_3_Title"), bDidCancel);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (bDidCancel)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2", true);
		return true;
	}
	if (!bResult)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2", true);
		return false;
	}

	if (bCloseAll)
	{
		for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
		{
			if (((CIMGEditorTab*)pEditorTab)->getIMGModifiedSinceRebuild())
			{
				((CIMGEditorTab*)pEditorTab)->rebuild();
			}
		}
	}
	else
	{
		getIMGF()->getEntryListTab()->rebuild();
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestClose2");
	return true;
}
void		CTaskDispatchManager::onRequestReplaceAllFromFolder(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestReplaceAllFromFolder");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestReplaceAllFromFolder", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_14"), getIMGF()->getLastUsedDirectory("REPLACE_ALL_FOLDER"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestReplaceAllFromFolder", true);
		return;
	}
	strFolderPath = CPathManager::addSlashToEnd(strFolderPath);
	getIMGF()->setLastUsedDirectory("REPLACE_ALL_FOLDER", strFolderPath);

	vector<string> vecFileNames = CFileManager::getFileNames(strFolderPath);
	vector<string> vecFilePaths;
	for (uint32 i = 0; i < vecFileNames.size(); i++)
	{
		vecFilePaths[i] = strFolderPath + vecFileNames[i];
	}

	vector<string> vecUniqueFilePaths = CPathManager::getUniqueFilePaths(vecFilePaths, getIMGF()->getEntryListTab()->getIMGFile()->getEntryNames());
	vector<string> vecReplaceFilePaths = CStdVector::getUniqueEntries(vecFilePaths, vecUniqueFilePaths);
	uint32 uiReplaceEntryCount = vecReplaceFilePaths.size();

	bool bOverwriteFiles = false;
	if (getIMGF()->getSettingsManager()->getSettingBool("AskBeforeOverwritingFiles"))
	{
		getIMGF()->getTaskManager()->onTaskPause();
		bOverwriteFiles = getIMGF()->getPopupGUIManager()->showConfirmDialog(CLocalizationManager::get()->getTranslatedFormattedText("Window_Confirm_2_Message", uiReplaceEntryCount), CLocalizationManager::get()->getTranslatedText("Window_Confirm_2_Title"));
		getIMGF()->getTaskManager()->onTaskUnpause();

		if (!bOverwriteFiles)
		{
			vecFilePaths = vecUniqueFilePaths;
		}
	}
	else
	{
		//vector<string> vecA = CStdVector::getUniqueEntries(getIMGF()->getEntryListTab()->getIMGFile()->getEntryNamesUpper(), CPathManager::getFileNamesFromFilePaths(vecPaths));

		vector<string> vecNewReplacedFilePaths;
		for (auto strFilePath : vecReplaceFilePaths)
		{
			bool bReplaceEntry = true;
			CIMGEntry *pIMGEntry = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByName(CPathManager::getFileName(strFilePath));

			uint32
				uiExistingEntryFileCreationDate = pIMGEntry->getFileCreationDate(),
				uiNewEntryFileCreationDate = CFileManager::getFileCreationDate(strFilePath);

			if (uiExistingEntryFileCreationDate < uiNewEntryFileCreationDate)
			{
				// the existing entry is older than the new entry

				if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteOlderFiles"))
				{
					bReplaceEntry = true;
				}
				else
				{
					bReplaceEntry = false;
				}
			}
			else if (uiExistingEntryFileCreationDate > uiNewEntryFileCreationDate)
			{
				// the existing entry is newer than the new entry

				if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteNewerFiles"))
				{
					bReplaceEntry = true;
				}
				else
				{
					bReplaceEntry = false;
				}
			}

			if (pIMGEntry->isProtectedEntry())
			{
				// the entry is protected

				if (getIMGF()->getSettingsManager()->getSettingBool("OverwriteProtectedFiles"))
				{
					bReplaceEntry = true;
				}
				else
				{
					bReplaceEntry = false;
				}
			}

			if (bReplaceEntry)
			{
				vecNewReplacedFilePaths.push_back(strFilePath);
			}
		}
		vecFilePaths = CStdVector::combineVectors(vecUniqueFilePaths, vecNewReplacedFilePaths);
	}

	vector<string> vecReplacedEntryNames;
	getIMGF()->getEntryListTab()->replace(vecFilePaths, vecReplacedEntryNames);

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("ReplacedEntries", vecReplacedEntryNames.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("EntriesForReplace"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecReplacedEntryNames, "\n"), true);

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestReplaceAllFromFolder");
}
void		CTaskDispatchManager::onRequestExportAllEntriesFromAllTabs(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportAllEntriesFromAllTabs");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportAllEntriesFromAllTabs", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORT_ALL_ALL"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportAllEntriesFromAllTabs", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_ALL_ALL", strPath);

	uint32 uiTotalEntryCount = 0;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		uiTotalEntryCount += ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntryCount();
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiTotalEntryCount);

	vector<string> vecIMGPaths;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		vecIMGPaths.push_back(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath());

		((CIMGEditorTab*)pEditorTab)->getIMGFile()->exportMultiple(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntries(), strPath);
		//pEditorTab->log("Exported all " + CString2::toString(pEditorTab->getIMGFile()->m_vecEntries.size()) + " entr" + (pEditorTab->getIMGFile()->m_vecEntries.size() == 1 ? "y" : "ies") + ".");
	}

	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedFormattedText("LogAllTabs_6", uiTotalEntryCount, getIMGF()->getIMGEditor()->getTabs().getEntryCount()));
	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedText("LogAllTabs_7"), true);
	getIMGF()->getIMGEditor()->logAllTabs(CString2::join(vecIMGPaths, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportAllEntriesFromAllTabs");
}
void		CTaskDispatchManager::onRequestExportEntriesViaIDEFileFromAllTabs(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportEntriesViaIDEFileFromAllTabs");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaIDEFileFromAllTabs", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("EXPORT_IDE_ALL__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause(); 
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaIDEFileFromAllTabs", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("EXPORT_IDE_ALL__IDE", CPathManager::getDirectory(vecPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORT_IDE_ALL__DEST"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaIDEFileFromAllTabs", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_IDE_ALL__DEST", strPath);

	vector<string> vecEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecPaths);
	vecEntryNamesWithoutExtension = CStdVector::toUpperCase(vecEntryNamesWithoutExtension);
	
	uint32 uiTotalEntryCount = 0;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		uiTotalEntryCount += ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntryCount();
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiTotalEntryCount);

	uint32 uiTotalEntryExportedCount = 0;
	vector<string> vecIMGPaths;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		vecIMGPaths.push_back(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath());

		vector<CIMGEntry*> vecIMGEntries;
		for (auto pIMGEntry : ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntries())
		{
			string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
			auto it = std::find(vecEntryNamesWithoutExtension.begin(), vecEntryNamesWithoutExtension.end(), strEntryNameWithoutExtension);
			if (it != vecEntryNamesWithoutExtension.end())
			{
				uiTotalEntryExportedCount++;
				vecIMGEntries.push_back(pIMGEntry);
			}

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}

		((CIMGEditorTab*)pEditorTab)->getIMGFile()->exportMultiple(vecIMGEntries, strPath);
	}

	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedFormattedText("Log_108", uiTotalEntryExportedCount, getIMGF()->getIMGEditor()->getTabs().getEntryCount()));
	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedText("LogAllTabs_7"), true);
	getIMGF()->getIMGEditor()->logAllTabs(CString2::join(vecIMGPaths, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaIDEFileFromAllTabs");
}
void		CTaskDispatchManager::onRequestExportEntriesViaTextLinesFromAllTabs(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportEntriesViaTextLinesFromAllTabs");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaTextLinesFromAllTabs", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextArea_3_Message"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strData == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaTextLinesFromAllTabs", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORT_TEXTLINES_ALL"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaTextLinesFromAllTabs", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_TEXTLINES_ALL", strPath);

	vector<string> vecEntryNames;
	vector<string> vecLines = CString2::split(strData, "\r\n");
	for (auto strLine : vecLines)
	{
		strLine = CString2::trim(strLine);
		if (strLine == "")
		{
			continue;
		}

		vecEntryNames.push_back(strLine);
	}
	vecEntryNames = CStdVector::toUpperCase(vecEntryNames);

	uint32 uiTotalEntryCount = 0;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		uiTotalEntryCount += ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntryCount();
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiTotalEntryCount);

	uint32 uiTotalEntryExportedCount = 0;
	vector<string> vecIMGPaths;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		vecIMGPaths.push_back(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath());

		vector<CIMGEntry*> vecIMGEntries;
		for (auto pIMGEntry : ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntries())
		{
			string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
			auto it = std::find(vecEntryNames.begin(), vecEntryNames.end(), strEntryNameWithoutExtension);
			if (it != vecEntryNames.end())
			{
				uiTotalEntryExportedCount++;
				vecIMGEntries.push_back(pIMGEntry);
			}

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}

		((CIMGEditorTab*)pEditorTab)->getIMGFile()->exportMultiple(vecIMGEntries, strPath);
	}

	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedFormattedText("LogAllTabs_8", uiTotalEntryExportedCount, getIMGF()->getIMGEditor()->getTabs().getEntryCount()));
	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedText("LogAllTabs_7"), true);
	getIMGF()->getIMGEditor()->logAllTabs(CString2::join(vecIMGPaths, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportEntriesViaTextLinesFromAllTabs");
}
void		CTaskDispatchManager::onRequestImportViaFolder(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestImportViaFolder");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaFolder", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_15"), getIMGF()->getLastUsedDirectory("IMPORT_FOLDER"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaFolder", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("IMPORT_FOLDER", strPath);

	vector<string> vecFileNames = CFileManager::getFileNames(strPath);
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecFileNames.size());
	for (auto strFileName : vecFileNames)
	{
		getIMGF()->getEntryListTab()->addOrReplaceEntryViaFileAndSettings(strPath + strFileName);
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_99", vecFileNames.size(), CPathManager::getFolderName(strPath).c_str()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_100"), true);
	getIMGF()->getEntryListTab()->log(strPath, true);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("EntriesForImport"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecFileNames, "\n"), true);

	if (vecFileNames.size() > 0)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestImportViaFolder");
}
void		CTaskDispatchManager::onRequestDuplicateEntries(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestDuplicateEntries");

	// show window
	getIMGF()->getTaskManager()->onTaskPause();
	CDuplicateEntriesDialogData *pDuplicateEntriesDialogData = getIMGF()->getPopupGUIManager()->showDuplicateEntriesDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (!pDuplicateEntriesDialogData->m_bCheck)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestDuplicateEntries", true);
		return;
	}

	// choose entries
	vector<CIMGFormat*> veCIMGFormats;
	if (pDuplicateEntriesDialogData->m_ucEntriesType == 0) // all entries in active tab
	{
		if (getIMGF()->getEntryListTab() == nullptr)
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestDuplicateEntries", true);
			return;
		}

		veCIMGFormats.push_back(getIMGF()->getEntryListTab()->getIMGFile());
	}
	else if (pDuplicateEntriesDialogData->m_ucEntriesType == 1) // selected entries in active tab
	{
		if (getIMGF()->getEntryListTab() == nullptr)
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestDuplicateEntries", true);
			return;
		}

		veCIMGFormats.push_back(getIMGF()->getEntryListTab()->getIMGFile());
	}
	else if (pDuplicateEntriesDialogData->m_ucEntriesType == 2) // all entries in all tabs
	{
		if (getIMGF()->getEntryListTab() == nullptr)
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestDuplicateEntries", true);
			return;
		}

		veCIMGFormats = getIMGF()->getIMGEditor()->getAllMainWindowTabsIMGFiles();
	}
	else if (pDuplicateEntriesDialogData->m_ucEntriesType == 3) // DAT file
	{
		ePlatformedGame ePlatformedGameValue = PLATFORMED_GAME_UNKNOWN;
		switch (pDuplicateEntriesDialogData->m_uiDATGameIndex)
		{
		case 0: // GTA III
			ePlatformedGameValue = PLATFORMED_GAME_PC_GTA_III;
			break;
		case 1: // GTA VC
			ePlatformedGameValue = PLATFORMED_GAME_PC_GTA_VC;
			break;
		case 2: // GTA SA
			ePlatformedGameValue = PLATFORMED_GAME_PC_GTA_SA;
			break;
		case 3: // SOL
			ePlatformedGameValue = PLATFORMED_GAME_PC_SOL;
			break;
		case 4: // Other
			break;
		}
		string strDATPath = pDuplicateEntriesDialogData->m_strDATGameDirectoryPath + CDATLoaderManager::getDefaultGameDATSubPath(ePlatformedGameValue);

		CDATLoaderFormat *pDATFile = CDATLoaderManager::get()->parseViaFile(strDATPath);
		if (!pDATFile->doesHaveError())
		{
			veCIMGFormats = pDATFile->parseIMGFiles(pDuplicateEntriesDialogData->m_strDATGameDirectoryPath);
		}
		pDATFile->unload();
		delete pDATFile;

		vector<string> vecGameIMGPaths = CIMGManager::getDefaultGameIMGSubPaths(ePlatformedGameValue);

		for (auto strIMGRelativePath : vecGameIMGPaths)
		{
			string strIMGPath = pDuplicateEntriesDialogData->m_strDATGameDirectoryPath + strIMGRelativePath;
			if (CFileManager::doesFileExist(strIMGPath))
			{
				CIMGFormat *pIMGFile = CIMGManager::get()->parseViaFile(strIMGPath);
				if(!pIMGFile->doesHaveError())
				{
					veCIMGFormats.push_back(pIMGFile);
				}
			}
		}
	}

	// max progress tick
	uint32 uiTickCount = 0;
	for (auto pIMGFile : veCIMGFormats)
	{
		uiTickCount += pIMGFile->getEntryCount();
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiTickCount);

	// fetch selected entries
	vector<CIMGEntry*> vecSelectedIMGEntries;
	if (pDuplicateEntriesDialogData->m_ucEntriesType == 1) // selected entries
	{
		vecSelectedIMGEntries = getIMGF()->getEntryListTab()->getSelectedEntries();
	}

	// find duplicate entries
	unordered_map < string, vector<CIMGEntry*> >
		umapIMGEntries;
	vector<string>
		vecEntryDuplicateNames;
	for (auto pIMGFile : veCIMGFormats)
	{
		// choose IMG entries
		vector<CIMGEntry*> vecIMGEntries;
		if (pDuplicateEntriesDialogData->m_ucEntriesType == 1) // selected entries
		{
			vecIMGEntries = vecSelectedIMGEntries;
		}
		else
		{
			vecIMGEntries = pIMGFile->getEntries();
		}

		// store IMG entry name for checking
		for (auto pIMGEntry : vecIMGEntries)
		{
			umapIMGEntries[CString2::toUpperCase(pIMGEntry->getEntryName())].push_back(pIMGEntry);

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}
	for (auto it : umapIMGEntries)
	{
		vector<CIMGEntry*>& vecEntries = it.second;
		if (vecEntries.size() > 1)
		{
			vector<string> vecEntryIMGFileNames;
			for (auto pIMGEntry : vecEntries)
			{
				vecEntryIMGFileNames.push_back(CPathManager::getFileName(pIMGEntry->getIMGFile()->getFilePath()));
			}
			vecEntryDuplicateNames.push_back(vecEntries[0]->getEntryName() + " (" + CString2::join(vecEntryIMGFileNames, ", ") + ")");
		}
	}

	umapIMGEntries.clear();

	// log
	if (getIMGF()->getEntryListTab())
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_102", vecEntryDuplicateNames.size()));
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_103"), true);
		getIMGF()->getEntryListTab()->log(CString2::join(vecEntryDuplicateNames, "\n"), true);
	}

	// results window
	string strSaveFileName;
	if (pDuplicateEntriesDialogData->m_ucEntriesType == 3) // DAT file
	{
		strSaveFileName = CLocalizationManager::get()->getTranslatedText("SaveFilePopup_5_InitialFilename");
	}
	else
	{
		strSaveFileName = CLocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_6_InitialFilename", CPathManager::replaceFileExtension(CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()), "txt").c_str());
	}
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showListViewDialog(CLocalizationManager::get()->getTranslatedText("DuplicateEntries"), "Showing " + CString2::toString(vecEntryDuplicateNames.size()) + " duplicate entr" + (vecEntryDuplicateNames.size() == 1 ? "y" : "ies") + ".", CLocalizationManager::get()->getTranslatedText("Window_OrphanEntries_EntryName"), vecEntryDuplicateNames, strSaveFileName, "DUPLICATEENTRIES");
	getIMGF()->getTaskManager()->onTaskUnpause();

	// clean up
	vecEntryDuplicateNames.clear();
	if (pDuplicateEntriesDialogData->m_ucEntriesType == 3) // DAT file
	{
		for (auto pIMGFile : veCIMGFormats)
		{
			pIMGFile->unload();
			delete pIMGFile;
		}
	}
	delete pDuplicateEntriesDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestDuplicateEntries");
}
void		CTaskDispatchManager::onRequestExportAllEntriesFromAllTabsIntoMultipleFolders(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportAllEntriesFromAllTabsIntoMultipleFolders");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportAllEntriesFromAllTabsIntoMultipleFolders", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_16"), getIMGF()->getLastUsedDirectory("EXPORT_ALL_FOLDERS"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportAllEntriesFromAllTabsIntoMultipleFolders", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_ALL_FOLDERS", strPath);

	uint32 uiTotalEntryCount = 0;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		uiTotalEntryCount += ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntryCount();
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(uiTotalEntryCount);

	vector<string> vecIMGPaths;
	for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
	{
		vecIMGPaths.push_back(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath());

		((CIMGEditorTab*)pEditorTab)->getIMGFile()->exportMultiple(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntries(), strPath + CPathManager::getFileName(((CIMGEditorTab*)pEditorTab)->getIMGFile()->getFilePath()) + "/");
	}

	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedFormattedText("LogAllTabs_9", uiTotalEntryCount, getIMGF()->getIMGEditor()->getTabs().getEntries()));
	getIMGF()->getIMGEditor()->logAllTabs(CLocalizationManager::get()->getTranslatedText("LogAllTabs_7"), true);
	getIMGF()->getIMGEditor()->logAllTabs(CString2::join(vecIMGPaths, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportAllEntriesFromAllTabsIntoMultipleFolders");
}
void		CTaskDispatchManager::onRequestOpenLast(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOpenLast");
	uint32 uiRecentlyOpenedCount = CRegistryManager::getSoftwareValueInt("IMGF\\RecentlyOpened", "Count");
	if (uiRecentlyOpenedCount > 0)
	{
		string strIMGPath = CRegistryManager::getSoftwareValueString("IMGF\\RecentlyOpened", "Data_" + CString2::toString(uiRecentlyOpenedCount));
		openFile(strIMGPath);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOpenLast");
}
void		CTaskDispatchManager::onRequestConvertTXDToGame(ePlatformedGame ePlatformedGame)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_ConvertTXD_Game(ePlatformedGame);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertTXDToGame");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToGame", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToGame", true);
		return;
	}

	CIMGEntry *pIMGEntry = nullptr;
	uint32 uiConvertedTXDCount = 0;
	vector<string>
		vecConvertedTXDNames,
		vecMipmapsRemoved;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) != "TXD")
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CTXDFormat *pTXDFile = CTXDManager::get()->parseViaMemory(pIMGEntry->getEntryData());
		if (pTXDFile->doesHaveError())
		{
			pTXDFile->unload();
			delete pTXDFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}
		uiConvertedTXDCount++;
		vecConvertedTXDNames.push_back(pIMGEntry->getEntryName());

		pTXDFile->convertToGame(ePlatformedGame, vecMipmapsRemoved);
		CRWVersion *pRWVersion = pTXDFile->getRWVersion();
		string strFileData = pTXDFile->serializeViaMemory();
		pTXDFile->unload();
		delete pTXDFile;
		
		pIMGEntry->setEntrySize(strFileData.length());
		pIMGEntry->setRWVersion(pRWVersion);
		
		pIMGEntry->setEntryData(strFileData);

		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
		
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_104", uiConvertedTXDCount, CRWManager::get()->getGameName(ePlatformedGame).c_str(), vecMipmapsRemoved.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_105"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecConvertedTXDNames, "\n"), true);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("MipmapsRemoved"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecMipmapsRemoved, "\n"), true);

	if (pIMGEntry != nullptr)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToGame");
	*/
}
void		CTaskDispatchManager::onRequestConvertTXDToRWVersion(CRWVersion *pRWVersion)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_ConvertTXD_RWVersion(pRWVersion);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertTXDToRWVersion");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToRWVersion", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToRWVersion", true);
		return;
	}

	CIMGEntry *pIMGEntry = nullptr;
	vector<string> vecConvertedTXDEntryNames;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) != "TXD")
		{
			continue;
		}

		string strEntryData = pIMGEntry->getEntryData();
		CTXDFormat *pTXDFile = CTXDManager::get()->parseViaMemory(strEntryData);
		if (pTXDFile->doesHaveError())
		{
			pTXDFile->unload();
			delete pTXDFile;
			continue;
		}

		vecConvertedTXDEntryNames.push_back(pIMGEntry->getEntryName());

		pTXDFile->setRWVersion(pRWVersion);
		string strFileData = pTXDFile->serializeViaMemory();
		uint32 uiFileSize = strFileData.length();
		pTXDFile->unload();
		delete pTXDFile;

		pIMGEntry->setEntrySize(uiFileSize);
		pIMGEntry->setRWVersion(pRWVersion);
		
		pIMGEntry->setEntryData(strFileData);
		
		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_107", vecConvertedTXDEntryNames.size(), (pRWVersion->getVersionName() + " (" + CLocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").c_str()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_105"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecConvertedTXDEntryNames, "\n"), true);

	if (pIMGEntry != nullptr)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToRWVersion");
	*/
}
void		CTaskDispatchManager::onRequestDump(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestDump");
	getIMGF()->getDumpManager()->process();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestDump");
}
void		CTaskDispatchManager::onRequestSessionManager(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSessionManager");
	CSessionManagerDialogData *pSessionManagerDialogData = nullptr;
	bool bReopenWindow;
	do
	{
		vector<string> vecSessionsData;
		uint32 uiSessionCount = CRegistryManager::getSoftwareValueInt("IMGF\\Sessions", "Count");
		for (int32 i = uiSessionCount; i >= 1; i--)
		{
			string strIMGPaths = CRegistryManager::getSoftwareValueString("IMGF\\Sessions", "Data_" + CString2::toString(i));
			vecSessionsData.push_back(strIMGPaths);
		}

		getIMGF()->getTaskManager()->onTaskPause();
		pSessionManagerDialogData = getIMGF()->getPopupGUIManager()->showSessionManagerDialog(vecSessionsData);
		getIMGF()->getTaskManager()->onTaskUnpause();
		bReopenWindow = pSessionManagerDialogData->m_vecSessionsToRemove.size() > 0 || pSessionManagerDialogData->m_vecSessionsToAdd.size() > 0 || pSessionManagerDialogData->m_strSessionNameToUpdate != "";

		for (auto strSessionName : pSessionManagerDialogData->m_vecSessionsToRemove)
		{
			/*
			char zz[1024];
			sprintf_s(zz, "strSessionName: %s", strSessionName.c_str());
			CDebugger::log(zz);
			*/
			getIMGF()->getSessionManager()->removeSession(getIMGF()->getSessionManager()->getSessionByName(strSessionName));
		}
		for (auto strSessionData : pSessionManagerDialogData->m_vecSessionsToAdd)
		{
			deque<string> deqIMGPaths = CStdVector::convertVectorToDeque(CString2::split(strSessionData, "; "));
			string strSessionName = deqIMGPaths[0];
			deqIMGPaths.pop_front();

			vector<string> vecIMGPaths;
			for (auto strIMGPath : deqIMGPaths)
			{
				vecIMGPaths.push_back(strIMGPath);
			}

			getIMGF()->getSessionManager()->addSession(strSessionName, vecIMGPaths);
		}
		if (pSessionManagerDialogData->m_strSessionNameToUpdate != "")
		{
			//pSessionManagerDialogData->m_strSessionDataToUpdate
			deque<string> deqIMGPaths = CStdVector::convertVectorToDeque(CString2::split(pSessionManagerDialogData->m_strSessionDataToUpdate, "; "));
			string strNewSessionName = deqIMGPaths[0];
			deqIMGPaths.pop_front();

			vector<string> vecIMGPaths;
			for (auto strIMGPath : deqIMGPaths)
			{
				vecIMGPaths.push_back(strIMGPath);
			}

			getIMGF()->getSessionManager()->getSessionByName(pSessionManagerDialogData->m_strSessionNameToUpdate)->setName(strNewSessionName);
			getIMGF()->getSessionManager()->getSessionByName(pSessionManagerDialogData->m_strSessionNameToUpdate)->setPaths(vecIMGPaths);
		}

		delete pSessionManagerDialogData;
		getIMGF()->getSessionManager()->loadSessions();
	} while (bReopenWindow);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSessionManager");
}
void		CTaskDispatchManager::onRequestWebsite(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestWebsite");
	//ShellExecute(NULL, L"open", L"http://imgfactory.mvec.io/", NULL, NULL, SW_SHOWNORMAL);
	ShellExecute(NULL, L"open", L"http://mvec.io/", NULL, NULL, SW_SHOWNORMAL);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestWebsite");
}
void		CTaskDispatchManager::onRequestOpenLogBasic(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOpenLogBasic");
	ShellExecute(NULL, NULL, CString2::convertStdStringToStdWString(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") + CString2::getDateTextForFolder() + " / " + CLocalizationManager::get()->getTranslatedText("LogFilename_Basic")).c_str(), NULL, NULL, SW_SHOWNORMAL);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOpenLogBasic");
}
void		CTaskDispatchManager::onRequestOpenLogExtended(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOpenLogExtended");
	ShellExecute(NULL, NULL, CString2::convertStdStringToStdWString(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath") + CString2::getDateTextForFolder() + " / " + CLocalizationManager::get()->getTranslatedText("LogFilename_Extended")).c_str(), NULL, NULL, SW_SHOWNORMAL);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOpenLogExtended");
}
void		CTaskDispatchManager::onRequestOpenLogFolder(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOpenLogFolder");
	ShellExecute(NULL, NULL, CString2::convertStdStringToStdWString(getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath")).c_str(), NULL, NULL, SW_SHOWNORMAL);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestOpenLogFolder");
}
void		CTaskDispatchManager::onRequestProcessLSTFile(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestProcessLSTFile");
	/*
	getIMGF()->getTaskManager()->onTaskPause();
	string strGameDirectoryPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("PROCESS_LST__GAME"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strGameDirectoryPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestProcessLSTFile", true);
		return;
	}
	strGameDirectoryPath = CPathManager::addSlashToEnd(strGameDirectoryPath);
	getIMGF()->setLastUsedDirectory("PROCESS_LST__GAME", strGameDirectoryPath);
	*/

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("PROCESS_LST__LST"), "LST", false);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestProcessLSTFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("PROCESS_LST__LST", CPathManager::getDirectory(vecPaths[0]));

	CLSTFormat *pLSTFile = CLSTManager::get()->parseViaFile(vecPaths[0]);
	if(!pLSTFile->doesHaveError())
	{
		getIMGF()->getLSTProcessingManager()->process(pLSTFile);
	}
	
	pLSTFile->unload();
	delete pLSTFile;
	
	getIMGF()->getTaskManager()->onTaskEnd("onRequestProcessLSTFile");
}
void		CTaskDispatchManager::onRequestSelectViaIDE(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSelectViaIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaIDE", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("SELECT_IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("SELECT_IDE", CPathManager::getDirectory(vecPaths[0]));

	vector<string> vecEntryNamesWithoutExtension = CIDEManager::getIDEEntryNamesWithoutExtension(vecPaths);
	vecEntryNamesWithoutExtension = CStdVector::toUpperCase(vecEntryNamesWithoutExtension);

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	bool bSelectEntry;
	uint32 uiSelectedEntryCount = 0;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetItemCount());
	for (uint32 i = 0, j = pListControl->GetItemCount(); i < j; i++)
	{
		CIMGEntry *pIMGEntry = (CIMGEntry*)pListControl->GetItemData(i);

		if (std::find(vecEntryNamesWithoutExtension.begin(), vecEntryNamesWithoutExtension.end(), CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()))) != vecEntryNamesWithoutExtension.end())
		{
			bSelectEntry = true;
		}
		else
		{
			bSelectEntry = false;
		}

		if (bSelectEntry)
		{
			uiSelectedEntryCount++;
			pListControl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			pListControl->SetSelectionMark(i);
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	getIMGF()->getEntryListTab()->log("Selected " + CString2::toString(uiSelectedEntryCount) + " entr" + (uiSelectedEntryCount == 1 ? "y" : "ies") + " (vie IDE file).");

	pListControl->SetFocus();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSelectViaIDE");
	*/
}
void		CTaskDispatchManager::onRequestExportViaIPLFile(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportViaIPLFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIPLFile", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("EXPORT_IPL__IPL"), "IPL");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIPLFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("EXPORT_IPL__IPL", CPathManager::getDirectory(vecPaths[0]));

	getIMGF()->getTaskManager()->onTaskPause();
	string strPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORT_IPL__DESTINATION"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIPLFile", true);
		return;
	}
	strPath = CPathManager::addSlashToEnd(strPath);
	getIMGF()->setLastUsedDirectory("EXPORT_IPL__DESTINATION", strPath);

	vector<string> vecEntryNamesWithoutExtension;
	for (auto strPath : vecPaths)
	{
		CIPLFormat *pIPLFile = CIPLManager::get()->parseViaFile(strPath);
		if(!pIPLFile->doesHaveError())
		{
			vector<string> vecModelNames = pIPLFile->getModelNames();
			vecEntryNamesWithoutExtension = CStdVector::combineVectors(vecEntryNamesWithoutExtension, CStdVector::toUpperCase(vecModelNames));
		}
		pIPLFile->unload();
		delete pIPLFile;
	}

	vector<CIMGEntry*> vecIMGEntries;
	vector<string> vecIMGEntryNames;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		string strEntryNameWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		auto it = std::find(vecEntryNamesWithoutExtension.begin(), vecEntryNamesWithoutExtension.end(), strEntryNameWithoutExtension);
		if (it != vecEntryNamesWithoutExtension.end())
		{
			vecIMGEntries.push_back(pIMGEntry);
			vecIMGEntryNames.push_back(pIMGEntry->getEntryName());
		}
	}
	
	for (auto pIMGEntry : vecIMGEntries)
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_109", pIMGEntry->getEntryName().c_str()), true);
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntries.size());
	getIMGF()->getEntryListTab()->getIMGFile()->exportMultiple(vecIMGEntries, strPath);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_110", vecIMGEntries.size(), getIMGF()->getEntryListTab()->getIMGFile()->getEntryCount()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_77"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecIMGEntryNames, "\n"), true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaIPLFile");
}
void		CTaskDispatchManager::onRequestRenameIMG(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRenameIMG");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenameIMG", true);
		return;
	}

	string strCurrentIMGFileName = CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath());
	getIMGF()->getTaskManager()->onTaskPause();
	string strNewIMGFileName = getIMGF()->getPopupGUIManager()->showTextInputDialog("Rename IMG", CLocalizationManager::get()->getTranslatedText("Window_TextInput_6_Message"), strCurrentIMGFileName);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strNewIMGFileName == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenameIMG", true);
		return;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(5);

	string strFolderPath = CPathManager::addSlashToEnd(CPathManager::removeFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()));
	CFileManager::renameFile(strFolderPath + strCurrentIMGFileName, strFolderPath + strNewIMGFileName);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	if (getIMGF()->getEntryListTab()->getIMGFile()->getVersion() == IMG_1)
	{
		CFileManager::renameFile(CPathManager::replaceFileExtension(strFolderPath + strCurrentIMGFileName, "dir"), CPathManager::replaceFileExtension(strFolderPath + strNewIMGFileName, "dir"));
	}
	getIMGF()->getTaskManager()->onTaskProgressTick();

	getIMGF()->getEntryListTab()->getIMGFile()->setFilePath(strFolderPath + strNewIMGFileName);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	((CEdit*)getIMGF()->getDialog()->GetDlgItem(38))->SetWindowTextW(CString2::convertStdStringToStdWString(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()).c_str());
	getIMGF()->getTaskManager()->onTaskProgressTick();

	getIMGF()->getEntryListTab()->searchText();
	getIMGF()->getTaskManager()->onTaskProgressTick();

	wstring wstrNewIMGFileName = CString2::convertStdStringToStdWString(strNewIMGFileName);
	TCITEM ltag;
	ltag.mask = TCIF_TEXT;
	ltag.pszText = &wstrNewIMGFileName[0];
	((CTabCtrl*)getIMGF()->getDialog()->GetDlgItem(1))->SetItem(getIMGF()->getEntryListTab()->getIndex(), &ltag);

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_111", strCurrentIMGFileName.c_str(), strNewIMGFileName.c_str()));
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRenameIMG");
	*/
}
void		CTaskDispatchManager::onRequestUpdate(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestUpdate");

	//vector<CUpdateConnection*> vecUpdateConnections;
	if (getIMGF()->getBuildMeta().isAlphaBuild())
	{
		// alpha version
		string strFileContent;
		CUpdateConnection *pActiveUpdateConnection = nullptr;
		for (auto pUpdateConnection : getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntries())
		{
			if (!pUpdateConnection->isAlpha())
			{
				continue;
			}

			pActiveUpdateConnection = pUpdateConnection;
			strFileContent = HTTP::get()->getFileContent(pUpdateConnection->getLatestVersionURL());
			if (strFileContent == "")
			{
				continue;
			}

			break;
		}
		if (strFileContent == "")
		{
			getIMGF()->getTaskManager()->onTaskPause();
			uint32 uiMirrorCount = getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntryCount();
			CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_40", uiMirrorCount), CLocalizationManager::get()->getTranslatedText("UnableToCheckForUpdates"), MB_OK);
			getIMGF()->getTaskManager()->onTaskUnpause();
			getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate", true);
			return;
		}

		vector<string> vecData = CString2::split(strFileContent, "\n");
		string strLatestVersion = vecData[0];
		string strLatestVersionFileName = vecData[1];
		string strLatestBuildNumber = vecData[2];

		uint32 uiLatestBuildNumber = CString2::toUint32(strLatestBuildNumber);

		if (uiLatestBuildNumber > BUILDNUMBER)
		{
			getIMGF()->getTaskManager()->onTaskPause();
			uint32 uiResult = CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_41", strLatestVersion.c_str(), strLatestBuildNumber.c_str(), getIMGF()->getBuildMeta().getCurrentVersionString().c_str(), BUILDNUMBER_STR), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_41"), MB_OKCANCEL);
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (uiResult == IDOK)
			{
				string strNewProgramData = HTTP::get()->getFileContent(pActiveUpdateConnection->getDownloadFolderURL() + strLatestVersionFileName);

				TCHAR szFilename[MAX_PATH];
				GetModuleFileName(NULL, szFilename, MAX_PATH);
				string strRunningProgramPath = CString2::convertStdWStringToStdString(szFilename);

				//CFileManager::overwriteLockedFileViaContent(strRunningProgramPath, strLatestVersionFileName, strNewProgramData);

				string strLockedFileDirectory = CPathManager::getDirectory(strRunningProgramPath);
				string strNewProgramPath = strLockedFileDirectory + strLatestVersionFileName;
				//rename(strRunningProgramPath.c_str(), (strLockedFileDirectory + "Temp File").c_str());
				strNewProgramPath = CFileManager::getNextIncrementingFileName(strNewProgramPath);
				CFileManager::storeFile(strNewProgramPath, strNewProgramData, false, true);

				// delete previous version's exe file
				if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
				{
					TCHAR szModuleName[MAX_PATH];
					GetModuleFileName(NULL, szModuleName, MAX_PATH);
					string strExePath = CString2::convertStdWStringToStdString(szModuleName);
					if (strNewProgramPath != strExePath)
					{
						CRegistryManager::setSoftwareValueString("IMGF\\InternalSettings", "DeletePreviousVersionOnNextLaunch", strExePath);
					}
				}

				getIMGF()->getTaskManager()->onTaskPause();
				uint32 uiResult2 = CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_42"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_42"), MB_OKCANCEL);
				getIMGF()->getTaskManager()->onTaskUnpause();
				if (uiResult2 == IDOK)
				{
					ShellExecute(NULL, NULL, CString2::convertStdStringToStdWString(strNewProgramPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
				}

				if (uiResult2 == IDOK)
				{
					getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate");
					ExitProcess(0);
				}
			}
		}
		else
		{
			getIMGF()->getTaskManager()->onTaskPause();
			CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_43", getIMGF()->getBuildMeta().getCurrentVersionString().c_str(), BUILDNUMBER_STR), CLocalizationManager::get()->getTranslatedText("UpToDate"), MB_OK);
			getIMGF()->getTaskManager()->onTaskUnpause();
		}
	}
	else
	{
		// non-alpha version
		string strFileContent;
		CUpdateConnection *pActiveUpdateConnection = nullptr;
		for (auto pUpdateConnection : getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntries())
		{
			if (pUpdateConnection->isAlpha())
			{
				continue;
			}

			pActiveUpdateConnection = pUpdateConnection;
			strFileContent = HTTP::get()->getFileContent(pUpdateConnection->getLatestVersionURL());
			if (strFileContent == "")
			{
				continue;
			}

			break;
		}
		if (strFileContent == "")
		{
			getIMGF()->getTaskManager()->onTaskPause();
			uint32 uiMirrorCount = getIMGF()->getUpdateManager()->getUpdateConnectionManager()->getEntryCount();
			CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_44", uiMirrorCount), CLocalizationManager::get()->getTranslatedText("UnableToCheckForUpdates"), MB_OK);
			getIMGF()->getTaskManager()->onTaskUnpause();
			getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate", true);
			return;
		}

		vector<string> vecData = CString2::split(HTTP::get()->getFileContent(pActiveUpdateConnection->getLatestVersionURL()), "\n");
		string strLatestVersion = vecData[0];
		string strLatestVersionFileName = vecData[1];

		float32 fLatestVersion = CString2::toFloat32(vecData[0]);

		if (fLatestVersion > getIMGF()->getBuildMeta().getCurrentVersion())
		{
			getIMGF()->getTaskManager()->onTaskPause();
			uint32 uiResult = CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_45", strLatestVersion.c_str(), getIMGF()->getBuildMeta().getCurrentVersionString().c_str()), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_45"), MB_OKCANCEL);
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (uiResult == IDOK)
			{
				string strNewProgramData = HTTP::get()->getFileContent(pActiveUpdateConnection->getDownloadFolderURL() + strLatestVersionFileName);

				TCHAR szFilename[MAX_PATH];
				GetModuleFileName(NULL, szFilename, MAX_PATH);
				string strRunningProgramPath = CString2::convertStdWStringToStdString(szFilename);

				//CFileManager::overwriteLockedFileViaContent(strRunningProgramPath, strLatestVersionFileName, strNewProgramData);

				string strLockedFileDirectory = CPathManager::getDirectory(strRunningProgramPath);
				string strNewProgramPath = strLockedFileDirectory + strLatestVersionFileName;
				//rename(strRunningProgramPath.c_str(), (strLockedFileDirectory + "Temp File").c_str());
				CFileManager::storeFile(strNewProgramPath, strNewProgramData, false, true);

				// delete previous version's exe file
				if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
				{
					TCHAR szModuleName[MAX_PATH];
					GetModuleFileName(NULL, szModuleName, MAX_PATH);
					string strExePath = CString2::convertStdWStringToStdString(szModuleName);
					if (strNewProgramPath != strExePath)
					{
						CRegistryManager::setSoftwareValueString("IMGF\\InternalSettings", "DeletePreviousVersionOnNextLaunch", strExePath);
					}
				}

				getIMGF()->getTaskManager()->onTaskPause();
				uint32 uiResult2 = CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_42"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_42"), MB_OKCANCEL);
				getIMGF()->getTaskManager()->onTaskUnpause();
				if (uiResult2 == IDOK)
				{
					ShellExecute(NULL, NULL, CString2::convertStdStringToStdWString(strNewProgramPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
				}

				if (uiResult2 == IDOK)
				{
					getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate");
					ExitProcess(0);
				}
			}
		}
		else
		{
			getIMGF()->getTaskManager()->onTaskPause();
			CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_46", getIMGF()->getBuildMeta().getCurrentVersionString().c_str()), CLocalizationManager::get()->getTranslatedText("UpToDate"), MB_OK);
			getIMGF()->getTaskManager()->onTaskUnpause();
		}
	}

	getIMGF()->getTaskManager()->onTaskEnd("onRequestUpdate");
}
void		CTaskDispatchManager::onRequestAutoUpdate(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestAutoUpdate");
	vector<string> vecData = CString2::split(HTTP::get()->getFileContent("http://updater.imgfactory.mvec.io/latest-version.txt"), "\n");
	if (vecData.size() == 0)
	{
		// e.g. no network connection
		getIMGF()->getTaskManager()->onTaskEnd("onRequestAutoUpdate", true);
		return;
	}
	string strLatestVersion = vecData[0];
	string strLatestVersionFileName = vecData[1];

	float32 fLatestVersion = CString2::toFloat32(vecData[0]);

	if (fLatestVersion > getIMGF()->getBuildMeta().getCurrentVersion())
	{
		getIMGF()->getTaskManager()->onTaskPause();
		uint32 uiResult = CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_45", strLatestVersion.c_str(), getIMGF()->getBuildMeta().getCurrentVersionString().c_str()), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_45"), MB_OKCANCEL);
		getIMGF()->getTaskManager()->onTaskUnpause();
		if (uiResult == IDOK)
		{
			string strNewProgramData = HTTP::get()->getFileContent("http://updater.imgfactory.mvec.io/versions/" + strLatestVersionFileName);

			TCHAR szFilename[MAX_PATH];
			GetModuleFileName(NULL, szFilename, MAX_PATH);
			string strRunningProgramPath = CString2::convertStdWStringToStdString(szFilename);

			//CFileManager::overwriteLockedFileViaContent(strRunningProgramPath, strLatestVersionFileName, strNewProgramData);

			string strLockedFileDirectory = CPathManager::getDirectory(strRunningProgramPath);
			string strNewProgramPath = strLockedFileDirectory + strLatestVersionFileName;
			//rename(strRunningProgramPath.c_str(), (strLockedFileDirectory + "Temp File").c_str());
			CFileManager::storeFile(strNewProgramPath, strNewProgramData, false, true);

			// delete previous version's exe file
			if (getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate"))
			{
				TCHAR szModuleName[MAX_PATH];
				GetModuleFileName(NULL, szModuleName, MAX_PATH);
				string strExePath = CString2::convertStdWStringToStdString(szModuleName);
				CRegistryManager::setSoftwareValueString("IMGF\\InternalSettings", "DeletePreviousVersionOnNextLaunch", strExePath);
			}

			getIMGF()->getTaskManager()->onTaskPause();
			uint32 uiResult2 = CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_42"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_42"), MB_OKCANCEL);
			getIMGF()->getTaskManager()->onTaskUnpause();
			if (uiResult2 == IDOK)
			{
				ShellExecute(NULL, NULL, CString2::convertStdStringToStdWString(strNewProgramPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
			}

			// close the currently open program
			if (uiResult2 == IDOK)
			{
				getIMGF()->getTaskManager()->onTaskEnd("onRequestAutoUpdate");
				ExitProcess(0);
			}
		}
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestAutoUpdate");
}
void		CTaskDispatchManager::onRequestSaveIMGSignature(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSaveIMGSignature");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveIMGSignature", true);
		return;
	}

	CIMGFormat *pIMGFile = getIMGF()->getEntryListTab()->getIMGFile();
	CDBFormat *pDBFile = CDBManager::get()->createDBFileFromIMGFile(pIMGFile);
	//CDBFormat *pDBFile = getIMGF()->getEntryListTab()->m_pDBFile;
	string strDBPath = CPathManager::replaceFileExtension(pIMGFile->getFilePath(), "db");
	pDBFile->storeViaFile(strDBPath);

	if (getIMGF()->getEntryListTab()->m_pDBFile != nullptr)
	{
		delete getIMGF()->getEntryListTab()->m_pDBFile;
	}
	getIMGF()->getEntryListTab()->m_pDBFile = pDBFile;
	getIMGF()->getEntryListTab()->loadProtectedEntryStates();
	getIMGF()->getEntryListTab()->readdAllEntriesToMainListView();

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_114", CPathManager::getFileName(strDBPath).c_str()));
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSaveIMGSignature");
}
void		CTaskDispatchManager::onRequestVerifyIMGSignature(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestVerifyIMGSignature");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestVerifyIMGSignature", true);
		return;
	}

	CIMGFormat *pIMGFile = getIMGF()->getEntryListTab()->getIMGFile();
	CDBFormat *pDBFileForIMGTab = CDBManager::get()->createDBFileFromIMGFile(pIMGFile);

	string strDBPath = CPathManager::replaceFileExtension(pIMGFile->getFilePath(), "db");
	CDBFormat *pDBFileForIMGFile = CDBManager::get()->parseViaFile(strDBPath);
	
	if(pDBFileForIMGFile->doesHaveError())
	{
		delete pDBFileForIMGTab;
		delete pDBFileForIMGFile;
		getIMGF()->getTaskManager()->onTaskEnd("onRequestVerifyIMGSignature", true);
		return;
	}
	
	if (!CFileManager::doesFileExist(strDBPath))
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_54", CPathManager::getFileName(strDBPath).c_str(), CPathManager::getDirectory(strDBPath).c_str()), CLocalizationManager::get()->getTranslatedText("FileNotFound"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
	}
	else if (CDBManager::get()->compareDBFiles(pDBFileForIMGTab, pDBFileForIMGFile))
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_55", CPathManager::getFileName(pIMGFile->getFilePath()).c_str(), CPathManager::getFileName(strDBPath).c_str()), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_55"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
	}
	else
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_56", CPathManager::getFileName(pIMGFile->getFilePath()).c_str(), CPathManager::getFileName(strDBPath).c_str()), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_56"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
	}

	delete pDBFileForIMGTab;
	delete pDBFileForIMGFile;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestVerifyIMGSignature");
}
void		CTaskDispatchManager::onRequestCompareIMG(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestCompareIMG");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCompareIMG", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("COMPAREIMG"), "IMG", false);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCompareIMG", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("COMPAREIMG", CPathManager::getDirectory(vecPaths[0]));

	CIMGFormat *pIMGFile1 = getIMGF()->getEntryListTab()->getIMGFile();

	eIMGVersion eIMGVersionValue = CIMGManager::detectIMGVersion(vecPaths[0]);
	/*
	todo
	if (uiFileResult == FILE_NOT_FOUND)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_32"), CLocalizationManager::get()->getTranslatedText("FileNotFound"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCompareIMG", true);
		return;
	}
	else if (uiFileResult == FILE_BLANK)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_33"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_33"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCompareIMG", true);
		return;
	}
	else if (uiFileResult == FILE_UNKNOWN2)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_34"), CLocalizationManager::get()->getTranslatedText("UnableToOpenIMG"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCompareIMG", true);
		return;
	}
	*/
	
	CIMGFormat *pIMGFile2 = CIMGManager::get()->parseViaFile(vecPaths[0]/* todo ?? -, (eIMGVersion)uiFileResult */);
	if (pIMGFile2->doesHaveError())
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedFormattedText("TextPopup_47", CPathManager::getFileName(vecPaths[0]).c_str()), CLocalizationManager::get()->getTranslatedText("UnableToOpenIMG"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
		
		pIMGFile2->unload();
		delete pIMGFile2;
		
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCompareIMG", true);
		return;
	}

	vector<string>
		vecEntriesInFile1NotInFile2,
		vecEntriesInFile2NotInFile1,
		vecEntriesInBothFiles;

	for (auto pIMGEntry : pIMGFile1->getEntries())
	{
		if (pIMGFile2->getEntryByName(pIMGEntry->getEntryName()) == nullptr)
		{
			vecEntriesInFile1NotInFile2.push_back(pIMGEntry->getEntryName());
		}
		else
		{
			vecEntriesInBothFiles.push_back(pIMGEntry->getEntryName());
		}
	}
	for (auto pIMGEntry : pIMGFile2->getEntries())
	{
		if (pIMGFile1->getEntryByName(pIMGEntry->getEntryName()) == nullptr)
		{
			vecEntriesInFile2NotInFile1.push_back(pIMGEntry->getEntryName());
		}
	}
	vecEntriesInFile1NotInFile2 = CStdVector::removeDuplicates(vecEntriesInFile1NotInFile2);
	vecEntriesInFile2NotInFile1 = CStdVector::removeDuplicates(vecEntriesInFile2NotInFile1);
	vecEntriesInBothFiles = CStdVector::removeDuplicates(vecEntriesInBothFiles);

	vector<string> vecLines;
	uint32
		uiEntryCountInFile1NotInFile2,
		uiEntryCountInFile2NotInFile1,
		uiEntryCountInBothFiles;
	if (vecEntriesInFile1NotInFile2.size() > 0)
	{
		vecLines.push_back("Entries in " + CPathManager::getFileName(pIMGFile1->getFilePath()) + " not in " + CPathManager::getFileName(pIMGFile2->getFilePath()) + ":");
		for (auto strEntryName : vecEntriesInFile1NotInFile2)
		{
			vecLines.push_back(strEntryName);
		}
	}
	uiEntryCountInFile1NotInFile2 = vecEntriesInFile1NotInFile2.size();
	vecEntriesInFile1NotInFile2.clear();
	if (vecEntriesInFile2NotInFile1.size() > 0)
	{
		vecLines.push_back("Entries in " + CPathManager::getFileName(pIMGFile2->getFilePath()) + " not in " + CPathManager::getFileName(pIMGFile1->getFilePath()) + ":");
		for (auto strEntryName : vecEntriesInFile2NotInFile1)
		{
			vecLines.push_back(strEntryName);
		}
	}
	uiEntryCountInFile2NotInFile1 = vecEntriesInFile2NotInFile1.size();
	vecEntriesInFile2NotInFile1.clear();

	if (vecEntriesInBothFiles.size() > 0)
	{
		vecLines.push_back("Entries in " + CPathManager::getFileName(pIMGFile1->getFilePath()) + " also in " + CPathManager::getFileName(pIMGFile2->getFilePath()) + ":");
		for (auto strEntryName : vecEntriesInBothFiles)
		{
			vecLines.push_back(strEntryName);
		}
	}
	uiEntryCountInBothFiles = vecEntriesInBothFiles.size();
	vecEntriesInBothFiles.clear();

	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showListViewDialog(
		"Compare IMG",
		CString2::toString(uiEntryCountInFile1NotInFile2) + " entr" + (uiEntryCountInFile1NotInFile2 == 1 ? "y" : "ies") + " not in " + CPathManager::getFileName(pIMGFile2->getFilePath()) + ", "
		+ CString2::toString(uiEntryCountInFile2NotInFile1) + " entr" + (uiEntryCountInFile2NotInFile1 == 1 ? "y" : "ies") + " not in " + CPathManager::getFileName(pIMGFile1->getFilePath()) + ", "
		+ CString2::toString(uiEntryCountInBothFiles) + " entr" + (uiEntryCountInBothFiles == 1 ? "y" : "ies") + " in both files",
		CLocalizationManager::get()->getTranslatedText("Window_OrphanEntries_EntryName"),
		vecLines,
		CLocalizationManager::get()->getTranslatedText("SaveFilePopup_7_InitialFilename"),
		"COMPAREIMG__SAVE"
	);
	getIMGF()->getTaskManager()->onTaskUnpause();

	pIMGFile2->unload();
	delete pIMGFile2;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestCompareIMG");
}

void			CTaskDispatchManager::onRequestConvertTXDToTextureFormat(CRasterDataFormat *pRasterDataFormat)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_ConvertTXD_TextureFormat(pRasterDataFormat);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertTXDToTextureFormat");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToTextureFormat", true);
		return;
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToTextureFormat", true);
		return;
	}

	CIMGEntry *pIMGEntry = nullptr;
	vector<string>
		vecConvertedTXDEntryNames,
		vecMipmapsRemoved;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) != "TXD")
		{
			continue;
		}

		string strEntryData = pIMGEntry->getEntryData();
		CTXDFormat *pTXDFile = CTXDManager::get()->parseViaMemory(strEntryData);
		if (pTXDFile->doesHaveError())
		{
			pTXDFile->unload();
			delete pTXDFile;
			continue;
		}

		vecConvertedTXDEntryNames.push_back(pIMGEntry->getEntryName());

		//pTXDFile->convertToTextureFormat(pTextureFormat, vecMipmapsRemoved);
		pTXDFile->convertToRasterDataFormat(pRasterDataFormat->getRasterDataFormatId(), vecMipmapsRemoved);

		string strFileData = pTXDFile->serializeViaMemory();
		uint32 uiFileSize = strFileData.length();
		pTXDFile->unload();
		delete pTXDFile;

		pIMGEntry->setEntrySize(uiFileSize);
		pIMGEntry->setEntryData(strFileData);

		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_115", vecConvertedTXDEntryNames.size(), CLocalizationManager::get()->getTranslatedText(pRasterDataFormat->getLocalizationKey()).c_str(), vecMipmapsRemoved.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_105"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecConvertedTXDEntryNames, "\n"), true);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("MipmapsRemoved"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecMipmapsRemoved, "\n"), true);

	if (pIMGEntry != nullptr)
	{
		getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertTXDToTextureFormat");
	*/
}

void			CTaskDispatchManager::onRequestClearLogs(bool bAllTabs)
{
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_ClearLogs_AllTabs(bAllTabs);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestClearLogs");
	vector<CIMGEditorTab*> veCIMGEditorTabs;
	if (bAllTabs)
	{
		for (auto pEntryListWindowTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
		{
			veCIMGEditorTabs.push_back((CIMGEditorTab*)pEntryListWindowTab);
		}
	}
	else
	{
		veCIMGEditorTabs.push_back(getIMGF()->getEntryListTab());
	}

	for (auto pEditorTab : veCIMGEditorTabs)
	{
		pEditorTab->clearLogs();
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestClearLogs");
}

void			CTaskDispatchManager::onRequestValidateAllDFFInActiveTab(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestValidateAllDFFInActiveTab");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestValidateAllDFFInActiveTab", true);
		return;
	}

	vector<string> vecCorruptDFFEntryLines;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		if (CPathManager::isModelExtension(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()))))
		{
			CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
			if (pDFFFile->doesHaveError())
			{
				vecCorruptDFFEntryLines.push_back(pIMGEntry->getEntryName() + " - " + pDFFFile->getErrorReason());
			}
			pDFFFile->unload();
			delete pDFFFile;
		}
	}

	if (vecCorruptDFFEntryLines.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_48"), CLocalizationManager::get()->getTranslatedText("DFFValidationComplete"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
	}
	else
	{
		getIMGF()->getTaskManager()->onTaskPause();
		getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("DFFValidationComplete"), CLocalizationManager::get()->getTranslatedFormattedText("Window_TextArea_6_Message", vecCorruptDFFEntryLines.size()), CString2::join(vecCorruptDFFEntryLines, "\n"));
		getIMGF()->getTaskManager()->onTaskUnpause();
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestValidateAllDFFInActiveTab");
}

void			CTaskDispatchManager::onRequestValidateAllTXDInActiveTab(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestValidateAllTXDInActiveTab");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestValidateAllTXDInActiveTab", true);
		return;
	}

	vector<string> vecCorruptTXDEntryLines;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) == "TXD")
		{
			string strTXDData = pIMGEntry->getEntryData();
			if (!CTXDFormat::isTXDSizeValid(strTXDData.size()))
			{
				vecCorruptTXDEntryLines.push_back(pIMGEntry->getEntryName() + " - TXD size not valid");
			}
			else
			{
				CTXDFormat *pTXDFile = CTXDManager::get()->parseViaMemory(strTXDData);
				if (pTXDFile->doesHaveError())
				{
					vecCorruptTXDEntryLines.push_back(pIMGEntry->getEntryName() + " - Failed to parse");
				}
				else
				{
					if (!CTXDFormat::isTextureCountValid(pTXDFile->getTextures().size(), pTXDFile->getGames()))
					{
						vecCorruptTXDEntryLines.push_back(CLocalizationManager::get()->getTranslatedFormattedText("Log_InvalidTextureCount", pIMGEntry->getEntryName(), pTXDFile->getTextures().size()));
					}
					else
					{
						uint32 uiTextureIndex = 0;
						for (auto pTexture : pTXDFile->getTextures())
						{
							if (!CTXDFormat::isTextureResolutionValid(pTexture->getImageSize().x, pTexture->getImageSize().y, pTXDFile->getGames()))
							{
								vecCorruptTXDEntryLines.push_back(pIMGEntry->getEntryName() + " - Invalid texture resolution: " + pTexture->getDiffuseName() + " (" + CString2::toString(pTexture->getImageSize().x) + " x " + CString2::toString(pTexture->getImageSize().y) + ")");
								break;
							}

							if (!CTXDFormat::isTextureNameValid(pTexture->getDiffuseName()) || !CTXDFormat::isTextureNameValid(pTexture->getAlphaName(), true))
							{
								vecCorruptTXDEntryLines.push_back(pIMGEntry->getEntryName() + " - Invalid texture name: #" + CString2::toString(uiTextureIndex + 1));
								break;
							}

							uiTextureIndex++;
						}
					}
				}
				pTXDFile->unload();
				delete pTXDFile;
			}
		}
	}

	if (vecCorruptTXDEntryLines.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskPause();
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_49"), CLocalizationManager::get()->getTranslatedText("TXDValidationComplete"), MB_OK);
		getIMGF()->getTaskManager()->onTaskUnpause();
	}
	else
	{
		getIMGF()->getTaskManager()->onTaskPause();
		getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("TXDValidationComplete"), CLocalizationManager::get()->getTranslatedFormattedText("Window_TextArea_7_Message", vecCorruptTXDEntryLines.size()), CString2::join(vecCorruptTXDEntryLines, "\n"));
		getIMGF()->getTaskManager()->onTaskUnpause();
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestValidateAllTXDInActiveTab");
}

void			CTaskDispatchManager::onRequestCredits(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestCredits");
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showCreditsDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestCredits");
}

void			CTaskDispatchManager::onRequestEntryViewer(bool bDontOpenWindow)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestEntryViewer");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
		return;
	}

	// fetch selected IMG entry
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
		return;
	}
	int nItem = pListControl->GetNextSelectedItem(pos);
	CIMGEntry *pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

	// check the entry type
	if (pIMGEntry->isTextureFile())
	{
		CTextureViewer *pTextureViewer = getIMGF()->getEntryViewerManager()->getTextureViewer();

		if (bDontOpenWindow && !pTextureViewer->isWindowOpen())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
			return;
		}

		pTextureViewer->reset();
		pTextureViewer->setIMGEntry(pIMGEntry);
		pTextureViewer->setWindowTitle(CLocalizationManager::get()->getTranslatedFormattedText("Window_TextureViewer_TitleWithEntryName", pIMGEntry->getEntryName().c_str()));
		pTextureViewer->prepareRenderData();

		if (pTextureViewer->isEntityDataCorrupt())
		{
			if (!bDontOpenWindow)
			{
				CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText(pIMGEntry->isTXDFile() ? "TXDReadError" : "WTDReadError"), CLocalizationManager::get()->getTranslatedText("TextPopup_Title52"), MB_OK);
			}
			getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
			return;
		}

		if (pTextureViewer->isWindowOpen())
		{
			pTextureViewer->applyWindowTitle();
		}
		else
		{
			if (!bDontOpenWindow)
			{
				pTextureViewer->loadThreadAndWindow();
			}
		}

		pTextureViewer->forceRender();
	}
	*/



	/*
	else if (pIMGEntry->isCOLFile())
	{
		CCollisionViewer *pCollisionViewer = getIMGF()->getEntryViewerManager()->getCollisionViewer();

		if (pCollisionViewer->isWindowOpening())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
			return;
		}

		if (bDontOpenWindow && !pCollisionViewer->isWindowOpen())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
			return;
		}

		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaMemory(pIMGEntry->getEntryData());
		if (pCOLFile->doesHaveError())
		{
			if (!bDontOpenWindow)
			{
				CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("COLReadError"), CLocalizationManager::get()->getTranslatedText("TextPopup_Title52"), MB_OK);
			}
			pCOLFile->unload();
			delete pCOLFile;
			getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
			return;
		}

		if (pCollisionViewer->isWindowOpen())
		{
			if(!bDontOpenWindow)
			{
				pCollisionViewer->unloadThreadAndWindow();
			}
		}

		pCollisionViewer->setEntryChanging(true);
		pCollisionViewer->reset();
		pCollisionViewer->setCOLFile(pCOLFile);
		pCollisionViewer->setWindowTitle(CLocalizationManager::get()->getTranslatedFormattedText("Window_CollisionViewer_TitleWithEntryName", pIMGEntry->getEntryName().c_str()));
		//pCollisionViewer->setCOLFileName(pIMGEntry->getEntryName());
		pCollisionViewer->prepareRenderData();
		pCollisionViewer->setEntryChanging(false);

		if (pCollisionViewer->isWindowOpen())
		{
			pCollisionViewer->applyWindowTitle();
		}
		else
		{
			if (!bDontOpenWindow)
			{
				pCollisionViewer->loadThreadAndWindow();
			}
		}
	}
	*/


	/*
	todo
	else if (pIMGEntry->isModelFile())
	{
	}
	else
	{
		// entry viewer does not support the type of file
		getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer", true);
		return;
	}

	getIMGF()->getTaskManager()->onTaskEnd("onRequestEntryViewer");
	*/
}

void			CTaskDispatchManager::onRequestRenamer(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRenamer");
	getIMGF()->getTaskManager()->onTaskPause();
	CRenamerDialogData *pRenamerDialogData = getIMGF()->getPopupGUIManager()->showRenamerDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();

	if (!pRenamerDialogData->m_bRename)
	{
		delete pRenamerDialogData;
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenamer", true);
		return;
	}

	// ensure a tab is open
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_50"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_50"), MB_OK);
		delete pRenamerDialogData;
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRenamer", true);
		return;
	}

	// choose entries to rename
	vector<CIMGEntry*> vecIMGEntries;
	if (pRenamerDialogData->m_ucEntriesType == 0) // all entries
	{
		vecIMGEntries = getIMGF()->getEntryListTab()->getIMGFile()->getEntries();
	}
	else if (pRenamerDialogData->m_ucEntriesType == 1) // selected entries
	{
		vecIMGEntries = getIMGF()->getEntryListTab()->getSelectedEntries();
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntries.size() * 2); // x1 for the main loop, and x1 for the refreshing the main list view display

	vector<CRenamedIMGEntry*> vecIMGEntriesWithNewNames;

	// loop around entries
	for (auto pIMGEntry : vecIMGEntries)
	{
		// skip LODs if "update LOD names to match new name" is enabled, as matching LOD entries will be updated anyway
		if (pRenamerDialogData->m_bUpdateLODNamesToMatch)
		{
			if (CString2::toUpperCase(pIMGEntry->getEntryName().substr(0, 3)) == "LOD")
			{
				getIMGF()->getTaskManager()->onTaskProgressTick();
				continue;
			}
		}

		string strEntryPreviousName = pIMGEntry->getEntryName();

		// character adding/replacing
		if (pRenamerDialogData->m_ucCharReplacementType == 0) // don't replace characters
		{
			if (pRenamerDialogData->m_strCharAdding_Front != "")
			{
				pIMGEntry->setEntryName(pRenamerDialogData->m_strCharAdding_Front + pIMGEntry->getEntryName());
			}

			if (pRenamerDialogData->m_strCharAdding_End != "")
			{
				pIMGEntry->setEntryName(pIMGEntry->getEntryName() + pRenamerDialogData->m_strCharAdding_End);
			}

			if (pRenamerDialogData->m_strCharAdding_AtPosition != "")
			{
				uint32
					uiPosition = pRenamerDialogData->m_uiCharAddingAtPosition_Position;
				if (uiPosition <= pIMGEntry->getEntryName().length())
				{
					string
						strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
						strNameAfter = pIMGEntry->getEntryName().substr(uiPosition);
					pIMGEntry->setEntryName(strNameBefore + pRenamerDialogData->m_strCharAdding_AtPosition + strNameAfter);
				}
			}
		}
		else if (pRenamerDialogData->m_ucCharReplacementType == 1) // always replace characters
		{
			if (pRenamerDialogData->m_strCharAdding_Front != "")
			{
				string strNewEntryName = pRenamerDialogData->m_strCharAdding_Front + pIMGEntry->getEntryName().substr(pRenamerDialogData->m_strCharAdding_Front.length());
				pIMGEntry->setEntryName(strNewEntryName);
			}

			if (pRenamerDialogData->m_strCharAdding_End != "")
			{
				string strNewEntryName = pIMGEntry->getEntryName().substr(0, pIMGEntry->getEntryName().length() - pRenamerDialogData->m_strCharAdding_End.length()) + pRenamerDialogData->m_strCharAdding_End;
				pIMGEntry->setEntryName(strNewEntryName);
			}

			if (pRenamerDialogData->m_strCharAdding_AtPosition != "")
			{
				uint32
					uiPosition = pRenamerDialogData->m_uiCharAddingAtPosition_Position;
				if (uiPosition <= pIMGEntry->getEntryName().length())
				{
					string
						strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
						strNameAfter = pIMGEntry->getEntryName().substr(uiPosition + pRenamerDialogData->m_strCharAdding_AtPosition.length());
					pIMGEntry->setEntryName(strNameBefore + pRenamerDialogData->m_strCharAdding_AtPosition + strNameAfter);
				}
			}
		}
		else if (pRenamerDialogData->m_ucCharReplacementType == 2) // only replace characters if length exceeds
		{
			uint32
				uiExceedLength = pRenamerDialogData->m_uiCharReplaceConditional_Length;

			if (pRenamerDialogData->m_strCharAdding_Front != "")
			{
				string strPrefixText = pRenamerDialogData->m_strCharAdding_Front;
				string strEntryName = pIMGEntry->getEntryName();

				string strExtension = CPathManager::getFileExtension(pIMGEntry->getEntryName());
				uint32 uiCharCountLeft = uiExceedLength - (strExtension.length() + 1);

				string strEntryNewName = CString2::mergeStrings(strPrefixText, CPathManager::removeFileExtension(strEntryName), uiExceedLength) + "." + strExtension;


				/*
				uint32 uiNewLength = pRenamerDialogData->m_strCharAdding_Front.length() + pIMGEntry->getEntryName().length();
				uint32 uiNameAfterSubstrPosition = uiNewLength > uiExceedLength ? (uiNewLength - uiExceedLength) : 0;
				//CDebugger::log("pRenamerDialogData->m_strCharAdding_Front.length(): " + CString2::toString(pRenamerDialogData->m_strCharAdding_Front.length()));
				//CDebugger::log("pIMGEntry->getEntryName().length(): " + CString2::toString(pIMGEntry->getEntryName().length()));
				//CDebugger::log("uiNewLength: " + CString2::toString(uiNewLength));
				//CDebugger::log("uiNameAfterSubstrPosition: " + CString2::toString(uiNameAfterSubstrPosition));
				string strNameAfter = pIMGEntry->getEntryName().substr(uiNameAfterSubstrPosition); // substr(12) causes crash when str.size() == 11
				string strNewEntryName = pRenamerDialogData->m_strCharAdding_Front + strNameAfter;
				*/
				pIMGEntry->setEntryName(strEntryNewName);
			}

			if (pRenamerDialogData->m_strCharAdding_End != "")
			{
				uint32 uiNewLength = pRenamerDialogData->m_strCharAdding_End.length() + pIMGEntry->getEntryName().length();
				uint32 uiNameBeforeSubstrLength = uiNewLength > uiExceedLength ? (pIMGEntry->getEntryName().length() - (uiNewLength - uiExceedLength)) : 0;
				string strNameBefore = pIMGEntry->getEntryName().substr(0, uiNameBeforeSubstrLength);
				string strNewEntryName = strNameBefore + pRenamerDialogData->m_strCharAdding_End;
				pIMGEntry->setEntryName(strNewEntryName);
			}

			if (pRenamerDialogData->m_strCharAdding_AtPosition != "")
			{
				uint32
					uiPosition = pRenamerDialogData->m_uiCharAddingAtPosition_Position;
				if (uiPosition <= pIMGEntry->getEntryName().length())
				{
					uint32 uiNewLength = pRenamerDialogData->m_strCharAdding_AtPosition.length() + pIMGEntry->getEntryName().length();
					uint32 uiNameAfterSubstrPosition = uiNewLength > uiExceedLength ? (uiPosition + (uiNewLength - uiExceedLength)) : 0;
					string
						strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
						strNameAfter = pIMGEntry->getEntryName().substr(uiNameAfterSubstrPosition);
					string strNewEntryName = strNameBefore + pRenamerDialogData->m_strCharAdding_AtPosition + strNameAfter;
					pIMGEntry->setEntryName(strNewEntryName);
				}
			}
		}

		// character removing
		if (pRenamerDialogData->m_uiCharRemoving_Front > 0)
		{
			if ((pIMGEntry->getEntryName().length() - pRenamerDialogData->m_uiCharRemoving_Front) > 0)
			{
				pIMGEntry->setEntryName(pIMGEntry->getEntryName().substr(pRenamerDialogData->m_uiCharRemoving_Front));
			}
		}

		if (pRenamerDialogData->m_uiCharRemoving_End > 0)
		{
			if ((pIMGEntry->getEntryName().length() - pRenamerDialogData->m_uiCharRemoving_End) > 0)
			{
				pIMGEntry->setEntryName(pIMGEntry->getEntryName().substr(pIMGEntry->getEntryName().length() - pRenamerDialogData->m_uiCharRemoving_End));
			}
		}

		if (pRenamerDialogData->m_uiCharRemoving_AtPosition > 0)
		{
			uint32
				uiPosition = pRenamerDialogData->m_uiCharRemovingAtPosition_Position,
				uiLength = pRenamerDialogData->m_uiCharRemoving_AtPosition;
			if ((pIMGEntry->getEntryName().length() - uiLength) > 0)
			{
				string
					strNameBefore = pIMGEntry->getEntryName().substr(0, uiPosition),
					strNameAfter = pIMGEntry->getEntryName().substr(uiPosition + uiLength);
				pIMGEntry->setEntryName(strNameBefore + strNameAfter);
			}
		}

		// character case
		if (pRenamerDialogData->m_ucCharCaseType == 0)
		{
			// leave untouched
		}
		else if (pRenamerDialogData->m_ucCharCaseType == 1)
		{
			// uppercase
			pIMGEntry->setEntryName(CString2::toUpperCase(pIMGEntry->getEntryName()));
		}
		else if (pRenamerDialogData->m_ucCharCaseType == 2)
		{
			// lowercase
			pIMGEntry->setEntryName(CString2::toLowerCase(pIMGEntry->getEntryName()));
		}
		else if (pRenamerDialogData->m_ucCharCaseType == 3)
		{
			// title case
			pIMGEntry->setEntryName(CString2::toTitleCase(pIMGEntry->getEntryName()));
		}

		// mark IMG entry as renamed
		if (strEntryPreviousName != pIMGEntry->getEntryName())
		{
			CRenamedIMGEntry *pRenamedIMGEntry = new CRenamedIMGEntry;
			pRenamedIMGEntry->m_pIMGEntry = pIMGEntry;
			pRenamedIMGEntry->m_strPreviousName = strEntryPreviousName;
			vecIMGEntriesWithNewNames.push_back(pRenamedIMGEntry);
		}

		// update LOD names to match new name
		if (pRenamerDialogData->m_bUpdateLODNamesToMatch)
		{
			string strLODPreviousName = "LOD" + strEntryPreviousName.substr(3);
			CIMGEntry *pIMGEntryLOD = getIMGF()->getEntryListTab()->getIMGFile()->getEntryByName(strLODPreviousName);
			if (pIMGEntryLOD != nullptr)
			{
				string strLODNewName = pIMGEntryLOD->getEntryName().substr(0, 3) + pIMGEntry->getEntryName().substr(3);
				pIMGEntryLOD->setEntryName(strLODNewName);

				// mark IMG entry as renamed
				if (strLODPreviousName != strLODNewName)
				{
					CRenamedIMGEntry *pRenamedIMGEntry = new CRenamedIMGEntry;
					pRenamedIMGEntry->m_pIMGEntry = pIMGEntryLOD;
					pRenamedIMGEntry->m_strPreviousName = strLODPreviousName;
					vecIMGEntriesWithNewNames.push_back(pRenamedIMGEntry);
				}
			}
		}

		// progress bar
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// matching entries
	vector<string> vecFilePaths;

	// matching entries - IDE
	if (pRenamerDialogData->m_bMatchingState_IDE)
	{
		vecFilePaths = CFileManager::getFilePaths(pRenamerDialogData->m_strMatchingPath_IDE, true);
		for (auto strFilePath : vecFilePaths)
		{
			if (CString2::toUpperCase(CPathManager::getFileExtension(strFilePath)) == "IDE")
			{
				CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strFilePath);
				
				if(pIDEFile->doesHaveError())
				{
					pIDEFile->unload();
					delete pIDEFile;
					continue;
				}
				
				for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
				{
					vector<CIDEEntry*> vecIDEEntries;

					// OBJS/TOBJ model name
					vecIDEEntries = pIDEFile->getEntriesByModelName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pIDEEntry : vecIDEEntries)
					{
						switch (pIDEEntry->getSectionType()) // todo - make work with all sections with setModelName on CIDEEntry_Data and CIPLEntry_Data
						{
						case IDE_SECTION_OBJS:
							((CIDEEntry_OBJS*)pIDEEntry)->setModelName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						case IDE_SECTION_TOBJ:
							((CIDEEntry_TOBJ*)pIDEEntry)->setModelName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						}
					}

					// OBJS/TOBJ texture name
					vecIDEEntries = pIDEFile->getEntriesByTXDName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pIDEEntry : vecIDEEntries)
					{
						switch (pIDEEntry->getSectionType()) // todo - make work with all sections with setTXDName on CIDEEntry_Data and CIPLEntry_Data
						{
						case IDE_SECTION_OBJS:
							((CIDEEntry_OBJS*)pIDEEntry)->setTXDName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						case IDE_SECTION_TOBJ:
							((CIDEEntry_TOBJ*)pIDEEntry)->setTXDName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
							break;
						}
					}
				}

				pIDEFile->serializeViaFile();
				pIDEFile->unload();
				delete pIDEFile;
			}
		}
	}

	// matching entries - IPL
	if (pRenamerDialogData->m_bMatchingState_IPL)
	{
		vecFilePaths = CFileManager::getFilePaths(pRenamerDialogData->m_strMatchingPath_IPL, true);
		for (auto strFilePath : vecFilePaths)
		{
			if (CString2::toUpperCase(CPathManager::getFileExtension(strFilePath)) == "IPL")
			{
				CIPLFormat *pIPLFile = CIPLManager::get()->parseViaFile(strFilePath);
				
				if(pIPLFile->doesHaveError())
				{
					pIPLFile->unload();
					delete pIPLFile;
					continue;
				}
				
				if (pIPLFile->isBinary()) // skip binary IPL files as they don't contain a model name
				{
					pIPLFile->unload();
					delete pIPLFile;
					continue;
				}

				for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
				{
					vector<CIPLEntry*> vecIPLEntries;

					// INST model name
					vecIPLEntries = pIPLFile->getEntriesByModelName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pIPLEntry : vecIPLEntries)
					{
						// todo - make work with all sections with setModelName on CIDEEntry_Data and CIPLEntry_Data
						if (pIPLEntry->getSectionType() == IPL_SECTION_INST)
						{
							((CIPLEntry_INST*)pIPLEntry)->setModelName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
						}
					}
				}

				pIPLFile->serializeViaFile();
				pIPLFile->unload();
				delete pIPLFile;
			}
		}
	}

	// matching entries - COL
	vector<string> vecCorruptCOLFiles;
	if (pRenamerDialogData->m_bMatchingState_COL)
	{
		vecFilePaths = CFileManager::getFilePaths(pRenamerDialogData->m_strMatchingPath_COL, true);
		for (auto strFilePath : vecFilePaths)
		{
			if (CString2::toUpperCase(CPathManager::getFileExtension(strFilePath)) == "COL")
			{
				//CDebugger::log("strFilePath: " + strFilePath);
				CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(strFilePath);
				pCOLFile->setFilePath(strFilePath);
				if (pCOLFile->doesHaveError())
				{
					vecCorruptCOLFiles.push_back(CPathManager::getFileName(pCOLFile->getFilePath()) + " - Corrupt Reason: " + pCOLFile->getErrorReason());
					//CDebugger::log(CPathManager::getFileName(pCOLFile->getFilePath()) + " - CORRUPT REASON: " + pCOLFile->getCorruptReason());
					pCOLFile->unload();
					delete pCOLFile;
					continue;
				}

				for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
				{
					vector<CCOLEntry*> vecCOLEntries;

					// COL model name
					vecCOLEntries = pCOLFile->getEntriesByModelName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_strPreviousName));
					for (auto pCOLEntry : vecCOLEntries)
					{
						pCOLEntry->setModelName(CPathManager::removeFileExtension(pRenamedIMGEntry->m_pIMGEntry->getEntryName()));
					}
				}

				pCOLFile->serializeViaFile();
				pCOLFile->unload();
				delete pCOLFile;
			}
		}
	}

	// log
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_116", vecIMGEntriesWithNewNames.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_117"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecCorruptCOLFiles, "\n"), true);

	// mark tab as modified
	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);

	// refresh tab's main list view
	getIMGF()->getIMGEditor()->refreshActiveTab();

	// clean up
	for (auto pRenamedIMGEntry : vecIMGEntriesWithNewNames)
	{
		delete pRenamedIMGEntry;
	}
	vecIMGEntriesWithNewNames.clear();
	delete pRenamerDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRenamer");
}

void		CTaskDispatchManager::onRequestClearRecentlyOpenedList(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestClearRecentlyOpenedList");
	getIMGF()->getRecentlyOpenManager()->removeRecentlyOpenedEntries();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestClearRecentlyOpenedList");
}

void		CTaskDispatchManager::onRequestBuildTXD(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestBuildTXD");

	getIMGF()->getTaskManager()->onTaskPause();
	CBuildTXDDialogData *pBuildTXDDialogData = getIMGF()->getPopupGUIManager()->showBuildTXDDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();

	if (!pBuildTXDDialogData->m_bBuild) // cancel
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
		delete pBuildTXDDialogData;
		return;
	}

	// choose DFF files
	//vector<CDFFFormat*> veCDFFFormats;
	unordered_map<CDFFFormat*, string> umapDFFEntries;
	if (pBuildTXDDialogData->m_uCDFFFormatsType == 0) // All DFF entries in active tab
	{
		if (!getIMGF()->getEntryListTab())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
			delete pBuildTXDDialogData;
			return;
		}

		vector<CIMGEntry*> vecIMGEntries = getIMGF()->getEntryListTab()->getIMGFile()->getEntriesByExtension("DFF");
		vector<CIMGEntry*> vecIMGEntries_BSP = getIMGF()->getEntryListTab()->getIMGFile()->getEntriesByExtension("BSP");
		for (auto pIMGEntry : vecIMGEntries_BSP)
		{
			vecIMGEntries.push_back(pIMGEntry);
		}
		for (auto pIMGEntry : vecIMGEntries)
		{
			CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
			umapDFFEntries[pDFFFile] = CPathManager::removeFileExtension(pIMGEntry->getEntryName());
		}
	}
	else if (pBuildTXDDialogData->m_uCDFFFormatsType == 1) // Selected DFF entries in active tab
	{
		if (!getIMGF()->getEntryListTab())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
			delete pBuildTXDDialogData;
			return;
		}

		vector<CIMGEntry*> vecIMGEntries = getIMGF()->getEntryListTab()->getSelectedEntries();
		
		for(auto pIMGEntry : vecIMGEntries)
		{
			if (CPathManager::isModelExtension(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName()))))
			{
				CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
				umapDFFEntries[pDFFFile] = CPathManager::removeFileExtension(pIMGEntry->getEntryName());
			}
		}
	}
	else if (pBuildTXDDialogData->m_uCDFFFormatsType == 2) // All DFF entries in all tabs
	{
		if (!getIMGF()->getEntryListTab())
		{
			getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD", true);
			delete pBuildTXDDialogData;
			return;
		}

		for (auto pEditorTab : getIMGF()->getIMGEditor()->getTabs().getEntries())
		{
			vector<CIMGEntry*> vecIMGEntries = ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntriesByExtension("DFF");
			vector<CIMGEntry*> vecIMGEntries_BSP = ((CIMGEditorTab*)pEditorTab)->getIMGFile()->getEntriesByExtension("BSP");
			for (auto pIMGEntry : vecIMGEntries_BSP)
			{
				vecIMGEntries.push_back(pIMGEntry);
			}
			for (auto pIMGEntry : vecIMGEntries)
			{
				CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
				umapDFFEntries[pDFFFile] = CPathManager::removeFileExtension(pIMGEntry->getEntryName());
			}
		}
	}
	else if (pBuildTXDDialogData->m_uCDFFFormatsType == 3) // Folder containing DFF files
	{
		vector<string> vecFileNames = CFileManager::getFileNames(pBuildTXDDialogData->m_strDFFsFolderPath);

		for (string strFileName : vecFileNames)
		{
			string strExtensionUpper = CString2::toUpperCase(CPathManager::getFileExtension(strFileName));
			if (CPathManager::isModelExtension(strExtensionUpper))
			{
				CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pBuildTXDDialogData->m_strDFFsFolderPath + strFileName);
				umapDFFEntries[pDFFFile] = CPathManager::removeFileExtension(strFileName);
			}
		}
	}
	else if (pBuildTXDDialogData->m_uCDFFFormatsType == 4) // IDE file referencing DFF files
	{
		CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(pBuildTXDDialogData->m_strIDEFilePath);
		if(!pIDEFile->doesHaveError())
		{
			// todo - make it work with all IDE sections
			for (auto pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_OBJS>(IDE_SECTION_OBJS))
			{
				CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pBuildTXDDialogData->m_strDFFsFolderPath + pIDEEntry->getModelName());
				umapDFFEntries[pDFFFile] = pIDEEntry->getTXDName();
			}
			for (auto pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_TOBJ>(IDE_SECTION_TOBJ))
			{
				CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pBuildTXDDialogData->m_strDFFsFolderPath + pIDEEntry->getModelName());
				umapDFFEntries[pDFFFile] = pIDEEntry->getTXDName();
			}
		}
		
		pIDEFile->unload();
		delete pIDEFile;
	}

	// process
	//for (auto pDFFFile : veCDFFFormats)
	uint32
		uiTotalTXDFileCount = 0,
		uiTotalTextureCountUsed = 0;
	vector<string>
		vecTextureImagesNotFound,
		veCTXDFormatNames;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(umapDFFEntries.size());
	for (auto it : umapDFFEntries)
	{
		CDFFFormat *pDFFFile = it.first;
		string strOutputFileName = it.second + ".txd";

		if (pDFFFile->doesHaveError())
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		vector<string> vecTextureNames = pDFFFile->getTextureNames();
		vecTextureNames = CStdVector::removeDuplicates(vecTextureNames);

		uint32 uiTXDFileCount = pBuildTXDDialogData->m_uiTextureCountPerTXD == 0 ? 1 : (uint32) ceil((float32)vecTextureNames.size() / (float32)pBuildTXDDialogData->m_uiTextureCountPerTXD);
		uiTotalTXDFileCount += uiTXDFileCount;
		uint32 uiTXDFileIndex = 0;
		for (uint32 i = 0; i < uiTXDFileCount; i++)
		{
			string strFilePath = pBuildTXDDialogData->m_strDestinationFolderPath + strOutputFileName;
			strFilePath = CPathManager::getNextFileName(strFilePath, uiTXDFileIndex, "-part");

			CTXDFormat *pTXDFile = CTXDManager::get()->createFormat();
			pTXDFile->setRWVersion(pBuildTXDDialogData->m_pRWVersion);
			for (uint32 i2 = i * pBuildTXDDialogData->m_uiTextureCountPerTXD, j2 = i2 + (pBuildTXDDialogData->m_uiTextureCountPerTXD == 0 ? vecTextureNames.size() : pBuildTXDDialogData->m_uiTextureCountPerTXD); i2 < j2; i2++)
			{
				if (i2 >= vecTextureNames.size())
				{
					break;
				}

				string strTextureName = vecTextureNames[i2];
				string strTextureImagePath = CFileManager::findImageFile(strTextureName, pBuildTXDDialogData->m_strTexturesFolderPath);

				// check if texture file exists
				if (strTextureImagePath != "")
				{
					uiTotalTextureCountUsed++;

					// add texture to TXD
					CRWSection_TextureNative *pTexture = pTXDFile->addTextureViaFile(strTextureImagePath, strTextureName, strTextureName + "a");

					if (pTexture != nullptr)
					{
						//vector<string> vecMipmapsRemoved;
						//pTexture->convertToRasterDataFormat(pBuildTXDDialogData->m_pRasterDataFormat->getId(), vecMipmapsRemoved);
					}
				}
				else
				{
					vecTextureImagesNotFound.push_back(strTextureName + ".BMP");
				}
			}
			if (pTXDFile->getTextures().size() > 0)
			{
				pTXDFile->storeViaFile(strFilePath);
				veCTXDFormatNames.push_back(CPathManager::getFileName(strFilePath));
				uiTXDFileIndex++;
			}
			
			pTXDFile->unload();
			delete pTXDFile;
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// log
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_118", uiTotalTXDFileCount, uiTotalTextureCountUsed));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_119", pBuildTXDDialogData->m_strTexturesFolderPath.c_str()), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecTextureImagesNotFound, "\n"), true);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_120"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(veCTXDFormatNames, "\n"), true);

	// clean up
	//for (CDFFFormat *pDFFFile : veCDFFFormats)
	for (auto it : umapDFFEntries)
	{
		CDFFFormat *pDFFFile = it.first;
		pDFFFile->unload();
		delete pDFFFile;
	}
	//veCDFFFormats.clear();
	umapDFFEntries.clear();
	delete pBuildTXDDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestBuildTXD");
}

void		CTaskDispatchManager::onRequestIMGVersionSettings(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestIMGVersionSettings");

	// ensure a tab is open
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_50"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_50"), MB_OK);
		getIMGF()->getTaskManager()->onTaskEnd("onRequestIMGVersionSettings", true);
		return;
	}

	// ensure IMG version has settings
	if (getIMGF()->getEntryListTab()->getIMGFile()->getVersion() != IMG_FASTMAN92)
	{
		CInputManager::showMessage(CLocalizationManager::get()->getTranslatedText("TextPopup_51"), CLocalizationManager::get()->getTranslatedText("TextPopupTitle_51"), MB_OK);
		getIMGF()->getTaskManager()->onTaskEnd("onRequestIMGVersionSettings", true);
		return;
	}

	// show IMG Version Settings window
	getIMGF()->getTaskManager()->onTaskPause();
	CIMGVersionSettingsDialogData *pIMGVersionSettingsDialogData = getIMGF()->getPopupGUIManager()->showIMGVersionSettingsDialog();
	getIMGF()->getTaskManager()->onTaskUnpause();

	if (!pIMGVersionSettingsDialogData->m_bSave)
	{
		delete pIMGVersionSettingsDialogData;
		getIMGF()->getTaskManager()->onTaskEnd("onRequestIMGVersionSettings", true);
		return;
	}

	// fetch selected entries
	vector<CIMGEntry*> vecSelectedIMGEntries = getIMGF()->getEntryListTab()->getSelectedEntries();
	
	// choose IMG entries
	vector<CIMGEntry*> vecIMGEntries;
	if (pIMGVersionSettingsDialogData->m_ucEntriesType == 0) // All entries in active tab
	{
		vecIMGEntries = getIMGF()->getEntryListTab()->getIMGFile()->getEntries();
	}
	else if (pIMGVersionSettingsDialogData->m_ucEntriesType == 1) // Selected entries in active tab
	{
		vecIMGEntries = vecSelectedIMGEntries;
	}

	// apply new compression type to IMG entries
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntries.size());
	vector<string> vecEntryNames;
	for (auto pIMGEntry : vecIMGEntries)
	{
		pIMGEntry->applyCompression(pIMGVersionSettingsDialogData->m_eCompressionAlgorithm, pIMGVersionSettingsDialogData->m_uiCompressionLevel);
		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
		vecEntryNames.push_back(pIMGEntry->getEntryName());

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// update IMG version text in main window
	getIMGF()->getEntryListTab()->updateIMGText();

	// log
	// todo rename getCompressionTypeText to alrogrfirmtm
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_121", CIMGManager::getCompressionTypeText(pIMGVersionSettingsDialogData->m_eCompressionAlgorithm).c_str(), vecIMGEntries.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_122"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecEntryNames, "\n"), true);

	// mark as modified since rebuild
	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);

	// clean up
	delete pIMGVersionSettingsDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestIMGVersionSettings");
}

void		CTaskDispatchManager::onRequestFeatureByName(string strFeatureName)
{
	if (strFeatureName == "onRequestFeatureByName")
	{
	}
	else if (strFeatureName == "chooseFilesToOpen")
	{
		chooseFilesToOpen();
	}
	else if (strFeatureName == "openFile")
	{
		openFile(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Open2_IMGPath());
	}
	else if (strFeatureName == "onRequestClose")
	{
		onRequestClose();
	}
	else if (strFeatureName == "onRequestCloseAll")
	{
		onRequestCloseAll();
	}
	else if (strFeatureName == "onRequestExitTool")
	{
		onRequestExitTool();
	}
	else if (strFeatureName == "onRequestImportViaFiles")
	{
		onRequestImportViaFiles();
	}
	else if (strFeatureName == "onRequestRemoveSelected")
	{
		onRequestRemoveSelected();
	}
	else if (strFeatureName == "onRequestRenameEntry")
	{
		onRequestRenameEntry();
	}
	else if (strFeatureName == "onRequestSelectAll")
	{
		onRequestSelectAll();
	}
	else if (strFeatureName == "onRequestSelectInverse")
	{
		onRequestSelectInverse();
	}
	else if (strFeatureName == "onRequestRebuild")
	{
		onRequestRebuild();
	}
	else if (strFeatureName == "onRequestRebuildAs")
	{
		onRequestRebuildAs();
	}
	else if (strFeatureName == "onRequestRebuildAll")
	{
		onRequestRebuildAll();
	}
	else if (strFeatureName == "onRequestConvertIMGVersion")
	{
		onRequestConvertIMGVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Convert_IMGVersion());
	}
	else if (strFeatureName == "onRequestConvertIMGVersionViaButton")
	{
		onRequestConvertIMGVersionViaButton();
	}
	else if (strFeatureName == "onRequestMerge")
	{
		onRequestMerge();
	}
	else if (strFeatureName == "onRequestSplitViaButton")
	{
		onRequestSplitViaButton();
	}
	else if (strFeatureName == "onRequestSplitSelectedEntries")
	{
		onRequestSplitSelectedEntries();
	}
	else if (strFeatureName == "onRequestSplitViaIDEFile")
	{
		onRequestSplitViaIDEFile();
	}
	else if (strFeatureName == "onRequestSplitViaTextLines")
	{
		onRequestSplitViaTextLines();
	}
	else if (strFeatureName == "onRequestReplace")
	{
		onRequestReplace();
	}
	else if (strFeatureName == "onRequestExportSelected")
	{
		onRequestExportSelected();
	}
	else if (strFeatureName == "onRequestSearchText")
	{
		onRequestSearchText();
	}
	else if (strFeatureName == "onRequestSearchSelection")
	{
		onRequestSearchSelection();
	}
	else if (strFeatureName == "onRequestFilter")
	{
		onRequestFilter();
	}
	else if (strFeatureName == "onRequestFind")
	{
		onRequestFind();
	}
	else if (strFeatureName == "onRequestExportViaButton")
	{
		onRequestExportViaButton();
	}
	else if (strFeatureName == "onRequestExportViaIDEFile")
	{
		onRequestExportViaIDEFile();
	}
	else if (strFeatureName == "onRequestExportViaTextLines")
	{
		onRequestExportViaTextLines();
	}
	else if (strFeatureName == "onRequestSortEntries")
	{
		onRequestSortEntries();
	}
	else if (strFeatureName == "onRequestSortButton")
	{
		onRequestSortButton();
	}
	else if (strFeatureName == "onRequestRemoveViaIDEFile")
	{
		onRequestRemoveViaIDEFile();
	}
	else if (strFeatureName == "onRequestRemoveViaTextLines")
	{
		onRequestRemoveViaTextLines();
	}
	else if (strFeatureName == "onRequestRemoveViaButton")
	{
		onRequestRemoveViaButton();
	}
	else if (strFeatureName == "onRequestImportViaButton")
	{
		onRequestImportViaButton();
	}
	else if (strFeatureName == "onRequestImportViaIDEFile")
	{
		onRequestImportViaIDEFile();
	}
	else if (strFeatureName == "onRequestImportViaTextLines")
	{
		onRequestImportViaTextLines();
	}
	else if (strFeatureName == "onRequestNew")
	{
		onRequestNew(getIMGF()->getLastUsedValueManager()->getLastUsedValue_New_IMGVersion());
	}
	else if (strFeatureName == "onRequestStats")
	{
		onRequestStats();
	}
	else if (strFeatureName == "onRequestNameCase")
	{
		onRequestNameCase(getIMGF()->getLastUsedValueManager()->getLastUsedValue_NameCase_CaseType(), getIMGF()->getLastUsedValueManager()->getLastUsedValue_NameCase_FilenameType());
	}
	else if (strFeatureName == "onRequestCopyEntryData")
	{
		onRequestCopyEntryData(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Copy_IMGEntryProperty());
	}
	else if (strFeatureName == "onRequestShift")
	{
		onRequestShift(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Shift_Direction());
	}
	else if (strFeatureName == "onRequestQuickExport")
	{
		onRequestQuickExport();
	}
	else if (strFeatureName == "onRequestSelectViaFileExtension")
	{
		onRequestSelectViaFileExtension();
	}
	else if (strFeatureName == "onRequestSelectViaRWVersion")
	{
		onRequestSelectViaRWVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Select_RWVersion());
	}
	else if (strFeatureName == "onRequestVersion")
	{
		onRequestVersion();
	}
	else if (strFeatureName == "onRequestTextureList")
	{
		onRequestTextureList();
	}
	else if (strFeatureName == "onRequestAssociateIMGExtension")
	{
		onRequestAssociateIMGExtension();
	}
	else if (strFeatureName == "onRequestSaveLog")
	{
		onRequestSaveLog(getIMGF()->getLastUsedValueManager()->getLastUsedValue_SaveLog_ActiveTab(), getIMGF()->getLastUsedValueManager()->getLastUsedValue_SaveLog_NormalFormat());
	}
	else if (strFeatureName == "onRequestSaveSession")
	{
		onRequestSaveSession();
	}
	else if (strFeatureName == "onRequestSettings")
	{
		onRequestSettings();
	}
	else if (strFeatureName == "onRequestReopen")
	{
		onRequestReopen();
	}
	else if (strFeatureName == "onRequestConvertDFFToRWVersion")
	{
		onRequestConvertDFFToRWVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertDFF_RWVersion());
	}
	else if (strFeatureName == "onRequestMissingTextures")
	{
		onRequestMissingTextures();
	}
	else if (strFeatureName == "onRequestClose2")
	{
		onRequestClose2(getIMGF()->getLastUsedValueManager()->getLastUsedValue_Close2_CloseAll());
	}
	else if (strFeatureName == "onRequestReplaceAllFromFolder")
	{
		onRequestReplaceAllFromFolder();
	}
	else if (strFeatureName == "onRequestExportAllEntriesFromAllTabs")
	{
		onRequestExportAllEntriesFromAllTabs();
	}
	else if (strFeatureName == "onRequestExportEntriesViaIDEFileFromAllTabs")
	{
		onRequestExportEntriesViaIDEFileFromAllTabs();
	}
	else if (strFeatureName == "onRequestExportEntriesViaTextLinesFromAllTabs")
	{
		onRequestExportEntriesViaTextLinesFromAllTabs();
	}
	else if (strFeatureName == "onRequestImportViaFolder")
	{
		onRequestImportViaFolder();
	}
	else if (strFeatureName == "onRequestDuplicateEntries")
	{
		onRequestDuplicateEntries();
	}
	else if (strFeatureName == "onRequestExportAllEntriesFromAllTabsIntoMultipleFolders")
	{
		onRequestExportAllEntriesFromAllTabsIntoMultipleFolders();
	}
	else if (strFeatureName == "onRequestOpenLast")
	{
		onRequestOpenLast();
	}
	else if (strFeatureName == "onRequestConvertTXDToGame")
	{
		onRequestConvertTXDToGame(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertTXD_Game());
	}
	else if (strFeatureName == "onRequestConvertTXDToRWVersion")
	{
		onRequestConvertTXDToRWVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertTXD_RWVersion());
	}
	else if (strFeatureName == "onRequestDump")
	{
		onRequestDump();
	}
	else if (strFeatureName == "onRequestSessionManager")
	{
		onRequestSessionManager();
	}
	else if (strFeatureName == "onRequestWebsite")
	{
		onRequestWebsite();
	}
	else if (strFeatureName == "onRequestOpenLogBasic")
	{
		onRequestOpenLogBasic();
	}
	else if (strFeatureName == "onRequestOpenLogExtended")
	{
		onRequestOpenLogExtended();
	}
	else if (strFeatureName == "onRequestOpenLogFolder")
	{
		onRequestOpenLogFolder();
	}
	else if (strFeatureName == "onRequestProcessLSTFile")
	{
		onRequestProcessLSTFile();
	}
	else if (strFeatureName == "onRequestSelectViaIDE")
	{
		onRequestSelectViaIDE();
	}
	else if (strFeatureName == "onRequestExportViaIPLFile")
	{
		onRequestExportViaIPLFile();
	}
	else if (strFeatureName == "onRequestRenameIMG")
	{
		onRequestRenameIMG();
	}
	else if (strFeatureName == "onRequestUpdate")
	{
		onRequestUpdate();
	}
	else if (strFeatureName == "onRequestAutoUpdate")
	{
		onRequestAutoUpdate();
	}
	else if (strFeatureName == "onRequestSaveIMGSignature")
	{
		onRequestSaveIMGSignature();
	}
	else if (strFeatureName == "onRequestVerifyIMGSignature")
	{
		onRequestVerifyIMGSignature();
	}
	else if (strFeatureName == "onRequestCompareIMG")
	{
		onRequestCompareIMG();
	}
	else if (strFeatureName == "onRequestConvertTXDToTextureFormat")
	{
		onRequestConvertTXDToTextureFormat(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertTXD_TextureFormat());
	}
	else if (strFeatureName == "onRequestClearLogs")
	{
		onRequestClearLogs(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ClearLogs_AllTabs());
	}
	else if (strFeatureName == "onRequestValidateAllDFFInActiveTab")
	{
		onRequestValidateAllDFFInActiveTab();
	}
	else if (strFeatureName == "onRequestValidateAllTXDInActiveTab")
	{
		onRequestValidateAllTXDInActiveTab();
	}
	else if (strFeatureName == "onRequestCredits")
	{
		onRequestCredits();
	}
	else if (strFeatureName == "onRequestEntryViewer")
	{
		onRequestEntryViewer();
	}
	else if (strFeatureName == "onRequestRenamer")
	{
		onRequestRenamer();
	}
	else if (strFeatureName == "onRequestClearRecentlyOpenedList")
	{
		onRequestClearRecentlyOpenedList();
	}
	else if (strFeatureName == "onRequestBuildTXD")
	{
		onRequestBuildTXD();
	}
	else if (strFeatureName == "onRequestIMGVersionSettings")
	{
		onRequestIMGVersionSettings();
	}
	else if (strFeatureName == "onRequestConvertCOLtoCOLVersion")
	{
		onRequestConvertCOLtoCOLVersion(getIMGF()->getLastUsedValueManager()->getLastUsedValue_ConvertCOL_COLVersion());
	}
	else if (strFeatureName == "onRequestReportIssueOrIdea")
	{
		onRequestReportIssueOrIdea();
	}
	else if (strFeatureName == "onRequestSortViaColumn")
	{
		onRequestSortViaColumn(getIMGF()->getLastUsedValueManager()->getLastUsedValue_SortViaColumn_Column());
	}
	else if (strFeatureName == "onRequestCenterCOLCollisionMeshes")
	{
		onRequestCenterCOLCollisionMeshes();
	}
	else if (strFeatureName == "onRequestAlignCOLCollisionMeshesToDFFMesh")
	{
		onRequestAlignCOLCollisionMeshesToDFFMesh();
	}
	else if (strFeatureName == "onRequestConvertDFFFileToWDRFile")
	{
		onRequestConvertDFFFileToWDRFile();
	}
	else if (strFeatureName == "onRequestTXDOrganizer")
	{
		onRequestTXDOrganizer();
	}
	else if (strFeatureName == "onRequestConvertWTDFileToTXDFile")
	{
		onRequestConvertWTDFileToTXDFile();
	}
	else if (strFeatureName == "onRequestDATPathsMover")
	{
		onRequestDATPathsMover();
	}
	else if (strFeatureName == "onRequestExportViaDATFile")
	{
		onRequestExportViaDATFile();
	}
	else if (strFeatureName == "onRequestMapMoverAndIDShifter")
	{
		onRequestMapMoverAndIDShifter();
	}
	else if (strFeatureName == "onRequestDATModelList")
	{
		onRequestDATModelList();
	}
	else if (strFeatureName == "onRequestFindTXDMissingFromIMGFoundInIDE")
	{
		onRequestFindTXDMissingFromIMGFoundInIDE();
	}
	else if (strFeatureName == "onRequestFindCOLMissingFromCOLFoundInIDE")
	{
		onRequestFindCOLMissingFromCOLFoundInIDE();
	}
	else if (strFeatureName == "onRequestFindDFFMissingFromIMGFoundInIDE")
	{
		onRequestFindDFFMissingFromIMGFoundInIDE();
	}
	else if (strFeatureName == "onRequestCloneIMG")
	{
		onRequestCloneIMG();
	}
	else if (strFeatureName == "onRequestOpenIMGFolder")
	{
		onRequestOpenIMGFolder();
	}
	else if (strFeatureName == "onRequestRemoveOrphanTexturesFromModel")
	{
		onRequestRemoveOrphanTexturesFromModel();
	}
	else if (strFeatureName == "onRequestNewWindow")
	{
		onRequestNewWindow();
	}
	else if (strFeatureName == "onRequestOrphanDFFEntriesNotInCOL")
	{
		onRequestOrphanDFFEntriesNotInCOL();
	}
	else if (strFeatureName == "onRequestOrphanIDEEntriesNotInCOL")
	{
		onRequestOrphanIDEEntriesNotInCOL();
	}
	else if (strFeatureName == "onRequestOrphanCOLEntriesNotInIDE")
	{
		onRequestOrphanCOLEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanDFFEntriesNotInIDE")
	{
		onRequestOrphanDFFEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanIMGEntriesNotInIDE")
	{
		onRequestOrphanIMGEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanIPLEntriesNotInIDE")
	{
		//onRequestOrphanIPLEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanTXDEntriesNotInIDE")
	{
		onRequestOrphanTXDEntriesNotInIDE();
	}
	else if (strFeatureName == "onRequestOrphanIDEEntriesNotInIMG")
	{
		onRequestOrphanIDEEntriesNotInIMG();
	}
	else if (strFeatureName == "onRequestFindDFFMissingFromIDEFoundInIPL")
	{
		onRequestFindDFFMissingFromIDEFoundInIPL();
	}

	else
	{
	}
}

void		CTaskDispatchManager::onRequestLastFeatureUsed(void)
{
	string strPreviousTaskName = getIMGF()->getTaskManager()->getPreviousTaskName();
	if (strPreviousTaskName == "")
	{
		return;
	}

	onRequestFeatureByName(strPreviousTaskName);
}

void		CTaskDispatchManager::onRequestConvertCOLtoCOLVersion(CCOLVersion *pCOLVersion)
{
	/*
	todo
	getIMGF()->getLastUsedValueManager()->setLastUsedValue_ConvertCOL_COLVersion(pCOLVersion);
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertCOLtoCOLVersion");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertCOLtoCOLVersion", true);
		return;
	}

	// fetch selected entries
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertCOLtoCOLVersion", true);
		return;
	}
	uint32 uiEntryCount = 0;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetItemCount());

	CIMGEntry *pIMGEntry = nullptr;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) != "COL")
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaMemory(pIMGEntry->getEntryData());
		if (pCOLFile->doesHaveError())
		{
			pCOLFile->unload();
			delete pCOLFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}
		for (auto pCOLEntry : pCOLFile->getEntries())
		{
			pCOLEntry->setCOLVersion(pCOLVersion);
		}

		string strNewEntryData = pCOLFile->storeViaMemory();
		pCOLFile->unload();
		delete pCOLFile;

		pIMGEntry->setEntryData(strNewEntryData);

		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);

		getIMGF()->getTaskManager()->onTaskProgressTick();
		uiEntryCount++;
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_123", uiEntryCount, pCOLVersion->getText().c_str()));

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);

	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertCOLtoCOLVersion");
	*/
}

void			CTaskDispatchManager::onRequestReportIssueOrIdea(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestReportIssueOrIdea");
	ShellExecute(NULL, L"open", L"http://mvec.io/todo/project/4", NULL, NULL, SW_SHOWNORMAL);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestReportIssueOrIdea");
}

uint32 uiSortPreviousColumnIndex;
bool bSortDirectionIsAscending = true;

int CALLBACK		CTaskDispatchManager::sortMainListView(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	/*
	todo
	int nRetVal = 0;

	CListCtrl *pListCtrl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);

	CIMGEntry *pIMGEntry1 = (CIMGEntry*)lParam1;
	CIMGEntry *pIMGEntry2 = (CIMGEntry*)lParam2;

	switch (lParamSort)
	{
	case 0: // ID
		break;

	case 1: // Type
		nRetVal = strcmp(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry1->getEntryName())).c_str(), CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry2->getEntryName())).c_str());
		break;

	case 2: // Name
		nRetVal = strcmp(pIMGEntry1->getEntryName().c_str(), pIMGEntry2->getEntryName().c_str());
		break;

	case 3: // Offset
		nRetVal = pIMGEntry1->getEntryOffset() - pIMGEntry2->getEntryOffset();
		break;

	case 4: // Size
		nRetVal = pIMGEntry1->getEntrySize() - pIMGEntry2->getEntrySize();
		break;

	case 5: // RW Version / Resource Type
		break;

	default:
		break;
	}

	if (!bSortDirectionIsAscending)
	{
		nRetVal = -nRetVal;
	}

	return nRetVal;
	*/
	return 0;
}

bool sortViaColumn_Type(CIMGEntry *pIMGEntry1, CIMGEntry *pIMGEntry2)
{
	int32 iResult = strcmp(CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry1->getEntryName())).c_str(), CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry2->getEntryName())).c_str());
	if (bSortDirectionIsAscending)
	{
		return iResult < 0;
	}
	else
	{
		return iResult > 0;
	}
}
bool sortViaColumn_Name(CIMGEntry *pIMGEntry1, CIMGEntry *pIMGEntry2)
{
	int32 iResult = strcmp(pIMGEntry1->getEntryName().c_str(), pIMGEntry2->getEntryName().c_str());
	if (bSortDirectionIsAscending)
	{
		return iResult < 0;
	}
	else
	{
		return iResult > 0;
	}
}
bool sortViaColumn_Offset(CIMGEntry *pIMGEntry1, CIMGEntry *pIMGEntry2)
{
	if (bSortDirectionIsAscending)
	{
		return pIMGEntry1->getEntryOffset() < pIMGEntry2->getEntryOffset();
	}
	else
	{
		return pIMGEntry1->getEntryOffset() > pIMGEntry2->getEntryOffset();
	}
}
bool sortViaColumn_Size(CIMGEntry *pIMGEntry1, CIMGEntry *pIMGEntry2)
{
	if (bSortDirectionIsAscending)
	{
		return pIMGEntry1->getEntrySize() < pIMGEntry2->getEntrySize();
	}
	else
	{
		return pIMGEntry1->getEntrySize() > pIMGEntry2->getEntrySize();
	}
}
bool sortViaColumn_ExtraInfo(CIMGEntry *pIMGEntry1, CIMGEntry *pIMGEntry2)
{
	return false;// strcmp(pIMGEntry1->getEntryName().c_str(), pIMGEntry2->getEntryName().c_str());
}

void			CTaskDispatchManager::onRequestSortViaColumn(uint32 uiColumnIndex)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSortViaColumn");
	if (uiColumnIndex == uiSortPreviousColumnIndex)
	{
		bSortDirectionIsAscending = !bSortDirectionIsAscending;
	}
	CListCtrl *pListCtrl = (CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37);
	CIMGFormat *pIMGFile = getIMGF()->getEntryListTab()->getIMGFile();
	if (uiColumnIndex == 1) // Type
	{
		std::sort(pIMGFile->getEntries().begin(), pIMGFile->getEntries().end(), sortViaColumn_Type);
	}
	else if (uiColumnIndex == 2) // Name
	{
		std::sort(pIMGFile->getEntries().begin(), pIMGFile->getEntries().end(), sortViaColumn_Name);
	}
	else if (uiColumnIndex == 3) // Offset
	{
		std::sort(pIMGFile->getEntries().begin(), pIMGFile->getEntries().end(), sortViaColumn_Offset);
	}
	else if (uiColumnIndex == 4) // Size
	{
		std::sort(pIMGFile->getEntries().begin(), pIMGFile->getEntries().end(), sortViaColumn_Size);
	}
	else if (uiColumnIndex == 5) // Extra Info
	{
		//std::sort(pIMGFile->getEntries().begin(), pIMGFile->getEntries().end(), sortViaColumn_ExtraInfo);
	}
	pListCtrl->SortItems(sortMainListView, uiColumnIndex);
	getIMGF()->getEntryListTab()->reassignEntryIds();
	uiSortPreviousColumnIndex = uiColumnIndex;
	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestSortViaColumn");
	*/
}

void			CTaskDispatchManager::onRequestCenterCOLCollisionMeshes(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestCenterCOLCollisionMeshes");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCenterCOLCollisionMeshes", true);
		return;
	}

	// fetch selected entries
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCenterCOLCollisionMeshes", true);
		return;
	}
	uint32 uiEntryCount = 0;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());

	CIMGEntry *pIMGEntry = nullptr;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (CString2::toUpperCase(CPathManager::getFileExtension(pIMGEntry->getEntryName())) != "COL")
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaMemory(pIMGEntry->getEntryData());
		if (pCOLFile->doesHaveError())
		{
			delete pCOLFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}
		for (auto pCOLEntry : pCOLFile->getEntries())
		{
			if (pCOLEntry->getCollisionMeshVertexCount() > 1)
			{
				vector<Vec3f>& vecVertices = (vector<Vec3f>&) pCOLEntry->getCollisionMeshVertices(); // Vec3f is the same size and data types as TVertex so the cast should work.
				Vec3f vecCollisionMeshCenter = CMath::getPolygonCenter(vecVertices);
				if (vecCollisionMeshCenter != 0.0f)
				{
					pCOLEntry->applyCollisionMeshVerticesOffset(-vecCollisionMeshCenter);
				}
			}
		}

		string strNewEntryData = pCOLFile->storeViaMemory();
		pCOLFile->unload();
		delete pCOLFile;

		pIMGEntry->setEntryData(strNewEntryData);
		
		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);

		getIMGF()->getTaskManager()->onTaskProgressTick();
		uiEntryCount++;
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_124", uiEntryCount));

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);

	getIMGF()->getTaskManager()->onTaskEnd("onRequestCenterCOLCollisionMeshes");
	*/
}

void			CTaskDispatchManager::onRequestAlignCOLCollisionMeshesToDFFMesh(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestAlignCOLCollisionMeshesToDFFMesh");

	// choose DFFs folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strDFFFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_8"), getIMGF()->getLastUsedDirectory("ALIGNCOLMESHTODFFMESH_DFF"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strDFFFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestAlignCOLCollisionMeshesToDFFMesh", true);
		return;
	}
	strDFFFolderPath = CPathManager::addSlashToEnd(strDFFFolderPath);
	getIMGF()->setLastUsedDirectory("ALIGNCOLMESHTODFFMESH_DFF", strDFFFolderPath);

	// choose COLs folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strCOLFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_7"), getIMGF()->getLastUsedDirectory("ALIGNCOLMESHTODFFMESH_COL"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strCOLFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestAlignCOLCollisionMeshesToDFFMesh", true);
		return;
	}
	strCOLFolderPath = CPathManager::addSlashToEnd(strCOLFolderPath);
	getIMGF()->setLastUsedDirectory("ALIGNCOLMESHTODFFMESH_COL", strCOLFolderPath);

	// initialize
	unordered_map<string, Vec3f> umapGeometryPolygonCenters;
	vector<string>
		vecFilePaths_DFF = CFileManager::getFileNamesByExtension(strDFFFolderPath, "dff"),
		vecFilePaths_BSP = CFileManager::getFileNamesByExtension(strDFFFolderPath, "bsp"),
		vecFilePaths_COL = CFileManager::getFileNamesByExtension(strCOLFolderPath, "col");

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecFilePaths_DFF.size() + vecFilePaths_COL.size());

	vecFilePaths_DFF = CStdVector::combineVectors(vecFilePaths_DFF, vecFilePaths_BSP);
	
	// fetch DFF texture names and mesh centers
	for (string strFilePath : vecFilePaths_DFF)
	{
		CDFFFormat *pDFFFile = CDFFManager::get()->parseViaFile(strFilePath);
		if(pDFFFile->doesHaveError())
		{
			pDFFFile->unload();
			delete pDFFFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}
		
		vector<CRWSection*> vecDFFGeometrySections = pDFFFile->getSectionsByType(RW_SECTION_GEOMETRY);
		for (CRWSection *pRWSection : vecDFFGeometrySections)
		{
			CRWSection_Geometry *pGeometry = (CRWSection_Geometry*) pRWSection;

			string strTextureDiffuseName = pGeometry->getTextureDiffuseName();
			vector<Vec3f> vecVertices = pGeometry->getVertexPositions();
			Vec3f vecPolygonCenter = CMath::getPolygonCenter(vecVertices);
			umapGeometryPolygonCenters[CString2::toUpperCase(strTextureDiffuseName)] = vecPolygonCenter;
		}

		pDFFFile->unload();
		delete pDFFFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// check if COL mesh centers are the same as DFF mesh centers, if not then align the COLs to match DFFs
	for (string strFilePath : vecFilePaths_COL)
	{
		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(strFilePath);
		if(pCOLFile->doesHaveError())
		{
			pCOLFile->unload();
			delete pCOLFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}
		pCOLFile->setFilePath(strFilePath);

		for (auto pCOLEntry : pCOLFile->getEntries())
		{
			if (umapGeometryPolygonCenters.find(CString2::toUpperCase(pCOLEntry->getModelName())) == umapGeometryPolygonCenters.end())
			{
				continue;
			}
			Vec3f vecDFFPolygonCenter = umapGeometryPolygonCenters[CString2::toUpperCase(pCOLEntry->getModelName())];

			if (pCOLEntry->getCollisionMeshVertexCount() > 1)
			{
				vector<Vec3f>& vecVertices = (vector<Vec3f>&) pCOLEntry->getCollisionMeshVertices(); // Vec3f is the same size and data types as TVertex so the cast should work.
				Vec3f vecCollisionMeshCenter = CMath::getPolygonCenter(vecVertices);
				if (vecCollisionMeshCenter != vecDFFPolygonCenter)
				{
					pCOLEntry->applyCollisionMeshVerticesOffset(-(vecCollisionMeshCenter - vecDFFPolygonCenter));
				}
			}
		}

		pCOLFile->serializeViaFile();

		pCOLFile->unload();
		delete pCOLFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}
	
	string strLogText = CLocalizationManager::get()->getTranslatedFormattedText("Log_AlignMeshes_COL_DFF", vecFilePaths_COL.size());
	if (getIMGF()->getIMGEditor()->getTabs().getEntryCount() > 0)
	{
		getIMGF()->getEntryListTab()->log(strLogText);
	}
	else
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(strLogText);
	}

	getIMGF()->getTaskManager()->onTaskEnd("onRequestAlignCOLCollisionMeshesToDFFMesh");
}

void			CTaskDispatchManager::onRequestConvertDFFFileToWDRFile(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertDFFFileToWDRFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFFileToWDRFile", true);
		return;
	}

	// fetch selected entries
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFFileToWDRFile", true);
		return;
	}
	uint32 uiEntryCount = 0;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());

	CIMGEntry *pIMGEntry = nullptr;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (!pIMGEntry->isModelFile())
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
		if (pDFFFile->doesHaveError())
		{
			pDFFFile->unload();
			delete pDFFFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CIntermediateModelFormat *pGeneralModelFile = pDFFFile->convertToIntermediateModelFormat();
		CWDRFormat *pWDRFile = CWDRManager::get()->convertIntermediateModelFileToWDRFile(pGeneralModelFile);
		pGeneralModelFile->unload();
		delete pGeneralModelFile;
		string strWDRFileData = pWDRFile->serializeViaMemory();
		pWDRFile->unload();
		delete pWDRFile;

		pIMGEntry->setEntryName(CPathManager::replaceFileExtension(pIMGEntry->getEntryName(), "wdr"));
		pIMGEntry->setEntryData(strWDRFileData);
		
		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);
		
		pDFFFile->unload();
		delete pDFFFile;
		
		getIMGF()->getTaskManager()->onTaskProgressTick();
		uiEntryCount++;
	}

	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_Convert_DFF_WDR", uiEntryCount));

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertDFFFileToWDRFile");
	*/
}

void				CTaskDispatchManager::onRequestTXDOrganizer(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestTXDOrganizer");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestTXDOrganizer", true);
		return;
	}

	CTXDOrganizerDialogData *pTXDOrganizerDialogData = getIMGF()->getPopupGUIManager()->showTXDOrganizerDialog();

	if (!pTXDOrganizerDialogData->m_bOrganize)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestTXDOrganizer", true);
		return;
	}

	vector<string> vecFilePaths;
	if (pTXDOrganizerDialogData->m_bIDEUpdate)
	{
		vecFilePaths = CFileManager::getFilePaths(pTXDOrganizerDialogData->m_strIDEUpdateFolderPath, true);
	}

	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetItemCount() + (pTXDOrganizerDialogData->m_bIDEUpdate ? vecFilePaths.size() : 0));

	uint32 uiTXDCount = 0;
	CTXDFormat *pTXDFile = CTXDManager::get()->createFormat();
	pTXDFile->setDeviceId(0);
	pTXDFile->setRWVersion(CRWManager::get()->getVersionManager()->getEntryByVersionId(RW_VERSION_3_6_0_3));

	CIMGEntry *pIMGEntry = nullptr;
	uint32
		uiEntryCount = 0,
		uiDFFFileCount = 0;
	unordered_map<string, string> umapNewEntryNames;
	unordered_map<string, bool> umapTextureNamesUsedInTXD;

	for (uint32 i = 0, j = pListControl->GetItemCount(); i < j; i++)
	{
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(i);

		if (!pIMGEntry->isModelFile())
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
		if (pDFFFile->doesHaveError())
		{
			pDFFFile->unload();
			delete pDFFFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		vector<string> vecDFFTextureNames = pDFFFile->getTextureNames();
		for (string strDFFTextureName : vecDFFTextureNames)
		{
			// check if texture is already in TXD
			if (umapTextureNamesUsedInTXD.find(CString2::toUpperCase(strDFFTextureName)) != umapTextureNamesUsedInTXD.end())
			{
				continue;
			}

			// check if texture file exists
			string strTextureImagePath = CFileManager::findImageFile(strDFFTextureName, pTXDOrganizerDialogData->m_strTextureImportFolderPath);
			if (strTextureImagePath != "")
			{
				// add texture to TXD
				umapTextureNamesUsedInTXD[CString2::toUpperCase(strDFFTextureName)] = true;
				CRWSection_TextureNative *pTexture = pTXDFile->addTextureViaFile(strTextureImagePath, strDFFTextureName, strDFFTextureName + "a");

				if (pTexture != nullptr)
				{
					vector<string> vecMipmapsRemoved;
					//CDebugger::log("pTXDOrganizerDialogData->m_pTextureFormat->getId(): " + CString2::toString(pTXDOrganizerDialogData->m_pTextureFormat->getId()));
					pTexture->convertToRasterDataFormat(pTXDOrganizerDialogData->m_pRasterDataFormat->getRasterDataFormatId(), vecMipmapsRemoved);
				}
			}
		}

		string strNextTXDFileName = pTXDOrganizerDialogData->m_strTXDNamePrefix + ((uiTXDCount + 1) < 10 ? "0" : "") + CString2::toString(uiTXDCount + 1) + ".txd";
		string strDFFFileNameWithoutExtension = CPathManager::removeFileExtension(pIMGEntry->getEntryName());
		string strTXDFileNameWithoutExtension = CPathManager::removeFileExtension(strNextTXDFileName);
		umapNewEntryNames[strDFFFileNameWithoutExtension] = strTXDFileNameWithoutExtension;

		uiDFFFileCount++;
		if (uiDFFFileCount == pTXDOrganizerDialogData->m_uiEveryNDFFFiles)
		{
			uiTXDCount++;
			string strTXDFileName = pTXDOrganizerDialogData->m_strTXDNamePrefix + (uiTXDCount < 10 ? "0" : "") + CString2::toString(uiTXDCount) + ".txd";
			pTXDFile->storeViaFile(pTXDOrganizerDialogData->m_strOutputFolderPath + strTXDFileName);
			pTXDFile->unload();
			delete pTXDFile;
			pTXDFile = nullptr;
			
			uiDFFFileCount = 0;
			umapTextureNamesUsedInTXD.clear();
			pTXDFile = CTXDManager::get()->createFormat();
			pTXDFile->setDeviceId(0);
			pTXDFile->setRWVersion(CRWManager::get()->getVersionManager()->getEntryByVersionId(RW_VERSION_3_6_0_3));
		}
		
		pDFFFile->unload();
		delete pDFFFile;
		
		getIMGF()->getTaskManager()->onTaskProgressTick();
		uiEntryCount++;
	}

	if (uiDFFFileCount > 0)
	{
		uiTXDCount++;
		string strTXDFileName = pTXDOrganizerDialogData->m_strTXDNamePrefix + (uiTXDCount < 10 ? "0" : "") + CString2::toString(uiTXDCount) + ".txd";
		pTXDFile->storeViaFile(pTXDOrganizerDialogData->m_strOutputFolderPath + strTXDFileName);
		pTXDFile->unload();
		delete pTXDFile;
		pTXDFile = nullptr;
	}
	
	if(pTXDFile != nullptr)
	{
		pTXDFile->unload();
		delete pTXDFile;
		pTXDFile = nullptr;
	}

	// update IDE files
	if (pTXDOrganizerDialogData->m_bIDEUpdate)
	{
		for (string strFilePath : vecFilePaths)
		{
			if (CString2::toUpperCase(CPathManager::getFileExtension(strFilePath)) != "IDE")
			{
				continue;
			}

			CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strFilePath);

			if (pIDEFile->doesHaveError())
			{
				getIMGF()->getTaskManager()->onTaskProgressTick();
				continue;
			}

			for (auto it : umapNewEntryNames)
			{
				string strDFFFileName = it.first;
				string strTXDFileName = it.second;
				vector<CIDEEntry*> vecIDEEntries = pIDEFile->getEntriesByModelName(strDFFFileName);

				for (CIDEEntry *pIDEEntry : vecIDEEntries)
				{
					switch (pIDEEntry->getSectionType())
					{
						// todo - make it work with all IDE sections
					case IDE_SECTION_OBJS:
					{
						CIDEEntry_OBJS *pIDEEntry_OBJS = (CIDEEntry_OBJS*) pIDEEntry;
						pIDEEntry_OBJS->setTXDName(strTXDFileName);
						break;
					}
					case IDE_SECTION_TOBJ:
					{
						CIDEEntry_TOBJ *pIDEEntry_TOBJ = (CIDEEntry_TOBJ*)pIDEEntry;
						pIDEEntry_TOBJ->setTXDName(strTXDFileName);
						break;
					}
					}
				}
			}

			pIDEFile->serializeViaFile();

			pIDEFile->unload();
			delete pIDEFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}

	// log
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_TXDOrganizer", uiEntryCount, uiTXDCount));

	// clean up
	delete pTXDOrganizerDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestTXDOrganizer");
	*/
}

void			CTaskDispatchManager::onRequestConvertWTDFileToTXDFile(void)
{
	/*
	todo
	getIMGF()->getTaskManager()->onTaskBegin("onRequestConvertWTDFileToTXDFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertWTDFileToTXDFile", true);
		return;
	}

	// fetch selected entries
	CListCtrl *pListControl = ((CListCtrl*)getIMGF()->getDialog()->GetDlgItem(37));
	POSITION pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertWTDFileToTXDFile", true);
		return;
	}
	uint32 uiEntryCount = 0;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pListControl->GetSelectedCount());

	CIMGEntry *pIMGEntry = nullptr;
	while (pos)
	{
		int nItem = pListControl->GetNextSelectedItem(pos);
		pIMGEntry = (CIMGEntry*)pListControl->GetItemData(nItem);

		if (!pIMGEntry->isWTDFile())
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		string strEntryData = pIMGEntry->getEntryData();
		CWTDFormat *pWTDFile = CWTDManager::get()->parseViaMemory(strEntryData);
		if (pWTDFile->doesHaveError())
		{
			pWTDFile->unload();
			delete pWTDFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CIntermediateTextureFormat *pGeneralTextureFile = pWTDFile->convertToIntermediateFormat();
		pWTDFile->unload();
		delete pWTDFile;
		CTXDFormat *pTXDFile = CTXDManager::get()->convertIntermediateTextureFileToTXDFile(pGeneralTextureFile);
		pGeneralTextureFile->unload();
		delete pGeneralTextureFile;
		string strTXDFileData = pTXDFile->serializeViaMemory();
		pTXDFile->unload();
		delete pTXDFile;

		pIMGEntry->setEntryName(CPathManager::replaceFileExtension(pIMGEntry->getEntryName(), "txd"));
		pIMGEntry->setEntryData(strTXDFileData);
		
		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);

		getIMGF()->getTaskManager()->onTaskProgressTick();
		uiEntryCount++;
	}

	getIMGF()->getEntryListTab()->log("Converted " + CString2::toString(uiEntryCount) + " WTD file" + (uiEntryCount == 1 ? "" : "s") + " to TXD file" + (uiEntryCount == 1 ? "" : "s") + ".");

	getIMGF()->getEntryListTab()->setIMGModifiedSinceRebuild(true);
	getIMGF()->getTaskManager()->onTaskEnd("onRequestConvertWTDFileToTXDFile");
	*/
}

bool			sortDATFiles(CDATPathFormat *pDATFile_Paths1, CDATPathFormat *pDATFile_Paths2)
{
	return pDATFile_Paths1->m_uiFileIndex < pDATFile_Paths2->m_uiFileIndex;
}
bool			sortDATPathsEntries(CDATEntry_Paths_General_PathNode &pathNode1, CDATEntry_Paths_General_PathNode& pathNode2)
{
	if (pathNode1.m_bIsVehiclePathNode && pathNode2.m_bIsVehiclePathNode)
	{
		return false;
	}
	if (pathNode1.m_bIsVehiclePathNode)
	{
		return true;
	}
	return false;
}
void			CTaskDispatchManager::onRequestDATPathsMover(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestDATPathsMover");
	
	getIMGF()->getTaskManager()->onTaskPause();
	CDATPathsMoverDialogData *pDATPathsMoverDialogData = getIMGF()->getPopupGUIManager()->showDATPathsMoverDialogData();
	getIMGF()->getTaskManager()->onTaskUnpause();

	if (!pDATPathsMoverDialogData->m_bMove)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestDATPathsMover", true);
		return;
	}

	vector<string>
		vecFileNames = CFileManager::getFileNamesByExtension(pDATPathsMoverDialogData->m_strInputFolderPath, "DAT");
	vector<CDATPathFormat*>
		vecDATInputFiles,
		vecDATOutputFiles;
	for (auto strFileName : vecFileNames)
	{
		uint32 uiAreaId = CString2::toNumber(CPathManager::removeFileExtension(strFileName).substr(5)); // example filename: nodes0.dat, nodes1.dat, nodes63.dat

		CDATPathFormat *pDATFile = CDATPathManager::get()->parseViaMemory(CFileManager::getFileContent(pDATPathsMoverDialogData->m_strInputFolderPath + strFileName, true)/*, uiAreaId*/);
		if(!pDATFile->doesHaveError())
		{
			vecDATInputFiles.push_back(pDATFile);
		}
	}
	for (uint32 i = 0, j = CDATPathManager::getTileCount(pDATPathsMoverDialogData->m_vecOutputMapRangeMin, pDATPathsMoverDialogData->m_vecOutputMapRangeMax, pDATPathsMoverDialogData->m_vecOutputTileSize); i < j; i++)
	{
		CDATPathFormat *pDATFile = new CDATPathFormat;
		pDATFile->setPathsFormat(DAT_PATH_FASTMAN92);
		pDATFile->m_uiFileIndex = i;
		vecDATOutputFiles.push_back(pDATFile);
	}
	
	std::sort(vecDATInputFiles.begin(), vecDATInputFiles.end(), sortDATFiles);

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount((vecDATInputFiles.size() * 2) + (vecDATOutputFiles.size() * 4));

	for (auto pDATFile : vecDATInputFiles)
	{
		pDATFile->applyOffsetToPositions(pDATPathsMoverDialogData->m_vecPositionOffset);

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// process
	//unordered_map<CDATEntry_Paths_General_PathNode&, CNodeAddress> umapNewAddresses_PathNode;
	for (auto pDATFile : vecDATInputFiles)
	{
		uint32 uiAreaId_SA = pDATFile->m_uiFileIndex;

		for (auto& pathNode : pDATFile->m_vecPathNodes)
		{
			Vec2f vecPathNodePosition = { (float32)pathNode.m_vecPosition.x / 8.0f, (float32)pathNode.m_vecPosition.y / 8.0f };
			uint32 uiNewAreaIdForPathNode = CDATPathManager::getAreaIdFromPosition(vecPathNodePosition, pDATPathsMoverDialogData->m_vecOutputMapRangeMin, pDATPathsMoverDialogData->m_vecOutputMapRangeMax, pDATPathsMoverDialogData->m_vecOutputTileSize);

			uint32 uiFirstLinkIndex = pathNode.m_wConnectedNodesStartId;
			uint32 uiLinkCountForNode = pathNode.m_uiFlags & 0xF;
			pathNode.m_wConnectedNodesStartId = vecDATOutputFiles[uiNewAreaIdForPathNode]->m_vecLinks.size();

			CDATEntry_Paths_General_Link link;
			for (uint32 i = 0; i < uiLinkCountForNode; i++)
			{
				link = pDATFile->m_vecLinks[uiFirstLinkIndex + i];
				vecDATOutputFiles[uiNewAreaIdForPathNode]->addLink(link);
			}
			//uint32 uiNewPathNodeId = vecDATOutputFiles[uiNewAreaIdForPathNode].size();
			vecDATOutputFiles[uiNewAreaIdForPathNode]->addPathNode(pathNode);
			
			//umapNewAddresses_PathNode[vecDATOutputFiles[uiNewAreaIdForPathNode]->m_vecPathNodes[uiNewPathNodeId]] = { uiNewAreaIdForPathNode, uiNewPathNodeId };
		}

		uint32 i = 0;
		for (auto& naviNode : pDATFile->m_vecNaviNodes)
		{
			Vec2f vecNaviNodePosition = { (float32)naviNode.m_iPosition[0] / 8.0f, (float32)naviNode.m_iPosition[1] / 8.0f };
			uint32 uiNewAreaIdForNaviNode = CDATPathManager::getAreaIdFromPosition(vecNaviNodePosition, pDATPathsMoverDialogData->m_vecOutputMapRangeMin, pDATPathsMoverDialogData->m_vecOutputMapRangeMax, pDATPathsMoverDialogData->m_vecOutputTileSize);

			vecDATOutputFiles[uiNewAreaIdForNaviNode]->addNaviNode(naviNode);
			i++;
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	for (auto pDATFile : vecDATOutputFiles)
	{
		std::sort(pDATFile->m_vecPathNodes.begin(), pDATFile->m_vecPathNodes.end(), sortDATPathsEntries);

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	for (auto pDATFile : vecDATOutputFiles)
	{
		for (auto& naviNode : pDATFile->m_vecNaviNodes)
		{
			// this code is in a separate loop because the new position may not have been applied yet.
			
			auto& targetPathNode_Input = vecDATInputFiles[naviNode.m_usTargetNode_AreaId]->m_vecPathNodes[naviNode.m_usTargetNode_NodeId]; // the position has already been updated for this target node.

			uint32 uiAreaId_Out;
			uint32 uiNodeId_Out;
			bool bFound = CDATPathManager::findPathNode(vecDATOutputFiles, targetPathNode_Input, uiAreaId_Out, uiNodeId_Out);
			if (bFound)
			{
				naviNode.m_usTargetNode_AreaId = uiAreaId_Out;
				naviNode.m_usTargetNode_NodeId = uiNodeId_Out;
			}
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}
	
	for (auto pDATFile : vecDATOutputFiles)
	{
		for (auto& link : pDATFile->m_vecLinks)
		{
			auto& pathNode_Input = vecDATInputFiles[link.m_usAreaId]->m_vecPathNodes[link.m_usNodeId];

			uint32 uiAreaId_Out;
			uint32 uiNodeId_Out;
			bool bFound = CDATPathManager::findPathNode(vecDATOutputFiles, pathNode_Input, uiAreaId_Out, uiNodeId_Out);
			if (bFound)
			{
				link.m_usAreaId = uiAreaId_Out;
				link.m_usNodeId = uiNodeId_Out;
			}



			if (link.m_usNaviAreaId == 0 && link.m_usNaviNodeId == 0)
			{
				// do nothing
			}
			else
			{
				auto& naviNode_Input2 = vecDATInputFiles[link.m_usNaviAreaId]->m_vecNaviNodes[link.m_usNaviNodeId];

				uint32 uiAreaId_Out2;
				uint32 uiNodeId_Out2;
				bool bFound2 = CDATPathManager::findNaviNode(vecDATOutputFiles, naviNode_Input2, uiAreaId_Out2, uiNodeId_Out2);
				if (bFound2)
				{
					link.m_usNaviAreaId = uiAreaId_Out2;
					link.m_usNaviNodeId = uiNodeId_Out2;
				}
			}
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// update target nodes of navi nodes to always be the "lower" node
	/*
	for (auto pDATFile : vecDATOutputFiles)
	{
		uint32 uiNaviNodeAreaId = pDATFile->m_uiFileIndex;
		uint32 uiNaviNodeNodeId = 0;
		for (auto& naviNode : pDATFile->m_vecNaviNodes)
		{
			CDATEntry_Paths_General_PathNode pathNode1 = vecDATOutputFiles[naviNode.m_usTargetNode_AreaId]->m_vecPathNodes[naviNode.m_usTargetNode_NodeId];
			uint32 uiLinkId_Out;
			vector<CDATEntry_Paths_General_PathNode> vecTargetPathNodes = CDATManager::getTargetPathNodesForNaviNode(vecDATOutputFiles, naviNode, uiNaviNodeAreaId, uiNaviNodeNodeId, uiLinkId_Out);
			vecTargetPathNodes.push_back(pathNode1);
			//if (vecTargetPathNodes.size() != 2)
			//{
			//	CDebugger::log("vecTargetPathNodes.size(): " + CString2::toString(vecTargetPathNodes.size()));
			//}

			//CDATEntry_Paths_General_PathNode lowestTargetPathNode = CDATManager::getLowestPathNode(vecTargetPathNodes);
			//naviNode.m_usTargetNode_AreaId = lowestTargetPathNode.m_wAreaId;
			//naviNode.m_usTargetNode_NodeId = lowestTargetPathNode.m_wNodeId;

			CDATEntry_Paths_General_PathNode lowerTargetPathNode = CDATManager::getLowestPathNode(vecTargetPathNodes);
			CDATEntry_Paths_General_PathNode higherTargetPathNode;
			if (vecTargetPathNodes[0].m_vecPosition.x == lowerTargetPathNode.m_vecPosition.x
			 && vecTargetPathNodes[0].m_vecPosition.y == lowerTargetPathNode.m_vecPosition.y
			 && vecTargetPathNodes[0].m_vecPosition.z == lowerTargetPathNode.m_vecPosition.z
			 && vecTargetPathNodes[0].m_ucPathWidth == lowerTargetPathNode.m_ucPathWidth)
			{
				higherTargetPathNode = vecTargetPathNodes[1];
			}
			else
			{
				higherTargetPathNode = vecTargetPathNodes[0];
			}

			auto& link = vecDATOutputFiles[vecTargetPathNodes[0].m_wAreaId]->m_vecLinks[uiLinkId_Out];
			link.m_usNaviAreaId = higherTargetPathNode.m_wAreaId;
			link.m_usNaviNodeId = higherTargetPathNode.m_wNodeId;
			naviNode.m_usTargetNode_AreaId = lowerTargetPathNode.m_wAreaId;
			naviNode.m_usTargetNode_NodeId = lowerTargetPathNode.m_wNodeId;

			//
			CDATEntry_Paths_General_PathNode previousPathNode = vecTargetPathNodes[0];
			naviNode.m_usTargetNode_AreaId = previousPathNode.m_wAreaId;
			naviNode.m_usTargetNode_NodeId = previousPathNode.m_wNodeId;
			naviNode.m_ucDirection[0] = -((int8)naviNode.m_ucDirection[0]);
			naviNode.m_ucDirection[1] = -((int8)naviNode.m_ucDirection[1]);
			
			uint32 uiLeftLaneCount = naviNode.m_uiFlags & 1792;
			uint32 uiRightLaneCount = naviNode.m_uiFlags & 14336;
			
			uint32 uiNewLeftLaneCount = uiRightLaneCount;
			uint32 uiNewRightLaneCount = uiLeftLaneCount;

			naviNode.m_uiFlags &= 0xFFFFF8FF;
			naviNode.m_uiFlags |= uiNewLeftLaneCount;

			naviNode.m_uiFlags &= 0xFFFFC7FF;
			naviNode.m_uiFlags |= uiNewRightLaneCount;
			//

			uiNaviNodeNodeId++;
		}
	}
	*/

	// store output DAT files
	uint32 i = 0;
	for (auto pDATFile : vecDATOutputFiles)
	{
		CFileManager::storeFile(pDATPathsMoverDialogData->m_strOutputFolderPath + "nodes" + CString2::toString(i) + ".dat", pDATFile->serializeViaMemory(), false, true);
		getIMGF()->getTaskManager()->onTaskProgressTick();
		i++;
	}

	// clean up
	for (auto pDATFile : vecDATInputFiles)
	{
		pDATFile->unload();
		delete pDATFile;
	}
	for (auto pDATFile : vecDATOutputFiles)
	{
		pDATFile->unload();
		delete pDATFile;
	}
	delete pDATPathsMoverDialogData;

	getIMGF()->getTaskManager()->onTaskEnd("onRequestDATPathsMover");
}

void			CTaskDispatchManager::onRequestExportViaDATFile(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExportViaDATFile");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaDATFile", true);
		return;
	}

	// choose input DAT GTA files
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecDATPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("EXPORTVIADAT_DAT"), "DAT", true);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecDATPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaDATFile", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("EXPORTVIADAT_DAT", CPathManager::getDirectory(vecDATPaths[0]));

	// choose input game folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strGameFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("EXPORTVIADAT_GAME"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecDATPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaDATFile", true);
		return;
	}
	strGameFolderPath = CPathManager::addSlashToEnd(strGameFolderPath);
	getIMGF()->setLastUsedDirectory("EXPORTVIADAT_GAME", strGameFolderPath);

	// fetch IDE paths from DAT files
	vector<string> vecIDEPaths;
	for (string strDATPath : vecDATPaths)
	{
		CDATLoaderFormat *pDATFile = CDATLoaderManager::get()->parseViaFile(strDATPath);
		if(!pDATFile->doesHaveError())
		{
			vector<string> vecRelativeIDEPaths = pDATFile->getRelativeIDEPaths();
			for (string strRelativeIDEPath : vecRelativeIDEPaths)
			{
				vecIDEPaths.push_back(strGameFolderPath + strRelativeIDEPath);
			}
		}
		pDATFile->unload();
		delete pDATFile;
	}

	// choose input IDE files to export entries from
	getIMGF()->getTaskManager()->onTaskPause();
	string strData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(CLocalizationManager::get()->getTranslatedText("Window_TextArea_8_Title"), CLocalizationManager::get()->getTranslatedText("Window_TextArea_8_Message"), CString2::join(vecIDEPaths, "\r\n"));
	if (strData == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaDATFile", true);
		return;
	}
	getIMGF()->getTaskManager()->onTaskUnpause();

	// choose output folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strOutputFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_12"), getIMGF()->getLastUsedDirectory("EXPORTVIADAT_OUTPUT"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strOutputFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaDATFile", true);
		return;
	}
	strOutputFolderPath = CPathManager::addSlashToEnd(strOutputFolderPath);
	getIMGF()->setLastUsedDirectory("EXPORTVIADAT_OUTPUT", strOutputFolderPath);

	// generate input IDE file objects
	vector<string> vecEntryNames;
	vector<string> vecLines = CString2::split(strData, "\r\n");
	vector<CIDEFormat*> veCIDEFormats;
	for (auto strLine : vecLines)
	{
		strLine = CString2::trim(strLine);
		if (strLine == "")
		{
			continue;
		}

		vecEntryNames.push_back(strLine);
		CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strLine);
		if(!pIDEFile->doesHaveError())
		{
			veCIDEFormats.push_back(pIDEFile);
		}
	}
	vecEntryNames = CStdVector::toUpperCase(vecEntryNames);

	// fetch IDE entry names
	unordered_map<string, CIDEEntry*> umapIDEEntryNamesUpper;
	for (auto pIDEFile : veCIDEFormats)
	{ // todo - make it work with all IDE sections
		for (auto pIDEEntry : pIDEFile->getEntriesBySection<CIDEEntry_OBJS>(IDE_SECTION_OBJS))
		{
			umapIDEEntryNamesUpper[CString2::toUpperCase(pIDEEntry->getModelName())] = pIDEEntry;
			umapIDEEntryNamesUpper[CString2::toUpperCase(pIDEEntry->getTXDName())] = pIDEEntry;
		}
	}

	vector<CIMGEntry*> vecIMGEntriesToExport;
	vector<string> vecExportedEntryNames;
	for (auto pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		string strEntryNameUpperWithoutExtension = CString2::toUpperCase(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));

		if (umapIDEEntryNamesUpper.find(strEntryNameUpperWithoutExtension) != umapIDEEntryNamesUpper.end())
		{
			vecIMGEntriesToExport.push_back(pIMGEntry);
			vecExportedEntryNames.push_back(pIMGEntry->getEntryName());
		}
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIMGEntriesToExport.size());
	getIMGF()->getEntryListTab()->getIMGFile()->exportMultiple(vecIMGEntriesToExport, strOutputFolderPath);
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_Export_DAT", vecIMGEntriesToExport.size()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_77"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecExportedEntryNames, "\n"), true);
	
	for (auto pIDEFile : veCIDEFormats)
	{
		pIDEFile->unload();
		delete pIDEFile;
	}
	
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExportViaDATFile");
}

void						CTaskDispatchManager::onRequestMapMoverAndIDShifter(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestMapMoverAndIDShifter");

	CMapMoverAndIDShifterDialogData *pMapMoverAndIDShifterDialogData = getIMGF()->getPopupGUIManager()->showMapMoverAndIDShifterDialog();
	if (!pMapMoverAndIDShifterDialogData->m_bGo)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMapMoverAndIDShifter", true);
		return;
	}

	unordered_map<ePlatformedGame, vector<string>>
		umapIgnoreDefaultObjectFileNamesVector;
	string
		strDefaultModelNamesFolder = getIMGF()->getInstallationMeta().getProgramFilesPath() + "Default Files/Model Names/",
		strModelNamesPath_PC_GTA_III = strDefaultModelNamesFolder + "Model Names - PC GTA III.txt",
		strModelNamesPath_PC_GTA_VC = strDefaultModelNamesFolder + "Model Names - PC GTA VC.txt",
		strModelNamesPath_PC_GTA_SA = strDefaultModelNamesFolder + "Model Names - PC GTA SA.txt"
	;
	if (CFileManager::doesFileExist(strModelNamesPath_PC_GTA_III))
	{
		umapIgnoreDefaultObjectFileNamesVector[PLATFORMED_GAME_PC_GTA_III] = CString2::split(CFileManager::getFileContent(strModelNamesPath_PC_GTA_III), ", ");
	}
	if (CFileManager::doesFileExist(strModelNamesPath_PC_GTA_VC))
	{
		umapIgnoreDefaultObjectFileNamesVector[PLATFORMED_GAME_PC_GTA_VC] = CString2::split(CFileManager::getFileContent(strModelNamesPath_PC_GTA_VC), ", ");
	}
	if (CFileManager::doesFileExist(strModelNamesPath_PC_GTA_SA))
	{
		umapIgnoreDefaultObjectFileNamesVector[PLATFORMED_GAME_PC_GTA_SA] = CString2::split(CFileManager::getFileContent(strModelNamesPath_PC_GTA_SA), ", ");
	}

	unordered_map<string, bool> umapIgnoreDefaultObjectFileNames;
	for (auto it : umapIgnoreDefaultObjectFileNamesVector)
	{
		for (string& strFileName : it.second)
		{
			umapIgnoreDefaultObjectFileNames[strFileName] = true;
		}
	}
	umapIgnoreDefaultObjectFileNamesVector.clear();

	CDATLoaderFormat *pDATFile = CDATLoaderManager::get()->parseViaFile(pMapMoverAndIDShifterDialogData->m_strDATFilePath);
	if(pDATFile->doesHaveError())
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMapMoverAndIDShifter", true);
		return;
	}
	vector<string>
		vecRelativeIDEPaths = pDATFile->getRelativeIDEPaths(),
		vecRelativeIPLPaths = pDATFile->getRelativeIPLPaths();
	pDATFile->unload();
	delete pDATFile;

	vector<string>
		vecIDEPaths,
		vecIPLPaths;
	uint32 i;
	vecIDEPaths.resize(vecRelativeIDEPaths.size());
	vecIPLPaths.resize(vecRelativeIPLPaths.size());
	i = 0;
	for (string& strRelativeIDEPath : vecRelativeIDEPaths)
	{
		vecIDEPaths[i] = pMapMoverAndIDShifterDialogData->m_strGameFolderPath + strRelativeIDEPath;
		i++;
	}
	i = 0;
	for (string& strRelativeIPLPath : vecRelativeIPLPaths)
	{
		vecIPLPaths[i] = pMapMoverAndIDShifterDialogData->m_strGameFolderPath + strRelativeIPLPath;
		i++;
	}
	vecRelativeIDEPaths.clear();
	vecRelativeIPLPaths.clear();
	if (pMapMoverAndIDShifterDialogData->m_bUpdateIDEInFolder)
	{
		vecIDEPaths = CStdVector::combineVectors(vecIDEPaths, CFileManager::getFilePaths(pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath, true, false, "IDE"));
	}
	if (pMapMoverAndIDShifterDialogData->m_bUpdateIPLInFolder)
	{
		vecIPLPaths = CStdVector::combineVectors(vecIPLPaths, CFileManager::getFilePaths(pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath, true, false, "IPL"));
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecIDEPaths.size() + vecIPLPaths.size());

	uint32 uiIDEEntryNewObjectId = pMapMoverAndIDShifterDialogData->m_uiIDStart;
	unordered_map<uint32, uint32> umapNewObjectIds;
	uint32
		uiIPLCount_Text = 0,
		uiIPLCount_Binary = 0;
	if (pMapMoverAndIDShifterDialogData->m_bShiftIds)
	{
		for (string& strIDEPath : vecIDEPaths)
		{
			bool bIgnoreShifter = pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.find(CString2::toUpperCase(CPathManager::getFileName(strIDEPath))) != pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.end();
			if (bIgnoreShifter)
			{
				// ignore file for ID shifter
				continue;
			}
			CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strIDEPath);
			if(!pIDEFile->doesHaveError())
			{
				for (auto it : pIDEFile->getSectionEntries())
				{
					for (CIDEEntry *pIDEEntry : it.second)
					{
						if (pIDEEntry->getEntryType() == SECTION_LINES_ENTRY_DATA)
						{
							CIDEEntry_Data *pIDEEntry_Data = (CIDEEntry_Data*)pIDEEntry;
							umapNewObjectIds[pIDEEntry_Data->getObjectId()] = uiIDEEntryNewObjectId;
							//pIDEEntry_Data->setObjectId(uiIDEEntryNewObjectId); // todo - must be uncommented
							uiIDEEntryNewObjectId++;
						}
					}
				}

				pIDEFile->setFilePath(pMapMoverAndIDShifterDialogData->m_strOutputFolderPath + CPathManager::getFileName(strIDEPath));
				pIDEFile->serializeViaFile();
			}
			pIDEFile->unload();
			delete pIDEFile;

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}

	for (string& strIPLPath : vecIPLPaths)
	{
		bool
			bIgnoreShifter = !pMapMoverAndIDShifterDialogData->m_bShiftIds,
			bIgnoreMover = !pMapMoverAndIDShifterDialogData->m_bMovePosition;
		if (!bIgnoreShifter)
		{
			bIgnoreShifter = pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.find(CString2::toUpperCase(CPathManager::getFileName(strIPLPath))) != pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames.end();
		}
		if (!bIgnoreMover)
		{
			bIgnoreMover = pMapMoverAndIDShifterDialogData->m_umapMoverIgnoreFilenames.find(CString2::toUpperCase(CPathManager::getFileName(strIPLPath))) != pMapMoverAndIDShifterDialogData->m_umapMoverIgnoreFilenames.end();
		}

		CIPLFormat *pIPLFile = CIPLManager::get()->parseViaFile(strIPLPath);
		if(!pIPLFile->doesHaveError())
		{
			if (pIPLFile->isBinary())
			{
				uiIPLCount_Binary++;
			}
			else
			{
				uiIPLCount_Text++;
			}
			for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_INST>(IPL_SECTION_INST))
			{
				if (umapNewObjectIds.find(pIPLEntry->getObjectId()) != umapNewObjectIds.end())
				{
					if (!bIgnoreShifter)
					{
						pIPLEntry->setObjectId(umapNewObjectIds[pIPLEntry->getObjectId()]);
					}
				}
				if (!bIgnoreMover)
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
			}
			if (!bIgnoreMover)
			{
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_AUZO>(IPL_SECTION_AUZO))
				{
					switch (pIPLEntry->getFormatType())
					{
					case 0:
						pIPLEntry->getLowerLeftPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getLowerLeftPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getLowerLeftPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						pIPLEntry->getUpperRightPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getUpperRightPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getUpperRightPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						break;
					case 1:
						pIPLEntry->getCenterPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getCenterPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getCenterPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						break;
					}
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_CARS>(IPL_SECTION_CARS))
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_CULL>(IPL_SECTION_CULL))
				{
					switch (pIPLEntry->getFormatType())
					{
					case 1:
						pIPLEntry->getLowerLeftPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getLowerLeftPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getLowerLeftPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						pIPLEntry->getUpperRightPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getUpperRightPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getUpperRightPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						/* no break intended */
					case 0:
					case 2:
						pIPLEntry->getCenterPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
						pIPLEntry->getCenterPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
						pIPLEntry->getCenterPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
						break;
					}
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_ENEX>(IPL_SECTION_ENEX))
				{
					pIPLEntry->getEntrancePosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getEntrancePosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getEntrancePosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getExitPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getExitPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getExitPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_GRGE>(IPL_SECTION_GRGE))
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getLine().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getLine().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getCubePosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getCubePosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getCubePosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_JUMP>(IPL_SECTION_JUMP))
				{
					pIPLEntry->getStartLowerPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getStartLowerPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getStartLowerPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getStartUpperPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getStartUpperPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getStartUpperPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getTargetLowerPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getTargetLowerPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getTargetLowerPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getTargetUpperPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getTargetUpperPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getTargetUpperPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getCameraPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getCameraPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getCameraPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_OCCL>(IPL_SECTION_OCCL))
				{
					pIPLEntry->getMidPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getMidPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_PICK>(IPL_SECTION_PICK))
				{
					pIPLEntry->getPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
				for (auto pIPLEntry : pIPLFile->getEntriesBySection<CIPLEntry_ZONE>(IPL_SECTION_ZONE))
				{
					pIPLEntry->getBottomLeftPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getBottomLeftPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getBottomLeftPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
					pIPLEntry->getTopRightPosition().x += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x;
					pIPLEntry->getTopRightPosition().y += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y;
					pIPLEntry->getTopRightPosition().z += pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z;
				}
			}
			
			pIPLFile->setFilePath(pMapMoverAndIDShifterDialogData->m_strOutputFolderPath + CPathManager::getFileName(strIPLPath));
			pIPLFile->serializeViaFile();
		}
		
		pIPLFile->unload();
		delete pIPLFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen("Moved and ID shifted " + CString2::toString(vecIDEPaths.size()) + " IDE files and " + CString2::toString(vecIPLPaths.size()) + " IPL files (" + CString2::toString(uiIPLCount_Text) + " text, " + CString2::toString(uiIPLCount_Binary) + " binary) in " + CPathManager::getFileName(pMapMoverAndIDShifterDialogData->m_strDATFilePath));
	}
	else
	{
		getIMGF()->getEntryListTab()->log("Moved and ID shifted " + CString2::toString(vecIDEPaths.size()) + " IDE files and " + CString2::toString(vecIPLPaths.size()) + " IPL files in " + CPathManager::getFileName(pMapMoverAndIDShifterDialogData->m_strDATFilePath));
	}

	delete pMapMoverAndIDShifterDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestMapMoverAndIDShifter");
}

void						CTaskDispatchManager::onRequestDATModelList(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestModelListFromDAT");

	CDATModelListDialogData *pDATModelListDialogData = getIMGF()->getPopupGUIManager()->showDATModelListDialog();
	if (!pDATModelListDialogData->m_bFetch)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestModelListFromDAT", true);
		return;
	}

	CDATLoaderFormat *pDATFile = CDATLoaderManager::get()->parseViaFile(pDATModelListDialogData->m_strDATFilePath);
	if(pDATFile->doesHaveError())
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestModelListFromDAT", true);
		return;
	}
	
	vector<string>
		vecRelativeIDEPaths = pDATFile->getRelativeIDEPaths(),
		vecRelativeIPLPaths = pDATFile->getRelativeIPLPaths();
	pDATFile->unload();
	delete pDATFile;

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecRelativeIDEPaths.size() + vecRelativeIPLPaths.size() + 1);

	vector<string> vecModelNames;
	for (string& strRelativeIDEPath : vecRelativeIDEPaths)
	{
		string strIDEPath = pDATModelListDialogData->m_strGameFolderPath + strRelativeIDEPath;

		CIDEFormat *pIDEFile = CIDEManager::get()->parseViaFile(strIDEPath);
		if(!pIDEFile->doesHaveError())
		{
			vecModelNames = CStdVector::combineVectors(vecModelNames, pIDEFile->getModelNames());
		}
		pIDEFile->unload();
		delete pIDEFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	for (string& strRelativeIPLPath : vecRelativeIPLPaths)
	{
		string strIPLPath = pDATModelListDialogData->m_strGameFolderPath + strRelativeIPLPath;

		CIPLFormat *pIPLFile = CIPLManager::get()->parseViaFile(strIPLPath);
		if(!pIPLFile->doesHaveError())
		{
			vecModelNames = CStdVector::combineVectors(vecModelNames, pIPLFile->getModelNames());
		}
		pIPLFile->unload();
		delete pIPLFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	vecModelNames = CStdVector::removeDuplicates(vecModelNames);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen("Found " + CString2::toString(vecModelNames.size()) + " unique model names in IDE/IPL files in " + CPathManager::getFileName(pDATModelListDialogData->m_strDATFilePath));
	}
	else
	{
		getIMGF()->getEntryListTab()->log("Found " + CString2::toString(vecModelNames.size()) + " unique model names in IDE/IPL files in " + CPathManager::getFileName(pDATModelListDialogData->m_strDATFilePath));
	}

	/*
	string strFilePath = CInputManager::saveFileDialog(getIMGF()->getLastUsedDirectory("DATMODELLIST"), "TXT", "Model Names for " + CPathManager::removeFileExtension(CPathManager::getFileName(strDATFilePath)) + ".txt");
	if (strFilePath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestModelListFromDAT", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("DATMODELLIST", CPathManager::getDirectory(strFilePath));
	*/

	CFileManager::storeFile(pDATModelListDialogData->m_strOutputFilePath, CString2::join(vecModelNames, "\n"), false, false);

	delete pDATModelListDialogData;
	getIMGF()->getTaskManager()->onTaskEnd("onRequestModelListFromDAT");
}

void						CTaskDispatchManager::onRequestFindTXDMissingFromIMGFoundInIDE(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestFindTXDMissingFromIMGFoundInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindTXDMissingFromIMGFoundInIDE", true);
		return;
	}

	// fetch TXD names in IDE files
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSINGENTRIES_IDE_IMG_TXD__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindTXDMissingFromIMGFoundInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MISSINGENTRIES_IDE_IMG_TXD__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	vector<string> vecTXDNamesWithoutExtensionInIDE = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, false, true);

	// fetch TXD names in active IMG file
	vector<string> vecTXDNamesWithoutExtensionInIMG;
	for (CIMGEntry *pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		if (pIMGEntry->isTXDFile())
		{
			vecTXDNamesWithoutExtensionInIMG.push_back(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		}
	}
	vecTXDNamesWithoutExtensionInIMG = CStdVector::toUpperCase(vecTXDNamesWithoutExtensionInIMG);
	unordered_map<string, bool> umapTXDNamesWithoutExtensionInIMG = CStdVector::convertVectorToUnorderedMap(vecTXDNamesWithoutExtensionInIMG);
	vecTXDNamesWithoutExtensionInIMG.clear();

	// find TXD names found in IDE but not found in IMG
	vector<string> vecTXDNamesWithoutExtensionMissingFromIMG;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecTXDNamesWithoutExtensionInIDE.size());
	for (string& strTXDName : vecTXDNamesWithoutExtensionInIDE)
	{
		if (umapTXDNamesWithoutExtensionInIMG.count(CString2::toUpperCase(strTXDName)) == 0)
		{
			vecTXDNamesWithoutExtensionMissingFromIMG.push_back(strTXDName);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// log
	string strIMGFileName = CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath());
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_132", vecTXDNamesWithoutExtensionMissingFromIMG.size(), strIMGFileName.c_str()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_135"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecTXDNamesWithoutExtensionMissingFromIMG, "\n"), true);

	// popup
	string strInitialFilename = CLocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_9_InitialFilename", CPathManager::replaceFileExtension(CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()), "txt").c_str());
	string strTitle = CLocalizationManager::get()->getTranslatedFormattedText("Log_132", vecTXDNamesWithoutExtensionMissingFromIMG.size(), strIMGFileName.c_str());
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showListViewDialog("Missing Entries", strTitle, "TXD Name", vecTXDNamesWithoutExtensionMissingFromIMG, strInitialFilename, "MISSINGENTRIES");
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestFindTXDMissingFromIMGFoundInIDE");
}
void						CTaskDispatchManager::onRequestFindCOLMissingFromCOLFoundInIDE(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestFindCOLMissingFromCOLFoundInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindCOLMissingFromCOLFoundInIDE", true);
		return;
	}

	// fetch DFF names in IDE files (these DFF names will be compared with COL names)
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSINGENTRIES_IDE_COL_COL__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindCOLMissingFromCOLFoundInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MISSINGENTRIES_IDE_COL_COL__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	vector<string> vecDFFNamesWithoutExtensionInIDE = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, true, false);

	// fetch COL names in COL file
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecCOLPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSINGENTRIES_IDE_COL_COL__COL"), "COL");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecCOLPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestMissingCOLEntriesInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MISSINGENTRIES_IDE_COL_COL__COL", CPathManager::getDirectory(vecCOLPaths[0]));

	vector<string> vecCOLNamesWithoutExtensionInCOL;
	for (string& strCOLPath : vecCOLPaths)
	{
		CCOLFormat *pCOLFile = CCOLManager::get()->parseViaFile(strCOLPath);
		if (!pCOLFile->doesHaveError())
		{
			for (CCOLEntry *pCOLEntry : pCOLFile->getEntries())
			{
				vecCOLNamesWithoutExtensionInCOL.push_back(pCOLEntry->getModelName());
			}
		}
		pCOLFile->unload();
		delete pCOLFile;
	}

	vecCOLNamesWithoutExtensionInCOL = CStdVector::toUpperCase(vecCOLNamesWithoutExtensionInCOL);
	unordered_map<string, bool> umapCOLNamesWithoutExtensionInCOL = CStdVector::convertVectorToUnorderedMap(vecCOLNamesWithoutExtensionInCOL);
	vecCOLNamesWithoutExtensionInCOL.clear();

	// find COL names found in IDE but not found in COL
	vector<string> vecCOLNamesWithoutExtensionMissingFromIMG;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFNamesWithoutExtensionInIDE.size());
	for (string& strDFFName : vecDFFNamesWithoutExtensionInIDE)
	{
		if (umapCOLNamesWithoutExtensionInCOL.count(CString2::toUpperCase(strDFFName)) == 0)
		{
			vecCOLNamesWithoutExtensionMissingFromIMG.push_back(strDFFName);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// log
	string strIMGFileName = CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath());
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_133", vecCOLNamesWithoutExtensionMissingFromIMG.size(), strIMGFileName.c_str()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_135"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecCOLNamesWithoutExtensionMissingFromIMG, "\n"), true);

	// popup
	string strInitialFilename = CLocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_9_InitialFilename", CPathManager::replaceFileExtension(CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()), "txt").c_str());
	string strTitle = CLocalizationManager::get()->getTranslatedFormattedText("Log_133", vecCOLNamesWithoutExtensionMissingFromIMG.size(), strIMGFileName.c_str());
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showListViewDialog("Missing Entries", strTitle, "TXD Name", vecCOLNamesWithoutExtensionMissingFromIMG, strInitialFilename, "MISSINGENTRIES");
	getIMGF()->getTaskManager()->onTaskUnpause();
	getIMGF()->getTaskManager()->onTaskEnd("onRequestFindCOLMissingFromCOLFoundInIDE");
}
void						CTaskDispatchManager::onRequestFindDFFMissingFromIMGFoundInIDE(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestFindDFFMissingFromIMGFoundInIDE");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindDFFMissingFromIMGFoundInIDE", true);
		return;
	}

	// fetch DFF names in IDE files
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSINGENTRIES_IDE_IMG_DFF__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindDFFMissingFromIMGFoundInIDE", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MISSINGENTRIES_IDE_IMG_DFF__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	vector<string> vecDFFNamesWithoutExtensionInIDE = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, true, false);

	// fetch DFF names in active IMG file
	vector<string> vecDFFNamesWithoutExtensionInIMG;
	for (CIMGEntry *pIMGEntry : getIMGF()->getEntryListTab()->getIMGFile()->getEntries())
	{
		if (pIMGEntry->isDFFFile())
		{
			vecDFFNamesWithoutExtensionInIMG.push_back(CPathManager::removeFileExtension(pIMGEntry->getEntryName()));
		}
	}
	vecDFFNamesWithoutExtensionInIMG = CStdVector::toUpperCase(vecDFFNamesWithoutExtensionInIMG);
	unordered_map<string, bool> umapDFFNamesWithoutExtensionInIMG = CStdVector::convertVectorToUnorderedMap(vecDFFNamesWithoutExtensionInIMG);
	vecDFFNamesWithoutExtensionInIMG.clear();

	// find DFF names found in IDE but not found in IMG
	vector<string> vecDFFNamesWithoutExtensionMissingFromIMG;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFNamesWithoutExtensionInIDE.size());
	for (string& strDFFName : vecDFFNamesWithoutExtensionInIDE)
	{
		if (umapDFFNamesWithoutExtensionInIMG.count(CString2::toUpperCase(strDFFName)) == 0)
		{
			vecDFFNamesWithoutExtensionMissingFromIMG.push_back(strDFFName);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// log
	string strIMGFileName = CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath());
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_134", vecDFFNamesWithoutExtensionMissingFromIMG.size(), strIMGFileName.c_str()));
	getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_135"), true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecDFFNamesWithoutExtensionMissingFromIMG, "\n"), true);

	// popup
	string strInitialFilename = CLocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_9_InitialFilename", CPathManager::replaceFileExtension(CPathManager::getFileName(getIMGF()->getEntryListTab()->getIMGFile()->getFilePath()), "txt").c_str());
	string strTitle = CLocalizationManager::get()->getTranslatedFormattedText("Log_134", vecDFFNamesWithoutExtensionMissingFromIMG.size(), strIMGFileName.c_str());
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showListViewDialog("Missing Entries", strTitle, "TXD Name", vecDFFNamesWithoutExtensionMissingFromIMG, strInitialFilename, "MISSINGENTRIES");
	getIMGF()->getTaskManager()->onTaskUnpause();
	
	getIMGF()->getTaskManager()->onTaskEnd("onRequestFindDFFMissingFromIMGFoundInIDE");
}

void						CTaskDispatchManager::onRequestCloneIMG(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestCloneIMG");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCloneIMG", true);
		return;
	}

	CIMGFormat *pIMGFile = getIMGF()->getEntryListTab()->getIMGFile();
	
	string strIMGFileExtension = CPathManager::getFileExtension(pIMGFile->getFilePath());
	string strClonedIMGPath = CPathManager::getDirectory(pIMGFile->getFilePath()) + CPathManager::removeFileExtension(CPathManager::getFileName(pIMGFile->getFilePath())) + "-cloned." + strIMGFileExtension;

	CIMGFormat *pClonedIMGFile = pIMGFile->clone(strClonedIMGPath);
	if (!pClonedIMGFile)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestCloneIMG", true);
		return;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(pIMGFile->getEntryCount() * 3);

	//CIMGEditorTab *pNewTab = getIMGF()->getIMGEditor()->addTab(strClonedIMGPath, pIMGFile->getVersion());
	//getIMGF()->getIMGEditor()->setActiveTab(pNewTab);

	getIMGF()->getTaskManager()->onTaskEnd("onRequestCloneIMG");
}

void						CTaskDispatchManager::onRequestOpenIMGFolder(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestOpenIMGFolder");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestOpenIMGFolder", true);
		return;
	}

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(2);

	CIMGFormat *pIMGFile = getIMGF()->getEntryListTab()->getIMGFile();
	string strFolderPath = CPathManager::getDirectory(pIMGFile->getFilePath());
	getIMGF()->getTaskManager()->onTaskProgressTick();

	ShellExecute(NULL, NULL, CString2::convertStdStringToStdWString(strFolderPath).c_str(), NULL, NULL, SW_SHOWNORMAL);
	getIMGF()->getTaskManager()->onTaskProgressTick();

	getIMGF()->getTaskManager()->onTaskEnd("onRequestOpenIMGFolder");
}

void						CTaskDispatchManager::onRequestRemoveOrphanTexturesFromModel(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestRemoveOrphanTexturesFromModel");
	if (getIMGF()->getEntryListTab() == nullptr)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveOrphanTexturesFromModel", true);
		return;
	}

	// input - txd
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecTXDPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("REMOVEORPHANTEXTURESFROMMODEL_TXD"), "TXD");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecTXDPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveOrphanTexturesFromModel", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("REMOVEORPHANTEXTURESFROMMODEL_TXD", CPathManager::getDirectory(vecTXDPaths[0]));

	// progess bar
	uint32 uiSelectedDFFCount = 0;
	for (CIMGEntry *pIMGEntry : getIMGF()->getEntryListTab()->getSelectedEntries())
	{
		if (pIMGEntry->isDFFFile())
		{
			uiSelectedDFFCount++;
		}
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount((uiSelectedDFFCount  * 2) + vecTXDPaths.size());

	// fetch texture names from DFF files (selected IMG entries)
	vector<string> vecDFFTextureNames;
	vector<CDFFFormat*> vecDFFFormatsInput;
	vector<CIMGEntry*> vecIMGEntries;
	uint32 uiProgressMaxTicksDecudctionForCorruptDFFFiles = 0;
	for (CIMGEntry *pIMGEntry : getIMGF()->getEntryListTab()->getSelectedEntries())
	{
		if (pIMGEntry->isDFFFile())
		{
			CDFFFormat *pDFFFile = CDFFManager::get()->parseViaMemory(pIMGEntry->getEntryData());
			if (pDFFFile->doesHaveError())
			{
				pDFFFile->unload();
				delete pDFFFile;
				getIMGF()->getTaskManager()->onTaskProgressTick();
				uiProgressMaxTicksDecudctionForCorruptDFFFiles++;
				continue;
			}

			CStdVector::addToVector(vecDFFTextureNames, pDFFFile->getTextureNames());
			vecDFFFormatsInput.push_back(pDFFFile);
			vecIMGEntries.push_back(pIMGEntry);

			getIMGF()->getTaskManager()->onTaskProgressTick();
		}
	}
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(getIMGF()->getTaskManager()->getTaskMaxProgressTickCount() - uiProgressMaxTicksDecudctionForCorruptDFFFiles, false); // for below

	// fetch texture names from TXD files (files input)
	vector<string> vecTXDTextureNames;
	for (string strTXDPath : vecTXDPaths)
	{
		CTXDFormat *pTXDFile = CTXDManager::get()->parseViaFile(strTXDPath);
		if (pTXDFile->doesHaveError())
		{
			pTXDFile->unload();
			delete pTXDFile;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		CStdVector::addToVector(vecTXDTextureNames, pTXDFile->getTextureNames());

		pTXDFile->unload();
		delete pTXDFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// find texture names found in DFF files getIMGF()->getEntryListTab()but not found in TXD files
	vecTXDTextureNames = CStdVector::toUpperCase(vecTXDTextureNames);
	unordered_map<string, bool> umapTXDTextureNames = CStdVector::convertVectorToUnorderedMap(vecTXDTextureNames);
	vecTXDTextureNames.clear();

	vector<string> vecTexturesInDFFMissingFromTXD;
	unordered_map<string, bool> umapTexturesInDFFMissingFromTXD;
	for (string& strDFFTextureName : vecDFFTextureNames)
	{
		string strDFFTextureNameUpper = CString2::toUpperCase(strDFFTextureName);
		if (umapTXDTextureNames.count(strDFFTextureNameUpper) == 0)
		{
			if (umapTexturesInDFFMissingFromTXD.count(strDFFTextureNameUpper) == 0)
			{
				umapTexturesInDFFMissingFromTXD[strDFFTextureNameUpper] = true;
				vecTexturesInDFFMissingFromTXD.push_back(strDFFTextureName);
			}
		}
	}
	umapTexturesInDFFMissingFromTXD.clear();

	// remove textures entries from DFF files that are not found in TXD files
	uint32 i = 0;
	uint32 uiDFFFileCountWithRemovedSections = 0;
	for (CDFFFormat *pDFFFile : vecDFFFormatsInput)
	{
		bool bRemovedSection = false;
		for (string& strDFFTextureName : vecTexturesInDFFMissingFromTXD)
		{
			CTextureEntry *pDFFTextureEntry = pDFFFile->getTextureByDiffuseOrAlphaName(strDFFTextureName);
			if (pDFFTextureEntry != nullptr)
			{
				CRWSection_Material *pMaterial = (CRWSection_Material*)pDFFTextureEntry->getRWTextureSection()->getParentNode();
				pMaterial->removeSection();
				pDFFFile->removeTextureEntry(pDFFTextureEntry);
				bRemovedSection = true;
			}
		}

		CIMGEntry *pIMGEntry = vecIMGEntries[i];
		pIMGEntry->setEntryData(pDFFFile->storeViaMemory());
		getIMGF()->getEntryListTab()->updateEntryInMainListView(pIMGEntry);

		if (bRemovedSection)
		{
			uiDFFFileCountWithRemovedSections++;
		}

		getIMGF()->getTaskManager()->onTaskProgressTick();

		i++;
	}

	// log
	getIMGF()->getEntryListTab()->log("Removed orphan textures from " + CString2::toString(uiDFFFileCountWithRemovedSections) + " of " + CString2::toString(vecDFFFormatsInput.size()) + " DFF files.");
	getIMGF()->getEntryListTab()->log("Textures in DFF files missing from TXD files:", true);
	getIMGF()->getEntryListTab()->log(CString2::join(vecTexturesInDFFMissingFromTXD, "\n"), true);

	// clean up
	for (auto pDFFFile : vecDFFFormatsInput)
	{
		pDFFFile->unload();
		delete pDFFFile;
	}
	getIMGF()->getTaskManager()->onTaskEnd("onRequestRemoveOrphanTexturesFromModel");
}
void						CTaskDispatchManager::onRequestNewWindow(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestNewWindow");

	TCHAR wszRunningProgramPath[MAX_PATH];
	wmemset(wszRunningProgramPath, 0, MAX_PATH);
	GetModuleFileName(NULL, wszRunningProgramPath, MAX_PATH);

	ShellExecute(NULL, L"open", wszRunningProgramPath, NULL, NULL, SW_SHOWNORMAL);

	getIMGF()->getTaskManager()->onTaskEnd("onRequestNewWindow");
}

void						CTaskDispatchManager::onRequestFindDFFMissingFromIDEFoundInIPL(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestFindDFFMissingFromIDEFoundInIPL");

	// fetch DFF names in IDE files
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIDEPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSINGENTRIES_IPL_IDE_DFF__IDE"), "IDE");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindDFFMissingFromIDEFoundInIPL", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MISSINGENTRIES_IPL_IDE_DFF__IDE", CPathManager::getDirectory(vecIDEPaths[0]));

	vector<string> vecDFFNamesWithoutExtensionInIDE = CIDEManager::getIDEEntryNamesWithoutExtension(vecIDEPaths, true, false);

	// fetch DFF names in IPL files
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecIPLPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("MISSINGENTRIES_IPL_IDE_DFF__IPL"), "IPL");
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecIDEPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestFindDFFMissingFromIDEFoundInIPL", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("MISSINGENTRIES_IPL_IDE_DFF__IPL", CPathManager::getDirectory(vecIPLPaths[0]));

	vector<string> vecDFFNamesWithoutExtensionInIPL;
	for (string& strIPLPath : vecIPLPaths)
	{
		CIPLFormat *pIPLFile = CIPLManager::get()->parseViaFile(strIPLPath);

		if (!pIPLFile->doesHaveError())
		{
			CStdVector::addToVector(vecDFFNamesWithoutExtensionInIPL, pIPLFile->getModelNames());
		}

		pIPLFile->unload();
		delete pIPLFile;
	}
	
	vecDFFNamesWithoutExtensionInIDE = CStdVector::toUpperCase(vecDFFNamesWithoutExtensionInIDE);
	unordered_map<string, bool> umapDFFNamesWithoutExtensionInIDE = CStdVector::convertVectorToUnorderedMap(vecDFFNamesWithoutExtensionInIDE);
	vecDFFNamesWithoutExtensionInIDE.clear();

	// find DFF names found in IPL but not found in IDE
	vector<string> vecDFFNamesWithoutExtensionMissingFromIDE;
	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFNamesWithoutExtensionInIDE.size());
	for (string& strDFFName : vecDFFNamesWithoutExtensionInIPL)
	{
		if (umapDFFNamesWithoutExtensionInIDE.count(CString2::toUpperCase(strDFFName)) == 0)
		{
			vecDFFNamesWithoutExtensionMissingFromIDE.push_back(strDFFName);
		}
		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// log
	if (getIMGF()->getEntryListTab())
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_136", vecDFFNamesWithoutExtensionMissingFromIDE.size()));
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedText("Log_135"), true);
		getIMGF()->getEntryListTab()->log(CString2::join(vecDFFNamesWithoutExtensionMissingFromIDE, "\n"), true);
	}
	else
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CLocalizationManager::get()->getTranslatedFormattedText("Log_136", vecDFFNamesWithoutExtensionMissingFromIDE.size()));
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CLocalizationManager::get()->getTranslatedText("Log_135"), true);
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CString2::join(vecDFFNamesWithoutExtensionMissingFromIDE, "\n"), true);
	}

	// popup
	string strInitialFilename = CLocalizationManager::get()->getTranslatedFormattedText("SaveFilePopup_9_InitialFilename", "DFF not in IDE found in IPL");
	string strTitle = CLocalizationManager::get()->getTranslatedFormattedText("Log_136", vecDFFNamesWithoutExtensionMissingFromIDE.size());
	getIMGF()->getTaskManager()->onTaskPause();
	getIMGF()->getPopupGUIManager()->showListViewDialog("Missing Entries", strTitle, "TXD Name", vecDFFNamesWithoutExtensionMissingFromIDE, strInitialFilename, "MISSINGENTRIES");
	getIMGF()->getTaskManager()->onTaskUnpause();

	getIMGF()->getTaskManager()->onTaskEnd("onRequestFindDFFMissingFromIDEFoundInIPL");
}

void				CTaskDispatchManager::onRequestSortIDEAndIPLFilesByObjectId(void)
{
	getIMGF()->getTaskManager()->onTaskBegin("onRequestSortIDEAndIPLFilesByObjectId");

	// choose DAT file
	getIMGF()->getTaskManager()->onTaskPause();
	vector<string> vecDATPaths = CInputManager::openFile(getIMGF()->getLastUsedDirectory("SORTIDEANDIPL_OBJECTID_DAT"), "DAT", false);
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (vecDATPaths.size() == 0)
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSortIDEAndIPLFilesByObjectId", true);
		return;
	}
	getIMGF()->setLastUsedDirectory("SORTIDEANDIPL_OBJECTID_DAT", CPathManager::getDirectory(vecDATPaths[0]));
	string strDATFilePath = vecDATPaths[0];

	// choose game folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strGameDirectoryPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("SORTIDEANDIPL_OBJECTID_GAME"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strGameDirectoryPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSortIDEAndIPLFilesByObjectId", true);
		return;
	}
	strGameDirectoryPath = CPathManager::addSlashToEnd(strGameDirectoryPath);
	getIMGF()->setLastUsedDirectory("SORTIDEANDIPL_OBJECTID_GAME", strGameDirectoryPath);

	// choose output folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strOutputFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_23"), getIMGF()->getLastUsedDirectory("SORTIDEANDIPL_OBJECTID_OUTPUT"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strOutputFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSortIDEAndIPLFilesByObjectId", true);
		return;
	}
	strOutputFolderPath = CPathManager::addSlashToEnd(strOutputFolderPath);
	getIMGF()->setLastUsedDirectory("SORTIDEANDIPL_OBJECTID_OUTPUT", strOutputFolderPath);

	// parse DAT file
	CDATLoaderFormat *pDATFile_GTA = CDATLoaderManager::get()->parseViaFile(strDATFilePath);
	if (pDATFile_GTA->doesHaveError())
	{
		pDATFile_GTA->unload();
		delete pDATFile_GTA;
		getIMGF()->getTaskManager()->onTaskEnd("onRequestSortIDEAndIPLFilesByObjectId", true);
		return;
	}

	// parse IDE and IPL files listed in DAT file
	vector<CIDEFormat*> veCIDEFormats = pDATFile_GTA->parseIDEFiles(strGameDirectoryPath);
	vector<CIPLFormat*> veCIPLFormats = pDATFile_GTA->parseIPLFiles(strGameDirectoryPath);

	pDATFile_GTA->unload();
	delete pDATFile_GTA;

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(veCIDEFormats.size() + veCIPLFormats.size());

	// sort and store IDE files
	for (CIDEFormat *pIDEFile : veCIDEFormats)
	{
		pIDEFile->sortAllSectionsByObjectId();
		pIDEFile->storeViaFile(strOutputFolderPath + CPathManager::getFileName(pIDEFile->getFilePath()));

		pIDEFile->unload();
		delete pIDEFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// sort and store IPL files
	for (CIPLFormat *pIPLFile : veCIPLFormats)
	{
		pIPLFile->sortAllSectionsByObjectId();
		pIPLFile->storeViaFile(strOutputFolderPath + CPathManager::getFileName(pIPLFile->getFilePath()));

		pIPLFile->unload();
		delete pIPLFile;

		getIMGF()->getTaskManager()->onTaskProgressTick();
	}

	// log
	if (getIMGF()->getEntryListTab())
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_137", veCIDEFormats.size(), veCIPLFormats.size(), CPathManager::getFileName(strDATFilePath).c_str()));
	}
	else
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CLocalizationManager::get()->getTranslatedFormattedText("Log_137", veCIDEFormats.size(), veCIPLFormats.size(), CPathManager::getFileName(strDATFilePath).c_str()));
	}

	getIMGF()->getTaskManager()->onTaskEnd("onRequestSortIDEAndIPLFilesByObjectId");
}

void				CTaskDispatchManager::onRequestExtractDVCAndNVCColoursIntoDFFs(void)
{
	// begin
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExtractDVCAndNVCColoursIntoDFFs");

	// choose DVC, NVC, or both
	uint32 uiUpdateType = getIMGF()->getPopupGUIManager()->show3ButtonDialog("DVC / NVC Action", "Extract DVC, NVC, or both?", "DVC", "NVC", "Both");
	if (uiUpdateType == 0)
	{
		// user pressed cancel
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExtractDVCAndNVCColoursIntoDFFs", true);
		return;
	}

	// choose DFF input folder for colours
	getIMGF()->getTaskManager()->onTaskPause();
	string strDFFInputFolderForColours = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_24"), getIMGF()->getLastUsedDirectory("EXTRACTNVCDVC_DFFCOLOURINPUT"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strDFFInputFolderForColours == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExtractDVCAndNVCColoursIntoDFFs", true);
		return;
	}
	strDFFInputFolderForColours = CPathManager::addSlashToEnd(strDFFInputFolderForColours);
	getIMGF()->setLastUsedDirectory("EXTRACTNVCDVC_DFFCOLOURINPUT", strDFFInputFolderForColours);

	// choose DFF input folder for models
	getIMGF()->getTaskManager()->onTaskPause();
	string strDFFInputFolderForModels = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_25"), getIMGF()->getLastUsedDirectory("EXTRACTNVCDVC_DFFMODELINPUT"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strDFFInputFolderForModels == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExtractDVCAndNVCColoursIntoDFFs", true);
		return;
	}
	strDFFInputFolderForModels = CPathManager::addSlashToEnd(strDFFInputFolderForModels);
	getIMGF()->setLastUsedDirectory("EXTRACTNVCDVC_DFFMODELINPUT", strDFFInputFolderForModels);

	// choose output folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strOutputFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_23"), getIMGF()->getLastUsedDirectory("EXTRACTNVCDVC_OUTPUT"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strOutputFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExtractDVCAndNVCColoursIntoDFFs", true);
		return;
	}
	strOutputFolderPath = CPathManager::addSlashToEnd(strOutputFolderPath);
	getIMGF()->setLastUsedDirectory("EXTRACTNVCDVC_OUTPUT", strOutputFolderPath);

	// fetch DFF file paths
	vector<string> vecDFFInputFilenamesForColours = CFileManager::getFileNamesByExtension(strDFFInputFolderForColours, "DFF");
	vector<string> vecDFFInputFilenamesForModels = CFileManager::getFileNamesByExtension(strDFFInputFolderForModels, "DFF");
	
	//vecDFFInputFilenamesForColours = CStdVector::sortAZCaseInsensitive(vecDFFInputFilenamesForColours);
	//vecDFFInputFilenamesForModels = CStdVector::sortAZCaseInsensitive(vecDFFInputFilenamesForModels);

	unordered_map<string, bool> umapDFFInputFilenamesUpperForModels = CStdVector::convertVectorToUnorderedMap(CStdVector::toUpperCase(vecDFFInputFilenamesForModels));

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFInputFilenamesForColours.size());

	// iterate around input DFFs
	uint32 uiDFFUpdatedFileCount = 0;
	for (string& strDFFFilename_Colours : vecDFFInputFilenamesForColours)
	{
		if (umapDFFInputFilenamesUpperForModels.count(CString2::toUpperCase(strDFFFilename_Colours)) == 0)
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}
		string& strDFFFilename_Model = strDFFFilename_Colours;

		CDFFFormat *pDFFFile_Colours = CDFFManager::get()->parseViaFile(strDFFInputFolderForColours + strDFFFilename_Colours);
		if (pDFFFile_Colours->doesHaveError())
		{
			pDFFFile_Colours->unload();
			delete pDFFFile_Colours;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		vector<Vec4u8> vecDFFColours_DVC;
		vector<Vec4u8> vecDFFColours_NVC;
		if (uiUpdateType == 1 || uiUpdateType == 3) // DVC or both
		{
			vecDFFColours_DVC = pDFFFile_Colours->getDVCColours();
		}
		if (uiUpdateType == 2 || uiUpdateType == 3) // NVC or both
		{
			vecDFFColours_NVC = pDFFFile_Colours->getNVCColours();
			if (vecDFFColours_NVC.size() == 0)
			{
				vecDFFColours_NVC = vecDFFColours_DVC;
			}
		}

		pDFFFile_Colours->unload();
		delete pDFFFile_Colours;

		//CDFFFormat *pDFFFile_Model = CDFFManager::get()->parseViaFile(strDFFInputFolderForModels + strDFFFilename_Model);
		CDFFFormat *pDFFFile_Model = CDFFManager::get()->parseViaMemory(CFileManager::getFileContent(strDFFInputFolderForModels + strDFFFilename_Model, true));
		if (pDFFFile_Model->doesHaveError())
		{
			pDFFFile_Model->unload();
			delete pDFFFile_Model;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		if (uiUpdateType == 1 || uiUpdateType == 3) // DVC or both
		{
			if (vecDFFColours_DVC.size() > 0)
			{
				pDFFFile_Model->setDVCColours(vecDFFColours_DVC);
			}
		}
		if (uiUpdateType == 2 || uiUpdateType == 3) // NVC or both
		{
			if (vecDFFColours_NVC.size() > 0)
			{
				pDFFFile_Model->setNVCColours(vecDFFColours_NVC);
			}
		}

		pDFFFile_Model->storeViaFile(strOutputFolderPath + strDFFFilename_Colours);

		pDFFFile_Model->unload();
		delete pDFFFile_Model;
		getIMGF()->getTaskManager()->onTaskProgressTick();
		uiDFFUpdatedFileCount++;
	}

	// log
	if (getIMGF()->getEntryListTab())
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_138", uiDFFUpdatedFileCount));
	}
	else
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CLocalizationManager::get()->getTranslatedFormattedText("Log_138", uiDFFUpdatedFileCount));
	}

	// end
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExtractDVCAndNVCColoursIntoDFFs");
}

void				CTaskDispatchManager::onRequestExtract2DFXIntoDFFs(void)
{
	// begin
	getIMGF()->getTaskManager()->onTaskBegin("onRequestExtract2DFXIntoDFFs");

	// choose DFF input folder for colours
	getIMGF()->getTaskManager()->onTaskPause();
	string strDFFInputFolderFor2DFX = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_26"), getIMGF()->getLastUsedDirectory("EXTRACTDFF2DFX_INPUT2DFX"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strDFFInputFolderFor2DFX == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExtract2DFXIntoDFFs", true);
		return;
	}
	strDFFInputFolderFor2DFX = CPathManager::addSlashToEnd(strDFFInputFolderFor2DFX);
	getIMGF()->setLastUsedDirectory("EXTRACTDFF2DFX_INPUT2DFX", strDFFInputFolderFor2DFX);

	// choose DFF input folder for models
	getIMGF()->getTaskManager()->onTaskPause();
	string strDFFInputFolderForModels = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_25"), getIMGF()->getLastUsedDirectory("EXTRACTDFF2DFX_INPUTMODEL"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strDFFInputFolderForModels == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExtract2DFXIntoDFFs", true);
		return;
	}
	strDFFInputFolderForModels = CPathManager::addSlashToEnd(strDFFInputFolderForModels);
	getIMGF()->setLastUsedDirectory("EXTRACTDFF2DFX_INPUTMODEL", strDFFInputFolderForModels);

	// choose output folder
	getIMGF()->getTaskManager()->onTaskPause();
	string strOutputFolderPath = CInputManager::chooseFolderDialog(CLocalizationManager::get()->getTranslatedText("ChooseFolderPopup_23"), getIMGF()->getLastUsedDirectory("EXTRACTDFF2DFX_OUTPUT"));
	getIMGF()->getTaskManager()->onTaskUnpause();
	if (strOutputFolderPath == "")
	{
		getIMGF()->getTaskManager()->onTaskEnd("onRequestExtract2DFXIntoDFFs", true);
		return;
	}
	strOutputFolderPath = CPathManager::addSlashToEnd(strOutputFolderPath);
	getIMGF()->setLastUsedDirectory("EXTRACTDFF2DFX_OUTPUT", strOutputFolderPath);

	// fetch DFF file paths
	vector<string> vecDFFInputFilenamesFor2DFX = CFileManager::getFileNamesByExtension(strDFFInputFolderFor2DFX, "DFF");
	vector<string> vecDFFInputFilenamesForModels = CFileManager::getFileNamesByExtension(strDFFInputFolderForModels, "DFF");

	//vecDFFInputFilenamesForColours = CStdVector::sortAZCaseInsensitive(vecDFFInputFilenamesForColours);
	//vecDFFInputFilenamesForModels = CStdVector::sortAZCaseInsensitive(vecDFFInputFilenamesForModels);

	unordered_map<string, bool> umapDFFInputFilenamesUpperForModels = CStdVector::convertVectorToUnorderedMap(CStdVector::toUpperCase(vecDFFInputFilenamesForModels));

	getIMGF()->getTaskManager()->setTaskMaxProgressTickCount(vecDFFInputFilenamesFor2DFX.size());

	// iterate around input DFFs
	uint32 uiDFFUpdatedFileCount = 0;
	for (string& strDFFFilename_2DFX : vecDFFInputFilenamesFor2DFX)
	{
		if (umapDFFInputFilenamesUpperForModels.count(CString2::toUpperCase(strDFFFilename_2DFX)) == 0)
		{
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}
		string& strDFFFilename_Model = strDFFFilename_2DFX;

		CDFFFormat *pDFFFile_2DFX = CDFFManager::get()->parseViaFile(strDFFInputFolderFor2DFX + strDFFFilename_2DFX);
		if (pDFFFile_2DFX->doesHaveError())
		{
			pDFFFile_2DFX->unload();
			delete pDFFFile_2DFX;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		vector<vector<C2dEffect*>> vec2dEffects = pDFFFile_2DFX->get2dEffects();

		CDFFFormat *pDFFFile_Model = CDFFManager::get()->parseViaFile(strDFFInputFolderForModels + strDFFFilename_Model);
		if (pDFFFile_Model->doesHaveError())
		{
			pDFFFile_2DFX->unload();
			delete pDFFFile_2DFX;
			pDFFFile_Model->unload();
			delete pDFFFile_Model;
			getIMGF()->getTaskManager()->onTaskProgressTick();
			continue;
		}

		pDFFFile_Model->set2dEffects(vec2dEffects);

		pDFFFile_Model->storeViaFile(strOutputFolderPath + strDFFFilename_2DFX);

		pDFFFile_2DFX->unload();
		delete pDFFFile_2DFX;
		pDFFFile_Model->unload();
		delete pDFFFile_Model;
		getIMGF()->getTaskManager()->onTaskProgressTick();
		uiDFFUpdatedFileCount++;
	}

	// log
	if (getIMGF()->getEntryListTab())
	{
		getIMGF()->getEntryListTab()->log(CLocalizationManager::get()->getTranslatedFormattedText("Log_139", uiDFFUpdatedFileCount));
	}
	else
	{
		getIMGF()->getIMGEditor()->logWithNoTabsOpen(CLocalizationManager::get()->getTranslatedFormattedText("Log_139", uiDFFUpdatedFileCount));
	}

	// end
	getIMGF()->getTaskManager()->onTaskEnd("onRequestExtract2DFXIntoDFFs");
}