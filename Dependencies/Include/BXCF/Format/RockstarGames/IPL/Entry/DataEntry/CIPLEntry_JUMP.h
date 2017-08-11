#ifndef CIPLEntry_JUMP_H
#define CIPLEntry_JUMP_H

#include "bxcf.h"
#include "Type/Types.h"
#include "Format/RockstarGames/IPL/Entry/CIPLEntry_Data.h"
#include "Type/Vector/Vec3f.h"

class bxcf::CIPLEntry_JUMP : public bxcf::CIPLEntry_Data
{
public:
	CIPLEntry_JUMP(bxcf::CIPLFormat *pIPLFormat) :
		CIPLEntry_Data(pIPLFormat, IPL_SECTION_JUMP),
		m_vecStartLowerPosition{ 0.0f, 0.0f, 0.0f },
		m_vecStartUpperPosition{ 0.0f, 0.0f, 0.0f },
		m_vecTargetLowerPosition{ 0.0f, 0.0f, 0.0f },
		m_vecTargetUpperPosition{ 0.0f, 0.0f, 0.0f },
		m_vecCameraPosition{ 0.0f, 0.0f, 0.0f },
		m_uiReward(0)
	{
	};

	void						unserialize(void);
	void						serialize(void);

	void						setStartLowerPosition(bxcf::Vec3f& vecStartLowerPosition) { m_vecStartLowerPosition = vecStartLowerPosition; }
	bxcf::Vec3f&					getStartLowerPosition(void) { return m_vecStartLowerPosition; }

	void						setStartUpperPosition(bxcf::Vec3f& vecStartUpperPosition) { m_vecStartUpperPosition = vecStartUpperPosition; }
	bxcf::Vec3f&					getStartUpperPosition(void) { return m_vecStartUpperPosition; }

	void						setTargetLowerPosition(bxcf::Vec3f& vecTargetLowerPosition) { m_vecTargetLowerPosition = vecTargetLowerPosition; }
	bxcf::Vec3f&					getTargetLowerPosition(void) { return m_vecTargetLowerPosition; }

	void						setTargetUpperPosition(bxcf::Vec3f& vecTargetUpperPosition) { m_vecTargetUpperPosition = vecTargetUpperPosition; }
	bxcf::Vec3f&					getTargetUpperPosition(void) { return m_vecTargetUpperPosition; }

	void						setCameraPosition(bxcf::Vec3f& vecCameraPosition) { m_vecCameraPosition = vecCameraPosition; }
	bxcf::Vec3f&					getCameraPosition(void) { return m_vecCameraPosition; }

	void						setReward(uint32 uiReward) { m_uiReward = uiReward; }
	uint32						getReward(void) { return m_uiReward; }

private:
	// GTA SA only
	bxcf::Vec3f					m_vecStartLowerPosition;
	bxcf::Vec3f					m_vecStartUpperPosition;
	bxcf::Vec3f					m_vecTargetLowerPosition;
	bxcf::Vec3f					m_vecTargetUpperPosition;
	bxcf::Vec3f					m_vecCameraPosition;
	uint32						m_uiReward;
};

#endif