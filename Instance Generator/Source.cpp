#include <iostream>
#include <fstream>

#include "Instance.h"

using namespace std;

int main() {
	Instance* instance;

	for (int i = 0;i < 5;i++) {
		instance = new Instance(50+20*i, i);
		instance->generateTasks(100, 150);
		instance->generateBreaks();
		instance->saveToFile(1);
	}
	system("pause");
	return 0;
}