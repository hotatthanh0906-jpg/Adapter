#pragma once
#pragma once
#include "IXMLStockDataProvider.h"
#include "AnalyticsLibraryJSON.h"
#include <string>
#include<sstream>
// Interface(tarhet)
class IStockAnalytics {
public:
    virtual ~IStockAnalytics() = default;
    virtual void processStockInfo() = 0;
    virtual void processHistory() = 0;
    virtual void processMetadata() = 0;
};
//////////////////////////
class StockDataAdapter :public IStockAnalytics {
private:
    IXMLStockDataProvider* provider;
    AnalyticsLibraryJSON* analytics;

public:
    StockDataAdapter(IXMLStockDataProvider* p, AnalyticsLibraryJSON* a)
        : provider(p), analytics(a) {}

  

private:
    std::string convertStockInfoXMLToJSON(const std::string& xml)
    {
        
        std::string json = "{";
        auto pos1 = xml.find("<symbol>");
        auto pos2 = xml.find("</symbol>");
        json += "\"symbol\":\"" + xml.substr(pos1 + 8, pos2 - pos1 - 8) + "\",";

        pos1 = xml.find("<price>");
        pos2 = xml.find("</price>");
        json += "\"price\":" + xml.substr(pos1 + 7, pos2 - pos1 - 7) + ",";

        pos1 = xml.find("<timestamp>");
        pos2 = xml.find("</timestamp>");
        json += "\"timestamp\":\"" + xml.substr(pos1 + 11, pos2 - pos1 - 11) + "\"";

        json += "}";
        return json;
    }
    std::string convertHistoryXMLToJSON(const std::string& xml) {
        std::string json = "[";
        size_t pos = 0;
        while ((pos = xml.find("<entry>", pos)) != std::string::npos) {
            size_t end = xml.find("</entry>", pos);
            std::string entry = xml.substr(pos, end - pos);
            size_t p1 = entry.find("<price>");
            size_t p2 = entry.find("</price>");
            std::string price = entry.substr(p1 + 7, p2 - p1 - 7);

            p1 = entry.find("<date>");
            p2 = entry.find("</date>");
            std::string date = entry.substr(p1 + 6, p2 - p1 - 6);

            json += "{\"price\":" + price + ",\"date\":\"" + date + "\"},";
            pos = end + 7;
        }
        if (json.back() == ',') json.pop_back();
        json += "]";
        return json;
    }
    std::string convertMetadataXMLToJSON(const std::string& xml)
    {
        std::string json = "{";
        size_t pos1 = xml.find("<provider>");
        size_t pos2 = xml.find("</provider>");
        json += "\"provider\":\"" + xml.substr(pos1 + 10, pos2 - pos1 - 10) + "\",";

        pos1 = xml.find("<market>");
        pos2 = xml.find("</market>");
        json += "\"market\":\"" + xml.substr(pos1 + 8, pos2 - pos1 - 8) + "\"";

        json += "}";
        return json;
    }

public:
    void processStockInfo() override {
        std::string xml = provider->getXMLStockInfo();
        std::string json = convertStockInfoXMLToJSON(xml);
        analytics->analyzeStockInfoJSON(json);
    }

    void processHistory() override {
        std::string xml = provider->getXMLStockHistory();
        std::string json = convertHistoryXMLToJSON(xml);
        analytics->analyzeHistoryJSON(json);
    }

    void processMetadata() override {
        std::string xml = provider->getXMLMetadata();
        std::string json = convertMetadataXMLToJSON(xml);
        analytics->analyzeMetadataJSON(json);
    }
};
