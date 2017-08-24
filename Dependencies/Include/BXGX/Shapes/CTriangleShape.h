#ifndef CTriangleShape_H
#define CTriangleShape_H

#include "Type/Vector/Vec2i.h"
#include "Type/Vector/Vec2u.h"
#include "Shapes/Geometries/CGUIShapeGeometry_3xPoints.h"

class CTriangleShape : public CGUIShapeGeometry_3xPoints
{
public:
	CTriangleShape(void);

	void							bindEvents(void);

	void							onRender(void);

	bool							isPointInItem(bxcf::Vec2i& vecPoint);
	bxcf::Vec2i					getBoundingRectanglePosition(void);
	bxcf::Vec2u					getBoundingRectangleSize(void);
};

#endif