#pragma once
#include "my_vector.h"
#include "structs.h"
class ResultParser {
private:
	myVector<Query> queries;
	myVector<City> cities;
	myVector<myVector<myString>> shortestPathsCities;
	myVector<myVector<int>> shortestPaths;

public:
	ResultParser(myVector<Query>& _queries, myVector<City>& cities, myVector<myVector<myString>>& _shortestPathsCities, myVector<myVector<int>>& shortestPaths);
	void printOutput();
	int getIndexOfCity(myString& cityName);

};