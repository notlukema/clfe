#pragma once

#include<iostream>

namespace thig
{

	class Thing1
	{
	public:
		Thing1()
		{
			std::cout << "Thing1 constructor\n";
		}
		~Thing1()
		{
			std::cout << "Thing1 destructor\n";
		}
		void boom()
		{
			std::cout << "boom\n";
		}
	};

	class Thing2 : public Thing1
	{
	public:
		Thing2()
		{
			std::cout << "Thing2 constructor\n";
		}
		~Thing2()
		{
			std::cout << "Thing2 destructor\n";
		}
	};

}