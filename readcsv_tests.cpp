#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "convertcsv.h"
#include <fstream>
#include <cstdio> // std::remove
#include <nlohmann/json.hpp> // Optional, for parsing JSON in test (install with vcpkg)

using json = nlohmann::json;

void writeTempCSV(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

std::string readFileContents(const std::string& filename) {
    std::ifstream file(filename);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

TEST_CASE("readCSV handles well-formed CSV") {
    std::string filename = "test1.csv";
    writeTempCSV(filename, "name,age\nAlice,30\nBob,25");

    std::vector<std::vector<std::string>> data;
    REQUIRE(readCSV(filename, data, ','));
    REQUIRE(data.size() == 3);
    REQUIRE(data[0][0] == "name");
    REQUIRE(data[1][1] == "30");
    REQUIRE(data[2][0] == "Bob");

    std::remove(filename.c_str());
}

TEST_CASE("readCSV detects inconsistent column count") {
    std::string filename = "test_inconsistent.csv";
    writeTempCSV(filename, "id,name\n1,Alice\n2");

    std::vector<std::vector<std::string>> data;
    REQUIRE(readCSV(filename, data, ','));
    REQUIRE(data.size() == 3); // Still pushes inconsistent rows
    REQUIRE(data[2].size() == 1); // Second row is short

    std::remove(filename.c_str());
}

TEST_CASE("readCSV handles empty rows") {
    std::string filename = "test_empty.csv";
    writeTempCSV(filename, "a,b\n\n1,2");

    std::vector<std::vector<std::string>> data;
    REQUIRE(readCSV(filename, data, ','));
    REQUIRE(data.size() == 2); // Skips the empty row

    std::remove(filename.c_str());
}

TEST_CASE("convertToJSON produces expected output") {
    std::string csvFile = "input.csv";
    std::string jsonFile = "output.json";

    writeTempCSV(csvFile, "name,age\nAlice,30\nBob,25");
    std::vector<std::vector<std::string>> data;
    REQUIRE(readCSV(csvFile, data, ','));

    convertToJSON(data, jsonFile);

    std::string jsonContents = readFileContents(jsonFile);
    json parsed = json::parse(jsonContents);

    REQUIRE(parsed["name"].size() == 2);
    REQUIRE(parsed["age"][0] == "30");
    REQUIRE(parsed["name"][1] == "Bob");

    std::remove(csvFile.c_str());
    std::remove(jsonFile.c_str());
}

TEST_CASE("readCSV fails on nonexistent file") {
    std::vector<std::vector<std::string>> data;
    REQUIRE_FALSE(readCSV("nonexistent.csv", data, ','));
}
