#pragma once

#include "nsimgf.h"

enum imgf::mainLayer::input::EInputItem
{
	FORMATS,
	UTILITY,

	DAT,
	IMG,
	ITEM_DEFINITION,
	ITEM_PLACEMENT,
	MODELS,
	COLLISIONS,
	TEXTURES,
	ANIMATIONS,
	RADAR,

	NEW,
	OPEN,
	CLOSE,
	SAVE,

	SELECT_ALL,
	UNSELECT_ALL,
	SELECT_INVERSE,

	SETTINGS
};