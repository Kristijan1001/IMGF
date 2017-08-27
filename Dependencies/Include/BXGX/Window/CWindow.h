#pragma once

#include "nsbxgx.h"
#include "nsbxcf.h"
#include "Type/Types.h"
#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Type/Colour/CColour.h"
#include "Pool/CVectorPool.h"
#include "Layer/CLayer.h"
#include "Item/CLayerItem.h"
#include "Control/Control.h"
#include "Interaction/CRectangleItemPlacement.h"
#include "Event/Events.h"
#include "Renderable/ERenderable.h"
#include "Window/EWindowType.h"
#include "Renderable/CRenderable.h"
#include <unordered_map>
#include <vector>
#include <mutex>

class bxgx::CRadioButton;
class CDropTarget;
class bxgx::CWindow;
class bxgx::Control;

class bxgx::CWindow : public bxcf::EventBindable, public bxcf::CVectorPool<CLayer*>, public CRenderable
{
public:
	CWindow(void);
	~CWindow(void);
	
	void									init(void);

	void									unload(void);

	void									bindEvents(void);
	void									unbindEvents(void);
	void									bindLayerEvents(void);
	void									unbindLayerEvents(void);
	
	void									unserialize(void);
	void									serialize(void);

	bxgx::item::ERenderable					getItemType(void) { return bxgx::item::WINDOW; }
	uint32									getItemSubType(void) { return bxgx::item::window::TYPE_1; }

	bool									isPointInItem(bxcf::Vec2i& vecPoint) { return true; }
	bool									doesItemHaveFocus(void) { return true; }

	bool									isPointInControl(bxcf::Vec2i& vecPoint);
	bxgx::Control*							getControlFromPoint(bxcf::Vec2i& vecPoint);
	std::vector<CLayerItem*>					getItemsInRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	bool									doesDropHaveListOpen(void);

	void									onWindowLoseFocus(void);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPoint);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPoint);
	bool									onDoubleLeftMouseUp(bxcf::Vec2i& vecCursorPoint);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPoint);

	void									onRenderBefore(void);
	void									onRenderAfter(void);

	// render main
	void									onPaint(void);

	void									onRenderWindow(void);
	void									onRenderRenderables(void);
	void									onRenderRenderable(CRenderable *pRenderable);

	// render marking
	void									setRenderableMarkedForRender(CRenderable *pItem, bool bItemIsMarkedForRender);
	bool									isRenderableMarkedForRender(CRenderable *pItem);
	std::vector<CRenderable*>&				getRenderablesMarkedForRender(void) { return m_vecRenderablesMarkedToRender; }
	bool									areAnyRenderablesMarkedForRender(void);
	void									clearRenderablesMarkedForRender(void);

	bool									isWindowMarkedForRender(void);
	std::vector<CWindow*>					getWindowsMarkedForRender(void);

	// render marking and triggering
	void									render(void);
	void									renderNow(void);
	void									renderRectangle(bxcf::Vec2i& vecPosition, bxcf::Vec2u& vecSize);

	// paint triggering (WM_PAINT in WndProc)
	void									checkToTriggerPaint(void);
	
	void									triggerPaint(void);
	void									triggerPaintNow(void);

	// window resize
	bool									checkToApplyWindowResizeCursor(void);
	bool									checkToApplyWindowRegularCursor(void);
	bool									checkToStartMovingOrResizingWindow(bool bCursorIsHoveringTitleBarIcon = false);
	bool									checkToStopMovingOrResizingWindow(void);
	bool									checkToMoveOrResizeWindow(void);

	void									setMaxSizeApplies(bool bMaxSizeApplies) { m_bMaxSizeApplies = bMaxSizeApplies; }
	bool									doesMaxSizeApply(void) { return m_bMaxSizeApplies; }

	void									setMinSize(bxcf::Vec2u& vecMinSize) { m_vecMinSize = vecMinSize; }
	bxcf::Vec2u&							getMinSize(void) { return m_vecMinSize; }

	void									setMaxSize(bxcf::Vec2u& vecMaxSize) { m_vecMaxSize = vecMaxSize; }
	bxcf::Vec2u&							getMaxSize(void) { return m_vecMaxSize; }

	void									setClassName(const char * pClassName) { m_pClassName = pClassName; }
	const char *							getClassName(void) { return m_pClassName; }

	void									setTitleBarHeight(uint32 uiTitleBarHeight) { m_uiTitleBarHeight = uiTitleBarHeight; }
	uint32									getTitleBarHeight(void) { return m_uiTitleBarHeight; }

private:
	void									setTitleBarColour(bxcf::CColour colour) { m_colTitleBarColour = colour; }
	bxcf::CColour							getTitleBarColour(void) { return m_colTitleBarColour; }

	void									setTitleBarIconGapDistance(uint32 uiTitleBarIconGapDistance) { m_uiTitleBarIconGapDistance = uiTitleBarIconGapDistance; }
	uint32									getTitleBarIconGapDistance(void) { return m_uiTitleBarIconGapDistance; }

	void									setTitleBarIconHoverStatus(bool bTitleBarIconHoverStatus) { m_bTitleBarIconHoverStatus = bTitleBarIconHoverStatus; }
	bool									getTitleBarIconHoverStatus(void) { return m_bTitleBarIconHoverStatus; }

	void									setTitleBarIconHoverIndex(uint32 uiTitleBarIconHoverIndex) { m_uiTitleBarIconHoverIndex = uiTitleBarIconHoverIndex; }
	uint32									getTitleBarIconHoverIndex(void) { return m_uiTitleBarIconHoverIndex; }

public:
	void									addTitleBar(std::string strTitleBarText);
	void									removeTitleBar(void);

private:
	bxcf::Vec2i								getTitleBarIconPosition(uint32 uiIconIndex);
	bxcf::Vec2u								getTitleBarIconSize(void);
	bool									isPointInTitleBar(bxcf::Vec2i& vecPoint);
	void									onClickTitleBarIcon(uint32 uiIconIndex);

	uint8									getTitleBarIconCursorHoverIndex(void);
	bool									isCursorHoveringTitleBarIcon(void);
	bxcf::Vec2i								getTitleBarIconsHoverPosition(void);
	bxcf::Vec2u								getTitleBarIconsHoverSize(void);

	void									renderBorder(void);

	void									renderTitleBar(void);
	void									renderTitleBarBackground(void);
	void									renderTitleBarText(void);

	void									renderTitleBarIcons(void);

	void									renderTitleBarIconHoverBackground(void);

	void									renderTitleBarMinimizeIcon(void);
	void									renderTitleBarMaximizeIcon(void);
	void									renderTitleBarCloseIcon(void);

public:
	CLayer*									addLayer(uint32 uiLayerId = -1, bool bEnabled = true, int32 iZIndex = 0);
	template <class LayerClass>
	LayerClass*								addLayer(uint32 uiLayerId = -1, bool bEnabled = true, int32 iZIndex = 0);
	void									removeLayer(CLayer* pLayer);
	CLayer*									getLayerById(uint32 uiLayerId);
	void									swapLayersEnabled(uint32 uiLayerId1, uint32 uiLayerId2);

	uint32									getLayerInsertionIndex(int32 iZIndex);

	bool									doesActiveItemExist(void) { return m_pActiveItem != nullptr; }
	void									setActiveItem(CLayerItem *pItem);
	CLayerItem*								getActiveItem(void) { return m_pActiveItem; }
	void									clearActiveItem(void);

	void									unmarkRadios(CRadioButton *pRadio);

	void									setOpenLastFilename(std::string strFileName);
	void									clearOpenLastFilename(void);

	void									setWindowHandle(HWND hwndWindow) { m_hwndWindow = hwndWindow; }
	HWND									getWindowHandle(void) { return m_hwndWindow; }

	void									setPosition(bxcf::Vec2i& vecPosition);
	bxcf::Vec2i&							getPosition(void) { return m_vecPosition; }

	void									setSize(bxcf::Vec2u vecSize);
	bxcf::Vec2u&							getSize(void) { return m_vecSize; }

	void									setMovingWindow(bool bMovingMainWindow) { m_bMovingWindow = bMovingMainWindow; }
	bool									isMovingWindow(void) { return m_bMovingWindow; }

	void									setResizingWindow(bool bResizingWindow) { m_bResizingWindow = bResizingWindow; }
	bool									isResizingWindow(void) { return m_bResizingWindow; }

	void									setWindowResizeEdges(uint32 uiMainWindowResizeEdges) { m_uiWindowResizeEdges = uiMainWindowResizeEdges; }
	uint32									getWindowResizeEdges(void) { return m_uiWindowResizeEdges; }

	void									setParentWindow(CWindow *pParentWindow) { m_pParentWindow = pParentWindow; }
	CWindow*								getParentWindow(void) { return m_pParentWindow; }

	void									setMaximized(bool bMaximized);
	bool									isMaximized(void) { return m_bMaximized; }

	void									setMinimized(bool bMinimized);
	bool									isMinimized(void) { return m_bMinimized; }

	void									setPreviousPosition(bxcf::Vec2i& vecPreviousPosition) { m_vecPreviousPosition = vecPreviousPosition; }
	bxcf::Vec2i&							getPreviousPosition(void) { return m_vecPreviousPosition; }

	void									setPreviousSize(bxcf::Vec2u& vecPreviousSize) { m_vecPreviousSize = vecPreviousSize; }
	bxcf::Vec2u&							getPreviousSize(void) { return m_vecPreviousSize; }

private:
	void									initializeLayer(CLayer *pLayer, uint32 uiLayerId, bool bEnabled, int32 iZIndex);

private:
	const char *							m_pClassName;
	HWND									m_hwndWindow;
	CWindow*								m_pParentWindow;
	bxcf::Vec2i								m_vecPosition;
	bxcf::Vec2u								m_vecSize;
	bxcf::Vec2u								m_vecMinSize;
	bxcf::Vec2u								m_vecMaxSize;
	uint32									m_uiWindowResizeEdges;
	CDropTarget*							m_pDropTarget;
	uint32									m_uiTitleBarHeight;
	bxcf::CColour							m_colTitleBarColour;
	std::string								m_strTitleBarText;
	uint32									m_uiTitleBarIconGapDistance;
	uint32									m_uiTitleBarIconHoverIndex;
	uint8									m_bMovingWindow					: 1;
	uint8									m_bResizingWindow				: 1;
	uint8									m_bMaximized					: 1;
	uint8									m_bMinimized					: 1;
	uint8									m_bTitleBarIconHoverStatus		: 1;
	uint8									m_bTitleBarExists				: 1;
	uint8									m_bMaxSizeApplies				: 1;
	bxcf::Vec2i								m_vecPreviousPosition;
	bxcf::Vec2u								m_vecPreviousSize;
	CLayerItem*								m_pActiveItem;
	// todo CRectangleItemPlacement<CWindow>	m_placeableWindow;		// gui windows
	CRectangleItemPlacement<CLayerItem>		m_placeableItem;		// gui items - e.g. shapes and controls
	std::unordered_map<uint32, bool>		m_umapEventUsages;
	std::vector<CRenderable*>				m_vecRenderablesMarkedToRender;
public:
	bool									m_bCurrentlyPainting;
	bool									m_bTriggerPaintAfterPaint;
	bool									m_bTriggerPaintNow;

	/*
	todo
	HMENU						m_hMenu_File;
	HMENU						m_hSubMenu_File_OpenRecent;
	HMENU						m_hMenu_Entry_Sort;
	HMENU						m_hSubMenu_File_Sessions;

	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_SelectRWVersion; // todo - move this shit to like CMenuManager
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertDFFtoRWVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertTXDtoRWVersion;
	std::unordered_map<uint32, CRasterDataFormat*>	m_umapMenuItemMapping_ConvertTXDtoTextureFormat;
	std::unordered_map<uint32, CCOLVersion*>		m_umapMenuItemMapping_ConvertCOLtoCOLVersion;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertDFFtoRWVersion_DragDrop;
	std::unordered_map<uint32, CRWVersion*>			m_umapMenuItemMapping_ConvertTXDtoRWVersion_DragDrop;
	std::unordered_map<uint32, CRasterDataFormat*>	m_umapMenuItemMapping_ConvertTXDtoTextureFormat_DragDrop;
	std::unordered_map<uint32, CCOLVersion*>		m_umapMenuItemMapping_ConvertCOLtoCOLVersion_DragDrop;

	std::unordered_map<uint32, eCOLVersion>		m_umapFilterMapping_COLVersion;
	std::unordered_map<uint32, eRWVersion>		m_umapFilterMapping_RWVersion;
	int											m_iFilterMapping_UnknownVersion;
	*/
};

template <class LayerClass>
LayerClass*								bxgx::CWindow::addLayer(uint32 uiLayerId, bool bEnabled, int32 iZIndex)
{
	LayerClass *pLayer = new LayerClass;
	initializeLayer(pLayer, uiLayerId, bEnabled, iZIndex);
	return pLayer;
}