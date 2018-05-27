#include <iostream>
#include <stdio.h>
#include <ctime>
#include "LinkedList.h"

void someTest()
{
	srand(time(NULL));
	LinkedList<int> list;

	for (size_t i = 0; i < 10; i++)
		list.insert(0, i);
	for (size_t i = 0; i < 10; i++)
		list.push_front(i);

	list.show();
	list.remove(9);
	list.show();
	list.remove(0);
	list.show();
	list.remove(1);
	list.show();

	std::cout << "[1]\t" << list[1] << std::endl;

	std::cout << std::endl;
}

int main(int argc, char *argv[])
{
	someTest();
	return 0;
}
