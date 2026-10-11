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
#include <type_traits>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;
using Milliseconds = std::chrono::duration<double, std::milli>;
using StudentComparator = bool (*)(const Person&, const Person&);

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
struct ContainerRun {
    std::size_t records = 0;
    std::size_t passed = 0;
    std::size_t failed = 0;
    double readMilliseconds = 0.0;
    double sortMilliseconds = 0.0;
    double splitMilliseconds = 0.0;
    double writeMilliseconds = 0.0;
    double totalMilliseconds = 0.0;
};

template <typename Container>
void writeStudents(const std::filesystem::path& fileName,
                   const Container& students) {
    std::ofstream outputFile(fileName);
    if (!outputFile) {
        throw StudentException("Cannot create output file: " +
                               fileName.string());
    }

    outputFile << "Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n";
    for (const Person& student : students) {
        outputFile << student.firstName() << ' ' << student.surname();
        for (const double score : student.homeworkScores()) {
            outputFile << ' ' << score;
        }
        outputFile << ' ' << student.exam() << '\n';
    }

    if (!outputFile) {
        throw StudentException("Error while writing output file: " +
                               fileName.string());
    }
}

template <typename Container>
ContainerRun<Container> benchmarkContainer(
    const std::filesystem::path& inputFile,
    const std::filesystem::path& outputDirectory,
    const std::string& containerName) {
    ContainerRun<Container> result;
    const auto totalStart = Clock::now();
    Container students;

    const auto readStart = Clock::now();
    std::ifstream dataFile(inputFile);
    if (!dataFile) {
        throw StudentException("Cannot open input file: " + inputFile.string());
    }

    std::string header;
    if (!std::getline(dataFile, header)) {
        throw StudentException("Input file is empty: " + inputFile.string());
    }
    if (header.find("Name") == std::string::npos ||
        header.find("Surname") == std::string::npos) {
        throw StudentException("Invalid header in input file: " +
                               inputFile.string());
    }

    std::string dataLine;
    std::size_t lineNumber = 1;
    while (std::getline(dataFile, dataLine)) {
        ++lineNumber;
        if (dataLine.empty()) {
            continue;
        }

        Person student;
        if (!student.readFileLine(dataLine)) {
            throw StudentException("Invalid student record at line " +
                                   std::to_string(lineNumber));
        }
        students.push_back(student);
    }
    if (students.empty()) {
        throw StudentException("Input file contains no student records: " +
                               inputFile.string());
    }
    const auto readEnd = Clock::now();

    const auto sortStart = Clock::now();
    sortStudents(students);
    const auto sortEnd = Clock::now();

    Container passedStudents;
    Container failedStudents;
    const auto splitStart = Clock::now();
    for (const Person& student : students) {
        if (student.calculateFinalGrade() >= 5.0) {
            passedStudents.push_back(student);
        } else {
            failedStudents.push_back(student);
        }
    }
    const auto splitEnd = Clock::now();

    const auto writeStart = Clock::now();
    writeStudents(outputDirectory / (containerName + "_passed.txt"),
                  passedStudents);
    writeStudents(outputDirectory / (containerName + "_failed.txt"),
                  failedStudents);
    const auto writeEnd = Clock::now();
    const auto totalEnd = Clock::now();

    const auto elapsed = [](const auto start, const auto end) {
        return Milliseconds(end - start).count();
    };
    result.records = students.size();
    result.passed = passedStudents.size();
    result.failed = failedStudents.size();
    result.readMilliseconds = elapsed(readStart, readEnd);
    result.sortMilliseconds = elapsed(sortStart, sortEnd);
    result.splitMilliseconds = elapsed(splitStart, splitEnd);
    result.writeMilliseconds = elapsed(writeStart, writeEnd);
    result.totalMilliseconds = elapsed(totalStart, totalEnd);
    return result;
}

template <typename Container>
void printResult(const std::string& name, const ContainerRun<Container>& result) {
    std::cout << name << ',' << result.records << ',' << result.passed << ','
              << result.failed << ',' << std::fixed << std::setprecision(3)
              << result.readMilliseconds << ',' << result.sortMilliseconds << ','
              << result.splitMilliseconds << ',' << result.writeMilliseconds << ','
              << result.totalMilliseconds << '\n';
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: container_benchmark <input-file> <output-directory>\n";
        return 1;
    }

    try {
        const std::filesystem::path inputFile(argv[1]);
        const std::filesystem::path outputDirectory(argv[2]);
        std::filesystem::create_directories(outputDirectory);

        std::cout << "Container,Records,Passed,Failed,Read_ms,Sort_ms,"
                     "Split_ms,Write_ms,Total_ms\n";
        printResult("vector", benchmarkContainer<std::vector<Person>>(
                                inputFile, outputDirectory, "vector"));
        printResult("list", benchmarkContainer<std::list<Person>>(
                              inputFile, outputDirectory, "list"));
        printResult("deque", benchmarkContainer<std::deque<Person>>(
                               inputFile, outputDirectory, "deque"));
        return 0;
    } catch (const StudentException& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    } catch (const std::filesystem::filesystem_error& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
