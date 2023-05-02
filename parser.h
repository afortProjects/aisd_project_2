#pragma once
#include "my_hash_map.h"
#include "my_vector.h"
#include "structs.h"
#include "my_string.h"
#include "my_queue.h"
#include "my_double_linked_list.h"
#include <iostream>

class Parser {
public:
	int w, h, amountOfFlights, amountOfQueries;
	size_t amountOfCities;
	bool wasVisitedArrayChanged;
	myVector<myVector<char>> board;
	myVector<Flight> flights;
	myVector<Query> queries;
	myVector<City> cities;
	myVector<myVector<int>> shortestPaths;
	myVector<myVector<myString>> shortestPathsCities;
	myVector<myVector<int>> graph;
	myVector<myVector<bool>> visitedArray;
	myHashMap<const char*, DoubleLinkedList<City>*> citiesHashMap;
	bool needToDoBfs = false;
	myVector<DoubleLinkedList<City>> graphList;
public:
	Parser();

	void createHashMap();

	void getData();

	void getBoard();

	void getFlights();

	void getQueries(); 

	const char* getCityName(int i, int j);

	void getCities();

	void fillVisitedArrayWithZeros();

	City findCity(int i, int j);

	//myVector<int> bfs(City& source);
	DoubleLinkedList<City>* bfs(int sourceI, int sourceJ);


	void convertToGraph();

	void includeFlights();

	int minDistance(myVector<int>& distances, myVector<bool>& visitedArr);

	void djikstra();

	void printOutput();

	~Parser();
};