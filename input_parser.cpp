#define _CRT_SECURE_NO_WARNINGS
#include "input_parser.h"
#include <cstdlib>

void InputParser::getBoard() {
	char inputCharacter;
	scanf("%d%d", &w, &h);
	inputCharacter = getchar();

	for (size_t i = 0; i < h; i++) {
		myVector<char> tempVector;
		for (size_t j = 0; j < w; j++) {
			inputCharacter = getchar();
			tempVector.push_back(inputCharacter);
		}
		inputCharacter = getchar();
		board.push_back(tempVector);
	}
}

void InputParser::getFlights() {
	scanf("%d", &amountOfFlights);
	getchar();

	myString temp = "";
	myString tempSource = "";
	myString tempDestination = "";
	int cost = 0;
	char character;

	for (size_t i = 0; i < amountOfFlights; i++) {
		temp = "";
		tempSource = "";
		tempDestination = "";
		cost = 0;
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
		cost = atoi(temp.str());
		this->flights.push_back(Flight(tempSource, tempDestination, cost));
	}
}

void InputParser::getQueries() {
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

void InputParser::getData() {
	getBoard();
	getFlights();
	getQueries();
	getCities();
}

void InputParser::getCityName(int i, int j) {
	//Check where is first character
	myString cityName = "";
	for (int a = i - 1; a <= i + 1; a++) {
		for (int b = j - 1; b <= j + 1; b++) {

			//Check if in board
			if (a < 0 || a > h - 1 || b < 0 || b > w - 1)
				continue;

			if (a == i && b == j)
				continue;

			if (isalpha(this->board[a][b]) || isdigit(this->board[a][b])) {

				int counterX = b;
				cityName += this->board[a][b];

				//We have a first character, now we need to check, in which direction it goes
				if (b > 0 && isalpha(this->board[a][b - 1])) {
					//Check if we really took last/first letter
					if (b < this->w - 1 && (isalpha(this->board[a][b + 1]) || isdigit(this->board[a][b+1]))) {
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
					if (b > 0 && (isalpha(this->board[a][b - 1]) || isdigit(this->board[a][b-1]))) {
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
				City newCity = { i, j, cityName, this->cities.getSize()};
				this->cities.push_back(newCity);
				return;
			}
		}
	}
}

void InputParser::getCities() {
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			if (this->board[i][j] == '*')
				getCityName(i, j);
		}
	}

}

void InputParser::prepareBoard() {
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			if (this->board[i][j] == '*')
				this->board[i][j] = '2';
			else if (this->board[i][j] == '#')
				this->board[i][j] = '1';
			else
				this->board[i][j] = '0';
		}
	}
}

void InputParser::printBoard() {
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++) {
			std::cout << board[i][j];
		}
		std::cout << '\n';
	}
}