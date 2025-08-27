#include <fstream>
#include <iostream>

int main() 
{
	std::fstream File;
	File.open("secretdata.txt", std::ios::out);
	if (File.is_open()) 
	{
		File << "Hello World" << std::endl;
	}
	
	File.close();

	std::fstream SecretNumberFile;
	SecretNumberFile.open("secretnumbers.txt", std::ios::in);
	if (SecretNumberFile.is_open()) 
	{
		int ReadNumber = 0;
		while (!SecretNumberFile.eof()) 
		{
			SecretNumberFile >> ReadNumber;
			std::cout << "tHeNuMbeR: " << ReadNumber << std::endl;
		}
	}

	SecretNumberFile.close();

	std::fstream SecretBinaryFile;
	SecretBinaryFile.open("secretbinary.try: ", std::ios::out | std::ios::binary);
	int TheNumber = 5;
	SecretBinaryFile.write((char*)&TheNumber, sizeof(TheNumber));
	SecretBinaryFile.close();

	std::fstream IncomingSecretBinaryFile;
	IncomingSecretBinaryFile.open("secretbinary.try: ", std::ios::out | std::ios::binary);
	if (IncomingSecretBinaryFile.is_open()) 
	{
		int TheNumber = 0;
		IncomingSecretBinaryFile.read((char*)&TheNumber, sizeof(TheNumber));
		std::cout << "secret BINARRY data: " << TheNumber << std::endl;
	}
	IncomingSecretBinaryFile.close();
	return 0;
}