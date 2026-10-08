#include "StudentManager.h"

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

    if (!dataFile || !std::getline(dataFile, header)) {
        return false;
    }

    while (std::getline(dataFile, dataLine)) {
        if (dataLine.empty()) {
            continue;
        }

        Person student;
        if (student.readFileLine(dataLine)) {
            loadedStudents.push_back(student);
        }
    }

    if (loadedStudents.empty()) {
        return false;
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

const std::vector<Person>& StudentManager::students() const {
    return students_;
}
