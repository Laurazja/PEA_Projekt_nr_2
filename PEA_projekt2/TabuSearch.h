#pragma once
#include "Solution.h"


class TabuSearch
{
public:
	vector<vector<int>> tabuMatrix;
	vector<vector<int>> matrix;
	int tabuTabSize;
	int minCost;
	int numberOfCities;
	vector<int> minPath;
	long timeS;

	TabuSearch(Solution solution);
	~TabuSearch();

	void solveTubuSearch(double stopTime);
	vector<int> setSolution(vector<vector<int>> tabuMatrix);
	vector<int> findNeighbour(vector<int> path);
	int findCost(vector<int>& path);
};

