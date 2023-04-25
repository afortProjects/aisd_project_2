#pragma once
#include <iostream>
#include "structs.h"
#include "my_vector.h"
#include "my_string.h"
class InputParser {
public:
	int w, h;
	myVector<myVector<char>> board;
	myVector<City> cities;
public:
	void getBoard();

	void getCityName(int i, int j);

	void getCities();

	void prepareBoard();

	void printBoard();
};