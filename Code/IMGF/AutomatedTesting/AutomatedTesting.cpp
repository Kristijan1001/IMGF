#include "AutomatedTesting.h"
#include "Format/Image/BMP/BMPManager.h"
#include "Format/Image/BMP/BMPFormat.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

template<class Manager, class Format>
void						testFormatSerialization(string strFormatFilePath)
{
	// test parsing
	Format *pFormat = Manager::get()->parseViaFile(strFormatFilePath);
	bool bHasError = pFormat->doesHaveError();
	if(bHasError)
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_PARSE;
	}
	
	// test storing
	string strOutputFormatFilePath = "Output/" + Path::getFileName(strFormatFilePath);
	pFormat->storeViaFile(strOutputFormatFilePath);
	if(bHasError)
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_STORE;
	}
	
	// test store with file that is: stored, then parsed, then stored
	if(!File::compareFiles(strFormatFilePath, strOutputFormatFilePath))
	{
		pFormat->unload();
		delete pFormat;
		throw TESTING_COMPARE;
	}
	
	// unload
	pFormat->unload();
	delete pFormat;
}

void						AutomatedTesting::testFormatsSerialization(void)
{
	/*
	testFormatSerialization<BMPManager,		BMPFormat>			("a.bmp");
	testFormatSerialization<CCOLManager,		CCOLFormat>			("a.col");
	testFormatSerialization<CDATLoaderManager,	CDATLoaderFormat>	("a.dat");
	testFormatSerialization<CDATPathManager,	CDATPathFormat>		("a.dat");
	testFormatSerialization<DBManager,			DBFormat>			("a.db");
	testFormatSerialization<DDSManager,		DDSFormat>			("a.dds");
	testFormatSerialization<CDFFManager,		CDFFFormat>			("a.dff");
	testFormatSerialization<CIDEManager,		CIDEFormat>			("a.ide");
	testFormatSerialization<CIMGManager,		CIMGFormat>			("a.img");
	testFormatSerialization<CIPLManager,		CIPLFormat>			("a.ipl");
	testFormatSerialization<LSTManager,		LSTFormat>			("a.lst");
	testFormatSerialization<CTXDManager,		CTXDFormat>			("a.txd");
	testFormatSerialization<CWDRManager,		CWDRFormat>			("a.wdr");
	testFormatSerialization<CWTDManager,		CWTDFormat>			("a.wtd");
	*/
}