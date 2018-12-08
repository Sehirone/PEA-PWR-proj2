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
	cout << "2.Solve Brute Force" << endl;
	cout << "3.Solve Branch&Bound" << endl;
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
const int dataRangesCountBT = 6;
const int dataRangesBT[dataRangesCountBT] = { 7, 8, 9, 10, 11, 12 };
const int dataRangesCountBNB = 6;
const int dataRangesBNB[dataRangesCountBNB] = { 7, 8, 9, 10, 11, 12 };
ofstream testOutput;
string testFileOutput = "testData.txt";

int main() {
	//char opt;
	string filename = "gr7.txt";
	tabuSearch testTS;
	simmulatedAnnealing testSA;

	testTS.setSource(filename);
	testSA.setSource(filename);

	testTS.Solve();

	cout << testTS.getShortestRoute() << endl;
	cout << testTS.getShortestRouteValue();
}

