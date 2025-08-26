#include <iostream>
using namespace std;

int SumTwoIntPtrs(int* a, int* b)
{
    return *a + *b;
}

int main() 
{
    int Val = 2;
    int OtherVal = 4;

    int* A = &Val;
    int* B = &OtherVal;

    // call the swap function here

    std::cout << Val << std::endl;   // this should read 2 beacause Val is unchanged
    std::cout << OtherVal << std::endl;  // this should read 4 beacuse OtherVal is unchanged

    std::cout << *A << std::endl; // this should read 4 because A is now pointing to the value of OtherVal
    std::cout << *B << std::endl; // this shoald read 2 because B is now pointing to the value of Val
    
    // Returns a pointer to a dynamic integer array
    // - size defines the length of the array

    int* ZeroArray(size_t size);

    // instantiate two pointers to heap-allocated integers
    int* NumAptr = new int(10);
    int* NumBptr = new int(15);

    std::cout << "numA: " << *NumAptr << std::endl;
    std::cout << "numB: " << *NumBptr << std::endl;

    // provide them as args
    int Res = SumTwoIntPtrs(NumAptr, NumBptr);

    std::cout << "summ: " << Res << std::endl;

    int array[] = { 1,5,9,7,9 };

    int* arrayPtr = array;
    cout << arrayPtr[4];

    int size = 5;
    int* arr = new int[size];  // Allocate memory for an array

    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;       // Assign values
    }

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " "; // Print values
    }
    cout << endl;

    delete[] arr;             // Free the allocated memory
    arr = nullptr;            // Avoid dangling pointer

    // clean up
    delete NumAptr;
    delete NumBptr;

    // the array is gonna continue throughout the whole code and end with a bang
    return 0;
}
