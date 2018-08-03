#include<list>
#include<string>
#include "entryStats.h"
#include "dataEntry.h"

entryStats::entryStats(std::list<dataEntry*> &entries) {

	//if no entries are recorded then stats should default to zero
	if (entries.size() == 0) {
		effAvg = 0;
		distTotal = 0;
		fills = 0;
		priceAvg = 0;
		return;
	}
	
	double effSum = 0; //stores summation of all efficiency values
	int distFirst = 0; //first odo value
	int distLast = 0;	//last odo value
	double priceSum = 0; //summation of all pricePerLitre values

						 //iterates through and collects data from first to second last entry in list
	for (std::list<dataEntry*>::iterator entry = entries.begin(); entry != entries.end(); ++entry) {

		effSum += (*entry)->returnEfficiency();
		priceSum += (*entry)->returnPriceLitre();

		if (*entry == entries.front()) {
			distFirst = (*entry)->returnOdo();
		}

		if (*entry == entries.back()) {
			distLast = (*entry)->returnOdo();
		}
	}

	effAvg = effSum / (entries.size() - 1);
	distTotal = distLast - distFirst;
	fills = entries.size();
	priceAvg = priceSum / entries.size();

}

entryStats::~entryStats() {}

void
entryStats::updateStats(dataEntry* newEntry, std::list<dataEntry*> &prevEntries) {
	
	if (prevEntries.size() != 0) {
		distTotal += newEntry->returnOdo() - prevEntries.back()->returnOdo();
		effAvg = effAvg + ((prevEntries.back()->returnEfficiency() - effAvg) / fills);
	}

	priceAvg = ((priceAvg * fills) + newEntry->returnPriceLitre()) / (fills + 1);
	fills++;
}

double
entryStats::returnEffAvg() {
	return effAvg;
}

int
entryStats::returnDistTotal() {
	return distTotal;
}

int
entryStats::returnFills() {
	return fills;
}

double
entryStats::returnPriceAvg() {
	return priceAvg;
}

char*
entryStats::returnEffAvgS() {

	std::string s = std::to_string(effAvg).substr(0, 5);
	char* c = new char[s.length() + 1]; //create room for null terminator
	strcpy_s(c, s.length()+1, s.c_str()); //copy contents of string to new char* array
	return c;
}

char*
entryStats::returnDistTotalS() {
	std::string s = std::to_string(distTotal);
	char* c = new char[s.length() + 1]; //create room for null terminator
	strcpy_s(c, s.length()+1, s.c_str()); //copy contents of string to new char* array
	return c;
}

char*
entryStats::returnFillsS() {
	std::string s = std::to_string(fills);
	char* c = new char[s.length() + 1]; //create room for null terminator
	strcpy_s(c, s.length()+1, s.c_str()); //copy contents of string to new char* array
	return c;
}

char*
entryStats::returnPriceAvgS() {
	std::string s = std::to_string(priceAvg).substr(0,4);
	char* c = new char[s.length() + 1]; //create room for null terminator
	strcpy_s(c, s.length()+1, s.c_str()); //copy contents of string to new char* array
	return c;		//reduces values to two decimal points
}

//reset stats to default values
void entryStats::resetStats() {
	effAvg = 0;
	distTotal = 0;
	fills = 0;
	priceAvg = 0;
}