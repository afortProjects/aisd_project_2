#include <iostream>
#include "my_string.h"
#include "my_vector.h"
#include "my_queue.h"
#include "double_linked_list.h"

#include "structs.h"
#include "input_parser.h"
#include "graph_parser.h"
#include "result_parser.h"
using namespace std;
int main() {
	InputParser inputParser;
	inputParser.getData();
	//inputParser.prepareBoard();

	GraphParser graphParser = {inputParser.board, inputParser.cities, inputParser.flights, inputParser.w, inputParser.h};
	graphParser.convertToGraph();

	if(inputParser.flights.getSize() != 0)
		graphParser.includeFlights();

	graphParser.djikstra();

	ResultParser resultParser = { inputParser.queries, graphParser.cities, graphParser.shortestPathsCities, graphParser.shortestPaths };
	resultParser.printOutput();
	//cout << inputParser.cities;
	//graphParser.printGraph();
	//graphParser.printGraphAfterDjikstra();
	//for (size_t i = 0; i < inputParser.cities.getSize(); i++) {
	//	if (inputParser.cities[i].name == "DD") cout << graphParser.shortestPaths[i];
	//}
	//inputParser.printBoard();

	//cout << graphParser.shortestPathsCities[0][];
	//graphParser.printGraph();
	//cout << endl;
	//graphParser.printGraphAfterDjikstra();
	//graphParser.printPaths();
	//parse flights, change graphs, calculate djikstra
	//cout << graphParser.shortestPathsCities[0][6];
	//cout << graphParser.shortestPathsCities[6][0];
}