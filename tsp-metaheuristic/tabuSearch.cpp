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
void tabuSearch::Solve()
{
	if (cities.isEmpty()) {
		return;
	}
	initRoute();
}
