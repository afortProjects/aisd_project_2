#include <iostream>
//#include "my_string.h"
//#include "my_vector.h"
//#include "my_queue.h"
//#include "double_linked_list.h"
//#include "my_hash_map.h"
//
//#include "structs.h"
//#include "input_parser.h"
//#include "graph_parser.h"
//#include "result_parser.h"

#include "parser.h";
using namespace std;
int main() {
	Parser parser;
	parser.getData();
	parser.convertToGraph();
	if (parser.amountOfFlights != 0)
		parser.includeFlights();

	parser.djikstra();

	parser.printOutput();

	//for (size_t i = 0; i < 1000; i++) {
	//	if (parser.citiesHashMap.table[i] != NULL) {
	//		cout << parser.citiesHashMap.table[i]->getValue() << " ";
	//		cout << parser.citiesHashMap.table[i]->getKey() << endl;

	//	}
	//}
	//cout << endl;
	//cout << parser.cities << endl;
	/*const char* a = "KRAKOW";
	cout << parser.citiesHashMap[a];
	for (size_t i = 0; i < 1000; i++) {
		if (parser.citiesHashMap.table[i] != NULL) {
			cout << parser.citiesHashMap.table[i]->getKey();
			cout << parser.citiesHashMap.table[i]->getValue();
		}
	}


	cout << parser.queries;*/

	/*InputParser inputParser;
	inputParser.getData();
	cout << inputParser.cities<<endl;

	cout << endl;;
	GraphParser graphParser = {inputParser.board, inputParser.cities, inputParser.flights, inputParser.w, inputParser.h};
	graphParser.convertToGraph();

	if(inputParser.flights.getSize() != 0)
		graphParser.includeFlights();

	graphParser.djikstra();

	ResultParser resultParser = { inputParser.queries, graphParser.cities, graphParser.shortestPathsCities, graphParser.shortestPaths, inputParser.hashMap };
	for (size_t i = 0; i < 1000; i++) {
		if (resultParser.hashMap.table[i] != NULL) {
			cout << resultParser.hashMap.table[i]->getValue();
			cout << resultParser.hashMap.table[i]->getKey();

		}
	}
	cout << endl;;*/
	//resultParser.printOutput();
 //	cout << inputParser.cities<<endl;
	//inputParser.printBoard();
	//graphParser.printGraph();
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