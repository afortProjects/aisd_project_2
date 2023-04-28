#include <iostream>
#include "graph_parser.h"
#include "my_queue.h"
#include <stack>
GraphParser::GraphParser() {
	this->h = 0;
	this->w = 0;
}

GraphParser::GraphParser(myVector<myVector<char>>& newBoard, myVector<City> newCities, int newW, int newH) : w(newW), h(newH) {
	this->board = newBoard;
	this->cities = newCities;
	fillVisitedArrayWithZeros();
}

myString GraphParser::findCity(int i, int j) {
	for (size_t m = 0; m < this->cities.getSize(); m++) {
		if (this->cities[m].index.i == i && this->cities[m].index.j == j)
			return this->cities[m].name;
	}
	return "";
}


int GraphParser::bfs(City& source, City& destination) {
	int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	int steps = 0;
	myQueue<Pair<int>> queue;
	myVector<myVector<int>> paths;
	

	fillVisitedArrayWithZeros();
	int destinationX = destination.index.i, destinationY = destination.index.j;

	for (size_t i = 0; i < this->board.getSize(); i++) {
		myVector<int> tempVector;
		for (size_t j = 0; j < this->board[i].getSize(); j++) {
			tempVector.push_back(0);
		}
		paths.push_back(tempVector);
	}

	queue.addElementToQueue(Pair<int>(source.index.i, source.index.j));
	this->visitedArray[source.index.i][source.index.j] = 1;

	while (!queue.isEmpty()) {
		int size = queue.getSize();
		while (size--) {
			Pair<int> currentElement = queue.getElementFromQueue();
			int queueFirstElementIndexI = currentElement.firstValue;
			int queueFirstElementIndexJ = currentElement.secondValue;

			for (size_t i = 0; i < 4; i++) {
				int newX = queueFirstElementIndexI + directions[i][0];
				int newY = queueFirstElementIndexJ + directions[i][1];

				if (newX >= 0 && newY >= 0 && newX < this->h && newY < this->w) {
					if ((this->board[newX][newY] == '1') && this->visitedArray[newX][newY] == 0) {
						queue.addElementToQueue(Pair<int>(newX, newY));
						this->visitedArray[newX][newY] = 1;
					}
					else if (newX >= 0 && newY >= 0 && newX < this->h && newY < this->w && this->board[newX][newY] == '2' && newX == destination.index.i && newY == destinationY) {
						return steps + 1;
					}
				}
			}
		}
		steps++;
	}
	return 0;

}

void GraphParser::fillVisitedArrayWithZeros() {
	myVector<myVector<int>> newVisitedArray;
	for (size_t i = 0; i < this->h; i++) {
		myVector<int> tempVector;
		for (size_t j = 0; j < this->w; j++) {
			tempVector.push_back(0);
		}
		newVisitedArray.push_back(tempVector);
	}
	this->visitedArray = newVisitedArray;
}

void GraphParser::convertToGraph() {
	int steps = 0;
	myString path = "";
	for (size_t i = 0; i < cities.getSize(); i++) {
		myVector<int> tempVector;
		for (size_t j = 0; j < cities.getSize(); j++) {
			if (i == j)
				tempVector.push_back(0);
			else {
				steps = bfs(this->cities[i], this->cities[j]);
				tempVector.push_back(steps);
			}
		}
		this->graph.push_back(tempVector);
	}
}

int GraphParser::minDistance(myVector<int>& distances, myVector<int>& visitedArr) {
	int min = INT_MAX;
	int min_index = 0;

	for (int v = 0; v < this->cities.getSize(); v++) {
		if (visitedArr[v] == 0 && distances[v] <= min) {
			min = distances[v];
			min_index = v;
		}
	}
	return min_index;
}

void GraphParser::djikstra() {
	int citiesSize = this->cities.getSize();
	int minDist;
	myString temp;
	for (size_t i = 0; i < citiesSize; i++) {
		fillVisitedArrayWithZeros();
		myVector<int> distances;
		myVector<myString> shortestPath;
		myString temp = "";
		for (size_t j = 0; j < citiesSize; j++) {
			distances.push_back(INT_MAX);
			shortestPath.push_back("");
		}
		
		distances[i] = 0;

		for (size_t counter = 0; counter < citiesSize - 1; counter++) {
			minDist = minDistance(distances, this->visitedArray[i]);
			this->visitedArray[i][minDist] = 1;
			for (size_t secondCounter = 0; secondCounter < citiesSize; secondCounter++) {
				if (!this->visitedArray[i][secondCounter] && this->graph[minDist][secondCounter] != 0 && distances[minDist] != INT_MAX && distances[minDist] + this->graph[minDist][secondCounter] < distances[secondCounter]) {
					distances[secondCounter] = distances[minDist] + this->graph[minDist][secondCounter];
					if (this->cities[minDist].name != this->cities[i].name) {
						temp = shortestPath[minDist];
						if (this->cities[minDist].name.length() != 0) {
							temp += this->cities[minDist].name;
							temp += " ";
						}
					}
						shortestPath[secondCounter] = temp;
				}
			}
		}
		this->shortestPaths.push_back(distances);
		this->shortestPathsCities.push_back(shortestPath);
	}
}

void GraphParser::printGraph() {
	for (size_t i = 0; i < this->graph.getSize(); i++) {
		for (size_t j = 0; j < this->graph[0].getSize(); j++) {
			std::cout << this->graph[i][j] << " ";
		}
		std::cout << '\n';
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

void GraphParser::printGraphAfterDjikstra() {
	for (size_t i = 0; i < this->cities.getSize(); i++) {
		for (size_t j = 0; j < this->cities.getSize(); j++) {
			std::cout << this->shortestPaths[i][j] << " ";
		}
		std::cout << '\n';
	}
}

void GraphParser::printPaths() {
	for (size_t i = 0; i < this->cities.getSize(); i++) {
		for (size_t j = 0; j < this->cities.getSize(); j++) {
			std::cout << this->shortestPathsCities[i][j] << " ";
		}
		std::cout << '\n';
	}
}