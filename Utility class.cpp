#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

class StringUtils {
public:
    // Trim leading and trailing whitespace
    static std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // Convert string to uppercase
    static std::string toUpperCase(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    // Split string by a delimiter
    static std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

int main() {
    std::string text = "   Hello, World!   ";
    std::string trimmed = StringUtils::trim(text);
    std::cout << "Trimmed: '" << trimmed << "'" << std::endl;

    std::string upper = StringUtils::toUpperCase(trimmed);
    std::cout << "Uppercase: '" << upper << "'" << std::endl;

    std::string csv = "apple,banana,cherry";
    std::vector<std::string> fruits = StringUtils::split(csv, ',');
    std::cout << "Split: ";
    for (const auto& fruit : fruits) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;

    return 0;
}
