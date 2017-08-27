#pragma once

#include "nsbxgx.h"
#include "Type/Types.h"
#include "Control/Control.h"
#include "Controls/Components/TextComponent.h"

class bxgx::CButton : public bxgx::Control, public bxgx::TextComponent
{
public:
	CButton(void);
	virtual ~CButton(void) {}

	void									bindEvents(void);

	void									unserialize(bool bSkipControlId = false);
	void									serialize(void);

	bool									onLeftMouseDown(bxcf::Vec2i& vecCursorPosition);
	bool									onLeftMouseUp(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseMove(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseEnter(bxcf::Vec2i& vecCursorPosition);
	bool									onMouseExit(bxcf::Vec2i& vecCursorPosition);
	void									onRender(void);

	bool									doesControlUsePosition(bxcf::Vec2i& vecPoint) { return true; }

	void									setCursorHoverActive(bool bCursorHoverIsActive) { m_bCursorHoverIsActive = bCursorHoverIsActive; }
	bool									isCursorHoverActive(void) { return m_bCursorHoverIsActive; }

private:
	bool									m_bCursorHoverIsActive;
};