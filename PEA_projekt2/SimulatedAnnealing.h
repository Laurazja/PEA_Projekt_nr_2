#pragma once
#include "Solution.h"


class SimulatedAnnealing
{
public:
	double temperatur;
	int minCost;
	vector<int> minPath;
	vector<vector<int>> matrix;
	int numberOfCities;
	long timeS;

	SimulatedAnnealing(Solution solution);
	~SimulatedAnnealing();

	double cooling(double a);
	void solveSimulatedAnnealing(double stopTime, double a);
	vector<int> findNeighbour(vector<int> path);
	double propability(vector<int> path, vector<int> neighbours);
	int findCost(vector<int>& path);
	vector<int> setSolution(vector<vector<int>> matrix, double a);

};

