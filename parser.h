#pragma once
#include "my_hash_map.h"
#include "my_vector.h"
#include "structs.h"
#include "my_string.h"
#include "my_queue.h"
#include "double_linked_list.h"
#include <iostream>

class Parser {
public:
	int w, h, amountOfFlights, amountOfQueries;
	size_t amountOfCities;
	myVector<myVector<char>> board;
	myVector<Flight> flights;
	myVector<Query> queries;
	myVector<City> cities;
	myVector<myVector<int>> shortestPaths;
	myVector<myVector<myString>> shortestPathsCities;
	myVector<myVector<int>> graph;
	myVector<myVector<int>> visitedArray;
	myHashMap<const char*, City> citiesHashMap;
	myVector<DoubleLinkedList<City>> graphList;
public:
	Parser();

	void getData();

	void getBoard();

	void getFlights();

	void getQueries();

	void getCityName(int i, int j);

	void getCities();

	void fillVisitedArrayWithZeros();

	City findCity(int i, int j);

	myVector<int> bfs(City& source);

	void convertToGraph();

	void includeFlights();

	int minDistance(myVector<int>& distances, myVector<int>& visitedArr);

	void djikstra();

	void printOutput();

	~Parser();
};