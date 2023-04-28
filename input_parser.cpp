#include "input_parser.h"
#include <cstdlib>

void InputParser::getBoard() {
	std::cin >> w >> h;
	char inputCharacter;
	for (size_t i = 0; i < h; i++) {
		myVector<char> tempVector;
		for (size_t j = 0; j < w; j++) {
			std::cin >> inputCharacter;
			tempVector.push_back(inputCharacter);
		}
		board.push_back(tempVector);
	}
}

void InputParser::getFlights() {
	std::cin >> amountOfFlights;
	myString temp = "";
	myString tempSource = "";
	myString tempDestination = "";
	int cost = 0;
	char character;

	// To skip first \n
	getchar();
	for (size_t i = 0; i < this->amountOfFlights; i++) {
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

				else if (b + 1 < this-> w && isalpha(this->board[a][b + 1]) || isdigit(this->board[a][b+1])) {
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
				City newCity = { i, j, cityName };
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