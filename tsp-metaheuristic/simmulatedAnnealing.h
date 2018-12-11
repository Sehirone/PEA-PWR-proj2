#pragma once
#include "AdjacencyMatrix.h"
#include <random>
class simmulatedAnnealing
{
private:
	AdjacencyMatrix cities;
	int* shortestRoute = nullptr;
	int shortestRouteValue = INT_MAX;
	const int startNode = 0; // starting node should be 0
	mt19937 rng;

	void initRoute();
	int calculateRouteLength(int * route);
	void copySolution(int *from, int *to);
	void invertElements(int * route, int i, int j);

public:
	simmulatedAnnealing();
	~simmulatedAnnealing();

	int setSource(string filename);
	string printSource();

	string getShortestRoute();
	int getShortestRouteValue();
	void solve();
};

