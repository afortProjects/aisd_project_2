#include "parser.h"

Parser::Parser() {
	this->amountOfCities = 0;
	this->amountOfQueries = 0;
	this->amountOfFlights = 0;
	this->h = 0;
	this->w = 0;
	this->wasVisitedArrayChanged = false;
	this->areThereRoads = false;
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
			if (inputCharacter == '#') {
				areThereRoads = true;
			}
		}
		inputCharacter = getchar();
		board.push_back(tempVector);
	}
}

void Parser::getFlights() {
	scanf("%d", &amountOfFlights);
	getchar();


	for (int i = 0; i < amountOfFlights; i++) {
		char* source = new char[BUFFER_SIZE];
		char* destination = new char[BUFFER_SIZE];
		char* cost = new char[BUFFER_SIZE];
		int counter = 0;

		char character = _getchar_nolock();
		while (character != ' ') {
			source[counter] = character;
			character = getchar();
			counter++;
		}

		source[counter] = '\0';
		counter = 0;
		character = _getchar_nolock();
		while (character != ' ') {
			destination[counter] = character;
			character = _getchar_nolock();
			counter++;
		}

		destination[counter] = '\0';
		counter = 0;
		character = _getchar_nolock();
		while (character != '\n') {
			cost[counter] = character;
			character = _getchar_nolock();
			counter++;
		}
		cost[counter] = '\0';

		DoubleLinkedList<City>* currentList = citiesHashMap[source].secondValue;
		currentList->addLast(City{ citiesHashMap[destination].secondValue->getHead()->value.index.firstValue, citiesHashMap[destination].secondValue->getHead()->value.index.secondValue, atoi(cost) });

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
		character = _getchar_nolock();

		while (character != '\n') {
			if (character == ' ') {
				if (tempSource.length() == 0) tempSource = temp;
				else if (tempDestination.length() == 0) tempDestination = temp;
				temp = "";
			}
			else
				temp += character;
			character = _getchar_nolock();
		}
		choice = atoi(temp.str());

		Pair<int, Pair<int, myVector<int>>> temp = djikstra(citiesHashMap[tempSource.str()], citiesHashMap[tempDestination.str()]);
		std::cout << temp.firstValue << " ";

		if (choice == 1) {
			int counter = temp.secondValue.firstValue;
			myVector<const char*> reconstructedPath;
			while (counter != -1) {
				if (counter != temp.secondValue.firstValue) {
					Pair<int, int> indexOfFoundCity{ citiesVector[counter]->getHead()->value.index.firstValue, citiesVector[counter]->getHead()->value.index.secondValue };
					reconstructedPath.push_back(citiesIndexHashMap[indexOfFoundCity]);
				}
				counter = temp.secondValue.secondValue[counter];
			}
			for (int i = reconstructedPath.getSize() - 2; i >= 0; i--) {
					std::cout << reconstructedPath[i] << " ";
			}
		}
		std::cout << std::endl;
	}
}

const char* Parser::getCityName(int i, int j) {
	//Check where is first character
	myString cityName = "";
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
				//We have a first character, now we need to check, in which direction it goes
				if (b > 0 && isalpha(this->board[a][b - 1])) {
					//Check if we really took last/first letter
					if (b < this->w - 1 && (isalpha(this->board[a][b + 1]) || isdigit(this->board[a][b + 1]))) {
						cityName = "";
						continue;
					}

					counterX--;
					while (isalpha(this->board[a][counterX]) || isdigit(this->board[a][counterX])) {
						cityName += this->board[a][counterX];
						counterX--;
						if (counterX < 0) break;

					}
					cityName.reverse();
				}

				else if (b + 1 < this->w && (isalpha(this->board[a][b + 1]) || isdigit(this->board[a][b + 1]))) {
					//Check if we really took last/first letter
					if (b > 0 && (isalpha(this->board[a][b - 1]) || isdigit(this->board[a][b - 1]))) {
						cityName = "";
						continue;
					}

					counterX++;
					while (isalpha(this->board[a][counterX]) || isdigit(this->board[a][counterX])) {
						cityName += this->board[a][counterX];
						counterX++;
						if (counterX > this->w - 1) break;
					}

				}
				char* a = new char[cityName.length()+1];
				strcpy_s(a, cityName.length()+1, cityName.str());
				return a;
			}

		}
	}
	return nullptr;
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
	adjencies->addLast(City{ sourceI, sourceJ, 0 });

	//Check if there is any road nearby
	int tempCounter = 0;
	if (sourceJ == 0 || (this->board[sourceI][sourceJ - 1] != '#' && this->board[sourceI][sourceJ - 1] != '*'))
		tempCounter++;
	if(sourceJ == this->w - 1 || (this->board[sourceI][sourceJ + 1] != '#' && this->board[sourceI][sourceJ + 1] != '*'))
		tempCounter++;
	if (sourceI == 0 || (this->board[sourceI - 1][sourceJ] != '#' && this->board[sourceI-1][sourceJ] != '*'))
		tempCounter++;
	if (sourceI == this->h - 1 || (this->board[sourceI + 1][sourceJ] != '#' && this->board[sourceI + 1][sourceJ] != '*'))
		tempCounter++; 
	if(tempCounter == 4) 
		return adjencies;

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
				}
				else if (this->board[newX][newY] == '*' && (newX != sourceI || newY != sourceJ)) {
					adjencies->addLast(City{ newX, newY, currentElement.cost + 1 });
				}

				this->wasVisitedArrayChanged = true;
				this->visitedArray[newX][newY] = true;

			}

		}
	}
	this->visitedArray[sourceI][sourceJ] = false;
	return adjencies;
}

Pair<int, Pair<int, myVector<int>>> Parser::djikstra(Pair<int, DoubleLinkedList<City>*> source, Pair<int, DoubleLinkedList<City>*> dest) {
	myVector<int> paths;
	myVector<int> distances;
	distances.reserveNewCapacity(this->amountOfCities);
	paths.reserveNewCapacity(this->amountOfCities);
	for (size_t i = 0; i < this->amountOfCities; i++) {
		distances.push_back(INT_MAX);
		paths.push_back(-1);
	}
	distances[source.firstValue] = 0;

	myPriorityQueue queue;
	if (!areThereRoads)
		queue.heap.reserveNewCapacity(100000);
	queue.push(Pair<int, int>{0, source.firstValue});


	while (!queue.empty()) {
		//Second value is index in vector of cities
		Pair<int, int> temp = queue.top();
		int u = temp.secondValue; // index in city vector
		queue.pop();

		if (u == dest.firstValue) {
			return Pair<int, Pair<int, myVector<int>>> {distances[u], Pair<int, myVector<int>> {u, paths}};
		}

		if (distances[u] < temp.firstValue) continue;

		DoubleLinkedList<City>* currentList = this->citiesVector[u];

		Node<City>* headNode = currentList->getHead();

		headNode = headNode->next;

		//Search neighbours
		while (headNode != NULL) {
			Pair<int, int> currentCityIndex{ headNode->value.index.firstValue, headNode->value.index.secondValue };
			const char* cityName = this->citiesIndexHashMap[currentCityIndex];
			int v = this->citiesHashMap[cityName].firstValue; // v - index of neighbour in city vector
			int weight = headNode->value.cost;
			if (!areThereRoads && distances[u] + weight >= distances[v] - 100) {
				break;
			}
			if (distances[u] != INT_MAX && distances[v] > distances[u] + weight) {
				distances[v] = distances[u] + weight;
				paths[v] = u;
				queue.push(Pair<int, int>{distances[v], v});
			}
			headNode = headNode->next;
		}

	}
	return Pair<int, Pair<int, myVector<int>>>();
}

void Parser::createDataStructures() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (this->board[i][j] == '*') {
				DoubleLinkedList<City>* adjencies = bfs(i, j);
				const char* cityName = getCityName(i, j);
				this->citiesIndexHashMap.add(Pair<int, int>{ i, j }, cityName);
				this->citiesHashMap.add(cityName, Pair<int, DoubleLinkedList<City>*> {this->amountOfCities, adjencies});
				this->citiesVector.push_back(adjencies);
				this->amountOfCities++;
			}
		}
	}
}

void Parser::run() {
	getBoard();
	fillVisitedArrayWithZeros();
	createDataStructures();
	getFlights();
	getQueries();
}

Parser::~Parser() {}