#pragma once
#include "my_vector.h"
#include "structs.h"
#include "double_linked_list.h"
class GraphParser {
public:
	int w, h;
	myVector<myVector<int>> shortestPaths;
	myVector<myVector<myString>> shortestPathsCities;
	myVector<myVector<int>> graph;
	myVector<myVector<int>> visitedArray;
	myVector<myVector<char>> board;
	myVector<Flight> flights;
	myVector<City> cities;

	GraphParser();

	GraphParser(myVector<myVector<char>>& board, myVector<City>& cities, myVector<Flight>& flights, int w, int h);

	void fillVisitedArrayWithZeros();

	myString findCity(int i, int j);

	myVector<int> bfs(City& source);

	int bfs(City& source, City& destination);

	void convertToGraph();
	
	int getCostOfFlight(myString& firstCityName, myString& secondCityName);

	void includeFlights();

	int minDistance(myVector<int>& distances, myVector<int>& visitedArr);

	void djikstra();

	void printBoard();

	void printVisitedArray();

	void printGraph();

	void printGraphAfterDjikstra();

	void printPaths();
};