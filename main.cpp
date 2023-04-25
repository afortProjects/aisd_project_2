#include <iostream>
#include "my_string.h"
#include "double_linked_list.h"
#include "my_vector.h"
#include "structs.h"
#include "input_parser.h"
using namespace std;
int main() {
	InputParser inputParser;
	inputParser.getBoard();
	inputParser.getCities();
	inputParser.prepareBoard();
	inputParser.printBoard();

}