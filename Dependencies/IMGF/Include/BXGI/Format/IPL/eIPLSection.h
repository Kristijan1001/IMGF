#pragma once

#include "nsbxgi.h"
#include "Type/Types.h"

enum bxgi::EIPLSection
{
	IPL_SECTION_UNKNOWN,
	IPL_SECTION_INST,
	IPL_SECTION_ZONE,
	IPL_SECTION_CULL,
	IPL_SECTION_PICK,
	IPL_SECTION_PATH,
	IPL_SECTION_OCCL,
	IPL_SECTION_MULT,
	IPL_SECTION_GRGE,
	IPL_SECTION_ENEX,
	IPL_SECTION_CARS,
	IPL_SECTION_JUMP,
	IPL_SECTION_TCYC,
	IPL_SECTION_AUZO,
	IPL_SECTION_MZON,
	IPL_SECTION_VNOD,
	IPL_SECTION_LINK,
	IPL_SECTION_BLOK,
	IPL_SECTION_MLOPLUS,
	IPL_SECTION_2DFX,
	IPL_SECTION_LODM,
	IPL_SECTION_SLOW,
	IPL_SECTION_RTFX
};