#include<fstream>
#include<iostream>
#include<string>
#include<list>
#include<cstdlib>
#include"dataEntry.h"

bool loadEntries(std::list<dataEntry*> &entriesPrev);

bool saveEntries(std::list<dataEntry*> &entries);