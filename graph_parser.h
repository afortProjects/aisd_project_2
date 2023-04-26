#pragma once
#include "my_vector.h"
#include "structs.h"
#include "double_linked_list.h"
class GraphParser {
public:
	int w, h;
	myVector<myVector<int>> shortestPaths;
	myVector<myVector<int>> graph;
	myVector<myVector<int>> visitedArray;
	myVector<myVector<char>> board;
	myVector<City> cities;

	GraphParser();

	GraphParser(myVector<myVector<char>>& board, myVector<City> cities, int w, int h);

	void fillVisitedArrayWithZeros();

	int bfs(City& source, City& destination);

	void convertToGraph();

	int minDistance(myVector<int>& distances, myVector<int>& visitedArr);

	void djikstra();

	void printBoard();

	void printVisitedArray();

	void printGraph();

	void printGraphAfterDjikstra();
};