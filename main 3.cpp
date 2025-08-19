#include <iostream>
#include <cstring>



void removeWhitespace(char* input) {
	int length = strlen(input);
	int index = 0;

	for (int i = 0; i < length; ++i) {
		if (!isspace(input[i])) {
			input[index++] = input[i];
		}
	}
	input[index] = '\0'; // Null-terminate the modified string
}


int stringLength(const std::string & inputString)
{
	int count = 0;
	for (char c : inputString)
	{
		count++;
	}
	return count;


}
int main() 
{
	char Name[50] = "Hunter Hello Hunter!";
	Name[0] = 'H';

	char Empty[256] = "";

	int Length = strlen(Name);
	std::cout << Name << std::endl;

	// strcat(Empty, Name);
	// strcat_s(Empty, Name);
	strcat_s(Empty, 256, Name);

	char Input[50] = {};
	std::cin >> Input;

	std::cout << "You said that I can make a code:" << Input << std::endl;
	std::cout << "What is your favorite color:" << Input << std::endl;
	std::cout << "My favorite color is blue:" << Input << std::endl;

	std::string color;
    if (color == "Black") {
        std::cout << "Black is also a fruit." << std::endl;
    } else if (color == "Red") {
        std::cout << "Red? Like the color of roses?" << std::endl;
    } else {
        std::cout << "I haven't heard of that color before." << std::endl;
    }

	std::cout << stringLength("Goodspaceprogrammer") << std::endl; 
	// Output: 19
	std::cout << stringLength("Harrison St.") << std::endl;       
	// Output: 12

	// Test c - string to copy from
	const char* InputA = "The seeker comes and finds me in a special spot!";
	// Start: 0



    return 0;

	
	



}