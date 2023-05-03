#pragma once
#include "my_hash_map.h"
#include "my_vector.h"
#include "structs.h"
#include "my_string.h"
#include "my_queue.h"
#include "my_double_linked_list.h"
#include "my_priority_queue.h"
#include <iostream>
#include "consts.h"
#include <cstdlib>
class Parser {
public:
	int w, h, amountOfFlights, amountOfQueries;
	int amountOfCities;
	bool wasVisitedArrayChanged;

	myVector<myVector<char>> board;
	myVector<myVector<bool>> visitedArray;
	myVector<DoubleLinkedList<City>*> citiesVector;
	myHashMap<const char*, Pair<int, DoubleLinkedList<City>*>> citiesHashMap;
	myHashMap<Pair<int, int>, const char* > citiesIndexHashMap;
public:
	Parser();

	void createDataStructures();

	void getBoard();

	void getFlights();

	void getQueries(); 

	const char* getCityName(int i, int j);

	void fillVisitedArrayWithZeros();

	DoubleLinkedList<City>* bfs(int sourceI, int sourceJ);

	Pair<int, Pair<int, myVector<int>>>  djikstra(Pair<int, DoubleLinkedList<City>*> source, Pair<int, DoubleLinkedList<City>*> dest);

	void run();

	~Parser();
};