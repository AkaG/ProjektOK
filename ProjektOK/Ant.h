#pragma once

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <iostream>

typedef std::vector<std::vector<float>> FeromoneTable;
typedef std::vector<std::vector<int>> Solution, Tasks, Breaks;

class Ants
{
private:
	FeromoneTable *feromone_table;
	Tasks tasks;
	Breaks breaks;
	int number_of_tasks, number_of_breaks;

	int number_of_ants;

public:
	void writeFeromoneToTable(Solution solution);
	int getSolutionLength(Solution solution);

public:
	Ants();
	Ants(int n, FeromoneTable *feromoneTable, Tasks tasks, Breaks breaks, int number_of_tasks, int number_of_breaks);
	~Ants();
};

