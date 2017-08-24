#pragma once

#include "bxcf.h"
#include <string>

class NetworkDevice;

class bxcf::LinkLayer
{
public:
	static std::string				createPacket(void);

	static NetworkDevice*			getDevice(void);
};