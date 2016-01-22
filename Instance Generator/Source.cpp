#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Instance.h"

using namespace std;

int main() {
	Instance* instance;

	for (int i = 0;i < 10;i++) {
		instance = new Instance(50+20*i, i);
		instance->generateTasks(100, 150);
		instance->generateBreaks();
		instance->saveToFile(std::to_string(i).append(".txt"));
		delete instance;
	}
	system("pause");
	return 0;
}