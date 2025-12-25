#pragma once
#include<iostream>
#include <string>
using namespace std;
class AnalyticsLibraryJSON {
public:
    void analyzeStockInfoJSON(const std::string& stockJson) {
        cout << " Analyzing JSON: " << stockJson << endl;
    }

    void analyzeHistoryJSON(const std::string& historyJson) {
        cout << "Analyzing History JSON <" << historyJson << ">" << endl;
    }

    void analyzeMetadataJSON(const std::string& metadataJson) {
        cout << "Analyzing Metadata JSON (" << metadataJson << ")" << endl;
    }
};
