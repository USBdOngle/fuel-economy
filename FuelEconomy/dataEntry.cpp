#include "dataEntry.h"

//creates new dataEntry with assigned values from user input
dataEntry::dataEntry(int dateInput, int odoInput, double priceTotalInput, double litresInput, double pricePerLitreInput, double efficiencyInput){
	date = dateInput;
	odo = odoInput;
	priceTotal = priceTotalInput;
	litres = litresInput;
	efficiency = efficiencyInput;

	if (pricePerLitreInput != 0) { pricePerLitre = pricePerLitreInput; } //if non-zero means entry was read in from file
	else (pricePerLitre = priceTotal / litres);

}


dataEntry::~dataEntry() {}


//calculates fuel effiency for previous entry based on current odo and pushes update to file
//input: odo reading from subsequent entry
//output: 1 for success 0 for fail
void
dataEntry::updateEfficiency(dataEntry* newEntry){

	int distance = newEntry->returnOdo() - odo;
	efficiency = 100 / ((double)distance / newEntry->returnLitres());

}


//saves current data entry to end of file
//input: address of file for save data
//output: 1 for success 0 for failure
void
dataEntry::saveEntry(std::ofstream &file) {

	if (file.is_open()) {
		file << std::fixed;
		file << std::setprecision(2);
		file << date << " " << odo << " " << priceTotal << " " << litres << " " << pricePerLitre << " "; 
		file << std::setprecision(3);
		file << efficiency << "\n";
	}
}

//output: returns entry's efficiency
double
dataEntry::returnEfficiency() {
	return efficiency;
}

//output: returns entry's odo
int
dataEntry::returnOdo() {
	return odo;
}

double
dataEntry::returnPriceLitre() {
	return pricePerLitre;
}

double
dataEntry::returnLitres() {
	return litres;
}

//returns vector containing all data [date, odo, price total, litres, $/litre, efficiency]
std::vector<double>
dataEntry::returnAllData() {
	std::vector<double> allData = { (double)date, (double)odo, priceTotal, litres, pricePerLitre };
	return allData;
}