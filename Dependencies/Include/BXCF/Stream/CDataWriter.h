#ifndef CDataWriter_H
#define CDataWriter_H

#include "bxcf.h"
#include "CDataStream.h"
#include "Object/CIndexedInstance.h"
#include "Type/Types.h"
#include "eDataStreamType.h"
#include "Unit/Byte/eEndian.h"
#include "Type/Vector/CVector2D.h"
#include "Type/Vector/CVector3D.h"
#include "Type/Vector/CVector4D.h"
#include "Type/Vector/CVector2ui8.h"
#include "Type/Vector/CVector2ui32.h"
#include "Type/Vector/CVector3ui8.h"
#include "Type/Vector/CVector3ui32.h"
#include "Type/Vector/CVector4ui8.h"
#include "Type/Vector/CVector4ui16.h"
#include "Type/Vector/CPoint2D.h"
#include "Type/Vector/CSize2D.h"
#include "Pool/CVectorPool.h"
#include <string>
#include <vector>
#include <fstream>

class bxcf::CDataWriter;

class bxcf::CDataWriter : public bxcf::CDataStream, public bxcf::CIndexedInstance<bxcf::CDataWriter>
{
public:
	CDataWriter(void);

	// reset
	void					close(bool bHasError = false);
	void					reset(bool bHasError = false);
	void					resetData(void);

	// file processing
	void					openFile(std::string& strFilePath, uint32 uiFlags);
	bool					isFileOpen(void);
	void					resetFile(void);

	// write string
	void					writeStringRef(std::string& strData);
	void					writeStringRef(std::string& strData, uint32 uiTotalByteCountPadded);
	void					writeString(std::string strData);
	void					writeString(std::string strData, uint32 uiTotalByteCountPadded);
	void					writeString(uint32 uiZeroByteCount);
	void					writeStringWithLengthRef(std::string& strData);
	void					writeStringWithLength(std::string strData);
	void					writeCString(char *pData, uint32 uiByteCount);

	// write int
	void					writeUint8(uint8 uiInt);
	void					writeUint16(uint16 uiInt);
	void					writeUint32(uint32 uiInt);
	void					writeUint64(uint64 uiInt);
	void					writeInt8(int8 iInt);
	void					writeInt16(int16 iInt);
	void					writeInt32(int32 iInt);
	void					writeInt64(int64 iInt);
	void					writePoint2D(bxcf::CPoint2D& vecPoint);
	void					writeVector2i32(bxcf::CVector2i32& vecUints);
	void					writeSize2D(bxcf::CSize2D& vecSize);
	void					writeVector2ui8(bxcf::CVector2ui8& vecUints);
	void					writeVector2ui32(bxcf::CVector2ui32& vecUints);
	void					writeVector3ui8(bxcf::CVector3ui8& vecUints);
	void					writeVector3ui32(bxcf::CVector3ui32& vecUints);
	void					writeVector4ui8(bxcf::CVector4ui8& vecUints);
	void					writeStdVectorUint32(std::vector<uint32>& vecUints);
	void					writeStdVector4ui8(std::vector<bxcf::CVector4ui8>& vecVectors);
	void					writeStdVector4ui16(std::vector<CVector4ui16>& vecVectors);

	// write float
	void					writeFloat32(float32 fFloat);
	void					writeFloat64(float64 fFloat);
	void					writeVector2D(bxcf::CVector2D& vecVector);
	void					writeVector3D(bxcf::CVector3D& vecVector);
	void					writeVector4D(bxcf::CVector4D& vecVector);
	void					writeStdVector2D(std::vector<bxcf::CVector2D>& vecVectors);
	void					writeStdVector3D(std::vector<bxcf::CVector3D>& vecVectors);
	void					writeStdVector4D(std::vector<bxcf::CVector4D>& vecVectors);

	// write token
	void					writeTokenString(std::string& strString);
	void					writeTokenInt32(int32 iInt);
	void					writeTokenUint32(uint32 uiInt);
	void					writeTokenFloat32(float32 fFloat);
	void					writeTokenVector2D(bxcf::CVector2D& vecVector);
	void					writeTokenVector3D(bxcf::CVector3D& vecVector);
	void					writeTokenVector4D(bxcf::CVector4D& vecVector);

	// write string - type guessed
	void					write(std::string& strData);
	void					write(std::string& strData, uint32 uiTotalByteCountPadded);
	void					write(char *pData, uint32 uiByteCount);

	// write int - type guessed
	void					write(uint8 uiInt);
	void					write(uint16 uiInt);
	void					write(uint32 uiInt);
	void					write(uint64 uiInt);
	void					write(int8 iInt);
	void					write(int16 iInt);
	void					write(int32 iInt);
	void					write(int64 iInt);
	void					write(bxcf::CPoint2D& vecPoint);
	void					write(bxcf::CSize2D& vecSize);
	void					write(bxcf::CVector4ui8& vecUints);
	void					write(std::vector<uint32>& vecUints);
	void					write(std::vector<bxcf::CVector2D>& vecVectors);
	void					write(std::vector<bxcf::CVector3D>& vecVectors);
	void					write(std::vector<bxcf::CVector4ui8>& vecVectors);
	void					write(std::vector<bxcf::CVector4ui16>& vecVectors);

	// write float - type guessed
	void					write(float32 fFloat);
	void					write(float64 fFloat);
	void					write(bxcf::CVector2D& vecVector);
	void					write(bxcf::CVector3D& vecVector);
	void					write(bxcf::CVector4D& vecVector);

	// write token - type guessed
	void					writeToken(std::string& strString);
	void					writeToken(int32 iInt);
	void					writeToken(uint32 uiInt);
	void					writeToken(float32 fFloat);
	void					writeToken(bxcf::CVector2D& vecVector);
	void					writeToken(bxcf::CVector3D& vecVector);
	void					writeToken(bxcf::CVector4D& vecVector);

	template <class DerivedFormatClass>
	void					writeLineEntries(bxcf::CVectorPool<DerivedFormatClass> *pPool);
	template <class SectionClass, class EntryClass>
	void					writeSectionLineEntries(bxcf::CVectorPool<SectionClass> *pPool);

	// write struct
	void					write(CDataWriter& pDataWriter);

	// write raw struct
	template <class T>
	void					writeStruct(T& object)
	{
		write(&object, sizeof(T));
	}
	
	// replace
	void					replace(uint32 uiByteIndex, std::string& strData);

	// seek
	void					setSeek(uint64 uiByteIndex);
	uint64					getSeek(void);

	// file mode only
	std::ofstream&			getFile(void) { return m_file; }

	void					setTemporaryFilePath(std::string& strTemporaryFilePath) { m_strTemporaryFilePath = strTemporaryFilePath; }
	std::string&			getTemporaryFilePath(void) { return m_strTemporaryFilePath; }

	std::string				generateTemporaryFilePath(std::string& strFilePath);

private:
	static std::vector<CDataWriter*>	m_vecDataWriters;
	std::ofstream			m_file;
	std::string				m_strTemporaryFilePath;
};

template<class DerivedFormatClass>
void						bxcf::CDataWriter::writeLineEntries(bxcf::CVectorPool<DerivedFormatClass> *pPool)
{
	CDataWriter *pDataWriter = CDataWriter::getInstance();

	for (DerivedFormatClass *pEntry : pPool->getEntries())
	{
		pEntry->serialize();
		pDataWriter->writeString("\n");
	}
}

template <class SectionClass, class EntryClass>
void						bxcf::CDataWriter::writeSectionLineEntries(bxcf::CVectorPool<SectionClass> *pPool)
{
	CDataWriter *pDataWriter = CDataWriter::getInstance();

	for (SectionClass *pSection : pPool->getEntries())
	{
		pSection->serialize();
		pDataWriter->writeString("\n");

		for (EntryClass *pEntry : pSection->getEntries())
		{
			pEntry->serialize();
			pDataWriter->writeString("\n");
		}

		pDataWriter->writeString("end\n");
	}
}

#endif