#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Student {
    std::string name;
    int score;
};

int main() {
    std::vector<Student> students = {
        {"Alice", 85},
        {"Bob", 67},
        {"Charlie", 92},
        {"Diana", 74},
        {"Ethan", 58}
    };

    std::ofstream file("test_results.txt"); // create/open file

    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return 1;
    }

    // Print to console and file
    auto writeResult = [&](const std::string& text) {
        std::cout << text;
        file << text;
        };

    writeResult("=== Test Results ===\n\n");

    double total = 0;
    for (const auto& s : students) {
        std::string line = s.name + " - Score: " + std::to_string(s.score) +
            " - " + (s.score >= 60 ? "Pass" : "Fail") + "\n";
        writeResult(line);
        total += s.score;
    }

    double average = total / students.size();
    writeResult("\nClass Average: " + std::to_string(average) + "\n");

    file.close();

    std::cout << "\nResults have been written to test_results.txt\n";

    return 0;
}
