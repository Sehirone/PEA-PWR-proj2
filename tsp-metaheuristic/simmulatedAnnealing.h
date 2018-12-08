#pragma once
#include "AdjacencyMatrix.h"
class simmulatedAnnealing
{
private:
	AdjacencyMatrix cities;

public:
	simmulatedAnnealing();
	~simmulatedAnnealing();

	int setSource(string filename);
};

