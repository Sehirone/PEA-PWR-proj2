#pragma once
#include "AdjacencyMatrix.h"
class simmulatedAnnealing
{
private:
	AdjacencyMatrix cities;
	int* shortestRoute = nullptr;
	int shortestRouteValue = INT_MAX;
	const int startNode = 0; // starting node should be 0
	void initRoute();
	int calculateRouteLength(int * route);

public:
	simmulatedAnnealing();
	~simmulatedAnnealing();

	int setSource(string filename);

	string getShortestRoute();
	int getShortestRouteValue();
	void solve();
};

