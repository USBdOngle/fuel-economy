#pragma once
#include<fstream>
#include<iostream>
#include "dataEntry.h"

//class that holds information for a single fuel entry
class dataEntry{

public:
	
	dataEntry(int dateInput, int odoInput, double priceTotalInput, double litresInput, double pricePerLitreInput, double efficiencyInput);
	~dataEntry();

	void updateEfficiency(dataEntry* newEntry);
	void saveEntry(std::ofstream &file);
	
	int returnOdo();
	double returnEfficiency();
	double returnPriceLitre();
	double returnLitres();




	
private:
	
	int date;			//yyyy/mm/dd
	int odo;			//current odo reading km
	double litres;		//#of litres bought
	double priceTotal; 
	double pricePerLitre;
	double efficiency = 0;   //litres/100km to be updated
	
};

