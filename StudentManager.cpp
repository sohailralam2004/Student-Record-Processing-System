#include "StudentManager.h"
#include "StudentException.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

bool StudentManager::loadFromFile(const std::string& fileName) {
    std::ifstream dataFile(fileName);
    std::string header;
    std::string dataLine;
    std::vector<Person> loadedStudents;

    if (!dataFile) {
        throw StudentException("Cannot open input file: " + fileName);
    }
    if (!std::getline(dataFile, header)) {
        throw StudentException("Input file is empty: " + fileName);
    }
    if (header.find("Name") == std::string::npos ||
        header.find("Surname") == std::string::npos) {
        throw StudentException("Invalid header in input file: " + fileName);
    }

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
        loadedStudents.push_back(student);
    }

    if (loadedStudents.empty()) {
        throw StudentException("Input file contains no student records: " +
                               fileName);
    }

    students_ = loadedStudents;
    return true;
}

void StudentManager::sortBySurname() {
    std::sort(students_.begin(), students_.end(),
              [](const Person& left, const Person& right) {
                  if (left.surname() != right.surname()) {
                      return left.surname() < right.surname();
                  }
                  return left.firstName() < right.firstName();
              });
}

void StudentManager::printReport(std::ostream& output) const {
    output << "\n" << std::left << std::setw(15) << "Name"
           << std::setw(15) << "Surname"
           << std::right << std::setw(16) << "Final (Avg.)"
           << " | " << std::setw(14) << "Final (Med.)" << '\n';
    output << std::string(66, '-') << '\n';

    output << std::fixed << std::setprecision(2);
    for (const Person& student : students_) {
        output << std::left << std::setw(15) << student.firstName()
               << std::setw(15) << student.surname()
               << std::right << std::setw(16)
               << student.calculateFinalGrade() << " | "
               << std::setw(14) << student.calculateFinalGradeByMedian()
               << '\n';
    }
}

void StudentManager::splitByFinalGrade(const std::string& passedFileName,
                                       const std::string& failedFileName) const {
    std::vector<const Person*> passedStudents;
    std::vector<const Person*> failedStudents;
    passedStudents.reserve(students_.size());
    failedStudents.reserve(students_.size());

    for (const Person& student : students_) {
        if (student.calculateFinalGrade() >= 5.0) {
            passedStudents.push_back(&student);
        } else {
            failedStudents.push_back(&student);
        }
    }

    const auto bySurnameAndName = [](const Person* left, const Person* right) {
        if (left->surname() != right->surname()) {
            return left->surname() < right->surname();
        }
        return left->firstName() < right->firstName();
    };
    std::sort(passedStudents.begin(), passedStudents.end(), bySurnameAndName);
    std::sort(failedStudents.begin(), failedStudents.end(), bySurnameAndName);

    std::ofstream passedFile(passedFileName);
    if (!passedFile) {
        throw StudentException("Cannot create output file: " + passedFileName);
    }

    std::ofstream failedFile(failedFileName);
    if (!failedFile) {
        throw StudentException("Cannot create output file: " + failedFileName);
    }

    const std::string header = "Name Surname HW1 HW2 HW3 HW4 HW5 Exam\n";
    passedFile << header;
    failedFile << header;

    const auto writeStudent = [](std::ostream& output, const Person& student) {
        output << student.firstName() << ' ' << student.surname();
        for (const double score : student.homeworkScores()) {
            output << ' ' << score;
        }
        output << ' ' << student.exam() << '\n';
    };

    for (const Person* student : passedStudents) {
        writeStudent(passedFile, *student);
    }
    for (const Person* student : failedStudents) {
        writeStudent(failedFile, *student);
    }

    if (!passedFile || !failedFile) {
        throw StudentException("Error while writing split output files.");
    }
}

const std::vector<Person>& StudentManager::students() const {
    return students_;
}
