#include "Ant.h"

Instance::Instance()
{
}


Instance::Instance(int n)
{
	this->number_of_tasks = n;
	this->number_of_breaks = (rand() % (n / 2 - 2)) + 2;

	tasks.resize(sizeof(std::vector<int>)*number_of_tasks);
	for (auto &i :tasks) {
		i.resize(sizeof(int) * 2);
	}

	breaks.resize(sizeof(std::vector<int>) * number_of_breaks);
	for (auto &i : breaks) {
		i.resize(sizeof(int) * 2);
	}

	feromone_table.resize(sizeof(std::vector<float>) * number_of_tasks);
	for (auto &i : feromone_table) {
		i.resize(sizeof(float) * number_of_tasks);
	}
}

Instance::~Instance()
{
}


void Instance::generate(int max, int min)
{
	this->max_task_length = max;
	this->min_task_length = min;

	for (int i = 0; i < number_of_tasks; i++){
		tasks[i][0] = (rand() % (max_task_length - min_task_length)) + min_task_length;
		tasks[i][1] = (rand() % (max_task_length - min_task_length)) + min_task_length;
	}
}

void Instance::generateBreaks()
{
	int sumaZadan = 0;
	int najkrotsze = max_task_length;

	int minBreak = 5;
	int maxBreak = 50;

	for (int i = 0; i < number_of_tasks; i++){
		sumaZadan += tasks[i][0];
		if (tasks[i][0] < najkrotsze)
			najkrotsze = tasks[i][0];
	}
	
	breaks[0][0] = ((rand() % 3) + 1) * najkrotsze;
	breaks[0][1] = breaks[0][0] + ((rand() % maxBreak) + minBreak);

	for (int i = 1; i < number_of_breaks; i++){
		breaks[i][0] = breaks[i - i][1] + ((rand() % (3 * max_task_length)) + min_task_length);
		breaks[i][1] = breaks[i][0] + ((rand() % maxBreak) + minBreak);
	}
}

Solution Instance::generateRandomSolution()
{
	Solution solution;
	std::vector<bool> used;
	used.resize(sizeof(bool)*number_of_tasks);
	for (auto &i: used) {
		i = false;
	}

	int number_of_unused = number_of_tasks;

	while (number_of_unused > 0) {
		int random_number = rand() % number_of_unused;

		int index_of_choosed = 0;
		while (!random_number) {
			if (used[++index_of_choosed] == false)
				random_number--;
			if (index_of_choosed == number_of_tasks)
				index_of_choosed = 0;
		}
		used[index_of_choosed] = true;
		
		for (auto &sol : solution) {
			sol[number_of_tasks - number_of_unused] = index_of_choosed;
		}

		number_of_unused--;
	}
	return solution;
}


std::vector<std::vector<int>> Instance::getSolution()
{
	return solution;
}
