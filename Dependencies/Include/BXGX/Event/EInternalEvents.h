#pragma once

#include "bxgx.h"

enum bxgx::events::EInternalEvents
{
	// window
	GAIN_WINDOW_FOCUS			= 1000,
	LOSE_WINDOW_FOCUS			= 1001,

	// mouse
	MOVE_MOUSE					= 2000,
	
	LEFT_MOUSE_DOWN				= 2001,
	LEFT_MOUSE_UP				= 2002,
	DOUBLE_LEFT_MOUSE_DOWN		= 2003,
	DOUBLE_LEFT_MOUSE_UP		= 2004,

	RIGHT_MOUSE_DOWN			= 2100,
	RIGHT_MOUSE_UP				= 2101,
	DOUBLE_RIGHT_MOUSE_DOWN		= 2102,
	DOUBLE_RIGHT_MOUSE_UP		= 2103,

	MOVE_MOUSE_WHEEL			= 2200,
	MOUSE_WHEEL_DOWN			= 2201,
	MOUSE_WHEEL_UP				= 2202,
	DOUBLE_MOUSE_WHEEL_DOWN		= 2203,
	DOUBLE_MOUSE_WHEEL_UP		= 2204,

	MOUSE_ENTER					= 2300,
	MOUSE_EXIT					= 2301,

	// key
	KEY_DOWN					= 3000,
	KEY_UP						= 3001,
	KEY_HELD					= 3002,
	DOUBLE_KEY_DOWN				= 3003,
	DOUBLE_KEY_UP				= 3004,

	// render
	RENDER						= 4000,
	BEFORE_RENDER				= 4001,
	AFTER_RENDER				= 4002
};