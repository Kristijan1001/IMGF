#ifndef CDATChaseFormat_H
#define CDATChaseFormat_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/CFormat.h"
#include "Pool/CVectorPool.h"
#include "CDATChaseEntry.h"
#include <vector>

class bxcf::CDATChaseFormat : public bxcf::CFormat, public bxcf::CVectorPool<bxcf::CDATChaseEntry*>
{
public:
	CDATChaseFormat(void);
	
	void					unserialize(void);
	void					serialize(void);
};

#endif