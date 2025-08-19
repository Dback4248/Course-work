#include <iostream>

int main() 
{

	int num{ 0 };

	std::cout << "Please enter the amount of numbers: ";
	std::cin >> num;

	for (int i = 1; i <= num; i++)
	{
		if (i % 3 == 0 && i % 5 == 0) 
		{
			std::cout << "Fizz Buzz" << "\n";
		}
		else if (i % 5 == 0) 
		{
			std::cout << "Buzz" << "\n";
		}
		else if (i % 3 == 0) 
		{
			std::cout << "Fizz" << "\n";
		}
		else {
			std::cout << i << "\n";
		}
	}
}