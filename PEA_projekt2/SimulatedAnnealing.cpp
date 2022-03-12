#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Solution solution) {
	numberOfCities = solution.numberOfCities;
	matrix = solution.matrix;
	temperatur = 0;
	minCost = INT32_MAX;
	minPath.resize(numberOfCities);
	timeS = 0;
}

SimulatedAnnealing::~SimulatedAnnealing() {
	numberOfCities = 0;
	matrix.clear();
	temperatur = 0;
	minCost = 0;
	minPath.clear();
}

void SimulatedAnnealing::solveSimulatedAnnealing(double stopTime, double a) {

	int stop = (numberOfCities * 5)+1;
	vector<int> currentPath;
	currentPath.resize(numberOfCities);
	currentPath = setSolution(matrix,a);

	vector<int> neighbours;
	neighbours.resize(numberOfCities);

	MeasureTime time;
	time.start();

	while (time.totalTime() < stopTime) {

		for (int j = 0; j < stop; j++) {
			neighbours = findNeighbour(currentPath);

			if (findCost(neighbours) < findCost(currentPath)) {

				currentPath = neighbours;
				time.stop();
				timeS = time.totalTime();

			}
			else if(((double) rand()/RAND_MAX) < propability(currentPath,neighbours)){

				currentPath = neighbours;
				time.stop();
				timeS = time.totalTime();

			}
		}

		/*neighbours = findNeighbour(currentPath);

		if (findCost(neighbours) < findCost(currentPath)) {

			currentPath = neighbours;
			time.stop();
			timeS = time.totalTime();

		}
		else if (((double)rand() / RAND_MAX) < propability(currentPath, neighbours)) {

			currentPath = neighbours;
			time.stop();
			timeS = time.totalTime();

		}*/

		temperatur = cooling(a);
		time.stop();
	}

	minPath = currentPath;
	minCost = findCost(minPath);

}

vector<int> SimulatedAnnealing::findNeighbour(vector<int> path) {
	int current = rand() % path.size();
	int next;

	do {
		next = rand() % path.size();
	} while (current == next);

	iter_swap(path.begin() + current, path.begin() + next);

	return path;
}

double SimulatedAnnealing::propability(vector<int> path, vector<int> neighbourds) {

	return exp(-(findCost(neighbourds) - findCost(path)) / temperatur);

}

int SimulatedAnnealing::findCost(vector<int>& path) {
	int cost = 0;
	int iterator = 0;

	for (int i = 1; i < path.size(); i++) {
		cost += matrix[path[iterator]][path[i]];
		iterator++;
	}

	cost += matrix[path[iterator]][path[0]];

	return cost;
}

double SimulatedAnnealing::cooling(double a) {

	return a * temperatur;

}

vector<int> SimulatedAnnealing::setSolution(vector<vector<int>> matrix, double a) {

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

	temperatur = findCost(solution) * a;

	return solution;
}