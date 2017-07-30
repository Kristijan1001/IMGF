#ifndef CGUIStyles_H
#define CGUIStyles_H

#include "bxgx.h"
#include "Type/Types.h"
#include "Type/Vector/CPoint2D.h"
#include "Pool/CMultipleTypeValuesUMapContainer.h"
#include "Styles/CCoordinates.h"
#include <string>
#include <vector>

class CGUIStyles;

namespace bxgx
{
	// functions
	template <typename ...T>
	CGUIStyles*		styles(T...); // in CGUIStyles.h
};

class CGUIStyles : public bxcf::CMultipleTypeValuesUMapContainer<std::string>
{
public:
	CGUIStyles(void);

	void					init(void);
	void					uninit(void);

	bool					doesStyleExist(std::string strStyleName);

	void					setStyle(std::string strStyleName, bool bStyleValue);
	void					setStyle(std::string strStyleName, uint32 uiStyleValue);
	void					setStyle(std::string strStyleName, int32 iStyleValue);
	void					setStyle(std::string strStyleName, float32 fStyleValue);
	void					setStyle(std::string strStyleName, std::string strStyleValue);

	template <typename ValueType>
	void					setStyle(std::string strStyleName, ValueType value);
	template <typename ValueType>
	ValueType				getStyle(std::string strStyleName);

	template <typename ValueType>
	ValueType				getStyleDefaultValue(std::string strStyleName);

	bool					doesHaveBorder(void);
	bool					doesHaveLeftBorder(void);
	bool					doesHaveRightBorder(void);
	bool					doesHaveTopBorder(void);
	bool					doesHaveBottomBorder(void);
	bool					doesHaveFill(void);

	std::string				getTextAlignX(void);
	std::string				getTextAlignY(void);
	bxcf::CPoint2D				getMinInnerSpacing(void);
	bxcf::CPoint2D				getMaxInnerSpacing(void);
	uint32					getInnerSpacingTotalX(void);
	uint32					getInnerSpacingTotalY(void);

	void					restoreTemporaryStyleData(void);
	void					restoreStyleOverwrites(void);

	std::string				getResolvedStyleName(std::string strStyleName);

	void					setItemComponent(std::string strItemComponent) { m_strItemComponent = strItemComponent; }
	std::string&			getItemComponent(void) { return m_strItemComponent; }
	void					resetItemComponent(void) { m_strItemComponent = ""; }

	void					setItemStatus(std::string strItemStatus) { m_strItemStatus = strItemStatus; }
	std::string&			getItemStatus(void) { return m_strItemStatus; }
	void					resetItemStatus(void) { m_strItemStatus = ""; }

	void					setHasFillOverwrite(bool bHasFillOverwrite) { m_bHasFillOverwrite = bHasFillOverwrite; }
	bool					doesHaveFillOverwrite(void) { return m_bHasFillOverwrite; }

	static bxcf::CMultipleTypeValuesUMapContainer<std::string>&	getStyleDefaultValues(void) { return m_umapStyleDefaultValues; }

	static bool				doesDefaultStyleValueExist(std::string strStyleName);

private:
	uint8													m_bHasFillOverwrite		: 1;
	std::string												m_strItemComponent;
	std::string												m_strItemStatus;
	static bxcf::CMultipleTypeValuesUMapContainer<std::string>	m_umapStyleDefaultValues;
};




template <typename ValueType>
void				CGUIStyles::setStyle(std::string strStyleName, ValueType value)
{
	setEntry<ValueType>(strStyleName, value);
}

template <typename ValueType>
ValueType				CGUIStyles::getStyle(std::string strStyleName)
{
	/*
	Order of style processing
	-------------------------
	applied style: default.fill-colour:marked
	applied style: fill-colour:marked
	default style: fill-colour:marked	- eventually can be fully resolved to encounter for default values for multiple components - todo
	applied style: default.fill-colour
	applied style: fill-colour
	default style: fill-colour		- eventually can be fully resolved to encounter for default values for multiple components - todo
	*/

	bool
		bHasComponent = getItemComponent() != "",
		bHasStatus = getItemStatus() != "";
	std::string
		strStyleNameFullyResolved = (getItemComponent() == "" ? "default." : (getItemComponent() + ".")) + strStyleName + (getItemStatus() == "" ? "" : (":" + getItemStatus())), // with component and status
		strStyleNameWithStatus = strStyleName + (getItemStatus() == "" ? "" : (":" + getItemStatus())),
		strStyleNameWithComponent = (getItemComponent() == "" ? "default." : (getItemComponent() + ".")) + strStyleName;

	if (bHasComponent && bHasStatus && doesStyleExist(strStyleNameFullyResolved))
	{
		// e.g. drop-triangle.fill-colour:list-open
		return *getEntryPointer<ValueType>(strStyleNameFullyResolved);
	}
	else if (bHasComponent && bHasStatus && doesDefaultStyleValueExist(strStyleNameFullyResolved))
	{
		// e.g. drop-triangle.fill-colour:list-open
		return getStyleDefaultValue<ValueType>(strStyleNameFullyResolved);
	}
	else if (bHasStatus && doesStyleExist(strStyleNameWithStatus))
	{
		// e.g. fill-colour:list-open
		return *getEntryPointer<ValueType>(strStyleNameWithStatus);
	}
	else if (bHasStatus && doesDefaultStyleValueExist(strStyleNameWithStatus))
	{
		// e.g. fill-colour:list-open
		return getStyleDefaultValue<ValueType>(strStyleNameWithStatus);
	}
	else if (bHasComponent && doesStyleExist(strStyleNameWithComponent))
	{
		// e.g. drop-triangle.fill-colour
		return *getEntryPointer<ValueType>(strStyleNameWithComponent);
	}
	else if (bHasComponent && doesDefaultStyleValueExist(strStyleNameWithComponent))
	{
		// e.g. drop-triangle.fill-colour
		return getStyleDefaultValue<ValueType>(strStyleNameWithComponent);
	}
	else if (doesStyleExist(strStyleName))
	{
		// e.g. fill-colour
		return *getEntryPointer<ValueType>(strStyleName);
	}
	else
	{
		// e.g. fill-colour
		return getStyleDefaultValue<ValueType>(strStyleName);
	}
}

template <typename ValueType>
ValueType				CGUIStyles::getStyleDefaultValue(std::string strStyleName)
{
	if (getStyleDefaultValues().doesEntryExist(strStyleName))
	{
		return *(getStyleDefaultValues().getEntryPointer<ValueType>(strStyleName));
	}
	else
	{
		return ValueType();
	}
}

template <typename ...T>
CGUIStyles*		bxgx::styles(T... ppStyles)
{
	std::vector<const char * /*, sizeof...(T)*/> vecStyles = { ppStyles ... };
	CGUIStyles * pStyles = new CGUIStyles;
	for (const char * szStyle : vecStyles)
	{
		std::string strStyle = std::string(szStyle);
		auto parts = bxcf::CString2::split(strStyle, ":");
		std::string prop = bxcf::CString2::trim(parts[0]);
		std::string value = bxcf::CString2::trim(parts[1]);

		if (prop == "border-colour")
		{
			auto parts2 = bxcf::CString2::split(value, " ");
			uint8 r = bxcf::CString2::toNumber(parts2[0]);
			uint8 g = bxcf::CString2::toNumber(parts2[1]);
			uint8 b = bxcf::CString2::toNumber(parts2[2]);
			uint8 a = bxcf::CString2::toNumber(parts2[3]);
			pStyles->setStyle(prop, bxcf::CColour(r, g, b, a));
		}
		else if (prop == "line-thickness")
		{
		}
		else if (prop == "x" || prop == "y")
		{
			pStyles->setStyle(prop, CCoordinateExpression(value));
		}
		else if (prop.c_str()[0] == 'x' || prop.c_str()[0] == 'y')
		{
			pStyles->setStyle(prop, CString2::toFloat32(value));
		}
		else if (prop == "text-size")
		{
			pStyles->setStyle(prop, CString2::toNumber(value));
		}
		else
		{
			pStyles->setStyle(prop, value);
		}
	}
	return pStyles;
}

#endif