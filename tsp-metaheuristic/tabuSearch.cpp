#include "pch.h"
#include "tabuSearch.h"
#include "AdjacencyMatrix.h"
#include <iostream>

// *********************************************************************************************
// Initializes shortestRoute and shortestRouteValue using greedy aproach treating startNode as 0
// *********************************************************************************************
void tabuSearch::initRoute()
{
	if (shortestRoute != nullptr) {
		delete shortestRoute;
	}
	shortestRoute = new int[cities.getNodesNumber()];
	shortestRoute[0] = startNode;

	bool* alreadyVisited = new bool[cities.getNodesNumber()];
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		alreadyVisited[i] = false;
	}
	alreadyVisited[startNode] = true;

	for (int i = 0; i < cities.getNodesNumber() - 1; i++) {
		int min = INT_MAX;
		int chosen = -1;
		for (int j = 0; j < cities.getNodesNumber(); j++) {
			if (cities.getElement(shortestRoute[i], j) < min && !alreadyVisited[j]) {
				min = cities.getElement(shortestRoute[i], j);
				chosen = j;
			}
		}
		alreadyVisited[chosen] = true;
		shortestRoute[i + 1] = chosen;
	}

	shortestRouteValue = calculateRouteLength(shortestRoute);
}

// *********************************************************************************************
// Copies one solution into another
// *********************************************************************************************
void tabuSearch::copySolution(int * from, int * to)
{
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		to[i] = from[i];
	}
}

// *********************************************************************************************
// Swaps two elements in an array
// *********************************************************************************************
void tabuSearch::swapElements(int * route, int i, int j)
{
	int temp = route[i];
	route[i] = route[j];
	route[j] = temp;
}

// *********************************************************************************************
// Calculates length of a given route
// *********************************************************************************************
int tabuSearch::calculateRouteLength(int * route)
{
	int length = 0;
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		length += cities.getElement(route[i], route[i + 1 >= cities.getNodesNumber() ? 0 : i + 1]);
	}
	return length;
}

// *********************************************************************************************
// Empty constructor
// *********************************************************************************************
tabuSearch::tabuSearch()
{

}

// *********************************************************************************************
// Destructor, clears memory
// *********************************************************************************************
tabuSearch::~tabuSearch()
{
	if (shortestRoute != nullptr) {
		delete shortestRoute;
	}
}

// *********************************************************************************************
// Sets source of adjacencyMatrix containing cities and routes between them
// *********************************************************************************************
int tabuSearch::setSource(string filename)
{
	return cities.generateFromFile(filename);
}

// *********************************************************************************************
// Prints stored shortest route
// *********************************************************************************************
string tabuSearch::getShortestRoute()
{
	if (cities.isEmpty()) {
		return "No graph to solve!";
	}
	string temp = "";
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		temp += to_string(shortestRoute[i]) + " -> ";
	}
	temp += to_string(shortestRoute[0]);
	return temp;
}

// *********************************************************************************************
// Getter for shortestRouteValue
// *********************************************************************************************
int tabuSearch::getShortestRouteValue()
{
	return shortestRouteValue == INT_MAX ? 0 : shortestRouteValue;
}

// *********************************************************************************************
// Where the Magic takes place, solves TSP using tabuSearch
// *********************************************************************************************
void tabuSearch::solve(int repetitions, int repetitionsTillTabuRemoval, int aspirationValue)
{
	if (cities.isEmpty()) {
		return;
	}
	initRoute();

	int aspirationPlus = false;
	int aspirationCounter = 0;
	int maxAspirationCount = 10;

	// Initialize tabu list
	int **tabuList = new int *[cities.getNodesNumber()];
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		tabuList[i] = new int[cities.getNodesNumber()];
		for (int j = 0; j < cities.getNodesNumber(); j++) {
			tabuList[i][j] = 0;
		}
	}

	int *currentRoute = new int[cities.getNodesNumber()];
	copySolution(shortestRoute, currentRoute);

	int *tempRoute = new int[cities.getNodesNumber()];
	int tempShortestValue = shortestRouteValue;
	int bestSwapFrom, bestSwapTo, bestSwapValue;

	while (repetitions--) {
		// looking for best neighbour
		bestSwapValue = INT_MAX;
		aspirationPlus = false;
		for (int i = 1; i < cities.getNodesNumber(); i++) {
			for (int j = i + 1; j < cities.getNodesNumber(); j++) {
				copySolution(currentRoute, tempRoute);
				swapElements(tempRoute, i, j);
				int diff = calculateRouteLength(tempRoute) - calculateRouteLength(currentRoute);
				// sets new values if: found new best value that's not on tabu list || aspiration criterium's met(route shorter than the shortest one)
				if (((diff < bestSwapValue) && tabuList[i][j] == 0) || diff < aspirationValue) {
					bestSwapValue = diff;
					bestSwapFrom = i;
					bestSwapTo = j;
					if (diff < aspirationValue) {
						aspirationPlus = true;
						aspirationCounter = 0;
					}
				}
				aspirationCounter++;
				if (aspirationCounter == maxAspirationCount && aspirationPlus) {
					goto aspHappend;
				}
			}
		}

aspHappend:
		// decrement tabuList
		for (int i = 0; i < cities.getNodesNumber(); i++) {
			for (int j = 0; j < cities.getNodesNumber(); j++) {
				if (tabuList[i][j] > 0) {
					tabuList[i][j]--;
				}
			}
		}

		// set best neighbour as current road and add swap to tabu
		swapElements(currentRoute, bestSwapFrom, bestSwapTo);
		tabuList[bestSwapFrom][bestSwapTo] = repetitionsTillTabuRemoval;
		tabuList[bestSwapTo][bestSwapFrom] = repetitionsTillTabuRemoval;

		// set new best value if one's found
		if (calculateRouteLength(currentRoute) < shortestRouteValue) {
			swapElements(shortestRoute, bestSwapFrom, bestSwapTo);
			shortestRouteValue = calculateRouteLength(shortestRoute);
		}
	}

	// CleanUp tabuList
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		delete[] tabuList[i];
	}
	delete[] tabuList;
	delete[] currentRoute;
	delete[] tempRoute;
}
