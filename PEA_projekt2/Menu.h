#pragma once
#include "Solution.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"


class Menu
{
public:
	Solution lastSolution;

	void mainMenu();
	void testMenu();
};

