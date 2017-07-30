#ifndef CGUIShapeGeometry_3xPoints_H
#define CGUIShapeGeometry_3xPoints_H

#include "Type/Types.h"
#include "Type/Vector/CVector2i32.h"
#include "Type/Vector/CPoint2D.h"
#include "Shape/eGUIShape.h"
#include "Shape/CGUIShape.h"

class CGUIShapeGeometry_3xPoints : public CGUIShape
{
public:
	CGUIShapeGeometry_3xPoints(eGUIShape eShapeType);

	void							unserialize(bool bSkipShapeId = false);
	void							serialize(void);

	void							moveItem(bxcf::CVector2i32& vecPositionChange);
	void							resizeItemViaOffsets(bxcf::CVector2i32& vecItemSizeChange) {}

	void							setPoint1(bxcf::CPoint2D& vecPoint1) { m_vecPoint1 = vecPoint1; }
	bxcf::CPoint2D&						getPoint1(void) { return m_vecPoint1; }

	void							setPoint2(bxcf::CPoint2D& vecPoint2) { m_vecPoint2 = vecPoint2; }
	bxcf::CPoint2D&						getPoint2(void) { return m_vecPoint2; }
	
	void							setPoint3(bxcf::CPoint2D& vecPoint3) { m_vecPoint3 = vecPoint3; }
	bxcf::CPoint2D&						getPoint3(void) { return m_vecPoint3; }
	
private:
	bxcf::CPoint2D						m_vecPoint1;
	bxcf::CPoint2D						m_vecPoint2;
	bxcf::CPoint2D						m_vecPoint3;
};

#endif