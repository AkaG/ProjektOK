#include "Ant.h"



void Ant::writeFeromoneToTable(Solution solution)
{
	auto prev = solution[0][0];
	std::cout << prev << " ";

	for (auto &i : solution[0]) {
		if (i == prev)
			continue;
		std::cout << prev << " " << i <<" |";

		(*feromone_table)[prev][i] += 1;

		prev = i;
	}
}

Ant::Ant()
{
}

Ant::Ant(int n, FeromoneTable &table, Tasks tasks, Breaks breaks)
{
	number_of_ants = n;
	feromone_table = &table;
	this->tasks = tasks;
	this->breaks = breaks;
}

Ant::~Ant()
{
}
