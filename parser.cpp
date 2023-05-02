#include "parser.h"
#include <iostream>
#include <string>
#include "consts.h"
#include <cstdlib>
#define TABLE_SIZE 1000
Parser::Parser() {
	this->amountOfCities = 0;
	this->amountOfQueries = 0;
	this->amountOfFlights = 0;
	this->h = 0;
	this->w = 0;
	this->wasVisitedArrayChanged = false;
}

void Parser::getBoard() {
	char inputCharacter;
	scanf("%d%d", &w, &h);
	inputCharacter = getchar();

	for (size_t i = 0; i < h; i++) {
		myVector<char> tempVector;
		for (size_t j = 0; j < w; j++) {
			inputCharacter = getchar();
			tempVector.push_back(inputCharacter);
			if (inputCharacter == '#') needToDoBfs = true;
		}
		inputCharacter = getchar();
		board.push_back(tempVector);
	}
}

void Parser::getFlights() {
	scanf("%d", &amountOfFlights);
	getchar();


	for (int i = 0; i < amountOfFlights; i++) {
		//tempSource = "";
		//tempDestination = "";
		char* source = new char[64];
		char* destination = new char[64];
		int counter = 0;
		//myVector<char>tempDestination;
		int cost = 0;

		char character = getchar();
		while (character != ' ') {
			source[counter] = character;
			character = getchar();
			counter++;
		}
		source[counter] = '\0';
		counter = 0;
		character = getchar();
		while (character != ' ') {
			destination[counter] = character;
			character = getchar();
			counter++;
		}
		destination[counter] = '\0';

		scanf("%d", &cost); 
		getchar();

		DoubleLinkedList<City>* currentList = this->citiesHashMap[source];
		Node<City>* headNode = currentList->getHead();
		bool isNeighbour = false;

		while (headNode != nullptr) {
			if (headNode->value.index.firstValue == this->citiesHashMap[destination]->getHead()->value.index.firstValue && headNode->value.index.secondValue == this->citiesHashMap[destination]->getHead()->value.index.secondValue) {
				//Element is a neighbour
				if (headNode->value.cost > cost) {
					headNode->value.cost = cost;
					isNeighbour = true;
					break;
				}
			}
			headNode = headNode->next;
		}
		if (!isNeighbour) {
			currentList->addLast(City{ this->citiesHashMap[destination]->getHead()->value.index.firstValue, this->citiesHashMap[destination]->getHead()->value.index.secondValue, cost });
		}
		delete[] source;
		delete[] destination;
	}
}

void Parser::getQueries() {
	scanf("%d", &amountOfQueries);
	getchar();

	myString temp = "";
	myString tempSource = "";
	myString tempDestination = "";
	int choice = 0;
	char character;

	for (size_t i = 0; i < this->amountOfQueries; i++) {
		temp = "";
		tempSource = "";
		tempDestination = "";
		choice = 0;
		character = getchar();

		while (character != '\n') {
			if (character == ' ') {
				if (tempSource.length() == 0) tempSource = temp;
				else if (tempDestination.length() == 0) tempDestination = temp;
				temp = "";
			}
			else
				temp += character;
			character = getchar();
		}
		choice = atoi(temp.str());
		this->queries.push_back(Query(tempSource, tempDestination, choice));
	}
}

const char* Parser::getCityName(int i, int j) {
	//Check where is first character
	myString cityName = "";
	//char* buffer = new char[STRING_BUFFER];
	//char buffer[STRING_BUFFER];
	//std::string cityName;
	int counter = 0;
	for (int a = i - 1; a <= i + 1; a++) {
		for (int b = j - 1; b <= j + 1; b++) {

			//Check if in board
			if (a < 0 || a > h - 1 || b < 0 || b > w - 1) {
				continue;
			}

			if (a == i && b == j) {
				continue;
			}

			if (isalpha(this->board[a][b]) || isdigit(this->board[a][b])) {

				int counterX = b;
				cityName += this->board[a][b];
				//buffer[counter] = this->board[a][b];
				counter++;
				//We have a first character, now we need to check, in which direction it goes
				if (b > 0 && isalpha(this->board[a][b - 1])) {
					//Check if we really took last/first letter
					if (b < this->w - 1 && (isalpha(this->board[a][b + 1]) || isdigit(this->board[a][b + 1]))) {
						cityName = "";
						//counter = 0;
						continue;
					}

					counterX--;
					while (isalpha(this->board[a][counterX]) || isdigit(this->board[a][counterX])) {
						cityName += this->board[a][counterX];
						//buffer[counter] = this->board[a][counterX];
						counter++;
						counterX--;
						if (counterX < 0) break;

					}
					cityName.reverse();
					//std::string.reverse();
					/*int len = strlen(buffer);
					for (int i = 0; i < len / 2; i++) {
						char temp = buffer[i];
						buffer[i] = buffer[len - 1 - i];
						buffer[len - 1 - i] = temp;
					}*/
				}

				else if (b + 1 < this->w && (isalpha(this->board[a][b + 1]) || isdigit(this->board[a][b + 1]))) {
					//Check if we really took last/first letter
					if (b > 0 && (isalpha(this->board[a][b - 1]) || isdigit(this->board[a][b - 1]))) {
						//cityName = "";
						cityName = "";
						counter = 0;
						continue;
					}

					counterX++;
					while (isalpha(this->board[a][counterX]) || isdigit(this->board[a][counterX])) {
						cityName += this->board[a][counterX];
						//buffer[counter] = this->board[a][counterX];
						counterX++;
						counter++;
						if (counterX > this->w - 1) break;
					}

				}
				//buffer[counter] = '\0';
				char* a = new char[cityName.length()+1];
				strcpy_s(a, cityName.length()+1, cityName.str());
	/*			for (size_t i = 0; i < cityName.length()+1; i++) {
					a[i] = cityName[i];
				}*/
				//a[cityName.length()] = '\0';
				return a;
				//City newCity = { i, j, a, c};
				//this->citiesHashMap.add(cityName.str(), newCity);
				//this->cities.push_back(newCity);
				//this->amountOfCities += 1;
				//return;
			}

		}
	}
	//delete[] buffer;


}

void Parser::createHashMap() {
	getBoard();
	fillVisitedArrayWithZeros();
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			if (this->board[i][j] == '*') {
				//const char* cityName = ;
				DoubleLinkedList<City>* adjencies = bfs(i, j);
 				this->citiesHashMap.add(getCityName(i, j), adjencies);
			}
		}
	}
	getFlights();
}

void Parser::fillVisitedArrayWithZeros() {
	myVector<myVector<bool>> newVisitedArray;
	for (size_t i = 0; i < this->h; i++) {
		myVector<bool> tempVector;
		for (size_t j = 0; j < this->w; j++) {
			tempVector.push_back(false);
		}
		newVisitedArray.push_back(tempVector);
	}
	this->visitedArray = newVisitedArray;
}

DoubleLinkedList<City>* Parser::bfs(int sourceI, int sourceJ) {
	int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	myQueue<City> queue;

	int queueFirstElementIndexI;
	int queueFirstElementIndexJ;

	DoubleLinkedList<City>* adjencies = new DoubleLinkedList<City>;
	adjencies->addFirst(City{ sourceI, sourceJ });

	if (this->wasVisitedArrayChanged) {
		for (size_t i = 0; i < this->visitedArray.getSize(); i++) {
			for (size_t j = 0; j < visitedArray[i].getSize(); j++) {
				this->visitedArray[i][j] = false;
			}
		}
	}
	
	queue.addElementToQueue(City{ sourceI, sourceJ, 0 });
	this->visitedArray[sourceI][sourceJ] = true;

	while (!queue.isEmpty()) {
		City currentElement = queue.getElementFromQueue();
		queueFirstElementIndexI = currentElement.index.firstValue;
		queueFirstElementIndexJ = currentElement.index.secondValue;
		int newX, newY;

		for (size_t i = 0; i < 4; i++) {
			newX = queueFirstElementIndexI + directions[i][0];
			newY = queueFirstElementIndexJ + directions[i][1];


			if (newX >= 0 && newY >= 0 && newX < this->h && newY < this->w && this->visitedArray[newX][newY] == false) {
				if ((this->board[newX][newY] == '#')) {
					queue.addElementToQueue(City{ newX, newY, currentElement.cost + 1 });
					this->visitedArray[newX][newY] = true;
					this->wasVisitedArrayChanged = true;
				}
				else if (this->board[newX][newY] == '*' && (newX != sourceI || newY != sourceJ)) {
					//TODO: MAKE SURE IT WORKS
					adjencies->addLast(City{ newX, newY, currentElement.cost + 1 });
					this->visitedArray[newX][newY] = true;
					this->wasVisitedArrayChanged = true;
				}
			}
		}
	}
	this->visitedArray[sourceI][sourceJ] = false;
	return adjencies;
}

//void Parser::includeFlights() {
//	for (size_t i = 0; i < this->flights.getSize(); i++) {
//		int first = this->citiesHashMap[this->flights[i].source].indexInCityVector;
//		int second = this->citiesHashMap[this->flights[i].destination].indexInCityVector;
//		if ((this->graph[first][second] > this->flights[i].cost || graph[first][second] == 0)) {
//			graph[first][second] = this->flights[i].cost;
//		}
//	}
//}
//
//int Parser::minDistance(myVector<int>& distances, myVector<bool>& visitedArr) {
//	int min = INT_MAX;
//	int min_index = 0;
//
//	for (int v = 0; v < this->cities.getSize(); v++) {
//		if (visitedArr[v] == 0 && distances[v] <= min) {
//			min = distances[v];
//			min_index = v;
//		}
//	}
//	return min_index;
//}
//void Parser::djikstra() {
//	int citiesSize = this->cities.getSize();
//	int minDist;
//	myString temp;
//	fillVisitedArrayWithZeros();
//	for (size_t i = 0; i < citiesSize; i++) {
//		myVector<int> distances;
//		myVector<myString> shortestPath;
//		myString temp = "";
//		for (size_t j = 0; j < citiesSize; j++) {
//			distances.push_back(INT_MAX);
//			shortestPath.push_back("");
//		}
//
//		distances[i] = 0;
//
//		for (size_t counter = 0; counter < citiesSize - 1; counter++) {
//			minDist = minDistance(distances, this->visitedArray[i]);
//			this->visitedArray[i][minDist] = 1;
//			for (size_t secondCounter = 0; secondCounter < citiesSize; secondCounter++) {
//				if (!this->visitedArray[i][secondCounter] && this->graph[minDist][secondCounter] != 0 && distances[minDist] != INT_MAX && distances[minDist] + this->graph[minDist][secondCounter] < distances[secondCounter]) {
//					distances[secondCounter] = distances[minDist] + this->graph[minDist][secondCounter];
//					if (this->cities[minDist].name != this->cities[i].name) {
//						temp = shortestPath[minDist];
//						if (strlen(this->cities[minDist].name) != 0) {
//							temp += this->cities[minDist].name;
//							temp += " ";
//						}
//					}
//					shortestPath[secondCounter] = temp;
//				}
//			}
//		}
//		this->shortestPaths.push_back(distances);
//		this->shortestPathsCities.push_back(shortestPath);
//	}
//}
//
//void Parser::printOutput() {
//	for (size_t i = 0; i < queries.getSize(); i++) {
//		const char* src = queries[i].source.str();
//		const char* dest = queries[i].destination.str();
//		size_t srcIndex = this->citiesHashMap[src].indexInCityVector;
//		size_t destIndex = this->citiesHashMap[dest].indexInCityVector;
//
//		std::cout << this->shortestPaths[(this->citiesHashMap[src].indexInCityVector)][(this->citiesHashMap[dest].indexInCityVector)];
//		if (queries[i].choice == 1) {
//			std::cout << " " << this->shortestPathsCities[this->citiesHashMap[src].indexInCityVector][this->citiesHashMap[dest].indexInCityVector];
//		}
//		std::cout << std::endl;
//	}
//}

Parser::~Parser() {}