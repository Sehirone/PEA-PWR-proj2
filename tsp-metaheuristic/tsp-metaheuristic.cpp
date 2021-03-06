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
	cout << "4.Print struct" << endl;
	cout << "7.Test (pomiary)" << endl;
	cout << "0.Exit" << endl;
	cout << "Podaj opcje:";
}

void waitForConfirmation() {
	cout << "Press any key to continue" << endl;
	cin.clear();
	cin.ignore(256, '\n');
	_getche();
}

const int testsCount = 50;
const int dataRangesCount = 7;
const int dataRangesSYM[dataRangesCount] = { 17, 48, 52, 76, 96, 136, 150 };
const string dataRangesPrefixesSYM[dataRangesCount] = { "gr", "gr", "berlin", "pr", "gr", "pr", "ch"};
const int dataRangesASY[dataRangesCount] = { 17, 33, 47, 64, 70, 170, 323 };
const string dataRangesPrefixesASY[dataRangesCount] = { "br", "ftv", "ftv", "ftv", "ftv", "ftv", "rbg" };
ofstream testOutput;
string dataFolder = "testData/";
string testFileOutput = dataFolder + "testsData.txt";

int main() {
	char opt;
	string filename;
	tabuSearch testTS;
	simmulatedAnnealing testSA;

	while (true) {
		system("cls");
		displayMenu();
		opt = _getche();
		system("cls");
		switch (opt)
		{
		case '1':
			cout << "Nazwa pliku: ";
			cin >> filename;
			if (!testTS.setSource(dataFolder + filename)) {
				cout << "Wczytywanie nie powiodlo sie!" << endl;
				waitForConfirmation();
				break;
			}
			if (!testSA.setSource(dataFolder + filename)) {
				cout << "Wczytywanie nie powiodlo sie!" << endl;
				waitForConfirmation();
				break;
			}
			cout << "Wczytano dane pomyslnie!" << endl;
			waitForConfirmation();
			break;
		case '2':
			testTS.solve();
			cout << testTS.getShortestRoute() << endl;
			cout << testTS.getShortestRouteValue() << endl;
			waitForConfirmation();
			break;
		case '3':
			testSA.solve();
			cout << testSA.getShortestRoute() << endl;
			cout << testSA.getShortestRouteValue() << endl;
			waitForConfirmation();
			break;
		case '4':
			cout << testSA.printSource() << endl;
			waitForConfirmation();
		case '7':
			testOutput.open(testFileOutput);
			if (!testOutput) {
				cout << "BLAD otwarcia pliku zapisu testow!";
				waitForConfirmation();
				break;
			}

			testOutput << "Czasy podano w microsekukndach" << endl;

			testOutput << "Tabu Search Symmetric" << endl;
			testOutput << "L.miast\tCzas\tRozwiazanie" << endl;
			for (int i = 0; i < dataRangesCount; i++) {
				testTS.setSource(dataFolder + "SYM/" + dataRangesPrefixesSYM[i] + to_string(dataRangesSYM[i]) + ".txt");
				int result = 0;
				testOutput << to_string(dataRangesSYM[i]) + "\t";
				auto startTime = chrono::high_resolution_clock::now();
				for (int j = 0; j < testsCount; j++) {
					testTS.solve();
					result += testTS.getShortestRouteValue();
				}
				auto finishTime = chrono::high_resolution_clock::now();
				auto operationTime = chrono::duration_cast<chrono::microseconds>(finishTime - startTime).count() / testsCount;
				testOutput << to_string(operationTime) << '\t' << to_string(result / testsCount) << '\t' << endl;
				testOutput.flush();
			}
			testOutput << endl;

			testOutput << "Simmulated Annealing Symmetric" << endl;
			testOutput << "L.miast\tCzas\tRozwiazanie" << endl;
			for (int i = 0; i < dataRangesCount; i++) {
				testSA.setSource(dataFolder + "SYM/" + dataRangesPrefixesSYM[i] + to_string(dataRangesSYM[i]) + ".txt");
				int result = 0;
				testOutput << to_string(dataRangesSYM[i]) + "\t";
				auto startTime = chrono::high_resolution_clock::now();
				for (int j = 0; j < testsCount; j++) {
					testSA.solve();
					result += testSA.getShortestRouteValue();
				}
				auto finishTime = chrono::high_resolution_clock::now();
				auto operationTime = chrono::duration_cast<chrono::microseconds>(finishTime - startTime).count() / testsCount;
				testOutput << to_string(operationTime) << '\t' << to_string(result / testsCount) << '\t' << endl;
				testOutput.flush();
			}
			testOutput << endl;

			testOutput << "Tabu Search Asymmetric" << endl;
			testOutput << "L.miast\tCzas\tRozwiazanie" << endl;
			for (int i = 0; i < dataRangesCount; i++) {
				testTS.setSource(dataFolder + "ASY/" + dataRangesPrefixesASY[i] + to_string(dataRangesASY[i]) + ".txt");
				int result = 0;
				testOutput << to_string(dataRangesASY[i]) + "\t";
				auto startTime = chrono::high_resolution_clock::now();
				for (int j = 0; j < testsCount; j++) {
					testTS.solve();
					result += testTS.getShortestRouteValue();
				}
				auto finishTime = chrono::high_resolution_clock::now();
				auto operationTime = chrono::duration_cast<chrono::microseconds>(finishTime - startTime).count() / testsCount;
				testOutput << to_string(operationTime) << '\t' << to_string(result / testsCount) << '\t' << endl;
				testOutput.flush();
			}
			testOutput << endl;

			testOutput << "Simmulated Annealing Asymmetric" << endl;
			testOutput << "L.miast\tCzas\tRozwiazanie" << endl;
			for (int i = 0; i < dataRangesCount; i++) {
				testSA.setSource(dataFolder + "ASY/" + dataRangesPrefixesASY[i] + to_string(dataRangesASY[i]) + ".txt");
				int result = 0;
				testOutput << to_string(dataRangesASY[i]) + "\t";
				auto startTime = chrono::high_resolution_clock::now();
				for (int j = 0; j < testsCount; j++) {
					testSA.solve();
					result += testSA.getShortestRouteValue();
				}
				auto finishTime = chrono::high_resolution_clock::now();
				auto operationTime = chrono::duration_cast<chrono::microseconds>(finishTime - startTime).count() / testsCount;
				testOutput << to_string(operationTime) << '\t' << to_string(result / testsCount) << '\t' << endl;
				testOutput.flush();
			}
			testOutput << endl;

			testOutput.close();
			waitForConfirmation();
			break;
		case '0':
			return 0;
		default:
			break;
		}
	}
}

