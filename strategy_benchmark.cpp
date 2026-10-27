#include "Person.h"
#include "StudentException.h"

#include <algorithm>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;
using Milliseconds = std::chrono::duration<double, std::milli>;

bool compareStudents(const Person& left, const Person& right) {
    if (left.surname() != right.surname()) {
        return left.surname() < right.surname();
    }
    return left.firstName() < right.firstName();
}

template <typename Container>
void sortStudents(Container& students) {
    std::sort(students.begin(), students.end(), compareStudents);
}

void sortStudents(std::list<Person>& students) {
    students.sort(compareStudents);
}

template <typename Container>
void loadStudents(const std::filesystem::path& inputFile,
                  Container& students) {
    std::ifstream input(inputFile);
    if (!input) {
        throw StudentException("Cannot open input file: " +
                               inputFile.string());
    }

    std::string header;
    if (!std::getline(input, header)) {
        throw StudentException("Input file is empty: " + inputFile.string());
    }
    if (header.find("Name") == std::string::npos ||
        header.find("Surname") == std::string::npos) {
        throw StudentException("Invalid input header: " + inputFile.string());
    }

    std::string line;
    std::size_t lineNumber = 1;
    while (std::getline(input, line)) {
        ++lineNumber;
        if (line.empty()) {
            continue;
        }

        Person student;
        if (!student.readFileLine(line)) {
            throw StudentException("Invalid student record at line " +
                                   std::to_string(lineNumber));
        }
        students.push_back(student);
    }

    if (students.empty()) {
        throw StudentException("No student records found in: " +
                               inputFile.string());
    }
}

template <typename Container>
void writeStudents(const std::filesystem::path& outputFile,
                   const Container& students) {
    std::ofstream output(outputFile);
    if (!output) {
        throw StudentException("Cannot create output file: " +
                               outputFile.string());
    }

    output << "Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n";
    for (const Person& student : students) {
        output << student.firstName() << ' ' << student.surname();
        for (double score : student.homeworkScores()) {
            output << ' ' << score;
        }
        output << ' ' << student.exam() << '\n';
    }

    if (!output) {
        throw StudentException("Error while writing: " +
                               outputFile.string());
    }
}

template <typename Container>
struct Measurement {
    std::string container;
    int strategy = 0;
    std::size_t original = 0;
    std::size_t passed = 0;
    std::size_t failed = 0;
    double readMilliseconds = 0.0;
    double sortMilliseconds = 0.0;
    double splitMilliseconds = 0.0;
    double writeMilliseconds = 0.0;
    double totalMilliseconds = 0.0;
};

double elapsedMilliseconds(Clock::time_point start,
                           Clock::time_point finish) {
    return Milliseconds(finish - start).count();
}

template <typename Container>
Measurement<Container> runStrategyOne(
    const std::filesystem::path& inputFile,
    const std::filesystem::path& outputDirectory,
    const std::string& containerName) {
    Measurement<Container> result;
    result.container = containerName;
    result.strategy = 1;
    const auto totalStart = Clock::now();

    Container students;
    const auto readStart = Clock::now();
    loadStudents(inputFile, students);
    const auto readEnd = Clock::now();

    const auto sortStart = Clock::now();
    sortStudents(students);
    const auto sortEnd = Clock::now();

    Container passed;
    Container failed;
    const auto splitStart = Clock::now();
    for (const Person& student : students) {
        if (student.calculateFinalGrade() >= 5.0) {
            passed.push_back(student);
        } else {
            failed.push_back(student);
        }
    }
    const auto splitEnd = Clock::now();

    const auto writeStart = Clock::now();
    writeStudents(outputDirectory /
                  (containerName + "_strategy1_passed.txt"), passed);
    writeStudents(outputDirectory /
                  (containerName + "_strategy1_failed.txt"), failed);
    const auto writeEnd = Clock::now();
    const auto totalEnd = Clock::now();

    if (passed.size() + failed.size() != students.size()) {
        throw StudentException("Strategy 1 lost student records");
    }

    result.original = students.size();
    result.passed = passed.size();
    result.failed = failed.size();
    result.readMilliseconds = elapsedMilliseconds(readStart, readEnd);
    result.sortMilliseconds = elapsedMilliseconds(sortStart, sortEnd);
    result.splitMilliseconds = elapsedMilliseconds(splitStart, splitEnd);
    result.writeMilliseconds = elapsedMilliseconds(writeStart, writeEnd);
    result.totalMilliseconds = elapsedMilliseconds(totalStart, totalEnd);
    return result;
}

template <typename Container>
Measurement<Container> runStrategyTwo(
    const std::filesystem::path& inputFile,
    const std::filesystem::path& outputDirectory,
    const std::string& containerName) {
    Measurement<Container> result;
    result.container = containerName;
    result.strategy = 2;
    const auto totalStart = Clock::now();

    Container students;
    const auto readStart = Clock::now();
    loadStudents(inputFile, students);
    const auto readEnd = Clock::now();
    const std::size_t originalSize = students.size();

    const auto sortStart = Clock::now();
    sortStudents(students);
    const auto sortEnd = Clock::now();

    Container failed;
    const auto splitStart = Clock::now();
    for (auto iterator = students.begin(); iterator != students.end();) {
        if (iterator->calculateFinalGrade() < 5.0) {
            failed.push_back(std::move(*iterator));
            iterator = students.erase(iterator);
        } else {
            ++iterator;
        }
    }
    const auto splitEnd = Clock::now();

    const auto writeStart = Clock::now();
    writeStudents(outputDirectory /
                  (containerName + "_strategy2_passed.txt"), students);
    writeStudents(outputDirectory /
                  (containerName + "_strategy2_failed.txt"), failed);
    const auto writeEnd = Clock::now();
    const auto totalEnd = Clock::now();

    if (students.size() + failed.size() != originalSize) {
        throw StudentException("Strategy 2 lost student records");
    }

    result.original = originalSize;
    result.passed = students.size();
    result.failed = failed.size();
    result.readMilliseconds = elapsedMilliseconds(readStart, readEnd);
    result.sortMilliseconds = elapsedMilliseconds(sortStart, sortEnd);
    result.splitMilliseconds = elapsedMilliseconds(splitStart, splitEnd);
    result.writeMilliseconds = elapsedMilliseconds(writeStart, writeEnd);
    result.totalMilliseconds = elapsedMilliseconds(totalStart, totalEnd);
    return result;
}

template <typename Container>
void printResult(const Measurement<Container>& result) {
    std::cout << result.container << ',' << result.strategy << ','
              << result.original << ',' << result.passed << ','
              << result.failed << ',' << std::fixed << std::setprecision(3)
              << result.readMilliseconds << ',' << result.sortMilliseconds
              << ',' << result.splitMilliseconds << ','
              << result.writeMilliseconds << ',' << result.totalMilliseconds
              << '\n';
}

template <typename Container>
void runSelectedStrategies(int strategy,
                           const std::filesystem::path& inputFile,
                           const std::filesystem::path& outputDirectory,
                           const std::string& containerName) {
    if (strategy == 1 || strategy == 3) {
        printResult(runStrategyOne<Container>(inputFile, outputDirectory,
                                              containerName));
    }
    if (strategy == 2 || strategy == 3) {
        printResult(runStrategyTwo<Container>(inputFile, outputDirectory,
                                              containerName));
    }
}

void runSelectedContainer(int strategy,
                          int containerChoice,
                          const std::filesystem::path& inputFile,
                          const std::filesystem::path& outputDirectory) {
    if (containerChoice == 1 || containerChoice == 4) {
        runSelectedStrategies<std::vector<Person>>(
            strategy, inputFile, outputDirectory, "vector");
    }
    if (containerChoice == 2 || containerChoice == 4) {
        runSelectedStrategies<std::list<Person>>(
            strategy, inputFile, outputDirectory, "list");
    }
    if (containerChoice == 3 || containerChoice == 4) {
        runSelectedStrategies<std::deque<Person>>(
            strategy, inputFile, outputDirectory, "deque");
    }
}

int readChoice(const std::string& prompt, int minimum, int maximum) {
    int choice = 0;
    std::cout << prompt;
    if (!(std::cin >> choice) || choice < minimum || choice > maximum) {
        throw StudentException("Invalid menu choice");
    }
    return choice;
}

}  // namespace

int main(int argc, char* argv[]) {
    try {
        std::filesystem::path inputFile;
        std::filesystem::path outputDirectory;
        int strategy = 0;
        int containerChoice = 0;

        if (argc == 3) {
            inputFile = argv[1];
            outputDirectory = argv[2];
            strategy = 3;
            containerChoice = 4;
        } else if (argc == 5) {
            inputFile = argv[1];
            outputDirectory = argv[2];
            strategy = std::stoi(argv[3]);
            containerChoice = std::stoi(argv[4]);
            if (strategy < 1 || strategy > 3 ||
                (containerChoice < 1 || containerChoice > 4)) {
                throw StudentException("Invalid command-line choice");
            }
        } else if (argc == 1) {
            std::string inputName;
            std::string outputName;
            std::cout << "Input file: ";
            std::cin >> inputName;
            std::cout << "Output directory: ";
            std::cin >> outputName;
            inputFile = inputName;
            outputDirectory = outputName;
            strategy = readChoice(
                "Strategy (1=copy to two containers, "
                "2=erase failed, 3=both): ", 1, 3);
            containerChoice = readChoice(
                "Container (1=vector, 2=list, 3=deque, 4=all): ", 1, 4);
        } else {
            std::cerr << "Usage: strategy_benchmark <input-file> "
                         "<output-directory> [strategy] [container]\n";
            return 1;
        }

        std::filesystem::create_directories(outputDirectory);
        std::cout << "Container,Strategy,Records,Passed,Failed,Read_ms,"
                     "Sort_ms,Split_ms,Write_ms,Total_ms\n";
        runSelectedContainer(strategy, containerChoice, inputFile,
                             outputDirectory);
    } catch (const StudentException& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
