#include "DBEntry.h"
#include "Stream/DataReader.h"
#include "Stream/DataWriter.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

void				DBEntry::unserialize(void)
{
	DataReader *pDataReader = DataReader::get();

	uint32 uiEntryNameLength = pDataReader->readUint32();
	m_strEntryName = string((char*)pDataReader->readCString(uiEntryNameLength));
	m_uiEntrySize = pDataReader->readUint32();
	m_uiEntryDataCRC = pDataReader->readUint32();
	m_uiEntryCreationDate = pDataReader->readUint32();
	m_bHasIssue = (pDataReader->readUint8() & 1) == 1;
}

void				DBEntry::serialize(void)
{
	DataWriter *pDataWriter = DataWriter::get();

	pDataWriter->writeUint32(m_strEntryName.length());
	pDataWriter->writeStringRef(m_strEntryName);
	pDataWriter->writeUint32(m_uiEntrySize);
	pDataWriter->writeUint32(m_uiEntryDataCRC);
	pDataWriter->writeUint32(m_uiEntryCreationDate);
	pDataWriter->writeUint8((m_bHasIssue ? 1 : 0));
}