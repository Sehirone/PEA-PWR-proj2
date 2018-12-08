#include "pch.h"
#include "simmulatedAnnealing.h"
#include "AdjacencyMatrix.h"
#include <iostream>


simmulatedAnnealing::simmulatedAnnealing()
{
}


simmulatedAnnealing::~simmulatedAnnealing()
{
}

int simmulatedAnnealing::setSource(string filename)
{
	return cities.generateFromFile(filename);
}
