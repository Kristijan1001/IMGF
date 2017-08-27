#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"

#pragma pack(push, 1)
struct bxcf::CDDSFormat_Header_DDS_PIXELFORMAT_Part2
{
	uint32					m_uiCaps;
	uint32					m_uiCaps2;
	uint32					m_uiCaps3;
	uint32					m_uiCaps4;
	uint32					m_uiReserved2;
};
#pragma pack(pop)