#include "TabuSearch.h"

TabuSearch::TabuSearch(Solution solution) {
	minCost = INT32_MAX;
	numberOfCities = solution.numberOfCities;
	tabuTabSize = pow(numberOfCities, 2);
	minPath.resize(numberOfCities);
	matrix = solution.matrix;
	timeS = 0;
}

TabuSearch::~TabuSearch() {
	minCost = -1;
	numberOfCities = 0;
	tabuTabSize = 0;
	minPath.clear();
	matrix.clear();
}

void TabuSearch::solveTubuSearch(double stopTime) {

	vector<int> currentPath;
	currentPath.resize(numberOfCities);
	currentPath = setSolution(matrix);
	minCost = findCost(currentPath);
	vector<vector<int>> neighbourds;
	tabuMatrix.push_back(currentPath);
	int stop = numberOfCities * 5;
	int zmiana = 0;

	MeasureTime time;
	time.start();

	while (time.totalTime() < stopTime) {

		if (zmiana < 500) {
			for (int j = 0; j < stop; j++) {
				neighbourds.push_back(findNeighbour(currentPath));
			}

			for (auto& k : neighbourds) {

				if (!(find(tabuMatrix.begin(), tabuMatrix.end(), k) != tabuMatrix.end()) && (findCost(k) < findCost(currentPath))) {
					currentPath = k;
				}
			}

			if (findCost(currentPath) < minCost) {
				minPath = currentPath;
				minCost = findCost(currentPath);
				time.stop();
				timeS = time.totalTime();
				zmiana = 0;
			}
			else {
				zmiana++;
			}

			tabuMatrix.push_back(currentPath);

			if (tabuMatrix.size() > tabuTabSize) {
				tabuMatrix.erase(tabuMatrix.begin());
			}
		}
		else {
			for (int i = 0; i < numberOfCities / 2; i++) {
				currentPath = findNeighbour(currentPath);
			}
		}

		time.stop();
	}
}

vector<int> TabuSearch::setSolution(vector<vector<int>> matrix) {

	vector<int> solution;
	int visitedCitires = 0;
	int currentCity = 0;

	while (visitedCitires < numberOfCities) {

		int min = INT32_MAX;
		int minIndex = 0;

		for (int i = 0; i < numberOfCities; i++) {
			if ((matrix[currentCity][i] < min) && (matrix[currentCity][i] != -1)) {
				min = matrix[currentCity][i];
				minIndex = i;
			}
		}

		for (int i = 0; i < numberOfCities; i++) {
			matrix[currentCity][minIndex] = INT32_MAX;
			matrix[minIndex][currentCity] = INT32_MAX;
			matrix[minIndex][0] = INT32_MAX;
		}

		solution.push_back(minIndex);
		visitedCitires++;
	}

	return solution;
}

vector<int> TabuSearch::findNeighbour(vector<int> path) {

	int current = rand() % path.size();
	int next;

	do {

		next = rand() % path.size();

	} while (current == next);

	iter_swap(path.begin() + current, path.begin() + next);

	return path;
}

int TabuSearch::findCost(vector<int>& path) {
	int cost = 0;
	int iterator = 0;

	for (int i = 1; i < path.size(); i++) {
		cost += matrix[path[iterator]][path[i]];
		iterator++;
	}

	cost += matrix[path[iterator]][path[0]];

	return cost;
}