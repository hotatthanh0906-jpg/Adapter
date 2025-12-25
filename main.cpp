#include "NasdaqXMLProvider.h"
#include "StockDataAdapter.h"
#include "AnalyticsLibraryJSON.h"

int main() {
    NasdaqXMLProvider provider;
    AnalyticsLibraryJSON analytics;

    StockDataAdapter adapter(&provider, &analytics);

    adapter.processStockInfo();
    adapter.processHistory();
    adapter.processMetadata();

    return 0;
}
