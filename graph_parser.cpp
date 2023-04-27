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
	myVector<myVector<Pair<int>>> parents;

	fillVisitedArrayWithZeros();
	int destinationX = destination.index.i, destinationY = destination.index.j;

	queue.addElementToQueue(Pair<int>(source.index.i, source.index.j));
	this->visitedArray[source.index.i][source.index.j] = 1;

	for (size_t i = 0; i < this->board.getSize(); i++) {
		myVector<Pair<int>> tempVector;
		for (size_t j = 0; j < this->board[i].getSize(); j++) {
			tempVector.push_back(Pair<int>(-1, -1));
		}
		parents.push_back(tempVector);
	}


	while (!queue.isEmpty()) {
		int size = queue.getSize();
		while (size--) {
			Pair<int> currentElement = queue.getElementFromQueue();
			int queueFirstElementIndexI = currentElement.firstValue;
			int queueFirstElementIndexJ = currentElement.secondValue;
			
			if (queueFirstElementIndexI == destinationX && queueFirstElementIndexJ == destinationY) {
				myString temp2 = "";
				Pair<int> temp = parents[destinationX][destinationY];

				while (temp.firstValue != -1 && temp.secondValue != -1) {
					if(this->board[temp.firstValue][temp.secondValue] == '2' && temp.firstValue != destinationX && temp.firstValue && source.index.i && temp.secondValue != destinationY && temp.secondValue != source.index.j)
						temp2 += findCity(temp.firstValue, temp.secondValue);
					temp = parents[temp.firstValue][temp.secondValue];
				}

				/*for (size_t i = 0; i < parents.getSize(); i++) {
					for (size_t j = 0; j < parents[i].getSize(); j++) {
						if (parents[i][j].firstValue != -1 && parents[i][j].secondValue != -1) {
							if (this->board[parents[i][j].firstValue][parents[i][j].secondValue] == '2') {
								temp += findCity(parents[i][j].firstValue, parents[i][j].secondValue);
							}
						}
					}
				}*/
				cout << steps << temp2 << endl;
				return steps;
			}

			for (size_t i = 0; i < 4; i++) {
				int newX = queueFirstElementIndexI + directions[i][0];
				int newY = queueFirstElementIndexJ + directions[i][1];

				if (newX >= 0 && newY >= 0 && newX < this->h && newY < this->w && (this->board[newX][newY] == '1' || this->board[newX][newY] == '2') && this->visitedArray[newX][newY] == 0) {
					queue.addElementToQueue(Pair<int>(newX, newY));
					this->visitedArray[newX][newY] = 1;
					parents[newX][newY] = Pair<int>(queueFirstElementIndexI, queueFirstElementIndexJ);
				}
			}
		}
		steps++;
	}

	return 0;
}

myString GraphParser::bfsPaths(City& source, City& destination) {
	int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	myQueue<Node> queue;
	fillVisitedArrayWithZeros();

	int destinationX = destination.index.i, destinationY = destination.index.j;
	queue.addElementToQueue(Node(destinationX, destinationY, ""));

	this->visitedArray[source.index.i][source.index.j] = 1;

	while (!queue.isEmpty()) {
		Node curr = queue.getElementFromQueue();
		if (curr.x == destinationX && curr.y == destinationY) {
			return curr.path;
		}
		for (size_t i = 0; i < 4; i++) {
			int newX = curr.x + directions[i][0];
			int newY = curr.y + directions[i][1];

			if (newX >= 0 && newY >= 0 && newX < this->h && newY < this->w && this->board[newX][newY] != '0' && this->visitedArray[newX][newY] == 0) {
				queue.addElementToQueue(Node(newX, newY, curr.path += findCity(newX, newY)));
				this->visitedArray[newX][newY] = 1;
			}
		}
	}
	return myString{ "" };
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

void GraphParser::printPath(myVector<int> parents, int target) {
	myVector<int> path;
	int curr = target;
	while (curr != -1) {
		path.push_back(curr);
		curr = parents[curr];
	}

	// Print the path in reverse order
	for (int i = path.getSize() - 1; i >= 0; i--) {
		cout << this->cities[path[i]];
		if (i != 0) {
			cout << " -> ";
		}
	}
	cout << endl;
}

void GraphParser::djikstra() {
	int citiesSize = this->cities.getSize();
	int minDist;
	myString temp;
	for (size_t i = 0; i < citiesSize; i++) {
		fillVisitedArrayWithZeros();
		myVector<int> distances;
		myVector<myString> shortestPath;
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
					shortestPath[secondCounter] = shortestPath[minDist] += this->cities[minDist].name += " ";
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