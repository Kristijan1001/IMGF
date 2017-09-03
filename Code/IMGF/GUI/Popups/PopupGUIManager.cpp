#pragma warning(disable : 4005)

#include "PopupGUIManager.h"
#include "Static/String.h"
#include "Shlobj.h"
#include "WindowControlIds.h"
#include "Static/Input.h"
#include "Static/File.h"
#include "Static/Path.h"
#include "Static/StdVector.h"
#include "IMGF.h"
#include "Globals.h"
#include "Tasks/Sort/SortManager.h"
#include "Tasks/Sort/SortType.h"
#include "Tasks/Sort/SortPriority.h"
#include "Format/IMG/Regular/IMGEntry.h"
#include "Engine/RW/RWManager.h"
#include "Engine/RW/RWVersionManager.h"
#include "Format/TXD/TXDManager.h"
#include "Image/RasterDataFormatManager.h"
#include "Image/ImageManager.h"
#include "Format/COL/COLManager.h"
#include "Format/COL/COLVersionManager.h"
#include "Format/COL/COLVersion.h"
#include "Localization/LocalizationManager.h"
#include "Language/LanguageManager.h"
#include "Language/Language.h"
#include "Tasks/Sort/SortTypes.h"
#include "Tasks/Sort/SortPriorities.h"
#include "Game/GameManager.h"
#include "Settings/SettingsManager.h"
#include "Static/Debug.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void									PopupGUIManager::init(void)
{
}
void									PopupGUIManager::uninit(void)
{
}

/*
void									PopupGUIManager::updateGUIControlsTextToLanguage(CDialog *pDialog, string strWindowName)
{
	todo
	auto umapTranslatedTextEntries = LocalizationManager::get()->getTranslatedTextEntries();
	for (auto it : umapTranslatedTextEntries)
	{
		string strInternalName = it.first;
		string strLanguageText = it.second;

		string strStartText = "Window_" + strWindowName + "_";

		if (String::doesStartWith(strInternalName, strStartText, false))
		{
			string strTextRemaining = strInternalName.substr(strStartText.length());

			if (String::toUpperCase(strTextRemaining) == "TITLE")
			{
				// e.g. Window_DFFConversion_Title
				SetWindowText(pDialog->GetSafeHwnd(), String::convertStdStringToStdWString(strLanguageText).c_str());
			}
			else if (String::isPositiveInteger(strTextRemaining))
			{
				// e.g. Window_DFFConversion_100
				uint32 uiControlId = String::toNumber(strTextRemaining);
				pDialog->GetDlgItem(uiControlId)->SetWindowText(String::convertStdStringToStdWString(strLanguageText).c_str());
				//CWnd::FromHandle(GetDlgItem(pDialog->GetSafeHwnd(), uiControlId))->SetWindowText(String::convertStdStringToStdWString(strLanguageText).c_str());
			}
		}
	}
}
*/

INT_PTR CALLBACK DialogProc_3ButtonDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	C3ButtonDialogData *p3ButtonDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	p3ButtonDialogData = (C3ButtonDialogData*)lParam;
	pDialog->SetWindowTextW(String::convertStdStringToStdWString(p3ButtonDialogData->m_strWindowTitle).c_str());
	((CStatic*)pDialog->GetDlgItem(100))->SetWindowTextW(String::convertStdStringToStdWString(p3ButtonDialogData->m_strStaticText).c_str());

	((CStatic*)pDialog->GetDlgItem(150))->SetWindowTextW(String::convertStdStringToStdWString(p3ButtonDialogData->m_strButton1Text).c_str());
	((CStatic*)pDialog->GetDlgItem(151))->SetWindowTextW(String::convertStdStringToStdWString(p3ButtonDialogData->m_strButton2Text).c_str());
	((CStatic*)pDialog->GetDlgItem(152))->SetWindowTextW(String::convertStdStringToStdWString(p3ButtonDialogData->m_strButton3Text).c_str());

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)p3ButtonDialogData);
	break;
	case WM_COMMAND:
	p3ButtonDialogData = (C3ButtonDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 150:
	p3ButtonDialogData->m_bCancel = false;
	p3ButtonDialogData->m_uiResult = 1;
	EndDialog(hwndDlg, 0);
	break;
	case 151:
	p3ButtonDialogData->m_bCancel = false;
	p3ButtonDialogData->m_uiResult = 2;
	EndDialog(hwndDlg, 0);
	break;
	case 152:
	p3ButtonDialogData->m_bCancel = false;
	p3ButtonDialogData->m_uiResult = 3;
	EndDialog(hwndDlg, 0);
	break;
	case 200:
	p3ButtonDialogData->m_bCancel = true;
	EndDialog(hwndDlg, 0);
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
uint32							PopupGUIManager::show3ButtonDialog(string strWindowTitle, string strStaticText, string strButton1Text, string strButton2Text, string strButton3Text)
{
	C3ButtonDialogData *p3ButtonDialogData = new C3ButtonDialogData;
	p3ButtonDialogData->m_bCancel = false;
	p3ButtonDialogData->m_uiResult = 0;
	p3ButtonDialogData->m_strWindowTitle = strWindowTitle;
	p3ButtonDialogData->m_strStaticText = strStaticText;
	p3ButtonDialogData->m_strButton1Text = strButton1Text;
	p3ButtonDialogData->m_strButton2Text = strButton2Text;
	p3ButtonDialogData->m_strButton3Text = strButton3Text;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_3BUTTONDIALOG), getParentWindowHwnd(), DialogProc_3ButtonDialog, (DWORD) p3ButtonDialogData);

	uint32 uiResult = p3ButtonDialogData->m_uiResult;
	delete p3ButtonDialogData;
	return uiResult;
}

INT_PTR CALLBACK DialogProc_TextInputDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	TextInputDialogData *pTextInputDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pTextInputDialogData = (TextInputDialogData*)lParam;
	pDialog->SetWindowTextW(String::convertStdStringToStdWString(pTextInputDialogData->m_strWindowTitle).c_str());
	((CStatic*)pDialog->GetDlgItem(1))->SetWindowTextW(String::convertStdStringToStdWString(pTextInputDialogData->m_strStaticText).c_str());
	((CStatic*)pDialog->GetDlgItem(0))->SetWindowTextW(String::convertStdStringToStdWString(pTextInputDialogData->m_strEditText).c_str());

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pTextInputDialogData);
	break;
	case WM_COMMAND:
	switch (wParam)
	{
	case 2:
	((TextInputDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_strResultText = "";
	EndDialog(hwndDlg, 0);
	break;
	case 3:
	((CEdit*)pDialog->GetDlgItem(0))->GetWindowTextW(strText);
	((TextInputDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_strResultText = String::convertCStringToStdString(strText);
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
string				PopupGUIManager::showTextInputDialog(string strWindowTitle, string strStaticText, string strEditText)
{
	TextInputDialogData *pTextInputDialogData = new TextInputDialogData;
	pTextInputDialogData->m_strWindowTitle = strWindowTitle;
	pTextInputDialogData->m_strStaticText = strStaticText;
	pTextInputDialogData->m_strEditText = strEditText;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_TEXTINPUTDIALOG), getParentWindowHwnd(), DialogProc_TextInputDialog, (DWORD) pTextInputDialogData);

	string strInputText = pTextInputDialogData->m_strResultText;
	delete pTextInputDialogData;
	return strInputText;
}

INT_PTR CALLBACK DialogProc_ConvertDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CConvertDialogData *pConvertDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "ConvertIMG");

	pConvertDialogData = (CConvertDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pConvertDialogData);

	pDialog->SetWindowTextW(String::convertStdStringToStdWString(pConvertDialogData->m_strWindowTitle).c_str());
	((Button*)pDialog->GetDlgItem(5))->SetWindowTextW(String::convertStdStringToStdWString(pConvertDialogData->m_strButtonText).c_str());
	break;
	case WM_COMMAND:
	switch (wParam)
	{
	case 4:
	EndDialog(hwndDlg, 0);
	break;
	case 5:
	((CConvertDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_bRadioButtonSelected = true;
	if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 0))
	{
	((CConvertDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 0;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 1))
	{
	((CConvertDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 1;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 2))
	{
	((CConvertDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 2;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 3))
	{
	((CConvertDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 3;
	}
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
uint32		PopupGUIManager::showConvertDialog(string strWindowTitle, string strButtonText)
{
	CConvertDialogData *pConvertDialogData = new CConvertDialogData;
	pConvertDialogData->m_bRadioButtonSelected = false;
	pConvertDialogData->m_strWindowTitle = strWindowTitle;
	pConvertDialogData->m_strButtonText = strButtonText;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_CONVERTDIALOG), getParentWindowHwnd(), DialogProc_ConvertDialog, (DWORD) pConvertDialogData);

	bool bRadioButtonSelected = pConvertDialogData->m_bRadioButtonSelected;
	uint32 uiRadioButtonIndex = pConvertDialogData->m_uiRadioButtonIndex;
	delete pConvertDialogData;
	if (bRadioButtonSelected)
	{
		return uiRadioButtonIndex;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

INT_PTR CALLBACK DialogProc_ExportViaDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CExportViaDialogData *pExportViaDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Export");

	pExportViaDialogData = (CExportViaDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pExportViaDialogData);
	break;
	case WM_COMMAND:
	switch (wParam)
	{
	case 3:
	EndDialog(hwndDlg, 0);
	break;
	case 4:
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_bRadioButtonSelected = true;
	if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 0))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 0;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 1))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 1;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 2))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 2;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 5))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 3;
	}
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
uint32		PopupGUIManager::showExportViaDialog(void)
{
	CExportViaDialogData *pExportViaDialogData = new CExportViaDialogData;
	pExportViaDialogData->m_bRadioButtonSelected = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_EXPORTVIADIALOG), getParentWindowHwnd(), DialogProc_ExportViaDialog, (DWORD) pExportViaDialogData);

	bool bRadioButtonSelected = pExportViaDialogData->m_bRadioButtonSelected;
	uint32 uiRadioButtonIndex = pExportViaDialogData->m_uiRadioButtonIndex;
	delete pExportViaDialogData;
	if (bRadioButtonSelected)
	{
		return uiRadioButtonIndex;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

INT_PTR CALLBACK DialogProc_TextAreaDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	TextInputDialogData *pTextInputDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pTextInputDialogData = (TextInputDialogData*)lParam;
	pDialog->SetWindowTextW(String::convertStdStringToStdWString(pTextInputDialogData->m_strWindowTitle).c_str());
	((CStatic*)pDialog->GetDlgItem(0))->SetWindowTextW(String::convertStdStringToStdWString(pTextInputDialogData->m_strStaticText).c_str());
	((CStatic*)pDialog->GetDlgItem(1))->SetWindowTextW(String::convertStdStringToStdWString(pTextInputDialogData->m_strEditText).c_str());

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pTextInputDialogData);
	break;
	case WM_COMMAND:
	switch (wParam)
	{
	case 2:
	((CEdit*)pDialog->GetDlgItem(1))->GetWindowTextW(strText);
	((TextInputDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_strResultText = String::convertCStringToStdString(strText);
	EndDialog(hwndDlg, 0);
	break;
	case 3:
	((TextInputDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_strResultText = "";
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
string				PopupGUIManager::showTextAreaDialog(string strWindowTitle, string strStaticText, string strEditText)
{
	TextInputDialogData *pTextInputDialogData = new TextInputDialogData;
	pTextInputDialogData->m_strWindowTitle = strWindowTitle;
	pTextInputDialogData->m_strStaticText = strStaticText;
	pTextInputDialogData->m_strEditText = strEditText;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_TEXTAREADIALOG), getParentWindowHwnd(), DialogProc_TextAreaDialog, (DWORD) pTextInputDialogData);

	string strInputText = pTextInputDialogData->m_strResultText;
	delete pTextInputDialogData;
	return strInputText;
}

INT_PTR CALLBACK DialogProc_SortOptionsDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CSortOptionsDialogData *pSortOptionsDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pSortOptionsDialogData = (CSortOptionsDialogData*)lParam;
	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Sort");
	for (uint32 i = 0; i < 10; i++)
	{
	SortPriority *pSortPriority = getIMGF()->getSortManager()->getSortPriorities()->getEntryByIndex((uint16)i);

	uint32 i2 = 0;
	for (auto pSortType : getIMGF()->getSortManager()->getSortTypes()->getEntries())
	{
	((CComboBox*)pDialog->GetDlgItem(i))->InsertString(i2, LocalizationManager::get()->getTranslatedFormattedTextW("Sort_ByText", pSortType->getText().c_str()).c_str());

	if (pSortPriority->isEnabled() && pSortPriority->getType()->getType() == pSortType->getType())
	{
	((CComboBox*)pDialog->GetDlgItem(i))->SetCurSel(i2);
	}

	i2++;
	}
	}

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pSortOptionsDialogData);
	break;
	case WM_COMMAND:
	pSortOptionsDialogData = (CSortOptionsDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 100:
	for (uint32 i = 0; i < 10; i++)
	{
	pSortOptionsDialogData->m_vecSortOptions.push_back(-1);
	}
	pSortOptionsDialogData->m_vecSortOptions.push_back(-1);
	EndDialog(hwndDlg, 0);
	break;
	case 101:
	for (uint32 i = 0; i < 10; i++)
	{
	pSortOptionsDialogData->m_vecSortOptions.push_back(((CComboBox*)pDialog->GetDlgItem(i))->GetCurSel());
	}
	pSortOptionsDialogData->m_vecSortOptions.push_back(0);
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	pSortOptionsDialogData = (CSortOptionsDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	for (uint32 i = 0; i < 10; i++)
	{
	pSortOptionsDialogData->m_vecSortOptions.push_back(-1);
	}
	pSortOptionsDialogData->m_vecSortOptions.push_back(-1);
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
vector<int>			PopupGUIManager::showSortOptionsDialog(void)
{
	CSortOptionsDialogData *pSortOptionsDialogData = new CSortOptionsDialogData;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_SORTOPTIONSDIALOG), getParentWindowHwnd(), DialogProc_SortOptionsDialog, (DWORD) pSortOptionsDialogData);

	vector<int> vecSortOptions = pSortOptionsDialogData->m_vecSortOptions;
	delete pSortOptionsDialogData;
	return vecSortOptions;
}

INT_PTR CALLBACK DialogProc_RemoveViaDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CExportViaDialogData *pExportViaDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Remove");

	pExportViaDialogData = (CExportViaDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pExportViaDialogData);
	break;
	case WM_COMMAND:
	switch (wParam)
	{
	case 3:
	EndDialog(hwndDlg, 0);
	break;
	case 4:
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_bRadioButtonSelected = true;
	if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 0))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 0;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 1))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 1;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 2))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 2;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 5))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 3;
	}
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
uint32		PopupGUIManager::showRemoveViaDialog(void)
{
	CExportViaDialogData *pExportViaDialogData = new CExportViaDialogData;
	pExportViaDialogData->m_bRadioButtonSelected = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_REMOVEVIADIALOG), getParentWindowHwnd(), DialogProc_RemoveViaDialog, (DWORD) pExportViaDialogData);

	bool bRadioButtonSelected = pExportViaDialogData->m_bRadioButtonSelected;
	uint32 uiRadioButtonIndex = pExportViaDialogData->m_uiRadioButtonIndex;
	delete pExportViaDialogData;
	if (bRadioButtonSelected)
	{
		return uiRadioButtonIndex;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

INT_PTR CALLBACK DialogProc_ImportViaDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CExportViaDialogData *pExportViaDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Import");

	pExportViaDialogData = (CExportViaDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pExportViaDialogData);
	break;
	case WM_COMMAND:
	switch (wParam)
	{
	case 3:
	EndDialog(hwndDlg, 0);
	break;
	case 4:
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_bRadioButtonSelected = true;
	if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 0))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 0;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 1))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 1;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 2))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 2;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 5))
	{
	((CExportViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 3;
	}
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
uint32		PopupGUIManager::showImportViaDialog(void)
{
	CExportViaDialogData *pExportViaDialogData = new CExportViaDialogData;
	pExportViaDialogData->m_bRadioButtonSelected = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_IMPORTVIADIALOG), getParentWindowHwnd(), DialogProc_ImportViaDialog, (DWORD) pExportViaDialogData);

	bool bRadioButtonSelected = pExportViaDialogData->m_bRadioButtonSelected;
	uint32 uiRadioButtonIndex = pExportViaDialogData->m_uiRadioButtonIndex;
	delete pExportViaDialogData;
	if (bRadioButtonSelected)
	{
		return uiRadioButtonIndex;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

INT_PTR CALLBACK DialogProc_StatsDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CStatsDialogData *pStatsDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	uint32 uiItemIndex;
	string strSaveFilePath, strSaveData = "";
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pStatsDialogData = (CStatsDialogData*)lParam;
	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Stats");
	((CListCtrl*)pDialog->GetDlgItem(1))->InsertColumn(0, LocalizationManager::get()->getTranslatedTextW("Window_Stats_StatName").c_str(), 0, 150);
	((CListCtrl*)pDialog->GetDlgItem(1))->InsertColumn(1, LocalizationManager::get()->getTranslatedTextW("Window_Stats_StatValue").c_str(), 1, 150);
	((CListCtrl*)pDialog->GetDlgItem(1))->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	for (auto it : pStatsDialogData->m_umapStatsExtensions)
	{
	uiItemIndex = ((CListCtrl*)pDialog->GetDlgItem(1))->GetItemCount();
	((CListCtrl*)pDialog->GetDlgItem(1))->InsertItem(uiItemIndex, String::convertStdStringToStdWString(it.first).c_str());
	((CListCtrl*)pDialog->GetDlgItem(1))->SetItem(uiItemIndex, 1, LVIF_TEXT, String::convertStdStringToStdWString(String::toString(it.second)).c_str(), 0, 0, 0, 0);
	}

	uiItemIndex = ((CListCtrl*)pDialog->GetDlgItem(1))->GetItemCount();
	((CListCtrl*)pDialog->GetDlgItem(1))->InsertItem(uiItemIndex, L"-");
	((CListCtrl*)pDialog->GetDlgItem(1))->SetItem(uiItemIndex, 1, LVIF_TEXT, L"-", 0, 0, 0, 0);

	for (auto it : pStatsDialogData->m_umapStatsRWVersions)
	{
	uint32 uiRWVersion = it.first;
	string strRWVersionName;
	if (pStatsDialogData->m_umapRWVersionNames.count(uiRWVersion) > 0)
	{
	strRWVersionName = pStatsDialogData->m_umapRWVersionNames[uiRWVersion];
	}
	else
	{
	char szData[20];
	sprintf_s(szData, "0x%X", uiRWVersion);
	strRWVersionName = szData;
	}

	uiItemIndex = ((CListCtrl*)pDialog->GetDlgItem(1))->GetItemCount();
	((CListCtrl*)pDialog->GetDlgItem(1))->InsertItem(uiItemIndex, String::convertStdStringToStdWString(strRWVersionName).c_str());
	((CListCtrl*)pDialog->GetDlgItem(1))->SetItem(uiItemIndex, 1, LVIF_TEXT, String::convertStdStringToStdWString(String::toString(it.second)).c_str(), 0, 0, 0, 0);
	}

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pStatsDialogData);
	break;
	case WM_COMMAND:
	pStatsDialogData = (CStatsDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 0:
	EndDialog(hwndDlg, 0);
	break;
	case 5:
	strSaveFilePath = Input::saveFileDialog(getIMGF()->getLastUsedDirectory("SAVE_STATS"), "TXT", LocalizationManager::get()->getTranslatedText("SaveFilePopup_1_InitialFilename"));
	if (strSaveFilePath != "")
	{
	getIMGF()->setLastUsedDirectory("SAVE_STATS", strSaveFilePath);
	for (int i = 0; i < ((CListCtrl*)pDialog->GetDlgItem(1))->GetItemCount(); i++)
	{
	CString strText1 = ((CListCtrl*)pDialog->GetDlgItem(1))->GetItemText(i, 0);
	CString strText2 = ((CListCtrl*)pDialog->GetDlgItem(1))->GetItemText(i, 1);
	strSaveData += String::convertCStringToStdString(strText1) + "\t" + String::convertCStringToStdString(strText2) + "\n";
	}
	File::storeFile(strSaveFilePath, strSaveData, false, false);
	}
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
void				PopupGUIManager::showStatsDialog(
	unordered_map<uint32, uint32>& umapStatsRWVersions,
	unordered_map<string, uint32>& umapStatsExtensions,
	unordered_map<uint32, string>& umapRWVersionNames
	)
{
	CStatsDialogData *pStatsDialogData = new CStatsDialogData;
	pStatsDialogData->m_umapStatsRWVersions = umapStatsRWVersions;
	pStatsDialogData->m_umapRWVersionNames = umapRWVersionNames;
	pStatsDialogData->m_umapStatsExtensions = umapStatsExtensions;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_STATSDIALOG), getParentWindowHwnd(), DialogProc_StatsDialog, (DWORD)pStatsDialogData);

	delete pStatsDialogData;
}

INT_PTR CALLBACK DialogProc_OrphanEntriesDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
	{
	/*
	COrphanEntriesData *pOrphanEntriesData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	uint32 uiItemIndex;
	string strSaveFilePath, strSaveData = "";
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pOrphanEntriesData = (COrphanEntriesData*)lParam;
	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "OrphanEntries");
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertColumn(0, LocalizationManager::get()->getTranslatedTextW("Window_OrphanEntries_EntryName").c_str(), 0, 200);
	((CListCtrl*)pDialog->GetDlgItem(100))->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	((CStatic*)pDialog->GetDlgItem(101))->SetWindowTextW(String::convertStdStringToStdWString(pOrphanEntriesData->m_strStaticText).c_str());
	((CStatic*)pDialog->GetDlgItem(102))->SetWindowTextW(String::convertStdStringToStdWString(pOrphanEntriesData->m_strButtonText).c_str());

	for (auto strEntryName : pOrphanEntriesData->m_vecEntryNames)
	{
	uiItemIndex = ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemCount();
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertItem(uiItemIndex, String::convertStdStringToStdWString(strEntryName).c_str());
	}

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pOrphanEntriesData);
	break;
	case WM_COMMAND:
	pOrphanEntriesData = (COrphanEntriesData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 103:
	EndDialog(hwndDlg, 0);
	break;
	case 102:
	pOrphanEntriesData->m_bProcessAction = true;
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}
	*/
	return FALSE;
}
bool				PopupGUIManager::showOrphanEntriesDialog(vector<string>& vecEntryNames, string strStaticText, string strButtonText)
{
	COrphanEntriesData *pOrphanEntriesData = new COrphanEntriesData;
	pOrphanEntriesData->m_strStaticText = strStaticText;
	pOrphanEntriesData->m_strButtonText = strButtonText;
	pOrphanEntriesData->m_vecEntryNames = vecEntryNames;
	pOrphanEntriesData->m_bProcessAction = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_ORPHANENTRIESDIALOG), getParentWindowHwnd(), DialogProc_OrphanEntriesDialog, (DWORD) pOrphanEntriesData);

	bool bProcessAction = pOrphanEntriesData->m_bProcessAction;
	delete pOrphanEntriesData;
	return bProcessAction;
}

static unordered_map<uint32, Language*> umapSettingsLanguageOptions;
INT_PTR CALLBACK DialogProc_SettingsDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CSettingsData *pSettingsData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	string strSaveFilePath, strSaveData = "";
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
	pSettingsData = (CSettingsData*)lParam;

	//ShowScrollBar(hwndDlg, SB_VERT, true);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Settings");

	pSettingsData->m_strQuickExportPath = getIMGF()->getSettingsManager()->getSettingString("QuickExportPath");
	pSettingsData->m_bColouredButtons = getIMGF()->getSettingsManager()->getSettingBool("ColouredButtons");
	pSettingsData->m_bColouredTabs = getIMGF()->getSettingsManager()->getSettingBool("ColouredTabs");
	pSettingsData->m_bRebuildConfirmationOnClose = getIMGF()->getSettingsManager()->getSettingBool("RebuildConfirmationOnClose");
	pSettingsData->m_bRebuildOnConvert = getIMGF()->getSettingsManager()->getSettingBool("RebuildOnConvert");
	pSettingsData->m_strAutomaticLoggingPath = getIMGF()->getSettingsManager()->getSettingString("AutomaticLoggingPath");
	pSettingsData->m_bAutomaticLoggingBasic = getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingBasic");
	pSettingsData->m_bAutomaticLoggingExtended = getIMGF()->getSettingsManager()->getSettingBool("AutomaticLoggingExtended");
	pSettingsData->m_bAskBeforeOverwritingFiles = getIMGF()->getSettingsManager()->getSettingBool("AskBeforeOverwritingFiles");
	pSettingsData->m_bOverwriteOlderFiles = getIMGF()->getSettingsManager()->getSettingBool("OverwriteOlderFiles");
	pSettingsData->m_bOverwriteNewerFiles = getIMGF()->getSettingsManager()->getSettingBool("OverwriteNewerFiles");
	pSettingsData->m_bOverwriteProtectedFiles = getIMGF()->getSettingsManager()->getSettingBool("OverwriteProtectedFiles");
	pSettingsData->m_bAutoSave = getIMGF()->getSettingsManager()->getSettingBool("AutoSave");
	pSettingsData->m_bRemoveOldVersionOnUpdate = getIMGF()->getSettingsManager()->getSettingBool("RemoveOldVersionOnUpdate");
	pSettingsData->m_bAutoCompressionImportReplace = getIMGF()->getSettingsManager()->getSettingBool("AutoCompressionImportReplace");
	pSettingsData->m_ELanguage = (ELanguage)getIMGF()->getSettingsManager()->getSettingInt("Language");

	// quick export path
	((CEdit*)pDialog->GetDlgItem(104))->SetWindowTextW(String::convertStdStringToStdWString(pSettingsData->m_strQuickExportPath).c_str());

	// language
	uint32
	uiLanguageOptionIndex = 0,
	uiActivELanguageOptionIndex = -1;
	umapSettingsLanguageOptions.clear();
	for (Language *pLanguage : getIMGF()->getLanguageManager()->getEntries())
	{
	((CComboBox*)pDialog->GetDlgItem(115))->AddString(LocalizationManager::get()->getTranslatedTextW(pLanguage->getLocalizationKey()).c_str());
	umapSettingsLanguageOptions[uiLanguageOptionIndex] = pLanguage;

	if (pLanguage->getLanguageId() == pSettingsData->m_ELanguage)
	{
	uiActivELanguageOptionIndex = uiLanguageOptionIndex;
	}
	uiLanguageOptionIndex++;
	}
	if (uiActivELanguageOptionIndex != -1)
	{
	((CComboBox*)pDialog->GetDlgItem(115))->SetCurSel(uiActivELanguageOptionIndex);
	}

	// checkboxes
	((Button*)pDialog->GetDlgItem(102))->SetCheck(pSettingsData->m_bColouredButtons ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(106))->SetCheck(pSettingsData->m_bColouredTabs ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(107))->SetCheck(pSettingsData->m_bRebuildConfirmationOnClose ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(108))->SetCheck(pSettingsData->m_bRebuildOnConvert ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(150))->SetCheck(pSettingsData->m_bAskBeforeOverwritingFiles ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(151))->SetCheck(pSettingsData->m_bOverwriteOlderFiles ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(152))->SetCheck(pSettingsData->m_bOverwriteNewerFiles ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(153))->SetCheck(pSettingsData->m_bOverwriteProtectedFiles ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(120))->SetCheck(pSettingsData->m_bAutoSave ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(121))->SetCheck(pSettingsData->m_bRemoveOldVersionOnUpdate ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(154))->SetCheck(pSettingsData->m_bAutoCompressionImportReplace ? BST_CHECKED : BST_UNCHECKED);

	// automatic logging
	((CEdit*)pDialog->GetDlgItem(110))->SetWindowTextW(String::convertStdStringToStdWString(pSettingsData->m_strAutomaticLoggingPath).c_str());
	((Button*)pDialog->GetDlgItem(112))->SetCheck(pSettingsData->m_bAutomaticLoggingBasic ? BST_CHECKED : BST_UNCHECKED);
	((Button*)pDialog->GetDlgItem(113))->SetCheck(pSettingsData->m_bAutomaticLoggingExtended ? BST_CHECKED : BST_UNCHECKED);

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pSettingsData);
	break;
	}
	case WM_COMMAND:
	pSettingsData = (CSettingsData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 101: // cancel
	EndDialog(hwndDlg, 0);
	break;
	case 105: // save
	{
	pSettingsData->m_bSave = true;
	((CEdit*)pDialog->GetDlgItem(104))->GetWindowTextW(strText);
	pSettingsData->m_strQuickExportPath = String::convertCStringToStdString(strText);
	pSettingsData->m_bColouredButtons = ((Button*)pDialog->GetDlgItem(102))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bColouredTabs = ((Button*)pDialog->GetDlgItem(106))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bRebuildConfirmationOnClose = ((Button*)pDialog->GetDlgItem(107))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bRebuildOnConvert = ((Button*)pDialog->GetDlgItem(108))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bAutoSave = ((Button*)pDialog->GetDlgItem(120))->GetCheck() == BST_CHECKED;
	((CEdit*)pDialog->GetDlgItem(110))->GetWindowTextW(strText);
	pSettingsData->m_strAutomaticLoggingPath = String::convertCStringToStdString(strText);
	pSettingsData->m_bAutomaticLoggingBasic = ((Button*)pDialog->GetDlgItem(112))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bAutomaticLoggingExtended = ((Button*)pDialog->GetDlgItem(113))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bAskBeforeOverwritingFiles = ((Button*)pDialog->GetDlgItem(150))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bOverwriteOlderFiles = ((Button*)pDialog->GetDlgItem(151))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bOverwriteNewerFiles = ((Button*)pDialog->GetDlgItem(152))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bOverwriteProtectedFiles = ((Button*)pDialog->GetDlgItem(153))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bRemoveOldVersionOnUpdate = ((Button*)pDialog->GetDlgItem(121))->GetCheck() == BST_CHECKED;
	pSettingsData->m_bAutoCompressionImportReplace = ((Button*)pDialog->GetDlgItem(154))->GetCheck() == BST_CHECKED;

	uint32 uiLanguageOptionIndex = ((CComboBox*)pDialog->GetDlgItem(115))->GetCurSel();
	ELanguage
	ePreviousLanguage = pSettingsData->m_ELanguage,
	eNewLanguage = umapSettingsLanguageOptions[uiLanguageOptionIndex]->getLanguageId();
	pSettingsData->m_ELanguage = eNewLanguage;

	pSettingsData->m_bNewLanguageApplied = false;
	if (ePreviousLanguage != eNewLanguage)
	{
	TCHAR szModuleName[MAX_PATH];
	GetModuleFileName(NULL, szModuleName, MAX_PATH);
	string strExePath = String::convertStdWStringToStdString(szModuleName);

	uint32 uiResult2 = Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_61"), LocalizationManager::get()->getTranslatedText("TextPopupTitle_61"), MB_OKCANCEL);
	if (uiResult2 == IDOK)
	{
	ShellExecute(NULL, L"open", String::convertStdStringToStdWString(strExePath).c_str(), NULL, NULL, SW_SHOWNORMAL);
	pSettingsData->m_bNewLanguageApplied = true;
	}
	}

	getIMGF()->getSettingsManager()->setSettingString("QuickExportPath", pSettingsData->m_strQuickExportPath);
	getIMGF()->getSettingsManager()->setSettingBool("ColouredButtons", pSettingsData->m_bColouredButtons);
	getIMGF()->getSettingsManager()->setSettingBool("ColouredTabs", pSettingsData->m_bColouredTabs);
	getIMGF()->getSettingsManager()->setSettingBool("RebuildConfirmationOnClose", pSettingsData->m_bRebuildConfirmationOnClose);
	getIMGF()->getSettingsManager()->setSettingBool("RebuildOnConvert", pSettingsData->m_bRebuildOnConvert);
	getIMGF()->getSettingsManager()->setSettingString("AutomaticLoggingPath", pSettingsData->m_strAutomaticLoggingPath);
	getIMGF()->getSettingsManager()->setSettingBool("AutomaticLoggingBasic", pSettingsData->m_bAutomaticLoggingBasic);
	getIMGF()->getSettingsManager()->setSettingBool("AutomaticLoggingExtended", pSettingsData->m_bAutomaticLoggingExtended);
	getIMGF()->getSettingsManager()->setSettingBool("AskBeforeOverwritingFiles", pSettingsData->m_bAskBeforeOverwritingFiles);
	getIMGF()->getSettingsManager()->setSettingBool("OverwriteOlderFiles", pSettingsData->m_bOverwriteOlderFiles);
	getIMGF()->getSettingsManager()->setSettingBool("OverwriteNewerFiles", pSettingsData->m_bOverwriteNewerFiles);
	getIMGF()->getSettingsManager()->setSettingBool("OverwriteProtectedFiles", pSettingsData->m_bOverwriteProtectedFiles);
	getIMGF()->getSettingsManager()->setSettingBool("AutoSave", pSettingsData->m_bAutoSave);
	getIMGF()->getSettingsManager()->setSettingBool("RemoveOldVersionOnUpdate", pSettingsData->m_bRemoveOldVersionOnUpdate);
	getIMGF()->getSettingsManager()->setSettingBool("AutoCompressionImportReplace", pSettingsData->m_bAutoCompressionImportReplace);
	getIMGF()->getSettingsManager()->setSettingInt("Language", pSettingsData->m_ELanguage);

	EndDialog(hwndDlg, 0);
	break;
	}
	case 100: // choose (for quick export path)
	pSettingsData->m_strQuickExportPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_1"));
	((CEdit*)pDialog->GetDlgItem(104))->SetWindowTextW(String::convertStdStringToStdWString(pSettingsData->m_strQuickExportPath).c_str());
	break;
	case 111: // choose (for automatic logging path)
	pSettingsData->m_strAutomaticLoggingPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_2"));
	((CEdit*)pDialog->GetDlgItem(110))->SetWindowTextW(String::convertStdStringToStdWString(pSettingsData->m_strAutomaticLoggingPath).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
bool				PopupGUIManager::showSettingsDialog(void)
{
	CSettingsData *pSettingsData = new CSettingsData;
	pSettingsData->m_bSave = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_SETTINGSDIALOG), getParentWindowHwnd(), DialogProc_SettingsDialog, (DWORD) pSettingsData);

	bool bSave = pSettingsData->m_bSave;
	delete pSettingsData;
	return bSave;
}

INT_PTR CALLBACK DialogProc_ConfirmDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CConfirmDialogData *pConfirmDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	string strSaveFilePath, strSaveData = "";
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pConfirmDialogData = (CConfirmDialogData*)lParam;
	((CStatic*)pDialog->GetDlgItem(100))->SetWindowTextW(String::convertStdStringToStdWString(pConfirmDialogData->m_strStaticText).c_str());
	pDialog->SetWindowTextW(String::convertStdStringToStdWString(pConfirmDialogData->m_strWindowTitle).c_str());

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pConfirmDialogData);
	break;
	case WM_COMMAND:
	pConfirmDialogData = (CConfirmDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 101: // No
	pConfirmDialogData->m_bResult = false;
	EndDialog(hwndDlg, 0);
	break;
	case 102: // Yes
	pConfirmDialogData->m_bResult = true;
	EndDialog(hwndDlg, 0);
	break;
	case 103: // Cancel
	pConfirmDialogData->m_bResult = false;
	pConfirmDialogData->m_bCancel = true;
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
bool				PopupGUIManager::showConfirmDialog(string strStaticText, string strWindowTitle)
{
	CConfirmDialogData *pConfirmDialogData = new CConfirmDialogData;
	pConfirmDialogData->m_strStaticText = strStaticText;
	pConfirmDialogData->m_strWindowTitle = strWindowTitle;
	pConfirmDialogData->m_bResult = false;
	pConfirmDialogData->m_bCancel = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_CONFIRMDIALOG), getParentWindowHwnd(), DialogProc_ConfirmDialog, (DWORD) pConfirmDialogData);

	bool bResult = pConfirmDialogData->m_bResult;
	delete pConfirmDialogData;
	return bResult;
}
bool				PopupGUIManager::showConfirmDialog(string strStaticText, string strWindowTitle, bool& bDidCancel)
{
	CConfirmDialogData *pConfirmDialogData = new CConfirmDialogData;
	pConfirmDialogData->m_strStaticText = strStaticText;
	pConfirmDialogData->m_strWindowTitle = strWindowTitle;
	pConfirmDialogData->m_bResult = false;
	pConfirmDialogData->m_bCancel = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_CONFIRMDIALOG), getParentWindowHwnd(), DialogProc_ConfirmDialog, (DWORD) pConfirmDialogData);
	bDidCancel = pConfirmDialogData->m_bCancel;

	bool bResult = pConfirmDialogData->m_bResult;
	delete pConfirmDialogData;
	return bResult;
}

INT_PTR CALLBACK DialogProc_DumpDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CDumpDialogData *pDumpDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pDumpDialogData = (CDumpDialogData*)lParam;

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Dump");

	pDialog->GetDlgItem(142)->SetWindowTextW((L"- " + LocalizationManager::get()->getTranslatedTextW("Window_Dump_GameFolderPath")).c_str());
	pDialog->GetDlgItem(147)->SetWindowTextW((L"- " + LocalizationManager::get()->getTranslatedTextW("Window_Dump_GameFolderPath")).c_str());

	((Button*)pDialog->GetDlgItem(107))->SetCheck(BST_CHECKED);
	//((Button*)pDialog->GetDlgItem(161))->SetCheck(BST_CHECKED);

	pDumpDialogData->m_strDumpDestinationFolderPath = pDumpDialogData->m_strLastUsedPath__Destination;
	((CEdit*)pDialog->GetDlgItem(113))->SetWindowTextW(String::convertStdStringToStdWString(pDumpDialogData->m_strLastUsedPath__Destination).c_str());

	((CComboBox*)pDialog->GetDlgItem(141))->InsertString(0, LocalizationManager::get()->getTranslatedTextW("Game_III").c_str());
	((CComboBox*)pDialog->GetDlgItem(141))->InsertString(1, LocalizationManager::get()->getTranslatedTextW("Game_VC").c_str());
	((CComboBox*)pDialog->GetDlgItem(141))->InsertString(2, LocalizationManager::get()->getTranslatedTextW("Game_SA").c_str());
	((CComboBox*)pDialog->GetDlgItem(141))->InsertString(3, LocalizationManager::get()->getTranslatedTextW("Game_SOL").c_str());
	((CComboBox*)pDialog->GetDlgItem(141))->InsertString(4, LocalizationManager::get()->getTranslatedTextW("Other").c_str());
	((CComboBox*)pDialog->GetDlgItem(141))->SetCurSel(0);

	((CComboBox*)pDialog->GetDlgItem(145))->InsertString(0, LocalizationManager::get()->getTranslatedTextW("Game_III").c_str());
	((CComboBox*)pDialog->GetDlgItem(145))->InsertString(1, LocalizationManager::get()->getTranslatedTextW("Game_VC").c_str());
	((CComboBox*)pDialog->GetDlgItem(145))->InsertString(2, LocalizationManager::get()->getTranslatedTextW("Game_SA").c_str());
	((CComboBox*)pDialog->GetDlgItem(145))->InsertString(3, LocalizationManager::get()->getTranslatedTextW("Game_SOL").c_str());
	((CComboBox*)pDialog->GetDlgItem(145))->SetCurSel(0);

	/*
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(0, L"Choose:");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(1, L"CUR (.cur)");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(2, L"ICO (.ico)");
	((CComboBox*)pDialog->GetDlgItem(156))->SetCurSel(0);
	*/

	/*
	todo

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD) pDumpDialogData);
	break;
	case WM_COMMAND:
		pDumpDialogData = (CDumpDialogData*) GetWindowLong(hwndDlg, GWL_USERDATA);
		switch (wParam)
		{
		case 111: // cancel
			pDumpDialogData->m_bResult = false;
			EndDialog(hwndDlg, 0);
			break;
		case 112: // dump
			if (((Button*) pDialog->GetDlgItem(107))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_uiDumpType = 0;
			}
			else if (((Button*) pDialog->GetDlgItem(160))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_uiDumpType = 4;
			}
			else if (((Button*) pDialog->GetDlgItem(106))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_uiDumpType = 1;
			}
			else if (((Button*) pDialog->GetDlgItem(108))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_uiDumpType = 2;
			}
			else if (((Button*) pDialog->GetDlgItem(109))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_uiDumpType = 3;
			}

			if (pDumpDialogData->m_strDumpDestinationFolderPath == "")
			{
				Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_2"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
				break;
			}

			if (pDumpDialogData->m_uiDumpType == 2) // DAT file
			{
				pDumpDialogData->m_uiDATOptionIndex = ((CComboBox*) pDialog->GetDlgItem(141))->GetCurSel();

				if (pDumpDialogData->m_uiDATOptionIndex == 4 && pDumpDialogData->m_strDATPath == "") // 4 is Other
				{
					Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_3"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
					break;
				}
				if (pDumpDialogData->m_strGameDirectoryPath == "")
				{
					Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_4"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
					break;
				}
			}

			if (pDumpDialogData->m_uiDumpType == 3) // Game IMGs
			{
				pDumpDialogData->m_uiGameIndex = ((CComboBox*) pDialog->GetDlgItem(141))->GetCurSel();

				if (pDumpDialogData->m_strGameDirectoryPath == "")
				{
					Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_5"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
					break;
				}
			}

			pDumpDialogData->m_bResult = true;

			// dump entry types
			if (((Button*) pDialog->GetDlgItem(102))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpExtensions.push_back("COL");
			}
			if (((Button*) pDialog->GetDlgItem(100))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpExtensions.push_back("DFF");
			}
			if (((Button*) pDialog->GetDlgItem(103))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpExtensions.push_back("IPL");
			}
			if (((Button*) pDialog->GetDlgItem(104))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpExtensions.push_back(LocalizationManager::get()->getTranslatedText("Window_Dump_104"));
			}
			if (((Button*) pDialog->GetDlgItem(101))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpExtensions.push_back("TXD");
			}
			if (((Button*) pDialog->GetDlgItem(105))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpExtensions.push_back("Other");
			}

			// image formats for texture extraction
			if (((Button*) pDialog->GetDlgItem(150))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("BMP");
			}
			if (((Button*) pDialog->GetDlgItem(151))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("GIF");
			}
			if (((Button*) pDialog->GetDlgItem(152))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("JPG");
			}
			if (((Button*) pDialog->GetDlgItem(153))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("PNG");
			}
			if (((Button*) pDialog->GetDlgItem(154))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("TGA");
			}
			if (((Button*) pDialog->GetDlgItem(155))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("TIFF");
			}
			if (((Button*) pDialog->GetDlgItem(156))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("CUR");
			}
			if (((Button*) pDialog->GetDlgItem(157))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("ICO");
			}
			if (((Button*) pDialog->GetDlgItem(158))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_vecDumpImageTypes.push_back("DDS");
			}

			// options
			if (((Button*) pDialog->GetDlgItem(170))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_bDumpTextureImagesAsFolders = true;
			}
			if (((Button*) pDialog->GetDlgItem(171))->GetCheck() == BST_CHECKED)
			{
				pDumpDialogData->m_bDumpAllTextureMipmaps = true;
			}

			EndDialog(hwndDlg, 0);
			break;
		case 141: // DAT file path dropdown option
				  // this doesn't get called here when the user changes the selected option in the dropdown
			break;
		case 115: // Change button for DAT file path
			vecFilePaths = Input::openFile(pDumpDialogData->m_strLastUsedPath__DAT, "DAT", false);
			if (vecFilePaths.size() == 0)
			{
				break;
			}
			pDumpDialogData->m_strDATPath = vecFilePaths[0];
			((CEdit*) pDialog->GetDlgItem(116))->SetWindowTextW(String::convertStdStringToStdWString(pDumpDialogData->m_strDATPath).c_str());
			break;
		case 144: // Change button for Game folder path
		case 148:
			pDumpDialogData->m_strGameDirectoryPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("DUMP__GAME"));
			if (pDumpDialogData->m_strGameDirectoryPath == "")
			{
				break;
			}
			pDumpDialogData->m_strGameDirectoryPath = Path::addSlashToEnd(pDumpDialogData->m_strGameDirectoryPath);
			getIMGF()->setLastUsedDirectory("DUMP__GAME", pDumpDialogData->m_strGameDirectoryPath);
			((CEdit*) pDialog->GetDlgItem(143))->SetWindowTextW(String::convertStdStringToStdWString(pDumpDialogData->m_strGameDirectoryPath).c_str());
			((CEdit*) pDialog->GetDlgItem(149))->SetWindowTextW(String::convertStdStringToStdWString(pDumpDialogData->m_strGameDirectoryPath).c_str());
			break;
		case 110: // Change button for dump destination folder path
			pDumpDialogData->m_strDumpDestinationFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_4"), pDumpDialogData->m_strLastUsedPath__Destination);
			if (pDumpDialogData->m_strDumpDestinationFolderPath == "")
			{
				break;
			}
			pDumpDialogData->m_strDumpDestinationFolderPath = Path::addSlashToEnd(pDumpDialogData->m_strDumpDestinationFolderPath);
			((CEdit*) pDialog->GetDlgItem(113))->SetWindowTextW(String::convertStdStringToStdWString(pDumpDialogData->m_strDumpDestinationFolderPath).c_str());
			break;
		}
		break;
	case WM_CLOSE:
		pDumpDialogData = (CDumpDialogData*) GetWindowLong(hwndDlg, GWL_USERDATA);
		pDumpDialogData->m_bResult = false;
		EndDialog(hwndDlg, 0);
		break;
	}
	*/
return FALSE;
}
CDumpDialogData*		PopupGUIManager::showDumpDialog(string strLastUsedPath__DAT, string strLastUsedPath__Destination)
{
	CDumpDialogData *pDumpDialogData = new CDumpDialogData;
	pDumpDialogData->m_strLastUsedPath__DAT = strLastUsedPath__DAT;
	pDumpDialogData->m_strLastUsedPath__Destination = strLastUsedPath__Destination;
	pDumpDialogData->m_bDumpTextureImagesAsFolders = false;
	pDumpDialogData->m_bDumpAllTextureMipmaps = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DUMPDIALOG), getParentWindowHwnd(), DialogProc_DumpDialog, (DWORD) pDumpDialogData);

	return pDumpDialogData;
}

INT_PTR CALLBACK DialogProc_ListViewDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CListViewDialogData *pListViewDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	uint32 uiItemIndex;
	string strSaveFilePath, strSaveData = "";
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pListViewDialogData = (CListViewDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pListViewDialogData);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "ListView");

	pDialog->SetWindowTextW(String::convertStdStringToStdWString(pListViewDialogData->m_strWindowTitle).c_str());

	((CListCtrl*)pDialog->GetDlgItem(100))->InsertColumn(0, String::convertStdStringToStdWString(pListViewDialogData->m_strCol1Text).c_str(), 0, 200);
	((CListCtrl*)pDialog->GetDlgItem(100))->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	((CStatic*)pDialog->GetDlgItem(101))->SetWindowTextW(String::convertStdStringToStdWString(pListViewDialogData->m_strStaticText).c_str());

	for (auto strLineText : pListViewDialogData->m_vecLines)
	{
	uiItemIndex = ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemCount();
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertItem(uiItemIndex, String::convertStdStringToStdWString(strLineText).c_str());
	}

	break;
	case WM_COMMAND:
	pListViewDialogData = (CListViewDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 103:
	EndDialog(hwndDlg, 0);
	break;
	case 102:
	strSaveFilePath = Input::saveFileDialog(getIMGF()->getLastUsedDirectory("LISTVIEW__" + pListViewDialogData->m_strSaveFolderPartialHandle), "TXT", pListViewDialogData->m_strSaveFileName);
	if (strSaveFilePath != "")
	{
	getIMGF()->setLastUsedDirectory("LISTVIEW__" + pListViewDialogData->m_strSaveFolderPartialHandle, strSaveFilePath);
	for (int i = 0; i < ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemCount(); i++)
	{
	CString strText1 = ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemText(i, 0);
	strSaveData += String::convertCStringToStdString(strText1) + "\n";
	}
	File::storeFile(strSaveFilePath, strSaveData, false, false);
	}
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
void				PopupGUIManager::showListViewDialog(string strWindowTitle, string strStaticText, string strCol1Text, vector<string>& vecLines, string strSaveFileName, string strSaveFolderPartialHandle)
{
	CListViewDialogData *pListViewDialogData = new CListViewDialogData;
	pListViewDialogData->m_strWindowTitle = strWindowTitle;
	pListViewDialogData->m_strStaticText = strStaticText;
	pListViewDialogData->m_vecLines = vecLines;
	pListViewDialogData->m_strCol1Text = strCol1Text;
	pListViewDialogData->m_strSaveFileName = strSaveFileName;
	pListViewDialogData->m_strSaveFolderPartialHandle = strSaveFolderPartialHandle;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_LISTVIEWDIALOG), getParentWindowHwnd(), DialogProc_ListViewDialog, (DWORD) pListViewDialogData);

	delete pListViewDialogData;
}

INT_PTR CALLBACK DialogProc_TextureListDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	TextureListDialogData *pTextureListDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	uint32 uiItemIndex;
	string strSaveFilePath, strSaveData = "";
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pTextureListDialogData = (TextureListDialogData*)lParam;

	pDialog->SetWindowTextW(String::convertStdStringToStdWString(pTextureListDialogData->m_strWindowTitle).c_str());

	((CListCtrl*)pDialog->GetDlgItem(100))->InsertColumn(0, String::convertStdStringToStdWString(pTextureListDialogData->m_strCol1Text).c_str(), 0, 200);
	((CListCtrl*)pDialog->GetDlgItem(100))->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	((CStatic*)pDialog->GetDlgItem(101))->SetWindowTextW(String::convertStdStringToStdWString(pTextureListDialogData->m_strStaticText).c_str());

	for (auto strTextureName : pTextureListDialogData->m_vecLines)
	{
	uiItemIndex = ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemCount();
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertItem(uiItemIndex, String::convertStdStringToStdWString(strTextureName).c_str());
	}

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pTextureListDialogData);
	break;
	case WM_COMMAND:
	pTextureListDialogData = (TextureListDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 104:
	pTextureListDialogData->m_bSaveTexturesFormat2 = true;
	EndDialog(hwndDlg, 0);
	break;
	case 103:
	EndDialog(hwndDlg, 0);
	break;
	case 102:
	strSaveFilePath = Input::saveFileDialog(getIMGF()->getLastUsedDirectory("TEXTURE_LIST"), "TXT", LocalizationManager::get()->getTranslatedText("SaveFilePopup_2_InitialFilename"));
	if (strSaveFilePath != "")
	{
	getIMGF()->setLastUsedDirectory("TEXTURE_LIST", strSaveFilePath);
	for (int i = 0; i < ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemCount(); i++)
	{
	CString strText1 = ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemText(i, 0);
	strSaveData += String::convertCStringToStdString(strText1) + "\n";
	}
	File::storeFile(strSaveFilePath, strSaveData, false, false);
	}
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
TextureListDialogData*		PopupGUIManager::showTextureListDialog(string strWindowTitle, string strStaticText, string strCol1Text, vector<string>& vecLines)
{
	TextureListDialogData *pTextureListDialogData = new TextureListDialogData;
	pTextureListDialogData->m_strWindowTitle = strWindowTitle;
	pTextureListDialogData->m_strStaticText = strStaticText;
	pTextureListDialogData->m_vecLines = vecLines;
	pTextureListDialogData->m_strCol1Text = strCol1Text;
	pTextureListDialogData->m_bSaveTexturesFormat2 = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_LISTVIEWDIALOG), getParentWindowHwnd(), DialogProc_TextureListDialog, (DWORD) pTextureListDialogData);

	//delete pTextureListDialogData;
	// caller must delete

	return pTextureListDialogData;
}

INT_PTR CALLBACK DialogProc_SessionManagerDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	SessionManagerDialogData *pSessionManagerDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	CString strText;
	uint32 uiItemIndex;
	string strSaveFilePath, strSaveData = "";
	uint32 uiSessionIndex;

	string strNewSessionData, strSessionName;
	CListCtrl *pListControl;
	POSITION pos;
	int nItem;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	pSessionManagerDialogData = (SessionManagerDialogData*)lParam;

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "SessionManager");

	((CListCtrl*)pDialog->GetDlgItem(100))->InsertColumn(0, LocalizationManager::get()->getTranslatedTextW("Window_SessionManager_Column_1").c_str(), 0, 80);
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertColumn(1, LocalizationManager::get()->getTranslatedTextW("SessionName").c_str(), 0, 150);
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertColumn(2, LocalizationManager::get()->getTranslatedTextW("Window_SessionManager_Column_3").c_str(), 0, 80);
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertColumn(3, LocalizationManager::get()->getTranslatedTextW("Window_SessionManager_Column_4").c_str(), 0, 275);
	((CListCtrl*)pDialog->GetDlgItem(100))->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);

	uiSessionIndex = 0;
	for (auto strSessionData : pSessionManagerDialogData->m_vecSessionsData)
	{
	deque<string> deqIMGPaths = StdVector::convertVectorToDeque(String::split(strSessionData, ";"));
	string strSessionName = deqIMGPaths[0];
	deqIMGPaths.pop_front();
	uint32 uiIMGFileCount = deqIMGPaths.size();
	vector<string> vecIMGNames;
	for (uint32 i2 = 0; i2 < uiIMGFileCount; i2++)
	{
	vecIMGNames.push_back(Path::getFileName(deqIMGPaths[i2]));
	}

	uiItemIndex = ((CListCtrl*)pDialog->GetDlgItem(100))->GetItemCount();
	((CListCtrl*)pDialog->GetDlgItem(100))->InsertItem(uiItemIndex, String::convertStdStringToStdWString(String::toString(uiSessionIndex + 1)).c_str());
	((CListCtrl*)pDialog->GetDlgItem(100))->SetItem(uiItemIndex, 1, LVIF_TEXT, String::convertStdStringToStdWString(strSessionName).c_str(), 0, 0, 0, 0);
	((CListCtrl*)pDialog->GetDlgItem(100))->SetItem(uiItemIndex, 2, LVIF_TEXT, String::convertStdStringToStdWString(String::toString(uiIMGFileCount)).c_str(), 0, 0, 0, 0);
	((CListCtrl*)pDialog->GetDlgItem(100))->SetItem(uiItemIndex, 3, LVIF_TEXT, String::convertStdStringToStdWString(String::join(vecIMGNames, "; ")).c_str(), 0, 0, 0, 0);

	uiSessionIndex++;
	}

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pSessionManagerDialogData);
	break;
	case WM_COMMAND:
	pSessionManagerDialogData = (SessionManagerDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 101:
	// add session
	strNewSessionData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(LocalizationManager::get()->getTranslatedText("AddSession"), LocalizationManager::get()->getTranslatedText("Window_TextArea_1_Message"));
	if (String::split(strNewSessionData, "\n").size() >= 2)
	{
	pSessionManagerDialogData->m_vecSessionsToAdd.push_back(String::join(String::split(strNewSessionData, "\n"), "; "));
	EndDialog(hwndDlg, 0);
	}
	break;
	case 102:
	// update session
	pListControl = ((CListCtrl*)pDialog->GetDlgItem(100));
	pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
	break;
	}
	nItem = pListControl->GetNextSelectedItem(pos);
	strSessionName = String::convertCStringToStdString(pListControl->GetItemText(nItem, 1));

	for (auto strSessionData : pSessionManagerDialogData->m_vecSessionsData)
	{
	if (String::split(strSessionData, "; ")[0] == strSessionName)
	{
	//Debugger::log(strSessionData);
	strNewSessionData = getIMGF()->getPopupGUIManager()->showTextAreaDialog(LocalizationManager::get()->getTranslatedText("UpdateSession"), LocalizationManager::get()->getTranslatedText("Window_TextArea_1_Message"), String::join(String::split(strSessionData, "; "), "\n"));
	if (String::split(strNewSessionData, "\n").size() >= 2)
	{
	pSessionManagerDialogData->m_strSessionNameToUpdate = strSessionName;
	pSessionManagerDialogData->m_strSessionDataToUpdate = String::join(String::split(strNewSessionData, "\n"), "; ");
	EndDialog(hwndDlg, 0);
	}
	break;
	}
	}
	break;
	case 103:
	// delete sessions
	pListControl = ((CListCtrl*)pDialog->GetDlgItem(100));
	pos = pListControl->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
	break;
	}
	while (pos)
	{
	nItem = pListControl->GetNextSelectedItem(pos);
	pSessionManagerDialogData->m_vecSessionsToRemove.push_back(String::convertCStringToStdString(pListControl->GetItemText(nItem, 1)));
	pListControl->DeleteItem(nItem);

	pos = pListControl->GetFirstSelectedItemPosition();
	}
	EndDialog(hwndDlg, 0);
	break;
	case 104:
	// close
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
SessionManagerDialogData*	PopupGUIManager::showSessionManagerDialog(vector<string>& vecSessionsData)
{
	SessionManagerDialogData *pSessionManagerDialogData = new SessionManagerDialogData;
	pSessionManagerDialogData->m_vecSessionsData = vecSessionsData;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_SESSIONMANAGERDIALOG), getParentWindowHwnd(), DialogProc_SessionManagerDialog, (DWORD) pSessionManagerDialogData);

	// caller must delete
	return pSessionManagerDialogData;
}

INT_PTR CALLBACK DialogProc_SplitViaDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CSplitViaDialogData *pSplitViaDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Split");

	pSplitViaDialogData = (CSplitViaDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pSplitViaDialogData);
	break;
	case WM_COMMAND:
	switch (wParam)
	{
	case 3:
	EndDialog(hwndDlg, 0);
	break;
	case 4:
	((CSplitViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_bRadioButtonSelected = true;
	if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 0))
	{
	((CSplitViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 0;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 1))
	{
	((CSplitViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 1;
	}
	else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 2))
	{
	((CSplitViaDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA))->m_uiRadioButtonIndex = 2;
	}
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
uint32		PopupGUIManager::showSplitViaDialog(void)
{
	CSplitViaDialogData *pSplitViaDialogData = new CSplitViaDialogData;
	pSplitViaDialogData->m_bRadioButtonSelected = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_SPLITVIADIALOG), getParentWindowHwnd(), DialogProc_SplitViaDialog, (DWORD) pSplitViaDialogData);

	bool bRadioButtonSelected = pSplitViaDialogData->m_bRadioButtonSelected;
	uint32 uiRadioButtonIndex = pSplitViaDialogData->m_uiRadioButtonIndex;
	delete pSplitViaDialogData;
	if (bRadioButtonSelected)
	{
		return uiRadioButtonIndex;
	}
	else
	{
		return 0xFFFFFFFF;
	}
}

INT_PTR CALLBACK DialogProc_DragDropDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	DragDropDialogData *pDragDropDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	uint32 i;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "DragDrop");

	pDragDropDialogData = (DragDropDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pDragDropDialogData);

	// default drag/drop operation
	((Button*)pDialog->GetDlgItem(11))->SetCheck(BST_CHECKED);

	// conversion options - DFF
	// - RW versions
	i = 0;
	((CComboBox*)pDialog->GetDlgItem(52))->AddString(LocalizationManager::get()->getTranslatedTextW("RWVersion").c_str());
	i++;
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
	if (pRWVersion->getFileType() == TYPE_MODEL)
	{
	((CComboBox*)pDialog->GetDlgItem(52))->AddString(String::convertStdStringToStdWString(pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").c_str());
	// todo getIMGF()->m_umapMenuItemMapping_ConvertDFFtoRWVersion_DragDrop[i] = pRWVersion;
	i++;
	}

	// conversion options - default for DFF
	if (pDragDropDialogData->m_uiDestinationIMGVersion == IMG_1 && pRWVersion->getVersionId() == RW_3_4_0_3)
	{
	((CComboBox*)pDialog->GetDlgItem(52))->SetCurSel(((CComboBox*)pDialog->GetDlgItem(52))->GetCount() - 1); // VC
	}
	else if (pDragDropDialogData->m_uiDestinationIMGVersion == IMG_2 && pRWVersion->getVersionId() == RW_3_6_0_3)
	{
	((CComboBox*)pDialog->GetDlgItem(52))->SetCurSel(((CComboBox*)pDialog->GetDlgItem(52))->GetCount() - 1); // SA
	}
	}

	// conversion options - COL
	// - COL versions
	i = 0;
	((CComboBox*)pDialog->GetDlgItem(56))->AddString(LocalizationManager::get()->getTranslatedTextW("COLVersion").c_str());
	i++;
	for (auto pCOLVersion : COLManager::get()->getVersionManager()->getEntries())
	{
	((CComboBox*)pDialog->GetDlgItem(56))->AddString(String::convertStdStringToStdWString(pCOLVersion->getText()).c_str());
	// todo getIMGF()->m_umapMenuItemMapping_ConvertCOLtoCOLVersion_DragDrop[i] = pCOLVersion;
	i++;

	// conversion options - default for COL
	if (pDragDropDialogData->m_uiDestinationIMGVersion == IMG_1 && pCOLVersion->getVersionId() == COL_2)
	{
	((CComboBox*)pDialog->GetDlgItem(56))->SetCurSel(((CComboBox*)pDialog->GetDlgItem(56))->GetCount() - 1); // VC
	}
	else if (pDragDropDialogData->m_uiDestinationIMGVersion == IMG_2 && pCOLVersion->getVersionId() == COL_3)
	{
	((CComboBox*)pDialog->GetDlgItem(56))->SetCurSel(((CComboBox*)pDialog->GetDlgItem(56))->GetCount() - 1); // SA
	}
	}

	// conversion options - TXD
	// - games
	((CComboBox*)pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_Game").c_str());
	/*
	for (auto pGame : CGeneralManager::get()->getGameManager()->getEntries())
	{
	((CComboBox*)pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW(pGame->getLocalizationKey()).c_str());
	}
	*/

	/*
	todo
	((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("Game_III").c_str());
	((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("Game_VC").c_str());
	((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("Game_SA").c_str());
	((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("GTA_Android").c_str());
	((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("GTA_XBOX").c_str());

	// - RW versions
	i = 6;
	((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("RWVersion").c_str());
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
		if (pRWVersion->getFileType() == TYPE_MODEL)
		{
			((CComboBox*) pDialog->GetDlgItem(54))->AddString(String::convertStdStringToStdWString(pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").c_str());
			// todo getIMGF()->m_umapMenuItemMapping_ConvertTXDtoRWVersion_DragDrop[i] = pRWVersion;
			i++;
		}
	}

	// - texture formats
	((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW("Menu_Convert_TXD_TextureFormat").c_str());
	for (auto pRasterDataFormat : ImageManager::get()->getRasterDataFormatManager()->getEntries())
	{
		((CComboBox*) pDialog->GetDlgItem(54))->AddString(LocalizationManager::get()->getTranslatedTextW(pRasterDataFormat->getLocalizationKey()).c_str());
		// todo getIMGF()->m_umapMenuItemMapping_ConvertTXDtoTextureFormat_DragDrop[i] = pRasterDataFormat;
		i++;
	}

	// conversion options - default for TXD
	if (pDragDropDialogData->m_uiDestinationIMGVersion == IMG_1)
	{
		((CComboBox*) pDialog->GetDlgItem(54))->SetCurSel(2); // VC
	}
	else if (pDragDropDialogData->m_uiDestinationIMGVersion == IMG_2)
	{
		((CComboBox*) pDialog->GetDlgItem(54))->SetCurSel(3); // SA
	}

	break;
	case WM_COMMAND:
		pDragDropDialogData = (DragDropDialogData*) GetWindowLong(hwndDlg, GWL_USERDATA);
		switch (wParam)
		{
		case 2: // Cancel button
			pDragDropDialogData->m_bCancel = true;
			EndDialog(hwndDlg, 0);
			break;
		case 1: // OK button
			pDragDropDialogData->m_bCancel = false;
			if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 11)) // Copy
			{
				pDragDropDialogData->m_bCopy = true;
				pDragDropDialogData->m_bConvert = false;
			}
			else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 12)) // Move
			{
				pDragDropDialogData->m_bCopy = false;
				pDragDropDialogData->m_bConvert = false;
			}
			else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 13)) // Copy & Convert
			{
				pDragDropDialogData->m_bCopy = true;
				pDragDropDialogData->m_bConvert = true;
			}
			else if (IsDlgButtonChecked(pDialog->GetSafeHwnd(), 14)) // Move & Convert
			{
				pDragDropDialogData->m_bCopy = false;
				pDragDropDialogData->m_bConvert = true;
			}

			//////////////
			todo

			pDragDropDialogData->m_pDFFConversionRWVersion = getIMGF()->m_umapMenuItemMapping_ConvertDFFtoRWVersion_DragDrop[((CComboBox*)pDialog->GetDlgItem(52))->GetCurSel()];
			pDragDropDialogData->m_pNewCOLVersion = getIMGF()->m_umapMenuItemMapping_ConvertCOLtoCOLVersion_DragDrop[((CComboBox*)pDialog->GetDlgItem(56))->GetCurSel()];
			int uiTXDConversionComboOption = ((CComboBox*)pDialog->GetDlgItem(54))->GetCurSel();
			pDragDropDialogData->m_uiTXDConversionOption = 0;
			if (uiTXDConversionComboOption >= 1 && uiTXDConversionComboOption <= 5)
			{
			pDragDropDialogData->m_uiTXDConversionOption = 1; // game
			//pDragDropDialogData->m_uiTXDConversionGame = GTA_III;
			}
			else if (getIMGF()->m_umapMenuItemMapping_ConvertTXDtoRWVersion_DragDrop.find(uiTXDConversionComboOption) != getIMGF()->m_umapMenuItemMapping_ConvertTXDtoRWVersion_DragDrop.end())
			{
			pDragDropDialogData->m_uiTXDConversionOption = 2; // rw version
			pDragDropDialogData->m_pTXDConversionRWVersion = getIMGF()->m_umapMenuItemMapping_ConvertTXDtoRWVersion_DragDrop[uiTXDConversionComboOption];
			}
			else if (getIMGF()->m_umapMenuItemMapping_ConvertTXDtoTextureFormat_DragDrop.find(uiTXDConversionComboOption) != getIMGF()->m_umapMenuItemMapping_ConvertTXDtoTextureFormat_DragDrop.end())
			{
			pDragDropDialogData->m_uiTXDConversionOption = 3; // texture format
			pDragDropDialogData->m_pTXDConversionRasterDataFormat = getIMGF()->m_umapMenuItemMapping_ConvertTXDtoTextureFormat_DragDrop[uiTXDConversionComboOption];
			}
			/////////////////

			EndDialog(hwndDlg, 0);
			break;
		}
		break;
	case WM_CLOSE:
		pDragDropDialogData = (DragDropDialogData*) GetWindowLong(hwndDlg, GWL_USERDATA);
		pDragDropDialogData->m_bCancel = true;
		EndDialog(hwndDlg, 0);
		break;
}

*/
return FALSE;
}
DragDropDialogData*			PopupGUIManager::showDragDropDialog(DragDropDialogData *pDragDropDialogData)
{
	pDragDropDialogData->m_bCopy = true;
	pDragDropDialogData->m_bConvert = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DRAGDROPDIALOG), getParentWindowHwnd(), DialogProc_DragDropDialog, (DWORD) pDragDropDialogData);

	return pDragDropDialogData;
}


CDumpResultsDialogData::CDumpResultsDialogData(void) :
	m_bOpenAdvancedLog(false)
{
}

INT_PTR CALLBACK DialogProc_DumpResultsDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CDumpResultsDialogData *pDumpResultsDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	pDumpResultsDialogData = (CDumpResultsDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pDumpResultsDialogData);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "DumpResults");

	SetWindowText(pDialog->GetDlgItem(1)->GetSafeHwnd(), String::convertStdStringToStdWString(String::toString(pDumpResultsDialogData->m_uiCorruptTXDCount)).c_str());
	SetWindowText(pDialog->GetDlgItem(2)->GetSafeHwnd(), String::convertStdStringToStdWString(String::toString(pDumpResultsDialogData->m_uiTooLargeTXDCount)).c_str());
	SetWindowText(pDialog->GetDlgItem(3)->GetSafeHwnd(), String::convertStdStringToStdWString(String::toString(pDumpResultsDialogData->m_uiInvalidResolutionTXDCount)).c_str());
	SetWindowText(pDialog->GetDlgItem(4)->GetSafeHwnd(), String::convertStdStringToStdWString(String::toString(pDumpResultsDialogData->m_uiInvalidTextureNameCount)).c_str());
	SetWindowText(pDialog->GetDlgItem(5)->GetSafeHwnd(), String::convertStdStringToStdWString(String::toString(pDumpResultsDialogData->m_uiTXDCountExceededTextureCountLimit)).c_str());
	SetWindowText(pDialog->GetDlgItem(6)->GetSafeHwnd(), String::convertStdStringToStdWString(String::toString(pDumpResultsDialogData->m_uiMipmapSkippedCount)).c_str());
	break;
	case WM_COMMAND:
	pDumpResultsDialogData = (CDumpResultsDialogData*) GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 10: // close button
	EndDialog(hwndDlg, 0);
	break;
	case 11: // open advancded log button
	pDumpResultsDialogData->m_bOpenAdvancedLog = true;
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
void				PopupGUIManager::showDumpResultsDialog(CDumpResultsDialogData *pDumpResultsDialogData)
{
	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DUMPRESULTSDIALOG), getParentWindowHwnd(), DialogProc_DumpResultsDialog, (DWORD) pDumpResultsDialogData);
}

INT_PTR CALLBACK DialogProc_CreditsDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	//CCreditsDialogData *pCreditsDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Credits");

	pDialog->GetDlgItem(2)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Credits_ProjectLeader").c_str());
	pDialog->GetDlgItem(4)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Credits_ProjectLeader").c_str());

	pDialog->GetDlgItem(5)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Credits_Programmer").c_str());

	pDialog->GetDlgItem(7)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Credits_Tester").c_str());
	pDialog->GetDlgItem(9)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Credits_Tester").c_str());

	//pDumpResultsDialogData = (CDumpResultsDialogData*)lParam;
	//SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pDumpResultsDialogData);
	break;
	case WM_COMMAND:
	//pDumpResultsDialogData = (CDumpResultsDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 1: // close button
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
void				PopupGUIManager::showCreditsDialog(void)
{
	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_CREDITSDIALOG), getParentWindowHwnd(), DialogProc_CreditsDialog, 0);
}




// renamer dialog

CRenamerDialogData::CRenamerDialogData(void) :
	m_bRename(false),
	m_bMatchingState_IDE(false),
	m_bMatchingState_IPL(false),
	m_bMatchingState_COL(false),
	m_bUpdateLODNamesToMatch(false)
{
}

INT_PTR CALLBACK DialogProc_RenamerDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CRenamerDialogData *pRenamerDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	pRenamerDialogData = (CRenamerDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pRenamerDialogData);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "Renamer");

	pDialog->GetDlgItem(157)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_ChooseFolder").c_str());
	pDialog->GetDlgItem(158)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_ChooseFolder").c_str());
	pDialog->GetDlgItem(159)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_ChooseFolder").c_str());

	pDialog->GetDlgItem(201)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_Front").c_str());
	pDialog->GetDlgItem(301)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_Front").c_str());

	pDialog->GetDlgItem(202)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_End").c_str());
	pDialog->GetDlgItem(302)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_End").c_str());

	pDialog->GetDlgItem(203)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_AtPosition").c_str());
	pDialog->GetDlgItem(303)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_AtPosition").c_str());

	pDialog->GetDlgItem(207)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_Position").c_str());
	pDialog->GetDlgItem(307)->SetWindowTextW(LocalizationManager::get()->getTranslatedTextW("Window_Renamer_Position").c_str());

	((Button*)pDialog->GetDlgItem(101))->SetCheck(BST_CHECKED);
	((Button*)pDialog->GetDlgItem(251))->SetCheck(BST_CHECKED);
	((Button*)pDialog->GetDlgItem(351))->SetCheck(BST_CHECKED);
	break;
	case WM_COMMAND:
	pRenamerDialogData = (CRenamerDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 401: // cancel button
	pRenamerDialogData->m_bRename = false;
	EndDialog(hwndDlg, 0);
	break;
	case 400: // rename button
	{
	pRenamerDialogData->m_bRename = true;

	CString cstrStrIDEFolder, cstrStrIPLFolder, cstrStrCOLFolder;
	((CEdit*)pDialog->GetDlgItem(154))->GetWindowText(cstrStrIDEFolder);
	((CEdit*)pDialog->GetDlgItem(155))->GetWindowText(cstrStrIPLFolder);
	((CEdit*)pDialog->GetDlgItem(156))->GetWindowText(cstrStrCOLFolder);
	pRenamerDialogData->m_strMatchingPath_IDE = String::convertCStringToStdString(cstrStrIDEFolder);
	pRenamerDialogData->m_strMatchingPath_IPL = String::convertCStringToStdString(cstrStrIPLFolder);
	pRenamerDialogData->m_strMatchingPath_COL = String::convertCStringToStdString(cstrStrCOLFolder);

	if (((Button*)pDialog->GetDlgItem(101))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucEntriesType = 0;
	}
	else if (((Button*)pDialog->GetDlgItem(102))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucEntriesType = 1;
	}

	if (((Button*)pDialog->GetDlgItem(151))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_bMatchingState_IDE = true;
	if (pRenamerDialogData->m_strMatchingPath_IDE == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_6"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	}
	if (((Button*)pDialog->GetDlgItem(152))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_bMatchingState_IPL = true;
	if (pRenamerDialogData->m_strMatchingPath_IPL == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_7"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	}
	if (((Button*)pDialog->GetDlgItem(153))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_bMatchingState_COL = true;
	if (pRenamerDialogData->m_strMatchingPath_COL == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_8"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	}

	CString cstrStr1, cstrStr2, cstrStr3;
	((CEdit*)pDialog->GetDlgItem(204))->GetWindowText(cstrStr1);
	((CEdit*)pDialog->GetDlgItem(205))->GetWindowText(cstrStr2);
	((CEdit*)pDialog->GetDlgItem(206))->GetWindowText(cstrStr3);
	pRenamerDialogData->m_strCharAdding_Front = String::convertCStringToStdString(cstrStr1);
	pRenamerDialogData->m_strCharAdding_End = String::convertCStringToStdString(cstrStr2);
	pRenamerDialogData->m_strCharAdding_AtPosition = String::convertCStringToStdString(cstrStr3);

	if (pRenamerDialogData->m_strCharAdding_AtPosition != "")
	{
	CString cstrStr4;
	((CEdit*)pDialog->GetDlgItem(208))->GetWindowText(cstrStr4);
	string strStr4 = String::convertCStringToStdString(cstrStr4);

	if (strStr4 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_9"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	pRenamerDialogData->m_uiCharAddingAtPosition_Position = String::toNumber(strStr4);
	}

	if (((Button*)pDialog->GetDlgItem(251))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucCharReplacementType = 0;
	}
	else if (((Button*)pDialog->GetDlgItem(252))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucCharReplacementType = 1;
	}
	else if (((Button*)pDialog->GetDlgItem(253))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucCharReplacementType = 2;
	}

	if (pRenamerDialogData->m_ucCharReplacementType == 2) // only replace if length exceeds
	{
	CString cstrStr5;
	((CEdit*)pDialog->GetDlgItem(254))->GetWindowText(cstrStr5);
	string strStr5 = String::convertCStringToStdString(cstrStr5);

	if (strStr5 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_10"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	pRenamerDialogData->m_uiCharReplaceConditional_Length = String::toNumber(strStr5);
	}
	CString cstrStr6, cstrStr7, cstrStr8;
	((CEdit*)pDialog->GetDlgItem(304))->GetWindowText(cstrStr6);
	((CEdit*)pDialog->GetDlgItem(305))->GetWindowText(cstrStr7);
	((CEdit*)pDialog->GetDlgItem(306))->GetWindowText(cstrStr8);
	string strStr6_2 = String::convertCStringToStdString(cstrStr6);
	string strStr7_2 = String::convertCStringToStdString(cstrStr7);
	string strStr8 = String::convertCStringToStdString(cstrStr8);
	if (strStr6_2 == "")
	{
	pRenamerDialogData->m_uiCharRemoving_Front = 0;
	}
	else
	{
	pRenamerDialogData->m_uiCharRemoving_Front = String::toNumber(strStr6_2);
	}
	if (strStr7_2 == "")
	{
	pRenamerDialogData->m_uiCharRemoving_End = 0;
	}
	else
	{
	pRenamerDialogData->m_uiCharRemoving_End = String::toNumber(strStr7_2);
	}
	if (strStr8 == "")
	{
	pRenamerDialogData->m_uiCharRemoving_AtPosition = 0;
	}
	else
	{
	pRenamerDialogData->m_uiCharRemoving_AtPosition = String::toNumber(strStr8);
	}
	if (strStr8 != "")
	{
	CString cstrStr9;
	((CEdit*)pDialog->GetDlgItem(308))->GetWindowText(cstrStr9);
	string strStr9 = String::convertCStringToStdString(cstrStr9);

	if (strStr9 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_11"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	pRenamerDialogData->m_uiCharRemovingAtPosition_Position = String::toNumber(strStr9);
	}

	if (((Button*)pDialog->GetDlgItem(351))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucCharCaseType = 0;
	}
	else if (((Button*)pDialog->GetDlgItem(352))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucCharCaseType = 1;
	}
	else if (((Button*)pDialog->GetDlgItem(353))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucCharCaseType = 2;
	}
	else if (((Button*)pDialog->GetDlgItem(354))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_ucCharCaseType = 3;
	}

	if (((Button*)pDialog->GetDlgItem(451))->GetCheck() == BST_CHECKED)
	{
	pRenamerDialogData->m_bUpdateLODNamesToMatch = true;
	}

	EndDialog(hwndDlg, 0);

	break;
	}
	case 157: // matching IDE - folder path
	pRenamerDialogData->m_strMatchingPath_IDE = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_5"), getIMGF()->getLastUsedDirectory("RENAMER__MATCHING_IDE"));
	if (pRenamerDialogData->m_strMatchingPath_IDE == "")
	{
	break;
	}
	pRenamerDialogData->m_strMatchingPath_IDE = Path::addSlashToEnd(pRenamerDialogData->m_strMatchingPath_IDE);
	getIMGF()->setLastUsedDirectory("RENAMER__MATCHING_IDE", pRenamerDialogData->m_strMatchingPath_IDE);
	((CEdit*)pDialog->GetDlgItem(154))->SetWindowTextW(String::convertStdStringToStdWString(pRenamerDialogData->m_strMatchingPath_IDE).c_str());
	break;
	case 158: // matching IPL - folder path
	pRenamerDialogData->m_strMatchingPath_IPL = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_6"), getIMGF()->getLastUsedDirectory("RENAMER__MATCHING_IPL"));
	if (pRenamerDialogData->m_strMatchingPath_IPL == "")
	{
	break;
	}
	pRenamerDialogData->m_strMatchingPath_IPL = Path::addSlashToEnd(pRenamerDialogData->m_strMatchingPath_IPL);
	getIMGF()->setLastUsedDirectory("RENAMER__MATCHING_IPL", pRenamerDialogData->m_strMatchingPath_IPL);
	((CEdit*)pDialog->GetDlgItem(155))->SetWindowTextW(String::convertStdStringToStdWString(pRenamerDialogData->m_strMatchingPath_IPL).c_str());
	break;
	case 159: // matching COL - folder path
	pRenamerDialogData->m_strMatchingPath_COL = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_7"), getIMGF()->getLastUsedDirectory("RENAMER__MATCHING_COL"));
	if (pRenamerDialogData->m_strMatchingPath_COL == "")
	{
	break;
	}
	pRenamerDialogData->m_strMatchingPath_COL = Path::addSlashToEnd(pRenamerDialogData->m_strMatchingPath_COL);
	getIMGF()->setLastUsedDirectory("RENAMER__MATCHING_COL", pRenamerDialogData->m_strMatchingPath_COL);
	((CEdit*)pDialog->GetDlgItem(156))->SetWindowTextW(String::convertStdStringToStdWString(pRenamerDialogData->m_strMatchingPath_COL).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
CRenamerDialogData*	PopupGUIManager::showRenamerDialog(void)
{
	CRenamerDialogData *pRenamerDialogData = new CRenamerDialogData;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_RENAMERDIALOG), getParentWindowHwnd(), DialogProc_RenamerDialog, (DWORD) pRenamerDialogData);

	return pRenamerDialogData;
}




// DFF conversion dialog
INT_PTR CALLBACK DialogProc_DFFConversionDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	DFFConversionDialogData *pConversionDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	HWND hWnd;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	hWnd = pDialog->GetDlgItem(0)->GetSafeHwnd();
	SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 1);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "DFFConversion");

	pConversionDialogData = (DFFConversionDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pConversionDialogData);

	((Button*)pDialog->GetDlgItem(101))->SetCheck(BST_CHECKED);

	break;
	case WM_COMMAND:
	pConversionDialogData = (DFFConversionDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 201: // close button
	EndDialog(hwndDlg, 0);
	break;
	case 200: // convert button
	pConversionDialogData->m_bConvert = true;

	uint32 uiAdjustType = 0;
	if (((Button*)pDialog->GetDlgItem(101))->GetCheck() == BST_CHECKED)
	{
	pConversionDialogData->m_ucPrelightningOption = 0;
	}
	else if (((Button*)pDialog->GetDlgItem(102))->GetCheck() == BST_CHECKED)
	{
	pConversionDialogData->m_ucPrelightningOption = 1;
	}
	else if (((Button*)pDialog->GetDlgItem(103))->GetCheck() == BST_CHECKED)
	{
	pConversionDialogData->m_ucPrelightningOption = 2;
	uiAdjustType = 1;
	}
	else if (((Button*)pDialog->GetDlgItem(104))->GetCheck() == BST_CHECKED)
	{
	pConversionDialogData->m_ucPrelightningOption = 2;
	uiAdjustType = 2;
	}

	if (pConversionDialogData->m_ucPrelightningOption == 2) // adjust prelightning
	{
	if (uiAdjustType == 1)
	{
	pConversionDialogData->m_ucAdjustPrelightningOption = 0;
	}
	else if (uiAdjustType == 2)
	{
	pConversionDialogData->m_ucAdjustPrelightningOption = 1;
	}

	CString cstrStr1, cstrStr2, cstrStr3, cstrStr4;
	string strStr1, strStr2, strStr3, strStr4;
	((CEdit*)pDialog->GetDlgItem(156))->GetWindowText(cstrStr1);
	((CEdit*)pDialog->GetDlgItem(157))->GetWindowText(cstrStr2);
	((CEdit*)pDialog->GetDlgItem(158))->GetWindowText(cstrStr3);
	((CEdit*)pDialog->GetDlgItem(159))->GetWindowText(cstrStr4);
	strStr1 = String::convertCStringToStdString(cstrStr1);
	strStr2 = String::convertCStringToStdString(cstrStr2);
	strStr3 = String::convertCStringToStdString(cstrStr3);
	strStr4 = String::convertCStringToStdString(cstrStr4);
	if (pConversionDialogData->m_ucAdjustPrelightningOption == 0)
	{
	if (strStr1 == "" || strStr2 == "" || strStr3 == "" || strStr4 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_12"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	}
	else if (pConversionDialogData->m_ucAdjustPrelightningOption == 1)
	{
	if (strStr1 == "" || strStr2 == "" || strStr3 == "" || strStr4 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_13"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	}

	pConversionDialogData->m_ssAdjustColourValues[0] = String::toNumber(strStr1);
	pConversionDialogData->m_ssAdjustColourValues[1] = String::toNumber(strStr2);
	pConversionDialogData->m_ssAdjustColourValues[2] = String::toNumber(strStr3);
	pConversionDialogData->m_ssAdjustColourValues[3] = String::toNumber(strStr4);
	}

	EndDialog(hwndDlg, 0);

	break;
	}
	break;
	case WM_CLOSE:
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
DFFConversionDialogData*	PopupGUIManager::showDFFConversionDialog(void)
{
	DFFConversionDialogData *pConversionDialogData = new DFFConversionDialogData;
	pConversionDialogData->m_bConvert = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DFFCONVERSIONDIALOG), getParentWindowHwnd(), DialogProc_DFFConversionDialog, (DWORD) pConversionDialogData);

	return pConversionDialogData;
}




// duplicate entries dialog
INT_PTR CALLBACK DialogProc_DuplicateEntriesDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CDuplicateEntriesDialogData *pDuplicateEntriesDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pDuplicateEntriesDialogData = (CDuplicateEntriesDialogData*)lParam;

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "DuplicateEntries");

	pDialog->GetDlgItem(204)->SetWindowTextW((L"- " + LocalizationManager::get()->getTranslatedTextW("Window_Dump_GameFolderPath")).c_str());

	((Button*)pDialog->GetDlgItem(150))->SetCheck(BST_CHECKED);

	((CComboBox*)pDialog->GetDlgItem(201))->InsertString(0, LocalizationManager::get()->getTranslatedTextW("Game_III").c_str());
	((CComboBox*)pDialog->GetDlgItem(201))->InsertString(1, LocalizationManager::get()->getTranslatedTextW("Game_VC").c_str());
	((CComboBox*)pDialog->GetDlgItem(201))->InsertString(2, LocalizationManager::get()->getTranslatedTextW("Game_SA").c_str());
	((CComboBox*)pDialog->GetDlgItem(201))->InsertString(3, LocalizationManager::get()->getTranslatedTextW("Game_SOL").c_str());
	((CComboBox*)pDialog->GetDlgItem(201))->InsertString(4, LocalizationManager::get()->getTranslatedTextW("Other").c_str());
	((CComboBox*)pDialog->GetDlgItem(201))->SetCurSel(0);

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pDuplicateEntriesDialogData);
	break;
	case WM_COMMAND:
	pDuplicateEntriesDialogData = (CDuplicateEntriesDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 251: // cancel
	pDuplicateEntriesDialogData->m_bCheck = false;
	EndDialog(hwndDlg, 0);
	break;
	case 250: // check
	pDuplicateEntriesDialogData->m_bCheck = true;

	if (((Button*)pDialog->GetDlgItem(150))->GetCheck() == BST_CHECKED)
	{
	pDuplicateEntriesDialogData->m_ucEntriesType = 0;
	}
	else if (((Button*)pDialog->GetDlgItem(151))->GetCheck() == BST_CHECKED)
	{
	pDuplicateEntriesDialogData->m_ucEntriesType = 1;
	}
	else if (((Button*)pDialog->GetDlgItem(152))->GetCheck() == BST_CHECKED)
	{
	pDuplicateEntriesDialogData->m_ucEntriesType = 2;
	}
	else if (((Button*)pDialog->GetDlgItem(153))->GetCheck() == BST_CHECKED)
	{
	pDuplicateEntriesDialogData->m_ucEntriesType = 3;
	}

	if (pDuplicateEntriesDialogData->m_ucEntriesType == 3) // DAT file
	{
	pDuplicateEntriesDialogData->m_uiDATGameIndex = ((CComboBox*)pDialog->GetDlgItem(201))->GetCurSel();

	if (pDuplicateEntriesDialogData->m_uiDATGameIndex == 4 && pDuplicateEntriesDialogData->m_strDATPath == "") // 4 is Other
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_14"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	if (pDuplicateEntriesDialogData->m_strDATGameDirectoryPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_15"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	}

	EndDialog(hwndDlg, 0);
	break;
	case 203: // Change button for DAT file path
	vecFilePaths = Input::openFile(getIMGF()->getLastUsedDirectory("DUPLICATEENTRIES__DAT"), "DAT", false);
	if (vecFilePaths.size() == 0)
	{
	break;
	}
	pDuplicateEntriesDialogData->m_strDATPath = vecFilePaths[0];
	getIMGF()->setLastUsedDirectory("DUPLICATEENTRIES__DAT", pDuplicateEntriesDialogData->m_strDATPath);
	((CEdit*)pDialog->GetDlgItem(202))->SetWindowTextW(String::convertStdStringToStdWString(pDuplicateEntriesDialogData->m_strDATPath).c_str());
	break;
	case 206: // Change button for Game folder path
	pDuplicateEntriesDialogData->m_strDATGameDirectoryPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("DUPLICATEENTRIES__GAME"));
	if (pDuplicateEntriesDialogData->m_strDATGameDirectoryPath == "")
	{
	break;
	}
	pDuplicateEntriesDialogData->m_strDATGameDirectoryPath = Path::addSlashToEnd(pDuplicateEntriesDialogData->m_strDATGameDirectoryPath);
	getIMGF()->setLastUsedDirectory("DUPLICATEENTRIES__GAME", pDuplicateEntriesDialogData->m_strDATGameDirectoryPath);
	((CEdit*)pDialog->GetDlgItem(205))->SetWindowTextW(String::convertStdStringToStdWString(pDuplicateEntriesDialogData->m_strDATGameDirectoryPath).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	pDuplicateEntriesDialogData = (CDuplicateEntriesDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pDuplicateEntriesDialogData->m_bCheck = false;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
CDuplicateEntriesDialogData*		PopupGUIManager::showDuplicateEntriesDialog(void)
{
	CDuplicateEntriesDialogData *pDuplicateEntriesDialogData = new CDuplicateEntriesDialogData;
	pDuplicateEntriesDialogData->m_ucEntriesType = 0;
	pDuplicateEntriesDialogData->m_uiDATGameIndex = 0;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DUPLICATEENTRIESDIALOG), getParentWindowHwnd(), DialogProc_DuplicateEntriesDialog, (DWORD) pDuplicateEntriesDialogData);

	return pDuplicateEntriesDialogData;
}




// build txd dialog
INT_PTR CALLBACK DialogProc_BuildTXDDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CBuildTXDDialogData *pBuildTXDDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
	pBuildTXDDialogData = (CBuildTXDDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pBuildTXDDialogData);

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "BuildTXD");

	((Button*)pDialog->GetDlgItem(101))->SetCheck(BST_CHECKED);

	uint32 uiOptionIndex = 0;
	for (auto pRWVersion : RWManager::get()->getVersionManager()->getEntries())
	{
	((CComboBox*)pDialog->GetDlgItem(203))->InsertString(uiOptionIndex, String::convertStdStringToStdWString(pRWVersion->getVersionText() + " (" + LocalizationManager::get()->getTranslatedText(pRWVersion->getLocalizationKey()) + ")").c_str());
	uiOptionIndex++;
	}
	((CComboBox*)pDialog->GetDlgItem(203))->SetCurSel(7);

	((CComboBox*)pDialog->GetDlgItem(201))->SetWindowText(LocalizationManager::get()->getTranslatedTextW("Digit0").c_str());

	break;
	}
	case WM_COMMAND:
	pBuildTXDDialogData = (CBuildTXDDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 151: // cancel
	pBuildTXDDialogData->m_bBuild = false;
	EndDialog(hwndDlg, 0);
	break;
	case 150: // check
	{
	pBuildTXDDialogData->m_bBuild = true;

	CString cstr1, cstr2, cstr3, cstr4;
	((CEdit*)pDialog->GetDlgItem(251))->GetWindowText(cstr1);
	((CEdit*)pDialog->GetDlgItem(255))->GetWindowText(cstr2);
	((CEdit*)pDialog->GetDlgItem(110))->GetWindowText(cstr3);
	pBuildTXDDialogData->m_strTexturesFolderPath = Path::addSlashToEnd(String::convertCStringToStdString(cstr1));
	pBuildTXDDialogData->m_strDestinationFolderPath = Path::addSlashToEnd(String::convertCStringToStdString(cstr2));
	pBuildTXDDialogData->m_strIDEFilePath = String::convertCStringToStdString(cstr3);

	if (((Button*)pDialog->GetDlgItem(101))->GetCheck() == BST_CHECKED)
	{
	pBuildTXDDialogData->m_uDFFFormatsType = 0;
	}
	else if (((Button*)pDialog->GetDlgItem(102))->GetCheck() == BST_CHECKED)
	{
	pBuildTXDDialogData->m_uDFFFormatsType = 1;
	}
	else if (((Button*)pDialog->GetDlgItem(103))->GetCheck() == BST_CHECKED)
	{
	pBuildTXDDialogData->m_uDFFFormatsType = 2;
	}
	else if (((Button*)pDialog->GetDlgItem(104))->GetCheck() == BST_CHECKED)
	{
	pBuildTXDDialogData->m_uDFFFormatsType = 3;
	}
	else if (((Button*)pDialog->GetDlgItem(108))->GetCheck() == BST_CHECKED)
	{
	pBuildTXDDialogData->m_uDFFFormatsType = 4;
	}

	if (pBuildTXDDialogData->m_uDFFFormatsType == 3)
	{
	((CEdit*)pDialog->GetDlgItem(106))->GetWindowText(cstr4);
	pBuildTXDDialogData->m_strDFFsFolderPath = Path::addSlashToEnd(String::convertCStringToStdString(cstr4));
	}
	else if (pBuildTXDDialogData->m_uDFFFormatsType == 4)
	{
	((CEdit*)pDialog->GetDlgItem(113))->GetWindowText(cstr4);
	pBuildTXDDialogData->m_strDFFsFolderPath = Path::addSlashToEnd(String::convertCStringToStdString(cstr4));
	}

	if (pBuildTXDDialogData->m_uDFFFormatsType == 3) // Folder containg DFF files
	{
	if (pBuildTXDDialogData->m_strDFFsFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_16"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	}
	else if (pBuildTXDDialogData->m_uDFFFormatsType == 4) // IDE file referencing DFF files
	{
	if (pBuildTXDDialogData->m_strIDEFilePath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_17"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}

	if (pBuildTXDDialogData->m_strDFFsFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_18"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	}

	if (pBuildTXDDialogData->m_strTexturesFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_19"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}

	if (pBuildTXDDialogData->m_strDestinationFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_20"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}

	CString cstr5;
	((CEdit*)pDialog->GetDlgItem(201))->GetWindowText(cstr5);
	string str5 = String::convertCStringToStdString(cstr5);
	pBuildTXDDialogData->m_uiTextureCountPerTXD = str5 == "" ? 0 : String::toNumber(str5);
	pBuildTXDDialogData->m_pRWVersion = RWManager::get()->getVersionManager()->getEntryByIndex(((CComboBox*)pDialog->GetDlgItem(203))->GetCurSel());

	EndDialog(hwndDlg, 0);
	break;
	}
	case 107: // Change button for DFFs folder path
	case 114:
	pBuildTXDDialogData->m_strDFFsFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_8"), getIMGF()->getLastUsedDirectory("BUILDTXD__DFF"));
	if (pBuildTXDDialogData->m_strDFFsFolderPath == "")
	{
	break;
	}
	pBuildTXDDialogData->m_strDFFsFolderPath = Path::addSlashToEnd(pBuildTXDDialogData->m_strDFFsFolderPath);
	getIMGF()->setLastUsedDirectory("BUILDTXD__DFF", pBuildTXDDialogData->m_strDFFsFolderPath);
	((CEdit*)pDialog->GetDlgItem(106))->SetWindowTextW(String::convertStdStringToStdWString(pBuildTXDDialogData->m_strDFFsFolderPath).c_str());
	((CEdit*)pDialog->GetDlgItem(113))->SetWindowTextW(String::convertStdStringToStdWString(pBuildTXDDialogData->m_strDFFsFolderPath).c_str());
	break;
	case 111: // Change button for IDE file path
	vecFilePaths = Input::openFile(getIMGF()->getLastUsedDirectory("BUILDTXD__IDE"), "IDE", false);
	if (vecFilePaths.size() == 0)
	{
	break;
	}
	pBuildTXDDialogData->m_strIDEFilePath = vecFilePaths[0];
	getIMGF()->setLastUsedDirectory("BUILDTXD__IDE", pBuildTXDDialogData->m_strIDEFilePath);
	((CEdit*)pDialog->GetDlgItem(110))->SetWindowTextW(String::convertStdStringToStdWString(pBuildTXDDialogData->m_strIDEFilePath).c_str());
	break;
	case 253: // Change button for textures folder path
	pBuildTXDDialogData->m_strTexturesFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_9"), getIMGF()->getLastUsedDirectory("BUILDTXD__TEXTURES"));
	if (pBuildTXDDialogData->m_strTexturesFolderPath == "")
	{
	break;
	}
	getIMGF()->setLastUsedDirectory("BUILDTXD__TEXTURES", pBuildTXDDialogData->m_strTexturesFolderPath);
	((CEdit*)pDialog->GetDlgItem(251))->SetWindowTextW(String::convertStdStringToStdWString(pBuildTXDDialogData->m_strTexturesFolderPath).c_str());
	break;
	case 256: // Change button for destination folder path
	pBuildTXDDialogData->m_strDestinationFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_10"), getIMGF()->getLastUsedDirectory("BUILDTXD__DESTINATION"));
	if (pBuildTXDDialogData->m_strDestinationFolderPath == "")
	{
	break;
	}
	getIMGF()->setLastUsedDirectory("BUILDTXD__DESTINATION", pBuildTXDDialogData->m_strDestinationFolderPath);
	((CEdit*)pDialog->GetDlgItem(255))->SetWindowTextW(String::convertStdStringToStdWString(pBuildTXDDialogData->m_strDestinationFolderPath).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	pBuildTXDDialogData = (CBuildTXDDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pBuildTXDDialogData->m_bBuild = false;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
CBuildTXDDialogData*		PopupGUIManager::showBuildTXDDialog(void)
{
	CBuildTXDDialogData *pBuildTXDDialogData = new CBuildTXDDialogData;
	pBuildTXDDialogData->m_uDFFFormatsType = 0;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_BUILDTXDDIALOG), getParentWindowHwnd(), DialogProc_BuildTXDDialog, (DWORD) pBuildTXDDialogData);

	return pBuildTXDDialogData;
}




// IMG Version Settings dialog
INT_PTR CALLBACK DialogProc_IMGVersionSettingsDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	IMGVersionSettingsDialogData *pIMGVersionSettingsDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pIMGVersionSettingsDialogData = (IMGVersionSettingsDialogData*)lParam;

	getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "IMGVersionSettings");

	((Button*)pDialog->GetDlgItem(152))->SetCheck(BST_CHECKED);

	((CComboBox*)pDialog->GetDlgItem(155))->InsertString(0, LocalizationManager::get()->getTranslatedTextW("CompressionType_None").c_str());
	((CComboBox*)pDialog->GetDlgItem(155))->InsertString(1, LocalizationManager::get()->getTranslatedTextW("CompressionType_ZLib").c_str());
	((CComboBox*)pDialog->GetDlgItem(155))->InsertString(2, LocalizationManager::get()->getTranslatedTextW("CompressionType_LZ4").c_str());
	((CComboBox*)pDialog->GetDlgItem(155))->SetCurSel(0);

	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(0, L"Compression Level Not Applicable");
	((CComboBox*)pDialog->GetDlgItem(156))->SetCurSel(0);

	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pIMGVersionSettingsDialogData);
	break;
	case WM_COMMAND:
	pIMGVersionSettingsDialogData = (IMGVersionSettingsDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (LOWORD(wParam))
	{
	case 155: // compression type dropdown
	{
	int iCompressionType = ((CComboBox*)pDialog->GetDlgItem(155))->GetCurSel();
	((CComboBox*)pDialog->GetDlgItem(156))->ResetContent();
	if (iCompressionType == 0)
	{
	// Not Compressed
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(0, L"Compression Level Not Applicable");
	((CComboBox*)pDialog->GetDlgItem(156))->SetCurSel(0);
	}
	else if (iCompressionType == 1)
	{
	// ZLib
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(0, L"Default Compression Level - Level 6");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(1, L"Compression Not Applied");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(2, L"Level 1 - Fastest Time");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(3, L"Level 2 - Fast Time");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(4, L"Level 3");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(5, L"Level 4");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(6, L"Level 5");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(7, L"Level 6");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(8, L"Level 7");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(9, L"Level 8 - Small Size");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(10, L"Level 9 - Smallest Size");
	((CComboBox*)pDialog->GetDlgItem(156))->SetCurSel(0);
	}
	else if (iCompressionType == 2)
	{
	// LZ4
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(0, L"Level 1 - Fastest Time");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(1, L"Level 2 - Fast Time");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(2, L"Level 3");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(3, L"Level 4");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(4, L"Level 5");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(5, L"Level 6");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(6, L"Level 7");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(7, L"Level 8 - Small Size");
	((CComboBox*)pDialog->GetDlgItem(156))->InsertString(8, L"Level 9 - Smallest Size");
	((CComboBox*)pDialog->GetDlgItem(156))->SetCurSel(0);
	}
	break;
	}
	case 201: // cancel
	pIMGVersionSettingsDialogData->m_bSave = false;
	EndDialog(hwndDlg, 0);
	break;
	case 200: // check
	pIMGVersionSettingsDialogData->m_bSave = true;

	if (((Button*)pDialog->GetDlgItem(152))->GetCheck() == BST_CHECKED)
	{
	pIMGVersionSettingsDialogData->m_ucEntriesType = 0;
	}
	else if (((Button*)pDialog->GetDlgItem(153))->GetCheck() == BST_CHECKED)
	{
	pIMGVersionSettingsDialogData->m_ucEntriesType = 1;
	}

	int iCompressionType = ((CComboBox*)pDialog->GetDlgItem(155))->GetCurSel();
	switch (iCompressionType)
	{
	case 0:
	pIMGVersionSettingsDialogData->m_ECompressionAlgorithm = COMPRESSION_NONE;
	break;
	case 1:
	pIMGVersionSettingsDialogData->m_ECompressionAlgorithm = COMPRESSION_ZLIB;
	break;
	case 2:
	pIMGVersionSettingsDialogData->m_ECompressionAlgorithm = COMPRESSION_LZ4;
	break;
	}

	int iCompressionLevel = ((CComboBox*)pDialog->GetDlgItem(156))->GetCurSel();
	if (iCompressionType == 0)
	{
	pIMGVersionSettingsDialogData->m_uiCompressionLevel = 0;
	}
	else if (iCompressionType == 1)
	{
	pIMGVersionSettingsDialogData->m_uiCompressionLevel = iCompressionLevel - 2;
	}
	else if (iCompressionType == 2)
	{
	pIMGVersionSettingsDialogData->m_uiCompressionLevel = iCompressionLevel - 1;
	}

	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	pIMGVersionSettingsDialogData = (IMGVersionSettingsDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pIMGVersionSettingsDialogData->m_bSave = false;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
IMGVersionSettingsDialogData*		PopupGUIManager::showIMGVersionSettingsDialog(void)
{
	IMGVersionSettingsDialogData *pIMGVersionSettingsDialogData = new IMGVersionSettingsDialogData;
	pIMGVersionSettingsDialogData->m_bSave = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_IMGVERSIONSETTINGSDIALOG), getParentWindowHwnd(), DialogProc_IMGVersionSettingsDialog, (DWORD) pIMGVersionSettingsDialogData);

	return pIMGVersionSettingsDialogData;
}




// TXD Organizer dialog
INT_PTR CALLBACK DialogProc_TXDOrganizerDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	TXDOrganizerDialogData *pTXDOrganizerDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
	pTXDOrganizerDialogData = (TXDOrganizerDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pTXDOrganizerDialogData);

	uint32 i = 0;
	for (auto pRasterDataFormat : ImageManager::get()->getRasterDataFormatManager()->getEntries())
	{
	((CComboBox*)pDialog->GetDlgItem(114))->InsertString(i, LocalizationManager::get()->getTranslatedTextW(pRasterDataFormat->getLocalizationKey()).c_str());
	i++;
	}
	((CComboBox*)pDialog->GetDlgItem(114))->SetCurSel(0);
	break;
	}
	case WM_COMMAND:
	pTXDOrganizerDialogData = (TXDOrganizerDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 151: // cancel
	pTXDOrganizerDialogData->m_bOrganize = false;
	EndDialog(hwndDlg, 0);
	break;
	case 150: // organize
	{
	pTXDOrganizerDialogData->m_bOrganize = true;

	CString cstr1, cstr2, cstr3, cstr4, cstr5;
	((CEdit*)pDialog->GetDlgItem(101))->GetWindowText(cstr1);
	((CEdit*)pDialog->GetDlgItem(103))->GetWindowText(cstr2);
	((CEdit*)pDialog->GetDlgItem(105))->GetWindowText(cstr3);
	((CEdit*)pDialog->GetDlgItem(108))->GetWindowText(cstr4);
	((CEdit*)pDialog->GetDlgItem(111))->GetWindowText(cstr5);
	string strString1 = String::convertCStringToStdString(cstr1);
	pTXDOrganizerDialogData->m_uiEveryNDFFFiles = String::toNumber(strString1);
	pTXDOrganizerDialogData->m_strTXDNamePrefix = String::convertCStringToStdString(cstr2);
	pTXDOrganizerDialogData->m_strTextureImportFolderPath = String::convertCStringToStdString(cstr3);
	pTXDOrganizerDialogData->m_strIDEUpdateFolderPath = String::convertCStringToStdString(cstr4);
	pTXDOrganizerDialogData->m_strOutputFolderPath = String::convertCStringToStdString(cstr5);

	if (strString1 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_24"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}

	if (pTXDOrganizerDialogData->m_strTXDNamePrefix == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_25"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}

	if (pTXDOrganizerDialogData->m_strTextureImportFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_26"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}

	if (pTXDOrganizerDialogData->m_strOutputFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_28"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}

	if (((Button*)pDialog->GetDlgItem(107))->GetCheck() == BST_CHECKED)
	{
	pTXDOrganizerDialogData->m_bIDEUpdate = true;

	if (pTXDOrganizerDialogData->m_strIDEUpdateFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_30"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}
	}

	pTXDOrganizerDialogData->m_pRasterDataFormat = ImageManager::get()->getRasterDataFormatManager()->getEntryByIndex(((CComboBox*)pDialog->GetDlgItem(114))->GetCurSel());

	pTXDOrganizerDialogData->m_strTextureImportFolderPath = Path::addSlashToEnd(pTXDOrganizerDialogData->m_strTextureImportFolderPath);
	pTXDOrganizerDialogData->m_strIDEUpdateFolderPath = Path::addSlashToEnd(pTXDOrganizerDialogData->m_strIDEUpdateFolderPath);
	pTXDOrganizerDialogData->m_strOutputFolderPath = Path::addSlashToEnd(pTXDOrganizerDialogData->m_strOutputFolderPath);

	EndDialog(hwndDlg, 0);
	break;
	}
	case 106: // Change button for Texture Import Folder Path
	pTXDOrganizerDialogData->m_strTextureImportFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_18"), getIMGF()->getLastUsedDirectory("TXDORGANIZER_TEXTUREIMPORT"));
	if (pTXDOrganizerDialogData->m_strTextureImportFolderPath == "")
	{
	break;
	}
	pTXDOrganizerDialogData->m_strTextureImportFolderPath = Path::addSlashToEnd(pTXDOrganizerDialogData->m_strTextureImportFolderPath);
	getIMGF()->setLastUsedDirectory("TXDORGANIZER_TEXTUREIMPORT", pTXDOrganizerDialogData->m_strTextureImportFolderPath);
	((CEdit*)pDialog->GetDlgItem(105))->SetWindowTextW(String::convertStdStringToStdWString(pTXDOrganizerDialogData->m_strTextureImportFolderPath).c_str());
	break;
	case 109: // Change button for IDE Update Folder Path
	pTXDOrganizerDialogData->m_strIDEUpdateFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_19"), getIMGF()->getLastUsedDirectory("TXDORGANIZER_IDEUPDATE"));
	if (pTXDOrganizerDialogData->m_strIDEUpdateFolderPath == "")
	{
	break;
	}
	pTXDOrganizerDialogData->m_strIDEUpdateFolderPath = Path::addSlashToEnd(pTXDOrganizerDialogData->m_strIDEUpdateFolderPath);
	getIMGF()->setLastUsedDirectory("TXDORGANIZER_IDEUPDATE", pTXDOrganizerDialogData->m_strIDEUpdateFolderPath);
	((CEdit*)pDialog->GetDlgItem(108))->SetWindowTextW(String::convertStdStringToStdWString(pTXDOrganizerDialogData->m_strIDEUpdateFolderPath).c_str());
	break;
	case 112: // Change button for Output Folder
	pTXDOrganizerDialogData->m_strOutputFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_20"), getIMGF()->getLastUsedDirectory("TXDORGANIZER_OUTPUTFOLDER"));
	if (pTXDOrganizerDialogData->m_strOutputFolderPath == "")
	{
	break;
	}
	pTXDOrganizerDialogData->m_strOutputFolderPath = Path::addSlashToEnd(pTXDOrganizerDialogData->m_strOutputFolderPath);
	getIMGF()->setLastUsedDirectory("TXDORGANIZER_OUTPUTFOLDER", pTXDOrganizerDialogData->m_strOutputFolderPath);
	((CEdit*)pDialog->GetDlgItem(111))->SetWindowTextW(String::convertStdStringToStdWString(pTXDOrganizerDialogData->m_strOutputFolderPath).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	pTXDOrganizerDialogData = (TXDOrganizerDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pTXDOrganizerDialogData->m_bOrganize = false;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
TXDOrganizerDialogData*			PopupGUIManager::showTXDOrganizerDialog(void)
{
	TXDOrganizerDialogData *pTXDOrganizerDialogData = new TXDOrganizerDialogData;
	pTXDOrganizerDialogData->m_bOrganize = false;
	pTXDOrganizerDialogData->m_bIDEUpdate = false;
	pTXDOrganizerDialogData->m_pRasterDataFormat = nullptr;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_TXDORGANIZERDIALOG), getParentWindowHwnd(), DialogProc_TXDOrganizerDialog, (DWORD) pTXDOrganizerDialogData);

	return pTXDOrganizerDialogData;
}




// DAT Paths Mover dialog
INT_PTR CALLBACK DialogProc_DATPathsMoverDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	DATPathsMoverDialogData *pDATPathsMoverDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
	pDATPathsMoverDialogData = (DATPathsMoverDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pDATPathsMoverDialogData);

	((CComboBox*)pDialog->GetDlgItem(204))->SetWindowTextW(L"0.0");
	((CComboBox*)pDialog->GetDlgItem(205))->SetWindowTextW(L"0.0");
	((CComboBox*)pDialog->GetDlgItem(206))->SetWindowTextW(L"0.0");




	((CComboBox*)pDialog->GetDlgItem(105))->SetWindowTextW(L"-12000");
	((CComboBox*)pDialog->GetDlgItem(106))->SetWindowTextW(L"-12000");
	((CComboBox*)pDialog->GetDlgItem(107))->SetWindowTextW(L"12000");
	((CComboBox*)pDialog->GetDlgItem(108))->SetWindowTextW(L"12000");

	((CComboBox*)pDialog->GetDlgItem(153))->SetWindowTextW(L"750");
	((CComboBox*)pDialog->GetDlgItem(154))->SetWindowTextW(L"750");

	((CComboBox*)pDialog->GetDlgItem(204))->SetWindowTextW(L"7500");
	((CComboBox*)pDialog->GetDlgItem(205))->SetWindowTextW(L"-7500");
	((CComboBox*)pDialog->GetDlgItem(206))->SetWindowTextW(L"0.0");
	break;
	}
	case WM_COMMAND:
	pDATPathsMoverDialogData = (DATPathsMoverDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 351: // cancel
	pDATPathsMoverDialogData->m_bMove = false;
	EndDialog(hwndDlg, 0);
	break;
	case 350: // move
	{
	pDATPathsMoverDialogData->m_bMove = true;

	CString cstr1, cstr2, cstr3, cstr4, cstr5, cstr6, cstr7, cstr8, cstr9, cstr10, cstr11;
	((CEdit*)pDialog->GetDlgItem(105))->GetWindowText(cstr1);
	((CEdit*)pDialog->GetDlgItem(106))->GetWindowText(cstr2);
	((CEdit*)pDialog->GetDlgItem(107))->GetWindowText(cstr3);
	((CEdit*)pDialog->GetDlgItem(108))->GetWindowText(cstr4);
	((CEdit*)pDialog->GetDlgItem(153))->GetWindowText(cstr5);
	((CEdit*)pDialog->GetDlgItem(154))->GetWindowText(cstr6);
	((CEdit*)pDialog->GetDlgItem(204))->GetWindowText(cstr7);
	((CEdit*)pDialog->GetDlgItem(205))->GetWindowText(cstr8);
	((CEdit*)pDialog->GetDlgItem(206))->GetWindowText(cstr9);
	((CEdit*)pDialog->GetDlgItem(251))->GetWindowText(cstr10);
	((CEdit*)pDialog->GetDlgItem(301))->GetWindowText(cstr11);
	string str1, str2, str3, str4, str5, str6, str7, str8, str9, str10, str11;
	str1 = String::convertCStringToStdString(cstr1);
	str2 = String::convertCStringToStdString(cstr2);
	str3 = String::convertCStringToStdString(cstr3);
	str4 = String::convertCStringToStdString(cstr4);
	str5 = String::convertCStringToStdString(cstr5);
	str6 = String::convertCStringToStdString(cstr6);
	str7 = String::convertCStringToStdString(cstr7);
	str8 = String::convertCStringToStdString(cstr8);
	str9 = String::convertCStringToStdString(cstr9);
	str10 = String::convertCStringToStdString(cstr10);
	str11 = String::convertCStringToStdString(cstr11);

	pDATPathsMoverDialogData->m_strInputFolderPath = String::convertCStringToStdString(cstr10);
	pDATPathsMoverDialogData->m_strOutputFolderPath = String::convertCStringToStdString(cstr11);

	if (str1 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_31", "min", "x"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str2 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_31", "min", "y"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str3 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_31", "max", "x"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str4 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_31", "max", "y"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}

	if (str5 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_35", "width"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str6 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_35", "height"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}

	if (str7 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_57", "x"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str8 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_57", "y"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str9 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_57", "z"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}

	if (pDATPathsMoverDialogData->m_strInputFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_58"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}

	if (pDATPathsMoverDialogData->m_strOutputFolderPath == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_59"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_PathNotSet").c_str());
	break;
	}

	pDATPathsMoverDialogData->m_vecOutputMapRangeMin.x = String::toFloat32(String::convertCStringToStdString(cstr1));
	pDATPathsMoverDialogData->m_vecOutputMapRangeMin.y = String::toFloat32(String::convertCStringToStdString(cstr2));
	pDATPathsMoverDialogData->m_vecOutputMapRangeMax.x = String::toFloat32(String::convertCStringToStdString(cstr3));
	pDATPathsMoverDialogData->m_vecOutputMapRangeMax.y = String::toFloat32(String::convertCStringToStdString(cstr4));

	pDATPathsMoverDialogData->m_vecOutputTileSize.x = String::toFloat32(String::convertCStringToStdString(cstr5));
	pDATPathsMoverDialogData->m_vecOutputTileSize.y = String::toFloat32(String::convertCStringToStdString(cstr6));

	pDATPathsMoverDialogData->m_vecPositionOffset.x = String::toFloat32(String::convertCStringToStdString(cstr7));
	pDATPathsMoverDialogData->m_vecPositionOffset.y = String::toFloat32(String::convertCStringToStdString(cstr8));
	pDATPathsMoverDialogData->m_vecPositionOffset.z = String::toFloat32(String::convertCStringToStdString(cstr9));

	pDATPathsMoverDialogData->m_strInputFolderPath = Path::addSlashToEnd(pDATPathsMoverDialogData->m_strInputFolderPath);
	pDATPathsMoverDialogData->m_strOutputFolderPath = Path::addSlashToEnd(pDATPathsMoverDialogData->m_strOutputFolderPath);

	EndDialog(hwndDlg, 0);
	break;
	}
	case 252: // Change button for Input Folder
	pDATPathsMoverDialogData->m_strInputFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_21"), getIMGF()->getLastUsedDirectory("DATPATHSMOVER_DATINPUT"));
	if (pDATPathsMoverDialogData->m_strInputFolderPath == "")
	{
	break;
	}
	pDATPathsMoverDialogData->m_strInputFolderPath = Path::addSlashToEnd(pDATPathsMoverDialogData->m_strInputFolderPath);
	getIMGF()->setLastUsedDirectory("DATPATHSMOVER_DATINPUT", pDATPathsMoverDialogData->m_strInputFolderPath);
	((CEdit*)pDialog->GetDlgItem(251))->SetWindowTextW(String::convertStdStringToStdWString(pDATPathsMoverDialogData->m_strInputFolderPath).c_str());
	break;
	case 302: // Change button for Output Folder
	pDATPathsMoverDialogData->m_strOutputFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_22"), getIMGF()->getLastUsedDirectory("DATPATHSMOVER_DATOUTPUT"));
	if (pDATPathsMoverDialogData->m_strOutputFolderPath == "")
	{
	break;
	}
	pDATPathsMoverDialogData->m_strOutputFolderPath = Path::addSlashToEnd(pDATPathsMoverDialogData->m_strOutputFolderPath);
	getIMGF()->setLastUsedDirectory("DATPATHSMOVER_DATOUTPUT", pDATPathsMoverDialogData->m_strOutputFolderPath);
	((CEdit*)pDialog->GetDlgItem(301))->SetWindowTextW(String::convertStdStringToStdWString(pDATPathsMoverDialogData->m_strOutputFolderPath).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	pDATPathsMoverDialogData = (DATPathsMoverDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pDATPathsMoverDialogData->m_bMove = false;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
DATPathsMoverDialogData*			PopupGUIManager::showDATPathsMoverDialogData(void)
{
	DATPathsMoverDialogData *pDATPathsMoverDialogData = new DATPathsMoverDialogData;
	pDATPathsMoverDialogData->m_bMove = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DATPATHSMOVERDIALOG), getParentWindowHwnd(), DialogProc_DATPathsMoverDialog, (DWORD) pDATPathsMoverDialogData);

	return pDATPathsMoverDialogData;
}




// map mover and ID shifter dialog
INT_PTR CALLBACK DialogProc_MapMoverAndIDShifterDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	CMapMoverAndIDShifterDialogData *pMapMoverAndIDShifterDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
	pMapMoverAndIDShifterDialogData = (CMapMoverAndIDShifterDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pMapMoverAndIDShifterDialogData);
	break;
	}
	case WM_COMMAND:
	pMapMoverAndIDShifterDialogData = (CMapMoverAndIDShifterDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 351: // cancel
	pMapMoverAndIDShifterDialogData->m_bGo = false;
	EndDialog(hwndDlg, 0);
	break;
	case 350: // go
	{
	pMapMoverAndIDShifterDialogData->m_bGo = true;

	pMapMoverAndIDShifterDialogData->m_bUpdateIDEInFolder = ((Button*)pDialog->GetDlgItem(106))->GetCheck() == BST_CHECKED;
	pMapMoverAndIDShifterDialogData->m_bUpdateIPLInFolder = ((Button*)pDialog->GetDlgItem(109))->GetCheck() == BST_CHECKED;
	pMapMoverAndIDShifterDialogData->m_bIgnoreDefaultObjects = ((Button*)pDialog->GetDlgItem(250))->GetCheck() == BST_CHECKED;

	pMapMoverAndIDShifterDialogData->m_bMovePosition = ((Button*)pDialog->GetDlgItem(200))->GetCheck() == BST_CHECKED;
	pMapMoverAndIDShifterDialogData->m_bShiftIds = ((Button*)pDialog->GetDlgItem(150))->GetCheck() == BST_CHECKED;

	CString cstr1, cstr2, cstr3, cstr4, cstr5;
	((CEdit*)pDialog->GetDlgItem(101))->GetWindowText(cstr1);
	((CEdit*)pDialog->GetDlgItem(104))->GetWindowText(cstr2);
	((CEdit*)pDialog->GetDlgItem(107))->GetWindowText(cstr3);
	((CEdit*)pDialog->GetDlgItem(110))->GetWindowText(cstr4);
	((CEdit*)pDialog->GetDlgItem(113))->GetWindowText(cstr5);
	string str1, str2, str3, str4, str5;
	str1 = String::convertCStringToStdString(cstr1);
	str2 = String::convertCStringToStdString(cstr2);
	str3 = String::convertCStringToStdString(cstr3);
	str4 = String::convertCStringToStdString(cstr4);
	str5 = String::convertCStringToStdString(cstr5);

	pMapMoverAndIDShifterDialogData->m_strDATFilePath = str1;
	pMapMoverAndIDShifterDialogData->m_strGameFolderPath = str2;
	pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath = str3;
	pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath = str4;
	pMapMoverAndIDShifterDialogData->m_strOutputFolderPath = str5;

	if (str1 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_62"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str2 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (pMapMoverAndIDShifterDialogData->m_bUpdateIDEInFolder)
	{
	if (str3 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_64"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	}
	if (pMapMoverAndIDShifterDialogData->m_bUpdateIPLInFolder)
	{
	if (str4 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_65"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	}
	if (str5 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_28"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}

	pMapMoverAndIDShifterDialogData->m_strGameFolderPath = Path::addSlashToEnd(pMapMoverAndIDShifterDialogData->m_strGameFolderPath);
	pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath = Path::addSlashToEnd(pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath);
	pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath = Path::addSlashToEnd(pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath);

	CString cstr6, cstr7, cstr8, cstr9, cstr10, cstr11;
	((CEdit*)pDialog->GetDlgItem(151))->GetWindowText(cstr6);
	((CEdit*)pDialog->GetDlgItem(204))->GetWindowText(cstr7);
	((CEdit*)pDialog->GetDlgItem(205))->GetWindowText(cstr8);
	((CEdit*)pDialog->GetDlgItem(206))->GetWindowText(cstr9);
	((CEdit*)pDialog->GetDlgItem(301))->GetWindowText(cstr10);
	((CEdit*)pDialog->GetDlgItem(303))->GetWindowText(cstr11);
	string str6, str7, str8, str9, str10, str11;
	str6 = String::convertCStringToStdString(cstr6);
	str7 = String::convertCStringToStdString(cstr7);
	str8 = String::convertCStringToStdString(cstr8);
	str9 = String::convertCStringToStdString(cstr9);
	str10 = String::convertCStringToStdString(cstr10);
	str11 = String::convertCStringToStdString(cstr11);

	pMapMoverAndIDShifterDialogData->m_uiIDStart = String::toNumber(str6);
	pMapMoverAndIDShifterDialogData->m_vecPositionOffset.x = String::toFloat32(str7);
	pMapMoverAndIDShifterDialogData->m_vecPositionOffset.y = String::toFloat32(str8);
	pMapMoverAndIDShifterDialogData->m_vecPositionOffset.z = String::toFloat32(str9);

	if (pMapMoverAndIDShifterDialogData->m_bMovePosition)
	{
	if (str6 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_66"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	}
	else if (pMapMoverAndIDShifterDialogData->m_bShiftIds)
	{
	if (str7 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_67", "X"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str8 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_67", "Y"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str9 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedFormattedText("TextPopup_67", "Z"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	}
	else
	{
	Input::showMessage("You must choose an action (ID Shifter or Map Mover)", "Action Choice Required");
	break;
	}

	for (string strFilename : String::split(str10, "\n"))
	{
	pMapMoverAndIDShifterDialogData->m_umapShifterIgnoreFilenames[strFilename] = true;
	}
	for (string strFilename : String::split(str11, "\n"))
	{
	pMapMoverAndIDShifterDialogData->m_umapMoverIgnoreFilenames[strFilename] = true;
	}

	EndDialog(hwndDlg, 0);
	break;
	}
	case 102: // Change button for DAT File
	{
	vector<string> vecFilePaths = Input::openFile(getIMGF()->getLastUsedDirectory("MAPMOVERANDIDSHIFTER_DATINPUT"), "DAT", false);
	if (vecFilePaths.size() == 0)
	{
	break;
	}
	pMapMoverAndIDShifterDialogData->m_strDATFilePath = vecFilePaths[0];
	getIMGF()->setLastUsedDirectory("MAPMOVERANDIDSHIFTER_DATINPUT", Path::getDirectory(pMapMoverAndIDShifterDialogData->m_strDATFilePath));
	((CEdit*)pDialog->GetDlgItem(101))->SetWindowTextW(String::convertStdStringToStdWString(pMapMoverAndIDShifterDialogData->m_strDATFilePath).c_str());
	break;
	}
	case 105: // Change button for Game Folder
	pMapMoverAndIDShifterDialogData->m_strGameFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("MAPMOVERANDIDSHIFTER_GAMEFOLDER"));
	if (pMapMoverAndIDShifterDialogData->m_strGameFolderPath == "")
	{
	break;
	}
	pMapMoverAndIDShifterDialogData->m_strGameFolderPath = Path::addSlashToEnd(pMapMoverAndIDShifterDialogData->m_strGameFolderPath);
	getIMGF()->setLastUsedDirectory("MAPMOVERANDIDSHIFTER_GAMEFOLDER", pMapMoverAndIDShifterDialogData->m_strGameFolderPath);
	((CEdit*)pDialog->GetDlgItem(104))->SetWindowTextW(String::convertStdStringToStdWString(pMapMoverAndIDShifterDialogData->m_strGameFolderPath).c_str());
	break;
	case 108: // Change button for IDE Folder
	pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_5"), getIMGF()->getLastUsedDirectory("MAPMOVERANDIDSHIFTER_IDEFOLDER"));
	if (pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath == "")
	{
	break;
	}
	pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath = Path::addSlashToEnd(pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath);
	getIMGF()->setLastUsedDirectory("MAPMOVERANDIDSHIFTER_IDEFOLDER", pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath);
	((CEdit*)pDialog->GetDlgItem(107))->SetWindowTextW(String::convertStdStringToStdWString(pMapMoverAndIDShifterDialogData->m_strUpdateIDEInFolderPath).c_str());
	break;
	case 111: // Change button for IPL Folder
	pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_6"), getIMGF()->getLastUsedDirectory("MAPMOVERANDIDSHIFTER_IPLFOLDER"));
	if (pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath == "")
	{
	break;
	}
	pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath = Path::addSlashToEnd(pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath);
	getIMGF()->setLastUsedDirectory("MAPMOVERANDIDSHIFTER_IPLFOLDER", pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath);
	((CEdit*)pDialog->GetDlgItem(110))->SetWindowTextW(String::convertStdStringToStdWString(pMapMoverAndIDShifterDialogData->m_strUpdateIPLInFolderPath).c_str());
	break;
	case 114: // Change button for Output Folder
	pMapMoverAndIDShifterDialogData->m_strOutputFolderPath = Input::chooseFolderDialog(LocalizationManager::get()->getTranslatedText("TextPopup_28"), getIMGF()->getLastUsedDirectory("MAPMOVERANDIDSHIFTER_OUTPUTFOLDER"));
	if (pMapMoverAndIDShifterDialogData->m_strOutputFolderPath == "")
	{
	break;
	}
	pMapMoverAndIDShifterDialogData->m_strOutputFolderPath = Path::addSlashToEnd(pMapMoverAndIDShifterDialogData->m_strOutputFolderPath);
	getIMGF()->setLastUsedDirectory("MAPMOVERANDIDSHIFTER_OUTPUTFOLDER", Path::getDirectory(pMapMoverAndIDShifterDialogData->m_strOutputFolderPath));
	((CEdit*)pDialog->GetDlgItem(113))->SetWindowTextW(String::convertStdStringToStdWString(pMapMoverAndIDShifterDialogData->m_strOutputFolderPath).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	pMapMoverAndIDShifterDialogData = (CMapMoverAndIDShifterDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pMapMoverAndIDShifterDialogData->m_bGo = false;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
CMapMoverAndIDShifterDialogData*		PopupGUIManager::showMapMoverAndIDShifterDialog(void)
{
	CMapMoverAndIDShifterDialogData *pMapMoverAndIDShifterDialogData = new CMapMoverAndIDShifterDialogData;
	pMapMoverAndIDShifterDialogData->m_bGo = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_MAPMOVERANDIDSHIFTERDIALOG), getParentWindowHwnd(), DialogProc_MapMoverAndIDShifterDialog, (DWORD) pMapMoverAndIDShifterDialogData);

	return pMapMoverAndIDShifterDialogData;
}




// DAT model list dialog
INT_PTR CALLBACK DialogProc_DATModelListDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	DATModelListDialogData *pDATModelListDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
	pDATModelListDialogData = (DATModelListDialogData*)lParam;
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pDATModelListDialogData);
	break;
	}
	case WM_COMMAND:
	pDATModelListDialogData = (DATModelListDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 151: // cancel
	pDATModelListDialogData->m_bFetch = false;
	EndDialog(hwndDlg, 0);
	break;
	case 150: // fetch
	{
	pDATModelListDialogData->m_bFetch = true;

	CString cstr1, cstr2, cstr3;
	((CEdit*)pDialog->GetDlgItem(101))->GetWindowText(cstr1);
	((CEdit*)pDialog->GetDlgItem(104))->GetWindowText(cstr2);
	((CEdit*)pDialog->GetDlgItem(107))->GetWindowText(cstr3);
	string str1, str2, str3;
	str1 = String::convertCStringToStdString(cstr1);
	str2 = String::convertCStringToStdString(cstr2);
	str3 = String::convertCStringToStdString(cstr3);

	pDATModelListDialogData->m_strDATFilePath = str1;
	pDATModelListDialogData->m_strGameFolderPath = str2;
	pDATModelListDialogData->m_strOutputFilePath = str3;

	if (str1 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_62"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str2 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}
	if (str3 == "")
	{
	Input::showMessage(LocalizationManager::get()->getTranslatedText("TextPopup_63"), LocalizationManager::get()->getTranslatedFormattedText("TextPopupTitle_InputRequired").c_str());
	break;
	}

	pDATModelListDialogData->m_strGameFolderPath = Path::addSlashToEnd(pDATModelListDialogData->m_strGameFolderPath);

	EndDialog(hwndDlg, 0);
	break;
	}
	case 102: // Change button for DAT File
	{
	vector<string> vecFilePaths = Input::openFile(getIMGF()->getLastUsedDirectory("DATMODELLIST_DATINPUT"), "DAT", false);
	if (vecFilePaths.size() == 0)
	{
	break;
	}
	pDATModelListDialogData->m_strDATFilePath = vecFilePaths[0];
	getIMGF()->setLastUsedDirectory("DATMODELLIST_DATINPUT", Path::getDirectory(pDATModelListDialogData->m_strDATFilePath));
	((CEdit*)pDialog->GetDlgItem(101))->SetWindowTextW(String::convertStdStringToStdWString(pDATModelListDialogData->m_strDATFilePath).c_str());
	break;
	}
	case 105: // Change button for Game Folder
	pDATModelListDialogData->m_strGameFolderPath = Input::chooseFolderDialog(hwndDlg, LocalizationManager::get()->getTranslatedText("ChooseFolderPopup_3"), getIMGF()->getLastUsedDirectory("DATMODELLIST_GAMEFOLDER"));
	if (pDATModelListDialogData->m_strGameFolderPath == "")
	{
	break;
	}
	pDATModelListDialogData->m_strGameFolderPath = Path::addSlashToEnd(pDATModelListDialogData->m_strGameFolderPath);
	getIMGF()->setLastUsedDirectory("DATMODELLIST_GAMEFOLDER", pDATModelListDialogData->m_strGameFolderPath);
	((CEdit*)pDialog->GetDlgItem(104))->SetWindowTextW(String::convertStdStringToStdWString(pDATModelListDialogData->m_strGameFolderPath).c_str());
	break;
	case 108: // Change button for Output File
	pDATModelListDialogData->m_strOutputFilePath = Input::saveFileDialog(getIMGF()->getLastUsedDirectory("DATMODELLIST_TXTOUTPUT"), "TXT", "Model List.txt");
	if (pDATModelListDialogData->m_strOutputFilePath == "")
	{
	break;
	}
	getIMGF()->setLastUsedDirectory("DATMODELLIST_TXTOUTPUT", Path::getDirectory(pDATModelListDialogData->m_strOutputFilePath));
	((CEdit*)pDialog->GetDlgItem(107))->SetWindowTextW(String::convertStdStringToStdWString(pDATModelListDialogData->m_strOutputFilePath).c_str());
	break;
	}
	break;
	case WM_CLOSE:
	pDATModelListDialogData = (DATModelListDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pDATModelListDialogData->m_bFetch = false;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
DATModelListDialogData*				PopupGUIManager::showDATModelListDialog(void)
{
	DATModelListDialogData *pDATModelListDialogData = new DATModelListDialogData;
	pDATModelListDialogData->m_bFetch = false;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DATMODELLISTDIALOG), getParentWindowHwnd(), DialogProc_DATModelListDialog, (DWORD) pDATModelListDialogData);

	return pDATModelListDialogData;
}




// Overwrite Dialog
INT_PTR CALLBACK DialogProc_OverwriteEntryDialog(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	/*
	COverwriteEntryDialogData *pOverwriteEntryDialogData;
	CDialog *pDialog = (CDialog*)CWnd::FromHandle(hwndDlg);
	vector<string> vecFilePaths;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	pOverwriteEntryDialogData = (COverwriteEntryDialogData*)lParam;

	//getIMGF()->getPopupGUIManager()->updateGUIControlsTextToLanguage(pDialog, "OverwriteEntry");
	SetWindowLong(hwndDlg, GWL_USERDATA, (DWORD)pOverwriteEntryDialogData);
	break;
	case WM_COMMAND:
	pOverwriteEntryDialogData = (COverwriteEntryDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	switch (wParam)
	{
	case 150: // import
	pOverwriteEntryDialogData->m_bCancel = false;
	pOverwriteEntryDialogData->m_uiResultOption = 0;
	EndDialog(hwndDlg, 0);
	break;
	case 151: // check
	pOverwriteEntryDialogData->m_bCancel = false;
	pOverwriteEntryDialogData->m_uiResultOption = 1;
	EndDialog(hwndDlg, 0);
	break;
	case 152: // cancel
	pOverwriteEntryDialogData->m_bCancel = true;
	EndDialog(hwndDlg, 0);
	break;
	}
	break;
	case WM_CLOSE:
	pOverwriteEntryDialogData = (COverwriteEntryDialogData*)GetWindowLong(hwndDlg, GWL_USERDATA);
	pOverwriteEntryDialogData->m_bCancel = true;
	EndDialog(hwndDlg, 0);
	break;
	}

	*/
	return FALSE;
}
COverwriteEntryDialogData*				PopupGUIManager::showOverwriteEntryDialog(void)
{
	COverwriteEntryDialogData *pOverwriteEntryDialogData = new COverwriteEntryDialogData;
	pOverwriteEntryDialogData->m_bCancel = true;

	DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_OVERWRITEENTRYDIALOG), getParentWindowHwnd(), DialogProc_OverwriteEntryDialog, (DWORD) pOverwriteEntryDialogData);

	return pOverwriteEntryDialogData;
}