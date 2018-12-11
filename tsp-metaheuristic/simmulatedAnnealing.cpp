#include "pch.h"
#include "simmulatedAnnealing.h"
#include "AdjacencyMatrix.h"
#include <iostream>
#include <random>
#include <math.h>

// *********************************************************************************************
// Random device init
// *********************************************************************************************
simmulatedAnnealing::simmulatedAnnealing()
{
	rng.seed(std::random_device()());
}

// *********************************************************************************************
// Destructor, clears memory
// *********************************************************************************************
simmulatedAnnealing::~simmulatedAnnealing()
{
	if (shortestRoute != nullptr) {
		delete shortestRoute;
	}
}

// *********************************************************************************************
// Sets source of adjacencyMatrix containing cities and routes between them
// *********************************************************************************************
int simmulatedAnnealing::setSource(string filename)
{
	return cities.generateFromFile(filename);
}

string simmulatedAnnealing::printSource()
{
	return cities.printStruct();
}

// *********************************************************************************************
// Initializes shortestRoute and shortestRouteValue using greedy aproach treating startNode as 0
// *********************************************************************************************
void simmulatedAnnealing::initRoute()
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
int simmulatedAnnealing::calculateRouteLength(int * route)
{
	int length = 0;
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		length += cities.getElement(route[i], route[i + 1 >= cities.getNodesNumber() ? 0 : i + 1]);
	}
	return length;
}

// *********************************************************************************************
// Getter for shortestRouteValue
// *********************************************************************************************
int simmulatedAnnealing::getShortestRouteValue()
{
	return shortestRouteValue == INT_MAX ? 0 : shortestRouteValue;
}

// *********************************************************************************************
// Prints stored shortest route
// *********************************************************************************************
string simmulatedAnnealing::getShortestRoute()
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
// Copies one solution into another
// *********************************************************************************************
void simmulatedAnnealing::copySolution(int * from, int * to)
{
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		to[i] = from[i];
	}
}

// *********************************************************************************************
// inverts elements between i and j
// *********************************************************************************************
void simmulatedAnnealing::invertElements(int * route, int i, int j)
{
	//int temp = route[i];
	//route[i] = route[j];
	//route[j] = temp;
	for (; i < j; i++, j--) {
		int temp = route[j];
		route[j] = route[i];
		route[i] = temp;
	}
}

// *********************************************************************************************
// Where the Magic takes place, solves TSP using simmulated annealing
// *********************************************************************************************
void simmulatedAnnealing::solve() {
	if (cities.isEmpty()) {
		return;
	}
	initRoute();

	double temperature = shortestRouteValue / cities.getNodesNumber() * cities.getNodesNumber();
	double coolingValue = 0.9999;
	long long maxIterations = pow(cities.getNodesNumber(), 4);
	long long iterationWithoutChange = 0;
	long long maxIterationWithoutChange = maxIterations/1000;
	std::uniform_int_distribution<std::mt19937::result_type> distNode(1, cities.getNodesNumber() - 1);
	std::uniform_real_distribution<double> distProb(0.0, 1.0);
	cout << temperature << '\t' << maxIterations << '\t' << maxIterationWithoutChange << endl;

	int * newRoute = new int[cities.getNodesNumber()];
	int * bestRoute = new int[cities.getNodesNumber()];
	int bestRouteValue = shortestRouteValue;
	copySolution(shortestRoute, bestRoute);

	
	while (maxIterations-- && iterationWithoutChange < maxIterationWithoutChange && temperature > 0.5) {
		copySolution(bestRoute, newRoute);
		// picking a new solution and getting its routeValue
		int swapFrom = distNode(rng);
		int swapTo = distNode(rng);
		while (swapTo == swapFrom) {
			swapTo = distNode(rng);
		}
		invertElements(newRoute, swapFrom, swapTo);
		int newRouteValue = calculateRouteLength(newRoute);

		//if newRouteValue is shorter than actual shortestRoute, set new shortest route
		if (newRouteValue < bestRouteValue) {
			bestRouteValue = newRouteValue;
			copySolution(newRoute, shortestRoute);
			iterationWithoutChange = 0;
		}
		else {
			int diff = bestRouteValue - newRouteValue;
			double prob = exp(diff / temperature);
			if (distProb(rng) <= prob) {
				bestRouteValue = newRouteValue;
				copySolution(newRoute, shortestRoute);
				iterationWithoutChange = 0;
			}
			else {
				iterationWithoutChange++;
			}
		}
		// cooling down
		temperature *= coolingValue;
		// remember best route
		if (bestRouteValue < shortestRouteValue) {
			copySolution(bestRoute, shortestRoute);
			shortestRouteValue = bestRouteValue;
		}
	}
	cout << temperature << '\t' << maxIterations << '\t' << maxIterationWithoutChange << '\t' << iterationWithoutChange << endl;
	delete[] newRoute;
	delete[] bestRoute;
}