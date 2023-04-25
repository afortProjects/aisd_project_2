#pragma once
#include "my_vector.h"
class GraphParser {
public:
	myVector<myVector<bool>> visitedArray;
	myVector<myVector<char>> board;
	int w, h;

	GraphParser();

	GraphParser(myVector<myVector<char>>& board, int w, int h);

	void printBoard();

	void printVisitedArray();
};