#pragma once
#include"IXMLStockDataProvider.h"
class NasdaqXMLProvider :public IXMLStockDataProvider {
public:
	string getXMLStockInfo()override
	{
		return "<stock><symbol>APPL</symbol><price>190.5</price><timestamp>2025-05-02</timestap></stock>";
	}
	string getXMLStockHistory() override
	{
		return "<history>"
			"<entry><price>180.5</price><date>2025-04-10</date></entry>"
			"<entry><price>185.0</price><date>2025-04-20</date></entry>"
			"</history>";
	}
	std::string getXMLMetadata() override {
		return "<metadata><provider>Nasdaq</provider><market>US</market></metadata>";
	}

};
