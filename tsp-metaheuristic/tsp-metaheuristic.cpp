// tsp-metaheuristic.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <conio.h>
#include "AdjacencyMatrix.h"
#include "tabuSearch.h"
#include "simmulatedAnnealing.h"

void displayMenu() {
	cout << "TSP:" << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Solve Tabu Search" << endl;
	cout << "3.Solve Simmulated Anealing" << endl;
	cout << "4.Wyswietl" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "0.Exit" << endl;
	cout << "Podaj opcje:";
}

void waitForConfirmation() {
	cout << "Press any key to continue" << endl;
	_getch();
}

const int testsCount = 50;
const int dataRangesCount = 6;
const int dataRanges[dataRangesCount] = { 17, 21, 24, 29, 48, 52 };
const string dataRangesPrefixes[dataRangesCount] = { "gr", "gr", "bays", "gr", "gr", "berlin" };
ofstream testOutput;
string dataFolder = "testData/";
string testFileOutput = "testsData.txt";

int main() {
	//char opt;
	string filename = dataFolder + "bays29.txt";
	tabuSearch testTS;
	simmulatedAnnealing testSA;

	testTS.setSource(filename);
	testSA.setSource(filename);

	//testTS.solve();
	testSA.solve();

	cout << testSA.getShortestRoute() << endl;
	cout << testSA.getShortestRouteValue();
}

