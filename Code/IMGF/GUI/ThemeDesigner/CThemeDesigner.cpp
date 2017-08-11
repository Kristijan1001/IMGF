#include "CThemeDesigner.h"
#include "Math/CMath.h"
#include "Event/eEvent.h"
#include "Event/CEventManager.h"
#include "Input/CInputManager.h"
#include "Layer/CGUILayer.h"
#include "Shape/CGUIShape.h"
#include "Styles/CGUIStyles.h"
#include "Controls/CTabBarControl.h"
#include "GUI/ThemeDesigner/Tabs/CThemeDesignerTab_AddItem.h"
#include "GUI/ThemeDesigner/Tabs/CThemeDesignerTab_Save.h"
#include "Type/Colour/CColour.h"
#include <vector>

using namespace std;
using namespace bxcf;

CThemeDesigner::CThemeDesigner(void) :
	m_bThemeDesignerModeEnabled(false),
	m_pWindow(nullptr),
	m_pTabControl(nullptr),
	m_pItemHoverRectangle(nullptr),
	m_pActiveItemRectangle(nullptr)
{
}

void					CThemeDesigner::init(void)
{
	/*
	todo
	initWindow();
	initWindowDesign();
	CEventManager::get()->bindEvent(EVENT_onToolReady, [](void *pBoundArg) { ((CThemeDesigner*) pBoundArg)->bindEvents(); }, this);
	*/
}

void					CThemeDesigner::bindEvents(void)
{
	for (CThemeDesignerTab *pThemeDesignerTab : getEntries())
	{
		pThemeDesignerTab->bindEvents();
	}
}

void					CThemeDesigner::initWindow(void)
{
	/*
	Vec2i vecWindowPosition((int32)10, 10);
	Vec2u vecWindowSize(500, 500);
	CWindow *pWindow = bxgx::CGUIManager::get()->addWindow(vecWindowPosition, vecWindowSize);
	pWindow->getStyles()->setStyle("fill-colour", CColour(33, 78, 103));
	setWindow(pWindow);

	CGUIStyles *pStyles_TabControl = bxgx::CGUIManager::createStyles();
	pStyles_TabControl->setStyle("fill-colour", CColour(19, 46, 60));
	pStyles_TabControl->setStyle("text-colour", CColour(121, 180, 199));
	pStyles_TabControl->setStyle("border-colour", CColour(121, 180, 199));
	pStyles_TabControl->setStyle<string>("text-align", "center center");
	pStyles_TabControl->setStyle<uint32>("inner-spacing-x", 15);
	//pStyles_TabControl->setStyle<bool>("border-state-left", false);
	//pStyles_TabControl->setStyle<bool>("border-state-top", false);

	CGUILayer *pLayer_ThemeDesignerWindow = pWindow->addLayer(pWindow, true);
	CTabBarControl *pTabControl = pLayer_ThemeDesignerWindow->addTabBar(Vec2i((int32)0, 0), Vec2u(vecWindowSize.x, 25), pStyles_TabControl);
	setTabControl(pTabControl);
	m_umapTabControlEntries["items"] = pTabControl->addTab("Items");
	m_umapTabControlEntries["add_item"] = pTabControl->addTab("Add Item", true);
	m_umapTabControlEntries["item"] = pTabControl->addTab("Item");
	m_umapTabControlEntries["load"] = pTabControl->addTab("Load");
	m_umapTabControlEntries["save"] = pTabControl->addTab("Save");
	m_umapTabControlEntries["download"] = pTabControl->addTab("Download");
	m_umapTabControlEntries["upload"] = pTabControl->addTab("Upload");
	*/
}

void					CThemeDesigner::initWindowDesign(void)
{
	addEntry(new CThemeDesignerTab_AddItem(this));
	addEntry(new CThemeDesignerTab_Save(this));

	for (CThemeDesignerTab *pThemeDesignerTab : getEntries())
	{
		pThemeDesignerTab->initDesign();
	}
}

// layers
CGUILayer*				CThemeDesigner::addLayer(string strLayerKey, bool bLayerIsEnabled)
{
	CGUILayer *pLayer = getWindow()->createLayer(getWindow(), bLayerIsEnabled); // todo - param same as object
	m_umapTabLayers[strLayerKey] = pLayer;
	getTabControl()->bindTabLayer(m_umapTabControlEntries[strLayerKey], pLayer);
	return pLayer;
}

// enabled status
void					CThemeDesigner::setThemeDesignerModeEnabled(bool bThemeDesignerModeEnabled)
{
	m_bThemeDesignerModeEnabled = bThemeDesignerModeEnabled;
	bxgx::CGUIManager::get()->getEntryByIndex(1)->setEventTriggerEventTypeId(bThemeDesignerModeEnabled ? EVENT_TYPE_THEME_DESIGNER : EVENT_TYPE_WINDOW);
}