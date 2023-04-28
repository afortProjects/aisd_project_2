#pragma once
#include <iostream>
#include "structs.h"
#include "my_vector.h"
#include "my_string.h"
class InputParser {
public:
	int w, h, amountOfFlights, amountOfQueries;
	myVector<myVector<char>> board;
	myVector<City> cities;
	myVector<Flight> flights;
	myVector<Query> queries;

public:
	void getData();

	void getBoard();

	void getFlights();

	void getQueries();

	void getCityName(int i, int j);

	void getCities();

	void prepareBoard();

	void printBoard();
};