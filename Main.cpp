#include <iostream>
using namespace std;
int fibonacci(int n) {
	if (n <= 1)
		return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}
int main() 
{
	// varibles - storing data
	// TYPE IDENTIFIER
	int Cash = 0; // whole numbers
	float Distance = 15.3f; // numbers with decimals
	double Cost = 3.50; // MORE PRECISION
	bool bIsProgrammingRad = false; // true/false

	const char* Name = "John Madden"; // srting!


	std::cout << "Hello World!" << std::endl;
	std::cout << "Current Dollar: $" << Cash << std::endl;

	
	int Total = 3 + 7;              // exactly 10
	float MyCash = 5.00f + .50f;    // about 5.50f
	float OurCash = MyCash + 3.75f; // works with variables too!

	// assigns the value '1' to the varble 'defaultLevel'
	int DefaultLevel = 1;
	
	// adds '1' and '2' together, resulting in a sum of '3'
	int Sum = 1 + 2;

	int Num = 9001;
	bool bIsJokeEnabled = true;

	if (Num < 100)
	{
		std::cout << "That's a big number.";
	}
	else if (Num > 0)
	{
		std::cout << "That's a small number.";
	}
	else
	{
		std::cout << "Negatives?!";
	}

	// Add a new line
	std::cout << std::endl;

	if (Num == 1 && bIsJokeEnabled)
	{
		std::cout << "One is a lonely number.";
	}
	
	int Numbers[5] = {};

	Numbers[0] = 2;
	Numbers[1] = 4;
	Numbers[2] = 6;
	Numbers[3] = 8;
	Numbers[4] = 10;

	// read element at an index
	std::cout << Numbers[0] << std::endl;

	// read element using a loop
	for (size_t i = 0; i < 5; ++i)
	{
		std::cout << Numbers[i] << std::endl;
	}
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
	int n;
	cout << "Enter the number of terms: ";
	cin >> n;
	cout << "Fibonacci Sequence: ";
	for (int i = 0; i < n; i++) {
		cout << fibonacci(i) << " ";
	}
	cout << endl;
	return 0;

};

	