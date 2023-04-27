#include <iostream>
#include "my_string.h"
#include "my_vector.h"
#include "my_queue.h"
#include "double_linked_list.h"

#include "structs.h"
#include "input_parser.h"
#include "graph_parser.h"
using namespace std;
int main() {
	InputParser inputParser;
	inputParser.getData();
	inputParser.getCities();
	inputParser.prepareBoard();

	GraphParser graphParser = {inputParser.board, inputParser.cities, inputParser.w, inputParser.h};
	graphParser.convertToGraph();
	//graphParser.djikstra();

	graphParser.printGraph();
	cout << endl;
	//graphParser.printGraphAfterDjikstra();
	graphParser.printPaths();
	cout << graphParser.cities;
	//cout << graphParser.shortestPathsCities[6][0];
}