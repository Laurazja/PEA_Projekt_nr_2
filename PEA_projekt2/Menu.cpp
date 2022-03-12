#include "Menu.h"

void Menu::mainMenu() {
	char option = 0;
	string fileName = "";
	double stopTime = 60;
	double a = 0.99;

	while (option != 'e') {

		cout << "Wybierz opcje: " << endl
			<< "1. Wczytaj dane z pliku" << endl
			<< "2. Wprowadz kryterium stopu" << endl
			<< "3. Rozwiaz przy pomocy Tabu search" << endl
			<< "4. Wprowadz wartosc wspolczynnika zaminy temperatury" << endl
			<< "5. Rozwiaz przy pomocy symulowanego wyzazania" << endl
			<< "6. Wyswietl ostatnio wczytane dane i rozwiazanie" << endl
			<< "7. Wyswitel aktualne ograniczenie i wartosc wspolczynnika zaminy temperatury" << endl
			<< "e. Wyjdz" << endl;
		cin >> option;

		switch (option) {
		case '1':
			cout << "Podaj nazwe pliku: ";
			cin >> fileName;
			lastSolution.readFromFile(fileName);
			break;
		case '2':
			cout << endl << "Podaj czas w sekundach: ";
			cin >> stopTime;
			stopTime = stopTime * 1000000;
			break;
		case '3':
			if (!lastSolution.matrix.empty()) {
				TabuSearch tabu(lastSolution);
				tabu.solveTubuSearch(stopTime);
				lastSolution.minCost = tabu.minCost;
				lastSolution.minPath = tabu.minPath;
				lastSolution.time = tabu.timeS;
				lastSolution.displaySolution();
			}
			else {
				cout << "Brak danych do wykonania algorytmu" << endl;
			}
			break;
		case '4':
			cout << endl << "Podaj wartosc wspolczynnika zaminy temperatury: ";
			cin >> a;
			break;
		case '5':
			if (!lastSolution.matrix.empty()) {
				SimulatedAnnealing simAnn(lastSolution);
				simAnn.solveSimulatedAnnealing(stopTime,a);
				lastSolution.minCost = simAnn.minCost;
				lastSolution.minPath = simAnn.minPath;
				lastSolution.time = simAnn.timeS;
				lastSolution.displaySolution();
				cout << "Temperatura koncowa: " << simAnn.temperatur << endl;
			}
			else {
				cout << "Brak danych do wykonania algorytmu" << endl;
			}
			break;
		case '6':
			lastSolution.display();
			break;
		case '7':
			cout << "Ograniczenie: " << stopTime << " sekund" << endl;
			cout << "Wartosc wspolczynnika zaminy temperatury: " << (double)a << endl;
			break;
		case 'e':
			cout << "Zakonczenie programu" << endl;
			break;
		default:
			cout << "Zle oznaczenie opcji" << endl;
			break;
		}
	}
}


void Menu::testMenu() {
	char option = 0;
	string fileName = "";
	double stopTime = 60;
	double a = 0.999999999;

	while (option != 'e') {

		cout << "Wybierz opcje: " << endl
			<< "1. Wczytaj dane z pliku" << endl
			<< "2. Wprowadz kryterium stopu" << endl
			<< "3. Rozwiaz przy pomocy Tabu search" << endl
			<< "4. Wprowadz wartosc wspolczynnika zaminy temperatury" << endl
			<< "5. Rozwiaz przy pomocy symulowanego wyzarzania" << endl
			<< "6. Wyswietl ostatnio wczytane dane i rozwiazanie" << endl
			<< "e. Wyjdz" << endl;
		cin >> option;

		switch (option) {
		case '1':
			cout << "Podaj nazwe pliku: ";
			cin >> fileName;
			lastSolution.readFromFile(fileName);
			break;
		case '2':
			cout << endl << "Podaj czas w sekundach: ";
			cin >> stopTime;
			stopTime = stopTime * 1000000;
			break;
		case '3':
			for (int i = 0; i < 10; i++) {
				if (!lastSolution.matrix.empty()) {
					TabuSearch tabu(lastSolution);
					tabu.solveTubuSearch(stopTime);
					lastSolution.minCost = tabu.minCost;
					lastSolution.minPath = tabu.minPath;
					lastSolution.time = tabu.timeS;
					lastSolution.displaySolution();
				}
				else {
					cout << "Brak danych do wykonania algorytmu" << endl;
				}
			}
			break;
		case '4':
			cout << endl << "Podaj wartosc wspolczynnika zaminy temperatury: ";
			cin >> a;
			break;
		case '5':
			for (int i = 0; i < 10; i++) {
				if (!lastSolution.matrix.empty()) {
					SimulatedAnnealing simAnn(lastSolution);
					simAnn.solveSimulatedAnnealing(stopTime, a);
					lastSolution.minCost = simAnn.minCost;
					lastSolution.minPath = simAnn.minPath;
					lastSolution.time = simAnn.timeS;
					lastSolution.displaySolution();
					cout << "Temperatura koncowa: " << simAnn.temperatur << endl;
				}
				else {
					cout << "Brak danych do wykonania algorytmu" << endl;
				}
			}
			break;
		case '6':
			lastSolution.display();
			break;
		case 'e':
			cout << "Zakonczenie programu" << endl;
			break;
		default:
			cout << "Zle oznaczenie opcji" << endl;
			break;
		}
	}
}
