#ifndef CIPLEntry_TCYC_H
#define CIPLEntry_TCYC_H

#include "bxcf.h"
#include "Type/Vector/Vec3f.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"

class bxcf::CIPLEntry_TCYC : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_TCYC(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_TCYC)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setPositionLower(bxcf::Vec3f& vecPositionLower) { m_vecPositionLower = vecPositionLower; }
	bxcf::Vec3f&					getPositionLower(void) { return m_vecPositionLower; }

	void						setPositionUpper(bxcf::Vec3f& vecPositionUpper) { m_vecPositionUpper = vecPositionUpper; }
	bxcf::Vec3f&					getPositionUpper(void) { return m_vecPositionUpper; }

	void						setUnknown1(uint32 uiUnknown1) { m_uiUnknown1 = uiUnknown1; }
	uint32						getUnknown1(void) { return m_uiUnknown1; }

	void						setWeatherId(uint32 uiWeatherId) { m_uiWeatherId = uiWeatherId; }
	uint32						getWeatherId(void) { return m_uiWeatherId; }

	void						setBrightness(int32 iBrightness) { m_iBrightness = iBrightness; }
	int32						getBrightness(void) { return m_iBrightness; }

	void						setTime(uint32 uiTime) { m_uiTime = uiTime; }
	uint32						getTime(void) { return m_uiTime; }

	void						setDrawDistance(uint32 uiDrawDistance) { m_uiDrawDistance = uiDrawDistance; }
	uint32						getDrawDistance(void) { return m_uiDrawDistance; }

private:
	// GTA SA only
	bxcf::Vec3f					m_vecPositionLower;
	bxcf::Vec3f					m_vecPositionUpper;
	uint32						m_uiUnknown1;
	uint32						m_uiWeatherId;
	int32						m_iBrightness;
	uint32						m_uiTime;
	uint32						m_uiDrawDistance;
};

#endif