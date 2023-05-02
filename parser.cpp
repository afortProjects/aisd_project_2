#include "parser.h"
#include <iostream>
#include <string>
#include "consts.h"
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
		counter = 0;
		character = getchar();
		while (character != ' ') {
			destination[counter] = character;
			character = getchar();
			counter++;
		}

		scanf("%d", &cost);
		getchar();
		flights.push_back(Flight(source, destination, cost));
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

void Parser::getCityName(int i, int j) {
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
				size_t c = amountOfCities;
				//buffer[counter] = '\0';
				const char* a = cityName.str();

				City newCity = { i, j, a, c};
				this->citiesHashMap.add(cityName.str(), newCity);
				this->cities.push_back(newCity);
				this->amountOfCities += 1;
				return;
			}

		}
	}
	//delete[] buffer;


}

void Parser::getCities() {
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			if (this->board[i][j] == '*') {
				getCityName(i, j);
			}
		}
	}

}

void Parser::getData() {
	getBoard();
	getFlights();
 	getQueries();
	getCities();
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

City Parser::findCity(int i, int j) {
	for (size_t m = 0; m < this->cities.getSize(); m++) {
		if (this->cities[m].index.i == i && this->cities[m].index.j == j)
			return this->cities[m];
	}
	return City();
}

DoubleLinkedList<City>& Parser::bfs(City& source) {
	int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	myQueue<Node> queue;
	/*myVector<int> distances;
	myVector<City> cities;*/
	int queueFirstElementIndexI;
	int queueFirstElementIndexJ;

	DoubleLinkedList<City> adjencies;
	adjencies.addNewBlockToList(&source);

	//distances.reserveNewCapacity(this->amountOfCities);
	//cities.reserveNewCapacity(this->amountOfCities);

	//for (size_t i = 0; i < this->amountOfCities; i++) {
	//	distances[i] = 0;
	//	//cities[i] = City();
	//}

	if (this->wasVisitedArrayChanged) {
		for (size_t i = 0; i < this->visitedArray.getSize(); i++) {
			for (size_t j = 0; j < visitedArray[i].getSize(); j++) {
				this->visitedArray[i][j] = false;
			}
		}
	}


	queue.addElementToQueue(Node{ source.index.i, source.index.j, 0 });
	this->visitedArray[source.index.i][source.index.j] = true;

	while (!queue.isEmpty()) {
		Node currentElement = queue.getElementFromQueue();
		queueFirstElementIndexI = currentElement.x;
		queueFirstElementIndexJ = currentElement.y;
		int newX, newY;
		for (size_t i = 0; i < 4; i++) {
			newX = queueFirstElementIndexI + directions[i][0];
			newY = queueFirstElementIndexJ + directions[i][1];


			if (newX >= 0 && newY >= 0 && newX < this->h && newY < this->w && this->visitedArray[newX][newY] == 0) {
				if ((this->board[newX][newY] == '#')) {
					queue.addElementToQueue(Node{ newX, newY, currentElement.distance + 1 });
					this->visitedArray[newX][newY] = true;
					this->wasVisitedArrayChanged = true;
				}
				else if (this->board[newX][newY] == '*' && (newX != source.index.i || newY != source.index.j)) {
					City foundCity = findCity(newX, newY);
					foundCity.cost = currentElement.distance + 1;
					adjencies.addNewBlockToList(&foundCity);
					this->visitedArray[newX][newY] = true;
					this->wasVisitedArrayChanged = true;
					//cities[foundCity.indexInCityVector] = foundCity;
					//distances[foundCity.indexInCityVector] = (currentElement.distance + 1);

				}
			}
		}
	}
	this->visitedArray[source.index.i][source.index.j] = false;
	//for(size_t i=0;i<cities)
	return adjencies;
}

void Parser::convertToGraph() {
	fillVisitedArrayWithZeros();
		for (size_t i = 0; i < cities.getSize(); i++) {
			//this->graph.push_back(bfs(this->cities[i]));
			this->graphList.push_back(bfs(this->cities[i]));
		}
}

void Parser::includeFlights() {
	for (size_t i = 0; i < this->flights.getSize(); i++) {
		int first = this->citiesHashMap[this->flights[i].source].indexInCityVector;
		int second = this->citiesHashMap[this->flights[i].destination].indexInCityVector;
		if ((this->graph[first][second] > this->flights[i].cost || graph[first][second] == 0)) {
			graph[first][second] = this->flights[i].cost;
		}
	}
}

int Parser::minDistance(myVector<int>& distances, myVector<bool>& visitedArr) {
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
void Parser::djikstra() {
	int citiesSize = this->cities.getSize();
	int minDist;
	myString temp;
	fillVisitedArrayWithZeros();
	for (size_t i = 0; i < citiesSize; i++) {
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
						if (strlen(this->cities[minDist].name) != 0) {
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

void Parser::printOutput() {
	for (size_t i = 0; i < queries.getSize(); i++) {
		const char* src = queries[i].source.str();
		const char* dest = queries[i].destination.str();
		size_t srcIndex = this->citiesHashMap[src].indexInCityVector;
		size_t destIndex = this->citiesHashMap[dest].indexInCityVector;

		std::cout << this->shortestPaths[(this->citiesHashMap[src].indexInCityVector)][(this->citiesHashMap[dest].indexInCityVector)];
		if (queries[i].choice == 1) {
			std::cout << " " << this->shortestPathsCities[this->citiesHashMap[src].indexInCityVector][this->citiesHashMap[dest].indexInCityVector];
		}
		std::cout << std::endl;
	}
}

Parser::~Parser() {}