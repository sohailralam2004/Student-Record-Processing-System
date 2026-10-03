#include "Person.h"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

bool loadStudentsFromFile(const std::string& fileName,
                          std::vector<Person>& students) {
    std::ifstream dataFile(fileName);
    std::string header;
    std::string dataLine;

    if (!dataFile || !std::getline(dataFile, header)) {
        return false;
    }

    while (std::getline(dataFile, dataLine)) {
        if (dataLine.empty()) {
            continue;
        }

        Person student;
        if (student.readFileLine(dataLine)) {
            students.push_back(student);
        }
    }

    return !students.empty();
}

int main() {
    Person student;
    std::vector<Person> students;

    int inputMode = 1;
    std::cout << "Choose data input (1 - manual, 2 - random, 3 - file): ";
    if (!(std::cin >> inputMode) || (inputMode < 1 || inputMode > 3)) {
        std::cerr << "Invalid input mode.\n";
        return 1;
    }

    if (inputMode == 1) {
        std::cout << "Enter: first name, surname, homework scores, -1, exam score\n";
        std::cout << "Example: Anna Smith 8 9 10 -1 9\n> ";

        if (!(std::cin >> student)) {
            std::cerr << "Invalid student data.\n";
            return 1;
        }
    } else if (inputMode == 2) {
        std::string firstName;
        std::string surname;
        int homeworkCount = 0;

        std::cout << "Enter first name, surname and homework count: ";
        if (!(std::cin >> firstName >> surname >> homeworkCount) ||
            homeworkCount < 0) {
            std::cerr << "Invalid random student data.\n";
            return 1;
        }

        std::random_device seed;
        std::mt19937 generator(seed());
        std::uniform_int_distribution<int> scoreDistribution(0, 10);

        std::vector<double> homework;
        for (int i = 0; i < homeworkCount; ++i) {
            homework.push_back(scoreDistribution(generator));
        }
        const double exam = scoreDistribution(generator);
        student = Person(firstName, surname, homework, exam);

        std::cout << "Random scores generated on the range 0..10.\n";
    } else {
        if (!loadStudentsFromFile("Students.txt", students)) {
            std::cerr << "Could not read student records from Students.txt.\n";
            return 1;
        }
        student = students.front();
        std::cout << students.size()
                  << " student records loaded into vector<Person>.\n";
    }

    int method = 1;
    std::cout << "Choose calculation method (1 - average, 2 - median): ";
    if (!(std::cin >> method) || (method != 1 && method != 2)) {
        std::cerr << "Invalid method. Average will be used.\n";
        method = 1;
    }

    const bool useMedian = method == 2;
    const double selectedHomeworkResult =
        useMedian ? student.homeworkMedian() : student.homeworkAverage();
    const double selectedFinalGrade =
        useMedian ? student.calculateFinalGradeByMedian()
                  : student.calculateFinalGrade();

    std::cout << "\nStudent: " << student << '\n';
    std::cout << "\n" << std::left << std::setw(15) << "Name"
              << std::setw(15) << "Surname"
              << std::right << std::setw(18)
              << (useMedian ? "Homework (Med.)" : "Homework (Avg.)")
              << std::setw(18)
              << (useMedian ? "Final (Med.)" : "Final (Avg.)") << '\n';
    std::cout << std::string(66, '-') << '\n';
    std::cout << std::left << std::setw(15) << student.firstName()
              << std::setw(15) << student.surname()
              << std::right << std::fixed << std::setprecision(2)
              << std::setw(18) << selectedHomeworkResult
              << std::setw(18) << selectedFinalGrade << '\n';

    // Simple checks that exercise the explicitly defined Rule of Three.
    Person copiedStudent(student);
    Person assignedStudent;
    assignedStudent = student;

    std::cout << "Copy constructor check: " << copiedStudent << '\n';
    std::cout << "Assignment operator check: " << assignedStudent << '\n';

    return 0;
}
