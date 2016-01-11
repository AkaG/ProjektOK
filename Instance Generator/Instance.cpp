#include "Instance.h"

using namespace std;

Instance::Instance(int number_of_tasks, int ID)
{
	this->ID = ID;
	this->number_of_tasks = number_of_tasks;
	this->number_of_breaks = (rand() % (number_of_tasks / 2 - 2)) + 2;

	tasks.resize(this->number_of_tasks);
	for (auto &i : tasks) {
		i.resize(3);
	}

	breaks.resize(this->number_of_breaks);
	for (auto &i : breaks) {
		i.resize(2);
	}
}

void Instance::generateTasks(int max, int min)
{
	this->max_task_length = max;
	this->min_task_length = min;

	for (int i = 0; i < number_of_tasks; i++) {
		tasks[i][0] = (rand() % (max_task_length - min_task_length)) + min_task_length;
		tasks[i][1] = (rand() % (max_task_length - min_task_length)) + min_task_length;
		tasks[i][2] = (rand() % (min_task_length*number_of_tasks + number_of_breaks * 50));
	}
}

void Instance::generateBreaks()
{
	int sumOfTasks = 0;
	int shortest = max_task_length;

	int minBreak = 5;
	int maxBreak = 50;

	for (int i = 0; i < number_of_tasks; i++) {
		sumOfTasks += tasks[i][0];
		if (tasks[i][0] < shortest)
			shortest = tasks[i][0];
	}

	breaks[0][0] = ((rand() % 3) + 1) * shortest;
	breaks[0][1] = breaks[0][0] + ((rand() % maxBreak) + minBreak);

	for (int i = 1; i < number_of_breaks; i++) {
		breaks[i][0] = breaks[i - 1][1] + ((rand() % (3 * max_task_length)) + min_task_length);
		breaks[i][1] = breaks[i][0] + ((rand() % maxBreak) + minBreak);
	}
}

void Instance::saveToFile(char * filename)
{
	std::fstream out(filename,	fstream::out);

	out << ID << endl;
	out << number_of_tasks << endl;

	for (auto task : tasks) {
		for (auto content : task) {
			out << content << ";";
		}
		out << endl;
	}
	
	int breakNumber = 1;
	for (auto pause : breaks) {
		out << breakNumber << ";";
		out << (pause[1] - pause[0]) << ";" << pause[0] << ";\n";
		breakNumber++;
	}

	out.close();
}
