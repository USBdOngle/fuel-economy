#pragma once
#include "dataEntry.h"

class entryStats
{
public:

	entryStats(std::list<dataEntry*> &entries);
	~entryStats();

	void updateStats(dataEntry* newEntry, std::list<dataEntry*> &prevEntries);
	void resetStats();

	double returnEffAvg();
	int returnDistTotal();
	int returnFills();
	double returnPriceAvg();

	char* returnEffAvgS();
	char* returnDistTotalS();
	char* returnFillsS();
	char* returnPriceAvgS();

private:

	double effAvg; //average efficiency L/100km
	int distTotal; //total distance travelled km
	int fills; //total number of fills
	double priceAvg; //avg price per litre
};
