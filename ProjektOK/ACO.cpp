#include "ACO.h"

ACO::ACO()
{
}


ACO::ACO(int number_of_tasks, int number_of_ants)
{
	this->number_of_tasks = number_of_tasks;
	this->number_of_breaks = (rand() % (number_of_tasks / 2 - 2)) + 2;
	this->number_of_ants = number_of_ants;

	tasks.resize(this->number_of_tasks);
	for (auto &i :tasks) {
		i.resize(3);
	}

	breaks.resize(this->number_of_breaks);
	for (auto &i : breaks) {
		i.resize(2);
	}

	feromone_table.resize(this->number_of_tasks);
	for (auto &i : feromone_table) {
		i.resize(this->number_of_tasks);
	}

	ants = new Ants(number_of_ants, &feromone_table, tasks, breaks, number_of_tasks, number_of_breaks);
}

ACO::~ACO()
{
	delete ants;
}


void ACO::generateTasks(int max, int min)
{
	this->max_task_length = max;
	this->min_task_length = min;

	for (int i = 0; i < number_of_tasks; i++) {
		tasks[i][0] = (rand() % (max_task_length - min_task_length)) + min_task_length;
		tasks[i][1] = (rand() % (max_task_length - min_task_length)) + min_task_length;
		tasks[i][2] = (rand() % (min_task_length*number_of_tasks + number_of_breaks * 50));
	}
}

void ACO::generateBreaks()
{
	int sumOfTasks = 0;
	int shortest = max_task_length;

	int minBreak = 5;
	int maxBreak = 50;

	for (int i = 0; i < number_of_tasks; i++){
		sumOfTasks += tasks[i][0];
		if (tasks[i][0] < shortest)
			shortest = tasks[i][0];
	}
	
	breaks[0][0] = ((rand() % 3) + 1) * shortest;
	breaks[0][1] = breaks[0][0] + ((rand() % maxBreak) + minBreak);

	for (int i = 1; i < number_of_breaks; i++){
		breaks[i][0] = breaks[i - 1][1] + ((rand() % (3 * max_task_length)) + min_task_length);
		breaks[i][1] = breaks[i][0] + ((rand() % maxBreak) + minBreak);
	}
}

Solution ACO::generateRandomSolution()
{
	Solution solution;
	std::vector<bool> used;
	used.resize(number_of_tasks);
	for (auto &i: used) {
		i = false;
	}

	solution.resize(2);
	for (auto &i : solution) {
		i.resize(number_of_tasks);
	}

	int number_of_unused = number_of_tasks;

	while (number_of_unused > 0) {
		int random_number = (rand() % number_of_unused) + 1;

		int index_of_choosed = -1;
		while (random_number){
			if (used[(++index_of_choosed)] == false)
				random_number--;
		}
		used[index_of_choosed] = true;
		
		for (auto &sol : solution) {
			sol[number_of_tasks - number_of_unused] = index_of_choosed;
		}

		number_of_unused--;
	}
	return solution;
}


Solution ACO::getSolution()
{
	return solution;
}

void ACO::printSolution(Solution solution)
{
	//std::cout << "First machine\n";
	ants->writeFeromoneToTable(solution);

	int currentBreak = 0;
	int pointer = 0;
	for (auto task : solution[0]) {
		if (currentBreak < number_of_breaks) {
			if (tasks[task][0] >
				(breaks[currentBreak][0] - pointer)) {
				while (pointer < breaks[currentBreak][0]) {
					//std::cout << "! ";
					pointer++;
				}
				while (pointer < breaks[currentBreak][1]) {
					//std::cout << "_ ";
					pointer++;
				}
				currentBreak++;
			}
		}
		for (int i = pointer; pointer < tasks[task][0] + i; pointer++) {
			//std::cout << task << " ";
		}
	}

	while (currentBreak < number_of_breaks) {
		while (pointer < breaks[currentBreak][0]) {
			//std::cout << "! ";
			pointer++;
		}
		while (pointer < breaks[currentBreak][1]) {
			//std::cout << "_ ";
			pointer++;
		}
		currentBreak++;
	}
	std::cout << std::endl;
	for (auto task : solution[0]) {
		std::cout << task << std::endl;
	}
}

int ACO::getSolutionLength(Solution solution)
{
	return ants->getSolutionLength(solution);
}

void ACO::loadFromFile(std::string name)
{
	std::fstream file;
	std::string input;

	file.open(name, std::ios::in);
	if (file.is_open()) {
		int count;
		file >> count;
		std::getline(file, input);

		for (int i = 0; i < count; i++) {
			std::getline(file, input);
			std::istringstream ss(input);
			std::string token;

			std::getline(ss, token, ';');
			tasks[i][0] = atoi(token.c_str());
			std::getline(ss, token, ';');
			tasks[i][1] = atoi(token.c_str());
			std::getline(ss, token, ';');
			tasks[i][2] = atoi(token.c_str());
		}

		int i = 0;

		while (std::getline(file, input)) {
			std::istringstream ss(input);
			std::string token;

			breaks.resize(i + 1);
			breaks[i].resize(2);

			std::getline(ss, token, ';');

			std::getline(ss, token, ';');
			breaks[i][1] = atoi(token.c_str());
			std::getline(ss, token, ';');
			breaks[i][0] = atoi(token.c_str());
			breaks[i][1] += breaks[i][0];
			
			i++;
		}
	}
	else {
		std::cout << "Nie odnaleziono pliku" << "\n";
	}

	file.close();
}
