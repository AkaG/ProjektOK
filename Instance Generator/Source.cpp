#include <iostream>
#include <fstream>

#include "Instance.h"

using namespace std;

int main() {
	Instance* instance = new Instance(50, 1);

	instance->generateTasks(10, 100);
	instance->generateBreaks();

	instance->saveToFile("Instance one");

	system("pause");
	return 0;
}