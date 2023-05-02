#pragma once
#include "my_hash_map.h"
#include "my_vector.h"
#include "structs.h"
#include "my_string.h"
#include "my_queue.h"
#include "my_double_linked_list.h"
#include "my_priority_queue.h"
#include <iostream>

class Parser {
public:
	int w, h, amountOfFlights, amountOfQueries;
	int amountOfCities;
	bool wasVisitedArrayChanged;
	myVector<myVector<char>> board;
	myVector<myVector<bool>> visitedArray;
	myHashMap<const char*, Pair<int, DoubleLinkedList<City>*>> citiesHashMap;
	myVector<DoubleLinkedList<City>*> citiesVector;
	myHashMap<Pair<int, int>, const char* > citiesIndexHashMap;
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

	//void djikstra();
	Pair<int, myString> djikstra(Pair<int, DoubleLinkedList<City>*> source, Pair<int, DoubleLinkedList<City>*> dest);


	void printOutput();

	~Parser();
};