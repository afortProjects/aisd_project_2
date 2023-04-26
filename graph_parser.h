#pragma once
#include "my_vector.h"
#include "structs.h"
#include "double_linked_list.h"
class GraphParser {
public:
	int w, h;
	myVector<myVector<CityNode>> graph;
	myVector<myVector<bool>> visitedArray;
	myVector<myVector<char>> board;

	GraphParser();

	GraphParser(myVector<myVector<char>>& board, int w, int h);

	void convertToGraph();

	void printBoard();

	void printVisitedArray();
};