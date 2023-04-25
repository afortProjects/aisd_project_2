#include <iostream>
#include "graph_parser.h"

GraphParser::GraphParser(myVector<myVector<char>>& newBoard, int newW, int newH) : w(newW), h(newH) {
	this->board = newBoard;
	for (size_t i = 0; i < h; i++) {
		myVector<bool> tempVector;
		for (size_t j = 0; j < w; j++) {
			tempVector.push_back(0);
		}
		this->visitedArray.push_back(tempVector);
	}
}

void GraphParser::printVisitedArray() {
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			std::cout << visitedArray[i][j];
		}
		std::cout << '\n';
	}
}

void GraphParser::printBoard() {
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			std::cout << board[i][j];
		}
		std::cout << '\n';
	}
}