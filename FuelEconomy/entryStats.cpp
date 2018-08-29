#include "entryStats.h"

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

	if (entries.size() > 1){ effAvg = effSum / (entries.size() - 1); } //if we have 1 entry we divide by zero causing -inf
	else { effAvg = effSum; }
	
	distTotal = distLast - distFirst;
	fills = entries.size();
	priceAvg = priceSum / entries.size();

}

entryStats::~entryStats() {}

void
entryStats::updateStats(dataEntry* newEntry, std::list<dataEntry*> &prevEntries) {
	
	if (prevEntries.size() != 0) { //unable to calculate total and efficiency when there are no current entries
		distTotal += newEntry->returnOdo() - prevEntries.back()->returnOdo();
		effAvg = effAvg + ((prevEntries.back()->returnEfficiency() - effAvg) / fills);
	}

	fills++;
	priceAvg = priceAvg + ((newEntry->returnPriceLitre() - priceAvg) / fills);
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


//returns specified stat as char* (string) needed for FTLK widget labels
char*
entryStats::returnStatS(int choice) {
	//0 = eff, 1 = dist, 2 = fills, 3 = price

	std::string s;

	switch (choice) {
	case 0:
		s = std::to_string(effAvg).substr(0, 5);
		break;

	case 1:
		s = std::to_string(distTotal);
		break;

	case 2:
		s = std::to_string(fills);
		break;

	case 3:
		s = std::to_string(priceAvg).substr(0, 4);
		break;
	}

	char* c = new char[s.length() + 1]; //create room for null terminator
	strcpy_s(c, s.length() + 1, s.c_str()); //copy contents of string to new char* array
	return c;
}

//reset stats to default values
void entryStats::resetStats() {
	effAvg = 0;
	distTotal = 0;
	fills = 0;
	priceAvg = 0;
}