#ifndef CGUIShape_H
#define CGUIShape_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Event/CEventType.h"
#include "Event/CEventBinder.h"
#include "Shape/Geometry/eGUIShapeGeometry.h"
#include "Shape/eGUIShape.h"
#include "Item/CGUIItem.h"
#include <vector>

class CGUIStyles;
class CGUILayer;
class CWindow;

class CGUIShape : public CGUIItem, public bxcf::CEventType
{
public:
	CGUIShape(eGUIShapeGeometry eShapeGeometry, eGUIShape eShapeType);
	virtual ~CGUIShape(void) {}

	void									unload(void) {}

	virtual void							unserialize(bool bSkipShapeId = false);
	virtual void							serialize(void);

	uint32									getItemType(void) { return bxgx::item::SHAPE; }
	uint32									getItemSubType(void) { return m_eShapeType; }

	bool									doesItemHaveFocus(void) { return true; }

	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, void(*pFunction)(void*, void*), void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bxcf::CEventBoundFunction*				bindEvent(uint32 uiEventId, bxcf::CInputEventCallbacks *pObject, void *pTriggerArgument = nullptr, int32 iZOrder = 0);
	bool									triggerEvent(uint32 uiEventId, void *pTriggerArgument = nullptr);

	void									setShapeGeometry(eGUIShapeGeometry eShapeGeometry) { m_eShapeGeometry = eShapeGeometry; }
	eGUIShapeGeometry						getShapeGeometry(void) { return m_eShapeGeometry; }

	void									setShapeType(eGUIShape eShapeType) { m_eShapeType = eShapeType; }
	eGUIShape								getShapeType(void) { return m_eShapeType; }

	void									setShapeId(uint32 uiShapeId) { m_uiShapeId = uiShapeId; }
	uint32									getShapeId(void) { return m_uiShapeId; }

private:
	eGUIShapeGeometry						m_eShapeGeometry;
	eGUIShape								m_eShapeType;
	uint32									m_uiShapeId;
};

#endif