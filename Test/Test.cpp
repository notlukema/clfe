#include <thread>
#include <mutex>
#include <iostream>

#include "f/thig.h"

using namespace thig;
using namespace std;

mutex m;

void func()
{
	for (int i = 0; i < 1000; i++)
	{
		increment();
		m.lock();
		std::cout << "thread: " << gnum() << "\n";
		m.unlock();
	}
}

int main()
{

	thread t(func);

	//func();
	for (int i = 0; i < 1000; i++)
	{
		increment();
		m.lock();
		std::cout << "this: " << gnum() << "\n";
		m.unlock();
	}

	t.join();

	return 0;
}
