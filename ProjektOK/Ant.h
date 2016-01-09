#pragma once

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <iostream>

typedef std::vector<std::vector<float>> FeromoneTable;
typedef std::vector<std::vector<int>> Solution, Tasks, Breaks;

class Ant
{
private:
	FeromoneTable *feromone_table;
	Tasks tasks;
	Breaks breaks;

	int number_of_ants;
public:
	void writeFeromoneToTable(Solution solution);

public:
	Ant();
	Ant(int n, FeromoneTable &table, Tasks tasks, Breaks breaks);
	~Ant();
};

