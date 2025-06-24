#include "convertcsv.h"

int main() {
    std::string inputFilename, outputFilename;
    char delimiter;

    std::cout << "Enter the input CSV file name: ";
    std::cin >> inputFilename;
    std::cout << "Enter the output JSON file name: ";
    std::cin >> outputFilename;
    std::cout << "Enter the delimiter (default is ','): ";
    std::cin >> delimiter;

    std::vector<std::vector<std::string>> data;
    if (!readCSV(inputFilename, data, delimiter)) {
        return 1; // Exit on error
    }

    convertToJSON(data, outputFilename);
    return 0;
}
