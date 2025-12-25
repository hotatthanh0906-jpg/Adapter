#pragma once
#include <string>
#include<vector>
using namespace std;
class IXMLStockDataProvider {
public:
	virtual~IXMLStockDataProvider() = default;
	virtual string getXMLStockHistory() = 0;
	virtual string getXMLStockInfo() = 0;
	virtual string getXMLMetadata() = 0;
};