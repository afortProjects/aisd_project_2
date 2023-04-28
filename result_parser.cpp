#include "result_parser.h"
#include <iostream>
ResultParser::ResultParser(myVector<Query>& _queries, myVector<City>& _cities, myVector<myVector<myString>>& _shortestPathsCities, myVector<myVector<int>>& _shortestPaths) : queries(_queries), cities(_cities), shortestPathsCities(_shortestPathsCities), shortestPaths(_shortestPaths) {
}
void ResultParser::printOutput() {
	for (size_t i = 0; i < queries.getSize(); i++) {
		std::cout << this->shortestPaths[getIndexOfCity(queries[i].source)][getIndexOfCity(queries[i].destination)];
		if (queries[i].choice == 1)
			std::cout << " "<<this->shortestPathsCities[getIndexOfCity(queries[i].source)][getIndexOfCity(queries[i].destination)];
		std::cout << std::endl;
	}
}

int ResultParser::getIndexOfCity(myString& cityName) {
	for (size_t i = 0; i < cities.getSize(); i++) {
		if (cities[i].name == cityName) {
			return cities[i].indexInCityVector;
		}
	}
	return -1;
}